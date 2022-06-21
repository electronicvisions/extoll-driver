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
#include "arch_define.h"

/*! \file  atu_drv 
This is the Linux kernel level driver for the EXTOLL R2 Address Translation Unit (ATU2).
ATU is mainly used by URMA and user-space RMA application which need address translation
services.
*/
#ifndef ATU2_DRV_H
#define ATU2_DRV_H
#define MAX_VPID_NUM 256
/*!
  \brief Encoding of the page sizes supported by ATU2
 */
typedef enum {
  ATU2_KB4 = 0,
  ATU2_KB64 = 4,
  ATU2_MB2 = 9,
  ATU2_GB1 = 18
} atu2_gat_size_t;

/*!
  \brief Encoding of the valid field of an ATU2 GATe
 */
typedef enum {
  ATU2_INV = 0,
  ATU2_RO  = 1,
  ATU2_WO  = 2,
  ATU2_RW  = 3
} atu2_valid_t;


/*!
  \brief Type for the on-chip first-level translation RAM, one GAT
*/
#pragma pack(push)
#pragma pack(1)
struct gat_lookup {
  unsigned long int gat_address : 31;
  unsigned long int valid : 1;
};
typedef struct gat_lookup atu2_gat_lookup_t;

/*!
  \brief Type for one translation entry, a Global Address Translation entry, short GATe
*/
#pragma pack(1)
union gate {
  struct {
  unsigned long int valid : 2;
  unsigned long int vpid : 10;
  unsigned long int pa :   40;
  unsigned long int rsv:    7;
  unsigned long int size :  5;
  } structured;
  uint64_t value;
};

typedef union gate atu2_gate_t;

/*!
  /brief Type for one GAT, a Global Address Table, the table for ATU that resides in memory
  
  Such a GAT has a size of 2MB. This is enough to hold 256k page entries, enough for 1 GB PA.
  GATs form the second level of translation in ATU, the first level is on-chip
*/
typedef atu2_gate_t atu2_gat_t[262144]; 

/*!
  \brief Type for the management structure of one GAT
  This structure includes some additional information per GAT
*/
typedef struct {
  bool valid; //! Wheter this GAT is valid, i.e. allocated and registered in the on-chip first-level
  unsigned long pa; //! The physical start address of the table
  unsigned long free_entries_in_1k[256]; //! number of free entries is 1k entries -> for quicker search...
  //atu2_gat_t* entries; //! Pointer to the actual table
  atu2_gate_t* entries; //! Pointer to the actual table
} atu2_gat_table_t;

/* \brief Table to count registered pages per VPID (one page)
*/
int* _atu2_num_pages_of_vpid;


typedef struct {
  volatile unsigned long int notifications[256];
  unsigned long int padding[256];
} atu2_notification_table_t;

/* Functions that are exported for other modules to be used:
*/

/*! 
  \brief Returns the maximum number of VPIDs supported by atudrv.
  \return number of VPIDs supported
*/
int atu2_get_supported_vpids(void);

/*! 
  \brief Returns the ID of the highest VPID that can be used. Generally  atu_get_supported_vpids()-1
  \return highest VPID
*/
int atu2_get_max_vpids(void);

/*!
\brief Registers a region of user virtual memory of given size on behalf of a VPID. 

Register a memory region, that is contigous in the virtual address space of the current process context (user space).
The NLA of the registered region is returned. The function als pins the pages associated with that region.

\param vpid The VPID for which the memory region should be registered
\param address The start address of the memory region to be registered with ATU2. This is a user virtual address
\param size Size of the region in bytes
\param read_acc whether read accesses to the region will be performed by RMA. Unused for now
\param write_acc whether write accesses to the region will be performed by RMA. Unused for now
\param nla Pointer to an unsigend long, where the resulting start NLA, as a result of the registration will be written to
*/
int atu2_register_virtual_region(unsigned int vpid, unsigned long address, unsigned long size, bool read_access, bool write_access, unsigned long* nlas);

/*!
\brief Registers a region of physical memory of given size on behalf of a VPID. 

Register a memory region, that is contigous in the physical address space.
The NLA of the registered region is returned. The function als pins the pages associated with that region.

\param vpid The VPID for which the memory region should be registered
\param address The start address of the memory region to be registered with ATU2. This is a physical address.
\param size Size of the region in bytes
\param read_acc whether read accesses to the region will be performed by RMA. Unused for now
\param write_acc whether write accesses to the region will be performed by RMA. Unused for now
\param nla Pointer to an unsigend long, where the resulting start NLA, as a result of the registration will be written to
*/
int atu2_register_physical_region(unsigned int vpid, unsigned long address, unsigned long size, bool read_acc, bool write_acc, unsigned long* nla);

/*!
 \brief Registers a list of pages (struct page* pages) which is embedded in a linear array of an arbitratry type on behalf of a VPID. 
 Example fo a struct page** p with n entries-> vec=p, count=n. stride=sizeof(struct page *)
 
 \param vpid The VPID for which the memory region should be registered  
 \param vec pointer to the struct page* of the first entry of the vector
 \param count number of entries in vec
 \param stride number of bytes to be added to reach the next struct page in the vector
 \param read_acc whether read accesses to the region will be performed by RMA. Unused for now
\param write_acc whether write accesses to the region will be performed by RMA. Unused for now
\param nla Pointer to an unsigend long, where the resulting start NLA, as a result of the registration will be written to
*/
int atu2_register_page_list(unsigned int vpid, void* vec,unsigned long count, unsigned int stride, bool read_acc, bool write_acc, unsigned long* nla);

/*!
\brief Unregisters a single page, identified by ist NLA

 \param vpid The VPID for which the page should be unregistered  
 \param nla the NLA of the page to be unregistered
*/
int atu2_unregister_page_by_nla(unsigned int vpid, unsigned long nla);

/*!
\brief Unregisters a page list, identified by its NLA

 \param vpid The VPID for which the page should be unregistered  
 \param nla the NLA of the page to be unregistered
 \param count Number of pages to unregister
 \param physical Physical address
*/
int atu2_unregister_pages_by_nla(unsigned int vpid, unsigned long nla, int count, int physical);

/*!
\brief Unregisters a virtual user memory region again

 \param vpid The VPID for which the page should be unregistered  
 \param start_nla the starting NLA of the region to be unregistered
 \param size Size of the region in bytes
*/
int atu2_unregister_virtual_region(unsigned vpid, unsigned long start_nla, uint64_t size);

/*!
\brief Unregisters a physical memory region again

 \param vpid The VPID for which the page should be unregistered  
 \param start_nla the starting NLA of the physical region to be unregistered
 \param size Size of the region in bytes
*/
int atu2_unregister_physical_region(unsigned vpid, unsigned long start_nla, uint64_t size);

/*!
  \brief Unregister all pages, registered by the given VPID.
  
  This function is especially usefull to implement the correct behavior,
  when a process ends.
  
  Note: This function does not acquire the mm lock, because usually it 
  is not available anymore when this function is called,
  i.e. when the process has ended.
*/
int atu2_unregister_vpid_pages(unsigned int vpid, int physical);

int atu2_unregister_pages_by_nla(unsigned int vpid, unsigned long nla, int count, int physical);

/* End of exported functions */

#ifdef ATU_DRV_INT
/*!
\brief Searches for num_pages free entries for the given VPID.
This function searches for enough entries in a GAT to support registering num_pages pages 
on behalf of the given VPID. The starting entry is returned using gat_idx and gate_idx.
If no mathcing space is found, the function fails.
\param vpid
\param num_pages
\param gat_idx
\param gate_idx
\return
*/
static int find_free_entries(int vpid, int num_pages, int* gat_idx, int* gate_idx);

/*!
\brief Performs the actual registration of a set of pages
*/
static int perform_register_pages(unsigned int vpid, unsigned long address, unsigned long npages, bool read_access, bool write_access, /*unsigned long* nla,*/ int gat_idx, int gate_idx, unsigned long * return_first_page);
  
/*!
\brief Waits that a flush is finished
*/
static int atu2_wait_for_flush(unsigned int vpid);

/*!
\brief Performs the actual un- or deregistration of a page
*/
static int perform_unregister_page(int vpid,int gat_idx, int gate_idx, int lock, int flush, int physical);

int atu2_unregister_region(unsigned vpid, unsigned long start_nla, uint64_t size,int physical);

/*!
\brief Performs the actual un- or deregistration of a set of pages
*/
//static int perform_unregister_pages(int vpid,int gat_idx, int start_gate_idx, int count);
//static int perform_unregister_pages_pa(int vpid,int start_gat_idx, int start_gate_idx, int count);
static int perform_unregister_pages(int vpid,int start_gat_idx, int start_gate_idx, int count,int physical);


#endif

#pragma pack(pop) //resets packing of structs no more problems with other header files following this one!
#endif
