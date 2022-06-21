/* EXTOLL Net driver */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>

#include <linux/sched.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/errno.h>  /* error codes */
#include <linux/types.h>  /* size_t */
#include <linux/interrupt.h> /* mark_bh */
#include <linux/list.h>

#include <linux/slab.h>		//kmem lookaside cache 
#include <linux/in.h>
#include <linux/netdevice.h>   /* struct device, and other headers */
#include <linux/etherdevice.h> /* eth_type_trans */
#include <linux/ip.h>          /* struct iphdr */
#include <linux/tcp.h>         /* struct tcphdr */
#include <linux/skbuff.h>
#include <linux/if_arp.h>

#include "arch_define.h"
#ifdef MICEXTOLL
#include "micextoll.h"
#include "extoll_kernel.h"
#endif


#include "extolldrv.h"
#include "atu2_drv.h"
#include "extoll_kapi.h"
#include "extolldrv.h"
#include "extoll_rf_sysfs.h"
#include "velo2drv.h"

#include <linux/in6.h>
#include <asm/checksum.h>

//preallocate SKB for RMA RX?
//#define RXSKB

//in jiffies?
#define EXN_TIMEOUT 5

#define RMA_FREE_BUFFER_SIZE 1024 

MODULE_AUTHOR("Sarah Neuwirth");
MODULE_LICENSE("GPL");

/*
 * Do we run in NAPI mode?
 */
static int use_napi = 0;
module_param(use_napi, int, 0);

static int napi_velo_budget = 64;
module_param(napi_velo_budget, int, 0);

static int napi_rma_budget = 64;
module_param(napi_rma_budget, int, 0);



static int timeout = EXN_TIMEOUT;
module_param(timeout, int, 0);

static int velo_threshold = 120;
module_param(velo_threshold, int, 0);

static int default_nodeid=-1;
module_param(default_nodeid,int,0);

int pool_size = 128;
module_param(pool_size, int, 0);

int exn_no_rx_csum=1;
module_param(exn_no_rx_csum, int, 0);

int exn_no_tx_csum=1;
module_param(exn_no_tx_csum, int, 0);


#define EXN_MAC0 0x2e
#define EXN_MAC1 0x87
#define EXN_MAC2 0x04
#define EXN_MAC3 0x07

int mac0 = EXN_MAC0;
module_param(mac0,int,0);
int mac1 = EXN_MAC1;
module_param(mac1,int,0);
int mac2 = EXN_MAC2;
module_param(mac2,int,0);
int mac3 = EXN_MAC3;
module_param(mac3,int,0);

#define MAX_EXN_LEN 65536

uint32_t rma_mtu = 496;
#define RMA_MTU	rma_mtu
/*
 * A structure representing an in-flight packet.
 * Used for multi velo messages.
 */
struct exn_packet {
    struct  list_head list;
    struct  net_device *dev;
    int     datalen;
    int     pcount;
    u8      data[MAX_EXN_LEN]; // Used to store incoming data fragments
    uint32_t srcid;
    uint8_t tag;
};

typedef struct exn_packet packet;

struct exn_rma_skb_buffer {
	struct list_head list;
	void *local_address;
	struct sk_buff *skb;
	unsigned int NLA;
//	unsigned int age; //count how many times we have seen this entry, without matching it, works, because new entries are added to the end of the list
};
 /*
 * This structure is private to each device. It is used to pass
 * packets in and out, so there is place for a packet
 */
struct exn_priv {
    struct net_device_stats stats;
    int status;
    struct exn_packet *ppool;
    struct exn_packet *rx_queue;  /* List of incoming packets */

    uint16_t nodeid;
    RMA2_Handle* rhandle;
    VELO2_Handle* vhandle;
    int vvpid;
    int rvpid;	

    rma2_i_handler* rma2_handler;
    velo2_i_handler* velo_handler;
	
    int npackets;
    int tx_packetlen;
    u8 *tx_packetdata;
    struct sk_buff *skb;
    spinlock_t lock;
    struct net_device *dev;
   
    // Separate NAPI structs per FU
    struct napi_struct napi_velo;
    struct napi_struct napi_rma;

    //buffer for skbs send/received via rma
    //those buffers are a linux kenrel style linked list, here stands only the list header.
    struct list_head rma_send_buffer;
    struct list_head rma_recv_buffer;
//    struct list_head rma_free_buffer;
    spinlock_t rma_lock; //TODO: finer locking for rma... maybe one lock for the send, recv queue and the pool each
    spinlock_t velo_lock; //for velo debugging

    struct kmem_cache *rma_queue_cache;
    //struct workqueue_struct *rma_queue;
};

/*
 * The devices
 */
struct net_device *exn_devs[1];
#ifdef RXSKB
static struct sk_buff *skb=0;
#endif

#define DEV exn_devs[0]

//forward declaration of functions
#if 0
static void exn_tx_timeout(struct net_device *dev);
#endif
static void exn_regular_velo_interrupt(int vpid, snq_entry_t*);
static void exn_regular_rma_interrupt(int vpid, snq_entry_t*);

// NAPI IRQ Handlers
static void exn_napi_velo_interrupt(int vpid, snq_entry_t*);
static void exn_napi_rma_interrupt(int vpid, snq_entry_t*);

static void exn_rx_rma_start(void); //TODO: better name for this function, describing what it actually does
static void exn_regular_velo_tasklet(void);
EKVCL_DECLARE_TASKLET(exn_rma_tasklet, (void *)&exn_rx_rma_start);
EKVCL_DECLARE_TASKLET(exn_velo_tasklet, (void *)&exn_regular_velo_tasklet);


void exn_rma2_wcb_cb(struct kapi_wcb_info* info)
{
  pr_debug("rma2_wcb_cb called\n");
  netif_wake_queue(exn_devs[0]);
}

void exn_velo2_wcb_cb(struct kapi_wcb_info* info)
{
  pr_debug("velo2_wcb_cb_called\n");
  netif_wake_queue(exn_devs[0]);
}

/*
 * Set up a device's packet pool.
 */
static inline void exn_setup_pool(struct net_device *dev) {
    struct exn_priv *priv = netdev_priv(dev);
    int i;
    struct exn_packet *pkt;

    netdev_dbg(DEV,"setting up a pool of %d entries\n",pool_size);
    for (i = 0; i < pool_size; i++) {
		pkt = kmalloc (sizeof (struct exn_packet), GFP_KERNEL);
		if (pkt == NULL) {
			netdev_alert(DEV,"Ran out of memory allocating packet pool\n");
			return;
		}
		pkt->dev = dev;
		pkt->tag=0;
		pkt->srcid=0;
		pkt->datalen=0;
		
		list_add(&(pkt->list), &(priv->ppool->list));		
	}
}

static inline void exn_teardown_pool(struct net_device *dev) {
    struct exn_priv *priv = netdev_priv(dev);
    struct list_head *pos, *q;
    struct exn_packet *tmp;
    
    if(list_empty(&(priv->ppool->list)) == 0){
		list_for_each_safe(pos, q, &(priv->ppool->list)){
			tmp = list_entry(pos, struct exn_packet, list);
			list_del(&(tmp->list));
			kfree (tmp);
		}
	}
}    

//release a packet to the free pool
static inline void exn_free_packet(struct exn_packet *pkt) {
	struct exn_priv *priv = netdev_priv(pkt->dev);
	
	list_add(&(pkt->list), &(priv->ppool->list));	
}

static inline struct exn_packet *exn_get_packet(struct net_device *dev) {
	struct exn_priv *priv = netdev_priv(dev);
	struct exn_packet *pkt=0;
  
	//if free list is emtpy add some more packets to it
	if(list_empty(&(priv->ppool->list))){
		exn_setup_pool(dev);
	}

	//get the first entry, remove it and return it
	pkt=list_first_entry(&(priv->ppool->list), struct exn_packet, list);
	list_del_init(&(pkt->list));
	return pkt;  
}

static void exn_nw_state(uint64_t state)
{
    switch (state) {
      case EXTOLL_NW_STATE_UC: netdev_info(DEV,"network not configured. EXN dormant.\n");
                            break;
      case EXTOLL_NW_STATE_C: netdev_info(DEV,"network configured. EXN up.\n");
                            break;
      case EXTOLL_NW_STATE_S: netdev_info(DEV,"network stopped. EXN dormant.\n");
                            break;
    default: netdev_info(DEV,"network state is unknown (%lld). EXN dormant.\n",state);
    }
    if (state==EXTOLL_NW_STATE_C) {
      uint64_t node=get_extoll_rf_info_rf_node();
      uint16_t nodeid=(node>>24l) & 0xffff; 
      DEV->dev_addr[4] = nodeid >> 8;
      DEV->dev_addr[5] = nodeid & 0xff;      
      velo2_set_tx_id(EXTOLL_VPID_NET,nodeid,EXTOLL_VPID_NET);

      netif_carrier_on(DEV);
    }
    else
      netif_carrier_off(DEV);

}

/** RMA unfinished transmissions buffer and helper functions
*/

//TODO: This and the RMA_MTU value should be in the kernel api
static inline unsigned int exn_rma_noti_address_offset(int len) {
	return ((len-1)/RMA_MTU)*RMA_MTU;
}

/*
static void exn_rma_pool_init(unsigned int size, struct list_head *pool)
{
	struct exn_rma_skb_buffer *new = NULL;
	int i = 0;

	for(i=0; i<size; i++) {
		new = kmalloc(sizeof(*new), GFP_KERNEL);
		if(new == NULL) {
			printk(KERN_ALERT "Out of memory while setting up pool for unfinished RMA transactions.\n");
			return;
		}
		list_add(&new->list, pool);
	}
}

static void exn_rma_pool_free(struct list_head *pool)
{
	struct list_head *pos, *q;
	struct exn_rma_skb_buffer *tmp;

	list_for_each_safe(pos, q, pool) {
		tmp = list_entry(pos, struct exn_rma_skb_buffer, list);
		list_del(pos);
		kfree(tmp);
	}
}
*/

/*
static struct exn_rma_skb_buffer *exn_rma_get_free_buffer(struct list_head *pool)
{
	struct list_head *free_head = NULL;
	struct exn_rma_skb_buffer *free_buffer = NULL;
	
	if(list_empty(pool)) {
		return NULL;
	} else {
		free_head = pool->next;
		free_buffer = list_entry(free_head, struct exn_rma_skb_buffer,list);
		list_del(free_head);
		return free_buffer;
	}
}

static void exn_rma_return_buffer(struct exn_rma_skb_buffer *free, struct list_head *pool)
{
	list_del(&free->list);
	free->skb = NULL;
	free->local_address = NULL;
	//free->age=0;
	list_add(&free->list, pool);
}
*/

static unsigned long put_skb(struct list_head *buffer, void *local_address, struct sk_buff *skb, int len)
{
	struct exn_priv *priv = netdev_priv(exn_devs[0]);
	unsigned int  offset = exn_rma_noti_address_offset(len); 
	struct exn_rma_skb_buffer *new_entry = NULL;
	int ret = 0;
        unsigned long irq_flags;

//	unsigned int page_offset = (((uint64_t)local_address) & 0xfffl);
	

	new_entry = (struct exn_rma_skb_buffer *) kmem_cache_alloc(priv->rma_queue_cache, GFP_ATOMIC);	

//	new_entry = exn_rma_get_free_buffer(&priv->rma_free_buffer);
	
	if(new_entry == NULL) {
//		int i=0;
//		struct list_head *pos = NULL;
		
//		list_for_each(pos, buffer) {
//			new_entry = list_entry(pos, struct exn_rma_skb_buffer, list);
//			netedv_alert(DEV,"%i: %p age %u\n", i++, new_entry->local_address, new_entry->age);
//		}
		//spin_unlock_bh(&priv->rma_lock, irq_flags);
		netdev_alert(DEV,"no free buffer entries\n");
		return 0;
	}
	memset(new_entry, 0, sizeof(*new_entry));

	new_entry->skb = skb;
	new_entry->NLA = 0;
	//ret = atu2_register_physical_region(EXTOLL_VPID_NET, virt_to_phys(local_address), len, 1, 1, &new_entry->NLA);
	if(ret != 0) {
		netdev_alert(DEV,"error on registerin NLA for skb %p\n", skb);
		kmem_cache_free(priv->rma_queue_cache, new_entry);
		return 0;
	}
	new_entry->local_address = local_address+offset;
//	new_entry->age=0;

        //MN: list operations should be sufficient to be spinlocked, nothing more
        //MN: spinlock_bh should be enough, since we are not running in HW irq context???
        spin_lock_irqsave(&priv->rma_lock, irq_flags);
	list_add(&new_entry->list, buffer); //TODO: add tail!
        spin_unlock_irqrestore(&priv->rma_lock, irq_flags);
	
	return (unsigned long) local_address;

}

static struct sk_buff* get_skb(struct list_head *buffer, void *local_address)
{
	struct sk_buff *skb = NULL;
	unsigned long irq_flags;
	struct exn_priv *priv = netdev_priv(exn_devs[0]);
	struct list_head *pos = NULL;
	struct exn_rma_skb_buffer *tmp = NULL;
	static int how_often;
	//unsigned long NLA;

	spin_lock_irqsave(&priv->rma_lock, irq_flags);
	if(list_empty(buffer)) {
                netdev_alert(DEV,"Trying to find SKB with RMA local address %lx, but list is empty\n",(unsigned long) local_address);
		return NULL;
	}

	list_for_each(pos, buffer) {
		tmp = list_entry(pos, struct exn_rma_skb_buffer, list);
		if(tmp->local_address == local_address) {
			skb = tmp->skb;
			break;
		}
	}

	if(skb != NULL) { //only if the skb was found, remove it from list
		//exn_rma_return_buffer(tmp, &priv->rma_free_buffer);
		list_del(pos);
	//	NLA = tmp->NLA;	
	//	atu2_unregister_physical_region(EXTOLL_VPID_NET, NLA, skb->len);
		kmem_cache_free(priv->rma_queue_cache, tmp);
	} else {
		int i=0;
		netdev_alert(DEV,"skb not found %i! searching for %p\n", how_often++, local_address);
		netdev_alert(DEV,"but got those in unfinished buffer:\n");
		pos = NULL;
		tmp = NULL;
		list_for_each(pos, buffer) {
			tmp = list_entry(pos, struct exn_rma_skb_buffer, list);
			netdev_alert(DEV,"%i: %p, diff: %lx\n", i++, tmp->local_address, tmp->local_address - local_address);
		}
	}
			
	spin_unlock_irqrestore(&priv->rma_lock, irq_flags);

	return skb;
}

static void exn_drop_skb(struct list_head *skb_buffer, uint64_t data)
{
	struct list_head *pos = NULL;
	struct sk_buff *skb = NULL;
	struct exn_rma_skb_buffer *tmp = NULL;
	struct exn_priv *priv = netdev_priv(exn_devs[0]);
	unsigned long irq_flags;

	spin_lock_irqsave(&priv->rma_lock, irq_flags);
	list_for_each(pos, skb_buffer) {
		tmp = list_entry(pos, struct exn_rma_skb_buffer, list);
		if((void *)data == tmp->skb->data) {
			skb = tmp->skb;
			break;
		}	
	}
	
	if(skb != NULL){
		//exn_rma_return_buffer(tmp, &priv->rma_free_buffer);
		kmem_cache_free(priv->rma_queue_cache, tmp);
	}
	
	spin_unlock_irqrestore(&priv->rma_lock, irq_flags);
	
	if(skb!=NULL) {
		netdev_alert(DEV, "found skb to drop, dropping\n");
		//priv->stats.tx_dropped += skb->len;
		dev_kfree_skb_any(skb);
	} else { 
		netdev_alert(DEV,"tried to drop skb, but did not find it!\n");
	}
	netdev_dbg(DEV,"NEXT PRINTOUT JUST FOR the list in the sending queue, ignore error\n");
	skb = get_skb(&priv->rma_send_buffer, NULL);
	netdev_dbg(DEV,"NEXT PRINTOUT JUST FOR the list in the recving queue, ignore error\n");
	skb = get_skb(&priv->rma_recv_buffer, NULL);
	netdev_dbg(DEV,"NEXT PRINTOUT JUST FOR the list in the receive queue, ignore error\n");
        skb = get_skb(&priv->rma_send_buffer, NULL);
        netdev_dbg(DEV,"DONE PRINTOUT\n");

}

/*
 * Open and close
 */
int exn_open(struct net_device *dev) {
	struct exn_priv *priv = netdev_priv(dev);
	int ret;
	//int i = 0;
  
	/* request_region(), request_irq(), ....  (like fops->open) */
	netdev_info(DEV,"exn open called\n");

	ret=kapi_rma2_open(&(priv->rhandle), EXTOLL_VPID_NET);
	if (ret!=0){
		netdev_alert(DEV,"acquiring rma handle failed...\n");
		return -EBUSY;
	}
	//printk("EXN: RMA_MTU is %i\n", kapi_rma2_get_mtu(priv->rhandle));
	//rma_mtu = kapi_rma2_get_mtu(priv->rhandle);
	ret=kapi_velo2_open(&(priv->vhandle), EXTOLL_VPID_NET);
	if (ret!=0){
		netdev_info(DEV,"acquiring velo handle failed...\n");
		return -EBUSY;
	}
	kapi_rma2_wcb_register_callback(priv->rhandle,exn_rma2_wcb_cb);
	kapi_velo2_wcb_register_callback(priv->vhandle,exn_velo2_wcb_cb);
#ifdef RXSKB 
	netdev_dbg(DEV,"allocate initial RX SKB with size %d\n", exn_devs[0]->mtu+2);
	skb = dev_alloc_skb(exn_devs[0]->mtu+2);
#endif

	priv->rvpid=kapi_rma2_get_vpid(priv->rhandle);
	priv->vvpid=kapi_velo2_get_vpid(priv->vhandle);
	netdev_dbg(DEV,"opened rma handle for communication. Got VPID %d\n",priv->rvpid);
	netdev_dbg(DEV,"opened velo handle for communication. Got VPID %d\n",priv->vvpid);

	//now registering interrupt handler...
	if(use_napi == 0){
                netdev_info(DEV,"Not using NAPI...\n");
		rma2_register_vpid_irq_handler(priv->rvpid, &exn_regular_rma_interrupt);
		velo2_register_vpid_irq_handler(priv->vvpid, &exn_regular_velo_interrupt);
		netdev_dbg(DEV,"Registering regular interrupt handler.\nrma_handler: %p\nvelo_handler: %p\n", &exn_regular_rma_interrupt, &exn_regular_velo_interrupt);
	}else{
                netdev_dbg(DEV,"Using NAPI...\n");
		rma2_register_vpid_irq_handler(priv->rvpid, &exn_napi_rma_interrupt);
		//rma2_register_vpid_irq_handler(priv->rvpid, &exn_regular_rma_interrupt);
		velo2_register_vpid_irq_handler(priv->vvpid, &exn_napi_velo_interrupt);
		netdev_dbg(DEV,"Registering NAPI handler.\n");
		netdev_dbg(DEV,"Registered NAPI IRQ handlers.\nRMA: %p\nVELO: %p\n", &exn_napi_rma_interrupt, &exn_napi_velo_interrupt);
	}
	priv->dev = dev;
	priv->npackets = 0;

        extoll_add_nw_state_handler(exn_nw_state);

	if(use_napi==1){
		napi_enable(&(priv->napi_rma));
		napi_enable(&(priv->napi_velo));
	}

	netif_start_queue(dev);
	return 0;
}

static inline void exn_free_queue(struct exn_priv *priv, struct list_head *buffer) {
	struct list_head *pos, *q;
	//struct exn_rma_skb_buffer *tmp, *t2;
	struct exn_rma_skb_buffer *tmp;
	unsigned int counter = 0;

	netdev_dbg(DEV,"list contains %u entries.\n", counter);

	list_for_each_safe(pos, q, buffer) {
		tmp = list_entry(pos, struct exn_rma_skb_buffer, list);
		netdev_dbg(DEV,"got skb for %p (%p)... ", tmp->local_address, tmp->skb);
		kfree_skb(tmp->skb);
		list_del(pos);
		kmem_cache_free(priv->rma_queue_cache, tmp);
		netdev_dbg(DEV,"done\n");
	}
}
int exn_release(struct net_device *dev) {
	struct exn_priv *priv = netdev_priv(dev);
	int ret;
	//int i = 0;
        extoll_remove_nw_state_handler(exn_nw_state);
  
	/* release ports, irq and such -- like fops->close */
	netdev_dbg(DEV,"exn close called\n");
	
	if (use_napi == 1) {
		napi_disable(&(priv->napi_rma));
		napi_disable(&(priv->napi_velo));
	}

	netif_stop_queue(dev); /* can't transmit any more */

	/* free the transactions buffer */
	if(!list_empty(&priv->rma_send_buffer)) {
		netdev_dbg(DEV,"rma  send buffer contains elements, freeing...\n");
		exn_free_queue(priv, &priv->rma_send_buffer);
	}
	if(!list_empty(&priv->rma_recv_buffer)) {
		netdev_dbg(DEV,"rma  recv buffer contains elements, freeing...\n");
		exn_free_queue(priv, &priv->rma_recv_buffer);
	}
	kmem_cache_destroy(priv->rma_queue_cache);

	//deregister interrupt handler
	rma2_deregister_vpid_irq_handler(priv->rvpid);
	velo2_deregister_vpid_irq_handler(priv->vvpid);

        tasklet_kill(&exn_velo_tasklet);
        tasklet_kill(&exn_rma_tasklet);

	ret=kapi_rma2_close(&(priv->rhandle));
	if (ret!=0) {
		netdev_alert(DEV,"rma2 close failed.\n");
		return -EFAULT;
	}
	
	ret=kapi_velo2_close(&(priv->vhandle));
	if (ret!=0) {
		netdev_alert(DEV,"velo2 close not failed.\n");
		return -EFAULT;
	}

	return 0;
}

/*
 * Configuration changes (passed on by ifconfig)
 */
int exn_config(struct net_device *dev, struct ifmap *map) {
    netdev_dbg(DEV,"exn config called\n");
    if (dev->flags & IFF_UP) /* can't act on a running interface */
		return -EBUSY;
		
    /* Don't allow changing the I/O address */
    if (map->base_addr != dev->base_addr) {
		netdev_warn(DEV, "Can't change I/O address\n");
		return -EOPNOTSUPP;
    }

    /* Allow changing the IRQ */
    if (map->irq != dev->irq) {
		netdev_warn(DEV,"Can't change interrupt\n");
		return -EOPNOTSUPP;
    }

    /* ignore other fields */
    return 0;
}


/*
 * Add new entry in the list of incoming packet parts.
 */
packet *exn_list_add(struct net_device *dev, uint8_t tag, uint32_t srcid, uint32_t data_len, uint8_t *data) {
	struct exn_packet *tmp;
	struct exn_priv *priv = netdev_priv(dev);
  
	tmp = exn_get_packet(dev);
	tmp->tag = tag;
	tmp->srcid = srcid;
	tmp->dev = dev;
	tmp->datalen = data_len;
	memcpy(&(tmp->data), data, data_len);
	list_add(&(tmp->list), &(priv->rx_queue->list));
  
	return tmp;
}

/*
 * Add data to the buffer for splitted packets.
 */
packet *exn_add_data(struct exn_packet *packet, uint32_t data_len, uint8_t *data, uint8_t tag) {
	struct exn_packet *tmp = packet;
	void *buf = &tmp->data[tmp->datalen];
  
	tmp->tag = tag;
	memcpy(buf, data, data_len);
	tmp->datalen = tmp->datalen + data_len;
  
	return tmp;
}


packet *exn_search_list(struct net_device *dev, uint32_t srcid) {
	struct exn_packet *tmp = NULL;
	struct list_head *pos, *q;
	struct exn_priv *priv = netdev_priv(dev);
	
	list_for_each_safe(pos, q, &(priv->rx_queue->list)){
		tmp = list_entry(pos, struct exn_packet, list);
		if(tmp->srcid == srcid){
			return tmp;
		}
	}
	
	return 0;
}


void exn_rx_end(struct exn_packet *tmp) {
	struct sk_buff *skb;
	struct exn_priv *priv = netdev_priv(tmp->dev);
	uint32_t len;
	char* rbuf;
	
	if(tmp == NULL)
		goto out;
	
	len = tmp->datalen;
	
	skb = dev_alloc_skb(len+2);
	if (!skb) {
		if (printk_ratelimit())
			netdev_warn(DEV,"rx: low on mem - packet dropped\n");
		priv->stats.rx_dropped++;
		if (tmp)
			kfree(tmp);
		goto out;
	}
	rbuf = skb_put(skb, len);
	memcpy(rbuf, &tmp->data[0], len);
	
	/* Write metadata, and then pass to the receive level */
	skb->dev = exn_devs[0]; //tmp->dev;
	skb->protocol = eth_type_trans(skb, exn_devs[0]); //tmp->dev);
	netdev_alert(DEV,"received packet with proto %x and pkt_type %x\n",skb->protocol, skb->pkt_type);
        if (exn_no_rx_csum!=0)
         skb->ip_summed = CHECKSUM_UNNECESSARY; //CHECKSUM_NONE -> sw should calculate checksum , CHECKSUM_UNNECESSARY -> sw should not check checksum
        else
         skb->ip_summed = CHECKSUM_NONE; //CHECKSUM_NONE -> sw should calculate checksum , CHECKSUM_UNNECESSARY -> sw should not check checksum
	priv->stats.rx_bytes += len;
	priv->stats.rx_packets++;
	netdev_alert(DEV,"call netif_rx to hand packet to upper layer\n");
	if(use_napi == 0) {
		netif_rx(skb);
	} else {
		netif_receive_skb(skb);
		//priv->npackets++;
		netdev_alert(DEV,"netif_receive_skb called.\n");
	}
	//return the exn_packet to its free_list (ppool)
	if (tmp)
		exn_free_packet(tmp);
	
out:
	return;
}


/*
 * Receive a packet: retrieve, encapsulate and pass over to upper levels
 */
void exn_rx(struct net_device *dev, uint32_t data_len, uint8_t* data, uint8_t tag, uint32_t srcid)
{
	struct sk_buff *skb;
	struct exn_priv *priv = netdev_priv(dev);
	char* rbuf;
	uint32_t len;

	netdev_dbg(DEV,"enx: exn rx called\n");

	len = data_len;

	/*
	 * The packet has been retrieved from the transmission
	 * medium. Build an skb around it, so upper layers can handle it
	 */
	skb = dev_alloc_skb(len+2);
	if (!skb) {
		if (printk_ratelimit())
			netdev_warn(DEV,"rx: low on mem - packet dropped\n");
		priv->stats.rx_dropped++;
		return;
	}

	rbuf = skb_put(skb, len);
	memcpy(rbuf, data, len);

	/* Write metadata, and then pass to the receive level */
	skb->dev = exn_devs[0];
	skb->protocol = eth_type_trans(skb, exn_devs[0]);
	netdev_dbg(DEV,"received packet with proto %x and pkt_type %x\n",skb->protocol, skb->pkt_type);
	if (exn_no_rx_csum!=0)
		skb->ip_summed = CHECKSUM_UNNECESSARY; //CHECKSUM_UNNECESSARY -> sw should not check checksum
	else
		skb->ip_summed = CHECKSUM_NONE; //CHECKSUM_NONE -> sw 
	priv->stats.rx_bytes += len;
	priv->stats.rx_packets++;
	netdev_dbg(DEV,"call netif_rx to hand packet to upper layer\n");
	if(use_napi == 0) {
		netif_rx(skb);
	} else {
		netif_receive_skb(skb);
		//priv->npackets++;
		netdev_alert(DEV,"netif_receive_skb called.\n");
	}
}

#if 0
static int check_eth_header(char *data, unsigned int nodeid)
{
	char rev[13];
	int i = 0;

	rev[0] = 0;
	rev[1] = 0;
	rev[2] = 0;
	rev[3] = 0;
	rev[4] = 0;
	rev[5] = nodeid;
	rev[6] = 0;
	rev[7] = 0;
	rev[8] = 0;
	rev[9] = 0;
	rev[10] = 0;
	rev[11] = !nodeid;
	rev[12] = 8;
	//rev[13] = 0;

	for(i = 0; i<13; i++) {
		if(data[i] != rev[i]) {
			printk("exn: skb has wrong eth header1111111!!!\n");
			return -1;
		}
	}
	return 0;
}
#endif

/*int exn_check_alignment(uint64_t pointer) 
{
	int result = 0;

	if(pointer%64!=0 || pointer%8!=0) {
		printk("exn: %p", pointer);
	}

	if (pointer%64 != 0) {
		result = 1;
		printk("not 64byte aligned ", (void *) pointer);
	} 
	if (pointer%8 != 0) {
		result = 1;
		printk(" not qw aligned ",(void *) pointer);
	}

	return result;
}*/


static void exn_rx_rma(uint32_t remote_id, uint64_t remote_buf, uint64_t len)
{
	struct exn_priv *priv = netdev_priv(exn_devs[0]);
#ifndef RXSKB
	struct sk_buff *skb;
#endif
	char *local_buf;
#if 0
	static int i;
#endif
	unsigned long local_NLA;

	netdev_dbg(DEV,"exn rx interrupt started\n");

	netdev_dbg(DEV, "will fetch from node %u, %llu bytes from address %p\n", remote_id, len, (uint64_t *) remote_buf);
#ifndef RXSKB
	skb = dev_alloc_skb(len+2);
#endif
	if (!skb) {
		//if (printk_ratelimit())
		netdev_warn(DEV,"rx: low on mem - packet dropped\n");
		goto mem_error;
	}
	local_buf = skb_put(skb, len);


	skb->dev = exn_devs[0]; //TODO Fix pointers
        if (exn_no_rx_csum!=0)
         skb->ip_summed = CHECKSUM_UNNECESSARY; //CHECKSUM_NONE -> sw should calculate checksum , CHECKSUM_UNNECESSARY -> sw should not check checksum
        else
         skb->ip_summed = CHECKSUM_NONE; //CHECKSUM_NONE -> sw should calculate checksum , CHECKSUM_UNNECESSARY -> sw should not check checksum

	local_NLA = put_skb(&priv->rma_recv_buffer, local_buf, skb, len);
#if 0
	if(local_NLA == 0) { 
		netdev_alert(DEV,"out of SKB buffers on RMA receive\n");
		//exn_regular_rma_interrupt(EXTOLL_VPID_NET, NULL);
		//start the receive, really...
		//exn_rx_rma_start();	

		//ret = put_skb(&priv->rma_recv_buffer, local_buf, skb, len);
		//if(ret !=0) {
			//if (printk_ratelimit())
			netdev_alert(DEV, "rx: low on mem for skbs - packet dropped %i\n", i++);
			kapi_velo2_send(priv->vhandle, remote_id, EXTOLL_VPID_NET, &remote_buf, sizeof(remote_buf), 0, 2, 0, 1);
			dev_kfree_skb_any(skb);
			goto mem_error;
		//}
	} 
#endif
	//only if the skb can be managed, add it to queue
#ifdef MICEXTOLL
	kapi_rma2_get_bt(priv->rhandle, remote_id, EXTOLL_VPID_NET, (void*) remote_buf, (void *)virt_to_phys((void*)local_NLA)+ micextoll_micbase0, len, RMA2_RESPCOMPL_NOTIFICATION, RMA2_CMD_DEFAULT, RMA2_CONN_IRQ /*| RMA2_CONN_TC1*/);
#else	
	kapi_rma2_get_bt(priv->rhandle, remote_id, EXTOLL_VPID_NET, (void*) remote_buf, (void *)virt_to_phys((void*)local_NLA), len, RMA2_RESPCOMPL_NOTIFICATION, RMA2_CMD_DEFAULT, RMA2_CONN_IRQ /*| RMA2_CONN_TC1*/);
#endif	
#ifdef RXSKB
	skb = dev_alloc_skb(exn_devs[0]->mtu+2);
#endif	
	netdev_dbg(DEV,"exn rx interrupt ended\n");

	return;	
	
mem_error:	
	priv->stats.rx_dropped++;
	return;
}


static void exn_rx_rma_end(void *local_address)
{
	struct exn_priv *priv = netdev_priv(exn_devs[0]);
	struct sk_buff *skb = NULL;

	skb = get_skb(&priv->rma_recv_buffer, local_address);

	netdev_dbg(DEV,"exn rx rma end interrupt started\n");

	if(skb == NULL) {
		netdev_alert(DEV,"rx finish interrupt, skb not found! return\n");
		priv->stats.rx_dropped++;
		return;
	}

	skb->protocol = eth_type_trans(skb, exn_devs[0]);
	priv->stats.rx_bytes += skb->len;
	priv->stats.rx_packets++;
	
	/* Write metadata, and then pass to the receive level */
	netdev_dbg(DEV,"received packet with proto %x and pkt_type %x\n",skb->protocol, skb->pkt_type);

	if(use_napi == 0) {
		netif_rx(skb);
	} else {
		netif_receive_skb(skb);
		//priv->npackets++;
	}
	netdev_dbg(DEV,"exn rx finish interrupt ended\n");

	return;
}


/*
 * The poll implementation for NAPI mode.
 */
static int exn_poll_velo(struct napi_struct *napi, int budget) {
	int ret;
	uint32_t len;
	uint8_t mtt;
	uint8_t tag;
	uint32_t srcid;
	int receives=0;
	struct exn_priv *priv = netdev_priv(exn_devs[0]);
	char *tbuf;
	struct exn_packet *tmp = NULL;
	unsigned int posted_rma=0;
	int count = 1;

	netdev_dbg(DEV,"exn_poll_velo: exn VELO NAPI handler called\n");
	
	while ((kapi_velo2_check(priv->vhandle,&srcid,&len, &mtt, &tag)==0) && (count <= budget)) {
		if (mtt == 1) {
			uint64_t tx_info[2];
			uint32_t remote_node = srcid & 0xff;
			ret = kapi_velo2_recv_complete(priv->vhandle, tx_info);
			netdev_dbg(DEV,"exn_rma: started recv from %i (remote address: %p, length %llu)\n", remote_node, (void *)tx_info[0], tx_info[1]);
			exn_rx_rma(remote_node, tx_info[0], tx_info[1]);
                        posted_rma++;
		} else if (mtt == 0) { // && tag!=0){
			netdev_dbg(DEV,"exn_velo_irq: tag!=0\n");
			tmp = exn_search_list(exn_devs[0], srcid);
			if(tmp == NULL){
				tmp = exn_get_packet(exn_devs[0]);
				ret=kapi_velo2_recv_complete(priv->vhandle, &(tmp->data));
				tmp->tag = tag;
				tmp->srcid = srcid;
				tmp->dev = exn_devs[0];
				tmp->datalen = len;
				list_add(&(tmp->list), &(priv->rx_queue->list));
			}else{
				if ( tmp->tag!= ((tag+1) &0xff ) ) {
                                    netdev_alert(DEV,"Received2 msg from srcid %d (previous srcid was %d) with tag %d, but previous tag was %d.\n",srcid,tmp->srcid,tag,tmp->tag);
                                }
				tmp->tag = tag;
				ret=kapi_velo2_recv_complete(priv->vhandle, &tmp->data[tmp->datalen]);
				tmp->datalen = tmp->datalen + len;
			}
			if (ret==0)
				netdev_warn(DEV,"velo interrupt receive returned a zero. Should not happen, but ignored.\n");
		}else if (mtt ==3) { // && tag == 0) {
			tmp = exn_search_list(exn_devs[0], srcid);
			if(tmp != NULL){
				if ( tmp->tag!= ((tag+1) & 0xff) ) {
                                    netdev_alert(DEV,"Received2 msg from srcid %d (previous srcid was %d) with tag %d, but previous tag was %d.\n",srcid,tmp->srcid,tag,tmp->tag);
				}

				tmp->tag = tag;
				ret=kapi_velo2_recv_complete(priv->vhandle, &tmp->data[tmp->datalen]);
				tmp->datalen = tmp->datalen + len;
				list_del_init(&(tmp->list));
				exn_rx_end(tmp);
			}else{
				netdev_dbg(DEV,"exn_rx: buffer = data, tag = 0.\n");
				tbuf = kmalloc(sizeof(char)*len, GFP_ATOMIC);
				ret=kapi_velo2_recv_complete(priv->vhandle, tbuf);
				exn_rx(exn_devs[0], len, tbuf, tag, srcid);
				kfree(tbuf);
			}
			if (ret==0)
				netdev_warn(DEV,"velo interrupt receive returned a zero. Should not happen, but ignored.\n");
		}
		receives++;
		if (receives % 32)
			kapi_velo2_recv_commit(priv->vhandle,0);

		count++;
	}
        if (posted_rma!=0) {
	         ret=kapi_rma2_wcb_check(priv->rhandle,1000);
	         if (ret!=0) { //retry needed or not empty -> fix needed
	           netdev_alert(DEV,"kapi_rma2_wcb_check returned !=0\n");
	           netif_stop_queue(exn_devs[0]);
	           kapi_rma2_wcb_fix(priv->rhandle);           
	         }
        }
	kapi_velo2_recv_commit(priv->vhandle,1);
	
	// If there are no more RX SNQ entries available, 
	// bail out, reenable IRQs and stop polling.
	if(kapi_velo2_check(priv->vhandle,&srcid,&len, &mtt, &tag) != 0){
		napi_complete(&priv->napi_velo);
		kapi_velo2_recv_commit(priv->vhandle,1);
		return 0;
	}
  
	// Not all packets were handled. Keep polling.	
	return budget;
}

static int exn_poll_rma(struct napi_struct *napi, int budget) {
	struct exn_priv *priv = netdev_priv(exn_devs[0]);
	RMA2_Notification *noti;
	char *local_buf;
	RMA2_Notification_Spec noti_type;
	struct sk_buff *skb = NULL;
	int ended_sends = 0;
	unsigned int receives = 0;
	int count = 1;
	
	netdev_dbg(DEV,"start RMA NAPI polling\n");
	while((0 != kapi_rma2_noti_peek(priv->rhandle)) && (count <= budget)) {
		kapi_rma2_noti_fetch(priv->rhandle, &noti);
		noti_type = kapi_rma2_noti_get_notification_type(noti);
		local_buf = (char *)phys_to_virt(kapi_rma2_noti_get_local_address(noti));
		netdev_dbg(DEV,"got interrupt for noti:");
		if(0 != kapi_rma2_noti_get_error(noti)) {
			netdev_alert(DEV,"found error in notification:\n");
			kapi_rma2_noti_dump(noti);
		}
		if (noti_type == RMA2_RESPONDER_NOTIFICATION) {
			//read from skb complete free the local send buffer
			netdev_dbg(DEV,"tx interrupt started\n");
			skb = get_skb(&priv->rma_send_buffer, local_buf);
			if(skb == NULL) {
				dev_kfree_skb(skb);
				priv->stats.tx_dropped++;
				netdev_alert(DEV,"did not find skb on finishing send, abort!\n");
				goto loop_end;
			}

			priv->stats.tx_packets++;
			priv->stats.tx_bytes += skb->len;
			dev_kfree_skb(skb);
			
			ended_sends++;
			
			netdev_dbg(DEV,"tx interrupt ended\n");
		} else if (noti_type == RMA2_COMPLETER_NOTIFICATION) {
			exn_rx_rma_end(local_buf);
			netdev_dbg(DEV,"finished receiver side of transmission\n");
		} else {
			netdev_alert(DEV,"exn_poll_rma: found  unexpected noti, return.\n");
			kapi_rma2_noti_dump(noti);
		}

loop_end:	kapi_rma2_noti_mark_read(priv->rhandle);
                receives++;
		if(receives%32) {
			kapi_rma2_noti_commit(priv->rhandle,0);
		}

		count++;
	}
	//kfree(noti_dbg);
	
	// no more entries avail -> reenable IRQs
	if (kapi_rma2_noti_peek(priv->rhandle) == 0){
		napi_complete(&priv->napi_rma);
		kapi_rma2_noti_commit(priv->rhandle, 1);
		return 0;
	}
	
	kapi_rma2_noti_commit(priv->rhandle,0);

	// Keep polling for RMA.
	return budget;
}


/*
 * The typical interrupt entry point
 */
char rbuffer[128];
static void exn_regular_velo_interrupt(int vpid, snq_entry_t* entry) 
{

	tasklet_schedule(&exn_velo_tasklet);
}

static void exn_regular_velo_tasklet(void)
{
	static int i;
	int ret;
	uint32_t len;
	uint8_t mtt;
	uint8_t tag;
	uint32_t srcid;
	int receives=0;
	struct exn_priv *priv = netdev_priv(exn_devs[0]);
	char *tbuf;
	struct exn_packet *tmp = NULL;
	//unsigned long flags;
	unsigned int posted_rma=0;

	netdev_dbg(DEV,"enx_velo_irq: exn regual interrupt handler called\n");
	
	if(spin_trylock(&priv->velo_lock)) {
	while (kapi_velo2_check(priv->vhandle,&srcid,&len, &mtt, &tag)==0) {
		if (mtt == 1) {
			uint64_t tx_info[2];
			uint32_t remote_node = srcid & 0xffff;
			ret = kapi_velo2_recv_complete(priv->vhandle, tx_info);
			netdev_dbg(DEV,"exn_rma: started recv from %i (remote address: %p, length %llu)\n", remote_node, (void *)tx_info[0], tx_info[1]);
			exn_rx_rma(remote_node, tx_info[0], tx_info[1]);
                        posted_rma++;
		} else if (mtt == 2) {
			uint64_t buf;
			//other side dropped packet
			kapi_velo2_recv_complete(priv->vhandle, &buf);
			exn_drop_skb(&priv->rma_send_buffer, buf);
			netdev_alert(DEV,"other side dropped packet starting at %p, number dropped: %i\n",(void*)buf, i++);
		} else if (mtt == 0) { // && tag!=0){
			netdev_dbg(DEV,"exn_velo_irq: tag!=0\n");
			tmp = exn_search_list(exn_devs[0], srcid);
			if(tmp == NULL){
				tmp = exn_get_packet(exn_devs[0]);
				ret=kapi_velo2_recv_complete(priv->vhandle, &(tmp->data));
				tmp->tag = tag;
				tmp->srcid = srcid;
				tmp->dev = exn_devs[0];
				tmp->datalen = len;
				list_add(&(tmp->list), &(priv->rx_queue->list));
			}else{
				if ( tmp->tag!= ((tag+1) &0xff ) ) {
                                    netdev_alert(DEV,"Received2 msg from srcid %d (previous srcid was %d) with tag %d, but previous tag was %d.\n",srcid,tmp->srcid,tag,tmp->tag);
                               }

				tmp->tag = tag;
				ret=kapi_velo2_recv_complete(priv->vhandle, &tmp->data[tmp->datalen]);
				tmp->datalen = tmp->datalen + len;
			}
			if (ret==0)
				netdev_warn(DEV,"velo interrupt receive returned a zero. Should not happen, but ignored.\n");
		}else if (mtt ==3) { // && tag == 0) {
			tmp = exn_search_list(exn_devs[0], srcid);
			if(tmp != NULL){
                            if ( tmp->tag!= ((tag+1) & 0xff) ) {
                                    netdev_alert(DEV,"Received2 msg from srcid %d (previous srcid was %d) with tag %d, but previous tag was %d.\n",srcid,tmp->srcid,tag,tmp->tag);
                               }


				tmp->tag = tag;
				ret=kapi_velo2_recv_complete(priv->vhandle, &tmp->data[tmp->datalen]);
				tmp->datalen = tmp->datalen + len;
				list_del_init(&(tmp->list));
				exn_rx_end(tmp);
			}else{
				netdev_dbg(DEV,"exn_rx: buffer = data, tag = 0.\n");
				tbuf = kmalloc(sizeof(char)*len, GFP_ATOMIC);
				ret=kapi_velo2_recv_complete(priv->vhandle, tbuf);
				exn_rx(exn_devs[0], len, tbuf, tag, srcid);
				kfree(tbuf);
			}
			if (ret==0)
				netdev_warn(DEV,"velo interrupt receive returned a zero. Should not happen, but ignored.\n");
		}
		receives++;
		if (receives % 32)
			kapi_velo2_recv_commit(priv->vhandle,0);
	}
        if (posted_rma!=0) {
	         ret=kapi_rma2_wcb_check(priv->rhandle,1000);
	         if (ret!=0) { //retry needed or not empty -> fix needed
	           netdev_alert(DEV,"kapi_rma2_wcb_check returned !=0\n");
	           netif_stop_queue(exn_devs[0]);
	           kapi_rma2_wcb_fix(priv->rhandle);           
	         }
         
        }
	kapi_velo2_recv_commit(priv->vhandle,1);
		
	spin_unlock(&priv->velo_lock);
	} else {
		netdev_warn(DEV,"concurrent acces to interrupt handler?!\n");
	}
	

	netdev_dbg(DEV,"exn_velo_irq: exiting velo irq handler\n");
	if (receives>1) netdev_dbg(DEV,"receveived more than one velo message, %d messages, in interrupt handler\n",receives);
}

static void exn_rx_rma_start(void)
{
	struct exn_priv *priv = netdev_priv(exn_devs[0]);
	RMA2_Notification *noti;
	char *local_buf;
	RMA2_Notification_Spec noti_type;
	struct sk_buff *skb = NULL;
	int ended_sends = 0;
	unsigned int receives = 0;
	
	netdev_dbg(DEV,"start RMA interrupt\n");
	while(0 != kapi_rma2_noti_peek(priv->rhandle)) {
		kapi_rma2_noti_fetch(priv->rhandle, &noti);
		noti_type = kapi_rma2_noti_get_notification_type(noti);
#ifdef MICEXTOLL
                netdev_dbg(DEV,"got noti, local address is %lx, fixed address is %lx, virtual address is %lx\n", kapi_rma2_noti_get_local_address(noti), kapi_rma2_noti_get_local_address(noti)-micextoll_micbase0, phys_to_virt(kapi_rma2_noti_get_local_address(noti)-micextoll_micbase0))
                local_buf = (char *)phys_to_virt(kapi_rma2_noti_get_local_address(noti)-micextoll_micbase0);
#else
		local_buf = (char *)phys_to_virt(kapi_rma2_noti_get_local_address(noti));
#endif

		netdev_dbg(DEV,"got interrupt for noti:");
		if(0 != kapi_rma2_noti_get_error(noti)) {
			netdev_alert(DEV,"found error in notification:\n");
			kapi_rma2_noti_dump(noti);
		}
		if (noti_type == RMA2_RESPONDER_NOTIFICATION) {
			//read from skb complete free the local send buffer
			netdev_dbg(DEV,"tx interrupt started\n");
			skb = get_skb(&priv->rma_send_buffer, local_buf);
			if(skb == NULL) {
				dev_kfree_skb(skb);
				priv->stats.tx_dropped++;
				netdev_alert(DEV,"did not find skb on finishing send, abort!\n");
				goto loop_end;
			}

			priv->stats.tx_packets++;
			priv->stats.tx_bytes += skb->len;
			dev_kfree_skb(skb);
			
			ended_sends++;
			
			netdev_dbg(DEV,"tx interrupt ended\n");
		} else if (noti_type == RMA2_COMPLETER_NOTIFICATION) {
			exn_rx_rma_end(local_buf);
			netdev_dbg(DEV,"finished receiver side of transmission\n");
		} else {
			netdev_alert(DEV,"exn_regular_rma_interrup: found  unexpected noti, return.\n");
			kapi_rma2_noti_dump(noti);
		}

loop_end:	kapi_rma2_noti_mark_read(priv->rhandle);
                receives++;
		if(receives%32) {
			kapi_rma2_noti_commit(priv->rhandle,0);
		}
	}
	//kfree(noti_dbg);
	/*if(ended_sends > 0 && netif_queue_stopped(exn_devs[0])) { //TODO wake queue only when sends were freed?! or are we stopping the queue forever in a dump situation?
		netif_wake_queue(exn_devs[0]);
		netdev_alert(DEV,"wake queue, after freeing %i entries\n", ended_sends);
	}*/
		
	kapi_rma2_noti_commit(priv->rhandle, 1);
	
	netdev_dbg(DEV,"return from RMA interrupt\n");
	
	return;

}

static void exn_regular_rma_interrupt(int vpid, snq_entry_t* entry)
{
	netdev_dbg(DEV,"exn regular interrupt RMA handler called for vpid %i.\n", vpid);

	tasklet_schedule(&exn_rma_tasklet);
	return;
}


/*
 * RMA NAPI interrupt handler.
 */
static void exn_napi_rma_interrupt(int vpid, snq_entry_t* entry) {
	struct exn_priv *priv = netdev_priv(exn_devs[0]);
	
	napi_schedule(&priv->napi_rma);
	return;
}


/*
 * VELO NAPI interrupt handler.
 */
static void exn_napi_velo_interrupt(int vpid, snq_entry_t* entry) {
	struct exn_priv *priv = netdev_priv(exn_devs[0]);
  
	napi_schedule(&priv->napi_velo);
	return;
}


/*
 * Transmit a packet (low level interface)
 */
//static int exn_hw_tx(char *buf, int len, struct net_device *dev, struct sk_buff *skb) {
int exn_hw_tx(struct sk_buff *skb, struct net_device *dev) {

	struct exn_priv *priv = netdev_priv(dev);
	struct ethhdr *eth=(struct ethhdr *)skb->data;
	char *tbuf,*buf,*header;
	int i;
	uint8_t tag=0;
	uint8_t mtt;
	int mc;
	uint32_t dest_id;
	int ret=0, ret_sum=0;
	int count_p, tlen, last_msg_length;

        int len;
        uint64_t tx_info[2];
        unsigned long local_NLA;


        netdev_dbg(DEV,"exn tx called\n");
        buf = skb->data;
        header = skb->head;
        len = skb->len;
        netdev_dbg(DEV,"skb->len is %d data is %p header is %p\n",len,buf, header);

	EKVCL_update_trans_start(dev, jiffies);

	#if 0
            { /* enable this conditional to look at the data */
		netdev_dbg(DEV,"len is %i\n" KERN_DEBUG "data:",len);
		for (i=0 ; i<len; i++)
			netdev_dbg(DEV," %02x",buf[i]&0xff);
		netdev_dbg(DEV,"\n");
	}
        #endif
  
	//extract the EXTOLL destination id from the MAC destination address
	dest_id=(eth->h_dest[4]<<8) | eth->h_dest[5];
        netdev_dbg(DEV,"Send a packet to mac address: %hhx:%hhx:%hhx:%hhx:%hhx:%hhx\n", eth->h_dest[0],eth->h_dest[1],eth->h_dest[2],eth->h_dest[3],eth->h_dest[4],eth->h_dest[5]);
	netdev_dbg(DEV,"packet goes to destination id %u,\n",dest_id);
	//check if this should be a broadcast
        if (eth->h_dest[0] & 0x1) {
		dest_id=63;
		mc=1;
		netdev_dbg(DEV,"This is a broadcast with MAC:  %hhx:%hhx:%hhx:%hhx:%hhx:%hhx\n", eth->h_dest[0],eth->h_dest[1],eth->h_dest[2],eth->h_dest[3],eth->h_dest[4],eth->h_dest[5]);
	} else {
		mc=0;
	}
  
        if (mc==0 && eth->h_dest[0]!=mac0 && eth->h_dest[1]!=mac1 && eth->h_dest[2]!=mac2 && eth->h_dest[3]!=mac3)
        {
          if (default_nodeid==-1) {
            netdev_dbg(DEV,"Send a packet to mac address requested: %hhx:%hhx:%hhx:%hhx:%hhx:%hhx. dropping it\n", eth->h_dest[0],eth->h_dest[1],eth->h_dest[2],eth->h_dest[3],eth->h_dest[4],eth->h_dest[5]);
            priv->stats.tx_dropped++;
            dev_kfree_skb(priv->skb);
            return NETDEV_TX_OK;
	  } else {           
            dest_id=default_nodeid;
            netdev_dbg(DEV,"Send a packet to mac address: %hhx:%hhx:%hhx:%hhx:%hhx:%hhx destid is %d\n", eth->h_dest[0],eth->h_dest[1],eth->h_dest[2],eth->h_dest[3],eth->h_dest[4],eth->h_dest[5],dest_id);
          }
	}

        if (len < velo_threshold || mc==1) //if multicast or message is smaller then velo_threshold, send using velo eager protocol
        { 
		//calculate number of velo packets necessary
		count_p = ((len % VELO2_MAX_MSG_SIZE) == 0) ? (len / VELO2_MAX_MSG_SIZE) : ((len/VELO2_MAX_MSG_SIZE) +1);
		//all packets but the last have a length of VELO2_MAX_MSG, calculate the length of the last packet
		last_msg_length=((len % VELO2_MAX_MSG_SIZE) != 0) ? (len % VELO2_MAX_MSG_SIZE) : VELO2_MAX_MSG_SIZE;
  
		i = 0;
		netdev_dbg(DEV,"i is %d, count_p is %d len is %d\n",i, count_p,len);
		while(count_p > 0) {
			tag = (count_p - 1) & 0xff;
			tbuf = buf + (120*(i));
			
			if(count_p == 1) { //last message
				mtt= 3;
				tlen = last_msg_length;
			} else {
				mtt= 0;
				tlen = VELO2_MAX_MSG_SIZE;
			}
			netdev_dbg(DEV,"send a packet to dest %d, mc is %d buf is %p tbuf is %p\n",dest_id,mc,buf,tbuf);

			ret = kapi_velo2_send(priv->vhandle, dest_id, EXTOLL_VPID_NET, tbuf, tlen, tag, mtt, mc,1);
		
			ret_sum = ret_sum + ret;
    
			if (ret!=0) {
				netdev_warn(DEV,"oops, kapi_velo2_send failed.\n");
			}
	                i++;
    	
			count_p--;
		}
  
                ret=kapi_velo2_wcb_check(priv->vhandle,1000);
                if (ret!=0) { //retry needed or not empty -> fix needed
                  netdev_dbg(DEV,"kapi_velo2_wcb_check1 returned !=0\n");
                  netif_stop_queue(exn_devs[0]);
                  kapi_velo2_wcb_fix(priv->vhandle);           
                }

		if(ret_sum == 0) {
			//everything is fine... free resources
			dev_kfree_skb(skb); 
			priv->stats.tx_packets++;
			priv->stats.tx_bytes += len;
			return NETDEV_TX_OK;
		} else {
			netdev_alert(DEV,"EXN_HW_TX: Oh no... returned with NETDEV_TX_BUSY\n");
			return NETDEV_TX_BUSY; //transmission not possible at the moment
		}
	} else { //not a multicast message and message size is larger then velo_threshold -> send using rma based rendez-vous protocol
		netdev_dbg(DEV,"rma tx started\n");
	        tx_info[1] = (uint64_t) len;
	        netdev_dbg(DEV,"exn_hw_tx_rma initiated send to %i.\n", dest_id);
	        local_NLA = put_skb(&priv->rma_send_buffer, buf, skb, len);
	        netdev_dbg(DEV,"puts next datagram in send-queue\n");
#ifdef MICEXTOLL
                tx_info[0] = (uint64_t) virt_to_phys((void*) local_NLA) + micextoll_micbase0;
                netdev_alert(DEV,"send local_NLA of %lx, phys %lx pcie phys %lx\n",local_NLA,virt_to_phys(local_NLA), virt_to_phys(local_NLA) + micextoll_micbase0 )
#else
	        tx_info[0] = (uint64_t) virt_to_phys((void*)local_NLA);
#endif

	        if(local_NLA != 0) { //the data was put into the buffer
	                kapi_velo2_send(priv->vhandle, dest_id, EXTOLL_VPID_NET, tx_info, sizeof(uint64_t)*2, 0, 1, 0, 1);
        	        //rest of skb-handeling in interrupt for Responder Notifications
	                netdev_dbg(DEV,"rma tx ended\n");

        	        //WCB retry check
                        ret=kapi_velo2_wcb_check(priv->vhandle,1000);
                        if (ret!=0) { //retry needed or not empty -> fix needed
                          netdev_dbg(DEV,"kapi_velo2_wcb_check2 returned !=0\n");
                          netif_stop_queue(exn_devs[0]);
                          kapi_velo2_wcb_fix(priv->vhandle);           
                        }
	                return NETDEV_TX_OK;
	        } else {
	                netif_stop_queue(exn_devs[0]);
	                netdev_alert(DEV,"queue stopped, trying to free buffers...\n");
	                tasklet_schedule(&exn_rma_tasklet);
                	return NETDEV_TX_BUSY; //transmission not possible at the moment
        	}
	}
     return NETDEV_TX_BUSY; //default return, cannot be reached
}

#if 0
/*
 * Deal with a transmit timeout.
 */
void exn_tx_timeout(struct net_device *dev) {
	struct exn_priv *priv = netdev_priv(dev);
	//int free_count = 0;
	//struct list_head *pos;

	netdev_info(DEV,"Transmit timeout at %ld, latency %ld\n", jiffies,
		jiffies - dev->trans_start);
        
	priv->stats.tx_errors++;

	//How to deal with timeouts?
	//Assume the network does not produce errors ;)
	//Try to consume all extoll-messages, and free buffers!
	//exn_regular_velo_interrupt(EXTOLL_VPID_NET, NULL);
	netdev_dbg(DEV,"in timeout function, print the buffers:\n");
	netdev_dbg(DEV,"send buffer:\n");
	get_skb(&priv->rma_send_buffer, NULL);
	netdev_dbg(DEV,"recv buffer\n");
	get_skb(&priv->rma_recv_buffer, NULL);
	/*list_for_each(pos, &priv->rma_free_buffer) {
		free_count++;
	}
	netdev_alert(DEV,"end printing buffers, count of free structures: %i\n", free_count);
	*/
	if(netif_queue_stopped(dev)) {
		netdev_alert(DEV,"queue stopped in tx timeout at beginning\n");
	}

	exn_regular_rma_interrupt(EXTOLL_VPID_NET, NULL);	

	//do we need here to enabkle the queue? the interrupt does this for us        
	if(netif_queue_stopped(dev)) {
		netdev_alert(DEV,"queue stopped in tx timeout at endi, starting\n");
		netif_wake_queue(dev);
	} else {
		netdev_alert(DEV,"queue started after tx timeout\n");
	}
	

	return;
}
#endif

/*
 * Ioctl commands 
 */
int exn_ioctl(struct net_device *dev, struct ifreq *rq, int cmd) {
	netdev_dbg(DEV,"ioctl called, cmd: %i\n", cmd);
	return 0;
}

/*
 * Return statistics to the caller
 */
struct net_device_stats *exn_stats(struct net_device *dev) {
	struct exn_priv *priv = netdev_priv(dev);
	return &priv->stats;
}

/*
 * This function is called to fill up an eth header.
 */
int exn_rebuild_header(struct sk_buff *skb) {
 	netdev_alert(DEV,"OOPS exn rebuild header called\n");

    return 0;
}


int exn_header(struct sk_buff *skb, struct net_device *dev, unsigned short type, const void *daddr, const void *saddr,
                unsigned int len)
{
	int i;
   
	struct ethhdr *eth = (struct ethhdr *)skb_push(skb,ETH_HLEN);

	eth->h_proto = htons(type);
	memcpy(eth->h_source, saddr ? saddr : dev->dev_addr, dev->addr_len);
	memcpy(eth->h_dest, daddr ? daddr : dev->dev_addr, dev->addr_len);
	netdev_dbg(DEV,"Made header: len is %d, addr_len is %d, type is %x\n", dev->hard_header_len, dev->addr_len,type);

	netdev_dbg(DEV,"addr len is %i\n" KERN_DEBUG "saddr/daddr:",len);
	for (i=0 ; i<6; i++)
		netdev_dbg(DEV," %02x",((uint8_t*)eth->h_source)[i]&0xff);
	netdev_dbg(DEV, "\t");
	for (i=0 ; i<6; i++)
		netdev_dbg(DEV," %02x",((uint8_t*)eth->h_dest)[i]&0xff);
	netdev_dbg(DEV,"\n");

	return (dev->hard_header_len);
}

/*
 * The "change_mtu" method is usually not needed.
 * If you need it, it must be like this.
 */
int exn_change_mtu(struct net_device *dev, int new_mtu) {
	unsigned long flags;
	struct exn_priv *priv = netdev_priv(dev);
	spinlock_t *lock = &priv->lock;
    
	/* check ranges */
	if ((new_mtu < 68) || (new_mtu > MAX_EXN_LEN))
		return -EINVAL;
	/*
	* Do anything you need, and the accept the value
	*/
	netdev_info(DEV,"changed mtu to %d\n",new_mtu);
	spin_lock_irqsave(lock, flags);
	dev->mtu = new_mtu;
#ifdef RXSKB
        //MM: this is strictly speaking dangerous, as the same variable may be changed in the exn_rma_star function.
        //worst thing that can happen is, that we loose one SKB worth of memory, though
	skb = dev_alloc_skb(new_mtu+2);
#endif
	spin_unlock_irqrestore(lock, flags);
	return 0; /* success */
}

static const struct header_ops exn_header_ops = {
	.create  = exn_header,
	//.rebuild = exn_rebuild_header,
	.cache   = NULL,  /* disable caching */
};

static const struct net_device_ops exn_netdev_ops = {
	.ndo_open = exn_open,
	.ndo_stop = exn_release,
	.ndo_set_config = exn_config,
	.ndo_start_xmit = exn_hw_tx,
	.ndo_do_ioctl = exn_ioctl,
	.ndo_get_stats = exn_stats,
	EKVCL_NDO_CHANGE_MTU, //.ndo_change_mtu = exn_change_mtu
	//.ndo_tx_timeout = exn_tx_timeout, //FIXME: hows that?
};

void exn_constructor_kmem(void *asdf) {
	//netdev_dbg(DEV,"called constructor..., with %p\n", asdf);
}

/*
 * The init function (sometimes called probe).
 * It is invoked by register_netdev()
 */
void exn_init(struct net_device *dev) {
	struct exn_priv *priv = netdev_priv(dev);
	//struct exn_priv *priv;
	//int ret=0;
	uint64_t node=get_extoll_rf_info_rf_node();
	uint16_t nodeid=(node>>24l) & 0xffff;
	int i=0;
        
	netdev_dbg(DEV,"exn_init called on node %uh %02x %02x\n",nodeid,nodeid >> 8 ,nodeid & 0xff);
        netif_carrier_off(dev);
	/*
     * Make the usual checks: check_region(), probe irq, ...  -ENODEV
     * should be returned if no device found.  No resource should be
     * grabbed: this is done on open(). 
     */
    /* 
     * Then, assign other fields in dev, using ether_setup() and some
     * hand assignments
     */

	dev->type   = ARPHRD_ETHER;
	memset(dev->broadcast, 0xFF, ETH_ALEN);

	dev->netdev_ops = &exn_netdev_ops;
	dev->header_ops = &exn_header_ops;
	dev->watchdog_timeo = timeout;
        
	/* Add Broadcast and Multicast flags */
	dev->flags |= IFF_BROADCAST;
        if (exn_no_tx_csum!=0)
 	  dev->features |= NETIF_F_HW_CSUM; //sw should not calc checksum, not sure wheter this is a good idea

	dev->features |= NETIF_F_HIGHDMA;
	
	//init hw related fields of dev
	dev->hard_header_len = ETH_HLEN;
	
	dev->mtu = 65536; 
	dev->tx_queue_len = 1000;
	dev->addr_len = ETH_ALEN;
	
	dev->dev_addr[0] = mac0;
	dev->dev_addr[1] = mac1;
	dev->dev_addr[2] = mac2;
	dev->dev_addr[3] = mac3;
	dev->dev_addr[4] = nodeid >> 8;
	dev->dev_addr[5] = nodeid & 0xff;
	
        /*
         * Then, initialize the priv field. This encloses the statistics
         * and a few private fields. -> SN: moved to probe function
         */
	priv = netdev_priv(dev);
	memset(priv, 0, sizeof(struct exn_priv));
	priv->dev = dev;
	
	priv->nodeid = nodeid;

        /* napi_struct must be initialized and registered before
	 * the net device is registered.
	 * The last parameter above is the NAPI "budget". 
	 * Budget places a limit on the amount of work the driver
	 * can do before bailing out of the poll function.
	 */
	if(use_napi){ 
                pr_info("exn0: NAPI active. Using a budget of %d for VELO and %d for RMA\n",napi_velo_budget,napi_rma_budget);
		netif_napi_add(dev, &priv->napi_velo, &exn_poll_velo, napi_velo_budget);
		netif_napi_add(dev, &priv->napi_rma, &exn_poll_rma, napi_rma_budget);
	
	}   

	spin_lock_init(&priv->lock);
        
	priv->rx_queue = kmalloc(sizeof(struct exn_packet), GFP_KERNEL);
	priv->ppool = kmalloc(sizeof(struct exn_packet), GFP_KERNEL);
	INIT_LIST_HEAD(&(priv->rx_queue->list));
	INIT_LIST_HEAD(&(priv->ppool->list));
	netdev_dbg(DEV,"setting up pool...\n");
	exn_setup_pool(dev);

 	//init data buffer for sending via rma
	INIT_LIST_HEAD(&priv->rma_send_buffer);
	INIT_LIST_HEAD(&priv->rma_recv_buffer);
//	INIT_LIST_HEAD(&priv->rma_free_buffer);

//	exn_rma_pool_init(RMA_FREE_BUFFER_SIZE ,&priv->rma_free_buffer);
	priv->rma_queue_cache = kmem_cache_create("rma_queue_cache", sizeof(struct exn_rma_skb_buffer), 0, 0/*SLAB_HWCACHE_ALIGN*/, &exn_constructor_kmem);
	//warumup cache
	for(i=0; i<1000; i++){
		struct exn_rma_skb_buffer *b;
		b = kmem_cache_alloc(priv->rma_queue_cache, GFP_KERNEL);
		kmem_cache_free(priv->rma_queue_cache, b);
	}

	spin_lock_init(&priv->rma_lock);
	
	spin_lock_init(&priv->velo_lock);
	
	//priv->rma_queue = create_workqueue("exn_rma_queue");       
	// record the "real" irq of EXTOLL here
	dev->irq = extoll_get_irq();

}


/*
* Finally, the module stuff
*/
void exn_register(struct work_struct *work) {
  register_netdev(exn_devs[0]);
}

DECLARE_WORK(register_exn_netdev, exn_register);

void exn_cleanup(void) {
	int i;
	pr_info("exn: exn_cleanup called\n");
        //extoll_remove_nw_state_handler(exn_nw_state2);
	for (i = 0; i < 1;  i++) {
		if (exn_devs[i]) {

			unregister_netdev(exn_devs[i]);
			exn_teardown_pool(exn_devs[i]);
			free_netdev(exn_devs[i]);
		}
	}
	return;
}

int exn_init_module(void) {
	int result, i, ret = -ENOMEM;
//	struct exn_priv *priv;

	 if (extoll_get_init_done()==0)
	  {
	    pr_alert("EXTOLL Base driver not initialized! Bailing out\n");
	    return -1;
	  }

	/* Allocate the device, calls exn_init */
	exn_devs[0] = EKVCL_alloc_netdev(sizeof(struct exn_priv), "exn%d", NET_NAME_UNKNOWN,
			exn_init);
	if (exn_devs[0] == NULL)
		goto out;

	ret = -ENODEV;
	//register one device
	for (i = 0; i < 1;  i++) {
		if ((result = register_netdev(exn_devs[i])))
			pr_alert("exn: error %i registering device \"%s\"\n",
					result, exn_devs[i]->name);
		else
			ret = 0;
	}

out:
	if (ret) 
		exn_cleanup();
	return ret;
}


module_init(exn_init_module);
module_exit(exn_cleanup);
