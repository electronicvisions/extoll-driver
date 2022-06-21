/*
 *  This file is part of the  Linux Kernel Driver Package for EXTOLL R2.
 *
 *  Copyright (C) 2012 EXTOLL GmbH
 *
 *  Written by Mondrian Nuessle (2012)
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

#ifndef _SMFU2_IOCTL_H_
#define _SMFU2_IOCTL_H_


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
#define SMFU2_IOC_MAGIC 'k'
#define SMFU2_IOC_MAXNR 2

#define SMFU2_IOCTL_GET_LOCAL_SIZE _IOR(SMFU2_IOC_MAGIC, 0, uint64_t)
#define SMFU2_IOCTL_FLUSH_CACHES _IOR(SMFU2_IOC_MAGIC, 1, uint64_t)
#define SMFU2_IOCTL_GET_NODE_ID _IOR(SMFU2_IOC_MAGIC, 2, uint64_t)



#endif
