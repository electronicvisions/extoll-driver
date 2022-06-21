# frist draft of the makefile, copied from linux device drivers 3rd ed.
# 2005 o'relly

# To build modules outside of the kernel tree, we run "make"
# in the kernel source tree; the Makefile these then includes this
# Makefile once again.
# This conditional selects whether we are being included from the
# kernel Makefile or not.

# path to parent folders of modules which export symbols we want to use
# should be relative to the directory of this Makefile
EXTRA_MODULES = ../Module.symvers

ifeq ($(KERNELRELEASE),)

    # Assume the source tree is where the running kernel was built
    # You should set KERNELDIR in the environment if it's elsewhere
    KERNELDIR ?= /lib/modules/$(shell uname -r)/build
    # The current directory is passed to sub-makes as argument
    PWD := $(shell pwd)

modules:
	$(MAKE) -C $(KERNELDIR) KBUILD_EXTRA_SYMBOLS=$(PWD)/$(EXTRA_MODULES) M=$(PWD) modules

#modules_install:
#	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.symvers

.PHONY: modules modules_install clean

else
	
# Enable Debugging
DEBUG=y

ifeq ($(DEBUG),y)
DBGFLAGS = -O -g -DDEBUG
else
DBGFLAGS = -O
endif
EXTRA_CFLAGS += $(DBGFLAGS) -std=gnu99

# called from kernel build system: just declare what our modules are
 obj-m := velo_send_one_msg.o velo_recv_one_msg.o test_nla.o test_kapi_ping.o test_kapi_pong.o test_kapi.o rma_irq_send.o rma_irq_recv.o velo_fill_bq_send.o velo_fill_bq_recv.o rma_print_noti.o #rra.o

#obj-m := test_nla.o 
endif

