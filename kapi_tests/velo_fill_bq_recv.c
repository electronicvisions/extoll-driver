#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include "../extoll_kapi.h"
#include <linux/module.h>

int remote_vpid = 0;
module_param(remote_vpid, int, 0);
MODULE_PARM_DESC(remote_vpid, "in ping mode: remote vpid");

int remote_node = 0;
module_param(remote_node, int, 0);
MODULE_PARM_DESC(remote_node, "in ping mode: remote nodeid");

static int __init doIt(void)
{
	VELO2_Handle *vhandle;

	char *msg = NULL;
	int srcid, len;
        uint8_t	mtt = 0, tag = 0;
	int i = 0;

	msg = (char *) kmalloc(120, GFP_KERNEL);

	kapi_velo2_open(&vhandle, -1);

	pr_info("pong mode\n");
  
  	pr_info("my vpid %i on node %i\n", kapi_velo2_get_vpid(vhandle), kapi_velo2_get_nodeid(vhandle));

	do {
		kapi_velo2_receive(vhandle, msg, &srcid, &len, &mtt, &tag, 0);
		if(mtt == 0) pr_info("recvd message #%i\n", i++);
	} while (mtt == 0);

	pr_info("recv done\n");

	kapi_velo2_close(&vhandle);
	return 0;
}

static void __exit end(void)
{
	pr_info("unloaded simple velo2 pong\n");
}

MODULE_LICENSE("GPL");
module_init(doIt);
module_exit(end);
