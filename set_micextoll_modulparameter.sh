#!/bin/bash

#Defines
temps=temp temp1 mictemp
#extoll2_drv = $? #$? returnvalue of the last command TODO: Why dont work this?
gpl="../../../../gpl/"
extoll2_drv="../extoll/sw/extoll_r2/extoll2_drv/"
knc_dev_sig="8086:225c"
extoll_dev_sig="1cad:0007"

APICICR0=0x0000A9D0 #Offset address of the API register inside the SBOX
SBOX=0x10000 #Offset address of the SBOX inside the bar/region 4
APIC_SIZE=0x8 #Size of one APIC Register
APIC_SELECT=0x7 #Number of the APIC Register we will use [0:7]


#we have to calculate this addresses later with the script 
#0x00002d is the HTOC specific command for extoll. We write only one quadword
#0x40002d is the HTOC specific command for extoll. We write two quadwords
snq0="40002d" #"fbe1aa0800002d" #ATTENTION! the lower 2 bit of the address (SBOX-Register) are not used!
snq2="F000002061" #TODO: calculate this inside extolldrv.c, when we register a irq number

#get the pci config informations of the installed extoll
#lspci -vv -n -d 0007:0007 > temp OLD VERSION
lspci -vv -n -d ${extoll_dev_sig} > temp

#check if a extoll card is installed
if ! test -s temp
then
	rm -f ${temps}
	echo "Can't find a extoll device, please check if the card is installed correct, or inform your administrator please"
	exit
else
	cat temp
fi
 
#get the pci config informations of the installed MIC
lspci -vv -n -d 8086:225c > mictemp

#check if there is a MIC card installed TODO:check if there are other device codes for MIC or not!
if ! test -s mictemp
then
	rm -f ${temps} 
	echo "Can't find a KNC device ${knc_dev_sig}, please check if the card is installed correct, or inform your administrator please"
	exit
else
	cat mictemp
fi

#micctrl -s > mictemp_online
#check if there is more than one mic, if yes, abort, because atm we only support system with one MIC
if micctrl -s | grep mic1 
then
	echo "You have installed more than one MIC. At the moment we only support systems with one MIC"
	rm -f ${temps}
	exit
fi

#check if the MIC is online
if ! micctrl -s | grep online
then
	echo "Your MIC device is offline, try to start it"
	micctrl -r
	wait

	if ! service mpss restart
	then
		echo "unable to start the MIC card"
		rm -f ${temps}
		exit
	fi
	
fi

#get lines with the information of the memory mapping
grep Region mictemp > mictemp1
mv mictemp1 mictemp

#delete the beginning of the line, so that the address is alwas the first element
sed 's/^[ \t]*//' < mictemp > mictemp1
mv mictemp1 mictemp

#delete the string before the memory addresss
sed -e 's/Region .: Memory at //' < mictemp > mictemp1
mv mictemp1 mictemp

#get the lines with the information of the memory mapping
grep Region temp > temp1
mv temp1 temp
#cat temp

#delete the beginning of the line, so that the address is always the first element
sed 's/^[ \t]*//' < temp > temp1
mv temp1 temp

#delete the string before the memory address
sed -e 's/Region .: Memory at //' < temp > temp1
mv temp1 temp
#cat temp


#extract the bar addresses for MIC
micbar0=0
micbar0_len=0
micbar4=0

readtemp=$(sed -n 1p < mictemp)
address=$(echo ${readtemp} | tr " " "\n")

set -- $address
micbar0=$1
shift
echo "Address for the MIC region0 is ${micbar0}"

#extract the size of the bar
micbar0_len=${3}
micbar0_len=${micbar0_len//[\[size=\]]/} #//[]/..deletes every sign inside the [] that is in the variable 



readtemp=$(sed -n 2p < mictemp)
address=$(echo ${readtemp} | tr " " "\n")

set -- $address
micbar4=$1
shift
echo "Address for the MIC region4 is ${micbar4}"
micbar4_hex=0x${micbar4}

#now we have to get the bits [63:34] of the address of region0. This is the offset value for the SMPT register
#echo $micbar0



#With the actual version of set_SMPT we don`t need this part, because set_SMPT do this for us
micbar0_hex=0x${micbar0}
echo $micbar0_hex
#we use a simple right shift to get the upper part of the address
SMPT=$(($micbar0_hex  >> 34))
#printf "The Bits [63:34] of the host address for the mapped MIC-GDDR5 RAM is: 0x%X\n" $SMPT #we have to use now printf, because echo is not able to display this correct
#echo "Match SMPT register format"

#Now we have to shift the value again 2 bits left, to match the SMPT register format. It ist not possible to just shift right 32 bits, because then it is not clear what value the lower 2 bits have
#SMPT=$(($SMPT << 2))
#We match now the SMPT register format, and just have to select the two lower bits.
#Bit [1] is reserved and have the reset value 0, so we choose also 0 for this
#Bit [0] is the "No Snoop" flag. Default is to not set this bit. TODO:Or should we set this bit?
#Because of the leftshift the 2 bits are already 0, so we have nothing to do.

#Bye default we write to the SMPT-register 31 TODO:add a test, if the selected register have the default value. If not, select another register
SMPTnum=31

pci_slot=$(lspci -d ${knc_dev_sig})
#we need no check, because we have already checked if there is a KNC

#get the first word. This is the pci-slot number
set -- $pci_slot
pci_slot=$1
#echo ${pci_slot}

resource_path='/sys/bus/pci/devices/0000:'${pci_slot}'/resource4' #TODO: get the path at runtime
#echo ${resource_path}
#printf "We will write now the value %X to the SMPT register ${SMPTnum}\n" $SMPT 
echo $resource_path
cd $gpl
cd extoll_tools
make 
#./config_SMPT ${resource_path}#display only the values of all SMPT registers
./config_SMPT ${resource_path} ${SMPTnum} ${SMPT} 0 0 


#go back to the starting dir. SMPT is now finished
cd ../${extoll2_drv}


#extract the bar addresses for extoll
replace[0]=0
replace[1]=0
replace[2]=0

for ((x=1; x<4; x++));
do
	readtemp=$(sed -n ${x}p < temp)
	address=$(echo ${readtemp} | tr " " "\n")

	set -- $address
	replace[${x}-1]=$1
	shift
	echo "Address for Bar${x} is ${replace[${x}-1]}" 
done

#clean up temp files
rm -f ${temps}



#With this address we have to calcuate and change the module loadparameter for extoll on MIC

#We need now the bits [33:0] from the host extoll-bar addresses. This are the lower 34 bits of the MIC address
#For this we first copy the values, rightshift them, and after this leftshift them back. So we can diff the hiher bits

#addresses of the extoll_bar from the view of MIC
micextoll_hex[0]=0
micextoll_hex[1]=0
micextoll_hex[2]=0

#addresses of the extoll_bar form the view of the host
extoll_hex[0]=0
extoll_hex[1]=0
extoll_hex[0]=0

for ((i=0; i<3; i++));
do
	a=0x${replace[${i}]} #First we have to convert the value into hex
	replace[${i}]=${a}
	extoll_hex[${i}]=${a}

	#now we can get the top bits
#	printf "replace=%X\n" ${replace[${i}]}
	a=$((${a} >> 34))
#	printf "a=%X\n" $a
	a=$((${a} << 34))
#	printf "a=%X\n" $a
#	printf "r=%X\n" ${replace[${i}]}

	#After this we have the bits [33:0] from the host adress, which are equal for the MIC Adress of extoll
	replace[${i}]=$(( ${replace[${i}]} - $a ))
	
	#now we have to set the bits [38:34], which are equal to the SMPT register number, we have written
	replace[${i}]=$(( ${replace[${i}]} + ($SMPTnum << 34) )) #we have to rightshift the SMPTnum, to match the right place for the bits

	#Final we have to set the Bit [29] to 1
	replace[${i}]=$(( ${replace[${i}]} + 0x8000000000 ))
	printf "micextoll_resource_start%i address is %X\n" ${i} ${replace[${i}]}

	#to add the values into the newvalue string, we have to convert it first into a string. Otherwise we would add the values as dec instead of hex values
	replace_hex[${i}]=$(printf "%X" ${replace[${i}]})
#	echo ${replace_hex[${i}]}
	extoll_hex[${i}]=$(printf "%X" ${extoll_hex[${i}]})
	
done


#calculate snq0 address
apic=$(( ${micbar4_hex} + ${SBOX} + ${APICICR0} + ${APIC_SIZE}*${APIC_SELECT}))
printf "We use APIC-Register %d at address %x\n" ${APIC_SELECT} ${apic}
#shift 2 digits now, to zero the lower bits. This is just for savety and normaly not needed
apic=$((${apic}>>2))
apic=$((${apic}<<2))
#transform the value into a string to build the command
apic=$(printf "%X" ${apic}) #Attention! We lost the information about the bits [24:25]

snq0=${apic}${snq0} #because we have zeroed the lower 2 bits, we can now just shift the address to fit the snq register format, where the address [64/32:2] starts at bit 26 of the register extoll_rf_snq_rf_irq_0
printf "We use for the extoll_rf_snq_rf_irq_0 register:  0x${snq0}\n"

#Now we can update the extoll load script for the MIC
search='\/sbin\/insmod \${MODUL_DIR}\/extoll\.ko micextoll\_resource\_start0\=.*'
newvalue='/sbin/insmod ${MODUL_DIR}/extoll.ko micextoll_resource_start0=0x'${replace_hex[0]}' micextoll_resource_start2=0x'${replace_hex[1]}' micextoll_resource_start4=0x'${replace_hex[2]}' micextoll_micbase0=0x'${micbar0}' micextoll_miclen0=0x'${micbar0_len}' extoll_physical_bar0_addr=0x'${extoll_hex[0]}' extoll_physical_bar2_addr=0x'${extoll_hex[1]}' extoll_rf_snq_rf_irq_0_param=0x'${snq0}' extoll_rf_snq_rf_irq_2_param=0x'${snq2}' $*'

sed -i "s!${search}!${newvalue}!g" micextoll_load.sh 

echo "Try to copy the new load script to the card"
scp ./micextoll_*oad.sh 172.31.1.1:~/

cd $gpl

echo "(Re)build the card modules?"
COMPILE="n"
read -n 1 -s COMPILE 
if [ "$COMPILE" = "y" ];
then
	make card-kmods 
fi

#echo "Try to copy the micextoll modules to the card"
make miccopy


