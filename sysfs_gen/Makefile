gen_all: gen_tourmalet gen_ventoux gen_galibier64 gen_galibier128 gen_stratix128

gen_tourmalet:
	./generate_sysfs_tourmalet.sh
	cp *.tcl ../script/tcl
	 cp extoll_rf_sysfs.c extoll_rf_sysfs_tourmalet.c
	 cp extoll_rf_sysfs.h extoll_rf_sysfs_tourmalet.h
	 cp ../../../hw/extoll_r2_targets/asic/register_file/xml_output/doc/snq_tdg.txt .
	 cp ../../../hw/extoll_r2_targets/asic/register_file/xml_output/doc/snq_te.txt .
	../../../sw/building_blocks/snqc/snqc snq_te.txt snq_tdg.txt snq_extra.txt 32 0xc800 snq_pram_tourmalet.h snq_decl_tourmalet.h
	 rm -f snq_pram.h snq_decl.h
	 cp snq_tdg.txt snq_tdg_tourmalet.txt
	 cp snq_te.txt snq_te_tourmalet.txt
	 ln -s snq_pram_tourmalet.h snq_pram.h 
	 ln -s snq_decl_tourmalet.h snq_decl.h 

gen_ventoux:
	./generate_sysfs_ventoux64.sh
	cp *.tcl ../script/tcl
	cp extoll_rf_sysfs.c extoll_rf_sysfs_ventoux64.c
	cp extoll_rf_sysfs.h extoll_rf_sysfs_ventoux64.h
	cp ../../../hw/extoll_r2_targets/ventoux_64/register_file/xml_output/doc/snq_tdg.txt .
	cp ../../../hw/extoll_r2_targets/ventoux_64/register_file/xml_output/doc/snq_te.txt .
	../../../sw/building_blocks/snqc/snqc snq_te.txt snq_tdg.txt snq_extra.txt 32 0xc800 snq_pram_ventoux64.h snq_decl_ventoux64.h
	rm -f snq_pram.h snq_decl.h
	cp snq_tdg.txt snq_tdg_ventoux64.txt
	cp snq_te.txt snq_te_ventoux64.txt
	ln -s snq_pram_ventoux64.h snq_pram.h 
	ln -s snq_decl_ventoux64.h snq_decl.h 

gen_galibier64:
	./generate_sysfs_galibier64.sh
	cp *.tcl ../script/tcl
	cp extoll_rf_sysfs.c extoll_rf_sysfs_galibier64.c
	cp extoll_rf_sysfs.h extoll_rf_sysfs_galibier64.h
	cp ../../../hw/extoll_r2_targets/galibier_64/register_file/xml_output/doc/snq_tdg.txt .
	cp ../../../hw/extoll_r2_targets/galibier_64/register_file/xml_output/doc/snq_te.txt .
	../../../sw/building_blocks/snqc/snqc snq_te.txt snq_tdg.txt snq_extra.txt 32 0xc800 snq_pram_galibier64.h snq_decl_galibier64.h
	rm -f snq_pram.h snq_decl.h
	cp snq_tdg.txt snq_tdg_galibier64.txt
	cp snq_te.txt snq_te_galibier64.txt
	ln -s snq_pram_galibier64.h snq_pram.h 
	ln -s snq_decl_galibier64.h snq_decl.h 

gen_galibier128:
	./generate_sysfs_galibier128.sh
	cp *.tcl ../script/tcl
	cp extoll_rf_sysfs.c extoll_rf_sysfs_galibier128.c
	cp extoll_rf_sysfs.h extoll_rf_sysfs_galibier128.h
	cp ../../../hw/extoll_r2_targets/galibier_128/register_file/xml_output/doc/snq_tdg.txt .
	cp ../../../hw/extoll_r2_targets/galibier_128/register_file/xml_output/doc/snq_te.txt .
	../../../sw/building_blocks/snqc/snqc snq_te.txt snq_tdg.txt snq_extra.txt 32 0xc800 snq_pram_galibier128.h snq_decl_galibier128.h
	rm -f snq_pram.h snq_decl.h
	cp snq_tdg.txt snq_tdg_galibier128.txt
	cp snq_te.txt snq_te_galibier128.txt
	ln -s snq_pram_galibier128.h snq_pram.h
	ln -s snq_decl_galibier128.h snq_decl.h

gen_stratix128:
	./generate_sysfs_stratixV.sh
	cp *.tcl ../script/tcl
	cp extoll_rf_sysfs.c extoll_rf_sysfs_stratixV.c
	cp extoll_rf_sysfs.h extoll_rf_sysfs_stratixV.h
	cp ../../../hw/extoll_r2_targets/stratix5_128/register_file/xml_output/doc/snq_tdg.txt .
	cp ../../../hw/extoll_r2_targets/stratix5_128/register_file/xml_output/doc/snq_te.txt .
	../../../sw/building_blocks/snqc/snqc snq_te.txt snq_tdg.txt snq_extra.txt 32 0xc800 snq_pram_stratix128.h snq_decl_stratix128.h
	rm -f snq_pram.h snq_decl.h
	cp snq_tdg.txt snq_tdg_stratix128.txt
	cp snq_te.txt snq_te_stratix128.txt
	ln -s snq_pram_stratix128.h snq_pram.h 
	ln -s snq_decl_stratix128.h snq_decl.h 