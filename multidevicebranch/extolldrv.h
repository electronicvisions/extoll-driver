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

// Includes
//--------------

//-- PCI
#include <linux/pci.h>

//-- IRQ things
#include <linux/interrupt.h>
#include <linux/htirq.h>

//-- Driver user interface for structure definitions
#include "extolldrv_user.h"

/*!
\file extolldrv

This driver is the base driver for EXTOLL. It relies on extoll_rf for management
of the EXTOLL register file.
The base driver manages the PCI device (as seen from the Linux side) and such things
as claiming and mapping of BARs and interrupts. It does not implement any communication
functions.

 About Extoll Devices/Units mapping
  ---------------------------------

  Extoll device: One physical device (HT/PCIe card)
  Extoll unit  : The extoll functions (RF,RMA,VELO...) present in a card

   - Per default, one extoll device has at least one extoll unit (standard case)
   - One extoll device may have 2+ units in it (Like KLA design)
   - One system may have 2+ Extoll devices with 1+ units (2 cards with KLA design would have 4 units)

   Mapping detection:

   - Each extoll device (lspci loop) describes at least one unit
   - For each of the extoll device, use the vendorid:deviceid pair to guess
     If there are more than one unit in the device (a bit hardcoded for now, but its okay,
     and would be very easy to make for dynamic if needed)


   Extoll Devices:

   Name        Vendor ID          Device ID        Units
   -----------------------------------------------------
   Ventoux1    0007               0007               1
   Ventoux2    0007               0008               1
   Galibier1   0007               0009               1
   Tourmalet   0007               000A               1
   KLA         0007               000B               2

*/

#define PCI_VENDOR_ID_EXTOLL             0x7
#define PCI_DEVICE_ID_VENTOUX1           0x7
#define PCI_DEVICE_ID_VENTOUX2           0x8
#define PCI_DEVICE_ID_GALIBIER1          0x9
#define PCI_DEVICE_ID_TOURMALET          0xA
#define PCI_DEVICE_ID_KLA                0xB

/// The revision of Extoll cards supported by this driver
#define PCI_EXTOLL_REVISION				 0x42

//default MMIO sizes for R2 are 32M each, only SMFU is 256MB
#define EXTOLL_R2_RF_MMIO_SIZE           33554432l
#define EXTOLL_R2_VELO2_MMIO_SIZE        33554432ll
//16777216l
#define EXTOLL_R2_RMA2_MMIO_SIZE         33554432l
#define EXTOLL_R2_SMFU2_MMIO_SIZE        268435456l
//184549376l
//201326592l
//218103808l

//3 units use bar 0
#define EXTOLL_R2_RF_MMIO_OFFSET         0l
#define EXTOLL_R2_VELO2_MMIO_OFFSET      (0+EXTOLL_R2_RF_MMIO_SIZE)
#define EXTOLL_R2_RMA2_MMIO_OFFSET       (EXTOLL_R2_VELO2_MMIO_OFFSET+EXTOLL_R2_VELO2_MMIO_SIZE)
//smfu uses bar2
#define EXTOLL_R2_SMFU2_MMIO_OFFSET      0
//(EXTOLL_R2_RMA2_MMIO_OFFSET+EXTOLL_R2_RMA2_MMIO_SIZE)

#define EXTOLL_R2_RF_MMIO_END         (EXTOLL_R2_RF_MMIO_OFFSET+EXTOLL_R2_RF_MMIO_SIZE)
#define EXTOLL_R2_VELO2_MMIO_END      (EXTOLL_R2_VELO2_MMIO_OFFSET+EXTOLL_R2_VELO2_MMIO_SIZE)
#define EXTOLL_R2_RMA2_MMIO_END       (EXTOLL_R2_RMA2_MMIO_OFFSET+EXTOLL_R2_RMA2_MMIO_SIZE)
#define EXTOLL_R2_SMFU2_MMIO_END      (EXTOLL_R2_SMFU2_MMIO_OFFSET+EXTOLL_R2_SMFU2_MMIO_SIZE)






/** \defgroup interrupt handling */
/** @{ */

/*!
  \brief Type for the extoll interrupt handler functions
*/
typedef void (*extoll_i_handler)(int);

/*!
  \brief Registers a handler function for the extoll interrupt cause with the given idx

  \param idx The interrupt cause index (i.e. the bit in the cause register) that should cause execution of handler
  \param handler the handler function for the given interrupt cause
  */
void extoll_register_interrupt_handler(int idx, extoll_i_handler handler);

/*!
  \brief Deregisters a handler function for the extoll interrupt cause with the given idx

  \param idx The interrupt cause index (i.e. the bit in the cause register) that should not cause execution of a handler
  */
void extoll_deregister_interrupt_handler(int idx);

/*!
  \brief Clear the interrupt register

  Clears the interrupt register bit for the interrupt cause with the given index.
  Can be called by a handler to immediately clear the interrupt bit.

  \param idx the interrupt cause that should be cleared (i.e. the bit in the cause register)
*/
void extoll_clear_interrupt(int idx);

/** }@ */


/*Functions etc. internal to extolldrv.ko*/
#ifdef EXTOLLDRV

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


/** \defgroup Extoll access methods */
/** @{ */

/**
 * Checks the device index exists, and that the unit index in the device also exists
 *
 * @param extoll_device_num
 * @param extoll_unit_num
 * @return >=0 if success, -1 if an error occured
 */
extern int extoll_is_device_unit(unsigned int extoll_device_num,unsigned int extoll_unit_num);

/**
 *
 * @return 1 if all extoll devices have been inited, something else otherwise (like -1)
 */
extern int extoll_get_init_done(void);

/**
 *
 * @return The pointer to pci_dev structure for the provided extoll device number
 */
extern struct pci_dev* extoll_get_pdev(unsigned int extoll_device_num);

/**
 * Returns a pointer to the Register file virtual address
 * @param extoll_device_num The number of the extoll_device concerned
 */
extern void* extoll_get_rf_vaddr(unsigned int extoll_device_num,unsigned int extoll_unit_num);

/**
 * Returns a pointer to the VELO virtual address
 * @param extoll_device_num The number of the extoll_device concerned
 */
extern void* extoll_get_velo2_vaddr(unsigned int extoll_device_num,unsigned int extoll_unit_num);

/**
 * Returns a pointer to the RMA virtual address
 * @param extoll_device_num The number of the extoll_device concerned
 */
extern void* extoll_get_rma2_vaddr(unsigned int extoll_device_num,unsigned int extoll_unit_num);

/**
 * Returns a pointer to the SMFU virtual address
 * @param extoll_device_num The number of the extoll_device concerned
 */
extern void* extoll_get_smfu_vaddr(unsigned int extoll_device_num,unsigned int extoll_unit_num);

/**
 * Returns The physical address of RegisterFile
 * @param extoll_device_num The number of the extoll_device concerned
 */
extern unsigned long extoll_get_rf_addr(unsigned int extoll_device_num,unsigned int extoll_unit_num);

/**
 * Returns The physical address of VELO
 * @param extoll_device_num The number of the extoll_device concerned
 */
extern unsigned long extoll_get_velo2_addr(unsigned int extoll_device_num,unsigned int extoll_unit_num);

/**
 * Returns The physical address of the RMA
 * @param extoll_device_num The number of the extoll_device concerned
 */
extern unsigned long extoll_get_rma2_addr(unsigned int extoll_device_num,unsigned int extoll_unit_num);

/**
 * Returns The physical address of the SMFU
 * @param extoll_device_num The number of the extoll_device concerned
 */
extern unsigned long extoll_get_smfu_addr(unsigned int extoll_device_num,unsigned int extoll_unit_num);

/**
 * Returns the size of Register File address space
 * @param extoll_device_num The number of the extoll_device concerned
 */
extern unsigned int extoll_get_rf_size(unsigned int extoll_device_num,unsigned int extoll_unit_num);

/**
 * Returns the size of VELO address space
 * @param extoll_device_num The number of the extoll_device concerned
 */
extern unsigned int extoll_get_velo2_size(unsigned int extoll_device_num,unsigned int extoll_unit_num);

/**
 * Returns the size of the RMA address space
 * @param extoll_device_num The number of the extoll_device concerned
 */
extern unsigned int extoll_get_rma2_size(unsigned int extoll_device_num,unsigned int extoll_unit_num);

/**
 * Returns the size of the SMFU address space
 * @param extoll_device_num The number of the extoll_device concerned
 */
extern unsigned int extoll_get_smfu_size(unsigned int extoll_device_num,unsigned int extoll_unit_num);

extern unsigned int extoll_get_interrupt_counter(void);

extern void extoll_set_interrupt_counter(unsigned int v);

/** }@ */

#endif
