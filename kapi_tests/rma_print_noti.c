#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include "../extoll_kapi.h"
#include <linux/module.h>
#include <linux/string.h>

static int __init doIt(void)
{
	RMA2_Notification noti;

	uint64_t word0 = 0x1000000000000001;
	uint64_t word1 = 0;

	noti.word0.value = word0;
	noti.word1.value = word1;

	kapi_rma2_noti_dump(&noti);


	return 0;
}

static void __exit end(void)
{
	pr_info("Unloaded notification printing module.\n");
}

MODULE_LICENSE("GPL");
module_init(doIt);
module_exit(end);
