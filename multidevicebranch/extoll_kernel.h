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
#ifndef EXTOLL_KERNEL_H
#define EXTOLL_KERNEL_H


/* Prototypes for kernel routines imported from other EXTOLL modules */
extern int extoll_get_init_done(void);

extern struct pci_dev* extoll_get_pdev(void);

/**
 * Return a pointer to the device structure for an extoll_device
 * @param extoll_device_num The number of the extoll_device
 * @return The pointer to the device structure, or NULL if an error occured
 */
extern extoll_device_t * extoll_get_device(unsigned int extoll_device_num);

extern void* extoll_get_rf_vaddr(void);
extern void* extoll_get_velo2_vaddr(void);
extern void* extoll_get_rma2_vaddr(void);
extern void* extoll_get_smfu_vaddr(void);
extern unsigned long extoll_get_rf_addr(void);
extern unsigned long extoll_get_velo2_addr(void);
extern unsigned long extoll_get_rma2_addr(void);
extern unsigned long extoll_get_smfu_addr(void);
extern unsigned int extoll_get_rf_size(void);
extern unsigned int extoll_get_velo2_size(void);
extern unsigned int extoll_get_rma2_size(void);
extern unsigned int extoll_get_smfu_size(void);
extern unsigned int extoll_get_interrupt_counter(void);
extern void extoll_set_interrupt_counter(unsigned int v);
#endif
