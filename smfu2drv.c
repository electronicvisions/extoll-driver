
	/*
	 *  This file is part of the  Linux SMFU2 Package for EXTOLL R2.
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
	#include <linux/signal.h>
	#ifndef LS3BEXTOLL
	#include <asm/mtrr.h>
	#endif

	#include <asm/uaccess.h>
	#include <linux/list.h>

	#include "extoll_kernel.h"
	#include "extolldrv.h"
	#include "extoll_rf_sysfs.h"
	#include "smfu2drv.h"
	#include "smfu2_ioctl.h"

	#include "snq_decl.h"
	#include "extoll_kernel_version_compability_layer.h"

	// set this define to 1 if a list of PIDs that have SMFU opened should be maintained
	#define MAINTAIN_PID_LIST 0
	
	#define DEV smfu2.dev

	/******************************************************************************
	 *  Global Variables			   				      *
	 ******************************************************************************/
	static struct smfu2_device smfu2; 
	static unsigned int smfu2_opened = 0; // is device already opened
	static int smfu2_en_write_combining = 1; // mmap with write combining or not
#if 0
	static int smfu2_en_emmio = 0;
#endif
	static char* smfu2_target_mem_start = "0xFFFFFFFFFFFFFFFF";
	static char* smfu2_target_mem_size = "0xFFFFFFFFFFFFFFFF";
	static char* smfu2_global_mem_size = "0x00";
	static unsigned long int smfu2_target_mem_start_val = 0xFFFFFFFFFFFFFFFF;
	static unsigned long int smfu2_target_mem_size_val = 0xFFFFFFFFFFFFFFFF;
	static unsigned long int smfu2_global_mem_size_val = 0x00;
	static bool smfu2_timeout_response = false;
#if 0
	static char* smfu2_intervals = "";
#endif
	static int smfu2_mtrr_number = -1;

	static struct list_head pids;


	/******************************************************************************
	 *  module parameters (could be set at loadtime)			              *
	 ******************************************************************************/
	// enable write-combining (will prevent cachable mappings)
	module_param ( smfu2_en_write_combining, uint,  S_IRUGO ); 
	MODULE_PARM_DESC ( smfu2_en_write_combining, "Enable write combining. No write combining means write-back");

#if 0
	// use emmio mapping and configure machine accordingly
	module_param ( smfu2_en_emmio, uint, S_IRUGO );
	MODULE_PARM_DESC ( smfu2_en_emmio, "Enable EMMIO");
#endif
	// provide start and size of exported global memory. If not provided, will 
	// allocate 4M of exported memory within the driver
	module_param ( smfu2_target_mem_start,   charp, S_IRUGO ); 
	MODULE_PARM_DESC ( smfu2_target_mem_start, "Start address of local memory to share");
	module_param ( smfu2_target_mem_size,    charp, S_IRUGO );
	MODULE_PARM_DESC ( smfu2_target_mem_size, "Size of local memory to share");
	module_param ( smfu2_global_mem_size,    charp, S_IRUGO );
	MODULE_PARM_DESC ( smfu2_global_mem_size, "Size of global memory, used to detect bad mmaps");
#if 0
	module_param ( smfu2_intervals, charp, S_IRUGO );
	MODULE_PARM_DESC ( smfu2_intervals, "List of intervals, format: <nodeid>:<size of interval>[, <nodeid>:<size of interval>] . Example: 01:2M,02:2M" );
#endif

	//error response
	module_param ( smfu2_timeout_response, bool, S_IRUGO );
	MODULE_PARM_DESC ( smfu2_timout_response, "Determines if error response should be sent on timeout");

	/******************************************************************************
	 *  Registerfile access			   				      *
	 ******************************************************************************/


	/******************************************************************************
	 *  Manage concurrent access to global lists   				      *
	 ******************************************************************************/
	/* in the early version of this driver a more coarse grain synchronization
	 * is implemented. The policy for using this driver wide mutex is as follows:
	 * all entry functions of this driver module have to take care of correct 
	 * locking / synchronization, so that a helper/internal functions do not have
	 * to care about this mutex. This first and simple policy should preserve 
 * race conditions and deadlocks.
 *
 * Later a more fine grain locking could be realized. The author has marked 
 * potentially critical sections with respective "TODO:" markers
 */
//DECLARE_MUTEX ( smfu2_mutex );	//mutex is initialized unlocked.
DEFINE_MUTEX ( smfu2_mutex );	//mutex is initialized unlocked.
DEFINE_MUTEX ( smfu2_pids_mutex );	//mutex is initialized unlocked.

/******************************************************************************
 *  helper functions      						      *
 ******************************************************************************/

/*
 * Functions to append pids in the pid List(single chain list)
 */
static void smfu2_process_append(struct task_struct* task){
    struct smfu2_process* tmp;
    tmp = (struct smfu2_process*) kmalloc(sizeof(struct smfu2_process),GFP_KERNEL);
    if(tmp == 0){
        dev_alert(DEV,"Oops. Unable to register process.");
        return;
    }
    tmp->task = task;
    mutex_lock(&smfu2_pids_mutex);
    list_add(&(tmp->list), &(pids));		
    mutex_unlock(&smfu2_pids_mutex);   
}

/*
 * Helper Function to remove pids from the pid List
 */
static void smfu2_process_remove(struct task_struct* task){
    struct list_head *pos, *q;
    struct smfu2_process* tmp;

    mutex_lock(&smfu2_pids_mutex);
    if(list_empty(&(pids)) == 0){
        list_for_each_safe(pos, q, &(pids)){
            tmp = list_entry(pos, struct smfu2_process, list);
            if (tmp->task==task) //found the right entry
                list_del(&(tmp->list));
            {
                kfree (tmp);
                mutex_unlock(&smfu2_pids_mutex);
                return;
            }
        }
    }
    dev_alert(DEV,"tried to remove task, no task found.\n");
    mutex_unlock(&smfu2_pids_mutex);
}

/*
 * irq handler for timeouts
 */
void smfu_timeout_irq_handler(snq_entry_t* entry, int te, int entry_idx) {
    struct list_head *pos, *q;
    struct smfu2_process* tmp;
    long unsigned int timeout_rf; // timeout register file
    /*
       Do NOT migrate a part of this irq handler to a tasklet or something
       else that enable concurent handling of other irqs. If this irq handler
       is exected the related processes had already got wrong data. A communication
       with other processes or devices could be fatal.
       This irq handler should be (hopefully) executed very rare, so Latencys doesn't mater.

*/
    if(smfu2_timeout_response){
        dev_info(DEV, "smfu2: timeout interrupt");

	if (MAINTAIN_PID_LIST) {
		//signal to (all?) process
                dev_info(DEV, "killing processes");

		if(list_empty(&(pids)) == 0){
			list_for_each_safe(pos, q, &(pids)){
				tmp = list_entry(pos, struct smfu2_process, list);
				send_sig_info(SIGKILL,              //signal send to process
				              (struct EKVCL_siginfo*) 1,  //1 means send signal as Kernel signal
				              tmp->task);    //Process descripton
			}
		}
	}

        //reset timeout
        // the following two lines look a little bit absurd,
        // but the bit for the timeout get set by an xor.
        timeout_rf = get_extoll_rf_smfu_rf_timeout_control() ;
        set_extoll_rf_smfu_rf_timeout_control(timeout_rf);
    }else{
        dev_info(DEV,"timeout interrupt, not handled ");
    }
}

// Parses different formats for sizes, accepts:
//   hex: 0x10 -> 16 Bytes
//   dec: 10 -> 10 Bytes
//   dec + suffix: 10K -> 10240 Bytes
//
//   returns 0 on succes, -1 on error
int strtosize(char* str, unsigned long int* val)
{
    unsigned long int size;
    if ( sscanf(str, "0x%lX", &size) == 1 ) {
        *val = size;
        return 0;
    } else {
        char suffix;
        int pos;
        int hits;
        hits = sscanf(str, "%lu%n%c", &size, &pos, &suffix);
        switch (hits) {
            case 0:
            case 1:
                if (pos > 0) {
                    *val = size;
                    return 0;
                } else {
                    return -1;
                }
                break;

            case 2:
                switch (suffix) {
                    case 'K':
                        *val = size * 1024;
                        return 0;
                        break;
                    case 'M':
                        *val = size * 1024 * 1024;
                        return 0;
                        break;
                    case 'G':
                        *val = size * 1024 * 1024 * 1024;
                        return 0;
                        break;
                    case 'T':
                        *val = size * 1024 * 1024 * 1024 * 1024;
                        return 0;
                        break;
                    default:
                        return -1;
                }
                break;
        }
    }
    return -1;
}

smfu2_interval_t* smfu2_reserve_interval(uint64_t size, uint16_t node, uint8_t target_port,int i_num_req)
{
 int i;
 smfu2_interval_t *interval;
 smfu2_interval_t *smallest=0;
 int new_size;
 int hw_interval_idx=-1;
 unsigned long flags;

 spin_lock_irqsave(&smfu2.interval_lock,flags);
 if (i_num_req==-1) {
 for (i=0;i<63;i++) {
   if (smfu2.hw_intervals[i]==0) //unused!
    {
      hw_interval_idx=i;
      break;
    }
 }}
 else
 {
 if (smfu2.hw_intervals[i_num_req]==0) //unused!
    {
      dev_dbg(DEV,"interval %d requested and it is unused\n",i_num_req);
      hw_interval_idx=i_num_req;
    }
    else
      dev_alert(DEV,"interval %d requested but it is in use\n",i_num_req);
 }
 if (hw_interval_idx==-1) {
  dev_alert(DEV,"could not find free hw interval\n");
  spin_unlock_irqrestore(&smfu2.interval_lock,flags);
  return 0;
 }

 list_for_each_entry(interval, &smfu2.intervals_free_list, list) {
   dev_dbg(DEV,"traversing intervals. current size is %ld requested size is %ld\n",(unsigned long) interval->size,(unsigned long)size);
   if (interval->size>=size) {
     //would fit
     if (smallest==0) smallest=interval;
     else if (smallest->size >= interval->size)
     smallest=interval;
   }
 }
 if (smallest==0) //no match
 {
   dev_info(DEV,"Could not find mactch for requester interval\n");
   spin_unlock_irqrestore(&smfu2.interval_lock,flags);
   return 0;
 }
 //remove froem free list
 list_del_init(&smallest->list);
 if (smallest->size!=size) {
  //split interval
  new_size=smallest->size-size;
  interval=kmalloc(sizeof(smfu2_interval_t),GFP_KERNEL);
  interval->start=smallest->start;
  interval->stop=smallest->start+size;
  interval->size=size;
  INIT_LIST_HEAD(&interval->list);
  smallest->start=smallest->start+size;
  smallest->stop=smallest->start+size+new_size;
  smallest->size=new_size;
  smallest->v_addr=0;
  //add rest of interval to free list
  list_add(&smallest->list, &smfu2.intervals_free_list);
 } else {
 //exact match, use this interval 
  interval=smallest;
 }
 interval->valid=1;
 interval->ref_count++;
 interval->node=node;
 interval->target_port=target_port;
 interval->interval_num=hw_interval_idx;
 interval->v_addr=0;
 //add interval to used list'
 list_add(&interval->list,&smfu2.intervals);
 smfu2.hw_intervals[hw_interval_idx]=interval;
 smfu2_sync_interval_to_hw(hw_interval_idx);
 spin_unlock_irqrestore(&smfu2.interval_lock,flags);
 return interval;
}
EXPORT_SYMBOL(smfu2_reserve_interval);

int smfu2_free_interval(smfu2_interval_t* interval)
{
  unsigned long flags;

  spin_lock_irqsave(&smfu2.interval_lock,flags);

  interval->ref_count--;
  if (interval->ref_count==0) //free itnerval
  {
    interval->valid=0;
    interval->node=0;
    interval->target_port=0;
    smfu2_sync_interval_to_hw(interval->interval_num);
    smfu2.hw_intervals[interval->interval_num]=0;
    interval->interval_num=-1;
    if (interval->v_addr!=0)
      dev_warn(DEV,"freeing interval with v_addr != 0\n");
    interval->v_addr=0;
    list_del_init(&interval->list);
    list_add(&interval->list,&smfu2.intervals_free_list);
    //compact free list missing
  }
  else
  {
    dev_alert(DEV,"Requested freeing of interval %d, but still refcount %d.\n",interval->interval_num,interval->ref_count);
  }
  spin_unlock_irqrestore(&smfu2.interval_lock,flags);

  return 0;
}
EXPORT_SYMBOL(smfu2_free_interval);

int smfu2_interval_modify_node(smfu2_interval_t* interval, uint16_t target_node)
{ 
 unsigned long flags;

 if (interval==0) return -1;
 spin_lock_irqsave(&smfu2.interval_lock,flags);
 interval->node=target_node;
 if (interval->interval_num!=-1) {
  smfu2_sync_interval_to_hw(interval->interval_num);
  spin_unlock_irqrestore(&smfu2.interval_lock,flags);
  return 0;
 }
 else
 {
  spin_unlock_irqrestore(&smfu2.interval_lock,flags);
  return -2;
 }
 return 0;
}
EXPORT_SYMBOL(smfu2_interval_modify_node);

void smfu2_rra_write(int node, uint32_t r_address, uint64_t value)
{
 //set node id in smfu interval
 smfu2_interval_modify_node(smfu2.rra_interval,node);
 //write
 smfu2.rra_interval->v_addr[r_address/8]=(unsigned long) value;
}
EXPORT_SYMBOL(smfu2_rra_write);

uint64_t smfu2_rra_read(int node, uint32_t r_address)
{
 uint64_t value;
 //set node id in smfy interval
 smfu2_interval_modify_node(smfu2.rra_interval,node);
 //read and return
 value=smfu2.rra_interval->v_addr[r_address/8];
 return value;
}
EXPORT_SYMBOL(smfu2_rra_read);

void* smfu2_ioremap_nocache(smfu2_interval_t* interval) {
 if (interval==0) {
   dev_alert(DEV,"smfu2_ioremap_nocache called, but interval is NULL\n");
   return 0;
 }
 if (interval->v_addr!=0) {
   dev_alert(DEV,"trying to iomap_nochache an interval which already has an assigned v_addr\n");
   return 0;
 }
 interval->v_addr=EKVCL_ioremap(interval->start,interval->size);
 if (!interval->v_addr) {
   dev_alert(DEV,"ioreampping of interval failed\n");
 }
 return interval->v_addr;
}
EXPORT_SYMBOL(smfu2_ioremap_nocache);

void smfu2_iounmap(smfu2_interval_t* interval) {
 if (interval->v_addr!=0) {
  iounmap(interval->v_addr);
  interval->v_addr=0;
 } else {
  dev_alert(DEV,"trying to iounmap interval with v_addr of NULL\n");
 }
}
EXPORT_SYMBOL(smfu2_iounmap);

/*
int smfu2_sync_interval_from_hw(uint32_t i) {
  uint64_t value;
  if (i>63) {
    dev_warn(DEV,"smfu2_sync_interval_from_hw: trying to access interval %d of 64 intervals.\n");
    return -1;
  } 
  value=get_extoll_rf_smfu_rf_interval_control(i);
  smfu2.hw_intervals[i].node=(value & 0xffff0000) >> 16l;
  smfu2.hw_intervals[i].target_port=(value & 0x700) >> 8l;
  smfu2.hw_intervals[i].valid=(value & 0x1);
 
  smfu2.hw_intervals[i].start=get_extoll_rf_smfu_rf_interval_startaddr(i);
  smfu2.hw_intervals[i].stop=get_extoll_rf_smfu_rf_interval_endaddr(i);
  return 0;
}
*/
int smfu2_sync_interval_to_hw(int i)
{
  uint64_t value;
  if (i>63) {
    dev_warn(DEV,"smfu2_sync_interval_to_hw: trying to access interval %d of 64 intervals.\n",i);
    return -1;
  } 
 if (smfu2.hw_intervals[i]==0) {
    dev_alert(DEV,"syncing of interval %d requested, but hw_interval not set\n",i);
    return -1;
 }
 value = ((smfu2.hw_intervals[i]->target_port & 0x7l)<<8l) | ((smfu2.hw_intervals[i]->node & 0xffff)<<16l) | (smfu2.hw_intervals[i]->valid & 0x1l);
 set_extoll_rf_smfu_rf_interval_control(i,value);
 dev_dbg(DEV,"Syncing interval to hw: start %lx, stop %lx\n",(unsigned long) smfu2.hw_intervals[i]->start,(unsigned long)smfu2.hw_intervals[i]->stop);
 set_extoll_rf_smfu_rf_interval_startaddr(i,smfu2.hw_intervals[i]->start);
 set_extoll_rf_smfu_rf_interval_endaddr(i,smfu2.hw_intervals[i]->stop);
 return 0;
}

void smfu2_reset_hw_intervals(void)
{
    int i;
    for (i = 0; i < 63; i++) {
        set_extoll_rf_smfu_rf_interval_startaddr( i, 0 );
        set_extoll_rf_smfu_rf_interval_endaddr( i, 0 );
        set_extoll_rf_smfu_rf_interval_control( i, 0 );
    }
}


int smfu2_init_intervals(void)
{
 smfu2_interval_t* interval;
 //int i;

 smfu2_reset_hw_intervals();
 
 interval=kmalloc(sizeof(smfu2_interval_t),GFP_KERNEL);
 if (interval == NULL) {
   dev_alert(DEV,"could not allocalte interval structure\n");
   return -1;
 }
 dev_dbg(DEV,"init_intervals. Global_mem_addr=%lx, size=%lx\n",(unsigned long)smfu2.global_mem_addr, (unsigned long) smfu2.global_mem_size);
 interval->start=smfu2.global_mem_addr;
 interval->stop=smfu2.global_mem_addr+smfu2.global_mem_size;
 interval->node=-1;
 interval->target_port=-1;
 interval->valid=0;
 interval->ref_count=0;
 interval->size=smfu2.global_mem_size;
 interval->interval_num=-1;
 interval->v_addr=0;
 INIT_LIST_HEAD(&interval->list);
 list_add(&interval->list,&smfu2.intervals_free_list);
 return 0;
}

void smfu2_free_intervals(void)
{
 smfu2_interval_t* interval,*next;

 list_for_each_entry_safe(interval,next, &smfu2.intervals_free_list, list) {
   if (interval->v_addr!=0)
     smfu2_iounmap(interval);
   dev_dbg(DEV,"removing interval from free list\n");
   list_del(&interval->list);
   kfree(interval);
 }

 list_for_each_entry_safe(interval, next,&smfu2.intervals, list) {
   if (interval->v_addr!=0)    
     smfu2_iounmap(interval);
   dev_dbg(DEV,"removing interval from used list\n");
   list_del(&interval->list);
   kfree(interval);
 }

}

/******************************************************************************
 *  file operations of smfu2 device					      *
 ******************************************************************************/
/* Handle open of the smfu2 example device. */    
static int smfu2_open(struct inode *inode, struct file *filp)
{
    int minor_nr;

    struct smfu2_context *context = kmalloc(GFP_KERNEL, sizeof(*context));
    context->pid = current->pid;

    /* register this task with the nw state task monitoring facitilty (to it gets stopped if necessary) */
    extoll_add_nw_state_task(context->pid, SMFU_PID, current);


    /* check if network is ready -> if not return -EAGAIN
   */
  if (extoll_get_nw_state()!=EXTOLL_NW_STATE_C) //network not configured
  {
    extoll_remove_nw_state_task(context->pid, SMFU_PID);
    kfree(context);
    return -EAGAIN;
  }
  
    
    if ( smfu2_opened > 0 ) {
        dev_dbg(DEV,"device already opened by %d other processes\n", smfu2_opened);
    }

    minor_nr = MINOR ( inode->i_rdev );
    dev_dbg(DEV,"device open request (minor=%d)\n", minor_nr );

    if ( minor_nr > 1 ) {
        dev_alert(DEV," only minor number 0 is valid!\n" );
        extoll_remove_nw_state_task(context->pid, SMFU_PID);
	kfree(context);
        return -ENODEV;
    }

    if (MAINTAIN_PID_LIST) {
        dev_dbg(DEV,"adding PID (current->pid=%d) to list", current->pid);
        //register pid
	smfu2_process_append(current);
    }

    smfu2_opened ++;
    filp->private_data = context;

    return 0;
}

/* Handle close of the smfu2 example device. */
static int smfu2_release(struct inode *inode,struct file *filp)
{ 
    int minor_nr;

    struct smfu2_context *context = filp->private_data;

    minor_nr = MINOR ( inode->i_rdev );
    if ( minor_nr > 1 ) {     
        dev_alert(DEV,"only minor number 0 is valid!\n" );
        return -ENODEV;
    }

    if (MAINTAIN_PID_LIST) {
         dev_dbg(DEV,"removing PID (current->pid=%d) from list", current->pid);
        //unregister pid
        smfu2_process_remove(current);
    }

    smfu2_opened --;
    dev_dbg(DEV,"device has been released\n" );

    //remove task from nw state monitoring
    extoll_remove_nw_state_task(context->pid, SMFU_PID);

    kfree(context);

    return 0;
}

/********************************************************************************/
/*  VMA operations                                                             **/
/* ******************************************************************************/

static long smfu2_ioctl_unlocked( struct file *filp,
        unsigned int cmd, unsigned long arg)
{
    dev_dbg(DEV,"ioctl entry (cmd=%u, arg=%u)\n", (unsigned int) cmd, (unsigned int) arg );

    // Do some security tests on the requested command number
    if (_IOC_TYPE(cmd) != SMFU2_IOC_MAGIC)
        return -ENOTTY;

    if (_IOC_NR(cmd) > SMFU2_IOC_MAXNR)
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
        case (SMFU2_IOCTL_GET_LOCAL_SIZE):
            {
                dev_dbg(DEV,"ioctl get local size: %lx\n",smfu2.target_size);
                return put_user(smfu2.target_size, ((uint64_t *) arg));
            }
        case (SMFU2_IOCTL_FLUSH_CACHES):
            {
#ifndef LS3BEXTOLL              
                dev_dbg(DEV,"SMFU2_IOCTL_FLUSH_CACHES\n");
                asm ( "wbinvd"
                        :         //outputs
                        :         //inputs
                        //:       //clobber list
                    );
#else
                dev_alert(DEV,"SMFU2_IOCTL_FLUSH_CACHES currently on LS3B not supported\n");
                return -EFAULT;
#endif                
                return 0;
            }
		case (SMFU2_IOCTL_GET_NODE_ID):
			{
				uint64_t value = (get_extoll_rf_info_rf_node()>>24l ) & 0xffffl;
                                dev_dbg(DEV,"SMFU2_GET_NODE_ID: %lx\n",(unsigned long int) value);
				return put_user(value, ((uint64_t*) arg) );
			}
        default:
            {
                dev_warn(DEV,"unknown minor and/or IOCTL (%d)\n",cmd);
                break;
            }
    }
    return 0;
}

static int smfu2_mmap_default ( struct file *filp, struct vm_area_struct *vma )
{
    unsigned long offset = 0;     /* full offset from start of BAR0 */
    unsigned long physical = 0;   /* physical start address */
    unsigned long vsize = 0;      /* size in virtual address space */
    unsigned long psize = 0;      /* size in physical address space */
    pgprot_t page_prot;           /* protection bits for address space */

    offset = vma->vm_pgoff;

    vsize = vma->vm_end - vma->vm_start;
    if ( offset == 0 ) //global memory mapping
    {
        dev_dbg(DEV,"mmap of global memory requested (req. size=%ldMB, max=%ldMB)\n", vsize / 1024 / 1024, smfu2.global_mem_size / 1024 / 1024 );
        if ( vsize > smfu2.global_mem_size ) {
            dev_alert(DEV,"Wrong size. Use less or equal than %lu! Requested: %lu\n", smfu2.global_mem_size, vsize );
            return -EFAULT;
        }
        physical = smfu2.global_mem_addr; 
        psize = vsize; 
        if ( smfu2_en_write_combining != 0 ) {
            page_prot = __pgprot ( pgprot_val ( vma->vm_page_prot ) | EXTOLLWCATTR );
            dev_dbg(DEV,"mmap BAR2 (write-combining): physical %lx, vsize %lu, psize %lu\n", physical, vsize, psize); 
        } else {
            // Use this pgprot in order to allow mapping the BAR without caching
            //page_prot = __pgprot ( pgprot_val ( vma->vm_page_prot ) | _PAGE_PCD ); 
            //printk ( KERN_INFO "smfu2: mmap BAR2 (uncachable): physical %lx, vsize %lu, psize %lu\n", physical, vsize, psize); 

            // Use this pgprot in order to allow mapping the BAR with (write-back) caching
#ifndef  LS3BEXTOLL
            page_prot = __pgprot ( pgprot_val ( vma->vm_page_prot ) & ~_PAGE_CACHE_MASK ); 
#else            
            page_prot = __pgprot ( pgprot_val ( vma->vm_page_prot )); 
#endif            
            dev_dbg(DEV,"mmap BAR2 (write-back allowed): physical %lx, vsize %lu, psize %lu\n", physical, vsize, psize); 

            //page_prot = __pgprot ( pgprot_val ( vma->vm_page_prot ) | _PAGE_PAT ); //unused
        }

        io_remap_pfn_range ( vma, vma->vm_start, physical >> PAGE_SHIFT, vsize, page_prot);
        dev_dbg(DEV,"mmap of global memory done, vma->vm_start = %lX, physical = %lX\n", vma->vm_start, (unsigned long int)virt_to_phys((void*)vma->vm_start) );
    }
    else if ( offset == 1 ) //local memory
    {
        dev_dbg(DEV,"mmap of local memory requested...\n");
        if ( vsize > smfu2.target_size ) {
            dev_alert(DEV,"Wrong size for mmap of local memory. Legal is up to %lu bytes  Given: %lu\n",smfu2.target_size,vsize );
            return -EFAULT;
        }

#ifdef MICEXTOLL    
        physical = smfu2.target_physical_address - micextoll_micbase0; 
#else
        physical = smfu2.target_physical_address;
#endif
        psize = vsize; 
        remap_pfn_range(vma, vma->vm_start, physical >> PAGE_SHIFT , psize , vma->vm_page_prot); 
        //io_remap_pfn_range ( vma, vma->vm_start, physical >> PAGE_SHIFT, vsize, page_prot); 
        dev_dbg(DEV,"mmap of local memory done, vma->vm_start = %lX, physical = %lX\n", vma->vm_start, (unsigned long int)virt_to_phys((void*)vma->vm_start));
    }
    else
    {
        dev_alert(DEV,"oops wrong offset: %ld\n", offset );
        return -EFAULT;
    }

    return 0;
}

static int smfu2_mmap ( struct file *filp, struct vm_area_struct *vma )
{
    int err;

    dev_dbg(DEV,"starting mmap with offset %lu\n", vma->vm_pgoff );

    /* do real mmap in seperate function */
    err = smfu2_mmap_default ( filp, vma );

    dev_dbg(DEV,"mmap call done\n" );
    return err;
}


/**
 * smfu2 file operations
 */
static struct file_operations smfu2_fops = {
    .owner = THIS_MODULE,
    .mmap = smfu2_mmap,
    .unlocked_ioctl = smfu2_ioctl_unlocked,
    .open = smfu2_open,
    .release = smfu2_release,
};

#if 0
static int smfu2_setup_mmio_cpurouting ( void )
{
#ifdef MICEXTOLL
   dev_alert(DEV,"the function smfu2_setup_mmio_CPUrouting ist not implemented yet for KNC \n\n\n");
   return -1;
#else
    // TODO: would be nice to pass paddr as argument, now it's statically 0x8000000000
    // reconfigure the AMD Opteron to route a new address interval to the EXTOLL PCI device
    // Assume that MMIO entry #5 is unused (D18F1xA8, ..AC). Also see AMD BKDG for 15h
    // setpci -v -s 00:18.1 AC.l=BFFFFF20
    // setpci -v -s 00:18.1 A8.l=80000003
    // int pci_read_config_dword(struct pci_dev *dev, int where, u32 *val); 
    // int pci_write_config_dword(struct pci_dev *dev, int where, u32 val); 

    struct pci_dev *cpu_dev;
    uint32_t val;

    // get handle to CPU configuration space (00:18.1) for AIC C32 boxes
    cpu_dev = pci_get_device ( /*PCI_VENDOR_ID*/ 0x1022, /*PCI_DEVICE_ID*/ 0x1601, NULL);
    if ( cpu_dev == NULL) {
        dev_alert(DEV,"CPU PCI handle not found!\n" );
        return -ENODEV;
    }

    // read MMIO registers for sanity reasons
    pci_read_config_dword ( cpu_dev, 0xA8, &val );
    dev_dbg(DEV,"\"MMIO Base Low #5\" before: 0x%08X\n", val );
    pci_read_config_dword ( cpu_dev, 0xAC, &val );
    dev_dbg(DEV,"\"MMIO Limit Low #5\" before: 0x%08X\n", val );

    // # MMIO Base[39:16]                res.    Lock  res. WE RE
    // # 1000_0000_0000_0000_0000_0000  _0000   _0      0   1  1 
    pci_write_config_dword ( cpu_dev, 0xA8, 0x80000003 /*(( paddr ) >> 8l ) || 3l */ );

    // # MMIO Limit[39:16]                NonPosted  DstSubLink   DstLink   Reserved   DstNode
    // # 1011_1111_1111_1111_1111_1111   _0            0            10         _0        000
    pci_write_config_dword ( cpu_dev, 0xAC, 0xBFFFFF20 );

    // close handle to CPU
    pci_dev_put ( cpu_dev );

    return 0;
#endif
}
#endif

/******************************************************************************
 *  PCI subsystem integration                                                  *
 ******************************************************************************/

static int smfu2_setup_mmio ( void )
{
    unsigned long int size;
    //unsigned long int paddr;
    //uint32_t val;

    if (sscanf(smfu2_target_mem_start, "0x%lx", &smfu2_target_mem_start_val) != 1) {
        dev_info(DEV,"malformed target memory start\n");
        return -EINVAL;
    }

    if (strtosize(smfu2_target_mem_size, &smfu2_target_mem_size_val) != 0) {
        dev_info(DEV,"malformed target memory size\n");
        return -EINVAL;
    }

    if (strtosize(smfu2_global_mem_size, &smfu2_global_mem_size_val) != 0) {
        dev_info(DEV,"malformed global memory size\n");
        return -EINVAL;
    }

    if ( smfu2_target_mem_start_val == 0xFFFFFFFFFFFFFFFF ) {
        dev_info(DEV,"target memory not specified, allocating with dma_alloc_coherent\n" );
        // default value of argument -> no global mem specified -> 4M + dma_alloc
        size = 4*1024*1024;
        smfu2.target_virtual_address = dma_alloc_coherent ( &smfu2.devp->dev, size, (dma_addr_t *) & smfu2.target_physical_address, GFP_KERNEL );
        smfu2.target_size=size;

        #ifdef MICEXTOLL
        smfu2.target_physical_address += micextoll_micbase0; //TODO:We have to check this! Not tested yet
	#endif

    } else {
        dev_info(DEV,"target memory specified at address: 0x%lx, size is 0x%lx\n",
                smfu2_target_mem_start_val, smfu2_target_mem_size_val );
        // global mem specified -> use this address and smfu2_target_mem_size accordingly
        // no allocation necessary as global memory has been allocated previously (kernel boot parameter 'mem')
        size = smfu2_target_mem_size_val;
        smfu2.target_physical_address = smfu2_target_mem_start_val;
        smfu2.target_virtual_address  = (void*) smfu2_target_mem_start_val;
        smfu2.target_size = size;
    }

#if 0
    if (smfu2_en_emmio != 0) { // EMMIO Mapping
        dev_info(DEV,"using EMMIO\n" );
        // reconfigure HTAX routing registers to use new (larger) BAR
        paddr = 0x8000000000; // use this as new BAR address
        // TODO: would be nice to update card.smfu2_paddr and card.smfu2_size here (see extolldrv.c)

        //smfu2.global_mem_vaddr = extoll_get_smfu_vaddr(); not used
        smfu2.global_mem_addr = paddr;
        if (smfu2_global_mem_size_val == 0x00)
            smfu2.global_mem_size = size;
        else
            smfu2.global_mem_size = smfu2_global_mem_size_val;

        //disable the routing table to reconfigure it
        set_extoll_rf_htax_bridge_rf_general ( 0 );

        //set up smfu routing for posted channel
        set_extoll_rf_htax_bridge_rf_intvl_upper   ( 3, ( paddr + smfu2_global_mem_size_val ) >> 12l );
        set_extoll_rf_htax_bridge_rf_intvl_lower   ( 3, (( paddr ) >> 12l) - 1l );
        set_extoll_rf_htax_bridge_rf_intvl_control ( 3, HTAX_INVTL_POSTED_VC /*| HTAX_INVTL_NONPOSTED_VC*/| HTAX_INVTL_SMFU_PORT_OH| HTAX_INVTL_POSTED_HOST_PORT | HTAX_INVTL_ENABLE);

        //set up smfu routing for non-posted channel
        set_extoll_rf_htax_bridge_rf_intvl_upper   ( 4, ( paddr + smfu2_global_mem_size_val ) >> 12l );
        set_extoll_rf_htax_bridge_rf_intvl_lower   ( 4, (( paddr ) >> 12l) - 1l );
        set_extoll_rf_htax_bridge_rf_intvl_control ( 4, /*HTAX_INVTL_POSTED_VC |*/ HTAX_INVTL_NONPOSTED_VC| HTAX_INVTL_SMFU_PORT_OH| HTAX_INVTL_NONPOSTED_HOST_PORT | HTAX_INVTL_ENABLE);

        //enable the routing table just set-up
        set_extoll_rf_htax_bridge_rf_general ( HTAX_GENERAL_ENABLE | HTAX_USE_VC_MODE | ((8l<<4l)) | (8) );

        // Enable HT-Core EMMIO
        // THIS HAS TO BE DONE BEFORE WRITING ANYTHING TO BAR2
        val = get_extoll_rf_htax_bridge_rf_general ();
        set_extoll_rf_htax_bridge_rf_general ( val | ( 0x1 << 16 ) ); // Enables HT-Core EMMIO feature for BAR2

	#ifndef MICEXTOLL
        //configure BAR2 of the EXTOLL device and enable it (HT core does not check size of BAR2)
        //setpci -v -s 20:00.0 20.l=00000004
        //setpci -v -s 20:00.0 24.l=00000080
        pci_write_config_dword ( smfu2.devp, 0x20, 0x00000004 );
        pci_write_config_dword ( smfu2.devp, 0x24, 0x00000080 );
	#endif

        // reconfigure the AMD Opteron to route a new address interval to the EXTOLL PCI device
        if ( smfu2_setup_mmio_cpurouting () < 0 )
            return -ENODEV;

/*
#ifndef LS3BEXTOLL        
        smfu2_mtrr_number = mtrr_add(0x8000000000, 0x4000000000, MTRR_TYPE_WRBACK, 0);
        if (smfu2_mtrr_number < 0) {
            printk ( KERN_ALERT "smfu2: MTRR setup for BAR with base 0x%lx, size 0x%lx failed",
                    0x8000000000, 0x4000000000);
        } else {
            printk ( KERN_INFO "smfu2: MTRR setup for BAR successful" );
        }
#endif        
*/

    } else {
#endif
        dev_info(DEV,"using normal MMIO\n" );
        //smfu2.global_mem_vaddr = extoll_get_smfu_vaddr(); not used

        //For MIC/KNC, we have to switch first to the real PCI-E addresses, when we use it inside a host//TODO: Check this
        #ifdef MICEXTOLL
	//physical_extoll_set_up_internal_address_map();
	#endif
	smfu2.global_mem_addr = extoll_get_smfu_addr ();//MICEXTOLL TODO: We have to check this
        dev_dbg(DEV,"got global mem addr from base driver: %lx %lx\n",(unsigned long) smfu2.global_mem_addr,(unsigned long) extoll_get_smfu_addr());
	#ifdef MICEXTOLL
	//extoll_set_up_internal_address_map();
	#endif
        if (smfu2_global_mem_size_val == 0x00)
            smfu2.global_mem_size = extoll_get_smfu_size ();
        else
            smfu2.global_mem_size = smfu2_global_mem_size_val;


#ifndef LS3BEXTOLL           
        if ( smfu2_en_write_combining == 0 ) {
            smfu2_mtrr_number = EKVCL_mtrr_add(smfu2.global_mem_addr, smfu2.global_mem_size, MTRR_TYPE_WRBACK, 0);
            if (smfu2_mtrr_number < 0) {
                dev_alert(DEV,"MTRR setup for BAR with base 0x%lx, size 0x%lx failed", smfu2.global_mem_addr, smfu2.global_mem_size);
            } else {
                dev_info(DEV,"MTRR setup for BAR successful" );
            }
        }   
#endif        

        // TODO: if previously driver was loaded using EMMIO parameters, now it won't work because htax_bridge routing is misconfigured
#if 0
    }
#endif

    if (smfu2.target_virtual_address == NULL) {
        dev_alert(DEV,"memory allocation for target memory failed.\n" );
        return -ENOMEM;
    }

    //set oStartAddr to global_mem_addr (local access to global memory, i.e. BAR)
#ifdef MICEXTOLL
    set_extoll_rf_smfu_rf_oStartAddr ( extoll_get_smfu_addr_physical() ); 
#else   
    set_extoll_rf_smfu_rf_oStartAddr ( smfu2.global_mem_addr );
#endif
    //set tStartAddr_default to exported memory
    set_extoll_rf_smfu_rf_tStartAddr_default ( smfu2.target_physical_address );
    dev_info(DEV,"target memory allocated at physical address 0x%lx, size is 0x%lx\n",
            smfu2.target_physical_address, size );

    //set default mask to zero (all requests target nodeID 0)
    set_extoll_rf_smfu_rf_addr_mask ( 0l );

    //set the default traffic classes to a sane value (tc_r != tc_np) (in the FPGA version, only 2 traffic classes are available...)
    //posted =0, response=0 and nonposted=1
    //set_extoll_rf_smfu_rf_traffic_class ( 0x001l );
    set_extoll_rf_smfu_rf_traffic_class ( 0x223l );

    //enable network port 3, configure it to handle splitted packets (i.e., to combine splitted packets before forwarding them to the SMFU)
		//also set the s/f bit
    set_extoll_rf_np_top_rf_n3_general ( 0xff );

    //set enable to 1
    set_extoll_rf_smfu_rf_status_control ( 1l );
    dev_info(DEV,"smfu2_setup_mmio done\n");
    return 0;
}

static int smfu2_free_mmio(void)
{
    //free memory (if allocated by dma_alloc_coherent)
    if (smfu2_target_mem_start_val == 0xFFFFFFFFFFFFFFFF) {
	#ifdef MICEXTOLL
	//get again the real physical hardware address. The memory is allocated on MIC/KNC 
	smfu2.target_physical_address -= micextoll_micbase0;
	#endif
        dma_free_coherent(&smfu2.devp->dev,4*1024*1024,(void*) smfu2.target_virtual_address ,(dma_addr_t ) smfu2.target_physical_address);
    }
    //set enable to 0
    set_extoll_rf_smfu_rf_status_control(0l);

    //disable network port 3
    set_extoll_rf_np_top_rf_n3_general(0l);

#ifndef LS3BEXTOLL       
    if (smfu2_mtrr_number >= 0)
        EKVCL_mtrr_del(smfu2_mtrr_number, 0, 0);
#endif    

    return 0;
}

#if 0
static uint32_t get_nodeid(void)
{
    return ( get_extoll_rf_info_rf_node() >> 24l ) & 0xffffl;
}
#endif

/* Sets (almost) arbitrary intervals
 *
 * Easiest access through module parameter "smfu2_intervals"
 *
 * Each interval is specified by a node ID and its size.
 * All intervals are stacked onto eachother.
 * Format: <Node ID>:<Size>,<Node ID>:<Size>
 * 
 * Example: 1:2M,2:4G,4:2G
 *
 * This would result in the lowest 2MB being "owned" by Node ID 1,
 * the next 4G by Node ID 2 and the last 2G by Node ID 4
 */
#if 0
void smfu2_reset_hw_intervals(void)
{
    int i;
    for (i = 0; i < 16; i++) {
        set_extoll_rf_smfu_rf_interval_startaddr( i, 0 );
        set_extoll_rf_smfu_rf_interval_endaddr( i, 0 );
        set_extoll_rf_smfu_rf_interval_control( i, 0 );
    }
}
int smfu2_set_intervals3(uint64_t phys_addr, uint32_t* node_id, size_t* mem_size, 
        uint32_t num_nodes)
{
    uint64_t start_i;
    uint64_t end_i;
    uint64_t val;
    uint32_t nodeid = get_nodeid();

    unsigned int i;

    smfu2_reset_intervals();

    start_i = smfu2.global_mem_addr;

    for (i = 0; i < num_nodes; i++) {
        if (mem_size[i] != 0) {
            val = 0x301 | (16 << node_id[i]);
            end_i = start_i + mem_size[i] - 1;
            set_extoll_rf_smfu_rf_interval_startaddr( node_id[i], start_i );
            set_extoll_rf_smfu_rf_interval_endaddr( node_id[i], end_i );
            set_extoll_rf_smfu_rf_interval_control( node_id[i], val );
            start_i += mem_size[i];
        } else {
            /* Skipping entry */
        }
    }

    set_extoll_rf_smfu_rf_vpid_tStartAddr(nodeid, phys_addr);

    return 0;
}

EXPORT_SYMBOL( smfu2_set_intervals3 );

int smfu2_set_intervals2 ( char* intervals )
{
    char *ptr, *last, *end;
    unsigned long int size;
    uint64_t start_i;
    uint64_t end_i;
    uint64_t val;
    uint32_t node;

    unsigned int i;

    // Reset all intervals
    for (i = 0; i < 16; i++) {
        set_extoll_rf_smfu_rf_interval_startaddr( i, 0 );
        set_extoll_rf_smfu_rf_interval_endaddr( i, 0 );
        set_extoll_rf_smfu_rf_interval_control( i, 0 );
    }

    // We want to extract node ID and the size of each nodes interval
    //
    // strtok is not available in kernel space so we have to
    // parse the string manually

    // we're going to modify the string, so we want to remember where it ends
    end = intervals + strlen(intervals) + 1;

    last = intervals;
    ptr = intervals;

    start_i = smfu2.global_mem_addr;

    // process complete list
    while ( last < end ) {
        char *entry_sep;

        // search next seperator or end of string
        while (*ptr != ',' && *ptr != '\0')
            ptr++;

        // make NULL terminated string from "last" to "ptr"
        *ptr = '\0';

        // look for delimiter in this item
        entry_sep = last;
        while ( *entry_sep != ':' && *entry_sep != '\0' )
            entry_sep++;

        // no delimiter in this item
        if ( entry_sep >= end || *entry_sep == '\0' ) {
            // BAD we don't want to work on malformed data
            return -EINVAL;
        }

        // make 
        *entry_sep = '\0';
        entry_sep++;

        // We now have seperated both values, the node ID is stored in the
        // string starting at "last" and the size of that chunk is stored
        // in the string starting at "entry_sep"

        if ( sscanf ( last, "%u", &node ) != 1 ) {
            dev_alert(DEV,"intervals - error converting node id '%s'\n",
                    last);
            return -EINVAL;
        }

        if ( strtosize ( entry_sep, &size ) != 0 ) {
            dev_alert(DEV,"intervals - error converting size '%s'\n",
                    entry_sep);
            return -EINVAL;
        }

        val = 0x301 | ( node << 16 );
        end_i = start_i + size - 1;
        set_extoll_rf_smfu_rf_interval_startaddr( node, start_i );
        set_extoll_rf_smfu_rf_interval_endaddr( node, end_i );
        set_extoll_rf_smfu_rf_interval_control( node, val );

        dev_info(DEV,"intervals - done setting interval for node %d\n",
                node );
        dev_info(DEV,"intervals -   start: 0x%lX end: 0x%lX\n",
                (unsigned long int) start_i, (unsigned long int) end_i );

        // Prepare next iteration
        start_i = end_i + 1;
        ptr++;
        last = ptr;
    }

	// Set all vpid target start addresses, because at the time the driver is being inserted we
	//  don't know the node id (defaults to 0)
	for ( i = 0; i < 16; i++) 
	    set_extoll_rf_smfu_rf_vpid_tStartAddr(i , smfu2.target_physical_address);

    return 0;
}

EXPORT_SYMBOL ( smfu2_set_intervals2 );

int smfu2_set_intervals ( uint64_t phys_addr, size_t size, int num_nodes )
{
    int i;
    uint32_t nodeid = get_nodeid();
    uint64_t val;
    uint64_t start;
    uint64_t end;

    start = smfu2.global_mem_addr;
    dev_info(DEV,"set intervals with %d nodes, my nodeid is %d, start is %x\n", num_nodes, nodeid, (unsigned int) start );

    if(num_nodes > 1) {
        for(i = 0; i<num_nodes; i++) {
            end = start+size-1;
            val =  0x301 | (i<<16);

            set_extoll_rf_smfu_rf_interval_startaddr(i,( start));
            set_extoll_rf_smfu_rf_interval_endaddr( i,  (end));
            set_extoll_rf_smfu_rf_interval_control(i, val);

            start+=size;
        }
        set_extoll_rf_smfu_rf_vpid_tStartAddr(nodeid, phys_addr);
    } else if( num_nodes == 1) {
        end = start+size-1;
        val =  0x301 | (nodeid<<16);
        set_extoll_rf_smfu_rf_interval_startaddr(nodeid, (start));
        set_extoll_rf_smfu_rf_interval_endaddr( nodeid,  (end));
        set_extoll_rf_smfu_rf_interval_control(nodeid, val);
        set_extoll_rf_smfu_rf_vpid_tStartAddr(0, phys_addr);
    } else
        return -EINVAL;
    return 0;
}

EXPORT_SYMBOL ( smfu2_set_intervals );
#endif


/**
 * set up the char_dev structure for requester & completer
 * @return 0 if everyting is OK otherwise errorcode is returned
 */
static int smfu2_setup_cdev ( void )
{
    int err, devnr;

    // setup default minor dev
    devnr = MKDEV ( MAJOR ( smfu2.devnr ), SMFU_MINOR_DEFAULT );
    cdev_init ( &smfu2.cdev_default, &smfu2_fops );
    smfu2.cdev_default.owner = THIS_MODULE;
    smfu2.cdev_default.ops = &smfu2_fops;
    err = cdev_add ( &smfu2.cdev_default, devnr, 1 );
    if ( err < 0 ) {
        dev_alert(DEV,"Error %d adding default-cdev", err);
        cdev_del ( &smfu2.cdev_default );
        return err;
    }

    return 0;
}

/**
 * initialize smfu2 device in order to work seamless in kernel pci subsystem.
 * 1. enable the device
 * 2. do some checks (revision etc.)
 * 3. set bit mask(32/64) for dma access
 * 4. retrieve and save base address register values from device
 * 5. dynamically allocate a major number
 * 6. setup character device for requester and completer
 * 7. register interrupt handler
 *
 * called by smfu2_init
 */
static int smfu2_probe ( void )
{
    INIT_LIST_HEAD(&pids);

    printk ( KERN_INFO "smfu2: probe() called!\n");
    smfu2.devp = extoll_get_pdev ();
    if ( smfu2.devp == 0 ) {
        printk ( KERN_ALERT "smfu2: No device found.\n" );
        return -EINVAL;
    }

    // dynamically allocate a major number and create one minor numbers:
    // ->  minor 0 = default
    if ( alloc_chrdev_region ( &smfu2.devnr, 0, SMFU_MINOR_COUNT, "smfu2" ) ) {
        printk ( KERN_ALERT "smfu2: No Major Number available!!\n" );
        return -EINVAL;
    }
    printk ( KERN_INFO "smfu2: Major number: %u\n", MAJOR ( smfu2.devnr ) );

    /*smfu2.global_mem_vaddr = extoll_get_smfu_vaddr();
      smfu2.global_mem_addr = extoll_get_smfu_addr ();
      smfu2.global_mem_size = extoll_get_smfu_size (); now done in smfu2_setup_mmio() */

    smfu2.dev=device_create(extoll_get_class_user(),extoll_get_device(), smfu2.devnr, NULL, "smfu2");
    if (smfu2.dev==NULL) {
      printk("velo2 device creation failed\n");
      goto free_chrdev_region;
    }


    // init registerfile
    // bar has to be initialized successfully!
    //extoll_rf = (struct extoll_map *) smfu2.bar0_vaddr;

    // Now setup character device specific ops 
    if ( smfu2_setup_cdev () < 0 ) {
        goto destroy_device;
    }
    
    INIT_LIST_HEAD(&smfu2.intervals);
    INIT_LIST_HEAD(&smfu2.intervals_free_list);
    spin_lock_init(&smfu2.interval_lock);
    smfu2.rra_interval=0;

    smfu2_setup_mmio();


    dev_dbg(DEV,"smfu2: global_mem (BAR) placed at physical addr 0x%lx size 0x%lx\n", smfu2.global_mem_addr, smfu2.global_mem_size );

    smfu2_init_intervals();

    dev_dbg(DEV,"init intervals done\n");
    smfu2.rra_interval=smfu2_reserve_interval(32*1024*1024,0,3,0);
    if (smfu2.rra_interval==NULL) {
      dev_alert(DEV, "Could not allocate RRA interval\n");
      goto destroy_device;
    }

    smfu2_ioremap_nocache(smfu2.rra_interval);


/*    if ( strlen(smfu2_intervals) > 0 ) {
        smfu2_set_intervals2 ( smfu2_intervals );
    }
*/
    //register interrupt handler
   //FIXME: commented out, since it can make problems
 //   if(smfu2_timeout_response)
//	extoll_register_interrupt_handler(SNQ_TE_SMFU_TIMEOUT,&smfu_timeout_irq_handler);
  return 0;
  destroy_device:
    device_destroy(extoll_get_class_user(),smfu2.devnr);
  free_chrdev_region:
    unregister_chrdev_region ( smfu2.devnr, SMFU_MINOR_COUNT );
    printk ( KERN_ALERT "smfu2: Major requester number %x freed \n", MAJOR ( smfu2.devnr ) );
  return -EINVAL;
    
}

static void smfu2_remove(void)
{
    smfu2_free_intervals();
    // clean up any allocated resources and stuff here.
    dev_dbg(DEV,"smfu2: deleting cdev of minor devices\n");
    cdev_del ( &smfu2.cdev_default );

    unregister_chrdev_region ( smfu2.devnr, SMFU_MINOR_COUNT );
    device_destroy(extoll_get_class_user(),smfu2.devnr); 
    smfu2_free_mmio();

    extoll_deregister_interrupt_handler(SNQ_TE_SMFU_TIMEOUT);
    printk ( KERN_INFO "smfu2: remove done\n" );
}

/******************************************************************************
 *  Module handling							      *
 ******************************************************************************/
static int __init smfu2_init(void)
{
    printk ( KERN_INFO "smfu2: Module init\n" );
    if (extoll_get_init_done()==0)
    {
        printk("EXTOLL Base driver not initialized! Bailing out\n");
        return -1;
    }
 
    return smfu2_probe();
}

static void __exit smfu2_exit(void)
{
    printk ( KERN_INFO "smfu2: Module exit\n" );
    smfu2_remove ();
}

MODULE_LICENSE ( "GPL" );
MODULE_AUTHOR ( "Holger Froening froening@uni-hd.de, Mondrian Nuessle mondrian.nuessle@extoll.de" );
MODULE_DESCRIPTION ( "Extoll R2: SMFU2 driver" );
MODULE_VERSION ( "1.0" );

module_init ( smfu2_init );
module_exit ( smfu2_exit );
