#!/bin/sh

if [ `id -u` -ne 0 ]
then
    echo 'Error: must be root.'
    exit -1
fi

if [ ! -f serviceSetup.sh ] || [ ! -f start ]
then
    echo 'Error: must be in the $AMIRA_ROOT/bin directory'
    exit -1
fi 

cmd='sh '`pwd`'/serviceSetup.sh install hxvrdaemon "Daemon for VR Pack cluster" "'`pwd`'/start -clusterdaemon -nogui" ; sh '`pwd`'/serviceSetup.sh start hxvrdaemon'

# For each nodes install the service
for hostname in $*
do
  ssh $hostname "$cmd" 
done
