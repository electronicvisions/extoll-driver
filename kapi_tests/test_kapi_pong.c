#include "test_kapi.h"

static int __init kapi_test_init(void) 
{

  kapi_pong();

  return -ENODEV;
}

static void kapi_test_exit(void)
{
  printk("EXTOLL kernel API test unloaded\n");
}

MODULE_LICENSE("GPL");
module_init(kapi_test_init);
module_exit(kapi_test_exit);
