#!/usr/bin/env bash
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

set -e

load_from_path() {
    THIS_SCRIPT_DIR=$1
    
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
        /sbin/insmod ${THIS_SCRIPT_DIR}/smfu2.ko smfu2_en_write_combining=0 $*
        #/sbin/insmod  ${THIS_SCRIPT_DIR}/limic.ko
        /sbin/insmod  ${THIS_SCRIPT_DIR}/extoll_kapi.ko
        /sbin/insmod ${THIS_SCRIPT_DIR}/extoll_rf_access.ko
       
        /sbin/insmod ${THIS_SCRIPT_DIR}/exn.ko
    fi
}

set_device_permissions() {
    devices="velo2 smfu2 rma2 pmap extoll_rf_access"
    mode="666"

    for i in $devices ; do

        # Group: since distributions do it differently, look for wheel or use staff
        if grep -q '^extoll:' /etc/group; then
            group="extoll"
        else
            group="root"
        fi

        # give appropriate group/permissions, and change the group.
        # Not all distributions have staff, some have "wheel" instead.
        chgrp $group /dev/extoll/${i}
        chmod $mode /dev/extoll/${i}
    done
}

load_system_modules() {
    modules="exn extoll_rf_access pmap"
    for module in $modules ; do
        modprobe --first-time ${module}
        if [[ $? -ne 0 ]] ; then 
            exit 
        fi
    done 
}

print_usage() {
    echo "Load extoll driver. Usage: extoll_load.sh [-f /path/to/modules/]"
    echo "No parameter is given: installed driver via modprobe."
    echo "Paramter -f: load modules from given path."
}

if [[ $# -eq 0 ]]  ; then
    load_system_modules
    set_device_permissions
    echo "Loaded driver from system install"
elif [[ $# -eq 2 && $1 -eq "-f" ]] ; then
    MODULES_PATH=$2
    load_from_path $MODULES_PATH
    set_device_permissions
    echo "Loaded driver from path $MODULES_PATH"
else
    print_usage
fi

#deactivate CPU frequency scaling
#cd /sys/devices/system/cpu
#if [ -e cpu0/cpufreq/scaling_governor ] ; then
#for i in cpu{0..9}* ; do
#echo "performance"> $i/cpufreq/scaling_governor ; done
#fi

#cd $EXTOLL_R2_SYSFS 
#for i in {0..6} ; do echo 0x7fff00000000 > extoll_rf_nw_phy_rf_link${i}_rf_rcompValue ; done
#for j in {0..6} ; do for i in {0..40}; do echo 0x4000000 > extoll_rf_nw_phy_rf_link${j}_rf_rcompCsr ; done ; done

#set the NB watchdog disble bit in the function 3, reg 44, bit 8 (note this is a hack of course)
#setpci -s 00:18.3 44.l=4a70015c
#setpci -s 00:19.3 44.l=4a70015c



