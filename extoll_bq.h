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
#ifndef _EXTOLL2_BQ_H_
#define _EXTOLL2_BQ_H_

#include "arch_define.h"

//includes needed to include this file
#include <linux/mm.h>

/* This file contains the Buffer Queue (BQ) driver */

#define VELO_BQ 1
#define RMA_BQ 2

#define BQ_MAX_QUEUE_NUMBER 256

#define _BQ_DEFAULT_DESC_SIZE (64*1024)

//maximum number of segments in one queue (hw limit!) is 512
#define BQ_MAX_SEGMENTS (4096/8)

//descriptor queue is max 4kb size, memory should be alloced with size 4 kb
#define DCQ_SIZE 4096

#define VELO_RP_OFFSET  0xd00000
#define RMA_RP_OFFSET   0xf00000

//descriptor entry valid bit
#define BQ_ENTRY_VALID 0x0400000000000000l

struct bq_descriptor {
  unsigned long ph_addr; //physical address of this queue entry
  void* k_v_addr; // kernel virtual address
  void* u_v_addr; // user space virtual address
  unsigned long size; //size in bytes of this entry
  uint64_t bde;//binary representation of the entry, as given to the HW
};
typedef struct bq_descriptor bq_descriptor_t;

struct extoll_bq {
  //which unit is this struct associated to: 0 - VELO 1 - RMA
  int unit_flag;
  //which slot size to use, either 16,32,64 or 128 byte. RMA should be 16, VELO is 64 or 128 byte.
  int slot_size;
  //which VPID ist this struct associated to
  int vpid;
  
  //the size of the mmemory currenctly allocated
  uint64_t size;
  //segment size to use
  uint64_t desc_size;
  //the physical address of the DCQ, the Descriptor Queue
  //entries reference the different buffer segments then
  unsigned long physical_address;
  //the kernel virtual address of the DCQ, the Descriptor Queue
  //entries reference the different buffer segments then
  uint64_t* virtual_address;
  
  //the physical address of the lrp register -> to map it into ua
  uint64_t rp_physical_address;
  //management info.
  int no_of_entries;
  struct bq_descriptor* descs; //pointer to the actual queue ear

  int current_descriptor; //the descriptor from which the data is read
  unsigned long current_slot; //the current slot in the current descriptor
  uint64_t *status_word; //the status word of the next message
  unsigned long outstanding_updates; //how many rp updates have not been commited to hw
};
typedef struct extoll_bq extoll_bq_t;

//allocates memory and fills the given bqd with a memory segment of size
extern int fill_bqd_struct(bq_descriptor_t* d, uint64_t size, int vpid, int slot_size);
//free a given bqd again
int destroy_bqd_struct(bq_descriptor_t* d);

//init the queue for one vpid with given parameters.
extoll_bq_t* bq_init_queue(uint64_t size, int unit_flag, int vpid,int slot_size, int desc_size, int* return_value);
//destroy one queue again
int bq_destroy_queue(extoll_bq_t* queue);
//activate a queue,
void bq_activate_bq(int unit_flag);
//de-activate a queue,
void bq_deactivate_bq(int unit_flag);
//mmap rp and memory space into user-space
int bq_mmap(struct vm_area_struct *vma, extoll_bq_t* queue );

uint64_t bq_get_desc_size(extoll_bq_t* queue);
void bq_set_desc_size(extoll_bq_t* queue,uint64_t size);

uint64_t bq_get_lrp(extoll_bq_t* queue);
void bq_set_lrp(extoll_bq_t* queue,uint64_t lrp);
uint64_t bq_get_lwp(extoll_bq_t* queue);
void bq_set_lwp(extoll_bq_t* queue,uint64_t lwp);

/*
 * Helper Functions for the EXTOLL Kernel API
 */
//increment the buffer queue rp by one, return outstanding rp updates that still need to be commited
int bq_read_slot_inc_rp(extoll_bq_t *bq);
//commit the buffer queue rp to HW, set the irq ack bit if requested
void bq_read_slot_commit_rp(extoll_bq_t *bq, int update_irq);
//get the current status word
uint64_t* bq_get_status_word(extoll_bq_t *bq);
//get the current slot
uint64_t* bq_get_current_slot(extoll_bq_t* bq);

#endif
