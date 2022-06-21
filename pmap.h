/*
 *  This file is part of the  Linux Kernel Driver Package for EXTOLL R2.
 *
 *  Copyright (C) 2011,2014 EXTOLL GmbH
 *
 *  Written by Mondrian Nuessle (2011,2014)
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
#ifndef PMAP_H
#define PMAP_H

#include "arch_define.h"

#ifdef PMAPDRV
#include <linux/cdev.h>
#define PMAP_MINOR_COUNT       1
#define PMAP_MINOR             0

struct pmap_device {

    struct pci_dev *devp;         //! pointer to the pci device of EXTOLL
    struct cdev cdev;             //! the character device file for PMAP
    dev_t devnr;                 //! the major number of the PMAP device file
    struct device* dev;
    

};
typedef struct pmap_device pmap_device_t;

struct pmap_map {
  struct list_head list;
  uint64_t p_address;
  void* v_address;
  uint64_t size;
  uint64_t type; //0 - dma_alloced memory 1- high mem 2- unused yet
  uint32_t key;
};
typedef struct pmap_map pmap_map_t;

struct pmap_proc {
  pid_t pid;
  int mapped;
  struct list_head map_list;
  pmap_map_t* current_buffer;
#ifdef MICEXTOLL
  struct micextoll_device *devp;
#else
  struct pci_dev *devp;
#endif
};

typedef struct pmap_proc pmap_proc_t;
#endif

#define PMAP_IOC_MAGIC 'k'
#define PMAP_IOC_MAXNR 9

#define PMAP_IOCTL_SET_TYPE    _IOW(PMAP_IOC_MAGIC, 0, uint32_t)
#define PMAP_IOCTL_GET_TYPE    _IOR(PMAP_IOC_MAGIC, 1, uint32_t)
#define PMAP_IOCTL_SET_HADDR   _IOW(PMAP_IOC_MAGIC, 2, uint32_t)
#define PMAP_IOCTL_GET_HADDR   _IOR(PMAP_IOC_MAGIC, 3, uint32_t)
#define PMAP_IOCTL_SET_SIZE    _IOW(PMAP_IOC_MAGIC, 4, uint32_t)
#define PMAP_IOCTL_GET_SIZE    _IOR(PMAP_IOC_MAGIC, 5, uint32_t)
#define PMAP_IOCTL_GET_PADDR   _IOR(PMAP_IOC_MAGIC, 6, uint32_t)
#define PMAP_IOCTL_CREATE      _IOR(PMAP_IOC_MAGIC, 7, uint32_t)
#define PMAP_IOCTL_FREE        _IOR(PMAP_IOC_MAGIC, 8, uint32_t)
#define PMAP_IOCTL_SET_CURRENT _IOW(PMAP_IOC_MAGIC, 9, uint32_t)

#endif
