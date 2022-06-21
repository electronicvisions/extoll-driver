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

THIS_SCRIPT_DIR="$(dirname "$(readlink -f ${BASH_SOURCE[0]})")"

# If EXTOLL_R2_HOME is not set, source environement setup
# env setup defines in env the paths to sw home directory, device directory, sysfs directory etc...
# Everything that is needed to have a base dataset describing where devices are and so on
if [ -z $EXTOLL_R2_HOME ] 
then
	
  echo "Sourcing extoll_env.bash (MUST be in parent directory of this script"
  . ${THIS_SCRIPT_DIR}/../extoll_env.bash

fi

# Commented out from richard : what was that for ?
#cd $EXTOLL_R2_HOME/sbin

# switch on write combining - > performance!!
#echo "base=0xf8000000 size=0x2000000 type=write-combining" >| /proc/mtrr
#echo "base=0x80000000 size=0x80000000 type=write-combining" >| /proc/mtrr

# invoke insmod with all arguments we got
# and use a pathname, as newer modutils don't look in . by default
/sbin/insmod ${THIS_SCRIPT_DIR}/extoll_rf_sysfs.ko $* 
/sbin/insmod ${THIS_SCRIPT_DIR}/extoll.ko $* 

# Give more permissions to sysfs for now
#########################

echo PATH is $EXTOLL_R2_SYSFS
cd $EXTOLL_R2_SYSFS
chmod 666 *
#done changing rf permissions

#deactivate CPU frequency scaling
cd /sys/devices/system/cpu
for i in cpu? ; do
echo "performance"> $i/cpufreq/scaling_governor ; done

#set the NB watchdog disble bit in the function 3, reg 44, bit 8 (note this is a hack of course)
#setpci -s 00:18.3 44.l=4a70015c
#setpci -s 00:19.3 44.l=4a70015c



