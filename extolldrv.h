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
#ifndef _EXTOLL2_H_
#define _EXTOLL2_H_

#include "extoll_kernel_version_compability_layer.h"

#include "arch_define.h"

#include <linux/irqreturn.h>
#include <linux/interrupt.h>
#include <linux/types.h>

#ifdef MICEXTOLL
  #include "micextoll.h"
#endif

/*!
\file extolldrv
This driver is the base driver for EXTOLL. It relies on extoll_rf for management
of the EXTOLL register file.
The base driver manages the PCI device (as seen from the Linux side) and such things
as claiming and mapping of BARs and interrupts. It does not implement any communication
functions.
*/

//The following Vendor IDs are currently used by EXTOLL Devices
#define PCI_VENDOR_ID_EXTOLL             0x1cad
#define PCI_VENDOR_ID_EUROTECHEXTOLL     0x1172
#define PCI_VENDOR_ID_FAKE               0x0007
#define PCI_VENDOR_ID_TEST		  0x1cad

//The following device IDs are given to the different EXTOLL Devices
#define PCI_DEVICE_ID_VENTOUX1           0x7
#define PCI_DEVICE_ID_GALIBIER           0x9
#define PCI_DEVICE_ID_TOURMALET          0x10
#define PCI_DEVICE_ID_TOURMALET_V2       0x11
#define PCI_VENDOR_ID_AURORA             0x4
#define PCI_DEVICE_ID_VENTOUXHT3         0x10

//default MMIO sizes for R2 are 32M each, only SMFU is 256MB
#define EXTOLL_R2_RF_MMIO_SIZE           33554432ll
#define EXTOLL_R2_VELO2_MMIO_SIZE        33554432ll
//16777216l
#define EXTOLL_R2_RMA2_MMIO_SIZE         33554432l
#ifdef DEEP_HOST 
  //Supports 16 KNCs right now
  //#define EXTOLL_R2_SMFU2_MMIO_SIZE        17179869184l //16GB
  //#define EXTOLL_R2_SMFU2_MMIO_SIZE        34359738368l //32GB
  //#define EXTOLL_R2_SMFU2_MMIO_SIZE        34393292800l //32GB+32MB
  //#define EXTOLL_R2_SMFU2_MMIO_SIZE       274877906944l //256GB
  #define EXTOLL_R2_SMFU2_MMIO_SIZE       549755813888l //512GB
  
#else
  #define EXTOLL_R2_SMFU2_MMIO_SIZE        268435456l
#endif

#ifdef DEEP_HOST
  //3 units use bar 0
  #define EXTOLL_R2_RF_MMIO_OFFSET         ((256*1024*1024)-EXTOLL_R2_RF_MMIO_SIZE)
  #define EXTOLL_R2_VELO2_MMIO_OFFSET      (EXTOLL_R2_RF_MMIO_OFFSET-EXTOLL_R2_VELO2_MMIO_SIZE)
  #define EXTOLL_R2_RMA2_MMIO_OFFSET       (EXTOLL_R2_VELO2_MMIO_OFFSET-EXTOLL_R2_RMA2_MMIO_SIZE)
#else
  //3 units use bar 0
  #define EXTOLL_R2_RF_MMIO_OFFSET         0l
  #define EXTOLL_R2_VELO2_MMIO_OFFSET      (0+EXTOLL_R2_RF_MMIO_SIZE)
  #define EXTOLL_R2_RMA2_MMIO_OFFSET       (EXTOLL_R2_VELO2_MMIO_OFFSET+EXTOLL_R2_VELO2_MMIO_SIZE)
#endif

//smfu uses bar2
#define EXTOLL_R2_SMFU2_MMIO_OFFSET      0
//(EXTOLL_R2_RMA2_MMIO_OFFSET+EXTOLL_R2_RMA2_MMIO_SIZE)

#define EXTOLL_R2_RF_MMIO_END         (EXTOLL_R2_RF_MMIO_OFFSET+EXTOLL_R2_RF_MMIO_SIZE)
#define EXTOLL_R2_VELO2_MMIO_END      (EXTOLL_R2_VELO2_MMIO_OFFSET+EXTOLL_R2_VELO2_MMIO_SIZE)
#define EXTOLL_R2_RMA2_MMIO_END       (EXTOLL_R2_RMA2_MMIO_OFFSET+EXTOLL_R2_RMA2_MMIO_SIZE)
#define EXTOLL_R2_SMFU2_MMIO_END      (EXTOLL_R2_SMFU2_MMIO_OFFSET+EXTOLL_R2_SMFU2_MMIO_SIZE)

//HTAX Configuration Constants
/* This functions actuallys configures the address map for EXTOLL.
   Current mapping is to BAR0.
   0 - 16M: RF
   16M - 32M: VELO
   32M-64M: RMA
   BAR2: SMFU
  */

#define HTAX_INVTL_POSTED_VC    (1l<<14l)
#define HTAX_INVTL_NONPOSTED_VC (2l<<14l)
#define HTAX_INVTL_RESPONSE_VC  (4l<<14l)

#define HTAX_INVTL_RF_PORT_OH     (8l<<5l)
#define HTAX_INVTL_VELO_PORT_OH   (16l<<5l)
#define HTAX_INVTL_RMAREQ_PORT_OH (32l<<5l)
#define HTAX_INVTL_SMFU_PORT_OH   (256l<<5l)

#define HTAX_INVTL_POSTED_HOST_PORT     (0l<<1l)
#define HTAX_INVTL_NONPOSTED_HOST_PORT  (1l<<1l)
#define HTAX_INVTL_RESPONSE_HOST_PORT   (2l<<1l)
#define HTAX_INVTL_RF_PORT     (3l<<1l)
#define HTAX_INVTL_VELO_PORT   (4l<<1l)
#define HTAX_INVTL_RMAREQ_PORT (5l<<1l)
#define HTAX_INVTL_SMFU_PORT   (8l<<1l)


#define HTAX_INVTL_ENABLE 1l
#define HTAX_USE_SF_MODE (1l<<14l)
#define HTAX_USE_VC_MODE (0l<<14l)
#define HTAX_GENERAL_ENABLE (1l<<15l)


//VPID to use for management stuff
#define EXTOLL_VPID_MGMT 255
//VPID to use for the net driver
#define EXTOLL_VPID_NET  254
//VPID to use for a future direct socket implementation
#define EXTOLL_VPID_DS   253
//VPID for remote RF access
#define EXTOLL_VPID_RRA	 252
//max VPID for "normal" usage
#define EXTOLL_VPID_MAX  251

#define EXTOLL_PAGE 4096

//Scratchpad offsets
#define EXTOLL_SCRATCH_CHIP_REV 0
#define EXTOLL_SCRATCH_FW_REV1 1
#define EXTOLL_SCRATCH_FW_REV2 2
#define EXTOLL_SCRATCH_NETWORK_STATE 3

//! Network is unconfigured
#define EXTOLL_NW_STATE_UC 0
////! Network is configured
#define EXTOLL_NW_STATE_C 1
////! Network is stopped (reconfigure)
#define EXTOLL_NW_STATE_S 2

typedef struct {
  union {
    struct {
      unsigned long int ts : 40;
      unsigned long int tc : 8;
      unsigned long int pc : 12;
      unsigned long int rsvd : 3;
      unsigned long int flip : 1;
    } fields;
    uint64_t value;
  };
} snq_header_t;

/*!
\brief The structure that represents one snq entry
*/
typedef struct {
  uint64_t payload[7];
  snq_header_t header;
} snq_entry_t;

/*!
\brief The structure to manage the SNQ on one EXTOLL device
*/
typedef struct {
  uint32_t wb_rp;
  uint32_t wp;
  unsigned int fb;
  volatile snq_entry_t* snq;
  unsigned long snq_pa;
  unsigned long snq_size;
  unsigned long watermark;
  unsigned long snq_mask;
  unsigned long irq_bits[2];
} snq_config_t;

/*! 
  \brief Type for the extoll interrupt handler functions 
*/
typedef void (*extoll_i_handler_t)(snq_entry_t*, int te, int entry_idx);

/*! 
  \brief Type for the extoll network state handler functions 
*/
typedef void (*extoll_nw_state_handler_t)(uint64_t nw_state);


/*! 
  \brief Registers a handler function for the extoll interrupt cause with the given idx
  
  \param idx The interrupt cause index (i.e. the bit in the cause register) that should cause execution of handler
  \param handler the handler function for the given interrupt cause
  */
void extoll_register_interrupt_handler(int idx, extoll_i_handler_t handler);

/*!
  \brief Deregisters a handler function for the extoll interrupt cause with the given idx
  
  \param idx The interrupt cause index (i.e. the bit in the cause register) that should not cause execution of a handler
  */
void extoll_deregister_interrupt_handler(int idx);


struct extoll_nw_handler_list{
  struct list_head list;
  extoll_nw_state_handler_t handler;
};
typedef struct extoll_nw_handler_list extoll_nw_handler_list_t;

typedef enum {
	RMA_VPID,
	VELO_VPID,
	SMFU_PID
} VPID_TYPE; 

struct extoll_nw_task_list{
  struct list_head list;
  struct task_struct* task;
  VPID_TYPE vpid_type;
  int vpid;
};
typedef struct extoll_nw_task_list extoll_nw_task_list_t;


/*!
\brief The structure to manage one EXTOLL device
*/
struct extoll_device {
#ifdef MICEXTOLL
    struct micextoll_device *devp;
#else
    struct pci_dev *devp;	//! pointer to the kernel PCI device (HyperTransport devices are also managed as PCI devices).
#endif
    //void *bar0_vaddr;		//! kernel virtual address of BAR0 of the device. The registerfile is located in BAR0.
    unsigned long bar0_addr;	//! physical virtual address of BAR0 of the device. The registerfile is located in BAR0.
    unsigned long bar0_size;	//! size of BAR0 of the device. The registerfile is located in BAR2.
    //void *bar2_vaddr;		//! kernel virtual address of BAR0 of the device. The VELO (Requester) functional unit is located in BAR2.
    unsigned long bar2_addr;	//! physical virtual address of BAR0 of the device. The VELO (Requester) functional unit is located in BAR2.
    unsigned long bar2_size;	//! size of BAR2 of the device. The VELO (Requester) functional unit is located in BAR0.
    //void *bar4_vaddr;		//! kernel virtual address of BAR0 of the device. The RMA (requester) functional unit is located in BAR0.
    unsigned long bar4_addr;	//! physical virtual address of BAR0 of the device. The RMA (requester) functional unit is located in BAR0.
    unsigned long bar4_size;	//! size of BAR0 of the device. The RMA (requester) functional unit is located in BAR2.
    
    void* rf_vaddr;              //! kernel virtual address of the registerfile, located in BAR0, not cacheable
    void* velo2_vaddr;           //! kernel virtual address of the VELO unit, located in BAR0, wc mapped
    void* rma2_vaddr;            //! kernel virtual address of the RMA unit, located in BAR0, wc mapped
    void* smfu2_vaddr;           //! kernel virtual address of the SMFU unit, located in BAR2, not cacheable

    unsigned long rf_paddr;      //! physical address of the registerfile,
    unsigned long velo2_paddr;   //! physical address ofextoll_rf_snq_rf_trigger_now the VELO unit
    unsigned long rma2_paddr;    //! physical address of the RMA unit
    unsigned long smfu2_paddr;   //! physical address of the SMFU unit
    
    unsigned long rf_size;       //! size of the memory region (part of the BAR) for the registerfile
    unsigned long velo2_size;    //! size of the memory region (part of the BAR) for the VELO unit
    unsigned long rma2_size;     //! size of the memory region (part of the BAR) for the RMA unit
    unsigned long smfu2_size;    //! size of the memory region (part of the BAR) for the SMFU unit
    
    unsigned int init_done;      //! set to one if basic init was successfull
    snq_config_t snq_config;     //! SNQ config structure
#ifdef MICEXTOLL
    unsigned int irq;
#else    
    unsigned int num_irqs;       //! number of irqs available for this device
    unsigned int irqs[32];       //! irq numbers for this device
    unsigned int irq_free[32];   //! whether this irq can still be used
#endif

    unsigned int use_msi;        //! Wheter we use MSI or not
    
    unsigned int use_pcie;       //! Whether device is attached to pcie (1) or HT (0)
    unsigned int nw_state;       //! What state the network is in
    spinlock_t nw_state_lock;
    struct list_head nw_state_handlers;
    struct list_head nw_task_list;
    struct tasklet_struct xbar_outp10_tasklet;
};

typedef struct extoll_device extoll_device_t;

#ifdef MICEXTOLL

void extoll_register_dev(struct micextoll_device *dev);
#endif
/*Functions etc. internal to extolldrv.ko*/
#ifdef EXTOLLDRV

#ifndef MICEXTOLL
/*! 
 /brief Register a handler for an additional MSI, if free MSI vectors are available (usually for remote device)
 returns zero on success
 Parameters are like request_irq()
 */
int extoll_request_free_irq(irq_handler_t handler,
                unsigned long irqflags,
                const char *devname,
                void *dev_id);
#endif

/*!
/brief The actual interrupt handler
This function is registered with the kernel. It calls the handler function for
individual interrupt causes, that have been registered using extoll_register_interrupt_handler()
\param The irq the handler is called for
\param dev_id the devp parameter of request_irq()
*/
static irqreturn_t extoll_interrupt_handler(int irq, void *dev_id);

/*!
\brief Initializes the EXTOLL interrupt handler table.
All interrupt causes are initialized with a null handler, thus disabled.
*/
void init_extoll_interrupt_handlers(void);
#endif

extern int extoll_get_init_done(void);

#ifdef MICEXTOLL
extern struct micextoll_device* extoll_get_pdev(void);
#else
extern struct pci_dev* extoll_get_pdev(void);
#endif

extern struct class* extoll_get_class_user(void);
extern struct class* extoll_get_class_priv(void);

extern uint32_t extoll_get_mtu(void);

extern void* extoll_get_rf_vaddr(void);

extern void* extoll_get_velo2_vaddr(void);

extern void* extoll_get_rma2_vaddr(void);

extern void* extoll_get_smfu_vaddr(void);

extern unsigned long extoll_get_rf_addr(void);

extern unsigned long extoll_get_velo2_addr(void);

extern unsigned long extoll_get_rma2_addr(void);

extern unsigned long extoll_get_smfu_addr(void);

extern unsigned long  extoll_get_rf_size(void);

extern unsigned long  extoll_get_velo2_size(void);

extern unsigned long  extoll_get_rma2_size(void);

extern unsigned long  extoll_get_smfu_size(void);

extern unsigned long extoll_get_bar0_addr(void);

extern unsigned int extoll_get_interrupt_counter(void);

extern void extoll_set_interrupt_counter(unsigned int v);

extern void snq_dump_entry(snq_entry_t * entry);

extern int extoll_get_irq(void);

extern unsigned long extoll_query_max_htoc_size(void);

extern unsigned long extoll_query_max_vpids(void);

extern unsigned long extoll_query_vpids_per_page(void);

extern void set_extoll_dummyWrapper(irq_handler_t knc_handler);

extern void set_nvidia_state(void *nvl);

extern void set_nvidia_irq(int irq);

extern void extoll_clean_dummyWrapper(void);

#ifdef MICEXTOLL
unsigned long extoll_get_smfu_addr_physical(void);

#endif

extern int extoll_pcie_get_mps(struct pci_dev *dev);

extern int extoll_pcie_get_readrq(struct pci_dev *dev);

extern int extoll_is_tourmalet(void);

extern int extoll_add_nw_state_handler(extoll_nw_state_handler_t handler);
extern int extoll_remove_nw_state_handler(extoll_nw_state_handler_t handler);
extern uint64_t extoll_get_nw_state(void);

extern int extoll_add_nw_state_task(int vpid, VPID_TYPE vtype, struct task_struct* task);
extern int extoll_remove_nw_state_task(int vpid, VPID_TYPE vtype);

#endif
