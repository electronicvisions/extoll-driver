/*
 *  This file is part of the  Linux Kernel Driver Package for EXTOLL R2.
 *
 *  Copyright (C) 2016 EXTOLL GmbH
 *
 *  Written by Mondrian Nuessle (2016)
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

#ifndef _EXTOLL_RF_ACCESS_IOCTL_H_
#define _EXTOLL_RF_ACCESS_IOCTL_H_


/******************************************************************************
 *  IOCTL                                                                     *
 ******************************************************************************/
/* ioctl commands
 *
 * IOCTL commands are used for the user configuration space registers.
 * All other memory on the device has to be written with file operation
 * commands.
 *
 * Use 'n' as magic number.
 *
 * When writing official drivers for distribution or for the linux
 * kernel source tree, we should get a regular magic number like
 * described here :
 *      /usr/src/linux/Documentation/ioctl-number.txt
 *      /lib/modules/2.4.10-4GB/build/include/asm/ioctl.h
 *
 */
#define EXTOLL_RF_IOC_MAGIC 'n'
#define EXTOLL_RF_IOC_MAXNR 5

#define EXTOLL_RF_IOCTL_GET_RRA_WRITE_METHOD _IOR(EXTOLL_RF_IOC_MAGIC, 0, uint64_t)
#define EXTOLL_RF_IOCTL_GET_RRA_READ_METHOD _IOR(EXTOLL_RF_IOC_MAGIC, 1, uint64_t)
#define EXTOLL_RF_IOCTL_GET_RRA_RMA_TIMEOUT _IOR(EXTOLL_RF_IOC_MAGIC, 2, uint64_t)
#define EXTOLL_RF_IOCTL_SET_RRA_WRITE_METHOD _IOW(EXTOLL_RF_IOC_MAGIC, 3, uint64_t)
#define EXTOLL_RF_IOCTL_SET_RRA_READ_METHOD _IOW(EXTOLL_RF_IOC_MAGIC, 4, uint64_t)
#define EXTOLL_RF_IOCTL_SET_RRA_RMA_TIMEOUT _IOW(EXTOLL_RF_IOC_MAGIC, 5, uint64_t)


/* RRA Access methods. Can be set idenpendently for read and write.
   Two methods defined for now: using RMA or SMFU */
#define EXTOLL2_RF_RRA_SMFU2 1
#define EXTOLL2_RF_RRA_RMA2 0
#define EXTOLL2_RF_RRA_LOCAL 2

#endif
