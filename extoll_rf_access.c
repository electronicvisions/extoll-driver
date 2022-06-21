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
#include <linux/mutex.h>

#include <asm/uaccess.h>

#include "extolldrv.h"
#include "extoll_rf_sysfs.h"
#include "extoll_kapi.h"
#include "smfu2drv.h"
#include "extoll_rf_access_ioctl.h"
#include "extoll_rf_access.h"

//for debugging purpose
#include <linux/jiffies.h>
#include <linux/delay.h>

/* minors */
#define EXTOLL_RF_ACCESS_MINOR_COUNT	1
#define EXTOLL_RF_ACCESS_MINOR			0

#define DEV extoll2_rf.dev

DEFINE_MUTEX(rra_mutex);  

struct extoll2_rf_device {

    struct pci_dev *devp;         //! pointer to the pci device of EXTOLL
    struct cdev cdev;             //! the character device file for direct rf access
    dev_t devnr;                 //! the major number of the rf access device file
    struct device* dev;
    RMA2_Handle* rma2_handle;
};

typedef struct extoll2_rf_device extoll2_rf_device_t;

static extoll2_rf_device_t extoll2_rf; 
/******************************************************************************
*  Manage concurrent access		   				      *
******************************************************************************/
//DECLARE_MUTEX(access_mutex);	//mutex is initialized unlocked.
DEFINE_MUTEX(access_mutex);	//mutex is initialized unlocked.


/*
 Kernel level functions to perform RRA Accesses
*/

extoll2_rf_context_t* extoll2_rf_rra_open(void)
{
 extoll2_rf_context_t* context;

 context=kmalloc(sizeof(extoll2_rf_context_t),GFP_KERNEL);
  if (context==NULL) {
    dev_alert(DEV,"no memory available for extoll_rf_context\n");
    return NULL;
  }
 context->node=-1;
 context->addr=0x8008;
 context->write_mode=EXTOLL2_RF_RRA_SMFU2;
 context->read_mode=EXTOLL2_RF_RRA_RMA2;
 context->timeout=1000;

 return context;
}
EXPORT_SYMBOL(extoll2_rf_rra_open);

int extoll2_rf_rra_close(extoll2_rf_context_t* context)
{
 kfree(context);
 return 0;
}
EXPORT_SYMBOL(extoll2_rf_rra_close);

int extoll2_rf_rra_write(extoll2_rf_context_t* context, uint64_t value)
{
  int result;
  volatile uint64_t* reg;
 
  if (context==NULL) {
    dev_warn(DEV,"rra_write called with NULL context.\n");
    return -EFAULT;
  }
 if (context->node==-1) {
   dev_warn(DEV,"rra access to node id -1 requested\n");
   return -EFAULT;
 }
 dev_dbg(DEV,"requested to write %lx to register\n",(unsigned long) value);
 if (context->write_mode==EXTOLL2_RF_RRA_SMFU2) {
  dev_dbg(DEV,"write with SMFU\n");
  smfu2_rra_write(context->node,context->addr,value);
 } else if (context->write_mode==EXTOLL2_RF_RRA_RMA2) {
  dev_dbg(DEV,"write with RMA\n");
  result=kapi_rra_write(extoll2_rf.rma2_handle, context->node, context->addr, value,context->timeout);
  if (result!=0) {
    dev_alert(DEV,"rma2 based rra write failed with %d\n",result);
    return result;
  }
 }
else if (context->write_mode==EXTOLL2_RF_RRA_LOCAL) {
 reg=extoll_get_rf_vaddr() + context->addr;
  *reg=value;
  return 0;
 } else {
  dev_alert(DEV,"write with unkonwn method.\n");
  return -EFAULT;
 }
 return 0;
}
EXPORT_SYMBOL(extoll2_rf_rra_write);

int extoll2_rf_rra_read(extoll2_rf_context_t* context, uint64_t* value)
{
  int result;
  volatile uint64_t* reg;

  if (context==NULL) {
    dev_warn(DEV,"rra_read called with NULL context.\n");
    return -EFAULT;
  }
 if (context->node==-1) {
   dev_warn(DEV,"rra access to node id -1 requested\n");
   return -EFAULT;
 }
 dev_dbg(DEV,"read requested from node %d and addr %x\n",context->node,context->addr);
 if (context->read_mode==EXTOLL2_RF_RRA_SMFU2) {
  dev_dbg(DEV,"read with SMFU\n");
  *value=smfu2_rra_read(context->node,context->addr);
 } else if (context->read_mode==EXTOLL2_RF_RRA_RMA2) {
  dev_dbg(DEV,"read with RMA\n");
  //uint64_t kapi_rra_read(RMA2_Handle *rhandle, struct page *page, uint16_t dest_nodeid, uint64_t dest_rra_addr);
  result=kapi_rra_read(extoll2_rf.rma2_handle,context->node, context->addr,value,context->timeout);
  if (result!=0) {
    dev_alert(DEV,"rma2 based rra read failed with %ld\n",(long)result);
    return result;
  }
 }
 else if (context->read_mode==EXTOLL2_RF_RRA_LOCAL) {
  reg=extoll_get_rf_vaddr() + context->addr;
  *value=*reg;
  return 0;
 } else {
  dev_alert(DEV,"read with unkonwn method.\n");
  return -EFAULT;
 }
 dev_dbg(DEV,"read %lx from register\n",(unsigned long) value);
 return 0;
}
EXPORT_SYMBOL(extoll2_rf_rra_read);

void extoll2_rf_rra_seek(extoll2_rf_context_t* context, int node, int address)
{
  context->node=node;
  context->addr=address;  
}
EXPORT_SYMBOL(extoll2_rf_rra_seek);

int extoll2_rf_rra_set_read_timeout(extoll2_rf_context_t* context, uint64_t value)
{
 context->timeout=value;
 return 0;
}
EXPORT_SYMBOL(extoll2_rf_rra_set_read_timeout);



/*****************************************************************************
*  file operations of device					      *
******************************************************************************/
static int extoll2_rf_open(struct inode *inodp, struct file *filp)
{
  int minor;
  extoll2_rf_context_t* context;

  minor = MINOR(inodp->i_rdev);
  if (minor!=0)
  {
	dev_alert(DEV,"trying to open invalid minor.\n");
	return -EINVAL;
  }
  dev_dbg(DEV,"opened special file...\n");
  if (mutex_lock_interruptible(&rra_mutex)==-EINTR){
    dev_alert(DEV,"rra mutex locking intertupted\n");
    return -EINTR;
  }

  context=extoll2_rf_rra_open();
  if (context==NULL) {
    dev_alert(DEV,"no memory available for extoll_rf_context\n");
    mutex_unlock(&rra_mutex);
    return -ENOMEM;
  }
 filp->private_data=context;
 mutex_unlock(&rra_mutex);

 return 0;
}


static loff_t extoll2_rf_llseek(struct file *filp, loff_t off, int whence)
{
  unsigned long node;
  unsigned long addr;
  extoll2_rf_context_t* context;
  
  if (mutex_lock_interruptible(&rra_mutex)==-EINTR){
    dev_alert(DEV,"rra mutex locking intertupted\n");
    return -EINTR;
  }

  context=(extoll2_rf_context_t*) filp->private_data;
  
  addr= off & 0x3ffffffl;
  node = (off >> 32l) & 0xffffl;
  dev_dbg(DEV,"Seeking to node %ld and addr %lx\n",node, addr);
  extoll2_rf_rra_seek(context,node, addr);
  
 filp->f_pos=off;
  mutex_unlock(&rra_mutex);

  return off;
}

ssize_t extoll2_rf_read(struct file *filp, char __user *buff, size_t count, loff_t *offp)
{
 extoll2_rf_context_t* context;
 uint64_t value;
 int result;
  if (mutex_lock_interruptible(&rra_mutex)==-EINTR){
    dev_alert(DEV,"rra mutex locking intertupted\n");
    return -EINTR;
  }

 context=(extoll2_rf_context_t*) filp->private_data;
 if (count!=8) {
   dev_alert(DEV,"RRA access only supported with write() sizes of 8 byte (requested %ld bytest)\n",count);
   mutex_unlock(&rra_mutex);
   return -EFAULT;
 }

 *offp=filp->f_pos;
 result=extoll2_rf_rra_read(context,&value);
 if (result!=0) {
  dev_alert(DEV,"error performing rra read\n");
  mutex_unlock(&rra_mutex);
  return result;
 } 
 if (copy_to_user(buff,&value,8)!=0) {
  dev_alert(DEV,"rra read: could not copy data to userspace\n");
  mutex_unlock(&rra_mutex);
  return -EFAULT;
 }
 mutex_unlock(&rra_mutex);
 return 8;
}

ssize_t extoll2_rf_write(struct file *filp, const char __user *buff,size_t count, loff_t *offp)
{
 extoll2_rf_context_t* context;
 uint64_t value;
 int result;
  if (mutex_lock_interruptible(&rra_mutex)==-EINTR){
    dev_alert(DEV,"rra mutex locking intertupted\n");
    return -EINTR;
  }

 context=(extoll2_rf_context_t*) filp->private_data;
 
 if (count!=8) {
   dev_alert(DEV,"RRA access only supported with write() sizes of 8 byte (requested %ld bytest)\n",count);
   mutex_unlock(&rra_mutex);
   return -EFAULT;
 }

 *offp=filp->f_pos;
 dev_dbg(DEV,"write requested to node %d and addr %x\n",context->node,context->addr);
 if (copy_from_user(&value,buff,8)!=0) {
  dev_alert(DEV,"rra read: could not copy data from userspace\n");
  mutex_unlock(&rra_mutex);
  return -EFAULT;
 }
 dev_dbg(DEV,"requested to write %lx to register\n",(unsigned long) value);
 result=extoll2_rf_rra_write(context, value);
 if (result!=0) {
    dev_alert(DEV,"rra write failed with %d\n",result);
    mutex_unlock(&rra_mutex);
    return result;
  }
 mutex_unlock(&rra_mutex);
 return 8;
}


static int extoll2_rf_release(struct inode *inodp, struct file *filp)
{
  int result;
  if (mutex_lock_interruptible(&rra_mutex)==-EINTR){
    dev_alert(DEV,"rra mutex locking intertupted\n");
    return -EINTR;
  }
 result=extoll2_rf_rra_close((extoll2_rf_context_t*)filp->private_data);
 filp->private_data=0;
 dev_dbg(DEV,"succesfully released.\n");
 mutex_unlock(&rra_mutex);

  return result;
}

/********************************************************************************/
/*  VMA operations                                                             **/
/* ******************************************************************************/

/******************************************************************************
*  mmap rf space to user space                                                *
******************************************************************************/
static int extoll2_rf_mmap(struct file *filp, struct vm_area_struct *vma)
{
  unsigned long vsize = 0;	// size of needed virtual address space
  unsigned long physical = 0;	// physical start address
  unsigned long pfn;	// page frame number

  vsize = vma->vm_end - vma->vm_start;
  dev_dbg(DEV,"mmap called for rf space. offset is %lx\n",
        (unsigned long)vma->vm_pgoff << PAGE_SHIFT);
    
  if (vsize!=EXTOLL_R2_RF_MMIO_SIZE) //must request the whole rf -> is 32 MB at the moment
	return -EINVAL;

  mutex_lock(&access_mutex);
 
   physical = extoll_get_rf_addr();
    vsize = vma->vm_end - vma->vm_start;
      
    dev_dbg(DEV,"mmaping physical %lx, vsize %lu, vm_start is %lx\n", physical, vsize,vma->vm_start);

    pfn = physical >> PAGE_SHIFT;
    dev_dbg(DEV,"pfn is: %lx\n", pfn);

    io_remap_pfn_range(vma, vma->vm_start, pfn,EXTOLL_R2_RF_MMIO_SIZE , vma->vm_page_prot);

    dev_dbg(DEV,"remapping iomem done.\n");

  mutex_unlock(&access_mutex);
  return 0;

}



/******************************************************************************
*  IO controls			                                              *
******************************************************************************/
/*static int extoll2_rf_ioctl(struct inode *inodp, struct file *filp,
                      unsigned int cmd, unsigned long arg)*/
static long extoll2_rf_ioctl_unlocked(struct file *filp,
                      unsigned int cmd, unsigned long arg)
{
  int result=0;
  extoll2_rf_context_t* context;
  uint64_t value;
  
  dev_dbg(DEV,"ioctl entry (cmd=%u, arg=%u)\n", (unsigned int) cmd, (unsigned int) arg );

  // Do some security tests on the requested command number
  if (_IOC_TYPE(cmd) != EXTOLL_RF_IOC_MAGIC)
      return -ENOTTY;
  if (_IOC_NR(cmd) > EXTOLL_RF_IOC_MAXNR)
      return -ENOTTY;

  // test provided argument buffer for necessary access rights
  if (_IOC_DIR(cmd) & _IOC_READ) {
      if (!access_ok(VERIFY_WRITE, (void *)arg, _IOC_SIZE(cmd)))
          return -EFAULT;
  }

  if (_IOC_DIR(cmd) & _IOC_WRITE) {
      if (!access_ok(VERIFY_READ, (void *)arg, _IOC_SIZE(cmd)))
          return -EFAULT;
  }
  context=(extoll2_rf_context_t*) filp->private_data;
 
  switch (cmd) {
    case (EXTOLL_RF_IOCTL_GET_RRA_WRITE_METHOD): {
      dev_dbg(DEV,"get rra write method %d\n",context->write_mode);
      value=context->write_mode;
      result=put_user(value, ((uint64_t *) arg));
      break;
    }
    case (EXTOLL_RF_IOCTL_GET_RRA_READ_METHOD): {
      dev_dbg(DEV,"get rra read method %d\n",context->read_mode);
      value=context->read_mode;
      result=put_user(value, ((uint64_t *) arg));
      break;
    }
    case (EXTOLL_RF_IOCTL_GET_RRA_RMA_TIMEOUT): {
      dev_dbg(DEV,"get rra read timeout %ld\n",(unsigned long) context->timeout);
      value=context->timeout;
      result=put_user(value, ((uint64_t *) arg));
      break;
    }
    case (EXTOLL_RF_IOCTL_SET_RRA_WRITE_METHOD): {
      get_user(value,((uint64_t *) arg));
      if (value==EXTOLL2_RF_RRA_SMFU2 ||value==EXTOLL2_RF_RRA_RMA2||value==EXTOLL2_RF_RRA_LOCAL)
        context->write_mode=value;
      else {
        dev_warn(DEV,"trying to set unkown RRA write method: %ld. Setting to default EXTOLL2_RF_RRA_SMFU2\n",(unsigned long) value);
        context->write_mode=EXTOLL2_RF_RRA_SMFU2;
        result=-EFAULT;
      }
      break;
    }
    case (EXTOLL_RF_IOCTL_SET_RRA_READ_METHOD): {
     get_user(value,((uint64_t *) arg));
      if (value==EXTOLL2_RF_RRA_SMFU2 ||value==EXTOLL2_RF_RRA_RMA2||value==EXTOLL2_RF_RRA_LOCAL)
        context->read_mode=value;
      else {
        dev_warn(DEV,"trying to set unkown RRA read method: %ld. Setting to default EXTOLL2_RF_RRA_RMA2\n",(unsigned long) value);
        context->read_mode=EXTOLL2_RF_RRA_RMA2;
        result=-EFAULT;
      }
      break;
    }
    case (EXTOLL_RF_IOCTL_SET_RRA_RMA_TIMEOUT): {
     get_user(value,((uint64_t *) arg));
     context->timeout=value;
     break;
    }

   default:{ 
      dev_warn(DEV,"unkown ioctl called.\n");
      result=-EFAULT;
      break;
    }
  }
  
  return result;
}

/**
* extoll2_rf file operations
*/
static struct file_operations extoll2_rf_fops = {
  .owner = THIS_MODULE,
  .llseek = extoll2_rf_llseek,
  .mmap = extoll2_rf_mmap,
  .unlocked_ioctl = extoll2_rf_ioctl_unlocked,
  .open = extoll2_rf_open,
  .release = extoll2_rf_release,
  .read = extoll2_rf_read,
  .write = extoll2_rf_write,
};

/******************************************************************************
*  PCI subsystem integration                                                  *
******************************************************************************/

static int extoll2_rf_setup_cdev(void)
{
  int err, devnr;

  devnr = MKDEV(MAJOR(extoll2_rf.devnr), EXTOLL_RF_ACCESS_MINOR);
  cdev_init(&extoll2_rf.cdev, &extoll2_rf_fops);
  extoll2_rf.cdev.owner = THIS_MODULE;
  extoll2_rf.cdev.ops = &extoll2_rf_fops;
  err = cdev_add(&extoll2_rf.cdev, devnr, 1);
  if (err < 0)
  {
    dev_alert(DEV,"Error %d adding cdev", err);
    cdev_del(&extoll2_rf.cdev);
    return err;
  }

  return 0;
}


static int extoll2_rf_probe(void)
{
  int result=0;
 
  printk(KERN_INFO "extoll2_rf: probe() called!\n");

  extoll2_rf.devp = extoll_get_pdev();
  if (extoll2_rf.devp==0)
    {
      printk(KERN_ALERT "extoll2_rf: no device found.\n");
      return -EINVAL;
    }

  /* dynamically allocate a major number and create two minor numbers:
  * ->  minor 0 = requester
  * ->  minor 1 = completer
  */
  if (alloc_chrdev_region(&extoll2_rf.devnr, 0, EXTOLL_RF_ACCESS_MINOR_COUNT, "extoll_rf_access")) {
    printk(KERN_ALERT "extoll2_rf: No Major Number available!!\n");
	result=-EBUSY;
    goto extoll2_rf_open_err_no_major;
  };

  extoll2_rf.dev=device_create(extoll_get_class_priv(), NULL, extoll2_rf.devnr, NULL, "extoll_rf_access");
  if (extoll2_rf.dev==NULL) {
     printk(KERN_ALERT "extoll2_rf device creation failed\n");
     result=-EBUSY;
     goto extoll2_rf_open_err_register_chrdev;
  }

 
  /* Device OK!
  * Now setup character device specific ops for requester and completer
  */
  if (extoll2_rf_setup_cdev() < 0)
  {
    printk(KERN_ALERT "extoll2_rf: error in extoll2_rf_setup_cdev\n");
    result=-EBUSY;
    goto extoll2_rf_open_err_device_create;
  }

  if (kapi_rma2_open(&extoll2_rf.rma2_handle,EXTOLL_VPID_RRA)!=0) {
   printk(KERN_ALERT "extoll2_rf: could not open rma2 vpid %d\n",EXTOLL_VPID_RRA);
   result=-EFAULT;
   goto extoll2_rf_open_err_rma2_open;
  }
  
  return 0;

  /* ERROR handling */
extoll2_rf_open_err_rma2_open:
  cdev_del(&extoll2_rf.cdev);
extoll2_rf_open_err_device_create:
  device_destroy(extoll_get_class_priv(),extoll2_rf.devnr);  
extoll2_rf_open_err_register_chrdev:
  unregister_chrdev_region(extoll2_rf.devnr, 1);
  printk(KERN_ALERT "extoll2_rf: Major requesternumber %x freed \n",
        MAJOR(extoll2_rf.devnr));

extoll2_rf_open_err_no_major:
  printk(KERN_ALERT "extoll2_rf: no major number available.\n");
  return result;
}


static void extoll2_rf_remove(void)
{
  kapi_rma2_close(&extoll2_rf.rma2_handle);
  dev_dbg(DEV,"deleting cdev of minor devices\n");
  cdev_del(&extoll2_rf.cdev);
      
  dev_dbg(DEV,"unregistering Major %d minor 0\n", MAJOR(extoll2_rf.devnr));
  unregister_chrdev_region(extoll2_rf.devnr, 1);
  device_destroy(extoll_get_class_priv(),extoll2_rf.devnr);     
  printk(KERN_DEBUG "extoll2_rf: remove done!!\n\n");
}

/******************************************************************************
*  Module handling							      *
******************************************************************************/
static int __init extoll2_rf_init(void)
{

  printk(KERN_DEBUG "extoll2_rf: module init\n");
  if (extoll_get_init_done()==0)
  {
    printk("EXTOLL Base driver not initialized! Bailing out\n");
    return -1;
  }
  /* Hardware needs 4KB pages !!!
  */
  if (PAGE_SIZE != 4096) {
    printk(KERN_ALERT "extoll2_rf: PAGE_SIZE is not 4KB !! exiting");
    return -ENXIO;
  }

  return extoll2_rf_probe();
  
}

static void __exit extoll2_rf_exit(void)
{
  extoll2_rf_remove();
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mondrian Nuessle mondrian.nuessle@extoll.de");
MODULE_DESCRIPTION("Extollv2: extoll2_rf driver");
MODULE_VERSION("1.0");

module_init(extoll2_rf_init);
module_exit(extoll2_rf_exit);
