if {![info exists AMIRA_DEMOS]} {
	set AMIRA_DEMOS $env(AMIRA_DEMOS)
}
global SETUP
global AMIRA_ROOT
if {[info exists AMIRA_ROOT]} {
        set SETUP $AMIRA_ROOT/share/hxdemos-scripts
} else {
        set SETUP "[file join [pwd] [file dir [info script]]]";
        set AMIRA_ROOT $SETUP/../..
} 
if {$AMIRA_DEMOS == ""} {
	echo "you must point AMIRA_DEMOS to the hxdemos directory\n";
	exit;
}
source $SETUP/setuphelpers.tcl

proc descend { verbose } {
    set PWD [pwd]

    #first decide, if we have a container or a demo by checking the style-attribute in the <description> tag of description.xml
    set dsList [fetchDescriptionStyle $PWD/description.xml]
    set whatHaveWe [lindex [split $dsList "/"] 0]
    
    if {$whatHaveWe == "error"} {
        puts "No description.xml file found in the current directory $PWD\n"
    } else {

        downloadDataFromFile $verbose
        
        if {$whatHaveWe == "container" || $whatHaveWe == "project" || $whatHaveWe == "projectlist"} {
            set files [lsort [glob *]]
            foreach dir $files {
                if {[file isdirectory $dir] && $dir != "." && $dir !=".."} {
                    if {[file exists $dir/description.xml]} {
                        cd $dir
                        descend $verbose
                        cd ..
                    }
                }
            }
        }
    }
}
proc downloadDataFromFile { verbose } {
    global AMIRA_DEMOS
    global SETUP
    set PWD [pwd]
    
        set XSL [open "|xsltproc \"$SETUP/collectData.xsl\" \"$PWD/description.xml\""]
        set i 0
        while {![eof $XSL]} {
            incr i
            
            # any first line the stylesheets returns is a base url
            gets $XSL href 
            # delete heading and trailing whitespace
            regsub {^\s*} $href "" href
            regsub {\s*$} $href "" href
            
            if {$href != ""} {
                if {[eof $XSL]} {
                    puts "no href|file pair\n";
                    exit;
                }
                incr i			
                gets $XSL file
                
                regsub {^\s*} $href "" href
                regsub {\s*$} $href "" href
                
                # add trailing "/" if not there already
                if {[string index $href [expr [string length $href]-1]] != "/"} {
                    set href $href/
                }
                set pathext ""
                
                # A path extension must be extracted from filename. The filename must match regular expression
                # as in isValidPrepackedName
                
                if {[ isValidPrepackedName $file ]} {
                    set prepackedFileParts [ parsePrepackedName $file ]
                    set name [lindex $prepackedFileParts 0]
                    set version [lindex $prepackedFileParts 1]
                    set versionpath [lindex $prepackedFileParts 2]
                    set fileextension [lindex $prepackedFileParts 3]
                    set class [lindex $prepackedFileParts 4]
                    set arch [lindex $prepackedFileParts 5]
                    set config [lindex $prepackedFileParts 6]

                    set pathext $name/$versionpath/
                    
                    set tarverbosity ""
                    if {$verbose==1} {
						set tarverbosity "v"
					}
					
                    set options x${tarverbosity}f
                    if { ($fileextension == ".tar.gz") || ($fileextension == ".tgz") } {
                        set options "xz${tarverbosity}f"
                    }

                    # save the current working directory
                    set savePwd [pwd]
                    
                    # move to the $AMIRA_DEMOS directory
                    cd $AMIRA_DEMOS
					
					#downloads go to cacheddata
					file mkdir cacheddata
					cd cacheddata
					
                    # newer versions of wget musst be called with option --no-check-certificate
                    # because amira.zib.de has wrong certificate
                    
                    if { [catch {regexp {^GNU Wget 1\.([0-9]+)} [exec wget --version] match minor} ] } {
                        error "Cannot execute 'wget --version' ! Maybe, wget is not installed ?";
                    } elseif { $minor < 10 } {
                        set wget_certificate_option {}
                    } elseif { $minor >= 10 } {
                        set wget_certificate_option {--no-check-certificate}
                    } else {
                        error "Cannot recognize version string of wget !"
                    }
                    # download file
                    set wget "wget $wget_certificate_option --timestamping --no-directories $href$pathext$file"
                    puts "$wget"
                    set filedateprev ""
                    set filesizeprev ""
                    set fileexistsprev [ file exists $file ]
                    if {$fileexistsprev} {
						set filedateprev [ file mtime $file ]
						set filesizeprev [ file size $file ]
					}
                    #execute wget, print to stdout 
                    if {[catch { exec wget $wget_certificate_option --timestamping --no-directories --progress=bar:force $href$pathext$file 2>@stderr >@stdout } result ] } {
						puts stderr $result
					
					} else {
												
						set filedatenow ""
						set filesizenow ""
						set fileexistsnow [ file exists $file ]
						if {$fileexistsnow} {
							set filedatenow [ file mtime $file ]
							set filesizenow [ file size $file ]
						}
						
						# download goes to $AMIRA_DEMOS/cacheddata, go back to $AMIRA_DEMOS
						cd $AMIRA_DEMOS
						
						# if the file has been newly downloaded or filesize or date has changed, untar/unzip
						
						if { !$fileexistsprev && $fileexistsnow || 
								( $fileexistsnow && ($filedatenow!=$filedateprev || $filesizenow!=$filesizeprev ))} {
							
							if { [ info exist tarCommand ] } {
								unset tarCommand
							}
						    
							if { [ catch { exec which gtar } result ] } {
								if { ! [ catch { exec which tar } result ] } {
									set tarCommand "tar"
								} 
							} else {
								set tarCommand [ exec which gtar ] 
								if { [ info exist tarCommand ] && [ file executable $tarCommand ] } {
									set tarCommand "gtar"
								} elseif { ! [ catch { exec which tar } result ] } {
									set tarCommand [ exec which tar ]
									if { [ info exist tarCommand ] && [ file executable $tarCommand ] } {
										set tarCommand "tar"
									} 
								} 
							}
					        
							if { [ info exist tarCommand ] } {
								if { $tarCommand == "gtar" } {
									puts "gtar -$options \$AMIRA_DEMOS/cacheddata/$file"
									exec gtar -$options cacheddata/$file >@stdout 2>@stderr
								} else {
									# check if we have to uncompress first
									if { [string first "z" $options ] >= 0 } {
										puts "gzip -cd \$AMIRA_DEMOS/cacheddata/$file | tar -x${tarverbosity}f -"
										exec gzip -cd cacheddata/$file | tar -x${tarverbosity}f - >@stdout 2>@stderr
									} else {
										puts "tar -$options \$AMIRA_DEMOS/cacheddata/$file"
										exec tar -$options cacheddata/$file >@stdout 2>@stderr
									}
								}
							} else {
								puts stderr "$result"
							}
						}
						
                    }
                    # afterwards, jump back to the previous place in the filesystem
                    cd $savePwd
                } else {
                    puts "invalid package name $file\n"
                }
            }
        }

        close $XSL

}
set verbose 1
for {set i 0 } { $i < $argc } { incr i } {
	set arg [ lindex $argv $i ]
	if { $arg == "-v" || $arg == "--verbose" } {
		set verbose 1
	} elseif { $arg == "-nv" || $arg == "--non-verbose" } {
		set verbose 0
	} elseif { $arg == "-h" || $arg == "--help" } {
		puts {syntax: downloadData [ --verbose | -- non-verbose ]}
		puts {--verbose,     -v : print all output: wget, tar, additional output}
		puts {--non-verbose, -nv: print no output from tar (tar -x[z]f), but the rest as above}
		exit
	}
}
descend $verbose
