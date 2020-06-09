# Amira Script -*-Tcl-*-
#
# ParallelMovieMakerInit.hx
#
# author: Daniel Lichau (dlichau@mc.com)
# (C) copyright 2007, Mercury Computer Systems
# 


#
# Let Amira listen commands from socket port, possibly specified
#
if {[info exist env(AMIRA_SLAVE_PORT)]} {
    app listen $env(AMIRA_SLAVE_PORT)
} else {
    app listen
}

#
# Send back commands to master
# (ParallelMovieMaker module)
# 

proc ParallelMovieMaker_sendMaster { command } {
    global env
    set command [concat $env(AMIRA_MASTER_MODULE) " " $command]
    app send "$command" $env(AMIRA_MASTER_NAME) $env(AMIRA_MASTER_PORT)
    # [string trim $env(AMIRA_MASTER_NAME)] 
}

#
# Procedures to be launched from master
#

proc ParallelMovieMaker_load { script } {
    global env
    global AMIRA_ROOT
    global SCRIPT
    global SCRIPTDIR
    set slaveIdent "#$env(AMIRA_SLAVE_INDEX) $env(AMIRA_SLAVE_NAME) port [app port]"
    if {[catch {load $script} errorMsg]} {
	ParallelMovieMaker_sendMaster "reportError \"$slaveIdent\" \"no such script file\" " 
    } else {
	ParallelMovieMaker_sendMaster "reportLoadedScript \"$slaveIdent\" " 
    }
}

proc ParallelMovieMaker_run { nodeIndex startStep numStep incStep outputdir resolutionX resolutionY useOffscreenSnapshot reportImageDone noOutput} {
    global env
    global theNodeIndex
    global theResolutionX 
    global theResolutionY 
    global imageFilenameFormatString
    global reportImageDoneFlag
    
    # set global variables
    set theNodeIndex $nodeIndex
    set theResolutionX $resolutionX
    set theResolutionY $resolutionY
    set reportImageDoneFlag $reportImageDone
    
    # end step
    set endStep [expr $startStep + ($numStep * $incStep) - 1]

    # search for module with time port without upstream connection
    set  controlModule ""
    set timePort ""
    set initTime ""
    foreach module [all -visible] {
	foreach port [$module allPorts] {
	    if { [$module $port isOfType HxPortTime]  && [$module $port source] == "" } {
		set controlModule $module
		set timePort $port
	    }
	}
    }

    # initialize control module 
    $controlModule $timePort setSubMinMax $startStep $endStep; 
    $controlModule $timePort setIncrement $incStep;
    $controlModule $timePort setValue $startStep; 

    # show module properties 
    $controlModule select  

    $controlModule compute;
    $controlModule  fire; 
    viewer 0 redraw;

	set outputdirFormated 0
    # Replace #### by image number in file string
    while {$outputdirFormated == 0} {
		if {[regexp "#+" $outputdir corresp]} {
			set len [string length $corresp]
			regsub "#+" $outputdir %d${corresp} imageFilenameFormatString
			set filePattern ""
			# Do only clean on first node 
			if { $nodeIndex == 0 } {
				regsub "#+" $outputdir * filePattern
				system "rm -f $filePattern"
			}
			set outputdirFormated 1
		} else {
			if { $outputdir != "" } {
				set outputdir  ${outputdir}/output-####.jpg
			} else {
				set outputdirFormated 1
			}
		}
    }
    
    if { $useOffscreenSnapshot == 0} {
		if { $outputdir != "" } {
			set numFrames [expr $endStep + 1 - $startStep]
			set filename [format $imageFilenameFormatString $nodeIndex]
			# Requires that the viewer is set as top level window in preferences
			viewer 0 setSize $resolutionX $resolutionY
			set MovieMaker [create HxMovieMaker]
			$MovieMaker size setValue 3
			$MovieMaker resolution setMinMax 0 0 2048
			$MovieMaker resolution setValue 0 $resolutionX
			$MovieMaker resolution setMinMax 1 0 2048
			$MovieMaker resolution setValue 1 $resolutionY
			$MovieMaker frames setValue $numFrames
			if { $noOutput == 0 } {
				$MovieMaker time connect $controlModule
			}
			$MovieMaker filename setValue $filename
			$MovieMaker action setValue 0; 
			
			if { $reportImageDone } {
				regexp "#+" $outputdir corresp
				set len [string length $corresp]
				regsub "#+" $outputdir %d%0${len}d imageFilenameFormatString	
				$controlModule time setTimeCallback ParallelMovieMaker_movieMaker_timeCallback [concat AnimationStateChanged | NewTimeStep]
			} else {
				$controlModule time setTimeCallback ParallelMovieMaker_movieMaker_timeCallback AnimationStateChanged
			}
			$controlModule time play
		} else {
			viewer 0 redraw;
		}
    } else {
		regexp "#+" $outputdir corresp
		set len [string length $corresp]
		regsub "#+" $outputdir %d%0${len}d imageFilenameFormatString
		
		if { $noOutput == 0 } {
			$controlModule time setTimeCallback ParallelMovieMaker_offscreen_timeCallback [concat AnimationStateChanged | NewTimeStep]
		} else {
			$controlModule time setTimeCallback ParallelMovieMaker_offscreen_timeCallback AnimationStateChanged
		}
		$controlModule time play
    }
}

proc ParallelMovieMaker_imageDone { step filename} {
	global theNodeIndex
	
	ParallelMovieMaker_sendMaster "reportImageDone $theNodeIndex $step \"$filename\" "
} 

proc ParallelMovieMaker_offscreen_timeCallback { eventType eventValue } {
	global theNodeIndex
	global theResolutionX
	global theResolutionY
	global reportImageDoneFlag
	global imageFilenameFormatString
	
	if { $eventType == "AnimationStateChanged" && $eventValue == 0 } {
		ParallelMovieMaker_sendMaster "reportJobDone $theNodeIndex" 
	} elseif { $eventType == "NewTimeStep" && $imageFilenameFormatString != "" } {
		set filename [format $imageFilenameFormatString $theNodeIndex [expr $eventValue - 1]]
		viewer 0 snapshot -offscreen $theResolutionX $theResolutionY $filename	
		if { $reportImageDoneFlag } {
			ParallelMovieMaker_imageDone [expr $eventValue - 1] $filename		
		}
	}
}

proc ParallelMovieMaker_movieMaker_timeCallback { eventType eventValue } {
	global theNodeIndex
	global reportImageDoneFlag
	global imageFilenameFormatString
	
	if { $eventType == "AnimationStateChanged" && $eventValue == 0 } {
		ParallelMovieMaker_sendMaster "reportJobDone $theNodeIndex" 
	} elseif { $eventType == "NewTimeStep" && $reportImageDoneFlag } {
		set filename [format $imageFilenameFormatString $theNodeIndex [expr $eventValue - 1]]
		ParallelMovieMaker_imageDone $eventValue $filename
	}
}

#
# Tell master that slave is initialized
# 

ParallelMovieMaker_sendMaster "reportSlaveStarted $env(AMIRA_SLAVE_NAME) $env(AMIRA_SLAVE_INDEX) [app port] [pid]"
