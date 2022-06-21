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

cd $SYSPATH 

echo "smfu2 control&status register: ----------------------------------"
cat extoll_rf_smfu_top_rf_smfu_top_rf_smfu_status_control
echo "----------------------------------------------"
echo

echo "smfu2 count register: -----------------------------"
echo "misc count" -n
cat extoll_rf_smfu_top_rf_smfu_top_rf_smfu_misc_count
echo "rcvd np count" -n
cat extoll_rf_smfu_top_rf_smfu_top_rf_smfu_rcvd_count_np
echo "rcvd p count" -n
cat extoll_rf_smfu_top_rf_smfu_top_rf_smfu_rcvd_count_p
echo "rcvd resp count" -n
cat extoll_rf_smfu_top_rf_smfu_top_rf_smfu_rcvd_count_rsp
echo "send np count" -n
cat extoll_rf_smfu_top_rf_smfu_top_rf_smfu_sent_count_np
echo "send p count" -n
cat extoll_rf_smfu_top_rf_smfu_top_rf_smfu_sent_count_p
echo "send resp count" -n
cat extoll_rf_smfu_top_rf_smfu_top_rf_smfu_sent_count_rsp
echo "----------------------------------------------"
echo
