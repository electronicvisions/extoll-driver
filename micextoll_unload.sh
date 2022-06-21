#!/bin/sh
#  This file is part of the  Linux Kernel Driver Package for EXTOLL R2.
#
#  Copyright (C) 2011 EXTOLL GmbH
#
#  Written by Richard Leys (2011)
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

# invoke rmmod with all arguments we got

#for module in  exn extoll_kapi rma2 atu2 smfu2 velo2 extoll_bq pmap extoll_rf_access extoll micextoll extoll_rf_sysfs ; do #limic
for module in  exn extoll_kapi rma2 atu2 smfu2 velo2 extoll_bq pmap extoll_rf_access extoll micextoll extoll_rf_sysfs ; do #limic
	rmmod $module.ko ;
done

# Remove stale nodes
rm -f /dev/rma*
rm -f /dev/velo*
rm -f /dev/smfu2*
