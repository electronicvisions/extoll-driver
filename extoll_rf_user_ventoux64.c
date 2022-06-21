#include "extoll_rf_user.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

static int rf_fd;
volatile long unsigned int* base_address_ptr; 



//==========================================================
// Register access functions
//==========================================================

//----------------------------------------------------------
// Functions for instance extoll_rf:info_rf:driver
//----------------------------------------------------------
long unsigned int
get_extoll_rf_info_rf_driver()
{
	return *((uint64_t*)(((void*)base_address_ptr)+16384)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:info_rf:node
//----------------------------------------------------------
void
set_extoll_rf_info_rf_node(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+16392)) = value; 

}

long unsigned int
get_extoll_rf_info_rf_node()
{
	return *((uint64_t*)(((void*)base_address_ptr)+16392)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:info_rf:management_sw
//----------------------------------------------------------
void
set_extoll_rf_info_rf_management_sw(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+16400)) = value; 

}

long unsigned int
get_extoll_rf_info_rf_management_sw()
{
	return *((uint64_t*)(((void*)base_address_ptr)+16400)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:info_rf:ip_addresses
//----------------------------------------------------------
void
set_extoll_rf_info_rf_ip_addresses(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+16408)) = value; 

}

long unsigned int
get_extoll_rf_info_rf_ip_addresses()
{
	return *((uint64_t*)(((void*)base_address_ptr)+16408)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:info_rf:mgt_ip_addresses
//----------------------------------------------------------
void
set_extoll_rf_info_rf_mgt_ip_addresses(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+16416)) = value; 

}

long unsigned int
get_extoll_rf_info_rf_mgt_ip_addresses()
{
	return *((uint64_t*)(((void*)base_address_ptr)+16416)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:info_rf:tsc
//----------------------------------------------------------
void
set_extoll_rf_info_rf_tsc(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+16424)) = value; 

}

long unsigned int
get_extoll_rf_info_rf_tsc()
{
	return *((uint64_t*)(((void*)base_address_ptr)+16424)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:info_rf:tsc_global_load_value
//----------------------------------------------------------
void
set_extoll_rf_info_rf_tsc_global_load_value(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+16432)) = value; 

}

long unsigned int
get_extoll_rf_info_rf_tsc_global_load_value()
{
	return *((uint64_t*)(((void*)base_address_ptr)+16432)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:info_rf:scratchpad:scratchpad
//----------------------------------------------------------
void
set_extoll_rf_info_rf_scratchpad_scratchpad(long unsigned int index_inst, long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+16440+index_inst*8)) = value; 

}

long unsigned int
get_extoll_rf_info_rf_scratchpad_scratchpad(long unsigned int index_inst)
{
	return *((uint64_t*)(((void*)base_address_ptr)+16440+index_inst*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:info_rf:tsc_global_load_enable
//----------------------------------------------------------
void
set_extoll_rf_info_rf_tsc_global_load_enable(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+16504)) = value; 

}

long unsigned int
get_extoll_rf_info_rf_tsc_global_load_enable()
{
	return *((uint64_t*)(((void*)base_address_ptr)+16504)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:info_rf:timer_interrupt
//----------------------------------------------------------
void
set_extoll_rf_info_rf_timer_interrupt(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+16512)) = value; 

}

long unsigned int
get_extoll_rf_info_rf_timer_interrupt()
{
	return *((uint64_t*)(((void*)base_address_ptr)+16512)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:i2c_rf:i2c
//----------------------------------------------------------
void
set_extoll_rf_i2c_rf_i2c(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+18432)) = value; 

}

long unsigned int
get_extoll_rf_i2c_rf_i2c()
{
	return *((uint64_t*)(((void*)base_address_ptr)+18432)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:i2c_rf:si570
//----------------------------------------------------------
long unsigned int
get_extoll_rf_i2c_rf_si570()
{
	return *((uint64_t*)(((void*)base_address_ptr)+18440)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:i2c_rf:rsvd0
//----------------------------------------------------------
long unsigned int
get_extoll_rf_i2c_rf_rsvd0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+18448)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:i2c_rf:rsvd1
//----------------------------------------------------------
long unsigned int
get_extoll_rf_i2c_rf_rsvd1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+18456)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:i2c_rf:config
//----------------------------------------------------------
void
set_extoll_rf_i2c_rf_config(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+18464)) = value; 

}

long unsigned int
get_extoll_rf_i2c_rf_config()
{
	return *((uint64_t*)(((void*)base_address_ptr)+18464)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:i2c_rf:sysmon
//----------------------------------------------------------
long unsigned int
get_extoll_rf_i2c_rf_sysmon()
{
	return *((uint64_t*)(((void*)base_address_ptr)+18472)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:i2c_rf:sysmon_interface
//----------------------------------------------------------
void
set_extoll_rf_i2c_rf_sysmon_interface(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+19456+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_i2c_rf_sysmon_interface(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+19456+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:pflash_rf:ctrl
//----------------------------------------------------------
void
set_extoll_rf_pflash_rf_ctrl(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+20480)) = value; 

}

long unsigned int
get_extoll_rf_pflash_rf_ctrl()
{
	return *((uint64_t*)(((void*)base_address_ptr)+20480)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:pflash_rf:base_addr
//----------------------------------------------------------
void
set_extoll_rf_pflash_rf_base_addr(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+20488)) = value; 

}

long unsigned int
get_extoll_rf_pflash_rf_base_addr()
{
	return *((uint64_t*)(((void*)base_address_ptr)+20488)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:pflash_rf:buffer_data
//----------------------------------------------------------
void
set_extoll_rf_pflash_rf_buffer_data(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+20736+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_pflash_rf_buffer_data(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+20736+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:htax_bridge_rf:intvl:upper
//----------------------------------------------------------
void
set_extoll_rf_htax_bridge_rf_intvl_upper(long unsigned int index_inst, long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+20992+index_inst*24)) = value; 

}

long unsigned int
get_extoll_rf_htax_bridge_rf_intvl_upper(long unsigned int index_inst)
{
	return *((uint64_t*)(((void*)base_address_ptr)+20992+index_inst*24)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:htax_bridge_rf:intvl:lower
//----------------------------------------------------------
void
set_extoll_rf_htax_bridge_rf_intvl_lower(long unsigned int index_inst, long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21000+index_inst*24)) = value; 

}

long unsigned int
get_extoll_rf_htax_bridge_rf_intvl_lower(long unsigned int index_inst)
{
	return *((uint64_t*)(((void*)base_address_ptr)+21000+index_inst*24)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:htax_bridge_rf:intvl:control
//----------------------------------------------------------
void
set_extoll_rf_htax_bridge_rf_intvl_control(long unsigned int index_inst, long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21008+index_inst*24)) = value; 

}

long unsigned int
get_extoll_rf_htax_bridge_rf_intvl_control(long unsigned int index_inst)
{
	return *((uint64_t*)(((void*)base_address_ptr)+21008+index_inst*24)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:htax_bridge_rf:general
//----------------------------------------------------------
void
set_extoll_rf_htax_bridge_rf_general(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21112)) = value; 

}

long unsigned int
get_extoll_rf_htax_bridge_rf_general()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21112)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:htax_bridge_rf:debug
//----------------------------------------------------------
long unsigned int
get_extoll_rf_htax_bridge_rf_debug()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21120)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:htax_bridge_rf:posted_counter
//----------------------------------------------------------
void
set_extoll_rf_htax_bridge_rf_posted_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21128)) = value; 

}

long unsigned int
get_extoll_rf_htax_bridge_rf_posted_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21128)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:htax_bridge_rf:nonposted_counter
//----------------------------------------------------------
void
set_extoll_rf_htax_bridge_rf_nonposted_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21136)) = value; 

}

long unsigned int
get_extoll_rf_htax_bridge_rf_nonposted_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21136)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:htax_bridge_rf:response_counter
//----------------------------------------------------------
void
set_extoll_rf_htax_bridge_rf_response_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21144)) = value; 

}

long unsigned int
get_extoll_rf_htax_bridge_rf_response_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21144)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:htax_bridge_rf:discarded_counter
//----------------------------------------------------------
void
set_extoll_rf_htax_bridge_rf_discarded_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21152)) = value; 

}

long unsigned int
get_extoll_rf_htax_bridge_rf_discarded_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21152)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:htax_bridge_rf:error_ecc
//----------------------------------------------------------
void
set_extoll_rf_htax_bridge_rf_error_ecc(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21160)) = value; 

}

long unsigned int
get_extoll_rf_htax_bridge_rf_error_ecc()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21160)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:htax_rf:debug_0
//----------------------------------------------------------
long unsigned int
get_extoll_rf_htax_rf_debug_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21248)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:htax_rf:debug_1
//----------------------------------------------------------
long unsigned int
get_extoll_rf_htax_rf_debug_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21256)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:htax_rf:debug_2
//----------------------------------------------------------
long unsigned int
get_extoll_rf_htax_rf_debug_2()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21264)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:htax_rf:port:debug
//----------------------------------------------------------
long unsigned int
get_extoll_rf_htax_rf_port_debug(long unsigned int index_inst)
{
	return *((uint64_t*)(((void*)base_address_ptr)+21272+index_inst*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n0:hp2np_counter
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n0_hp2np_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21504)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n0_hp2np_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21504)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n0:np2hp_counter
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n0_np2hp_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21512)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n0_np2hp_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21512)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n0:np_debug_0
//----------------------------------------------------------
long unsigned int
get_extoll_rf_np_top_rf_n0_np_debug_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21520)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n0:general
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n0_general(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21528)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n0_general()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21528)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n0:credits_0
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n0_credits_0(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21536)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n0_credits_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21536)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n0:credits_1
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n0_credits_1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21544)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n0_credits_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21544)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n0:avail_fcc
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n0_avail_fcc(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21552)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n0_avail_fcc()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21552)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n0:raw_ctrl
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n0_raw_ctrl(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21560)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n0_raw_ctrl()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21560)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n0:ln:raw
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n0_ln_raw(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21568)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n0_ln_raw()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21568)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n0:np_debug_1
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n0_np_debug_1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21576)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n0_np_debug_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21576)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n1:hp2np_counter
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n1_hp2np_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21632)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n1_hp2np_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21632)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n1:np2hp_counter
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n1_np2hp_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21640)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n1_np2hp_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21640)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n1:np_debug_0
//----------------------------------------------------------
long unsigned int
get_extoll_rf_np_top_rf_n1_np_debug_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21648)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n1:general
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n1_general(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21656)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n1_general()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21656)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n1:credits_0
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n1_credits_0(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21664)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n1_credits_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21664)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n1:credits_1
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n1_credits_1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21672)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n1_credits_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21672)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n1:avail_fcc
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n1_avail_fcc(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21680)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n1_avail_fcc()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21680)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n1:raw_ctrl
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n1_raw_ctrl(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21688)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n1_raw_ctrl()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21688)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n1:ln:raw
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n1_ln_raw(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21696)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n1_ln_raw()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21696)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n1:np_debug_1
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n1_np_debug_1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21704)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n1_np_debug_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21704)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n2:hp2np_counter
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n2_hp2np_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21760)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n2_hp2np_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21760)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n2:np2hp_counter
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n2_np2hp_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21768)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n2_np2hp_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21768)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n2:np_debug_0
//----------------------------------------------------------
long unsigned int
get_extoll_rf_np_top_rf_n2_np_debug_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21776)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n2:general
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n2_general(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21784)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n2_general()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21784)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n2:credits_0
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n2_credits_0(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21792)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n2_credits_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21792)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n2:credits_1
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n2_credits_1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21800)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n2_credits_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21800)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n2:avail_fcc
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n2_avail_fcc(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21808)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n2_avail_fcc()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21808)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n2:raw_ctrl
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n2_raw_ctrl(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21816)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n2_raw_ctrl()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21816)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n2:ln:raw
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n2_ln_raw(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21824)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n2_ln_raw()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21824)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n2:np_debug_1
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n2_np_debug_1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21832)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n2_np_debug_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21832)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n3:hp2np_counter
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n3_hp2np_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21888)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n3_hp2np_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21888)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n3:np2hp_counter
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n3_np2hp_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21896)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n3_np2hp_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21896)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n3:np_debug_0
//----------------------------------------------------------
long unsigned int
get_extoll_rf_np_top_rf_n3_np_debug_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21904)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n3:general
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n3_general(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21912)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n3_general()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21912)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n3:credits_0
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n3_credits_0(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21920)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n3_credits_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21920)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n3:credits_1
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n3_credits_1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21928)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n3_credits_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21928)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n3:avail_fcc
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n3_avail_fcc(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21936)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n3_avail_fcc()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21936)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n3:raw_ctrl
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n3_raw_ctrl(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21944)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n3_raw_ctrl()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21944)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n3:ln:raw
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n3_ln_raw(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21952)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n3_ln_raw()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21952)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:np_top_rf:n3:np_debug_1
//----------------------------------------------------------
void
set_extoll_rf_np_top_rf_n3_np_debug_1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+21960)) = value; 

}

long unsigned int
get_extoll_rf_np_top_rf_n3_np_debug_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+21960)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:smfu_rf:status_control
//----------------------------------------------------------
void
set_extoll_rf_smfu_rf_status_control(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+22528)) = value; 

}

long unsigned int
get_extoll_rf_smfu_rf_status_control()
{
	return *((uint64_t*)(((void*)base_address_ptr)+22528)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:smfu_rf:traffic_class
//----------------------------------------------------------
void
set_extoll_rf_smfu_rf_traffic_class(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+22536)) = value; 

}

long unsigned int
get_extoll_rf_smfu_rf_traffic_class()
{
	return *((uint64_t*)(((void*)base_address_ptr)+22536)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:smfu_rf:timeout_control
//----------------------------------------------------------
void
set_extoll_rf_smfu_rf_timeout_control(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+22544)) = value; 

}

long unsigned int
get_extoll_rf_smfu_rf_timeout_control()
{
	return *((uint64_t*)(((void*)base_address_ptr)+22544)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:smfu_rf:counter_reset
//----------------------------------------------------------
void
set_extoll_rf_smfu_rf_counter_reset(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+22552)) = value; 

}

long unsigned int
get_extoll_rf_smfu_rf_counter_reset()
{
	return *((uint64_t*)(((void*)base_address_ptr)+22552)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:smfu_rf:sent_count_np
//----------------------------------------------------------
long unsigned int
get_extoll_rf_smfu_rf_sent_count_np()
{
	return *((uint64_t*)(((void*)base_address_ptr)+22560)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:smfu_rf:sent_count_p
//----------------------------------------------------------
long unsigned int
get_extoll_rf_smfu_rf_sent_count_p()
{
	return *((uint64_t*)(((void*)base_address_ptr)+22568)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:smfu_rf:sent_count_rsp
//----------------------------------------------------------
long unsigned int
get_extoll_rf_smfu_rf_sent_count_rsp()
{
	return *((uint64_t*)(((void*)base_address_ptr)+22576)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:smfu_rf:rcvd_count_np
//----------------------------------------------------------
long unsigned int
get_extoll_rf_smfu_rf_rcvd_count_np()
{
	return *((uint64_t*)(((void*)base_address_ptr)+22584)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:smfu_rf:rcvd_count_p
//----------------------------------------------------------
long unsigned int
get_extoll_rf_smfu_rf_rcvd_count_p()
{
	return *((uint64_t*)(((void*)base_address_ptr)+22592)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:smfu_rf:rcvd_count_rsp
//----------------------------------------------------------
long unsigned int
get_extoll_rf_smfu_rf_rcvd_count_rsp()
{
	return *((uint64_t*)(((void*)base_address_ptr)+22600)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:smfu_rf:misc_count
//----------------------------------------------------------
void
set_extoll_rf_smfu_rf_misc_count(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+22608)) = value; 

}

long unsigned int
get_extoll_rf_smfu_rf_misc_count()
{
	return *((uint64_t*)(((void*)base_address_ptr)+22608)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:smfu_rf:oStartAddr
//----------------------------------------------------------
void
set_extoll_rf_smfu_rf_oStartAddr(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+22616)) = value; 

}

long unsigned int
get_extoll_rf_smfu_rf_oStartAddr()
{
	return *((uint64_t*)(((void*)base_address_ptr)+22616)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:smfu_rf:tStartAddr_default
//----------------------------------------------------------
void
set_extoll_rf_smfu_rf_tStartAddr_default(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+22624)) = value; 

}

long unsigned int
get_extoll_rf_smfu_rf_tStartAddr_default()
{
	return *((uint64_t*)(((void*)base_address_ptr)+22624)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:smfu_rf:nNodeOffset
//----------------------------------------------------------
void
set_extoll_rf_smfu_rf_nNodeOffset(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+22632)) = value; 

}

long unsigned int
get_extoll_rf_smfu_rf_nNodeOffset()
{
	return *((uint64_t*)(((void*)base_address_ptr)+22632)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:smfu_rf:addr_mask
//----------------------------------------------------------
void
set_extoll_rf_smfu_rf_addr_mask(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+22640)) = value; 

}

long unsigned int
get_extoll_rf_smfu_rf_addr_mask()
{
	return *((uint64_t*)(((void*)base_address_ptr)+22640)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:smfu_rf:rsvd_0
//----------------------------------------------------------

//----------------------------------------------------------
// Functions for instance extoll_rf:smfu_rf:interval:control
//----------------------------------------------------------
void
set_extoll_rf_smfu_rf_interval_control(long unsigned int index_inst, long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+22656+index_inst*32)) = value; 

}

long unsigned int
get_extoll_rf_smfu_rf_interval_control(long unsigned int index_inst)
{
	return *((uint64_t*)(((void*)base_address_ptr)+22656+index_inst*32)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:smfu_rf:interval:startaddr
//----------------------------------------------------------
void
set_extoll_rf_smfu_rf_interval_startaddr(long unsigned int index_inst, long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+22664+index_inst*32)) = value; 

}

long unsigned int
get_extoll_rf_smfu_rf_interval_startaddr(long unsigned int index_inst)
{
	return *((uint64_t*)(((void*)base_address_ptr)+22664+index_inst*32)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:smfu_rf:interval:endaddr
//----------------------------------------------------------
void
set_extoll_rf_smfu_rf_interval_endaddr(long unsigned int index_inst, long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+22672+index_inst*32)) = value; 

}

long unsigned int
get_extoll_rf_smfu_rf_interval_endaddr(long unsigned int index_inst)
{
	return *((uint64_t*)(((void*)base_address_ptr)+22672+index_inst*32)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:smfu_rf:interval:counter
//----------------------------------------------------------
long unsigned int
get_extoll_rf_smfu_rf_interval_counter(long unsigned int index_inst)
{
	return *((uint64_t*)(((void*)base_address_ptr)+22680+index_inst*32)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:smfu_rf:vpid:tStartAddr
//----------------------------------------------------------
void
set_extoll_rf_smfu_rf_vpid_tStartAddr(long unsigned int index_inst, long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+23168+index_inst*8)) = value; 

}

long unsigned int
get_extoll_rf_smfu_rf_vpid_tStartAddr(long unsigned int index_inst)
{
	return *((uint64_t*)(((void*)base_address_ptr)+23168+index_inst*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:atu_rf:control
//----------------------------------------------------------
void
set_extoll_rf_atu_rf_control(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+32768)) = value; 

}

long unsigned int
get_extoll_rf_atu_rf_control()
{
	return *((uint64_t*)(((void*)base_address_ptr)+32768)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:atu_rf:cmd_interface
//----------------------------------------------------------
void
set_extoll_rf_atu_rf_cmd_interface(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+32776)) = value; 

}


//----------------------------------------------------------
// Functions for instance extoll_rf:atu_rf:cnt_0
//----------------------------------------------------------
void
set_extoll_rf_atu_rf_cnt_0(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+32784)) = value; 

}

long unsigned int
get_extoll_rf_atu_rf_cnt_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+32784)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:atu_rf:cnt_1
//----------------------------------------------------------
void
set_extoll_rf_atu_rf_cnt_1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+32792)) = value; 

}

long unsigned int
get_extoll_rf_atu_rf_cnt_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+32792)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:atu_rf:cnt_2
//----------------------------------------------------------
void
set_extoll_rf_atu_rf_cnt_2(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+32800)) = value; 

}

long unsigned int
get_extoll_rf_atu_rf_cnt_2()
{
	return *((uint64_t*)(((void*)base_address_ptr)+32800)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:atu_rf:cnt_3
//----------------------------------------------------------
void
set_extoll_rf_atu_rf_cnt_3(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+32808)) = value; 

}

long unsigned int
get_extoll_rf_atu_rf_cnt_3()
{
	return *((uint64_t*)(((void*)base_address_ptr)+32808)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:atu_rf:cnt_4
//----------------------------------------------------------
void
set_extoll_rf_atu_rf_cnt_4(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+32816)) = value; 

}

long unsigned int
get_extoll_rf_atu_rf_cnt_4()
{
	return *((uint64_t*)(((void*)base_address_ptr)+32816)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:atu_rf:cnt_5
//----------------------------------------------------------
void
set_extoll_rf_atu_rf_cnt_5(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+32824)) = value; 

}

long unsigned int
get_extoll_rf_atu_rf_cnt_5()
{
	return *((uint64_t*)(((void*)base_address_ptr)+32824)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:atu_rf:fifo_fill_level
//----------------------------------------------------------
void
set_extoll_rf_atu_rf_fifo_fill_level(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+32832)) = value; 

}

long unsigned int
get_extoll_rf_atu_rf_fifo_fill_level()
{
	return *((uint64_t*)(((void*)base_address_ptr)+32832)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:atu_rf:ecc
//----------------------------------------------------------
void
set_extoll_rf_atu_rf_ecc(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+32840)) = value; 

}

long unsigned int
get_extoll_rf_atu_rf_ecc()
{
	return *((uint64_t*)(((void*)base_address_ptr)+32840)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:atu_rf:excel_port
//----------------------------------------------------------
void
set_extoll_rf_atu_rf_excel_port(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+32848)) = value; 

}

long unsigned int
get_extoll_rf_atu_rf_excel_port()
{
	return *((uint64_t*)(((void*)base_address_ptr)+32848)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:atu_rf:excel_port_address
//----------------------------------------------------------
void
set_extoll_rf_atu_rf_excel_port_address(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+32856)) = value; 

}

long unsigned int
get_extoll_rf_atu_rf_excel_port_address()
{
	return *((uint64_t*)(((void*)base_address_ptr)+32856)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:atu_rf:preload
//----------------------------------------------------------
void
set_extoll_rf_atu_rf_preload(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+36864+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_atu_rf_preload(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+36864+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:atu_rf:gat
//----------------------------------------------------------
void
set_extoll_rf_atu_rf_gat(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+40960+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_atu_rf_gat(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+40960+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:snq_rf:trigger_enable
//----------------------------------------------------------
void
set_extoll_rf_snq_rf_trigger_enable(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+49152)) = value; 

}

long unsigned int
get_extoll_rf_snq_rf_trigger_enable()
{
	return *((uint64_t*)(((void*)base_address_ptr)+49152)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:snq_rf:trigger_now
//----------------------------------------------------------
void
set_extoll_rf_snq_rf_trigger_now(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+49160)) = value; 

}

long unsigned int
get_extoll_rf_snq_rf_trigger_now()
{
	return *((uint64_t*)(((void*)base_address_ptr)+49160)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:snq_rf:trigger_once_enable
//----------------------------------------------------------
void
set_extoll_rf_snq_rf_trigger_once_enable(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+49168)) = value; 

}


//----------------------------------------------------------
// Functions for instance extoll_rf:snq_rf:trigger_once
//----------------------------------------------------------
void
set_extoll_rf_snq_rf_trigger_once(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+49176)) = value; 

}

long unsigned int
get_extoll_rf_snq_rf_trigger_once()
{
	return *((uint64_t*)(((void*)base_address_ptr)+49176)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:snq_rf:queue_balt
//----------------------------------------------------------
void
set_extoll_rf_snq_rf_queue_balt(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+49184)) = value; 

}

long unsigned int
get_extoll_rf_snq_rf_queue_balt()
{
	return *((uint64_t*)(((void*)base_address_ptr)+49184)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:snq_rf:queue_mslt
//----------------------------------------------------------
void
set_extoll_rf_snq_rf_queue_mslt(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+49192)) = value; 

}

long unsigned int
get_extoll_rf_snq_rf_queue_mslt()
{
	return *((uint64_t*)(((void*)base_address_ptr)+49192)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:snq_rf:queue_wplt
//----------------------------------------------------------
long unsigned int
get_extoll_rf_snq_rf_queue_wplt()
{
	return *((uint64_t*)(((void*)base_address_ptr)+49200)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:snq_rf:queue_rplt
//----------------------------------------------------------
void
set_extoll_rf_snq_rf_queue_rplt(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+49208)) = value; 

}

long unsigned int
get_extoll_rf_snq_rf_queue_rplt()
{
	return *((uint64_t*)(((void*)base_address_ptr)+49208)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:snq_rf:irq_watermark
//----------------------------------------------------------
void
set_extoll_rf_snq_rf_irq_watermark(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+49216)) = value; 

}

long unsigned int
get_extoll_rf_snq_rf_irq_watermark()
{
	return *((uint64_t*)(((void*)base_address_ptr)+49216)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:snq_rf:irq_0
//----------------------------------------------------------
void
set_extoll_rf_snq_rf_irq_0(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+49224)) = value; 

}

long unsigned int
get_extoll_rf_snq_rf_irq_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+49224)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:snq_rf:irq_1
//----------------------------------------------------------
void
set_extoll_rf_snq_rf_irq_1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+49232)) = value; 

}

long unsigned int
get_extoll_rf_snq_rf_irq_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+49232)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:snq_rf:irq_2
//----------------------------------------------------------
void
set_extoll_rf_snq_rf_irq_2(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+49240)) = value; 

}

long unsigned int
get_extoll_rf_snq_rf_irq_2()
{
	return *((uint64_t*)(((void*)base_address_ptr)+49240)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:snq_rf:dbg_0
//----------------------------------------------------------
void
set_extoll_rf_snq_rf_dbg_0(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+49248)) = value; 

}

long unsigned int
get_extoll_rf_snq_rf_dbg_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+49248)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:snq_rf:execute
//----------------------------------------------------------
void
set_extoll_rf_snq_rf_execute(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+49256)) = value; 

}

long unsigned int
get_extoll_rf_snq_rf_execute()
{
	return *((uint64_t*)(((void*)base_address_ptr)+49256)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:snq_rf:htax
//----------------------------------------------------------
void
set_extoll_rf_snq_rf_htax(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+49264)) = value; 

}

long unsigned int
get_extoll_rf_snq_rf_htax()
{
	return *((uint64_t*)(((void*)base_address_ptr)+49264)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:snq_rf:program_ram
//----------------------------------------------------------
void
set_extoll_rf_snq_rf_program_ram(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+51200+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_snq_rf_program_ram(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+51200+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp0:routing
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp0_routing(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4194304)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp0_routing()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4194304)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp0:rcvd_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp0_rcvd_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4194312)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp0_rcvd_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4194312)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp0:send_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp0_send_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4194320)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp0_send_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4194320)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp0:debug
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp0_debug(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4194328)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp0_debug()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4194328)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp0:mcast
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp0_mcast(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4194816+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp0_mcast(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4194816+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp0:grt
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp0_grt(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4195328+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp0_grt(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4195328+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp0:lrt
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp0_lrt(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4202496+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp0_lrt(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4202496+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp1:routing
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp1_routing(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4210688)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp1_routing()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4210688)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp1:rcvd_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp1_rcvd_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4210696)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp1_rcvd_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4210696)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp1:send_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp1_send_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4210704)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp1_send_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4210704)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp1:debug
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp1_debug(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4210712)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp1_debug()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4210712)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp1:mcast
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp1_mcast(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4211200+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp1_mcast(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4211200+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp1:grt
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp1_grt(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4211712+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp1_grt(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4211712+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp1:lrt
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp1_lrt(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4218880+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp1_lrt(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4218880+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp2:routing
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp2_routing(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4227072)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp2_routing()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4227072)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp2:rcvd_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp2_rcvd_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4227080)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp2_rcvd_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4227080)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp2:send_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp2_send_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4227088)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp2_send_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4227088)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp2:debug
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp2_debug(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4227096)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp2_debug()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4227096)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp2:mcast
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp2_mcast(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4227584+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp2_mcast(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4227584+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp2:grt
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp2_grt(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4228096+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp2_grt(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4228096+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp2:lrt
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp2_lrt(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4235264+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp2_lrt(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4235264+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp3:routing
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp3_routing(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4243456)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp3_routing()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4243456)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp3:rcvd_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp3_rcvd_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4243464)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp3_rcvd_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4243464)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp3:send_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp3_send_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4243472)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp3_send_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4243472)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp3:debug
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp3_debug(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4243480)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp3_debug()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4243480)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp3:mcast
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp3_mcast(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4243968+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp3_mcast(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4243968+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp3:grt
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp3_grt(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4244480+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp3_grt(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4244480+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp3:lrt
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp3_lrt(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4251648+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp3_lrt(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4251648+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp4:routing
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp4_routing(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4259840)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp4_routing()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4259840)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp4:rcvd_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp4_rcvd_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4259848)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp4_rcvd_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4259848)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp4:send_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp4_send_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4259856)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp4_send_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4259856)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp4:debug
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp4_debug(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4259864)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp4_debug()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4259864)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp4:mcast
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp4_mcast(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4260352+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp4_mcast(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4260352+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp4:grt
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp4_grt(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4260864+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp4_grt(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4260864+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp4:lrt
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp4_lrt(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4268032+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp4_lrt(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4268032+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp5:routing
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp5_routing(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4276224)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp5_routing()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4276224)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp5:rcvd_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp5_rcvd_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4276232)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp5_rcvd_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4276232)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp5:send_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp5_send_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4276240)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp5_send_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4276240)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp5:debug
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp5_debug(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4276248)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp5_debug()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4276248)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp5:mcast
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp5_mcast(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4276736+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp5_mcast(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4276736+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp5:grt
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp5_grt(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4277248+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp5_grt(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4277248+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp5:lrt
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp5_lrt(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4284416+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp5_lrt(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4284416+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp6:routing
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp6_routing(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4292608)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp6_routing()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4292608)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp6:rcvd_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp6_rcvd_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4292616)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp6_rcvd_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4292616)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp6:send_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp6_send_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4292624)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp6_send_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4292624)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp6:debug
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp6_debug(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4292632)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp6_debug()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4292632)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp6:mcast
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp6_mcast(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4293120+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp6_mcast(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4293120+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp6:grt
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp6_grt(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4293632+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp6_grt(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4293632+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp6:lrt
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp6_lrt(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4300800+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp6_lrt(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4300800+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp7:routing
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp7_routing(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4308992)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp7_routing()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4308992)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp7:rcvd_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp7_rcvd_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4309000)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp7_rcvd_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4309000)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp7:send_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp7_send_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4309008)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp7_send_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4309008)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp7:debug
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp7_debug(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4309016)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp7_debug()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4309016)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp7:mcast
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp7_mcast(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4309504+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp7_mcast(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4309504+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp7:grt
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp7_grt(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4310016+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp7_grt(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4310016+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:inp7:lrt
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_inp7_lrt(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+4317184+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_inp7_lrt(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4317184+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp0:counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp0_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325376)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp0_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325376)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp0:fcc_credits
//----------------------------------------------------------
long unsigned int
get_extoll_rf_nw_xbar_rf_outp0_fcc_credits()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325384)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp0:general
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp0_general(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325392)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp0_general()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325392)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp0:credits_0
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp0_credits_0(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325400)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp0_credits_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325400)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp0:credits_1
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp0_credits_1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325408)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp0_credits_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325408)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp0:avail_fcc
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp0_avail_fcc(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325416)) = value; 

}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp1:counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp1_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325440)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp1_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325440)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp1:fcc_credits
//----------------------------------------------------------
long unsigned int
get_extoll_rf_nw_xbar_rf_outp1_fcc_credits()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325448)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp1:general
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp1_general(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325456)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp1_general()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325456)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp1:credits_0
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp1_credits_0(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325464)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp1_credits_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325464)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp1:credits_1
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp1_credits_1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325472)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp1_credits_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325472)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp1:avail_fcc
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp1_avail_fcc(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325480)) = value; 

}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp2:counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp2_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325504)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp2_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325504)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp2:fcc_credits
//----------------------------------------------------------
long unsigned int
get_extoll_rf_nw_xbar_rf_outp2_fcc_credits()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325512)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp2:general
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp2_general(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325520)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp2_general()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325520)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp2:credits_0
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp2_credits_0(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325528)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp2_credits_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325528)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp2:credits_1
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp2_credits_1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325536)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp2_credits_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325536)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp2:avail_fcc
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp2_avail_fcc(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325544)) = value; 

}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp3:counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp3_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325568)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp3_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325568)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp3:fcc_credits
//----------------------------------------------------------
long unsigned int
get_extoll_rf_nw_xbar_rf_outp3_fcc_credits()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325576)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp3:general
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp3_general(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325584)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp3_general()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325584)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp3:credits_0
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp3_credits_0(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325592)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp3_credits_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325592)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp3:credits_1
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp3_credits_1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325600)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp3_credits_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325600)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp3:avail_fcc
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp3_avail_fcc(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325608)) = value; 

}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp4:counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp4_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325632)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp4_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325632)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp4:fcc_credits
//----------------------------------------------------------
long unsigned int
get_extoll_rf_nw_xbar_rf_outp4_fcc_credits()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325640)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp4:general
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp4_general(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325648)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp4_general()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325648)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp4:credits_0
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp4_credits_0(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325656)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp4_credits_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325656)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp4:credits_1
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp4_credits_1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325664)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp4_credits_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325664)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp4:avail_fcc
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp4_avail_fcc(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325672)) = value; 

}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp5:counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp5_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325696)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp5_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325696)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp5:fcc_credits
//----------------------------------------------------------
long unsigned int
get_extoll_rf_nw_xbar_rf_outp5_fcc_credits()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325704)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp5:general
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp5_general(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325712)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp5_general()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325712)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp5:credits_0
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp5_credits_0(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325720)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp5_credits_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325720)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp5:credits_1
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp5_credits_1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325728)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp5_credits_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325728)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp5:avail_fcc
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp5_avail_fcc(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325736)) = value; 

}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp6:counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp6_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325760)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp6_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325760)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp6:fcc_credits
//----------------------------------------------------------
long unsigned int
get_extoll_rf_nw_xbar_rf_outp6_fcc_credits()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325768)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp6:general
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp6_general(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325776)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp6_general()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325776)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp6:credits_0
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp6_credits_0(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325784)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp6_credits_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325784)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp6:credits_1
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp6_credits_1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325792)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp6_credits_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325792)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp6:avail_fcc
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp6_avail_fcc(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325800)) = value; 

}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp7:counter
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp7_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325824)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp7_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325824)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp7:fcc_credits
//----------------------------------------------------------
long unsigned int
get_extoll_rf_nw_xbar_rf_outp7_fcc_credits()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325832)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp7:general
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp7_general(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325840)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp7_general()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325840)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp7:credits_0
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp7_credits_0(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325848)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp7_credits_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325848)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp7:credits_1
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp7_credits_1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325856)) = value; 

}

long unsigned int
get_extoll_rf_nw_xbar_rf_outp7_credits_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4325856)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:xbar_rf:outp7:avail_fcc
//----------------------------------------------------------
void
set_extoll_rf_nw_xbar_rf_outp7_avail_fcc(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4325864)) = value; 

}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:barrier_rf:units:work_set
//----------------------------------------------------------
void
set_extoll_rf_nw_barrier_rf_units_work_set(long unsigned int index_inst, long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4456448+index_inst*4096)) = value; 

}

long unsigned int
get_extoll_rf_nw_barrier_rf_units_work_set(long unsigned int index_inst)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4456448+index_inst*4096)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:barrier_rf:interrupts:work_set
//----------------------------------------------------------
void
set_extoll_rf_nw_barrier_rf_interrupts_work_set(long unsigned int index_inst, long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4521984+index_inst*4096)) = value; 

}

long unsigned int
get_extoll_rf_nw_barrier_rf_interrupts_work_set(long unsigned int index_inst)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4521984+index_inst*4096)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:barrier_rf:units_config:config
//----------------------------------------------------------
void
set_extoll_rf_nw_barrier_rf_units_config_config(long unsigned int index_inst, long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4538368+index_inst*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_barrier_rf_units_config_config(long unsigned int index_inst)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4538368+index_inst*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:barrier_rf:interrupts_config:config
//----------------------------------------------------------
void
set_extoll_rf_nw_barrier_rf_interrupts_config_config(long unsigned int index_inst, long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4538496+index_inst*8)) = value; 

}

long unsigned int
get_extoll_rf_nw_barrier_rf_interrupts_config_config(long unsigned int index_inst)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4538496+index_inst*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp0:counter
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp0_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587520)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp0_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587520)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp0:status
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp0_status(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587528)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp0_status()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587528)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp0:retransmission_counters
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp0_retransmission_counters(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587536)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp0_retransmission_counters()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587536)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp0:ids
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp0_ids(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587544)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp0_ids()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587544)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp0:lp_in
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp0_lp_in(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587552)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp0_lp_in()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587552)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp0:lp_fsm_states
//----------------------------------------------------------
long unsigned int
get_extoll_rf_nw_lp_top_rf_lp0_lp_fsm_states()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587560)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp0:lp_out_status
//----------------------------------------------------------
long unsigned int
get_extoll_rf_nw_lp_top_rf_lp0_lp_out_status()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587568)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp0:lp_out_arbiter
//----------------------------------------------------------
long unsigned int
get_extoll_rf_nw_lp_top_rf_lp0_lp_out_arbiter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587576)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp0:ack_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp0_ack_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587584)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp0_ack_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587584)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp0:credit_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp0_credit_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587592)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp0_credit_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587592)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp0:info_handler
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp0_info_handler(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587600)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp0_info_handler()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587600)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp0:timeout
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp0_timeout(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587608)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp0_timeout()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587608)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp0:debug
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp0_debug(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587616)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp0_debug()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587616)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp1:counter
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp1_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587648)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp1_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587648)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp1:status
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp1_status(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587656)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp1_status()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587656)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp1:retransmission_counters
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp1_retransmission_counters(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587664)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp1_retransmission_counters()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587664)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp1:ids
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp1_ids(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587672)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp1_ids()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587672)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp1:lp_in
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp1_lp_in(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587680)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp1_lp_in()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587680)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp1:lp_fsm_states
//----------------------------------------------------------
long unsigned int
get_extoll_rf_nw_lp_top_rf_lp1_lp_fsm_states()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587688)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp1:lp_out_status
//----------------------------------------------------------
long unsigned int
get_extoll_rf_nw_lp_top_rf_lp1_lp_out_status()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587696)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp1:lp_out_arbiter
//----------------------------------------------------------
long unsigned int
get_extoll_rf_nw_lp_top_rf_lp1_lp_out_arbiter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587704)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp1:ack_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp1_ack_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587712)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp1_ack_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587712)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp1:credit_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp1_credit_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587720)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp1_credit_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587720)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp1:info_handler
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp1_info_handler(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587728)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp1_info_handler()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587728)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp1:timeout
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp1_timeout(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587736)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp1_timeout()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587736)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp1:debug
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp1_debug(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587744)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp1_debug()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587744)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp2:counter
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp2_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587776)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp2_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587776)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp2:status
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp2_status(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587784)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp2_status()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587784)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp2:retransmission_counters
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp2_retransmission_counters(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587792)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp2_retransmission_counters()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587792)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp2:ids
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp2_ids(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587800)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp2_ids()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587800)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp2:lp_in
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp2_lp_in(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587808)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp2_lp_in()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587808)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp2:lp_fsm_states
//----------------------------------------------------------
long unsigned int
get_extoll_rf_nw_lp_top_rf_lp2_lp_fsm_states()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587816)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp2:lp_out_status
//----------------------------------------------------------
long unsigned int
get_extoll_rf_nw_lp_top_rf_lp2_lp_out_status()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587824)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp2:lp_out_arbiter
//----------------------------------------------------------
long unsigned int
get_extoll_rf_nw_lp_top_rf_lp2_lp_out_arbiter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587832)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp2:ack_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp2_ack_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587840)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp2_ack_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587840)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp2:credit_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp2_credit_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587848)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp2_credit_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587848)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp2:info_handler
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp2_info_handler(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587856)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp2_info_handler()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587856)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp2:timeout
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp2_timeout(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587864)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp2_timeout()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587864)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp2:debug
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp2_debug(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587872)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp2_debug()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587872)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp3:counter
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp3_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587904)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp3_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587904)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp3:status
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp3_status(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587912)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp3_status()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587912)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp3:retransmission_counters
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp3_retransmission_counters(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587920)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp3_retransmission_counters()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587920)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp3:ids
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp3_ids(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587928)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp3_ids()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587928)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp3:lp_in
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp3_lp_in(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587936)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp3_lp_in()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587936)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp3:lp_fsm_states
//----------------------------------------------------------
long unsigned int
get_extoll_rf_nw_lp_top_rf_lp3_lp_fsm_states()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587944)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp3:lp_out_status
//----------------------------------------------------------
long unsigned int
get_extoll_rf_nw_lp_top_rf_lp3_lp_out_status()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587952)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp3:lp_out_arbiter
//----------------------------------------------------------
long unsigned int
get_extoll_rf_nw_lp_top_rf_lp3_lp_out_arbiter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587960)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp3:ack_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp3_ack_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587968)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp3_ack_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587968)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp3:credit_counter
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp3_credit_counter(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587976)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp3_credit_counter()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587976)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp3:info_handler
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp3_info_handler(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587984)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp3_info_handler()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587984)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp3:timeout
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp3_timeout(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4587992)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp3_timeout()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4587992)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:lp_top_rf:lp3:debug
//----------------------------------------------------------
void
set_extoll_rf_nw_lp_top_rf_lp3_debug(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4588000)) = value; 

}

long unsigned int
get_extoll_rf_nw_lp_top_rf_lp3_debug()
{
	return *((uint64_t*)(((void*)base_address_ptr)+4588000)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:phy_rf:link:status
//----------------------------------------------------------
void
set_extoll_rf_nw_phy_rf_link_status(long unsigned int index_inst, long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4588032+index_inst*40)) = value; 

}

long unsigned int
get_extoll_rf_nw_phy_rf_link_status(long unsigned int index_inst)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4588032+index_inst*40)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:phy_rf:link:dbg_cnt
//----------------------------------------------------------
long unsigned int
get_extoll_rf_nw_phy_rf_link_dbg_cnt(long unsigned int index_inst)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4588040+index_inst*40)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:phy_rf:link:overrides
//----------------------------------------------------------
void
set_extoll_rf_nw_phy_rf_link_overrides(long unsigned int index_inst, long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4588048+index_inst*40)) = value; 

}

long unsigned int
get_extoll_rf_nw_phy_rf_link_overrides(long unsigned int index_inst)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4588048+index_inst*40)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:phy_rf:link:PRBS_errorcnt
//----------------------------------------------------------
long unsigned int
get_extoll_rf_nw_phy_rf_link_PRBS_errorcnt(long unsigned int index_inst)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4588056+index_inst*40)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:nw:phy_rf:link:ctrl
//----------------------------------------------------------
void
set_extoll_rf_nw_phy_rf_link_ctrl(long unsigned int index_inst, long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+4588064+index_inst*40)) = value; 

}

long unsigned int
get_extoll_rf_nw_phy_rf_link_ctrl(long unsigned int index_inst)
{
	return *((uint64_t*)(((void*)base_address_ptr)+4588064+index_inst*40)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:buffer_queue_rf:velo:general
//----------------------------------------------------------
void
set_extoll_rf_buffer_queue_rf_velo_general(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+12582912)) = value; 

}

long unsigned int
get_extoll_rf_buffer_queue_rf_velo_general()
{
	return *((uint64_t*)(((void*)base_address_ptr)+12582912)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:buffer_queue_rf:velo:debug
//----------------------------------------------------------
void
set_extoll_rf_buffer_queue_rf_velo_debug(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+12582920)) = value; 

}

long unsigned int
get_extoll_rf_buffer_queue_rf_velo_debug()
{
	return *((uint64_t*)(((void*)base_address_ptr)+12582920)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:buffer_queue_rf:velo:ub
//----------------------------------------------------------
void
set_extoll_rf_buffer_queue_rf_velo_ub(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+12584960+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_buffer_queue_rf_velo_ub(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+12584960+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:buffer_queue_rf:velo:dcq_base_dcq_ub
//----------------------------------------------------------
void
set_extoll_rf_buffer_queue_rf_velo_dcq_base_dcq_ub(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+12587008+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_buffer_queue_rf_velo_dcq_base_dcq_ub(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+12587008+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:buffer_queue_rf:velo:c_base_size_valid
//----------------------------------------------------------
void
set_extoll_rf_buffer_queue_rf_velo_c_base_size_valid(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+12589056+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_buffer_queue_rf_velo_c_base_size_valid(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+12589056+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:buffer_queue_rf:velo:n_base_size_valid
//----------------------------------------------------------
void
set_extoll_rf_buffer_queue_rf_velo_n_base_size_valid(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+12591104+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_buffer_queue_rf_velo_n_base_size_valid(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+12591104+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:buffer_queue_rf:velo:wp_lwp_dcq_rp
//----------------------------------------------------------
void
set_extoll_rf_buffer_queue_rf_velo_wp_lwp_dcq_rp(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+12593152+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_buffer_queue_rf_velo_wp_lwp_dcq_rp(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+12593152+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:buffer_queue_rf:velo:rp
//----------------------------------------------------------
void
set_extoll_rf_buffer_queue_rf_velo_rp(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+13631488+index_entry*4096)) = value; 

}

long unsigned int
get_extoll_rf_buffer_queue_rf_velo_rp(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+13631488+index_entry*4096)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:buffer_queue_rf:rma:general
//----------------------------------------------------------
void
set_extoll_rf_buffer_queue_rf_rma_general(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+14680064)) = value; 

}

long unsigned int
get_extoll_rf_buffer_queue_rf_rma_general()
{
	return *((uint64_t*)(((void*)base_address_ptr)+14680064)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:buffer_queue_rf:rma:debug
//----------------------------------------------------------
void
set_extoll_rf_buffer_queue_rf_rma_debug(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+14680072)) = value; 

}

long unsigned int
get_extoll_rf_buffer_queue_rf_rma_debug()
{
	return *((uint64_t*)(((void*)base_address_ptr)+14680072)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:buffer_queue_rf:rma:ub
//----------------------------------------------------------
void
set_extoll_rf_buffer_queue_rf_rma_ub(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+14682112+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_buffer_queue_rf_rma_ub(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+14682112+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:buffer_queue_rf:rma:dcq_base_dcq_ub
//----------------------------------------------------------
void
set_extoll_rf_buffer_queue_rf_rma_dcq_base_dcq_ub(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+14684160+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_buffer_queue_rf_rma_dcq_base_dcq_ub(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+14684160+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:buffer_queue_rf:rma:c_base_size_valid
//----------------------------------------------------------
void
set_extoll_rf_buffer_queue_rf_rma_c_base_size_valid(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+14686208+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_buffer_queue_rf_rma_c_base_size_valid(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+14686208+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:buffer_queue_rf:rma:n_base_size_valid
//----------------------------------------------------------
void
set_extoll_rf_buffer_queue_rf_rma_n_base_size_valid(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+14688256+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_buffer_queue_rf_rma_n_base_size_valid(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+14688256+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:buffer_queue_rf:rma:wp_lwp_dcq_rp
//----------------------------------------------------------
void
set_extoll_rf_buffer_queue_rf_rma_wp_lwp_dcq_rp(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+14690304+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_buffer_queue_rf_rma_wp_lwp_dcq_rp(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+14690304+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:buffer_queue_rf:rma:rp
//----------------------------------------------------------
void
set_extoll_rf_buffer_queue_rf_rma_rp(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+15728640+index_entry*4096)) = value; 

}

long unsigned int
get_extoll_rf_buffer_queue_rf_rma_rp(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+15728640+index_entry*4096)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:velo_rf:timeout
//----------------------------------------------------------
void
set_extoll_rf_velo_rf_timeout(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+18880512)) = value; 

}

long unsigned int
get_extoll_rf_velo_rf_timeout()
{
	return *((uint64_t*)(((void*)base_address_ptr)+18880512)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:velo_rf:completer
//----------------------------------------------------------
void
set_extoll_rf_velo_rf_completer(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+18880520)) = value; 

}

long unsigned int
get_extoll_rf_velo_rf_completer()
{
	return *((uint64_t*)(((void*)base_address_ptr)+18880520)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:velo_rf:counter_0
//----------------------------------------------------------
void
set_extoll_rf_velo_rf_counter_0(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+18880528)) = value; 

}

long unsigned int
get_extoll_rf_velo_rf_counter_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+18880528)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:velo_rf:counter_1
//----------------------------------------------------------
void
set_extoll_rf_velo_rf_counter_1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+18880536)) = value; 

}

long unsigned int
get_extoll_rf_velo_rf_counter_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+18880536)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:velo_rf:counter_2
//----------------------------------------------------------
void
set_extoll_rf_velo_rf_counter_2(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+18880544)) = value; 

}

long unsigned int
get_extoll_rf_velo_rf_counter_2()
{
	return *((uint64_t*)(((void*)base_address_ptr)+18880544)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:velo_rf:debug_0
//----------------------------------------------------------
long unsigned int
get_extoll_rf_velo_rf_debug_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+18880552)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:velo_rf:debug_1
//----------------------------------------------------------
void
set_extoll_rf_velo_rf_debug_1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+18880560)) = value; 

}

long unsigned int
get_extoll_rf_velo_rf_debug_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+18880560)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:velo_rf:node_vpid_prot_desc
//----------------------------------------------------------
void
set_extoll_rf_velo_rf_node_vpid_prot_desc(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+18876416+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_velo_rf_node_vpid_prot_desc(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+18876416+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:velo_rf:comp_prot_desc
//----------------------------------------------------------
void
set_extoll_rf_velo_rf_comp_prot_desc(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+18878464+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_velo_rf_comp_prot_desc(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+18878464+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:velo_rf:wcbuf_rf:timeout
//----------------------------------------------------------
void
set_extoll_rf_velo_rf_wcbuf_rf_timeout(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+17825792)) = value; 

}

long unsigned int
get_extoll_rf_velo_rf_wcbuf_rf_timeout()
{
	return *((uint64_t*)(((void*)base_address_ptr)+17825792)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:velo_rf:wcbuf_rf:errors0
//----------------------------------------------------------
void
set_extoll_rf_velo_rf_wcbuf_rf_errors0(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+17825800)) = value; 

}

long unsigned int
get_extoll_rf_velo_rf_wcbuf_rf_errors0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+17825800)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:velo_rf:wcbuf_rf:errors1
//----------------------------------------------------------
void
set_extoll_rf_velo_rf_wcbuf_rf_errors1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+17825808)) = value; 

}

long unsigned int
get_extoll_rf_velo_rf_wcbuf_rf_errors1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+17825808)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:velo_rf:wcbuf_rf:event_mirror
//----------------------------------------------------------
void
set_extoll_rf_velo_rf_wcbuf_rf_event_mirror(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+17825816)) = value; 

}

long unsigned int
get_extoll_rf_velo_rf_wcbuf_rf_event_mirror()
{
	return *((uint64_t*)(((void*)base_address_ptr)+17825816)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:velo_rf:wcbuf_rf:retry_mirror_base
//----------------------------------------------------------
void
set_extoll_rf_velo_rf_wcbuf_rf_retry_mirror_base(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+17825824)) = value; 

}

long unsigned int
get_extoll_rf_velo_rf_wcbuf_rf_retry_mirror_base()
{
	return *((uint64_t*)(((void*)base_address_ptr)+17825824)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:velo_rf:wcbuf_rf:ecc_status
//----------------------------------------------------------
void
set_extoll_rf_velo_rf_wcbuf_rf_ecc_status(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+17825832)) = value; 

}

long unsigned int
get_extoll_rf_velo_rf_wcbuf_rf_ecc_status()
{
	return *((uint64_t*)(((void*)base_address_ptr)+17825832)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:velo_rf:wcbuf_rf:state
//----------------------------------------------------------
void
set_extoll_rf_velo_rf_wcbuf_rf_state(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+16777216+index_entry*4096)) = value; 

}

long unsigned int
get_extoll_rf_velo_rf_wcbuf_rf_state(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+16777216+index_entry*4096)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:velo_rf:noti_interrupt_handler:int_ctrl
//----------------------------------------------------------

//----------------------------------------------------------
// Functions for instance extoll_rf:velo_rf:noti_interrupt_handler:int_vec
//----------------------------------------------------------
long unsigned int
get_extoll_rf_velo_rf_noti_interrupt_handler_int_vec(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+18874400+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:velo_rf:noti_interrupt_handler:int_retrig_vec
//----------------------------------------------------------
void
set_extoll_rf_velo_rf_noti_interrupt_handler_int_retrig_vec(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+18874432+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_velo_rf_noti_interrupt_handler_int_retrig_vec(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+18874432+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:config
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_config(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+23068800)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_config()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23068800)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:lock_base
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_lock_base(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+23068808)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_lock_base()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23068808)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:lock_cfg
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_lock_cfg(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+23068816)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_lock_cfg()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23068816)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:bq_timeout
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_bq_timeout(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+23068824)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_bq_timeout()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23068824)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:requester_error_ctrl
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_requester_error_ctrl(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+23072768)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_requester_error_ctrl()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23072768)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:requester_error_cnt_st
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_requester_error_cnt_st()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23072784)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:requester_error_cnt_0
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_requester_error_cnt_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23072792)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:requester_error_cnt_1
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_requester_error_cnt_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23072800)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:responder_error_ctrl
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_responder_error_ctrl(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+23072808)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_responder_error_ctrl()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23072808)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:responder_error_cnt_st
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_responder_error_cnt_st()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23072824)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:responder_error_cnt_0
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_responder_error_cnt_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23072832)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:responder_error_cnt_1
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_responder_error_cnt_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23072840)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:responder_error_cnt_2
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_responder_error_cnt_2()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23072848)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:completer_error_ctrl
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_completer_error_ctrl(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+23072856)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_completer_error_ctrl()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23072856)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:completer_error_cnt_st
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_completer_error_cnt_st()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23072872)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:completer_error_cnt_0
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_completer_error_cnt_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23072880)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:completer_error_cnt_1
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_completer_error_cnt_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23072888)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:completer_error_cnt_2
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_completer_error_cnt_2()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23072896)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:completer_error_cnt_3
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_completer_error_cnt_3()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23072904)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:error_ram_ecc
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_error_ram_ecc(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+23072912)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_error_ram_ecc()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23072912)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:vpid_table
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_vpid_table(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+23070720+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_vpid_table(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+23070720+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:requester_history
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_requester_history(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+23072776+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:responder_history
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_responder_history(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+23072816+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:completer_history
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_completer_history(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+23072864+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:wcbuf_rf:timeout
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_wcbuf_rf_timeout(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+22020096)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_wcbuf_rf_timeout()
{
	return *((uint64_t*)(((void*)base_address_ptr)+22020096)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:wcbuf_rf:errors0
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_wcbuf_rf_errors0(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+22020104)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_wcbuf_rf_errors0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+22020104)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:wcbuf_rf:errors1
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_wcbuf_rf_errors1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+22020112)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_wcbuf_rf_errors1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+22020112)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:wcbuf_rf:event_mirror
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_wcbuf_rf_event_mirror(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+22020120)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_wcbuf_rf_event_mirror()
{
	return *((uint64_t*)(((void*)base_address_ptr)+22020120)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:wcbuf_rf:retry_mirror_base
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_wcbuf_rf_retry_mirror_base(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+22020128)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_wcbuf_rf_retry_mirror_base()
{
	return *((uint64_t*)(((void*)base_address_ptr)+22020128)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:wcbuf_rf:ecc_status
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_wcbuf_rf_ecc_status(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+22020136)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_wcbuf_rf_ecc_status()
{
	return *((uint64_t*)(((void*)base_address_ptr)+22020136)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:wcbuf_rf:state
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_wcbuf_rf_state(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+20971520+index_entry*4096)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_wcbuf_rf_state(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+20971520+index_entry*4096)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:noti_interrupt_handler:int_ctrl
//----------------------------------------------------------

//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:noti_interrupt_handler:int_vec
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_noti_interrupt_handler_int_vec(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+23068704+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:noti_interrupt_handler:int_retrig_vec
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_noti_interrupt_handler_int_retrig_vec(long unsigned int index_entry, long unsigned int value)
{

	*((uint64_t*)(((void*)base_address_ptr)+23068736+index_entry*8)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_noti_interrupt_handler_int_retrig_vec(long unsigned int index_entry)
{
	return *((uint64_t*)(((void*)base_address_ptr)+23068736+index_entry*8)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:counter_control
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_perf_counter_control(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+23073280)) = value; 

}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:requester_perf_in_0
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_requester_perf_in_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073288)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:requester_perf_in_1
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_requester_perf_in_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073296)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:requester_perf_in_2
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_requester_perf_in_2()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073304)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:requester_perf_in_3
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_requester_perf_in_3()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073312)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:requester_perf_atu_0
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_requester_perf_atu_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073320)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:requester_perf_atu_1
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_requester_perf_atu_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073328)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:requester_perf_atu_2
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_requester_perf_atu_2()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073336)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:requester_perf_re_0
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_requester_perf_re_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073344)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:requester_perf_re_1
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_perf_requester_perf_re_1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+23073352)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_perf_requester_perf_re_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073352)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:requester_perf_re_2
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_requester_perf_re_2()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073360)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:requester_perf_re_3
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_perf_requester_perf_re_3(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+23073368)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_perf_requester_perf_re_3()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073368)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:requester_perf_out_0
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_requester_perf_out_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073376)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:requester_perf_out_1
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_requester_perf_out_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073384)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:requester_perf_out_2
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_requester_perf_out_2()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073392)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:requester_perf_out_3
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_requester_perf_out_3()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073400)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:requester_perf_out_4
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_requester_perf_out_4()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073408)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:requester_perf_out_5
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_requester_perf_out_5()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073416)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:requester_perf_out_6
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_perf_requester_perf_out_6(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+23073424)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_perf_requester_perf_out_6()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073424)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:requester_perf_noti
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_requester_perf_noti()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073432)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:responder_perf_in_0
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_responder_perf_in_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073440)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:responder_perf_in_1
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_responder_perf_in_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073448)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:responder_perf_atu_0
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_responder_perf_atu_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073456)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:responder_perf_atu_1
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_responder_perf_atu_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073464)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:responder_perf_atu_2
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_responder_perf_atu_2()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073472)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:responder_perf_re_0
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_responder_perf_re_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073480)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:responder_perf_re_1
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_perf_responder_perf_re_1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+23073488)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_perf_responder_perf_re_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073488)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:responder_perf_re_2
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_responder_perf_re_2()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073496)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:responder_perf_re_3
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_perf_responder_perf_re_3(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+23073504)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_perf_responder_perf_re_3()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073504)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:responder_perf_out_0
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_responder_perf_out_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073512)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:responder_perf_out_1
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_responder_perf_out_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073520)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:responder_perf_out_2
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_responder_perf_out_2()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073528)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:responder_perf_out_3
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_responder_perf_out_3()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073536)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:responder_perf_out_4
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_perf_responder_perf_out_4(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+23073544)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_perf_responder_perf_out_4()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073544)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:responder_perf_noti
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_responder_perf_noti()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073552)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:completer_perf_in_0
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_completer_perf_in_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073560)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:completer_perf_in_1
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_completer_perf_in_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073568)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:completer_perf_in_2
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_completer_perf_in_2()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073576)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:completer_perf_in_3
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_completer_perf_in_3()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073584)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:completer_perf_in_4
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_perf_completer_perf_in_4(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+23073592)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_perf_completer_perf_in_4()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073592)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:completer_perf_atu_0
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_completer_perf_atu_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073600)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:completer_perf_atu_1
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_completer_perf_atu_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073608)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:completer_perf_atu_2
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_completer_perf_atu_2()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073616)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:completer_perf_out_0
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_completer_perf_out_0()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073624)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:completer_perf_out_1
//----------------------------------------------------------
void
set_extoll_rf_rma_rf_perf_completer_perf_out_1(long unsigned int value)
{
	*((uint64_t*)(((void*)base_address_ptr)+23073632)) = value; 

}

long unsigned int
get_extoll_rf_rma_rf_perf_completer_perf_out_1()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073632)); 
}


//----------------------------------------------------------
// Functions for instance extoll_rf:rma_rf:perf:completer_perf_noti
//----------------------------------------------------------
long unsigned int
get_extoll_rf_rma_rf_perf_completer_perf_noti()
{
	return *((uint64_t*)(((void*)base_address_ptr)+23073640)); 
}



//==========================================================
// Helper function for bit filtering
//==========================================================
long unsigned int
bit_get(unsigned int bit_offset, unsigned int bit_length, long unsigned int value)
{
	uint64_t mask = 0;

	if (bit_length >= 64)
		mask = 0xffffffffffffffffull;
	else
		mask = (1ull << bit_length)-1;

	return (value >> bit_offset) & mask;
}

// Init and Close function for RF access
//----------------------------------------
int extoll_rf_open() { 

    //-- Open the driver file
    // FIXME Can the file name be generated from rfName ???
    rf_fd=open("/dev/extoll2_rf",O_RDWR);
    if ( rf_fd<0){
        perror("Opening EXTOLL2 RF device special file:");
        return -1;
    }
    //-- mmap the buffer
    base_address_ptr = mmap(
        0,                      /* preferred start  */
        32*1024*1024,           /* length in bytes  */
        PROT_READ | PROT_WRITE, /* protection flags */
        MAP_SHARED,             /* mapping flags    */
        rf_fd,                  /* file descriptor  */
        0                       /* offset           */
    );
    if (base_address_ptr==MAP_FAILED) {
                                       
        perror("Physcial EXTOLL2 RF mmap failed");
        return -1;
                                                       
    }
                                                       
    return 0;
}
void extoll_rf_close() {
    close(rf_fd);
}
