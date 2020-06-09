source $AMIRA_ROOT/share/hxdemos-scripts/makeIcon.hx
proc makeAllSnapshots {{snapshotname "gfx/step%s"}} {
	set numDemos [llength [DemoSequence getVar demoList]]

	for {set demo 0} {$demo < $numDemos} {incr demo} {

		set thisDemo [lindex [DemoSequence getVar demoList] $demo]
		# in $thisDemo, the first element is the demo name, the second is the script-loading, the 3RD is
		# the first step
		set numSteps [expr [llength $thisDemo] - 2]
	    
		DemoSequence startDemo $demo 0
		
		# go to the correct demo directory
		cd [subst [ DemoSequence getDemoDir $demo ] ]
		if {![file isdirectory gfx]} {
			# make directory gfx
			file mkdir gfx
		}
		
		makeIcon "gfx/step0" 0 150
	    
		for {set step 1} {$step <=$numSteps} {incr step} {
			DemoSequence startDemo $demo $step
		    
			cd [ subst [ DemoSequence getDemoDir $demo ] ]
		    makeIcon [format "gfx/step%s" $step] 0 150
		}
	}
}

proc startDemoSequence { {whichFile {}} } {
	global AMIRA_ROOT
		
	# Amira Script
	remove -all
	remove DemoStatusDisplay DemoSequence

	# Create viewers
	viewer setVertical 0

	viewer 0 setBackgroundMode 1
	viewer 0 setBackgroundColor 0 0 0
	viewer 0 setBackgroundColor2 0 0 0.4
	viewer 0 setTransparencyType 6
	viewer 0 setAutoRedraw 0
	viewer 0 decoration 0
	viewer 0 show
	#mainWindow show

        # Creating a HxAnnotation module here is not neccessary
        # anymore since DemoSequence creates one on its own.
	#set hideNewModules 0
	#create HxAnnotation {DemoStatusDisplay}
	#DemoStatusDisplay setIconPosition 301 10
	#DemoStatusDisplay fire
	#DemoStatusDisplay color setColor 0 1 1 1
	#DemoStatusDisplay options setValue 0 1
	#DemoStatusDisplay postype setValue 0
	#DemoStatusDisplay position setMinMax 0 -2000 2000
	#DemoStatusDisplay position setValue 0 -20
	#DemoStatusDisplay position setMinMax 1 -2000 2000
	#DemoStatusDisplay position setValue 1 20
	#DemoStatusDisplay ndcposition setMinMax 0 -1 1
	#DemoStatusDisplay ndcposition setValue 0 0.0500000007450581
	#DemoStatusDisplay ndcposition setMinMax 1 -1 1
	#DemoStatusDisplay ndcposition setValue 1 -0.0500000007450581
	#DemoStatusDisplay text setValue "."
	#DemoStatusDisplay setFont -bold -noitalic  Helvetica
	#DemoStatusDisplay setFontSize 14
	#DemoStatusDisplay fire
	#DemoStatusDisplay setViewerMask 32767

	set hideNewModules 0
	create HxScriptObject {DemoSequence}
	{DemoSequence} script setValue ${AMIRA_ROOT}/share/script-objects/DemoSequence.scro
	DemoSequence setIconPosition 160 10
	{DemoSequence} setVar {scroTypeDemoSequence} {1}
	{DemoSequence} setVar {currentDemo} {-1}
	{DemoSequence} setVar {currentStep} {-1}
	{DemoSequence} setVar {init} {0}
	{DemoSequence} setVar {defDemo} {}
	DemoSequence fire
	if {$whichFile != ""} {
		DemoSequence demoFile setState $whichFile
		DemoSequence demoList setOptValue 0 0
		DemoSequence options setValue 0 1
		DemoSequence options setValue 1 1
		DemoSequence fire
	}
	DemoSequence setViewerMask 32767
	DemoSequence select

	set hideNewModules 0

	viewer 0 setCameraPosition -0.161631 -0.464742 1.1436
	viewer 0 setCameraOrientation 0.179289 0.211403 -0.960814 3.05405
	viewer 0 setCameraFocalDistance 1.08615
	viewer 0 setAutoRedraw 1
	viewer 0 redraw
}

