#!/bin/sh
# $1 = 1 initiate session / 0 stop session
# $2 = session Id
# $3 = hostname where session has to be loaded
# $4 = OIV_REMOTERENDER_DISPLAY definition. match the display settings defined in RemoteVizD_resources.cfg for the defined hostname ($3)
# $5 = VNC port. Defines the communication port to use for VNC data. This 
# $6 = VNC password (can be used to set VNC Server password on VNC Server startup (when supported)
# $7 = hostname where RemoteViz Daemon is running
# $8 = connection port to daemon

if [ $1 -eq 1 ]; then

	# ensure the vncserver is free on requested display.
	ssh $3 "vncserver -kill :$2"

	# start a new VNC server
	ssh $3 "vncserver :$2 -depth 24 -rfbport $5 -AlwaysShared" &

	# Set environment and start application
	ssh $3 "

		# tcsh shell
#		setenv DISPLAY :$2
#		setenv OIV_REMOTE_ENABLE 1
#		setenv OIV_REMOTERENDER ON
#		setenv OIV_REMOTERENDER_DISPLAY $4
#		setenv REMOTEVIZ_DAEMON_LOCATION $7
#		setenv REMOTEVIZ_DAEMON_PORT $8
 
		# bash shell
		export DISPLAY=:$2
		export OIV_REMOTE_ENABLE=1
		setenv OIV_REMOTERENDER=ON
		export OIV_REMOTERENDER_DISPLAY=$4
		export REMOTEVIZ_DAEMON_LOCATION=$7
		export REMOTEVIZ_DAEMON_PORT=$8

		sleep 5
		xhost +
		QtReadFile"

else
	# kill the VNC server
	ssh $3 "vncserver -kill :$2"
fi
