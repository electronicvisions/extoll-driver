#ifndef _EXTOLL_KERNEL_VERSION_COMPABILITY_LAYER_
#define _EXTOLL_KERNEL_VERSION_COMPABILITY_LAYER_

#include <linux/version.h>
#include <linux/netdevice.h>
#include <linux/mm.h>
#include <linux/pci.h>

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4,9,0) && !defined RHEL_MAJOR) 
static inline long EKVCL_get_user_pages_remote(struct task_struct *tsk, struct mm_struct *mm, 
				unsigned long start, unsigned long nr_pages, 
				int write, int force, struct page **pages, 
				struct vm_area_struct **vmas) 
{
	unsigned int gup_flags = 0;
	if(write) gup_flags = gup_flags ^ FOLL_WRITE;
	if(force) gup_flags = gup_flags ^ FOLL_FORCE;

	return get_user_pages_remote(tsk, mm, start, nr_pages, gup_flags,  pages, vmas);
}
#elif (LINUX_VERSION_CODE >= KERNEL_VERSION(4,6,0) && (LINUX_VERSION_CODE < KERNEL_VERSION(4,9,0)) && !defined RHEL_MAJOR) || (defined RHEL_MAJOR && RHEL_MAJOR <= 7 && defined RHEL_MINOR && RHEL_MINOR >= 5)

static inline long EKVCL_get_user_pages_remote(struct task_struct *tsk, struct mm_struct *mm, 
				unsigned long start, unsigned long nr_pages, 
				int write, int force, struct page **pages, 
				struct vm_area_struct **vmas) 
{
	return get_user_pages_remote(tsk, mm, start, nr_pages, write, force,  pages, vmas);
}
#elif (LINUX_VERSION_CODE < KERNEL_VERSION(4,6,0) && !defined RHEL_MAJOR) || (defined RHEL_MAJOR && RHEL_MAJOR <= 7 && defined RHEL_MINOR && RHEL_MINOR < 5)
static inline long EKVCL_get_user_pages_remote(struct task_struct *tsk, struct mm_struct *mm, 
				unsigned long start, unsigned long nr_pages, 
				int write, int force, struct page **pages, 
				struct vm_area_struct **vmas) 
{
	return get_user_pages(tsk, mm, start, nr_pages, write, force, pages, vmas);
}
#endif

#if LINUX_VERSION_CODE <= KERNEL_VERSION(3,14,0)
	#define EKVCL_pci_msi_vec_count(devp) 1
#else
 #define EKVCL_pci_msi_vec_count(devp) pci_msi_vec_count(devp)
#endif

#if LINUX_VERSION_CODE <= KERNEL_VERSION(3,5,0)
 #define EKVCL_dev_info_ratelimited(args...) { if (printk_ratelimit()) dev_info(args); }
 #define EKVCL_get_uid_val(u) (u)
#else
 #define EKVCL_dev_info_ratelimited(args...) dev_info_ratelimited(args)
 #define EKVCL_get_uid_val(u) (u).val
#endif

#if LINUX_VERSION_CODE <= KERNEL_VERSION(3,3,0)
#define EKVCL_umode_t mode_t
#else
#define EKVCL_umode_t umode_t
#endif

#if LINUX_VERSION_CODE <= KERNEL_VERSION(3,1,0)
/*
 *  *  pcie_get_mps - get PCI Express maximum payload size
 *   *  @dev: PCI device to query
 *    * 
 *     *  Returns maximum payload size in bytes
 *      **/
static inline int EKVCL_pcie_get_mps(struct pci_dev *dev)
{
      u16 ctl;

      //pcie_capability_read_word(dev, PCI_EXP_DEVCTL, &ctl);
		  pci_read_config_word(dev,pci_pcie_cap(dev) + PCI_EXP_DEVCTL,&ctl);
		  return 128 << ((ctl & PCI_EXP_DEVCTL_PAYLOAD) >> 5);
}
#else
static inline int EKVCL_pcie_get_mps(struct pci_dev *dev)
{
	  return pcie_get_mps(dev);
}

#endif	

/*
 * The functions mtrr_add and mtrr_del do not get exported on recent kernels, instead arch_phys_wc_add
 * and arch_phys_wc_del have to be used. They seem to have been introduced in kernel 3.11, although
 * they also exist in the 3.10 kernel provided by CentOS 7.
 */
#if LINUX_VERSION_CODE <= KERNEL_VERSION(3,10,0)
#include <asm/mtrr.h>

static inline int EKVCL_mtrr_add(unsigned long base, unsigned long size, unsigned int type, bool increment)
{
	return mtrr_add(base, size, type, increment);
}
static inline void EKVCL_mtrr_del(int reg, unsigned long base, unsigned long size)
{
	mtrr_del(reg, base, size);
}
#else
#include <asm/io.h>

static inline int EKVCL_mtrr_add(unsigned long base, unsigned long size, unsigned int type, bool increment)
{
	return arch_phys_wc_add(base, size);
}
static inline void EKVCL_mtrr_del(int reg, unsigned long base, unsigned long size)
{
	arch_phys_wc_del(reg);
}
#endif

//Network device driver kernel api differences
#if defined RHEL_MAJOR && RHEL_MAJOR >= 7 && defined RHEL_MINOR && RHEL_MINOR >= 4 || LINUX_VERSION_CODE >= KERNEL_VERSION(3,18,0) 
 #define EKVCL_update_trans_start(dev, jiffies)
#else
 #define EKVCL_update_trans_start(dev, jiffies) dev->trans_start=jiffies
#endif

#if defined RHEL_MAJOR && RHEL_MAJOR >= 7 && defined RHEL_MINOR && RHEL_MINOR >= 5
 #define EKVCL_NDO_CHANGE_MTU .ndo_change_mtu_rh74 = exn_change_mtu
#else
 #define EKVCL_NDO_CHANGE_MTU .ndo_change_mtu = exn_change_mtu
#endif


#if LINUX_VERSION_CODE <= KERNEL_VERSION(3,16,0)
#define EKVCL_alloc_netdev(sizeof_priv, name, name_assign_type, setup) alloc_netdev(sizeof_priv, name, setup)
#else
#define EKVCL_alloc_netdev(sizeof_priv, name, name_assign_type, setup) alloc_netdev(sizeof_priv, name, name_assign_type, setup)
#endif

#if LINUX_VERSION_CODE <= KERNEL_VERSION(3,16,0)
#define EKVCL_PAGE_CACHE_MODE_WC _PAGE_CACHE_WC
#define EKVCL_PAGE_CACHE_MODE_WB _PAGE_CACHE_WB
#else
#define EKVCL_PAGE_CACHE_MODE_WC _PAGE_CACHE_MODE_WC
#define EKVCL_PAGE_CACHE_MODE_WB _PAGE_CACHE_MODE_WB
#endif

#endif /*_EXTOLL_KERNEL_VERSION_COMPABILITY_LAYER_*/
