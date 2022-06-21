#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include "../extoll_kapi.h"
#include <linux/module.h>
#include <linux/string.h>

int remote_vpid = 0;
module_param(remote_vpid, int, 0);
MODULE_PARM_DESC(remote_vpid, "in ping mode: remote vpid");

int remote_node = 0;
module_param(remote_node, int, 0);
MODULE_PARM_DESC(remote_node, "in ping mode: remote nodeid");

static int __init doIt(void)
{
	VELO2_Handle *vhandle;

	char *msg = kmalloc(121, GFP_KERNEL);
	int srcid, len, i = 0;
        uint8_t	mtt, tag;

	memset(msg, '.', 120);
	msg[120] = '\0';
	kapi_velo2_open(&vhandle, -1);

	pr_info("pong mode\n");
  
  	pr_info("my vpid %i on node %i\n", kapi_velo2_get_vpid(vhandle), kapi_velo2_get_nodeid(vhandle));

	kapi_velo2_receive(vhandle, msg, &srcid, &len, &mtt, &tag, 0);
	pr_info("recv done\n");
	pr_info("msg recevied: %s\n", msg);
	for(i = 0; i < 15; i++) {
		pr_info("msg raw %02i: %016llx\n", i, *((uint64_t *) msg+i));
	}


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
