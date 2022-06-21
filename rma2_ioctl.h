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

#ifndef _RMA2_IOCTL_H_
#define _RMA2_IOCTL_H_


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
 */
#define RMA2_IOC_MAGIC 'k'
#define RMA2_IOC_MAXNR 26

//"legacy" from RMA1:
#define RMA2_IOCTL_GET_NOTIQ_SIZE _IOR(RMA2_IOC_MAGIC, 0, uint32_t)
#define RMA2_IOCTL_SET_NOTIQ_SIZE _IOW(RMA2_IOC_MAGIC, 1, uint32_t)
#define RMA2_IOCTL_SET_NOTIQ_SEGMENT_SIZE _IOW(RMA2_IOC_MAGIC, 2, uint32_t)
#define RMA2_IOCTL_GET_NOTIQ_SEGMENT_SIZE _IOR(RMA2_IOC_MAGIC, 3, uint32_t)
#define RMA2_IOCTL_SET_NOTIQ_WP _IOW(RMA2_IOC_MAGIC, 4, uint32_t)
#define RMA2_IOCTL_SET_NOTIQ_RP _IOW(RMA2_IOC_MAGIC, 5, uint32_t)
#define RMA2_IOCTL_GET_NOTIQ_WP _IOR(RMA2_IOC_MAGIC, 6, uint32_t)
#define RMA2_IOCTL_GET_NOTIQ_RP _IOR(RMA2_IOC_MAGIC, 7, uint32_t)
#define RMA2_IOCTL_GET_NODEID _IOR(RMA2_IOC_MAGIC, 8, uint32_t)
#define RMA2_IOCTL_GET_VPID _IOR(RMA2_IOC_MAGIC, 9, uint32_t)
#define RMA2_IOCTL_REGISTER_REGION _IOW(RMA2_IOC_MAGIC, 10, void*)
#define RMA2_IOCTL_UNREGISTER_REGION _IOW(RMA2_IOC_MAGIC,11, void*)
#define RMA2_IOCTL_GET_MAXNODEID _IOR(RMA2_IOC_MAGIC, 12, uint32_t)
#define RMA2_IOCTL_GET_MAXVPID _IOR(RMA2_IOC_MAGIC, 13, uint32_t)

//new for RMA2:
#define RMA2_IOCTL_SET_TUS _IOW(RMA2_IOC_MAGIC, 14, uint32_t)
#define RMA2_IOCTL_GET_TUS _IOR(RMA2_IOC_MAGIC, 15, uint32_t)
#define RMA2_IOCTL_SET_EXCELL _IOW(RMA2_IOC_MAGIC, 16, uint32_t)
#define RMA2_IOCTL_GET_EXCELL _IOR(RMA2_IOC_MAGIC, 17, uint32_t)

#define RMA2_IOCTL_SET_TCS _IOW(RMA2_IOC_MAGIC, 18, uint32_t)
#define RMA2_IOCTL_GET_TCS _IOR(RMA2_IOC_MAGIC, 19, uint32_t)

#define RMA2_IOCTL_SET_PROTDESC _IOW(RMA2_IOC_MAGIC, 20, uint32_t)
#define RMA2_IOCTL_GET_PROTDESC _IOR(RMA2_IOC_MAGIC, 21, uint32_t)

#define RMA2_IOCTL_SET_TPHBITS _IOW(RMA2_IOC_MAGIC, 22, uint32_t)
#define RMA2_IOCTL_GET_TPHBITS _IOR(RMA2_IOC_MAGIC, 23, uint32_t)

#define RMA2_IOCTL_SET_HISTMODE _IOW(RMA2_IOC_MAGIC, 24, uint32_t)
#define RMA2_IOCTL_GET_HISTMODE _IOR(RMA2_IOC_MAGIC, 25, uint32_t)



#endif
