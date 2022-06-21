#!/bin/bash

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

# Sync folder structure and files needed for drivers/script interfaces to work into root folder
basedir=/root/`id -nu`/extoll_r2_driver/

# extoll_env
# drivers
# script interfaces
#rsync -avzrC -e "ssh -l root"  ../extoll_env.bash ../extoll2_drv ../script `hostname`:/root/extoll_r2_driver/
rsync -avzrC -e "ssh -l root" *.ko `hostname`:${basedir}
