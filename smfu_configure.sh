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

bdf=`lspci -d 0007:0007 | awk '{print $1}'`
SYSPATH=/sys/bus/pci/devices/0000:$bdf/extoll_rf
echo "Using $SYSPATH"
# cd /sys/bus/pci/devices/0000:$bdf/extoll
# cd /sys/bus/pci/devices/0000\:0b\:01.0/extoll/

cd $SYSPATH

#Lower
#Name	field	hw	sw	reset value	desc
#Valid	[0:0]	ro	rw	1’h0	 
#FuncNo	[3:1]	ro	rw	3’h0	 
#tNodeId	[19:4]	ro	rw	16’h0	 
#iEndAddr	[55:20]	ro	rw	36’h0	 
echo 0x0 >  extoll_rf_smfu_top_rf_smfu_status_control 
echo "0 0xfffffffff00007" >extoll_rf_smfu_top_rf_addr_calc_interval_lower
echo "0 0" >extoll_rf_smfu_top_rf_addr_calc_interval_upper
echo 0x1 >  extoll_rf_smfu_top_rf_smfu_status_control 
