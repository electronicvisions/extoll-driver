#!/bin/bash
#  This file is part of the  Linux Kernel Driver Package for EXTOLL R2.
#
#  Copyright (C) 2011 EXTOLL GmbH
#
#  Written by Mondrian Nuessle (2011)
#  Partly based on work done by Philip Degler (2007)
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
#

THIS_SCRIPT_DIR="$(dirname "$(readlink -f ${BASH_SOURCE[0]})")"
# THIS_SCRIPT_DIR="."
# If EXTOLL_R2_HOME is not set, source environement setup
# env setup defines in env the paths to sw home directory, device directory, sysfs directory etc...
# Everything that is needed to have a base dataset describing where devices are and so on
#if [ -z $EXTOLL_R2_HOME ] 
#then
	
#  echo "Sourcing extoll_env.bash (MUST be in parent directory of this script"
#  . ${THIS_SCRIPT_DIR}/../extoll_env.bash

#fi

# invoke insmod with all arguments we got
# and use a pathname, as newer modutils don't look in . by default
/sbin/insmod ${THIS_SCRIPT_DIR}/extoll_rf_sysfs.ko $* 
/sbin/insmod ${THIS_SCRIPT_DIR}/extoll.ko $* 
returnvalue=$?

if [ "$returnvalue" -eq "1" ] ; then
 echo "Loading extoll.ko failed. No device?"
 /sbin/rmmod  ${THIS_SCRIPT_DIR}/extoll.ko
 /sbin/rmmod  ${THIS_SCRIPT_DIR}/extoll_rf_sysfs.ko
 exit
else
 /sbin/insmod ${THIS_SCRIPT_DIR}/extoll_bq.ko $*
 /sbin/insmod ${THIS_SCRIPT_DIR}/velo2.ko $* 
 #/sbin/insmod ${THIS_SCRIPT_DIR}/limic.ko
 /sbin/insmod ${THIS_SCRIPT_DIR}/atu2.ko atu2_enable_preload=0
 /sbin/insmod ${THIS_SCRIPT_DIR}/rma2.ko
 /sbin/insmod ${THIS_SCRIPT_DIR}/pmap.ko
 #/sbin/insmod ${THIS_SCRIPT_DIR}/smfu2.ko smfu2_global_mem_size=274877906944 smfu2_en_write_combining=1 #256GB
 /sbin/insmod ${THIS_SCRIPT_DIR}/smfu2.ko smfu2_global_mem_size=549755813888 smfu2_en_write_combining=1 #512GB
# /sbin/insmod  ${THIS_SCRIPT_DIR}/limic.ko
 /sbin/insmod  ${THIS_SCRIPT_DIR}/extoll_kapi.ko
 /sbin/insmod ${THIS_SCRIPT_DIR}/extoll_rf_access.ko

 /sbin/insmod ${THIS_SCRIPT_DIR}/exn.ko
fi

#devices="smfu2 rma2 pmap extoll_rf_access"
#mode="666"

#for i in $devices ; do

# # remove stale nodes
# rm -f /dev/${i}*
# # create nodes
# major=$(awk "\$2==\"$i\" {print \$1}" /proc/devices)
# mknod /dev/${i} c $major 0
 
# # Group: since distributions do it differently, look for wheel or use staff
# if grep -q '^staff:' /etc/group; then
#     group="staff"
# else
#     group="root"
# fi

# # give appropriate group/permissions, and change the group.
# # Not all distributions have staff, some have "wheel" instead.
# chgrp $group /dev/${i}
# chmod $mode /dev/${i}
#done

# Give more permissions to sysfs for now
#########################

echo PATH is $EXTOLL_R2_SYSFS
cd $EXTOLL_R2_SYSFS && chmod 666 *
#done changing rf permissions

#deactivate CPU frequency scaling
cd /sys/devices/system/cpu
if [ -e cpu0/cpufreq/scaling_governor ] ; then
for i in cpu{0..9}* ; do
echo "performance"> $i/cpufreq/scaling_governor ; done
fi

#cd $EXTOLL_R2_SYSFS 
#for i in {0..6} ; do echo 0x7fff00000000 > extoll_rf_nw_phy_rf_link${i}_rf_rcompValue ; done
#for j in {0..6} ; do for i in {0..40}; do echo 0x4000000 > extoll_rf_nw_phy_rf_link${j}_rf_rcompCsr ; done ; done

#set the NB watchdog disble bit in the function 3, reg 44, bit 8 (note this is a hack of course)
#setpci -s 00:18.3 44.l=4a70015c
#setpci -s 00:19.3 44.l=4a70015c



