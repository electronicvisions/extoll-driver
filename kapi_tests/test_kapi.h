#include "../extoll_kapi.h"
#include <linux/module.h>
#include <asm/msr.h>

#define cycles_per_usec 2.5f

#define PRINT(...) printk(KERN_ALERT "TEST KAPI: " __VA_ARGS__)

//Module paramerters
int recv_node = 0;
module_param(recv_node, int, 0);
MODULE_PARM_DESC(recv_node, "In ping mode: receiving node id\n");
int recv_vpid = 0;
module_param(recv_vpid, int, 0);
MODULE_PARM_DESC(recv_vpid, "In ping mode: receiving vpid\n");

static void kapi_ping(void)
{
  RMA2_Handle *rhandle;
//  uint64_t guard = 0;
  VELO2_Handle *vhandle;

  uint64_t msg = 42, recv = 0;
  uint32_t srcid = 0, len = 0;
  uint8_t mtt = 0, tag = 0;

  unsigned int rma_vpid, rma_nodeid;
  char *buffer = kmalloc(4*1024*1024, GFP_KERNEL);
  void *remote = 0;

  int i=0, j=0;
  uint64_t start = 0, stop = 0, delta = 0;

  RMA2_Notification *noti = kmalloc(sizeof(*noti), GFP_KERNEL);

  kapi_velo2_open(&vhandle, -1);

  PRINT("connected to vpid %i on node %i, sending start package.\n", recv_vpid, recv_node);

  kapi_velo2_send(vhandle, recv_node, recv_vpid , &msg, sizeof(msg), 0, 0, 0, 0);


  PRINT("Starting VELO streaming test\n");
  for(j=1;j<=120;j++){
    for(i=0;i<1024;i++) {
      kapi_velo2_send(vhandle, recv_node, recv_vpid , buffer, j, 0, 0, 0, 0);
    }
  }
  PRINT("Starting VELO latency benchmark.\n");
  //warump
  for(i=0;i<100;i++){
    kapi_velo2_send(vhandle, recv_node, recv_vpid, buffer, 1, 0, 0, 0, 0);
    kapi_velo2_receive(vhandle, buffer, &srcid, &len, &mtt, &tag, 0);
  }

  //real benchmark
  for(j = 1; j<=120; j++) {
    rdtscll(start);
    for(i=0;i<1000;i++){
      kapi_velo2_send(vhandle, recv_node, recv_vpid, buffer, j, 0, 0, 0, 0);
      kapi_velo2_receive(vhandle, buffer, &srcid, &len, &mtt, &tag, 0);
    }
    rdtscll(stop);
    delta = stop-start;
    PRINT("latency velo %i byte message: %llu ns\n", j, delta/(1000*5)); //10000 * 2 (half round trip) *2.5 (cycles per usec)
  }


  kapi_velo2_receive(vhandle, &rma_nodeid, &srcid, &len, &mtt, &tag, 0);
  kapi_velo2_receive(vhandle, &rma_vpid, &srcid, &len, &mtt, &tag, 0);
  kapi_velo2_receive(vhandle, &remote, &srcid, &len, &mtt, &tag, 0);
  //PRINT("remote rma node %i and vpid %i, address: %p\n", rma_nodeid, rma_vpid, remote);
  
  PRINT("RMA test\n");
  kapi_rma2_open(&rhandle, -1);

  for(i=0;i<1050;i++) {
    kapi_rma2_put_bt(rhandle, rma_nodeid, rma_vpid, buffer, remote, (4*1024*1024)-1050+i, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT, RMA2_CONN_DEFAULT);
    //printk ("ping did send %i rma messages\n", i); 
  }

  kapi_rma2_close(&rhandle);
  PRINT("RMA test done\n");
 
  //kapi_velo2_receive(vhandle, &recv, &srcid, &len, &mtt, &tag, 0);
  kapi_velo2_close(&vhandle);
  kfree(buffer);
  kfree(noti);
}

static void kapi_pong(void)
{
  RMA2_Handle *rhandle;
  VELO2_Handle *vhandle;
  uint64_t recv = 0;
  uint32_t srcid, len;
  uint8_t mtt, tag;
  unsigned int vpid;
  unsigned int nodeid;
  int i=0, j=0;
  char *buffer = kmalloc(4*1024*1024, GFP_KERNEL);
  RMA2_Notification *noti = kmalloc(sizeof(*noti), GFP_KERNEL);

  if(buffer == NULL || noti == NULL) {
    PRINT("no buffer allocatesd! buffer: %p, noti %p\n", buffer, noti);
  }

  kapi_velo2_open(&vhandle, -1);
  PRINT("my node: %i, my vpid %i\n",kapi_velo2_get_nodeid(vhandle), kapi_velo2_get_vpid(vhandle));
  kapi_velo2_receive(vhandle, &recv, &srcid, &len, &mtt, &tag,0);
  //PRINT("remote srcid: %x node %i, vpid %x\n", srcid, srcid&0xffff, srcid>>16);
  vpid = srcid>>16;
  nodeid = srcid&0xfff;

  for(j=1;j<=120;j++){
    for(i=0;i<1024;i++) {
      kapi_velo2_receive(vhandle, buffer, &srcid, &len, &mtt, &tag,0);
    }
  }

  PRINT("received all streaming messages, starting warum on pong side\n");

  //latency benchmark: warmup
  for(i=0;i<100;i++){
    kapi_velo2_receive(vhandle, buffer, &srcid, &len, &mtt, &tag, 0);
    kapi_velo2_send(vhandle, nodeid, vpid, buffer, 1, 0, 0, 0, 0);
  }

  //real benchmark
  for(j = 1; j<=120; j++) {
    for(i=0;i<1000;i++){
      kapi_velo2_receive(vhandle, buffer, &srcid, &len, &mtt, &tag, 0);
      kapi_velo2_send(vhandle, nodeid, vpid, buffer, j, 0, 0, 0, 0);
    }
  }
  
  kapi_rma2_open(&rhandle, -1);

  recv = kapi_rma2_get_nodeid(rhandle);
  kapi_velo2_send(vhandle, nodeid, vpid, &recv, sizeof(recv), 0, 0, 0, 0);
  recv = kapi_rma2_get_vpid(rhandle);
  kapi_velo2_send(vhandle, nodeid, vpid, &recv, sizeof(recv), 0, 0, 0, 0);
  kapi_velo2_send(vhandle, nodeid, vpid, &buffer, sizeof(buffer), 0,0,0,0);

  PRINT("VELO: received value: %llu\n", recv);

  for(i=0;i<1050;i++) {
    long int size = 0;
    kapi_rma2_noti_fetch(rhandle, &noti);
    /*size = kapi_rma2_noti_get_size(noti);
    PRINT("rma message #%i, sequence number: %li\n", i, size);
    //kapi_rma2_noti_dump(noti);*/
  }


  //kapi_velo2_send(vhandle, nodeid, vpid , &recv, sizeof(recv), 0, 0, 0, 0);
  kapi_velo2_close(&vhandle);

  kapi_rma2_close(&rhandle);

  kfree(noti);
  kfree(buffer);
}

