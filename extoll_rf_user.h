#ifndef EXTOLL_RF_USER_H
#define EXTOLL_RF_USER_H

#include <stdint.h>
//==========================================================
// Register access functions
//==========================================================

//----------------------------------------------------------
// Functions for unit extoll_rf
//----------------------------------------------------------

//----------------------------------------------------------
// Functions for unit pcie_rf
//----------------------------------------------------------

//----------------------------------------------------------
// Functions for unit bridge_rf
//----------------------------------------------------------
void set_extoll_rf_pcie_rf_bridge_rf_htoc_to_pcie(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_htoc_to_pcie(void);
void set_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_cfg(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_cfg(void);
void set_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_interrupt_0(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_interrupt_0(void);
void set_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_interrupt_1(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_interrupt_1(void);
void set_extoll_rf_pcie_rf_bridge_rf_tag_maps(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_tag_maps(void);
void set_extoll_rf_pcie_rf_bridge_rf_htoc_to_pcie_p_counter(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_htoc_to_pcie_p_counter(void);
void set_extoll_rf_pcie_rf_bridge_rf_htoc_to_pcie_np_counter(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_htoc_to_pcie_np_counter(void);
void set_extoll_rf_pcie_rf_bridge_rf_htoc_to_pcie_r_counter(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_htoc_to_pcie_r_counter(void);
void set_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_counter_memwr(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_counter_memwr(void);
void set_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_counter_msg(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_counter_msg(void);
void set_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_counter_memrd(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_counter_memrd(void);
void set_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_counter_iowr(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_counter_iowr(void);
void set_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_counter_iord(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_counter_iord(void);
void set_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_counter_cfgwr(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_counter_cfgwr(void);
void set_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_counter_cfgrd(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_counter_cfgrd(void);
void set_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_counter_atomic(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_counter_atomic(void);
void set_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_counter_rdrsp(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_counter_rdrsp(void);
void set_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_counter_tgtdone(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_counter_tgtdone(void);
void set_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_regfwd_drop(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_regfwd_drop(void);
void set_extoll_rf_pcie_rf_bridge_rf_htoc_to_pcie_backdoor_control(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_htoc_to_pcie_backdoor_control(void);
void set_extoll_rf_pcie_rf_bridge_rf_error_ram_ecc(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_error_ram_ecc(void);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_debug_p(void);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_debug_np(void);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_debug_r(void);
void set_extoll_rf_pcie_rf_bridge_rf_htoc_to_pcie_backdoor_data(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_htoc_to_pcie_backdoor_data(long unsigned int index_entry);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_backdoor_info(long unsigned int index_entry);
long unsigned int get_extoll_rf_pcie_rf_bridge_rf_pcie_to_htoc_backdoor_data(long unsigned int index_entry);

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
void set_extoll_rf_info_rf_tsc_global_load_enable(long unsigned int value);
long unsigned int get_extoll_rf_info_rf_tsc_global_load_enable(void);
void set_extoll_rf_info_rf_timer_interrupt(long unsigned int value);
long unsigned int get_extoll_rf_info_rf_timer_interrupt(void);

//----------------------------------------------------------
// Functions for unit i2c_rf
//----------------------------------------------------------
void set_extoll_rf_i2c_rf_i2c(long unsigned int value);
long unsigned int get_extoll_rf_i2c_rf_i2c(void);
long unsigned int get_extoll_rf_i2c_rf_si570(void);
long unsigned int get_extoll_rf_i2c_rf_rsvd0(void);
long unsigned int get_extoll_rf_i2c_rf_rsvd1(void);
void set_extoll_rf_i2c_rf_config(long unsigned int value);
long unsigned int get_extoll_rf_i2c_rf_config(void);
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
void set_extoll_rf_htax_bridge_rf_error_ecc(long unsigned int value);
long unsigned int get_extoll_rf_htax_bridge_rf_error_ecc(void);

//----------------------------------------------------------
// Functions for unit htax_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_htax_rf_debug_0(void);
long unsigned int get_extoll_rf_htax_rf_debug_1(void);
long unsigned int get_extoll_rf_htax_rf_debug_2(void);
long unsigned int get_extoll_rf_htax_rf_port_debug(long unsigned int index_inst);

//----------------------------------------------------------
// Functions for unit np_top_rf
//----------------------------------------------------------

//----------------------------------------------------------
// Functions for unit n0
//----------------------------------------------------------
void set_extoll_rf_np_top_rf_n0_hp2np_counter(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n0_hp2np_counter(void);
void set_extoll_rf_np_top_rf_n0_np2hp_counter(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n0_np2hp_counter(void);
long unsigned int get_extoll_rf_np_top_rf_n0_np_debug_0(void);
void set_extoll_rf_np_top_rf_n0_general(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n0_general(void);
void set_extoll_rf_np_top_rf_n0_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n0_credits_0(void);
void set_extoll_rf_np_top_rf_n0_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n0_credits_1(void);
void set_extoll_rf_np_top_rf_n0_avail_fcc(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n0_avail_fcc(void);
void set_extoll_rf_np_top_rf_n0_raw_ctrl(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n0_raw_ctrl(void);
void set_extoll_rf_np_top_rf_n0_ln_raw(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n0_ln_raw(long unsigned int index_inst);
void set_extoll_rf_np_top_rf_n0_np_debug_1(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n0_np_debug_1(void);

//----------------------------------------------------------
// Functions for unit n1
//----------------------------------------------------------
void set_extoll_rf_np_top_rf_n1_hp2np_counter(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n1_hp2np_counter(void);
void set_extoll_rf_np_top_rf_n1_np2hp_counter(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n1_np2hp_counter(void);
long unsigned int get_extoll_rf_np_top_rf_n1_np_debug_0(void);
void set_extoll_rf_np_top_rf_n1_general(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n1_general(void);
void set_extoll_rf_np_top_rf_n1_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n1_credits_0(void);
void set_extoll_rf_np_top_rf_n1_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n1_credits_1(void);
void set_extoll_rf_np_top_rf_n1_avail_fcc(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n1_avail_fcc(void);
void set_extoll_rf_np_top_rf_n1_raw_ctrl(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n1_raw_ctrl(void);
void set_extoll_rf_np_top_rf_n1_ln_raw(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n1_ln_raw(long unsigned int index_inst);
void set_extoll_rf_np_top_rf_n1_np_debug_1(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n1_np_debug_1(void);

//----------------------------------------------------------
// Functions for unit n2
//----------------------------------------------------------
void set_extoll_rf_np_top_rf_n2_hp2np_counter(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n2_hp2np_counter(void);
void set_extoll_rf_np_top_rf_n2_np2hp_counter(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n2_np2hp_counter(void);
long unsigned int get_extoll_rf_np_top_rf_n2_np_debug_0(void);
void set_extoll_rf_np_top_rf_n2_general(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n2_general(void);
void set_extoll_rf_np_top_rf_n2_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n2_credits_0(void);
void set_extoll_rf_np_top_rf_n2_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n2_credits_1(void);
void set_extoll_rf_np_top_rf_n2_avail_fcc(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n2_avail_fcc(void);
void set_extoll_rf_np_top_rf_n2_raw_ctrl(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n2_raw_ctrl(void);
void set_extoll_rf_np_top_rf_n2_ln_raw(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n2_ln_raw(long unsigned int index_inst);
void set_extoll_rf_np_top_rf_n2_np_debug_1(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n2_np_debug_1(void);

//----------------------------------------------------------
// Functions for unit n3
//----------------------------------------------------------
void set_extoll_rf_np_top_rf_n3_hp2np_counter(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n3_hp2np_counter(void);
void set_extoll_rf_np_top_rf_n3_np2hp_counter(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n3_np2hp_counter(void);
long unsigned int get_extoll_rf_np_top_rf_n3_np_debug_0(void);
void set_extoll_rf_np_top_rf_n3_general(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n3_general(void);
void set_extoll_rf_np_top_rf_n3_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n3_credits_0(void);
void set_extoll_rf_np_top_rf_n3_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n3_credits_1(void);
void set_extoll_rf_np_top_rf_n3_avail_fcc(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n3_avail_fcc(void);
void set_extoll_rf_np_top_rf_n3_raw_ctrl(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n3_raw_ctrl(void);
void set_extoll_rf_np_top_rf_n3_ln_raw(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n3_ln_raw(long unsigned int index_inst);
void set_extoll_rf_np_top_rf_n3_np_debug_1(long unsigned int value);
long unsigned int get_extoll_rf_np_top_rf_n3_np_debug_1(void);

//----------------------------------------------------------
// Functions for unit smfu_rf
//----------------------------------------------------------
void set_extoll_rf_smfu_rf_status_control(long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_status_control(void);
void set_extoll_rf_smfu_rf_traffic_class(long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_traffic_class(void);
void set_extoll_rf_smfu_rf_timeout_control(long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_timeout_control(void);
void set_extoll_rf_smfu_rf_counter_reset(long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_counter_reset(void);
long unsigned int get_extoll_rf_smfu_rf_sent_count_np(void);
long unsigned int get_extoll_rf_smfu_rf_sent_count_p(void);
long unsigned int get_extoll_rf_smfu_rf_sent_count_rsp(void);
long unsigned int get_extoll_rf_smfu_rf_rcvd_count_np(void);
long unsigned int get_extoll_rf_smfu_rf_rcvd_count_p(void);
long unsigned int get_extoll_rf_smfu_rf_rcvd_count_rsp(void);
void set_extoll_rf_smfu_rf_misc_count(long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_misc_count(void);
void set_extoll_rf_smfu_rf_oStartAddr(long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_oStartAddr(void);
void set_extoll_rf_smfu_rf_tStartAddr_default(long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_tStartAddr_default(void);
void set_extoll_rf_smfu_rf_nNodeOffset(long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_nNodeOffset(void);
void set_extoll_rf_smfu_rf_addr_mask(long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_addr_mask(void);
void set_extoll_rf_smfu_rf_interval_control(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_interval_control(long unsigned int index_inst);
void set_extoll_rf_smfu_rf_interval_startaddr(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_interval_startaddr(long unsigned int index_inst);
void set_extoll_rf_smfu_rf_interval_endaddr(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_interval_endaddr(long unsigned int index_inst);
long unsigned int get_extoll_rf_smfu_rf_interval_counter(long unsigned int index_inst);
void set_extoll_rf_smfu_rf_vpid_tStartAddr(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_smfu_rf_vpid_tStartAddr(long unsigned int index_inst);

//----------------------------------------------------------
// Functions for unit atu_rf
//----------------------------------------------------------
void set_extoll_rf_atu_rf_control(long unsigned int value);
long unsigned int get_extoll_rf_atu_rf_control(void);
void set_extoll_rf_atu_rf_cmd_interface(long unsigned int value);
void set_extoll_rf_atu_rf_cnt_0(long unsigned int value);
long unsigned int get_extoll_rf_atu_rf_cnt_0(void);
void set_extoll_rf_atu_rf_cnt_1(long unsigned int value);
long unsigned int get_extoll_rf_atu_rf_cnt_1(void);
void set_extoll_rf_atu_rf_cnt_2(long unsigned int value);
long unsigned int get_extoll_rf_atu_rf_cnt_2(void);
void set_extoll_rf_atu_rf_cnt_3(long unsigned int value);
long unsigned int get_extoll_rf_atu_rf_cnt_3(void);
void set_extoll_rf_atu_rf_cnt_4(long unsigned int value);
long unsigned int get_extoll_rf_atu_rf_cnt_4(void);
void set_extoll_rf_atu_rf_cnt_5(long unsigned int value);
long unsigned int get_extoll_rf_atu_rf_cnt_5(void);
void set_extoll_rf_atu_rf_fifo_fill_level(long unsigned int value);
long unsigned int get_extoll_rf_atu_rf_fifo_fill_level(void);
void set_extoll_rf_atu_rf_ecc(long unsigned int value);
long unsigned int get_extoll_rf_atu_rf_ecc(void);
void set_extoll_rf_atu_rf_excel_port(long unsigned int value);
long unsigned int get_extoll_rf_atu_rf_excel_port(void);
void set_extoll_rf_atu_rf_excel_port_address(long unsigned int value);
long unsigned int get_extoll_rf_atu_rf_excel_port_address(void);
void set_extoll_rf_atu_rf_preload(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_atu_rf_preload(long unsigned int index_entry);
void set_extoll_rf_atu_rf_gat(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_atu_rf_gat(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit snq_rf
//----------------------------------------------------------
void set_extoll_rf_snq_rf_trigger_enable(long unsigned int value);
long unsigned int get_extoll_rf_snq_rf_trigger_enable(void);
void set_extoll_rf_snq_rf_trigger_now(long unsigned int value);
long unsigned int get_extoll_rf_snq_rf_trigger_now(void);
void set_extoll_rf_snq_rf_trigger_once_enable(long unsigned int value);
void set_extoll_rf_snq_rf_trigger_once(long unsigned int value);
long unsigned int get_extoll_rf_snq_rf_trigger_once(void);
void set_extoll_rf_snq_rf_queue_balt(long unsigned int value);
long unsigned int get_extoll_rf_snq_rf_queue_balt(void);
void set_extoll_rf_snq_rf_queue_mslt(long unsigned int value);
long unsigned int get_extoll_rf_snq_rf_queue_mslt(void);
long unsigned int get_extoll_rf_snq_rf_queue_wplt(void);
void set_extoll_rf_snq_rf_queue_rplt(long unsigned int value);
long unsigned int get_extoll_rf_snq_rf_queue_rplt(void);
void set_extoll_rf_snq_rf_irq_watermark(long unsigned int value);
long unsigned int get_extoll_rf_snq_rf_irq_watermark(void);
void set_extoll_rf_snq_rf_irq_0(long unsigned int value);
long unsigned int get_extoll_rf_snq_rf_irq_0(void);
void set_extoll_rf_snq_rf_irq_1(long unsigned int value);
long unsigned int get_extoll_rf_snq_rf_irq_1(void);
void set_extoll_rf_snq_rf_irq_2(long unsigned int value);
long unsigned int get_extoll_rf_snq_rf_irq_2(void);
void set_extoll_rf_snq_rf_dbg_0(long unsigned int value);
long unsigned int get_extoll_rf_snq_rf_dbg_0(void);
void set_extoll_rf_snq_rf_execute(long unsigned int value);
long unsigned int get_extoll_rf_snq_rf_execute(void);
void set_extoll_rf_snq_rf_htax(long unsigned int value);
long unsigned int get_extoll_rf_snq_rf_htax(void);
void set_extoll_rf_snq_rf_program_ram(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_snq_rf_program_ram(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit nw
//----------------------------------------------------------

//----------------------------------------------------------
// Functions for unit xbar_rf
//----------------------------------------------------------

//----------------------------------------------------------
// Functions for unit inp0
//----------------------------------------------------------
void set_extoll_rf_nw_xbar_rf_inp0_routing(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp0_routing(void);
void set_extoll_rf_nw_xbar_rf_inp0_rcvd_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp0_rcvd_counter(void);
void set_extoll_rf_nw_xbar_rf_inp0_send_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp0_send_counter(void);
void set_extoll_rf_nw_xbar_rf_inp0_debug(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp0_debug(void);
void set_extoll_rf_nw_xbar_rf_inp0_mcast(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp0_mcast(long unsigned int index_entry);
void set_extoll_rf_nw_xbar_rf_inp0_grt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp0_grt(long unsigned int index_entry);
void set_extoll_rf_nw_xbar_rf_inp0_lrt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp0_lrt(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit inp1
//----------------------------------------------------------
void set_extoll_rf_nw_xbar_rf_inp1_routing(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp1_routing(void);
void set_extoll_rf_nw_xbar_rf_inp1_rcvd_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp1_rcvd_counter(void);
void set_extoll_rf_nw_xbar_rf_inp1_send_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp1_send_counter(void);
void set_extoll_rf_nw_xbar_rf_inp1_debug(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp1_debug(void);
void set_extoll_rf_nw_xbar_rf_inp1_mcast(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp1_mcast(long unsigned int index_entry);
void set_extoll_rf_nw_xbar_rf_inp1_grt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp1_grt(long unsigned int index_entry);
void set_extoll_rf_nw_xbar_rf_inp1_lrt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp1_lrt(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit inp2
//----------------------------------------------------------
void set_extoll_rf_nw_xbar_rf_inp2_routing(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp2_routing(void);
void set_extoll_rf_nw_xbar_rf_inp2_rcvd_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp2_rcvd_counter(void);
void set_extoll_rf_nw_xbar_rf_inp2_send_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp2_send_counter(void);
void set_extoll_rf_nw_xbar_rf_inp2_debug(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp2_debug(void);
void set_extoll_rf_nw_xbar_rf_inp2_mcast(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp2_mcast(long unsigned int index_entry);
void set_extoll_rf_nw_xbar_rf_inp2_grt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp2_grt(long unsigned int index_entry);
void set_extoll_rf_nw_xbar_rf_inp2_lrt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp2_lrt(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit inp3
//----------------------------------------------------------
void set_extoll_rf_nw_xbar_rf_inp3_routing(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp3_routing(void);
void set_extoll_rf_nw_xbar_rf_inp3_rcvd_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp3_rcvd_counter(void);
void set_extoll_rf_nw_xbar_rf_inp3_send_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp3_send_counter(void);
void set_extoll_rf_nw_xbar_rf_inp3_debug(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp3_debug(void);
void set_extoll_rf_nw_xbar_rf_inp3_mcast(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp3_mcast(long unsigned int index_entry);
void set_extoll_rf_nw_xbar_rf_inp3_grt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp3_grt(long unsigned int index_entry);
void set_extoll_rf_nw_xbar_rf_inp3_lrt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp3_lrt(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit inp4
//----------------------------------------------------------
void set_extoll_rf_nw_xbar_rf_inp4_routing(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp4_routing(void);
void set_extoll_rf_nw_xbar_rf_inp4_rcvd_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp4_rcvd_counter(void);
void set_extoll_rf_nw_xbar_rf_inp4_send_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp4_send_counter(void);
void set_extoll_rf_nw_xbar_rf_inp4_debug(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp4_debug(void);
void set_extoll_rf_nw_xbar_rf_inp4_mcast(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp4_mcast(long unsigned int index_entry);
void set_extoll_rf_nw_xbar_rf_inp4_grt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp4_grt(long unsigned int index_entry);
void set_extoll_rf_nw_xbar_rf_inp4_lrt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp4_lrt(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit inp5
//----------------------------------------------------------
void set_extoll_rf_nw_xbar_rf_inp5_routing(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp5_routing(void);
void set_extoll_rf_nw_xbar_rf_inp5_rcvd_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp5_rcvd_counter(void);
void set_extoll_rf_nw_xbar_rf_inp5_send_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp5_send_counter(void);
void set_extoll_rf_nw_xbar_rf_inp5_debug(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp5_debug(void);
void set_extoll_rf_nw_xbar_rf_inp5_mcast(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp5_mcast(long unsigned int index_entry);
void set_extoll_rf_nw_xbar_rf_inp5_grt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp5_grt(long unsigned int index_entry);
void set_extoll_rf_nw_xbar_rf_inp5_lrt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp5_lrt(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit inp6
//----------------------------------------------------------
void set_extoll_rf_nw_xbar_rf_inp6_routing(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp6_routing(void);
void set_extoll_rf_nw_xbar_rf_inp6_rcvd_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp6_rcvd_counter(void);
void set_extoll_rf_nw_xbar_rf_inp6_send_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp6_send_counter(void);
void set_extoll_rf_nw_xbar_rf_inp6_debug(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp6_debug(void);
void set_extoll_rf_nw_xbar_rf_inp6_mcast(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp6_mcast(long unsigned int index_entry);
void set_extoll_rf_nw_xbar_rf_inp6_grt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp6_grt(long unsigned int index_entry);
void set_extoll_rf_nw_xbar_rf_inp6_lrt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp6_lrt(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit inp7
//----------------------------------------------------------
void set_extoll_rf_nw_xbar_rf_inp7_routing(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp7_routing(void);
void set_extoll_rf_nw_xbar_rf_inp7_rcvd_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp7_rcvd_counter(void);
void set_extoll_rf_nw_xbar_rf_inp7_send_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp7_send_counter(void);
void set_extoll_rf_nw_xbar_rf_inp7_debug(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp7_debug(void);
void set_extoll_rf_nw_xbar_rf_inp7_mcast(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp7_mcast(long unsigned int index_entry);
void set_extoll_rf_nw_xbar_rf_inp7_grt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp7_grt(long unsigned int index_entry);
void set_extoll_rf_nw_xbar_rf_inp7_lrt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp7_lrt(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit inp8
//----------------------------------------------------------
void set_extoll_rf_nw_xbar_rf_inp8_routing(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp8_routing(void);
void set_extoll_rf_nw_xbar_rf_inp8_rcvd_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp8_rcvd_counter(void);
void set_extoll_rf_nw_xbar_rf_inp8_send_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp8_send_counter(void);
void set_extoll_rf_nw_xbar_rf_inp8_debug(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp8_debug(void);
void set_extoll_rf_nw_xbar_rf_inp8_mcast(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp8_mcast(long unsigned int index_entry);
void set_extoll_rf_nw_xbar_rf_inp8_grt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp8_grt(long unsigned int index_entry);
void set_extoll_rf_nw_xbar_rf_inp8_lrt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp8_lrt(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit inp9
//----------------------------------------------------------
void set_extoll_rf_nw_xbar_rf_inp9_routing(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp9_routing(void);
void set_extoll_rf_nw_xbar_rf_inp9_rcvd_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp9_rcvd_counter(void);
void set_extoll_rf_nw_xbar_rf_inp9_send_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp9_send_counter(void);
void set_extoll_rf_nw_xbar_rf_inp9_debug(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp9_debug(void);
void set_extoll_rf_nw_xbar_rf_inp9_mcast(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp9_mcast(long unsigned int index_entry);
void set_extoll_rf_nw_xbar_rf_inp9_grt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp9_grt(long unsigned int index_entry);
void set_extoll_rf_nw_xbar_rf_inp9_lrt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp9_lrt(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit inp10
//----------------------------------------------------------
void set_extoll_rf_nw_xbar_rf_inp10_routing(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp10_routing(void);
void set_extoll_rf_nw_xbar_rf_inp10_rcvd_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp10_rcvd_counter(void);
void set_extoll_rf_nw_xbar_rf_inp10_send_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp10_send_counter(void);
void set_extoll_rf_nw_xbar_rf_inp10_debug(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp10_debug(void);
void set_extoll_rf_nw_xbar_rf_inp10_mcast(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp10_mcast(long unsigned int index_entry);
void set_extoll_rf_nw_xbar_rf_inp10_grt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp10_grt(long unsigned int index_entry);
void set_extoll_rf_nw_xbar_rf_inp10_lrt(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_inp10_lrt(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit outp0
//----------------------------------------------------------
void set_extoll_rf_nw_xbar_rf_outp0_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp0_counter(void);
long unsigned int get_extoll_rf_nw_xbar_rf_outp0_fcc_credits(void);
void set_extoll_rf_nw_xbar_rf_outp0_general(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp0_general(void);
void set_extoll_rf_nw_xbar_rf_outp0_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp0_credits_0(void);
void set_extoll_rf_nw_xbar_rf_outp0_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp0_credits_1(void);
void set_extoll_rf_nw_xbar_rf_outp0_avail_fcc(long unsigned int value);

//----------------------------------------------------------
// Functions for unit outp1
//----------------------------------------------------------
void set_extoll_rf_nw_xbar_rf_outp1_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp1_counter(void);
long unsigned int get_extoll_rf_nw_xbar_rf_outp1_fcc_credits(void);
void set_extoll_rf_nw_xbar_rf_outp1_general(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp1_general(void);
void set_extoll_rf_nw_xbar_rf_outp1_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp1_credits_0(void);
void set_extoll_rf_nw_xbar_rf_outp1_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp1_credits_1(void);
void set_extoll_rf_nw_xbar_rf_outp1_avail_fcc(long unsigned int value);

//----------------------------------------------------------
// Functions for unit outp2
//----------------------------------------------------------
void set_extoll_rf_nw_xbar_rf_outp2_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp2_counter(void);
long unsigned int get_extoll_rf_nw_xbar_rf_outp2_fcc_credits(void);
void set_extoll_rf_nw_xbar_rf_outp2_general(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp2_general(void);
void set_extoll_rf_nw_xbar_rf_outp2_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp2_credits_0(void);
void set_extoll_rf_nw_xbar_rf_outp2_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp2_credits_1(void);
void set_extoll_rf_nw_xbar_rf_outp2_avail_fcc(long unsigned int value);

//----------------------------------------------------------
// Functions for unit outp3
//----------------------------------------------------------
void set_extoll_rf_nw_xbar_rf_outp3_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp3_counter(void);
long unsigned int get_extoll_rf_nw_xbar_rf_outp3_fcc_credits(void);
void set_extoll_rf_nw_xbar_rf_outp3_general(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp3_general(void);
void set_extoll_rf_nw_xbar_rf_outp3_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp3_credits_0(void);
void set_extoll_rf_nw_xbar_rf_outp3_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp3_credits_1(void);
void set_extoll_rf_nw_xbar_rf_outp3_avail_fcc(long unsigned int value);

//----------------------------------------------------------
// Functions for unit outp4
//----------------------------------------------------------
void set_extoll_rf_nw_xbar_rf_outp4_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp4_counter(void);
long unsigned int get_extoll_rf_nw_xbar_rf_outp4_fcc_credits(void);
void set_extoll_rf_nw_xbar_rf_outp4_general(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp4_general(void);
void set_extoll_rf_nw_xbar_rf_outp4_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp4_credits_0(void);
void set_extoll_rf_nw_xbar_rf_outp4_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp4_credits_1(void);
void set_extoll_rf_nw_xbar_rf_outp4_avail_fcc(long unsigned int value);

//----------------------------------------------------------
// Functions for unit outp5
//----------------------------------------------------------
void set_extoll_rf_nw_xbar_rf_outp5_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp5_counter(void);
long unsigned int get_extoll_rf_nw_xbar_rf_outp5_fcc_credits(void);
void set_extoll_rf_nw_xbar_rf_outp5_general(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp5_general(void);
void set_extoll_rf_nw_xbar_rf_outp5_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp5_credits_0(void);
void set_extoll_rf_nw_xbar_rf_outp5_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp5_credits_1(void);
void set_extoll_rf_nw_xbar_rf_outp5_avail_fcc(long unsigned int value);

//----------------------------------------------------------
// Functions for unit outp6
//----------------------------------------------------------
void set_extoll_rf_nw_xbar_rf_outp6_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp6_counter(void);
long unsigned int get_extoll_rf_nw_xbar_rf_outp6_fcc_credits(void);
void set_extoll_rf_nw_xbar_rf_outp6_general(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp6_general(void);
void set_extoll_rf_nw_xbar_rf_outp6_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp6_credits_0(void);
void set_extoll_rf_nw_xbar_rf_outp6_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp6_credits_1(void);
void set_extoll_rf_nw_xbar_rf_outp6_avail_fcc(long unsigned int value);

//----------------------------------------------------------
// Functions for unit outp7
//----------------------------------------------------------
void set_extoll_rf_nw_xbar_rf_outp7_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp7_counter(void);
long unsigned int get_extoll_rf_nw_xbar_rf_outp7_fcc_credits(void);
void set_extoll_rf_nw_xbar_rf_outp7_general(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp7_general(void);
void set_extoll_rf_nw_xbar_rf_outp7_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp7_credits_0(void);
void set_extoll_rf_nw_xbar_rf_outp7_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp7_credits_1(void);
void set_extoll_rf_nw_xbar_rf_outp7_avail_fcc(long unsigned int value);

//----------------------------------------------------------
// Functions for unit outp8
//----------------------------------------------------------
void set_extoll_rf_nw_xbar_rf_outp8_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp8_counter(void);
long unsigned int get_extoll_rf_nw_xbar_rf_outp8_fcc_credits(void);
void set_extoll_rf_nw_xbar_rf_outp8_general(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp8_general(void);
void set_extoll_rf_nw_xbar_rf_outp8_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp8_credits_0(void);
void set_extoll_rf_nw_xbar_rf_outp8_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp8_credits_1(void);
void set_extoll_rf_nw_xbar_rf_outp8_avail_fcc(long unsigned int value);

//----------------------------------------------------------
// Functions for unit outp9
//----------------------------------------------------------
void set_extoll_rf_nw_xbar_rf_outp9_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp9_counter(void);
long unsigned int get_extoll_rf_nw_xbar_rf_outp9_fcc_credits(void);
void set_extoll_rf_nw_xbar_rf_outp9_general(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp9_general(void);
void set_extoll_rf_nw_xbar_rf_outp9_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp9_credits_0(void);
void set_extoll_rf_nw_xbar_rf_outp9_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp9_credits_1(void);
void set_extoll_rf_nw_xbar_rf_outp9_avail_fcc(long unsigned int value);

//----------------------------------------------------------
// Functions for unit outp10
//----------------------------------------------------------
void set_extoll_rf_nw_xbar_rf_outp10_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp10_counter(void);
long unsigned int get_extoll_rf_nw_xbar_rf_outp10_fcc_credits(void);
void set_extoll_rf_nw_xbar_rf_outp10_general(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp10_general(void);
void set_extoll_rf_nw_xbar_rf_outp10_credits_0(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp10_credits_0(void);
void set_extoll_rf_nw_xbar_rf_outp10_credits_1(long unsigned int value);
long unsigned int get_extoll_rf_nw_xbar_rf_outp10_credits_1(void);
void set_extoll_rf_nw_xbar_rf_outp10_avail_fcc(long unsigned int value);

//----------------------------------------------------------
// Functions for unit barrier_rf
//----------------------------------------------------------
void set_extoll_rf_nw_barrier_rf_units_work_set(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_nw_barrier_rf_units_work_set(long unsigned int index_inst);
void set_extoll_rf_nw_barrier_rf_interrupts_work_set(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_nw_barrier_rf_interrupts_work_set(long unsigned int index_inst);
void set_extoll_rf_nw_barrier_rf_units_config_config(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_nw_barrier_rf_units_config_config(long unsigned int index_inst);
void set_extoll_rf_nw_barrier_rf_interrupts_config_config(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_nw_barrier_rf_interrupts_config_config(long unsigned int index_inst);

//----------------------------------------------------------
// Functions for unit lp_top_rf
//----------------------------------------------------------

//----------------------------------------------------------
// Functions for unit lp0
//----------------------------------------------------------
void set_extoll_rf_nw_lp_top_rf_lp0_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp0_counter(void);
void set_extoll_rf_nw_lp_top_rf_lp0_status(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp0_status(void);
void set_extoll_rf_nw_lp_top_rf_lp0_retransmission_counters(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp0_retransmission_counters(void);
void set_extoll_rf_nw_lp_top_rf_lp0_ids(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp0_ids(void);
void set_extoll_rf_nw_lp_top_rf_lp0_lp_in(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp0_lp_in(void);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp0_lp_fsm_states(void);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp0_lp_out_status(void);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp0_lp_out_arbiter(void);
void set_extoll_rf_nw_lp_top_rf_lp0_ack_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp0_ack_counter(void);
void set_extoll_rf_nw_lp_top_rf_lp0_credit_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp0_credit_counter(void);
void set_extoll_rf_nw_lp_top_rf_lp0_info_handler(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp0_info_handler(void);
void set_extoll_rf_nw_lp_top_rf_lp0_timeout(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp0_timeout(void);
void set_extoll_rf_nw_lp_top_rf_lp0_debug(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp0_debug(void);

//----------------------------------------------------------
// Functions for unit lp1
//----------------------------------------------------------
void set_extoll_rf_nw_lp_top_rf_lp1_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp1_counter(void);
void set_extoll_rf_nw_lp_top_rf_lp1_status(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp1_status(void);
void set_extoll_rf_nw_lp_top_rf_lp1_retransmission_counters(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp1_retransmission_counters(void);
void set_extoll_rf_nw_lp_top_rf_lp1_ids(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp1_ids(void);
void set_extoll_rf_nw_lp_top_rf_lp1_lp_in(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp1_lp_in(void);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp1_lp_fsm_states(void);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp1_lp_out_status(void);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp1_lp_out_arbiter(void);
void set_extoll_rf_nw_lp_top_rf_lp1_ack_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp1_ack_counter(void);
void set_extoll_rf_nw_lp_top_rf_lp1_credit_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp1_credit_counter(void);
void set_extoll_rf_nw_lp_top_rf_lp1_info_handler(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp1_info_handler(void);
void set_extoll_rf_nw_lp_top_rf_lp1_timeout(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp1_timeout(void);
void set_extoll_rf_nw_lp_top_rf_lp1_debug(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp1_debug(void);

//----------------------------------------------------------
// Functions for unit lp2
//----------------------------------------------------------
void set_extoll_rf_nw_lp_top_rf_lp2_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp2_counter(void);
void set_extoll_rf_nw_lp_top_rf_lp2_status(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp2_status(void);
void set_extoll_rf_nw_lp_top_rf_lp2_retransmission_counters(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp2_retransmission_counters(void);
void set_extoll_rf_nw_lp_top_rf_lp2_ids(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp2_ids(void);
void set_extoll_rf_nw_lp_top_rf_lp2_lp_in(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp2_lp_in(void);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp2_lp_fsm_states(void);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp2_lp_out_status(void);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp2_lp_out_arbiter(void);
void set_extoll_rf_nw_lp_top_rf_lp2_ack_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp2_ack_counter(void);
void set_extoll_rf_nw_lp_top_rf_lp2_credit_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp2_credit_counter(void);
void set_extoll_rf_nw_lp_top_rf_lp2_info_handler(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp2_info_handler(void);
void set_extoll_rf_nw_lp_top_rf_lp2_timeout(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp2_timeout(void);
void set_extoll_rf_nw_lp_top_rf_lp2_debug(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp2_debug(void);

//----------------------------------------------------------
// Functions for unit lp3
//----------------------------------------------------------
void set_extoll_rf_nw_lp_top_rf_lp3_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp3_counter(void);
void set_extoll_rf_nw_lp_top_rf_lp3_status(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp3_status(void);
void set_extoll_rf_nw_lp_top_rf_lp3_retransmission_counters(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp3_retransmission_counters(void);
void set_extoll_rf_nw_lp_top_rf_lp3_ids(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp3_ids(void);
void set_extoll_rf_nw_lp_top_rf_lp3_lp_in(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp3_lp_in(void);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp3_lp_fsm_states(void);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp3_lp_out_status(void);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp3_lp_out_arbiter(void);
void set_extoll_rf_nw_lp_top_rf_lp3_ack_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp3_ack_counter(void);
void set_extoll_rf_nw_lp_top_rf_lp3_credit_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp3_credit_counter(void);
void set_extoll_rf_nw_lp_top_rf_lp3_info_handler(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp3_info_handler(void);
void set_extoll_rf_nw_lp_top_rf_lp3_timeout(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp3_timeout(void);
void set_extoll_rf_nw_lp_top_rf_lp3_debug(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp3_debug(void);

//----------------------------------------------------------
// Functions for unit lp4
//----------------------------------------------------------
void set_extoll_rf_nw_lp_top_rf_lp4_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp4_counter(void);
void set_extoll_rf_nw_lp_top_rf_lp4_status(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp4_status(void);
void set_extoll_rf_nw_lp_top_rf_lp4_retransmission_counters(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp4_retransmission_counters(void);
void set_extoll_rf_nw_lp_top_rf_lp4_ids(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp4_ids(void);
void set_extoll_rf_nw_lp_top_rf_lp4_lp_in(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp4_lp_in(void);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp4_lp_fsm_states(void);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp4_lp_out_status(void);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp4_lp_out_arbiter(void);
void set_extoll_rf_nw_lp_top_rf_lp4_ack_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp4_ack_counter(void);
void set_extoll_rf_nw_lp_top_rf_lp4_credit_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp4_credit_counter(void);
void set_extoll_rf_nw_lp_top_rf_lp4_info_handler(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp4_info_handler(void);
void set_extoll_rf_nw_lp_top_rf_lp4_timeout(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp4_timeout(void);
void set_extoll_rf_nw_lp_top_rf_lp4_debug(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp4_debug(void);

//----------------------------------------------------------
// Functions for unit lp5
//----------------------------------------------------------
void set_extoll_rf_nw_lp_top_rf_lp5_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp5_counter(void);
void set_extoll_rf_nw_lp_top_rf_lp5_status(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp5_status(void);
void set_extoll_rf_nw_lp_top_rf_lp5_retransmission_counters(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp5_retransmission_counters(void);
void set_extoll_rf_nw_lp_top_rf_lp5_ids(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp5_ids(void);
void set_extoll_rf_nw_lp_top_rf_lp5_lp_in(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp5_lp_in(void);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp5_lp_fsm_states(void);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp5_lp_out_status(void);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp5_lp_out_arbiter(void);
void set_extoll_rf_nw_lp_top_rf_lp5_ack_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp5_ack_counter(void);
void set_extoll_rf_nw_lp_top_rf_lp5_credit_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp5_credit_counter(void);
void set_extoll_rf_nw_lp_top_rf_lp5_info_handler(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp5_info_handler(void);
void set_extoll_rf_nw_lp_top_rf_lp5_timeout(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp5_timeout(void);
void set_extoll_rf_nw_lp_top_rf_lp5_debug(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp5_debug(void);

//----------------------------------------------------------
// Functions for unit lp6
//----------------------------------------------------------
void set_extoll_rf_nw_lp_top_rf_lp6_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp6_counter(void);
void set_extoll_rf_nw_lp_top_rf_lp6_status(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp6_status(void);
void set_extoll_rf_nw_lp_top_rf_lp6_retransmission_counters(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp6_retransmission_counters(void);
void set_extoll_rf_nw_lp_top_rf_lp6_ids(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp6_ids(void);
void set_extoll_rf_nw_lp_top_rf_lp6_lp_in(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp6_lp_in(void);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp6_lp_fsm_states(void);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp6_lp_out_status(void);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp6_lp_out_arbiter(void);
void set_extoll_rf_nw_lp_top_rf_lp6_ack_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp6_ack_counter(void);
void set_extoll_rf_nw_lp_top_rf_lp6_credit_counter(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp6_credit_counter(void);
void set_extoll_rf_nw_lp_top_rf_lp6_info_handler(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp6_info_handler(void);
void set_extoll_rf_nw_lp_top_rf_lp6_timeout(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp6_timeout(void);
void set_extoll_rf_nw_lp_top_rf_lp6_debug(long unsigned int value);
long unsigned int get_extoll_rf_nw_lp_top_rf_lp6_debug(void);

//----------------------------------------------------------
// Functions for unit phy_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link_status(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link_status(long unsigned int index_inst);
long unsigned int get_extoll_rf_nw_phy_rf_link_dbg_cnt(long unsigned int index_inst);
void set_extoll_rf_nw_phy_rf_link_overrides(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link_overrides(long unsigned int index_inst);
long unsigned int get_extoll_rf_nw_phy_rf_link_PRBS_errorcnt(long unsigned int index_inst);

//----------------------------------------------------------
// Functions for unit buffer_queue_rf
//----------------------------------------------------------

//----------------------------------------------------------
// Functions for unit velo
//----------------------------------------------------------
void set_extoll_rf_buffer_queue_rf_velo_general(long unsigned int value);
long unsigned int get_extoll_rf_buffer_queue_rf_velo_general(void);
void set_extoll_rf_buffer_queue_rf_velo_debug(long unsigned int value);
long unsigned int get_extoll_rf_buffer_queue_rf_velo_debug(void);
void set_extoll_rf_buffer_queue_rf_velo_ub(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_buffer_queue_rf_velo_ub(long unsigned int index_entry);
void set_extoll_rf_buffer_queue_rf_velo_dcq_base_dcq_ub(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_buffer_queue_rf_velo_dcq_base_dcq_ub(long unsigned int index_entry);
void set_extoll_rf_buffer_queue_rf_velo_c_base_size_valid(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_buffer_queue_rf_velo_c_base_size_valid(long unsigned int index_entry);
void set_extoll_rf_buffer_queue_rf_velo_n_base_size_valid(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_buffer_queue_rf_velo_n_base_size_valid(long unsigned int index_entry);
void set_extoll_rf_buffer_queue_rf_velo_wp_lwp_dcq_rp(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_buffer_queue_rf_velo_wp_lwp_dcq_rp(long unsigned int index_entry);
void set_extoll_rf_buffer_queue_rf_velo_rp(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_buffer_queue_rf_velo_rp(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit rma
//----------------------------------------------------------
void set_extoll_rf_buffer_queue_rf_rma_general(long unsigned int value);
long unsigned int get_extoll_rf_buffer_queue_rf_rma_general(void);
void set_extoll_rf_buffer_queue_rf_rma_debug(long unsigned int value);
long unsigned int get_extoll_rf_buffer_queue_rf_rma_debug(void);
void set_extoll_rf_buffer_queue_rf_rma_ub(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_buffer_queue_rf_rma_ub(long unsigned int index_entry);
void set_extoll_rf_buffer_queue_rf_rma_dcq_base_dcq_ub(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_buffer_queue_rf_rma_dcq_base_dcq_ub(long unsigned int index_entry);
void set_extoll_rf_buffer_queue_rf_rma_c_base_size_valid(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_buffer_queue_rf_rma_c_base_size_valid(long unsigned int index_entry);
void set_extoll_rf_buffer_queue_rf_rma_n_base_size_valid(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_buffer_queue_rf_rma_n_base_size_valid(long unsigned int index_entry);
void set_extoll_rf_buffer_queue_rf_rma_wp_lwp_dcq_rp(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_buffer_queue_rf_rma_wp_lwp_dcq_rp(long unsigned int index_entry);
void set_extoll_rf_buffer_queue_rf_rma_rp(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_buffer_queue_rf_rma_rp(long unsigned int index_entry);

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
// Functions for unit wcbuf_rf
//----------------------------------------------------------
void set_extoll_rf_velo_rf_wcbuf_rf_timeout(long unsigned int value);
long unsigned int get_extoll_rf_velo_rf_wcbuf_rf_timeout(void);
void set_extoll_rf_velo_rf_wcbuf_rf_errors0(long unsigned int value);
long unsigned int get_extoll_rf_velo_rf_wcbuf_rf_errors0(void);
void set_extoll_rf_velo_rf_wcbuf_rf_errors1(long unsigned int value);
long unsigned int get_extoll_rf_velo_rf_wcbuf_rf_errors1(void);
void set_extoll_rf_velo_rf_wcbuf_rf_event_mirror(long unsigned int value);
long unsigned int get_extoll_rf_velo_rf_wcbuf_rf_event_mirror(void);
void set_extoll_rf_velo_rf_wcbuf_rf_retry_mirror_base(long unsigned int value);
long unsigned int get_extoll_rf_velo_rf_wcbuf_rf_retry_mirror_base(void);
void set_extoll_rf_velo_rf_wcbuf_rf_ecc_status(long unsigned int value);
long unsigned int get_extoll_rf_velo_rf_wcbuf_rf_ecc_status(void);
void set_extoll_rf_velo_rf_wcbuf_rf_state(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_velo_rf_wcbuf_rf_state(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit noti_interrupt_handler
//----------------------------------------------------------
long unsigned int get_extoll_rf_velo_rf_noti_interrupt_handler_int_vec(long unsigned int index_entry);
void set_extoll_rf_velo_rf_noti_interrupt_handler_int_retrig_vec(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_velo_rf_noti_interrupt_handler_int_retrig_vec(long unsigned int index_entry);

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
long unsigned int get_extoll_rf_rma_rf_requester_error_cnt_st(void);
long unsigned int get_extoll_rf_rma_rf_requester_error_cnt_0(void);
long unsigned int get_extoll_rf_rma_rf_requester_error_cnt_1(void);
void set_extoll_rf_rma_rf_responder_error_ctrl(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_responder_error_ctrl(void);
long unsigned int get_extoll_rf_rma_rf_responder_error_cnt_st(void);
long unsigned int get_extoll_rf_rma_rf_responder_error_cnt_0(void);
long unsigned int get_extoll_rf_rma_rf_responder_error_cnt_1(void);
long unsigned int get_extoll_rf_rma_rf_responder_error_cnt_2(void);
void set_extoll_rf_rma_rf_completer_error_ctrl(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_completer_error_ctrl(void);
long unsigned int get_extoll_rf_rma_rf_completer_error_cnt_st(void);
long unsigned int get_extoll_rf_rma_rf_completer_error_cnt_0(void);
long unsigned int get_extoll_rf_rma_rf_completer_error_cnt_1(void);
long unsigned int get_extoll_rf_rma_rf_completer_error_cnt_2(void);
long unsigned int get_extoll_rf_rma_rf_completer_error_cnt_3(void);
void set_extoll_rf_rma_rf_error_ram_ecc(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_error_ram_ecc(void);
void set_extoll_rf_rma_rf_vpid_table(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_vpid_table(long unsigned int index_entry);
long unsigned int get_extoll_rf_rma_rf_requester_history(long unsigned int index_entry);
long unsigned int get_extoll_rf_rma_rf_responder_history(long unsigned int index_entry);
long unsigned int get_extoll_rf_rma_rf_completer_history(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit wcbuf_rf
//----------------------------------------------------------
void set_extoll_rf_rma_rf_wcbuf_rf_timeout(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_wcbuf_rf_timeout(void);
void set_extoll_rf_rma_rf_wcbuf_rf_errors0(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_wcbuf_rf_errors0(void);
void set_extoll_rf_rma_rf_wcbuf_rf_errors1(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_wcbuf_rf_errors1(void);
void set_extoll_rf_rma_rf_wcbuf_rf_event_mirror(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_wcbuf_rf_event_mirror(void);
void set_extoll_rf_rma_rf_wcbuf_rf_retry_mirror_base(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_wcbuf_rf_retry_mirror_base(void);
void set_extoll_rf_rma_rf_wcbuf_rf_ecc_status(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_wcbuf_rf_ecc_status(void);
void set_extoll_rf_rma_rf_wcbuf_rf_state(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_wcbuf_rf_state(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit noti_interrupt_handler
//----------------------------------------------------------
long unsigned int get_extoll_rf_rma_rf_noti_interrupt_handler_int_vec(long unsigned int index_entry);
void set_extoll_rf_rma_rf_noti_interrupt_handler_int_retrig_vec(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_noti_interrupt_handler_int_retrig_vec(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit perf
//----------------------------------------------------------
void set_extoll_rf_rma_rf_perf_counter_control(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_perf_requester_perf_in_0(void);
long unsigned int get_extoll_rf_rma_rf_perf_requester_perf_in_1(void);
long unsigned int get_extoll_rf_rma_rf_perf_requester_perf_in_2(void);
long unsigned int get_extoll_rf_rma_rf_perf_requester_perf_in_3(void);
long unsigned int get_extoll_rf_rma_rf_perf_requester_perf_atu_0(void);
long unsigned int get_extoll_rf_rma_rf_perf_requester_perf_atu_1(void);
long unsigned int get_extoll_rf_rma_rf_perf_requester_perf_atu_2(void);
long unsigned int get_extoll_rf_rma_rf_perf_requester_perf_re_0(void);
void set_extoll_rf_rma_rf_perf_requester_perf_re_1(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_perf_requester_perf_re_1(void);
long unsigned int get_extoll_rf_rma_rf_perf_requester_perf_re_2(void);
void set_extoll_rf_rma_rf_perf_requester_perf_re_3(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_perf_requester_perf_re_3(void);
long unsigned int get_extoll_rf_rma_rf_perf_requester_perf_out_0(void);
long unsigned int get_extoll_rf_rma_rf_perf_requester_perf_out_1(void);
long unsigned int get_extoll_rf_rma_rf_perf_requester_perf_out_2(void);
long unsigned int get_extoll_rf_rma_rf_perf_requester_perf_out_3(void);
long unsigned int get_extoll_rf_rma_rf_perf_requester_perf_out_4(void);
long unsigned int get_extoll_rf_rma_rf_perf_requester_perf_out_5(void);
void set_extoll_rf_rma_rf_perf_requester_perf_out_6(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_perf_requester_perf_out_6(void);
long unsigned int get_extoll_rf_rma_rf_perf_requester_perf_noti(void);
long unsigned int get_extoll_rf_rma_rf_perf_responder_perf_in_0(void);
long unsigned int get_extoll_rf_rma_rf_perf_responder_perf_in_1(void);
long unsigned int get_extoll_rf_rma_rf_perf_responder_perf_atu_0(void);
long unsigned int get_extoll_rf_rma_rf_perf_responder_perf_atu_1(void);
long unsigned int get_extoll_rf_rma_rf_perf_responder_perf_atu_2(void);
long unsigned int get_extoll_rf_rma_rf_perf_responder_perf_re_0(void);
void set_extoll_rf_rma_rf_perf_responder_perf_re_1(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_perf_responder_perf_re_1(void);
long unsigned int get_extoll_rf_rma_rf_perf_responder_perf_re_2(void);
void set_extoll_rf_rma_rf_perf_responder_perf_re_3(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_perf_responder_perf_re_3(void);
long unsigned int get_extoll_rf_rma_rf_perf_responder_perf_out_0(void);
long unsigned int get_extoll_rf_rma_rf_perf_responder_perf_out_1(void);
long unsigned int get_extoll_rf_rma_rf_perf_responder_perf_out_2(void);
long unsigned int get_extoll_rf_rma_rf_perf_responder_perf_out_3(void);
void set_extoll_rf_rma_rf_perf_responder_perf_out_4(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_perf_responder_perf_out_4(void);
long unsigned int get_extoll_rf_rma_rf_perf_responder_perf_noti(void);
long unsigned int get_extoll_rf_rma_rf_perf_completer_perf_in_0(void);
long unsigned int get_extoll_rf_rma_rf_perf_completer_perf_in_1(void);
long unsigned int get_extoll_rf_rma_rf_perf_completer_perf_in_2(void);
long unsigned int get_extoll_rf_rma_rf_perf_completer_perf_in_3(void);
void set_extoll_rf_rma_rf_perf_completer_perf_in_4(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_perf_completer_perf_in_4(void);
long unsigned int get_extoll_rf_rma_rf_perf_completer_perf_atu_0(void);
long unsigned int get_extoll_rf_rma_rf_perf_completer_perf_atu_1(void);
long unsigned int get_extoll_rf_rma_rf_perf_completer_perf_atu_2(void);
long unsigned int get_extoll_rf_rma_rf_perf_completer_perf_out_0(void);
void set_extoll_rf_rma_rf_perf_completer_perf_out_1(long unsigned int value);
long unsigned int get_extoll_rf_rma_rf_perf_completer_perf_out_1(void);
long unsigned int get_extoll_rf_rma_rf_perf_completer_perf_noti(void);

//==========================================================
// Bit manipulation helper function
//==========================================================
long unsigned int bit_get(unsigned int bit_offset, unsigned int bit_length, long unsigned int value);

//==========================================================
// Init and close of RF interface
//==========================================================
int  extoll_rf_open(); 
void extoll_rf_close(); 
#endif 
