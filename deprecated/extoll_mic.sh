# This script sets the user environement correctly for Extoll R2 usage:
# - LD_LIBRARY_PATH for C/C++ libs
# - PATH for executables
# - TCL and Python Env Variables to find the modules
# - Detects the location of Extoll device in pci space

# Location of this script for path setups
###########################################
export EXTOLL_R2_HOME="$(dirname "$(readlink -f ${BASH_SOURCE[0]})")"
#export EXTOLL_R2_HOME=/extoll2 

# Detects Extoll device
##############################

if $(lspci -n | grep -q "0007:0007"); then
	bdf=`lspci -n | grep "0007:0007" | cut -d " " -f 1`
	bus=`lspci -n | grep "0007:0007" | cut -d " " -f 1| cut -d ":" -f 1`
elif $(lspci -n | grep -q "1cad:0007"); then
	bdf=`lspci -n | grep "1cad:0007" | cut -d " " -f 1`
	bus=`lspci -n | grep "1cad:0007" | cut -d " " -f 1| cut -d ":" -f 1`
fi

export EXTOLL_R2_DEVICE="/sys/bus/micextoll/devices/extoll/"
export EXTOLL_R2_SYSFS="$EXTOLL_R2_DEVICE/extoll_rf"


# PATH
###########################
export PATH=$EXTOLL_R2_HOME/bin:$EXTOLL_R2_HOME/sbin:$PATH

# LD_LIBRARY_PATH
###########################
export LD_LIBRARY_PATH=$EXTOLL_R2_HOME/lib:$LD_LIBRARY_PATH

# TCL
########################
#export TCL_8_4_TM_PATH=$TCL_8_4_TM_PATH:"$EXTOLL_R2_HOME/lib/tcl/"
#unset TCLLIBPATH
#export TCLLIBPATH="$TCLLIBPATH $EXTOLL_R2_HOME/lib/tcl/"

# Python
#########################
#unset PYTHONPATH
#export PYTHONPATH=$PYTHONPATH:"$EXTOLL_R2_HOME/script/"

tty -s && echo "Loaded Extoll R2 SW environment at: $EXTOLL_R2_HOME"
tty -s && echo "Sysfs is: $EXTOLL_R2_SYSFS"

