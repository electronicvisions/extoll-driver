#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/fs.h>
#include <linux/major.h>
#include <linux/blkdev.h>
#include <linux/capability.h>
#include <linux/uio.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/mutex.h>
#include <linux/spinlock.h>
#include <linux/pci.h>
#include <linux/version.h>
#include <asm/io.h>
#include <asm/ioctl.h>
#include <asm/uaccess.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/rtnetlink.h>
#include <net/rtnetlink.h>
#include <linux/pm.h>
#include <linux/notifier.h>
#include <linux/suspend.h>
#include <linux/ctype.h>
#include <linux/sysfs.h>
#include "arch_define.h"

#ifdef DEEP_HOST

// Include Header for special structs so the wrapper can be called
#include "HW_if.h"
// Include EXTOLL header files
#include "extolldrv.h"
#include "extoll_rf_sysfs.h"


// Define module parameters. Needed to calculate the mapped SMFU stuff.
static int knc_size = 16;
module_param(knc_size, int, 0);
MODULE_PARM_DESC(knc_size, "Size of the connected KNC. Default value: 16 GB.\n");

static int num_kncs = 1;
module_param(num_kncs, int, 0);
MODULE_PARM_DESC(num_kncs, "Number of connected KNCs. Default value: 1. Max value: 16.\n");


// Define some needed structures for the dummy PCIe driver.
struct et_KNC_info_t *KNCInfo; 


int InitHWLayer(struct et_KNC_info_t *KNCs,  irq_handler_t IrqWrapper) {
	struct pci_dev *pdev = extoll_get_pdev();
	int i = 0, j = 0;
	struct kncs_on_et * CurKnc;
	uint64_t smfu_paddr = (uint64_t)extoll_get_smfu_addr();
	uint64_t mmio_base = (uint64_t)extoll_get_bar0_addr();
        char* sbox;
        uint32_t* reg;
	uint64_t mmiolen = 131072;
	//uint64_t membarlen = 8589934592; //8GB
	uint64_t membarlen = 17179869184;   // 16GB
	
	PrintLine("InitHWLayer: Called extoll_knc_virt to map SMFU to KNC.\n");
	printk("<1>MIC: Used SMFU Addr: %016llx\n", smfu_paddr);
	
	KNCInfo=KNCs;
	
	KNCInfo->RealDevice = pdev->dev;
	KNCs->NumKNCs = num_kncs;
	
	for(i = 0; i < num_kncs; i++){
		CurKnc = &(KNCInfo->KNCDescriptor[i]);
		CurKnc->Id = i;
		CurKnc->DeviceType = PCI_DEVICE_KNC_225c;
		
		CurKnc->MemBAR.start = smfu_paddr;
		CurKnc->MemBAR.end   = smfu_paddr + membarlen - 1;
		CurKnc->MemBAR.len   = membarlen;
		
		CurKnc->MMIOBAR.start= mmio_base + ((i) * mmiolen);
		CurKnc->MMIOBAR.end  = mmio_base + ((i+1) * (mmiolen)) - 1;
		CurKnc->MMIOBAR.len  = mmiolen;
		
		for (j = 0; j < MIC_NUM_MSIX_ENTRIES; j++)
			CurKnc->MsixEntries[i].entry = i;

		smfu_paddr = CurKnc->MemBAR.end + 1;
		
		sbox = ioremap_nocache(CurKnc->MMIOBAR.start,CurKnc->MMIOBAR.len);
	        printk("ioremapped sbox to %p\n",sbox);
	        if (!sbox) {
		        printk("error mapping sbox to configure MSI-X. OOps\n");
		} else {
		        printk("configuring MSI-X vector 0\n");
			reg = (uint32_t*) (sbox+0x17000);
		        //*reg = 0xfee00098;
			*reg = 0x00000000;
		        printk("wrote lower addr of %x to %p\n",*reg,reg);
			reg = (uint32_t*) (sbox+0x17004);
		        //*reg = 0x0;
                        *reg = 0xfd;
		        printk("wrote upper addr of %x to %p\n",*reg,reg);
			reg = (uint32_t*) (sbox+0x17008);
		        *reg = 0x0;
		        printk("wrote message of %x to %p\n",*reg,reg);
			reg = (uint32_t*) (sbox+0x1700C);
		        *reg = 0x0;
		        printk("wrote vector control of %x to %p\n",*reg,reg);
		        iounmap(sbox);
		}
	}	
	
	set_extoll_dummyWrapper(IrqWrapper);
	
	return 0;
}
EXPORT_SYMBOL(InitHWLayer);


void  KillHWLayer(void) {
	extoll_clean_dummyWrapper();
}
EXPORT_SYMBOL(KillHWLayer);

#endif

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sarah Neuwirth sarah.neuwirth@ziti.uni-heidelberg.de");
MODULE_DESCRIPTION("Module is used to map SMFU to KNC in DEEP setup.");
MODULE_VERSION("1.5");
