#!/bin/sh
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

MODUL_DIR="/lib/modules/2.6.38.8-g32944d0"
# If EXTOLL_R2_HOME is not set, source environement setup
# env setup defines in env the paths to sw home directory, device directory, sysfs directory etc...
# Everything that is needed to have a base dataset describing where devices are and so on
#if [ -z $EXTOLL_R2_HOME ] 
#then
	
 # echo "Sourcing extoll_env.bash (MUST be in parent directory of this script"
  #. ${THIS_SCRIPT_DIR}/../extoll_env.bash

#fi

# invoke insmod with all arguments we got
# and use a pathname, as newer modutils don't look in . by default
/sbin/insmod ${MODUL_DIR}/extoll_rf_sysfs.ko $* 
/sbin/insmod ${MODUL_DIR}/micextoll.ko $*
#/sbin/insmod ${MODUL_DIR}/extoll.ko $*
#TODO 
#we have to extend this, so that the set_micextoll_modulparameter.sh script can set the right values
#/sbin/insmod #${MODUL_DIR}/extoll.ko micextoll_resource_start0= micextoll_resource_len0= micextoll_resource_start2= micextoll_resource_len2= micextoll_resource_start4= micextoll_resource_len4= $*
/sbin/insmod ${MODUL_DIR}/extoll.ko micextoll_resource_start0=0xFE20000000 micextoll_resource_start2=0xFE10000000 micextoll_resource_start4=0xFE00000000 micextoll_micbase0=0x3c1c00000000 micextoll_miclen0=0x200000000 extoll_physical_bar0_addr=0x3C1E20000000 extoll_physical_bar2_addr=0x3C1E10000000 extoll_rf_snq_rf_irq_0_param=0xFBE1AA0840002d extoll_rf_snq_rf_irq_2_param=0xF000002061 $*

returnvalue=$?

if [ "$returnvalue" -eq "1" ] ; then
 echo "Loading extoll.ko failed. No device?"
 /sbin/rmmod  ${MODUL_DIR}/extoll.ko
 /sbin/rmmod  ${MODUL_DIR}/micextoll.ko
 /sbin/rmmod  ${MODUL_DIR}/extoll_rf_sysfs.ko
 exit
else
 /sbin/insmod ${MODUL_DIR}/extoll_bq.ko $*
 /sbin/insmod ${MODUL_DIR}/velo2.ko VELO2_MIN_VPID=0 $* #FIXME; only if you want to use Extoll with MIC in a host System for debugging
# /sbin/insmod ${THIS_SCRIPT_DIR}/limic.ko
 /sbin/insmod ${MODUL_DIR}/atu2.ko
 /sbin/insmod ${MODUL_DIR}/rma2.ko
 /sbin/insmod ${MODUL_DIR}/pmap.ko
 /sbin/insmod ${MODUL_DIR}/extoll_rf_access.ko
 /sbin/insmod ${MODUL_DIR}/smfu2.ko smfu2_en_write_combining=0 $*
# /sbin/insmod  ${MODUL_DIR}/limic.ko
 /sbin/insmod ${MODUL_DIR}/extoll_kapi.ko
# /sbin/insmod ${MODUL_DIR}/exn.ko
fi

#devices="velo2 smfu2 limic rma2 pmap extoll_rf_access"
devices="velo2 smfu2 rma2 pmap extoll_rf_access"
mode="666"

for i in $devices ; do

 # remove stale nodes
 rm -f /dev/${i}*
 # create nodes
 major=$(awk "\$2==\"$i\" {print \$1}" /proc/devices)
 mknod /dev/${i} c $major 0
 
 # Group: since distributions do it differently, look for wheel or use staff
 if grep -q '^staff:' /etc/group; then
     group="staff"
 else
     group="root"
 fi

 # give appropriate group/permissions, and change the group.
 # Not all distributions have staff, some have "wheel" instead.
 chgrp $group /dev/${i}
 chmod $mode /dev/${i}
done

echo "EXTOLL_load done"

# Give more permissions to sysfs for now
#########################

#echo PATH is $EXTOLL_R2_SYSFS
#cd $EXTOLL_R2_SYSFS && chmod 666 *
#done changing rf permissions

#deactivate CPU frequency scaling
#cd /sys/devices/system/cpu
#for i in cpu? ; do
#echo "performance"> $i/cpufreq/scaling_governor ; done

#set the NB watchdog disble bit in the function 3, reg 44, bit 8 (note this is a hack of course)
#setpci -s 00:18.3 44.l=4a70015c
#setpci -s 00:19.3 44.l=4a70015c



