/*
*  Linux Kernel Driver for the SMFU-FPGA HTX platform.
*
*  Copyright (C) 2007 LSRA, University of Heidelberg
*
*  Written by Philipp Degler (2007)
*  based on the work of Mondrian Nuessle (2006)
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

#ifndef _SMFU2_H_
#define _SMFU2_H_

#include "arch_define.h"
/*!
\file smfu2drv
This is the driver of the SMFU functional unit of EXTOLL.
This driver enables user space applications to directly leverage
the low latency of SMFU using OS bypass operations.
The driver also offers a kernel based communication mechanism based
on the read and write system calls. Note that this mechanism is not
so well tested and should only be used with care.
*/
#include <linux/fs.h>
#include <linux/list.h>
#include <linux/cdev.h>
#include <linux/types.h>
#include <linux/kobject.h>

//#include "extoll_kernel.h"

//#include "smfu2_mod.h"
//#include "smfu2_ioctl.h"

//#include "extoll_map.h"
//#include "extoll_map_macro.h"

/* minors */
#define SMFU_MINOR_COUNT 	1	//Number of MINOR-Entries
#define SMFU_MINOR_DEFAULT	0	//Default-MINOR: 
//#define SMFU_MINOR_XXX	1	//not used

/* routing config */
//number of routing table entries = number of nodes
//#define SMFU_NUM_RLT	64

struct smfu2_interval {
  struct list_head list;
  uint64_t start;
  uint64_t stop;
  uint16_t node;
  uint8_t target_port;
  uint8_t valid;
  uint32_t ref_count;
  uint64_t  size;
  uint32_t interval_num; 
  uint64_t* v_addr;
};
typedef struct smfu2_interval smfu2_interval_t;



/******************************************************************************
*  Definition of smfu2 hardware info					      *
******************************************************************************/
/*!
  \brief The SMFU device structure
  This structure represents the SMFU functional unit of the EXTOLL hardware.
  BAR0: Register File for control & status
  BAR2: SMFU functional unit
 */
struct smfu2_device {
#ifdef MICEXTOLL
    struct micextoll_device *devp;
#else
    struct pci_dev *devp;        //! pointer to the pci device of EXTOLL
#endif
    struct cdev cdev_default;    //! the default character device file
    dev_t devnr;                 //! the major number of the SMFU device file
    struct device* dev;
    //void *bar0_vaddr;            //! kernel virtual address of BAR0 of the device. 
    //unsigned long bar0_addr;     //! physical virtual address of BAR0 of the device.
    //unsigned long bar0_size;     //! size of BAR0 of the device.
    void *global_mem_vaddr;            //! FIXME
    unsigned long global_mem_addr;     //! 
    unsigned long global_mem_size;     //! 
    void* target_virtual_address;     //! kernel virtual address of the local memory
    unsigned long target_size;        //! local memory size
    unsigned long target_physical_address; //! physical address of the local memorya

    /* Interval handling routines */
    struct list_head intervals_free_list;
    struct list_head intervals;
    spinlock_t interval_lock;
    smfu2_interval_t* hw_intervals[64];
    // smfu2_interval_t intervals[64];
    smfu2_interval_t* rra_interval;
};
/*!
 \brief List of all processes that use the SMFU
 This structur is part of a chaind list that record the processes that open
 a handel on the smfu.
 */
struct smfu2_process {
    struct  list_head list;          //! Kernel list
    struct task_struct* task;  //! process that created an handel
    //struct smfu2_process* next; //! next entry of list
};

/*!
 * \brief Hold management informations for SMFU context
 */

struct smfu2_context {
	int pid; //!PID of process that opend the SMFU
};

/******************************************************************************
*  shared function prototypes						      *
******************************************************************************/
void smfu2_reset_hw_intervals(void);

int smfu2_interval_modify_node(smfu2_interval_t* interval, uint16_t target_node);
int smfu2_free_interval(smfu2_interval_t* interval);
smfu2_interval_t* smfu2_reserve_interval(uint64_t size, uint16_t node, uint8_t target_port,int i_num_req);

int smfu2_sync_interval_to_hw(int i);

void smfu2_rra_write(int node, uint32_t r_address, uint64_t value);
uint64_t smfu2_rra_read(int node, uint32_t r_address);

void* smfu2_ioremap_nocache(smfu2_interval_t* interval);
void smfu2_iounmap(smfu2_interval_t* interval);


#endif
