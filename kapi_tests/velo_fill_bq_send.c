#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include "../extoll_kapi.h"
//#include <linux/string.h>
#include <linux/module.h>

int remote_vpid = 0;
module_param(remote_vpid, int, 0);
MODULE_PARM_DESC(remote_vpid, "in ping mode: remote vpid");

int remote_node = 0;
module_param(remote_node, int, 0);
MODULE_PARM_DESC(remote_node, "in ping mode: remote nodeid");

unsigned int slot_offset = 0;
module_param(slot_offset, uint, 0);
MODULE_PARM_DESC(slot_offset, "How many slots is t first message long.");

unsigned int slots = 3;
module_param(slots, uint, 0);
MODULE_PARM_DESC(slots, "Size of the bulk messages.");

unsigned int pages = 2;
module_param(pages, uint, 0);
MODULE_PARM_DESC(pages, "How many pages is the buffer queue long.");

//static int size2slots(size_t s)
//{
//	if(s <= 56) return 1;
//	if(s <= 112) return 2;
//	return 3;
//}

static int slots2size(int slots)
{
	switch(slots) {
		case 1 : return 56;
		case 2 : return 112;
		case 3 : return 120;
		default: return 120;
	}
}
		

static int __init doIt(void)
{
	size_t message_size = slots2size(slots);
	VELO2_Handle *vhandle;
	char *msg = NULL;
	int i = 0;
	int slot_size = 0;
	int slot_count = 0;

	msg = (char *)kmalloc(message_size, GFP_KERNEL);
	memset(msg, 'A', message_size);

	kapi_velo2_open(&vhandle, -1);
	slot_size = vhandle->port->bq->slot_size;
	slot_count = ((4096*pages)/(slots*slot_size))*2 + 5; //some more messages than needed to fill the bq two times for good measure

	pr_info("ping mode, sending %i messages", slot_count);
	if(slot_count > 0) {
		pr_cont(" + 1 for offset\n");
	} else {
		pr_cont("\n");
	}
  
  	pr_info("my vpid %i on node %i\n", kapi_velo2_get_vpid(vhandle), kapi_velo2_get_nodeid(vhandle));

	pr_info("starting to fill bq; offset of %i, filling with messages of %i slots, with slot size of %i bytes\n", slot_offset, slots, slot_size);

	if(slot_offset > 0 ) {
		kapi_velo2_send(vhandle, remote_node, remote_vpid, msg, slots2size(slot_offset), 0, 0, 0, 0); //extra message for misalignend
	}
	for(i = 0; i<slot_count; i++) {
		kapi_velo2_send(vhandle, remote_node, remote_vpid, msg, message_size, 0, 0, 0, 0);
		pr_info("send message #%i\n", i);
	}
	
	kapi_velo2_send(vhandle, remote_node, remote_vpid, msg, message_size, 0, 1, 0, 0); //mtt 1 to tell other side we are finished
	pr_info("send done\n");

	kapi_velo2_close(&vhandle);
	return 0;
}

static void __exit end(void)
{
	pr_info("unloaded simple velo ping\n");
}

MODULE_LICENSE("GPL");
module_init(doIt);
module_exit(end);
