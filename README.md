# Amira on a OSX docker
WHAT IS THIS : 
A CentOS 7 docker with an amira license and one amira instance.  
Features:  
- CentOS 7 Docker Container 
- Amira license server
- Amira 5.5.0

We start with a clean OSX 10.15.3 (Catalina).

To download docker for mac, follow the instructions (https://docs.docker.com/docker-for-mac/install/).   

## Running the amira docker (first time)

- Choose a folder where the docker will lay. \  
- Download the docker. WARNING: it's quite big (2.1G) \
 ``git clone https://github.com/jucastil/amira-mac.git`` \  
- Go into the docker folder **amira-mac**.\
``cd amira-mac``
- Start the X11 forwarding. \ 
``./start-X11-forwarding.sh``.\
The script will kill the port forwarding if already running.\
It will also download a docker image to test the X11.\
You may choose not to run the Xeyes test.\
Expected output:\

<details>
  <summary>Click to expand!</summary>
  
  ```javascript
 
  Setting up X11 forwarding using socat
  
  Check if socat is already running
  socat port seems to be free
  Check if socat is installed
  /usr/local/Cellar/socat/1.7.3.4/bin/filan
  /usr/local/Cellar/socat/1.7.3.4/bin/procan
  /usr/local/Cellar/socat/1.7.3.4/bin/socat
  /usr/local/Cellar/socat/1.7.3.4/share/man/man1/socat.1
  Socat should be availabe
  Starting socat
  Starting headless XQuartz
   Do you wish to run the Xeyes test (Y/N)?Y
  Gathering your IP
  Your IP seems to be: XXXX
  Calling an Xeyes docker

  WARNING: the docker image will be downloaded if not present
  WARNING: the script will not end until you close the Xeyes
  
  No more tests to do... exiting
  
  All systems OK  
  ```
</details>

- Start the docker.\
``./start-amira-docker.sh``. \
This script will do several things:
1. Download the docker image (if not there)
2. Create a docker named COMPUTERNAMEamira (if not there) 
3. Start the docker (if not running)
4. Install in the docker some missing packages 
5. Start the amira license server.
6. Start amira.
First time you run the script, a window will pop-up asking you to accept the license.\
Once accepted, amira should start.\
Closing it will just close amira, not docker.\ 
Expected output:\

<details>
  <summary>Click to expand!</summary>
  
  ```javascript
        Setting up your amira docker 
  
        Default docker name now:  COMPUTERNAMEamira
        Is the name OK (Y/N)?Y
        Continuing
        Pulling docker image
        Using default tag: latest
        latest: Pulling from andrewklau/centos-lamp
        Status: Downloaded newer image for andrewklau/centos-lamp:latest
        docker.io/andrewklau/centos-lamp:latest
        Image installed
        No docker named COMPUTERNAMEamira listed. Creating it
        a25230663a71e12eade526d29fa782bf558ed19c123bc7bce71cfada3bb219b2
        A docker COMPUTERNAMEamira created. Running post-creation and first run
        ... now packages installed...
        Complete!
        ...done. Customizing docker...
        Licensing for: sbmm329amira
        ...done. Starting license server...
        ...done. All ready to launch.
         Using arch-LinuxAMD64-Optimize ...
 
  ```
</details>

## Run the amira docker (after the initial install)
- Check "COMPUTERNAMEamira" is running ``docker ps -a`` should show it as running. \
- Run AMIRA. Type ``docker exec -it COMPUTERNAMEamira /extra/start-amira.sh``. \

## Issues 
- No X11 (socat error).  Run ``./start-X11-forwarding.sh``.\. <br>
- amiramain: cannot connect to X server host.docker.internal:0. Run ``./start-X11-forwarding.sh``.\
You can always remove the docker and install it again :-)

## IMPORTANT remarks

- There is **no data share** mapped inside the container. \  
If you want to do that, simply edit **start-amira-docker.sh** and map the corresponding folder. \
- There is **no user defined** inside the container. Everything runs as root. \
If you don't want to run as root, please add yourself as an user via command line. \
NOTE that this docker visible only in the same subnet. \
NOTE that not all the options were tested. \
