#include "../extoll_kapi.h"
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/highmem.h>

#define PRINT(...) printk(KERN_ALERT "RMA NLA TEST: " __VA_ARGS__)
#define DEBUG_OUT 1 

int recv_node = 0;
module_param(recv_node, int, 0);
int numpages = 1;
module_param(numpages, int, 0);

RMA2_Handle *rhandle;
struct page **spage;
struct page **rpage;
unsigned long *spage_addr;
unsigned long *rpage_addr;
unsigned long snla = 0l;
unsigned long rnla = 0l;
vpid_t vpid;
int use_nla = 0;
int numfrags = 1;
int transfersize = 0;
int complnoticnt = 0;

static void rma_irq_handler(int vpid, snq_entry_t *snq_entry) {
	RMA2_Notification *noti = NULL;
	RMA2_Notification_Spec noti_type;
	uint32_t *tmp;
	int i = 0;

	while (0 != kapi_rma2_noti_peek(rhandle)) {
		kapi_rma2_noti_fetch(rhandle, &noti);
		noti_type = kapi_rma2_noti_get_notification_type(noti);
		kapi_rma2_noti_dump(noti);
		
		if (noti_type == RMA2_REQUESTER_NOTIFICATION) {
			PRINT("Finished RMA put / Requester notification\n");
		} else if (noti_type == RMA2_COMPLETER_NOTIFICATION) {
			PRINT("Finished PUT on data-receiving side / Completer notification\n");
			complnoticnt++;
			if (DEBUG_OUT) {
				PRINT("Print receive buffer after PUT:\n");
				if (use_nla == 0 && numpages == 1) {
					tmp = (uint32_t*)rpage_addr[0];
					for (i = 0; i < (PAGE_SIZE / 4); i++) {
						if (tmp[i]!=i)
						 printk("mismatch at %d: %08x",i, tmp[i]&0xffffffff);
					}
				} else if (use_nla == 1) {
					/*for (i=0; i<numpages; i++){
						tmp = (uint32_t*)rpage_addr[i];
						errorcnt = 0;
						for (j=0; j<(PAGE_SIZE / 4); j++) {
							if (tmp[j]!=j){
								//printk("mismatch at %d: %08x",j, tmp[j]&0xffffffff);
								errorcnt++;
							}
						}
						if (errorcnt != 0){
							printk("Mismatch on page %d\n",i);
							mismatchcnt++;
						}
					}
					printk("Number of pages with mismatch: %d", mismatchcnt);*/
				}
				//PRINT("Print receive buffer after Put done\n");
			}
		} else {
			PRINT("Unexpected notification received\n");
		}

		kapi_rma2_noti_free(rhandle, 1);
	}
}

static int __init test_nla_init(void) {
	int ret = 0, i, j;
	uint32_t *tmp;
	int nla_err = 0;
	uint64_t *debug;

	ret = kapi_rma2_open(&rhandle, -1);
	vpid = kapi_rma2_get_vpid(rhandle);
	recv_node = kapi_rma2_get_nodeid(rhandle);
	rma2_register_vpid_irq_handler(vpid, &rma_irq_handler);

	spage_addr = kmalloc(numpages*sizeof(unsigned long), GFP_KERNEL);
	rpage_addr = kmalloc(numpages*sizeof(unsigned long), GFP_KERNEL);
	if ((spage_addr == NULL) || (rpage_addr == NULL)){
		PRINT("Couldn't allocate address arrays. Abort...");
		goto error2;
	}

	spage = kmalloc(numpages*sizeof(struct page*), GFP_KERNEL);
	rpage = kmalloc(numpages*sizeof(struct page*), GFP_KERNEL);
	if ((spage == NULL) || (rpage == NULL)){
		PRINT("Couldn't allocate struct pages arrays. Abort...");
		goto error2;
	}

	for (j=0; j < numpages; j++) {
		spage_addr[j] = __get_free_page(GFP_KERNEL);
		rpage_addr[j] = __get_free_page(GFP_KERNEL);
		if (((void*)spage_addr[j] == NULL) || ((void*)rpage_addr[j] == NULL)){
			PRINT("Couldn't get free page for %d. Abort...", j);
			goto error;
		}
	        //PRINT("SPAGE_addr[%d] phys address is %p\n",j,virt_to_phys(spage_addr[j]));
	        //PRINT("RPAGE_addr[%d] phys address is %p\n",j,virt_to_phys(rpage_addr[j]));
	
		// Initialize send and receive buffer
		memset((void*)rpage_addr[j], 0, PAGE_SIZE);
		tmp = (uint32_t*)spage_addr[j];		
		for (i = 0; i < ((PAGE_SIZE) / 4); i++) {
			tmp[i] = i;
		}
		//tmp[i-1]=17;

		if (spage_addr[j] >= VMALLOC_START && spage_addr[j] < VMALLOC_END) {
			spage[j] = vmalloc_to_page((void*)spage_addr[j]);
		}else{
			spage[j] = virt_to_page(spage_addr[j]);
		}

		if (rpage_addr[j] >= VMALLOC_START && rpage_addr[j] < VMALLOC_END) {
			rpage[j] = vmalloc_to_page((void*)rpage_addr[j]);
		}else{
			rpage[j] = virt_to_page(rpage_addr[j]);
		}
	        //PRINT("SPAGE[%d] address is %p, struct page* is %p\n",j,&(spage[j]),spage[j]);
	        //PRINT("RPAGE[%d] address is %p, struct page* is %p\n",j,&(rpage[j]),rpage[j]);
		

		if (spage[j] == NULL || rpage[j] == NULL){
			nla_err++;
		}
	}

	if (DEBUG_OUT) {
		debug = kmap(spage[0]);
		for (j = 0; j<(128/8); j++) {
			printk("%016lx", debug[j]&0xffffffffffffffff);
		}
		// Print send and receive buffer
		PRINT("Print send buffer:\n");
		for (j=0; j<numpages;j++) {
	  		tmp = (uint32_t*)spage_addr[j];
			for (i = 0; i < ((PAGE_SIZE) / 4); i++) {
				if (tmp[i]!=i)
				 printk("mismatch at %d: %08x", i,tmp[i]&0xffffffff);
			}
		}
	        PRINT("Print receive buffer:\n");
		for (j=0;j<numpages;j++) {
			tmp = (uint32_t*)rpage_addr[j];
			for (i = 0; i < ((PAGE_SIZE) / 4); i++) {
				if (tmp[i]!=0)
					printk("mismatch at %d: %08x", i, tmp[i]&0xffffffff);
			}	
		}
	}
	
	// Check whether using NLAs is possible
	if(nla_err != 0 && numpages > 1) {
		PRINT("Cannot call kapi_atu2_map_pagelist, nla_err = %i", nla_err);
		goto error;
	} else if (nla_err != 0 && numpages == 1) {
		PRINT("Falling back to RMA PUT with physical addresses");
	} else {
		ret = kapi_atu2_map_pagelist(vpid, spage, numpages, sizeof(struct page*), &snla);
		if (ret != 0) {
			PRINT("Couldn't map sender page list. Bailing out...");
			goto error;
		}
		ret = kapi_atu2_map_pagelist(vpid, rpage, numpages, sizeof(struct page*), &rnla);
		if (ret != 0) {
			PRINT("Couldn't map receiver page list. Bailing out...");
			kapi_atu2_unmap_sg(vpid, numpages, snla);
			goto error;
		}
		PRINT("snla = %016lx, rnla = %016lx", snla, rnla);
		use_nla = 1;
	}

	if (use_nla == 0 && numpages == 1) {
		kapi_rma2_put_bt(rhandle, recv_node, vpid, (void*)virt_to_phys((void*)spage_addr[0]), 
				(void*)virt_to_phys((void*)rpage_addr[0]), PAGE_SIZE, RMA2_REQCOMPL_NOTIFICATION, 
				RMA2_CMD_DEFAULT, RMA2_CONN_IRQ);
	} else if (use_nla == 1) {
		PRINT("Use RMA PUT with RMA2_CONN_TE and %i pages", numpages);
		if (numpages <= 2048) {
			kapi_rma2_put_bt(rhandle, recv_node, vpid, (void*)snla, (void*)rnla, 
				numpages*PAGE_SIZE, RMA2_REQCOMPL_NOTIFICATION, 
				RMA2_CMD_DEFAULT, RMA2_CONN_IRQ | RMA2_CONN_TE);
		} else {
			if (numpages <= 4096)
				numfrags = 2;
			if ((numpages > 4096) && (numpages <= 6144))
				numfrags = 3;
			if (numpages > 6144) {
				PRINT("Transmission size not supported. Abort..");
				goto error;
			}


			for (i=0; i<numfrags;i++) {
				if ((i+1) == numfrags)
					transfersize = (numpages - (i*2048)) * PAGE_SIZE;
				else
					transfersize = 2048*PAGE_SIZE;
				kapi_rma2_put_bt(rhandle, recv_node, vpid, (void*)(snla+(2048*i*PAGE_SIZE)), (void*)(rnla+(2048*i*PAGE_SIZE)), 
					transfersize, RMA2_REQCOMPL_NOTIFICATION, 
					RMA2_CMD_DEFAULT, RMA2_CONN_IRQ | RMA2_CONN_TE);
				PRINT("Transfer (%d): snla = %016lx", i, snla+(2048*i*PAGE_SIZE));
			}
		}
	} else {
		PRINT("Transmission not supported. Abort...");
		goto error;
	}

	return 0;
error:
	for (i = 0; i<numpages; i++) {
		free_page(spage_addr[i]);
		free_page(rpage_addr[i]);
	}
error2:
	kfree(spage_addr);
	kfree(rpage_addr);
	kfree(spage);
	kfree(rpage);
error3:
	kapi_rma2_close(&rhandle);

	return -EIO;
}

static void __exit test_nla_exit(void) {
	int i = 0, j = 0;
	int errorcnt = 0, mismatchcnt = 0;
	uint32_t* tmp;
	if (complnoticnt == numfrags) {
		for (i=0; i<numpages; i++){
			tmp = (uint32_t*)rpage_addr[i];
			errorcnt = 0;
			for (j=0; j<(PAGE_SIZE / 4); j++) {
				if (tmp[j]!=j){
					//printk("mismatch at %d: %08x",j, tmp[j]&0xffffffff);
					errorcnt++;
				}
			}
			if (errorcnt != 0){
				PRINT("Mismatch on page %d\n",i);
				mismatchcnt++;
			}
		}
	}
	PRINT("Number of pages with mismatch: %d, number of transfers: %d\n", mismatchcnt, numfrags);

	if (use_nla == 1) {
		kapi_atu2_unmap_sg(vpid, numpages, snla);
		kapi_atu2_unmap_sg(vpid, numpages, rnla);
	}
	for (i = 0; i<numpages; i++) {
		free_page(spage_addr[i]);
		free_page(rpage_addr[i]);
	}
	kfree(spage_addr);
	kfree(rpage_addr);
	kfree(spage);
	kfree(rpage);
	kapi_rma2_close(&rhandle);
	PRINT("Done.");
	return;
}

MODULE_LICENSE("GPL");
module_init(test_nla_init);
module_exit(test_nla_exit);
