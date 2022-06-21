/*
 *
 * 	some first tests with the rma kapi
 *
 */

#include <linux/init.h>
#include <linux/module.h>
#include <asm/io.h>
#include <linux/dma-mapping.h>
#include <linux/pci.h>

#include "/extoll2/src/extolldrv-dev/extoll-driver/extoll_kapi.h"

#define KAPI_ANY_VPID -1
#define NO_MULTICAST 0
#define VELO_ISSUE_RX_INTR 1
#define VELO_COMMIT_IRQ_UPDATE 1

#define RMA_BUFF_SIZE 8

RMA2_Handle *rma_handle;
VELO2_Handle *velo_handle;

int recv_node = 0;
module_param(recv_node, int, 0);
int recv_vpid = 0;
module_param(recv_vpid, int, 0);
int msg = 0;
module_param(msg, int, 0);

uint64_t* rma_buffer;
dma_addr_t phys_rma_buffer;
struct pci_dev* devp;

static void velo_tx( int dst_node, int dst_vpid, void *tbuf){
	int i;
	uint64_t tx_info[2];
    uint64_t tx_hdr[1];
	int tag = 0;
	int mtt = 1; // message type tag
	int intr = 1;
	int status;

    tx_hdr[0]  = 123;
	tx_info[0] = 1;
	tx_info[1] = 2;

	// send velo notification with adress and length
	printk("Sending: Node: %i, vpid: %i, content: %p, len: %llu\n",dst_node, dst_vpid, (void*)tx_info[0], tx_info[1]);
	status = kapi_velo2_send_header(velo_handle, dst_node, dst_vpid, tx_info, sizeof(uint64_t)*2, tx_hdr, sizeof(uint64_t), tag, mtt, NO_MULTICAST, VELO_ISSUE_RX_INTR);
	printk("velo-header-send: velo send complete with status: %i\n", status);

}

static int __velo_core_init(void) {
	status = kapi_velo2_open(&velo_handle, KAPI_ANY_VPID);
	printk("velo-header-send: velo_open status: %i\n", status);

	// send velo message

	printk("\tStatus: %i\n", status);
    return 0;	
}

static int velo_core_init(void) {
	return __velo_core_init();
}

static void velo_core_exit(void) {
	kapi_velo2_close(&velo_handle);
	printk("velo-header-send: module is removed");
}

MODULE_LICENSE("GPL v2");
module_init(velo_core_init);
module_exit(velo_core_exit);
