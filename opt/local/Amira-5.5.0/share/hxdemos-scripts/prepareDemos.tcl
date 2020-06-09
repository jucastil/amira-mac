set include [ list ]
set includesteps [ list ]
set datainclude [ list ]
set exclude [ list ]
set forceOverwriteOutput 0
set download 0
set verbose 0
set packAndGo 0
set packAndGoFolder ""
set copyAllSources 0

if {![info exists AMIRA_DEMOS]} {
	set AMIRA_DEMOS $env(AMIRA_DEMOS)
}
if {$AMIRA_DEMOS == ""} {
	puts "you musst point AMIRA_DEMOS to the hxdemos directory\n"
	exit
}
if {![info exists AMIRA_ROOT]} {
        set AMIRA_ROOT "[file join [pwd] [file dir [info script]]]/../..";
} 
source $AMIRA_ROOT/share/hxdemos-scripts/hxDemosFunctions.tcl

# remove double and trailing '/'es from AMIRA_DEMOS
set AMIRA_DEMOS [ stripLastSlash $AMIRA_DEMOS ]

proc showHelpAttributesText {} {
  
  puts {If an attributes expression --attributes expression is provided, each 
  considered demo is only added to the output, if its attributes match 
  the expression.
  
  The expression is a logical expression following tcl syntax, with operators
  && (logical and), || (logical or) and ! (negation).
  
  The attributes can be matched against attribute values by expressions
  attribute-name == attribute-value
  attribute-name != attribute-value
  
  The list of valid attributes and their values are set in setup/attributes.xml
  This list should only be added by members of SigDemo
  
  The following attributes and values are allowed:}
  puts [get_all_attributes_and_values]
  puts {
  Example:
  
  prepareDemos.tcl --attributes "topic==flow && version==zib-2006-2"
  will process all flow-demos that have been successfully tested 
  against zib-2006-2.
  Note that the quotes are necessary.
  
  
  }
}
proc showHelpText {{dummy {} }} {
	puts {syntax: prepareDemos.tcl [--help | {[--include] {folder [--steps steplist]}* |
         --exclude folderlist }* | [--attributes expression | --help-attributes]
        [--datainclude <folderlist>*] |
        [--output outputfolder] | [--force | --download | --packandgo folder]
        
        --include,   -i: given folders are included recursively to the output
        --steps,     -s: string of type "5 8 2 1" defining selection 
                         and order of steps, steps starting from 1
        --exclude,   -e: following folders are omitted in the recursion
        --output,    -o: specifies the outputfolder relative to $AMIRA_DEMOS
        --attributes,-a: adds only demos which attributes match "expression".
                          "expression" consists of a combination of ||, && and
                          attribute-value-pairs, see --help-attributes for
                          more information
        --help-attributes: shows how to use attributes
        --force,     -f: overwrites content in outputfolder; if not given and 
                         folder exists, prepareDemos issues a warning and exits
                         
        --download,  -d: downloads data needed by the selected demos
        --packandgo, -p: copies output and needed data to the specified folder
        --allpackandgo : copies output, all from src and needed data
                         to the specified folder
        --datainclude  : given folders are included recursively to the data
                         folder, if --packandgo has been specified, too
        --help,      -h: prints this helpscreen and exits}
} 

proc checkParamsAndOpts { {dummy {}} } {
global include
global includesteps
global datainclude
global exclude
global forceOverwriteOutput
global download
global verbose
global packAndGo
global packAndGoFolder
global argv
global argc
global copyAllSources
global attributes_expression_commandline
set attributes_expression_commandline {}

	set output output
	set isInclude 1
        set isDataInclude 0
	for {set i 0 } { $i < $argc } { incr i } {
		set arg [ lindex $argv $i ]
		if { $arg == "-h" || $arg == "--help" } {
			showHelpText
			exit
		} elseif {$arg == "--help-attributes" } {
                        showHelpAttributesText
                        exit
                }
		if { $arg == "-o" || $arg == "--output" } {
			incr i
			set output [ lindex $argv $i ] 
                        if { $output == "src" || $output == "data" ||
                             $output == "cacheddata" || $output == "" } {
			     puts "folder name $output not allowed"
                             puts "using output instead"
                             set output output"
                        }
		} elseif { $arg == "-s" || $arg == "--steps" } {
			set includelength [ llength $include ]
			set includestepslength [ llength $includesteps ]
			for { set j $includestepslength } { $j < $includelength - 1 } {incr j } {
				lappend includesteps [list]
			}
			incr i
			set steplist [ lindex $argv $i ] 
			lappend includesteps [ split $steplist " " ]
		} elseif { $arg == "-a" || $arg == "--attributes" } {
			incr i
			set attributes_expression_commandline [ lindex $argv $i ]
		} elseif { $arg == "-e" || $arg == "--exclude" } {
			set isInclude 0
		} elseif {$arg == "-i" || $arg == "--include" } {
			set isInclude 1
		} elseif {$arg == "--datainclude" } {
			set isDataInclude 1
                        #set isInclude 0
		} elseif {$arg == "-f" || $arg == "--force" } {
			set forceOverwriteOutput 1
		} elseif {$arg == "-d" || $arg == "--download" } {
			set download 1
		} elseif { $arg == "-v" || $arg == "--verbose" } {
                  set verbose 1
                } elseif { $arg == "-nv" || $arg == "--non-verbose" } {
                        set verbose 0
                } elseif {$arg == "-p" || $arg == "--packandgo" ||
                          $arg == "--allpackandgo" } {
			set packAndGo 1
                        if {$arg == "--allpackandgo" } { set copyAllSources 1 }
			incr i
			set packAndGoFolder [ lindex $argv $i ] 
                        if { $packAndGoFolder == "src" ||
			     $packAndGoFolder == "data" ||
                             $packAndGoFolder == "cacheddata" ||
                             $packAndGoFolder == "" } {
			         puts "folder name $packAndGoFolder not allowed"
                                 puts "using packandgo instead"
                                 set packAndGoFolder packandgo
                        }
		} else {
			if { [ string range $arg 0 0 ] == "-" } {
				puts "unknown switch $arg"
				exit
			}
			if { $isDataInclude != 0 } {
				lappend datainclude [ stripLastSlash $arg ]
			} elseif { $isInclude != 0 } {
				lappend include [ stripLastSlash $arg ]
			} else {
				lappend exclude [ stripLastSlash $arg ]
			}
		}
	}
	puts -nonewline "processing "
	if { [ llength $include ] > 0 } {
		puts $include
		puts "with steps $includesteps"
	} else {
		puts "all demos..."
	}
	if { [ llength $exclude ] > 0 } {
		puts "omitting $exclude"
		
	}
	return $output
}

# load the available attributes from setup/attributes.xml
read_available_attributes



set output [ checkParamsAndOpts ]

# prepare attributes expression

set used_attributes [list]
set attribute_expression ""
if {$attributes_expression_commandline ne {}} {

  set used_attr_attr_expr [attribute_expression $attributes_expression_commandline]
  
  set used_attributes [lindex $used_attr_attr_expr 0]
  set attribute_expression [lindex $used_attr_attr_expr 1]
}



set result [list]
set visitedFolders [list]
if { [ llength $include ] == 0 } {
	set result [startDescend $AMIRA_DEMOS/$output [ pwd ] $exclude visitedFolders $forceOverwriteOutput $used_attributes $attribute_expression]
        set copyAllSources 1
} else {
	set result [startSelectionDescend $AMIRA_DEMOS/$output [ pwd ] $include $includesteps $exclude visitedFolders $forceOverwriteOutput $used_attributes $attribute_expression]
        #set result [startSelectionDescend $AMIRA_DEMOS/$output [ pwd ] $include $includesteps $exclude ]
}

set success [lindex $result 0]
set num_added_demos [lindex $result 1]
if {$success == 1} {
  puts "critical: output folder $AMIRA_DEMOS/$output exists. No action taken.\n          Force overwrite by --force"
} elseif {$result == 2} {
  puts "critical: output folder $AMIRA_DEMOS/$output can not be deleted. No action taken.\nPropably some files in there are locked by other applications."
} else {
  # success: we might want to download data or packandgo
  
  set neededURLs [list]
  set neededFiles [list]
  
  if { $download || $packAndGo } {
    puts "I will download the prepacked data from the description.xml files in folders:";
    puts [ join $visitedFolders "\n"]
    
    getDataURLsFromFolders neededURLs neededFiles $visitedFolders
    puts $neededURLs
    puts $neededFiles
  }
  
  if {$download} {
    downloadDataFromURLs $neededURLs $neededFiles $verbose
  }
  
  if {$packAndGo} {
    puts "packing... this might take some time"
    puts [packAndGoDataAndOutput $packAndGoFolder $neededFiles $include $datainclude $AMIRA_DEMOS/$output $forceOverwriteOutput $copyAllSources]
    puts "\nAdded $num_added_demos demos to output in $packAndGoFolder/$output"
  } else {
    puts "\nAdded $num_added_demos demos to output in $AMIRA_DEMOS/$output"
  }
}

