/*
 *
 * 	some first tests with the rma kapi
 *
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/dma-mapping.h>
#include <linux/pci.h>

#include "/extoll2/src/extolldrv-dev/extoll-driver/extoll_kapi.h"

// Include EXTOLL header files
//#include "/extoll2/src/extolldrv-dev/extoll-driver/extolldrv.h"
//#include "/extoll2/src/extolldrv-dev/extoll-driver/extoll_rf_sysfs.h"

#define KAPI_ANY_VPID -1
#define VELO_COMMIT_IRQ_UPDATE 1
#define NO_MULTICAST 0
#define VELO_ISSUE_RX_INTR 1
#define RMA_BUFF_SIZE 8

VELO2_Handle *velo_hdl;

uint64_t* rma_buffer;
dma_addr_t phys_rma_buffer;
struct pci_dev* devp;


static void velo_irq_rcv_handle(int vpid, snq_entry_t* snq) {
	uint32_t len, srcid;
	uint8_t mtt, tag;
	int recieves = 0;
	uint64_t rx_dat[3];
    uint64_t rx_hdr[1];
	int status; 
	uint64_t tmp;

	int i;
	char* local_buf;

	// poll until there are no more messages and get meta data of message
	while(kapi_velo2_check(velo_hdl, &srcid, &len, &mtt, &tag) == 0) {
		recieves++;	
		printk("MSG Meta: Src: %i\t Len: %i\t MTT: %i\t TAG %i\n", srcid & 0xff, len, mtt, tag);
		// get header
		kapi_velo2_recv_header(velo_hdl, rx_hdr, 1);
        printk("velo-header-recv: %llu \n", rx_hdr[0]);
		kapi_velo2_recv_payload(velo_hdl, &rx_dat, 1);
		printk("MSG Content: adr: %p, size: %llu, vpid: %llu\n", (void*) rx_dat[0], rx_dat[1],rx_dat[2]);
		kapi_velo2_recv_commit(velo_hdl, VELO_COMMIT_IRQ_UPDATE); 
	}
}
static int __velo_core_init(void) {
	int status; 
	status = kapi_velo2_open(&velo_hdl, KAPI_ANY_VPID);
	printk("velo-header-recv: VELO Device opened: Node: %u, vpid: %u\n", 
		kapi_velo2_get_nodeid(velo_hdl), 
		kapi_velo2_get_vpid(velo_hdl)
	);
	printk("\tStatus: %i\n", status);

	// velo handle for get messages
	velo2_register_vpid_irq_handler(kapi_velo2_get_vpid(velo_hdl), &velo_irq_rcv_handle);
	printk("VELO IRQ Handler registered\n");

    return 0;	
}

static int velo_core_init(void) {
	return __velo_core_init();
}

static void velo_core_exit(void) {
	kapi_velo2_close(&velo_hdl);
	printk("velo-header-recv: module is removed\n");
}

MODULE_LICENSE("GPL v2");
module_init(velo_core_init);
module_exit(velo_core_exit);
