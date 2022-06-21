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

/* This file contains the Buffer Queue (BQ) driver */
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include "arch_define.h"

//linux kernel includes
#include <linux/fs.h>
#ifdef MICEXTOLL
  #include "micextoll.h"
#endif
#include <linux/pci.h>
#include <linux/list.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/pagemap.h>
#include <asm/page.h>
#ifndef LS3BEXTOLL
#include <asm/mtrr.h>
#endif

#include <asm/uaccess.h>

//extoll2 driver includes
#include "extoll_kernel.h"
#include "extolldrv.h"
#include "extoll_rf_sysfs.h"
#include "extoll_bq.h"

//comment to add additional output
#define DEBUG(a)
//#define DEBUG(a) a

int bq_encode_slot_size(int slot_size)
{
	uint32_t result;
    switch (slot_size) {
	case 16: {
	  result=0l; 
	  break;
	}
	case 32: {
	  result=1l; 
	  break;
	}
	case 64: {
	  result=2l; 
	  break;
	}
	case 128: {
	 result=3l; 
	  break;
	}
	default: {
	  pr_alert("Illegal slot_size used in BQ, undefined results may occur.\n");
	  result=0l;
	}
  }
  return result;
}

//allocates memory and fills the given bqd with a memory segment of size
int fill_bqd_struct(struct bq_descriptor* d, uint64_t size, int vpid, int slot_size)
{
#ifdef MICEXTOLL
  struct micextoll_device *devp;
#else
  struct pci_dev *devp;
#endif
  int result=0;
  uint64_t segment_size;
  uint64_t base_address;

  if ( ((size % slot_size) !=0) || ((size % PAGE_SIZE)!=0) )
  {       
    pr_alert("EXTOLL BQ: size of segment is not a valid (size=%lu slot_size=%lu page_size %lu).\n", (long unsigned int)size, (long unsigned int)slot_size,PAGE_SIZE);
    result=-EINVAL;
    goto exit;
  }

  devp=extoll_get_pdev();
  d->u_v_addr=0;
  d->size=size;
  
  pr_debug("in fill_bqd_struct. size requested is %lx, slot_size is %d, vpid is %d\n",(unsigned long)size,slot_size, vpid);
  d->k_v_addr = dma_alloc_coherent( &devp->dev, size,(dma_addr_t *) (&d->ph_addr), GFP_KERNEL);
  if (d->k_v_addr == NULL) {
        pr_alert("EXTOLL BQ: memory allocation for Buffer Queue Segment of size %lu on behalf of vpid %u failed.\n", (long unsigned int)size, (unsigned int)vpid);
        result=-ENOMEM;
		goto exit;
      }
  memset((void*)d->k_v_addr, 0,size);      
  
  pr_debug("fill_bqd_struct: got a physical address of %lx and a virtual of %p\n",d->ph_addr,d->k_v_addr);
#ifdef MICEXTOLL
   d->ph_addr=d->ph_addr + micextoll_micbase0;
#endif
  //build entry now
  //set slot size field (lowest two bits) first
  d->bde=bq_encode_slot_size(slot_size);
  //set segment size (its in slots!) -> subtract one to account for coding 0==1
  segment_size= (size/slot_size)-1;
  segment_size=segment_size << 2l; //account for bit position
  base_address=d->ph_addr>>12l; //remove 12 lowest bits
  if ( (base_address & 0x0000000000l)!=0 ) //check that only 52 bits of the physical address are used
  {
	 pr_alert("memory allocation for Buffer Queue Segment of size %lu on behalf of vpid %u returned physical address that ist too large %lx.\n", 
			(long unsigned int)size, vpid,d->ph_addr );
         result=-ENOMEM;
	 goto exit_free;
  }
  pr_debug("fill_bqd_struct: calculated base address is %lx, encoded slot size is %lx, segment size (in slots, shifted two bits to the left, subtracted) is %lx\n",
		  (long unsigned int)base_address,(long unsigned int)d->bde,(long unsigned int) segment_size);
  base_address=base_address<<18l; //move to the right bit position
  d->bde= base_address | segment_size | d->bde; //and "or" it all together
  pr_debug("fill_bqd_struct: calculated bde is %lx and function is done.\n",(long unsigned int)d->bde);
  goto exit;
 exit_free:
    dma_free_coherent(&devp->dev,size,(void*)d->k_v_addr,(dma_addr_t) d->ph_addr);
 exit:
  return result;
}
//free a given bqd again
int destroy_bqd_struct(struct bq_descriptor* d)
{
#ifdef MICEXTOLL
  struct micextoll_device *devp;
#else
  struct pci_dev *devp;
#endif
  devp= extoll_get_pdev();
  dma_free_coherent(&devp->dev,d->size,(void*)d->k_v_addr,(dma_addr_t) d->ph_addr);
  return 0;
}


static int __init bq_init(void)
{
  int i;
  //init the buffer queue stuff
  pr_debug("bq: bq init called\n");
  
  if (extoll_get_init_done()==0)
  {
    pr_alert("EXTOLL Base driver not initialized! Bailing out\n");
    return -1;
  }
  //for velo bq
  for (i=0;i<BQ_MAX_QUEUE_NUMBER;i++)
  {
    // write ub to zero
	set_extoll_rf_buffer_queue_rf_velo_ub(i, 0l);
    // write dcq_base and dcq_ub to zero
	set_extoll_rf_buffer_queue_rf_velo_dcq_base_dcq_ub(i, 0l);
    // set c_base_size_valid to zero
	set_extoll_rf_buffer_queue_rf_velo_c_base_size_valid(i, 0l);
    //n_base_size_valid to zero
	set_extoll_rf_buffer_queue_rf_velo_n_base_size_valid(i, 0l);
    //wp_lwp_dcqrp to zero
	set_extoll_rf_buffer_queue_rf_velo_wp_lwp_dcq_rp(i, 0l);
    //rp to zero 
	set_extoll_rf_buffer_queue_rf_velo_rp(i, 0x00000000l);
  }
  //for rma bq
  for (i=0;i<BQ_MAX_QUEUE_NUMBER;i++)
  {
    // write ub to zero
	set_extoll_rf_buffer_queue_rf_rma_ub(i, 0l);
    // write dcq_base and dcq_ub to zero
	set_extoll_rf_buffer_queue_rf_rma_dcq_base_dcq_ub(i, 0l);
    // set c_base_size_valid to zero
	set_extoll_rf_buffer_queue_rf_rma_c_base_size_valid(i, 0l);
    //n_base_size_valid to zero
	set_extoll_rf_buffer_queue_rf_rma_n_base_size_valid(i, 0l);
    //qp_lqp_dcq_rp to zero
	set_extoll_rf_buffer_queue_rf_rma_wp_lwp_dcq_rp(i, 0l);
    //rp to zero
	set_extoll_rf_buffer_queue_rf_rma_rp(i, 0x00000000l);
  }
  //write to general register -> set the enable bit!
  bq_activate_bq(VELO_BQ);
  bq_activate_bq(RMA_BQ);
  return 0;
}

static void bq_finalize(void)
{
  bq_deactivate_bq(VELO_BQ);
  bq_deactivate_bq(RMA_BQ);
}
EXPORT_SYMBOL(bq_finalize);

extoll_bq_t* bq_init_queue(uint64_t size, int unit_flag, int vpid,int slot_size, int desc_size,int* return_value)
{ //size is the desired mailbox size in bytes
  // must be a multiple of 4KB
  //flag decides wheter it is VELO or RMA!
  //vpid decides which VPID is used
#ifdef MICEXTOLL
  struct micextoll_device *devp;
#else
  struct pci_dev *devp;
#endif
  uint32_t num_descriptors;
  extoll_bq_t* bq=0;
  struct bq_descriptor* descs;
  int i;
  int  result=0;
  int last_segment_size;
  uint32_t upper_bound;
//   long int locked=0;
//   long int lock_limit=0;
//   
  devp= extoll_get_pdev();
  //allocate struct and fill with zero
  
  pr_debug("called bq_init_queue with: size %llu, slot_size %i, desc_sise %i\n", size, slot_size, desc_size);

  bq=kmalloc(sizeof(extoll_bq_t), GFP_KERNEL);
  if (bq==0)
  {
	pr_alert("memory allocation extoll_bq_t on behalf of vpid %d failed.\n",vpid);
	result=-ENOMEM;
	goto exit;
  }
  memset((void*)bq, 0,sizeof(extoll_bq_t));  
  if (desc_size!=0)
	bq->desc_size=desc_size;
  else
	bq->desc_size=_BQ_DEFAULT_DESC_SIZE;
   
  num_descriptors=size / bq->desc_size;
  last_segment_size=size  % bq->desc_size;
  if ( last_segment_size != 0 ) {
	num_descriptors++;
  } else {
	last_segment_size=bq->desc_size;
  }
  if (unit_flag==VELO_BQ)
  {
    pr_debug("Setting up queue for VELO2. Requested size %lx, num_descriptors is therefore %d, last_segment size is %d\n",(unsigned long int)size, num_descriptors,last_segment_size);
  }
  else
  {
    pr_debug("Setting up queue for RMA2. Requested size %lx, num_descriptors is therefore %d, last_segment size is %d\n",(unsigned long int)size, num_descriptors,last_segment_size);
  }
  if (num_descriptors>BQ_MAX_SEGMENTS)
  {
	pr_alert("requested size %lu on behalf of vpid %d is larger than allowed using  maximum number of %d segments of size %ld. Consider increasing segment size.\n",
		   (unsigned long int) size,vpid,num_descriptors,(unsigned long)bq->desc_size);
	result=-EINVAL;
 	goto exit;
  }
 
  //set the fields of the struct
  bq->unit_flag=unit_flag;
  bq->slot_size=slot_size;
  bq->vpid=vpid;
  bq->size=size;
  bq->current_descriptor = 0;
  bq->current_slot = 0;
  bq->outstanding_updates = 0;
  
  if (bq->unit_flag==VELO_BQ)
    bq->rp_physical_address=extoll_get_rf_addr()+ VELO_RP_OFFSET+vpid*4096;
  else
    bq->rp_physical_address=extoll_get_rf_addr()+ RMA_RP_OFFSET+vpid*4096;
  pr_debug("rf address is %lx, therefore rp address is %lx\n",extoll_get_rf_addr(),(long unsigned int) bq->rp_physical_address);
  //allocate logical descriptor queue and set number of entries
  descs=kmalloc(sizeof(struct bq_descriptor) * num_descriptors, GFP_KERNEL);
  if (descs==0)
  {
	pr_alert("memory allocation bq_descriptors failed on behalf of vpid %d failed.\n",vpid);
	result=-ENOMEM;
	goto exit_free_bq;
  }
  memset((void*)descs, 0,sizeof(struct bq_descriptor) * num_descriptors);   
  //set the individual entries
  for (i=0;i<num_descriptors-1;i++)
  {
	result=fill_bqd_struct(&(descs[i]), bq->desc_size, vpid,slot_size);
	if (result!=0) {
	  bq->no_of_entries=i;
	  result=-ENOMEM;
	  goto exit_free_descs;
	}
  }
  result=fill_bqd_struct(&(descs[i]), last_segment_size, vpid, slot_size);
  if (result!=0) {
	  bq->no_of_entries=i;
	  result=-ENOMEM;
	  goto exit_free_descs;
	}
  bq->descs=descs;
  bq->no_of_entries=i+1;
  
  //allocate physical descriptor queue and set number of entries, allocate exactly one page
  bq->virtual_address = dma_alloc_coherent( &devp->dev, /*DCQ_SIZE*/ PAGE_SIZE,(dma_addr_t *) & bq->physical_address, GFP_KERNEL);
  if (bq->virtual_address == NULL) {
        pr_alert("memory allocation for Buffer Queue Descriptor physical representation on behalf of vpid %u failed.\n",vpid);
        result=-ENOMEM;
		goto exit_free_descs;
  }
  pr_debug("descriptor table allocated at physical %lx, virtual %p\n",bq->physical_address,bq->virtual_address);

#ifdef MICEXTOLL
  bq->physical_address =bq->physical_address + micextoll_micbase0;
  pr_debug("added %lx to the physical address to account for MIC bar. Physical is now %lx\n",micextoll_micbase0,bq->physical_address);
#endif

  memset((void*)bq->virtual_address, 0,DCQ_SIZE);      
  //copy entries from logical to physical representation
  for (i=0;i<bq->no_of_entries;i++)
  {
	bq->virtual_address[i]=bq->descs[i].bde;
	pr_debug("setting desc #%d to %lx\n",i,(long unsigned)bq->virtual_address[i]);
  }

  //write extoll_rf->bq_rf->bq_rf_XYZ.ub -> upper bound of the queue, i.e. size
  //32 bits: ub, 1 bit tph_e, 2bit tph_hint, then stag -> all unused except size
  upper_bound= ( size/slot_size) -1;
 
  
  if (bq->unit_flag==VELO_BQ)
  {
	pr_debug("velo upper bound of the BQ is %x, size is %lx, slot_size is %d\n", upper_bound, (long unsigned) size, slot_size);
	set_extoll_rf_buffer_queue_rf_velo_ub(vpid, upper_bound & 0xffffffffl);
	// write dcq_base and dcq ub: get from descriptor queue above
	if (num_descriptors<1 || num_descriptors>64*1024+1)
	{
	  pr_alert("velo Oh num_descriptors out of range (%u).\n",num_descriptors);
	  set_extoll_rf_buffer_queue_rf_velo_ub(vpid, 0);
	  goto exit_free_descs;
	}
	set_extoll_rf_buffer_queue_rf_velo_dcq_base_dcq_ub(vpid, ( (bq->physical_address & 0x000ffffffffff000l)<<4l) | (num_descriptors-1));
	pr_debug("velo set dcq_base_dcq_ub reg to %lx, bq->physical is %lx and there %u descriptors\n", 
		  ( (bq->physical_address & 0x000ffffffffff000l)<<4l) | (num_descriptors-1), bq->physical_address,num_descriptors);
	// wrte wp_lpw_dcq_rp set to zero,for the start all pointers should be zero
	// if we have more than two segments, two segments are already loaded into register, so the readpointer must be set to 2, otherwise this pointer must also be zero!
	if (num_descriptors<3)
	  set_extoll_rf_buffer_queue_rf_velo_wp_lwp_dcq_rp(vpid, 0l);
	else
	  set_extoll_rf_buffer_queue_rf_velo_wp_lwp_dcq_rp(vpid, 2l);
	// rp to zero and retrigger interrupts (if they were masked until now)
	set_extoll_rf_buffer_queue_rf_velo_rp(vpid, 0x100000000l);
  
	// set the current entry to the first descriptor (n_base_size_valid)
	set_extoll_rf_buffer_queue_rf_velo_c_base_size_valid(vpid, BQ_ENTRY_VALID | bq->virtual_address[0]);
	pr_debug("velo Set current reg to %lx\n",(long unsigned) (BQ_ENTRY_VALID | bq->virtual_address[0]));
	// set next entry to the second descriptor or the first if only one descriptor active (c_base_size_valid)   
	if (num_descriptors>1)
	{
	  set_extoll_rf_buffer_queue_rf_velo_n_base_size_valid(vpid, BQ_ENTRY_VALID |bq->virtual_address[1]);
	  pr_debug("velo Set next reg to %lx\n",(long unsigned)(BQ_ENTRY_VALID |bq->virtual_address[1]));
	}
	else
	{
	  set_extoll_rf_buffer_queue_rf_velo_n_base_size_valid(vpid, BQ_ENTRY_VALID |bq->virtual_address[0]);
	  pr_debug("velo Set next reg to to current reg, to %lx\n",(long unsigned)(BQ_ENTRY_VALID |bq->virtual_address[0]));
	}
  }
  else
  {
	set_extoll_rf_buffer_queue_rf_rma_ub(vpid, upper_bound & 0xffffffffl);
	// write dcq_base and dcq ub: get from descriptor queue above
	if (num_descriptors<1 || num_descriptors>64*1024+1)
	{
	  pr_debug("rma Oh num_descriptors out of range (%u).\n",num_descriptors);
	  set_extoll_rf_buffer_queue_rf_rma_ub(vpid, 0);
	  goto exit_free_descs;
	}
	set_extoll_rf_buffer_queue_rf_rma_dcq_base_dcq_ub(vpid, ( (bq->physical_address & 0x000ffffffffff000l)<<4l) | (num_descriptors-1));
	pr_debug("rma set dcq_base_dcq_ub reg to %lx, bq->physical is %lx and there %u descriptors\n", 
		  ( (bq->physical_address & 0x000ffffffffff000l)<<4l) | (num_descriptors-1), bq->physical_address,num_descriptors); 
	// wrte wp_lpw_dcq_rp set to zero,for the start all pointers should be zero
	// if we have more than two segments, two segments are already loaded into register, so the readpointer must be set to 2, otherwise this pointer must also be zero!
	if (num_descriptors<3)
	  set_extoll_rf_buffer_queue_rf_rma_wp_lwp_dcq_rp(vpid, 0l);
	else
	  set_extoll_rf_buffer_queue_rf_rma_wp_lwp_dcq_rp(vpid, 2l);
	// rp to zero and retrigger interrupts (if they were masked until now)
	set_extoll_rf_buffer_queue_rf_rma_rp(vpid, 0x100000000l);
  
	// set the current entry to the first descriptor (n_base_size_valid)
	set_extoll_rf_buffer_queue_rf_rma_c_base_size_valid(vpid, BQ_ENTRY_VALID | bq->virtual_address[0]);
	pr_debug("rma Set current reg to %lx\n",(long unsigned)(BQ_ENTRY_VALID | bq->virtual_address[0]));
	// set next entry to the second descriptor or the first if only one descriptor active (c_base_size_valid)   
	if (num_descriptors>0)
	{
	  set_extoll_rf_buffer_queue_rf_rma_n_base_size_valid(vpid, BQ_ENTRY_VALID |bq->virtual_address[1]);
	  pr_debug("rma Set next reg to %lx\n",(long unsigned)(BQ_ENTRY_VALID |bq->virtual_address[1]));
	}
	else
	{
	  set_extoll_rf_buffer_queue_rf_rma_n_base_size_valid(vpid, BQ_ENTRY_VALID |bq->virtual_address[0]);
	  pr_debug("rma Set next reg to to current reg, to %lx\n",(long unsigned)(BQ_ENTRY_VALID |bq->virtual_address[0]));
	}
  }
//   down_read(&current->mm->mmap_sem);
//   current->mm->locked_vm += (bq->size / PAGE_SIZE);
//   up_read(&current->mm->mmap_sem);

 bq->status_word = bq->descs[0].k_v_addr + bq->slot_size - sizeof(uint64_t);
 pr_debug("status word set to :%p\n", bq->status_word);
  
 goto exit;

 exit_free_descs:
  for (i=0;i<bq->no_of_entries;i++)
	destroy_bqd_struct(&(bq->descs[i]));
  kfree(descs);
 exit_free_bq:
  kfree(bq);
  bq=0;
 exit:
  pr_debug("finshed bq setup with slot size %i, first descriptor at %p and first status word at %p\n",slot_size, bq->descs[0].k_v_addr, bq->status_word);
  *return_value=result;
  return bq;
}
EXPORT_SYMBOL(bq_init_queue);

int bq_destroy_queue(extoll_bq_t* queue)
{
#ifdef MICEXTOLL
    struct micextoll_device *devp;
#else
    struct pci_dev *devp;
#endif
    int i;
	
    devp= extoll_get_pdev();
    pr_debug("bq_destroy_queue, setting regs to 0 first\n");
    pr_debug("returning locked pages... %lu\n",(unsigned long)(queue->size / PAGE_SIZE));

    // write ub to zero
    // write dcq_base and dcq_ub to zero
    // set c_base_size_valid to zero
    //n_base_size_valid to zero
    //qp_lqp_dcq_rp to zero
    //rp to zero
    if (queue->unit_flag==VELO_BQ)
    {
	  // write ub to zero
	  set_extoll_rf_buffer_queue_rf_velo_ub(queue->vpid, 0l);
	  // write dcq_base and dcq_ub to zero
	  set_extoll_rf_buffer_queue_rf_velo_dcq_base_dcq_ub(queue->vpid, 0l);
	  // set c_base_size_valid to zero
	  set_extoll_rf_buffer_queue_rf_velo_c_base_size_valid(queue->vpid, 0l);
	  //n_base_size_valid to zero
	  set_extoll_rf_buffer_queue_rf_velo_n_base_size_valid(queue->vpid, 0l);
	  //wp_lwp_dcqrp to zero
	  set_extoll_rf_buffer_queue_rf_velo_wp_lwp_dcq_rp(queue->vpid, 0l);
	  //rp to zero
	  set_extoll_rf_buffer_queue_rf_velo_rp(queue->vpid, 0l);
    }
    else
    {
	  // write ub to zero
	  set_extoll_rf_buffer_queue_rf_rma_ub(queue->vpid, 0l);
	  // write dcq_base and dcq_ub to zero
	  set_extoll_rf_buffer_queue_rf_rma_dcq_base_dcq_ub(queue->vpid, 0l);
	  // set c_base_size_valid to zero
	  set_extoll_rf_buffer_queue_rf_rma_c_base_size_valid(queue->vpid, 0l);
	  //n_base_size_valid to zero
	  set_extoll_rf_buffer_queue_rf_rma_n_base_size_valid(queue->vpid, 0l);
	  //qp_lqp_dcq_rp to zero
	  set_extoll_rf_buffer_queue_rf_rma_wp_lwp_dcq_rp(queue->vpid, 0l);
	  //rp to zero
	  set_extoll_rf_buffer_queue_rf_rma_rp(queue->vpid, 0l);
    }
	
    //free all memory
    pr_debug("freeing descriptor queue\n");
    dma_free_coherent(&devp->dev,DCQ_SIZE,(void*) queue->virtual_address,(dma_addr_t) queue->physical_address);
    pr_debug("now freing %d segments\n",queue->no_of_entries);
    for (i=0;i<queue->no_of_entries;i++)
      destroy_bqd_struct(&(queue->descs[i]));	
      kfree(queue->descs);
      kfree(queue);
      pr_debug("bq_destroy_queue done\n");
      return 0;
}
EXPORT_SYMBOL(bq_destroy_queue);


void bq_activate_bq(int unit_flag)
{
 uint64_t value;
 if (unit_flag==VELO_BQ)
  value=get_extoll_rf_buffer_queue_rf_velo_general();
 else
    value=get_extoll_rf_buffer_queue_rf_rma_general();
 
 value=value | 1l;
 
 if (unit_flag==VELO_BQ)
 {
  pr_debug("activating velo bq\n");
  set_extoll_rf_buffer_queue_rf_velo_general(value);
 }
 else
 {
  pr_debug("activating RMA bq\n");
  set_extoll_rf_buffer_queue_rf_rma_general(value);
 }
 
}
EXPORT_SYMBOL(bq_activate_bq);

void bq_deactivate_bq(int unit_flag)
{
 uint64_t value;
 if (unit_flag==VELO_BQ)
  value=get_extoll_rf_buffer_queue_rf_velo_general();
 else
    value=get_extoll_rf_buffer_queue_rf_rma_general();
 
 value=value & 0xfffffffffffffffel;
 
 if (unit_flag==VELO_BQ)
  set_extoll_rf_buffer_queue_rf_velo_general(value);
 else
    set_extoll_rf_buffer_queue_rf_rma_general(value);
    
}
EXPORT_SYMBOL(bq_deactivate_bq);

//called to mmap one queue into user space!
int bq_mmap(struct vm_area_struct *vma,extoll_bq_t* queue )
{
#ifdef MICEXTOLL
   struct micextoll_device *devp;
#else
   struct pci_dev *devp;        // part of struct pci_dev
#endif
  unsigned long vsize = 0;	// size in virtual address space
  unsigned long physical = 0; // physical start address
  unsigned long pfn;  // page frame numbera
  pgprot_t page_prot;
  uint32_t dma_offset;
  int i;
  int vpid;
  uint64_t size;
  uint64_t vpids_per_page;
  
  devp= extoll_get_pdev();
  vsize = vma->vm_end - vma->vm_start;
  vpid=queue->vpid;
  
  vpids_per_page=extoll_query_vpids_per_page();
  //check vpid
  if (vpid % vpids_per_page !=0)
  {
    pr_alert("vpid %d is not aligned to page size %ld of this machine. Not supported\n",vpid, PAGE_SIZE);
    return -EINVAL;
  }
  //check sizes
  if (vsize != (queue->size) + PAGE_SIZE) //must be equal or less to dma size plus one page for the read pointer
  {
    pr_alert("mmap of BQ failed on behalf of vpid %d, reason: invalid size %lx (should be %lx).\n",vpid,vsize,(long unsigned int)(queue->size) + PAGE_SIZE);
    return -EINVAL;	// spans too high
  }
  if (queue->virtual_address == NULL) {
    pr_alert("mmap of BQ failed on behalf of vpid %d, reason: no queue mapped in kernel.\n",vpid);
    return -EINVAL;
  }
  
  //get the address of the read_pointer for this queue
  physical = queue->rp_physical_address;
  pfn = physical >> PAGE_SHIFT;
  pr_debug("mapping read-pointer from physical address %lx into user space on behalf of vpid %d to virtual address %lx\n",physical,vpid,vma->vm_start);
  
  page_prot = pgprot_noncached( vma->vm_page_prot );
  io_remap_pfn_range(vma, vma->vm_start, pfn, PAGE_SIZE,page_prot);
  pr_debug("mapping read-pointer from physical address %lx into user space on behalf of vpid %d done\n",physical,vpid);

  //now map the actual mailbox region(s)
  dma_offset=0;
  pr_debug("now mapping individual queue segments into user space\n");
  for (i=0;i<queue->no_of_entries;i++)
  {
	pr_debug("segment %d, physical addr is %lx, size is %lx mapped at vma offset %lx\n",i,queue->descs[i].ph_addr,queue->descs[i].size,dma_offset+PAGE_SIZE);
#ifdef MICEXTOLL
        physical=queue->descs[i].ph_addr - micextoll_micbase0;
        pr_debug("mmaping, physical queue address was %lx After mic bar accouting it is now %lx\n",queue->descs[i].ph_addr, physical);
#else
        physical=queue->descs[i].ph_addr;
#endif
	pfn = physical >> PAGE_SHIFT;
	size=queue->descs[i].size;
	remap_pfn_range(vma, vma->vm_start + PAGE_SIZE +dma_offset ,pfn,size , vma->vm_page_prot); 
	dma_offset=dma_offset+queue->descs[i].size;
  }
  pr_debug("remapped DMA area complete.\n");
  
  return 0;
}
EXPORT_SYMBOL(bq_mmap);

uint64_t bq_get_lrp(extoll_bq_t* queue)
{
  if (queue->unit_flag==VELO_BQ)
   return get_extoll_rf_buffer_queue_rf_velo_rp(queue->vpid);
  else
   return get_extoll_rf_buffer_queue_rf_rma_rp(queue->vpid);
}
EXPORT_SYMBOL(bq_get_lrp);

void bq_set_lrp(extoll_bq_t* queue,uint64_t lrp)
{
 if (queue->unit_flag==VELO_BQ)
  set_extoll_rf_buffer_queue_rf_velo_rp(queue->vpid, lrp);
 else
    set_extoll_rf_buffer_queue_rf_rma_rp(queue->vpid, lrp);
}
EXPORT_SYMBOL(bq_set_lrp);

uint64_t bq_get_lwp(extoll_bq_t* queue)
{
 uint64_t value;
 if (queue->unit_flag==VELO_BQ)
   value=get_extoll_rf_buffer_queue_rf_velo_wp_lwp_dcq_rp(queue->vpid);
 else
   value=get_extoll_rf_buffer_queue_rf_rma_wp_lwp_dcq_rp(queue->vpid);
 value=value & 0xffffffff00000000l;
 value=value >> 32l;
 return value;
}
EXPORT_SYMBOL(bq_get_lwp);

void bq_set_lwp(extoll_bq_t* queue,uint64_t lwp)
{
 uint64_t value;
 if (queue->unit_flag==VELO_BQ)
   value=get_extoll_rf_buffer_queue_rf_velo_wp_lwp_dcq_rp(queue->vpid);
 else
   value=get_extoll_rf_buffer_queue_rf_rma_wp_lwp_dcq_rp(queue->vpid);

 value = value & 0xffffffffl;
 value = value | (lwp<<32l);
 
 if (queue->unit_flag==VELO_BQ)
  set_extoll_rf_buffer_queue_rf_velo_wp_lwp_dcq_rp(queue->vpid, value);
 else
  set_extoll_rf_buffer_queue_rf_rma_wp_lwp_dcq_rp(queue->vpid, value);
}
EXPORT_SYMBOL(bq_set_lwp);

uint64_t bq_get_desc_size(extoll_bq_t* queue){
  return queue->desc_size;
}
EXPORT_SYMBOL(bq_get_desc_size);

void bq_set_desc_size(extoll_bq_t* queue,uint64_t size){
  queue->desc_size=size;
}
EXPORT_SYMBOL(bq_set_desc_size);

int bq_read_slot_inc_rp(extoll_bq_t *bq)
{
  // here: unify the read methods of rma and velo, using only the informations given in the extoll_bq
  // maybe give a pointer to a counter in a handle...  
  // or expand the extoll_bq with a counter for the descritpor and the read bytes/slots
  
  unsigned long desc_size = bq->descs[bq->current_descriptor].size;
  
  bq->current_slot += 1;
  bq->outstanding_updates++;
  *(bq->status_word) = 0l; //npe here, should be resolved now

  if(unlikely(bq->current_slot >= desc_size/bq->slot_size)) {
    bq->current_descriptor = (bq->current_descriptor+1)%bq->no_of_entries;
    pr_debug("changed to next descriptor (%i of %i)\n", bq->current_descriptor+1, bq->no_of_entries);
    bq->current_slot = 0;
    //-> moved to commit to hw method; bq_set_lrp(bq, ((((uint64_t)update_irq) & 0x1l) <<32l) | 0l);
    bq->status_word = bq->descs[bq->current_descriptor].k_v_addr + bq->slot_size-sizeof(uint64_t);
    pr_debug("descritpor starts at: %p, status word: %p\n", bq->descs[bq->current_descriptor].k_v_addr, bq->status_word);
  } else {
    bq->status_word += (bq->slot_size)>>3; 
    pr_debug("increment of status-word: %i\n", (bq->slot_size)>>3);
    //-> moved to commit to hw method; if(unlikely(bq->current_slot%8 == 0) || update_irq!=0) { //update every 8 reads the hardware readpointer
      //-> moved to commit to hw method; bq_set_lrp(bq, ((((uint64_t)update_irq) & 0x1l) <<32l) | bq->current_slot);
    //-> moved to commit to hw method; }
  }
  return bq->outstanding_updates;
}
EXPORT_SYMBOL(bq_read_slot_inc_rp);

void bq_read_slot_commit_rp(extoll_bq_t *bq, int update_irq)
{
  pr_debug("commited rp of %lu\n",bq->current_slot);
  bq_set_lrp(bq, ((((uint64_t)update_irq) & 0x1l) <<32l) | bq->current_slot);
  bq->outstanding_updates=0; //rp updates have been committed, reset counter variable
}
EXPORT_SYMBOL(bq_read_slot_commit_rp);

uint64_t* bq_get_status_word(extoll_bq_t *bq)
{
  return bq->status_word;
}
EXPORT_SYMBOL(bq_get_status_word);

uint64_t* bq_get_current_slot(extoll_bq_t* bq)
{
  return ((bq->status_word))-((bq->slot_size)>>3)+1;
}
EXPORT_SYMBOL(bq_get_current_slot);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mondrian Nuessle mondrian.nuessle@extoll.de");
MODULE_DESCRIPTION("Extoll: BQ driver");
MODULE_VERSION("1.1");

module_init(bq_init);
module_exit(bq_finalize);
