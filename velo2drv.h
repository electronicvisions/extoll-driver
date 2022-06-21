/*
 *  This file is part of the  Linux Kernel Driver Package for EXTOLL R2.
 *
 *  Copyright (C) 2011 EXTOLL GmbH
 *
 *  Written by Mondrian Nuessle (2011)
 *  Partly based on work done by Philip Degler (2007)
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


#ifndef _VELO2_H_
#define _VELO2_H_

#include "arch_define.h"

//includes needed to include this header
#include "extoll_bq.h"

#include <linux/list.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

/*!
\file velo2drv.h
This is the driver of the VELO functional unit of EXTOLL.
This driver enables user space applications to directly leverage
the low latency of VELO using OS bypass operations.
*/

/* minors */
#define VELO2_MINOR_COUNT	1
#define VELO2_MINOR			0

/* ports config */
#define VELO2_MAX_VPID 256
#define VELO2_MAX_MSG_SIZE 120

//FIXME not tested yet!
//static unsigned int VELO2_MIN_VPID = 0;
//module_param(VELO2_MIN_VPID, uint, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
//EXPORT_SYMBOL(VELO2_MIN_VPID);


/******************************************************************************
*  Definition of requester (=rport) and completer ports (cport)	      *
******************************************************************************/

typedef  union {
	struct {
	  uint16_t nodeid;
	  uint8_t vpid;
	  uint8_t reserved0;
	};
	uint32_t raw;
} velo2_destination_t;

typedef  union {
	struct {
	  velo2_destination_t dest;
	  uint8_t mtt:2;
	  uint8_t req_irq:1;
	  uint8_t reserved1:5;
	  uint8_t tag;
	  uint8_t length:7;
	  uint8_t reserved2:1;
	  uint8_t reserved3; 
	};
	uint64_t raw;
} velo2_header_t;


/*!
  \brief Completer port descriptor 
 */
struct velo_port {
  pid_t pid;				//! process that owns ports
  //atomic_t rcount;			//! reference counter
  uint32_t opened;        /* port already used by another process?? */
  uint32_t kernel_owned;
  uint32_t vpid;
  uint32_t mbox_size;
  uint64_t desc_size;

  int wb_rp; //! last write pointer value actually written back (lazy pointer update, mostly unused in kernel)
  int rp; //! current read pointer

  
  uint32_t tx_prot_desc;
  uint32_t rx_prot_desc;
  uint32_t src_id;
  uint32_t htax_alternative_port_enable;
  uint32_t htax_alternative_port;
  
  uint32_t allow_tc_mapped[4];
  uint32_t allow_alternative_port;
  
  extoll_bq_t* bq; //!the bufferqueue instance for this port
};
typedef struct velo_port velo_port_t;

/******************************************************************************
*  Port & vpid management							      *
******************************************************************************/
/*!
  \brief Ports per thread/process 
  This datatype stores the ports that are assigned to one ower process/thread.
 */
// struct velo_port_owner {
//     pid_t pid;				//! process that owns ports
//     atomic_t rcount;			//! reference counter
//     uint64_t vpid; //! VPID of this process
//     struct velo_rport *current_rport;	//! points to latest rport
//     struct velo_cport *current_cport;	//! points to latest cport        
//     struct list_head entry;			//! entry in owner list
// };


/******************************************************************************
*  Definition of velo hardware info					      *
******************************************************************************/
/*!
  \brief The VELO device structure
  This structure represents the VELO functional unit of the EXTOLL hardware.
 */
struct velo2_device {

    struct pci_dev *devp;         //! pointer to the pci device of EXTOLL
    struct cdev cdev;             //! the character device file for VELO2
    dev_t devnr;                 //! the major number of the VELO device file
    struct device* dev;
    
    void* velo_mmio_vaddr;         //!requester space, kernel virtual address
    unsigned long velo_mmio_addr; //!requester space, physical address
    unsigned long velo_mmio_size; //!size of the mmio region

    uint32_t slot_size; //!Size of the buffer queues slots in bytes.
};

typedef struct velo2_device velo2_device_t;

/* *****************************************************************************
 * Interrupt handling 					      		       *
 ******************************************************************************/

/*! 
  \brief Type for the velo2 vpid interrupt handler functions 
*/
typedef void (*velo2_i_handler)(int vpid, snq_entry_t*);

/*! 
  \brief Registers a handler function for the velo2 vpid interrupt
    */
void velo2_register_vpid_irq_handler(int idx, velo2_i_handler handler);

/*!
  \brief Deregisters a handler function for the velo2 vpid interrupt
    */
void velo2_deregister_vpid_irq_handler(int idx);


/******************************************************************************
*  shared function prototypes						      *
******************************************************************************/
/*!
 \brief Searches the velo_port_owner for a given pid
*/
struct velo_port_owner *velo2_find_owner(pid_t pid);


  /*!
  \brief Read the VELO Read Pointer for the given completer port from hardware
 */
uint64_t velo2_get_rp(struct velo_port *portp);

/**
set the logica read pointer
*/
void velo2_set_rp(velo_port_t *portp, uint64_t new_rp);

/*!
  \brief Read the VELO Write Pointer for the given completer port from hardware
 */
uint64_t velo2_get_wp(struct velo_port *portp);

/**
* Sets the write pointer of velo device
* @param *portp: completer port management data
*/
void velo2_set_wp(velo_port_t *portp, uint64_t new_wp);

/*! 
 *\brief Give direct access to the velo-device.
 */
velo2_device_t* velo_get_device(void);

/*!
 *\brief Get the context to send (and recieve) a velo-message.
 */
//int velo_connect(struct velo_port_owner *ownerp, struct velo_cport *cportp);

/*!
 * \brief free allocated ports
 */
//int velo_disconnect(struct velo_port_owner *ownerp);

/*!
 * \brief gets the current nodeid
 */
uint32_t velo2_get_nodeid(void);

/*!
 * \brief get the current mbox size
 */
uint velo2_get_mbox_size(void);

/*!
 *\brief method to send bufp via velo
 */
int velo2_write(struct velo_port *portp, uint32_t node_id, uint32_t mbox_id, 
	       uint64_t *bufp, uint32_t buflen);
/*!
 * \brief method to recieve a message
 */
int velo2_read(struct velo_port *portp, uint64_t *buffer);

void velo2_set_tx_id(uint32_t vpid, uint16_t tx_nodeid, uint16_t tx_vpid);
void velo2_set_tx_protection_descriptor(uint32_t vpid, uint16_t protdesc);

/* **********************************************************************************
 * prototypes for kapi helper methods
 * *********************************************************************************/
int velo2_lock_mutex(void);

void velo2_unlock_mutex(void);

//initialise and register the port, opens requester
int velo2_init_port (velo_port_t **port, int vpid);

//unregister the port
int velo2_close_port(velo_port_t *port);

//open completer
//if total size and desc size are 0 the size described in the port will be used
int velo2_open_completer(velo_port_t *portp, unsigned int total_size, unsigned int desc_size);

#endif
