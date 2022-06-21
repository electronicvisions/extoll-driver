/**
 * extoll_drv_user.h
 *
 * This work is licensed under the Creative Commons Attribution-ShareAlike 3.0 Unported License. 
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/3.0/ or send 
 * a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.  
 *
 *
 * This .h gathers structure definitions and so on that are useful for
 * Users of the driver
 *
 */

#ifndef EXTOLL_DRV_USER_H_
#define EXTOLL_DRV_USER_H_

// Includes
//-----------------

//-- PCI
#include <linux/pci.h>



/** \defgroup Extoll device representation and memory mapping */
/** @{ */

/**
 * This structure holds informations about a mapped memory region
 */
typedef struct mapped_region {

  unsigned int  bar;      //< The BAR where this region is mapped into
  unsigned long paddress; //< Base physical address to map from virtual
  void *        vaddress; //< Kernel Virtual address of mapped region
  unsigned long size;     //< Size of the region

} mapped_region_t;

/**
 * The structure to manage an Extoll unit in an Extoll device
 * Holds the addresses to each FU of an Extoll unit
 */
typedef struct extoll_unit {

  mapped_region_t ** fu_regions;       //< Array of pointer to regions
  unsigned int       fu_regions_count; //< number of regions into fu_regions array

  int rf_region_index;     //< located in BAR0, not cacheable,  -1: Not mapped, otherwise index in the regions table
  int velo2_region_index;  //< located in BAR0, wc mapped,      -1: Not mapped, otherwise index in the regions table
  int rma2_region_index;   //< located in BAR0, wc mapped,      -1: Not mapped, otherwise index in the regions table
  int smfu2_region_index;  //< located in BAR2, not cacheable,  -1: Not mapped, otherwise index in the regions table


} extoll_unit_t ;



/*!
\brief The structure to manage one EXTOLL device
*/
typedef struct extoll_device {

    struct pci_dev *devp;       //! pointer to the kernel PCI device (HyperTransport devices are also managed as PCI devices).

    //void *bar0_vaddr;         //! kernel virtual address of BAR0 of the device. The registerfile is located in BAR0.
    unsigned long bar0_addr;    //! physical virtual address of BAR0 of the device. The registerfile is located in BAR0.
    unsigned long bar0_size;    //! size of BAR0 of the device. The registerfile is located in BAR2.

    //void *bar2_vaddr;     //! kernel virtual address of BAR0 of the device. The VELO (Requester) functional unit is located in BAR2.
    unsigned long bar2_addr;    //! physical virtual address of BAR0 of the device. The VELO (Requester) functional unit is located in BAR2.
    unsigned long bar2_size;    //! size of BAR2 of the device. The VELO (Requester) functional unit is located in BAR0.

    //void *bar4_vaddr;     //! kernel virtual address of BAR0 of the device. The RMA (requester) functional unit is located in BAR0.
    unsigned long bar4_addr;    //! physical virtual address of BAR0 of the device. The RMA (requester) functional unit is located in BAR0.
    unsigned long bar4_size;    //! size of BAR0 of the device. The RMA (requester) functional unit is located in BAR2.

    /// Extoll units array in the device
    extoll_unit_t * units;

    /// Number of extoll units in the device
    unsigned int    units_count;


    unsigned int  init_done;      //! set to one if basic init was successfull
} extoll_device_t;

/** }@ */

/** \defgroup Extoll access */
/** @{ */

/**
 * Returns the array of pointer to  the extoll devices
 * @return
 */
extern extoll_device_t ** extoll_get_devices(void);

/**
 * Returns the number of extoll devices detected
 * @return
 */
extern unsigned int extoll_get_devices_count(void);

/** }@ */


#endif /* EXTOLL_DRV_USER_H_ */
