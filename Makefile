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
VERSION=1.1b

ifeq ($(ARCH), k1om)
EXTOLL_PATH=/extoll2_knc
else
ifndef EXTOLL_R2_HOME
EXTOLL2_PATH=/opt/extoll
EXTOLL_R2_HOME=/opt/extoll
else
EXTOLL2_PATH=$(EXTOLL_R2_HOME)
endif
endif

#INST_DIR=$(EXTOLL2_PATH)
INST_DIR=/opt/extoll
PREFIX=$(INST_DIR)
KAPI_DIR=/opt/extoll/kapi
HOSTNAME=$(shell hostname)

FILE_LIST=atu2_drv.c extolldrv.c extoll_kapi.c extoll_rf_access.c extoll_rf_sysfs_galibier128.c extoll_rf_sysfs_stratixV.c  extoll_rf_sysfs_ventoux64.c extoll_rf_user_tourmalet.c micextoll.c rma2drv.c velo2drv.c \
exn.c extoll_bq.c extoll_knc_virt.c extoll_rf_sysfs.c extoll_rf_sysfs_galibier64.c extoll_rf_sysfs_tourmalet.c extoll_rf_user.c extoll_rf_user_ventoux64.c pmap.c smfu2drv.c \
arch_define.h extoll_rf_sysfs_galibier64.h extoll_rf_sysfs_ventoux64.h HW_if.h rma2_ioctl.h snq_decl_galibier128.h snq_decl_tourmalet.h snq_pram.h velo2drv.h \
atu2_drv.h extoll_kapi.h extoll_rf_sysfs.h extoll_rf_user.h micextoll.h rma2_region.h snq_decl_galibier64.h snq_decl_ventoux64.h snq_pram_stratix128.h velo2_ioctl.h \
extoll_bq.h extoll_kernel.h extoll_rf_sysfs_stratixV.h extoll_rf_user_tourmalet.h pmap.h smfu2drv.h snq_decl.h snq_pram_galibier128.h snq_pram_tourmalet.h velo2_mod.h \
extolldrv.h extoll_rf_sysfs_galibier128.h extoll_rf_sysfs_tourmalet.h extoll_rf_user_ventoux64.h rma2drv.h smfu2_ioctl.h snq_decl_stratix128.h  snq_pram_galibier64.h snq_pram_ventoux64.h \
Makefile Makefile_BNC Makefile.extoll2_drv.dist Makefile_KNC \
deep_compile_bnc.sh dump_kapi_test.sh extoll_env_mic.sh extoll_load_small.sh install_root_folder.sh micextoll_load.sh  set_micextoll_load.sh smfu_configure-emmio.sh smfu_debug.sh \
deep_compile_host.sh extoll_bringup_load.sh extoll_load.sh extoll_unload.sh micextoll_unload.sh set_micextoll_modulparameter.sh smfu_configure.sh extoll_env.bash dump_ecc_regs.sh



EXTRA_MODULES = Module.symvers
DOXYGEN = doxygen
DOXYFILE = doxyfile
HEADFILES = extoll_kapi.h
DOCDIR = doc

# Enable Debugging
 DEBUG=y

ifeq ($(DEBUG),y)
DBGFLAGS = -O -g -DDEBUG
else
DBGFLAGS = -O
endif
#EXTRA_CFLAGS += $(DBGFLAGS) -std=gnu99 -Wall
#EXTRA_CFLAGS += -std=gnu99 -Wall


#define object file for individual modules
extoll-objs := extolldrv.o
velo2-objs  := velo2drv.o
extoll2_bq-objs := extoll_bq.o
smfu2-objs := smfu2drv.o
rma2-objs := rma2drv.o
atu2-objs := atu2_drv.o
#exn-objs := exn.o
#exnnapi-objs := exn_napi.o
virt-objs := extoll_knc_virt.o

#pmap-objs := pmap.o
#define modules

#set-up kernel stuff
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD       := $(shell pwd)

all: modules

ventoux64:
	cp extoll_rf_sysfs_ventoux64.c extoll_rf_sysfs.c
	cp extoll_rf_sysfs_ventoux64.h extoll_rf_sysfs.h
	rm -f snq_pram.h snq_decl.h

	ln -s snq_pram_ventoux64.h snq_pram.h 
	ln -s snq_decl_ventoux64.h snq_decl.h

galibier64:
	cp extoll_rf_sysfs_galibier64.c extoll_rf_sysfs.c
	cp extoll_rf_sysfs_galibier64.h extoll_rf_sysfs.h
	rm -f snq_pram.h snq_decl.h
	ln -s snq_pram_galibier64.h snq_pram.h 
	ln -s snq_decl_galibier64.h snq_decl.h 

galibier128:
	cp extoll_rf_sysfs_galibier128.c extoll_rf_sysfs.c
	cp extoll_rf_sysfs_galibier128.h extoll_rf_sysfs.h
	rm -f snq_pram.h snq_decl.h
	ln -s snq_pram_galibier128.h snq_pram.h
	ln -s snq_decl_galibier128.h snq_decl.h

stratix128:
	cp extoll_rf_sysfs_stratixV.c extoll_rf_sysfs.c
	cp extoll_rf_sysfs_stratixV.h extoll_rf_sysfs.h
	rm -f snq_pram.h snq_decl.h
	ln -s snq_pram_stratix128.h snq_pram.h 
	ln -s snq_decl_stratix128.h snq_decl.h 

tourmalet:
	cp extoll_rf_sysfs_tourmalet.c extoll_rf_sysfs.c
	cp extoll_rf_sysfs_tourmalet.h extoll_rf_sysfs.h
	rm -f snq_pram.h snq_decl.h
	ln -s snq_pram_tourmalet.h snq_pram.h 
	ln -s snq_decl_tourmalet.h snq_decl.h 

	
#ifeq ($(ARCH), k1om)
#obj-m   := micextoll.o extoll_bq.o velo2.o extoll.o extoll_rf_sysfs.o smfu2.o rma2.o pmap.o extoll_rf_access.o atu2.o extoll_kapi.o exn.o
#else
obj-m	:= extoll_bq.o velo2.o extoll.o extoll_rf_sysfs.o smfu2.o rma2.o pmap.o extoll_rf_access.o atu2.o extoll_kapi.o exn.o extoll_knc_virt.o
#test_kapi_ping.o test_kapi_pong.o test_kapi.o
#endif

#CFLAGS_test_kapi_ping.o = -O0 
#CFLAGS_test_kapi_pong.o = -O0 
#
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.symvers .*o.d

distclean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.symvers .*o.d extoll_rf_sysfs_ventoux64.c extoll_rf_sysfs_galibier64.c extoll

install_kapi:
	install *.ko $(KAPI_DIR)
	install *.sh $(KAPI_DIR)
	install *.py $(KAPI_DIR)

install_root_folder:
	./install_root_folder.sh

install: modules
	$(MAKE) -C $(KERNELDIR) M=$(PWD) INSTALL_MOD_DIR=extra/extoll modules_install
	depmod -a
#	@echo "Installing Extoll2 Driver to $(PREFIX)"
#	install -d $(PREFIX)
#	install -d $(PREFIX)/include
#	install -d $(PREFIX)/sbin
#	install -d $(KAPI_DIR)
#	install *.ko $(PREFIX)/sbin
#	install *.sh $(PREFIX)/sbin
#	install  *.ko $(KAPI_DIR)
#	install  *.sh $(KAPI_DIR)
#	install arch_define.h velo2_ioctl.h velo2_mod.h velo2drv.h rma2_region.h rma2_ioctl.h rma2drv.h pmap.h smfu2_ioctl.h smfu2drv.h extolldrv.h extoll_bq.h HW_if.h atu2_drv.h extoll_kapi.h extoll_kernel.h extoll_rf_sysfs.h extoll_kernel_version_compability_layer.h $(PREFIX)/include
#	cp extoll_env.bash.swdev $(PREFIX)/extoll_env.bash
#	install extoll_env.bash $(PREFIX)

dist:
	@echo "Building dist tarball"
	tar czpf extoll_driver_${VERSION}.tgz ${FILE_LIST}

@PHONY: all clean dist
