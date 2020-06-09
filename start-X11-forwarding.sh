#!/bin/bash
### start the XQuartz properly :-)

tput setaf 2;
echo "  "
echo "  Setting up X11 forwarding using socat"
echo "  "  
tput sgr0;
### check of socat is already running
echo "  Check if socat is already running"
if lsof -n -i | grep 6000 ; then
    echo "  socat port occupied: killing it "
    kill -9 `lsof -n -i | grep 6000 | awk '{ print $2}'`
    echo `date +"%Y/%m/%d %H:%M:%S"`   "socat killed" >> output.txt
    tput setaf 1; echo "  socat port freed"; tput sgr0;
else
    echo "  socat port seems to be free"
fi
### check if socat is installed
tput setaf 2; echo "  Check if socat is installed"; tput sgr0;
brew list socat || brew install socat
tput setaf 2; echo "  Socat should be availabe" ; tput sgr0;
### starting socat
echo "  Starting socat"
socat TCP-LISTEN:6000,reuseaddr,fork UNIX-CLIENT:\"$DISPLAY\" >> output.txt 2>&1 &
echo `date +"%Y/%m/%d %H:%M:%S"`   "socat started" >> output.txt
echo "  Starting headless XQuartz"
open -a Xquartz

read -p "   Do you wish to run the Xeyes test (Y/N)?" yn
case $yn in
    [Yy]* ) 
            echo "  Gathering your IP"
            IP=`ifconfig | grep "inet " | grep -v 127.0.0.1 | cut -d\  -f2 | head -1`
            echo "  Your IP seems to be: " $IP
            echo "  Calling an Xeyes docker"
            echo ""
            tput setaf 1;
            echo "  WARNING: the docker image will be downloaded if not present"
            echo "  WARNING: the script will not end until you close the Xeyes"
            echo "  "
            tput sgr0;
            docker run -e DISPLAY=$IP:0 gns3/xeyes
            echo "  No more tests to do... exiting"
            ;;
    [Nn]* )
            echo "  Have a nice day! ";;
    * ) echo "  Please answer yes or no.";;
esac

tput setaf 2;
echo "  "
echo "  All systems OK  "
echo "  "
tput sgr0;
