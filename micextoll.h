/*    This file is part of the  Linux Kernel Driver Package for EXTOLL R2.
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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#ifndef _MICEXTOLL_H_
#define _MICEXTOLL_H_

#include "arch_define.h"

#include <linux/version.h>
#include <linux/fs.h>
//#include <linux/pci.h>
#include <linux/list.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/string.h>
#include <linux/slab.h>


//we need this to alloc iomemory
#include <asm/io.h>
#include <linux/ioport.h> //TODO check, if we really need this

//TODO check if we really need them
#include <linux/kobject.h>
#include <linux/sysfs.h>
//static int micextoll_probe(void);

extern struct bus_type micextoll_bus_type;

//static void micextoll_bus_release(struct device *dev);

struct device micextoll_bus;
struct micextoll_bus_type;

struct micextoll_device {

  char 			*name;
  struct module  	*module;
  struct bus_type	*bus;//TODO: check if we have to use struct micextoll_bus_type *bus;
//We have to check which attribute we need, this is not! a full list of attributes we have to check
//full list under http://www.cs.fsu.edu/~baker/devices/lxr/http/source/linux/include/linux/pci.h
  struct kobject 	kobj;
  void 			*sysdata;	/* hook for sys-specific extension */
  struct proc_dir_entry	*procent;	/* device entry in /proc/bus/micextoll */
  
  struct micextoll_driver *driver;	/* which driver has allocated this device */
  u64			dma_mask;  	/* Mask of the bits of bus address this
					   device implements.  Normally this is
                                           0xffffffff.  You only need to change
                                           this if your device has broken DMA
                                           or supports 64-bit transfers.  */
  struct device_dma_parameters dma_parms;

  struct device 	dev;		/* Generic device interface */
  unsigned char		irq;		/* device IRQ number    */ //FIXME
  
};

struct micextoll_driver {
/*TODO: PCI Version 
  struct list_head node;
*/
  char 			*name;
  struct module		*module;

//  const struct pci_device_id *id_table;   /* must be non-NULL for probe to be called */
//  int  (*match)  (struct device_driver *drv, struct micextoll_device *dev);//FIXME
  int  (*probe)  (struct micextoll_device *dev);//, const struct pci_device_id *id);   /* New device inserted */TODO chec, if we need the second struct
  void (*remove) (struct micextoll_device *dev);   /* Device removed (NULL if not a hot-plug capable driver) */
//  int  (*suspend) (struct pci_dev *dev, pm_message_t state);      /* Device suspended */
//  int  (*suspend_late) (struct pci_dev *dev, pm_message_t state);
//  int  (*resume_early) (struct pci_dev *dev);
//  int  (*resume) (struct pci_dev *dev);                   /* Device woken up */
/*  void (*shutdown) (struct pci_dev *dev);
  struct pci_error_handlers *err_handler;*/
  struct device_driver    driver;
/*  struct pci_dynids dynids;
*/
};

#define to_micextoll_driver(drv) container_of(drv, struct micextoll_driver, driver);



#define to_micextoll_device(n) container_of(n, struct micextoll_device, dev)

int register_micextoll_device(struct micextoll_device *);
void unregister_micextoll_device(struct micextoll_device *);

int __must_check __register_micextoll_driver(struct micextoll_driver *, struct module *,
						const char *mod_name);
#define register_micextoll_driver(driver) 										__register_micextoll_driver(driver, THIS_MODULE, KBUILD_MODNAME)

void unregister_micextoll_driver(struct micextoll_driver *);
int micextoll_enable_device(struct micextoll_device *);

#endif
