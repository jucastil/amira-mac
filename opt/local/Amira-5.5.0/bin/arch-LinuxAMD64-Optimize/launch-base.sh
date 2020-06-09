#!/bin/sh

#echo LAUNCHER called : $@
# <hostfile> <oiru executable> <exec_parameters>

# check that the given hostfile exist

	# get an array of nodes name to start
	i=0
	for item in $(cat "$1")
	do
	nodelist[$i]=$item
	i=`expr $i + 1`
	done

	nbnodes=${#nodelist[*]}
	
# get the masterOIRU for cluster communication
# by default it is the first node in the hostfile
masterOIRU=${nodelist[0]}

# this is the communication port used for cluster communication
# change it as required
port=4568

# get and check the name of the executable to launch
oiru_exec=$2

# get and check the name of the cluster com library used
oiru_lib=$3

# get executable parameters
shift 3
oiru_params=$@

# launch all oiru now !
nodeid=0
fcount=${#nodelist[@]}
while [ $nodeid -lt $fcount ]; do
  echo "ssh -x -f ${nodelist[$nodeid]} $oiru_exec $oiru_lib $masterOIRU $port $nbnodes $nodeid $oiru_params"
  ssh -x -f ${nodelist[$nodeid]} $oiru_exec $oiru_lib $masterOIRU $port $nbnodes $nodeid $oiru_params
  nodeid=`expr $nodeid '+' 1`
done

exit 0
