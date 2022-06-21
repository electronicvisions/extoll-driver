#include "../extoll_kapi.h"
#include <linux/module.h>
#include <asm/msr.h>
#include <asm/page.h>
#include <linux/dma-mapping.h>

#define PRINT(...) printk( KERN_ALERT "TEST RRA: " __VA_ARGS__)

// Module parameters

unsigned long int dest_rf_addr = 0x0;
unsigned long int data_val = 0x0;

int dest_nodeid = 0;
module_param(dest_nodeid, int, S_IRUGO);
MODULE_PARM_DESC(dest_nodeid, "Destation node ID for remote RF access\n");
char* dest_rra_address = "0x0";
module_param(dest_rra_address, charp, S_IRUGO);
MODULE_PARM_DESC(dest_rra_address, "RF address\n");
char* value = "0x0";
module_param(value, charp, S_IRUGO);
MODULE_PARM_DESC(value, "Data to be written to remote RF entry\n");
int cmd_type = 0;
module_param(cmd_type, int, S_IRUGO);
MODULE_PARM_DESC(cmd_type, "cmd_type: 0 for RRA write, 1 for RRA read\n");

int strtosize(char *str, unsigned long int *val)
{
  unsigned long int size;
  if (sscanf(str, "0x%lX", &size) == 1) {
    *val = size;
    return 0;
  } else
    return -1;
}

static int __init rra_init(void)
{
  RMA2_Handle *rhandle;
  int rc = 0;
  uint64_t tmp;
  //RMA2_Notification *noti = kmalloc(sizeof(*noti), GFP_KERNEL);
  //struct page *page = alloc_page(GFP_KERNEL); 
  //uint64_t *page_addr = page_address(page);
  //uint64_t tmp_addr = virt_to_phys(page_addr);

  strtosize(dest_rra_address, &dest_rf_addr);
  strtosize(value, &data_val);
  PRINT("Extoll RRA test loaded.\n");
  //kapi_rma2_open(&rhandle, 252);

  if(cmd_type == 0) {
    //rc = kapi_rma2_put_immediate(rhandle, (uint16_t)dest_nodeid, 252, (uint64_t)data_val, (void*)dest_rf_addr, 8, RMA2_REQUESTER_NOTIFICATION, RMA2_CMD_DEFAULT, RMA2_CONN_RRA);
    rc = kapi_rra_write((uint16_t)dest_nodeid, dest_rf_addr, (uint64_t)data_val);
    if(rc != 0){
      PRINT("kapi_rma2_put_immediate error!\n");
      return -1;
    }
  } else { // RRA read
    //rc = kapi_rma2_get_bt(rhandle, (uint16_t)dest_nodeid, 252, (void*)dest_rf_addr, (void*)tmp_addr, 8, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT, RMA2_CONN_RRA);
    tmp = kapi_rra_read((uint16_t)dest_nodeid, dest_rf_addr);
  }

  //rc = kapi_rma2_noti_fetch(rhandle, &noti);

  //kapi_rma2_noti_dump(noti);
  //kapi_rma2_noti_free(rhandle, 1);
  
  if(cmd_type == 1) {
    printk("0x%lx",tmp);
    printk("\n");
  }

  //kapi_rma2_close(&rhandle);
  //__free_page(page);

  return 0;
}

static void rra_exit(void)
{
  PRINT("Extoll RRA test unloaded.\n");
}


MODULE_LICENSE("GPL");
module_init(rra_init);
module_exit(rra_exit);
