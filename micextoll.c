/*  This file is part of the  Linux Kernel Driver Package for EXTOLL R2.
 *
 *  Copyright (C) 2011 EXTOLL GmbH
 *
 *  Written by Stephan Walter (2012)
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

#ifndef _MICEXTOLL_C_
#define _MICEXTOLL_C_
//#define MICEXTOLL


//TODO
//#include "extolldrv.h"
//#include "extoll_rf_sysfs.h"
#include "micextoll.h"

/*static int micextoll_probe(void)
{
  int err=-1;
//  card.init_done=0;
  printk(KERN_INFO "EXTOLL: MIC probe()\n");

  // err = pci_enable_device(devp); //TODO: we have to initialize I/O and Memory before this step instead of the check
  return 0;
}
*/
/*
//check if the driver and device match
*/
static int micextoll_match(struct device *dev, struct device_driver *driver)
{
  printk(KERN_INFO "MICEXTOLL: execute micextoll_match function\n");
  printk(KERN_INFO "DEVICE: %s\n", dev->init_name);
  printk(KERN_INFO "DEBUG: bus->name: %s\n", dev->bus->name);
  printk(KERN_INFO "DRIVER: %s\n", driver->name);
  
//  return !strncmp(dev->init_name, driver->name, strlen(driver->name));
 return 1;
} 

/*
 * virtual bus system to handle the low lvl abstraction for the extoll driver
 */
static int micextoll_device_probe(struct micextoll_driver *drv, struct micextoll_device *micextoll_dev)
{
  int error = 0;
  printk(KERN_INFO "MICEXTOLL: device_probe");

  error = micextoll_match(&micextoll_dev->dev, &drv->driver);

  return error;

}
EXPORT_SYMBOL(micextoll_device_probe);


struct bus_type micextoll_bus_type = {
  .name = "micextoll",
//  .match = micextoll_match,
//  .probe = micextoll_device_probe,
//  .remove = ,
//  .hotplug = micextoll_hotplug,
};

/*
//example for a simple attribute export. (Exchange the baseaddr and so on with something like this?)
*/
/*static ssize_t show_micextoll_version(struct bus_type *bus, struct bus_attribute *attr)//TODO
{
  return snprintf(attr, PAGE_SIZE,"%s\n", Version);
}
static BUS_ATTR(version, S_IRUGO, show_micextoll_version, NULL);
*/


/*
 * virtual bus device
*/
static void micextoll_bus_release(struct device *dev)
{
  printk(KERN_INFO "micextollbus release\n");
}

struct device micextoll_bus = {
  .init_name    = "micextoll-bus0",//TODO check why .bus_id don`t work!
  .bus          = &micextoll_bus_type,
  .release      = micextoll_bus_release,

};

/*
//Interface fot the registration of a device to the bus system
*/
static void micextoll_dev_release(struct device *dev)
{
 printk(KERN_INFO "micextoll_dev_release");
  }

//TODO: extend for all the parameters and so on
int register_micextoll_device(struct micextoll_device *micextolldev)
{
//  struct micextoll_device = kmalloc(sizeof(struct micextoll_device), GFP_KERNEL);FIXME

  size_t len = strlen(micextolldev->name)+1;
  printk(KERN_INFO "MICEXTOLL: register device: %s\n", micextolldev->name);

  micextolldev->bus 		= &micextoll_bus_type;

//printk (KERN_INFO "DEBUG: init_name: %s\n", micextolldev->dev.init_name);

//  micextolldev->dev.init_name   = micextolldev->name;//FIXME
//
//TODO

  micextolldev->dev.init_name = kmalloc(len , GFP_KERNEL);              // init data
  memset(micextolldev->dev.init_name, 0, len);
  strncpy(micextolldev->dev.init_name, micextolldev->name, len);
  micextolldev->dev.bus 	= &micextoll_bus_type;
  micextolldev->dev.parent 	= &micextoll_bus;
printk(KERN_ALERT "MICEXTOLL.ko DEBUG dev.parent %p\n", micextolldev->dev.parent);
printk(KERN_ALERT "MICEXTOLL.ko DEBUG micextolldev->dev->bus.init_name %s and should be %s\n", micextolldev->dev.bus->name, micextoll_bus_type.name);
  micextolldev->dev.release 	= &micextoll_dev_release;
  micextolldev->dma_mask        = 0xffffffful; //suppport 256MB for now (KNF 256MB BAR)
  micextolldev->dev.dma_mask    = &micextolldev->dma_mask;
//  micextolldev->dev.dma_ops     = &nommu_dma_ops;

//  strncpy(micextolldev->dev.init_name, micextolldev->name, BUS_ID_SIZE);//TODO: again check why .init_name and not .bus_id //TODO: INIT_NAME_SIZE’ undeclared (first use in this function)
//

  return device_register(&micextolldev->dev);
}
EXPORT_SYMBOL(register_micextoll_device);



void unregister_micextoll_device(struct micextoll_device *micextolldev)
{
  device_unregister(&micextolldev->dev);
}
EXPORT_SYMBOL(unregister_micextoll_device);



/*
//Driver Interface TODO:Extend

static ssize_t show_version(struct device_driver *driver, char *buf)
{
  struct micextoll_driver *micextolldriver = to_micextoll_driver(driver);

  sprintf(buf, "s\n", micextolldriver->version);
  return strlen(buf);
}
*/


/*
//Interface for the registration of a driver to the bus system
*/
// TODO:check if we need this
int __register_micextoll_driver(struct micextoll_driver *drv, struct module *owner, const char *mod_name)
{
//TODO: improve this to match the pci version
/*
int __pci_register_driver(struct pci_driver *drv, struct module *owner,
                          const char *mod_name)
{
  */
	int error;

	printk(KERN_INFO "MICEXTOLL: register driver to the micextoll-bus system");

        // initialize common driver fields /
//        drv->driver.name = drv->name;
        drv->driver.bus = &micextoll_bus_type;
//        drv->driver.owner = owner;
//        drv->driver.mod_name = mod_name;



//        spin_lock_init(&drv->dynids.lock);
//        INIT_LIST_HEAD(&drv->dynids.list);

        // register with core /
       error = driver_register(&drv->driver);
       if (error)
               printk(KERN_INFO "MICEXTOLL: unable to register driver");

       printk(KERN_INFO "MICEXTOLL: register driver %p finished", &drv->driver);
               goto out;


/*
        error = pci_create_newid_file(drv);
        if (error)
                goto out_newid;

        error = pci_create_removeid_file(drv);
        if (error)
                goto out_removeid;
*/
out:
        return error;
/*
out_removeid:
        pci_remove_newid_file(drv);
out_newid:
        driver_unregister(&drv->driver);
        goto out;
}
*/
  return error;

}

void unregister_micextoll_driver(struct micextoll_driver *driver)
{
  printk(KERN_INFO "MICEXTOLL: unregister driver %p\n", &driver->driver);
  driver_unregister(&driver->driver);
  printk(KERN_INFO "MICEXTOLL: unregister driver finished\n");
}
EXPORT_SYMBOL(__register_micextoll_driver);
EXPORT_SYMBOL(unregister_micextoll_driver);


int micextoll_enable_device(struct micextoll_device *devp)
{//TODO we have to lock, if we have to add something here, see it as placeholder atm. It is atm not 100% clear, if we have to do some of the operations that the pci version of this function do or not.
  int err=0;
  return err;
}
EXPORT_SYMBOL(micextoll_enable_device);

#define SBOX_SMPT00   0x00003100
#define SBOX_BASE_KNC 0x08007D0000
#define SBOX_SIZE 0x10000

static int __init micextoll_bus_init(void)
{
  int err = -1;
  void* sbox_addr;
  int sbox_size=SBOX_SIZE;

  printk(KERN_INFO "MICEXTOLL: micextoll_bus init\n");


  //register bus_type
  err = bus_register(&micextoll_bus_type);
  if (err)
    return err;

  //create version attribute for the bus
//  if(bus_create_file(&micextoll_bus_type, &bus_attr_version)) //TODO:
//	printk(KERN_NOTICE "Unable to create version attribute\n");


  //register bus "device"
  err = device_register(&micextoll_bus);
  if (err){
    printk(KERN_NOTICE "MICEXTOLL: Unable to register micextoll0 device\n");
  }else{
    printk(KERN_INFO "MICEXTOLL: micextoll0 device register complete\n");
  }

  sbox_addr=ioremap_nocache(SBOX_BASE_KNC,sbox_size);
  if(sbox_addr==NULL) {
    printk("MICEXTOLL: remapping of SBOX failed.");
    return -1;
  }
  printk("!! :Write SMTP Entry for EXTOLL\n");
  printk("sbox virt address is %p\n",sbox_addr);
  printk("SMPT31 was: %x\n",(uint32_t)ioread32(sbox_addr+SBOX_SMPT00+(4*31)));
  iowrite32(0x400,sbox_addr+SBOX_SMPT00+(4*31));
  printk("SMPT31 is now: %x\n",(uint32_t)ioread32(sbox_addr+SBOX_SMPT00+(4*31)));
  iounmap(sbox_addr);
 return err;

}


static void __exit micextoll_bus_exit(void)
{
  printk(KERN_INFO "MICEXTOLL: module exit\n");
 
 //remove bus "device"
  device_unregister(&micextoll_bus);

  //remove bus_type
  bus_unregister(&micextoll_bus_type);
}


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Stephan Walter swalter@ix.urz.uni-heidelberg.de");
MODULE_DESCRIPTION("Virtual EXTOLL bus for MIC");
MODULE_VERSION("1.0");

module_init(micextoll_bus_init);
module_exit(micextoll_bus_exit);

#endif
