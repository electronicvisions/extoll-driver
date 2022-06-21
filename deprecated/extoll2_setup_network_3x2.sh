#!/bin/bash

# (C) 2012 by EXTOLL GmbH

#########################################################
#                                                       #
# Simple Script to configure an EXTOLL R2 Network       #
#                                                       #
# This script uses ssh to log into a list of nodes      #
# and loads the kernel drivers using extoll_load.sh     #
# on each node.                                         #
# Then the routing table is set as specified below      #
#                                                       #
# To use this script, you need to edit the following    #
# variables below:                                      #
#                                                       #
# * path: this should point to the path of the sysfs    #
#    entries of EXTOLL on the nodes to be configured    #
# * num_nodes: set this variable to the number of nodes #
# * node_base_name: set this to the base host name of   #
#   the nodes to be configured. The hostname for ssh    #
#   will then be generated by concatenating a number    #
#   to this base name                                   #
# * routing: the routing table of the network.          #
#   This quadratic table consists of one entry for each #
#   destination on each host. See also below            #
#########################################################

#source to get path information                                                        
source ../extoll_env.bash
#remember sysfs path
path=$EXTOLL_R2_SYSFS

path=/sys/bus/pci/devices/0000\:20\:06.0/extoll_rf

#set size of the network and basename of nodes -> needs to be adjusted for the cluster
num_nodes=6
node_base_num=8
node_base_name=peac
#Routing Table:
# a table of size $num_nodes * $num_nodes
# each row sets the table on one node, first row on node 0, second row on node 1 etc
# within row i, number j represents the link to forward a packet from i to j
routing=(
         0 0 3 0 3 0
         0 0 0 3 0 3
         2 1 0 1 3 1
         0 2 0 0 0 3
         2 1 2 1 0 1
         0 2 0 2 0 0
        )

#define the routing strings for link0 to link3
link[0]=0x00000000
link[1]=0x21080100
link[2]=0x42100200
link[3]=0x63180300

#set a single routing entry in all inports in one EXTOLL Xbar
#Parameter: $1: node number to set the entry on
#Parameter: $2: nodeid of the destination, i.e. the routing entry index
#parameter: $3: the entry to be set (one of the value of link[0..3])
set_routing_entry()
{
local node_name=${node[$1]}
local dest_node=$2
local entry=$3
#echo called with $1 $2 $3
for i in 0 1 2 3 4 5 6 7 ; do
 #echo node: $node_name dest_node: $dest_node entry: ${entry} file: $path/extoll_rf_nw_xbar_rf_inp${i}_lrt_p0
 ssh $node_name "echo $dest_node ${entry}> $path/extoll_rf_nw_xbar_rf_inp${i}_lrt_p0"
done
}

#completely initialize one node
#Parameter: $1: node num
#parameter: $2 .. ${num_nodes}: links to reach the corresponding node
init_node()
{
 current_node=$1
 routing_links=( "${@:2}" )
 #echo "Node to be configured is $current_node, routing links is $routing_links" 
 #echo  "Init node with hostname ${node[$1]}"
 ssh ${node[$1]} "$EXTOLL_R2_HOME/sbin/extoll_load.sh"
 ssh ${node[$1]} 'for cpu in /sys/devices/system/cpu/cpu? ; do echo performance> ${cpu}/cpufreq/scaling_governor ; done'

 hex_num=`printf '%x\n' $1`
 echo Setting nodeid to 0x${hex_num}000000
 ssh ${node[$1]} "echo 0x${hex_num}000000 > $path/*node"
 let entry_index=0
 for e in ${routing_links[*]} ; do
    current_dest=$entry_index
    current_entry=${link[$e]}
    echo "Routing entry $current_dest should use link $e with a value of $current_entry"
    set_routing_entry $current_node $current_dest $current_entry
    let entry_index=$entry_index+1
 done
 return 0
}

echo "EXTOLL Network Setup Script"
echo "(C) 2012 by EXTOLL GmbH"
echo -n
# generate node name array
for ((i=$node_base_num, j=0;i < $node_base_num+$num_nodes ; i++, j++))
do
 #echo $j $i
 if (($i < 10)) ; then num=0$i ; else num=$i ; fi
 #echo $j $i
 echo "Found node $node_base_name$num"
 node[$j]=$node_base_name$num
done

# We define columns ans calculate rows accordingly
cols=$num_nodes
rows=$num_nodes

for ((n=0;n < $num_nodes ; n++))
do
 let start_index=n*$num_nodes
 node_routing=${routing[*]:$start_index:$num_nodes}
 #echo "For node $n, start is $start_index, routing is $node_routing"
 echo "Setting up node ${node[$n]}"
 init_node $n  "${node_routing[*]}"
done

echo "Setting up of EXTOLL network with $num_nodes nodes done."