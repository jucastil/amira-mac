proc fetchDescriptionStyle {{xmlfile}} {
	global AMIRA_DEMOS
	global AMIRA_ROOT
	set ret "error"
	if {[file exists $xmlfile]} {
		set XSL [open "|xsltproc \"$AMIRA_ROOT/share/hxdemos-scripts/fetchDescriptionStyle.xsl\" \"$xmlfile\"" ]
		while {![eof $XSL]} {
			set line [read $XSL]
			regsub "\n|\r| " $line "" line
			if {$line != ""} {
				set ret $line
			}
		}
		close $XSL
	} 
	return $ret
}
proc stringPower { string exp } {
	set result ""
	for { set i 0 } { $i < $exp } { incr i } {
		set result $result$string
	}
	return $result
}

proc isValidPrepackedName {n} {
    return [regexp  {^[a-zA-Z0-9]+_[0-9a-zA-Z.]+-[0-9]+_(base|dev|intern|data)(\.tar|\.tar\.gz|\.tgz)?$} $n];
}

proc parsePrepackedName {fullname} {
    set arch "";
    set config "";
    if { [regexp  {^([a-zA-Z0-9]+)_([0-9a-zA-Z.]+-[0-9]+)_(base|dev|intern|data)(\.tar|\.tar\.gz|\.tgz)?$} $fullname dummy name version class fileext] } {
        regexp {([0-9a-zA-Z.]+)-[0-9]+} $version dummy versionpath
        return [list $name $version $versionpath $fileext $class $arch $config ];
    }
    error "Internal ERROR: trying to parse invalid package name $n";
} 

proc getDataURLsFromFolders { neededURLsName neededFilesName folderList } {
    upvar $neededURLsName neededURLs
    upvar $neededFilesName neededFiles
    foreach folder $folderList {
      getDataURLsFromFile neededURLs neededFiles "$folder/description.xml"
    }
}
proc getDataURLsFromFile { neededURLsName neededFilesName xmlfile } {
    upvar $neededURLsName neededURLs
    upvar $neededFilesName neededFiles
    global AMIRA_DEMOS
    global AMIRA_ROOT
    set PWD [pwd]
    
        set XSL [open "|xsltproc \"$AMIRA_ROOT/share/hxdemos-scripts/collectData.xsl\" \"$xmlfile\""]
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
                
                regsub {^\s*} $file "" file
                regsub {\s*$} $file "" file
                
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
                    
                    lappend neededURLs "$href$pathext"
                    lappend neededFiles $file
                    
                } else {
                    puts "invalid package name $file\n"
                }
            }
        }

        close $XSL

}
proc downloadDataFromURLs { downloadURLs downloadFiles verbose } {
  for {set i 0} {$i < [llength $downloadURLs]} {incr i} {
    downloadDataFromURL [lindex $downloadURLs $i] [lindex $downloadFiles $i] $verbose
  }
}
proc downloadDataFromURL { URL file verbose} {
  global AMIRA_DEMOS
  set tarverbosity ""
  if {$verbose==1} {
    set tarverbosity "v"
  }
                      
  set options x${tarverbosity}f
  
  set fileextension [lindex [ parsePrepackedName $file ] 3]
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
  set wget "wget --timestamping --no-directories $URL$file"
  puts "$wget"
  set filedateprev ""
  set filesizeprev ""
  set fileexistsprev [ file exists $file ]
  if {$fileexistsprev} {
    set filedateprev [ file mtime $file ]
    set filesizeprev [ file size $file ]
  }
  #execute wget, print to stdout and stderr
  if {[catch { exec wget $wget_certificate_option --timestamping --no-directories --progress=bar:force $URL$file 2>@stderr >@stdout } result ] } {
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
}

# returns 0 in case of success
proc packAndGoDataAndOutput { packAndGoFolder whichFiles whichSources whichData htmlOutputFolder overwriteOutputFolder copyAllSources } {
global AMIRA_DEMOS
  if {[file exists $packAndGoFolder]} {
    if {$overwriteOutputFolder} {
      if {![file isdirectory $packAndGoFolder]} {
        return "no directory $packAndGoFolder exists"
      }
      if [ catch {file delete -force $packAndGoFolder} ret] {
        return "$packAndGoFolder can't be deleted";
      }  
    } else {
      return "folder already exists. break. No packing done"
    }
  }
  if {![file exists $packAndGoFolder]} {
    if [ catch {file mkdir $packAndGoFolder} ret] {
      return $ret
    }
  }
  
  # copy [part of] the src folder
  if { $copyAllSources } {
      if { [catch {file copy -force "$AMIRA_DEMOS/src" $packAndGoFolder} ret]} {
        return $ret
      }
  } else {
      if [ catch {file mkdir $packAndGoFolder/src} ret] {
        return $ret
      }
      foreach f $whichSources {
        set srcPath "$packAndGoFolder/src"
        set pathElems [ split $f / ]
        set n [expr [llength $pathElems] - 2 ]
        set pathElems [ lrange $pathElems 0 $n ]
        foreach p $pathElems {
           if { $p == "" } { continue }
           set srcPath "$srcPath/$p"
           if {![file exists $srcPath]} {
               if [ catch {file mkdir $srcPath} ret] { return $ret }
           }
        }
        if { [catch {file copy -force "$AMIRA_DEMOS/src/$f" $packAndGoFolder/src/$f} ret] } {
           return $ret
        }
    }
  }

  # copy the setup folder
  # not necessary anymore: is in amiraBase
  # if { [catch {file copy -force "$AMIRA_DEMOS/setup" $packAndGoFolder} ret]} {
  #  return $ret
  # }

  # copy the output folder
  if { [catch {file rename -force $htmlOutputFolder $packAndGoFolder} ret]} {
    return $ret
  }

  # if --datainclude is given copy the files from the given data folders
  # to $AMIRA_DEMOS/data, otherwise
  # try to take the data from $AMIRA_DEMOS/cacheddata
  set n [ llength $whichData ]
  if { $n > 0 } {
      if [ catch {file mkdir $packAndGoFolder/data} ret] {
        return $ret
      }
      foreach f $whichData {
        set dataPath "$packAndGoFolder/data"
        set pathElems [ split $f / ]
        set n [expr [llength $pathElems] - 2 ]
        set pathElems [ lrange $pathElems 0 $n ]
        foreach p $pathElems {
           if { $p == "" } { continue }
           set dataPath "$dataPath/$p"
           if {![file exists $dataPath]} {
               if [ catch {file mkdir $dataPath} ret] { return $ret }
           }
        }
        if { [catch {file copy -force "$AMIRA_DEMOS/data/$f" $packAndGoFolder/data/$f} ret] } {
           return $ret
        }
    }
  } elseif { [file exists $AMIRA_DEMOS/cacheddata] } {
     foreach f $whichFiles {
       if { [catch {file copy -force  "$AMIRA_DEMOS/cacheddata/$f" $packAndGoFolder} ret] } {
         return $ret
       }
     }
  } else {
     return "No folder $AMIRA_DEMOS/cacheddata found"
  }
  return "packing successful"
}
