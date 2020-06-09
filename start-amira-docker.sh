#!/bin/bash

NAME=`hostname -s`"amira"
HOSTNAME=`hostname -s`"amira"

function run_amira_docker {

    docker run --name $NAME --hostname=$HOSTNAME --mac-address "90:b1:1c:3d:e0:7a" -e DISPLAY=host.docker.internal:0 -d -p 8080:80 \
    -v `pwd`/opt:/opt \
    -v `pwd`/extra:/extra \
    -v `pwd`/html:/var/www/html \
    -t andrewklau/centos-lamp
}

echo "  "
echo "  Setting up your amira docker "
echo "  "

### docker name
echo "  Default docker name now: " $NAME
read -p "   Is the name OK (Y/N)?" yn
case $yn in
    [Yy]* ) 
            echo "  Continuing"
            ;;
    [Nn]* )
            read -p "  Please introduce docker name :" NAME
            echo "  docker will be named: " $NAME
            echo "  Continuing"
            ;;
    * ) echo "  Please answer yes or no.";;
esac

### check image is already installed
if [[ "$(docker images -q andrewklau/centos-lamp 2> /dev/null)" == "" ]]; then
    echo "  Pulling docker image"
    docker pull andrewklau/centos-lamp
    echo "  Image installed"
else
    echo "  Image installed already, using it"
fi

# ### check a docker with the same name is created
isthere=`docker ps -a | grep $NAME`
if [ -z "$isthere" ]; then
    echo "  No docker named "$NAME" listed. Creating it"
    run_amira_docker
    echo "  A docker "$NAME" created. Running post-creation and first run"
    docker exec $NAME extra/extra-packages.sh
else
    echo "  Something named "$NAME" is there. "
    read -r -p "  Would you like to remove it? (y/N) " response
    case "$response" in
        [yY][eE][sS]|[yY])
            docker rm $NAME
            echo "  docker removed: run the script again to create it anew"
            ;;
        *)
            echo "  Starting the existing docker "
            docker start $NAME
            echo "  Started : please check your docker is running"
            ;;
    esac
fi
