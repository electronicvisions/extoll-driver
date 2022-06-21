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

## Using Sysfs driver generator based on version from 29/12/11
gen_path=../../building_blocks/rfdrvgen_rfs/tags/291211

## Display instructions for new complete compilation
if [[ ! -e "${gen_path}/sysfs_gen" ]] 
then
    echo "The Sysfs driver generator executable does not exists in ${gen_path}. I will compile it"
    echo "Remember that I only generate code, so you can run me from any machine (for example one on which the generator compiles)"
    echo "-> In case of compilation failure, just re-run me on another machine (like your desktop one)"
    
fi

## Compile (will update exe on svn update for example)
make -C $gen_path all

if [[ -e "${gen_path}/sysfs_gen" ]] 
then
    
    ${gen_path}/sysfs_gen ../../../hw/extoll_r2_targets//stratix5_128/register_file/output/extoll_rf.anot.xml
    cp -v output/*.h .
    cp -v output/*.c .
    cp -v output/*.tcl .
    cp -v output/*.py .
    rm -rf output
    exit 0
    
else
    
    echo "Sysfs driver generator executable not found in ${gen_path}. Check for any compilation error above"
    exit -1
fi


