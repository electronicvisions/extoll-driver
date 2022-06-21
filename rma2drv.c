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
#define RMA2DRV
#include "arch_define.h"

#include <linux/version.h>
#include <linux/fs.h>
#include <linux/pci.h> //TODO Check if we have to skip this for KNC compile
#include <linux/list.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/mutex.h>
#ifndef LS3BEXTOLL
#include <asm/mtrr.h>
#endif

#include <asm/uaccess.h>

#include "extoll_kernel_version_compability_layer.h"
#include "extoll_bq.h"
#include "extoll_kernel.h"
#include "extolldrv.h"
#include "extoll_rf_sysfs.h"
#include "atu2_drv.h"
#include "snq_decl.h"

#include "rma2_ioctl.h"
//#include "rma2_mod.h"
#include "rma2_region.h"
#include "rma2drv.h"

//for debugging purpose
#include <linux/jiffies.h>
#include <linux/delay.h>

//#define DEBUG(a) a
#define DEBUG(a) 
#define DEV rma2.dev

//Cache line size in quad words (64 bit units)
#define RMA2_LAZYNESS       4
#define RMA2_VPIDS          256
#define RMA2_NODES          (64*1024)

//default value of 2MB for one BQ -> 128k notifications in the queue
#define RMA2_DMA_SIZE_CMP   2097152

#define RMA2_REQUESTER_SIZE  4096
/******************************************************************************
*  module parameters (could be set at loadtime)			      *
******************************************************************************/
uint rma_dma_size_cmp = RMA2_DMA_SIZE_CMP;	//notification queue size
module_param(rma_dma_size_cmp, uint, S_IRUGO);

/******************************************************************************
*  Listinitialisation							      *
******************************************************************************/
//LIST_HEAD(velo_rport_list);	//all open requester ports
//LIST_HEAD(velo_cport_list);	//all open completer ports
//LIST_HEAD(velo_owner_list);	//all threads/processes owning ports

/******************************************************************************
*  Other Stuff
******************************************************************************/

static rma2_device_t rma2; 
static int aoi_recv_msg=0;

static rma_port_t* ports[RMA2_MAX_VPID];

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
//DECLARE_MUTEX(rma_mutex);	//mutex is initialized unlocked.
DEFINE_MUTEX(rma_mutex);	//mutex is initialized unlocked.

/******************************************************************************
*  helper functions      						      *
******************************************************************************/

  /* per Device Register access methods: */
  uint32_t rma_get_mtu(void)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_config();
    value= value & 0x3ffl;
    rma2.mtu=value;
    return rma2.mtu;
  }
EXPORT_SYMBOL(rma_get_mtu);

  static inline uint32_t rma_get_pcie_mode(void)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_config();
    value= (value& 0x70000l)>>16l;
    rma2.pcie_mode=value;
    return rma2.pcie_mode;
  }
    static inline uint32_t rma_get_force_error_notifications(void)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_config();
    value= (value & 0x100000000l) >> 32l;
    rma2.force_error_notifications=value;
    return rma2.force_error_notifications;
  }
    static inline uint32_t rma_get_read_engine_passpwd_disable(void)
  {
        uint64_t value;
    value=get_extoll_rf_rma_rf_config();
    value= (value & 0x200000000l) >> 33l;
    rma2.read_engine_passpwd_disable=value;
    return rma2.read_engine_passpwd_disable;
  }
    static inline uint32_t rma_get_lock_base_address(void)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_lock_base();
    rma2.lock_base_address=value;
    return rma2.lock_base_address;
  }
    static inline uint32_t* rma_get_lock_base_vaddress(void)
  {
    return rma2.lock_base_vaddress;
  }
    static inline uint32_t rma_get_lock_number_locks(void)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_lock_cfg();
    value= value & 0xffffffl;
    rma2.lock_number_locks=value;
    return rma2.lock_number_locks;
  }
    static inline uint32_t rma_get_lock_number_vpids(void)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_lock_cfg();
    value= (value & 0x1FF80000000) >> 31l;
    rma2.lock_number_vpids=value;
    return rma2.lock_number_vpids;
  }
    static inline uint32_t rma_get_lock_steering_tag(void)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_lock_cfg();
    value= (value & 0x7F800000000000l)>>47l;
    rma2.lock_steering_tag=value;
    return rma2.lock_steering_tag;
  }
    static inline uint32_t rma_get_lock_tph(void)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_lock_cfg();
    value= (value & 0x180000000000000l)>>55l;
    rma2.lock_tph=value;
    return rma2.lock_tph;
  }
    static inline uint32_t rma_get_lock_th(void)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_lock_cfg();
    value= (value & 0x200000000000000l)>>57l;
    rma2.lock_th=value;
    return rma2.lock_th;
  }
  static inline uint32_t rma_get_requester_history_mode(void)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_requester_error_ctrl();

    rma2.requester_history_mode=(value & 0x1l);
    return rma2.requester_history_mode;

  }
  static inline uint32_t rma_get_responder_history_mode(void)
  {
        uint64_t value;
    value=get_extoll_rf_rma_rf_responder_error_ctrl();

    rma2.responder_history_mode=(value & 0x1l);
    return rma2.responder_history_mode;

  }
  static inline uint32_t rma_get_completer_history_mode(void)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_completer_error_ctrl();

    rma2.completer_history_mode=(value & 0x1l);
    return rma2.completer_history_mode;

  }
  // only sets internal data structure
  static inline void rma_set_mtu(uint32_t mtu)
  {
    rma2.mtu=mtu & 0x3ff;
  }
  // only sets internal data structure
  static inline void rma_set_pcie_mode(uint32_t mode)
  {
    rma2.pcie_mode=mode & 0x7l;
  }
  static inline void rma_set_pcie_readrq(uint32_t mode)
  {
    rma2.pcie_readrq=mode & 0xfl;
  }
  
  // only sets internal data structure
  static inline void rma_set_force_error_notifications(uint32_t fen)
  {
  rma2.force_error_notifications=fen & 0x1l;
  }
  // only sets internal data structure
  static inline void rma_set_read_engine_passpwd_disable(uint32_t repd)
  {
    rma2.read_engine_passpwd_disable=repd & 0x1l;
  }
   //set hw register from internal data structure
  static inline void rma_set_config(void)
  {
    uint64_t value;
    value= ((rma2.read_engine_passpwd_disable & 0x1l) << 33l) |
           ((rma2.force_error_notifications & 0x1l) << 32l) |
           ((rma2.pcie_readrq & 0xfl) << 20l) |
           ((rma2.pcie_mode & 0x7l) << 16l) |
           ((rma2.mtu & 0x3ffl));

    set_extoll_rf_rma_rf_config(value);
  }
  
  // only sets internal data structure &  address
  static inline void rma_set_lock_base_address(uint64_t paddress)
  {
    rma2.lock_base_address=paddress;
    set_extoll_rf_rma_rf_lock_base(rma2.lock_base_address);
  }
  
  // only sets internal data structure
  static inline void rma_set_lock_base_vaddress(uint32_t* vaddress)
  {
    rma2.lock_base_vaddress=vaddress;
  }
  
  // only sets internal data structure
  static inline void rma_set_lock_number_locks(uint32_t lock_numbers)
  {
    rma2.lock_number_locks=lock_numbers & 0xffffffl;
  }
  // only sets internal data structure
  static inline void rma_set_lock_number_vpids(uint32_t lock_numbers_per_vpid)
  {
    rma2.lock_number_vpids=lock_numbers_per_vpid & 0x3ffl;
  }
  // only sets internal data structure
  static inline void rma_set_lock_steering_tag(uint32_t steering_tag)
  {
    rma2.lock_steering_tag=steering_tag & 0xffl;
  }
  // only sets internal data structure
  static inline void rma_set_lock_tph(uint32_t tph)
  {
    rma2.lock_tph=tph & 0x3l;
  }
  // only sets internal data structure
  static inline void rma_set_lock_th(uint32_t th_enable)
  {
    rma2.lock_th=th_enable & 0x1l;
  }
  //set hw register from internal data structure
  static inline void rma_set_lock_config(void)
  {
    uint64_t value;
    value= ((rma2.lock_th & 0x1l) << 57l) |
	   ((rma2.lock_tph & 0x3l) << 55l) |
	   ((rma2.lock_steering_tag & 0x8l) << 47l) |
	   ((rma2.lock_number_vpids & 0x1ffl) << 31l) |
	   ((rma2.lock_number_locks & 0xffffffl));

    set_extoll_rf_rma_rf_lock_cfg(value);
  }
  
   //updates internal state and hw!
  static inline void rma_set_requester_history_mode(uint32_t mode)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_requester_error_ctrl();
    rma2.requester_history_mode=mode & 0x1l;
    value= (value & 0xFFFFFel) | (mode & 0x1l);
    set_extoll_rf_rma_rf_requester_error_ctrl(value);    
  }
  //updates internal state and hw!
  static inline void rma_set_responder_history_mode(uint32_t mode)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_responder_error_ctrl();
    rma2.responder_history_mode=mode & 0x1l;
    value= (value & 0xFFFFFel) | (mode & 0x1l);
    set_extoll_rf_rma_rf_responder_error_ctrl(value);    
  }
  //updates internal state and hw!
  static inline void rma_set_completer_history_mode(uint32_t mode)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_completer_error_ctrl();
    rma2.completer_history_mode=mode & 0x1l;
    value= (value & 0xFFFFFel) | (mode & 0x1l);
    set_extoll_rf_rma_rf_completer_error_ctrl(value);    
  }
  
  static inline uint32_t rma_get_bq_timeout(void)
  {
     uint64_t value;
    value=get_extoll_rf_rma_rf_bq_timeout();
    rma2.bq_timeout=value & 0xffffffffl;
    return rma2.bq_timeout;
  }
  
  static inline uint32_t rma_get_bq_timeout_enable(void)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_bq_timeout();
    rma2.bq_timeout_enable=(value>>32l) & 0x1l;
    return rma2.bq_timeout_enable;
  }
  
  static inline void rma_set_bq_timeout(uint32_t timeout)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_bq_timeout();
    rma2.bq_timeout=timeout & 0xffffffffl;
    value= (value & 0x100000000l) | (timeout & 0xFFFFFFFFl);
    set_extoll_rf_rma_rf_bq_timeout(value);    
  }
  
  static inline void rma_set_bq_timeout_enable(uint32_t enable)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_bq_timeout();
    rma2.bq_timeout_enable=enable & 0x1l;
    value= (( ((uint64_t)rma2.bq_timeout_enable)<<32l) & 0x100000000l) | (value & 0xFFFFFFFFl);
    set_extoll_rf_rma_rf_bq_timeout(value);    
  }
 
   static inline void rma_set_wcbuf_timeout(uint32_t timeout)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_wcbuf_rf_timeout();
    rma2.wcbuf_timeout=timeout;
    value=  ( (((uint64_t)timeout)) << 32l) | (value & 0xffffffffl);
    set_extoll_rf_rma_rf_wcbuf_rf_timeout(value);    
  }
  
  static inline void rma_set_wcbuf_timeout_enable(uint32_t enable)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_wcbuf_rf_timeout();
    rma2.wcbuf_timeout_enable=enable & 0x1l;
    value= (value & 0xfffffffffffffffel) | ((uint64_t)enable & 0x1l);
    set_extoll_rf_rma_rf_wcbuf_rf_timeout(value);    
  }

  
  /* per VPID Register access methods: */
  static inline uint32_t rma_get_vpid_en(uint32_t vpid)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_vpid_table(vpid);

    ports[vpid]->vpid_en=value & 0x1l;
    return ports[vpid]->vpid_en;

  }
  static inline uint32_t rma_get_tu_completer(uint32_t vpid)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_vpid_table(vpid);

    ports[vpid]->tu_completer=(value & 0x00000el)>>1l;
    return ports[vpid]->tu_completer;

  }
  static inline uint32_t rma_get_tu_responder(uint32_t vpid)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_vpid_table(vpid);

    ports[vpid]->tu_responder=(value & 0x0070l)>>4l;
    return ports[vpid]->tu_responder;

  }
  static inline uint32_t rma_get_excell_enable(uint32_t vpid)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_vpid_table(vpid);

    ports[vpid]->excell_enable=(value & 0x0080l)>>7l;
    return ports[vpid]->excell_enable;

  }
  static inline uint32_t rma_get_tc0(uint32_t vpid)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_vpid_table(vpid);

    ports[vpid]->tc0=(value & 0x0300l)>>8l;
    return ports[vpid]->tc0;

  }
  static inline uint32_t rma_get_tc1(uint32_t vpid)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_vpid_table(vpid);

    ports[vpid]->tc1=(value & 0x0c00l)>>9l;
    return ports[vpid]->tc1;

  }
  static inline uint32_t rma_get_tc2(uint32_t vpid)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_vpid_table(vpid);

    ports[vpid]->tc2=(value & 0x3000l)>>11l;
    return ports[vpid]->tc2;

  }
  static inline uint32_t rma_get_tc3(uint32_t vpid)
  {
        uint64_t value;
    value=get_extoll_rf_rma_rf_vpid_table(vpid);

    ports[vpid]->tc3=(value & 0xC000l)>>13l;
    return ports[vpid]->tc3;

  }
  static inline uint32_t rma_get_protection_descriptor(uint32_t vpid)
  {
        uint64_t value;
    value=get_extoll_rf_rma_rf_vpid_table(vpid);

    ports[vpid]->protection_descriptor=(value & 0xffff0000l)>>15l;
    return ports[vpid]->protection_descriptor;
  }
  
  static inline uint32_t rma_get_th_enable(uint32_t vpid)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_vpid_table(vpid);

    ports[vpid]->th=(value & 0x040000000000)>>41l;
    return ports[vpid]->th;

  }
  static inline uint32_t rma_get_tph_bits(uint32_t vpid)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_vpid_table(vpid);

    ports[vpid]->tph=(value & 0x30000000000)>>39l;
    return ports[vpid]->tph;

  }
  static inline uint32_t rma_get_steering_tag(uint32_t vpid)
  {
    uint64_t value;
    value=get_extoll_rf_rma_rf_vpid_table(vpid);

    ports[vpid]->steering_tag=(value & 0xFF00000000)>>31l;
    return ports[vpid]->steering_tag;

  }


  // only sets internal data structure
  static inline void rma_set_vpid_en(uint32_t vpid, uint32_t enable)
  { 
    ports[vpid]->vpid_en=enable & 0x1l;
  }
  // only sets internal data structure
  static inline void rma_set_tu_completer(uint32_t vpid,uint32_t tu)
  {
    ports[vpid]->tu_completer=tu & 0x7l;
  }
  // only sets internal data structure
  static inline void rma_set_tu_responder(uint32_t vpid,uint32_t tu)
  {
    ports[vpid]->tu_responder=tu & 0x7l;
  }
  // only sets internal data structure
  static inline void rma_set_excell_enable(uint32_t vpid,uint32_t tu)
  {
    ports[vpid]->excell_enable=tu & 0x1l;
  }
  // only sets internal data structure
  static inline void rma_set_tc0(uint32_t vpid,uint32_t tc)
  {
    ports[vpid]->tc0=tc & 0x3l;
  }
  // only sets internal data structure
  static inline void rma_set_tc1(uint32_t vpid,uint32_t tc)
  {
    ports[vpid]->tc1=tc & 0x3l;
  }
  // only sets internal data structure
  static inline void rma_set_tc2(uint32_t vpid,uint32_t tc)
  {
    ports[vpid]->tc2=tc & 0x3l;
  }
  // only sets internal data structure
  static inline void rma_set_tc3(uint32_t vpid,uint32_t tc)
  {
    ports[vpid]->tc3=tc & 0x3l;
  }
  // only sets internal data structure
  static inline void rma_set_protection_descriptor(uint32_t vpid,uint16_t protection_descriptor)
  {
    ports[vpid]->protection_descriptor=protection_descriptor & 0xffffl;
  }
  // only sets internal data structure
  static inline void rma_set_tph_bits(uint32_t vpid,uint32_t th_enable, uint32_t tph, uint32_t steering_tag)
  {
    ports[vpid]->tph=tph & 0x3l;
    ports[vpid]->th=th_enable & 0x1l;
    ports[vpid]->steering_tag=steering_tag & 0xffl;
  }
  // copies internal data to hw entry
  static inline void rma_set_vpid_ram_entry(uint32_t vpid)
  {
     uint64_t value;
     value= ((ports[vpid]->th & 0x1l)<<42l)| ((ports[vpid]->tph & 0x3l)<<40l) |((ports[vpid]->steering_tag&0xffffl)<<32l) |
	    ((ports[vpid]->protection_descriptor&0xffffl)<<16l) | 
	    ((ports[vpid]->tc3&0x3l)<<14l) | ((ports[vpid]->tc2&0x3l)<<12l) | ((ports[vpid]->tc1&0x3l)<<10l) | ((ports[vpid]->tc0&0x3l)<<8l) |
	    ((ports[vpid]->excell_enable & 0x1l)<<7l) |
	    ((ports[vpid]->tu_responder&0x7l)<<4l) | ((ports[vpid]->tu_completer&0x7l)<<1l) | (ports[vpid]->vpid_en& 0x1l);
     dev_dbg(DEV,"writing %lx into vpid ram entry for vpid %d\n",(long unsigned int)value,vpid);
     set_extoll_rf_rma_rf_vpid_table(vpid,value);
  }
  
 

/**
* reads details of a completer port descriptor. If descriptor
* does not exist it is created and gets added to the completer list
*
* @param nump	port number of requester
*/
static rma_port_t *rma2_get_port(int i)
{
  return ports[i];
}

/**
get the logical read pointer
*/
uint64_t rma2_get_rp(rma_port_t *portp)
{
  uint64_t value;
  if ( portp->bq)
   value=bq_get_lrp(portp->bq);
  else
    value=0xffffffffffffffffl;
  dev_dbg(DEV,"logical read pointer is %llx\n", value);      

  return value;
} 


/**
set the logica read pointer
*/
static void rma2_set_rp(rma_port_t *portp, uint64_t new_rp)
{
  portp->rp=new_rp;
  portp->wb_rp=new_rp;

  if ( portp->bq)
   bq_set_lrp(portp->bq,new_rp);
}

/**
* Retrieves the actual write pointer of the rma notia
* The write pointer has a size of 64 bit at the moment.
* @param *portp: Every queue has a seperate write pointer.
*                 Therefor portp allows the function to find
*                 out what mailbox is meant.
*/
uint64_t rma2_get_wp(rma_port_t *portp)
{
  uint64_t value;
  if ( portp->bq)
    value=bq_get_lwp(portp->bq);
  else
    value=0xffffffffffffffffl;
  
  dev_dbg(DEV,"logical write pointer is %llx\n", value);      

  return value;
}

/**
* Sets the write pointer of the rma notiq
* @param *portp: completer port management data
*/
static void rma2_set_wp(rma_port_t *portp, uint64_t new_wp)
{
  if ( portp->bq)
    bq_set_lwp(portp->bq,new_wp);
}

static void rma2_release_port(rma_port_t* portp)
{
	if (portp!=NULL)
	{
	  dev_dbg(DEV,"destroying port %d\n",portp->vpid);
	  if (portp->bq!=NULL)
		bq_destroy_queue(portp->bq);
	  memset(portp,0,sizeof(rma_port_t));
	}
}


int rma2_find_free_vpid(void)
{
  int i;
  int vpid_increment;
  //find the number of vpids per page, if system has larger page size -> then only every xth vpid should be used
  vpid_increment=extoll_query_vpids_per_page();
  
  dev_dbg(DEV,"Looking for free vpid...\n");
  for (i=0;i<EXTOLL_VPID_MAX;i=i+vpid_increment)
  {
    if (ports[i]->opened==0)
    {
      dev_dbg(DEV,"Return free VPID: %u\n",i);
      return i;
    }
  }
  dev_info(DEV,"No free vpid found...\n");
  return -1;
}
int rma2_check_free_vpid(int vpid)
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

int rma2_find_owned_vpid(int pid)
{
  int i;
  dev_dbg(DEV,"Looking for  vpid owned by pid %u...\n",pid);
  for (i=0;i<RMA2_MAX_VPID;i++)
    {
      if (ports[i]->pid!=pid)
        {
          dev_dbg(DEV,"Found vpid %d\n",i);
          return i;
        }
    }
  dev_dbg(DEV,"No vpid found\n");
  return -1;
}

int rma2_lock_mutex(void)
{
 mutex_lock(&rma_mutex);
 return 0;
}
EXPORT_SYMBOL(rma2_lock_mutex);

void rma2_unlock_mutex(void)
{
 mutex_unlock(&rma_mutex);
}
EXPORT_SYMBOL(rma2_unlock_mutex);


//used by kapi and user space
int rma2_init_port(rma_port_t **portp,int vpid)
{
  uint64_t old_wcb_state;
  uint64_t new_wcb_state;
  if (vpid==-1)
    vpid=rma2_find_free_vpid();
  else
    vpid = rma2_check_free_vpid(vpid);
  
  if (vpid==-1)  //all VPIDs in use
  {
    dev_info(DEV,"All VPIDs in use.\n");
    return -EBUSY;
  }
  
  *portp = rma2_get_port(vpid);
  if (*portp==0) {
    dev_alert(DEV,"no port available\n");
    return -EFAULT;
  }
  dev_dbg(DEV,"got portp for pid %ld\n",(long int)current->pid);
  /* init new port */
  memset(*portp,0,sizeof(rma_port_t));
  (*portp)->pid = current->pid;
  //register to nw_list should happen here, as now we know the task and the vpid
  
  //atomic_set(&ownerp->rcount, 0);
  (*portp)->opened++;
  (*portp)->kernel_owned=0;
  (*portp)->vpid=vpid;
  /* init registerfile for this VPID */
  rma_set_vpid_en(vpid,1);
  rma_set_tu_completer(vpid,1);
  rma_set_tu_responder(vpid,2);
  rma_set_excell_enable(vpid,0);
  rma_set_tc0(vpid,1);
  rma_set_tc1(vpid,1);
  rma_set_tc2(vpid,3);
  rma_set_tc3(vpid,3);
  rma_set_protection_descriptor(vpid,0);
  rma_set_tph_bits(vpid,0,0,0);
  rma_set_vpid_ram_entry(vpid);
  
//   portp->mbox_size=velo_dma_size_cmp;
  (*portp)->wb_rp=0;
  (*portp)->rp=0;

  init_waitqueue_head(&((*portp)->wq));
  (*portp)->poll_times=1000; //default  number of kernel poll spins
  (*portp)->poll_flag=0;
  (*portp)->async_flag=0;
  if (PAGE_SIZE > 64*1024)
    (*portp)->desc_size=PAGE_SIZE;
  else
    (*portp)->desc_size=64*1024;
  (*portp)->notiq_size=rma_dma_size_cmp;

   old_wcb_state=get_extoll_rf_rma_rf_wcbuf_rf_state(vpid);
   new_wcb_state=old_wcb_state & 0x00ffffffff000000l;
   set_extoll_rf_rma_rf_wcbuf_rf_state(vpid, new_wcb_state);
   dev_dbg(DEV,"vpid %d: wcb old state was %lx, new state will be %lx\n",vpid,(unsigned long)old_wcb_state,(unsigned long)new_wcb_state);


  return 0;
}
EXPORT_SYMBOL(rma2_init_port);

//used by KAPI
int rma2_init_completer(rma_port_t *port)
{
  int result;

  if(port->bq!=NULL) 
    bq_destroy_queue(port->bq);
  
  port->bq = bq_init_queue(port->notiq_size,RMA_BQ, port->vpid, 16,port->desc_size,&result); 
  if (port->bq==0) {
    dev_alert(DEV,"memory allocation for VPID %d receive queue failed (BQ).\n", port->vpid);
    return result;
  }
  return 0;
}
EXPORT_SYMBOL(rma2_init_completer);

//used by kapi and for user space
int rma2_close_port(rma_port_t *port)
{
  int vpid;
  int i;

  vpid=(port)->vpid;
  
  //release all memory locks for this VPID
  if (atu2_unregister_vpid_pages(vpid,0) > 0 ) { //some pages had to be unregistered
    mdelay(100);
  }

  //set all the registers for the VPID
  rma_set_vpid_en(vpid,0);
  rma_set_tu_completer(vpid,1);
  rma_set_tu_responder(vpid,2);
  rma_set_excell_enable(vpid,0);
  rma_set_tc0(vpid,1);
  rma_set_tc1(vpid,1);
  rma_set_tc2(vpid,3);
  rma_set_tc3(vpid,3);
  //rma_set_protection_descriptor(vpid,0xffff);
  rma_set_protection_descriptor(vpid,0x0);
  rma_set_tph_bits(vpid,0,0,0);
  rma_set_vpid_ram_entry(vpid);

    //reset locks for this vpid to zero
  for (i=0;i<rma2.lock_number_locks;i++)
  {
    rma2.lock_base_vaddress[vpid+(i*256)]=0;
  }
  
  rma2_release_port((port));
  

  dev_dbg(DEV,"port was succesfully released.\n");
  return 0;
}
EXPORT_SYMBOL(rma2_close_port);

/******************************************************************************
*  file operations of rma2 device					      *
******************************************************************************/
/**
* Check if process already opened rma. If not create new owner list entry
* and add it to the list of owners
*/
static int rma2_open(struct inode *inodp, struct file *filp)
{
  rma_port_t *portp;
  int minor;
  unsigned int current_uid;
  unsigned int inode_uid;
  int result;
  uint64_t register_value= 0;

  minor = MINOR(inodp->i_rdev);
  current_uid=EKVCL_get_uid_val(get_current_user()->uid);
  inode_uid=EKVCL_get_uid_val(inodp->i_uid);

  if (minor!=RMA2_MINOR)
  {
	dev_alert(DEV,"trying to open invalid minor.\n");      
	return -EINVAL;
  }

  /* check if network is ready -> if not return -EAGAIN
   */
  if (extoll_get_nw_state()!=EXTOLL_NW_STATE_C) { //network not configured
	  if (current_uid!=inode_uid) {
		  return -EAGAIN;
	  } else {
		  dev_info(DEV, "Granting Access to RMA2 although network is not configured because calling process is running as %u\n",inode_uid);
	  }
  }


  if (mutex_lock_interruptible(&rma_mutex)) {
        return -ERESTARTSYS;
  }

 dev_dbg(DEV,"opened rma2 special file with minor %d\n",minor);

  //request a port with arbitrary VPID
  result=rma2_init_port(&portp,-1);
  
   /* register this task with the nw state task monitoring facitilty (to it gets stopped if necessary) */
  if (current_uid!=inode_uid)
  	extoll_add_nw_state_task(portp->vpid, RMA_VPID, current);
  //Network state could have changed after last check, so check again if we are in stopped state:
  
  register_value=get_extoll_rf_info_rf_scratchpad_scratchpad(EXTOLL_SCRATCH_NETWORK_STATE);
  if(register_value != 1) {
	  force_sig(SIGSTOP, current);
  }
 
  mutex_unlock(&rma_mutex);      

  dev_dbg(DEV,"opened device by pid:%d got vpid %d!\n",(int)portp->pid,portp->vpid);
      
  /* assign to filp for fast access */
  filp->private_data = portp;
  aoi_recv_msg=0; 

  if (result!=0) {
    if (current_uid!=inode_uid)
     extoll_remove_nw_state_task(portp->vpid, RMA_VPID);
  }

  //atu2_unregister_vpid_pages(portp->vpid,0);

 //extoll_set_interrupt_counter(0);       

  return result;
}

/**
* standard file ops are used to access config entries of velo ports
* llseek changes position to the port(offset) that should be next read
* or written from.
*/

//not supported any more...
static loff_t rma2_llseek(struct file *filp, loff_t off, int whence)
{
  return -EFAULT;
}


/**
* whenever a process releases the velo device his kalloced mem has to be
* cleared and all used ports have to be freed.
*/
static int rma2_release(struct inode *inodp, struct file *filp)
{
  rma_port_t* portp;
  int result;

  dev_dbg(DEV,"release called [pid %d]\n", (int)current->pid);
  portp = filp->private_data;

  if (portp==0) {
    dev_alert(DEV,"rma2_release called, but no port to destroy, return...\n");
    return 0;
  }
 if (mutex_lock_interruptible(&rma_mutex)) {
        return -ERESTARTSYS;
      }

  result=rma2_close_port(portp);

  //remove task from nw state monitoring
  extoll_remove_nw_state_task(portp->vpid, RMA_VPID);
  
  mutex_unlock(&rma_mutex);
  return result;
}

/********************************************************************************/
/*  VMA operations                                                             **/
/* ******************************************************************************/

/******************************************************************************
*  velo memory mappings                                                       *
******************************************************************************/
/**
* Map a requester port into userspace. 
* There is only one port per VPID anymore.
* First implementation will map the minimum, which is one page!
*/
static int rma2_mmap_req(rma_port_t *portp, struct vm_area_struct *vma)
{
  unsigned long vsize = 0;	// size of needed virtual address space
  unsigned long physical = 0;	// physical start address
  unsigned long pfn;	// page frame number
  int err;		// error code
  int i;

  vsize = vma->vm_end - vma->vm_start;
  dev_dbg(DEV,"mmap called for requester space. offset is %lx, vpid is %d\n",
        (unsigned long)vma->vm_pgoff << PAGE_SHIFT,portp->vpid);
    
  if (!( ((vsize==32*PAGE_SIZE) ) && (vsize % PAGE_SIZE==0) )) { // map 32*4k for requester or page size if this is larger  
    dev_alert(DEV,"trying to map req for vpid %d, but requesed size (%ld) is not valid with the machine page size\n", portp->vpid, PAGE_SIZE);
    return -EINVAL;
  }

  if ( (vsize == 32*PAGE_SIZE)) {
    for (i=0;i<32;i++) {
      physical = extoll_get_rma2_addr() +  RMA2_REQUESTER_SIZE * portp->vpid + (i*256*4096);
      dev_dbg(DEV,"Mapped Requester for source vpid %x, at requester position %x, resulting physical address %lx rma base is %lx\n", 
	     portp->vpid, RMA2_REQUESTER_SIZE * portp->vpid + (i*256*4096), physical, (unsigned long) extoll_get_rma2_addr());
     
      //printk("rma2: requester (wc): given physical %lx, vsize %lu, vm_start is %lx\n", physical, vsize,vma->vm_start);

      pfn = physical >> PAGE_SHIFT;
      dev_dbg(DEV,"pfn is: %lx\n", pfn);
      //set WC protection -> own defin from arch_define.h
     vma->vm_page_prot=__pgprot(pgprot_val(vma->vm_page_prot) | EXTOLLWCATTR);

      io_remap_pfn_range(vma, vma->vm_start+i*PAGE_SIZE, pfn, PAGE_SIZE, vma->vm_page_prot);
    }
    dev_dbg(DEV,"remapping iomem.\n");

  } else {
    dev_alert(DEV,"Illegal mmap request for requester \
                port %lx\n", vma->vm_pgoff);
    err = -EFAULT;
    goto out_err;
  }
  return 0;

out_err:
  return err;
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
static int rma2_mmap_cmp(rma_port_t *portp, struct vm_area_struct *vma)
{
  int  result;
 
  if (portp->bq!=NULL)
	bq_destroy_queue(portp->bq);
  dev_dbg(DEV,"cmp mmap called. now calling bq_init_queue with size of %u\n",portp->notiq_size);
  
  portp->bq=bq_init_queue(portp->notiq_size,RMA_BQ, portp->vpid, 16,portp->desc_size,&result);
  if (portp->bq==0)
  {
    dev_alert(DEV,"memory allocation for VPID %d receive queue failed (BQ).\n", portp->vpid);
    return -1;
   }
  dev_dbg(DEV,"calling bq_mmap\n");
  result=bq_mmap(vma,portp->bq);    
  return result;
}

static int rma2_mmap_wcbufstate(rma_port_t *portp, struct vm_area_struct *vma)
{
  unsigned long physical = 0;
  unsigned long pfn;	// page frame numbers
  int err=0;
  
  if (vma->vm_end - vma->vm_start != PAGE_SIZE)
  {
    dev_alert(DEV,"trying to map wcbuf state for vpid %d, but requesed size (%ld) is not a page\n", portp->vpid, PAGE_SIZE);
    return -EINVAL;
  }

  if (vma->vm_end - vma->vm_start == PAGE_SIZE) {
      physical = extoll_get_rf_addr() + 0x1400000l+ (4096 * portp->vpid);
      pfn = physical >> PAGE_SHIFT;
      io_remap_pfn_range(vma, vma->vm_start, pfn, PAGE_SIZE, vma->vm_page_prot);
      
      
      dev_dbg(DEV,"mmaping wcbuf state to user space. address is %lx vpid is %d\n",physical,portp->vpid);
   }
   else {
    dev_alert(DEV,"Illegal mmap request for wcbuf state \
                port %lx\n", vma->vm_pgoff);
    err = -EFAULT;
    goto out_err;
  }
  return 0;

out_err:
  return err;
}

static int rma2_mmap(struct file *filp, struct vm_area_struct *vma)
{
  int err=0;
  unsigned long off;	// complete offset starting from bar2
  rma_port_t *portp;    // owner of mmaped port


  dev_dbg(DEV,"map for port %lu!!\n",vma->vm_pgoff);
  off = vma->vm_pgoff << PAGE_SHIFT;

  portp = filp->private_data;   //created in velo_open()
  if (portp==0)
  {
    dev_alert(DEV,"mmaping rx no port available\n");
    return -EFAULT;
  }

  if (portp->vpid % extoll_query_vpids_per_page() != 0 ) //machine with odd page size, check whether vpid is supported
    {
      dev_alert(DEV,"mmaping completer for vpid %d, which is not supported with page size %ld\n",portp->vpid,PAGE_SIZE);
      return -EFAULT;
    }



  if (mutex_lock_interruptible(&rma_mutex)) {
        return -ERESTARTSYS;
  }


  /* do real mmap in seperate function
  */
  if (off==0) //mmap one of the TX side pages
  {
      dev_dbg(DEV,"requester\n");
      err = rma2_mmap_req(portp, vma);
      dev_dbg(DEV,"requester mmap returns %d\n",err);
  }
  else if (off==32*4096 || off==PAGE_SIZE) //mmap the wcbuf page
  {
    dev_dbg(DEV,"wcbuf state\n");
    err=rma2_mmap_wcbufstate(portp, vma);
  }
  else //mmap RX side
  {
	dev_dbg(DEV,"completer\n");
	err = rma2_mmap_cmp(portp, vma);
	dev_dbg(DEV,"completer mmap returns %d\n",err);
  }
  dev_dbg(DEV,"mmap call done\n");
  mutex_unlock(&rma_mutex);
  return err;
}

/******************************************************************************
 * Helper functions for the EXTOLL Kernel API				      *
 * 2011 by Tobias Groschup				      *
 * FIXME: reduce copypasta, respect DRY ;)
 *****************************************************************************/
/**
 * Returns a struct with the needed pointers to access the rma-device
 */
rma2_device_t* rma2_get_device(void)
{
  return &rma2;
}


/**
 * returns the mbox_id
 */

uint32_t rma2_get_nodeid()
{
  rma2.nodeid=(get_extoll_rf_info_rf_node()>>24l) & 0xffffl;
  return rma2.nodeid;
}


/**
 * get the notiq size for a port
 */

uint rma2_get_notiq_size(uint16_t vpid)
{
  return ports[vpid]->notiq_size;
}

/******************************************************************************
*  IO controls			                                              *
******************************************************************************/
//static int rma2_ioctl(struct inode *inodp, struct file *filp,
                      //unsigned int cmd, unsigned long arg)
static long rma2_ioctl_unlocked( struct file *filp,
                      unsigned int cmd, unsigned long arg)
{
  rma_port_t * portp;
  //int minor;
  int result;
  RMA2_Region region;
  
  portp = filp->private_data;
  //minor = MINOR(inodp->i_rdev);

  if (portp==NULL) {
    dev_alert(DEV,"ioctl: invalid port\n");
    return -EFAULT;
  }

 // Do some security tests on the requested command number
  if (_IOC_TYPE(cmd) != RMA2_IOC_MAGIC)
    return -ENOTTY;

  if (_IOC_NR(cmd) > RMA2_IOC_MAXNR)
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
  case (RMA2_IOCTL_GET_NOTIQ_RP):
    {
      uint64_t rp;
      rp =  rma2_get_rp(portp);
      return put_user(rp, ((uint64_t *) arg));
      break;
    }
  case (RMA2_IOCTL_SET_NOTIQ_RP):
    {
      rma2_set_rp(portp, ((uint64_t) arg));
      break;
    }
  case (RMA2_IOCTL_GET_NOTIQ_WP):
    {
      uint64_t wp;
      wp = rma2_get_wp(portp);
      return put_user(wp, ((uint64_t *) arg));
      break;
    }
  case (RMA2_IOCTL_SET_NOTIQ_WP):
    {
      rma2_set_wp(portp, ((uint64_t) arg));
      break;
    }
  case (RMA2_IOCTL_GET_VPID):       
    {         
      uint32_t vpid=portp->vpid;
      return put_user(vpid, ((uint64_t*) arg));
      break;
    }
  case (RMA2_IOCTL_GET_NODEID):       
    {         
     // uint32_t nodeid=UNIT_TYPE__NODE_ID__READ(read64(&extoll_rf->ids));
      uint64_t value=rma2_get_nodeid();
      dev_dbg(DEV,"RMA2_IOCTL_GET_NODEID will return %lu\n",(unsigned long)value);
      return put_user(value, ((uint64_t*) arg));
      break;
    }
  case (RMA2_IOCTL_GET_NOTIQ_SIZE):       
    {         
      uint64_t size=portp->notiq_size;
      return put_user(size, ((uint64_t*) arg));
      break;
    }
  case (RMA2_IOCTL_SET_NOTIQ_SIZE):       
    {         
      if (arg % PAGE_SIZE != 0 )
      {
          dev_alert(DEV,"noti queue size requested to be %ld which is not a multiple of the machine page size (%ld), which is not supported\n",arg, PAGE_SIZE);
          return -EFAULT;
      }
      portp->notiq_size=arg;    
      dev_dbg(DEV,"setting queue size to %lu\n",arg);
      break;
    }
  case (RMA2_IOCTL_GET_NOTIQ_SEGMENT_SIZE):       
    {         
      uint32_t size=portp->desc_size;
      return put_user(size, ((uint64_t*) arg));
      break;
    }
  case (RMA2_IOCTL_SET_NOTIQ_SEGMENT_SIZE):       
    { 
        if (arg % PAGE_SIZE != 0 )
          {
            dev_alert(DEV,"segment size requested to be %ld which is not a multiple of the machine page size (%ld), which is not supported\n",arg, PAGE_SIZE);
            return -EFAULT;
          }
      portp->desc_size=arg;    
      break;
    }
  case (RMA2_IOCTL_GET_PROTDESC):       
    {         
      uint32_t vpid=portp->vpid;
      uint64_t descriptor=rma_get_protection_descriptor(vpid);
      return put_user(descriptor, ((uint64_t*) arg));
      break;
    }
  case (RMA2_IOCTL_SET_PROTDESC):
    {
      uint32_t vpid=portp->vpid;
      rma_set_protection_descriptor(vpid, (uint16_t)(arg & 0xffffl));
      rma_set_vpid_ram_entry(vpid);
      break;
    }
  case (RMA2_IOCTL_GET_MAXNODEID):
    {
      uint32_t vpid=RMA2_NODES;
      return put_user(vpid, ((uint64_t*) arg));
      break;
    }
  case (RMA2_IOCTL_GET_MAXVPID):
    {
      uint32_t nodeid=RMA2_VPIDS;
      return put_user(nodeid, ((uint64_t*) arg));
      break;
    }
   case (RMA2_IOCTL_REGISTER_REGION): 
   {
      uint32_t vpid=portp->vpid;
      
      result=copy_from_user(&region, ((uint64_t*) arg), sizeof(RMA2_Region));
      if (result!=0)
      {
	dev_alert(DEV,"ioctl (RMA_IOCTL_REGISTER_REGION) copy from user failed: %p Bytes not copied: %d Requested to be copied: %ld\n",(void*)arg,result,sizeof(RMA2_Region));
	result= -EFAULT;
	return result;
      }
      dev_dbg(DEV,"Region: va=%p, size=%lu,  count=%u\n",region.start, region.size, region.count);
      dev_dbg(DEV,"Need to allocate %lu bytes for the NLAs\n",region.count * sizeof(unsigned long));
      
      if (mutex_lock_interruptible(&rma_mutex)) {
	return -ERESTARTSYS;
      } 
      result=atu2_register_virtual_region(vpid, (unsigned long)region.start, region.size, 1, 1, &region.nla);
      mutex_unlock(&rma_mutex);
      if (result!=0)
      {
	dev_alert(DEV,"ioctl (RMA_IOCTL_REGISTER_REGION) atu_register_virtual_region failed with error code %d\n",result);
	result= -EFAULT;
	return result;
      }
      result|=copy_to_user(((uint64_t*) arg), &region, sizeof(RMA2_Region));
      break;
    }
  case (RMA2_IOCTL_UNREGISTER_REGION):       
    {  
      uint32_t vpid=portp->vpid;
      result=copy_from_user(&region, ((uint64_t*) arg), sizeof(RMA2_Region));
      if (result!=0)
      {
	dev_alert(DEV,"ioctl (RMA_IOCTL_UNREGISTER_REGION) copy from user failed: %p Bytes not copied: %d Requested to be copied: %ld\n",(void*)arg,result,sizeof(RMA2_Region));
	result= -EFAULT;
	return result;
      }
      if (mutex_lock_interruptible(&rma_mutex)) {
	return -ERESTARTSYS;
      } 
      result=atu2_unregister_virtual_region(vpid, region.nla, region.size);
      mutex_unlock(&rma_mutex);
      if (result!=0)
      {
	dev_alert(DEV,"ioctl (RMA_IOCTL_UNREGISTER_REGION) atu_unregister_virtual_region failed with error code %d\n",result);
	result= -EFAULT;
	return result;
      }
      break;
    }
  case (RMA2_IOCTL_GET_TUS):       
    {         
      uint32_t vpid=portp->vpid;
      uint64_t compl=rma_get_tu_completer(vpid);
      uint64_t resp=rma_get_tu_responder(vpid);
      uint64_t descriptor=(resp<<32l) | compl;
      return put_user(descriptor, ((uint64_t*) arg));
      break;
    }
  case (RMA2_IOCTL_SET_TUS):
    {
      uint32_t vpid=portp->vpid;
      uint64_t compl=arg & 0xffffffffl;
      uint64_t resp=(arg>>32l) & 0xffffffffl;
      rma_set_tu_completer(vpid, compl);
      rma_set_tu_responder(vpid,resp);      
      rma_set_vpid_ram_entry(vpid);
      break;
    }
    
  case (RMA2_IOCTL_GET_EXCELL):       
    {         
      uint32_t vpid=portp->vpid;
      uint64_t descriptor=rma_get_excell_enable(vpid);
      return put_user(descriptor, ((uint64_t*) arg));
      break;
    }
  case (RMA2_IOCTL_SET_EXCELL):
    {
      uint32_t vpid=portp->vpid;
      rma_set_excell_enable(vpid, (uint32_t)(arg));
      rma_set_vpid_ram_entry(vpid);
      break;
    }
  
  case (RMA2_IOCTL_GET_TCS):       
    {         
      //uint32_t vpid=portp->vpid;
      uint64_t value=(portp->tc3<<24l) | (portp->tc2<<16l) |(portp->tc1<<8l) | portp->tc0;
      return put_user(value, ((uint64_t*) arg));      
      break;
    }
  case (RMA2_IOCTL_SET_TCS):
    {
      uint32_t vpid=portp->vpid;
      uint64_t tc0=arg & 0xffl;
      uint64_t tc1=(arg>>8l) & 0xffl;
      uint64_t tc2=(arg>>16l) & 0xffl;
      uint64_t tc3=(arg>>24l) & 0xffl;
      rma_set_tc0(vpid,tc0);
      rma_set_tc1(vpid,tc1);
      rma_set_tc2(vpid,tc2);
      rma_set_tc3(vpid,tc3);
      rma_set_vpid_ram_entry(vpid);
      break;
    }   
  
   case (RMA2_IOCTL_GET_TPHBITS):       
    {         
    uint32_t vpid=portp->vpid;
      uint64_t steering_tag=rma_get_steering_tag(vpid);
      uint64_t tph=rma_get_tph_bits(vpid);
      uint64_t th_enable=rma_get_th_enable(vpid);
      
      uint64_t descriptor=((th_enable<<10l) & 0x1) | ((tph<<8) & 0x3) | (steering_tag & 0xff);
      return put_user(descriptor, ((uint64_t*) arg));
      break;
    }
  case (RMA2_IOCTL_SET_TPHBITS):
    {
      uint32_t vpid=portp->vpid;
      uint64_t steering_tag=arg & 0xffl;
      uint64_t tph=(arg>>8) & 0x3l;
      uint64_t th_enable=(arg>>10) & 0x1l;
      rma_set_tph_bits(vpid, th_enable,tph,steering_tag);
      rma_set_vpid_ram_entry(vpid);
      break;
    }      
    
    case (RMA2_IOCTL_GET_HISTMODE):       
    {         
      //uint32_t vpid=portp->vpid;
      uint64_t req=rma_get_requester_history_mode();
      uint64_t resp=rma_get_responder_history_mode();
      uint64_t compl=rma_get_completer_history_mode();
      
      uint64_t descriptor=req | (resp<<1) | (compl<<2);
      return put_user(descriptor, ((uint64_t*) arg));
      break;
    }
  case (RMA2_IOCTL_SET_HISTMODE):
    {
      //uint32_t vpid=portp->vpid;
      uint64_t req=arg & 0x1;
      uint64_t resp=(arg>>1) & 0x1;
      uint64_t compl=(arg>>2) & 0x1;
      rma_set_requester_history_mode(req);
      rma_set_responder_history_mode(resp);
      rma_set_completer_history_mode(compl);
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
static struct file_operations rma_fops = {
  .owner = THIS_MODULE,
  .llseek = rma2_llseek,
  .mmap = rma2_mmap,
  .unlocked_ioctl = rma2_ioctl_unlocked,
  .open = rma2_open,
  .release = rma2_release,
};

/******************************************************************************
*  PCI subsystem integration                                                  *
******************************************************************************/
/**
* set up the char_dev structure for requester & completer
* @return 0 if everyting is OK otherwise errorcode is returned
*/
static int rma2_setup_cdev(void)
{
  int err, devnr;

  /* setup requester first */
  devnr = MKDEV(MAJOR(rma2.devnr), RMA2_MINOR);
  cdev_init(&rma2.cdev, &rma_fops);
  rma2.cdev.owner = THIS_MODULE;
  rma2.cdev.ops = &rma_fops;
  err = cdev_add(&rma2.cdev, devnr, 1);
  if (err < 0)
  {
	printk(KERN_ALERT "rma2: Error %d adding cdev", err);
    cdev_del(&rma2.cdev);
	return err;
  }

  return 0;
}

/* RMA2 Interrupt handlers - called from interrupt dispatcher in extoll base driver
 */
//there is one possible handler per trigger group (interrupt cause)
static rma2_i_handler rma2_vpid_handlers[256];

void rma2_default_vpid_handler(int vpid,snq_entry_t* entry)
{
    //printk("rma2: default vpid message handler. new message available for vpid %d\n",vpid);
    dev_dbg(DEV,"default irq handler - message for vpid %d available\n",vpid);
    //snq_dump_entry(entry);
}

/* initialize the irq function pointer array */
void init_rma2_interrupt_handlers(void)
{
  int i;
  for (i=0;i<256;i++)
    {
      rma2_vpid_handlers[i]=rma2_default_vpid_handler;
    }
}

void rma2_msg_irq_handler(snq_entry_t* entry, int te, int entry_idx)
{
  int i,j,vpid;
  uint64_t value;
  rma2_i_handler handler;
  
  //snq_dump_entry(entry);
  // ok now look at the vpid bits, one by one...
  for (i=0;i<4;i++)
  {
    //select one of the four sources
    value = (unsigned long) entry->payload[3+i];
    for (j=0;j<64;j++)
    {
      //now check each bit
      if (value & 0x1l) //bit j is set
      {
	vpid=i*64+j;	
	handler=rma2_vpid_handlers[vpid];
	(*handler)(vpid,entry);
      }
      value=value>>1l;
    }
  }

}


void rma2_error_irq_handler(snq_entry_t* entry, int te, int entry_idx)
{
    dev_info(DEV,"error irq handler\n");
    snq_dump_entry(entry);
}

void rma2_error_history_irq_handler(snq_entry_t* entry, int te, int entry_idx)
{
    dev_info(DEV,"error history interrupt handler\n");
    snq_dump_entry(entry);
}


/* register a handler function for the extoll interrupt cause with the given idx
  */
void rma2_register_vpid_irq_handler(int idx, rma2_i_handler handler)
{
  rma2_vpid_handlers[idx]=handler;
}
EXPORT_SYMBOL(rma2_register_vpid_irq_handler);

/* register a handler function for the extoll interrupt cause with the given idx
  */
void rma2_deregister_vpid_irq_handler(int idx)
{
  rma2_vpid_handlers[idx]=rma2_default_vpid_handler;
}
EXPORT_SYMBOL(rma2_deregister_vpid_irq_handler);

/******************************************************************************
* SYSFS entries                                                               *
******************************************************************************/

static ssize_t rma2_processes_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int i = 0;
	ssize_t count = 0;
	for(i=0; i<RMA2_MAX_VPID; i++) {
		int pid = -1;
		if(ports[i]->opened) {
			pid = ports[i]->pid;
		}
		count += sprintf(buf, "%i:\t%i\n", i, pid);
		buf += strlen(buf);
	}

	return count;
}

static ssize_t rma2_processes_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	int ret = 0;
	unsigned int vpid;
	char const *current_position = buf;
	rma_port_t *port;
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

	if(vpid >= RMA2_MAX_VPID) {
	       dev_alert(DEV, "VPID to free must be between 0 and %i\n", RMA2_MAX_VPID-1);
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
	rma2_close_port(port);

out:	
	return strnlen(buf, count);
}

static DEVICE_ATTR_RW(rma2_processes);

static struct attribute *rma2_attrs[] = {
	    &dev_attr_rma2_processes.attr,
	    NULL
};
ATTRIBUTE_GROUPS(rma2);


/**
* initialize rma device in order to work seamless in kernel pci subsystem.
*/
static int rma2_probe(void)
{

  rma_port_t *portp = NULL;
  int i,j;
  int result=0;
  //uint64_t value;
  uint32_t size;
  uint32_t mps, readrq;
  uint64_t old_wcb_state;
  uint64_t new_wcb_state;

  DEBUG(printk(KERN_INFO "rma2: probe() called!\n");)

  rma2.devp = extoll_get_pdev();
  if (rma2.devp==0)
    {
      printk(KERN_ALERT "rma2: no device found.\n");
      return -EINVAL;
    }

  /* dynamically allocate a major number and create two minor numbers:
   *  0 is for physical address access
   *  1 is for RRA access
   *  2 is for normal user-space address with address translation
   */
  if (alloc_chrdev_region(&rma2.devnr, 0, RMA2_MINOR_COUNT, "rma2")) {
    printk(KERN_ALERT "rma2: No Major Number available!!\n");
	result=-EBUSY;
    goto rma_open_err_no_major;
  };
  DEBUG(printk(KERN_INFO "rma2: major number: %u\n", MAJOR(rma2.devnr));)
  DEBUG(printk(KERN_INFO "rma2: init successful\n");)
  rma2.dev=device_create(extoll_get_class_user(), extoll_get_device(), rma2.devnr, NULL, "rma2");
  if (rma2.dev==NULL) {
     printk("rma2 device creation failed\n");
     result=-EBUSY;
     goto rma_open_err_register_chrdev;
  }

  result = sysfs_create_group(&rma2.devp->dev.kobj, *rma2_groups);
  if(0 != result) {
	  return result;
  }

  //rma2.mmio_vaddr=extoll_get_rma2_vaddr();
  rma2.rma_mmio_addr=extoll_get_rma2_addr();
  rma2.rma_mmio_size=extoll_get_rma2_size();
  rma2.nodeid=(get_extoll_rf_info_rf_node()>>24l) & 0xffffl;
  
  /* Device OK!
  */
  if (rma2_setup_cdev() < 0)
  {
    dev_alert(DEV,"error in rma2_setup_cdev\n");
    result=-EBUSY;
    goto rma_open_err_device_create;
  }

  for (i=0;i<RMA2_MAX_VPID;i++)
    {            
      /* create port structure */
      portp = kmalloc(sizeof(rma_port_t), GFP_KERNEL);
      if (!portp) {
	dev_alert(DEV,"could not allocate memory for endpoint %d\n",i);
	result=-ENOMEM;
        goto rma_open_err_alloc;
      }
            
      /* init cport */
      memset(portp, 0, sizeof(rma_port_t));
      ports[i]=portp;
      
      portp->wb_rp=0;
      portp->rp=0;
      portp->async_flag=0;
      portp->poll_flag=0;
      portp->poll_times=1000; //default  number of kernel poll spins
      
      if (PAGE_SIZE > 64*1024)
        portp->desc_size=PAGE_SIZE;
      else
        portp->desc_size=64*1024;
      portp->notiq_size=rma_dma_size_cmp;
      portp->vpid=i;
      portp->kernel_owned=1;
      portp->opened=0;
      portp->pid=0;
      portp->bq=0;

      /* init registerfile for this VPID */
      //set-up per-vpid registers here. But don't enable yet! just basic stuff!
      rma_set_vpid_en(i,0);
      rma_set_tu_completer(i,1);
      rma_set_tu_responder(i,2);
      rma_set_excell_enable(i,0);
      rma_set_tc0(i,1);
      rma_set_tc1(i,1);
      rma_set_tc2(i,3);
      rma_set_tc3(i,3);
      rma_set_protection_descriptor(i,0);
      rma_set_tph_bits(i,0,0,0);
      rma_set_vpid_ram_entry(i);
 
      old_wcb_state=get_extoll_rf_rma_rf_wcbuf_rf_state(i);
      new_wcb_state=old_wcb_state & 0x00ffffffff000000l;
      set_extoll_rf_rma_rf_wcbuf_rf_state(i, new_wcb_state);
      dev_dbg(DEV,"vpid %d: wcb old state was %lx, new state will be %lx\n",i,(unsigned long)old_wcb_state,(unsigned long)new_wcb_state);

    }
    
    //set-up global configuration
    // config reg: set MTU to 256, pcie-mode to 0, fen to 0 and repd to 0 
    if (extoll_query_max_htoc_size()>64) {
      readrq=extoll_pcie_get_readrq(rma2.devp);
      mps=extoll_pcie_get_mps(rma2.devp);
    }
    else {
      readrq=64;
      mps=64;
    }
    
    switch (mps) {
      case 128: mps=2; break;
      case 256: mps=4; break;
      case 512: mps=8; break;
      default: mps=1; break;
    }
    switch (readrq) {
      case 128: readrq=2; break;
      case 256: readrq=4; break;
      case 512: readrq=8; break;
      default: readrq=1; break;
    }
    rma_set_mtu(extoll_get_mtu());

    rma_set_pcie_mode(mps);
    rma_set_pcie_readrq(readrq);
    rma_set_force_error_notifications(0);
    rma_set_read_engine_passpwd_disable(0);
    rma_set_config();
    
    //set-up locks
    rma_set_lock_number_locks(16);
    rma_set_lock_number_vpids(256);
    //alloc lock region
    size=rma2.lock_number_locks*rma2.lock_number_vpids*4;
    rma2.lock_base_vaddress = dma_alloc_coherent( &(rma2.devp->dev),size ,(dma_addr_t *) (&rma2.lock_base_address), GFP_KERNEL);
    if (rma2.lock_base_vaddress == NULL) {
        dev_alert(DEV,"memory allocation for lock segment of size %lu failed.\n", (long unsigned int)size);
        result=-ENOMEM;
	goto rma_open_err_alloc;
      }
    memset((void*)rma2.lock_base_vaddress, 0,size); 
    rma2.lock_size=size;
    //set registers
    rma_set_lock_base_address(rma2.lock_base_address);
    rma_set_lock_base_vaddress(rma2.lock_base_vaddress);
  
    rma_set_lock_steering_tag(0);
    rma_set_lock_tph(0);
    rma_set_lock_th(0);
    rma_set_lock_config();
    
    //configure history modes
    rma_set_requester_history_mode(0);
    rma_set_responder_history_mode(0);
    rma_set_completer_history_mode(0);
    
    //configure bq timeout
    rma_set_bq_timeout(0xa);
    rma_set_bq_timeout_enable(1);
    
    //configure wcbuf timeout
    rma_set_wcbuf_timeout(0x20l);
    rma_set_wcbuf_timeout_enable(1);
    
    //set store and forward mode
    //set utilization
    //enable network port 1 and 2
    set_extoll_rf_np_top_rf_n1_general(0xffl);
    set_extoll_rf_np_top_rf_n2_general(0xffl);
    
    //now register the interrupt handlers for velo
    init_rma2_interrupt_handlers();
    extoll_register_interrupt_handler(SNQ_TE_RMA_RF_NOTI_INTERRUPT_HANDLER_NOTI_INTERRUPT_VEC, &rma2_msg_irq_handler);
    extoll_register_interrupt_handler(SNQ_TE_RMA_HISTORY_DUMP, &rma2_error_history_irq_handler);
    extoll_register_interrupt_handler(SNQ_TE_RMA_ERROR, &rma2_error_irq_handler);
  return 0;

  /* ERROR handling */
rma_open_err_alloc:
  for (j=0;j<i;j++)
  {
	portp=ports[i];
	bq_destroy_queue(portp->bq);
	kfree(portp);
	ports[i]=0;
  }
rma_open_err_device_create:
  device_destroy(extoll_get_class_user(),rma2.devnr);
rma_open_err_register_chrdev:
  unregister_chrdev_region(rma2.devnr, RMA2_MINOR_COUNT);
  printk(KERN_ALERT "rma2: Major requesternumber %x freed \n",
         MAJOR(rma2.devnr));

rma_open_err_no_major:
  printk(KERN_ALERT "rma2: no major number available.\n");
  return result;
}


static void rma2_remove(void)
{
  rma_port_t *portp;
  int i;

  printk(KERN_INFO "rma2: removing driver...\n");
  if (rma2.devp==0) return;
  
  for (i=0;i<RMA2_MAX_VPID;i++)
    {
      portp=ports[i];
      rma2_release_port(portp);
      kfree((void *)portp);
      ports[i]=NULL;
    }
      
  sysfs_remove_group(&rma2.devp->dev.kobj, *rma2_groups);

  //disable network port 1 and 2 and reset utilisation mode etc
  set_extoll_rf_np_top_rf_n1_general(0l);
  set_extoll_rf_np_top_rf_n2_general(0l);

  //deregister rma interrupt handler
  extoll_deregister_interrupt_handler(SNQ_TE_RMA_RF_NOTI_INTERRUPT_HANDLER_NOTI_INTERRUPT_VEC);
  extoll_deregister_interrupt_handler(SNQ_TE_RMA_HISTORY_DUMP);
  extoll_deregister_interrupt_handler(SNQ_TE_RMA_ERROR);
  
  /* clean up any allocated resources and stuff here.
  * like call release_region();
  */
  printk(KERN_INFO "rma2: deleting cdev of minor devices\n");
  cdev_del(&rma2.cdev);
      
  printk(KERN_INFO "rma2: unregistering Major %d\n", MAJOR(rma2.devnr));
  unregister_chrdev_region(rma2.devnr, RMA2_MINOR_COUNT);
  device_destroy(extoll_get_class_user(),rma2.devnr);  
  dma_free_coherent(&(rma2.devp->dev),rma2.lock_size,(void*)rma2.lock_base_vaddress,(dma_addr_t) rma2.lock_base_address);
      
  printk(KERN_INFO "rma2: remove done!!\n");
}

/******************************************************************************
*  Module handling							      *
******************************************************************************/
static int __init rma2_init(void)
{

  printk(KERN_INFO "rma2: module init\n");

  if (extoll_get_init_done()==0)
  {
    printk("EXTOLL Base driver not initialized! Bailing out\n");
    return -1;
  }
 
  return rma2_probe();
  
}

static void __exit rma2_exit(void)
{
  printk(KERN_INFO "rma2: module exit\n");
  rma2_remove();
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mondrian Nuessle mondrian.nuessle@extoll.de");
MODULE_DESCRIPTION("Extollv2: RMA2 driver");
MODULE_VERSION("1.1");

module_init(rma2_init);
module_exit(rma2_exit);

EXPORT_SYMBOL(rma2_get_device);
EXPORT_SYMBOL(rma2_get_notiq_size);
EXPORT_SYMBOL(rma2_get_nodeid);
