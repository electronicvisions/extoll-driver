#link mac is missing

FILELIST="extoll_rf_ht_rf_ht3_rf_mem_ecc_err extoll_rf_pcie_rf_bridge_rf_error_ram_ecc extoll_rf_pcie_rf_vendor_ecc extoll_rf_htax_bridge_rf_error_ecc extoll_rf_np_top_rf_n0_np_debug_1 extoll_rf_np_top_rf_n1_np_debug_1 extoll_rf_np_top_rf_n2_np_debug_1 \
extoll_rf_np_top_rf_n3_np_debug_1 extoll_rf_smfu_rf_status_control extoll_rf_atu_rf_ecc extoll_rf_snq_rf_dbg_0 extoll_rf_debugport_rf_config extoll_rf_nw_xbar_rf_inp0_debug extoll_rf_nw_xbar_rf_inp1_debug extoll_rf_nw_xbar_rf_inp2_debug \
extoll_rf_nw_xbar_rf_inp3_debug extoll_rf_nw_xbar_rf_inp4_debug extoll_rf_nw_xbar_rf_inp5_debug extoll_rf_nw_xbar_rf_inp6_debug extoll_rf_nw_xbar_rf_inp7_debug extoll_rf_nw_xbar_rf_inp8_debug extoll_rf_nw_xbar_rf_inp9_debug \
extoll_rf_nw_xbar_rf_inp10_debug extoll_rf_nw_lp_top_rf_lp0_debug extoll_rf_nw_lp_top_rf_lp1_debug extoll_rf_nw_lp_top_rf_lp2_debug extoll_rf_nw_lp_top_rf_lp3_debug extoll_rf_nw_lp_top_rf_lp4_debug extoll_rf_nw_lp_top_rf_lp5_debug \
extoll_rf_nw_lp_top_rf_lp6_debug extoll_rf_velo_rf_debug_1 extoll_rf_buffer_queue_rf_velo_debug extoll_rf_buffer_queue_rf_rma_debug extoll_rf_rma_rf_error_ram_ecc extoll_rf_rma_rf_wcbuf_rf_ecc_status extoll_rf_velo_rf_wcbuf_rf_ecc_status"
cd $EXTOLL_R2_SYSFS

echo SEC
echo ------------------------
for i in $FILELIST ; do echo "$i:" ; cat $i |grep sec | grep "1;" ; done
echo
echo
echo DED
echo -----------------------
for i in $FILELIST ; do echo "$i:" ; cat $i |grep ded | grep "1;" ; done


