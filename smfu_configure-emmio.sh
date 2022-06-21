#!/bin/sh

#  This file is part of the  Linux Kernel Driver Package for EXTOLL R2.
#
#  Copyright (C) 2011 EXTOLL GmbH
#
#  Written by Mondrian Nuessle (2011)
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#FIXME!!
echo "NOT SUPPORTED"
exit

bdf=`lspci -d 0007:0007 | awk '{print $1}'`
SYSPATH=/sys/bus/pci/devices/0000:$bdf/extoll
echo "Using $SYSPATH"
# cd /sys/bus/pci/devices/0000:$bdf/extoll
# cd /sys/bus/pci/devices/0000\:0b\:01.0/extoll/

# Set smfu_general to local BAR base address
echo 0x8000000000 > $SYSPATH/smfu_general
echo "Setting smfu_general to '" `cat $SYSPATH/smfu_general` "'"

# For each node, set smfu_balt to the start address of the corresponding shared memory region
# echo <node> <shmem_start>
echo 0 0x00003c0000000 > $SYSPATH/smfu_balt
echo 1 0x00003c0000000 > $SYSPATH/smfu_balt
echo "Setting smfu_balt: ---------------------------"
echo 0 0x00003c0000000
echo 1 0x00003c0000000
echo "----------------------------------------------"
echo

# Set the address mask for the address calculation. This bit vector identifies the portion of 
# the address that is used to determine the target node.
echo 0x0000000008000000 > $SYSPATH/smfu_mask_calc
echo "Setting smfu_mask_calc to '" `cat $SYSPATH/smfu_mask_calc` "'"

# For each node, set the appropriate routing. See EXTOLL manual for details.
echo 0 0x0040000000000000 > $SYSPATH/rlt
echo 1 0x0040000000000043 > $SYSPATH/rlt
echo "Setting rlt: ---------------------------------"
echo 0 0x0040000000000000 
echo 1 0x0040000000000043 
echo "----------------------------------------------"
echo

# Set the ID for this node. Format can be seen below, ID is shifted left by 32 bits
echo 0x000000000 > $SYSPATH/ids
# echo 0x100000000 > ids
echo "Setting ids to '" `cat $SYSPATH/ids` "'"

echo "Local link status ----------------------------"
cat $SYSPATH/lp_status_reg
echo "----------------------------------------------"
echo

