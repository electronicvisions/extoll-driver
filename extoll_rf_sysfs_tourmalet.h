#ifndef RF_MAP_SYSFS_H 
#define RF_MAP_SYSFS_H 

#include <linux/device.h> 
#include <linux/sched.h> 
#include <linux/kernel.h>
#include <linux/module.h> 

//==========================================================
// Register access functions
//==========================================================

//----------------------------------------------------------
// Functions for unit extoll_rf
//----------------------------------------------------------

//----------------------------------------------------------
// Functions for unit ht_rf
//----------------------------------------------------------

//----------------------------------------------------------
// Functions for unit ht_cfg_rf
//----------------------------------------------------------
void set_extoll_rf_ht_rf_ht_cfg_rf_reg0_reg1(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht_cfg_rf_reg0_reg1(void);
long unsigned int get_extoll_rf_ht_rf_ht_cfg_rf_reg2_reg3(void);
void set_extoll_rf_ht_rf_ht_cfg_rf_reg4_reg5(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht_cfg_rf_reg4_reg5(void);
void set_extoll_rf_ht_rf_ht_cfg_rf_reg6_reg7(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht_cfg_rf_reg6_reg7(void);
void set_extoll_rf_ht_rf_ht_cfg_rf_reg8_reg9(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht_cfg_rf_reg8_reg9(void);
long unsigned int get_extoll_rf_ht_rf_ht_cfg_rf_reg10_reg11(void);
long unsigned int get_extoll_rf_ht_rf_ht_cfg_rf_reg12_reg13(void);
void set_extoll_rf_ht_rf_ht_cfg_rf_reg14_reg15(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht_cfg_rf_reg14_reg15(void);
void set_extoll_rf_ht_rf_ht_cfg_rf_reg16_reg17(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht_cfg_rf_reg16_reg17(void);
void set_extoll_rf_ht_rf_ht_cfg_rf_reg18_reg19(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht_cfg_rf_reg18_reg19(void);
void set_extoll_rf_ht_rf_ht_cfg_rf_reg20_reg21(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht_cfg_rf_reg20_reg21(void);
void set_extoll_rf_ht_rf_ht_cfg_rf_reg22_reg23(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht_cfg_rf_reg22_reg23(void);
void set_extoll_rf_ht_rf_ht_cfg_rf_reg24_reg25(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht_cfg_rf_reg24_reg25(void);
void set_extoll_rf_ht_rf_ht_cfg_rf_reg26_reg27(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht_cfg_rf_reg26_reg27(void);
void set_extoll_rf_ht_rf_ht_cfg_rf_reg28_reg29(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht_cfg_rf_reg28_reg29(void);
void set_extoll_rf_ht_rf_ht_cfg_rf_reg30_reg31(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht_cfg_rf_reg30_reg31(void);
void set_extoll_rf_ht_rf_ht_cfg_rf_reg32_reg33(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht_cfg_rf_reg32_reg33(void);

//----------------------------------------------------------
// Functions for unit ht3_rf
//----------------------------------------------------------
void set_extoll_rf_ht_rf_ht3_rf_general_cfg(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_rf_general_cfg(void);
void set_extoll_rf_ht_rf_ht3_rf_mem_ecc_err(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_rf_mem_ecc_err(void);
void set_extoll_rf_ht_rf_ht3_rf_bar_cfg(long unsigned int index_inst, long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_rf_bar_cfg(long unsigned int index_inst);
void set_extoll_rf_ht_rf_ht3_rf_id(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_rf_id(void);
long unsigned int get_extoll_rf_ht_rf_ht3_rf_manager_gen3(void);
long unsigned int get_extoll_rf_ht_rf_ht3_rf_link0_state(void);
long unsigned int get_extoll_rf_ht_rf_ht3_rf_link1_state(void);

//----------------------------------------------------------
// Functions for unit ht3_perf_rf
//----------------------------------------------------------
void set_extoll_rf_ht_rf_ht3_rf_ht3_perf_rf_perf_counter_control(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_rf_ht3_perf_rf_credit_cmd_pend_0(void);
long unsigned int get_extoll_rf_ht_rf_ht3_rf_ht3_perf_rf_credit_cmd_pend_1(void);
long unsigned int get_extoll_rf_ht_rf_ht3_rf_ht3_perf_rf_credit_data_pend_0(void);
long unsigned int get_extoll_rf_ht_rf_ht3_rf_ht3_perf_rf_credit_data_pend_1(void);
long unsigned int get_extoll_rf_ht_rf_ht3_rf_ht3_perf_rf_rx_pkts_0(void);
long unsigned int get_extoll_rf_ht_rf_ht3_rf_ht3_perf_rf_rx_pkts_1(void);
long unsigned int get_extoll_rf_ht_rf_ht3_rf_ht3_perf_rf_rx_pkts_2(void);
long unsigned int get_extoll_rf_ht_rf_ht3_rf_ht3_perf_rf_rx_pkts_3(void);
long unsigned int get_extoll_rf_ht_rf_ht3_rf_ht3_perf_rf_rx_pkts_4(void);
long unsigned int get_extoll_rf_ht_rf_ht3_rf_ht3_perf_rf_rx_pkts_5(void);
long unsigned int get_extoll_rf_ht_rf_ht3_rf_ht3_perf_rf_tx_pkts_0(void);
long unsigned int get_extoll_rf_ht_rf_ht3_rf_ht3_perf_rf_tx_pkts_1(void);
long unsigned int get_extoll_rf_ht_rf_ht3_rf_ht3_perf_rf_tx_pkts_2(void);
long unsigned int get_extoll_rf_ht_rf_ht3_rf_ht3_perf_rf_tx_pkts_3(void);
long unsigned int get_extoll_rf_ht_rf_ht3_rf_ht3_perf_rf_tx_pkts_4(void);

//----------------------------------------------------------
// Functions for unit ht3_phy_rf
//----------------------------------------------------------
void set_extoll_rf_ht_rf_ht3_phy_rf_PHY_Config_Engine_Configuration(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_PHY_Config_Engine_Configuration(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_PHY_Config_Engine_timers(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_PHY_Config_Engine_timers(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_Impedance_Calibration_Engine_Configuration(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_Impedance_Calibration_Engine_Configuration(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_Impedance_Calibration_Values(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_Impedance_Calibration_Values(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_ImpCal_RX_timers(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_ImpCal_RX_timers(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_ImpCal_TX_timers(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_ImpCal_TX_timers(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_RX_PHY_Global_signals(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_RX_PHY_Global_signals(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_RX_Debug(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_RX_Debug(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_RX_PHY_Analog_Controlls(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_RX_PHY_Analog_Controlls(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_RX_PHY_Digital_Controlls(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_RX_PHY_Digital_Controlls(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_RX_Data_Lane_Delay(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_RX_Data_Lane_Delay(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_RX_Clock_Delay(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_RX_Clock_Delay(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_RX_CDR_Phase_Recovery_Loop_Low(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_RX_CDR_Phase_Recovery_Loop_Low(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_RX_CDR_Phase_Recovery_Loop_High(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_RX_CDR_Phase_Recovery_Loop_High(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_RX_CDR_Phase_and_Frequency_Recovery_Loop(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_RX_CDR_Phase_and_Frequency_Recovery_Loop(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_RX_Termination_enable(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_RX_Termination_enable(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_RX_CDR_Debug_1(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_RX_CDR_Debug_1(void);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_RX_CDR_Debug_2(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_TX_PHY_Global_signals(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_TX_PHY_Global_signals(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_TX_PHY_Digital_Controlls(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_TX_PHY_Digital_Controlls(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_TX_PHY_Analog_Controlls(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_TX_PHY_Analog_Controlls(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_TX_PHY_Modes_1(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_TX_PHY_Modes_1(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_TX_PHY_Modes_2(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_TX_PHY_Modes_2(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_TX_PHY_PLL_Controls(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_TX_PHY_PLL_Controls(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_PHY_PLL_Config_1(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_PHY_PLL_Config_1(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_PHY_PLL_Config_2(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_PHY_PLL_Config_2(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_PHY_PLL_Config_3(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_PHY_PLL_Config_3(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_PHY_PLL_Config_4(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_PHY_PLL_Config_4(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_PHY_PLL_Config_5(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_PHY_PLL_Config_5(void);
void set_extoll_rf_ht_rf_ht3_phy_rf_PHY_PLL_Config_6(long unsigned int value);
long unsigned int get_extoll_rf_ht_rf_ht3_phy_rf_PHY_PLL_Config_6(void);

//----------------------------------------------------------
// Functions for unit pcie_rf
//----------------------------------------------------------
void set_extoll_rf_pcie_rf_configuration(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_configuration(void);
long unsigned int get_extoll_rf_pcie_rf_info(void);
long unsigned int get_extoll_rf_pcie_rf_status(void);
void set_extoll_rf_pcie_rf_vendor_ecc(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_vendor_ecc(void);
void set_extoll_rf_pcie_rf_int_msix_table(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_int_msix_table(long unsigned int index_entry);
void set_extoll_rf_pcie_rf_int_msix_pba_table(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_int_msix_pba_table(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit nwl_pcie_status_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_general0(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_flow_ctrl_remote(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_flow_ctrl_core(void);
void set_extoll_rf_pcie_rf_nwl_pcie_status_rf_flow_ctrl_blocked(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_flow_ctrl_blocked(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_phy_rx_stat(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_general1(void);
void set_extoll_rf_pcie_rf_nwl_pcie_status_rf_general2(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_general2(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_loopback_err0(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_loopback_err1(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_loopback_err2(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_loopback_err3(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_rp0(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_rp1(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_rp2(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_rp3(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_rp4(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_rp5(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_rp6(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_rp7(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_rp8(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_nwl_cfg_status(long unsigned int index_entry);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_nwl_cfg_estatus(long unsigned int index_entry);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_nwl_cfg_8g_status(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit phy_rx_cnt
//----------------------------------------------------------
void set_extoll_rf_pcie_rf_nwl_pcie_status_rf_phy_rx_cnt_reset(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_phy_rx_cnt_lane_oset0(long unsigned int index_inst);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_phy_rx_cnt_lane_oset1(long unsigned int index_inst);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_phy_rx_cnt_lane_oset2(long unsigned int index_inst);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_phy_rx_cnt_lane_oset3(long unsigned int index_inst);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_phy_rx_cnt_lane_oset4(long unsigned int index_inst);

//----------------------------------------------------------
// Functions for unit err_cnt
//----------------------------------------------------------
void set_extoll_rf_pcie_rf_nwl_pcie_status_rf_err_cnt_reset(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_err_cnt_p0(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_err_cnt_p1(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_err_cnt_p2(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_err_cnt_p3(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_err_cnt_p4(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_err_cnt_p5(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_err_cnt_p6(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_err_cnt_phy(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_err_cnt_rx_assertion(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_err_cnt_tl0(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_err_cnt_tl1(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_err_cnt_tl2(void);
long unsigned int get_extoll_rf_pcie_rf_nwl_pcie_status_rf_err_cnt_dll(void);

//----------------------------------------------------------
// Functions for unit nwl_constants_rf
//----------------------------------------------------------
void set_extoll_rf_pcie_rf_nwl_constants_rf_qw0(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_qw0(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_qw1(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_qw1(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_qw2(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_qw2(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_qw3(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_qw3(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_qw4(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_qw4(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_qw5(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_qw5(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_qw6(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_qw6(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_qw7(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_qw7(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_qw8(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_qw8(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_qw9(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_qw9(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_qw10(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_qw10(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_qw11(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_qw11(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_qw12(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_qw12(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_qw13(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_qw13(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_qw14(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_qw14(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_qw15(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_qw15(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_qw16(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_qw16(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw0(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw0(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw1(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw1(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw2(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw2(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw3(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw3(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw4(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw4(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw5(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw5(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw6(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw6(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw7(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw7(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw8(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw8(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw9(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw9(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw10(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw10(void);
void set_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw11(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_constants_rf_g3_qw11(void);

//----------------------------------------------------------
// Functions for unit nwl_control_rf
//----------------------------------------------------------
void set_extoll_rf_pcie_rf_nwl_control_rf_qw0(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_control_rf_qw0(void);
void set_extoll_rf_pcie_rf_nwl_control_rf_qw1(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_control_rf_qw1(void);
void set_extoll_rf_pcie_rf_nwl_control_rf_qw2(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_control_rf_qw2(void);
void set_extoll_rf_pcie_rf_nwl_control_rf_qw3(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_control_rf_qw3(void);
void set_extoll_rf_pcie_rf_nwl_control_rf_qw4(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_control_rf_qw4(void);
void set_extoll_rf_pcie_rf_nwl_control_rf_qw5(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_control_rf_qw5(void);
void set_extoll_rf_pcie_rf_nwl_control_rf_qw6(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_control_rf_qw6(void);
void set_extoll_rf_pcie_rf_nwl_control_rf_qw7(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_control_rf_qw7(void);
void set_extoll_rf_pcie_rf_nwl_control_rf_qw8(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_control_rf_qw8(void);
void set_extoll_rf_pcie_rf_nwl_control_rf_qw9(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_control_rf_qw9(void);
void set_extoll_rf_pcie_rf_nwl_control_rf_qw10(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_control_rf_qw10(void);
void set_extoll_rf_pcie_rf_nwl_control_rf_qw11(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_control_rf_qw11(void);
void set_extoll_rf_pcie_rf_nwl_control_rf_qw12(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_control_rf_qw12(void);
void set_extoll_rf_pcie_rf_nwl_control_rf_qw13(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_control_rf_qw13(void);
void set_extoll_rf_pcie_rf_nwl_control_rf_rp0(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_nwl_control_rf_rp0(void);

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
// Functions for unit pipe_rf
//----------------------------------------------------------
void set_extoll_rf_pcie_rf_pipe_rf_eb_cfg(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_pipe_rf_eb_cfg(void);
void set_extoll_rf_pcie_rf_pipe_rf_aligner_cfg(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_pipe_rf_aligner_cfg(void);
void set_extoll_rf_pcie_rf_pipe_rf_ctrl(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_pipe_rf_ctrl(void);
void set_extoll_rf_pcie_rf_pipe_rf_eq(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_pipe_rf_eq(void);
void set_extoll_rf_pcie_rf_pipe_rf_phy_cfg(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_pipe_rf_phy_cfg(void);
void set_extoll_rf_pcie_rf_pipe_rf_phy_txeq(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_pipe_rf_phy_txeq(void);
void set_extoll_rf_pcie_rf_pipe_rf_phy_gen3_eq(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_pipe_rf_phy_gen3_eq(void);
void set_extoll_rf_pcie_rf_pipe_rf_phy_rxeq(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_pipe_rf_phy_rxeq(void);
void set_extoll_rf_pcie_rf_pipe_rf_phy_rxeq_gen3(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_pipe_rf_phy_rxeq_gen3(void);
void set_extoll_rf_pcie_rf_pipe_rf_phy_rxeq_gen1(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_pipe_rf_phy_rxeq_gen1(void);
void set_extoll_rf_pcie_rf_pipe_rf_phy_rxeq_gen2(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_pipe_rf_phy_rxeq_gen2(void);
void set_extoll_rf_pcie_rf_pipe_rf_phy_eye(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_pipe_rf_phy_eye(void);
void set_extoll_rf_pcie_rf_pipe_rf_rcomp_val0(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_pipe_rf_rcomp_val0(void);
void set_extoll_rf_pcie_rf_pipe_rf_rcomp_val1(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_pipe_rf_rcomp_val1(void);
void set_extoll_rf_pcie_rf_pipe_rf_rcomp_ctrl(long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_pipe_rf_rcomp_ctrl(void);
long unsigned int get_extoll_rf_pcie_rf_pipe_rf_dbg_pipe(void);
long unsigned int get_extoll_rf_pcie_rf_pipe_rf_dbg_phy(void);
void set_extoll_rf_pcie_rf_pipe_rf_phy_rxeq_table(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_pcie_rf_pipe_rf_phy_rxeq_table(long unsigned int index_entry);

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
long unsigned int get_extoll_rf_i2c_rf_rsvd0(void);
long unsigned int get_extoll_rf_i2c_rf_rsvd1(void);
void set_extoll_rf_i2c_rf_config(long unsigned int value);
long unsigned int get_extoll_rf_i2c_rf_config(void);

//----------------------------------------------------------
// Functions for unit gpio_rf
//----------------------------------------------------------
void set_extoll_rf_gpio_rf_out(long unsigned int value);
void set_extoll_rf_gpio_rf_in(long unsigned int value);
long unsigned int get_extoll_rf_gpio_rf_in(void);

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
// Functions for unit debugport_rf
//----------------------------------------------------------
void set_extoll_rf_debugport_rf_spi_flash(long unsigned int value);
long unsigned int get_extoll_rf_debugport_rf_spi_flash(void);
void set_extoll_rf_debugport_rf_patch_engine(long unsigned int value);
long unsigned int get_extoll_rf_debugport_rf_patch_engine(void);
void set_extoll_rf_debugport_rf_config(long unsigned int value);
long unsigned int get_extoll_rf_debugport_rf_config(void);
void set_extoll_rf_debugport_rf_data_buffer(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_debugport_rf_data_buffer(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit clocking_rf
//----------------------------------------------------------
void set_extoll_rf_clocking_rf_pll_config(long unsigned int value);
long unsigned int get_extoll_rf_clocking_rf_pll_config(void);
long unsigned int get_extoll_rf_clocking_rf_status(void);
void set_extoll_rf_clocking_rf_control(long unsigned int value);
long unsigned int get_extoll_rf_clocking_rf_control(void);
void set_extoll_rf_clocking_rf_clk_detect_ctrl(long unsigned int value);
long unsigned int get_extoll_rf_clocking_rf_clk_detect_ctrl(void);
void set_extoll_rf_clocking_rf_adc(long unsigned int value);
long unsigned int get_extoll_rf_clocking_rf_adc(void);

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

//----------------------------------------------------------
// Functions for unit link0_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link0_rf_counter_control(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link0_rf_txRateconvCtrl(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_txRateconvCtrl(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_txRateconvPerf0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_txRateconvPerf1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_txRateconvPerf2(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_txRateconvPerf3(void);
void set_extoll_rf_nw_phy_rf_link0_rf_rxRateconvCtrl(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_rxRateconvCtrl(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_rxRateconvPerf0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_rxRateconvPerf1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_rxRateconvError0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_rxRateconvError1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_rxRateconvError2(void);
void set_extoll_rf_nw_phy_rf_link0_rf_linkRate(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_linkRate(void);
void set_extoll_rf_nw_phy_rf_link0_rf_ctrlTraining(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_ctrlTraining(void);
void set_extoll_rf_nw_phy_rf_link0_rf_ctrlTraining1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_ctrlTraining1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_ctrlTraining2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_ctrlTraining2(void);
void set_extoll_rf_nw_phy_rf_link0_rf_statusOverwrite(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_statusOverwrite(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_errorRetrainCnt0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_errorRetrainCnt1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_errorRetrainCnt2(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_errorRetrainCnt3(void);
void set_extoll_rf_nw_phy_rf_link0_rf_errorEcc(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_errorEcc(void);
void set_extoll_rf_nw_phy_rf_link0_rf_timeoutThreshold0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_timeoutThreshold0(void);
void set_extoll_rf_nw_phy_rf_link0_rf_timeoutThreshold1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_timeoutThreshold1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_timeoutThreshold2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_timeoutThreshold2(void);
void set_extoll_rf_nw_phy_rf_link0_rf_timeoutThreshold3(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_timeoutThreshold3(void);
void set_extoll_rf_nw_phy_rf_link0_rf_identifierTraining1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_identifierTraining1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_identifierTraining2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_identifierTraining2(void);
void set_extoll_rf_nw_phy_rf_link0_rf_staticPattern0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_staticPattern0(void);
void set_extoll_rf_nw_phy_rf_link0_rf_staticPattern1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_staticPattern1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_staticPattern2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_staticPattern2(void);
void set_extoll_rf_nw_phy_rf_link0_rf_staticPattern3(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_staticPattern3(void);
void set_extoll_rf_nw_phy_rf_link0_rf_staticPattern4(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_staticPattern4(void);
void set_extoll_rf_nw_phy_rf_link0_rf_staticPattern5(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_staticPattern5(void);
void set_extoll_rf_nw_phy_rf_link0_rf_statusTraining(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_statusTraining(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_infoTraining(void);
void set_extoll_rf_nw_phy_rf_link0_rf_trainLinkNeg0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_trainLinkNeg0(void);
void set_extoll_rf_nw_phy_rf_link0_rf_trainLinkNeg1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_trainLinkNeg1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_scrambler0And1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_scrambler0And1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_scrambler2And3(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_scrambler2And3(void);
void set_extoll_rf_nw_phy_rf_link0_rf_scrambler4And5(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_scrambler4And5(void);
void set_extoll_rf_nw_phy_rf_link0_rf_scrambler6And7(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_scrambler6And7(void);
void set_extoll_rf_nw_phy_rf_link0_rf_scrambler8And9(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_scrambler8And9(void);
void set_extoll_rf_nw_phy_rf_link0_rf_scrambler10And11(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_scrambler10And11(void);
void set_extoll_rf_nw_phy_rf_link0_rf_rcompValue(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_rcompValue(void);
void set_extoll_rf_nw_phy_rf_link0_rf_rcompCsr(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_rcompCsr(void);
void set_extoll_rf_nw_phy_rf_link0_rf_cfg_phy(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_cfg_phy(void);
void set_extoll_rf_nw_phy_rf_link0_rf_cfg_phy_powerdown(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_cfg_phy_powerdown(void);
void set_extoll_rf_nw_phy_rf_link0_rf_bert1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_bert1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_bert2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_bert2(void);
void set_extoll_rf_nw_phy_rf_link0_rf_txEqualizationCoeffTable(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_txEqualizationCoeffTable(long unsigned int index_entry);
void set_extoll_rf_nw_phy_rf_link0_rf_rxEqualizationCoeffTable(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_rxEqualizationCoeffTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit quad0_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_statusQuad(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_trafficFiller(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_trafficFiller(void);

//----------------------------------------------------------
// Functions for unit lane0_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane0_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane1_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane1_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane2_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane2_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane3_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad0_rf_lane3_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit quad1_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_statusQuad(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_trafficFiller(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_trafficFiller(void);

//----------------------------------------------------------
// Functions for unit lane0_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane0_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane1_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane1_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane2_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane2_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane3_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad1_rf_lane3_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit quad2_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_statusQuad(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_trafficFiller(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_trafficFiller(void);

//----------------------------------------------------------
// Functions for unit lane0_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane0_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane1_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane1_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane2_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane2_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane3_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link0_rf_quad2_rf_lane3_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit link1_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link1_rf_counter_control(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link1_rf_txRateconvCtrl(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_txRateconvCtrl(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_txRateconvPerf0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_txRateconvPerf1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_txRateconvPerf2(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_txRateconvPerf3(void);
void set_extoll_rf_nw_phy_rf_link1_rf_rxRateconvCtrl(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_rxRateconvCtrl(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_rxRateconvPerf0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_rxRateconvPerf1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_rxRateconvError0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_rxRateconvError1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_rxRateconvError2(void);
void set_extoll_rf_nw_phy_rf_link1_rf_linkRate(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_linkRate(void);
void set_extoll_rf_nw_phy_rf_link1_rf_ctrlTraining(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_ctrlTraining(void);
void set_extoll_rf_nw_phy_rf_link1_rf_ctrlTraining1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_ctrlTraining1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_ctrlTraining2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_ctrlTraining2(void);
void set_extoll_rf_nw_phy_rf_link1_rf_statusOverwrite(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_statusOverwrite(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_errorRetrainCnt0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_errorRetrainCnt1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_errorRetrainCnt2(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_errorRetrainCnt3(void);
void set_extoll_rf_nw_phy_rf_link1_rf_errorEcc(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_errorEcc(void);
void set_extoll_rf_nw_phy_rf_link1_rf_timeoutThreshold0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_timeoutThreshold0(void);
void set_extoll_rf_nw_phy_rf_link1_rf_timeoutThreshold1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_timeoutThreshold1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_timeoutThreshold2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_timeoutThreshold2(void);
void set_extoll_rf_nw_phy_rf_link1_rf_timeoutThreshold3(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_timeoutThreshold3(void);
void set_extoll_rf_nw_phy_rf_link1_rf_identifierTraining1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_identifierTraining1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_identifierTraining2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_identifierTraining2(void);
void set_extoll_rf_nw_phy_rf_link1_rf_staticPattern0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_staticPattern0(void);
void set_extoll_rf_nw_phy_rf_link1_rf_staticPattern1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_staticPattern1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_staticPattern2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_staticPattern2(void);
void set_extoll_rf_nw_phy_rf_link1_rf_staticPattern3(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_staticPattern3(void);
void set_extoll_rf_nw_phy_rf_link1_rf_staticPattern4(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_staticPattern4(void);
void set_extoll_rf_nw_phy_rf_link1_rf_staticPattern5(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_staticPattern5(void);
void set_extoll_rf_nw_phy_rf_link1_rf_statusTraining(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_statusTraining(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_infoTraining(void);
void set_extoll_rf_nw_phy_rf_link1_rf_trainLinkNeg0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_trainLinkNeg0(void);
void set_extoll_rf_nw_phy_rf_link1_rf_trainLinkNeg1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_trainLinkNeg1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_scrambler0And1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_scrambler0And1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_scrambler2And3(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_scrambler2And3(void);
void set_extoll_rf_nw_phy_rf_link1_rf_scrambler4And5(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_scrambler4And5(void);
void set_extoll_rf_nw_phy_rf_link1_rf_scrambler6And7(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_scrambler6And7(void);
void set_extoll_rf_nw_phy_rf_link1_rf_scrambler8And9(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_scrambler8And9(void);
void set_extoll_rf_nw_phy_rf_link1_rf_scrambler10And11(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_scrambler10And11(void);
void set_extoll_rf_nw_phy_rf_link1_rf_rcompValue(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_rcompValue(void);
void set_extoll_rf_nw_phy_rf_link1_rf_rcompCsr(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_rcompCsr(void);
void set_extoll_rf_nw_phy_rf_link1_rf_cfg_phy(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_cfg_phy(void);
void set_extoll_rf_nw_phy_rf_link1_rf_cfg_phy_powerdown(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_cfg_phy_powerdown(void);
void set_extoll_rf_nw_phy_rf_link1_rf_bert1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_bert1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_bert2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_bert2(void);
void set_extoll_rf_nw_phy_rf_link1_rf_txEqualizationCoeffTable(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_txEqualizationCoeffTable(long unsigned int index_entry);
void set_extoll_rf_nw_phy_rf_link1_rf_rxEqualizationCoeffTable(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_rxEqualizationCoeffTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit quad0_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_statusQuad(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_trafficFiller(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_trafficFiller(void);

//----------------------------------------------------------
// Functions for unit lane0_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane0_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane1_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane1_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane2_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane2_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane3_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad0_rf_lane3_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit quad1_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_statusQuad(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_trafficFiller(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_trafficFiller(void);

//----------------------------------------------------------
// Functions for unit lane0_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane0_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane1_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane1_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane2_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane2_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane3_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad1_rf_lane3_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit quad2_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_statusQuad(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_trafficFiller(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_trafficFiller(void);

//----------------------------------------------------------
// Functions for unit lane0_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane0_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane1_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane1_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane2_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane2_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane3_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link1_rf_quad2_rf_lane3_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit link2_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link2_rf_counter_control(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link2_rf_txRateconvCtrl(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_txRateconvCtrl(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_txRateconvPerf0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_txRateconvPerf1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_txRateconvPerf2(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_txRateconvPerf3(void);
void set_extoll_rf_nw_phy_rf_link2_rf_rxRateconvCtrl(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_rxRateconvCtrl(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_rxRateconvPerf0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_rxRateconvPerf1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_rxRateconvError0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_rxRateconvError1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_rxRateconvError2(void);
void set_extoll_rf_nw_phy_rf_link2_rf_linkRate(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_linkRate(void);
void set_extoll_rf_nw_phy_rf_link2_rf_ctrlTraining(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_ctrlTraining(void);
void set_extoll_rf_nw_phy_rf_link2_rf_ctrlTraining1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_ctrlTraining1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_ctrlTraining2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_ctrlTraining2(void);
void set_extoll_rf_nw_phy_rf_link2_rf_statusOverwrite(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_statusOverwrite(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_errorRetrainCnt0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_errorRetrainCnt1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_errorRetrainCnt2(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_errorRetrainCnt3(void);
void set_extoll_rf_nw_phy_rf_link2_rf_errorEcc(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_errorEcc(void);
void set_extoll_rf_nw_phy_rf_link2_rf_timeoutThreshold0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_timeoutThreshold0(void);
void set_extoll_rf_nw_phy_rf_link2_rf_timeoutThreshold1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_timeoutThreshold1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_timeoutThreshold2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_timeoutThreshold2(void);
void set_extoll_rf_nw_phy_rf_link2_rf_timeoutThreshold3(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_timeoutThreshold3(void);
void set_extoll_rf_nw_phy_rf_link2_rf_identifierTraining1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_identifierTraining1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_identifierTraining2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_identifierTraining2(void);
void set_extoll_rf_nw_phy_rf_link2_rf_staticPattern0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_staticPattern0(void);
void set_extoll_rf_nw_phy_rf_link2_rf_staticPattern1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_staticPattern1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_staticPattern2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_staticPattern2(void);
void set_extoll_rf_nw_phy_rf_link2_rf_staticPattern3(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_staticPattern3(void);
void set_extoll_rf_nw_phy_rf_link2_rf_staticPattern4(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_staticPattern4(void);
void set_extoll_rf_nw_phy_rf_link2_rf_staticPattern5(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_staticPattern5(void);
void set_extoll_rf_nw_phy_rf_link2_rf_statusTraining(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_statusTraining(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_infoTraining(void);
void set_extoll_rf_nw_phy_rf_link2_rf_trainLinkNeg0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_trainLinkNeg0(void);
void set_extoll_rf_nw_phy_rf_link2_rf_trainLinkNeg1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_trainLinkNeg1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_scrambler0And1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_scrambler0And1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_scrambler2And3(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_scrambler2And3(void);
void set_extoll_rf_nw_phy_rf_link2_rf_scrambler4And5(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_scrambler4And5(void);
void set_extoll_rf_nw_phy_rf_link2_rf_scrambler6And7(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_scrambler6And7(void);
void set_extoll_rf_nw_phy_rf_link2_rf_scrambler8And9(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_scrambler8And9(void);
void set_extoll_rf_nw_phy_rf_link2_rf_scrambler10And11(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_scrambler10And11(void);
void set_extoll_rf_nw_phy_rf_link2_rf_rcompValue(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_rcompValue(void);
void set_extoll_rf_nw_phy_rf_link2_rf_rcompCsr(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_rcompCsr(void);
void set_extoll_rf_nw_phy_rf_link2_rf_cfg_phy(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_cfg_phy(void);
void set_extoll_rf_nw_phy_rf_link2_rf_cfg_phy_powerdown(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_cfg_phy_powerdown(void);
void set_extoll_rf_nw_phy_rf_link2_rf_bert1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_bert1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_bert2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_bert2(void);
void set_extoll_rf_nw_phy_rf_link2_rf_txEqualizationCoeffTable(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_txEqualizationCoeffTable(long unsigned int index_entry);
void set_extoll_rf_nw_phy_rf_link2_rf_rxEqualizationCoeffTable(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_rxEqualizationCoeffTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit quad0_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_statusQuad(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_trafficFiller(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_trafficFiller(void);

//----------------------------------------------------------
// Functions for unit lane0_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane0_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane1_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane1_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane2_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane2_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane3_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad0_rf_lane3_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit quad1_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_statusQuad(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_trafficFiller(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_trafficFiller(void);

//----------------------------------------------------------
// Functions for unit lane0_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane0_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane1_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane1_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane2_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane2_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane3_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad1_rf_lane3_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit quad2_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_statusQuad(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_trafficFiller(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_trafficFiller(void);

//----------------------------------------------------------
// Functions for unit lane0_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane0_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane1_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane1_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane2_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane2_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane3_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link2_rf_quad2_rf_lane3_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit link3_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link3_rf_counter_control(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link3_rf_txRateconvCtrl(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_txRateconvCtrl(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_txRateconvPerf0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_txRateconvPerf1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_txRateconvPerf2(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_txRateconvPerf3(void);
void set_extoll_rf_nw_phy_rf_link3_rf_rxRateconvCtrl(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_rxRateconvCtrl(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_rxRateconvPerf0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_rxRateconvPerf1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_rxRateconvError0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_rxRateconvError1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_rxRateconvError2(void);
void set_extoll_rf_nw_phy_rf_link3_rf_linkRate(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_linkRate(void);
void set_extoll_rf_nw_phy_rf_link3_rf_ctrlTraining(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_ctrlTraining(void);
void set_extoll_rf_nw_phy_rf_link3_rf_ctrlTraining1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_ctrlTraining1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_ctrlTraining2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_ctrlTraining2(void);
void set_extoll_rf_nw_phy_rf_link3_rf_statusOverwrite(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_statusOverwrite(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_errorRetrainCnt0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_errorRetrainCnt1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_errorRetrainCnt2(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_errorRetrainCnt3(void);
void set_extoll_rf_nw_phy_rf_link3_rf_errorEcc(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_errorEcc(void);
void set_extoll_rf_nw_phy_rf_link3_rf_timeoutThreshold0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_timeoutThreshold0(void);
void set_extoll_rf_nw_phy_rf_link3_rf_timeoutThreshold1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_timeoutThreshold1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_timeoutThreshold2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_timeoutThreshold2(void);
void set_extoll_rf_nw_phy_rf_link3_rf_timeoutThreshold3(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_timeoutThreshold3(void);
void set_extoll_rf_nw_phy_rf_link3_rf_identifierTraining1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_identifierTraining1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_identifierTraining2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_identifierTraining2(void);
void set_extoll_rf_nw_phy_rf_link3_rf_staticPattern0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_staticPattern0(void);
void set_extoll_rf_nw_phy_rf_link3_rf_staticPattern1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_staticPattern1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_staticPattern2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_staticPattern2(void);
void set_extoll_rf_nw_phy_rf_link3_rf_staticPattern3(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_staticPattern3(void);
void set_extoll_rf_nw_phy_rf_link3_rf_staticPattern4(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_staticPattern4(void);
void set_extoll_rf_nw_phy_rf_link3_rf_staticPattern5(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_staticPattern5(void);
void set_extoll_rf_nw_phy_rf_link3_rf_statusTraining(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_statusTraining(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_infoTraining(void);
void set_extoll_rf_nw_phy_rf_link3_rf_trainLinkNeg0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_trainLinkNeg0(void);
void set_extoll_rf_nw_phy_rf_link3_rf_trainLinkNeg1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_trainLinkNeg1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_scrambler0And1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_scrambler0And1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_scrambler2And3(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_scrambler2And3(void);
void set_extoll_rf_nw_phy_rf_link3_rf_scrambler4And5(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_scrambler4And5(void);
void set_extoll_rf_nw_phy_rf_link3_rf_scrambler6And7(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_scrambler6And7(void);
void set_extoll_rf_nw_phy_rf_link3_rf_scrambler8And9(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_scrambler8And9(void);
void set_extoll_rf_nw_phy_rf_link3_rf_scrambler10And11(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_scrambler10And11(void);
void set_extoll_rf_nw_phy_rf_link3_rf_rcompValue(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_rcompValue(void);
void set_extoll_rf_nw_phy_rf_link3_rf_rcompCsr(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_rcompCsr(void);
void set_extoll_rf_nw_phy_rf_link3_rf_cfg_phy(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_cfg_phy(void);
void set_extoll_rf_nw_phy_rf_link3_rf_cfg_phy_powerdown(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_cfg_phy_powerdown(void);
void set_extoll_rf_nw_phy_rf_link3_rf_bert1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_bert1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_bert2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_bert2(void);
void set_extoll_rf_nw_phy_rf_link3_rf_txEqualizationCoeffTable(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_txEqualizationCoeffTable(long unsigned int index_entry);
void set_extoll_rf_nw_phy_rf_link3_rf_rxEqualizationCoeffTable(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_rxEqualizationCoeffTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit quad0_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_statusQuad(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_trafficFiller(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_trafficFiller(void);

//----------------------------------------------------------
// Functions for unit lane0_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane0_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane1_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane1_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane2_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane2_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane3_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad0_rf_lane3_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit quad1_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_statusQuad(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_trafficFiller(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_trafficFiller(void);

//----------------------------------------------------------
// Functions for unit lane0_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane0_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane1_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane1_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane2_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane2_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane3_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad1_rf_lane3_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit quad2_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_statusQuad(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_trafficFiller(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_trafficFiller(void);

//----------------------------------------------------------
// Functions for unit lane0_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane0_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane1_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane1_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane2_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane2_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane3_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link3_rf_quad2_rf_lane3_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit link4_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link4_rf_counter_control(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link4_rf_txRateconvCtrl(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_txRateconvCtrl(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_txRateconvPerf0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_txRateconvPerf1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_txRateconvPerf2(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_txRateconvPerf3(void);
void set_extoll_rf_nw_phy_rf_link4_rf_rxRateconvCtrl(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_rxRateconvCtrl(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_rxRateconvPerf0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_rxRateconvPerf1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_rxRateconvError0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_rxRateconvError1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_rxRateconvError2(void);
void set_extoll_rf_nw_phy_rf_link4_rf_linkRate(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_linkRate(void);
void set_extoll_rf_nw_phy_rf_link4_rf_ctrlTraining(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_ctrlTraining(void);
void set_extoll_rf_nw_phy_rf_link4_rf_ctrlTraining1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_ctrlTraining1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_ctrlTraining2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_ctrlTraining2(void);
void set_extoll_rf_nw_phy_rf_link4_rf_statusOverwrite(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_statusOverwrite(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_errorRetrainCnt0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_errorRetrainCnt1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_errorRetrainCnt2(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_errorRetrainCnt3(void);
void set_extoll_rf_nw_phy_rf_link4_rf_errorEcc(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_errorEcc(void);
void set_extoll_rf_nw_phy_rf_link4_rf_timeoutThreshold0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_timeoutThreshold0(void);
void set_extoll_rf_nw_phy_rf_link4_rf_timeoutThreshold1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_timeoutThreshold1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_timeoutThreshold2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_timeoutThreshold2(void);
void set_extoll_rf_nw_phy_rf_link4_rf_timeoutThreshold3(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_timeoutThreshold3(void);
void set_extoll_rf_nw_phy_rf_link4_rf_identifierTraining1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_identifierTraining1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_identifierTraining2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_identifierTraining2(void);
void set_extoll_rf_nw_phy_rf_link4_rf_staticPattern0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_staticPattern0(void);
void set_extoll_rf_nw_phy_rf_link4_rf_staticPattern1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_staticPattern1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_staticPattern2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_staticPattern2(void);
void set_extoll_rf_nw_phy_rf_link4_rf_staticPattern3(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_staticPattern3(void);
void set_extoll_rf_nw_phy_rf_link4_rf_staticPattern4(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_staticPattern4(void);
void set_extoll_rf_nw_phy_rf_link4_rf_staticPattern5(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_staticPattern5(void);
void set_extoll_rf_nw_phy_rf_link4_rf_statusTraining(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_statusTraining(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_infoTraining(void);
void set_extoll_rf_nw_phy_rf_link4_rf_trainLinkNeg0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_trainLinkNeg0(void);
void set_extoll_rf_nw_phy_rf_link4_rf_trainLinkNeg1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_trainLinkNeg1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_scrambler0And1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_scrambler0And1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_scrambler2And3(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_scrambler2And3(void);
void set_extoll_rf_nw_phy_rf_link4_rf_scrambler4And5(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_scrambler4And5(void);
void set_extoll_rf_nw_phy_rf_link4_rf_scrambler6And7(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_scrambler6And7(void);
void set_extoll_rf_nw_phy_rf_link4_rf_scrambler8And9(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_scrambler8And9(void);
void set_extoll_rf_nw_phy_rf_link4_rf_scrambler10And11(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_scrambler10And11(void);
void set_extoll_rf_nw_phy_rf_link4_rf_rcompValue(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_rcompValue(void);
void set_extoll_rf_nw_phy_rf_link4_rf_rcompCsr(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_rcompCsr(void);
void set_extoll_rf_nw_phy_rf_link4_rf_cfg_phy(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_cfg_phy(void);
void set_extoll_rf_nw_phy_rf_link4_rf_cfg_phy_powerdown(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_cfg_phy_powerdown(void);
void set_extoll_rf_nw_phy_rf_link4_rf_bert1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_bert1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_bert2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_bert2(void);
void set_extoll_rf_nw_phy_rf_link4_rf_txEqualizationCoeffTable(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_txEqualizationCoeffTable(long unsigned int index_entry);
void set_extoll_rf_nw_phy_rf_link4_rf_rxEqualizationCoeffTable(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_rxEqualizationCoeffTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit quad0_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_statusQuad(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_trafficFiller(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_trafficFiller(void);

//----------------------------------------------------------
// Functions for unit lane0_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane0_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane1_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane1_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane2_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane2_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane3_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad0_rf_lane3_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit quad1_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_statusQuad(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_trafficFiller(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_trafficFiller(void);

//----------------------------------------------------------
// Functions for unit lane0_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane0_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane1_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane1_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane2_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane2_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane3_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad1_rf_lane3_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit quad2_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_statusQuad(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_trafficFiller(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_trafficFiller(void);

//----------------------------------------------------------
// Functions for unit lane0_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane0_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane1_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane1_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane2_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane2_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane3_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link4_rf_quad2_rf_lane3_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit link5_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link5_rf_counter_control(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link5_rf_txRateconvCtrl(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_txRateconvCtrl(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_txRateconvPerf0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_txRateconvPerf1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_txRateconvPerf2(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_txRateconvPerf3(void);
void set_extoll_rf_nw_phy_rf_link5_rf_rxRateconvCtrl(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_rxRateconvCtrl(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_rxRateconvPerf0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_rxRateconvPerf1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_rxRateconvError0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_rxRateconvError1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_rxRateconvError2(void);
void set_extoll_rf_nw_phy_rf_link5_rf_linkRate(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_linkRate(void);
void set_extoll_rf_nw_phy_rf_link5_rf_ctrlTraining(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_ctrlTraining(void);
void set_extoll_rf_nw_phy_rf_link5_rf_ctrlTraining1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_ctrlTraining1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_ctrlTraining2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_ctrlTraining2(void);
void set_extoll_rf_nw_phy_rf_link5_rf_statusOverwrite(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_statusOverwrite(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_errorRetrainCnt0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_errorRetrainCnt1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_errorRetrainCnt2(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_errorRetrainCnt3(void);
void set_extoll_rf_nw_phy_rf_link5_rf_errorEcc(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_errorEcc(void);
void set_extoll_rf_nw_phy_rf_link5_rf_timeoutThreshold0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_timeoutThreshold0(void);
void set_extoll_rf_nw_phy_rf_link5_rf_timeoutThreshold1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_timeoutThreshold1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_timeoutThreshold2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_timeoutThreshold2(void);
void set_extoll_rf_nw_phy_rf_link5_rf_timeoutThreshold3(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_timeoutThreshold3(void);
void set_extoll_rf_nw_phy_rf_link5_rf_identifierTraining1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_identifierTraining1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_identifierTraining2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_identifierTraining2(void);
void set_extoll_rf_nw_phy_rf_link5_rf_staticPattern0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_staticPattern0(void);
void set_extoll_rf_nw_phy_rf_link5_rf_staticPattern1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_staticPattern1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_staticPattern2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_staticPattern2(void);
void set_extoll_rf_nw_phy_rf_link5_rf_staticPattern3(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_staticPattern3(void);
void set_extoll_rf_nw_phy_rf_link5_rf_staticPattern4(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_staticPattern4(void);
void set_extoll_rf_nw_phy_rf_link5_rf_staticPattern5(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_staticPattern5(void);
void set_extoll_rf_nw_phy_rf_link5_rf_statusTraining(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_statusTraining(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_infoTraining(void);
void set_extoll_rf_nw_phy_rf_link5_rf_trainLinkNeg0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_trainLinkNeg0(void);
void set_extoll_rf_nw_phy_rf_link5_rf_trainLinkNeg1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_trainLinkNeg1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_scrambler0And1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_scrambler0And1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_scrambler2And3(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_scrambler2And3(void);
void set_extoll_rf_nw_phy_rf_link5_rf_scrambler4And5(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_scrambler4And5(void);
void set_extoll_rf_nw_phy_rf_link5_rf_scrambler6And7(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_scrambler6And7(void);
void set_extoll_rf_nw_phy_rf_link5_rf_scrambler8And9(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_scrambler8And9(void);
void set_extoll_rf_nw_phy_rf_link5_rf_scrambler10And11(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_scrambler10And11(void);
void set_extoll_rf_nw_phy_rf_link5_rf_rcompValue(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_rcompValue(void);
void set_extoll_rf_nw_phy_rf_link5_rf_rcompCsr(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_rcompCsr(void);
void set_extoll_rf_nw_phy_rf_link5_rf_cfg_phy(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_cfg_phy(void);
void set_extoll_rf_nw_phy_rf_link5_rf_cfg_phy_powerdown(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_cfg_phy_powerdown(void);
void set_extoll_rf_nw_phy_rf_link5_rf_bert1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_bert1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_bert2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_bert2(void);
void set_extoll_rf_nw_phy_rf_link5_rf_txEqualizationCoeffTable(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_txEqualizationCoeffTable(long unsigned int index_entry);
void set_extoll_rf_nw_phy_rf_link5_rf_rxEqualizationCoeffTable(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_rxEqualizationCoeffTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit quad0_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_statusQuad(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_trafficFiller(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_trafficFiller(void);

//----------------------------------------------------------
// Functions for unit lane0_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane0_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane1_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane1_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane2_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane2_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane3_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad0_rf_lane3_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit quad1_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_statusQuad(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_trafficFiller(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_trafficFiller(void);

//----------------------------------------------------------
// Functions for unit lane0_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane0_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane1_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane1_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane2_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane2_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane3_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad1_rf_lane3_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit quad2_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_statusQuad(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_trafficFiller(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_trafficFiller(void);

//----------------------------------------------------------
// Functions for unit lane0_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane0_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane1_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane1_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane2_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane2_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane3_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link5_rf_quad2_rf_lane3_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit link6_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link6_rf_counter_control(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link6_rf_txRateconvCtrl(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_txRateconvCtrl(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_txRateconvPerf0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_txRateconvPerf1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_txRateconvPerf2(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_txRateconvPerf3(void);
void set_extoll_rf_nw_phy_rf_link6_rf_rxRateconvCtrl(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_rxRateconvCtrl(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_rxRateconvPerf0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_rxRateconvPerf1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_rxRateconvError0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_rxRateconvError1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_rxRateconvError2(void);
void set_extoll_rf_nw_phy_rf_link6_rf_linkRate(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_linkRate(void);
void set_extoll_rf_nw_phy_rf_link6_rf_ctrlTraining(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_ctrlTraining(void);
void set_extoll_rf_nw_phy_rf_link6_rf_ctrlTraining1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_ctrlTraining1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_ctrlTraining2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_ctrlTraining2(void);
void set_extoll_rf_nw_phy_rf_link6_rf_statusOverwrite(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_statusOverwrite(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_errorRetrainCnt0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_errorRetrainCnt1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_errorRetrainCnt2(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_errorRetrainCnt3(void);
void set_extoll_rf_nw_phy_rf_link6_rf_errorEcc(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_errorEcc(void);
void set_extoll_rf_nw_phy_rf_link6_rf_timeoutThreshold0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_timeoutThreshold0(void);
void set_extoll_rf_nw_phy_rf_link6_rf_timeoutThreshold1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_timeoutThreshold1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_timeoutThreshold2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_timeoutThreshold2(void);
void set_extoll_rf_nw_phy_rf_link6_rf_timeoutThreshold3(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_timeoutThreshold3(void);
void set_extoll_rf_nw_phy_rf_link6_rf_identifierTraining1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_identifierTraining1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_identifierTraining2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_identifierTraining2(void);
void set_extoll_rf_nw_phy_rf_link6_rf_staticPattern0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_staticPattern0(void);
void set_extoll_rf_nw_phy_rf_link6_rf_staticPattern1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_staticPattern1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_staticPattern2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_staticPattern2(void);
void set_extoll_rf_nw_phy_rf_link6_rf_staticPattern3(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_staticPattern3(void);
void set_extoll_rf_nw_phy_rf_link6_rf_staticPattern4(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_staticPattern4(void);
void set_extoll_rf_nw_phy_rf_link6_rf_staticPattern5(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_staticPattern5(void);
void set_extoll_rf_nw_phy_rf_link6_rf_statusTraining(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_statusTraining(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_infoTraining(void);
void set_extoll_rf_nw_phy_rf_link6_rf_trainLinkNeg0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_trainLinkNeg0(void);
void set_extoll_rf_nw_phy_rf_link6_rf_trainLinkNeg1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_trainLinkNeg1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_scrambler0And1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_scrambler0And1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_scrambler2And3(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_scrambler2And3(void);
void set_extoll_rf_nw_phy_rf_link6_rf_scrambler4And5(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_scrambler4And5(void);
void set_extoll_rf_nw_phy_rf_link6_rf_scrambler6And7(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_scrambler6And7(void);
void set_extoll_rf_nw_phy_rf_link6_rf_scrambler8And9(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_scrambler8And9(void);
void set_extoll_rf_nw_phy_rf_link6_rf_scrambler10And11(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_scrambler10And11(void);
void set_extoll_rf_nw_phy_rf_link6_rf_rcompValue(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_rcompValue(void);
void set_extoll_rf_nw_phy_rf_link6_rf_rcompCsr(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_rcompCsr(void);
void set_extoll_rf_nw_phy_rf_link6_rf_cfg_phy(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_cfg_phy(void);
void set_extoll_rf_nw_phy_rf_link6_rf_cfg_phy_powerdown(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_cfg_phy_powerdown(void);
void set_extoll_rf_nw_phy_rf_link6_rf_bert1(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_bert1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_bert2(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_bert2(void);
void set_extoll_rf_nw_phy_rf_link6_rf_txEqualizationCoeffTable(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_txEqualizationCoeffTable(long unsigned int index_entry);
void set_extoll_rf_nw_phy_rf_link6_rf_rxEqualizationCoeffTable(long unsigned int index_entry, long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_rxEqualizationCoeffTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit quad0_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_statusQuad(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_trafficFiller(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_trafficFiller(void);

//----------------------------------------------------------
// Functions for unit lane0_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane0_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane1_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane1_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane2_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane2_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane3_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad0_rf_lane3_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit quad1_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_statusQuad(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_trafficFiller(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_trafficFiller(void);

//----------------------------------------------------------
// Functions for unit lane0_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane0_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane1_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane1_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane2_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane2_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane3_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad1_rf_lane3_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit quad2_rf
//----------------------------------------------------------
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_statusQuad(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_trafficFiller(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_trafficFiller(void);

//----------------------------------------------------------
// Functions for unit lane0_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane0_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane1_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane1_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane2_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane2_rf_presetGrpMeritTable(long unsigned int index_entry);

//----------------------------------------------------------
// Functions for unit lane3_rf
//----------------------------------------------------------
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_counter_reinit(long unsigned int value);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_txEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_txEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_rxEqualization(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_rxEqualization(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_trainingFsm(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_trainingFsm(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_trainingFsmInputs(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_trainingFsmInfo(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_symbAligner(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_symbAligner(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_error0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_error1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_bert0(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_bert0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_bert1(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_rxTrafficFilter(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_trainingRcvr0(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_trainingRcvr1(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_phyCfg(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_phyCfg(void);
void set_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_meritLogic(long unsigned int value);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_meritLogic(void);
long unsigned int get_extoll_rf_nw_phy_rf_link6_rf_quad2_rf_lane3_rf_presetGrpMeritTable(long unsigned int index_entry);

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
// Constructor & Destructor (in a way)
//==========================================================
int extoll_rf_create_sysfs_extoll_rf_files(struct device* devp, unsigned long int* base_address); 
void extoll_rf_remove_sysfs_extoll_rf_files(struct device* devp); 

#endif 
