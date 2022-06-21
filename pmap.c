/* Linux Kernel Physical Memory Mapper driver
 *
 * (C)2006, 2007, 2008, 2009 Computer Architecture Group, University of Heidelberg
 * (C)2011,2014 EXTOLL GmbH
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Author: Holger Froening, froening@uni-hd.de, Mondrian Nuessle mondrian.nuessle@extoll.de
 *
*/

#include "arch_define.h"

#include <linux/version.h>
#include <linux/types.h>
#include <linux/module.h> 
#include <linux/init.h>   
#include <asm/uaccess.h>  
#include <linux/dma-mapping.h>  
#include <linux/mm.h>

#include <linux/pagemap.h>
#include <linux/sched.h>

#define PMAPDRV
#include "pmap.h"
#include "extoll_kernel.h"
#include "extolldrv.h"

#ifdef MICEXTOLL
  #include "micextoll.h"
#else
  #include <linux/pci.h>
#endif

#define DEBUG(a)
//#define DEBUG(a) a
#define DEV pmap.dev

//static int major_number;
static unsigned int memory_map_opened = 0;
static int en_write_combining = 0;
static int en_ioremap = 0;
static uint32_t next_key=1;

module_param(en_write_combining, uint, S_IRUGO);
module_param(en_ioremap, uint, S_IRUGO);

static pmap_device_t pmap;

/* device operations defined later */
static int     pmap_open ( struct inode *inode, struct file *filp );
static int     pmap_release ( struct inode *inode, struct file *filp );
static int     pmap_mmap ( struct file *filp, struct vm_area_struct *vma );
static long     pmap_ioctl_unlocked( struct file *filp,
			  unsigned int cmd, unsigned long arg);

/* supported file operations */
static struct file_operations pmap_fops = {
  .owner   = THIS_MODULE,
  .open    = pmap_open,
  .release = pmap_release,
  .mmap    = pmap_mmap,
  .unlocked_ioctl   = pmap_ioctl_unlocked
};

MODULE_LICENSE ("GPL");
MODULE_AUTHOR ("Mondrian Nuessle");
MODULE_DESCRIPTION ("Driver for direct access to physical memory regions");


/* Helper functions for lists and buffers*/
static pmap_map_t* pmap_allocate_empty_buffer(pmap_proc_t* p)
{
  pmap_map_t* buffer;
  buffer=kmalloc(sizeof(pmap_map_t),GFP_KERNEL);
  if (buffer==NULL)
  {
    dev_alert(DEV,"allocation of segment struct failed.\n");
    return NULL;
  }
  buffer->key=next_key++;
  buffer->type=2;
  buffer->size=0;
  buffer->v_address=0;
  buffer->p_address=0;
  return buffer;
}

static pmap_map_t* pmap_allocate_buffer(pmap_proc_t* p)
{
  pmap_map_t* buffer=p->current_buffer;
  
  buffer->v_address = dma_alloc_coherent( &(p->devp->dev), buffer->size,(dma_addr_t *) (&buffer->p_address), GFP_KERNEL);
    if (buffer->v_address  == NULL) {
        dev_alert(DEV,"memory allocation for physical memory segment failed. Requested size: %lx.\n", (long unsigned int)p->current_buffer->size);
        kfree(buffer);
        return NULL;
      }  
  memset((void*)p->current_buffer->v_address, 0,p->current_buffer->size);
  buffer->type=0;
  #ifdef MICEXTOLL
   buffer->p_address=buffer->p_address + micextoll_micbase0;
  #endif
  dev_dbg(DEV,"DMA alloced buffer, v_address is %p\n",buffer->v_address);
  return buffer;
}

static void pmap_free_buffer(pmap_proc_t*p, pmap_map_t* buffer)
{
   dev_dbg(DEV,"Freeing Buffer with physical address %lx, size %lx\n",
                                (unsigned long) buffer->p_address,(unsigned long)buffer->size);
#ifdef MICEXTOLL
   dma_free_coherent(&(p->devp->dev), buffer->size, buffer->v_address,buffer->p_address-micextoll_micbase0);
#else
   dma_free_coherent(&(p->devp->dev), buffer->size, buffer->v_address,buffer->p_address);
#endif
   kfree(buffer);
}


static pmap_map_t *pmap_search_list(pmap_proc_t* p, uint32_t key) {
        pmap_map_t *tmp = NULL;
        struct list_head *pos, *q;
        
        list_for_each_safe(pos, q, &(p->map_list)){
                tmp = list_entry(pos, pmap_map_t, list);
                if(tmp->key == key){
                        return tmp;
                }
        }        
        return NULL;
}

//remove buffer from list and delete buffer itself
static void pmap_delete_map(pmap_proc_t *p, pmap_map_t* buffer) {
 list_del(&(buffer->list));
 if (buffer->type==0)
  pmap_free_buffer(p,buffer);
 else
   kfree(buffer);
}

static void pmap_teardown_map_list(pmap_proc_t *p) {
    struct list_head *pos, *q;
    pmap_map_t *tmp;
    
    if(list_empty(&(p->map_list)) == 0){
         list_for_each_safe(pos, q, &(p->map_list)){
                        tmp = list_entry(pos, pmap_map_t, list);
                        list_del(&(tmp->list));
                        dev_dbg(DEV,"Removing Buffer with physical address %lx, size %lx\n",
                                (unsigned long)tmp->p_address,(unsigned long)tmp->size);

                        //remove the mapping!
                        if (tmp->type==0)
                          pmap_free_buffer(p,tmp);
                        else
                          kfree (tmp);
                }
        }
}    

static int pmap_setup_cdev(void)
{
  int err, devnr;

  /* setup requester first */
  devnr = MKDEV(MAJOR(pmap.devnr), PMAP_MINOR);
  cdev_init(&pmap.cdev, &pmap_fops);
  pmap.cdev.owner = THIS_MODULE;
  pmap.cdev.ops = &pmap_fops;
  err = cdev_add(&pmap.cdev, devnr, 1);
  if (err < 0)
  {
    dev_alert(DEV,"Error %d adding cdev", err);
    cdev_del(&pmap.cdev);
    return err;
  }

  return 0;
}

/* initialization function called during insmod */
static int __init pmap_init_module ( void )
{
  int result=0;
  if (extoll_get_init_done()==0)
  {
    printk(KERN_INFO "EXTOLL Base driver not initialized! Bailing out\n");
    return -1;
  }

  // dynamically allocate major device number and register file operations in kernel tables
  if (alloc_chrdev_region(&pmap.devnr, 0, PMAP_MINOR_COUNT, "pmap")) {
    printk(KERN_ALERT "pmap: No Major Number available!!\n");
    result=-EBUSY;
    goto pmap_open_err_no_major;
  };
      
  pmap.dev=device_create(extoll_get_class_priv(), extoll_get_device(), pmap.devnr, NULL, "pmap");
  if (pmap.dev==NULL) {
     printk(KERN_ALERT"pmap: pmap device creation failed\n");
     result=-EBUSY;
     goto pmap_open_err_register_chrdev;
  }
  
  if (pmap_setup_cdev() < 0)
  {
    printk(KERN_ALERT "pmap: error in pmap_setup_cdev\n");
    result=-EBUSY;
    goto pmap_open_err_device_create;
  }
  return 0;  /*  initialization successful */
 pmap_open_err_device_create:
  device_destroy(extoll_get_class_priv(),pmap.devnr);
 pmap_open_err_register_chrdev:
  unregister_chrdev_region(pmap.devnr, PMAP_MINOR_COUNT);
  printk(KERN_ALERT "pmap: Major requesternumber %x freed \n",
        MAJOR(pmap.devnr));

 pmap_open_err_no_major:
  printk(KERN_ALERT "pmap: no major number available.\n");
  return result;
}

/* cleanup function called during rmmod */
static void __exit pmap_cleanup_module ( void )
{
  if (memory_map_opened!=0)
  {
    printk(KERN_ALERT "pmap: still mapping open!\n");
  }
  
  cdev_del(&pmap.cdev);
      
  DEBUG(printk(KERN_INFO "pmap: unregistering Major %d\n", MAJOR(pmap.devnr));)
  unregister_chrdev_region(pmap.devnr, PMAP_MINOR_COUNT);
  device_destroy(extoll_get_class_priv(),pmap.devnr);  
  printk(KERN_INFO "pmap: remove done!!\n\n");
  
}

/* Handle open of the device. */    
static int pmap_open ( struct inode *inode, struct file *filp )
{
  int minor_nr;
  pmap_proc_t* p;
  pmap_map_t* buffer;
  
  minor_nr = MINOR ( inode->i_rdev ) ;
  dev_dbg(DEV,"Open memorymap minor device. Minor %d\n",minor_nr);
  if ( minor_nr != 0 ) {
    dev_alert(DEV,"Only minor number 0 is valid, but minor %d was requested\n",minor_nr);
    return -ENODEV;
  }
  p=(pmap_proc_t*)kmalloc(sizeof(pmap_proc_t), GFP_KERNEL);
  p->mapped=0;
  p->pid = current->pid;
  INIT_LIST_HEAD(&(p->map_list));
  p->devp=extoll_get_pdev();  
  filp->private_data = p;
  memory_map_opened ++;

  buffer=pmap_allocate_empty_buffer(p);
  list_add(&(buffer->list),&(p->map_list));
  p->current_buffer=buffer;
  
  return 0;
}

/* Handle close of the device. */
static int pmap_release ( struct inode *inode, struct file *filp)
{ 
  int minor_nr;
  pmap_proc_t* p;
  
  memory_map_opened --;
  
  minor_nr = MINOR ( inode->i_rdev ) ;
  if ( minor_nr != 0 ) {     
    dev_alert(DEV,"only minor 0 is valid, but release called with minor %d. Oops, that should never happen\n",minor_nr);
    return -ENODEV;
  }    
  p=filp->private_data;
  if (p==0)
  {
    dev_alert(DEV,"Invalid private data. Oops, that should never happen\n");
    return -ENODEV;
  }
  if (p->mapped!=0) {
    dev_dbg(DEV,"release from PID %d requested, but still memory maps open - will remove them first\n",p->pid);
    pmap_teardown_map_list(p);
  }
  kfree((void *)p);

  dev_dbg(DEV,"device has been released\n" );
  return 0;
}

//static int  pmap_ioctl(struct inode *inodp, struct file *filp,unsigned int cmd, unsigned long arg)
static long  pmap_ioctl_unlocked(struct file *filp,unsigned int cmd, unsigned long arg)
{
  pmap_proc_t* p;
  //int minor;
  p = filp->private_data;

  if (p==NULL) {
    dev_alert(DEV,"ioctl: invalid owner\n");
    return -EFAULT;
  }

  // Do some security tests on the requested command number
  if (_IOC_TYPE(cmd) != PMAP_IOC_MAGIC)
    return -ENOTTY;

  if (_IOC_NR(cmd) > PMAP_IOC_MAXNR)
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
  
   switch (cmd) {
    case (PMAP_IOCTL_GET_PADDR):
    {
     #ifdef MICEXTOLL
       uint64_t value=p->current_buffer->p_address - micextoll_micbase0;
     #else
      uint64_t value=p->current_buffer->p_address;
     #endif

      dev_dbg(DEV,"PMAP_IOCTL_GET_PADDR called. Returning %lx\n",(unsigned long)value);
      return put_user(value, ((uint64_t *) arg));
      break;
    }
    case (PMAP_IOCTL_SET_TYPE):
    {
      p->current_buffer->type=((uint64_t) arg);
      break;
    }
    case (PMAP_IOCTL_GET_TYPE):
    {
      uint64_t value=p->current_buffer->type;
      return put_user(value, ((uint64_t *) arg));
      break;
    }
    case (PMAP_IOCTL_SET_HADDR):
    {
      p->current_buffer->p_address=((uint64_t) arg);
      break;
    }
    case (PMAP_IOCTL_GET_HADDR):
    {
      uint64_t value=p->current_buffer->p_address;
      if (p->current_buffer->type!=1)
      {
	dev_alert(DEV,"trying to get HADDR, but mapping type is not HADDR!\n");
	value=0xffffffffffffffffl;
      }
      return put_user(value, ((uint64_t *) arg));
      break;
    }
    case (PMAP_IOCTL_SET_SIZE):
    {
      dev_dbg(DEV,"setting size to %lx\n",arg);
      p->current_buffer->size=((uint64_t) arg);
      break;
    }
    case (PMAP_IOCTL_GET_SIZE):
    {
      uint64_t value=p->current_buffer->size;
      return put_user(value, ((uint64_t *) arg));
      break;
    }
    case (PMAP_IOCTL_CREATE):
    {
      pmap_map_t* buffer;
      if (p->current_buffer->type!=2) //no empty buffer available as current
      {
        dev_dbg(DEV,"allocate create new buffer\n");
        buffer=pmap_allocate_empty_buffer(p);
        list_add(&(buffer->list),&(p->map_list));
        p->current_buffer=buffer;
      }
      dev_dbg(DEV,"allocate a buffer\n");
      return put_user(p->current_buffer->key,((uint64_t *) arg));
      break;
    }      
    case (PMAP_IOCTL_FREE):
    {
      pmap_map_t* buffer;
      dev_dbg(DEV,"free buffer\n");
      pmap_delete_map(p, p->current_buffer);
      p->mapped--;
      if (list_empty(&(p->map_list))==0) //list not empty -> set current to first entry
      p->current_buffer=list_entry((&(p->map_list))->prev, pmap_map_t, list);
      else {
        buffer=pmap_allocate_empty_buffer(p);
        list_add(&(buffer->list),&(p->map_list));
        p->current_buffer=buffer;
      }
        
      break;
    }      
    case (PMAP_IOCTL_SET_CURRENT):
    {
      uint32_t key=((uint64_t) arg);
      dev_dbg(DEV,"set current buffer to key %d\n",key);
      p->current_buffer=pmap_search_list(p,key);
      if (p->current_buffer==NULL)
        return -EFAULT;
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

/* define supported virtual memory operations */
static int pmap_mmap ( struct file *filp, struct vm_area_struct *vma )
{ 
  pmap_proc_t* p = filp->private_data;
  unsigned long offset = 0;     /* full offset from start of BAR0 */
  unsigned long physical = 0;   /* physical start address */
  unsigned long vsize = 0;      /* size in virtual address space */
  unsigned long psize = 0;      /* size in physical address space */
  pgprot_t page_prot;           /* protection bits for address space */

  offset = vma->vm_pgoff;

  if ( offset != 0 ) { //other offsets not supported
    dev_alert(DEV,"oops wrong offset\n" );
    return -EFAULT;
  }
  if (p->current_buffer->type==0) //memory should be alloced
  {
    dev_dbg(DEV,"mmap, allocate new buffer\n");
    pmap_allocate_buffer(p);
  }
  p->mapped++;
  physical = p->current_buffer->p_address;  //physical address of memory region to be mapped into user space
#ifdef MICEXTOLL
  physical=physical-micextoll_micbase0;
#endif
  dev_dbg(DEV,"mmaping buffer with physical address %lx\n",physical);
  vsize = vma->vm_end - vma->vm_start;
  psize = vsize;
  
  if (psize!=p->current_buffer->size)
  {
    dev_alert(DEV,"requested size does not match size of memory region. Please use a size of %lx instead of %lx\n",
	   (unsigned long)p->current_buffer->size,(unsigned long)psize);
    return -EFAULT;
  }
  
  if ( vsize % 4096 != 0 ) {
    dev_alert(DEV,"Wrong size. Use multiples of 4kB.\n" );
    return -EFAULT;      
  } 
     
  if ( en_write_combining != 0 ) {
    page_prot = __pgprot ( pgprot_val (vma->vm_page_prot) | EXTOLLWCATTR );
  } else {
    
    // Use this pgprot in order to allow mapping with (write-back) caching
    page_prot = __pgprot ( pgprot_val ( vma->vm_page_prot ) | EXTOLLWBATTR ); 
  }
 
  // USE IO REMAPPING FUNCTION if enabled
  if (en_ioremap)
  {
    io_remap_pfn_range ( vma, vma->vm_start, physical >> PAGE_SHIFT, vsize , page_prot ); 
  }
  else
  {
    remap_pfn_range(vma, vma->vm_start ,physical >> PAGE_SHIFT,vsize , page_prot); 		
  }
  return 0;
}

module_init ( pmap_init_module );
module_exit ( pmap_cleanup_module );
