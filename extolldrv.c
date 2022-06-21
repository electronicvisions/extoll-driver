/*
 *  This file is part of the  Linux Kernel Driver Package for EXTOLL R2.
 *
 *  Copyright (C) 2011 EXTOLL GmbH
 *
 *  Written by Mondrian Nuessle (2011)
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
#include "arch_define.h"

#include <linux/version.h>
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
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>  
#include <asm/uaccess.h>
#include <asm/smp.h>

#define EXTOLLDRV
//#define MICEXTOLL

#ifdef DEEP_HOST
#include "HW_if.h"
#endif

#include "extolldrv.h"
#include "extoll_rf_sysfs.h"

#include "snq_pram.h"

#ifdef MICEXTOLL
#include <linux/device.h>
#include "micextoll.h"
#include <linux/moduleparam.h>
#include <linux/irq.h>
#endif

void *vpci_nvl = NULL;
int vpci_nvidia_irq = 0;

//Debugging strings for readable output
static const char *vtype2string[] = {"RMA", "VELO", "SMFU PID"};

#define DEV &card.devp->dev

//EXTOLL R2 Ventoux only supported on halfway recent kernels
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,27)
#error "This driver needs at least kernel version 2.6.31. If you think this is wrong, contact the author."
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,8,0)
#define __extoll_devexit __devexit
#define __extoll_devinit __devinit
#define __extoll_devexit_p(a) __devexit_p(a)
#else
#define __extoll_devexit
#define __extoll_devinit
#define __extoll_devexit_p(a) (a)
#endif

#ifdef MICEXTOLL
static int irq;

static struct micextoll_driver micextoll_driver0;
static struct micextoll_device extoll_dev0;

static void physical_extoll_set_up_internal_address_map(void);
static void extoll_set_up_internal_address_map(void);
#endif

//#define DEBUG(a) a
#define DEBUG(a) 
/******************************************************************************
*  Boards supported by this driver      				                      *
*  At the moment this is VENTOUX, Galbier and others may follow.              *
******************************************************************************/
static struct pci_device_id ids[] = {
  {PCI_DEVICE(PCI_VENDOR_ID_EXTOLL, PCI_DEVICE_ID_VENTOUX1),}, //Ventoux
  {PCI_DEVICE(PCI_VENDOR_ID_TEST, PCI_DEVICE_ID_VENTOUX1),}, //Ventoux
  {PCI_DEVICE(PCI_VENDOR_ID_EXTOLL, PCI_DEVICE_ID_GALIBIER),}, //Galibier
  {PCI_DEVICE(PCI_VENDOR_ID_EXTOLL, PCI_DEVICE_ID_TOURMALET),}, //Tourmalet rev1
  {PCI_DEVICE(PCI_VENDOR_ID_EXTOLL, PCI_DEVICE_ID_TOURMALET_V2),}, //Tourmalet rev2
  {PCI_DEVICE(PCI_VENDOR_ID_EUROTECHEXTOLL, PCI_VENDOR_ID_AURORA),}, //Eurotech Aurora
  {PCI_DEVICE(PCI_VENDOR_ID_EXTOLL, PCI_DEVICE_ID_VENTOUXHT3),}, //Ventoux HT3
  {PCI_DEVICE(PCI_VENDOR_ID_FAKE, PCI_DEVICE_ID_VENTOUX1),}, //Ventoux with Fake (inofficial) Vendor ID

  {0,}
};

MODULE_DEVICE_TABLE(pci, ids);

/******************************************************************************
*  Registerfile access			   				      *
******************************************************************************/
void *extoll_rf;
static extoll_device_t card;
static unsigned int interrupt_counter=0;
static struct class *extoll2_class_user;
static struct class *extoll2_class_priv;

//DECLARE_MUTEX(extoll_mutex);	//mutex is initialized unlocked.
static unsigned long extoll_rf_snq_rf_irq_0_param = 0xfd2300000040002Dl;
module_param(extoll_rf_snq_rf_irq_0_param, ulong, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
static unsigned long extoll_rf_snq_rf_irq_1_param = 0x030001000000l; 
module_param(extoll_rf_snq_rf_irq_1_param, ulong, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
static unsigned long extoll_rf_snq_rf_irq_2_param = 0l;
module_param(extoll_rf_snq_rf_irq_2_param, ulong, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

//Needed for network-attached accelerator setup
static unsigned long smfu2_size_var = 0;
module_param(smfu2_size_var, ulong, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(smfu2_size_var, "smfu2_size: BAR size for SMFU2.\n");


#ifdef MICEXTOLL
static unsigned long micextoll_resource_start0  = 0xd0000000 + 0x8000000000;
//static unsigned long micextoll_resource_start0	= 0x3c1fd0000000 + 0x8000000000;
static unsigned long micextoll_resource_len0	= 256*1024*1024;
module_param(micextoll_resource_start0, ulong, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
//MODULE_PARM(micextoll_resource_start0, "l");
//module_param(micextoll_resource_len0, ulong, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

static unsigned long micextoll_resource_start2  = 0xc0000000 + 0x8000000000;
//static unsigned long micextoll_resource_start2	= 0x3c1fc0000000 + 0x8000000000;
static unsigned long micextoll_resource_len2	= 256*1024*1024;
module_param(micextoll_resource_start2, ulong, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
//MODULE_PARM(micextoll_resource_start2, "l");
//module_param(micextoll_resource_len2, ulong, IRUGO);

static unsigned long micextoll_resource_start4  = 0xb0000000 + 0x8000000000;
//static unsigned long micextoll_resource_start4	= 0x3c1fb0000000 + 0x8000000000;
static unsigned long micextoll_resource_len4	= 256*1024*1024;
module_param(micextoll_resource_start4, ulong, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
//MODULE_PARM(micextoll_resource_start4, "l");
//module_param(micextoll_resource_len4, ulong, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
//

// Base address of the BAR0 of the MIC inside physical address space as seen by EXTOLL
// this needs to be added as offset to the physical address programmed to EXTOLL registers
//unsigned long micextoll_micbase0    = 0xe0000000;
unsigned long micextoll_micbase0    = 0x3c1c00000000l;
EXPORT_SYMBOL(micextoll_micbase0);
module_param(micextoll_micbase0, ulong, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
//module_param(micextoll_micbase0, ulong, IRUGO);
//Length of the aperture of MIC, currently this is 256MB, this is also relevant for the DMA mask...
//unsigned long micextoll_miclen0    = 0x10000000;
unsigned long micextoll_miclen0    = 0x200000000l;
EXPORT_SYMBOL(micextoll_miclen0);
module_param(micextoll_miclen0, ulong, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
//module_param(micextoll_miclen0, ulong, IRUGO);

static unsigned long extoll_physical_bar0_addr = 0x0l;
EXPORT_SYMBOL(extoll_physical_bar0_addr);
module_param(extoll_physical_bar0_addr, ulong, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

static unsigned long extoll_physical_bar2_addr = 0x0l;
EXPORT_SYMBOL(extoll_physical_bar2_addr);
module_param(extoll_physical_bar2_addr, ulong, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);


/*
 *   Device struct for the micextoll virtual bus
 *   */
static struct micextoll_device micextoll_dev0 = {
  .name = "extoll",
/*  .dev = {
        .init_name = "extoll",
  },
*/
//  .release = micextoll_device_release,
//  .parent = &micextoll_bus,
};

void extoll_register_dev(struct micextoll_device *dev)
{
  int err;
//  dev.devp              = &extoll_dev0; FIXME ???
  printk(KERN_INFO "DEBUG: dev->dev.init_name = %s\n", dev->dev.init_name);
  dev->dev.init_name    = dev->name;
  printk(KERN_INFO "DEBUG: dev->dev.init_name = %s\n", dev->dev.init_name);

  dev->driver           = &micextoll_driver0;
  err = register_micextoll_device(&micextoll_dev0);
  if (err){
    printk(KERN_NOTICE "EXTOLL: Unable to register device %s\n", dev->name);
  }else{
    printk(KERN_INFO "EXTOLL: %s device register complete\n", dev->name);
    card.devp = &micextoll_dev0;
  }

}

#endif

int _extoll_vpids_per_page;
int _extoll_max_addressable_vpids;

/******************************************************************************
*  externally callable            functions                                  *
******************************************************************************/
int extoll_get_init_done(void)
{
  return card.init_done;
}
EXPORT_SYMBOL(extoll_get_init_done);

#ifdef MICEXTOLL
struct micextoll_device* extoll_get_pdev(void)
{
  return card.devp;
}
#else
struct pci_dev* extoll_get_pdev(void)
{
  return card.devp;
}
#endif
EXPORT_SYMBOL(extoll_get_pdev);

struct class* extoll_get_class_user(void)
{
  return extoll2_class_user;
}
EXPORT_SYMBOL(extoll_get_class_user);

struct class* extoll_get_class_priv(void)
{
  return extoll2_class_priv;
}
EXPORT_SYMBOL(extoll_get_class_priv);

struct device* extoll_get_device(void)
{
  return &card.devp->dev;
}
EXPORT_SYMBOL(extoll_get_device);

uint32_t extoll_get_mtu(void)
{
#ifdef MICEXTOLL
  return 512;
#else  
  uint16_t vendor=card.devp->vendor;
  uint16_t device=card.devp->device;
  if (vendor==PCI_VENDOR_ID_EUROTECHEXTOLL)
     return 512;
  if ( (vendor==PCI_VENDOR_ID_EXTOLL && device==PCI_DEVICE_ID_TOURMALET)    ||
       (vendor==PCI_VENDOR_ID_EXTOLL && device==PCI_DEVICE_ID_TOURMALET_V2) )
     return 512;
  return 256;
#endif  
}
EXPORT_SYMBOL(extoll_get_mtu);

int extoll_is_tourmalet(void)
{
#ifdef MICEXTOLL
  return 1;
#else  
  uint16_t vendor=card.devp->vendor;
  uint16_t device=card.devp->device;
  
  if ( (vendor==PCI_VENDOR_ID_EXTOLL && device==PCI_DEVICE_ID_TOURMALET)    ||
       (vendor==PCI_VENDOR_ID_EXTOLL && device==PCI_DEVICE_ID_TOURMALET_V2) )
    return 1;
  else
    return 0;
#endif
}
EXPORT_SYMBOL(extoll_is_tourmalet);

void* extoll_get_rf_vaddr(void)
{
  return card.rf_vaddr;
}
EXPORT_SYMBOL(extoll_get_rf_vaddr);

void* extoll_get_velo2_vaddr(void)
{
  return card.velo2_vaddr;
}
EXPORT_SYMBOL(extoll_get_velo2_vaddr);

void* extoll_get_rma2_vaddr(void)
{
  return card.rma2_vaddr;
}
EXPORT_SYMBOL(extoll_get_rma2_vaddr);

void* extoll_get_smfu_vaddr(void)
{
  return card.smfu2_vaddr;
}
EXPORT_SYMBOL(extoll_get_smfu_vaddr);

unsigned long extoll_get_rf_addr(void)
{	
  return card.rf_paddr;
}
EXPORT_SYMBOL(extoll_get_rf_addr);

unsigned long extoll_get_velo2_addr(void)
{	
  return card.velo2_paddr;
}
EXPORT_SYMBOL(extoll_get_velo2_addr);

unsigned long extoll_get_rma2_addr(void)
{	
  return card.rma2_paddr;
}
EXPORT_SYMBOL(extoll_get_rma2_addr);

unsigned long extoll_get_smfu_addr(void)
{	
  return card.smfu2_paddr;
}
EXPORT_SYMBOL(extoll_get_smfu_addr);

#ifdef MICEXTOLL
unsigned long extoll_get_smfu_addr_physical(void)
{
return extoll_physical_bar2_addr+EXTOLL_R2_SMFU2_MMIO_OFFSET;
}
EXPORT_SYMBOL(extoll_get_smfu_addr_physical);
#endif

unsigned long int extoll_get_rf_size(void)
{
  return card.rf_size;
}
EXPORT_SYMBOL(extoll_get_rf_size);

unsigned long int extoll_get_velo2_size(void)
{
  return card.velo2_size;
}
EXPORT_SYMBOL(extoll_get_velo2_size);

unsigned long int extoll_get_rma2_size(void)
{
  return card.rma2_size;
}
EXPORT_SYMBOL(extoll_get_rma2_size);

unsigned long int extoll_get_smfu_size(void)
{
  return card.smfu2_size;
}
EXPORT_SYMBOL(extoll_get_smfu_size);

unsigned long int extoll_get_bar0_addr(void)
{
  return card.bar0_addr;
}
EXPORT_SYMBOL(extoll_get_bar0_addr);

unsigned int extoll_get_interrupt_counter(void)
{
  return interrupt_counter;
}
EXPORT_SYMBOL(extoll_get_interrupt_counter);

void extoll_set_interrupt_counter(unsigned int v)
{
  interrupt_counter=v;
}
EXPORT_SYMBOL(extoll_set_interrupt_counter);
//#endif
#ifdef MICEXTOLL
unsigned long extoll_query_max_htoc_size(void)
{
 return 128;
}
#else
unsigned long extoll_query_max_htoc_size(void)
{   
   if (card.use_pcie==1)
     return 128;
   else
     return 64;
}
#endif
EXPORT_SYMBOL(extoll_query_max_htoc_size);

unsigned long extoll_query_max_vpids(void)
{
     return _extoll_max_addressable_vpids;
}
EXPORT_SYMBOL(extoll_query_max_vpids);

unsigned long extoll_query_vpids_per_page(void)
{
     return _extoll_vpids_per_page;
}
EXPORT_SYMBOL(extoll_query_vpids_per_page);

/******************************************************************************
*  network state functions
******************************************************************************/
/* EXTOLL NW State Handling */

//default nw state handler, registered by base driver
static void print_nw_state(uint64_t state)
{
    switch (state) {
      case EXTOLL_NW_STATE_UC: dev_info(DEV,"network not configured. Operations stopped.\n");
                            break;
      case EXTOLL_NW_STATE_C: dev_info(DEV,"network configured. Operations started.\n");
                            break;
      case EXTOLL_NW_STATE_S: dev_info(DEV,"network stopped. Operations stopped.\n");
                            break;
    default: dev_info(DEV,"network state is unknown (%lld). Operations stopped.\n",state);
  }
}

int extoll_add_nw_state_handler(extoll_nw_state_handler_t handler){
  extoll_nw_handler_list_t* item;
  unsigned long flags;
  
  item=kmalloc(sizeof(extoll_nw_handler_list_t),GFP_KERNEL);
  if (item==NULL) { //error
      dev_warn(DEV,"could not allocate item for nw_handler_list\n");
      //spin_unlock_irqrestore(&card.nw_state_lock,flags);
      return -1;
  }

  spin_lock_irqsave(&card.nw_state_lock,flags);
  item->handler=handler;  
  list_add(&item->list,&card.nw_state_handlers);
  handler(card.nw_state);
  spin_unlock_irqrestore(&card.nw_state_lock,flags);
  return 0;
}
EXPORT_SYMBOL(extoll_add_nw_state_handler);

int extoll_remove_nw_state_handler(extoll_nw_state_handler_t handler){  
  unsigned long flags;
  extoll_nw_handler_list_t* item;
  spin_lock_irqsave(&card.nw_state_lock,flags);
  //list_for_each_entry(type *cursor, struct list_head *list, member)
  list_for_each_entry(item, &card.nw_state_handlers, list) {
  //list_for_each(item,&card.nw_state_handlers) {
    if (item->handler==handler) {
        list_del(&item->list);
        kfree(item);
        spin_unlock_irqrestore(&card.nw_state_lock,flags);
        return 0;
    }
  }
  spin_unlock_irqrestore(&card.nw_state_lock,flags);
  return -1;
}
EXPORT_SYMBOL(extoll_remove_nw_state_handler);

static inline extoll_nw_task_list_t *extoll_alloc_nw_task_list_entry(void)
{
	extoll_nw_task_list_t *item = kmalloc(sizeof(extoll_nw_task_list_t),GFP_KERNEL);

	if(item == NULL) return item;

	item->task = NULL;
	item->vpid = -1;
	item->vpid_type = RMA_VPID;

	return item;
}

int extoll_add_nw_state_task(int vpid, VPID_TYPE vtype, struct task_struct* task)
{
	extoll_nw_task_list_t* item = NULL;
	unsigned long flags;

	dev_dbg(DEV, "add task %p to the nw_state_task list\n",task);

	item = extoll_alloc_nw_task_list_entry();
	if (item == NULL) {
		dev_warn(DEV,"could not allocate nw state task handler\n");
		return -1;
	}
	item->task=task;
	item->vpid = vpid;
	item->vpid_type = vtype;

	spin_lock_irqsave(&card.nw_state_lock,flags);
	list_add(&item->list,&card.nw_task_list);
	spin_unlock_irqrestore(&card.nw_state_lock,flags);

	return 0;
}
EXPORT_SYMBOL(extoll_add_nw_state_task);

int extoll_remove_nw_state_task(int vpid, VPID_TYPE vtype)
{
	extoll_nw_task_list_t* item;
	unsigned long flags;

	dev_dbg(DEV, "remove %s vpid %i to the nw_state_task list\n", vtype2string[vtype], vpid);

	spin_lock_irqsave(&card.nw_state_lock,flags);
	list_for_each_entry(item, &card.nw_task_list, list) {
		if (item->vpid == vpid && item->vpid_type == vtype) {
			list_del(&item->list);
			kfree(item);
			spin_unlock_irqrestore(&card.nw_state_lock,flags);
			return 0;
		}
	}
	spin_unlock_irqrestore(&card.nw_state_lock,flags);

	dev_alert(DEV,"Removing of %s vpid  %i failed..\n", vtype2string[vtype], vpid);

	return -1;
}
EXPORT_SYMBOL(extoll_remove_nw_state_task);

static void extoll_nw_state_info_tasks(int signo) 
{
 extoll_nw_task_list_t* item;

 list_for_each_entry(item, &card.nw_task_list, list) {
  if (item!=NULL) {
    if (item->task!=NULL) {
     force_sig(signo,item->task);
     dev_dbg(DEV,"extoll_nw_state_info_tasks: Taskitem %p in list while traversing\n",item);
    }
    else {
      dev_alert(DEV,"extoll_nw_state_info_tasks: Task of item already null!\n");
    }
   }
   else {
    dev_alert(DEV,"extoll_nw_state_info_tasks: Taskitem is zero!\n");
   }
  }
}


void extoll_nw_state_handler(void) {  
  uint64_t value;
  extoll_nw_handler_list_t* item;
  unsigned long flags;
  int signo;
  
  dev_dbg(DEV,"nw_state handler called\n");
  value=get_extoll_rf_info_rf_scratchpad_scratchpad(EXTOLL_SCRATCH_NETWORK_STATE);

  if (value==1) //running
    signo=SIGCONT;
  else
   signo=SIGSTOP;

  if (card.nw_state!=value) //state changed
  {
    card.nw_state=value;  
    //call handlers...        
    spin_lock_irqsave(&card.nw_state_lock,flags);
    list_for_each_entry(item, &card.nw_state_handlers, list) {
       if (item!=NULL) {
        if (item->handler!=NULL) {
         item->handler(value);   
        }
        else {
          dev_alert(DEV,"extoll_nw_state_handler: item handler is zero!\n");
        }
      } else {
        dev_alert(DEV,"extoll_nw_state_handler: item is zero\n");
      }   
    }
    //stop taska if necessary
    extoll_nw_state_info_tasks(signo);
    
    spin_unlock_irqrestore(&card.nw_state_lock,flags);
  }
}

uint64_t extoll_get_nw_state(void) {
  uint64_t value;
  unsigned long flags;
  
  spin_lock_irqsave(&card.nw_state_lock,flags);
  value=card.nw_state;
  spin_unlock_irqrestore(&card.nw_state_lock,flags);
  return value;
}
EXPORT_SYMBOL(extoll_get_nw_state);
unsigned long outp_handler_called=0;

/******************************************************************************
*  interrupt handler
******************************************************************************/
int extoll_xbar_fcc_cred_sum(uint64_t fcc_credits) {
 int value=0;
 int i;
 for (i=0;i<10;i++) {
   value+= (fcc_credits & 0x3fl);
   fcc_credits=fcc_credits<<6l;
 }
 return value;
}

void xbar_outp10_f(unsigned long d)
{
  unsigned char total_credits;
  uint64_t fcc_credits;
  unsigned long cleared_packets=0;
  unsigned long loop=0;
  unsigned int timeout=10000; //usec
  unsigned long int timeout_jiffies=usecs_to_jiffies(timeout);
  unsigned long stop;
  int check_count=0;

  outp_handler_called++;
  
  stop=jiffies+timeout_jiffies;
  dev_dbg(DEV,"XBAR Outport Interrupt\n");
  //snq_dump_entry(entry);
#ifdef DEEP_HOST
 set_extoll_rf_snq_rf_trigger_enable(0x1FED97FDL);
#else
#ifdef MICEXTOLL  
 set_extoll_rf_snq_rf_trigger_enable(0x1FED97FDL);
#else
  //which trigger to be set regularly? 
  if (extoll_is_tourmalet()==1)
    //set_extoll_rf_snq_rf_trigger_enable(0xFDFFFFFFl);
    //removed link/mac interrupts to prevent interrupt storm for now
    set_extoll_rf_snq_rf_trigger_enable(0x1FED9FFDL);
  else
    set_extoll_rf_snq_rf_trigger_enable(0x0l);
#endif
#endif

  total_credits=get_extoll_rf_nw_xbar_rf_outp10_general() & 0xff;
  fcc_credits=get_extoll_rf_nw_xbar_rf_outp10_fcc_credits();
  if (total_credits > 0 || fcc_credits!=0 ) {
    while (total_credits > 0 || fcc_credits!=0 || check_count <255 ) 
    {
      cleared_packets+=extoll_xbar_fcc_cred_sum(fcc_credits);
      loop++;
      dev_dbg(DEV,"Resetting Credits for port 10\n");
    
      set_extoll_rf_nw_xbar_rf_outp10_credits_0(0x0);
      set_extoll_rf_nw_xbar_rf_outp10_credits_0(0x40);
      set_extoll_rf_nw_xbar_rf_outp10_credits_0(0x80);
      set_extoll_rf_nw_xbar_rf_outp10_credits_0(0xc0);
      set_extoll_rf_nw_xbar_rf_outp10_credits_0(0x100);
      set_extoll_rf_nw_xbar_rf_outp10_credits_0(0x140);
      set_extoll_rf_nw_xbar_rf_outp10_credits_0(0x180);
      set_extoll_rf_nw_xbar_rf_outp10_credits_0(0x1c0);
      set_extoll_rf_nw_xbar_rf_outp10_credits_0(0x200);
      set_extoll_rf_nw_xbar_rf_outp10_credits_0(0x240);    
      set_extoll_rf_nw_xbar_rf_outp10_credits_1(0x2830008000);
      total_credits=get_extoll_rf_nw_xbar_rf_outp10_general() & 0xff;
      fcc_credits=get_extoll_rf_nw_xbar_rf_outp10_fcc_credits();
      if (time_after(jiffies,stop)) {
       if (cleared_packets>1000)
        dev_alert(DEV,"Illegal Routing detected. Cleared approx. %ldk messages",cleared_packets/1000);
       else
        dev_alert(DEV,"Illegal Routing detected. Cleared approx. %ld messages",cleared_packets);
       dev_dbg(DEV,"Cleared %ld packets from port 10 in %ld iterations. Timeout occured, more to be cleared possible,rescheduling task Check_Count=%d\n",cleared_packets,loop,check_count);
       tasklet_schedule(&card.xbar_outp10_tasklet);
       return;
      }
      if (total_credits==0 && fcc_credits==0) {
        check_count++;
      }
      else
      {
        check_count=0;
      }
    }
    if (cleared_packets>1000)
      dev_alert(DEV,"Illegal Routing detected. Cleared approx. %ldk messages",cleared_packets/1000);
    else
      dev_alert(DEV,"Illegal Routing detected. Cleared approx. %ld messages",cleared_packets);

    dev_dbg(DEV,"Cleared %ld packets from port 10 in %ld iterations, check_count=%d. Handler called %ld times\\n",cleared_packets,loop,check_count,outp_handler_called);
  }
#ifdef DEEP_HOST
 set_extoll_rf_snq_rf_trigger_enable(0x1FEDD7FDL);
#else
#ifdef MICEXTOLL  
 set_extoll_rf_snq_rf_trigger_enable(0x1FEDD7FDL);
#else
  //which trigger to be set regularly? 
  if (extoll_is_tourmalet()==1)
    //set_extoll_rf_snq_rf_trigger_enable(0xFDFFFFFFl);
    //removed link/mac interrupts to prevent interrupt storm for now
    set_extoll_rf_snq_rf_trigger_enable(0x1FEDDFFDL);
  else
    set_extoll_rf_snq_rf_trigger_enable(0x0l);
#endif
#endif
}

void extoll_check_xbar_outp(snq_entry_t* entry,int te, int entry_idx)
{
#ifdef DEEP_HOST
 set_extoll_rf_snq_rf_trigger_enable(0x1FED97FDL);
#else
#ifdef MICEXTOLL  
 set_extoll_rf_snq_rf_trigger_enable(0x1FED97FDL);
#else
  //which trigger to be set regularly? 
  if (extoll_is_tourmalet()==1)
    //set_extoll_rf_snq_rf_trigger_enable(0xFDFFFFFFl);
    //removed link/mac interrupts to prevent interrupt storm for now
    set_extoll_rf_snq_rf_trigger_enable(0x1FED9FFDL);
  else
    set_extoll_rf_snq_rf_trigger_enable(0x0l);
#endif
#endif
 tasklet_schedule(&card.xbar_outp10_tasklet);
}

void extoll_pcie_status_irq_handler(snq_entry_t* entry,int te, int entry_idx)
{
  uint64_t value;
  dev_info(DEV," PCIe status changed Interrupt received\n");
  dev_info(DEV,"PCIe status changed Header: raw: %lx ts: %lx tc: %x pc: %x flip: %x\n", (unsigned long) entry->header.value, (unsigned long) entry->header.fields.ts, (unsigned) entry->header.fields.tc,entry->header.fields.pc, entry->header.fields.flip);
  value=(unsigned long) entry->payload[6];
  dev_info(DEV,"PCIe status changed: reg value: %lx, phy_layer_up: %x dl_layer_up: %x ltssm_state: %x phy_loss_of_sync: %x phy_loss_of_sync_any: %x current_link_speed: %x link_width: %x\n",
          (unsigned long) value, (unsigned int) (value & 0x1l) , (unsigned int) ((value >> 0x1l) & 0x1l), (unsigned int) ((value >> 0x2l) & 0x1fl), (unsigned int) ((value >> 0x7l) & 0xffffl), 
          (unsigned int) ((value >> 23l) & 0x1l), (unsigned int) ((value >> 24l) & 0x3l), (unsigned int) ((value >> 26l) & 0x3fl));
  value=get_extoll_rf_pcie_rf_nwl_pcie_status_rf_err_cnt_phy();
  dev_info(DEV,"PCIe PHY err cnt: %lx\n",(unsigned long) value);

}

void extoll_bq_error_handler(snq_entry_t* entry,int te, int entry_idx)
{
  uint64_t value;
  dev_info(DEV,"BQ error interrupt received\n");
  dev_info(DEV,"BQ error Header: raw: %lx ts: %lx tc: %x pc: %x flip: %x\n", (unsigned long) entry->header.value, (unsigned long) entry->header.fields.ts, (unsigned) entry->header.fields.tc,entry->header.fields.pc, entry->header.fields.flip);
  value=(unsigned long) entry->payload[6];

  dev_info(DEV,"VELO BQ Status: reg value: %lx enabled: %x ub_assert: %x timeout_assert: %x lpw_assert: %x error_queue: %x error_count %x\n",
               (unsigned long) value, (unsigned int) (value & 0x1l) , (unsigned int) ((value >> 1l )& 0x1l) ,(unsigned int) ((value >> 2l )& 0x1l) ,(unsigned int) ((value >> 3l )& 0x1l) , 
               (unsigned int) ((value >> 4l )& 0xffl) , (unsigned int) ((value >> 12l )& 0xffffffff1l) );
  value=(unsigned long) entry->payload[5];
  dev_info(DEV,"RMA BQ Status: reg value: %lx enabled: %x ub_assert: %x timeout_assert: %x lpw_assert: %x error_queue: %x error_count %x\n",
               (unsigned long) value, (unsigned int) (value & 0x1l) , (unsigned int) ((value >> 1l )& 0x1l) ,(unsigned int) ((value >> 2l )& 0x1l) ,(unsigned int) ((value >> 3l )& 0x1l) , 
               (unsigned int) ((value >> 4l )& 0xffl) , (unsigned int) ((value >> 12l )& 0xffffffff1l) );
}

void extoll_ecc_correctable_status_irq_handler(snq_entry_t* entry,int te, int entry_idx)
{
  uint64_t value;
  dev_warn(DEV,"Correctable ECC error detected.\n");
  dev_warn(DEV,"Header: raw: %lx ts: %lx tc: %x pc: %x flip: %x\n", (unsigned long) entry->header.value, (unsigned long) entry->header.fields.ts, (unsigned) entry->header.fields.tc,entry->header.fields.pc, entry->header.fields.flip);
  value=(unsigned long) entry->payload[6];
}

void extoll_ecc_uncorrectable_status_irq_handler(snq_entry_t* entry,int te, int entry_idx)
{
  uint64_t value;
  dev_warn(DEV,"extolldrv: Uncorrectable ECC error detected.\n");
  dev_warn(DEV,"extolldrv: Header: raw: %lx ts: %lx tc: %x pc: %x flip: %x\n", (unsigned long) entry->header.value, (unsigned long) entry->header.fields.ts, (unsigned) entry->header.fields.tc,entry->header.fields.pc, entry->header.fields.flip);
  value=(unsigned long) entry->payload[6];
}

void extoll_nw_state_irq_handler(snq_entry_t* entry,int te, int entry_idx) {
  extoll_nw_state_handler();
}

void extoll_global_irq_handler(snq_entry_t* entry,int te, int entry_idx) {
  uint64_t value;
  int i;
  dev_info(DEV,"global interrupt\n");
  //snq_dump_entry(entry);
  for (i=3;i<7;i++) {
    value=entry->payload[i];
    if (value!=0) {
      dev_info(DEV,"global interrupt %d detected\n",i-3);
      //set_extoll_rf_nw_barrier_rf_interrupts_work_set(i-3,0);
      if (i==3) extoll_nw_state_handler();
    }
  }
}

/******************************************************************************
*  helper functions                                  *
******************************************************************************/



#ifdef MICEXTOLL

static unsigned char extoll_get_revision(struct micextoll_device *dev)
{
 return 0x40;
}

//set internal variables for the memory mapping
static void physical_extoll_set_up_internal_address_map(void)
{
  card.rf_paddr=extoll_physical_bar0_addr+EXTOLL_R2_RF_MMIO_OFFSET;
  card.rf_size=EXTOLL_R2_RF_MMIO_SIZE;
	
  dev_dbg(DEV, "extoll_physical_bar0_addr = %lx", extoll_physical_bar0_addr);
  
  card.velo2_paddr=extoll_physical_bar0_addr+EXTOLL_R2_VELO2_MMIO_OFFSET;
  card.velo2_size=EXTOLL_R2_VELO2_MMIO_SIZE;
  
  card.rma2_paddr=extoll_physical_bar0_addr+EXTOLL_R2_RMA2_MMIO_OFFSET;
  card.rma2_size=EXTOLL_R2_RMA2_MMIO_SIZE;
  
  card.smfu2_paddr=extoll_physical_bar2_addr+EXTOLL_R2_SMFU2_MMIO_OFFSET;
  card.smfu2_size=EXTOLL_R2_SMFU2_MMIO_SIZE;
}
EXPORT_SYMBOL(physical_extoll_set_up_internal_address_map);
int extoll_pcie_get_mps(struct pci_dev *dev)
{
	return 256;
    //TODO: different size???
}
EXPORT_SYMBOL(extoll_pcie_get_mps);
int extoll_pcie_get_readrq(struct pci_dev *dev)
{
	  return 512;
}
EXPORT_SYMBOL(extoll_pcie_get_readrq);
#else

static unsigned char extoll_get_revision(struct pci_dev *dev)
{
  u8 revision;

  pci_read_config_byte(dev, PCI_REVISION_ID, &revision);
  return revision;
}


int extoll_pcie_get_mps(struct pci_dev *dev)
{
	 return EKVCL_pcie_get_mps(dev);
}
EXPORT_SYMBOL(extoll_pcie_get_mps);
int extoll_pcie_get_readrq(struct pci_dev *dev)
{
	return pcie_get_readrq(dev);
}
EXPORT_SYMBOL(extoll_pcie_get_readrq);
#endif
//set internal variables for the memory mapping
static void extoll_set_up_internal_address_map(void)
{
  card.rf_paddr=card.bar0_addr+EXTOLL_R2_RF_MMIO_OFFSET;
  card.rf_size=EXTOLL_R2_RF_MMIO_SIZE;

  dev_dbg(DEV, "card.bar0_addr = %lx", card.bar0_addr);
 
  card.velo2_paddr=card.bar0_addr+EXTOLL_R2_VELO2_MMIO_OFFSET;
  card.velo2_size=EXTOLL_R2_VELO2_MMIO_SIZE;
  
  card.rma2_paddr=card.bar0_addr+EXTOLL_R2_RMA2_MMIO_OFFSET;
  card.rma2_size=EXTOLL_R2_RMA2_MMIO_SIZE;
  
#ifdef DEEP_HOST  
  card.smfu2_paddr=card.bar4_addr+EXTOLL_R2_SMFU2_MMIO_OFFSET;
#else
  card.smfu2_paddr=card.bar2_addr+EXTOLL_R2_SMFU2_MMIO_OFFSET;
#endif
  if(smfu2_size_var == 0)
    card.smfu2_size=EXTOLL_R2_SMFU2_MMIO_SIZE;
  else
    card.smfu2_size=smfu2_size_var;
}
#ifdef MICEXTOLL
EXPORT_SYMBOL(extoll_set_up_internal_address_map);
#endif

// Perform the actual ioremapping, so memory ressource become accessible from CPU
static int extoll_set_up_ioremap(extoll_device_t* dev)
{
  /* RF in BAR0 can be modified by user hardware and thus is not cacheable */
  dev->rf_vaddr = ioremap_nocache(dev->rf_paddr,dev->rf_size);
  if (!dev->rf_vaddr) {
    dev_alert(DEV, "ioremap_nocache for RF in Bar0/1 failed \n");
    goto err_rf_map;
  }
  dev_dbg(DEV, "RF in BAR0/1 vaddr=%p\n", dev->velo2_vaddr);
  
  /* VELO2 in Bar0/1 should be wc */
  dev->velo2_vaddr = ioremap_wc(dev->velo2_paddr,dev->velo2_size);
  if (!dev->velo2_vaddr) {
    dev_alert(DEV, "ioremap_wc for VELO2 in Bar0/1 failed \n");
    goto err_velo2_map;
  }
  dev_dbg(DEV, "VELO2 in BAR0/1 vaddr=%p\n", dev->velo2_vaddr);

  /* RMA2 in Bar0/1 should be wc */
#ifdef MICEXTOLL 
  dev->rma2_vaddr = ioremap_nocache(dev->rma2_paddr,dev->rma2_size);
#else
  dev->rma2_vaddr = ioremap_wc(dev->rma2_paddr,dev->rma2_size);
#endif
  if (!dev->rma2_vaddr) {
    dev_alert(DEV,"ioremap_wc for RMA2 in Bar0/1 failed \n");
    goto err_rma2_map;
  }
  dev_dbg(DEV, "RMA2 in BAR0/1 vaddr=%p\n", dev->rma2_vaddr);
  
   /* SMFU in Bar2/3 should be notcacheable for the moment */
  //dev->smfu2_vaddr = ioremap_nocache(dev->smfu2_paddr,dev->smfu2_size);
  //dev->smfu2_vaddr = ioremap_wc(dev->smfu2_paddr,dev->smfu2_size);
  //if (!dev->smfu2_vaddr) {
  //  printk(KERN_ALERT "EXTOLL: ioremap_nocache for SMFU2 in Bar0/1 failed \n");
  //  goto err_smfu2_map;
  //}
  //printk(KERN_INFO "EXTOLL: SMFU2 in BAR0/1 vaddr=%p\n",dev->smfu2_vaddr );

  /* bar 4/5 not used for now */
  return 0;
 /* ERROR handling */
 //err_smfu2_map:
 //  release_mem_region(dev->rma2_paddr,dev->rma2_size);

err_rma2_map:
  release_mem_region(dev->velo2_paddr,dev->velo2_size);

err_velo2_map:
  release_mem_region(dev->rf_paddr,dev->rf_size);

err_rf_map:
  return -1;
}

// do the HTAX interval mapping
static void extoll_set_up_address_intervals(void)
{
  #ifdef MICEXTOLL
  //before we can configure the HTAX interval mapping, we have to set the real physical addresses
  dev_dbg(DEV, "velo2_paddr= %lx", card.velo2_paddr);
  physical_extoll_set_up_internal_address_map();
  dev_dbg(DEV, "velo2_paddr= %lx", card.velo2_paddr);
 #endif

  //set up rf routing
  set_extoll_rf_htax_bridge_rf_intvl_upper( 0, ((card.rf_paddr+card.rf_size) >> 12l) );
  set_extoll_rf_htax_bridge_rf_intvl_lower( 0,((card.rf_paddr) >>12l) -1l);
  set_extoll_rf_htax_bridge_rf_intvl_control(0, HTAX_INVTL_POSTED_VC | HTAX_INVTL_NONPOSTED_VC| HTAX_INVTL_RF_PORT_OH | HTAX_INVTL_RF_PORT | HTAX_INVTL_ENABLE);
  
  //set up velo routing
  set_extoll_rf_htax_bridge_rf_intvl_upper( 1,((card.velo2_paddr+card.velo2_size) >> 12l) );
  set_extoll_rf_htax_bridge_rf_intvl_lower( 1,((card.velo2_paddr) >> 12l) -1l);
  set_extoll_rf_htax_bridge_rf_intvl_control(1, HTAX_INVTL_POSTED_VC | HTAX_INVTL_VELO_PORT_OH | HTAX_INVTL_VELO_PORT | HTAX_INVTL_ENABLE);
  
  //set up rma routing
  set_extoll_rf_htax_bridge_rf_intvl_upper( 2,((card.rma2_paddr+card.rma2_size) >> 12l) );
  set_extoll_rf_htax_bridge_rf_intvl_lower( 2, ((card.rma2_paddr) >> 12l) -1l);
  set_extoll_rf_htax_bridge_rf_intvl_control(2, HTAX_INVTL_POSTED_VC | HTAX_INVTL_RMAREQ_PORT_OH | HTAX_INVTL_RMAREQ_PORT | HTAX_INVTL_ENABLE);

#ifndef DEEP_KNC
 
  //set up smfu routing for rra channel
  set_extoll_rf_htax_bridge_rf_intvl_upper( 5,(card.smfu2_paddr+card.rf_size) >> 12l);
  set_extoll_rf_htax_bridge_rf_intvl_lower( 5, ((card.smfu2_paddr) >> 12l) -1l);
  set_extoll_rf_htax_bridge_rf_intvl_control(5, HTAX_INVTL_POSTED_VC | HTAX_INVTL_NONPOSTED_VC| HTAX_INVTL_SMFU_PORT_OH| HTAX_INVTL_RF_PORT | HTAX_INVTL_ENABLE);
 
 
  //set up smfu routing for posted channel
  set_extoll_rf_htax_bridge_rf_intvl_upper( 3,(card.smfu2_paddr+card.smfu2_size) >> 12l);
  set_extoll_rf_htax_bridge_rf_intvl_lower( 3, ((card.smfu2_paddr+card.rf_size) >> 12l) -1l);
  set_extoll_rf_htax_bridge_rf_intvl_control(3, HTAX_INVTL_POSTED_VC /*| HTAX_INVTL_NONPOSTED_VC*/| HTAX_INVTL_SMFU_PORT_OH| HTAX_INVTL_POSTED_HOST_PORT | HTAX_INVTL_ENABLE);
  
  //set up smfu routing for non-posted channel
  set_extoll_rf_htax_bridge_rf_intvl_upper( 4,(card.smfu2_paddr+card.smfu2_size) >> 12l);
  set_extoll_rf_htax_bridge_rf_intvl_lower( 4, ((card.smfu2_paddr+card.rf_size) >> 12l) -1l);
  set_extoll_rf_htax_bridge_rf_intvl_control(4, /*HTAX_INVTL_POSTED_VC |*/ HTAX_INVTL_NONPOSTED_VC| HTAX_INVTL_SMFU_PORT_OH| HTAX_INVTL_NONPOSTED_HOST_PORT | HTAX_INVTL_ENABLE);



 
#endif

  //enable the routing table just set-up
  set_extoll_rf_htax_bridge_rf_general(  HTAX_GENERAL_ENABLE | HTAX_USE_VC_MODE | ((8l<<4l)) | (8)  );

  #ifdef MICEXTOLL
  //after the configure, we have to use again the addresses from the view of MIC
  dev_dbg(DEV, "velo2_paddr= %lx", card.velo2_paddr);
  extoll_set_up_internal_address_map(); 
  dev_dbg(DEV, "velo2_paddr= %lx", card.velo2_paddr);
 #endif 
}

static int snq_setup(extoll_device_t* d);
static int snq_start(extoll_device_t* d);
static int snq_finalize(extoll_device_t* d);
static snq_entry_t* snq_get_next_entry(extoll_device_t* d);
static void snq_entry_done(extoll_device_t* d, snq_entry_t* entry);
static void snq_update_rp(extoll_device_t* d);


static int snq_setup(extoll_device_t* d)
{
  int i;
//  int my_cpu_id = -1;
  
   //disable snq if it was previously enabled
   set_extoll_rf_snq_rf_execute(0x0l);
  
  d->snq_config.snq_size=256l; // snq has 256 entries, corresponds to 16k of memory
  d->snq_config.snq_mask=d->snq_config.snq_size-1;
  dev_info(DEV,"setting SNQ size to %ld entries (%lx bytes)\n",d->snq_config.snq_size,d->snq_config.snq_size*64);
  //dma_alloc queue
  d->snq_config.snq= dma_alloc_coherent( &d->devp->dev, d->snq_config.snq_size * 64,(dma_addr_t *) (&d->snq_config.snq_pa), GFP_KERNEL | __GFP_DMA);
  if (d->snq_config.snq == NULL) {
        dev_alert(DEV,"memory allocation for SNQ with size %lx failed\n",d->snq_config.snq_size);
        return -ENOMEM;
  }
  memset((void*)d->snq_config.snq, 0,d->snq_config.snq_size * 64);      
  dev_dbg(DEV,"Memory allocated (pa=%lx va=%lx)\n",d->snq_config.snq_pa,(unsigned long) d->snq_config.snq);
  //record mask
  dev_info(DEV,"setting snq mask to %lx...\n",d->snq_config.snq_mask);
  //#ifdef MICEXTOLL
  //We have to add the offset, because MIC/KNC and Extoll are in a host system, and extoll only see the Host physical (PCI-E) addresses
  //TODO:We have to check, if we use snq_pa at another point as MIC/KNC-physical address. If yes, we should just manipulate extoll_rf_snq_rf_queue_balt
 // d->snq_config.snq_pa += micextoll_micbase0;
 //#endif
  set_extoll_rf_snq_rf_queue_mslt(d->snq_config.snq_mask);
  //set base address
  dev_dbg(DEV,"setting snq base address of %lx (shift left by 10 %lx) ...\n",d->snq_config.snq_pa,(d->snq_config.snq_pa>>10l));
  dev_dbg(DEV,"CPU ID: %i\n",smp_processor_id());
  #ifdef MICEXTOLL
  set_extoll_rf_snq_rf_queue_balt(((d->snq_config.snq_pa + micextoll_micbase0)>>10l));
  #else
  set_extoll_rf_snq_rf_queue_balt((d->snq_config.snq_pa>>10l));
  #endif
 //init rp and wp
  d->snq_config.wp=get_extoll_rf_snq_rf_queue_wplt();
  d->snq_config.wb_rp=(d->snq_config.wp-1)  & d->snq_config.snq_mask;
  dev_dbg(DEV,"snq wp is %x, setting snq rp to %x...\n",d->snq_config.wp,d->snq_config.wb_rp);
  snq_update_rp(d);
 
  //set watermark
  d->snq_config.watermark=d->snq_config.wp+1;
  d->snq_config.fb = 1;

  dev_dbg(DEV,"setting snq watermark to %lx...\n",d->snq_config.watermark);
  set_extoll_rf_snq_rf_irq_watermark(0x10000 | (d->snq_config.watermark & 0xffff));

  //write program memory of snq...
  for (i=0; i < 256; i++)
  {
    set_extoll_rf_snq_rf_program_ram(i, SNQ_program_table[i]);
  }
  
  //enable triggers for snq:
//   set_extoll_rf_snq_rf_trigger_enable(0x7ffffl);
   //enable triggers for snq:
#ifdef DEEP_HOST
  set_extoll_rf_snq_rf_trigger_enable(0x1FEDD7FDL);
#else
#ifdef MICEXTOLL  
    set_extoll_rf_snq_rf_trigger_enable(0x1FEDD7FDL);
#else
  //which trigger to be set regularly? 
  if (extoll_is_tourmalet()==1)
    //set_extoll_rf_snq_rf_trigger_enable(0xFDFFFFFFl);
    //removed link/mac interrupts to prevent interrupt storm for now
    set_extoll_rf_snq_rf_trigger_enable(0x1FEDDFFDL);

  else
    set_extoll_rf_snq_rf_trigger_enable(0x0l);
#endif  
#endif

  return 0;
}

static int snq_start(extoll_device_t* d)
{
  #ifndef MICEXTOLL
  uint32_t irq_config_value_0;
  uint32_t irq_config_value_1;
  #endif
  unsigned long value;

  if (card.use_msi) //configure SNQ IRQ regs for PCIe Use
  {
    //write irq config register
//    value=0xfd2300000040002Dl;
    dev_dbg(DEV,"setting snq_irq_0 reg to %lx\n",extoll_rf_snq_rf_irq_0_param);
    set_extoll_rf_snq_rf_irq_0(extoll_rf_snq_rf_irq_0_param);
//    value=0x030001000000l;
    dev_dbg(DEV,"setting snq_irq_1 reg to %lx\n",extoll_rf_snq_rf_irq_1_param);
    set_extoll_rf_snq_rf_irq_1(extoll_rf_snq_rf_irq_1_param);
//    value=0l;//irq_config_value_1 & 0xffffffl;
    dev_dbg(DEV,"setting snq_irq_2 reg to %lx\n",extoll_rf_snq_rf_irq_2_param);
    set_extoll_rf_snq_rf_irq_2(extoll_rf_snq_rf_irq_2_param);
  }
  else  //configure SNQ IRQ regs for HT use
  {
    #ifndef MICEXTOLL
    //read irq config
    //set IDCB index to 10h
    pci_write_config_dword(d->devp, 0x80, 0x80100008);
    //read first irq config value
    pci_read_config_dword(d->devp, 0x84, &irq_config_value_0);
    dev_dbg(DEV,"irq0 value is %x\n",irq_config_value_0);
    //set IDCB index to 11h
    pci_write_config_dword(d->devp, 0x80, 0x80110008);
    //read second irq config value
    pci_read_config_dword(d->devp, 0x84, &irq_config_value_1);
    dev_dbg(DEV,"irq1 value is %x\n",irq_config_value_1);

    //write irq config register
    value=0xfd00000000000029l | (((unsigned long)(irq_config_value_0 & 0xfffffffC))<<24l);
    dev_dbg(DEV,"setting snq_irq_0 reg to %lx\n",value);
    set_extoll_rf_snq_rf_irq_0(value);
    value=0x030001000000l;
    dev_dbg(DEV,"setting snq_irq_1 reg to %lx\n",value);
    set_extoll_rf_snq_rf_irq_1(value);
    value=irq_config_value_1 & 0xffffffl;
    dev_dbg(DEV,"setting snq_irq_2 reg to %lx\n",value);
    set_extoll_rf_snq_rf_irq_2(value);
    #endif
  }
  //configure to send interrupts and snq dump packet to htax port 1 and on vc 1 (posted)
  value=0x0201201;
  set_extoll_rf_snq_rf_htax(value);

  //enable snq 
  dev_info(DEV,"activating snq...\n");
  set_extoll_rf_snq_rf_execute(0x1l);
  return 0;
}

static int snq_finalize(extoll_device_t* d)
{
  //deactive snq 
  set_extoll_rf_snq_rf_execute(0x0l);
  //free the queue
  #ifdef MICEXTOLL
  //We have to substract the baroffset, to get again the real physical address for the uOS on MIC/KNC
//  d->snq_config.snq_pa -= micextoll_micbase0;
  #endif
  dma_free_coherent(&d->devp->dev,d->snq_config.snq_size * 64,(void*)d->snq_config.snq,(dma_addr_t) d->snq_config.snq_pa);
  return 0;
}

void snq_dump_entry(snq_entry_t * entry)
{
  int i;
  dev_info(DEV,"SNQ Entry:\n");
  dev_info(DEV,"Header: raw: %lx ts: %lx tc: %x pc: %x flip: %x\n", (unsigned long) entry->header.value, (unsigned long) entry->header.fields.ts, (unsigned) entry->header.fields.tc,entry->header.fields.pc, entry->header.fields.flip);
  for (i=6;i>=0;i--)
  {
    dev_info(DEV,"Payload %d: %lx\n",i,(unsigned long) entry->payload[i]);
  }
}
EXPORT_SYMBOL(snq_dump_entry);

static snq_entry_t* snq_get_next_entry(extoll_device_t* d)
{
  volatile snq_entry_t* entry;
  unsigned long rp=(d->snq_config.wb_rp+1) % d->snq_config.snq_size;
  entry=&(d->snq_config.snq[rp]);
   if(entry->header.fields.flip==d->snq_config.fb)
// 	  return (snq_entry_t*)entry;
//    if (entry->header.value!=0l) //FIXME: what is the right way here?
     return (snq_entry_t*)entry;
  else 
    return 0l;
}

static void snq_entry_done(extoll_device_t* d, snq_entry_t* entry)
{
//  int i = 0;
  unsigned long rp=(d->snq_config.wb_rp+1) % d->snq_config.snq_size;
//    ((volatile snq_entry_t*)entry)->header.value=0l; //reset header value to 0.
//    for(i=0; i<7; i++){
//  	((volatile snq_entry_t*)entry)->payload[i]=0l;
//    }
  dev_dbg(DEV,"SNQ entry done, set internal rp to %lx\n",rp);
  
  d->snq_config.wb_rp=rp;
   if((rp+1) % d->snq_config.snq_size == 0){
	   if(d->snq_config.fb == 1)
		  d->snq_config.fb = 0;
	   else
		  d->snq_config.fb = 1;
   }
  d->snq_config.watermark=(d->snq_config.watermark + 1 )   & d->snq_config.snq_mask;
}

static void snq_update_rp(extoll_device_t* d)
{
  dev_dbg(DEV,"SNQ writeback of rp (%x)\n",d->snq_config.wb_rp);
  set_extoll_rf_snq_rf_queue_rplt(d->snq_config.wb_rp);
}

static void snq_arm(extoll_device_t* d)
{
  dev_dbg(DEV,"setting snq watermark to %lx...\n",d->snq_config.watermark);
  set_extoll_rf_snq_rf_irq_watermark(0x10000 | (d->snq_config.watermark & 0xffff));
  dev_dbg(DEV,"set snq watermark to %lx...\n",d->snq_config.watermark);
}

/*********************************************************************************
 * Sysfs Entries
 ********************************************************************************/

static ssize_t extoll_tasks_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	extoll_nw_task_list_t *task = NULL;
//	extoll_nw_handler_list_t *handler = NULL;
	ssize_t count = 0;

	static char *h1 = "Registered tasks that will be notified:\nPID\tVPID\tVPID type\n";
	//static char *h2 = "AddressRegistered Network State Change Handlers:\n\t";

	count += sprintf(buf, "%s", h1);
	buf += count;
	list_for_each_entry(task, &card.nw_task_list, list) {
		count += sprintf(buf, "%i\t%i\t%s\n", task->task->pid, task->vpid
				, vtype2string[task->vpid_type]);
		buf += count;
	}
/*
	count += sprintf(buf, "%s", h2);
	buf += count;

	list_for_each_entry(handler, &card.nw_state_handlers, list) {
		count += sprintf(buf, "Address: %p\n\t", handler->handler);
		buf += count;
	}
*/
	return count;
}

static DEVICE_ATTR_RO(extoll_tasks);

static struct attribute *extoll_attrs[] = {
	&dev_attr_extoll_tasks.attr,
	NULL
};

ATTRIBUTE_GROUPS(extoll);

/**
* initialize extoll device in order to work seamless in kernel pci subsystem.
* 1. enable the device
* 2. do some checks (revision etc.)
* 3. set bit mask(32/64) for dma access
* 4. retrieve and save base address register values from device
*/
static int __extoll_devinit extoll_probe(struct pci_dev *devp, const struct pci_device_id *id)
{
  int err=-1;
  int num_irqs;
  int i;
  int irq;
  unsigned long flags;
#ifdef MICEXTOLL
  int irq_vector=-1;
  struct irq_desc* desc;
  struct irq_cfg* IrqCfg;
#endif
  card.init_done=0;
  card.devp = devp;

  dev_dbg(DEV,"PCI: probe() called!\n");

  /*
  * Like calling request_region();
  */
#ifdef MICEXTOLL
  err = micextoll_enable_device(devp);
#else
  err = pci_enable_device(devp);
#endif
  if (err)
    return err;
  
  err = sysfs_create_group(&card.devp->dev.kobj, *extoll_groups);
  if(err)
    return err;
#if 0  
/* is this an HT device? */
  err=pci_find_ht_capability(devp,HT_CAPTYPE_SLAVE );
  if (err==0) {
    dev_info(DEV,"device is a PCIe attached EXTOLL device\n");
    card.use_pcie=1;
  } else {
    dev_info(DEV,"device is an HT attached EXTOLL device\n");
    card.use_pcie=0;
  }
#endif
  //only pcie supported anymore
  card.use_pcie=1;

  dev_info(DEV,"device tied to numa node %d\n",dev_to_node(&devp->dev));

  //FIXME:What revisions should be supported here ?
  //at the moment EXTOLL returns 0x40 which is OK ?
  if (extoll_get_revision(devp) == 0x42) {
    dev_alert(DEV,"device enable failed\n");
    dev_alert(DEV,"wrong revision %x\n",
          extoll_get_revision(devp));
    return -ENODEV;
  }
  dev_dbg(DEV,"detected revision %x\n",
        extoll_get_revision(devp));
// 

#ifdef MICEXTOLL
  #ifndef KNFMICEXTOLL
  if (!dma_set_coherent_mask(&devp->dev,  DMA_BIT_MASK(64))) {
    dev_info(DEV,"using 64bit DMA addressing\n");
  } else if (!dma_set_coherent_mask(&devp->dev,  DMA_BIT_MASK(32))) {
    dev_dbg(DEV,"using 32bit DMA addressing\n");
  } else {
    dev_alert(DEV,"No suitable DMA available.\n");
    goto err_bar0_region;
  }
  #else
  if (!dma_set_coherent_mask(&devp->dev,  0xfffffff)) {
    dev_info(DEV,"using 28bit DMA addressing\n");
  } else {
   dev_alert(DEV,"No suitable DMA available.\n");
   goto err_bar0_region;
  }
 #endif
#else
  /* are 32bit or 64 bit */
  if (!pci_set_dma_mask(devp,  DMA_BIT_MASK(64))) {
     dev_dbg(DEV,"using 64bit DMA addressing\n");
   } else if (!pci_set_dma_mask(devp,  DMA_BIT_MASK(32))) {
     dev_alert(DEV,"using 32bit DMA addressing\n");
   } else {
     dev_alert(DEV,"No suitable DMA available.\n");
     goto err_bar0_region;
  }

  if (!pci_set_consistent_dma_mask(devp,  DMA_BIT_MASK(64))) {
    dev_dbg(DEV,"using 64bit consistent DMA addressing\n");
  } else if (!pci_set_consistent_dma_mask(devp,  DMA_BIT_MASK(32))) {
    dev_alert(DEV,"using 32bit consistent DMA addressing\n");
  } else {
    dev_alert(DEV,"No suitable consistent DMA available.\n");
    goto err_bar0_region;
  }
#endif

#ifdef MICEXTOLL
  /* get BAR0 address and size */
  card.bar0_addr = micextoll_resource_start0;
  card.bar0_size = micextoll_resource_len0;
  dev_dbg(DEV,"BAR0/1 region: %lx / %lx\n", card.bar0_addr,
        card.bar0_size);
  if (!request_mem_region(card.bar0_addr, card.bar0_size, "hal_regfile")) {
    dev_alert(DEV,"BAR0/1 already in use\n");
    goto err_bar0_region;
  }
  dev_dbg(DEV,"BAR0/1 allocated at addr %lx size %lx (hex)\n",
        card.bar0_addr, card.bar0_size);

  /* get BAR2 address and size */
  card.bar2_addr = micextoll_resource_start2;
  card.bar2_size = micextoll_resource_len2;
  dev_dbg(DEV,"BAR2/3 region: %lx / %lx\n", card.bar2_addr,
        card.bar2_size);
  if (!request_mem_region(card.bar2_addr, card.bar2_size, "hal_EXTOLL")) {
    dev_alert(DEV,"BAR2/3 already in use\n");
    goto err_bar2_region;
  }
  dev_dbg(DEV,"BAR2/3 allocated at addr %lx size %lx (hex)\n",
        card.bar2_addr, card.bar2_size);

  /* get BAR2 address and size */
  card.bar4_addr = micextoll_resource_start4;
  card.bar4_size = micextoll_resource_len4;
  dev_dbg(DEV,"BAR4/5 region: %lx / %lx\n", card.bar4_addr,
       card.bar4_size);
  if (!request_mem_region(card.bar4_addr, card.bar4_size, "hal_EXTOLL")) {
   dev_alert(DEV,"BAR4/5 already in use. Ignoring, as it is now used for now.\n");
   //FIXME: Allow failing of BAR4/5 for now!
   //goto err_bar4_region;
  }
  dev_dbg(DEV,"BAR4/5 allocated at addr %lx size %lx (hex)\n",
  card.bar4_addr, card.bar4_size);
#else
  /* get BAR0 address and size */
  card.bar0_addr = pci_resource_start(devp, 0);
  card.bar0_size = pci_resource_len(devp, 0);
  dev_dbg(DEV,"BAR0/1 region: %lx / %lx\n", card.bar0_addr,
        card.bar0_size);
  if (!request_mem_region(card.bar0_addr, card.bar0_size, "hal_regfile")) {
    dev_dbg(DEV,"BAR0/1 already in use\n");
    goto err_bar0_region;
  }
  dev_dbg(DEV,"BAR0/1 allocated at addr %lx size %lx (hex)\n",
        card.bar0_addr, card.bar0_size);

  /* get BAR2 address and size */
  card.bar2_addr = pci_resource_start(devp, 2);
  card.bar2_size = pci_resource_len(devp, 2);
  dev_dbg(DEV,"BAR2/3 region: %lx / %lx\n", card.bar2_addr,
        card.bar2_size);
  if (!request_mem_region(card.bar2_addr, card.bar2_size, "hal_EXTOLL")) {
    dev_alert(DEV,"BAR2/3 already in use\n");
    goto err_bar2_region;
  }
  dev_dbg(DEV,"BAR2/3 allocated at addr %lx size %lx (hex)\n",
        card.bar2_addr, card.bar2_size);

/* get BAR2 address and size */
  card.bar4_addr = pci_resource_start(devp, 4);
  card.bar4_size = pci_resource_len(devp, 4);
  dev_dbg(DEV,"BAR4/5 region: %lx / %lx\n", card.bar4_addr,
        card.bar4_size);
  if (!request_mem_region(card.bar4_addr, card.bar4_size, "hal_EXTOLL")) {
    dev_alert(DEV,"BAR4/5 already in use. Ignoring, as it is not used for now.\n");
    //FIXME: Allow failing of BAR4/5 for now!
    //goto err_bar4_region;
  }
  dev_dbg(DEV,"BAR4/5 allocated at addr %lx size %lx (hex)\n",
        card.bar4_addr, card.bar4_size);

 dev_dbg(DEV,"EXTOLL: enable bus-master mode...\n");
 pci_set_master(devp);
#endif

 dev_info(DEV,"EXTOLL: Set-up BAR remapping...\n");
 extoll_set_up_internal_address_map();
 if (extoll_set_up_ioremap(&card)!=0)
 {
   dev_alert(DEV,"error while remapping BAR regions. \n");
   return -EBUSY;
 }

  dev_info(DEV,"Setting up extoll registerfile and sysfs\n");
  extoll_rf_create_sysfs_extoll_rf_files(&devp->dev,(unsigned long*)card.rf_vaddr);
 
  dev_info(DEV,"Setting up address based intra-chip routing.\n");
  extoll_set_up_address_intervals();
  dev_info(DEV,"address based intra-chip routing done.\n");
  
  /* test for network readiness */ 
  dev_info(DEV,"Setting up NW state handling\n");  
  INIT_LIST_HEAD(&card.nw_state_handlers);
  INIT_LIST_HEAD(&card.nw_task_list);


  card.nw_state=get_extoll_rf_info_rf_scratchpad_scratchpad(EXTOLL_SCRATCH_NETWORK_STATE);
  dev_dbg(DEV,"init spinlock\n");
  spin_lock_init(&card.nw_state_lock);
  dev_dbg(DEV,"add handler\n");
  extoll_add_nw_state_handler(print_nw_state);  
  dev_info(DEV,"NW state handling setup done\n");

  dev_info(DEV,"Setting up XBAR monitoring for port 10...\n");
  tasklet_init(&card.xbar_outp10_tasklet, xbar_outp10_f,0);
  set_extoll_rf_nw_xbar_rf_outp10_general(0x4000000l);
  dev_info(DEV,"Setting up XBAR monitoring for port 10 donen");
 
  /* Now creating HT interrupt  & installing handler for it */
  dev_info(DEV,"Setting up interrupts...\n");

  dev_dbg(DEV,"setup default interrupt handler routines\n");
  init_extoll_interrupt_handlers();
  extoll_register_interrupt_handler(SNQ_TE_XBAR_OUTPORT,extoll_check_xbar_outp);
  extoll_register_interrupt_handler(SNQ_TE_PCIE_CORE_LINK_STATUS_INT,extoll_pcie_status_irq_handler);
  extoll_register_interrupt_handler(SNQ_TE_BQ_ERROR,extoll_bq_error_handler);
  extoll_register_interrupt_handler(SNQ_TE_ECC_ERROR,extoll_ecc_correctable_status_irq_handler);
  extoll_register_interrupt_handler(SNQ_TE_ECC_FATAL,extoll_ecc_uncorrectable_status_irq_handler);
  extoll_register_interrupt_handler(SNQ_TE_NW_STATE,extoll_nw_state_irq_handler);
  extoll_register_interrupt_handler(SNQ_TE_BARRIER_GLOBAL_INTERRUPT,extoll_global_irq_handler);
  

  dev_dbg(DEV,"setting up SNQ...\n");
  snq_setup(&card);
  dev_dbg(DEV,"setting up SNQ done\n");
 
#ifdef MICEXTOLL
   irq=0; //pci_enable_msi(devp) <-we have to implement the logik of this function

  if (irq!=0) {
    dev_alert(DEV,"creating MSI interrupt failed: %d\n", irq);
    dev_alert(DEV,"continuing without irqs...\n");
    card.irq=0;
  }
  else
  {
    card.use_msi=1;
    devp->irq=16;
    irq=devp->irq;
  }

  if (irq>0) //there is an interrupt available, register it
  {
    dev_dbg(DEV,"interrupt: %u\n", irq);
    dev_info(DEV,"registering interrupt handler\n");
    //if (request_irq(irq, extoll_interrupt_handler, IRQF_SHARED, "extoll", devp))
    if (request_irq(irq, extoll_interrupt_handler, 0, "extoll", devp))//FIXME we have to check this!!!
      {
        dev_dbg(DEV,"request_irq for irq %i failed\n", irq);
                                card.init_done=1;
      }
    else
      {
        desc = irq_get_irq_data(irq);
        if(desc == NULL)
        {
          dev_alert(DEV,"No description to IRQ found!\n");
        }
        else{
          IrqCfg = (struct irq_cfg*)(desc->chip_data);
          irq_vector = IrqCfg->vector;
        }
        dev_dbg(DEV,"request_irq for irq %i with vector %d successful\n", irq, irq_vector);
        card.irq=irq;
                                card.init_done=1;
        snq_start(&card);
      }
  }
#else
  dev_info(DEV,"enabling MSI interrupts...\n");    
  for (i=0;i<32;i++) {
    card.irqs[i]=0;
    card.irq_free[i]=0;
  }
  card.num_irqs=0;
  
  num_irqs=EKVCL_pci_msi_vec_count(devp);
  dev_info(DEV,"Card reports %d MSI vectors available\n",num_irqs);
  num_irqs=pci_enable_msi_range(devp, 1, num_irqs);
  dev_info(DEV,"Kernel enabled %d MSIs\n",num_irqs);
  if (num_irqs<0) { //error_count
      dev_alert(DEV,"creating MSI interrupt failed: %d\n", num_irqs);
      dev_alert(DEV,"continuing without irqs...\n");
      card.num_irqs=0;
      card.use_msi=0;
			irq=0;
  }
  else {
    card.num_irqs=num_irqs;
    irq=devp->irq;
    card.use_msi=1;
    for (i=0;i<card.num_irqs;i++)
    {
      card.irqs[i]=irq+i;
      card.irq_free[i]=1;
    }
  }
  
  if (card.num_irqs>0) //there is an interrupt available, register it
  {
    dev_dbg(DEV,"interrupt: %u\n", irq);
    dev_dbg(DEV,"registering interrupt handler\n");
    //make sure snq is running and card init done is flagged before requesting the actual interrupt
    snq_start(&card);
    card.init_done=1;
    
    //if (request_irq(irq, extoll_interrupt_handler, IRQF_SHARED, "extoll", devp))
    if (request_irq(card.irqs[0], extoll_interrupt_handler, 0, "extoll", devp))
      {
        dev_alert(DEV,"request_irq for irq %i failed\n", card.irqs[0]);
        //card.init_done=1;
        snq_finalize(&card);
      }
    else
      {
        dev_dbg(DEV,"request_irq for irq %i successful\n", card.irqs[0]);
        card.irq_free[0]=2;
        //card.init_done=1;
        //snq_start(&card);
      }
   
  }  
#endif
  //make sure we have the latest nw state
  spin_lock_irqsave(&card.nw_state_lock,flags);
  card.nw_state=get_extoll_rf_info_rf_scratchpad_scratchpad(EXTOLL_SCRATCH_NETWORK_STATE);
  spin_unlock_irqrestore(&card.nw_state_lock,flags);


  dev_info(DEV,"init successful \n");
       
  return 0;

  /* ERROR handling */
err_bar2_region:
  release_mem_region(card.bar0_addr, card.bar0_size);

err_bar0_region:
#ifndef MICEXTOLL
  pci_disable_device(devp);
#endif
  dev_alert(DEV,"init failed!\n\n");

  return -EBUSY;
}

static void __extoll_devexit extoll_remove(struct pci_dev *devp)
{
  int i;
  extoll_nw_handler_list_t* item,*next;


  spin_lock(&card.nw_state_lock);
  list_for_each_entry_safe(item,next,&card.nw_state_handlers,list) {
    list_del(&item->list);
    kfree(item);  
  }
  spin_unlock(&card.nw_state_lock);
  // clean-up snq
  snq_finalize(&card);
  card.init_done=0;

#ifdef MICEXTOLL
   if (card.irq!=0)
  {
    free_irq(irq,devp);
  }
#else  
  for (i=0;i<card.num_irqs;i++)
  {
    if (card.irq_free[i]==2) //its registered
    {
      free_irq(card.irqs[i],devp);
    }
  }
  if (card.use_msi==1)
      pci_disable_msi(devp);
#endif
  /* 
  * clean up sysfs
  */
 // extoll_remove_sysfs_extoll_files(&devp->dev);
  sysfs_remove_group(&card.devp->dev.kobj, *extoll_groups);
  extoll_rf_remove_sysfs_extoll_rf_files(&devp->dev);

  /* clean up any allocated resources and stuff here.
  * like call release_region();
  */

  dev_dbg(DEV,"unmapping RF  \n");
  iounmap(card.rf_vaddr);
  dev_dbg(DEV,"unmapping VELO2  \n");
  iounmap(card.velo2_vaddr);
  dev_dbg(DEV,"unmapping RMA2  \n");
  iounmap(card.rma2_vaddr);
  dev_dbg(DEV,"unmapping SMFU2  \n");
  iounmap(card.smfu2_vaddr);
  
  dev_dbg(DEV,"releasing BARs ...\n");
  release_mem_region(card.bar0_addr, card.bar0_size);
  release_mem_region(card.bar2_addr, card.bar2_size);
  release_mem_region(card.bar4_addr, card.bar4_size);
  
  dev_info(DEV,"EXTOLL: disabling Device ...\n");
#ifndef MICEXTOLL
  pci_disable_device(devp);
#endif

}

#ifdef MICEXTOLL
static struct micextoll_driver micextoll_driver0 = {
  .name = "extoll",
  .module = THIS_MODULE,
  .driver = {
	.name = "extoll",
  },
  .probe = extoll_probe, 
  .remove = __extoll_devexit_p(extoll_remove),
};

#else
static struct pci_driver pci_driver = {
  .name = "extoll",
  .id_table = ids,
  .probe = extoll_probe,
  .remove = __extoll_devexit_p(extoll_remove),
};
#endif



/******************************************************************************
*  Interrupt handling							      *
******************************************************************************/
#ifndef MICEXTOLL
int extoll_request_free_irq(irq_handler_t handler,
                unsigned long irqflags,
                const char *devname,
                void *dev_id)
{
  int i;
  for (i=0;i<card.num_irqs;i++) {
    if (card.irq_free[i]==1)
    {
      card.irq_free[i]=2;
      return  request_irq(card.irqs[i], handler, irqflags, devname, dev_id);
   }
  }
  return -EBUSY;
}
EXPORT_SYMBOL(extoll_request_free_irq);
#endif

//there is one possible handler per trigger group (interrupt cause)
static extoll_i_handler_t irq_handlers[SNQ_TRIG_NUM_MAX+1];

static irq_handler_t dummyWrapper;
static int dummyWrapper_set = 0;

void extoll_default_irq_handler(snq_entry_t* entry,int te, int entry_idx)
{
  if (printk_ratelimit()) {
   // dev_info_ratelimited(DEV,"default interrupt handler with TE=%x and entry_idx=%x\n",te,entry_idx);
    snq_dump_entry(entry);
  }
}

void set_extoll_dummyWrapper(irq_handler_t knc_handler){
	dummyWrapper = knc_handler;
	dummyWrapper_set = 1;
}
EXPORT_SYMBOL(set_extoll_dummyWrapper);

void set_nvidia_state(void *nvl){
	vpci_nvl = nvl;
}
EXPORT_SYMBOL(set_nvidia_state);

void set_nvidia_irq(int irq){
	vpci_nvidia_irq = irq;
}
EXPORT_SYMBOL(set_nvidia_irq);

void extoll_clean_dummyWrapper(void){
	dummyWrapper = NULL;
	dummyWrapper_set = 0;
}
EXPORT_SYMBOL(extoll_clean_dummyWrapper);


/* initialize the irq function pointer array */
void init_extoll_interrupt_handlers(void)
{
  int i;
  for (i=0;i<SNQ_TRIG_NUM_MAX+1;i++)
    {
      irq_handlers[i]=extoll_default_irq_handler;
    }
    dummyWrapper = NULL;
}
/* register a handler function for the extoll interrupt cause with the given idx
  */
void extoll_register_interrupt_handler(int idx, extoll_i_handler_t handler)
{
  irq_handlers[idx]=handler;
  dev_dbg(DEV,"extoll_register_interrupt_handler: TE: %i, handler: %p\n", idx, handler);
}
EXPORT_SYMBOL(extoll_register_interrupt_handler);

/* register a handler function for the extoll interrupt cause with the given idx
  */
void extoll_deregister_interrupt_handler(int idx)
{
  irq_handlers[idx]=extoll_default_irq_handler;
}
EXPORT_SYMBOL(extoll_deregister_interrupt_handler);

unsigned long int pcount = 0;
unsigned long int zerocnt = 0;
unsigned long int try_cnt = 0;

static irqreturn_t extoll_interrupt_handler(int irq, void *dev_id)
{
  snq_entry_t* entry;
  int handler_idx; //which te triggered the interrupt
  int entry_idx; //normally zero, for multi-entry events zero to (num_entries-1)
  extoll_i_handler_t handler;
  int retry_count=0;
  int entry_count=0;
//  int i = 0;
  unsigned long int rp = 0l;

  dev_dbg(DEV,"EXTOLL Interrupt. \n");
  if (card.init_done==0)
  {
    dev_alert(DEV,"EXTOLL Interrupt: card not yet configured, bailing out\n");
    return  IRQ_HANDLED;
  }

retry_snq:  
   //check all valid snq entries and dispatch
   entry=snq_get_next_entry(&card);
   if ((entry==0)&&(dummyWrapper_set==0))
   {     
     retry_count++;
	if ((retry_count == 1) || (retry_count==1000))
     {
	     dev_alert(DEV,"OOPS. Entry returned was zero for %i times. Interrupt bug??\n Software watermark: %li\n Current WP: %li\n Internal RP: %i\n try_cnt: %li\n Handled SNQ entries: %li\n CPU ID: %i\n", 
                       retry_count,card.snq_config.watermark,get_extoll_rf_snq_rf_queue_wplt(),card.snq_config.wb_rp,try_cnt,zerocnt,smp_processor_id());
	     dev_alert(DEV,"Packet Counter: %li\n",pcount);
       
       rp=(card.snq_config.wb_rp+1) % card.snq_config.snq_size;
       
       dev_info(DEV,"Dump of SNQ Entry: %i\n", card.snq_config.wb_rp);
       snq_dump_entry((snq_entry_t*)&card.snq_config.snq[card.snq_config.wb_rp]);
       dev_info(DEV,"Dump of SNQ Entry: %li\n", rp);
       snq_dump_entry((snq_entry_t*)&card.snq_config.snq[rp]);
       dev_info(DEV,"Dump of SNQ Entry: %li\n", (rp+1)%card.snq_config.snq_size);
       snq_dump_entry((snq_entry_t*)&card.snq_config.snq[(rp+1)%card.snq_config.snq_size]);
       dev_info(DEV,"Dump of SNQ Entry: %li\n", (rp+2)%card.snq_config.snq_size);
       snq_dump_entry((snq_entry_t*)&card.snq_config.snq[(rp+2)%card.snq_config.snq_size]);
       
       if(retry_count == 1000){
	       snq_arm(&card);
	       return IRQ_HANDLED;
       }
     }
     goto retry_snq;
   }else if(entry==0){
	dev_dbg(DEV,"extoll_interrupt_handler: calling dummyWrapper...\n");
	dummyWrapper(vpci_nvidia_irq,vpci_nvl);
	return IRQ_HANDLED;
   }
   do {
    //get the correct handler:
    pcount = (pcount+1) % card.snq_config.snq_size;
    handler_idx=SNQ_TE(SNQ_PC_table[entry->header.fields.pc]);
    entry_idx=SNQ_ENTRY(SNQ_PC_table[entry->header.fields.pc]);
    dev_dbg(DEV,"decoding snq event. pc is %x, handler idx is %x, entry_idx is %x\n", entry->header.fields.pc, handler_idx,entry_idx);
    handler=irq_handlers[handler_idx];
    dev_dbg(DEV,"handler selected for idx %x, %p, default handler is %p\n",handler_idx, handler, extoll_default_irq_handler);
    if (handler==0)  {
      dev_alert(DEV,"OOPS. Decoded a NULL interrupt handler!!!\n");
      snq_dump_entry(entry);
    }
    else  {
     (*handler)(entry,handler_idx,entry_idx);
     dev_dbg(DEV,"extolldrv called irq handler: %p\n", handler);
    }
    snq_entry_done(&card,entry);
    zerocnt++;
    entry=snq_get_next_entry(&card);
    entry_count++;
    } while (entry!=0 /*&& entry_count<64*/);
     snq_update_rp(&card);
    snq_arm(&card);
  interrupt_counter++;

  if (entry_count > 64)
     EKVCL_dev_info_ratelimited(DEV,"EXTOLL Interrupt: handled %d snq entries in one invocation\n",entry_count); 
  
  return IRQ_HANDLED;
}
int extoll_get_irq(void)
{
#ifdef MICEXTOLL
  if ( card.irq>0 )
   return card.irq;
#else
  if ( (card.num_irqs>0) && (card.irq_free[0]==2) )
   return card.irqs[0];
#endif
  else
   return -1;
}
EXPORT_SYMBOL(extoll_get_irq);

//#endif//CHECK
/******************************************************************************
*  Module handling							      *
******************************************************************************/
/* Make sure all device files for class extoll reside under subdir extoll.
 * Also set default permissions to 0666 respectively not for priviliged devs.
*/
static char *extoll_devnode_user(struct device *dev, EKVCL_umode_t *mode)
{
        if (mode) {
          *mode = 0666;
        }
        return kasprintf(GFP_KERNEL, "extoll/%s", dev_name(dev));
}

static char *extoll_devnode_priv(struct device *dev, EKVCL_umode_t *mode)
{
        return kasprintf(GFP_KERNEL, "extoll/%s", dev_name(dev));
}

static int __init extoll_init(void)
{
#ifdef MICEXTOLL
  int ret=-1;
#endif

  DEBUG(printk(KERN_INFO "EXTOLL: module init\n");)

  _extoll_vpids_per_page=PAGE_SIZE/4096;
  if (PAGE_SIZE<4096)
  {
    printk(KERN_ALERT "EXTOLL: size of a page is %li, which is smalled than 4k and not supported.\n",PAGE_SIZE);
    return -ENXIO;
  }
  if (PAGE_SIZE % 4096 != 0 )
  {
    printk(KERN_ALERT "EXTOLL: size of a page seems to be %li which is not a multiple of 4k\n",PAGE_SIZE);
    return -ENXIO;
  }
  if (PAGE_SIZE > 1048576l )
  {
    printk(KERN_ALERT "EXTOLL: machine page size is %ld which is larger then 1MB. Not supported\n",PAGE_SIZE);
    return -ENXIO;
  }
  _extoll_max_addressable_vpids=256 /  _extoll_vpids_per_page;
  printk(KERN_INFO "EXTOLL: machine page size is %ld, a maximum of %d vpids is supported\n",PAGE_SIZE,_extoll_max_addressable_vpids);
 
  extoll2_class_user = class_create(THIS_MODULE, "extoll");
  if (extoll2_class_user==NULL) {
     printk(KERN_ALERT "extoll_user class creation failed\n");
     return -ENOMEM;     
  }    
  extoll2_class_user->devnode = extoll_devnode_user;
  
  extoll2_class_priv = class_create(THIS_MODULE, "extoll_priv");
  if (extoll2_class_priv==NULL) {
     printk(KERN_ALERT "extoll_priv class creation failed\n");
     return -ENOMEM;     
  }    
  extoll2_class_priv->devnode = extoll_devnode_priv;


#ifdef MICEXTOLL

  printk(KERN_INFO "EXTOLL: try to init extoll device for MIC\n");
  extoll_register_dev(&micextoll_dev0);

  printk(KERN_INFO "EXTOLL: try to init extoll base driver for MIC\n");
  ret = register_micextoll_driver(&micextoll_driver0);//perhaps we should rename it into: micextoll_register_driver
  


  return extoll_probe(&micextoll_dev0, 0);

#else
//  printk(KERN_INFO "EXTOLL: have found %i devices\n");
  return pci_register_driver(&pci_driver);
#endif


}

static void __exit extoll_exit(void)
{
#ifdef MICEXTOLL
  printk(KERN_INFO "EXTOLL: extoll.ko module exit\n");

  extoll_remove(&micextoll_dev0);

   //unregister driver
  unregister_micextoll_driver(&micextoll_driver0);

  //unregister device
  unregister_micextoll_device(&micextoll_dev0);

#else
  printk(KERN_INFO "EXTOLL: module exit, interrupt counter is %u\n", interrupt_counter);
  pci_unregister_driver(&pci_driver);
#endif
 class_destroy(extoll2_class_user);
 class_destroy(extoll2_class_priv);
 printk(KERN_INFO "EXTOLL: module exit finished!\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mondrian Nuessle nuessle@uni-hd.de");
MODULE_DESCRIPTION("Base EXTOLL hardware driver.");
MODULE_VERSION("1.0");

module_init(extoll_init);
module_exit(extoll_exit);
