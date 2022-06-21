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

//#ifdef ARCH
//if (ARCH=k1om){
//#define MICEXTOLL
//}
//#endif

#ifndef _RMA2_H_
#define _RMA2_H_
/*!
\file rma2drv.h
This is the driver of the RMA functional unit of EXTOLL.
This driver enables user space applications to directly leverage
the low latency of RMA using OS bypass operations.
*/

/* minors 
 *  0 is for physical address access
 *  1 is for RRA access
 *  2 is for normal user-space address with address translation
 */
#define RMA2_MINOR_COUNT		1
#define RMA2_MINOR			0

/* ports config */
#define RMA2_MAX_VPID 256

#include "arch_define.h"

/******************************************************************************
*  Definition port structures (endpoints)                                     *
******************************************************************************/

/*!
  \brief RMA2 port descriptor 
 */
struct rma_port {
  pid_t pid;				//! process that owns ports
  //atomic_t rcount;			//! reference counter
  uint32_t opened;        		/* port already used by another process?? */
  uint32_t kernel_owned;
  uint32_t vpid;
  uint32_t notiq_size;
  uint64_t desc_size;

  int wb_rp; //! last write pointer value actually written back (lazy pointer update, mostly unused in kernel)
  int rp; //! current read pointer
  int async_flag; //! flag that defines how to proceed for in kernel reception: 0-> poll indefinit, 1->poll "poll_times", 2->use interrupts
  wait_queue_head_t wq; //! wait queue, to put process to sleep if waiting for a message in async kernel communication mode
  int poll_flag; //! flag for in kernel polling
  int poll_times;//! to count in kernel polling times
  
  uint16_t vpid_en;
  uint16_t tu_completer;
  uint16_t tu_responder;
  uint16_t excell_enable;
  uint16_t tc0;
  uint16_t tc1;
  
  uint16_t tc2;
  uint16_t tc3;
  
  uint16_t protection_descriptor;
  uint16_t steering_tag;
  uint16_t tph;
  uint16_t th;
 
    
  extoll_bq_t* bq; //!the bufferqueue instance for this port
};
typedef struct rma_port rma_port_t;


/******************************************************************************
*  Definition of velo hardware info					      *
******************************************************************************/
/*!
  \brief The RMA2 device structure
  This structure represents the RMA functional unit of the EXTOLL hardware.
 */
struct rma2_device {

#ifdef MICEXTOLL
    struct micextoll_device *devp;
#else
    struct pci_dev *devp;         //! pointer to the pci device of EXTOLL
#endif
    struct cdev cdev;             //! the character device file for VELO2
    dev_t devnr;                 //! the major number of the VELO device file
    struct device* dev;
    
    void* rma_mmio_vaddr;         //!requester space, kernel virtual address
    unsigned long rma_mmio_addr; //!requester space, physical address
    unsigned long rma_mmio_size; //!size of the mmio region
    
    uint16_t nodeid;
    
    /* FU wider configuration bits */
    uint16_t mtu;
    uint16_t pcie_mode;
    uint16_t pcie_readrq;
    uint16_t force_error_notifications;
    uint16_t read_engine_passpwd_disable;
    
    uint64_t  lock_base_address;
    uint32_t* lock_base_vaddress;
    uint32_t  lock_number_locks;
    uint32_t  lock_number_vpids;
    uint16_t  lock_steering_tag;
    uint16_t  lock_tph;
    uint16_t  lock_th;
    uint32_t  lock_size;
    
    uint16_t  requester_history_mode;
    uint16_t  responder_history_mode;
    uint16_t  completer_history_mode;
    
    uint32_t  bq_timeout;
    uint16_t  bq_timeout_enable;
    uint32_t  wcbuf_timeout;
    uint16_t  wcbuf_timeout_enable;
};

typedef struct rma2_device rma2_device_t;
/* *****************************************************************************
 * Interrupt handling 					      		       *
 ******************************************************************************/

/*! 
  \brief Type for the velo2 vpid interrupt handler functions 
*/
typedef void (*rma2_i_handler)(int vpid, snq_entry_t*);

/*! 
  \brief Registers a handler function for the velo2 vpid interrupt
    */
void rma2_register_vpid_irq_handler(int idx, rma2_i_handler handler);

/*!
  \brief Deregisters a handler function for the rma2 vpid interrupt
    */
void rma2_deregister_vpid_irq_handler(int idx);

/******************************************************************************
*  shared function prototypes						      *
******************************************************************************/
/*!
 \brief Searches the rma_port_owner for a given pid
*/
struct rma_port_owner *rma2_find_owner(pid_t pid);

/*!
  \brief Read the RMA Notiq Read Pointer for the given port from hardware
 */
uint64_t rma2_get_rp(struct rma_port *portp);

/*!
  \brief Read the RMA Notiq Write Pointer for the given port from hardware
 */
//uint64_t velo2_get_wp(struct rma_port *portp);//conflicts with velo2_get_wp from velo2drv.h

/*! 
 *\brief Give direct access to the rma2-device.
 */
rma2_device_t* rma2_get_device(void);

/*!
 * \brief gets the current nodeid
 */
uint32_t rma2_get_nodeid(void);

/*!
 * \brief get the current notiq size
 */
uint rma2_get_notiq_size(uint16_t vpid);

/*!
 * \brief register a port with the driver
 */ 
int rma2_init_port(rma_port_t **port,int vpid);

/*!
 * \brief register a port with the driver
 */ 
int rma2_init_completer(rma_port_t *port);

/*!
 * \brief unregister a port with the driver
 */
int rma2_close_port(rma_port_t *port);

/*!
 * \brief Get RMA MTU size
 */
uint32_t rma_get_mtu(void);

int rma2_lock_mutex(void);

void rma2_unlock_mutex(void);


#endif
