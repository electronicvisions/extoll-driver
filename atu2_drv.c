	/*
	 *  This file is part of the  Linux Kernel Driver Package for EXTOLL R2.
	 *
	 *  Copyright (C) 2011 EXTOLL GmbH
	 *
	 *  Written by Mondrian Nuessle (2011)
	 *
	 *  This program is free software; you can redistribute it and/or modify
	 *  it under the terms of the GNU General Public License as published by
	 *  the Free Software Foundation; either version 2 of the License
	 *
	 *  This program is distributed in the hope that it will be useful,
	 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
	 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	 *  GNU General Public License for more details.
	 *
	 *  You should have received a copy of the GNU General Public License
	 *  along with this program; if not, write to the Free Software
	 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
	 */
        #define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

	#include "arch_define.h"
	#include <linux/fs.h>
	#include <linux/pci.h>
	#include <linux/list.h>
	#include <linux/init.h>
	#include <linux/cdev.h>
	#include <linux/errno.h>
	#include <linux/types.h>
	#include <linux/kernel.h>
	#include <linux/module.h>
	#include <linux/sched.h>
	#include <linux/mm.h>
	#include <linux/pagemap.h>
	#include <asm/page.h>
	#include <asm/uaccess.h>
	#include <linux/delay.h>
	#include "extoll_rf_sysfs.h"

	//enable internal definitions
	#define ATU_DRV_INT
	#include "atu2_drv.h"
	#include "extolldrv.h"
	//we need extoll_kernel.h for micextoll_micbase0
	#include "extoll_kernel.h"
	#include "extoll_kernel_version_compability_layer.h"

	extern struct device* extoll_get_device(void);

	// spinlock_t preload_lock = SPIN_LOCK_UNLOCKED;
	// unsigned long preload_flags;

	// spinlock_t find_lock = SPIN_LOCK_UNLOCKED;
	// unsigned long find_flags;

	DEFINE_MUTEX(register_mutex);	//mutex is initialized unlocked.

	//define to use fences, otherwise only notifications are used...
	//#define USE_FENCE_ONLY

//#define DEBUG(a) a
#define DEBUG(a)

	//uncomment to disable TLB flushing
	//#define DBG_NO_FLUSH

	/* define MEASURE to enable cycle analysis of registration etc */
	//#define MEASURE 

		/* #if 1  */
	/* #define rdtscll(val) do { \ */
	/*        unsigned int __a,__d; \ */
	/*        asm volatile("rdtsc" : "=a" (__a), "=d" (__d)); \ */
	/*        (val) = ((unsigned long long)__a) | (((unsigned long long)__d)<<32); \ */
	/* } while(0) */
	/* #endif */

	//#define fence(dest) asm volatile("cflush %0" : : "m"(dest))
	//"movq %0,%%rax \n movdqa %1,%%xmm0 \n movntdq %%xmm0,(%%rax)" :: "m"(dest), "m"(source))

	// default value is 128 tables max
	#define ATU2_GAT_MAX_NUM 192
	#define ATU2_MAX_VPIDS 256
	#define _FLUSH_TIMEOUT 10000000
        #define ATU2_GAT_SMALL 4
        #define ATU2_GAT_MEDIUM 12
        #define ATU2_GAT_LARGE 64
        #define ATU2_GAT_XLARGE (ATU2_GAT_MAX_NUM - ATU2_GAT_LARGE - ATU2_GAT_MEDIUM - ATU2_GAT_SMALL)
	/******************************************************************************
	*  module parameters (could be set at loadtime)			      *
	******************************************************************************/
	int atu2_gat_max_num = ATU2_GAT_MAX_NUM;	// maximum number of GAT tables
	module_param(atu2_gat_max_num, int, S_IRUGO);
	
	int atu2_gat_small = ATU2_GAT_SMALL;
	module_param(atu2_gat_small, int, S_IRUGO);
	
	int atu2_gat_medium = ATU2_GAT_MEDIUM;
	module_param(atu2_gat_medium, int, S_IRUGO);
	
	int atu2_gat_large = ATU2_GAT_LARGE;
	module_param(atu2_gat_large, int, S_IRUGO);
	
	int atu2_gat_xlarge = ATU2_GAT_XLARGE;

	int atu2_flush_timeout_us=_FLUSH_TIMEOUT;
	module_param(atu2_flush_timeout_us,int,S_IRUGO);

	int atu2_enable_preload=0;
	module_param(atu2_enable_preload,int,S_IRUGO);

	/******************************************************************************
	*  global vars                                       			      *
	******************************************************************************/
	int atu2_gat_start_small;
	int atu2_gat_end_small;
	int atu2_gat_start_medium;
	int atu2_gat_end_medium;
	int atu2_gat_start_large;
	int atu2_gat_end_large;
	int atu2_gat_start_xlarge;
	int atu2_gat_end_xlarge;
	
	static struct page* __page_list[1024*256];
        static uint64_t __atu_pp; //atu pages per machine page
	static uint64_t __registered_count;
#ifdef USE_FENCE_ONLY        
	static uint64_t __fence_count=0;
#endif        
	uint64_t* _atu_num_pages_of_vpid;
	static struct semaphore atu2_register_sem;
	//static struct semaphore atu_unregister_sem;

	atu2_notification_table_t* atu2_notification_table;
	unsigned long atu2_notification_table_paddr;

	int atu2_get_supported_vpids(void)
	{
	  return ATU2_MAX_VPIDS;
	}

	int atu2_get_max_vpids(void)
	{
	  return ATU2_MAX_VPIDS-1; //start counting with zero :-)
	}
	/* The architecture currently allows for 512 tables. We divide them up and
	give 512/32 = 2**9 / 2**5 = 2**4=16 tables to each VPID, i.e. enough for 16 GByte
	If more is required, we need a different scheme :-)

	Ok, here comes the allocation strategy:

	- if the number of pages is between one and 31, take the next free page(s) in the first gat for this VPID
	  we use the free_entries_in_1k to accelerate the search somewhat
	- if the GAT is too full, continue with the next gat
	- if the number of pages is between 32 and 1023 start with the 4th gat
	- if the number of pages is between 1024 and 256*1024-1 start with the 12th Gat
	- if the number of pages is larger 256k pages give the 16th gat
	- if all this does not apply, or the GATs are used, return with an error :-)

	*/
	static atu2_gat_table_t* gat_tables; //global management array of gat tables, Not all have to be valid though!

	/* {{{ find_free_entries - util function */

	//returns the 0 on success, -1 otherwise
	static int find_free_entries(int vpid, int num_pages, int* gat_idx, int* gate_idx)
	{
	  int i=0,j=0;
	  int idx=0,c=0;
	  int found=0;
	  int start_gat_idx=0,end_gat_idx=0;
	  atu2_gat_table_t* base = gat_tables; //&(gat_tables[vpid*gat_per_vpid]);
	  int buckets=0;
	  int match=0;
	  int bucket_start;
	  int num_gats;
	  int gat_match;
	  
	  if (vpid>atu2_get_max_vpids())
	    {
	      pr_alert("Registering for VPID %u, but only %u vpids are supported. Consider increasing the atu_gat_num module parameter.\n",
		    vpid, ATU2_MAX_VPIDS);
	      return -ENOMEM;
	    }
	  
	  // spin_lock_irqsave(&find_lock, find_flags);
	  
	  pr_debug("find_free_entries for vpid %u for %u pages called.\n", vpid, num_pages);
	  if (num_pages<32)
	    {
	      pr_debug("%der group\n",atu2_gat_start_small);
	      start_gat_idx=atu2_gat_start_small;
	      end_gat_idx=atu2_gat_end_small;
	    }
	  else if (num_pages<1024)
	    {
	      pr_debug("%der group\n",atu2_gat_start_medium);
	      start_gat_idx=atu2_gat_start_medium;
	      end_gat_idx=atu2_gat_end_medium;
	    }
	  else if (num_pages<256*1024)
	    {
	      pr_debug("%der group\n",atu2_gat_start_large);
	      start_gat_idx=atu2_gat_start_large;
	      end_gat_idx=atu2_gat_end_large;
	    }
	  else if (num_pages<atu2_gat_xlarge*256*1024)
	    {
	      pr_debug("%der group\n",atu2_gat_start_xlarge);
	      start_gat_idx=atu2_gat_start_xlarge;	
	      end_gat_idx= atu2_gat_end_xlarge;
	    }
	  else
	    {
	      pr_alert("Registering, too many pages at once requested!\n");
	      //spin_unlock_irqrestore(&find_lock, find_flags);
	      return -ENOMEM;
	    }

	  if (num_pages<=1024)
	    {
	      for (i=start_gat_idx;i<=end_gat_idx;i++) 
		{
		  pr_debug("looking at table %i of vpid %i \n",i,vpid);
		  for (j=0;j<256;j++) //traverse the lookup-level
		    {             
		      if (base[i].free_entries_in_1k[j]>=num_pages)
			{
			  pr_debug("in group %d enough free pages..\n",j);
			  idx=j*1024; //start entry
			  bucket_start=idx; //remember bucket start, so we know when we come to then end of the bucket
			  while (found==0)
			    {					  
			      while (idx+num_pages<bucket_start+1024 && base[i].entries[idx].value!=0) idx++; //find first free entry
			      if (idx+num_pages>bucket_start+1024) {
				pr_debug("break the loop at idx %u...\n",idx);
				break; //break while loop and continue with for loop -> next bucket
			      }
			      for (c=0;c<num_pages;c++)
				{
				  if (base[i].entries[idx+c].value!=0)
				    break;
				}
			      if (c!=num_pages) 
			      {
				pr_debug("VPID: %d continue with next chunk. now table %d, search start at %d, length is %d, bucket is %d\n",vpid, i,idx,num_pages, j);
				idx+=num_pages; //this chunk has just been checked, so jump over it
				if (idx+num_pages>bucket_start+1024) break; //break while loop and continue with for loop -> next bucket
				continue; //not enough entries in a row...
			      }
			      else {
				found=1;
				pr_debug("found is one, extiting while loop\n");
			      }
			    pr_debug("end of while loop\n");
			    }
			  if (found==1)
			    {
			      *gat_idx=/*vpid*gat_per_vpid+*/i;
			      *gate_idx=idx;
			      //gat_tables[gat_idx].free_entries_in_1k[gate_idx/1024]-=npages;
			      pr_debug("find_free_entries returns successfully\n");
			      //spin_unlock_irqrestore(&find_lock, find_flags);
			      return 0;
			    }
			}
		    }
		}
	      pr_alert("error in find_free_entries for vpid %u.\n", vpid);
	      pr_alert("registering of %u pages failed: not enough room in table buckets.\n",num_pages);
	      //spin_unlock_irqrestore(&find_lock, find_flags);
	      return -ENOMEM;
	    }
	  else if (num_pages > 1024 && num_pages < 256*1024) //not enough room in one bucket for this!
	    {
	      buckets=num_pages/1024;
	      if ( (num_pages%1024)!=0) buckets++;
	      pr_debug("Looking for %d buckets for %d pages\n", buckets, num_pages);
	      for (i=start_gat_idx;i<=end_gat_idx;i++) 
		{
		  pr_debug("looking at table %i of vpid %i \n",i,vpid);
		  for (j=0;j<256-buckets;j++) //traverse the lookup-level
		    {
		      match=0;
		      for (c=0;c<buckets;c++)
			{
			  pr_debug("Free entries in bucket [%d]: %lu\n",j+c, base[i].free_entries_in_1k[j+c]);
			  if (base[i].free_entries_in_1k[j+c]==1024)
			    match++;
			  else
			    break;
			}              
		      pr_debug("Found %d matches\n",match);
		      if (buckets==match)
			{
			  *gat_idx=i;
			  *gate_idx=j*1024;
			  
			  pr_debug("Large request done gat=%d gate=%d\n",*gat_idx,*gate_idx);
			  //spin_unlock_irqrestore(&find_lock, find_flags);
			  return 0;
			}
		      else
			{
			   pr_debug("Not enough matches.\n");
			}
		    }
		}
	    }
	  else
	  {
	      //more pages neede than fit into one gat
	      num_gats=num_pages/262144;
	      if ( (num_pages%262144)!=0) num_gats++;
	      pr_alert("Allocating %d pages needs %d gats\n",num_pages,num_gats);
	      if (num_gats > atu2_gat_xlarge) {
		  pr_alert("Allocation of %d pages requested, but atu2_gat_xlarge=%d, so not enough ressources\n",num_pages,atu2_gat_xlarge);
		  return -ENOMEM;
	      }
	      
	      for (i=start_gat_idx;i<=end_gat_idx-num_gats;i++) {
		match=0;
		gat_match=0;
		
		for (j=i;j<i+num_gats;j++) {
		  for (c=0;c<256;c++) {
		    if (base[j].free_entries_in_1k[c]==1024) match++;
		    else break;
		  }
		  if (match!=256) {
		    pr_alert("Buckets not all free for Gat %d, breaking\n",j);
		    break;
		  }
		  else {
		    match=0;
		    pr_alert("Gat %d available\n",j);
		    gat_match++;
		  }
		}
		
		if (gat_match==num_gats)
		{
		  *gat_idx=i;
		  *gate_idx=0;
		  pr_alert("XLarge Allocation staring at Gat %d\n",*gat_idx);
		  return 0;
		}
	      }	
   	      pr_alert("No large Region found for %d pages\n",num_pages);		
	      return -ENOMEM;	
	  }
	 // spin_unlock_irqrestore(&find_lock, find_flags);
	  pr_alert("oops end of find free entries function. Large registration request failed! (%u)\n",num_pages);
	  return -ENOMEM;
	}

	  /* }}} */

	/* {{{ access GAT entries (GATes) */

	//access functions for gate entry:
	uint32_t atu2_gate_get_valid(atu2_gate_t g)
	{
	  //return (g) & 0x3;
	  return g.structured.valid;
	}


	uint32_t atu2_gate_get_vpid(atu2_gate_t g)
	{
	  //return (g>>48) & 0xffffff;
	  return g.structured.vpid;
	}

	unsigned long atu2_gate_get_pa(atu2_gate_t g)
	{
	  //return (g>>2)& 0xffffffffffffl;
	  return g.structured.pa;
	}

	atu2_gate_t atu2_gate_set_vpid(uint32_t vpid, atu2_gate_t g)
	{	
	  //g=g & 0x0000ffffffffffffl;
	  //g=g | ((uint64_t)vpid<<48);
	  g.structured.vpid=vpid;
	  return g;
	}

	atu2_gate_t atu2_gate_set_pa(unsigned long pa,atu2_gate_t g)
	{
	  //g=g & 0xffff000000000003l;
	  //g=g | (nla<<2);
	  g.structured.pa=pa;
	  return g;
	}

	atu2_gate_t atu2_gate_build(unsigned int page_size, unsigned long pa, uint32_t  vpid, bool read_access, bool write_access)
	{
	  atu2_gate_t g;
	  g.structured.pa=pa>>12l;
	  g.structured.vpid=vpid;
	  g.structured.rsv=0;
          g.structured.size=page_size;
	  if (read_access && !write_access) g.structured.valid=1;
	  if (!read_access && write_access) g.structured.valid=2;
	  if (read_access &&  write_access) g.structured.valid=3;
	  if (!read_access && !write_access) g.structured.valid=0;
	  return g;
	  //return ((uint64_t)vpid<<48) |  ((pa & 0xfffffffff000l)>>10) | (read_acces<<1) | (write_access) ; //shift pa only by ten, because is ored, and the lower two bits are used otherwise
	}

	/* }}} */

	void atu2_preload(int gate_idx,int gat_idx,unsigned long pa,unsigned int vpid,int page_size, int read_access, int write_access)
	{
	  unsigned long value0;
	  unsigned long value1;
	  unsigned long nla=(( ((uint64_t)gate_idx)&0x1ffl)<<18l) | ( ((uint64_t)gat_idx) & 0x3ffffl);
	  //unsigned long nla=((0x1ff)<<18l) | 0x4243;
	  unsigned long nla_msb=gate_idx>>9l;
	  //write_rf( .data({32'b0,1'b0,27'h000,4'b1101}),         .addr(RF_ATU2_PRELOAD) ); //32 rsvd 1 rsv | 27 nlpa | 1101 opcode
	  //write_rf( .data({3'b110,40'h06000,5'b0,5'b00000,10'b0,1'b0}), .addr(RF_ATU2_PRELOAD+8) ); // w/r/non evict | 40 PA [51:12]| 5 rsv | 5 size | 10 VPID | MSB NLA
	  pr_debug("doing preload for gate_idx %x gat_idx %x, pa %lx, vpid %x, access: %x %x, calculated nla is %lx nla_msb is %lx\n",
		  gate_idx,gat_idx,pa,vpid,read_access,write_access,nla,nla_msb);
	  if (nla_msb>1)
	  {
	    pr_alert("atu2_preload Oops, nla_msb is %lx\n",nla_msb);
	    return;
	  }
	  if (page_size>1)
	  {
	    pr_alert("atu2_preload Oops, page_size is %x\n",page_size);
	    return;
	  }
	  value0=(( (nla) & 0x7ffffffl)<<4l)|0xdl;
	  value1=((read_access&0x1l)<<63l)|((write_access&0x1l)<<62l)|(((pa>>12l)&0xffffffffffl)<<21l)| ((page_size & 0x1fl)<<11l) | ((((uint64_t)vpid) & 0xffl)<<1l) | (nla_msb & 0x1l);
	  pr_debug("preload value0: %lx value1: %lx\n",value0,value1);
	  //down(&atu2_register_sem);
	  //spin_lock_irqsave(&preload_lock, preload_flags);
	  set_extoll_rf_atu_rf_preload(vpid*2+0, value0);
	  set_extoll_rf_atu_rf_preload(vpid*2+1, value1);
	  //spin_unlock_irqrestore(&preload_lock, preload_flags);
	  //up(&atu2_register_sem);
	}


	/* {{{ wait for flush */

	static void atu2_flush_page(uint64_t gat_idx, uint64_t gate_idx)
	{
	  uint64_t value;
	  
	  //nla without page offset bits, here only 4k supported!
	  value = (gat_idx<<18l) | (gate_idx);
	  value = (0x1l<<60l) | value;
	  pr_debug("flushing page - command is %lx\n", (unsigned long int) value);
	  set_extoll_rf_atu_rf_cmd_interface(value);
	}

#if 0
	static void atu2_flush_vpid(int vpid)
	{
	  uint64_t value;
	  value = (0x2l<<60l) | (vpid & 0x3ffl);
	  pr_debug("flushing vpid - command is %lx\n", (unsigned long int) value);
	  set_extoll_rf_atu_rf_cmd_interface(value);
	}
#endif

	static void atu2_flush_pages(uint64_t gat_idx, uint64_t gate_idx,int count)
	{
	  uint64_t value;
	  if (count>1024)
	  {
	    pr_info("atu2_flush_pages called with count > 1024 (%d). Set to 1024.\n",count);    
	    count=1024;
	  }
	  if (count<1)
	  {
	    pr_info("atu2_flush_pages called with count < 1 (%d). Set to 1.\n",count);    
	    count=1;
	  }
	  count=count-1; //coding is zero = one in hardware!
	  //nla without page offset bits, here only 4k supported!
	  value = ( ((uint64_t)count)<<28l) | (gat_idx<<18l) | (gate_idx);
	  value = (0x1l<<60l) | value;
	  pr_debug("flushing page - command is %lx\n", (unsigned long int) value);
	  set_extoll_rf_atu_rf_cmd_interface(value);
	}

	#ifdef USE_FENCE_ONLY
	static void atu2_fence(unsigned int vpid)
	{
	  uint64_t value;
	  uint64_t fence_addr;
	  
	  __fence_count++;
	  atu2_notification_table->notifications[vpid]=0l;  
	  fence_addr=atu2_notification_table_paddr+vpid*8;
	  pr_debug("Fence Buffer at pa %lx\n",(unsigned long int)fence_addr);
	  pr_debug("Fence. Notification address is %p, addr for command is %lx\n",&(atu2_notification_table->notifications[vpid]), (unsigned long int)fence_addr);
	  value= ((0x3l)<<60l) | (fence_addr& 0xffffffffffffl);
	  pr_debug("fence - command is %lx\n", (unsigned long int)value);
	  pr_debug("now cheching priot fence var...\n");
	  pr_debug("value is %lx\n", (unsigned long int)atu2_notification_table->notifications[vpid]);

	  set_extoll_rf_atu_rf_cmd_interface(value);
	  pr_debug("now cheching after fence var 1...\n");
	  pr_debug("value is %lx\n", (unsigned long int)atu2_notification_table->notifications[vpid]);
	  pr_debug("fence count is %lx\n",(unsigned long int)__fence_count);
	}
	#else
	static void atu2_notification(unsigned int vpid)
	{
	  uint64_t value;
	  uint64_t fence_addr;
	  
	  
	  atu2_notification_table->notifications[vpid]=0l;
	  
	  fence_addr=atu2_notification_table_paddr+vpid*8;
	  pr_debug("Notification Buffer at pa %lx\n",(unsigned long int)fence_addr);
	  pr_debug("Notification. Notification address is %p, addr for command is %lx\n",&(atu2_notification_table->notifications[vpid]), (unsigned long int)fence_addr);
	  value= ((0x4l)<<60l) | (fence_addr& 0xffffffffffffl);
	  pr_debug("notification - command is %lx\n", (unsigned long int)value);
	  pr_debug("now cheching prior notification var...\n");
	  pr_debug("value is %lx\n", (unsigned long int)atu2_notification_table->notifications[vpid]);

	  set_extoll_rf_atu_rf_cmd_interface(value);
	  pr_debug("now cheching after notification var 1...\n");
	  pr_debug("value is %lx\n", (unsigned long int)atu2_notification_table->notifications[vpid]);
	}
	#endif

	static int atu2_wait_for_flush(unsigned int vpid)
	{
	  int timeout=0;
	  
	  //down(&atu2_register_sem);
	  
	  while ((volatile unsigned long int)atu2_notification_table->notifications[vpid]==0l && timeout < atu2_flush_timeout_us)
	  {
	    pr_debug("waiting for flush success,  fence_var is %lx\n", (unsigned long int)atu2_notification_table->notifications[vpid]);
	    timeout++;
	    udelay(1);
	    if (timeout==atu2_flush_timeout_us) break;
	  }
	  if ((volatile unsigned long int)atu2_notification_table->notifications[vpid]!=0l)
	  {
	    //success
	    pr_debug("Flush successfull, fence_var is %lx\n", (unsigned long int)atu2_notification_table->notifications[vpid]);
	    //up(&atu2_register_sem);
	    return 0;
	  }
	  else
	  {
	    //timeout
	    //MN: This is a more serious situation, it should actually not happen in normal operation. What should we do in that case?
	    pr_alert("OOps FLUSH Timeout...fence_var is %lx\n",(unsigned long int)atu2_notification_table->notifications[vpid]);
	    //up(&atu2_register_sem);
	    return -EFAULT;
	  }
	  //up(&atu2_register_sem);
	  return -EFAULT;
	}


	/* }}} */


	/* {{{ perform register page */
        //this function is called with SYSTEM pages which may be different then atu pages
	static int perform_register_pages(unsigned int vpid, unsigned long address, unsigned long npages, bool read_access, bool write_access, /*unsigned long* nla,*/ int gat_idx, int gate_idx, unsigned long * return_first_page)
	{
	  //int npages=1;
	  unsigned long cur_base;
	  long int locked=0;
	  long int lock_limit=0;
	  int ret=0;
	#ifdef MEASURE
	  unsgined long t1,t2;
	#endif
	  unsigned long pa;
	  unsigned long first_pa=0l;
	  int i,j;
	  //  uint64_t t1,t2;
	  int got;
          struct vm_area_struct *vma;
//           int continous=1;
	  
	  if (vpid>atu2_get_max_vpids())
	    {
	      pr_alert("perform_register_pages for VPID %u, but only %u vpids are supported. Consider increasing the atu_gat_num module parameter..\n",
		    vpid, ATU2_MAX_VPIDS);     
	      return -ENOMEM;
	    }
	    
	  pr_debug("Perform_register_pages called with npages=%lu on behalf of vpid %d\n",npages,vpid);

	  //check mlock()
	if (!can_do_mlock())
	    return -EPERM;

	//check page alignement...
	cur_base = address & PAGE_MASK;

	//get the mm semaphore
	EKVCL_mmap_read_unlock(current->mm);


	vma = find_vma(current->mm, address); 


	if(vma && vma->vm_flags & (VM_IO | VM_PFNMAP)){
	    int offset;
	    pr_debug("Find mmio maped address to register, with start addr %lx \n", vma->vm_pgoff);       
	    EKVCL_mmap_read_lock(current->mm);
	    gat_tables[gat_idx].free_entries_in_1k[gate_idx/1024]-=npages * __atu_pp;
	    if((cur_base + PAGE_SIZE*npages)>vma->vm_end)
			return -EINVAL;
	    offset = cur_base - vma->vm_start;
	    pa =( vma->vm_pgoff << PAGE_SHIFT) + offset; 
	   for (i=0;i<npages;i++)
	  {
           for (j=0;j<__atu_pp;j++)
           {
              pr_debug("Registering page %d with physical address %lx from vpid %u\n",i,pa,vpid); 
              gat_tables[gat_idx].entries[gate_idx]=atu2_gate_build(0,pa,vpid,1,1);//read_access,write_access);
              if (i==0) first_pa=pa;
              //     atu2_preload(gat_idx,gate_idx,pa,vpid,0,1,1);
              pr_debug("New entry is %lx, put at idx %u of table %u at address %p\n",
			  (long unsigned int)gat_tables[gat_idx].entries[gate_idx].value,gate_idx,gat_idx, 
			  &(gat_tables[gat_idx].entries[gate_idx]));
		//gat_tables[gat_idx].free_entries_in_1k[gate_idx/1024]--; //safe method - possibly less safe method befor loop
		gate_idx=gate_idx+1;
		if (gate_idx-(262144)>0) //need to continue to next gat table
		{
		  pr_debug("registration extends beyond one GAT. Overflow from table %d to %d\n",gat_idx,gat_idx+1);
			gat_idx++;
			gate_idx=0;
		}
		pa+= (PAGE_SIZE/__atu_pp);
            } 
	    

	  }

	}
	else {
	//check lock limits for the process
	    locked     = npages + current->mm->locked_vm;
	    lock_limit = current->signal->rlim[RLIMIT_MEMLOCK].rlim_cur >> PAGE_SHIFT;
	    if ((locked > lock_limit) && !capable(CAP_IPC_LOCK)) {
		ret = -ENOMEM;
		pr_alert("Out of lockable pages: locked %lx lock_limit %lx\n", locked, lock_limit);
		EKVCL_mmap_read_lock(current->mm);
		return ret;
	      }
	   pr_debug("current->mm->locked_vm is %lx\n",current->mm->locked_vm);
	  //lock the page
	#ifdef MEASURE
	  rdtscll(t1);
	#endif
	   for (got = 0; got < npages; got += ret) {
	  //ret=get_user_pages_fast(cur_base + got*PAGE_SIZE, npages - got,
	  //                      1 /*write access */,(__page_list)+got);
	      ret=EKVCL_get_user_pages_remote(current, current->mm, cur_base + got*PAGE_SIZE, npages - got,
				1 /*read access*/, 1 /*write access */,(&(__page_list[1024*vpid]))+got,0);
	     if (ret<0) {
	       for (i=0;i<got;i++)
	       {
		 if (!PageReserved(__page_list[(1024*vpid)+i]))
		  SetPageDirty(__page_list[(1024*vpid)+i]);
		 put_page(__page_list[(1024*vpid)+i]);
                 
	      }
	      EKVCL_mmap_read_lock(current->mm);
	      pr_alert("Could not get_user_pages pages. Return value was %d, locked was %ld, lock_limit %ld\n",ret,locked, lock_limit);
	      ret = -ENOMEM;
	      return ret;    
	     }
//              for (i=1;i<ret;i++){
//                 if (continous==1) {
//                     if (page_to_phys(__page_list[(1024*vpid)+i-1]) == page_to_phys(__page_list[(1024*vpid)+i])+PAGE_SIZE)
//                     {
//                       printk("ATU2: pages continous %d and %d: %lx %lx\n",i,i-1,page_to_phys(__page_list[(1024*vpid)+i-1]),page_to_phys(__page_list[(1024*vpid)+i])+PAGE_SIZE);
//                     }
//                     else
//                     {
//                       printk("ATU2: pages not continous %d and %d: %lx %lx\n",i,i-1,page_to_phys(__page_list[(1024*vpid)+i-1]),page_to_phys(__page_list[(1024*vpid)+i])+PAGE_SIZE);
//                       continous=0;
//                     }
//                   }
//               }
//               if (continous==1)
//                 printk("ATU2: %d pages are continous in physical memory!\n",got);
//               else
//                 printk("ATU2: %d pages were not continous in physical memory!\n",got);

	   }
	   pr_debug("after gup current->mm->locked_vm is %lx\n",current->mm->locked_vm);
	  //FIXME: this is nor working as expected! Commented for BK Gasnet development
	   current->mm->locked_vm += npages;
	   pr_debug("after update current->mm->locked_vm is %lx\n",current->mm->locked_vm);
	#ifdef MEASURE
	    rdtscll(t2);
	#endif
	    EKVCL_mmap_read_lock(current->mm);
	#ifdef MEASURE
	    pr_debug("get_user_pages for %ld pages took %lx cycles\n",npages, t2-t1);
	#endif
	    if (ret < 0)
	    {
	       pr_alert("get_user_pages failed with %d\n",ret);
	       return ret;
	    }
	    pr_debug("get user pages returned %d\n",ret);
	    pr_debug("Registering %ld pages with gat_idx=%d and gate_idx=%d for vpid %d\n",npages, gat_idx,gate_idx,vpid);
	//FIXME: not locked..
	   gat_tables[gat_idx].free_entries_in_1k[gate_idx/1024]-=npages;
	  for (i=0;i<npages;i++)
	  {
	    pa=page_to_phys(__page_list[(1024*vpid)+i]);
	    pr_debug("Registering page %d with physical address %lx from vpid %u\n",i,pa,vpid); 
	 #ifdef MICEXTOLL
	   pa=pa + micextoll_micbase0;
	   //printk("EXTOLL BQ: added %lx to the physical address to account for MIC bar. Physical is now %lx\n",micextoll_micbase0,d->ph_addr);
	 #endif
	   //put entry into GATe
           for (j=0;j<__atu_pp;j++)
           {
              gat_tables[gat_idx].entries[gate_idx]=atu2_gate_build(0,pa,vpid,1,1);//read_access,write_access);
              if (i==0 && j==0 ) first_pa=pa;
              //     atu2_preload(gat_idx,gate_idx,pa,vpid,0,1,1);
              pr_debug("New entry is %lx, put at idx %u of table %u at address %p\n",
			  (long unsigned int)gat_tables[gat_idx].entries[gate_idx].value,gate_idx,gat_idx, 
			  &(gat_tables[gat_idx].entries[gate_idx]));
		//gat_tables[gat_idx].free_entries_in_1k[gate_idx/1024]--; //safe method - possibly less safe method befor loop
		gate_idx=gate_idx+1;
		if (gate_idx-(262144)>0) //need to continue to next gat table
		{
		  pr_debug("registration extends beyond one GAT. Overflow from table %d to %d\n",gat_idx,gat_idx+1);
			gat_idx++;
			gate_idx=0;
		}
		pa=pa+(PAGE_SIZE/__atu_pp);
           }
	  }
	}
	//done...
	//FIXME: not locked..
	_atu_num_pages_of_vpid[vpid]+=npages*__atu_pp;
	pr_debug("perform_register_pages done\n");
	if (return_first_page!=0)
	  *return_first_page=first_pa;
	return 0;
	}

	//#define DEBUG(a)

	/* }}} */

	/* {{{ perform unregister page */
        //MACHINE page!
	static int perform_unregister_page(int vpid,int gat_idx, int gate_idx, int lock, int flush, int physical)
	{
	  unsigned long address, org_address=0l;
	  struct page *page= NULL;
	  int result=0;
          int i;
  
	  pr_debug("Unregister with gat %u and gate idx %u @ %p called.\n", gat_idx, gate_idx, &(gat_tables[gat_idx].entries[gate_idx]));
          if (physical==0) {
            org_address = gat_tables[gat_idx].entries[gate_idx].structured.pa;
            #ifdef MICEXTOLL
              org_address=org_address - (micextoll_micbase0>>12l); //this is a pfn, thus lower 12 bits not to be subracted
              pr_debug("manipulated org_address to fix MIC addressing, now %lx\n",org_address);
              #endif
          }
          for (i=0;i<__atu_pp;i++)
          {
            pr_debug("Entry address only is %lx\n",(long unsigned int)gat_tables[gat_idx].entries[gate_idx].structured.pa);
            address = gat_tables[gat_idx].entries[gate_idx].structured.pa; //address <<10l;

            //TODO:Check if this is right
            #ifdef MICEXTOLL
            address=address - (micextoll_micbase0>>12l); //this is a pfn, thus lower 12 bits not to be subracted
            pr_debug("manipulated address to fix MIC addressing, now %lx\n",address);
            #endif

            pr_debug("Unregistering page with physical page number %lx\n",address);
            if (address==0l)
            {
              pr_alert("ERROR - Trying to de-register page @ address 0 (gat_idx=0x%x gate_idx=0x%x)!\n",
                      gat_idx, gate_idx );
              gat_tables[gat_idx].entries[gate_idx].value=0l;
              return -EFAULT;
            }
            gat_tables[gat_idx].entries[gate_idx].value=0l;
            pr_debug("Reset GATe\n");
          
            #ifndef DBG_NO_FLUSH  
            if (flush==1)
            {
              atu2_flush_page(gat_idx,gate_idx);    
            }
          #endif

            pr_debug("after flush\n");

            gat_tables[gat_idx].free_entries_in_1k[gate_idx/1024]++;
            gate_idx++;
            if (gate_idx-(262144)>0) //need to continue to next gat table
                {
                  pr_debug("registration extends beyond one GAT. Overflow from table %d to %d\n",gat_idx,gat_idx+1);
                        gat_idx++;
                        gate_idx=0;
                }
          }

         #ifndef DBG_NO_FLUSH  
            if (flush==1)
            {
          #ifdef USE_FENCE_ONLY              
              atu2_fence(vpid);
          #else    
              atu2_notification(vpid);
          #endif    
            }
          #endif
        if (physical==0) {
          if(pfn_valid(org_address)){
            page=pfn_to_page(org_address);
            pr_debug("after pfn_to_page\n");
            //gat_tables[gat_idx].free_entries_in_1k[gate_idx/1024]++;

            if (lock==1)
              EKVCL_mmap_read_unlock(current->mm);
  
            if (!PageReserved(page))
              SetPageDirty(page);
            
            pr_debug("after SetPageDirty\n");
            put_page(page);

            if (lock==1)
              EKVCL_mmap_read_lock(current->mm);
            pr_debug("after up_read\n");
          }
        }
	  #ifndef DBG_NO_FLUSH  
	  if (flush==1)
	    result = atu2_wait_for_flush(vpid);
	    pr_debug("after atu2_wait_for_flush\n");
	   #endif

	  pr_debug("unregister page done!\n");
	  return result;
}

//machine pages!
static int perform_unregister_pages(int vpid,int start_gat_idx, int start_gate_idx, int count,int physical)
{
  unsigned long org_address,address;
  struct page *page = NULL;
  int gate_idx;
  int gat_idx;
  int i,j;
  int result=0;
 
  DEBUG(printk("Atu unregister pages\n");)
  //#define DEBUG(a) a
  if (count==0)
    {
      pr_info("BUG, unregister of 0 pages requested. Ignoring.\n");
      return 0;
    }

  gat_idx=start_gat_idx;  
  gate_idx=start_gate_idx;  
  pr_debug("Unregistering %d pages with gat %u and gate idx %u @ %p called.\n", count, gat_idx, gate_idx, &(gat_tables[gat_idx].entries[gate_idx]));
  if (physical==0)
    EKVCL_mmap_read_unlock(current->mm);
  for (i=0;i<count;i++)
    {
      if (physical==0) {
        org_address=gat_tables[gat_idx].entries[gate_idx].structured.pa;
      #ifdef MICEXTOLL
        org_address=org_address - (micextoll_micbase0>>12l); //this is a pfn, thus lower 12 bits not to be subracted
        pr_debug("manipulated org_address to fix MIC addressing, now %lx\n",org_address);
      #endif
      }
      for (j=0;j<__atu_pp;j++)
      {
          address=gat_tables[gat_idx].entries[gate_idx].structured.pa;
          #ifdef MICEXTOLL
            address=address - (micextoll_micbase0>>12l); //this is a pfn, thus lower 12 bits not to be subracted
            pr_debug("manipulated address to fix MIC addressing, now %lx\n",address);
          #endif         
          pr_debug("ATU2: Unregistering page with physical page address %lx\n",address);
            if (address==0l)
              {
                pr_alert("ERROR - %d. page - Trying to de-register page @ address 0 (gat_idx=0x%x gate_idx=0x%x)!\n",
                      i,gat_idx, gate_idx );
                gat_tables[gat_idx].entries[gate_idx].value=0l;
                if (physical==0)
                  EKVCL_mmap_read_lock(current->mm);
                return -EFAULT;
              }
          gat_tables[gat_idx].entries[gate_idx].value=0l;

    //        #ifndef DBG_NO_FLUSH  
    //        atu2_flush_page(gat_idx,gate_idx);
    //        #endif   

        gat_tables[gat_idx].free_entries_in_1k[gate_idx/1024]++;
          if (gat_tables[gat_idx].free_entries_in_1k[gate_idx/1024]>1024)
            {
              pr_alert("Ooops, increased free entries in bucket too much: gate_idx: %d, gat_idx: %d, count: %d, i=%d, free_entries: %ld, bucket=%d\n",gate_idx,gat_idx,count,i,
                                      gat_tables[gat_idx].free_entries_in_1k[gate_idx/1024], gate_idx/1024);
            }
        gate_idx++;
        //wait_for_flush(flush_value);
        if (gate_idx-(256*1024)>0) //need to continue to next gat table
        {
          gat_idx++;
          gate_idx=0;
        }    
      }
      if (physical==0) {
        if(pfn_valid(org_address)) {
          page=pfn_to_page(org_address /*>>PAGE_SHIFT*/);                    
          if (!PageReserved(page))
            SetPageDirty(page);
          put_page(page);  
          
          //FIXME: this is nor working as expected! Commented for BK Gasnet development
        current->mm->locked_vm -= 1;
        }   
      }
    }
  if (physical==0)
    EKVCL_mmap_read_lock(current->mm);
  
  //FIXME: last flush Flush!
  #ifndef DBG_NO_FLUSH  
  atu2_flush_pages(start_gat_idx,start_gate_idx,count);
 #ifdef USE_FENCE_ONLY   
    atu2_fence(vpid);
#else    
    atu2_notification(vpid);
#endif    
  #endif
  __registered_count-=count;
  #ifndef DBG_NO_FLUSH
  result = atu2_wait_for_flush(vpid);
  #endif
  return result;
  //return 0;
}

//#define DEBUG(a)

/* }}} */

/* {{{ atu_register functions */
//int atu2_register_page_list(unsigned int vpid, struct page * pages, unsigned long count, bool read_acc, bool write_acc, unsigned long* nla)
int atu2_register_page_list(unsigned int vpid, void* vec,unsigned long count, unsigned int stride,bool read_acc, bool write_acc, unsigned long* nla)
{
  int result=0l;
  unsigned long first_pa=0l;
  int gat_idx, gate_idx;
  int i,j;
  void * entry;
  unsigned long pa;

  pr_debug("Getting to register_lock\n");

  if (vpid>atu2_get_max_vpids())
    {
      pr_debug("perform_register_virtual_region for VPID %u, but only %u vpids are supported. Consider increasing the atu_gat_num module parameter..\n",
            vpid,ATU2_MAX_VPIDS );     
      return -ENOMEM;
    }

//   if (down_interruptible(&atu_register_sem)) {
//      return -ERESTARTSYS;
//   }  
  
//   if (size>4294967296l) 
//     {
//       printk("ATU2: try to register region larger than 4GB (actual size is %lu), currently not supported by SW\n",size);
//       //mutex_unlock(&register_mutex);
//       return -ENOMEM;
//     }
//   if (size==0l)
//   {
//     printk("ATU2: try to register zero pages. that is not supported\n");
//     //mutex_unlock(&register_mutex);
//     return -ENOMEM;
//   }
//   count=( (size-1)>>PAGE_SHIFT)+1;
//   DEBUG(printk("ATU2: Virtual Region: Size is %lu, count is %u\n",size,count);)

  //find empty slots for all pages...
  mutex_lock(&register_mutex);
  result=find_free_entries(vpid, count * __atu_pp, &gat_idx, &gate_idx); //take _atu_pp into account -> how many atu pages are needed for one system page
  if (result!=0) { mutex_unlock(&register_mutex); return result;}
  //mutex_unlock(&register_mutex);
  
  //mutex_lock(&register_mutex);  
  pr_debug("Registering %lu pages in table %d starting from index %d\n",
              count,gat_idx,gate_idx);
    
  *nla = ((((uint64_t)gat_idx)<<18l) | (((uint32_t)gate_idx) & 0x3ffffl) )<<12l;//PAGE_SHIFT; -> fixed that for 4k atu pages for the moment!
  entry=vec;
  for (i=0;i<count;i++) //perform for every bunch of 1024 pages...
    {
      pr_debug("vec=%p entry=%p stride=%d\n",vec,entry,stride);
 
      //perform the registration  
      pa=page_to_phys(*((struct page**)entry));
      pr_debug("Registering page %d with physical address %lx from vpid %u\n",i,pa,vpid); 
      #ifdef MICEXTOLL
      pa=pa + micextoll_micbase0;
      //printk("EXTOLL BQ: added %lx to the physical address to account for MIC bar. Physical is now %lx\n",micextoll_micbase0,d->ph_addr);
      #endif
      if (i==0)
          first_pa=pa;

     //put entry into GATe
     for (j=0;j<__atu_pp;j++)
      {
        gat_tables[gat_idx].entries[gate_idx]=atu2_gate_build(0,pa,vpid,1,1);//read_access,write_access);

        pr_debug("New entry is %lx, put at idx %u of table %u at address %p\n",
                    (long unsigned int)gat_tables[gat_idx].entries[gate_idx].value,gate_idx,gat_idx, 
                    &(gat_tables[gat_idx].entries[gate_idx]));
          gat_tables[gat_idx].free_entries_in_1k[gate_idx/1024]--; //safe method - possibly less safe method befor loop
          gate_idx=gate_idx+1;
          if (gate_idx-(262144)>0) //need to continue to next gat table
          {
            pr_debug("registration extends beyond one GAT. Overflow from table %d to %d\n",gat_idx,gat_idx+1);
            gat_idx++;
            gate_idx=0;
          }
          pa=pa+(PAGE_SIZE/__atu_pp);
      }
    //done...  
    _atu_num_pages_of_vpid[vpid]+=count*__atu_pp;
    entry=entry+stride;
    }
  mutex_unlock(&register_mutex);
  //preload the first one!
  if (atu2_enable_preload==1)
    atu2_preload(gat_idx,gate_idx,first_pa,vpid,0,1,1);
  //finally return the result
  return 0;
}

int atu2_register_physical_region(unsigned int vpid, unsigned long address, unsigned long size, bool read_acc, bool write_acc, unsigned long* nla)
{
  int result=0l;  
  unsigned long pa;
  unsigned long first_pa;
  int gat_idx, gate_idx;
  int gat_idx_temp, gate_idx_temp;
  int i,j;
  unsigned int count;

  pr_debug("Getting to register_lock\n");

  if (vpid>atu2_get_max_vpids())
    {
      pr_alert("perform_register_virtual_region for VPID %u, but only %u vpids are supported. Consider increasing the atu_gat_num module parameter..\n",
            vpid,ATU2_MAX_VPIDS );     
      return -ENOMEM;
    }

//   if (down_interruptible(&atu_register_sem)) {
//      return -ERESTARTSYS;
//   }
  
  
  pr_debug("ATU2: Passed register_lock, size is %ld\n",size);
  
  /*if (size>4294967296l) 
    {
      pr_alert("try to register region larger than 4GB (actual size is %lu), currently not supported by SW\n",size);
      //mutex_unlock(&register_mutex);
      return -ENOMEM;
    }*/
  if (size==0l)
  {
    pr_alert("try to register zero pages. that is not supported\n");
    //mutex_unlock(&register_mutex);
    return -ENOMEM;
  }
  count=( (size-1)>>PAGE_SHIFT)+1;
  pr_debug("Virtual Region: Size is %lu, count is %u\n",size,count);


  //find empty slots for all pages...
  mutex_lock(&register_mutex);
  result=find_free_entries(vpid, count * __atu_pp, &gat_idx, &gate_idx); //take _atu_pp into account -> how many atu pages are needed for one system page
  if (result!=0) { mutex_unlock(&register_mutex); return result;}
  //mutex_unlock(&register_mutex);
  
  //mutex_lock(&register_mutex);  
  pr_debug("Registering %u pages in table %d starting from index %d\n",
              count,gat_idx,gate_idx);
    
  *nla = ((((uint64_t)gat_idx)<<18l) | (((uint32_t)gate_idx) & 0x3ffffl) )<<12l;//PAGE_SHIFT; -> fixed that for 4k atu pages for the moment!
  pr_debug("Registered region for vpid %u with virtual address %lx and size %lx, got NLA %lx\n", vpid,address,size,*nla);
  gat_idx_temp=gat_idx;
  gate_idx_temp=gate_idx;
  pa=address && 0xfffffffffffff000l;
 ////
  first_pa=pa;
  ///// test for mmio-memory///
////
  for (i=0;i<count;i++) //perform for every bunch of 1024 pages...
    {
           //perform the registration  
      pr_debug("Registering page %d with physical address %lx from vpid %u\n",i,pa,vpid); 
      #ifdef MICEXTOLL
      pa=pa + micextoll_micbase0;
      //printk("EXTOLL BQ: added %lx to the physical address to account for MIC bar. Physical is now %lx\n",micextoll_micbase0,d->ph_addr);
      #endif
     //put entry into GATe
     for (j=0;j<__atu_pp;j++)
      {
        gat_tables[gat_idx].entries[gate_idx]=atu2_gate_build(0,pa,vpid,1,1);//read_access,write_access);

        pr_debug("New entry is %lx, put at idx %u of table %u at address %p\n",
                    (long unsigned int)gat_tables[gat_idx].entries[gate_idx].value,gate_idx,gat_idx, 
                    &(gat_tables[gat_idx].entries[gate_idx]));
          gat_tables[gat_idx].free_entries_in_1k[gate_idx/1024]--; //safe method - possibly less safe method befor loop
          gate_idx=gate_idx+1;
          if (gate_idx-(262144)>0) //need to continue to next gat table
          {
            pr_debug("registration extends beyond one GAT. Overflow from table %d to %d\n",gat_idx,gat_idx+1);
            gat_idx++;
            gate_idx=0;
          }
          pa=pa+(PAGE_SIZE/__atu_pp);
      }
     _atu_num_pages_of_vpid[vpid]+=count*__atu_pp;
  }
  mutex_unlock(&register_mutex);
  //preload the first one!
  if (atu2_enable_preload==1)
    atu2_preload(gat_idx,gate_idx,first_pa,vpid,0,1,1);
  //finally return the result
  return 0;
}

int atu2_register_virtual_region(unsigned int vpid, unsigned long address, unsigned long size, bool read_acc, bool write_acc, unsigned long* nla)
{
  int result=0l;
  unsigned long first_pa=0l;
  unsigned long pa_save=0l;
  int gat_idx, gate_idx;
  int gat_idx_temp, gate_idx_temp;
  int i,j;
  unsigned int count;

  pr_debug("Getting to register_lock\n");

  if (vpid>atu2_get_max_vpids())
    {
      pr_alert("perform_register_virtual_region for VPID %u, but only %u vpids are supported. Consider increasing the atu_gat_num module parameter..\n",
            vpid,ATU2_MAX_VPIDS );     
      return -ENOMEM;
    }

//   if (down_interruptible(&atu_register_sem)) {
// 	return -ERESTARTSYS;
//   }
  
  
  pr_debug("Passed register_lock, size is %ld\n",size);
  
  /*if (size>4294967296l) 
    {
      pr_alert("try to register region larger than 4GB (actual size is %lu), currently not supported by SW\n",size);
      //mutex_unlock(&register_mutex);
      return -ENOMEM;
    }*/
  if (size==0l)
  {
    pr_alert("try to register zero pages. that is not supported\n");
    //mutex_unlock(&register_mutex);
    return -ENOMEM;
  }
  count=( (size-1)>>PAGE_SHIFT)+1;
  pr_debug("Virtual Region: Size is %lu, count is %u\n",size,count);


  //find empty slots for all pages...
  mutex_lock(&register_mutex);
  result=find_free_entries(vpid, count * __atu_pp, &gat_idx, &gate_idx); //take _atu_pp into account -> how many atu pages are needed for one system page
  if (result!=0) { mutex_unlock(&register_mutex); return result;}
  //mutex_unlock(&register_mutex);
  
  //mutex_lock(&register_mutex);  
  pr_debug("Registering %u pages in table %d starting from index %d\n",
              count,gat_idx,gate_idx);
    
  *nla = ((((uint64_t)gat_idx)<<18l) | (((uint32_t)gate_idx) & 0x3ffffl) )<<12l;//PAGE_SHIFT; -> fixed that for 4k atu pages for the moment!
  pr_debug("Registered region for vpid %u with virtual address %lx and size %lx, got NLA %lx\n", vpid,address,size,*nla);
  gat_idx_temp=gat_idx;
  gate_idx_temp=gate_idx;
  
 ////

  ///// test for mmio-memory///
////
  for (i=0;i<(count/1024);i++) //perform for every bunch of 1024 pages...
    {
      //perform the registration	  
      result=perform_register_pages(vpid,address+i*1024*PAGE_SIZE,1024,read_acc, write_acc,/*&(nlas[i*1024]),*/gat_idx_temp,gate_idx_temp,&pa_save);
      if(result<0)
        {
          //printk("ATU: perform_register_page failed...\n");
          //roll back what has happened so far...
// 					printk("Getting to first unregister_lock\n");
// 					spin_lock(&unregister_lock);
// 					printk("Passed first unregister_lock\n");
          for (j=0;j<(i*1024);j++)
            {
              perform_unregister_page(vpid,gat_idx_temp,gate_idx_temp,1,1,0); //we don't care if this fails -> dont know what to anyway
            }
        // spin_unlock(&unregister_lock);
          mutex_unlock(&register_mutex);
          return result;
        }

	if (i==0)
	  first_pa=pa_save;

        __registered_count+=1024;
	gate_idx_temp+=1024 * __atu_pp;
	pr_debug("incremented gate_idx to %d\n",gate_idx_temp);
	//handle potential gat_overflow...
	if (gate_idx_temp>=(256*1024) )
	{
		gat_idx_temp++;
		gate_idx_temp= gate_idx_temp - (256*1024);
	}
    }
  //perform the registration of the rest
  if ( (count%1024) !=0)
    {
           //FIXME: error will not be propagated, because result is usigned here!!!!
      result=perform_register_pages(vpid,address+i*1024*PAGE_SIZE,count % 1024,read_acc,
        write_acc,/*&(nlas[(count/1024)*1024]),*/gat_idx_temp,gate_idx_temp, &pa_save);
      if(result<0)
        {
          pr_debug("perform_register_page failed...\n");
          //roll back what has happened so far...
// 					printk("Getting to second unregister_lock\n");
// 					spin_lock(&unregister_lock);
// 					printk("Passed second unregister_lock\n");
          for (j=0;j<(count%1024);j++)
            {
              perform_unregister_page(vpid,gat_idx_temp,gate_idx_temp,1,1,0); //we don't care if this fails -> dont know what to anyway
            }
                    //spin_unlock(&unregister_lock);
          mutex_unlock(&register_mutex);
          return result;
        }
       if (first_pa==0l)
 	  first_pa=pa_save;//result;	
      __registered_count+= (count%1024);
    }
  mutex_unlock(&register_mutex);
  //preload the first one!
  if (atu2_enable_preload==1)
    atu2_preload(gat_idx,gate_idx,first_pa,vpid,0,1,1);
  //finally return the result
  return 0;
}
//#define DEBUG(a)

/* }}} */

/* {{{ atu_unregister functions */

int atu2_unregister_pages_by_nla(unsigned int vpid, unsigned long nla, int count, int physical)
{
/*   struct page *page; */
  uint32_t gat_idx;
  uint32_t gate_idx;
/*   unsigned long address; */

  if (vpid>atu2_get_max_vpids())
    {
      pr_alert("Unregister pages by nla for VPID %u, but only %u vpids are supported. Nothing to do here. Consider increasing the atu_gat_num module parameter..\n",
            vpid, ATU2_MAX_VPIDS);     
      return 0;
    }

  nla=nla>>12l;//PAGE_SHIFT; //get rid of offsets...
  // get the page struct...
  gat_idx=(nla>>18l) & 0x1ffl;
//   if (gat_idx/gat_per_vpid != vpid)
//     {
//       printk("ATU2: Trying to unregister page with NLA %lu from vpid %u, which is located in GAT %u belonging to vpid %u\n",
//             nla, vpid, gat_idx, gat_idx/gat_per_vpid);
//       return -1;
//     }
  gate_idx=(nla)&0x3ffffl;

  return perform_unregister_pages(vpid,gat_idx,gate_idx,count,physical);
}

int atu2_unregister_virtual_region(unsigned vpid,  unsigned long start_nla, uint64_t size)
{
  return atu2_unregister_region(vpid,start_nla,size,0);
}
int atu2_unregister_physical_region(unsigned vpid,  unsigned long start_nla, uint64_t size)
{
  return atu2_unregister_region(vpid,start_nla,size,1);
}
int atu2_unregister_region(unsigned vpid,  unsigned long start_nla, uint64_t size,int physical)
{
  uint64_t i;
  int result;
  uint64_t count = ( (size-1) >>PAGE_SHIFT)+1;
  //#define DEBUG(a) a
  if (vpid>atu2_get_max_vpids())
    {
      pr_alert("Unregister pages for VPID %u, but only %u vpids are supported. Nothing to do here. Consider increasing the atu_gat_num module parameter.\n",
            vpid, ATU2_MAX_VPIDS);     
      return 0;
    }
 mutex_lock(&register_mutex);
  pr_debug("Unregister for vpid %u starting at NLA %lx with size %lu called (count is %lu)\n",
              vpid,start_nla,(long unsigned)size,(long unsigned)count);
//   if (down_interruptible(&atu_register_sem)) {
// 	return -ERESTARTSYS;
//   }

  //just set all from start to start+end to zero, increement the free counters and perform the flush stuff
  for (i=0; i< (count/1024); i++)
    {
      //spin_lock_irqsave(&find_lock, find_flags);
      result=atu2_unregister_pages_by_nla(vpid, start_nla, 1024,physical);
      //spin_unlock_irqrestore(&find_lock, find_flags);
      if (result!=0)
            {
			  //up(&atu_register_sem);
			  mutex_unlock(&register_mutex);
			  return result;
            }
      start_nla=start_nla + PAGE_SIZE * 1024; //0x1000*1024;      
    }
  if (count%1024 !=0)
  {
    //spin_lock_irqsave(&find_lock, find_flags);
    result=atu2_unregister_pages_by_nla(vpid, start_nla, count%1024,physical);
    //spin_unlock_irqrestore(&find_lock, find_flags);
  }
  //up(&atu_register_sem);
  mutex_unlock(&register_mutex);
  return result;
}



//#define DEBUG(a)
int atu2_unregister_vpid_pages(unsigned int vpid, int physical)
{
  int i,j,c;
  int unregister_count=0;
  //remove all entries from all tables...
  
  //if (down_interruptible(&atu_register_sem)) {
  // 	return -ERESTARTSYS;
  //   }
  
  pr_debug("Unregistering of all pages for vpid %u requested\n",vpid);
  //spin_lock_irqsave(&find_lock, find_flags);
  for (i=0; i<atu2_gat_max_num; i++)
  {
    for (j=0;j<256;j++)
    {    
      if (gat_tables[i].free_entries_in_1k[j]!=1024) //some page in usage...
      {
        for (c=0;c<1024/__atu_pp;c++)
        { 
          if (atu2_gate_get_vpid(gat_tables[i].entries[j*1024 + c*__atu_pp])==vpid && atu2_gate_get_valid(gat_tables[i].entries[j*1024 + c*__atu_pp])!=0)
          {     
            pr_debug("unregistering %u / %lu\n", i , (unsigned long)( j*1024+c*__atu_pp));
            unregister_count++;
            perform_unregister_page(vpid,i ,j*1024+c*__atu_pp,0,1, physical); //set lock flag to zero and flush flag to zero -> flush will be taken care of with command below
          }
        }
      }      
    }  
  }
  //up(&atu_register_sem); 
  //flush all pages from this vpid
  /* DEBUG(printk("ATU2: Flushing all entries for vpid %u requested\n",vpid);)
  atu2_flush_vpid(vpid);
  DEBUG(printk("ATU2: Fencing after all entries for vpid %u have been flushed\n",vpid);)
#ifdef USE_FENCE_ONLY   
    atu2_fence(vpid);
#else    
    atu2_notification(vpid);
#endif    
  result = atu2_wait_for_flush(vpid);
  DEBUG(printk("ATU2: atu2_unregister_vpid_pages for vpid %d done\n",vpid);)
  //spin_unlock_irqrestore(&find_lock, find_flags);
  return result; */
  return unregister_count;
}

/* }}} */

/******************************************************************************
*  Module handling							      *
******************************************************************************/
static int __init atu2_init(void)
{
  int i,j;
  uint64_t value;
  
  //gat_per_vpid=16;
  pr_info("module init\n");
  if (extoll_get_init_done()==0)
  {
    pr_alert("EXTOLL Base driver not initialized! Bailing out\n");
    return -1;
  }

  _atu_num_pages_of_vpid=kmalloc(sizeof(uint64_t)*MAX_VPID_NUM,GFP_KERNEL);
  if (!_atu_num_pages_of_vpid)
  {
    pr_alert("Could not kmalloc memory for VPID table\n");
    return -ENOMEM;
  }
  memset(_atu_num_pages_of_vpid,0,sizeof(uint64_t)*MAX_VPID_NUM);

  // init the GAT tables....
#ifdef MICEXTOLL
  if (atu2_gat_max_num<64)
#else
  if (atu2_gat_max_num<64)
#endif
    {
      pr_alert("Only %u GAT tables requested. Setting to 64.\n",atu2_gat_max_num);
#ifdef MICEXTOLL
      atu2_gat_max_num=64;
#else
      atu2_gat_max_num=64;
#endif
    }
  pr_info("Initializing. Number of GATs is set to %u.\n",
        atu2_gat_max_num);

  //Allocate tables...
  gat_tables=kmalloc(sizeof(atu2_gat_table_t)*atu2_gat_max_num,GFP_KERNEL);
  if (!gat_tables)
  {
    pr_alert("Could not kmalloc memory for gat_tables, cleaning up.\n");
    kfree(_atu_num_pages_of_vpid);
    return -ENOMEM;
  }
  atu2_notification_table=(atu2_notification_table_t*)dma_alloc_coherent(extoll_get_device(), sizeof(atu2_notification_table_t),(void*)&atu2_notification_table_paddr, GFP_KERNEL);
  if (!atu2_notification_table)
  {
    pr_alert("Allocation of Notification Table failed.\n");
    kfree(_atu_num_pages_of_vpid);
    return -ENOMEM;
  }
#ifdef MICEXTOLL
    atu2_notification_table_paddr=atu2_notification_table_paddr + micextoll_micbase0;
#endif
  pr_alert("Request of GAT buckets: small=%d, medium=%d, large=%d\n",atu2_gat_small,atu2_gat_medium,atu2_gat_large);
  atu2_gat_xlarge=atu2_gat_max_num-atu2_gat_small-atu2_gat_medium-atu2_gat_large;
  if (atu2_gat_small+atu2_gat_medium+atu2_gat_large>=atu2_gat_max_num)
  {
    atu2_gat_small = ATU2_GAT_SMALL;
    atu2_gat_medium = ATU2_GAT_MEDIUM;
    atu2_gat_large = ATU2_GAT_LARGE;
    atu2_gat_xlarge = ATU2_GAT_XLARGE;
    pr_alert("Combination of GAT buckets not allowed. Resetting to small=%d, medium=%d, large=%d\n",atu2_gat_small,atu2_gat_medium,atu2_gat_large);
  }
  atu2_gat_start_small=0;
  atu2_gat_end_small=atu2_gat_start_small+atu2_gat_small-1;
  atu2_gat_start_medium=atu2_gat_end_small+1;
  atu2_gat_end_medium=atu2_gat_start_medium+atu2_gat_medium-1;
  atu2_gat_start_large=atu2_gat_end_medium+1;
  atu2_gat_end_large=atu2_gat_start_large+atu2_gat_large-1;
  atu2_gat_start_xlarge=atu2_gat_end_large+1;
  atu2_gat_end_xlarge=atu2_gat_max_num-1;

  for (i=0;i<atu2_gat_max_num;i++)
    {
      //hm is this not too much??
      gat_tables[i].entries=(atu2_gate_t*)dma_alloc_coherent(extoll_get_device(), 1024*1024*2,
                                                        (void*)&(gat_tables[i].pa), GFP_KERNEL);
 #ifdef MICEXTOLL
    gat_tables[i].pa=gat_tables[i].pa + micextoll_micbase0;
#endif
    //printk("EXTOLL BQ: added %lx to the physical address to account for MIC bar. Physical is now %lx\n",micextoll_micbase0,d->ph_addr);
    // #endif
    //
      if (!gat_tables[i].entries)
      {
        pr_alert("Allocation of GA Table %d failed.\n",i);
        for (j=0;j<i;j++)
        {
          dma_free_coherent(0, 1024*1024*2,gat_tables[j].entries ,gat_tables[j].pa);
        }
        return -ENOMEM;
      }
      memset(gat_tables[i].entries, 0, 1024*1024*2);
      for (j=0;j<256;j++)
        gat_tables[i].free_entries_in_1k[j]=1024; 
      
      value=(1l<<31l) | (gat_tables[i].pa>>21);
      pr_debug("Constructed GAT %u a@ PA %lx (into atu_gat -> %lx, value is %lx)\n",i, gat_tables[i].pa,gat_tables[i].pa>>21,(long unsigned int)value );
      set_extoll_rf_atu_rf_gat(i,value);
    }
  __registered_count=0;
  for (i=atu2_gat_max_num;i<1024;i++)
  {
    set_extoll_rf_atu_rf_gat(i,0x0l);
  }
  //enable ATU
  if (atu2_enable_preload==1)
    pr_info("Translation Preloading is activated\n");
  pr_info("Enabling Engine\n");
  set_extoll_rf_atu_rf_control(1);
  
  //FIXME: this assumes we alsways use 4k ATU pages for now.
  __atu_pp=PAGE_SIZE / 4096;
 
  sema_init(&atu2_register_sem, 1);
  //sema_init(&atu_unregister_sem, 1);
  return 0;
}

static void __exit atu2_exit(void)
{
    int i;

    pr_info("exit: Registered count: %lu\n",(long unsigned int)__registered_count);

   //disable ATU
   set_extoll_rf_atu_rf_control(0);

  //free all memory
  for (i=0;i<atu2_gat_max_num;i++)  
    {
      dma_free_coherent(0, 1024*1024*2,gat_tables[i].entries ,gat_tables[i].pa);
      set_extoll_rf_atu_rf_gat(i,0);
    }
  kfree(gat_tables);
  kfree(_atu_num_pages_of_vpid);
  pr_info("ATU2: module exit\n");
}

EXPORT_SYMBOL(atu2_get_supported_vpids);
EXPORT_SYMBOL(atu2_get_max_vpids);
EXPORT_SYMBOL(atu2_register_virtual_region);
EXPORT_SYMBOL(atu2_unregister_virtual_region);
EXPORT_SYMBOL(atu2_unregister_vpid_pages);
EXPORT_SYMBOL(atu2_register_page_list);
EXPORT_SYMBOL(atu2_unregister_physical_region);
EXPORT_SYMBOL(atu2_register_physical_region);
EXPORT_SYMBOL(atu2_unregister_pages_by_nla);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mondrian Nuessle mondrian.nuessle@extoll.de");
MODULE_DESCRIPTION("ATU2 Adress Translation driver for the EXTOLL hardware platform.");
MODULE_VERSION("1.1");

module_init(atu2_init);
module_exit(atu2_exit);
