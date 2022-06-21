#
#  Linux Kernel Driver for the EXTOLL R2 Ventoux platform.
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

EXTOLL2_PATH=/extoll2/
INST_DIR=$(EXTOLL2_PATH)
HOSTNAME=$(shell hostname)

#define object file for individual modules
extoll-objs := extolldrv.o

obj-m	:= extolldrv.o extoll_rf_sysfs.o 

# extoll_rf_sysfs.o

#set-up kernel stuff
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD       := $(shell pwd)
ccflags-y := -std=gnu99



all: modules

#extoll_rf_sysfs.c: ../../../../hw/extoll_r2/register_file/output/extoll_rf.anot.xml
#	./generate_sysfs.sh

modules:
	$(MAKE) -C $(KERNELDIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.symvers .*o.d

install:
	install -d $(INST_DIR)
	install -d $(INST_DIR)/include
	install -d $(INST_DIR)/sbin
	install *.ko $(INST_DIR)/sbin
	install *.sh $(INST_DIR)/sbin
	install velo2_ioctl.h velo2_mod.h rma2_region.h rma2_ioctl.h pmap.h $(INST_DIR)/include

install_root_folder:
	./install_root_folder.sh


