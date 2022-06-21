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

	char msg[] = "1234567890ABCDEFGHIJKLMNOPQRSTEUWXYZabcdefghijklmnopqrstuvwxyz[];'{}:,./<>?|=-+_)(*&^%$#@!~abcdefghijklmnopqrstuvwxyz01";
	int len = strlen(msg)+1;

	kapi_velo2_open(&vhandle, -1);

	pr_info("ping mode\n");
  
  	pr_info("my vpid %i on node %i\n", kapi_velo2_get_vpid(vhandle), kapi_velo2_get_nodeid(vhandle));
	pr_info("msg is: %s, length %i\n", msg, len);

	kapi_velo2_send(vhandle, remote_node, remote_vpid, msg, len, 0, 0, 0, 0);
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
