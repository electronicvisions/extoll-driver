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

#ifndef _VELO2_MOD_H_
#define _VELO2_MOD_H_

/******************************************************************************
 *! \defgroup MACROS @{ 
 ******************************************************************************/
//! This macro is used to pack nodeid and vpid in one integer 
#define VELO2_ADDR_PACK(nodeid,vpid) ((((vpid) & 0xff)<<16l) | ((nodeid) & 0xffffl))

//! This macro is used to unpack nodeid and vpid from one integer 
#define VELO2_ADDR_UNPACK(addr, node_id,vpid) {(node_id)=(addr) & 0xffff; (vpid)=((addr)>>16) & 0xff;}

//! This macro is used to build a multicast address for the given group
#define VELO2_MCADDR_PACK(mc_group) ((mc_group) | 0x10000000)

//! This macro can be used to build the upper dword of a velo2 requester header
#define VELO2_REQUEST_UPPERHEADER(mtt,tag,length)  ((((length) & 0x7fl)<<16l) | (((tag) & 0xff)<<8l) | ((mtt) & 0x3l))

//! This macro builds one requester status word from individual fields
#define VELO2_REQUEST_HEADER(nodeid,vpid,mtt,tag,length)  ((VELO2_REQUEST_UPPERHEADER(mtt,tag,length)<<32l) | (VELO2_ADDR_PACK(nodeid,vpid)))

//! Works on a status word, when receiving. Get the source node id for the message being received.
#define VELO2_STATUS_NODEID(statusp)  ((*(statusp)) & 0xffffl)
//! Works on a status word, when receiving. Get the source VPID for the message being received.
#define VELO2_STATUS_VPID(statusp)    (((*(statusp))>>16l) & 0xffl)
//! Works on a status word, when receiving. Get the sourceid meaning node id and vpid together
#define VELO2_STATUS_SOURCEID(statusp)    (((*(statusp))) & 0xffffffl)
//! Works on a status word, when receiving. Get the Message Type Tag for the message being received.
#define VELO2_STATUS_MTT(statusp)     (((*(statusp))>>32l) & 0x3l)
//! Works on a status word, when receiving. Get the user tag for the message being received.
#define VELO2_STATUS_TAG(statusp)     (((*(statusp))>>40l) & 0xffl)
//! Works on a status word, when receiving. Get the length for the message being received.
#define VELO2_STATUS_LENGTH(statusp)  (((*(statusp))>>48l) & 0x7fl)
//! Works on a status word, when receiving. Get the end-of-message marker for the message being received.
#define VELO2_STATUS_EOM(statusp)     (((*(statusp))>>36l) & 0x1l)
//! Works on a status word, when receiving. Get the error markerfor the message being received.
#define VELO2_STATUS_ERR(statusp)     (((*(statusp))>>37l) & 0x1l)
/*! @} */

#endif
