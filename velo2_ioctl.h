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

#ifndef _VELO2_IOCTL_H_
#define _VELO2_IOCTL_H_


/******************************************************************************
 *  IOCTL                                                                     *
 ******************************************************************************/
/* ioctl commands
 *
 * IOCTL commands are used for the user configuration space registers.
 * All other memory on the device has to be written with file operation
 * commands.
 *
 * Use 'k' as magic number.
 *
 * When writing official drivers for distribution or for the linux
 * kernel source tree, we should get a regular magic number like
 * described here :
 *      /usr/src/linux/Documentation/ioctl-number.txt
 *      /lib/modules/2.4.10-4GB/build/include/asm/ioctl.h
 *
 * IOCx prefix indicates argument usage
 * S means "Set" through ptr
 * T means "Tell" directly with argument value
 * G means "Get" result through ptr
 * Q means "Query": returns value directly
 */
#define VELO2_IOC_MAGIC 'k'
#define VELO2_IOC_MAXNR 21

#define VELO2_IOCG_GET_RP               _IOR(VELO2_IOC_MAGIC, 0, uint32_t)
#define VELO2_IOCT_SET_RP               _IOW(VELO2_IOC_MAGIC, 1, uint32_t)
#define VELO2_IOCG_GET_WP               _IOR(VELO2_IOC_MAGIC, 2, uint32_t)
#define VELO2_IOCT_SET_WP               _IOW(VELO2_IOC_MAGIC, 3, uint32_t)
#define VELO2_IOCG_GET_VPID             _IOR(VELO2_IOC_MAGIC, 4, uint64_t)
#define VELO2_IOCG_GET_MBOX_SIZE        _IOR(VELO2_IOC_MAGIC, 5, uint64_t)
#define VELO2_IOCG_SET_MBOX_SIZE        _IOW(VELO2_IOC_MAGIC, 6, uint64_t)
#define VELO2_IOCG_GET_SEGMENT_SIZE     _IOR(VELO2_IOC_MAGIC, 7, uint64_t)
#define VELO2_IOCG_SET_SEGMENT_SIZE     _IOW(VELO2_IOC_MAGIC, 8, uint64_t)
#define VELO2_IOCT_SET_ASYNC            _IOW(VELO2_IOC_MAGIC, 9, uint32_t)
#define VELO2_IOCT_SET_POLLTIMES        _IOW(VELO2_IOC_MAGIC, 10, uint32_t)
#define VELO2_IOCT_SET_POLLFLAG         _IOW(VELO2_IOC_MAGIC, 11, uint32_t)
#define VELO2_IOCG_GET_NODEID           _IOR(VELO2_IOC_MAGIC, 12, uint64_t)
#define VELO2_IOCG_SET_TX_PROTDESC      _IOW(VELO2_IOC_MAGIC, 13, uint64_t)
#define VELO2_IOCG_GET_TX_PROTDESC      _IOR(VELO2_IOC_MAGIC, 14, uint64_t)
#define VELO2_IOCG_SET_RX_PROTDESC      _IOW(VELO2_IOC_MAGIC, 15, uint64_t)
#define VELO2_IOCG_GET_RX_PROTDESC      _IOR(VELO2_IOC_MAGIC, 16, uint64_t)
#define VELO2_IOCG_SET_TX_ID            _IOW(VELO2_IOC_MAGIC, 17, uint64_t)
#define VELO2_IOCG_GET_TX_ID            _IOR(VELO2_IOC_MAGIC, 18, uint64_t)
#define VELO2_IOCG_GET_PROCNUM          _IOR(VELO2_IOC_MAGIC, 19, uint32_t)
#define VELO2_IOCG_GET_NODENUM          _IOR(VELO2_IOC_MAGIC, 20, uint32_t)
#define VELO2_IOCG_GET_SLOT_SIZE        _IOR(VELO2_IOC_MAGIC, 21, uint32_t)

#endif
