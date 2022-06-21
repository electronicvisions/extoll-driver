/*
 *  This file is part of the  Linux Kernel Driver Package for EXTOLL R2.
 *
 *  Copyright (C) 2011 EXTOLL GmbH
 *
 *  Written by Mondrian Nuessle (2011)
 *  Partly based on work done by Philip Degler (2007)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include "arch_define.h"

#include <linux/fs.h>
#include <linux/pci.h>
#include <linux/list.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#ifndef LS3BEXTOLL
#include <asm/mtrr.h>
#endif
#include <asm/uaccess.h>

#include "extoll_bq.h"
#include "extoll_kernel.h"
#include "extolldrv.h"
#include "extoll_rf_sysfs.h"


#include "velo2_ioctl.h"
#include "velo2_mod.h"
#include "velo2drv.h"

#include "snq_decl.h"

//for debugging purpose
#include <linux/jiffies.h>
#include <linux/delay.h>

//Cache line size in quad words (64 bit units)
#define VELO2_CLINE_SIZE     8
#define VELO2_LAZYNESS       4
#define VELO2_VPIDS          256
#define VELO2_NODES          1024

#define DEBUG(a)
//#define DEBUG(a) a

#define DEV velo2.dev

//default value of 2MB for one BQ
#define VELO2_DMA_SIZE_CMP   2097152

//#define VELO2_REQUESTER_SIZE  4096
/******************************************************************************
*  module parameters (could be set at loadtime)			      *
******************************************************************************/
uint velo_dma_size_cmp = VELO2_DMA_SIZE_CMP;	//completer dma buffer size
module_param(velo_dma_size_cmp, uint, S_IRUGO);

//FIXME not tested yet!
static unsigned int VELO2_MIN_VPID = 0;
//static unsigned int VELO2_MIN_VPID;
module_param(VELO2_MIN_VPID, uint, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
EXPORT_SYMBOL(VELO2_MIN_VPID);

//unsigned int VELO2_MIN_VPID = 0;
//module_param(VELO2_MIN_VPID, unsigned int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
//EXPORT_SYMBOL(VELO2_MIN_VPID);

/******************************************************************************
*  Listinitialisation							      *
******************************************************************************/
//LIST_HEAD(velo_rport_list);	//all open requester ports
//LIST_HEAD(velo_cport_list);	//all open completer ports
//LIST_HEAD(velo_owner_list);	//all threads/processes owning ports

/******************************************************************************
*  Other Stuff
******************************************************************************/

static velo2_device_t velo2; 

static int aoi_recv_msg=0;

//static struct velo_vpid velo_free_vpids[VELO2_MAX_VPID];
static velo_port_t* ports[VELO2_MAX_VPID];

/******************************************************************************
*  Manage concurrent access to global lists   				      *
******************************************************************************/
/* in the early version of this driver a more coarse grain synchronization
* is implemented. The policy for using this driver wide mutex is as follows:
* all entry functions of this driver module have to take care of correct 
* locking / synchronization, so that a helper/internal functions do not have
* to care about this mutex. This first and simple policy should preserve 
* race conditions and deadlocks.
*/
DEFINE_MUTEX(velo_mutex);	//mutex is initialized unlocked.

/******************************************************************************
*  helper functions      						      *
******************************************************************************/
// FIXME: Implement functions here to handle all important regs from VELO!

/* set the protection descriptor for outbound messages */
void velo2_set_tx_protection_descriptor(uint32_t vpid, uint16_t protdesc)
{
  uint64_t value;
  value=get_extoll_rf_velo_rf_node_vpid_prot_desc(vpid);
  value= value & 0xffffffffffff0000l;
  value=value | ((uint64_t) protdesc);
  set_extoll_rf_velo_rf_node_vpid_prot_desc(vpid,value);
}
EXPORT_SYMBOL(velo2_set_tx_protection_descriptor);

static inline uint16_t velo2_get_tx_protection_descriptor(uint32_t vpid)
{  
  uint64_t value;
  value=get_extoll_rf_velo_rf_node_vpid_prot_desc(vpid);
  value= value & 0xffffffffffff0000l;
  return value;
}

void velo2_set_tx_id(uint32_t vpid, uint16_t tx_nodeid, uint16_t tx_vpid)
{
  uint64_t value;
  value=get_extoll_rf_velo_rf_node_vpid_prot_desc(vpid);
  value= value & 0xffffff000000ffffl;
  value=value | ((tx_nodeid&0xffffl)<<16l) | ((tx_vpid & 0xffl)<<32l);
  set_extoll_rf_velo_rf_node_vpid_prot_desc(vpid,value);
}
EXPORT_SYMBOL(velo2_set_tx_id);

static inline void velo2_native_cpuid(unsigned int *eax, unsigned int *ebx,
				unsigned int *ecx, unsigned int *edx)
{
	/* ecx is often an input as well as an output. */
	asm volatile("cpuid"
			: "=a" (*eax),
			  "=b" (*ebx),
			  "=c" (*ecx),
			  "=d" (*edx)
			: "0" (*eax), "2" (*ecx)
			: "memory");
}

static inline void velo2_cpuid(unsigned int op,
			 unsigned int *eax, unsigned int *ebx,
 			 unsigned int *ecx, unsigned int *edx)
{
	*eax = op;
	*ecx = 0;
	velo2_native_cpuid(eax, ebx, ecx, edx);
}

static inline int velo2_cpu_supports_large_slots(void)
{
#if defined(CONFIG_X86_32) || defined(CONFIG_X86_64)
	char x86_vendor_id[16];
	unsigned int cpuid_level;
	static char intel_cpuid[] = "GenuineIntel";

	cpuid(0x00000000, (unsigned int *)&cpuid_level,
			(unsigned int *)&x86_vendor_id[0],
			(unsigned int *)&x86_vendor_id[8],
			(unsigned int *)&x86_vendor_id[4]);

	pr_info("found cpu vendor id %s\n", x86_vendor_id);

	if(0 == strcmp(intel_cpuid, x86_vendor_id)) {
		return 1;
	}

	return 0;

#else
	return 0;
#endif /* defined(CONFIG_X86_32) || defined(CONFIG_X86_64) */
}

static inline uint32_t velo2_detect_slot_size(void)
{
	unsigned int slot_size = 0;
	if(velo2_cpu_supports_large_slots()) {
		slot_size = 128; //use 128 byte slots on intel cpus
	} else {
		slot_size = 64;
	}
	pr_info("using %i byte slots\n", slot_size);
	return slot_size;
}

static inline uint16_t velo2_get_tx_nodeid(uint32_t vpid)
{
  uint64_t value;
  value=get_extoll_rf_velo_rf_node_vpid_prot_desc(vpid);
  value= value & 0xffffffff0000ffffl;
  value=value>>16l;
  return value;
}

static inline uint16_t velo2_get_tx_vpid(uint32_t vpid)
{
  uint64_t value;
  value=get_extoll_rf_velo_rf_node_vpid_prot_desc(vpid);
  value= value & 0xffffff00ffffffffl;
  value=value>>24l;
  return value;
}

static inline uint32_t velo2_get_tx_id(uint32_t vpid)
{
  uint64_t value;
  value=get_extoll_rf_velo_rf_node_vpid_prot_desc(vpid);
  value= value & 0xffffff000000ffffl;
  value=value>>16l;
  return value;
}


static inline void velo2_set_rx_protection_descriptor(uint32_t vpid, uint16_t protdesc)
{
  uint64_t value;
  value=get_extoll_rf_velo_rf_comp_prot_desc(vpid);
  value= value & 0xffffffffffff0000l;
  value=value | protdesc;
  set_extoll_rf_velo_rf_comp_prot_desc(vpid,value);
}

static inline uint16_t velo2_get_rx_protection_descriptor(uint32_t vpid)
{
  uint64_t value;
  value=get_extoll_rf_velo_rf_comp_prot_desc(vpid);
  value= value & 0xffffl;
  return value;
}

static inline void velo2_set_rx_vpid_enable(uint32_t vpid, uint8_t enable)
{
  uint64_t value;
  value=get_extoll_rf_velo_rf_comp_prot_desc(vpid);
  value= (value & 0x1ffffl) | ( (enable& 0x1l)<<17l) ;
  set_extoll_rf_velo_rf_comp_prot_desc(vpid,value);
}

static inline uint16_t velo2_get_rx_vpid_enable(uint32_t vpid)
{
  uint64_t value;
  value=get_extoll_rf_velo_rf_comp_prot_desc(vpid);
  value= (value >> 17l) & 1l;
  return value;
}

static inline void velo2_set_rx_htax_reroute_enable(uint32_t vpid, uint32_t enable)
{
  uint64_t value;
  value=get_extoll_rf_velo_rf_comp_prot_desc(vpid);
  value= value & 0xfffffffffffeffffl;
  value=value | ( (enable& 0x1l)<<16l);
  set_extoll_rf_velo_rf_comp_prot_desc(vpid,value);
}

static inline uint32_t velo2_get_rx_htax_reroute_enable(uint32_t vpid)
{
  uint64_t value;
  value=get_extoll_rf_velo_rf_comp_prot_desc(vpid);
  value= value & 0xfffffffffffeffffl;
  value=(value>>16l) & 0x1l;
  return value;
}


static inline void velo2_rx_set_timeout(uint32_t timeout, uint32_t enable)
{
  uint64_t value;
  value=((uint64_t) enable)<<32l | timeout;
  set_extoll_rf_velo_rf_timeout(value);
}

static inline uint32_t velo2_rx_get_timeout(void)
{
  uint64_t value;
  value=get_extoll_rf_velo_rf_timeout();
  return value & 0xffffffffl;
}

static inline uint32_t velo2_rx_get_timeout_enable(void)
{
  uint64_t value;
  value=get_extoll_rf_velo_rf_timeout();
  return (value & 0x100000000l )>> 32l;
}

static inline void velo2_rx_set_alternative_htax_port(uint16_t port)
{
  uint64_t value;
  value=get_extoll_rf_velo_rf_completer() & 0x200l;
  value=value | (port & 0x1ff);
  set_extoll_rf_velo_rf_completer(value);
}

static inline uint8_t velo2_rx_get_alternative_htax_port(void)
{
  uint64_t value;
  value=get_extoll_rf_velo_rf_completer() & 0x1ffl;
  return value;
}

static inline void velo2_rx_enable_large_slots(uint32_t enable)
{
  uint64_t value;
  value=get_extoll_rf_velo_rf_completer() & 0x1ffl;
  value= value | ( (enable & 0x1)<<9);
  set_extoll_rf_velo_rf_completer(value);
}

static inline uint32_t velo2_rx_get_large_slots(void)
{
  uint64_t value;
  value=get_extoll_rf_velo_rf_completer() & 0x200l;
  return value>>9l;
}


/**
* reads details of a completer port descriptor. If descriptor
* does not exist it is created and gets added to the completer list
*
* @param nump	port number of requester
*/
static velo_port_t *velo_get_port(int i)
{
  return ports[i];
}

static inline void velo2_tx_set_timeout(uint32_t timeout, uint32_t enable)
{
  uint64_t value;
  value=((uint64_t) timeout)<<32l | (((uint64_t)enable) & 0x1l);
  set_extoll_rf_velo_rf_wcbuf_rf_timeout(value);
}

static inline uint32_t velo2_tx_get_timeout(void)
{
  uint64_t value;
  value=get_extoll_rf_velo_rf_wcbuf_rf_timeout();
  return ((value>>32l) & 0xffffffffl);
}

static inline uint32_t velo2_tx_get_timeout_enable(void)
{
  uint64_t value;
  value=get_extoll_rf_velo_rf_wcbuf_rf_timeout();
  return (value & 0x1l);
}

/**
get the logical read pointer
*/
uint64_t velo2_get_rp(velo_port_t *portp)
{
  uint64_t value;
  value=bq_get_lrp(portp->bq);
  dev_dbg(DEV,"velo2: logical read pointer is %llx\n", value); 
  return value;
} 
EXPORT_SYMBOL(velo2_get_rp);

/**
set the logica read pointer
*/
void velo2_set_rp(velo_port_t *portp, uint64_t new_rp)
{
  portp->rp=new_rp;
  portp->wb_rp=new_rp;

  bq_set_lrp(portp->bq,new_rp);
}
EXPORT_SYMBOL(velo2_set_rp);

/**
* Retrieves the actual write pointer from velo device
* The write pointer has a size of 64 bit at the moment.
* @param *portp: Every Mailbox has a seperate write pointer.
*                 Therefor portp allows the function to find
*                 out what mailbox is meant.
*/
uint64_t velo2_get_wp(velo_port_t *portp)
{
  uint64_t value;
  value=bq_get_lwp(portp->bq);
  dev_dbg(DEV,"velo2: logical write pointer is %llx\n", value);

  return value;
}
EXPORT_SYMBOL(velo2_get_wp);

/**
* Sets the write pointer of velo device
* @param *portp: completer port management data
*/
void velo2_set_wp(velo_port_t *portp, uint64_t new_wp)
{
  bq_set_lwp(portp->bq,new_wp);
}
EXPORT_SYMBOL(velo2_set_wp);

static void velo2_release_port(velo_port_t* portp)
{
	if (portp!=NULL)
	{
          dev_dbg(DEV,"velo2: destroying port %d\n",portp->vpid);
	  if (portp->bq!=NULL)
		bq_destroy_queue(portp->bq);
	  memset(portp,0,sizeof(velo_port_t));
	}
}

int velo2_find_free_vpid(void)
{
  int i;
  int vpid_increment;
  //find the number of vpids per page, if system has larger page size -> then only every xth vpid should be used
  vpid_increment=extoll_query_vpids_per_page();
  dev_dbg(DEV,"velo2: Looking for free vpid...\n");
  for (i=VELO2_MIN_VPID;i<EXTOLL_VPID_MAX;i=i+vpid_increment)
    {
       if (ports[i]->opened==0)
	{
          dev_dbg(DEV, "velo2: Return free VPID: %u\n",i);
          return i;
	}
    }
  dev_info(DEV,"No free vpid found...\n");
  return -1;
}

int velo2_check_free_vpid (int vpid)
{
    if (vpid % extoll_query_vpids_per_page() != 0 ) //machine with odd page size, check whether vpid is supported
    {
      dev_alert(DEV,"checking vpid %d for availability, which is not supported with page size %ld\n",vpid,PAGE_SIZE);
      return -1;
    }
    if (ports[vpid]->opened==0)
    {
       dev_dbg(DEV,"Acquired requested VPID: %u\n",vpid);
       return vpid;
    }
    return -1;
}

int velo2_find_owned_vpid(int pid)
{
  int i;
  dev_dbg(DEV," Looking for  vpid owned by pid %u...\n",pid);
  for (i=VELO2_MIN_VPID;i<VELO2_MAX_VPID;i++)
    {
      if (ports[i]->pid!=pid)
        {
          dev_dbg(DEV,"Found vpid %d\n",i);
          return i;
        }
    }
  dev_info(DEV,"No vpid found\n");
  return -1;
}

/* ***************************************************************************
 *  methods to support the extoll kapi
 * ***************************************************************************/
int velo2_lock_mutex(void)
{
 mutex_lock(&velo_mutex);
 return 0;
}
EXPORT_SYMBOL(velo2_lock_mutex);

void velo2_unlock_mutex(void)
{
 mutex_unlock(&velo_mutex);
}
EXPORT_SYMBOL(velo2_unlock_mutex);



//if vpid==-1 find a free one, otherwise try to use the given one
int velo2_init_port (velo_port_t **portp, int vpid)
{
  int i;
        

  if (vpid==-1)
    vpid = velo2_find_free_vpid();
  else
    vpid = velo2_check_free_vpid(vpid);
  
  *portp = velo_get_port(vpid);
  if((*portp)==0) {
    dev_alert(DEV,"all ports in use.\n");
    return -EFAULT;
  }
  memset(*portp,0,sizeof(portp));

  (*portp)->pid = current->pid;
  (*portp)->opened++;
  (*portp)->kernel_owned = 1; //this should be set by caller
  (*portp)->vpid = vpid;
  (*portp)->mbox_size = velo_dma_size_cmp;
  (*portp)->wb_rp = 0;  
  (*portp)->rp = 0;  
  (*portp)->tx_prot_desc = 0;
  (*portp)->rx_prot_desc = 0;
  (*portp)->src_id = ((*portp)->vpid<<16l) | ((get_extoll_rf_info_rf_node() >>24l) & 0xffffl);;
  dev_dbg(DEV,"set source id to %x, vpid is %d, node id is %d\n",(*portp)->src_id,(*portp)->vpid,(int)((get_extoll_rf_info_rf_node() >>24l)& 0xffffl));
  (*portp)->htax_alternative_port_enable=0;
  (*portp)->htax_alternative_port=0;
  for (i=0;i<4;i++)
	(*portp)->allow_tc_mapped[i]=0;
  (*portp)->allow_alternative_port=0;
  (*portp)->bq=0;
#ifdef MICEXTOLL //FIXME
  (*portp)->desc_size=64*1024; //64kB default segment size
#else
  if (PAGE_SIZE > 512*1024)
    (*portp)->desc_size=PAGE_SIZE;
  else
    (*portp)->desc_size=4*1024*1024; //64kb default segment size
#endif
  dev_dbg(DEV,"set desc_size to %lx for vpid %d\n", (unsigned long) (*portp)->desc_size, (*portp)->vpid);
   
  //set all the registers for the VPID
  velo2_set_tx_protection_descriptor(vpid, (*portp)->tx_prot_desc);
  velo2_set_tx_id(vpid, ((get_extoll_rf_info_rf_node() >>24l) & 0xffffl), (*portp)->vpid);
  velo2_set_rx_protection_descriptor(vpid, (*portp)->rx_prot_desc);
  velo2_set_rx_htax_reroute_enable(vpid, 0);
  
  //bug: should only be enabled, when BQ is initialized, need to check this!
  //velo2_set_rx_vpid_enable(vpid, 1);
  
  dev_dbg(DEV,"opened device by pid:%d got vpid %d!\n",(int)(*portp)->pid,(*portp)->vpid);
  return 0;
}
EXPORT_SYMBOL(velo2_init_port);

int velo2_open_completer(velo_port_t *portp, unsigned int total_size, unsigned int desc_size)
{
  int result;
  int size = portp->desc_size;
  int desc = portp->desc_size;
  
  if (portp->bq!=NULL)
      bq_destroy_queue(portp->bq);

  if(0 != total_size)
	  size = total_size;
  if(0 != desc_size)
	  desc = desc_size;
  //portp->bq = bq_init_queue(portp->mbox_size,VELO_BQ, portp->vpid, 64,portp->desc_size,&result); //from libvelo... but to test here, we want:
  portp->bq = bq_init_queue(size,VELO_BQ, portp->vpid, velo2.slot_size,desc,&result); // just init one descriptor, so that all memory is in one chunk
  if (portp->bq==0) {
    dev_alert(DEV,"memory allocation for VPID %d receive queue failed (BQ).\n", portp->vpid);
    return result;
  }
  velo2_set_rx_vpid_enable(portp->vpid, 1);
  return 0;
}
EXPORT_SYMBOL(velo2_open_completer);

int velo2_close_port(velo_port_t *portp)
{
  if(portp==0) {
    dev_alert(DEV,"close: no port to destroy...\n");
    return 0; 
  }

  //bq_get_lrp(port->queue);
  dev_dbg(DEV,"closing port %d. BQ Info: no_of_entries: %d size %ld slot_size %d ",portp->vpid,portp->bq->no_of_entries, (unsigned long) portp->bq->size,portp->bq->slot_size);
//   port->queue->no_of_entries
//   bq_size
//   bq_slot_size
  
  velo2_set_rx_vpid_enable(portp->vpid, 0);;
  velo2_set_tx_protection_descriptor(portp->vpid, 0);
  //velo2_set_tx_id(portp->vpid, 0,0);
  velo2_set_rx_protection_descriptor(portp->vpid, 0);
  velo2_set_rx_htax_reroute_enable(portp->vpid, 0);
  velo2_release_port(portp);
 
  return 0; 
}
EXPORT_SYMBOL(velo2_close_port);


/******************************************************************************
*  file operations of velo device					      *
******************************************************************************/
/**
* Check if process already opened velo. If not create new owner list entry
* and add it to the list of owners
*/
static int velo2_open(struct inode *inodp, struct file *filp)
{
  velo_port_t *portp;
  int vpid;
  int minor;
  int i;
  uint64_t old_wcb_state;
  uint64_t new_wcb_state;
  int register_value;


  minor = MINOR(inodp->i_rdev);
  if (minor!=VELO2_MINOR)
  {
        dev_alert(DEV,"trying to open invalid minor.\n");
	return -EINVAL;
  }
 
  
  /* check if network is ready -> if not return -EAGAIN
   */
  if (extoll_get_nw_state()!=EXTOLL_NW_STATE_C) //network not configured
  {
    return -EAGAIN;
  }
  
  dev_dbg(DEV,"opened velo2 special file...\n");

  if (mutex_lock_interruptible(&velo_mutex)) {
        return -ERESTARTSYS;
  }



  vpid=velo2_find_free_vpid();
  if (vpid==-1)  //all VPIDs in use
	{
          dev_alert(DEV,"All VPIDs in use.\n");
	  mutex_unlock(&velo_mutex);

	  return -EBUSY;
	}
  /* register this task with the nw state task monitoring facitilty (to it gets stopped if necessary) */
  extoll_add_nw_state_task(vpid, VELO_VPID, current);
  //Network state could have changed after last check, so check again if we are in stopped state:
  register_value=get_extoll_rf_info_rf_scratchpad_scratchpad(EXTOLL_SCRATCH_NETWORK_STATE);
  if(register_value != 1) {
	  EKVCL_force_sig(SIGSTOP);
  }

  portp = velo_get_port(vpid);
  if (portp==0) {
        dev_alert(DEV,"no port available\n");
	mutex_unlock(&velo_mutex);
        extoll_remove_nw_state_task(vpid, VELO_VPID);

	return -EFAULT;
  }
  dev_dbg(DEV,"got portp for pid %ld\n",(long int)current->pid);
  /* init new port */
  memset(portp,0,sizeof(velo_port_t));
  portp->pid = current->pid;
  //atomic_set(&ownerp->rcount, 0);
  portp->opened++;
  portp->kernel_owned=0;
  portp->vpid=vpid;
  portp->mbox_size=velo_dma_size_cmp;
  
  portp->wb_rp=0;
  portp->rp=0;
  portp->tx_prot_desc=0;
  portp->rx_prot_desc=0;
  portp->src_id=(portp->vpid<<16l) | ((get_extoll_rf_info_rf_node() >>24l) & 0xffffl);
  dev_dbg(DEV,"set source id to %x, vpid is %d, node id is %d\n",portp->src_id,portp->vpid,(int)((get_extoll_rf_info_rf_node() >>24l)& 0xffffl));
  portp->htax_alternative_port_enable=0;
  portp->htax_alternative_port=0;
  for (i=0;i<4;i++)
	portp->allow_tc_mapped[i]=0;
  portp->allow_alternative_port=0;
  portp->bq=0;
  
  if (PAGE_SIZE > 64*1024)
    portp->desc_size=PAGE_SIZE;
  else
    portp->desc_size=64*1024; //64kb default segment size
   
  //set all the registers for the VPID
  velo2_set_tx_protection_descriptor(vpid, portp->tx_prot_desc);
  velo2_set_tx_id(vpid, ((get_extoll_rf_info_rf_node() >>24l) & 0xffffl), portp->vpid);
  velo2_set_rx_protection_descriptor(vpid, portp->rx_prot_desc);
  velo2_set_rx_htax_reroute_enable(vpid, 0);

  old_wcb_state=get_extoll_rf_velo_rf_wcbuf_rf_state(vpid);
  new_wcb_state=old_wcb_state & 0x00ffffffff000000l;
  set_extoll_rf_velo_rf_wcbuf_rf_state(vpid, new_wcb_state);
  dev_dbg(DEV,"vpid %d: wcb old state was %lx, new state will be %lx\n",vpid,(unsigned long)old_wcb_state,(unsigned long)new_wcb_state);


  //bug: should only be enabled, when BQ is initialized, need to check this!
  //velo2_set_rx_vpid_enable(vpid, 1);
  mutex_unlock(&velo_mutex);      
  dev_dbg(DEV,"opened device by pid:%d got vpid %d!\n",(int)portp->pid,portp->vpid);
      
  /* assign to filp for fast access */
  filp->private_data = portp;
  aoi_recv_msg=0; 
 //extoll_set_interrupt_counter(0);       
  return 0;
}

/**
* standard file ops are used to access config entries of velo ports
* llseek changes position to the port(offset) that should be next read
* or written from.
*/

//not supported any more...
static loff_t velo2_llseek(struct file *filp, loff_t off, int whence)
{
  return -EFAULT;
}

/**
* whenever a process releases the velo device his kalloced mem has to be
* cleared and all used ports have to be freed.
*/
static int velo2_release(struct inode *inodp, struct file *filp)
{
  velo_port_t* portp;
  uint32_t slots;
  uint64_t wp;
  uint64_t rp;
  uint64_t old_wp;
  int i;

  dev_dbg(DEV,"release called [pid %d]\n", (int)current->pid);
  portp = filp->private_data;

  if (portp==0) {
    dev_dbg(DEV,"velo2_release: no port to destroy, return...\n");
    return 0;
  }
 if (mutex_lock_interruptible(&velo_mutex)) {
        return -ERESTARTSYS;
  }


 if (portp->bq==0) {
    dev_dbg(DEV, "velo2_release: no bq to be destroyed...\n");
 } else {
   dev_dbg(DEV,"velo2_release: closing port %d. BQ Info: no_of_entries: %d size %ld slot_size %d ",portp->vpid,portp->bq->no_of_entries, (unsigned long) portp->bq->size,portp->bq->slot_size);
   slots=portp->bq->size/portp->bq->slot_size;
   wp=bq_get_lwp(portp->bq);
   i=0;
   do {
    old_wp=wp;
    rp=(wp+1) % slots;
    i++;
    dev_dbg(DEV,"velo2_release:%d: wp from hw is %ld, setting rp to %ld\n",i,(unsigned long)wp,(unsigned long)rp);
    bq_set_lrp(portp->bq,rp);
    wp=bq_get_lwp(portp->bq);
   } while (old_wp!=wp && i<1000);
 }
 //set all the registers for the VPID
 velo2_set_rx_vpid_enable(portp->vpid, 0);;
 velo2_set_tx_protection_descriptor(portp->vpid, 0);
 //velo2_set_tx_id(portp->vpid, 0,0);
 velo2_set_rx_protection_descriptor(portp->vpid, 0);
 velo2_set_rx_htax_reroute_enable(portp->vpid, 0);


  //remove task from nw state monitoring
  extoll_remove_nw_state_task(portp->vpid, VELO_VPID);
 
  velo2_release_port(portp);
  mutex_unlock(&velo_mutex);
  dev_dbg(DEV,"port was succesfully released.\n");
  return 0;
}

/********************************************************************************/
/*  VMA operations                                                             **/
/* ******************************************************************************/

/******************************************************************************
*  velo memory mappings                                                       *
******************************************************************************/
//FIXME: no TC and alternative port etc support yet!
/**
* Map a requester port into userspace. 
* There is only one port per VPID anymore.
* First implementation will map the minimum, which is one page!
*/
static int velo2_mmap_req(velo_port_t *portp, struct vm_area_struct *vma)
{
  unsigned long vsize = 0;	// size of needed virtual address space
  unsigned long physical = 0;	// physical start address
  unsigned long pfn;	// page frame number
  int err;		// error code
    
  
  vsize = vma->vm_end - vma->vm_start;
  dev_dbg( DEV, "mmap requester called\n");
  dev_dbg( DEV,"velo2: mmap called for requester space. offset is %lx, vpid is %d\n",
        (unsigned long)vma->vm_pgoff << PAGE_SHIFT,portp->vpid);
  
  if (vsize!=2*PAGE_SIZE) 
	return -EINVAL;
 
  if (vma->vm_end - vma->vm_start == 2*PAGE_SIZE) {
    //first remap state (no pgprot magic necessary), but map at the end of the region
    //FIXME: offset address is constant and may change...
    physical = extoll_get_rf_addr() + 0x1000000l + (EXTOLL_PAGE * portp->vpid); //FIXME Check if we need for MIC 16777216 
    pfn = physical >> PAGE_SHIFT;
#ifdef LS3BEXTOLL
    vma->vm_page_prot=pgprot_noncached(vma->vm_page_prot);
#endif        
    io_remap_pfn_range(vma, vma->vm_start+PAGE_SIZE, pfn, PAGE_SIZE, vma->vm_page_prot);
    dev_dbg(&velo2.devp->dev,"mmaping wcbuf state to user space\n");
    physical = extoll_get_velo2_addr() + EXTOLL_PAGE * portp->vpid;

    vsize = vma->vm_end - vma->vm_start;            
    dev_dbg(DEV,"requester (wc): physical %lx, vsize %lu, vm_start is %lx\n", physical, vsize,vma->vm_start);

    pfn = physical >> PAGE_SHIFT;
    dev_dbg(DEV, "pfn is: %lx\n", pfn);
    //set WC protection
#ifndef   LS3BEXTOLL  
    vma->vm_page_prot=__pgprot(pgprot_val(vma->vm_page_prot) | EXTOLLWCATTR);
#endif    
    
    io_remap_pfn_range(vma, vma->vm_start, pfn, PAGE_SIZE, vma->vm_page_prot);
    dev_dbg(&velo2.devp->dev,"remapping iomem.\n");
  } else {
    dev_alert(DEV,"Illegal mmap request for requester \
                port %lx\n", vma->vm_pgoff);
    err = -EFAULT;
    return err;
  }
  return 0;
}

/**
* Map a completer port into userspace. The destination of the port is
* derived from vm_pgoff. As far as the completer only has to care about the
* local mailboxes we don't care about the node_id. That means vm_pgoff is
* equal to the mailbox_id.
* steps:
* 1. find/create completer port structure
* 2. check state of "opened"
* 3. if not already opened by another process open the port and assign
*    owner "descriptor"
* 4. Initialize a corresponding DMA area
* 5. let velo know the dma base address for this mailbox
*/
static int velo2_mmap_cmp(velo_port_t *portp, struct vm_area_struct *vma)
{
  int  result;
  
  if (portp->bq!=NULL)
    bq_destroy_queue(portp->bq);
  dev_dbg(&velo2.devp->dev,"cmp mmap called. now calling bq_init_queue with size of %u and slot_size %u\n",portp->mbox_size,velo2.slot_size);
  portp->bq=bq_init_queue(portp->mbox_size,VELO_BQ, portp->vpid, velo2.slot_size,portp->desc_size,&result);
  if (portp->bq==0)
  {
    dev_alert(DEV,"memory allocation for VPID %d receive queue failed (BQ).\n", portp->vpid);
    return -1;
   }
  dev_dbg(DEV,"calling bq_mmap\n");
  result=bq_mmap(vma,portp->bq);    
  if (result==0) velo2_set_rx_vpid_enable(portp->vpid, 1); 
  return result;
}

static int velo2_mmap(struct file *filp, struct vm_area_struct *vma)
{
  int err;
  unsigned long off;	// complete offset starting from bar2
  velo_port_t *portp;   // owner of mmaped port


  dev_dbg(DEV,"starting mmap for port %lu!!\n",vma->vm_pgoff);
  off = vma->vm_pgoff << PAGE_SHIFT;
  
  portp = filp->private_data;	//created in velo_open()
  if (!portp) {
    dev_alert(DEV,"maping tx no port available\n");

    return -EFAULT;
  }

  if (portp->vpid % extoll_query_vpids_per_page() != 0 ) //machine with odd page size, check whether vpid is supported
  {
      dev_alert(DEV,"mmaping requested for vpid %d, which is not supported with page size %ld\n",portp->vpid,PAGE_SIZE);
      return -EFAULT;
  } 


  if (mutex_lock_interruptible(&velo_mutex)) {
        return -ERESTARTSYS;
  }

  /* do real mmap in seperate function
  */
  if (off==0) //mmap TX side
  {
	dev_dbg(DEV,"requester\n");
	err = velo2_mmap_req(portp, vma);
	dev_dbg(DEV,"requester mmap returns %d\n",err);
  }
  else //mmap RX side
  {
	dev_dbg(DEV,"completer\n");
	err = velo2_mmap_cmp(portp, vma);
	dev_dbg(DEV,"completer mmap returns %d\n",err);
  }
  mutex_unlock(&velo_mutex);
  dev_dbg(DEV,"mmap call done\n");
  return err;
}

/******************************************************************************
 * Helper functions for the EXTOLL Kernel API				      *
 * 2011 by Tobias Groschup				      *
 * FIXME: reduce copypasta, respect DRY ;)
 *****************************************************************************/
/**
 * Returns a struct with the needed pointers to access the velo-device
 */
velo2_device_t* velo2_get_device(void)
{
  return &velo2;
}


/**
 * returns the mbox_id
 */

uint32_t velo2_get_nodeid()
{
  uint32_t nodeid=(get_extoll_rf_info_rf_node()>>24l)&0xffffl ;
  return nodeid;
}
//EXPORT_SYMBOL(velo2_get_nodeid); //also standing at the end of the file


/**
 * get the mbox_size
 */

uint velo2_get_mbox_size()
{
  return velo_dma_size_cmp;
}

/******************************************************************************
* SYSFS entries                                                               *
******************************************************************************/

static ssize_t velo2_processes_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int i = 0;
	ssize_t count = 0;
	for(i=VELO2_MIN_VPID; i<VELO2_MAX_VPID; i++) {
		int pid = -1;
		if(ports[i]->opened) {
			pid = ports[i]->pid;
		}
		count += sprintf(buf, "%i:\t%i\n", i, pid);
		buf += strlen(buf);
	}

	return count;
}

static ssize_t velo2_processes_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	int ret = 0;
	unsigned int vpid;
	char const *current_position = buf;
	velo_port_t *port;
	pid_t pid;
	struct pid *pid_struct = NULL;
	struct task_struct *task = NULL;

	static char start_string[] = "free ";
	int start_string_size = strlen(start_string);

	ret = strncmp(start_string, current_position, start_string_size);
	if(ret) {
		dev_alert(DEV, "Format: %s<vpid> (vpid in base10, hexadeximal or octal)\n", start_string);
		return -EINVAL;
	}
	current_position += start_string_size;

	ret = kstrtouint(current_position, 0, &vpid);
	if(ret) {
		dev_alert(DEV, "Error on parsing vpid. Format of vpid: positiv base10, hexadecimal(0x...) or octal(0...)\n");
		return -EINVAL;
	}

	if(vpid < VELO2_MIN_VPID || vpid >= VELO2_MAX_VPID) {
	       dev_alert(DEV, "VPID to free must be between %i and %i\n", VELO2_MIN_VPID, VELO2_MAX_VPID-1);
	       return -EINVAL;
	}

	port = ports[vpid];
	if(!port->opened) {
		dev_info(DEV, "VPID %i not in use, nothing to free.\n", vpid);
		goto out;
	}

	pid = port->pid;
	pid_struct = find_get_pid(pid);
	if(pid_struct == NULL) {
		dev_info(DEV, "No pid_struct found for PID %ld, freeing VPID %i\n", (long) pid, vpid);
		goto close_port;
	}

	task = pid_task(pid_struct,PIDTYPE_PID);
      	if(task != NULL) {
		dev_alert(DEV, "Found active task for PID %ld registered to VPID %i, doing nothing\n", (long) pid, vpid);
		return -EINVAL;
	}

	//After all sanity checks we can close the port as the process does not exist anymore.
close_port:
	velo2_close_port(port);

out:	
	return strnlen(buf, count);
}

static DEVICE_ATTR_RW(velo2_processes);

static struct attribute *velo2_attrs[] = {
	    &dev_attr_velo2_processes.attr,
	    NULL
};
ATTRIBUTE_GROUPS(velo2);

/******************************************************************************
*  IO controls			                                              *
******************************************************************************/
//static int velo2_ioctl(struct inode *inodp, struct file *filp,
                      //unsigned int cmd, unsigned long arg)
static long velo2_ioctl_unlocked(struct file *filp,
                      unsigned int cmd, unsigned long arg)
{
  velo_port_t * portp;
  //int minor;
  portp = filp->private_data;
//   minor = MINOR(inodp->i_rdev);

  if (portp==NULL) {
    dev_alert(DEV,"ioctl: invalid port\n");
    return -EFAULT;
  }

  // Do some security tests on the requested command number
  if (_IOC_TYPE(cmd) != VELO2_IOC_MAGIC)
    return -ENOTTY;

  if (_IOC_NR(cmd) > VELO2_IOC_MAXNR)
    return -ENOTTY;

  // test provided argument buffer for necessary access rights
  if (_IOC_DIR(cmd) & _IOC_READ) {
    if (!EKVCL_access_ok(VERIFY_WRITE, (void *)arg, _IOC_SIZE(cmd)))
      return -EFAULT;
  }

  if (_IOC_DIR(cmd) & _IOC_WRITE) {
    if (!EKVCL_access_ok(VERIFY_READ, (void *)arg, _IOC_SIZE(cmd)))
      return -EFAULT;
  }

  switch (cmd) {
  case (VELO2_IOCG_GET_RP):
    {
      uint64_t rp;
      rp =  velo2_get_rp(portp);
      return put_user(rp, ((uint64_t *) arg));
      break;
    }
  case (VELO2_IOCT_SET_RP):
    {
      velo2_set_rp(portp, ((uint64_t) arg));
      break;
    }
  case (VELO2_IOCG_GET_WP):
    {
      uint64_t wp;
      wp = velo2_get_wp(portp);
      return put_user(wp, ((uint64_t *) arg));
      break;
    }
  case (VELO2_IOCT_SET_WP):
    {
      velo2_set_wp(portp, ((uint64_t) arg));
      break;
    }
  case (VELO2_IOCG_GET_VPID):       
    {         
      uint32_t vpid=portp->vpid;
      return put_user(vpid, ((uint64_t*) arg));
      break;
    }
  case (VELO2_IOCG_GET_NODEID):       
    {         
     // uint32_t nodeid=UNIT_TYPE__NODE_ID__READ(read64(&extoll_rf->ids));
      return put_user(velo2_get_nodeid(), ((uint64_t*) arg));
      break;
    }
  case (VELO2_IOCG_GET_MBOX_SIZE):       
    {         
      uint32_t size=portp->mbox_size;
      return put_user(size, ((uint64_t*) arg));
      break;
    }
  case (VELO2_IOCG_SET_MBOX_SIZE):       
    {         
       if (arg % PAGE_SIZE != 0 )
          {
            dev_alert(DEV,"queue size requested to be %ld which is not a multiple of the machine page size (%ld), which is not supported\n",arg, PAGE_SIZE);
            return -EFAULT;
          }
	  portp->mbox_size=arg;    
	  dev_dbg(DEV,"setting queue size to %lu\n",arg);
      break;
    }
  case (VELO2_IOCG_GET_SEGMENT_SIZE):       
    {         
      uint32_t size=portp->desc_size;
      return put_user(size, ((uint64_t*) arg));
      break;
    }
  case (VELO2_IOCG_SET_SEGMENT_SIZE):       
    {         
          if (arg % PAGE_SIZE != 0 )
          {
            dev_alert(DEV,"segment size requested to be %ld which is not a multiple of the machine page size (%ld), which is not supported\n",arg, PAGE_SIZE);
            return -EFAULT;
          }
	  portp->desc_size=arg;    
	  dev_dbg(DEV,"setting segment size to %lu\n",arg);
      break;
    }
  case (VELO2_IOCG_GET_TX_PROTDESC):       
    {         
      uint32_t vpid=portp->vpid;
      uint64_t descriptor=velo2_get_tx_protection_descriptor(vpid);
      return put_user(descriptor, ((uint64_t*) arg));
      break;
    }
  case (VELO2_IOCG_GET_RX_PROTDESC):       
    {         
      uint32_t vpid=portp->vpid;
      uint64_t descriptor=velo2_get_rx_protection_descriptor(vpid);
      return put_user(descriptor, ((uint64_t*) arg));
      break;
    }
  case (VELO2_IOCG_GET_TX_ID):       
    {         
      uint32_t vpid=portp->vpid;
      uint64_t descriptor=velo2_get_tx_id(vpid);
      return put_user(descriptor, ((uint64_t*) arg));
      break;
    }
  case (VELO2_IOCG_SET_TX_PROTDESC):
    {
      uint32_t vpid=portp->vpid;
      velo2_set_tx_protection_descriptor(vpid, (uint16_t)(arg & 0xffffl));
      break;
    }
  case (VELO2_IOCG_SET_RX_PROTDESC):
    {
      uint32_t vpid=portp->vpid;
      velo2_set_rx_protection_descriptor(vpid, (uint16_t)(arg & 0xffffl));
      break;
    }
  case (VELO2_IOCG_SET_TX_ID):
    {
      uint32_t vpid=portp->vpid;
      uint16_t tx_nodeid=(uint16_t)(arg & 0xffffl);
      uint16_t tx_vpid=(uint16_t)((arg & 0xffff0000l)>>16l);
      velo2_set_tx_id(vpid, tx_nodeid,tx_vpid);
      break;
    }
  case (VELO2_IOCG_GET_PROCNUM):
    {
      uint32_t vpid=VELO2_VPIDS;
      return put_user(vpid, ((uint64_t*) arg));
      break;
    }
  case (VELO2_IOCG_GET_NODENUM):
    {
      uint32_t nodeid=VELO2_NODES;
      return put_user(nodeid, ((uint64_t*) arg));
      break;
    }
  case (VELO2_IOCG_GET_SLOT_SIZE) :
    {
      uint32_t slot_size=velo2.slot_size;
      return put_user(slot_size, (uint64_t *) arg);
      break;
    }    
  default:
    {
      dev_info(DEV,"unknown minor and/or IOCTL\n");
      break;
    }
  }

  return 0;
}

/**
* velo file operations
*/
static struct file_operations velo_fops = {
  .owner = THIS_MODULE,
  .llseek = velo2_llseek,
  .mmap = velo2_mmap,
  .unlocked_ioctl = velo2_ioctl_unlocked,
  .open = velo2_open,
  .release = velo2_release,
};

/******************************************************************************
*  PCI subsystem integration                                                  *
******************************************************************************/
/**
* set up the char_dev structure for requester & completer
* @return 0 if everyting is OK otherwise errorcode is returned
*/
static int velo2_setup_cdev(void)
{
  int err, devnr;

  /* setup requester first */
  devnr = MKDEV(MAJOR(velo2.devnr), VELO2_MINOR);
  cdev_init(&velo2.cdev, &velo_fops);
  velo2.cdev.owner = THIS_MODULE;
  velo2.cdev.ops = &velo_fops;
  err = cdev_add(&velo2.cdev, devnr, 1);
  if (err < 0)
  {
    dev_dbg(DEV,"Error %d adding cdev", err);
    cdev_del(&velo2.cdev);
    return err;
  }

  return 0;
}
/* VELO Interrupt handlers - called from interrupt dispatcher in extoll base driver
 */
//there is one possible handler per trigger group (interrupt cause)
static velo2_i_handler velo2_vpid_handlers[256];

void velo2_default_vpid_handler(int vpid,snq_entry_t* entry)
{
  if (printk_ratelimit()) {
    dev_info(DEV,"default vpid message handler. new message available for vpid %d (rate limited)\n",vpid);
    snq_dump_entry(entry);
  }
}

/* initialize the irq function pointer array */
void init_velo2_interrupt_handlers(void)
{
  int i;
  for (i=0;i<64;i++)
    {
      velo2_vpid_handlers[i]=velo2_default_vpid_handler;
    }
}

/* register a handler function for the extoll interrupt cause with the given idx
  */
void velo2_register_vpid_irq_handler(int idx, velo2_i_handler handler)
{
  dev_info(DEV,"register velo2 irq handler for vpid %d\n",idx);
  velo2_vpid_handlers[idx]=handler;
}
EXPORT_SYMBOL(velo2_register_vpid_irq_handler);

/* register a handler function for the extoll interrupt cause with the given idx
  */
void velo2_deregister_vpid_irq_handler(int idx)
{
  velo2_vpid_handlers[idx]=velo2_default_vpid_handler;
}
EXPORT_SYMBOL(velo2_deregister_vpid_irq_handler);

void velo2_error_irq_handler(snq_entry_t* entry, int te, int entry_idx)
{
 if (printk_ratelimit()) {  
    dev_alert(DEV,"error irq handler (rate limited)\n");
    snq_dump_entry(entry);
 }
}

void velo2_msg_irq_handler(snq_entry_t* entry,int te, int entry_idx)
{
  int i,j,vpid;
  uint64_t value;
  velo2_i_handler handler;
  dev_dbg(DEV,"message interrupt handler\n");
  
  //snq_dump_entry(entry);
  // ok now look at the vpid bits, one by one...
  for (i=0;i<4;i++)
  {
    //select one of the four sources
    value = (unsigned long) entry->payload[3+i];
    for (j=0;j<64;j++)
    {
      //now check each bit
      if ((value & 0x1l)==0x1l) //bit j is set
      {
	vpid=i*64+j;	
	dev_dbg(DEV,"Event for vpid %d\n",vpid);
	handler=velo2_vpid_handlers[vpid];
	dev_dbg(DEV,"velo2_msg_irq_handler: using %p for vpid %i\n", handler, vpid);
	(*handler)(vpid,entry);
	
      }
      value=value>>1l;
    }
  }
}



/**
* initialize velo device in order to work seamless in kernel pci subsystem.

*/

static int velo2_probe(void)
{

  velo_port_t *portp = NULL;
  int i,j;
  int result=0;
  uint64_t value;
  uint64_t old_wcb_state;
  uint64_t new_wcb_state;


  velo2.devp = extoll_get_pdev();
  if (velo2.devp==0)
    {
      printk(KERN_ALERT "velo2: no device found.\n");
      return -EINVAL;
    }

  /*if (extoll_query_max_htoc_size()==64) {
     printk(KERN_ALERT "velo2: 128 byte slots not available on this system. 64 Byte Slots no longe supported by this SW version. Bailing out.\n");
     return -ENOMEM;
  }*/

  

  /* dynamically allocate a major number and create two minor numbers:
  * ->  minor 0 = requester
  * ->  minor 1 = completer
  */
  if (alloc_chrdev_region(&velo2.devnr, 0, VELO2_MINOR_COUNT, "velo2")) {
    printk(KERN_ALERT "velo2: No Major Number available!!\n");
    result=-EBUSY;
    goto velo_open_err_no_major;
  };
  dev_dbg(DEV,"major number: %u\n", MAJOR(velo2.devnr));
  dev_dbg(DEV,"init successful\n");
  
  velo2.dev=device_create(extoll_get_class_user(), extoll_get_device(), velo2.devnr, NULL, "velo2");
  if (velo2.dev==NULL) {
     dev_alert(DEV,"device creation failed\n");
     result=-EBUSY;
     goto velo_open_err_register_chrdev;
  }

  result = sysfs_create_group(&velo2.devp->dev.kobj, *velo2_groups);
  if(0 != result) {
	  return result;
  }

  
  //velo2.devp->dev.groups = velo2_groups;

  //velo2.mmio_vaddr=extoll_get_velo2_vaddr();
  velo2.velo_mmio_addr=extoll_get_velo2_addr();
  velo2.velo_mmio_size=extoll_get_velo2_size();
  velo2.slot_size = velo2_detect_slot_size();
 
  /* Device OK!
  * Now setup character device specific ops for requester and completer
  */
  if (velo2_setup_cdev() < 0)
  {
    dev_alert(DEV,"error in velo_setup_cdev\n");
    result=-EBUSY;
    goto velo_open_err_device_create;
  }

  for (i=0;i<VELO2_MAX_VPID;i++)
    {            
      /* create port structure */
      portp = kmalloc(sizeof(velo_port_t), GFP_KERNEL);
      if (!portp) {
	dev_alert(DEV,"could not allocate memory for endpoint %d\n",i);
	result=-ENOMEM;
        goto velo_open_err_alloc;
      }
            
      /* init cport */
      memset(portp, 0, sizeof(velo_port_t));
      ports[i]=portp;

      /* init registerfile for this VPID */
      velo2_set_tx_protection_descriptor(i,0);
      value=get_extoll_rf_info_rf_node();
      value=(value>>24l) & 0xffffl;
      velo2_set_tx_id(i, value, i);
      velo2_set_rx_protection_descriptor(i,0);
      velo2_set_rx_htax_reroute_enable(i,0);
      velo2_set_rx_vpid_enable(i,0);
      //set_extoll_rf_velo_rf_wcbuf_rf_state(i,0l);
      old_wcb_state=get_extoll_rf_velo_rf_wcbuf_rf_state(i);
      new_wcb_state=old_wcb_state & 0x00ffffffff000000l;
      set_extoll_rf_velo_rf_wcbuf_rf_state(i, new_wcb_state);
      dev_dbg(DEV,"velo2: vpid %d: wcb old state was %lx, new state will be %lx\n",i,(unsigned long)old_wcb_state,(unsigned long)new_wcb_state);
    }
  velo2_rx_set_timeout(0x20l,1);
  velo2_tx_set_timeout(0x20l,1);
  velo2_rx_set_alternative_htax_port(8);
  if(velo2.slot_size == 128) {
	  dev_info(DEV, "using 128 byte buffer queue slots for velo2\n");
	  velo2_rx_enable_large_slots(1);
  } else {
	  dev_info(DEV, "using 64 byte buffer queue slots for velo2\n");
	  /*In case of debugging and using 128 and 64 byte sized slots in one run: disbale large slots when using small slots*/
	  velo2_rx_enable_large_slots(0);
  }

  //enable network port 0
  set_extoll_rf_np_top_rf_n0_general(81l);
  
  //now register the interrupt handlers for velo
  init_velo2_interrupt_handlers();
  extoll_register_interrupt_handler(SNQ_TE_VELO_RF_NOTI_INTERRUPT_HANDLER_NOTI_INTERRUPT_VEC, &velo2_msg_irq_handler);
  extoll_register_interrupt_handler(SNQ_TE_VELO_ERROR, &velo2_error_irq_handler);
  return 0;

  /* ERROR handling */
velo_open_err_alloc:
  for (j=0;j<i;j++)
  {
	portp=ports[i];
	bq_destroy_queue(portp->bq);
	kfree(portp);
	ports[i]=0;
  }
velo_open_err_device_create:
  device_destroy(extoll_get_class_user(),velo2.devnr);
velo_open_err_register_chrdev:
  unregister_chrdev_region(velo2.devnr, VELO2_MINOR_COUNT);
  printk(KERN_ALERT "velo2: Major requesternumber %x freed \n",
        MAJOR(velo2.devnr));

velo_open_err_no_major:
  printk(KERN_ALERT "velo2: no major number available.\n");
  return result;
}


static void velo2_remove(void)
{
  velo_port_t *portp;
  int i;

  if (velo2.devp==0) return;

  for (i=0;i<VELO2_MAX_VPID;i++)
    {
      portp=ports[i];
	  velo2_release_port(portp);
      kfree((void *)portp);
      ports[i]=NULL;
    }
    
  sysfs_remove_group(&velo2.devp->dev.kobj, *velo2_groups);

  //disable network port 0
  set_extoll_rf_np_top_rf_n0_general(81l);

  //deregister interrupt handlers for velo
  extoll_deregister_interrupt_handler(SNQ_TE_VELO_RF_NOTI_INTERRUPT_HANDLER_NOTI_INTERRUPT_VEC);
  extoll_deregister_interrupt_handler(SNQ_TE_VELO_ERROR);
  /* clean up any allocated resources and stuff here.
  * like call release_region();
  */
  cdev_del(&velo2.cdev);
      
  unregister_chrdev_region(velo2.devnr, VELO2_MINOR_COUNT);
  device_destroy(extoll_get_class_user(),velo2.devnr);  
  printk(KERN_INFO "velo2: remove done!!\n\n");
}



/******************************************************************************
*  Module handling							      *
******************************************************************************/
static int __init velo2_init(void)
{

  printk(KERN_INFO "velo2: module init\n");
  if (extoll_get_init_done()==0)
  {
    printk(KERN_ALERT "EXTOLL Base driver not initialized! Bailing out\n");
    return -1;
  }
 
  return velo2_probe();
  
}

static void __exit velo2_exit(void)
{
  printk(KERN_INFO "velo2: module exit\n");
  velo2_remove();
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mondrian Nuessle mondrian.nuessle@extoll.de");
MODULE_DESCRIPTION("Extollv2: VELO2 driver");
MODULE_VERSION("1.0");

module_init(velo2_init);
module_exit(velo2_exit);

EXPORT_SYMBOL(velo2_get_device);
EXPORT_SYMBOL(velo2_get_mbox_size);
EXPORT_SYMBOL(velo2_get_nodeid);
