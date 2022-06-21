#include "../extoll_kapi.h"
#include <linux/module.h>

#define PRINT(...) printk(KERN_ALERT "RMA IRQ TEST RECV: " __VA_ARGS__)

RMA2_Handle *rhandle;

static void rma_irq_recv(int vpid, snq_entry_t* snq_entry)
{
  RMA2_Notification noti;
  
  kapi_rma2_noti_fetch(rhandle, &noti);
  
  PRINT("fetched this noti:");
  kapi_rma2_noti_dump(&noti);
}

static int __init rma_irq_recv_init(void)
{
  vpid_t vpid;
  kapi_rma2_open(&rhandle, -1);

  vpid = kapi_rma2_get_nodeid(rhandle);
  
  rma2_register_vpid_irq_handler(vpid, &rma_irq_recv);

  PRINT("rma irq handler registered! Nodeid: %i, vpid: %i\n", vpid, kapi_rma2_get_vpid(rhandle));
  return 0;
}

static void __exit rma_irq_recv_exit(void)
{
  kapi_rma2_close(&rhandle);
  PRINT("done\n");
}

MODULE_LICENSE("GPL");
module_init(rma_irq_recv_init);
module_exit(rma_irq_recv_exit);
