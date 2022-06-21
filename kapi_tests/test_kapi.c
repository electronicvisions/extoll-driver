#include "test_kapi.h"
//Module paramerters
int mode = 0;
module_param(mode, int, 0);
MODULE_PARM_DESC(mode, "ping: 1, pong: 0, velo test with only one module: 2\n");

static int __init kapi_test_init(void) 
{
	if(mode == 1) {
		PRINT("ping mode\n");
		kapi_ping();
	} else if(mode == 0){ 
		PRINT("pong mode\n");
		kapi_pong();
	} else {
		int recv_vpid;
		int recv_node;
		int i=0, j=0;
		uint64_t header=1234;

		VELO2_Handle *vhandle;

		uint64_t msg = 42, recv = 0;
		uint32_t srcid = 0, len = 0;
		uint8_t mtt = 0, tag = 0;

		char *buffer = kmalloc(120, GFP_KERNEL);
		char *rbuffer = kmalloc(120, GFP_KERNEL);

		memset(buffer, 'A', 120);
		memset(buffer, 'B', 120);

		kapi_velo2_open(&vhandle, -1);
		recv_vpid = kapi_velo2_get_vpid(vhandle);
		recv_node = kapi_velo2_get_nodeid(vhandle);


		for(j = 1; j<=120; j++) {
			for(i=0;i<10;i++){
				int error = 0;
				kapi_velo2_send(vhandle, recv_node, recv_vpid, buffer, j, 0, 0, 0, 0);
				kapi_velo2_receive(vhandle, rbuffer, &srcid, &len, &mtt, &tag, 0);
				error = memcmp(buffer, rbuffer, j);
				if(error) {
					PRINT("velo recv error! wrong data in interration %i of length %i\n", i, j);
					break;
				}
				memset(rbuffer, 'B', j);
			}
			PRINT("send receive for size %i done\n", j);
		}


		//copy header bytes to rbuffer array
		for(i=0; i<sizeof(header); i++) {
			buffer[i] = (header>>i*8)&0xff;
		}
		for(j = 1; j<=120-sizeof(header); j++) {
			for(i=0;i<10;i++){
				int error = 0;
				kapi_velo2_send_header(vhandle, recv_node, recv_vpid, buffer+sizeof(header), j, &header, 1, 0, 0, 0, 0);
				kapi_velo2_receive(vhandle, rbuffer, &srcid, &len, &mtt, &tag, 0);
				error = memcmp(buffer, rbuffer, j);
				if(error) {
					PRINT("velo recv error for recv with header! wrong data in interration %i of length %i\n", i, len);
					PRINT("received bytes:\n");
					for(i=0; i<j+sizeof(header); i++) {
						printk("%02x | %02x\n", (rbuffer[i])&0xff, (buffer[i])&0xff);
					}
					break;
				}
				memset(rbuffer, 'B', j);
			}
			PRINT("send receive with header for size %i done\n", j);
		}
		kapi_velo2_close(&vhandle);
	}

	return -ENODEV;
}

static void kapi_test_exit(void)
{
  PRINT("EXTOLL kernel API test unloaded\n");
}

MODULE_LICENSE("GPL");
module_init(kapi_test_init);
module_exit(kapi_test_exit);
