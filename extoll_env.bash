# This script sets the user environement correctly for Extoll R2 usage:

# Detects Extoll device
##############################
if $(lspci -n | grep -q "0007:0007"); then
	bdf=`lspci -n | grep "0007:0007" | cut -d " " -f 1`
	bus=`lspci -n | grep "0007:0007" | cut -d " " -f 1| cut -d ":" -f 1`
elif $(lspci -n | grep -q "1cad:0007"); then
	bdf=`lspci -n | grep "1cad:0007" | cut -d " " -f 1`
	bus=`lspci -n | grep "1cad:0007" | cut -d " " -f 1| cut -d ":" -f 1`
elif $(lspci -n | grep -q "1cad:0011"); then
	bdf=`lspci -n | grep "1cad:0011" | cut -d " " -f 1`
	bus=`lspci -n | grep "1cad:0011" | cut -d " " -f 1| cut -d ":" -f 1`
fi

export EXTOLL_R2_DEVICE="/sys/bus/pci/drivers/extoll/0000:$bdf/"
export EXTOLL_R2_SYSFS="$EXTOLL_R2_DEVICE/extoll_rf"

tty -s && echo "Sysfs is: $EXTOLL_R2_SYSFS"

