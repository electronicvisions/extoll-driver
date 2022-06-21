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
 *
 *
 *
 *
 */

// Includes
//---------------------------
//-- Std
#include <linux/memory.h>

//-- linux things
#include <asm-generic/uaccess.h>
#include <linux/semaphore.h>
#include <linux/mutex.h>
#include <linux/unistd.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <linux/list.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/slab.h>

//-- PCI
#include <linux/pci.h>

//-- IRQ things
//#include <linux/interrupt.h>
//#include <linux/htirq.h>

//-- Sysfs
#include "extoll_rf_sysfs.h"

#define EXTOLLDRV
#include "extolldrv.h"

// EXTOLL R2 Ventoux only supported on halfway recent kernels
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,27)
#error "This driver needs at least kernel version 2.6.31. If you think this is wrong, contact the author."
#endif

/******************************************************************************
 *  Boards supported by this driver      				                      *
 *  At the moment this is VENTOUX, Galibier and others may follow.              *
 ******************************************************************************/
static struct pci_device_id ids[] = {
    {   PCI_DEVICE(PCI_VENDOR_ID_EXTOLL, PCI_DEVICE_ID_VENTOUX1),},
    {   PCI_DEVICE(PCI_VENDOR_ID_EXTOLL, PCI_DEVICE_ID_VENTOUX2),},
    {   PCI_DEVICE(PCI_VENDOR_ID_EXTOLL, PCI_DEVICE_ID_GALIBIER1),},
    {   PCI_DEVICE(PCI_VENDOR_ID_EXTOLL, PCI_DEVICE_ID_TOURMALET),},
    {   PCI_DEVICE(PCI_VENDOR_ID_EXTOLL, PCI_DEVICE_ID_KLA),},
    {   0,}
};

MODULE_DEVICE_TABLE(pci, ids);

/******************************************************************************
 *  Registerfile access			   				      *
 ******************************************************************************/

/// Array of extoll devices to support multiple units in 1+ devices
/// @warning extoll_device_t represents a  device.
static extoll_device_t** extoll_devices = 0;

/// Size of the extoll devices array
static unsigned int extoll_devices_count = 0;

static unsigned int interrupt_counter = 0;

//DEFINE_MUTEX(extoll_mutex);	//mutex is initialized unlocked.

/******************************************************************************
 *  externally callable            functions                                  *
 ******************************************************************************/


extoll_device_t ** extoll_get_devices() {
    return extoll_devices;
}
EXPORT_SYMBOL(extoll_get_devices);

unsigned int extoll_get_devices_count() {
    return extoll_devices_count;
}
EXPORT_SYMBOL(extoll_get_devices_count);

int extoll_get_init_done(void) {
    //-- All Devices must be inited
    int i = 0;
    for (i = 0; i < extoll_devices_count; i++) {
        if (extoll_devices[i]->init_done != 1)
            return -1;
    }

    // All Init OK (otherwise return before)
    return 1;

}
EXPORT_SYMBOL(extoll_get_init_done);

int extoll_is_device_unit(unsigned int extoll_device_num,
        unsigned int extoll_unit_num) {

    //-- Check device
    if (extoll_device_num > extoll_devices_count)
        return -1;

    //-- Check unit in device
    if (extoll_unit_num > extoll_devices[extoll_device_num]->units_count)
        return -1;

    //-- OK!
    return 1;
}

struct pci_dev* extoll_get_pdev(unsigned int extoll_device_num) {

    if (!extoll_is_device_unit(extoll_device_num, 0))
        return NULL;
    return extoll_devices[extoll_device_num]->devp;
}
EXPORT_SYMBOL(extoll_get_pdev);

extoll_device_t * extoll_get_device(unsigned int extoll_device_num) {

    if (!extoll_is_device_unit(extoll_device_num, 0))
        return NULL;

    return extoll_devices[extoll_device_num];
}
EXPORT_SYMBOL(extoll_get_device);

void* extoll_get_rf_vaddr(unsigned int extoll_device_num,
        unsigned int extoll_unit_num) {
    extoll_unit_t * unit;
    if (!extoll_is_device_unit(extoll_device_num, extoll_unit_num))
        return NULL;

    unit = &(extoll_devices[extoll_device_num]->units[extoll_unit_num]);
    return unit->fu_regions[unit->rf_region_index]->vaddress;
}
EXPORT_SYMBOL(extoll_get_rf_vaddr);

unsigned long extoll_get_rf_addr(unsigned int extoll_device_num,
        unsigned int extoll_unit_num) {
    extoll_unit_t * unit;
    if (!extoll_is_device_unit(extoll_device_num, extoll_unit_num))
        return 0;

    unit = &(extoll_devices[extoll_device_num]->units[extoll_unit_num]);
    return unit->fu_regions[unit->rf_region_index]->paddress;
}
EXPORT_SYMBOL(extoll_get_rf_addr);

unsigned int extoll_get_rf_size(unsigned int extoll_device_num,
        unsigned int extoll_unit_num) {
    extoll_unit_t * unit;
    if (!extoll_is_device_unit(extoll_device_num, extoll_unit_num))
        return 0;

    unit = &(extoll_devices[extoll_device_num]->units[extoll_unit_num]);
    return unit->fu_regions[unit->rf_region_index]->size;
}
EXPORT_SYMBOL(extoll_get_rf_size);

void* extoll_get_velo2_vaddr(unsigned int extoll_device_num,
        unsigned int extoll_unit_num) {
    extoll_unit_t * unit;
    if (!extoll_is_device_unit(extoll_device_num, extoll_unit_num))
        return NULL;

    unit = &(extoll_devices[extoll_device_num]->units[extoll_unit_num]);
    return unit->fu_regions[unit->velo2_region_index]->vaddress;
}
EXPORT_SYMBOL(extoll_get_velo2_vaddr);

unsigned long extoll_get_velo2_addr(unsigned int extoll_device_num,
        unsigned int extoll_unit_num) {
    extoll_unit_t * unit;
    if (!extoll_is_device_unit(extoll_device_num, extoll_unit_num))
        return 0;

    unit = &(extoll_devices[extoll_device_num]->units[extoll_unit_num]);
    return unit->fu_regions[unit->velo2_region_index]->paddress;
}
EXPORT_SYMBOL(extoll_get_velo2_addr);

unsigned int extoll_get_velo2_size(unsigned int extoll_device_num,
        unsigned int extoll_unit_num) {

    extoll_unit_t * unit;
    if (!extoll_is_device_unit(extoll_device_num, extoll_unit_num))
        return 0;

    unit = &(extoll_devices[extoll_device_num]->units[extoll_unit_num]);
    return unit->fu_regions[unit->velo2_region_index]->size;
}
EXPORT_SYMBOL(extoll_get_velo2_size);

void* extoll_get_rma2_vaddr(unsigned int extoll_device_num,
        unsigned int extoll_unit_num) {
    extoll_unit_t * unit;
    if (!extoll_is_device_unit(extoll_device_num, extoll_unit_num))
        return NULL;

    unit = &(extoll_devices[extoll_device_num]->units[extoll_unit_num]);
    return unit->fu_regions[unit->rma2_region_index]->vaddress;
}
EXPORT_SYMBOL(extoll_get_rma2_vaddr);

unsigned long extoll_get_rma2_addr(unsigned int extoll_device_num,
        unsigned int extoll_unit_num) {
    extoll_unit_t * unit;
    if (!extoll_is_device_unit(extoll_device_num, extoll_unit_num))
        return 0;

    unit = &(extoll_devices[extoll_device_num]->units[extoll_unit_num]);
    return unit->fu_regions[unit->rma2_region_index]->paddress;
}
EXPORT_SYMBOL(extoll_get_rma2_addr);

unsigned int extoll_get_rma2_size(unsigned int extoll_device_num,
        unsigned int extoll_unit_num) {
    extoll_unit_t * unit;
    if (!extoll_is_device_unit(extoll_device_num, extoll_unit_num))
        return 0;

    unit = &(extoll_devices[extoll_device_num]->units[extoll_unit_num]);
    return unit->fu_regions[unit->rma2_region_index]->size;
}
EXPORT_SYMBOL(extoll_get_rma2_size);

void* extoll_get_smfu_vaddr(unsigned int extoll_device_num,
        unsigned int extoll_unit_num) {
    extoll_unit_t * unit;
    if (!extoll_is_device_unit(extoll_device_num, extoll_unit_num))
        return NULL;

    unit = &(extoll_devices[extoll_device_num]->units[extoll_unit_num]);
    return unit->fu_regions[unit->smfu2_region_index]->vaddress;
}
EXPORT_SYMBOL(extoll_get_smfu_vaddr);

unsigned long extoll_get_smfu_addr(unsigned int extoll_device_num,
        unsigned int extoll_unit_num) {
    extoll_unit_t * unit;
    if (!extoll_is_device_unit(extoll_device_num, extoll_unit_num))
        return 0;

    unit = &(extoll_devices[extoll_device_num]->units[extoll_unit_num]);
    return unit->fu_regions[unit->smfu2_region_index]->paddress;
}
EXPORT_SYMBOL(extoll_get_smfu_addr);

unsigned int extoll_get_smfu_size(unsigned int extoll_device_num,
        unsigned int extoll_unit_num) {
    extoll_unit_t * unit;
    if (!extoll_is_device_unit(extoll_device_num, extoll_unit_num))
        return 0;

    unit = &(extoll_devices[extoll_device_num]->units[extoll_unit_num]);
    return unit->fu_regions[unit->smfu2_region_index]->size;
}
EXPORT_SYMBOL(extoll_get_smfu_size);

unsigned int extoll_get_interrupt_counter(void) {
    return interrupt_counter;
}
EXPORT_SYMBOL(extoll_get_interrupt_counter);

void extoll_set_interrupt_counter(unsigned int v) {
    interrupt_counter = v;
}
EXPORT_SYMBOL(extoll_set_interrupt_counter);

/******************************************************************************
 *  helper functions                                  *
 ******************************************************************************/

static unsigned char extoll_get_revision(struct pci_dev *dev) {
    u8 revision;

    pci_read_config_byte(dev, PCI_REVISION_ID, &revision);
    return revision;
}

/** \defgroup Setup functions: Address mapping, I/O Remap and Interval routing */
/** @{ */

#define HTAX_INVTL_POSTED_VC    (1l<<14l)
#define HTAX_INVTL_NONPOSTED_VC (2l<<14l)
#define HTAX_INVTL_RESPONSE_VC  (4l<<14l)

#define HTAX_INVTL_RF_PORT_OH     (8l<<5l)
#define HTAX_INVTL_VELO_PORT_OH   (16l<<5l)
#define HTAX_INVTL_RMAREQ_PORT_OH (32l<<5l)
#define HTAX_INVTL_SMFU_PORT_OH   (256l<<5l)

#define HTAX_INVTL_RF_PORT     (4l<<1l)
#define HTAX_INVTL_VELO_PORT   (5l<<1l)
#define HTAX_INVTL_RMAREQ_PORT (6l<<1l)
#define HTAX_INVTL_SMFU_PORT   (9l<<1l)

#define HTAX_INVTL_ENABLE 1l
#define HTAX_USE_SF_MODE (1l<<13l)
#define HTAX_USE_VC_MODE (0l<<13l)
#define HTAX_GENERAL_ENABLE (1l<<14l)

/**
 * Setup the HTAX interval mapping for a given region
 *
 */
static void extoll_set_up_address_interval(mapped_region_t * region,unsigned int targetHtaxPort,uint64_t control) {

    //-- Set Lower/Upper address bounds, and control register
    set_extoll_rf_htax_bridge_rf_intvl_lower(targetHtaxPort,(region->paddress>>12l) -1l);
    set_extoll_rf_htax_bridge_rf_intvl_upper( targetHtaxPort, (region->paddress+region->size) >> 12l);
    set_extoll_rf_htax_bridge_rf_intvl_control(targetHtaxPort,control);

}

/**
 * This function maps a region for an FU into a specific BAR:
 * - Set the physical address to the one of the BAR
 * - Remap to get a vaddress, using cacheable/not cacheable etc...
 * - Dynamically add the new region
 *
 * @param extoll_device_t* device         : The device in which the unit is located
 * @param extoll_unit_t *  targetUnit     : The unit in which to add the mapped region
 * @param unsigned long    size           : The size of region to map
 * @param unsigned int     targetBar      : The BAR to take as base for physical addresses
 * @param unsigned int     writeCombining : 1 if the mapped memory is write Combining, 0 if not (will be nocache then)
 * @return -1 if an error occured, the index of the mapped region otherwise
 */
static int extoll_map_fu(extoll_device_t*device,extoll_unit_t * targetUnit,unsigned long size,unsigned int targetBar,unsigned int writeCombining) {

    // Prepare BAR Location
    //-----------------
    mapped_region_t * region = 0; // new region to be created
    unsigned long bar_physical_address = 0; // Chosen BAR Address
    unsigned long bar_size = 0;
    unsigned long physical_address_in_bar = 0; // Address into BAR where to map
    int bar_choice_done = 0; // 0: not done, 1: done, -1: error
    int ri = 0;
    mapped_region_t ** oldRegions = 0;

    while (bar_choice_done == 0) {

        //-- Reinit variables
        mapped_region_t * previousRegion = NULL;
        bar_physical_address = 0;
        bar_size = 0;
        physical_address_in_bar = 0;
        bar_choice_done = 1; // Done per default to avoid infinite looping bugs

        //-- Select Bar address
        if (targetBar == 0) {
            bar_physical_address = device->bar0_addr;
            bar_size = device->bar0_size;
        } else if (targetBar == 2) {
            bar_physical_address = device->bar2_addr;
            bar_size = device->bar2_size;
        } else if (targetBar == 4) {
            bar_physical_address = device->bar4_addr;
            bar_size = device->bar4_size;
        } else {
            printk(
                    KERN_ERR "Mapping region into target BAR %d not possible (only BARS 0/2/4 allowed)\n",
                    targetBar);
            bar_choice_done = -1;
        }

        //-- Get Previous region in mapping (NULL if no previous)
        previousRegion =
                targetUnit->fu_regions_count == 0 ?
                        NULL :
                        targetUnit->fu_regions[targetUnit->fu_regions_count - 1];

        //-- Start at begining of BAR if no previous, or previous is in a different BAR
        if (previousRegion == NULL || previousRegion->bar != targetBar) {
            physical_address_in_bar = bar_physical_address;
        }
        //-- Otherwise, start at last physical_address + size
        else {
            physical_address_in_bar = previousRegion->paddress
                    + previousRegion->size;
        }

        // FIXME: Check physical chosen address + targetSize does not exceeed BAR size.
        // If so, try to swtich to next BAR
        //---------------
        if (physical_address_in_bar + size > bar_physical_address + bar_size) {

            printk(
                    KERN_WARNING "Mapping in BAR %d a FU of size 0x%lx at 0x%lx, exceeding BAR size -> Trying to jump to next BAR\n",
                    targetBar, size, physical_address_in_bar);

            //-- Jump BAR and redo
            targetBar += 2;
            bar_choice_done = 0;

        }

    }

    //-- If an error occured -> fail
    if (bar_choice_done == -1) {

        printk(KERN_ERR "BAR Choice while mapping FU failed");

        //-- Release all previously mapped regions
        for (int i = 0; i < targetUnit->fu_regions_count; i++) {
            release_mem_region((targetUnit->fu_regions[i])->paddress,
                    (targetUnit->fu_regions[i])->size);
            kfree(targetUnit->fu_regions[i]);
        }

        return -1;

    }

    printk(KERN_INFO"Mapping FU Region into bar %d at %lx -> %lx\n",targetBar,physical_address_in_bar,size);

    // Create Region
    //-------------------------
    region = (mapped_region_t*) kmalloc(sizeof(mapped_region_t), GFP_KERNEL | __GFP_REPEAT);
    if (!region) {
        printk(KERN_ERR "kmalloc allocating region structure failed");
        return -1;
    }

    //-- Set BAR,physical address, size
    region->bar = targetBar;
    region->paddress = physical_address_in_bar;
    region->size = size;

    // Remap
    //------------------
    printk(KERN_INFO"\tRemapping as wc : %d\n",writeCombining);

    if (writeCombining == 1)
        region->vaddress = ioremap_wc(region->paddress, region->size);
    else
        region->vaddress = ioremap_nocache(region->paddress, region->size);


    // Add region to unit regions array
    //---------------


    //-- Allocate new array and copy old
    oldRegions = targetUnit->fu_regions;
    targetUnit->fu_regions = (mapped_region_t **) kmalloc(targetUnit->fu_regions_count+1*sizeof(mapped_region_t*), GFP_KERNEL | __GFP_REPEAT);
    for (ri = 0 ; ri < targetUnit->fu_regions_count ; ri++) {
        targetUnit->fu_regions[ri] = oldRegions[ri];
    }

    //-- Add new region
    targetUnit->fu_regions[targetUnit->fu_regions_count++] = region;
    return targetUnit->fu_regions_count - 1;

}

/** }@ */

/** \defgroup Driver definition: Probe/Exit and describing structure */
/** @{ */

/**
 * Initialize extoll device in order to work seamless in kernel pci subsystem.
 * 1. enable the device
 * 2. do some checks (revision etc.)
 * 3. set bit mask(32/64) for dma access
 * 4. retrieve and save base address register values from device
 *
 * FIXME Support one device for the moment
 *
 */
static int __devinit extoll_probe(struct pci_dev *devp,
        const struct pci_device_id *id) {

    //-- Init variables
    int err;
    int di;
    extoll_device_t * newExtollDevice;
    extoll_device_t ** newExtolldevices; // New array to add newly created extoll device

    // Hello!
    printk(KERN_INFO "EXTOLL2: PCI: probe() called!\n");

    //-- Like calling request_region(); -> Enable device
    err = pci_enable_device(devp);
    if (err) {
        printk(KERN_ERR"Error while enabling extoll2 device\n");
        return err;
    }

    // Device seems to be OK :) so lets save it for future use
    //-----------------------------------

    //-- Prepare structure
    newExtollDevice = (extoll_device_t *) kmalloc(sizeof(extoll_device_t),
            GFP_KERNEL);
    if (!newExtollDevice) {
        printk(KERN_ERR"Error while kallocing\n");
        return -1;
    }

    // Save device pointer
    newExtollDevice->devp        = devp;
    newExtollDevice->units_count = 0;
    newExtollDevice->init_done   = 0;

    // Verify supported Revision
    //-----------------------------------

    //FIXME:What revisions should be supported here ?
    //at the moment EXTOLL2 returns 0x42 which is OK ?
    if (extoll_get_revision(newExtollDevice->devp) == PCI_EXTOLL_REVISION) {
        printk(KERN_ALERT "EXTOLL2: device enable failed\n");
        printk(KERN_ALERT "EXTOLL2: wrong revision %x\n",
                extoll_get_revision(newExtollDevice->devp));
        kfree(newExtollDevice);
        return -ENODEV;
    }
    printk(KERN_INFO "EXTOLL2: detected revision %x\n",
            extoll_get_revision(newExtollDevice->devp));

    // 32/64bits
    //-----------------------

    if (!pci_set_consistent_dma_mask(newExtollDevice->devp, DMA_BIT_MASK(64))) {
        printk(KERN_INFO "EXTOLL2: using 64bit DMA addressing\n");
    } else if (!pci_set_consistent_dma_mask(newExtollDevice->devp,
            DMA_BIT_MASK(32))) {
        printk(KERN_INFO "EXTOLL2: using 32bit DMA addressing\n");
    } else {
        printk(KERN_INFO "EXTOLL2: No suitable DMA available.\n");
        pci_disable_device(newExtollDevice->devp);
        printk(KERN_ALERT "EXTOLL2: init failed!\n\n");
        kfree(newExtollDevice);
        return -EBUSY;
    }

    // Configure BARS
    //------------------------

    //-- BAR0/1 : address and size
    newExtollDevice->bar0_addr = pci_resource_start(newExtollDevice->devp, 0);
    newExtollDevice->bar0_size = pci_resource_len(newExtollDevice->devp, 0);
    printk(KERN_INFO "EXTOLL2: BAR0/1 region: %lx / %lx\n",
            newExtollDevice->bar0_addr, newExtollDevice->bar0_size);
    if (!request_mem_region(newExtollDevice->bar0_addr, newExtollDevice->bar0_size, "hal_regfile")) {

        // Error
        printk(KERN_ALERT "EXTOLL2: BAR0/1 already in use\n");
        pci_disable_device(newExtollDevice->devp);
        printk(KERN_ALERT "EXTOLL2: init failed!\n\n");
        kfree(newExtollDevice);
        return -EBUSY;

    }
    printk(KERN_INFO "EXTOLL2: BAR0/1 allocated at addr %lx size %lx (hex)\n",
            newExtollDevice->bar0_addr, newExtollDevice->bar0_size);

    //-- BAR2/3 : address and size
    newExtollDevice->bar2_addr = pci_resource_start(newExtollDevice->devp, 2);
    newExtollDevice->bar2_size = pci_resource_len(newExtollDevice->devp, 2);
    printk(KERN_INFO "EXTOLL2: BAR2/3 region: %lx / %lx\n",
            newExtollDevice->bar2_addr, newExtollDevice->bar2_size);
    if (!request_mem_region(newExtollDevice->bar2_addr, newExtollDevice->bar2_size, "hal_regfile")) {

        // Error
        printk(KERN_ALERT "EXTOLL2: BAR2/3 already in use\n");
        printk(KERN_ALERT "EXTOLL2: init failed!\n\n");

        // Release previous BAR Region(s)
        release_mem_region(newExtollDevice->bar0_addr,
                newExtollDevice->bar0_addr);
        pci_disable_device(newExtollDevice->devp);

        kfree(newExtollDevice);
        return -EBUSY;
    }
    printk(KERN_INFO "EXTOLL2: BAR2/3 allocated at addr %lx size %lx (hex)\n",
            newExtollDevice->bar2_addr, newExtollDevice->bar2_size);

    //-- BAR4/5 : address and size
    newExtollDevice->bar4_addr = pci_resource_start(newExtollDevice->devp, 4);
    newExtollDevice->bar4_size = pci_resource_len(newExtollDevice->devp, 4);
    printk(KERN_INFO "EXTOLL2: BA4/5 region: %lx / %lx\n",
            newExtollDevice->bar4_addr, newExtollDevice->bar4_size);
    if (!request_mem_region(newExtollDevice->bar4_addr, newExtollDevice->bar4_size, "hal_regfile")) {

        // Error
        printk(KERN_ALERT "EXTOLL2: BAR4/5 already in use\n");
        printk(KERN_ALERT "EXTOLL2: init failed!\n\n");

        // Release previous BAR Region(s)
        release_mem_region(newExtollDevice->bar0_addr,
                newExtollDevice->bar0_addr);
        release_mem_region(newExtollDevice->bar2_addr,
                newExtollDevice->bar2_addr);
        pci_disable_device(newExtollDevice->devp);

        kfree(newExtollDevice);
        return -EBUSY;
    }
    printk(KERN_INFO "EXTOLL2: BAR4/5 allocated at addr %lx size %lx (hex)\n",
            newExtollDevice->bar4_addr, newExtollDevice->bar4_size);

    // Units Setup depending on Device ID
    //----------------------

    //---- First save new Extoll devices array
    //------------------------

    //-- Allocate new array of pointer to devices
    newExtolldevices = (extoll_device_t **) kmalloc(
            sizeof(extoll_device_t *) * extoll_devices_count + 1, GFP_KERNEL);

    //-- Copy pointers to actual devices into new array
    for (di = 0; di < extoll_devices_count; di++)
        newExtolldevices[di] = extoll_devices[di];

    //-- Add new at the end
    newExtolldevices[extoll_devices_count++] = newExtollDevice;

    //-- Replace old array
    kfree(extoll_devices);
    extoll_devices = newExtolldevices;

    //---- Number of units depends on device ID
    //-----------------------------
    switch (newExtollDevice->devp->device) {

        default:
        case PCI_DEVICE_ID_VENTOUX1:
        case PCI_DEVICE_ID_VENTOUX2:
        case PCI_DEVICE_ID_GALIBIER1:
        case PCI_DEVICE_ID_TOURMALET:

            //-- Create Units
            //--------------------------
            newExtollDevice->units_count = 1;
            newExtollDevice->units = (extoll_unit_t*) kmalloc(
                    newExtollDevice->units_count * sizeof(extoll_unit_t),
                    GFP_KERNEL);
            newExtollDevice->units[0].fu_regions_count = 0;

            //-- MAP FUs memory regions
            //----------------------
            (newExtollDevice->units[0]).rf_region_index = extoll_map_fu(
                    newExtollDevice, &((newExtollDevice->units)[0]),
                    EXTOLL_R2_RF_MMIO_SIZE, 0, 0);
            (newExtollDevice->units[0]).velo2_region_index = extoll_map_fu(
                    newExtollDevice, &(newExtollDevice->units[0]),
                    EXTOLL_R2_VELO2_MMIO_SIZE, 0, 1);
            (newExtollDevice->units[0]).rma2_region_index = extoll_map_fu(
                    newExtollDevice, &(newExtollDevice->units[0]),
                    EXTOLL_R2_RMA2_MMIO_SIZE, 0, 1);
            (newExtollDevice->units[0]).smfu2_region_index = extoll_map_fu(
                    newExtollDevice, &(newExtollDevice->units[0]),
                    EXTOLL_R2_SMFU2_MMIO_SIZE, 0, 0);

            //-- Setup RF
            //-----------------------
            printk(KERN_INFO "Setting up extoll registerfile and sysfs\n");
            extoll_rf_create_sysfs_extoll_rf_files(extoll_devices,extoll_devices_count);

            //-- Start interval routing
            //---------------------------------

            // Set up RF routing
            extoll_set_up_address_interval(
                (newExtollDevice->units[0]).fu_regions[(newExtollDevice->units[0]).rf_region_index],
                0,
                HTAX_INVTL_POSTED_VC | HTAX_INVTL_NONPOSTED_VC| HTAX_INVTL_RF_PORT_OH | HTAX_INVTL_RF_PORT | HTAX_INVTL_ENABLE);


            // Set up VELO routing
            extoll_set_up_address_interval(
               (newExtollDevice->units[0]).fu_regions[(newExtollDevice->units[0]).velo2_region_index],
               1,
               HTAX_INVTL_POSTED_VC | HTAX_INVTL_VELO_PORT_OH | HTAX_INVTL_VELO_PORT | HTAX_INVTL_ENABLE);

            // Set up RMA routing
            extoll_set_up_address_interval(
               (newExtollDevice->units[0]).fu_regions[(newExtollDevice->units[0]).rma2_region_index],
               2,
               HTAX_INVTL_POSTED_VC | HTAX_INVTL_RMAREQ_PORT_OH | HTAX_INVTL_RMAREQ_PORT | HTAX_INVTL_ENABLE);

            // Set up SMFU routing
            extoll_set_up_address_interval(
               (newExtollDevice->units[0]).fu_regions[(newExtollDevice->units[0]).smfu2_region_index],
               3,
               HTAX_INVTL_POSTED_VC | HTAX_INVTL_NONPOSTED_VC| HTAX_INVTL_SMFU_PORT_OH| HTAX_INVTL_SMFU_PORT | HTAX_INVTL_ENABLE);


            // Enable the routing table just set-up
            set_extoll_rf_htax_bridge_rf_general(  HTAX_GENERAL_ENABLE | HTAX_USE_VC_MODE | ((8l<<4l)) | (8)  );

            printk(
                    KERN_INFO "EXTOLL2: Address based intra-chip routing done.\n");

            break;

        case PCI_DEVICE_ID_KLA:

            //-- Create Units
            //------------------------
            newExtollDevice->units_count = 2;
            newExtollDevice->units = (extoll_unit_t*) kmalloc(
                    newExtollDevice->units_count * sizeof(extoll_unit_t),
                    GFP_KERNEL);

            //-- Map all two units
            for (int i = 0; i < newExtollDevice->units_count; i++) {

                newExtollDevice->units[i].fu_regions_count = 0;

                //-- Map FUs
                //----------------
                (newExtollDevice->units[i]).rf_region_index = extoll_map_fu(
                        newExtollDevice, &(newExtollDevice->units[i]),
                        EXTOLL_R2_RF_MMIO_SIZE, i * (2), 0);
                (newExtollDevice->units[i]).rma2_region_index = extoll_map_fu(
                        newExtollDevice, &(newExtollDevice->units[i]),
                        EXTOLL_R2_RMA2_MMIO_SIZE, i * (2), 1);

                (newExtollDevice->units[i]).velo2_region_index = -1;
                (newExtollDevice->units[i]).smfu2_region_index = -1;


                //-- Start interval routing
                //---------------------------------

                // Set up RF routing
                extoll_set_up_address_interval(
                    (newExtollDevice->units[0]).fu_regions[(newExtollDevice->units[0]).rf_region_index],
                    0,
                    HTAX_INVTL_POSTED_VC | HTAX_INVTL_NONPOSTED_VC| HTAX_INVTL_RF_PORT_OH | HTAX_INVTL_RF_PORT | HTAX_INVTL_ENABLE);

                // Set up VELO routing
                extoll_set_up_address_interval(
                   (newExtollDevice->units[0]).fu_regions[(newExtollDevice->units[0]).velo2_region_index],
                   1,
                   HTAX_INVTL_POSTED_VC | HTAX_INVTL_VELO_PORT_OH | HTAX_INVTL_VELO_PORT | HTAX_INVTL_ENABLE);

                // Set up RMA routing
                extoll_set_up_address_interval(
                   (newExtollDevice->units[0]).fu_regions[(newExtollDevice->units[0]).rma2_region_index],
                   2,
                   HTAX_INVTL_POSTED_VC | HTAX_INVTL_RMAREQ_PORT_OH | HTAX_INVTL_RMAREQ_PORT | HTAX_INVTL_ENABLE);

                // Set up SMFU routing
                extoll_set_up_address_interval(
                   (newExtollDevice->units[0]).fu_regions[(newExtollDevice->units[0]).smfu2_region_index],
                   3,
                   HTAX_INVTL_POSTED_VC | HTAX_INVTL_NONPOSTED_VC| HTAX_INVTL_SMFU_PORT_OH| HTAX_INVTL_SMFU_PORT | HTAX_INVTL_ENABLE);

            }

            //-- Setup RF
            //------------------
            printk(KERN_INFO "Setting up extoll registerfile and sysfs\n");
            extoll_rf_create_sysfs_extoll_rf_files(extoll_devices,extoll_devices_count);

            //--  Start interval routing
            //--------------------------------

            //-- Do It for every Unit
            for (int i = 0; i < newExtollDevice->units_count; i++) {

                // Set up RF routing
                extoll_set_up_address_interval(
                   (newExtollDevice->units[0]).fu_regions[(newExtollDevice->units[0]).rf_region_index],
                   (i*2)+0,
                   HTAX_INVTL_POSTED_VC | HTAX_INVTL_NONPOSTED_VC| HTAX_INVTL_RF_PORT_OH | HTAX_INVTL_RF_PORT | HTAX_INVTL_ENABLE);

                // Set up RMA routing
                extoll_set_up_address_interval(
                   (newExtollDevice->units[0]).fu_regions[(newExtollDevice->units[0]).rma2_region_index],
                   (i*2)+1,
                   HTAX_INVTL_POSTED_VC | HTAX_INVTL_RMAREQ_PORT_OH | HTAX_INVTL_RMAREQ_PORT | HTAX_INVTL_ENABLE);


            }

            //--  Enable the routing table just set-up
            set_extoll_rf_htax_bridge_rf_general(  HTAX_GENERAL_ENABLE | HTAX_USE_VC_MODE | ((8l<<4l)) | (8)  );

            printk(
                    KERN_INFO "EXTOLL2: Address based intra-chip routing done.\n");


            break;

    }

    // Success, save extoll_device array
    //-----------------
    printk(KERN_INFO "Initialised Extoll2 Device\n");




    return 0;
}

static void __devexit extoll_remove(struct pci_dev *devp) {

    //-- Init variables
    int ui; // Loop over units
    int ri; // Loop over region in units
    extoll_device_t * extoll_device = NULL;

    // Find extoll_device matching pci_dev
    //----------------------

    printk(KERN_INFO "EXTOLL2: Removing device: %d %d %d\n",devp->bus->number,devp->vendor,devp->device);

    extoll_device = extoll_devices[0];

    for (int i = 0; i < extoll_devices_count; i++) {

        if (extoll_devices[i] != NULL)
            printk(KERN_INFO "\t Registered: %d %d %d\n",
                    extoll_devices[i]->devp->bus->number,
                    extoll_devices[i]->devp->vendor,
                    extoll_devices[i]->devp->device);
        else {
            printk(KERN_INFO "\t Index in registered devices is NULL\n");
        }

        if (extoll_devices[i] != NULL
               && extoll_devices[i]->devp->bus->number == devp->bus->number
               && extoll_devices[i]->devp->vendor == devp->vendor
               && extoll_devices[i]->devp->device == devp->device) {

            extoll_device = extoll_devices[i];

            //-- Null to avoid a next remove call on freed memory
            extoll_devices[i] = NULL;
            break;
        }

    }

    //-- If not found fail
    if (extoll_device == NULL) {
        printk(
                KERN_WARNING "EXTOLL2: Trying to remove extoll pci device that has not been successfully probed\n");
        return;
    }

    // FIXME Cleanup SysFS
    //-------------------------
    extoll_rf_remove_sysfs_extoll_rf_files();


    // Release memory regions
    //----------------------------

    //-- Release BARS
    printk(KERN_INFO "EXTOLL2: releasing BARs ... \n");
    release_mem_region(extoll_device->bar0_addr, extoll_device->bar0_size);
    release_mem_region(extoll_device->bar2_addr, extoll_device->bar2_size);
    release_mem_region(extoll_device->bar4_addr, extoll_device->bar4_size);



    //-- Unmap all regions of all units
    printk(KERN_INFO "EXTOLL2: Unmapping regions of all units \n");
    for (ui = 0; ui < extoll_device->units_count; ui++) {
        for (ri = 0; ri < extoll_device->units[ui].fu_regions_count; ri++) {
            iounmap(extoll_device->units[ui].fu_regions[ri]->vaddress);
            kfree(extoll_device->units[ui].fu_regions[ri]);
        }

    }


    //-- Disable device
    printk(KERN_INFO "EXTOLL2: disabling Device ...\n");
    pci_disable_device(devp);

    //-- FIXME: Readapt the Array Free device at last
    kfree(extoll_device);
    printk(KERN_INFO "EXTOLL2: remove done!!\n\n");
}

/**
 * Driver description structure
 * name : The name of the driver (extoll is logic)
 * id_table: The ids variable is a table with all VENDOR_ID+DEVICE_ID supported by this driver
 * probe: pointer to the probe function
 * remove: pointer to the remove function
 */
static struct pci_driver pci_driver = {
        .name = "extoll",
        .id_table = ids,
        .probe = extoll_probe,
        .remove = __devexit_p(extoll_remove), };

/** }@ */

/******************************************************************************
 *  Interrupt handling							      *
 ******************************************************************************/

//FIXME: interrupts handling depends on SNQ, not yet implemented.
//Therefoer all functionality has been removed!
// static extoll_i_handler irq_handlers[64];
// 
// /* initialize the irq function pointer array */
// void init_extoll_interrupt_handlers(void)
// {
//   int i;
//   for (i=0;i<64;i++)
//     {
//       irq_handlers[i]=0;
//     }
// }
// 
// /* register a handler function for the extoll interrupt cause with the given idx
//   */
// void extoll_register_interrupt_handler(int idx, extoll_i_handler handler)
// {
//   irq_handlers[idx]=handler;
// }
// EXPORT_SYMBOL(extoll_register_interrupt_handler);
// 
// /* register a handler function for the extoll interrupt cause with the given idx
//   */
// void extoll_deregister_interrupt_handler(int idx)
// {
//   irq_handlers[idx]=0;
// }
// EXPORT_SYMBOL(extoll_deregister_interrupt_handler);
// 
// /* clears the interrupt register bit for the interrupt cause with the given index. 
//     Can be called by a handler to immediately clear the interrupt bit
// */
// void extoll_clear_interrupt(int idx)
// {
//   uint64_t to_clear=0;
//   to_clear=1<<idx;
//   //set_interrupts_intrs(to_clear);
// }
// EXPORT_SYMBOL(extoll_clear_interrupt);
static irqreturn_t extoll_interrupt_handler(int irq, void *dev_id) //, struct pt_regs *regs)
{
//   uint64_t interrupt_cause;
//   uint64_t mask;
//   int idx;
//   uint64_t to_be_cleared;
//   extoll_i_handler handler;
//   // first read the interrupt bit register
//   //to_be_cleared=get_interrupts_intrs();
//   interrupt_cause=to_be_cleared;
//   //printk("EXTOLL Interrupt. Interrupt cause register: %lx\n",(unsigned long)interrupt_cause);
//   /* //now call the appropriate handler */
//   idx=0;
//   mask=1l;
//   //while (interrupt_cause!=0)
//   for (idx=0;idx<64;idx++)
//     {
//       if (interrupt_cause & mask)
//         {
//           if (irq_handlers[idx]!=0)
//             {
//               handler=irq_handlers[idx];
//               handler(idx);
//             }
//           else
//             printk("<1> Extoll interrupt with no registered handler (index=%u)\n",idx);
//         }
//       //idx=idx<<1;
//       mask=mask<<1;      
//     }
    interrupt_counter++;
    //set_interrupts_intrs(to_be_cleared); //clear all irqs
    return IRQ_HANDLED;
}

/******************************************************************************
 *  Module handling							      *
 ******************************************************************************/
static int __init extoll_init(void) {
    printk(KERN_INFO "EXTOLL2: module init\n");

    /* Hardware needs 4KB pages !!!
     */
    if (PAGE_SIZE != 4096) {
        printk(KERN_ALERT "extoll: PAGE_SIZE is not 4KB !! exiting");
        return -ENXIO;
    }

    return pci_register_driver(&pci_driver);
}

static void __exit extoll_exit(void) {
    printk(KERN_INFO"EXTOLL2: module exit, interrupt counter is %u\n",
            interrupt_counter);

    pci_unregister_driver(&pci_driver);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mondrian Nuessle nuessle@uni-hd.de");
MODULE_DESCRIPTION("Base EXTOLL hardware driver.");
MODULE_VERSION("1.0");

module_init(extoll_init);
module_exit(extoll_exit);
