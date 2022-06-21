/*
 *  This file is part of the  Linux Kernel Driver Package for EXTOLL R2.
 *
 *  Copyright (C) 2012 EXTOLL GmbH
 *
 *  Written by Tobias Groschup (2012)
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

#include "extolldrv.h"
#define _KAPI_INTERNAL
#include "extoll_kapi.h"
#include "velo2_mod.h"
#include "atu2_drv.h"
#include "extoll_rf_sysfs.h"
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/jiffies.h>
#include <linux/slab.h>
#include <asm/page.h>
#include <linux/scatterlist.h>
//#include <asm-generic/io.h>

#ifdef MICEXTOLL
  #define flush_wc()  
#else
 #ifdef LS3BEXTOLL  
   #define flush_wc()  
 #else
  #define flush_wc()  asm volatile("sfence" ::: "memory")
 #endif
#endif

#define INT_DIV8_CEIL(a) (a%8==0)? a/8: a/8+1; //is this always save?

//* WCB Handling functions */

static int _kapi_wcb_init(kapi_wcb_info_t *wcb, unsigned int vpid, const kapi_wcb_type_t function)
{
  size_t size = 0;
  uint64_t old_wcb_state=get_extoll_rf_velo_rf_wcbuf_rf_state(vpid);
  uint64_t new_wcb_state=old_wcb_state & 0x00ffffffff000000l;
  pr_debug("_kapi_wcb_init: old state was %lx, new state will be %lx\n",(unsigned long)old_wcb_state,(unsigned long)new_wcb_state);
  if(function==KAPI_WCB_VELO) {
    size = 128*256;
    set_extoll_rf_velo_rf_wcbuf_rf_state(vpid, new_wcb_state);
  } else {
    size = 32*256;
    set_extoll_rf_rma_rf_wcbuf_rf_state(vpid, new_wcb_state);
  }
  wcb->vpid = vpid;
  wcb->packet_buffer=kmalloc(size,GFP_KERNEL);
  if (wcb->packet_buffer==NULL) {
    pr_alert("_kapi_wcb_init: no memory available\n");
    return -ENOMEM;
  }
  memset(wcb->packet_buffer,0,size);
  wcb->committed_count=0;
  wcb->packet_wp=0;
  wcb->retried_packet_count=0;
  wcb->state=KAPI_WCB_OK;
  wcb->replay_state=KAPI_REPLAY_OK;
  
  wcb->retry=0l;
  wcb->retry_count=0l;
  wcb->assembly=0l;
  wcb->streamout=0l;
  wcb->callback=0;
  wcb->tasklet_timeout_us=1000;
  wcb->disable_tasklet=0;

  wcb->function=function;

  pr_debug("wcb tasklet init. Data is %lx\n", (unsigned long) wcb);
  tasklet_init(&wcb->tasklet,wcb_tasklet, (unsigned long) wcb);
  
  return 0;
}
static void _kapi_wcb_release(kapi_wcb_info_t *wcb)
{
  wcb->disable_tasklet=1;
  pr_debug("disabled tasklet, now calling tasklet_kill for function %d\n",wcb->function);
  tasklet_kill(&(wcb->tasklet));
  kfree(wcb->packet_buffer);
}

void kapi_velo2_wcb_register_callback(VELO2_Handle *handle,kapi_replay_callback_t f)
{ 
  handle->wcb.callback=f;
}
EXPORT_SYMBOL(kapi_velo2_wcb_register_callback);

void kapi_rma2_wcb_register_callback(RMA2_Handle *handle,kapi_replay_callback_t f)
{ 
  handle->wcb.callback=f;
}
EXPORT_SYMBOL(kapi_rma2_wcb_register_callback);

static inline uint64_t _kapi_wcb_get_state(kapi_wcb_info_t *wcb, const kapi_wcb_type_t function)
{
   if(function==KAPI_WCB_VELO) {
     return get_extoll_rf_velo_rf_wcbuf_rf_state(wcb->vpid);
  }else{
    return get_extoll_rf_rma_rf_wcbuf_rf_state(wcb->vpid);
  }
  return 0;
}

static inline void _kapi_wcb_set_state(kapi_wcb_info_t *wcb, const kapi_wcb_type_t function,uint64_t value)
{
   if(function==KAPI_WCB_VELO) {
     return set_extoll_rf_velo_rf_wcbuf_rf_state(wcb->vpid,value);
  }else{
    return set_extoll_rf_rma_rf_wcbuf_rf_state(wcb->vpid,value);
  }  
}

static inline uint64_t _kapi_wcb_get_decode_state(kapi_wcb_info_t *wcb, const kapi_wcb_type_t function) 
{
  wcb->wcb_state=_kapi_wcb_get_state(wcb,function);
  
  wcb->committed_count=wcb->wcb_state & 0xff;
  wcb->retry=wcb->wcb_state & 0x100000000l;  
  wcb->retry_count=(wcb->wcb_state & 0xff00000000000000l) >> 56l;

  //pr_alert("kapi_wcb_decode_state: committed_count=%d, packet_wp=%d\n",wcb->committed_count,wcb->packet_wp);
  
  return wcb->wcb_state;
}

static inline kapi_wcb_send_state_t _kapi_wcb_update_commited_state(kapi_wcb_info_t *wcb, const kapi_wcb_type_t function)
{ 
  wcb->wcb_state=_kapi_wcb_get_decode_state(wcb,function);
  
  if (wcb->retry!=0) wcb->state=KAPI_WCB_RETRY_NEEDED;
  else if (( (wcb->packet_wp+1) & 0xff) == wcb->committed_count) wcb->state=KAPI_WCB_FULL;
  else if ((wcb->packet_wp & 0xff) == wcb->committed_count) wcb->state=KAPI_WCB_OK;
  else  wcb->state=KAPI_WCB_NOTFULL;

  pr_debug("_kapi_wcb_update_commited_state: state is %d\n",wcb->state);
  
  return wcb->state;
}

static inline int _kapi_wcb_replay(kapi_wcb_info_t* wcb,int us_timeout)
{
 unsigned long int timeout_jiffies;
 unsigned long stop_t;
 
  uint32_t start;
  uint32_t stop;
  unsigned int i,j;
  int buflen;
  uint64_t* msg;
  unsigned int words;
  unsigned int bytes;
  uint64_t* dest; //=port->requester_map;
  uint64_t assembly,streamout;
  uint64_t state;

  timeout_jiffies=usecs_to_jiffies(us_timeout);
  stop_t=jiffies+timeout_jiffies;
  
  switch (wcb->replay_state) {
    case KAPI_REPLAY_START: { 
      pr_debug("_kapi_wcb_replay: KAPI_REPLAY_START\n");
      goto REPLAY_RETRY_START;
    }
    case KAPI_REPLAY_IDLE: {
      pr_debug("_kapi_wcb_replay: KAPI_REPLAY_IDLE\n");
      goto REPLAY_RETRY_IDLE;
    }
    case KAPI_REPLAY_EMPTY: {
      pr_debug("_kapi_wcb_replay: KAPI_REPLAY_EMPTY\n");
      goto REPLAY_RETRY_EMPTY;
    }
    case KAPI_REPLAY_REPLAY: {
      pr_debug("_kapi_wcb_replay: KAPI_REPLAY_REPLAY\n");
      goto REPLAY_REPLAY;
    }
    case KAPI_REPLAY_NOTEMPTY: {
      pr_debug("_kapi_wcb_replay: KAPI_REPLAY_REPLAY\n");
      goto REPLAY_WAIT_EMPTY;
    }
    default: {
      pr_alert("kapi_wcb_replay: unknown replay state %d. Exiting\n",wcb->replay_state);
      return -10;
    }
  }
  
REPLAY_RETRY_START:
  //buffer is full, need to update commited count and/or check retry
  pr_debug("starting REPLAY_RETRY_START\n");

  state=_kapi_wcb_get_decode_state(wcb,wcb->function);
  state=wcb->wcb_state;
  
  
  //update commited count
  if (wcb->retry!=0l && wcb->retry_count!=0) //oops, a retry occured, need to play back!
  {
     //first make sure that the buffer for this vpid is idle: bit 33==bit34
     assembly =(state & 0x200000000l) >> 33l;
     streamout=(state & 0x400000000l) >> 34l;

     //waut for buffer self being full
     while (assembly!=streamout) {
       state=_kapi_wcb_get_state(wcb,wcb->function);
       assembly =(state & 0x200000000l) >> 33l;
       streamout=(state & 0x400000000l) >> 34l;
       
      if (time_after(jiffies,stop_t)) {
        pr_debug("Timeout in REPLAY_RETRY_START: jiffies are %ld, stop_t is %ld\n",jiffies,stop_t);
        return -1;
      }
     }
     wcb->replay_state=KAPI_REPLAY_IDLE;
REPLAY_RETRY_IDLE:

    pr_debug("ok, idle packet_wp is %d\n",wcb->packet_wp);
      //wait for no more packets in flight (all need to be either committed or need to be retried)
      while (((wcb->packet_wp-wcb->committed_count) & 0xff) != wcb->retry_count)
      {
        state=_kapi_wcb_get_decode_state(wcb,wcb->function);      
  
        //MN add second timrout handling here
        if (time_after(jiffies,stop_t)) {
        return -2;
      }
      }
      
     wcb->replay_state=KAPI_REPLAY_EMPTY;
REPLAY_RETRY_EMPTY:
      //reset the retry bit! bn a loop!
      pr_debug("reset the retry bit\n");
      state=_kapi_wcb_get_decode_state(wcb,wcb->function);
      _kapi_wcb_set_state(wcb,wcb->function, (state & ~(0xff00000100000000l)));

      do {
        //retry_count=((*(port->state_map))& (0xff00000000000000l)) >> 56l;
        state=_kapi_wcb_get_decode_state(wcb,wcb->function);  

        if (wcb->retry_count!=0) {
            _kapi_wcb_set_state(wcb,wcb->function, (state & ~(0xff00000100000000l)));
        }
  
       if (time_after(jiffies,stop_t)) {
        return -3;
       }
      } while (wcb->retry_count!=0);

      wcb->replay_state=KAPI_REPLAY_REPLAY;
REPLAY_REPLAY:

      //start over -> report packet from packet buffer
      pr_debug("start over\n");
      start=(wcb->committed_count) & 0xff;
      stop=wcb->packet_wp;
      pr_debug("start=%d, stop=%d\n",start,stop);

     for (i=start;i!=stop;i=(i+1)&0xff) //iterate over all messages in buffer
      {
        if (wcb->function==KAPI_WCB_VELO) {
          msg=&(wcb->packet_buffer[i<<4]);
          buflen=((velo2_header_t)(msg[0])).length;
          words=buflen>>3;
          bytes=buflen & 0x7;
          if (bytes) words++;
          dest=(uint64_t *)((extoll_get_velo2_vaddr()+((unsigned long int)(wcb->vpid)<<12)));
        } else {
           msg=&(wcb->packet_buffer[i<<2]);
           words = 2;
           dest = (uint64_t*)msg[3];
        }
        pr_debug("First Message word is %lx\n",(unsigned long)msg[0]);
        for (j=0;j<words+1;j++)
        {
            dest[j]=msg[j];
        }
        flush_wc();
        wcb->retried_packet_count++;
        //count++;
      }
      wcb->replay_state=KAPI_REPLAY_NOTEMPTY;
  }
REPLAY_WAIT_EMPTY:
  pr_debug("wcb_replay: wait for empty\n");
  state=_kapi_wcb_check(wcb,wcb->tasklet_timeout_us);
  if (wcb->state==KAPI_WCB_OK) wcb->replay_state=KAPI_REPLAY_OK;
  else if (wcb->state==KAPI_WCB_FULL) wcb->replay_state=KAPI_REPLAY_NOTEMPTY ;
  else if (wcb->state==KAPI_WCB_NOTFULL) wcb->replay_state=KAPI_REPLAY_NOTEMPTY;
  else if (wcb->state==KAPI_WCB_RETRY_NEEDED) wcb->replay_state=KAPI_REPLAY_START;
  else {
    pr_debug("wcb_replay: waited for empty -> state is %ld...\n",(unsigned long)wcb->wcb_state);
    wcb->replay_state=KAPI_REPLAY_START;
  }
  
  if (wcb->state!=KAPI_WCB_OK) return -4;
  else return 0;
}

//check whether not retry and buffer flushed, timeout given to wait for empty, retry condition will return immediately
//return 0 on ok, -1 means retry ->fix definitely needed, positive means not empty -> either call this function again or fix function
int _kapi_wcb_check(kapi_wcb_info_t* wcb,int us_timeout)
{
   unsigned long int timeout_jiffies;
    unsigned long stop;
    kapi_wcb_send_state_t state=_kapi_wcb_update_commited_state(wcb,wcb->function);
    
    pr_debug("wcb_check called, vpid is %d\n",wcb->vpid);

    if (state==KAPI_WCB_OK) return 0;
    pr_debug("wcb_check called, not ok %d\n",state);

    if (state==KAPI_WCB_RETRY_NEEDED) {
      pr_debug("wcb_check:retry needed\n");
      return -1;
    } else if (state==KAPI_WCB_NOTFULL || state==KAPI_WCB_FULL) {
        pr_debug("wcb_check:waiting for empty\n");
        timeout_jiffies=usecs_to_jiffies(us_timeout);
        stop=jiffies+timeout_jiffies;
        while (!time_after(jiffies,stop)) {
          state=_kapi_wcb_update_commited_state(wcb,wcb->function);
          if (state==KAPI_WCB_OK) return 0;
          else if (state==KAPI_WCB_RETRY_NEEDED) {
            pr_debug("wcb_check:retry needed2\n");
            return -1;
          }
        }
    }
    pr_debug("wcb_check:timedout while waiting for empty\n");
    return 1;
}

int kapi_velo2_wcb_check(VELO2_Handle* handle,int us_timeout) {
   return _kapi_wcb_check(&handle->wcb,us_timeout);
}
EXPORT_SYMBOL(kapi_velo2_wcb_check);

int kapi_rma2_wcb_check(RMA2_Handle* handle,int us_timeout) {
   return _kapi_wcb_check(&handle->wcb,us_timeout);
}
EXPORT_SYMBOL(kapi_rma2_wcb_check);


//check whether retry is off and packet buffer not full
int kapi_velo2_wcb_check_notfull(VELO2_Handle* handle) {
    kapi_wcb_send_state_t state=_kapi_wcb_update_commited_state(&handle->wcb,handle->wcb.function);
    if (state==KAPI_WCB_OK || state==KAPI_WCB_NOTFULL) {
       return 0;
    }
    return 1;
}
EXPORT_SYMBOL(kapi_velo2_wcb_check_notfull);

int kapi_rma2_wcb_check_notfull(RMA2_Handle* handle) {
    kapi_wcb_send_state_t state=_kapi_wcb_update_commited_state(&handle->wcb,handle->wcb.function);
    if (state==KAPI_WCB_OK || state==KAPI_WCB_NOTFULL) {
       return 0;
    }
    return 1;
}
EXPORT_SYMBOL(kapi_rma2_wcb_check_notfull);

// try to fix wcb state (i.e. get rid of retry, flush packet buffer)
// if called, transmit should be turned off by caller
// wcb callback function called, when wcb state is again ok
// will run tasklet in background with timeouts, possibly multiple times

void _kapi_wcb_fix(kapi_wcb_info_t* wcb)
{
  if (wcb->state==KAPI_WCB_RETRY_NEEDED) {
    pr_warn("wcb fix started with KAPI_WCB_RETRY_NEEDED\n");
    wcb->replay_state=KAPI_REPLAY_START;
  }
  else {
    pr_warn("wcb fix started with KAPI_REPLAY_NOTEMPTY\n");
    wcb->replay_state=KAPI_REPLAY_NOTEMPTY;
  }
  tasklet_schedule(&(wcb->tasklet));

}

void kapi_velo2_wcb_fix(VELO2_Handle* handle) {  
   _kapi_wcb_fix(&handle->wcb);
}
EXPORT_SYMBOL(kapi_velo2_wcb_fix);

void kapi_rma2_wcb_fix(RMA2_Handle* handle) {
  _kapi_wcb_fix(&handle->wcb);
}
EXPORT_SYMBOL(kapi_rma2_wcb_fix);

void wcb_tasklet(unsigned long data) {
  kapi_wcb_info_t* wcb=(kapi_wcb_info_t*) data;
  int result;

  //handle the case we started with a non empty pcket buffer and should wait for it to drain
  if (wcb->replay_state==KAPI_REPLAY_NOTEMPTY) {
    pr_debug("wcb_tasklet: called for not empty\n");
    result=_kapi_wcb_check(wcb,wcb->tasklet_timeout_us);
    if (result==0) goto KAPI_WCB_FIXED;
    else if (result==-1) {
      wcb->replay_state=KAPI_REPLAY_START;
    }
    else if (result==1) { //timedout
      wcb->replay_state=KAPI_REPLAY_NOTEMPTY;
    }
    goto KAPI_WCB_SCHEDULE;
  }
 //handle the case we are started with RETRY set...
 else if (wcb->replay_state!=KAPI_REPLAY_OK) {
   pr_debug("wcb_tasklet: called for retry? state=%d\n",wcb->replay_state);
   result=_kapi_wcb_replay(wcb,wcb->tasklet_timeout_us);
   if (result==0) goto KAPI_WCB_FIXED;
   else if (result==-10) goto KAPI_WCB_ERROR;
   else {
    goto KAPI_WCB_SCHEDULE;
   }
 } else {
   pr_debug("wcb tasklet: unexpected state %d\n",wcb->replay_state);
   return;
 }

 KAPI_WCB_SCHEDULE:
  if (wcb->disable_tasklet==0) { //prevent from being rescheduled, if release has been called
    pr_debug("reschedule called jiffies %ld\n",jiffies);
    tasklet_schedule(&wcb->tasklet);
  }
  return;
 KAPI_WCB_FIXED:
  //call callback
  pr_debug("callback called. Done\n");
  if (wcb->callback!=NULL)
    wcb->callback(wcb); 
  pr_warn("WCB Fix Task done\n");
  return;
 KAPI_WCB_ERROR:
  pr_alert("tasklet: ERROR!\n");
  return;
}





/* *********************************************************************************
 * Datatypes not needed outside this file
 ***************************************************************************************/

//static void _kapi_velo_send_check(unsigned long data);

/*******************************************************************
 * Open/close helper functions
 * ***************************************************************/


/* *******************************************************************************************
 * Velo:  Open and Close Methods
 * *****************************************************************************************/

/* register with velo-device, get vpid and allocate message box
 */
int kapi_velo2_open(VELO2_Handle **handle, int vpid)
{
  int error;
  velo_port_t *port;
  int slot_size;

  *handle = kmalloc(sizeof(VELO2_Handle), GFP_KERNEL);
  if(*handle==0) {
    pr_alert( "Extoll kernel API: no memory.\n");
    return -ENOMEM;
  }
  memset(*handle, 0, sizeof(VELO2_Handle));
  
  // (*handle)->on_exit = kmalloc(sizeof(struct completion), GFP_KERNEL);
  // if((*handle)->on_exit==0) {
	  // return -ENOMEM;
  // }
  // memset((*handle)->on_exit, 0, sizeof(struct completion));
 
  //init the requester
  error=velo2_lock_mutex();
  if (error!=0) {
    pr_alert("kapi_velo2_open: could not get mutex\n");
    kfree(handle);
    return -EFAULT;
  }
  pr_debug("Before velo2_init_port\n");
  error =  velo2_init_port(&port,vpid); // on second insmod, this method does not return!
  if(error) {
    pr_alert("An Error occured in velo2 init port!\n");
    velo2_unlock_mutex();
    kfree(*handle);
    return error; //return the error generated in underlying module
  }
  pr_debug("After velo2_init_port\n");

  (*handle)->port = port;
  (*handle)->vpid = port->vpid;
  (*handle)->nodeid = velo2_get_nodeid(); 

  //init the completer
  pr_debug("Before velo2_open_completer\n");
  error = velo2_open_completer(port, 0, 0);
  if(error) {
    velo2_unlock_mutex();
    pr_alert("An error occured while opening the velo2 completer.\n");
    kfree(*handle);
    return error;
  }
  pr_debug("After velo2_open_completer\n");
  velo2_unlock_mutex();

  slot_size = (*handle)->port->bq->slot_size == 128 ? 128 : 56;

  /*if ( (*handle)->port->bq->slot_size != 128 ) { // we can read everything at once
	pr_alert("64byte slot VELO2 configuration not supported by this version of KAPI.\n");
        kfree(*handle);
        return -1;
  }*/

  //init read and write pointer of mbox
  (*handle)->current_desc = 0;

  (*handle)->descs = port->bq->descs; //the first message
  (*handle)->msg = (*handle)->descs[0].k_v_addr;
  pr_debug("k_v_addr: %p", (*handle)->descs[0].k_v_addr);
  (*handle)->header = (*handle)->msg+7; //status-word of first message
  pr_debug("status-word: %p", (*handle)->header);
  (*handle)->slots_read = 0;

  pr_debug("setting write and read pointer\n");
  velo2_set_rp((*handle)->port, 0);
  velo2_set_wp(port, 0);
  
  pr_debug("setting up wcbuf packet buffer\n");
  error=_kapi_wcb_init(&((*handle)->wcb), port->vpid,  KAPI_WCB_VELO);
  if (error!=0) {
    pr_err("extoll_kapi_velo2_open: no memory available for wcb buffers\n");
    return error; 
  }
  pr_debug("kapi_velo2_open: wcb address is %p,vpid in wcb is %d\n",&((*handle)->wcb), (*handle)->wcb.vpid); 
  //reset the wcbuf state for this vpid when opening
  //set_extoll_rf_velo_rf_wcbuf_rf_state((*handle)->vpid, 0l);
  
  pr_debug("done setting up the port\n");
  return 0;
}
EXPORT_SYMBOL(kapi_velo2_open);

int kapi_velo2_close(VELO2_Handle **handle)
{
  int error = 0;

  _kapi_wcb_release(&((*handle)->wcb));
 
  error=velo2_lock_mutex();
  if (error!=0) {
    pr_alert("kapi_velo2_open: could not get mutex\n");
    return -EFAULT;
  }
  
  
  error = velo2_close_port((*handle)->port);
  if(error) {
    pr_alert("ERROR during closing of velo-port!\n");
  }
  velo2_unlock_mutex();
  
  kfree(*handle);
  *handle = 0;
  return error;
}
EXPORT_SYMBOL(kapi_velo2_close);

nodeid_t kapi_velo2_get_nodeid(VELO2_Handle *handle)
{
  return handle->nodeid;
}
EXPORT_SYMBOL(kapi_velo2_get_nodeid);

vpid_t kapi_velo2_get_vpid(VELO2_Handle *handle)
{
  return handle->vpid;
}
EXPORT_SYMBOL(kapi_velo2_get_vpid);
/* *******************************************************************************************
 * Velo: Send and Receive Methods 
 * *****************************************************************************************/
int kapi_velo2_send(VELO2_Handle *handle, nodeid_t destination_nodeid, vpid_t destination_vpid, void *buffer, uint16_t buffer_length, uint8_t tag, int mtt, int mc, int interrupt)
{
  uint64_t *destination;
  uint64_t descriptor;
  unsigned int words = buffer_length>>3;
  uint32_t wp=handle->wcb.packet_wp;
  uint32_t waddr=wp<<4;
  int bytes = buffer_length&0x7;
  int i = 0;
  

  descriptor = (((buffer_length) & 0x7ffl)<<48l) | (((tag) & 0xffl)<<40l) | ((interrupt & 0x1l)<<34l) | (((mtt) & 0x3l)<<32l) | 
		(((mc) & 0x1l)<<31l) | ((destination_vpid & 0x3ffl)<<16) | (destination_nodeid & 0xffffl);
#ifdef DEEP_HOST                
  destination = (uint64_t *)((extoll_get_velo2_vaddr()+((unsigned long int)(handle->vpid)<<12))+(0x200000) ); //use TC 2
#endif
#ifdef DEEP_KNC
  destination = (uint64_t *)((extoll_get_velo2_vaddr()+((unsigned long int)(handle->vpid)<<12))+(0x200000) ); //use TC 2  
#else  
  //destination = (uint64_t *)((extoll_get_velo2_vaddr()+((unsigned long int)(handle->vpid)<<12)));
	destination = (uint64_t *)((extoll_get_velo2_vaddr()+((unsigned long int)(handle->vpid)<<12))+(0x200000) ); //use TC 2
#endif  
  

  if (bytes) words++;

  //_kapi_wcb_empty_replay_buffer(&(handle->wcb), 1);
  //kapi_velo2_wcb_check(handle,1000);
  //copy packet to packet buffer -> part before and after copy in one function?
  handle->wcb.packet_buffer[waddr]=descriptor;
  memcpy(&(handle->wcb.packet_buffer[waddr+1]),buffer,buffer_length);
	
  for (i=0;i<words+1;i++)
  {
    *destination++ = handle->wcb.packet_buffer[waddr+i];
  }

  //inc packet buffer wp
  handle->wcb.packet_wp=(wp+1) & 0xff;
  flush_wc();	//just send it

  return 0;
}
EXPORT_SYMBOL(kapi_velo2_send);

//header_length in quadwords!
int kapi_velo2_send_header(VELO2_Handle *handle, nodeid_t destination_nodeid, vpid_t destination_vpid, void *buffer, uint16_t buffer_length, uint64_t *header, unsigned int header_length, uint8_t tag, int mtt, int mc, int interrupt)
{
  uint64_t *destination;
  uint64_t descriptor;
  unsigned int velo_length = buffer_length + (header_length<<3);
  unsigned int words = velo_length>>3;
  uint32_t wp=handle->wcb.packet_wp;
  uint32_t waddr=wp<<4;
  int bytes = velo_length&0x7;
  int i = 0;
 
  if(velo_length > 120) {
	return -1;
  } 

  descriptor = (((velo_length) & 0x7ffl)<<48l) | (((tag) & 0xffl)<<40l) | ((interrupt & 0x1l)<<34l) | (((mtt) & 0x3l)<<32l) | 
		(((mc) & 0x1l)<<31l) | ((destination_vpid & 0x3ffl)<<16) | (destination_nodeid & 0xffffl);
  destination = (uint64_t *)((extoll_get_velo2_vaddr()+((unsigned long int)(handle->vpid)<<12)));

  if (bytes) words++;

  //_kapi_wcb_empty_replay_buffer(&(handle->wcb), 1);
  
  //copy packet to packet buffer -> part before and after copy in one function?
  handle->wcb.packet_buffer[waddr]=descriptor;
  memcpy(&(handle->wcb.packet_buffer[waddr+1]),header,header_length<<3);
  memcpy(&(handle->wcb.packet_buffer[waddr+1+header_length]),buffer,buffer_length);
	
  for (i=0;i<words+1;i++) {
    *destination++ = handle->wcb.packet_buffer[waddr+i];
  }

  //inc packet buffer wp
  handle->wcb.packet_wp=(wp+1) & 0xff;
  flush_wc();	//just send it

  return 0;
}
EXPORT_SYMBOL(kapi_velo2_send_header);


/* blocks, until a new message arrives
 * fetch message later
 */
static inline void _velo2_wait_for_new_mesage(VELO2_Handle *handle)
{
  volatile uint64_t *status = handle->port->bq->status_word;
  //int i=0;
  //pr_debug("waiting on %p, (new method: %p)\n", status, bq_get_status_word(handle->port->bq));
  //if the message is longer than one slot -> wait for the last slot? or wait between two parts of a message?
  while(*status==0) {
    //wait for message
    //pr_debug("in _velo2_wait_for_new_message...%d\n",i);
    cpu_relax();
    //i++;
  }
}
void kapi_velo2_wait(VELO2_Handle *handle,uint32_t* srcid, uint32_t* len, uint8_t* mtt, uint8_t* tag )
{
  //int i=0;
  volatile uint64_t *status = handle->port->bq->status_word;
  pr_debug("waiting on %p, current value %llx\n", status, *status);
  //if the message is longer than one slot -> wait for the last slot? or wait between two parts of a message?
  while(*status==0) {
    //wait for message
    //handle wcbuf retry every 1000th iteration
//     if ((i & 0x1000l)!=0l)
//     {      
//       	uint32_t wp=handle->packet_wp;
//       	while ( ((wp) & 0xff) != handle->committed_count)
// 	{
// 	  _kapi_replay_buffer(handle);	  
// 	}
//     }
//     i++;
    cpu_relax();
  }
  *srcid=VELO2_STATUS_SOURCEID(status);
  *len=VELO2_STATUS_LENGTH(status);
  *mtt=VELO2_STATUS_MTT(status);
  *tag=VELO2_STATUS_TAG(status);
  pr_debug("velo2 wait for message finished\n");
}
EXPORT_SYMBOL(kapi_velo2_wait);

int kapi_velo2_check(VELO2_Handle *handle,uint32_t* srcid, uint32_t* len, uint8_t* mtt, uint8_t* tag )
{
  volatile uint64_t *status = handle->port->bq->status_word;
  //int i=0;
  //pr_debug("waiting on %p, (new method: %p)\n", status, bq_get_status_word(handle->port->bq));
  //if the message is longer than one slot -> wait for the last slot? or wait between two parts of a message?
  if (*status==0) {
    //no new message, handle just wcbuf retry
//       uint32_t wp=handle->packet_wp;
//       if ( ((wp) & 0xff) != handle->committed_count)
//       // if (((wp+1) & 0xff) == handle->committed_count)
//       {
//         pr_debug("call replay buffer from kapi_velo2_check i=%d!\n",i);
//         _kapi_replay_buffer(handle);
//        // wp=handle->packet_wp;
// 	i++;
//       }
    return -1;
  }
  *srcid=VELO2_STATUS_SOURCEID(status);
  *len=VELO2_STATUS_LENGTH(status);
  *mtt=VELO2_STATUS_MTT(status);
  *tag=VELO2_STATUS_TAG(status);
  return 0;
}
EXPORT_SYMBOL(kapi_velo2_check);
  
static int kapi_velo2_recv_default(VELO2_Handle *handle, void * buffer, unsigned int skip_length, unsigned int read_length, bool inc_read_slot);
//fetches a message from the buffer queue
int kapi_velo2_recv_complete(VELO2_Handle *handle, void *buffer)
{
  return kapi_velo2_recv_default(handle, buffer, 0, 0, true);
}
EXPORT_SYMBOL(kapi_velo2_recv_complete);

int kapi_velo2_recv_header(VELO2_Handle *handle, void *buffer, unsigned int hlen)
{
  return kapi_velo2_recv_default(handle, buffer, 0, hlen*8, false);
}
EXPORT_SYMBOL(kapi_velo2_recv_header);

int kapi_velo2_recv_payload(VELO2_Handle *handle, void *buffer, unsigned int skip)
{
  return kapi_velo2_recv_default(handle, buffer, skip*8, 0, true);
}
EXPORT_SYMBOL(kapi_velo2_recv_payload);

void kapi_velo2_recv_commit(VELO2_Handle *handle, int update_irq)
{
  bq_read_slot_commit_rp(handle->port->bq,update_irq);
}
EXPORT_SYMBOL(kapi_velo2_recv_commit);

int kapi_velo2_receive(VELO2_Handle *handle, void *buffer, uint32_t* srcid,uint32_t* len, uint8_t* mtt, uint8_t* tag, int update_irq)
{
  int result;
  pr_debug("called velo2_receive, waiting for velo message\n");
  kapi_velo2_wait(handle,srcid, len, mtt, tag);
  pr_debug("waited successfully for velo message!\n");
  result=kapi_velo2_recv_complete(handle, buffer);
  kapi_velo2_recv_commit(handle, update_irq);
  return result;
}
EXPORT_SYMBOL(kapi_velo2_receive);

int kapi_velo2_receive_nb(VELO2_Handle *handle, void *buffer, uint32_t* srcid,   uint32_t* len, uint8_t* mtt, uint8_t* tag, int update_irq)
{
  int result;
  result=kapi_velo2_check(handle,srcid, len, mtt, tag);
  if (result!=0) return result;
  result=kapi_velo2_recv_complete(handle, buffer);
  kapi_velo2_recv_commit(handle, update_irq);

  return result;
}
EXPORT_SYMBOL(kapi_velo2_receive_nb);
/*
 * How to receive with 128 byte slots:
 *
int kapi_velo2_recv_default_128(VELO2_Handle *handle, void *buffer, unsigned int skip_len, unsigned int read_len, bool inc_read_slot ) {
  volatile uint64_t *status = bq_get_status_word(handle->port->bq);
  const void *msg;
  uint64_t *bufp = (uint64_t*) buffer;
  uint16_t total_len = 0;
  int result = 0;
  int words;
  
  total_len =  (((*(status))>>48l) & 0x7fl);
  if(!(total_len > 0)) { //received nothing
	pr_debug("kapi_velo2_recv_default: Buffer Slot is empty!\n");
	return -1;
  }

  if (read_len == 0 ) { // read everything
    read_len = total_len - skip_len;
  }

  if((read_len + skip_len) > total_len || read_len <= 0) {
    pr_debug("Not enough data,[%u] bytes available. Requested read: read_len[%u], skip_len[%u]\n", total_len, read_len, skip_len);
    return -2;
  }

  words = INT_DIV8_CEIL(total_len);
  msg = (const void*) (status - words);
  memcpy((void*)bufp, ((char*) msg+skip_len), read_len); 
  if (inc_read_slot == true) result = bq_read_slot_inc_rp(handle->port->bq);

  return result;
}
*/

static int message_size_to_slots(unsigned int size, unsigned int slot_size)
{
	if(slot_size == 128) return 1;
	if(size <= 56) return 1;
	if(size <= 112) return 2;
	return 3;
}

static int kapi_velo2_recv_default(VELO2_Handle *handle, void * buffer, unsigned int skip_length, unsigned int read_length, bool inc_read_slot) 
{
	volatile uint64_t *status = bq_get_status_word(handle->port->bq);
	size_t header_length = sizeof(*status);
	int total_length = VELO2_STATUS_LENGTH(status);
	int current_length = 0;
	void *msg = NULL; 
	int words = 0;
	int slot_size = handle->port->bq->slot_size;
	int slot_payload = slot_size - header_length;
	int slots = 0;
	int result = 0;

	if(unlikely(0 == total_length)) {
		pr_alert("Trying to receive an empty message.\n");
		return -1;
	}
	if(0 == read_length) { // read everything
		read_length = total_length - skip_length;
	}

	if(unlikely((read_length + skip_length) > total_length || read_length <= 0)) {
		pr_alert("Not enough data,[%u] bytes available. Requested read: read_length[%u], skip_length[%u]\n", total_length, read_length, skip_length);
		return -2;
	}

	if(unlikely(skip_length >= slot_payload)) {
		pr_alert("Skipping more than one slot, abort receive.\n");
		return -3;
	}

	if(read_length>slot_payload) {
		current_length = slot_payload;
	} else {
		current_length = read_length;
	}
	words = INT_DIV8_CEIL(current_length);
	msg = (void *)(status-words);
	slots = message_size_to_slots(total_length, slot_size);

	pr_debug("velo2 recv with: length: %i, header size %zu, slots %i, slot size %i, slot payload %i, read length %i, skip length %i, status word: %llx\n",
			total_length, header_length, slots, slot_size, slot_payload, read_length, skip_length, *(uint64_t *)status);
	pr_debug("message starts at %p, value: %llx\n", msg, *(uint64_t *)msg);

	memcpy(buffer, msg+skip_length, current_length-skip_length);
	if(inc_read_slot == true) result += bq_read_slot_inc_rp(handle->port->bq);
	if(slots >= 2) {
		if((read_length-slot_payload)>slot_payload) {
			current_length = slot_payload;
		} else {
			current_length = read_length - slot_payload;
		}
		status = bq_get_status_word(handle->port->bq);
		words = INT_DIV8_CEIL(current_length);
		msg = (void *)(status-words);

		memcpy(buffer+slot_payload,msg, current_length);
		result += bq_read_slot_inc_rp(handle->port->bq);
	}
	if(slots == 3) {
		current_length = read_length - 2*slot_payload;
		status = bq_get_status_word(handle->port->bq);
		words = INT_DIV8_CEIL(current_length);
		msg = (void *)(status-words);

		memcpy(buffer+2*slot_payload, msg, current_length);
		result += bq_read_slot_inc_rp(handle->port->bq);
	}


	return result;
}

/* **************************************************************************************
 * RMA  open and close methods
 * ************************************************************************************/
int kapi_rma2_open(RMA2_Handle **h, int vpid)
{
  int error;
  rma_port_t *port = 0;
  unsigned int offset=0;
  RMA2_Handle * handle;

  error=rma2_lock_mutex();
  if (error!=0) {
    pr_alert("kapi_rma2_open: could not lock mutex.\n");
    return error;
  }

  handle = (RMA2_Handle*) kmalloc(sizeof(RMA2_Handle), GFP_KERNEL);
  if( (handle) == 0) {
    pr_alert("No memory for RMA2 handle.\n");
    rma2_unlock_mutex();
    return -ENOMEM;
  }
  memset(handle, 0, sizeof(RMA2_Handle));
 
  
  error = rma2_init_port(&port,vpid);
  if(error) {
    pr_alert("An error occured while opening the RMA2 port!\n");
    rma2_unlock_mutex();
    kfree(handle);
    return error;
  }

  error=rma2_init_completer(port);
  if (error!=0) {
     pr_alert("kapi_rma2_open: init completer failed\n");
     rma2_unlock_mutex();
     kfree(handle);
     return error;
  }
  (handle)->port = port;
  (handle)->vpid = port->vpid;
  (handle)->mtu = rma_get_mtu();
  (handle)->nodeid = rma2_get_nodeid();

  (handle)->descs = port->bq->descs; 

  //init ALL the requester addresses
  //here: for every possible combination of TC, RRA and INT calculate the requester address and  store it
  //later: just calculate the index by the features
  (handle)->requester = kmalloc(32*sizeof((handle)->requester[0]), GFP_KERNEL);
  if (handle->requester==NULL) {
     pr_alert("kapi_rma2_open: no memory for requester available\n");
     rma2_unlock_mutex();
     kfree(handle);
     return -ENOMEM;
  }
  memset((handle)->requester, 0, 32*sizeof((handle)->requester[0]));
  pr_alert("vpid is %d, rma2_vaddr %p \n",handle->vpid, extoll_get_rma2_vaddr());
  for(offset=0; offset<32; offset++) {
    (handle)->requester[offset] = extoll_get_rma2_vaddr() + ((offset << 20l) | ((((handle)->vpid) & 0xff) << 12l));
    pr_debug("kapi: requester page %d at address %p\n",offset,(handle)->requester[offset]);
  }

  (handle)->descriptors = kmalloc(6*sizeof((handle)->descriptors[0]), GFP_KERNEL);
  if (handle->descriptors==NULL) {
     pr_alert("kapi_rma2_open: no memory for descriptors available\n");
     rma2_unlock_mutex();
     kfree(handle->requester);
     kfree(handle);
     return -ENOMEM;
  }

  memset((handle)->descriptors, 0, 6*sizeof((handle)->descriptors[0]));

  //enable the access to the message queue
  (handle)->current_desc = 0;
  (handle)->descs = port->bq->descs;
  (handle)->slots_read = 0;
  (handle)->msg = (handle)->descs[(handle)->current_desc].k_v_addr;
  (handle)->header = (handle)->msg+1;

  error=_kapi_wcb_init(&(handle->wcb), port->vpid, KAPI_WCB_RMA);
  if (error!=0) {
     pr_alert("kapi_rma2_open: no memory for wcb packet buffer available\n");
     rma2_unlock_mutex();
     kfree(handle->requester);
     kfree(handle->descriptors);
     kfree(handle);
     return -ENOMEM;
  }

 handle->rra_page=alloc_page(GFP_KERNEL);
 if (handle->rra_page==0) {
   printk(KERN_ALERT "kapi_rma2_open: could not allocate page for RMA2 based RMA reads\n");
   rma2_unlock_mutex();
   kfree(handle->wcb.packet_buffer); 
   kfree(handle->requester);
   kfree(handle->descriptors);
   kfree(handle);
   return -ENOMEM;
  }


  *h=handle;
  rma2_unlock_mutex();
  return 0;
}
EXPORT_SYMBOL(kapi_rma2_open);

int kapi_rma2_close(RMA2_Handle **handle)
{
  int error = 0;

  _kapi_wcb_release(&((*handle)->wcb));

  kfree((*handle)->requester);
  kfree((*handle)->descriptors);
  error=rma2_lock_mutex();
  if (error!=0) {
    pr_alert("kapi_rma2_close: could not lock mutex.\n");
    return error;
  }
  error = rma2_close_port(((*handle)->port));
  rma2_unlock_mutex();
  //del_timer_sync(&(*handle)->wcb.send_wd);
  
  __free_page((*handle)->rra_page);
  kfree(*handle);
  *handle = 0;
  return error;
}
EXPORT_SYMBOL(kapi_rma2_close);

nodeid_t kapi_rma2_get_nodeid(RMA2_Handle *handle)
{
  return handle->nodeid;
}
EXPORT_SYMBOL(kapi_rma2_get_nodeid);

vpid_t kapi_rma2_get_vpid(RMA2_Handle *handle)
{
  return handle->vpid;
}
EXPORT_SYMBOL(kapi_rma2_get_vpid);

uint32_t kapi_rma2_get_mtu(RMA2_Handle *handle)
{
  return handle->mtu;
}
EXPORT_SYMBOL(kapi_rma2_get_mtu);

/****************************************************************************************
 * Post RMA commands
 ****************************************************************************************/
/***************************************************************************************
 * Helper Functions
 * *************************************************************************************/
static inline void _kapi_set_desc_values(RMA2_Descriptor *desc, uint32_t count, RMA2_Command_Modifier modifier, RMA2_Notification_Spec noti, nodeid_t nodeid, vpid_t vpid, RMA2_Command command)
{
   desc->value[0]=(((count-1) & 0x7fffffl)<<40l) | ((modifier & 0xfl)<<35l)| ((noti & 0x7l)<<32l)  | ((nodeid & 0xffffl)<<16l) | ((vpid & 0xffl)<<8l) | ((command & 0xfl)<<2l) | 3l;
}

static inline void _kapi_set_desc_read_addr(RMA2_Descriptor *desc, uint64_t *read_addr)
{
  desc->value[1] = (uint64_t)read_addr;
}

static inline void _kapi_set_desc_write_addr(RMA2_Descriptor *desc, uint64_t *write_addr)
{
  desc->value[2] = (uint64_t)write_addr;
}

static inline void _kapi_set_desc_notification_payload(RMA2_Descriptor *desc, uint64_t value)
{
  desc->value[1] = value;
}

static inline void _kapi_set_desc_immediate_value(RMA2_Descriptor *desc, uint64_t value)
{
  desc->value[2] = value;
}

static inline void _kapi_post_desc(RMA2_Handle *handle, RMA2_Descriptor *desc, RMA2_Connection_Options options)
{
  int i;
  uint64_t *destination = (handle->requester)[options];
  uint32_t wp=handle->wcb.packet_wp;
  uint32_t waddr=wp<<2;

  //_kapi_wcb_empty_replay_buffer(&(handle->wcb), 0);

  //debug output for the replay buffer development
  /*pr_debug("would write to %p descriptor: \n", destination);
  for(i=0;i<3;i++){
    pr_debug("%lx\n", desc->value[i]);
  }*/

  //write to wcb, and flush
  for (i=0;i<3;i++) {
   destination[i] = desc->value[i]; 
  }
  flush_wc();  //just send it

  //add to replay buffer
  for(i=0;i<3;i++) {
    handle->wcb.packet_buffer[waddr+i] = desc->value[i];
  }
  handle->wcb.packet_buffer[waddr+3] = (uint64_t)destination;
  handle->wcb.packet_wp = (wp+1) & 0xff;
}

/********************************************************************************************
 * The real commands
 * ****************************************************************************************/
int kapi_rma2_get_bt(RMA2_Handle *handle, nodeid_t nodeid, vpid_t vpid, void *source_addr, void *dest_addr, uint32_t count, RMA2_Notification_Spec noti, RMA2_Command_Modifier modifier, RMA2_Connection_Options option)
{
  RMA2_Command COMMAND = RMA2_BT_GET;
  RMA2_Descriptor *desc = &(handle->descriptors[COMMAND]);
  
  if(count < 1)
    count = 1;
  
  _kapi_set_desc_values(desc, count, modifier, noti, nodeid, vpid, COMMAND);
  _kapi_set_desc_read_addr(desc, source_addr);
  _kapi_set_desc_write_addr(desc, dest_addr);

  _kapi_post_desc(handle, desc, option);

  return 0;
}
EXPORT_SYMBOL(kapi_rma2_get_bt);

int kapi_rma2_get_qw(RMA2_Handle *handle, nodeid_t nodeid, vpid_t vpid, void *source_addr, void *dest_addr, uint32_t count, RMA2_Notification_Spec noti, RMA2_Command_Modifier modifier, RMA2_Connection_Options option)
{
  RMA2_Command COMMAND = RMA2_QW_GET;
  RMA2_Descriptor *desc = &(handle->descriptors[COMMAND]);
  
  if(count < 1)
    count = 1;
  
  _kapi_set_desc_values(desc, count, modifier, noti, nodeid, vpid, COMMAND);
  _kapi_set_desc_read_addr(desc, source_addr);
  _kapi_set_desc_write_addr(desc, dest_addr);

  _kapi_post_desc(handle, desc, option);

  return 0;
}
EXPORT_SYMBOL(kapi_rma2_get_qw);

int kapi_rma2_put_qw(RMA2_Handle *handle, nodeid_t nodeid, vpid_t vpid, void *source_addr, void *dest_addr, uint32_t count, RMA2_Notification_Spec noti, RMA2_Command_Modifier modifier, RMA2_Connection_Options option)
{
  RMA2_Command COMMAND = RMA2_QW_PUT;
  RMA2_Descriptor *desc = &(handle->descriptors[COMMAND]);
  
  if(count < 1)
    count = 1;
  
  _kapi_set_desc_values(desc, count, modifier, noti, nodeid, vpid, COMMAND);
  _kapi_set_desc_read_addr(desc, source_addr);
  _kapi_set_desc_write_addr(desc, dest_addr);

  _kapi_post_desc(handle, desc, option);

  return 0;
}
EXPORT_SYMBOL(kapi_rma2_put_qw);

int kapi_rma2_put_bt(RMA2_Handle *handle, nodeid_t nodeid, vpid_t vpid, void *source_addr, void *dest_addr, uint32_t count, RMA2_Notification_Spec noti, RMA2_Command_Modifier modifier, RMA2_Connection_Options option)
{
  RMA2_Command COMMAND = RMA2_BT_PUT;
  RMA2_Descriptor *desc = &(handle->descriptors[COMMAND]);
  
  if(count < 1)
    count = 1;
  
  _kapi_set_desc_values(desc, count, modifier, noti, nodeid, vpid, COMMAND);
  _kapi_set_desc_read_addr(desc, source_addr);
  _kapi_set_desc_write_addr(desc, dest_addr);

  _kapi_post_desc(handle, desc, option);

  return 0;
}
EXPORT_SYMBOL(kapi_rma2_put_bt);


int kapi_rma2_post_lock(RMA2_Handle *handle, nodeid_t nodeid, vpid_t vpid, uint32_t  target,  uint32_t lock_number, int32_t cmp_value, int32_t add_value, RMA2_Notification_Spec noti, RMA2_Command_Modifier modifier, RMA2_Connection_Options option)
{
  uint8_t type = target;
  uint32_t compare = cmp_value;
  RMA2_Descriptor *desc = &(handle->descriptors[RMA2_LOCK]);

  if (type==0)
    desc->value[0]=((modifier & 0xfl)<<35l)| ((noti & 0x7l)<<32l)  | ((nodeid & 0xffffl)<<16l) | ((vpid & 0xffl)<<7l) | ((RMA2_LOCK_REQ)<<2l) | 3l;
  else
    desc->value[0]= ((modifier & 0xfl)<<35l)| ((noti & 0x7l)<<32l)  | ((nodeid & 0xffffl)<<16l) | ((vpid & 0xffl)<<7l) | ((RMA2_LOCK_RSP)<<2l) | 3l;
       
   desc->value[1]=((lock_number & 0xffffffl)<<32) | compare;
   desc->value[2]=add_value; 

  _kapi_post_desc(handle, desc, option);
  return 0;
}
EXPORT_SYMBOL(kapi_rma2_post_lock);

int kapi_rma2_put_notification(RMA2_Handle *handle, nodeid_t nodeid, vpid_t vpid, uint64_t value, uint16_t class, RMA2_Notification_Spec noti, RMA2_Command_Modifier modifier, RMA2_Connection_Options option)
{
  RMA2_Command COMMAND = RMA2_NOTIFICATION_PUT;
  RMA2_Descriptor *desc = &(handle->descriptors[COMMAND]);
  
 class = (class & 0xffl)+1; //prepare class value to be used like the count value in the other descriptors
  _kapi_set_desc_values(desc, class, modifier, noti, nodeid, vpid, COMMAND);
  _kapi_set_desc_notification_payload(desc, value);

  _kapi_post_desc(handle, desc, option);

  return 0;
}
EXPORT_SYMBOL(kapi_rma2_put_notification);

int kapi_rma2_put_immediate(RMA2_Handle *handle, nodeid_t nodeid, vpid_t vpid, uint64_t value, void *dest_addr, uint32_t count, RMA2_Notification_Spec noti, RMA2_Command_Modifier modifier, RMA2_Connection_Options option)
{
  RMA2_Command COMMAND = RMA2_IMMEDIATE_PUT;
  RMA2_Descriptor *desc = &(handle->descriptors[COMMAND]);
  
  if(count < 1)
    count = 1;
  
  _kapi_set_desc_values(desc, count, modifier, noti, nodeid, vpid, COMMAND);
  _kapi_set_desc_read_addr(desc, dest_addr); //this is too crude...
  _kapi_set_desc_immediate_value(desc, value);

  _kapi_post_desc(handle, desc, option);

  return 0;
}
EXPORT_SYMBOL(kapi_rma2_put_immediate);
/****************************************************************************************
 * Receive & handle RMA Notifications
 ****************************************************************************************/

RMA2_Command kapi_rma2_noti_get_cmd(RMA2_Notification* noti)
{
  return (RMA2_Command)((noti->word1.value >> 51l) & 0xfl);
}
EXPORT_SYMBOL(kapi_rma2_noti_get_cmd);

RMA2_Notification_Spec kapi_rma2_noti_get_notification_type(RMA2_Notification* noti)
{
  return (noti->word1.value >> 48l) & 0x7l;
}
EXPORT_SYMBOL(kapi_rma2_noti_get_notification_type);

RMA2_Notification_Modifier kapi_rma2_noti_get_mode(RMA2_Notification *noti)
{
  return (noti->word1.value >> 55l) & 0x3fl;
}
EXPORT_SYMBOL(kapi_rma2_noti_get_mode);

uint8_t kapi_rma2_noti_get_error(RMA2_Notification* noti)
{
  return (noti->word1.value >> 61l) & 0x7l;
}
EXPORT_SYMBOL(kapi_rma2_noti_get_error);

nodeid_t kapi_rma2_noti_get_remote_nodeid(RMA2_Notification* noti)
{
  return (noti->word1.value >>32l) & 0xffffl;
}
EXPORT_SYMBOL(kapi_rma2_noti_get_remote_nodeid);

vpid_t kapi_rma2_noti_get_remote_vpid(RMA2_Notification* noti)
{
  return (noti->word1.value >> 23l ) & 0xffl;
}
EXPORT_SYMBOL(kapi_rma2_noti_get_remote_vpid);

uint32_t kapi_rma2_noti_get_size(RMA2_Notification* noti)
{
  return ((noti->word1.value) & 0x7fffffl) +1;
}
EXPORT_SYMBOL(kapi_rma2_noti_get_size);

uint64_t kapi_rma2_noti_get_local_address(RMA2_Notification* noti)
{
  return (noti->word0.value);
}
EXPORT_SYMBOL(kapi_rma2_noti_get_local_address);

uint64_t kapi_rma2_noti_get_notiput_payload(RMA2_Notification* noti)
{
  return noti->word0.value;
}
EXPORT_SYMBOL(kapi_rma2_noti_get_notiput_payload);

uint8_t kapi_rma2_noti_get_notiput_class(RMA2_Notification* noti)
{
  return noti->word1.value & 0xffl;
}
EXPORT_SYMBOL(kapi_rma2_noti_get_notiput_class);

uint32_t kapi_rma2_noti_get_lock_value(RMA2_Notification* noti)
{
  return (noti->word0.value >>32l) & 0xffffffffl;
}
EXPORT_SYMBOL(kapi_rma2_noti_get_lock_value);

uint32_t kapi_rma2_noti_get_lock_number(RMA2_Notification* noti)
{
  return (noti->word0.value ) & 0xffffffl;
}
EXPORT_SYMBOL(kapi_rma2_noti_get_lock_number);

uint8_t kapi_rma2_noti_get_lock_result(RMA2_Notification* noti)
{
  return (noti->word0.value >>24l) & 0xffl;
}
EXPORT_SYMBOL(kapi_rma2_noti_get_lock_result);

void kapi_rma2_noti_dump(RMA2_Notification* noti)
{
  pr_alert("Notification raw values: %llx %llx\n",noti->word1.value, noti->word0.value);
  pr_alert("Command: %x Notification Type (Spec): %x Mode bits: %x Error: %x\n", kapi_rma2_noti_get_cmd(noti), kapi_rma2_noti_get_notification_type(noti), kapi_rma2_noti_get_mode(noti), kapi_rma2_noti_get_error(noti));
  pr_alert("Remote nodeid is %x remote vpid is %x\n", kapi_rma2_noti_get_remote_nodeid(noti), kapi_rma2_noti_get_remote_vpid(noti));
  if (kapi_rma2_noti_get_cmd(noti)==RMA2_NOTIFICATION_PUT) {
    pr_alert("Notification put payload: %llx class: %x\n", kapi_rma2_noti_get_notiput_payload(noti), kapi_rma2_noti_get_notiput_class(noti));
  } else if (kapi_rma2_noti_get_cmd(noti)==RMA2_LOCK_REQ || kapi_rma2_noti_get_cmd(noti)==RMA2_LOCK_RSP) {
    pr_alert("Lock value %x lock number %x lock result %x\n", kapi_rma2_noti_get_lock_value(noti), kapi_rma2_noti_get_lock_number(noti), kapi_rma2_noti_get_lock_result(noti));
  } else {
    pr_alert("Sized put/get. Local address is %llx payload size is %d bytes (decimal)\n", kapi_rma2_noti_get_local_address(noti), kapi_rma2_noti_get_size(noti));
  }

}
EXPORT_SYMBOL(kapi_rma2_noti_dump);

static void rma2_noti_wait(RMA2_Handle *handle)
{
  volatile uint64_t *status = bq_get_status_word(handle->port->bq);//handle->header;
  while(*status == 0) {
  }
}

int kapi_rma2_noti_fetch(RMA2_Handle *handle, RMA2_Notification **noti)
{
  //pr_debug("header in:\nold method: %p\nnew method: %p\n", handle->header, handle->port->bq->status_word);
  rma2_noti_wait(handle);
  //pr_debug("new status: %p\nKAPI: old status: %p\n", bq_get_current_slot(handle->port->bq), handle->port->bq->status_word-1);
  //memcpy(noti, bq_get_current_slot(handle->port->bq), 128);
  *noti = (RMA2_Notification *) bq_get_current_slot(handle->port->bq);
  
//  bq_read_slot_inc_rp(handle->port->bq);
//  bq_read_slot_commit_rp(handle->port->bq,0);
  //pr_debug("fetch ended\n");
  return 0;
}
EXPORT_SYMBOL(kapi_rma2_noti_fetch);

int kapi_rma2_noti_commit(RMA2_Handle *handle, int update_irq)
{
  bq_read_slot_commit_rp(handle->port->bq,update_irq);
  return 0;
}
EXPORT_SYMBOL(kapi_rma2_noti_commit);

int kapi_rma2_noti_mark_read(RMA2_Handle *handle)
{
  bq_read_slot_inc_rp(handle->port->bq);
  return 0;
}
EXPORT_SYMBOL(kapi_rma2_noti_mark_read);

int kapi_rma2_noti_free(RMA2_Handle *handle, int update_irq)
{
  bq_read_slot_inc_rp(handle->port->bq);
  bq_read_slot_commit_rp(handle->port->bq,update_irq);
  return 0;
}
EXPORT_SYMBOL(kapi_rma2_noti_free);

int kapi_rma2_noti_peek(RMA2_Handle *handle)
{
  volatile uint64_t *status = bq_get_status_word(handle->port->bq);//handle->header;
  if(*status == 0) {
    return 0; //no new notification
  } else {
    return 1; //new notification
  }
}
EXPORT_SYMBOL(kapi_rma2_noti_peek);

int kapi_rma2_noti_fetch_nb(RMA2_Handle *handle, RMA2_Notification **noti)
{
  if(kapi_rma2_noti_peek(handle)) {
    kapi_rma2_noti_fetch(handle, noti);
    return 1;
  } else {
    return 0;
  }
}
EXPORT_SYMBOL(kapi_rma2_noti_fetch_nb);


/* *******************************************************************************************
 * Remote RF access helper functions
 * ******************************************************************************************/
int kapi_rra_write(RMA2_Handle *rhandle, uint16_t dest_nodeid, uint64_t dest_rra_address, uint64_t value,uint64_t timeout)
{
  int rc = 0;
  unsigned long int timeout_jiffies=usecs_to_jiffies(timeout);
  unsigned long stop;
  RMA2_Notification *noti;


  stop=jiffies+timeout_jiffies;
  while (kapi_rma2_noti_peek(rhandle)==1)
  {
    rc = kapi_rma2_noti_fetch_nb(rhandle, &noti);
    kapi_rma2_noti_free(rhandle, 1);
    pr_warn("kapi_rra_write: removed unexpected noti prior to transation\n");
    if (time_after(jiffies,stop)) {
      pr_debug("Timeout! jiffies=%ld\n",jiffies);
      return -ETIMEDOUT;
    }
  }
  
  rc = kapi_rma2_put_immediate(rhandle, dest_nodeid, EXTOLL_VPID_RRA, value, (void*)dest_rra_address, 8, RMA2_REQUESTER_NOTIFICATION, RMA2_CMD_DEFAULT, RMA2_CONN_RRA|RMA2_CONN_TC2);
  
  if(rc != 0) {
    return rc;
  }

  stop=jiffies+timeout_jiffies;
  pr_debug("timeout set to %ld, timeout_jiffies to %ld, stop time is %ld\n",(unsigned long) timeout, timeout_jiffies,stop);
  restart_rra_write_noti:

  while (kapi_rma2_noti_peek(rhandle)==0)
  {
    if (time_after(jiffies,stop)) {
      pr_debug("Timeout! jiffies=%ld\n",jiffies);
      return -ETIMEDOUT;
    }
  }

  rc = kapi_rma2_noti_fetch_nb(rhandle, &noti);
  if (kapi_rma2_noti_get_remote_nodeid(noti) != dest_nodeid) {
    pr_warn("kapi_rra_write: received noti from nodeid %d instead of %d. Dropping.\n",kapi_rma2_noti_get_remote_nodeid(noti), dest_nodeid);
    kapi_rma2_noti_free(rhandle, 1);
    goto restart_rra_write_noti;
  }
  if (kapi_rma2_noti_get_cmd(noti) !=RMA2_IMMEDIATE_PUT) {
     pr_warn("kapi_rra_write: received noti with wrong command %d. Dropping.\n",kapi_rma2_noti_get_cmd(noti));
     kapi_rma2_noti_free(rhandle, 1);
     goto restart_rra_write_noti;
  }
  if (kapi_rma2_noti_get_notification_type(noti) != RMA2_REQUESTER_NOTIFICATION) {
     pr_warn("kapi_rra_write: received noti with wrong type %d instead of a RMA2_REQUESTER_NOTIFICATION. Dropping.\n",kapi_rma2_noti_get_notification_type(noti));
     kapi_rma2_noti_free(rhandle, 1);
     goto restart_rra_write_noti;
  }
  if (kapi_rma2_noti_get_local_address(noti) != value) {
     pr_warn("kapi_rra_write: received noti with wrong address %lx instead of %lx. Dropping.\n",(unsigned long) kapi_rma2_noti_get_local_address(noti),(unsigned long)value);
     kapi_rma2_noti_free(rhandle, 1);
     goto restart_rra_write_noti;
  }
  if (kapi_rma2_noti_get_error(noti)!=0) {
    pr_warn("kapi_rra_write: received noti indicating an error occured: %d.\n",kapi_rma2_noti_get_error(noti));
    kapi_rma2_noti_free(rhandle, 1);
    return -1;
  }
  kapi_rma2_noti_free(rhandle, 1);
  return 0;
}
EXPORT_SYMBOL(kapi_rra_write);

uint64_t kapi_rra_read(RMA2_Handle *rhandle, uint16_t dest_nodeid, uint64_t dest_rra_addr,uint64_t *value, uint64_t timeout)
{
  int rc = 0;
  unsigned long int timeout_jiffies=usecs_to_jiffies(timeout);
  unsigned long stop;

  uint64_t *page_addr = page_address(rhandle->rra_page);
  uint64_t tmp_addr = virt_to_phys(page_addr);
  RMA2_Notification *noti;

  stop=jiffies+timeout_jiffies;
  while (kapi_rma2_noti_peek(rhandle)==1)
  {
    rc = kapi_rma2_noti_fetch_nb(rhandle, &noti);
    kapi_rma2_noti_free(rhandle, 1);
    pr_warn("kapi_rra_read: removed unexpected noti prior to transation\n");
    if (time_after(jiffies,stop)) {
      pr_debug("Timeout! jiffies=%ld\n",jiffies);
      return -ETIMEDOUT;
    }
  }


  rc = kapi_rma2_get_bt(rhandle, dest_nodeid, EXTOLL_VPID_RRA, (void*)dest_rra_addr, (void*)tmp_addr, 8, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT, RMA2_CONN_RRA|RMA2_CONN_TC2);
  if(rc != 0) {
    return rc;
  }

  stop=jiffies+timeout_jiffies;
  pr_debug("timeout set to %ld, timeout_jiffies to %ld, stop time is %ld\n",(unsigned long) timeout, timeout_jiffies,stop);
 restart_rra_read_noti:

  while (kapi_rma2_noti_peek(rhandle)==0)
  {
  if (time_after(jiffies,stop)) {
      pr_debug("Timeout! jiffies=%ld\n",jiffies);
      return -ETIMEDOUT;
    }
  }

  rc = kapi_rma2_noti_fetch_nb(rhandle, &noti);
  
  if (kapi_rma2_noti_get_remote_nodeid(noti) != dest_nodeid) {
    pr_warn("kapi_rra_read: received noti from nodeid %d instead of %d. Dropping.\n",kapi_rma2_noti_get_remote_nodeid(noti), dest_nodeid);
    kapi_rma2_noti_free(rhandle, 1);
    goto restart_rra_read_noti;
  }
  if (kapi_rma2_noti_get_cmd(noti) != RMA2_GET_BT_RSP) {
     pr_warn("kapi_rra_read: received noti with wrong command %d. Dropping.\n",kapi_rma2_noti_get_cmd(noti));
     kapi_rma2_noti_free(rhandle, 1);
     goto restart_rra_read_noti;
  }
  if (kapi_rma2_noti_get_notification_type(noti) != RMA2_COMPLETER_NOTIFICATION) {
     pr_warn("kapi_rra_read: received noti with wrong type %d instead of a RMA2_COMPLETER_NOTIFICATION. Dropping.\n",kapi_rma2_noti_get_notification_type(noti));
     kapi_rma2_noti_free(rhandle, 1);
     goto restart_rra_read_noti;
  }
  if (kapi_rma2_noti_get_local_address(noti) != tmp_addr) {
     pr_warn("kapi_rra_read: received noti with wrong address %lx instead of %lx. Dropping.\n",(unsigned long)kapi_rma2_noti_get_local_address(noti),(unsigned long)tmp_addr);
     kapi_rma2_noti_free(rhandle, 1);
     goto restart_rra_read_noti;
  }
  if (kapi_rma2_noti_get_error(noti)!=0) {
    pr_warn("kapi_rra_read: received noti indicating an error occured: %d.\n",kapi_rma2_noti_get_error(noti));
    kapi_rma2_noti_free(rhandle, 1);
    return -1;
  }

  kapi_rma2_noti_free(rhandle, 1);

  *value = page_addr[0];
  return 0;
}
EXPORT_SYMBOL(kapi_rra_read);


/* *******************************************************************************************
 * Register external IRQ handler with the Extoll IRQ handling
 * ******************************************************************************************/
void kapi_irq_register(irq_handler_t handler_fn)
{
  set_extoll_dummyWrapper(handler_fn);
}
EXPORT_SYMBOL(kapi_irq_register);

void kapi_irq_register_with_arguments(irq_handler_t handler_fn, int irq, void *nvl)
{
  set_extoll_dummyWrapper(handler_fn);
  set_nvidia_state(nvl);
  set_nvidia_irq(irq);
}
EXPORT_SYMBOL(kapi_irq_register_with_arguments);

void kapi_irq_unregister(void)
{
  extoll_clean_dummyWrapper();
}
EXPORT_SYMBOL(kapi_irq_unregister);


/* *************************************************************************
 * Handle scatter/gather list mapping via ATU2
 * ************************************************************************/
int kapi_atu2_map_sg(int vpid, struct scatterlist *sg, unsigned long count, unsigned long *nla){
	struct page *pagelist[count];
	struct scatterlist *tmp_sg;
	int i, ret = 0;

	for_each_sg(sg, tmp_sg, count, i) {
		pagelist[i] = sg_page(tmp_sg);
	}

	ret = atu2_register_page_list(vpid, pagelist, count, sizeof(struct page*), 1, 1, nla);
	if (ret != 0){
		pr_alert("atu2_register_page_list failed\n");
		return ret;
	}
	
	return 0;
}
EXPORT_SYMBOL(kapi_atu2_map_sg);

int kapi_atu2_map_pagelist(int vpid, struct page **pagelist, unsigned long count, unsigned int stride, unsigned long *nla){
	int ret = 0;

	ret = atu2_register_page_list(vpid, pagelist, count, stride, 1, 1, nla);
	if (ret != 0){
		pr_alert("atu2_register_page_list failed\n");
		return ret;
	}
	
	return 0;
}
EXPORT_SYMBOL(kapi_atu2_map_pagelist);

int kapi_atu2_unmap_sg(int vpid, unsigned long count, unsigned long nla){
	int ret = 0;

	//ret = atu2_unregister_pages_by_nla(vpid, nla, count, 1);
	ret = atu2_unregister_physical_region(vpid, nla, count*PAGE_SIZE);
	if (ret != 0){
		pr_alert("atu2_unregister_physical_region failed for scatter/gather list.\n");
		return ret;
	}

	return 0;
}
EXPORT_SYMBOL(kapi_atu2_unmap_sg);


/* *******************************************************************************************
 *  Module Handleing
 * ******************************************************************************************/
static int __init kapi_init(void)
{
  pr_debug("module_loaded\n");
      //somehow check if the extoll-device is present and ready
  if (extoll_get_init_done()==0)
  {
    pr_alert("EXTOLL Base driver not initialized! Bailing out\n");
    return -1;
  }

  return 0;
}
  static void __exit kapi_exit(void)
{
  pr_debug("EXTOLL Kernel API unloaded.\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tobias Groschup, Sarah Neuwirth, Mondrian Nuessle");
MODULE_VERSION("1.0");
module_init(kapi_init);
module_exit(kapi_exit);
