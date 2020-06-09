if {![info exists AMIRA_DEMOS]} {
	set AMIRA_DEMOS $env(AMIRA_DEMOS)
}
if {![info exists AMIRA_ROOT]} {
        set AMIRA_ROOT "[file join [pwd] [file dir [info script]]]/../..";
} 
source $AMIRA_ROOT/share/hxdemos-scripts/setuphelpers.tcl
source $AMIRA_ROOT/share/hxdemos-scripts/checkAttributes.tcl

# main procedure for recursive directory browsing
# returns list with 2 entries
# 0: 0 in case of success, 1 if outdir exists and --force is not active
# 1: number of processed _demos_
proc descend { outdir includeSteps excludeAbs visitedFoldersName { depth 0 } {forceOverwriteOutput 1} {used_attributes [list]} {attribute_expression {}} } {
        #call by name
        upvar $visitedFoldersName visitedFolders
	global AMIRA_DEMOS
	global AMIRA_ROOT
	
        set retCreate [createOutDirSafe $outdir $forceOverwriteOutput]

        if {$retCreate} {
          # outdir exists and no action should be taken in this case
          return [list $retCreate 0]
        }

	set PWD [pwd]

	regsub -nocase $AMIRA_DEMOS $PWD \$AMIRA_DEMOS demodir
	set demodir "[stripLastSlash $demodir]/"	

	# first decide, if we have a container or a demo by checking the 
	# style-attribute in the <description> tag of description.xml
	# also check the stepmode-tag in demo that is returned after /
        # the stepmode tag is saved here in variable status
	
	set dsList [ split [fetchDescriptionStyle $PWD/description.xml] "/" ]
	
	set whatHaveWe [lindex $dsList 0]
	set status [lindex $dsList 1]
	
	allActions $outdir
        
        # number of processed added demos
        set num_added_demos 0
        
	if {$whatHaveWe == "demo"} {
                
                # if current folder is a demo, check if correct attributes are set, if attributes are given               
                if {[llength $used_attributes] > 0} {
                  # attributes ARE given
                  # process description file
                  set description_xml "$PWD/description.xml"
                  
                  # if expression is not fulfilled by current file, return 0 - don't do anything with this demo
                  if {[file_fulfills_attributes $attribute_expression $used_attributes $description_xml]==0} {
                    return [list 0 0]
                  }
                }
                
        
		# create index.html and stepscripts. Don't descend
		demoActions $outdir $PWD $demodir $includeSteps $status $depth
                
                # store the local folder in the visitedFolders-List
                # actually all folders from $AMIRA_DEMOS to $PWD have to be added if not done already
                appendToVisitedFolders visitedFolders $PWD
                
                return [list 0 1]
	
	} elseif {$whatHaveWe == "container" || $whatHaveWe == "project" || $whatHaveWe == "projectlist"} {

		set linkTitle ""
		if { $depth==0 } {			
			set linkTitle "demo inventory"
		}
		
		# write the header of the container/projectlist to $outdir/index.html
		exec xsltproc --stringparam linkTitle $linkTitle --stringparam date [exec date] --stringparam action header --stringparam wd $PWD/ --stringparam relativeSrcDir [ relativeSrcDir $outdir $PWD ] $AMIRA_ROOT/share/hxdemos-scripts/collectDemo.xsl $PWD/description.xml > $outdir/index.html
		
		
		# remove old demosequence.demo file
		file delete $outdir/demosequence.demo
		
		# get and step through file list of current directory
		set files [lsort [glob *]]
		foreach dir $files {
			
			if {[file isdirectory $dir] && $dir != "." && $dir !=".." && [ lsearch -exact $excludeAbs $PWD/$dir ] == -1} {
				if {[file exists $dir/description.xml]} {
					# step into folders with description.xml
					
									
					# continue recursive browsing
                                        # setting the dir is necessary for symbolic links
                                        set saveDir [ pwd ]
					cd $dir
					set ret [ descend $outdir/$dir [ list ] excludeAbs visitedFolders [expr $depth+1] 1 $used_attributes $attribute_expression ]
                                        
                                        cd $saveDir
                                        
                                        
                                        # find out the number of added demos by last call of descend
                                        set num_last_added_demos [lindex $ret 1]
                                        incr num_added_demos $num_last_added_demos
                                        
                                        if {$num_last_added_demos > 0} {
                                          # only if a demo has been processed 
					
                                          #demosequence stuff
                                          writeDemoSequence $outdir $dir $depth
                                          
                                          # append a table row with thumbnail to $outdir/index.hmtl
                                          exec xsltproc --stringparam wd $PWD/$dir/ --stringparam path $dir/ --stringparam relativeSrcDir [ relativeSrcDir $outdir $PWD/$dir ] $AMIRA_ROOT/share/hxdemos-scripts/collectDemo.xsl $PWD/$dir/description.xml >> $outdir/index.html                                
                                        } else {
                                          # going into folder $dir was a complete utter waste of time
                                          # so output folder $outdir/$dir should be deleted
                                          deleteFolder $outdir/$dir
                                        }
					
				}
			}
		}
		# finally write footer to $outdir/index.html, i.e. at least </table></body></html>
		exec xsltproc --stringparam action footer $AMIRA_ROOT/share/hxdemos-scripts/collectDemo.xsl $PWD/description.xml >> $outdir/index.html

	} else {
		puts "run '\$AMIRA_ROOT/share/hxdemos-scripts/prepareDemos' in a directory below \$AMIRA_DEMOS/src\n";
	}
        return [ list 0 $num_added_demos ]
}


# append all Folders from $AMIRA_DEMOS to $PWD to $visitedFolders
proc appendToVisitedFolders { visitedFoldersName PWD} {
        #call by name
        upvar $visitedFoldersName visitedFolders
        global AMIRA_DEMOS

        # take $AMIRA_DEMOS from $PWD
        regsub -nocase $AMIRA_DEMOS $PWD "" relSrcDir
        
        # get all subsequent folders
        
        set foldersToVisit [ split $relSrcDir "/" ]
        set momentaryFolder $AMIRA_DEMOS
        foreach folder $foldersToVisit {
          if {$folder !=""} {
            append momentaryFolder "/$folder"
            if {[lsearch $visitedFolders $momentaryFolder ]==-1} {
              lappend visitedFolders $momentaryFolder
            }
          }
          
        }
}

# writes common output for each description style, i.e. demosequence.hx-files and snapshotscripts
proc allActions { outdir } {
	global AMIRA_DEMOS
	
	regsub $AMIRA_DEMOS $outdir \$AMIRA_DEMOS AMIRA_DEMOSoutdir
	
	# write demosequence-script
	writeToFile "$outdir/demosequence.hx" [subst {# Amira Script
source \$AMIRA_ROOT/share/hxdemos-scripts/demosequence.hx
startDemoSequence $AMIRA_DEMOSoutdir/demosequence.demo
}]

	# write snapshot-script
	writeToFile "$outdir/makeSnapshots.hx" [subst {# Amira Script
if {!\[info exists AMIRA_DEMOS]} {
	set AMIRA_DEMOS \$env(AMIRA_DEMOS)
}
source \$AMIRA_ROOT/share/hxdemos-scripts/demosequence.hx
startDemoSequence $AMIRA_DEMOSoutdir/demosequence.demo
makeAllSnapshots
}]
}

proc performFullDemo { includeSteps status} {
  set fullDemo [expr [llength $includeSteps] == 0] 
  if {!$fullDemo} {
      if {$status == "static"} {
          for {set i 0} {$i < [llength $includeSteps]} {incr i} {
              set indexi [lindex $includeSteps $i]
              set wanti [expr $i+1]
              if { $indexi != $wanti} {
                set fullDemo 1
              }
          }
      }
  }
  return $fullDemo
}

# writes output of demos: index.html, demosequence.demo files
proc demoActions {outdir PWD demodir includeSteps status depth } {
	global AMIRA_DEMOS
	global AMIRA_ROOT
        global one_file_docu_outdir
        
	set linkTitle ""
	if { $depth==0 } {
		set linkTitle "demo inventory"
	}
	set fullDemo [performFullDemo $includeSteps $status]
	if { $fullDemo == 1} {
		if { [llength $includeSteps] > 0 } {
			puts "Warning: demo $demodir is static. Step selection is disregarded"	
		}
		
		# no step selection passed for this demo. Extract default html file
		exec  xsltproc --stringparam linkTitle $linkTitle --stringparam path $PWD/ --stringparam relativeSrcDir [ relativeSrcDir $outdir $PWD] --stringparam printHtmlHead 1 $AMIRA_ROOT/share/hxdemos-scripts/description.xsl $PWD/description.xml > $outdir/index.html
                
		# append demo description to one file docu
		exec  xsltproc --stringparam linkTitle {} --stringparam path $PWD/ --stringparam relativeSrcDir [ relativeSrcDir $one_file_docu_outdir $PWD] --stringparam printHtmlHead 0 $AMIRA_ROOT/share/hxdemos-scripts/description.xsl $PWD/description.xml >> $one_file_docu_outdir/storyboard.html
			
		# extract demosequence file from description.xml
		exec xsltproc --stringparam path $PWD/ --stringparam dirAMIRA_DEMOSDemo $demodir --stringparam demodir $demodir $AMIRA_ROOT/share/hxdemos-scripts/demosequence.xsl $PWD/description.xml > $outdir/demosequence.demo
		
	} else {
	
		# steps are selected and might occur in different order
		
		# write header for this demo to $outdir/index.html
		exec  xsltproc --stringparam linkTitle $linkTitle --stringparam path $PWD/ --stringparam relativeSrcDir [ relativeSrcDir $outdir $PWD] --stringparam printHtmlHead 1 $AMIRA_ROOT/share/hxdemos-scripts/descriptionHeader.xsl $PWD/description.xml > $outdir/index.html
		
		# append header for this demo to one file docu
		exec  xsltproc --stringparam linkTitle {} --stringparam path $PWD/ --stringparam relativeSrcDir [ relativeSrcDir $one_file_docu_outdir $PWD] --stringparam printHtmlHead 0 $AMIRA_ROOT/share/hxdemos-scripts/descriptionHeader.xsl $PWD/description.xml >> $one_file_docu_outdir/storyboard.html
		
		# write header of demosequence file to $outdir/demosequence.demo
		exec xsltproc --stringparam path $PWD/ --stringparam dirAMIRA_DEMOSDemo $demodir $AMIRA_ROOT/share/hxdemos-scripts/demosequenceHeader.xsl $PWD/description.xml > $outdir/demosequence.demo
		
		
		# append output for each step to $outdir/index.html
		set scriptNr 0
		for {set step 0} { $step < [ llength $includeSteps ] } { incr step } {
			if { [ lindex $includeSteps $step ] > 0 } {
				incr scriptNr
			} 
                        
                        # append step description to index.html
			exec  xsltproc --stringparam step [ lindex $includeSteps $step ] --stringparam script $scriptNr --stringparam path $PWD/ --stringparam relativeSrcDir [ relativeSrcDir $outdir $PWD] --stringparam printHtmlHead 1 $AMIRA_ROOT/share/hxdemos-scripts/descriptionSteps.xsl $PWD/description.xml >> $outdir/index.html
                      
                        # append step description to one file docu
			exec  xsltproc --stringparam step [ lindex $includeSteps $step ] --stringparam script $scriptNr --stringparam path $PWD/ --stringparam relativeSrcDir [ relativeSrcDir $one_file_docu_outdir $PWD] --stringparam printHtmlHead 0 $AMIRA_ROOT/share/hxdemos-scripts/descriptionSteps.xsl $PWD/description.xml >> $one_file_docu_outdir/storyboard.html
			
                        if { [ lindex $includeSteps $step ] > 0 } {

				# append step to $outdir/demosequence.demo
				exec xsltproc --stringparam step [ lindex $includeSteps $step ] --stringparam dirAMIRA_DEMOSDemo $demodir $AMIRA_ROOT/share/hxdemos-scripts/demosequenceSteps.xsl $PWD/description.xml >> $outdir/demosequence.demo
			}			
		}
		
		# append footer to $outdir/index.html
		exec  xsltproc --stringparam printHtmlHead 1 $AMIRA_ROOT/share/hxdemos-scripts/descriptionFooter.xsl $PWD/description.xml >> $outdir/index.html
                
		# append footer to one file docu
		exec  xsltproc --stringparam printHtmlHead 0 $AMIRA_ROOT/share/hxdemos-scripts/descriptionFooter.xsl $PWD/description.xml >> $one_file_docu_outdir/storyboard.html
		
		# append footer to $outdir/demosequence.demo
		exec xsltproc --stringparam dirAMIRA_DEMOSDemo $demodir $AMIRA_ROOT/share/hxdemos-scripts/demosequenceFooter.xsl $PWD/description.xml >> $outdir/demosequence.demo
	}
	
	
	# Now each step gets its own script.
	writeStepScripts $outdir $PWD $demodir $includeSteps $status
}

# prepends directory $startdir to dir if dir is relative path. otherwise, returns dir
proc absoluteIfRelative { dir startdir } {
	if { [ file pathtype $dir ] == "absolute" } {
		set wd $dir
	} else {
		set wd $startdir/$dir
	}
	return $wd
}

# if $indir starts with $AMIRA_DEMOS, the postfix is replaced by {../}^n
proc relativeSrcDir { outdir indir } {
	global AMIRA_DEMOS
	set ret $indir
	
	regsub -nocase $AMIRA_DEMOS $indir "" relSrcDir
	if { $relSrcDir != $indir } {
		if { $relSrcDir == "/src" } {
			set relSrcDir ""
		} else {
			regsub -nocase {^/src/} $relSrcDir "" relSrcDir
			if {$relSrcDir != ""} {
				set relSrcDir $relSrcDir/
			}	
		}	
		regsub -nocase $AMIRA_DEMOS $outdir "" relOutDir
		set countSlashes [llength [split $relOutDir /]]
		set ret [stringPower {../} [expr $countSlashes -1 ]]src/$relSrcDir
	} else {
		set ret "/$ret/"
	}
	return $ret
}

# writes the stepscripts for a demo
proc writeStepScripts {outdir PWD demodir includeSteps status} {
        global AMIRA_DEMOS
	global AMIRA_ROOT
	regsub $AMIRA_DEMOS $outdir \$AMIRA_DEMOS AMIRA_DEMOSoutdir
	
	# get list of step numbers, one step number for each demo
	set XSL [open "|xsltproc \"$AMIRA_ROOT/share/hxdemos-scripts/fetchStepNumbers.xsl\" \"$PWD/description.xml\""]
	gets $XSL stepNumbersStr
	close $XSL
	
	# split the step number string into a list
	set stepNumbers [split $stepNumbersStr " "]
	
	# create a stepscripts folder
	if {[llength $stepNumbers] > 0} {
		if {![file exists  "$outdir/stepscripts"] } {
			file mkdir $outdir/stepscripts
		}
	}
	
	# only 1 demo in each file, take first list entry
	set availableStepNumbers [lindex $stepNumbers 0]
	
	# if no step selection is passed in $includeSteps, fill includeSteps with all steps
	if { [ llength $includeSteps] == 0 || $status == "static"} {
		if { $status == "static" } {
			# if demo is static, empty list
			set includeSteps [ list ]
		}
		for {set j 0} { $j <= $availableStepNumbers } { incr j } {
			lappend includeSteps $j
		}
	}
	
	# write the stepscripts for this demo
	set demoStepNumbers [llength $includeSteps]
	set scriptNr 0
	# always write step0
	exec xsltproc --stringparam whichStep 0 --stringparam outdir $AMIRA_DEMOSoutdir --stringparam demodir $demodir $AMIRA_ROOT/share/hxdemos-scripts/writeStepScripts.xsl $PWD/description.xml > $outdir/stepscripts/step0.hx

	# write other steps
	for {set stepCount 0} {$stepCount < $demoStepNumbers} {incr stepCount} {
		set whichStep [ lindex $includeSteps $stepCount ]
		if {$whichStep >  0} {
			incr scriptNr
		} 
		if { $whichStep <= $availableStepNumbers } {
			exec xsltproc --stringparam whichStep $scriptNr --stringparam outdir $AMIRA_DEMOSoutdir --stringparam demodir $demodir $AMIRA_ROOT/share/hxdemos-scripts/writeStepScripts.xsl $PWD/description.xml > $outdir/stepscripts/step$scriptNr.hx
			exec xsltproc --stringparam whichStep $scriptNr --stringparam outdir $AMIRA_DEMOSoutdir --stringparam demodir $demodir $AMIRA_ROOT/share/hxdemos-scripts/writeJumpScripts.xsl $PWD/description.xml > $outdir/stepscripts/jump$scriptNr.hx
		} else {
			puts "warning: step $whichStep doesnt exist in demo $demodir"
		}
	}
}

# writes the demosequence files for containers
proc writeDemoSequence { outdir cddir {cdirextension ""}} {
	global AMIRA_DEMOS
	
	regsub $AMIRA_DEMOS $outdir \$AMIRA_DEMOS AMIRA_DEMOSoutdir
	
	# append to the demosequence.demo file. Here simply the underlying demosequence.demo files are included via source
	set DEMO [open "$outdir/demosequence.demo" a+]
	puts $DEMO "set saveDir$cdirextension \[pwd\]\ncd $cddir\nsource demosequence.demo\ncd \$saveDir$cdirextension\n"
	close $DEMO
	
	# write the stepping scripts for forward, backward stepping
	if {![file isdirectory "$outdir/stepscripts"]} {
          file mkdir $outdir/stepscripts
	}
	writeToFile "$outdir/stepscripts/startSequence.hx" [subst {# Amira Script
	source $AMIRA_DEMOSoutdir/demosequence.hx
	DemoSequence startDemo 0 0
}]
	writeToFile "$outdir/stepscripts/prevDemo.hx" {# Amira Script
	DemoSequence startDemo -1 0
}
	writeToFile "$outdir/stepscripts/nextDemo.hx" {# Amira Script
	DemoSequence startDemo +1 0
}
	writeToFile "$outdir/stepscripts/prevStep.hx" {# Amira Script
	DemoSequence startDemo +0 -1
}
	writeToFile "$outdir/stepscripts/nextStep.hx" {# Amira Script
	DemoSequence startDemo +0 +1
}	
}

# helper for file output
proc writeToFile {file content {method w} } {
	set WRITE [open $file $method]
	puts $WRITE $content;
	close $WRITE
}

# first level of directory browsing when a selection is taken
# returns list with 2 entries
# 0: 0 in case of success, 1 if outdir exists and --force is not active
# 1: number of processed _demos_
proc selectionDescend { outdir include includeSteps excludeAbs visitedFoldersName {forceOverwriteOutput 1}   {used_attributes [list]} {attribute_expression {}} } {
        upvar $visitedFoldersName visitedFolders
	global AMIRA_DEMOS
	global AMIRA_ROOT
	set startdir [ pwd ]
        set ret [list 0]
	
        set retCreate [createOutDirSafe $outdir $forceOverwriteOutput]

        if {$retCreate} {
          # outdir exists and no action should be taken in this case
          return [list $retCreate]
        }
	
	# perform general action: write demosequence.hx, makeSnapshots.hx
	allActions $outdir 
	
	# print the header of the container/projectlist into $outdir/index.html
	exec xsltproc --stringparam linkTitle "demo inventory" --stringparam action header --stringparam date [exec date] --stringparam wd $startdir/ --stringparam relativeSrcDir [ relativeSrcDir $outdir $startdir ] $AMIRA_ROOT/share/hxdemos-scripts/collectDemo.xsl $AMIRA_DEMOS/src/description.xml > $outdir/index.html
        
        
	
	# remove old demosequence.demo file
	file delete $outdir/demosequence.demo
        
        set num_added_demos 0
	
	# step through list $include
	for {set idir 0 } { $idir < [llength $include ] } { incr idir } {
		set dir [ lindex $include $idir ]
		
		regsub -all "/" $dir "" newdir
		regsub -all ":" $newdir "" newdir
		
		# if passed folder doesnt contain a description.xml, print a warning
		if {[file exists $dir/description.xml]} {
					
			# trigger the recursive directory browsing
			set savedir [ pwd ]				
			cd $dir
			set steps [ lindex $includeSteps $idir ]
			set ret [descend $outdir/$newdir $steps $excludeAbs visitedFolders 0 1 $used_attributes $attribute_expression]
			cd $savedir
                        
                        # find out the number of added demos by last call of descend
                        set num_last_added_demos [lindex $ret 1]
                        incr num_added_demos $num_last_added_demos
                        
                        if {$num_last_added_demos > 0} {
                          # only if a demo has been processed 
                        
                          # append a table row for $dir/description.xml to current index.html
                          set wd [ absoluteIfRelative $dir $startdir ]
                          exec xsltproc --stringparam wd $wd/ --stringparam path $newdir/ --stringparam relativeSrcDir [ relativeSrcDir $outdir "$wd" ] $AMIRA_ROOT/share/hxdemos-scripts/collectDemo.xsl $wd/description.xml >> $outdir/index.html
                          
                          # demosequence output on level 0
                          writeDemoSequence $outdir $newdir                                 
                        } else {
                          # going into folder $dir was a complete utter waste of time
                          # so output folder $outdir/$dir should be deleted
                          deleteFolder $outdir/$newdir
                        }
                        
                        
		} else {
			puts "warning: $dir/description.xml does not exist"
		}
	}
	exec xsltproc --stringparam action footer $AMIRA_ROOT/share/hxdemos-scripts/collectDemo.xsl $AMIRA_DEMOS/src/description.xml >> $outdir/index.html
        
        # only return first entry of $ret
        return [ list [lindex $ret 0] $num_added_demos]
}

# triggers the directory browsing, when no selection is taken
# returns list with 2 entries
# 0: 0 in case of success, 1 if outdir exists and --force is not active
# 1: number of processed _demos_
proc startDescend { outdir startwhere exclude {visitedFoldersName {weirdNameThatDoesntOccur} } {forceOverwriteOutput 1} {used_attributes [list]} {attribute_expression {}} } {
        
        # if outdir exists, check if forceOverwriteOutput is set to 1 and $outdir is a directory
        if { [file exists $outdir] } {
          if {$forceOverwriteOutput == 0 || ![file isdirectory $outdir]} {
            # return with error and 0 demos processed
            return [ list 1 0 ]
          }
        }
        
        # storyboard.html is created at $outdir
        # save this in a global variable
        global one_file_docu_outdir
        set one_file_docu_outdir $outdir
        #create one file codu
        start_one_file_docu $one_file_docu_outdir
    
        if {$visitedFoldersName == "weirdNameThatDoesntOccur"} {
          set visitedFolders [list]
        } else {
          upvar $visitedFoldersName visitedFolders
        }
        
	set savedir [ pwd ]
	set excludeAbs [ list ]
	cd $startwhere
	foreach ex $exclude {
		if { [ file pathtyp $ex ] == "absolute" } {
			lappend excludeAbs $ex
		} else {
			lappend excludeAbs $startwhere/$ex
		}
	}
	set result [descend $outdir [ list ] $excludeAbs visitedFolders 0 1 $used_attributes $attribute_expression]
	cd $savedir
        
        # finish one file docu
        end_one_file_docu $one_file_docu_outdir
        
        # only return first entry of $result
        return $result 
}

# triggers the directory browsing including a selection
# returns list with 2 entries
# 0: 0 in case of success, 1 if outdir exists and --force is not active
# 1: number of processed _demos_
proc startSelectionDescend { outdir startwhere include includesteps exclude {visitedFoldersName {weirdNameThatDoesntOccur}} {forceOverwriteOutput 1} {used_attributes [list]} {attribute_expression {}}} {
          upvar $visitedFoldersName visitedFolders
#        if {$visitedFoldersName == "weirdNameThatDoesntOccur"} {
#          set visitedFolders [list]
#        } else {
#          upvar $visitedFoldersName visitedFolders
#        }
    if [info exists visitedFolder] {
    } else {
        set visitedFolders [ list ]
    }


        # if outdir exists, check if forceOverwriteOutput is set to 1 and $outdir is a directory
        if { [file exists $outdir] } {
          if {$forceOverwriteOutput == 0 || ![file isdirectory $outdir]} {
            # return with error and 0 demos processed
            return [ list 1 0 ]
          }
        }
        
        
        
        # storyboard.html is created at $outdir
        # save this in a global variable
        global one_file_docu_outdir
        set one_file_docu_outdir $outdir
        
        #create one file docu
        start_one_file_docu $one_file_docu_outdir

	global AMIRA_DEMOS
	set savedir [ pwd ]
	set excludeAbs [ list ]
	set includeRel [ list ]
	
	cd $startwhere
	
	# replace paths in $include by relative paths wherever possible
	foreach in $include {
		set in [ stripLastSlash $in ]
		regsub "^$startwhere/" $in "" in
		lappend includeRel $in
	}
	
	foreach ex $exclude {
		if { [ file pathtyp $ex ] == "absolute" } {
			lappend excludeAbs $ex
		} else {
			lappend excludeAbs $startwhere/$ex
		}
	}
	set result [selectionDescend $outdir $includeRel $includesteps $excludeAbs visitedFolders 1 $used_attributes $attribute_expression]
	cd $savedir
        
        # finish one file docu
        end_one_file_docu $one_file_docu_outdir
        
        return $result
}

# create the one file docu with html head
proc start_one_file_docu one_file_docu_outdir {
  file mkdir $one_file_docu_outdir
  writeToFile $one_file_docu_outdir/storyboard.html "<html>
<head><title>Selected demos</title></head>
<body>
<h1>Demo Selection</h1>
<div style=\"page-break-after:always\">
Created [clock format [clock seconds] -format "%D %H:%M:%S"]</div>
<!-- just to ensure that demos start on page 3 -->
<div>
&nbsp;
</div>"
}
# append html footer to one file docu
proc end_one_file_docu one_file_docu_outdir {
  writeToFile $one_file_docu_outdir/storyboard.html {
</body>
</html>} a
}


# replaces "//" by "/" and removes trailing slash
proc stripLastSlash { str } {
	while {[regsub "//" $str "/" str]>0} {}
	regsub "/$" $str "" str
	return $str
}

# creates the output directory if not existent
# if it exists, if
# forceOverwriteOutput == 1: overwrite the input
#                      == 0: don't do anything
proc createOutDirSafe { outdir forceOverwriteOutput} {
  if { [file exists $outdir] } {
    if {$forceOverwriteOutput == 1 && [file isdirectory $outdir]} {
    } else {
      #don't do anything
      return 1
    }
  } else {
    file mkdir $outdir
  }
  return 0;
}

proc deleteFolder {foldername} {
  #puts $foldername
  file delete -force -- $foldername
}
