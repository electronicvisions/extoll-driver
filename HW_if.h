/*
  Here goes all the global data and funciton calls provided by the extoll framework.
  This is for illistration only and should be replaced by Extoll internal equivalents if existing
*/
#ifndef _EXTOLL_IF_H_
#define _EXTOLL_IF_H_

#include "arch_define.h"

/* A modified printk */

#ifndef PrintLine
#define PrintLine(...) _PrintLine(__FILE__,__LINE__, __VA_ARGS__)
static inline void _PrintLine(char *File, uint32_t Line, char *Format, ...)
{
  va_list args;
  va_start(args,Format);
  printk("%s:%d :  ",File,Line);	
  vprintk(Format,args);
}

#endif

#define DLDR_APT_BAR 0
#define DLDR_MMIO_BAR 4

#define PCI_VENDOR_INTEL	0x8086

#define PCI_DEVICE_ABR_2249	0x2249
#define PCI_DEVICE_ABR_224a	0x224a

#define PCI_DEVICE_KNC_2250	0x2250
#define PCI_DEVICE_KNC_2251	0x2251
#define PCI_DEVICE_KNC_2252	0x2252
#define PCI_DEVICE_KNC_2253	0x2253
#define PCI_DEVICE_KNC_2254	0x2254
#define PCI_DEVICE_KNC_2255	0x2255
#define PCI_DEVICE_KNC_2256	0x2256
#define PCI_DEVICE_KNC_2257	0x2257
#define PCI_DEVICE_KNC_2258	0x2258
#define PCI_DEVICE_KNC_2259	0x2259
#define PCI_DEVICE_KNC_225a	0x225a

#define PCI_DEVICE_KNC_225b	0x225b
#define PCI_DEVICE_KNC_225c	0x225c
#define PCI_DEVICE_KNC_225d	0x225d
#define PCI_DEVICE_KNC_225e	0x225e

#define MIC_NUM_MSIX_ENTRIES 1 /* Only one MSI per KNC. This seems to be pretty stable */
/*
  This has to be filled in by extoll describing the appertures od a single resource of a  single KNCs.
  All addresses are physical in the space of the BIC.
*/
struct resource_hw{
  uint64_t start;
  uint64_t end;
  uint64_t len;
  uint32_t flags; /* used in micscif_pci_info  to check for IORESOURCE_PREFETCH probably ok to set it*/

};


#define MAX_KNC_CNT_PER_BIC 256
//#define RESOURCES_PER_KNC   2

/* 
   structure describing a complete KNC as made accessible through extoll
*/
struct kncs_on_et{
  struct resource_hw MMIOBAR; /* apperture to reach the SBOX registers */
  struct resource_hw MemBAR;  /* apperture to access the GDDR on KNC. We may reduce the size at the risk scif buffers become inaccssible. TBD*/
#ifndef MICEXTOLL
  struct msix_entry  MsixEntries[MIC_NUM_MSIX_ENTRIES]; /* private to Pci test sublayer, can be ignored by extoll */
  struct pci_dev     *PciDev;	   /* private to Pci test sublayer, can be ignored by extoll */
#endif
  uint32_t	     MsiEnable;    /* Can be skipped. Assumption from the KNC driver is that  MSI works */ 
  uint32_t	     Id;           /* a unique number per KNC form 0 to 8 */
  unsigned short     DeviceType;   /*  Pci device type,PCI_DEVICE_KNC_2250 is good enough for the moment. */
};

/*
  strucure containing all info to be delivered by extoll 
 */
struct et_KNC_info_t{
  struct kncs_on_et KNCDescriptor[MAX_KNC_CNT_PER_BIC];
  struct device RealDevice; /* A pointer to the extoll device. Used for a sym links in the /sys/ fs. */
  uint32_t NumKNCs; /* Actual number of KNCs found by extoll */
};
/*
  Called, when the mic driver gets shot down (which rarely happens)
*/
extern void  KillHWLayer(void);
/*
Called when mic driver gets loaded. The Extoll has to populate the <KNCs> stcuture and rrgister the <IrwWrapper> interrupt handler  */
extern int InitHWLayer(struct et_KNC_info_t *KNCs,  irq_handler_t IrqWrapper);

#endif
