#include "../extoll_kapi.h"
#include <linux/module.h>

#define PRINT(...) printk(KERN_ALERT "RMA IRQ TEST: " __VA_ARGS__)

int recv_node = 0;
module_param(recv_node, int, 0);
int recv_vpid = 0;
module_param(recv_vpid, int, 0);

static void rma_irq_send(void)
{
  RMA2_Handle *rhandle;
  int message = 42;

  kapi_rma2_open(&rhandle, -1);
  
  kapi_rma2_put_notification(rhandle, recv_node, recv_vpid, message, 0, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT, RMA2_CONN_IRQ);

  kapi_rma2_close(&rhandle);
}

static int __init rma_irq_send_init(void)
{
  rma_irq_send();
  return -ENODEV;
}

static void __exit rma_irq_send_exit(void)
{
  PRINT("done\n");
}

MODULE_LICENSE("GPL");
module_init(rma_irq_send_init);
module_exit(rma_irq_send_exit);
