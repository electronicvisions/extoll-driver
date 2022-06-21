/*
 *  This file is part of the  Linux Kernel Driver Package for EXTOLL R2.
 *
 *  Copyright (C) 2011 EXTOLL GmbH
 *
 *  Written by Mondrian Nuessle (2011)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef RF_MAP_SYSFS_H 
#define RF_MAP_SYSFS_H 

#include<linux/device.h> 
#include<linux/sched.h> 
#include<linux/kernel.h> 
#include "extolldrv_user.h"


//==========================================================
// Register access functions
//==========================================================

//----------------------------------------------------------
// Functions for unit extoll_rf
//----------------------------------------------------------

//----------------------------------------------------------
// Functions for unit pcie
//----------------------------------------------------------
void set_extoll_rf_pcie_kla_design(long unsigned int value);
long unsigned int get_extoll_rf_pcie_kla_design(void);

//----------------------------------------------------------
// Functions for unit pcie_pcie_tlp_control
//----------------------------------------------------------
void set_extoll_rf_pcie_pcie_pcie_tlp_control_pcie_conf(long unsigned int value);
long unsigned int get_extoll_rf_pcie_pcie_pcie_tlp_control_pcie_conf(void);
void set_extoll_rf_pcie_pcie_pcie_tlp_control_pcie_req_cmd(long unsigned int value);
long unsigned int get_extoll_rf_pcie_pcie_pcie_tlp_control_pcie_req_cmd(void);
void set_extoll_rf_pcie_pcie_pcie_tlp_control_pcie_compl_cmd(long unsigned int value);
long unsigned int get_extoll_rf_pcie_pcie_pcie_tlp_control_pcie_compl_cmd(void);
void set_extoll_rf_pcie_pcie_pcie_tlp_control_pcie_status_reg(long unsigned int value);
long unsigned int get_extoll_rf_pcie_pcie_pcie_tlp_control_pcie_status_reg(void);
void set_extoll_rf_pcie_pcie_pcie_tlp_control_pcie_req_data_pcie_req_data_reg(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_pcie_pcie_pcie_tlp_control_pcie_compl_data_pcie_compl_data_reg(long unsigned int index_inst);

//----------------------------------------------------------
// Functions for unit pcie_bridge_rf
//----------------------------------------------------------
void set_extoll_rf_pcie_pcie_bridge_rf_htoc_to_pcie(long unsigned int value);
long unsigned int get_extoll_rf_pcie_pcie_bridge_rf_htoc_to_pcie(void);
void set_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_cfg(long unsigned int value);
long unsigned int get_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_cfg(void);
void set_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_interrupt_0(long unsigned int value);
long unsigned int get_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_interrupt_0(void);
void set_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_interrupt_1(long unsigned int value);
long unsigned int get_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_interrupt_1(void);
void set_extoll_rf_pcie_pcie_bridge_rf_tag_map(long unsigned int value);
long unsigned int get_extoll_rf_pcie_pcie_bridge_rf_tag_map(void);
void set_extoll_rf_pcie_pcie_bridge_rf_htoc_to_pcie_p_counter(long unsigned int value);
long unsigned int get_extoll_rf_pcie_pcie_bridge_rf_htoc_to_pcie_p_counter(void);
void set_extoll_rf_pcie_pcie_bridge_rf_htoc_to_pcie_np_counter(long unsigned int value);
long unsigned int get_extoll_rf_pcie_pcie_bridge_rf_htoc_to_pcie_np_counter(void);
void set_extoll_rf_pcie_pcie_bridge_rf_htoc_to_pcie_r_counter(long unsigned int value);
long unsigned int get_extoll_rf_pcie_pcie_bridge_rf_htoc_to_pcie_r_counter(void);
void set_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_counter_memwr(long unsigned int value);
long unsigned int get_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_counter_memwr(void);
void set_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_counter_msg(long unsigned int value);
long unsigned int get_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_counter_msg(void);
void set_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_counter_memrd(long unsigned int value);
long unsigned int get_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_counter_memrd(void);
void set_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_counter_iowr(long unsigned int value);
long unsigned int get_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_counter_iowr(void);
void set_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_counter_iord(long unsigned int value);
long unsigned int get_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_counter_iord(void);
void set_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_counter_cfgwr(long unsigned int value);
long unsigned int get_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_counter_cfgwr(void);
void set_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_counter_cfgrd(long unsigned int value);
long unsigned int get_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_counter_cfgrd(void);
void set_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_counter_atomic(long unsigned int value);
long unsigned int get_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_counter_atomic(void);
void set_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_counter_rdrsp(long unsigned int value);
long unsigned int get_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_counter_rdrsp(void);
void set_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_counter_tgtdone(long unsigned int value);
long unsigned int get_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_counter_tgtdone(void);
long unsigned int get_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_regfile_sideband_tlpinfo(long unsigned int index_entry);
long unsigned int get_extoll_rf_pcie_pcie_bridge_rf_pcie_to_htoc_regfile_sideband_tlpdata(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit info_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_info_rf_driver(void);
void set_extoll_rf_info_rf_node(long unsigned int value);
long unsigned int get_extoll_rf_info_rf_node(void);
void set_extoll_rf_info_rf_management_sw(long unsigned int value);
long unsigned int get_extoll_rf_info_rf_management_sw(void);
void set_extoll_rf_info_rf_ip_addresses(long unsigned int value);
long unsigned int get_extoll_rf_info_rf_ip_addresses(void);
void set_extoll_rf_info_rf_mgt_ip_addresses(long unsigned int value);
long unsigned int get_extoll_rf_info_rf_mgt_ip_addresses(void);
void set_extoll_rf_info_rf_tsc(long unsigned int value);
long unsigned int get_extoll_rf_info_rf_tsc(void);
void set_extoll_rf_info_rf_tsc_global_load_value(long unsigned int value);
long unsigned int get_extoll_rf_info_rf_tsc_global_load_value(void);
void set_extoll_rf_info_rf_scratchpad_scratchpad(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_info_rf_scratchpad_scratchpad(long unsigned int index_inst);

//----------------------------------------------------------
// Functions for unit i2c_rf
//----------------------------------------------------------
void set_extoll_rf_i2c_rf_i2c(long unsigned int value);
long unsigned int get_extoll_rf_i2c_rf_i2c(void);
long unsigned int get_extoll_rf_i2c_rf_si570(void);
long unsigned int get_extoll_rf_i2c_rf_rsvd0(void);
long unsigned int get_extoll_rf_i2c_rf_rsvd1(void);
long unsigned int get_extoll_rf_i2c_rf_sysmon(void);
void set_extoll_rf_i2c_rf_sysmon_interface(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_i2c_rf_sysmon_interface(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit pflash_rf
//----------------------------------------------------------
void set_extoll_rf_pflash_rf_ctrl(long unsigned int value);
long unsigned int get_extoll_rf_pflash_rf_ctrl(void);
void set_extoll_rf_pflash_rf_base_addr(long unsigned int value);
long unsigned int get_extoll_rf_pflash_rf_base_addr(void);
void set_extoll_rf_pflash_rf_buffer_data(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_pflash_rf_buffer_data(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit htax_bridge_rf
//----------------------------------------------------------
void set_extoll_rf_htax_bridge_rf_intvl_upper(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_htax_bridge_rf_intvl_upper(long unsigned int index_inst);
void set_extoll_rf_htax_bridge_rf_intvl_lower(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_htax_bridge_rf_intvl_lower(long unsigned int index_inst);
void set_extoll_rf_htax_bridge_rf_intvl_control(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_htax_bridge_rf_intvl_control(long unsigned int index_inst);
void set_extoll_rf_htax_bridge_rf_general(long unsigned int value);
long unsigned int get_extoll_rf_htax_bridge_rf_general(void);
long unsigned int get_extoll_rf_htax_bridge_rf_debug(void);
void set_extoll_rf_htax_bridge_rf_posted_counter(long unsigned int value);
long unsigned int get_extoll_rf_htax_bridge_rf_posted_counter(void);
void set_extoll_rf_htax_bridge_rf_nonposted_counter(long unsigned int value);
long unsigned int get_extoll_rf_htax_bridge_rf_nonposted_counter(void);
void set_extoll_rf_htax_bridge_rf_response_counter(long unsigned int value);
long unsigned int get_extoll_rf_htax_bridge_rf_response_counter(void);
void set_extoll_rf_htax_bridge_rf_discarded_counter(long unsigned int value);
long unsigned int get_extoll_rf_htax_bridge_rf_discarded_counter(void);

//----------------------------------------------------------
// Functions for unit htax_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_htax_rf_debug_0(void);
long unsigned int get_extoll_rf_htax_rf_debug_1(void);

//----------------------------------------------------------
// Functions for unit np_top_rf
//----------------------------------------------------------

//----------------------------------------------------------
// Functions for unit np_top_rf_n0
//----------------------------------------------------------
void set_extoll_rf_np_top_rf_np_top_rf_n0_hp2np_counter(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n0_hp2np_counter(void);
void set_extoll_rf_np_top_rf_np_top_rf_n0_np2hp_counter(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n0_np2hp_counter(void);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n0_fcc_credits(void);
void set_extoll_rf_np_top_rf_np_top_rf_n0_general(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n0_general(void);
void set_extoll_rf_np_top_rf_np_top_rf_n0_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n0_credits_0(void);
void set_extoll_rf_np_top_rf_np_top_rf_n0_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n0_credits_1(void);
void set_extoll_rf_np_top_rf_np_top_rf_n0_avail_fcc(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n0_avail_fcc(void);
void set_extoll_rf_np_top_rf_np_top_rf_n0_raw_ctrl(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n0_raw_ctrl(void);
void set_extoll_rf_np_top_rf_np_top_rf_n0_raw_0(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n0_raw_0(void);

//----------------------------------------------------------
// Functions for unit np_top_rf_n1
//----------------------------------------------------------
void set_extoll_rf_np_top_rf_np_top_rf_n1_hp2np_counter(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n1_hp2np_counter(void);
void set_extoll_rf_np_top_rf_np_top_rf_n1_np2hp_counter(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n1_np2hp_counter(void);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n1_fcc_credits(void);
void set_extoll_rf_np_top_rf_np_top_rf_n1_general(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n1_general(void);
void set_extoll_rf_np_top_rf_np_top_rf_n1_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n1_credits_0(void);
void set_extoll_rf_np_top_rf_np_top_rf_n1_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n1_credits_1(void);
void set_extoll_rf_np_top_rf_np_top_rf_n1_avail_fcc(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n1_avail_fcc(void);
void set_extoll_rf_np_top_rf_np_top_rf_n1_raw_ctrl(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n1_raw_ctrl(void);
void set_extoll_rf_np_top_rf_np_top_rf_n1_raw_0(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n1_raw_0(void);

//----------------------------------------------------------
// Functions for unit np_top_rf_n2
//----------------------------------------------------------
void set_extoll_rf_np_top_rf_np_top_rf_n2_hp2np_counter(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n2_hp2np_counter(void);
void set_extoll_rf_np_top_rf_np_top_rf_n2_np2hp_counter(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n2_np2hp_counter(void);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n2_fcc_credits(void);
void set_extoll_rf_np_top_rf_np_top_rf_n2_general(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n2_general(void);
void set_extoll_rf_np_top_rf_np_top_rf_n2_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n2_credits_0(void);
void set_extoll_rf_np_top_rf_np_top_rf_n2_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n2_credits_1(void);
void set_extoll_rf_np_top_rf_np_top_rf_n2_avail_fcc(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n2_avail_fcc(void);
void set_extoll_rf_np_top_rf_np_top_rf_n2_raw_ctrl(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n2_raw_ctrl(void);
void set_extoll_rf_np_top_rf_np_top_rf_n2_raw_0(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n2_raw_0(void);

//----------------------------------------------------------
// Functions for unit np_top_rf_n3
//----------------------------------------------------------
void set_extoll_rf_np_top_rf_np_top_rf_n3_hp2np_counter(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n3_hp2np_counter(void);
void set_extoll_rf_np_top_rf_np_top_rf_n3_np2hp_counter(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n3_np2hp_counter(void);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n3_fcc_credits(void);
void set_extoll_rf_np_top_rf_np_top_rf_n3_general(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n3_general(void);
void set_extoll_rf_np_top_rf_np_top_rf_n3_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n3_credits_0(void);
void set_extoll_rf_np_top_rf_np_top_rf_n3_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n3_credits_1(void);
void set_extoll_rf_np_top_rf_np_top_rf_n3_avail_fcc(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n3_avail_fcc(void);
void set_extoll_rf_np_top_rf_np_top_rf_n3_raw_ctrl(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n3_raw_ctrl(void);
void set_extoll_rf_np_top_rf_np_top_rf_n3_raw_0(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_np_top_rf_n3_raw_0(void);

//----------------------------------------------------------
// Functions for unit smfu_rf
//----------------------------------------------------------
void set_extoll_rf_smfu_rf_oStartAddr(long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_oStartAddr(void);
void set_extoll_rf_smfu_rf_tStartAddr_default(long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_tStartAddr_default(void);
void set_extoll_rf_smfu_rf_addr_mask(long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_addr_mask(void);
void set_extoll_rf_smfu_rf_status_control(long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_status_control(void);
void set_extoll_rf_smfu_rf_sent_count_np(long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_sent_count_np(void);
void set_extoll_rf_smfu_rf_sent_count_p(long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_sent_count_p(void);
void set_extoll_rf_smfu_rf_sent_count_rsp(long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_sent_count_rsp(void);
void set_extoll_rf_smfu_rf_rcvd_count_np(long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_rcvd_count_np(void);
void set_extoll_rf_smfu_rf_rcvd_count_p(long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_rcvd_count_p(void);
void set_extoll_rf_smfu_rf_rcvd_count_rsp(long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_rcvd_count_rsp(void);
void set_extoll_rf_smfu_rf_misc_count(long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_misc_count(void);
void set_extoll_rf_smfu_rf_interval_lower(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_interval_lower(long unsigned int index_inst);
void set_extoll_rf_smfu_rf_interval_upper(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_interval_upper(long unsigned int index_inst);
void set_extoll_rf_smfu_rf_vpid_tStartAddr(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_vpid_tStartAddr(long unsigned int index_inst);

//----------------------------------------------------------
// Functions for unit atu_rf
//----------------------------------------------------------
void set_extoll_rf_atu_rf_cmd_interface(long unsigned int value);
void set_extoll_rf_atu_rf_counter_0(long unsigned int value);
long unsigned int get_extoll_rf_atu_rf_counter_0(void);
void set_extoll_rf_atu_rf_excel_port(long unsigned int value);
long unsigned int get_extoll_rf_atu_rf_excel_port(void);
void set_extoll_rf_atu_rf_excel_port_address(long unsigned int value);
long unsigned int get_extoll_rf_atu_rf_excel_port_address(void);
void set_extoll_rf_atu_rf_gat(long unsigned int index_entry, long unsigned int value);

//----------------------------------------------------------
// Functions for unit snq_rf
//----------------------------------------------------------
void set_extoll_rf_snq_rf_trigger_enable(long unsigned int value);
long unsigned int get_extoll_rf_snq_rf_trigger_enable(void);
void set_extoll_rf_snq_rf_one_shot(long unsigned int value);
long unsigned int get_extoll_rf_snq_rf_one_shot(void);
void set_extoll_rf_snq_rf_one_shot_activate(long unsigned int value);
void set_extoll_rf_snq_rf_queue_balt(long unsigned int value);
long unsigned int get_extoll_rf_snq_rf_queue_balt(void);
void set_extoll_rf_snq_rf_queue_mslt(long unsigned int value);
long unsigned int get_extoll_rf_snq_rf_queue_mslt(void);
long unsigned int get_extoll_rf_snq_rf_queue_wplt(void);
void set_extoll_rf_snq_rf_queue_rplt(long unsigned int value);
long unsigned int get_extoll_rf_snq_rf_queue_rplt(void);
void set_extoll_rf_snq_rf_irq_watermark(long unsigned int value);
long unsigned int get_extoll_rf_snq_rf_irq_watermark(void);
void set_extoll_rf_snq_rf_program(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_snq_rf_program(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit nw
//----------------------------------------------------------

//----------------------------------------------------------
// Functions for unit nw_xbar_rf
//----------------------------------------------------------

//----------------------------------------------------------
// Functions for unit nw_xbar_rf_inp0
//----------------------------------------------------------
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp0_routing(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp0_routing(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp0_rcvd_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp0_rcvd_counter(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp0_send_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp0_send_counter(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp0_dead_det(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp0_dead_det(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp0_mcast(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp0_mcast(long unsigned int index_entry);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp0_grt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp0_grt(long unsigned int index_entry);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp0_lrt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp0_lrt(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit nw_xbar_rf_inp1
//----------------------------------------------------------
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp1_routing(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp1_routing(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp1_rcvd_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp1_rcvd_counter(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp1_send_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp1_send_counter(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp1_dead_det(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp1_dead_det(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp1_mcast(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp1_mcast(long unsigned int index_entry);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp1_grt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp1_grt(long unsigned int index_entry);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp1_lrt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp1_lrt(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit nw_xbar_rf_inp2
//----------------------------------------------------------
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp2_routing(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp2_routing(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp2_rcvd_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp2_rcvd_counter(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp2_send_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp2_send_counter(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp2_dead_det(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp2_dead_det(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp2_mcast(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp2_mcast(long unsigned int index_entry);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp2_grt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp2_grt(long unsigned int index_entry);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp2_lrt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp2_lrt(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit nw_xbar_rf_inp3
//----------------------------------------------------------
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp3_routing(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp3_routing(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp3_rcvd_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp3_rcvd_counter(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp3_send_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp3_send_counter(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp3_dead_det(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp3_dead_det(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp3_mcast(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp3_mcast(long unsigned int index_entry);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp3_grt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp3_grt(long unsigned int index_entry);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp3_lrt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp3_lrt(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit nw_xbar_rf_inp4
//----------------------------------------------------------
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp4_routing(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp4_routing(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp4_rcvd_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp4_rcvd_counter(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp4_send_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp4_send_counter(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp4_dead_det(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp4_dead_det(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp4_mcast(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp4_mcast(long unsigned int index_entry);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp4_grt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp4_grt(long unsigned int index_entry);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp4_lrt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp4_lrt(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit nw_xbar_rf_inp5
//----------------------------------------------------------
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp5_routing(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp5_routing(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp5_rcvd_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp5_rcvd_counter(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp5_send_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp5_send_counter(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp5_dead_det(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp5_dead_det(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp5_mcast(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp5_mcast(long unsigned int index_entry);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp5_grt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp5_grt(long unsigned int index_entry);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp5_lrt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp5_lrt(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit nw_xbar_rf_inp6
//----------------------------------------------------------
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp6_routing(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp6_routing(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp6_rcvd_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp6_rcvd_counter(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp6_send_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp6_send_counter(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp6_dead_det(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp6_dead_det(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp6_mcast(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp6_mcast(long unsigned int index_entry);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp6_grt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp6_grt(long unsigned int index_entry);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp6_lrt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp6_lrt(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit nw_xbar_rf_inp7
//----------------------------------------------------------
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp7_routing(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp7_routing(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp7_rcvd_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp7_rcvd_counter(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp7_send_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp7_send_counter(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp7_dead_det(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp7_dead_det(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp7_mcast(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp7_mcast(long unsigned int index_entry);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp7_grt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp7_grt(long unsigned int index_entry);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp7_lrt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_inp7_lrt(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit nw_xbar_rf_outp0
//----------------------------------------------------------
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp0_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp0_counter(void);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp0_fcc_credits(void);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp0_general(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp0_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp0_credits_0(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp0_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp0_credits_1(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp0_avail_fcc(long unsigned int value);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp0_cong_det(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp0_cong_det(void);

//----------------------------------------------------------
// Functions for unit nw_xbar_rf_outp1
//----------------------------------------------------------
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp1_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp1_counter(void);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp1_fcc_credits(void);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp1_general(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp1_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp1_credits_0(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp1_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp1_credits_1(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp1_avail_fcc(long unsigned int value);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp1_cong_det(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp1_cong_det(void);

//----------------------------------------------------------
// Functions for unit nw_xbar_rf_outp2
//----------------------------------------------------------
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp2_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp2_counter(void);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp2_fcc_credits(void);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp2_general(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp2_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp2_credits_0(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp2_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp2_credits_1(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp2_avail_fcc(long unsigned int value);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp2_cong_det(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp2_cong_det(void);

//----------------------------------------------------------
// Functions for unit nw_xbar_rf_outp3
//----------------------------------------------------------
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp3_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp3_counter(void);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp3_fcc_credits(void);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp3_general(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp3_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp3_credits_0(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp3_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp3_credits_1(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp3_avail_fcc(long unsigned int value);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp3_cong_det(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp3_cong_det(void);

//----------------------------------------------------------
// Functions for unit nw_xbar_rf_outp4
//----------------------------------------------------------
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp4_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp4_counter(void);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp4_fcc_credits(void);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp4_general(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp4_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp4_credits_0(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp4_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp4_credits_1(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp4_avail_fcc(long unsigned int value);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp4_cong_det(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp4_cong_det(void);

//----------------------------------------------------------
// Functions for unit nw_xbar_rf_outp5
//----------------------------------------------------------
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp5_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp5_counter(void);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp5_fcc_credits(void);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp5_general(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp5_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp5_credits_0(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp5_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp5_credits_1(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp5_avail_fcc(long unsigned int value);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp5_cong_det(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp5_cong_det(void);

//----------------------------------------------------------
// Functions for unit nw_xbar_rf_outp6
//----------------------------------------------------------
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp6_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp6_counter(void);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp6_fcc_credits(void);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp6_general(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp6_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp6_credits_0(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp6_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp6_credits_1(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp6_avail_fcc(long unsigned int value);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp6_cong_det(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp6_cong_det(void);

//----------------------------------------------------------
// Functions for unit nw_xbar_rf_outp7
//----------------------------------------------------------
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp7_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp7_counter(void);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp7_fcc_credits(void);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp7_general(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp7_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp7_credits_0(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp7_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp7_credits_1(void);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp7_avail_fcc(long unsigned int value);
void set_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp7_cong_det(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_xbar_rf_nw_xbar_rf_outp7_cong_det(void);

//----------------------------------------------------------
// Functions for unit nw_barrier_rf
//----------------------------------------------------------
void set_extoll_rf_nw_nw_barrier_rf_units_config(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_barrier_rf_units_config(long unsigned int index_inst);
void set_extoll_rf_nw_nw_barrier_rf_units_work_set(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_barrier_rf_units_work_set(long unsigned int index_inst);
void set_extoll_rf_nw_nw_barrier_rf_interrupts_config(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_barrier_rf_interrupts_config(long unsigned int index_inst);
void set_extoll_rf_nw_nw_barrier_rf_interrupts_work_set(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_barrier_rf_interrupts_work_set(long unsigned int index_inst);

//----------------------------------------------------------
// Functions for unit nw_lp_top_rf
//----------------------------------------------------------

//----------------------------------------------------------
// Functions for unit nw_lp_top_rf_lp0
//----------------------------------------------------------
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp0_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp0_counter(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp0_status(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp0_status(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp0_retransmission_counters(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp0_retransmission_counters(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp0_ids(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp0_ids(void);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp0_lp_in_status(void);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp0_lp_fsm_states(void);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp0_lp_out_status(void);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp0_lp_out_arbiter(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp0_ack_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp0_ack_counter(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp0_credit_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp0_credit_counter(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp0_info_handler(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp0_info_handler(void);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp0_debug(void);

//----------------------------------------------------------
// Functions for unit nw_lp_top_rf_lp1
//----------------------------------------------------------
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp1_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp1_counter(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp1_status(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp1_status(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp1_retransmission_counters(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp1_retransmission_counters(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp1_ids(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp1_ids(void);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp1_lp_in_status(void);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp1_lp_fsm_states(void);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp1_lp_out_status(void);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp1_lp_out_arbiter(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp1_ack_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp1_ack_counter(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp1_credit_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp1_credit_counter(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp1_info_handler(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp1_info_handler(void);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp1_debug(void);

//----------------------------------------------------------
// Functions for unit nw_lp_top_rf_lp2
//----------------------------------------------------------
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp2_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp2_counter(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp2_status(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp2_status(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp2_retransmission_counters(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp2_retransmission_counters(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp2_ids(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp2_ids(void);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp2_lp_in_status(void);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp2_lp_fsm_states(void);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp2_lp_out_status(void);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp2_lp_out_arbiter(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp2_ack_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp2_ack_counter(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp2_credit_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp2_credit_counter(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp2_info_handler(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp2_info_handler(void);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp2_debug(void);

//----------------------------------------------------------
// Functions for unit nw_lp_top_rf_lp3
//----------------------------------------------------------
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp3_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp3_counter(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp3_status(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp3_status(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp3_retransmission_counters(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp3_retransmission_counters(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp3_ids(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp3_ids(void);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp3_lp_in_status(void);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp3_lp_fsm_states(void);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp3_lp_out_status(void);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp3_lp_out_arbiter(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp3_ack_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp3_ack_counter(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp3_credit_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp3_credit_counter(void);
void set_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp3_info_handler(long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp3_info_handler(void);
long unsigned int get_extoll_rf_nw_nw_lp_top_rf_nw_lp_top_rf_lp3_debug(void);

//----------------------------------------------------------
// Functions for unit nw_lp_phy_rf
//----------------------------------------------------------
void set_extoll_rf_nw_nw_lp_phy_rf_i_status(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_phy_rf_i_status(long unsigned int index_inst);
long unsigned int get_extoll_rf_nw_nw_lp_phy_rf_i_dbg_cnt(long unsigned int index_inst);
void set_extoll_rf_nw_nw_lp_phy_rf_i_overrides(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_nw_nw_lp_phy_rf_i_overrides(long unsigned int index_inst);
long unsigned int get_extoll_rf_nw_nw_lp_phy_rf_i_PRBS_errorcnt(long unsigned int index_inst);

//----------------------------------------------------------
// Functions for unit bq_rf
//----------------------------------------------------------

//----------------------------------------------------------
// Functions for unit bq_rf_velo
//----------------------------------------------------------
void set_extoll_rf_bq_rf_bq_rf_velo_general(long unsigned int value);
long unsigned int get_extoll_rf_bq_rf_bq_rf_velo_general(void);
void set_extoll_rf_bq_rf_bq_rf_velo_debug(long unsigned int value);
long unsigned int get_extoll_rf_bq_rf_bq_rf_velo_debug(void);
void set_extoll_rf_bq_rf_bq_rf_velo_ub(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_bq_rf_bq_rf_velo_ub(long unsigned int index_entry);
void set_extoll_rf_bq_rf_bq_rf_velo_dcq_base_dcq_ub(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_bq_rf_bq_rf_velo_dcq_base_dcq_ub(long unsigned int index_entry);
void set_extoll_rf_bq_rf_bq_rf_velo_c_base_size_valid(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_bq_rf_bq_rf_velo_c_base_size_valid(long unsigned int index_entry);
void set_extoll_rf_bq_rf_bq_rf_velo_n_base_size_valid(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_bq_rf_bq_rf_velo_n_base_size_valid(long unsigned int index_entry);
void set_extoll_rf_bq_rf_bq_rf_velo_wp_lwp_dcq_rp(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_bq_rf_bq_rf_velo_wp_lwp_dcq_rp(long unsigned int index_entry);
void set_extoll_rf_bq_rf_bq_rf_velo_rp(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_bq_rf_bq_rf_velo_rp(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit bq_rf_rma
//----------------------------------------------------------
void set_extoll_rf_bq_rf_bq_rf_rma_general(long unsigned int value);
long unsigned int get_extoll_rf_bq_rf_bq_rf_rma_general(void);
void set_extoll_rf_bq_rf_bq_rf_rma_debug(long unsigned int value);
long unsigned int get_extoll_rf_bq_rf_bq_rf_rma_debug(void);
void set_extoll_rf_bq_rf_bq_rf_rma_ub(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_bq_rf_bq_rf_rma_ub(long unsigned int index_entry);
void set_extoll_rf_bq_rf_bq_rf_rma_dcq_base_dcq_ub(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_bq_rf_bq_rf_rma_dcq_base_dcq_ub(long unsigned int index_entry);
void set_extoll_rf_bq_rf_bq_rf_rma_c_base_size_valid(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_bq_rf_bq_rf_rma_c_base_size_valid(long unsigned int index_entry);
void set_extoll_rf_bq_rf_bq_rf_rma_n_base_size_valid(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_bq_rf_bq_rf_rma_n_base_size_valid(long unsigned int index_entry);
void set_extoll_rf_bq_rf_bq_rf_rma_wp_lwp_dcq_rp(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_bq_rf_bq_rf_rma_wp_lwp_dcq_rp(long unsigned int index_entry);
void set_extoll_rf_bq_rf_bq_rf_rma_rp(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_bq_rf_bq_rf_rma_rp(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit velo_rf
//----------------------------------------------------------
void set_extoll_rf_velo_rf_timeout(long unsigned int value);
long unsigned int get_extoll_rf_velo_rf_timeout(void);
void set_extoll_rf_velo_rf_completer(long unsigned int value);
long unsigned int get_extoll_rf_velo_rf_completer(void);
void set_extoll_rf_velo_rf_counter_0(long unsigned int value);
long unsigned int get_extoll_rf_velo_rf_counter_0(void);
void set_extoll_rf_velo_rf_counter_1(long unsigned int value);
long unsigned int get_extoll_rf_velo_rf_counter_1(void);
void set_extoll_rf_velo_rf_counter_2(long unsigned int value);
long unsigned int get_extoll_rf_velo_rf_counter_2(void);
long unsigned int get_extoll_rf_velo_rf_debug_0(void);
void set_extoll_rf_velo_rf_debug_1(long unsigned int value);
long unsigned int get_extoll_rf_velo_rf_debug_1(void);
void set_extoll_rf_velo_rf_node_vpid_prot_desc(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_velo_rf_node_vpid_prot_desc(long unsigned int index_entry);
void set_extoll_rf_velo_rf_comp_prot_desc(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_velo_rf_comp_prot_desc(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit velo_rf_wcbuf
//----------------------------------------------------------
void set_extoll_rf_velo_rf_velo_rf_wcbuf_timeout(long unsigned int value);
long unsigned int get_extoll_rf_velo_rf_velo_rf_wcbuf_timeout(void);
void set_extoll_rf_velo_rf_velo_rf_wcbuf_errors0(long unsigned int value);
long unsigned int get_extoll_rf_velo_rf_velo_rf_wcbuf_errors0(void);
void set_extoll_rf_velo_rf_velo_rf_wcbuf_errors1(long unsigned int value);
long unsigned int get_extoll_rf_velo_rf_velo_rf_wcbuf_errors1(void);
void set_extoll_rf_velo_rf_velo_rf_wcbuf_event_mirror(long unsigned int value);
long unsigned int get_extoll_rf_velo_rf_velo_rf_wcbuf_event_mirror(void);
void set_extoll_rf_velo_rf_velo_rf_wcbuf_retry_mirror_base(long unsigned int value);
long unsigned int get_extoll_rf_velo_rf_velo_rf_wcbuf_retry_mirror_base(void);
void set_extoll_rf_velo_rf_velo_rf_wcbuf_state(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_velo_rf_velo_rf_wcbuf_state(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit velo_rf_noti_interrupt_handler
//----------------------------------------------------------
long unsigned int get_extoll_rf_velo_rf_velo_rf_noti_interrupt_handler_int_vec(long unsigned int index_entry);
void set_extoll_rf_velo_rf_velo_rf_noti_interrupt_handler_int_retrig_vec(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_velo_rf_velo_rf_noti_interrupt_handler_int_retrig_vec(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit rma_rf
//----------------------------------------------------------
void set_extoll_rf_rma_rf_config(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_config(void);
void set_extoll_rf_rma_rf_lock_base(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_lock_base(void);
void set_extoll_rf_rma_rf_lock_cfg(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_lock_cfg(void);
void set_extoll_rf_rma_rf_bq_timeout(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_bq_timeout(void);
void set_extoll_rf_rma_rf_requester_error_ctrl(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_requester_error_ctrl(void);
long unsigned int get_extoll_rf_rma_rf_requester_error_cnt_0(void);
long unsigned int get_extoll_rf_rma_rf_requester_error_cnt_1(void);
void set_extoll_rf_rma_rf_responder_error_ctrl(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_responder_error_ctrl(void);
long unsigned int get_extoll_rf_rma_rf_responder_error_cnt_0(void);
long unsigned int get_extoll_rf_rma_rf_responder_error_cnt_1(void);
long unsigned int get_extoll_rf_rma_rf_responder_error_cnt_2(void);
void set_extoll_rf_rma_rf_completer_error_ctrl(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_completer_error_ctrl(void);
long unsigned int get_extoll_rf_rma_rf_completer_error_cnt_0(void);
long unsigned int get_extoll_rf_rma_rf_completer_error_cnt_1(void);
long unsigned int get_extoll_rf_rma_rf_completer_error_cnt_2(void);
long unsigned int get_extoll_rf_rma_rf_completer_error_cnt_3(void);
void set_extoll_rf_rma_rf_vpid_table(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_vpid_table(long unsigned int index_entry);
long unsigned int get_extoll_rf_rma_rf_requester_history(long unsigned int index_entry);
long unsigned int get_extoll_rf_rma_rf_responder_history(long unsigned int index_entry);
long unsigned int get_extoll_rf_rma_rf_completer_history(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit rma_rf_wcbuf
//----------------------------------------------------------
void set_extoll_rf_rma_rf_rma_rf_wcbuf_timeout(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_rma_rf_wcbuf_timeout(void);
void set_extoll_rf_rma_rf_rma_rf_wcbuf_errors0(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_rma_rf_wcbuf_errors0(void);
void set_extoll_rf_rma_rf_rma_rf_wcbuf_errors1(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_rma_rf_wcbuf_errors1(void);
void set_extoll_rf_rma_rf_rma_rf_wcbuf_event_mirror(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_rma_rf_wcbuf_event_mirror(void);
void set_extoll_rf_rma_rf_rma_rf_wcbuf_retry_mirror_base(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_rma_rf_wcbuf_retry_mirror_base(void);
void set_extoll_rf_rma_rf_rma_rf_wcbuf_state(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_rma_rf_wcbuf_state(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit rma_rf_noti_interrupt_handler
//----------------------------------------------------------
long unsigned int get_extoll_rf_rma_rf_rma_rf_noti_interrupt_handler_int_vec(long unsigned int index_entry);
void set_extoll_rf_rma_rf_rma_rf_noti_interrupt_handler_int_retrig_vec(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_rma_rf_noti_interrupt_handler_int_retrig_vec(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit rma_rf_perf
//----------------------------------------------------------
void set_extoll_rf_rma_rf_rma_rf_perf_counter_control(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_requester_perf_in_0(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_requester_perf_in_1(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_requester_perf_in_2(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_requester_perf_in_3(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_requester_perf_atu_0(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_requester_perf_atu_1(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_requester_perf_atu_2(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_requester_perf_re_0(void);
void set_extoll_rf_rma_rf_rma_rf_perf_requester_perf_re_1(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_requester_perf_re_1(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_requester_perf_re_2(void);
void set_extoll_rf_rma_rf_rma_rf_perf_requester_perf_re_3(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_requester_perf_re_3(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_requester_perf_out_0(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_requester_perf_out_1(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_requester_perf_out_2(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_requester_perf_out_3(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_requester_perf_out_4(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_requester_perf_out_5(void);
void set_extoll_rf_rma_rf_rma_rf_perf_requester_perf_out_6(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_requester_perf_out_6(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_requester_perf_noti(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_responder_perf_in_0(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_responder_perf_in_1(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_responder_perf_atu_0(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_responder_perf_atu_1(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_responder_perf_atu_2(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_responder_perf_re_0(void);
void set_extoll_rf_rma_rf_rma_rf_perf_responder_perf_re_1(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_responder_perf_re_1(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_responder_perf_re_2(void);
void set_extoll_rf_rma_rf_rma_rf_perf_responder_perf_re_3(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_responder_perf_re_3(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_responder_perf_out_0(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_responder_perf_out_1(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_responder_perf_out_2(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_responder_perf_out_3(void);
void set_extoll_rf_rma_rf_rma_rf_perf_responder_perf_out_4(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_responder_perf_out_4(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_responder_perf_noti(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_completer_perf_in_0(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_completer_perf_in_1(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_completer_perf_in_2(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_completer_perf_in_3(void);
void set_extoll_rf_rma_rf_rma_rf_perf_completer_perf_in_4(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_completer_perf_in_4(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_completer_perf_atu_0(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_completer_perf_atu_1(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_completer_perf_atu_2(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_completer_perf_out_0(void);
void set_extoll_rf_rma_rf_rma_rf_perf_completer_perf_out_1(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_completer_perf_out_1(void);
long unsigned int get_extoll_rf_rma_rf_rma_rf_perf_completer_perf_noti(void);

//==========================================================
// Bit manipulation helper function
//==========================================================
long unsigned int bit_get(unsigned int bit_offset, unsigned int bit_length, long unsigned int value);

//==========================================================
// Constructor & Destructor (in a way)
//==========================================================

/**
 * RFS Interface describes the RFS available for each device
 * - rf_base_addresses : Array of pointers to the base virtual addresses of RF for each unit
 * - attribute_group   : The Sysfs attribute group (to be able to remove later)
 *
 */
typedef struct extoll_rfs_interface {
        extoll_device_t * device;
        void ** rf_base_addresses;    //< The RF base addresses array for each units
        struct attribute_group attribute_group; //< The attribute group
} extoll_rfs_interface_t;



int extoll_rf_create_sysfs_extoll_rf_files(extoll_device_t **devices,unsigned int devices_count); 
void extoll_rf_remove_sysfs_extoll_rf_files(void);

#endif 
