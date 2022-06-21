#!/bin/bash
. /opt/mpss/3.4.3/environment-setup-k1om-mpss-linux
cp arch_define.h_knc arch_define.h
make stratix128
make clean
make -f Makefile_BNC
