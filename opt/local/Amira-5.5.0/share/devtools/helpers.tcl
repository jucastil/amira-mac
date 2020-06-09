####
#### Configuration
####
####
#### Two flavors of configvars exist:
#### configvars might be used as VAR VAR-arch and VAR-arch-Config
####      arch includes all aliases
#### simpleconfigvars only as VAR
####
####
set HELPERSDIR "[file join [pwd] [file dir [info script]]]";

set configvars [list SRC MOCSRC QRCSRC UICSRC ROCSRC INCSRC INCSRCINTERN];

set simpleconfigvars [list \
    SHARE SHAREDEV SHAREINTERN SHARESECURE DATA BISONSRC FLEXSRC DOX DOXINTERN NODOX GSOAPSRC CUDASRC \
    TESTSRC TESTINCSRC TESTSHARE \
]

# archs are built of [a-zA-Z0-9] and nothing else
set archs [list Linux Linux64 SunOS SunOS64 MacX LinuxAMD64 Win32VC8 Win32VC9 Win64VC9]

set configs [list Debug Optimize]

set compilers(Linux) [list gcc34 gcc41 gcc43]
set compilers(LinuxAMD64) [list gcc34 gcc41 gcc43 gcc44 gcc45]
set compilers(Linux64) [list gcc41]
set compilers(MacX) [list gcc42]

set arch-Aliases {
    Unix {Linux Linux64 SunOS SunOS64 MacX LinuxAMD64}
    X11 {Linux Linux64 SunOS SunOS64 LinuxAMD64}
    Win {Win32VC8 Win32VC9 Win64VC9}
}

set isas [list ppc i386]

set prepackedcompiler ""

# store download setting for reuse by subsequent
# downloads
set dl_cmd {}
set dl_opt {}
set dl_opt_time {}

#
# initialize default compilers
#
set arch2compiler(Linux) gcc41
set arch2compiler(LinuxAMD64) gcc41
set arch2compiler(Linux64) gcc41
set arch2compiler(MacX) gcc42

proc checkGCCVersion {executable major minor warn} {
    if { [catch {set gccversion [exec $executable -dumpversion]} ] } {
        return 0
    }
    set detectedmajor [lindex [split $gccversion .] 0]
    set detectedminor [lindex [split $gccversion .] 1]
    if { $detectedmajor == $major && $detectedminor == $minor } {
        return 1
    }
    if { $warn } {
        message "Warning: $executable reports a version different from $major.$minor."
    }
    return 0
}

proc findGCC {arch} {
    global arch2compiler
    global gccpostfix

    set gccpostfix ""
    regexp {gcc(\d)(\d)} $arch2compiler($arch) dummy major minor

    if {    [checkGCCVersion gcc-${major}.${minor} $major $minor 1]
         && [checkGCCVersion g++-${major}.${minor} $major $minor 1] } {
        message "Note: Using gcc-$major.$minor and g++-$major.$minor."
        set gccpostfix -$major.$minor
        return
    }
    if {    ![checkGCCVersion gcc $major $minor 0]
         || ![checkGCCVersion g++ $major $minor 0] } {
        message "Warning: Selected compiler ($arch2compiler($arch)) does not match gcc in PATH."
    }
}

set verbose 0;

proc setVerbosity {v} {
    global verbose

    set verbose $v
}

#~ Whether to use the function dos2cygwinpath or not.
set doReplaceDOSPaths 1;

###
### By default, the amira's copyright is used.
###
proc readCopyrightFile {copyrightFile} {
  global standardcopyright;
  global HELPERSDIR;
  set copyrightFile [file join $HELPERSDIR $copyrightFile]
  if ![ file exists $copyrightFile ] {
    puts "$copyrightFile doesn't exist! Copyright file set to 'amiraCopyright.txt'"
    set copyrightFile [file join $HELPERSDIR "amiraCopyright.txt"]
  }
  set fp [open $copyrightFile]
  set standardcopyright [read $fp];
  close $fp;
}

####
#### End of configuration
####

#### Use this function for output
#### print either to stdout or to the amira console
####
#### If some keywords indicate verbosity
####    'error'    -2
####    'warning'  -1
####    'note'     0
####
proc message {x} {
    set level 1
    if { [regexp -nocase {^note} $x] } {
        set level 0
    }
    if { [regexp -nocase {^warning} $x] } {
        set level -1
    }
    if { [regexp -nocase {^error} $x] } {
        set level -2
    }

    msgout $level $x
}


#### Use this function for output
#### if you want to control the verbosity yourself
#### print either to stdout or to the amira console
####
proc msgout {level x} {
    global verbose;

    if {$level < $verbose} {
        if {[info commands echo] == "echo"} {
            echo $x;
        } else {
            puts $x;
        }
    }
}


####
#### Build array of aliases
####

# validate architecture names
foreach a $archs {
    if { [regexp {^[a-zA-Z0-9]+$} $a] } {
# ok
    } else {
        error "invalid arch";
    }
}

foreach a $archs {
    set aliasedTo($a) [list];
}

array set expandAlias ${arch-Aliases};
set aliases "";
foreach {a l} ${arch-Aliases} {
    foreach x $l {
        lappend aliasedTo($x) $a;
    }
    lappend aliases $a;
}

proc isAlias {a} {
    global aliases
    if { [lsearch $aliases $a] >= 0 } {
        return 1
    }
    return 0
}

proc expandAliases {l} {
    global expandAlias;

    set ret [list];
	foreach x $l {
		if {[info exists expandAlias($x)]} {
			set ret [concat $ret $expandAlias($x)];
		} else {
            lappend ret $x;
        }
	}
    return $ret;
}
####
#### build list of all vars used
#### vars not statet here will trigger a warning
####
foreach e {
    BASE_DEFINES
    BASE_DEFINES-Win32VC8 BASE_DEFINES-Win32VC8-Debug BASE_DEFINES-Win32VC8-Optimize
    BASE_DEFINES-Win32VC9 BASE_DEFINES-Win32VC9-Debug BASE_DEFINES-Win32VC9-Optimize
    BASE_DEFINES-Win64VC9 BASE_DEFINES-Win64VC9-Debug BASE_DEFINES-Win64VC9-Optimize {-aliased Unix BASE_DEFINES}
    BASE_INCLUDES
    BASE_INCLUDES-Win32VC8 BASE_INCLUDES-Win32VC9 BASE_INCLUDES-Win64VC9
    INCLUDES
    INCLUDES-Win32VC8 INCLUDES-Win32VC9 INCLUDES-Win64VC9 {-aliased Unix BASE_INCLUDES}
    BASE_LIBPATH
    BASE_LIBPATH-Win32VC8 BASE_LIBPATH-Win32VC8-Debug
    BASE_LIBPATH-Win32VC9 BASE_LIBPATH-Win32VC9-Debug
    BASE_LIBPATH-Win64VC9 BASE_LIBPATH-Win64VC9-Debug
    LIBPATH
    LIBPATH-Win32VC8
    LIBPATH-Win32VC9 LIBPATH-Win64VC9
    BISON-Win32VC8
    BISON-Win32VC9
    BISON-Win64VC9
    BISONSRC
    CONSOLE
    COPY {-aliased Win COPY} {-aliased Unix COPY}
    COPYDEV {-aliased Win COPYDEV} {-aliased Unix COPYDEV}
    COPYINTERN {-aliased Win COPYINTERN} {-aliased Unix COPYINTERN}
    COPYRIGHT
    CUDASRC
    DATA
    DEFINES DEFINES-Win DEFINES-Win32VC8 DEFINES-Win32VC9 DEFINES-Win64VC9 {-aliased Unix DEFINES} DEFINES-X11
    DISTCOPY {-aliased Unix DISTCOPY} {-aliased Win DISTCOPY}
    DISTCOPYDEV {-aliased Unix DISTCOPYDEV} {-aliased Win DISTCOPYDEV}
    DISTCOPYINTERN {-aliased Unix DISTCOPYINTERN} {-aliased Win DISTCOPYINTERN}
    DISTEXTRA {-aliased Unix DISTEXTRA} {-aliased Win DISTEXTRA}
    DISTEXTRADEV {-aliased Unix DISTEXTRADEV} {-aliased Win DISTEXTRADEV}
    DISTEXTRAINTERN {-aliased Unix DISTEXTRADEV} {-aliased Win DISTEXTRADEV}
    DOC2HTML-Win32VC8
    DOC2HTML-Win32VC9
    DOC2HTML-Win64VC9
    DOCTYPE
    DOX
    DOXINTERN
    EXCLUDEISA-MacX
    EXECWRAPPER
    FLEX-Win32VC8
    FLEX-Win32VC9
    FLEX-Win64VC9
    FLEXSRC
    GSOAPSRC
    INCLUDES
    INCLUDES-Win32VC8
    INCLUDES-Win32VC9 INCLUDES-Win64VC9 {-aliased Unix INCLUDES}
    GTAR-Win32VC8
    GZIP-Win32VC8
    GTAR-Win32VC9
    GTAR-Win64VC9
    GZIP-Win32VC9
    GZIP-Win64VC9
    ICON
    INCSRC
    INCSRCINTERN
    LABELS
    LIBS {-aliased Win LIBS} {-aliased Unix LIBS} LIBS-X11
    LIBSALIAS {-aliased Win LIBSALIAS} {-aliasedcompiler Unix LIBSALIAS}
    LINKTYPE
    LINKOPTIONS
    MOCSRC
    NODOX
    ONLY EXCLUDEARCH
    PACKAGE
    PREPACKED
    PROVIDES
    QRCSRC
    QT_MOC-Win32VC8
    QT_RCC-Win32VC8
    QT_UIC-Win32VC8
    QT_MOC-Win32VC9
    QT_MOC-Win64VC9
    QT_RCC-Win32VC9
    QT_RCC-Win64VC9
    QT_UIC-Win32VC9
    QT_UIC-Win64VC9
    ROCSRC
    SHARE
    SHAREDEV
    SHAREDEVDIST
    SHAREINTERN
    SHARESECURE
    SRC SRC-Win SRC-Win32VC8 SRC-Win32VC9 SRC-Win64VC9 {-aliased Unix SRC}
    SYMLINK {-aliased Unix SYMLINK}
    TAGLIB-Win32VC8
    TAGLIB-Win32VC9
    TAGLIB-Win64VC9
    TARGET
    TYPE
    UICSRC
    WINDOWS_EXPORT_DEFINITION-Win32VC8
    WINDOWS_EXPORT_DEFINITION-Win32VC9
    WINDOWS_EXPORT_DEFINITION-Win64VC9
    {-aliased Unix BASE_MAKE}
    TESTLIBS
    TESTSRC
    TESTINCSRC
    TESTSHARE
} {
    if {[lindex $e 0] == "-aliased"} {
        set a [lindex $e 1];
        set v [lindex $e 2];
        set valid_variables($v-$a) 1
        foreach c $configs {
            set valid_variables($v-$a-$c) 1
        }
        foreach b [concat $expandAlias($a)] {
          set valid_variables($v-$b) 1
          foreach c $configs {
            set valid_variables($v-$b-$c) 1
          }
        }
    } elseif {[lindex $e 0] == "-aliasedcompiler"} {
        set a [lindex $e 1];
        set v [lindex $e 2];
        set valid_variables($v-$a) 1
        foreach c $configs {
            set valid_variables($v-$a-$c) 1
        }
        foreach b [concat $expandAlias($a)] {
          set valid_variables($v-$b) 1
          foreach c $configs {
            set valid_variables($v-$b-$c) 1
            if { [info exists compilers($b)] } {
                foreach compiler $compilers($b) {
                    set valid_variables($v-$b-$compiler-$c) 1
                }
            }
          }
        }
    } else {
        set valid_variables($e) 1
    }
}

proc isValidVariable {v} {
    global valid_variables
    return [info exists valid_variables($v)]
}

#############################################################
####### helpers
#############################################################
####
#### print message only if importance is lower than verbosity
####
proc debugmessage {imp x} {
    global verbose;

    if {[info exists verbose] && $imp < $verbose} {
        message "DEBUG: $x";
    }
}

####
#### print to the actual stream
####
proc output {x} {
    global outfp;

    puts -nonewline $outfp $x;
}

set uuidSeedValue 0
set uuidMachineInfo $::tcl_platform(user)[info hostname]$::tcl_platform(machine)$::tcl_platform(os)
proc getUUID {} {
    global uuidSeedValue
    global uuidMachineInfo

    incr uuidSeedValue;

    # Uncomment to get deterministic GUIDs for debugging.
    #return [format "11111111-1111-1111-1111-%012d" $uuidSeedValue];

    # See http://wiki.tcl.tk/10871

    # String together the Seed and Machine Info along with a random number for a end base.
    set MachInfo [expr {rand()}]$uuidSeedValue$uuidMachineInfo
    binary scan $MachInfo h* MachInfo_Hex
    set CmdCntAndSeq [string range "[info cmdcount]$uuidSeedValue$uuidSeedValue" 0 8]
    binary scan [expr {rand()}] h* Rand_Hex

    # Set the first part as the datetime in seconds.
    set guid [format %2.2x [clock seconds]]

    # Pick though clock clicks for a good "Random" sequence.
    append guid -[string range [format %2.2x [clock clicks]] 0 3] \
                -[string range [format %2.2x $CmdCntAndSeq] 0 3] \
                -[string range $Rand_Hex 3 6] \
                -[string range $MachInfo_Hex 0 11]

    return [string toupper $guid]
}


####
#### BUILDROOT
####
proc findBuildroot {rundir} {
    global buildroot;

    if { ![info exists buildroot] } {
        findDefaultBuildRoot $rundir
    }
    if { ![validRundir $rundir] } {
        message "Error: invalid rundir '$rundir', which is not a sub-directory of buildroot '$buildroot'."
        error "invalid rundir"
    }
    return $buildroot
}

proc validRundir {rundir} {
    global buildroot
    if { [catch { set normalbr [file normalize $buildroot] } ] } {
        # We use tcl versions that do not support "file normalize".
        # If this is the case we just return 1, hoping that
        # rundir is valid.
        return 1
    }
    set normalrd [file normalize $rundir]
    if { [string equal -length [string length $normalbr] $normalbr $normalrd ] } {
        return 1
    }
    return 0
}

proc findDefaultBuildRoot {rundir} {
    global buildroot
    global HELPERSDIR

    set pwd [pwd];
    cd $rundir;
    set foundbuildroot 0;

    set x [file join $HELPERSDIR .. .. ..]
    if {    [file isdirectory [file join $x src]]
         && [file isdirectory [file join $x src amira]]
         && [file isdirectory [file join $x src amira devtools]]
        } {
            cd $x;
            set rootpwd [pwd];
            set foundbuildroot 1;
    }

    cd $pwd;
    if {!$foundbuildroot} {
        message "Error: failed to automatically located BUILDROOT. Note: BUILDROOT must contain a directory 'src/amira/devtools' to be accepted.";
        error "Fatal";
    }
    set buildroot $rootpwd;
}

proc setBuildRoot {dir} {
    global buildroot

    if { ![file isdirectory $dir] } {
        message "Error: '$dir' does not exist. Cannot set buildroot."
        error "missing buildroot"
    }
    set buildroot $dir
}

#### return previously found buildroot
proc getBuildRoot {} {
    global buildroot;

    if {[info exists buildroot]} {
        return $buildroot;
    }
    message "ERROR: findBuildroot was not called, no buildroot set";
    error "missing buildroot";
}


proc getAllPackageDirs {} {
    global allPackages;

    set result [list]

    foreach x $allPackages {
        set dir [lindex $x 1];

        if { $dir != "." } {
            lappend result $dir
        }
    }

    return $result
}
####
#### check if arch is a known arch
####
proc isValidArch {a} {
    global archs
    return [expr [lsearch $archs $a] >= 0];
}

proc isValidConfig {c} {
    global configs

    return [expr [lsearch $configs $c] >= 0]
}

proc isValidISA {i} {
    global isas
    return [expr [lsearch $isas $i] >= 0];
}

####
#### check if this arch was requested to be processed by the user
#### the default is to accept all archs
proc isRequestedArch {a} {
    global archsonly;

    if {[info exists archsonly]} {
        if {[lsearch $archsonly $a] >= 0} {
            return 1;
        }
        return 0;
    }

    return 1;
}

####
#### return all requested archs
####
proc getRequestedArchs {} {
    global archsonly;
    global archs;

    if {[info exists archsonly]} {
        return $archsonly;
    }
    return $archs;
}

proc guessArch {} {
    global archsonly

    set m [exec uname -m]
    set s [exec uname -s]

    switch -glob $s {
        Darwin {
            set archsonly MacX
        }
        Linux {
            switch -glob $m {
                i*86 {
                    set archsonly Linux
                }
                x86_64 {
                    set archsonly LinuxAMD64
                }
                ia64 {
                    set archsonly Linux64
                }
            }
        }
        CYGWIN* {
            set archsonly Win64VC9
            message "Warning: If you want Win32VC8, you need to use --archs Win32VC8."
        }
    }
    if { [info exists archsonly] } {
        message "Note: detected --archs $archsonly"
    }
}
####
#### Check if package is ignored on all requested archs.
####
proc isIgnoredPackage {} {
    if { ![info exists ::Config::ONLY] } {
        return 0
    }
    if { ${::Config::ONLY} == "" } {
        return 0
    }
    foreach a [getRequestedArchs] {
        if { [lsearch ${::Config::ONLY} $a] != -1 } {
            return 0
        }
    }
    return 1
}

####
#### check if c is a known compiler
####
proc isValidCompiler {arch c} {
    global compilers
    if { ![info exists compilers($arch)] } {
        return 0
    }
    return [expr [lsearch $compilers($arch) $c] >= 0]
}

####
#### check if cc is the requested compiler for arch
####
proc isRequestedCompiler {arch cc} {
    global arch2compiler

    if { [info exists arch2compiler($arch)] && $arch2compiler($arch) == $cc } {
        return 1
    }
    return 0
}

proc isRequestedPrepackedCompiler {arch cc} {
    global prepackedcompiler
    
    if { $prepackedcompiler == "" } {
        return [isRequestedCompiler $arch $cc]
    }
        
    if { $prepackedcompiler == $cc } {
        return 1
    }
    return 0
}

proc getCompiler {arch} {
    global arch2compiler

    if { [info exists arch2compiler($arch)] } {
        return $arch2compiler($arch)
    }
    return ""
}

####
#### check if s is a know skin
####
proc setDocSkin {s} {
    global docskin
    if { $s == "AmiraSkin" } {
        set docskin [list amira AmiraSkin]
    } elseif { $s == "ZIBAmiraSkin" } {
        set docskin [list zibamira ZIBAmiraSkin]
    } elseif { $s == "AmiraSkinEmpty" } {
        set docskin [list empty AmiraSkinEmpty]
    } elseif { $s == "AvizoSkin" } {
        set docskin [list avizo AvizoSkin]
    } else {
        message "Error: invalid documentation skin $s"
        error "invalid docskin $s"
    }
}

proc getDocSkins {} {
    global docskin
    if {[info exists docskin]} {
        return $docskin
    }
    return [list amira AmiraSkin avizo AvizoSkin zibamira ZIBAmiraSkin]
}

#
# Customization hooks for directories.
#
set gIntermediateDir "intermediate"

proc setIntermediateDir { d } {
    global gIntermediateDir

    if { [regexp {^[a-zA-Z0-9-]+$} $d] } {
        set gIntermediateDir $d
    } else {
        message "Error: invalid intermediate dir $d (must only contain alphanums or -)."
        error "invalid intermediate dir."
    }
}

proc getIntermediateDir {} {
    global gIntermediateDir
    return $gIntermediateDir
}

set gProductDir "product"

proc setProductDir { d } {
    global gProductDir

    if { [regexp {^([a-zA-Z0-9-]+|\.)$} $d] } {
        set gProductDir $d
    } else {
        message "Error: invalid product dir $d (must only contain alphanums or -)."
        error "invalid product dir."
    }
}

proc getProductDir {} {
    global gProductDir
    return $gProductDir
}

#
# LABELS mechanism
#
set filter_list [list]

proc setIncludeLabel {arg} {
    global filter_list

    lappend filter_list includelabel [split $arg ","]
}

proc setIncludePackage {arg} {
    global filter_list

    lappend filter_list includepackage [split $arg ","]
}

proc setExcludePackage {arg} {
    global filter_list

    lappend filter_list excludepackage [split $arg ","]
}

proc setExcludeLabel {arg} {
    global filter_list

    lappend filter_list excludelabel [split $arg ","]
}

proc setExcludeLabelTest {} {
    global filter_list

    set filter_list [linsert $filter_list 0 excludelabel test]
}

proc passLabelFilter { args } {
    global filter_list

    if { [llength $args] == 0 } {
        if { ![info exists ::Config::LABELS] } {
            set labels [list]
        } else {
            set labels $::Config::LABELS
        }
    } else {
        set labels $args
    }

    foreach {type rule} $filter_list {
        switch $type {
            includepackage {
                if {[info exists ::Config::PACKAGE]} {
                    if { [lsearch $rule $::Config::PACKAGE] >= 0 } {
                        return 1
                    }
                }
            }
            excludepackage {
                if {[info exists ::Config::PACKAGE]} {
                    if { [lsearch $rule $::Config::PACKAGE] >= 0 } {
                        return 0
                    }
                }
            }
            includelabel {
                foreach l $labels {
                    if { [lsearch $rule $l] >= 0 } {
                        return 1
                    }
                }
            }
            excludelabel {
                foreach l $labels {
                    if { [lsearch $rule $l] >= 0 } {
                        return 0
                    }
                }
            }
        }
    }
    return 1
}

proc cacheArgs {} {
    global argv
    global cached_argv

    set cached_argv $argv
}

proc writeCachedArgs {} {
    global outfp
    global cached_argv

    if { ![info exists cached_argv] } {
        return
    }

    set cachefile [file join [getCacheDir] argscache]
    if {[catch {set outfp [open $cachefile "w"]}]} {
        message "Error opening $cachefile for writing."
        error "I/O error"
    }
    output "set cached_argv \[list $cached_argv\]\n"
    close $outfp
}

# Argument caching is only supported in the toplevel dir.
# Because the buildroot is not yet available, we try to open
# the cache file at a relative path.
proc readCachedArgs {} {
    global argc
    global argv

    set cachefile [file join setupcache argscache]
    if { ![file exists $cachefile] } {
        return
    }

    if { [catch {source $cachefile}] } {
        message "Error: Failed to read argument cache '$cachefile'."
        error "corrupted argument cache"
    }

    set argv $cached_argv
    set argc [llength $argv]

    msgout -2 "Using cached arguments:"
    msgout -2 $argv
}

proc readArgsPreset {presetfile command} {
    global HELPERSDIR

    set path [file join $HELPERSDIR preset.d $presetfile]
    if { ![file exists $path] } {
        error "preset '$path' does not exist."
    }
    if { [catch { namespace eval ArgsPreset "source {$path}" } ] } {
        error "Could not source preset file '$path'."
    }
    array set argspresets $ArgsPreset::args
    set preset [list]
    if { [info exists argspresets(default)] } {
        set preset $argspresets(default)
    }
    if { [info exists argspresets($command)] } {
        set preset [concat $preset $argspresets($command)]
    }
    return $preset
}
#
# Print help on the common options
#
proc helpersArgParseHelp {} {
    global archs
    global compilers

    message "Common options:"
    message {  [--preset <name>]             use args from preset <name> (mandatory).}
    message {  [--packagefilename filename]  filename will be read instead of Package}
    message {  [--archs arch1 arch2 ...]     process only listed archs (may be mandatory)}
    message "                                  may be 'ALL' or one or more architectures"
    message "                                  from the following list:"
    message "                                  $archs"
    message {  [--compiler compiler]         select compiler if multiple compilers supported by arch.}
    message {                                  Currently only one arch may be selected if a compiler is specified.}
    message {                                  Supported compilers:}
  foreach {a c} [array get compilers] {
    message "                                    $a: $c"
  }
    message {  [--prepackedcompiler <comp>]  use <comp> instead of actual compiler for selecting prepackeds.} 
    message {  [--multipleprocesses [num]]   Compile with [num] processes in parallel (Windows VC9 only).}
    message {                                  If [num] is not given the maximum number of cores will be used.}
    message {  [--intermediatedir <dir>]     sub-directory to store intermediate files.}
    message {  [--productdir <dir>]          sub-directory to store final build results.}
    message {  [--nocygwinpaths]             suppress replacement of DOS-Paths with cygwin-Paths}
    message {  [--verbose level]             print some debugging messages, e.g. verbose=50}
    message {  [--docskin skin]              use skin for creating documentation.}
    message {  [--includelabel label,...]    include packages that have a LABEL matching}
    message {                                  an entry in the comma separated list.}
    message {  [--includepackage name,...]   include packages with a name matching}
    message {                                  an entry in the comma separated list.}
    message {  [--excludepackage name,...]   exclude packages with a name matching}
    message {                                  an entry in the comma separated list.}
    message {  [--excludelabel label,...]    exclude packages that have a LABEL matching}
    message {                                  an entry in the comma separated list.}
    message {                                The filters are evaluated in command line order.}
    message {                                The first filter that matches makes the decision.}
    message {  [--ignoreprepacked name,...]  ignore prepacked name.}
    message {  [--overrideprepacked pkg,...] <name>_<version> forces using the specified version}
    message {                                 of prepacked <name>; for example, oiv_8.0.0-8.}
    message {  [--includedata]               Include prepacked package data.}
    message {  [--excludedata]               Exclude prepacked package data.}
    message {                                createBuildSystem's default is to exclude data.}
    message {                                makeDist's default is to include data.}
    message {  [--nolicensecheck]            switch off license checks for debug builds.}
    message {  [--test/--no-test]            control whether unit tests are included in the build.}
    message {  [--prepackedsrcpref subname]  set a subname used to sort the prepackets source.}
    message {                                  It is equivalent to set the AMIRA_PREPACKEDSRC env var.}
    message {  [--prepackedsrcs url1,...]    set a list of additional prepacked sources (one or more).}
    message {                                  This list is concatenated to the default one.}
    message {                                  No space char is allowed in url1,... }
}

#
# parse the arguments for common options and store them in global vars for
# later processing
#
proc helpersArgParse {command} {
    global packageFileName
    global verbose
    global doReplaceDOSPaths
    global argc
    global argv
    global archsonly
    global archs
    global prepackedcompiler
    global arch2compiler
    global validate
    global licensecheck
    global opt_test
    global prepackedSourcePref
    global prepackedSources
    global numprocesses

    set OPT_compiler ""
    set validate 1
    set licensecheck 1
    set opt_test 0

    set pos 0;
    while {$pos < $argc} {
        set o [lindex $argv $pos];
        set rem 0;
        if {$o == "--preset"} {
            set presetfile [lindex $argv [expr $pos + 1]]
            set preset [readArgsPreset $presetfile $command]
            message "Note: Expanding preset '$presetfile' to '$preset'"
            set argv [concat [lrange $argv 0 [expr $pos - 1]] $preset [lrange $argv [expr $pos + 2] end]]
            set argc [llength $argv]
            continue
        }
        if {$o == "--packagefilename"} {
            set packageFileName [lindex $argv [expr $pos + 1]];
            message "Using packagefilename [getPackageFileName]"
            set rem 2;
        } elseif {$o == "--verbose"} {
            setVerbosity [lindex $argv [expr $pos + 1]];
            message "Using verbosity $verbose";
            set rem 2;
        } elseif {$o == "--compiler"} {
            set OPT_compiler [lindex $argv [expr $pos + 1]];
            set rem 2;
        } elseif {$o == "--prepackedcompiler"} {
            set prepackedcompiler [lindex $argv [expr $pos + 1]];
            set rem 2;
        } elseif {$o == "--multipleprocesses" } {
            set x [lindex $argv [expr $pos + 1]];
            
            if {[string is integer -strict $x]} {
                set numprocesses $x
                message "Using $numprocesses concurrent processes";
                set rem 2;
            } else {
                set numprocesses -1
                message "Using max number of concurrent processes";
                set rem 1;
            }
        } elseif {$o == "--intermediatedir"} {
            set d [lindex $argv [expr $pos + 1]];
            setIntermediateDir $d
            set rem 2;
        } elseif {$o == "--productdir"} {
            set d [lindex $argv [expr $pos + 1]];
            setProductDir $d
            set rem 2;
        } elseif {$o == "--docskin"} {
            set s [lindex $argv [expr $pos + 1]];
            setDocSkin $s
            message "Using documentation skin $s"
            set rem 2;
        } elseif {$o == "--includelabel"} {
            set l [lindex $argv [expr $pos + 1]];
            setIncludeLabel $l
            set rem 2;
        } elseif {$o == "--includepackage"} {
            set l [lindex $argv [expr $pos + 1]];
            setIncludePackage $l
            set rem 2;
        } elseif {$o == "--excludepackage"} {
            set l [lindex $argv [expr $pos + 1]];
            setExcludePackage $l
            set rem 2;
        } elseif {$o == "--excludelabel"} {
            set l [lindex $argv [expr $pos + 1]];
            setExcludeLabel $l
            set rem 2;
        } elseif {$o == "--ignoreprepacked"} {
            set p [lindex $argv [expr $pos + 1]]
            setIgnorePrepacked $p
            set rem 2
        } elseif {$o == "--overrideprepacked"} {
            set p [lindex $argv [expr $pos + 1]]
            setOverridePrepacked $p
            set rem 2
        } elseif {$o == "--includedata"} {
            setIncludePrepackedData 1
            set rem 1
        } elseif {$o == "--excludedata"} {
            setIncludePrepackedData 0
            set rem 1
        } elseif {$o == "--nocygwinpaths"} {
            set doReplaceDOSPaths 0;
            message "Suppressing path replacements";
            set rem 1;
        } elseif {$o == "--nolicensecheck"} {
            set licensecheck 0;
            message "Warning: Switching off license checks for debug builds";
            set rem 1;
        } elseif {$o == "--test"} {
            set opt_test 1
            set rem 1
        } elseif {$o == "--no-test"} {
            set opt_test 0
            set rem 1
        } elseif {$o == "--prepackedsrcpref"} {
            set s [lindex $argv [expr $pos + 1]];
            set prepackedSourcePref $s
            set rem 2;
        } elseif {$o == "--prepackedsrcs"} {
            set s [lindex $argv [expr $pos + 1]]
            set prepackedSources $s
            set rem 2
        } elseif {$o == "--archs"} {
            set rem 1;
            foreach x [lrange $argv [expr $pos + 1] end] {
                if {[string compare -length 2 $x "--"] == 0} {
                    break;
                }
                # validate option
                # ALL is an alias for a default list of standard archs
                if { $x == "ALL" } {
                    set archsonly [list Linux Linux64 SunOS SunOS64 MacX Win64VC9 LinuxAMD64]
                } elseif { [isValidArch $x] } {
                    lappend archsonly $x;
                } else {
                    message "Error: found invalid arch string $x while parsing --archs";
                    error "invalid arch";
                }
                incr rem;
            }
            if { [llength $archsonly]  != 1 } {
                message "Warning: requesting more than one arch is deprecated."
            }
        }
        incr argc -$rem;
        set argv [lreplace $argv $pos [expr $pos + $rem - 1]];
        if {$rem == 0} {
            incr pos;
        }
    }

    if { ![info exists presetfile] } {
        message "Error: --preset is mandatory.  You can use '--preset none' to avoid this message."
        error "--preset is mandatory."
    }

    if { !$opt_test } {
        setExcludeLabelTest
    }

    if { ![info exists archsonly] } {
        guessArch
    }
    if { ![info exists archsonly] } {
        return
    }
    if { $OPT_compiler != "" } {
        if { [llength $archsonly] != 1 } {
            message "Error: when explicitly selecting a compiler by using --compiler you may select only one arch"
            error "only one arch with compiler"
        }
        if { [isValidCompiler $archsonly $OPT_compiler] } {
            message "Using compiler $OPT_compiler"
        } else {
            message "Error: found invalid compiler $OPT_compiler"
            error "invalid compiler"
        }
        set arch2compiler($archsonly) $OPT_compiler
    }
    foreach a $archsonly {
        if { [info exists arch2compiler($a)] } {
            findGCC $a
        }
    }
}

#set packageFileName "Package-Pfizer"
proc getPackageFileName {} {
    global packageFileName

    if {[info exists packageFileName]} {
        return $packageFileName
    } else {
        return "Package"
    }
}

####
#### Search Package files below -> packagedir
#### and run command $rootdir $packagedir
####
proc runForeachPackage [list rundir command [list opt [list]]] {
    global packagegloblist

    set rootpwd [findBuildroot $rundir];

    message "BUILDROOT: $rootpwd";
    set pwd [pwd];
    cd $rundir;
    set runpwd [pwd];
    set relpwd [string range $runpwd [expr [string length $rootpwd] + 1] end];
####
#### search all packages below rundir
####
    if { ![info exists packagegloblist($rundir)] } {
        set packagegloblist($rundir) [concat \
                    [glob -nocomplain -join [getPackageFileName]] \
                    [glob -nocomplain -join * [getPackageFileName]] \
                    [glob -nocomplain -join * * [getPackageFileName]] \
                    [glob -nocomplain -join * * * [getPackageFileName]] \
                    [glob -nocomplain -join * * * * [getPackageFileName]] \
                    [glob -nocomplain -join * * * * * [getPackageFileName]] \
                    [glob -nocomplain -join * * * * * * [getPackageFileName]] \
                ]
    }
    foreach x $packagegloblist($rundir) {
            set d [file dirname $x];
            if {$d == "."} {
                set p $relpwd;
            } else {
                set p [file join $relpwd $d];
            }
            if {[llength $opt]} {
                $command $rootpwd $p $opt;
            } else {
                $command $rootpwd $p;
            }
    }
    cd $pwd;
}

####
#### callback proc for buildAutoIncludeList
####
proc appendToIncludeList {rootdir dir} {
    global autoIncludeList;

    set inc BUILDROOT;
    foreach x [lrange [file split $dir] 0 end-1] {
        set inc [file join $inc $x];
    }
    if {[lsearch $autoIncludeList $inc] < 0} {
        lappend autoIncludeList $inc;
    }
}

####
#### search all packages below buildroot
#### and create a list of include paths
#### to all dirs one higher than a package dir
#### This list is required to make includes
#### #include <package/xyz.h>
#### work in any case.
####
proc buildAutoIncludeList {dir} {
    global autoIncludeList;
    set autoIncludeList [list];

    set rootpwd [findBuildroot $dir];
    runForeachPackage $rootpwd appendToIncludeList;
}

proc getAutoIncludes {} {
    global autoIncludeList

    return $autoIncludeList
}

####
#### callback proc for scanProvides
####
proc appendToProvides {rootdir dir} {
    global gProvides
    global gPackages

    message "scanning provides in $dir"
    readConfig $rootdir $dir

    # Remember all package names in gPackages.
    # Later gPackages will be used to filter out prepacked archives.
    lappend gPackages $::Config::PACKAGE

    if { ![info exists ::Config::PROVIDES] } {
        return
    }
    foreach {var value} $::Config::PROVIDES {
       if {![isValidProvidesVar $var]} {
           message "Error in $Run::reldir: PROVIDES contains invalid variable $var"
           error "Fatal"
       }
       foreach {from to} $value {
           if { [info exists gProvides($var,$from)] } {
               message "Error in $Run::reldir: PROVIDES tries to set $var { $from }, which was already set to '$to'. PROVIDES must be unique!"
               error "Fatal"
           }
           set gProvides($var,$from) 1
           foreach {a b} $to {
                set gProvides($var,$from,$a) $b
                message "$Run::reldir PROVIDES: $var: $a $from -> $b"
           }
       }
    }
}

proc isValidProvidesVar {var} {
    if { [regexp {^([A-Z]*)-([0-9a-zA-Z]*)(?:-([a-zA-Z0-9]+))?-([a-zA-Z]*)$} $var dummy name arch compiler config] } {
        if { $name == "LIBSALIAS" && [isValidArch $arch] && [isValidConfig $config]} {
            if { $compiler != "" && ![isValidCompiler $arch $compiler] } {
                message "Warning in $Run::reldir: $var uses invalid compiler '$compiler'."
            }
            return 1;
        }
    }
    return 0
}
####
#### search all packages below buildroot
#### and create a list of include paths
#### to all dirs one higher than a package dir
#### This list is required to make includes
#### #include <package/xyz.h>
#### work in any case.
####
proc scanProvides {dir} {
    message "scanning for PROVIDES"

    set rootpwd [findBuildroot $dir];
    runForeachPackage $rootpwd appendToProvides;
}

####
#### Store global config that contains setup of current product.
####
proc storeVariable {cmd var value} {
    global configStore

    set arch "default"
    if { [regexp {^[A-Z0-9_]*-(.*)$} $var dummy ac] } {
        regexp {^[^-]*} $ac arch
    }
    if { ![info exists configStore($arch)] } {
        set configStore($arch) ""
    }
    append configStore($arch) "$cmd $var $value\n\n"
}

proc storeBuildSystemConfig {} {
    global configStore
    global gProvides
    global outfp

    namespace eval Config {}
    namespace delete Config

    readGlobalConfig

    # Output configuration such that it can be sourced in namespace Config.
    regsub -all "::Config::" [info vars ::Config::*] "" tmp;
    foreach x $tmp {
        storeVariable set $x [string map [list PRODUCTROOT MAINROOT] "{[subst \${::Config::$x}]}"]
    }

    storeVariable set TAGLIB-Win32VC8 {[file join $MAINROOT bin arch-Win32VC8-Optimize taglib]}
    storeVariable set BASE_LIBPATH-Win32VC8 {[file join $MAINROOT bin arch-Win32VC8-Optimize]}
    storeVariable set BASE_LIBPATH-Win32VC8-Debug {[file join $MAINROOT bin arch-Win32VC8-Debug]}
    storeVariable set DOC2HTML-Win32VC8 {[file join $MAINROOT bin arch-Win32VC8-Optimize doc2html.exe]}
    storeVariable set QT_MOC-Win32VC8 {[file join $MAINROOT bin arch-Win32VC8-Optimize moc.exe]}
    storeVariable set QT_RCC-Win32VC8 {[file join $MAINROOT bin arch-Win32VC8-Optimize rcc.exe]}
    storeVariable set QT_UIC-Win32VC8 {[file join $MAINROOT bin arch-Win32VC8-Optimize uic.exe]}

    storeVariable set TAGLIB-Win32VC9 {[file join $MAINROOT bin arch-Win32VC9-Optimize taglib]}
    storeVariable set BASE_LIBPATH-Win32VC9 {[file join $MAINROOT bin arch-Win32VC9-Optimize]}
    storeVariable set BASE_LIBPATH-Win32VC9-Debug {[file join $MAINROOT bin arch-Win32VC9-Debug]}
    storeVariable set DOC2HTML-Win32VC9 {[file join $MAINROOT bin arch-Win32VC9-Optimize doc2html.exe]}
    storeVariable set QT_MOC-Win32VC9 {[file join $MAINROOT bin arch-Win32VC9-Optimize moc.exe]}
    storeVariable set QT_RCC-Win32VC9 {[file join $MAINROOT bin arch-Win32VC9-Optimize rcc.exe]}
    storeVariable set QT_UIC-Win32VC9 {[file join $MAINROOT bin arch-Win32VC9-Optimize uic.exe]}

    storeVariable set TAGLIB-Win64VC9 {[file join $MAINROOT bin arch-Win64VC9-Optimize taglib]}
    storeVariable set BASE_LIBPATH-Win64VC9 {[file join $MAINROOT bin arch-Win64VC9-Optimize]}
    storeVariable set BASE_LIBPATH-Win64VC9-Debug {[file join $MAINROOT bin arch-Win64VC9-Debug]}
    storeVariable set DOC2HTML-Win64VC9 {[file join $MAINROOT bin arch-Win64VC9-Optimize doc2html.exe]}
    storeVariable set QT_MOC-Win64VC9 {[file join $MAINROOT bin arch-Win64VC9-Optimize moc.exe]}
    storeVariable set QT_RCC-Win64VC9 {[file join $MAINROOT bin arch-Win64VC9-Optimize rcc.exe]}
    storeVariable set QT_UIC-Win64VC9 {[file join $MAINROOT bin arch-Win64VC9-Optimize uic.exe]}

    foreach {k to} [array get gProvides] {
        set keys [split $k ","]
        if { [llength $keys] == 3 } {
            set alias [lindex $keys 0]
            set from [lindex $keys 1]
            set detail [lindex $keys 2]
            storeVariable lappend $alias "$from {$detail {$to}}"
        }
    }

    set dir [file join [getBuildRoot] [getProductDir] share devtools BuildSystemConfig.d]
    file mkdir $dir
    foreach arch [concat default [getRequestedArchs]] {
        if { [info exists configStore($arch)] } {
            if {[catch {set outfp [open [file join $dir $arch] "w"]}]} {
                message "Error opening $dir/$arch for writing."
                error "I/O error"
            }
            output $configStore($arch)
            close $outfp
        }
    }
}

####
#### replace Unix path delimiters by DOS delimiters
####
#### This command is used when writing custom build
#### steps in Visual Studio dsp files (MOC,FLEX,BISON).
#### Unix style delimiters do not work on Windows 9x.
####
proc dospath {x} {
    regsub -all / $x \\ result
    return $result
}

proc dos2cygwinpath {x} {
    global doReplaceDOSPaths

    if {$doReplaceDOSPaths} {
        #~ Replace DOS-Path with Cygwin-Path
        regsub {^([a-zA-Z]):} $x {/cygdrive/\1} result;
        regsub -all {\\} $result {/} result
        return $result;
    }

    #~ No replacement: return given path as is
    return $x;
}

proc validIdentifier {x {abortOnError 1}} {
# replace all spaces
    regsub -all { } $x {} result;
# replace all except for alphanumerics
    regsub -all {[^a-zA-Z0-9]} $result {} result;
# replace starting numbers
    regsub {^ *[0-9]*} $result {} result;
    if {$abortOnError && $result == ""} {
        message "Error: Can't create valid identifier from $x";
        error "Fatal";
    }
    return $result;
}

####
#### expandCopy $src $dest
#### dest might be a
####   - a single file
####   - {dest1 -> symlink1 symlink2 symlink3}
####
proc expandCopy {src dest} {
###
### check if src starts with X:/ and standardize to X:
###
    if {[string match -nocase {[a-z]:/} [string range $src 0 2]]} {
       set src "[string range $src 0 1][string range $src 3 end]"
    }

    set syms [list];
    if {[llength $dest] > 1} {
        if {[lindex $dest 1] != "->" } {
            message "Error: multiple COPY target only support symlinks '->' ($dest)"
        }
        set maindest [lindex $dest 0];
        set syms [lrange $dest 2 end];

        set dest $maindest;
    }
    if {[string index $dest end] == "/"} {
        set dest [file join $dest [file tail $src]];
    }

    set expsyms [list];
    foreach x $syms {
        lappend expsyms [file join [file dirname $dest] $x];
    }
    return [list $src $dest $expsyms];
}

proc confineFile {f} {
    set warning 0;
    set parts [file split $f];
    while { [string equal [lindex $parts 0] ".."] } {
        set parts [lreplace $parts 0 0];
        set warning 1;
    }
    set confinedf "";
    foreach x $parts {
        set confinedf [file join $confinedf $x];
    }
    if {$warning} {
        message "WARNING: confined to --> $confinedf";
    }
    return $confinedf;
}

####
#### glob a list in a specfic directory
####
#### dir is relative to pwd
####
# WARNING: the following function will fail if directory part will be expanded
proc globCygwin {pattern} {
    set matches [glob $pattern];
    set result [list];
    foreach entry $matches {
        if {[file dirname $pattern] != "."} {
            lappend result "[file dirname $pattern]/[file tail $entry]";
        } else {
            lappend result "[file tail $entry]";
        }
    }
    return $result;
}

proc globList {dir var} {
    set ret [list];
    foreach x $var {
        set pwd [pwd];
        cd $dir;
        if {[catch {set ret [concat $ret [globCygwin $x]]} ]} {
            cd $pwd
            error "Could not find $x in $dir"
        }
        cd $pwd;
    }
    return $ret;
}

####
#### recursive glob (copied from http://wiki.tcl.tk/1474)
####
proc glob-r {{dir .}} {
    set res {}
    foreach i [lsort [glob -nocomplain -dir $dir *]] {
        if {[file type $i]=="directory"} {
            eval lappend  res [glob-r $i]
        } else {
            lappend res $i
        }
    }
    return $res
} ;# RS


####
#### expand LIBS using LIBSALIAS
#### you have to ask with full architecture (arch and config).
####
#### if no alias is found LIBS is expanded to itself
####
proc expandLIBS {libs var arch config} {
    global gProvides
    global gMainConfig
    global arch2compiler
    global prepackedcompiler

    set mainconfig $config
    if { [info exists gMainConfig] } {
        set mainconfig $gMainConfig
    }

    set compiler ""
    if { $prepackedcompiler != "" } {
        set compiler $prepackedcompiler
    } elseif { [info exists arch2compiler($arch)] } {
        set compiler $arch2compiler($arch)
    }

    set a [list]
    if { [info exists ::Config::LIBSALIAS-$arch] } {
        set a [subst $\{Config::LIBSALIAS-$arch\}]
    }
    set ac [list]
    if { [info exists ::Config::LIBSALIAS-$arch-$mainconfig] } {
        set ac [subst $\{Config::LIBSALIAS-$arch-$mainconfig\}]
    }
    set acc [list]
    if { [info exists ::Config::LIBSALIAS-$arch-$compiler] } {
        set acc [subst $\{Config::LIBSALIAS-$arch-$compiler\}]
    }
    set accc [list]
    if { [info exists ::Config::LIBSALIAS-$arch-$compiler-$mainconfig] } {
        set accc [subst $\{Config::LIBSALIAS-$arch-$compiler-$mainconfig\}]
    }

    set ret [list];
    array set tmp [concat $Config::LIBSALIAS $a $ac $acc $accc];
    foreach l $libs {
        if {[info exists gProvides(LIBSALIAS-$arch-$config,$l,$var)]} {
            set ret [concat $ret $gProvides(LIBSALIAS-$arch-$config,$l,$var)];
            continue;
        }
        if {[info exists gProvides(LIBSALIAS-$arch,$l,$var)]} {
            set ret [concat $ret $gProvides(LIBSALIAS-$arch,$l,$var)];
            continue;
        }
        if {[info exists gProvides(LIBSALIAS-$arch-$compiler,$l,$var)]} {
            set ret [concat $ret $gProvides(LIBSALIAS-$arch-$compiler,$l,$var)];
            continue;
        }
        if {[info exists gProvides(LIBSALIAS-$arch-$compiler-$config,$l,$var)]} {
            set ret [concat $ret $gProvides(LIBSALIAS-$arch-$compiler-$config,$l,$var)];
            continue;
        }
        if {![info exists tmp($l)]} {
            if {$var == "LIBS"} {
                set ret [concat $ret $l];
            }
            continue;
        }
        if {$tmp($l) == "."} {
            message "missing expansion for $l";
            continue;
        }
        if { [info exists tmp1] } {
            unset tmp1
        }
        array set tmp1 $tmp($l);
        if {![info exists tmp1($var)]} {
            continue;
        }
        set ret [concat $ret $tmp1($var)];
    }
    return $ret;
}

proc expandIncludes {arch config} {
    global MAINROOT
    set result [list]

    foreach x [ list \
            ::Config::INCLUDES-$arch \
            ::Config::LIBS-$arch \
            ::Config::LIBS-$arch-$config \
            ::Config::BASE_INCLUDES-$arch \
    ] {
        if { ![info exists $x] } {
            set $x ""
        }
    }

    foreach x [concat \
                [subst $\{::Config::INCLUDES-$arch\}] \
                ${::Config::INCLUDES} \
                [getAutoIncludes] \
                [expandLIBS \
                    [concat \
                        ${Config::LIBS} \
                        [subst $\{::Config::LIBS-$arch\}] \
                        [subst $\{::Config::LIBS-$arch-$config\}] \
                    ] \
                    INCLUDES $arch $config
                ] \
                [subst $\{::Config::BASE_INCLUDES-$arch\}] \
                $::Config::BASE_INCLUDES
              ] \
    {
        set start [lindex [file split $x] 0]

        if {$start == "." || $start == ".."} {
           set expanded $x;
        } elseif {$start == "BUILDROOT" } {
           set expanded [file join $::Run::pathToRoot [join [lrange [file split $x] 1 end] "/"]];
        } elseif {$start == "PRODUCTROOT" } {
           set expanded [file join $::Run::pathToProduct [join [lrange [file split $x] 1 end] "/"]];
        } elseif {$start == "MAINROOT" } {
           set expanded [file join $MAINROOT [join [lrange [file split $x] 1 end] "/"]];
        } else {
           set expanded $x;
        }
        lappend result $expanded
    }

    return $result
}

proc genVarNames {base ext} {
    set ret [list]
    foreach b $base {
        foreach e $ext {
            if {$e == ""} {
                lappend ret $b
            } else {
                lappend ret $b-$e
            }
        }
    }
    return $ret
}

# gen arch dependent var names based on names in base
proc genArchVars {base} {
    return [genVarNames $base [getRequestedArchs]]
}

# gen config dependent var names based on names in base
proc genConfVars {base} {
    global configs

    return [genVarNames $base $configs]
}

# gen all var names based on base
proc genAllVars {base} {
    return [concat $base [genArchVars $base] [genConfVars [genArchVars $base]]];
}

# validate prepacked
# The format is PACKAGENAME_VERSION-INTERNALPATCH_CLASSIFICATION_ARCH-COMPILER-CONFIG
#   PACKAGENAME: usual rule alphanum
#   VERION: alphanum and .
#   INTERNALPATCH: number
#   CLASSIFICATION: one of base, dev, intern, data, interndata
#   ARCH: one of our archs, no '-' allowed (optional)
#   COMPILER: one of our compilers
#   CONFIG: one of our configs (optional)
# ARCH may stand alone or together with -CONFIG, with -COMPILER, or with -COMPILER-CONFIG
proc isValidPrepackedName {n} {
    return [regexp {^[a-zA-Z0-9]+_[0-9a-zA-Z.]+-[0-9]+_(base|dev|intern|data|interndata)(_[a-zA-Z0-9]+(-([a-zA-Z0-9]+))?(-(Debug|Optimize))?)?$} $n];
}

####
#### parse prepacked name without any wildcard expansion
####
proc parsePrepackedName {fullname} {
    set arch "";
    set config "";
    set compiler "";
    if { [regexp {^([a-zA-Z0-9]+)_([0-9a-zA-Z.]+-[0-9]+)_(base|dev|intern|data|interndata)(_[a-zA-Z0-9]+(-([a-zA-Z0-9]+))?(-(Debug|Optimize))?)?$} $fullname dummy name version class remainder] } {
        if { [regexp {^_([a-zA-Z0-9]+)((-([a-zA-Z0-9]+))?(-(Debug|Optimize))?)$} $remainder dummy arch remainder1] } {
            if { [regexp {^-(Debug|Optimize)$} $remainder1 dummy config] } {
                ;
            } elseif { [regexp {^-([a-zA-Z0-9]+)-(Debug|Optimize)$} $remainder1 dummy compiler config] } {
                ;
            } else {
                regexp {^-([a-zA-Z0-9]+)$} $remainder1 dummy compiler
            }
        }
        return [list $name $version $class $arch $compiler $config];
    }
    error "Internal ERROR: trying to parse invalid package name $fullname";
}

# return base, dev, intern, data, interndata
proc getPrepackedClassification {fullname} {
    return [lindex [parsePrepackedName $fullname] 2];
}

set gIncludePrepackedData 1
proc setIncludePrepackedData {flag} {
    global gIncludePrepackedData

    set gIncludePrepackedData $flag
}

proc includePrepackedData {} {
    global gIncludePrepackedData

    return $gIncludePrepackedData
}

proc isRequestedPrepackedClassification {class} {
    switch $class {
        base
            -
        dev
            -
        intern {
            return 1;
        }
        interndata
            -
        data {
            return [includePrepackedData]
        }
        default {
            error "internal error, found invalid class '$class'"
        }
    }
}

# normally you might want to skip prepacked data
proc isRequestedPrepacked {package fullname} {
    set atoms [parsePrepackedName $fullname];
    set name [lindex $atoms 0];
    set class [lindex $atoms 2];
    set arch [lindex $atoms 3];
    set compiler [lindex $atoms 4];
    if {$arch == "" || [isRequestedArch $arch]} {
        if {$compiler == "" || [isRequestedPrepackedCompiler $arch $compiler]} {
            if {[isRequestedPrepackedClassification $class]} {
                if { ![prepackedAvailableAsPackage $package $name $class]
                     && ![isIgnoredPrepacked [lindex $atoms 0]] } {
                    return 1;
                }
            }
        }
    }
    return 0;
}

###
### TODO add compiler
###
proc validatePrepackedList {prepacked} {
    # sort atoms per package name
    foreach fullname $prepacked {
        if { [isValidPrepackedName $fullname] } {
            set atoms [parsePrepackedName $fullname];
            set arch [lindex $atoms 3];
            if {$arch == "" || [isValidArch $arch]} {
                ; #ok
            } elseif {$arch == "Win32"} {
               message "Warning in $Run::reldir/[getPackageFileName]: Support for Win32 was dropped. You should remove prepacked $fullname."
            } elseif {$arch == "Win32VC7"} {
               message "Warning in $Run::reldir/[getPackageFileName]: Support for Win32VC7 was dropped. You should remove prepacked $fullname."
            } else {
                message "ERROR: invalid arch in prepacked $fullname"
                error "invalid prepacked"
            }

            set compiler [lindex $atoms 4];
            if {$compiler == "" || [isValidCompiler $arch $compiler]} {
                ; #ok
            } else {
                message "Warning in $Run::reldir: invalid compiler in prepacked $fullname"
            }

            set pakname [lindex $atoms 0];
            lappend pak($pakname) $atoms
        } else {
            message "ERROR: invalid prepacked name $fullname";
            error "invalid prepacked"
        }
    }
    # check all package names for version conflict
    foreach {key atoms} [array get pak] {
        array unset archversion;
        array unset archccversion;
        set noarchcheck "";
        foreach a $atoms {
            set version [lindex $a 1]
            set arch [lindex $a 3];
            set compiler [lindex $a 4];
            set config [lindex $a 5];
            if {$arch == ""} {
                # noarch with noarch
                if {$noarchcheck != ""} {
                    if {$noarchcheck == $version} {
                        # fine
                    } else {
                        message "ERROR: prepacked $key: version conflict between $noarchcheck and $version ($a)";
                        error "invalid prepacked"
                    }
                } else {
                    set noarchcheck $version
                }
            } else {
                if {$compiler == ""} {
                    # arch with arch
                    if {[info exists archversion($arch)]} {
                        if {$archversion($arch) == $version} {
                            # fine
                        } else {
                            message "ERROR: prepacked $key: version conflict between $archversion($arch) and $version ($a)";
                            error "invalid prepacked"
                        }
                    } else {
                        set archversion($arch) $version
                    }
                } else {
                    # arch-compiler with arch-compiler
                    if {[info exists archccversion($arch,$compiler)]} {
                        if {$archccversion($arch,$compiler) == $version} {
                            # fine
                        } else {
                            message "ERROR: prepacked $key: version conflict between $archccversion($arch,$compiler) and $version ($a)";
                            error "invalid prepacked"
                        }
                    } else {
                        set archccversion($arch,$compiler) $version
                    }
                }
            }
        }
        # noarch with arch and arch-compiler
        if {$noarchcheck != ""} {
            foreach {arch ver} [array get archversion] {
                if {$ver != $noarchcheck} {
                    message "ERROR: prepacked $key: version conflict between $ver (arch $arch) and $noarchcheck (noarch)";
                    error "invalid prepacked"
                }
            }
            foreach {archcompiler ver} [array get archccversion] {
                set a [lindex [split $archcompiler ,] 0]
                set c [lindex [split $archcompiler ,] 1]
                if {$ver != $noarchcheck} {
                    message "ERROR: prepacked $key: version conflict between $ver (arch $a, compiler $c) and $noarchcheck (noarch)";
                    error "invalid prepacked"
                }
            }
        }
        # arch-compiler with arch
        foreach {archcompiler ver} [array get archccversion] {
            set a [lindex [split $archcompiler ,] 0]
            set c [lindex [split $archcompiler ,] 1]
            if {[info exists archversion($a)]} {
                if {$archversion($a) != $ver} {
                    message "ERROR: prepacked $key: version conflict between $ver (arch $a, compiler $c) and $archversion($a) (no compiler)";
                    error "invalid prepacked"
                }
            }
        }
    }
    return 1
}

proc prepackedAvailableAsPackage {package prepackedname class} {
    global gPackages
    # prepackeds must not be filtered out if they are defined in a package with the same name
    if { $prepackedname == $package } {
        return 0;
    }
    # data prepackeds must not be filtered out: demoalign uses prepacked "hxalign_3.1-1_data"
    if { $class == "data" || $class == "interndata" } {
        return 0;
    }
    if { [lsearch -exact $gPackages $prepackedname] >= 0 } {
        message "prepacked $prepackedname available as package, skip"
        return 1
    }
    return 0
}

proc setIgnorePrepacked {arg} {
    global gIgnoredPrepackeds

    global gIgnoredPrepackeds
    if { ![info exists gIgnoredPrepackeds] } {
        set gIgnoredPrepackeds [list]
    }

    set gIgnoredPrepackeds [concat gIgnoredPrepackeds [split $arg ","]]
}

proc withIgnorePrepacked {} {
    global gIgnoredPrepackeds
    return [info exists gIgnoredPrepackeds]
}

proc isIgnoredPrepacked {name} {
    global gIgnoredPrepackeds
    global gReportedIgnorePrepacked
    if { ![info exists gIgnoredPrepackeds] } {
        return 0
    }
    if { [lsearch -exact $gIgnoredPrepackeds $name] >= 0 } {
        if { ![info exists gReportedIgnorePrepacked($name)] } {
            message "Note: Ignoring prepacked $name due to --ignoreprepacked."
            set gReportedIgnorePrepacked($name) 1
        }
        return 1
    }
    return 0
}

proc setOverridePrepacked {arg} {
    global gOverridePrepacked

    foreach e [split $arg ","] {
        if { [regexp {^([a-zA-Z0-9]+)_([0-9a-zA-Z.]+-[0-9]+)$} $e dummy name version] } {
            set gOverridePrepacked($name) $version
        } else {
            message "Error: invalid entry '$e' in --overrideprepacked."
            error "invalid --overrideprepacked"
        }
    }
}

proc applyOverridePrepacked {atoms} {
    global gOverridePrepacked

    set name [lindex $atoms 0]
    set version [lindex $atoms 1]
    set class [lindex $atoms 2]
    set arch [lindex $atoms 3]
    set compiler [lindex $atoms 4]
    set config [lindex $atoms 5]

    set fullname "${name}"
    if { [info exists gOverridePrepacked($name)] } {
        append fullname "_$gOverridePrepacked($name)"
    } else {
        append fullname "_$version"
    }
    append fullname "_$class"
    if { $arch != "" } {
        append fullname "_$arch"
    }
    if { $compiler != "" } {
        append fullname "-$compiler"
    }
    if { $config != "" } {
        append fullname "-$config"
    }
    if { [info exists gOverridePrepacked($name)] } {
        message "Note: using $fullname due to --overrideprepacked."
    }
    return $fullname
}

# get a list of prepackeds matching arch and config
# prepackeds are implicitly filtered also by the current compiler
proc getFilteredPrepacked {package prepacked arch config} {
    set res [list]
    if {$arch == "" || [isValidArch $arch]} {
        foreach fullname $prepacked {
            set atoms [parsePrepackedName $fullname];
            if {       [isRequestedPrepackedClassification [lindex $atoms 2]]
                    && $arch == [lindex $atoms 3]
                    && ( [lindex $atoms 4] == "" || [isRequestedPrepackedCompiler $arch [lindex $atoms 4]] )
                    && $config == [lindex $atoms 5]
                    && ![prepackedAvailableAsPackage $package [lindex $atoms 0] [lindex $atoms 2]]
                    && ![isIgnoredPrepacked [lindex $atoms 0]] } {
                lappend res [applyOverridePrepacked $atoms]
            }
	}
	return $res;
    } else {
        message "Internal ERROR, getFilterPrepacked called with invalid arch $arch";
        error "exit";
    }
}

# the cache dir we're storing our downloaded files
proc getPrepackedCacheDirRelToRoot {} {
    return [file join setupcache prepacked];
}

proc getPrepackedCacheDir {} {
    set cachedir [file join [getBuildRoot] [getPrepackedCacheDirRelToRoot]];
    file mkdir $cachedir;
    return $cachedir;
}

# the cache dir we're storing state
proc getCacheDir {} {
    set cachedir [file join [getBuildRoot] setupcache];
    file mkdir $cachedir;
    return $cachedir;
}

proc urlSplitWithoutPassword {url} {
# the magic regexp from rfc2396
    regexp {^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\\?([^#]*))?(#(.*))?} $url alld d1 scheme d2 authority path d3 d4 query fragment

    set host [lindex [split $authority {@}] end]

    return [list scheme $scheme host $host path $path]
}

proc urlWithoutPassword {url} {
    array set p [urlSplitWithoutPassword $url]

    return "$p(scheme)://$p(host)$p(path)"
}

proc getPrepackedSourceUrls {} {
    global HELPERSDIR
    global prepackedSources

    if { [file exists [file join $HELPERSDIR secrets.tcl] ] } {
        source [file join $HELPERSDIR secrets.tcl]
    }
    if { [info exists prepackedSources ] } {
        return [concat $default_prepackedsrc [split $prepackedSources ","]]
    } else {
        return $default_prepackedsrc
    }
}

proc sortUrlsByPreference {urls} {
    global env
    global prepackedSourcePref
    global prepackedSources

    if {[info exists env(AMIRA_PREPACKEDSRC)]} {
        set prepackedSourcePref $env(AMIRA_PREPACKEDSRC)
    }
    if {[info exists prepackedSourcePref]} {
        if { [regexp {^[-a-zA-Z0-9._]+$} $prepackedSourcePref] } {
            message "sorting urls by $prepackedSourcePref"
            set preflength [expr [string length $prepackedSourcePref] - 1]
            set sorted [list]
            # first append all urls that match
            foreach u $urls {
                array set p [urlSplitWithoutPassword $u]
                if { [string range $p(host) end-$preflength end] == $prepackedSourcePref } {
                    message "preferring [urlWithoutPassword $u]"
                    lappend sorted $u
                }
            }
            # then fill up with all urls that don't match
            foreach u $urls {
                array set p [urlSplitWithoutPassword $u]
                if { [string range $p(host) end-$preflength end] != $prepackedSourcePref } {
                    lappend sorted $u
                }
            }
            return $sorted
        } else {
            if {[info exists env(AMIRA_PREPACKEDSRC)]} {
                message "Error: invalid environment var AMIRA_PREPACKEDSRC = '$prepackedSourcePref'. May only contain chars from [0-9A-Za-z._-]"
            } else {
                message "Error: invalid prepacked source preference = '$prepackedSourcePref'. May only contain chars from [0-9A-Za-z._-]"
            }
            error "invalid prepacked source preference";
        }
    }
    return $urls
}

# retrieve url.{lst,tar.gz,tar.bz2} to cache dir if not already present
proc retrievePrepacked {fullname} {
    global OPT_PEDANTIC
    global verbose
    global dl_cmd
    global dl_opt
    global dl_opt_time

    set prepackedsrcs [sortUrlsByPreference [getPrepackedSourceUrls]]

    if {${dl_cmd} == {}} {
        message "preferred prepacked sources list = $prepackedsrcs"

        if { [catch {regexp {^GNU Wget (\d+)\.(\d+)} [exec wget --version] match major minor} ] } {
            message "Cannot execute 'wget --version', falling back to cURL."
            set dl_cmd {curl}
            set dl_opt_cert {--insecure}
        } elseif { $minor < 10 } {
            set dl_cmd {wget}
            set dl_opt_cert {}
        } elseif { $minor >= 10 } {
            set dl_cmd {wget}
            set dl_opt_cert {--no-check-certificate}
        } else {
            message "Unrecognized Wget version, falling back to cURL."
            set dl_cmd {curl}
            set dl_opt_cert {--insecure}
        }

        # Set the download options: We do not retry and timeout after 30 seconds.
        switch $dl_cmd {
            wget {
                if {$verbose>=2} {
                    message "Using Wget $major.$minor as the download tool."
                }

                set dl_opt_def {--tries=1 --timeout=30 --no-directories --passive-ftp}
                set dl_opt_quiet {--quiet}
                set dl_opt_time {--timestamping}
            }
            curl {
                if { [catch {regexp {^curl (\d+)\.(\d+)} [exec curl --version] match major minor} ] } {
                    error "Neither Wget nor cURL seem to be available."
                }
                if {$verbose>=2} {
                    message "Using cURL $major.$minor as the download tool."
                }

                # Not specifying "--create-dirs" equals Wget's "--no-directories".
                # "--fail" enables Wget's default behavior for cURL to fail on HTTP errors instead of writing the error page to the output.
                # "--remote-name" enables Wget's default behavior for cURL to output to a file named like the remote file instead of stdout.
                set dl_opt_def {--retry 0 --connect-timeout 30 --ftp-pasv --fail --remote-name}
                set dl_opt_quiet {--silent}
                set dl_opt_time {--remote-time --time-cond}
            }
            default {
                error "Invalid download tool."
            }
        }

        if {$verbose>=1} {
            set dl_opt "$dl_opt_cert $dl_opt_def"
        } else {
            # Note: cURL's "--silent" option is positional, it needs to come first to work!
            set dl_opt "$dl_opt_quiet $dl_opt_cert $dl_opt_def"
        }
    }

    if {$verbose>=1} {
        set dl_pipe ">@stdout 2>@stderr"
    } else {
        set dl_pipe ""
    }

    set cachedir [getPrepackedCacheDir]
    set atoms [parsePrepackedName $fullname]
    set fullversion [lindex $atoms 1]
    set mainversion [lindex [split $fullversion '-'] 0]

    foreach ext [list lst tar] {
        set namegz $fullname.$ext.gz
        set namebz2 $fullname.$ext.bz2

        if { $ext=="tar" } {
            if { ! [info exists OPT_PEDANTIC] && ( [file exists [file join $cachedir $namegz]] || [file exists [file join $cachedir $namebz2]] ) } {
                continue
            }
            message "Trying to retrieve '$fullname.$ext.{gz,bz2}'."
        } else {
            if { ! [info exists OPT_PEDANTIC] && [file exists [file join $cachedir $fullname.$ext]] } {
                continue
            }
            message "Trying to retrieve '$fullname.$ext'."
        }

        set success 0
        set urlTried [list]
        foreach src $prepackedsrcs {
            set baseurl "$src/[lindex $atoms 0]/$mainversion/"
            lappend urlTried [urlWithoutPassword $baseurl/$fullname.$ext]

            # Only enable time comparison with HTTP; with FTP it would require a listing which might not be supported.
            if { [string first http $baseurl] == 0 } {
                set dl_opt_all "$dl_opt $dl_opt_time"
            } else {
                set dl_opt_all "$dl_opt"
            }

            # cURL does not support Wget's "--directory-prefix", so manually change to the output directory.
            set origdir [pwd]
            cd $cachedir
            if { $ext=="tar" } {
                # cURL requires the name of the existing file for time stamp comparison.
                set dl_exec [subst [string map {"--time-cond" "--time-cond $namegz"} "exec $dl_cmd $dl_opt_all $baseurl/$namegz $dl_pipe"] ]
                set failed [catch $dl_exec err]

                if {$failed} {
                    set dl_exec [string map {".gz" ".bz2"} $dl_exec]
                    set failed [catch $dl_exec err]
                }

                cd $origdir

                if {$failed} {
                    # ignore error; perhaps another base url will succeed
                    message "Warning: Failed to retrieve '$fullname.$ext.{gz,bz2}' from '[urlWithoutPassword $baseurl/$fullname.$ext.{gz,bz2}]'. Use '--verbose 2' to get more information. Note: You may safely ignore this warning, if no error follows."
                } else {
                    if { [file exists [file join $cachedir $namegz]] } {
                        message "Retrieved file from '[urlWithoutPassword $baseurl/$fullname.$ext.gz]'."
                        set success 1
                        break
                    }
                    if { [file exists [file join $cachedir $namebz2]] } {
                        message "Retrieved file from '[urlWithoutPassword $baseurl/$fullname.$ext.bz2]'."
                        set success 1
                        break
                    }
                }
            } else {
                # cURL requires the name of the existing file for time stamp comparison.
                set dl_exec [subst [string map {"--time-cond" "--time-cond $fullname.$ext"} "exec $dl_cmd $dl_opt_all $baseurl/$fullname.$ext $dl_pipe"] ]
                set failed [catch $dl_exec err]

                cd $origdir

                if {$failed} {
                    # ignore error; perhaps another base url will succeed
                    message "Warning: Failed to retrieve '$fullname.$ext' from '[urlWithoutPassword $baseurl/$fullname.$ext]'. Use '--verbose 2' to get more information. Note: You may safely ignore this warning, if no error follows."
                } else {
                    if { [file exists [file join $cachedir "$fullname.$ext"] ] } {
                        message "Retrieved file from '[urlWithoutPassword $baseurl/$fullname.$ext]'."
                        set success 1
                        break
                    }
                }
            }
        }
        if { !$success } {
            if { $ext=="tar" } {
                message "Error retrieving '$fullname.$ext.{gz,bz2}' from multiple sources ($urlTried.{gz,bz2}); use '--verbose 2' to get more information."
            } else {
                message "Error retrieving '$fullname.$ext' from multiple sources ($urlTried); use '--verbose 2' to get more information."
            }
            error "Download failed."
        }
    }
}

# get the list of files contained in the prepacked
proc getPrepackedList {fullname} {
    set cachedir [getPrepackedCacheDir];
    set lst [file join $cachedir "$fullname.lst"]
    if { ! [file exists $lst ] } {
        message "Error missing $lst";
        error "prepack problem";
    }
    set fp [open $lst]
    set dat [read $fp];
    close $fp;
    set filelist [split [string trim $dat] "\n"];
    set line 0;
    set error 0;
    # validate list
    foreach x $filelist {
        incr line;
        if { [regexp {^[a-zA-Z0-9][+-_a-zA-Z0-9./]*[+a-zA-Z0-9]$} $x] } {
            # ok
        } else {
            message "Warning: line $line of filelist $lst: unusual path $x";
            incr error;
        }
    }
    if { $error } {
        message "Note: Filepaths must start and end with an alphanumeric.";
        message "Note: they are only allowed to contain the following characters: +-_a-zA-Z0-9./";
        message "Note: If you need other characters in your path, think carefully before adding them in helpers.tcl";
        error "errors in filelist";
    }
    return $filelist
}

# get the path to the local archive in the cache dir
proc getPrepackedLocalArchive {fullname} {
    set cachedir [getPrepackedCacheDir]
    set archive [file join $cachedir "$fullname.tar.gz"]
    if { ! [file exists $archive] } {
        set archive [file join $cachedir "$fullname.tar.bz2"]
    }
    return $archive
}

proc getPrepackedLocalArchiveRelToRoot {fullname} {
    set archive [file join [getPrepackedCacheDirRelToRoot] "$fullname.tar.gz"]
    if { ! [file exists $archive] } {
        set archive [file join [getPrepackedCacheDirRelToRoot] "$fullname.tar.bz2"]
    }
    return $archive
}

proc multipleBaseNames {files} {
    foreach f $files {
        set t [file tail $f]
        if {[info exists used($t)]} {
            set multiples($t) 1
        }
        set used($t) 1
    }
    return [array names multiples]
}

proc usesSubDirs {files} {
    foreach f $files {
        if {[file tail $f] != $f} {
            return 1
        }
    }
    return 0
}


#############################################################
####### End of helpers
#############################################################

proc readGlobalConfig {} {
   global HELPERSDIR
####
#### source global configuration first
#### to allow the Package file to override default settings.
####
    foreach config [concat \
                     [list [file join $HELPERSDIR BuildSystemConfig]] \
                     [glob -nocomplain [file join $HELPERSDIR BuildSystemConfig.d *] ] \
                  ] \
    {
        if { ![string match *~ $config] && [file isfile $config] } {
            if {[catch { namespace eval Config "source {$config}" }]} {
                 message "Error sourcing configuration '$config'."
                 error "configuration error"
            }
        }
    }
}

####
#### read config stuff
####
#### The idea is to have two namespaces available:
####   - All Package files will be evaluated in ::Config::
####      - all valid config vars will be in ::Config:: and nothing more
####      - Therefore, if there are more vars this is an error
####      - If you use temporary vars inside a namespace eval Config,
####        you have to unset them. See below for an example
####   - All supporting vars used will live in ::Run:: It could be used to
####     pass stuff to the procs doing the real work.
####      - rootdir
####      - reldir
####      - pathToRoot
####      - ...
####
#### This proc will create these namespaces, source BuildSystemConfig and Package
#### and check if things are ok. In case of error it will report and exit.
####
proc readConfig {rootdir dir} {
   global HELPERSDIR;

   global configvars;
   global simpleconfigvars;
   global archs;

   global configcache

   global licensecheck
   global opt_test

#### clean up old namespaces
   namespace eval Run {};
   namespace delete Run;

   namespace eval Config {};
   namespace delete Config;

#### put some stuff into Run and all config vars into Config
   namespace eval Run "variable rootdir $rootdir";
   namespace eval Run "variable reldir $dir";

   if { [info exists configcache($rootdir,$dir)] } {
       namespace eval Config $configcache($rootdir,$dir)
       return
   }

#### source config in Package dir
   set pwd [pwd];
   cd $rootdir

   readGlobalConfig

if {$licensecheck == 0} {
    namespace eval Config {
        lappend BASE_DEFINES "NO_LICENSE_CHECK";
    }
}

   cd $dir;
####
#### now try to guess some defaults
####
# the default for INCSRC/INCSRCINTERN is
#   - to put *.h *.hpp in INCSRCINTERN except for
#       - explicitly statet otherwise
#       - all files which are in INCSRC, they are filtered out below
   namespace eval Config {
####
#### source Package in package dir
####
       if { [catch {source [getPackageFileName]}]} {
           message "Error: problems with $::Run::reldir/[getPackageFileName]. Try 'tclsh $::Run::reldir/[getPackageFileName]' to find out more.";
           return;
       }
   }

#### Validate variables
   regsub -all "::Config::" [info vars ::Config::*] "" tmp
   foreach x $tmp {
       if { ![isValidVariable $x] } {
           message "Error in $Run::reldir/[getPackageFileName]: $x is not used"
           error "Fatal"
       }
   }

#### Set defaults
   namespace eval Config {
       if { ![info exists PACKAGE] } {
           set PACKAGE [file tail $::Run::reldir]
       }
       if { ![info exists SRC] } {
           set SRC [lsort [glob -nocomplain *.cpp *.c]]
       }
       if { ![info exists TESTSRC] } {
           set TESTSRC [list]
       }
       if { ![info exists INCSRCINTERN] } {
           set INCSRCINTERN [lsort [glob -nocomplain *.h *.hpp]]
       }
       if { ![info exists TESTINCSRC] } {
           set TESTINCSRC [list]
       }
       if { ![info exists QRCSRC] } {
           set QRCSRC [lsort [glob -nocomplain *.qrc]]
       }
       if { ![info exists UICSRC] } {
           set UICSRC [lsort [glob -nocomplain *.ui]]
       }
       if { ![info exists MOCSRC] } {
           set MOCSRC [list]
           foreach x [lsort [glob -nocomplain *.h *.hpp]] {
               set fp [open $x];
               if {[regexp Q_OBJECT [read $fp] ]} {
                   lappend MOCSRC $x;
               }
               close $fp;
               unset fp;
           }
       }
       if { ![info exists ROCSRC] } {
           set ROCSRC [list]
           foreach x [lsort [glob -nocomplain *.h *.hpp]] {
               set fp [open $x];
               # check if file needs roc-prebuild step
               if {[regexp VS_RELAY_CLASS [read $fp] ]} {
                   lappend ROCSRC $x;
               }
               close $fp;
               unset fp;
           }
       }
       if { ![info exists BISONSRC] && ![info exists FLEXSRC] } {
           set FLEXSRC [lsort [glob -nocomplain *.l]]
           set BISONSRC [lsort [glob -nocomplain *.y]]
           foreach x $BISONSRC {
               set idx [lsearch $FLEXSRC [file rootname $x].l]
               if {$idx >= 0} {
                   set FLEXSRC [lreplace $FLEXSRC $idx $idx]
               }
           }
       }
       if { ![info exists FLEXSRC] } {
           set FLEXSRC [list]
       }
       if { ![info exists BISONSRC] } {
           set BISONSRC [list]
       }
       if { ![info exists GSOAPSRC] } {
           set GSOAPSRC [lsort [glob -nocomplain *.gsoap]]
       }
       if { ![info exists CUDASRC] } {
           set CUDASRC [lsort [glob -nocomplain *.cu]]
       }
       if { ![info exists SHARE] } {
           set SHARE [lsort [glob -nocomplain share/resources/*.rc]]
       }
       if { ![info exists TESTSHARE] } {
           set TESTSHARE [list]
       }


# remember to override the dox after all expansions took place
       if {![info exists DOX] && ![info exists DOXINTERN]} {
            set overridedox 1;
            set DOX [glob -nocomplain *.dox];
            set DOXINTERN [list];
       }
# now reset vars if not overridden in Package
       if {![info exists DOX]} {
            set DOX [list];
       }
       if {![info exists DOXINTERN]} {
            set DOXINTERN [list];
       }

# explicitly check of deprecated aliases "Amira" and "amiracom"
       if {[info exists LIBS]} {
           if { [lsearch $LIBS "Amira"] >= 0 } {
               message "Warning in $Run::reldir/[getPackageFileName]: using package alias Amira -> hxcore is deprecated."
           }
           if { [lsearch $LIBS "amiracom"] >= 0 } {
               message "Warning in $Run::reldir/[getPackageFileName]: using package alias amiracom -> hxcom is deprecated."
           }
       }


# aliasing of package names for Avizo rebranding
       if {![info exists PACKAGE]} {
            set PACKAGE ""
       }
       if {![info exists LIBS]} {
            set LIBS [list]
       }

       debugmessage 5 "SRC: $SRC";
       debugmessage 5 "INCSRCINTERN: $INCSRCINTERN";
       debugmessage 5 "MOCSRC: $MOCSRC";
       debugmessage 5 "QRCSRC: $QRCSRC";
       debugmessage 5 "UICSRC: $UICSRC";
       debugmessage 5 "ROCSRC: $ROCSRC";
       debugmessage 5 "BISONSRC: $BISONSRC";
       debugmessage 5 "FLEXSRC: $FLEXSRC";
       debugmessage 5 "SHARE: $SHARE";
   }

#### We cd pack to the BUILDROOT dir
#### the rest is run in rootdir
   cd $rootdir;
#################################
#### Glob necessary variables, including variables of type VAR-Alias.
#### Aliases are expanded afterwards to avoid multiple globbing
####
   foreach x [info vars ::Config::*] {
        set strippedconfig [string range $x 10 end]
        set var [lindex [split $strippedconfig -] 0]
        if { [lsearch $configvars $var] >= 0 || [lsearch $simpleconfigvars $var] >= 0 } {
            set ${x} [globList $::Run::reldir [subst $\{${x}\}]]
        }
   }

   namespace eval Config {
       if { [file exists [file join $::Run::reldir version.cpp]] && [lsearch $SRC version.cpp] < 0 } {
           lappend SRC version.cpp
       }
####
#### filter out INCSRC from INCSRCINTERN
####
        if { ![info exists INCSRC] } {
            set INCSRC [list]
        }
        set INCSRCINTERN [filterout $INCSRCINTERN $INCSRC]

# now set the default for DOX and DOXINTERN if none of
# the two is set in the Package file
# the default for DOX is to use all INCSRC and *.dox files
# the default fot DOXINTERN is all SRC and INCSRCINTERN
# NODOX can be used to filter out some files from doxygen
        if {[info exists overridedox]} {
            foreach x [concat $INCSRC] {
                lappend DOX $x
            }
            foreach x [concat $SRC $INCSRCINTERN] {
                lappend DOXINTERN $x
            }
            unset overridedox
        }

        if { ![info exists NODOX] } {
            set NODOX [list]
        }
        set DOX [filterout $DOX $NODOX]
        set DOXINTERN [filterout $DOXINTERN $NODOX]

        debugmessage 5 "DOX: $DOX"
        debugmessage 5 "DOXINTERN: $DOXINTERN"
####
#### if ONLY is empty but EXCLUDEARCH is set create ONLY based on exclude arch.
#### if arch is not excluded append it to ONLY
####
        if { ![info exists ONLY] } {
            set ONLY [list]
        }
        if { ![info exists EXCLUDEARCH] } {
            set EXCLUDEARCH [list]
        }
        if { $ONLY == "" && $EXCLUDEARCH != "" } {
            foreach a $archs {
                if { [lsearch $EXCLUDEARCH $a] == -1 } {
                    lappend ONLY $a
                }
            }
        }
        foreach v {
            TYPE CONSOLE INCLUDES COPY COPYINTERN COPYDEV SYMLINK
            PREPACKED SHAREDEV SHAREINTERN SHARESECURE
            DEFINES

            BASE_DEFINES
            LIBPATH
            BASE_INCLUDES
            BASE_LIBPATH
            LINKOPTIONS

            LIBS-Win32VC8
            LIBS-Win32VC8-Debug
            LIBS-Win32VC8-Optimize
            BASE_DEFINES-Win32VC8
            BASE_DEFINES-Win32VC8-Debug
            BASE_DEFINES-Win32VC8-Optimize
            DEFINES-Win32VC8
            LIBPATH-Win32VC8
            BASE_LIBPATH-Win32VC8
            BASE_LIBPATH-Win32VC8-Debug
            BASE_LIBPATH-Win32VC8-Optimize
            WINDOWS_EXPORT_DEFINITION-Win32VC8
            SRC-Win32VC8
            MOCSRC-Win32VC8
            ROCSRC-Win32VC8
            COPY-Win32VC8
            COPY-Win32VC8-Debug
            COPY-Win32VC8-Optimize
            COPYDEV-Win32VC8
            COPYDEV-Win32VC8-Debug
            COPYDEV-Win32VC8-Optimize
            COPYINTERN-Win32VC8
            COPYINTERN-Win32VC8-Debug
            COPYINTERN-Win32VC8-Optimize

            LIBS-Win32VC9
            LIBS-Win32VC9-Debug
            LIBS-Win32VC9-Optimize
            BASE_DEFINES-Win32VC9
            BASE_DEFINES-Win32VC9-Debug
            BASE_DEFINES-Win32VC9-Optimize
            DEFINES-Win32VC9
            LIBPATH-Win32VC9
            BASE_LIBPATH-Win32VC9
            BASE_LIBPATH-Win32VC9-Debug
            BASE_LIBPATH-Win32VC9-Optimize
            WINDOWS_EXPORT_DEFINITION-Win32VC9
            SRC-Win32VC9
            MOCSRC-Win32VC9
            ROCSRC-Win32VC9
            COPY-Win32VC9
            COPY-Win32VC9-Debug
            COPY-Win32VC9-Optimize
            COPYDEV-Win32VC9
            COPYDEV-Win32VC9-Debug
            COPYDEV-Win32VC9-Optimize
            COPYINTERN-Win32VC9
            COPYINTERN-Win32VC9-Debug
            COPYINTERN-Win32VC9-Optimize

            LIBS-Win64VC9
            LIBS-Win64VC9-Debug
            LIBS-Win64VC9-Optimize
            BASE_DEFINES-Win64VC9
            BASE_DEFINES-Win64VC9-Debug
            BASE_DEFINES-Win64VC9-Optimize
            DEFINES-Win64VC9
            LIBPATH-Win64VC9
            BASE_LIBPATH-Win64VC9
            BASE_LIBPATH-Win64VC9-Debug
            BASE_LIBPATH-Win64VC9-Optimize
            WINDOWS_EXPORT_DEFINITION-Win64VC9
            SRC-Win64VC9
            MOCSRC-Win64VC9
            ROCSRC-Win64VC9
            COPY-Win64VC9
            COPY-Win64VC9-Debug
            COPY-Win64VC9-Optimize
            COPYDEV-Win64VC9
            COPYDEV-Win64VC9-Debug
            COPYDEV-Win64VC9-Optimize
            COPYINTERN-Win64VC9
            COPYINTERN-Win64VC9-Debug
            COPYINTERN-Win64VC9-Optimize
            } {
            if { ![info exists $v] } {
                set $v ""
            }
        }
        if { ![info exists EXECWRAPPER] } {
            if { $TYPE == "bin" } {
                set EXECWRAPPER $PACKAGE
            } else {
                set EXECWRAPPER ""
            }
        }

####
#### handle tests
####
        set SRC [filterout $SRC $TESTSRC]
        set INCSRCINTERN [filterout $INCSRCINTERN $TESTINCSRC]
        set INCSRC [filterout $INCSRC $TESTINCSRC]
        set SHARE [filterout $SHARE $TESTSHARE]
        set SHAREINTERN [filterout $SHAREINTERN $TESTSHARE]
        if { $opt_test } {
            if { [info exists TESTLIBS] } {
                set LIBS [concat $LIBS $TESTLIBS]
            }
            set SRC [concat $SRC $TESTSRC]
            set INCSRCINTERN [concat $INCSRCINTERN $TESTINCSRC]
            set SHAREINTERN [concat $SHAREINTERN $TESTSHARE]
        }
   }

####
#### Expand all aliases: append them to the arch, and clear them.
####
   regsub -all "::Config::" [info vars ::Config::*] "" tmp
   foreach var $tmp {
        set atoms [split $var -]
        if { [llength $atoms] >= 2 } {
            set alias [lindex $atoms 1]
            if { [isAlias $alias] } {
                set from ::Config::$var
                foreach arch [expandAliases $alias] {
                    lset atoms 1 $arch
                    set to ::Config::[join $atoms -]
                    if { ![info exists $to] } {
                        set $to [list]
                    }
                    set $to [concat [subst $\{$to\}] [subst \$\{$from\}]]
                }
                set $from ""
            }
        }
   }

#### Validate the contents of some variables.
   if { [info exists ::Config::DATA] } {
       message "Warning in $Run::reldir/[getPackageFileName]: DATA is deprecated.  Use SHARE instead."
       set ::Config::SHARE [concat $::Config::SHARE $::Config::DATA]
   }

   set multiples [multipleBaseNames $Config::SRC]
   if { [llength $multiples] } {
       message "Error in $Run::reldir/[getPackageFileName]: basenames of files in SRC must be unique, found multiple basename(s): $multiples"
       error "Fatal"
   }
   foreach x $Config::SRC {
        if {[file pathtype $x] == "relative"} {
            set start [lindex [file split $x] 0]
            if {$start == ".."} {
                message "Warning in $Run::reldir/[getPackageFileName]: SRC contains a path pointing outside the package directory, which may cause trouble; found $x"
            }
        } else {
            message "Error in $Run::reldir/[getPackageFileName]: SRC must only contain relativ paths, found $x"
            error "Fatal"
        }
   }

   if { [usesSubDirs $Config::MOCSRC] } {
       message "Error in $Run::reldir/[getPackageFileName]: subdirs are not allowed in MOCSRC"
       error "Fatal"
   }
   if { [usesSubDirs $Config::QRCSRC] } {
       message "Error in $Run::reldir/[getPackageFileName]: subdirs are not allowed in QRCSRC"
       error "Fatal"
   }
   if { [usesSubDirs $Config::UICSRC] } {
       message "Error in $Run::reldir/[getPackageFileName]: subdirs are not allowed in UICSRC"
       error "Fatal"
   }
   if { [usesSubDirs $Config::ROCSRC] } {
       message "Error in $Run::reldir/[getPackageFileName]: subdirs are not allowed in ROCSRC"
       error "Fatal"
   }
   if { [usesSubDirs $Config::FLEXSRC] } {
       message "Error in $Run::reldir/[getPackageFileName]: subdirs are not allowed in FLEXSRC"
       error "Fatal"
   }
   if { [usesSubDirs $Config::BISONSRC] } {
       message "Error in $Run::reldir/[getPackageFileName]: subdirs are not allowed in BISONSRC"
       error "Fatal"
   }
   if { [usesSubDirs $Config::GSOAPSRC] } {
       message "Error in $Run::reldir/[getPackageFileName]: subdirs are not allowed in GSOAPSRC"
       error "Fatal"
   }
   if { [usesSubDirs $Config::CUDASRC] } {
       message "Error in $Run::reldir/[getPackageFileName]: subdirs are not allowed in CUDASRC"
       error "Fatal"
   }
   if { $::Config::TYPE == "staticlib" } {
       message "Warning in $Run::reldir/[getPackageFileName]: TYPE staticlib is used. This is an experimental feature and not supported on windows. It may be removed in the future"
   } elseif { $::Config::TYPE == "" || $::Config::TYPE == "bin" || $::Config::TYPE == "copy" || $::Config::TYPE == "python" } {
        # ok
   } else {
       message "Error in $Run::reldir/[getPackageFileName]: TYPE must be empty (-> shared lib), 'bin' or 'copy'; found '$::Config::TYPE'."
       error "invalid TYPE"
   }
   if { [info exist ::Config::EXCLUDEISA] } {
       message "Error in $Run::reldir/[getPackageFileName]: EXCLUDEISA must be empty.  Use EXCLUDEISA only for a specific architecture, for example EXCLUDEISA-MacX."
       error "invalid variable EXCLUDEISA"
   }
   if { $::Config::CONSOLE != "1" && $::Config::CONSOLE != "" } {
       message "Error in $Run::reldir/[getPackageFileName]: CONSOLE must either be '1' or empty"
       error "invalid content in CONSOLE"
   }
   foreach x $::Config::BISONSRC {
       set prefix [lindex $x 1];
       set nocompile [lindex $x 2];
       set target [lindex $x 3];

       if {$prefix != ""} {
           message "Error: BISONSRC's support for prefix was removed.  Use %name-prefix instead."
           error "syntax error"
       }

       if {$nocompile != ""} {
           message "Error: BISONSRC's support for nocompile was removed."
           error "syntax error"
       }

       if {$target != ""} {
           message "Error: BISONSRC's support for target was removed."
           error "syntax error"
       }
   }
### end of if validate

   cd $pwd;

### cache content of namespace for later reuse
   regsub -all "::Config::" [info vars ::Config::*] "" tmp;
   set store ""
   foreach x $tmp {
       append store "set $x {[subst \${::Config::$x}]}\n"
   }
   set configcache($rootdir,$dir) $store
}

####
#### helper function to filter out the second list from the first one
####
proc filterout {entries filter} {
    set result [list]
    foreach e $entries {
        if {[lsearch $filter $e] < 0} {
            lappend result $e
        }
    }
    return $result
}

################################################################
# functions to create lists of product files
################################################################
####
#### Check if current package is declared as internal package
####
proc isPackageInternal {} {
    global intern_label_list
    if { ![info exists intern_label_list] } {
        return 0
    }

    if { ![info exists ::Config::LABELS] } {
        return 0
    }

    foreach l $::Config::LABELS {
        if  {[lsearch $intern_label_list $l] >= 0} {
            return 1
        }
    }

    return 0
}

####
#### iterate over variables and concatenate values of
#### existing variables to a single list
####
proc concatExisting {args} {
    set l [list]
    foreach var $args {
        if {[info exists $var]} {
            set l [concat $l [subst $\{$var\}]]
        }
    }
    return $l
}

####
#### append product files that are created by a package to the
#### global list of product files.
####
#### dir is a relative path to rootdir.
####
proc getDistFiles [list rootdir dir [list opt [list]]] {
    global bindistfiles
    global distonly_bindistfiles
    global devdistfiles
    global distonly_devdistfiles
    global interndistfiles
    global distonly_interndistfiles
    global datadistfiles
    global auxfiles
    global aliasedTo
    global copyrights

    message "Processing Project $dir"

    array set param [concat [list archs [list] config Optimize headers selection separatedata 0] $opt]

    readConfig $rootdir $dir
    set productdir [file join $rootdir product]

    message "... archs: $param(archs)"
    message "... config: $param(config)"
####
#### we gather everthing in two lists
####    - bindistfiles
####    - devdistfiles
####
    foreach a $param(archs) {
        set loc_bindistfiles [list]
        set loc_distonly_bindistfiles [list]
        set loc_devdistfiles [list]
        set loc_distonly_devdistfiles [list]
        set loc_datadistfiles [list]

# Add doc directory before ignore checks, because doc files might be included
# indirectly by other packages.  For example, the usersguide includes hxtracking.
        set olddir [pwd]
        cd $productdir
        set userdocfiles [glob -nocomplain share/doc/*/$::Config::PACKAGE/*]
        if {[isPackageInternal]} {
             set interndistfiles($a) [concat $interndistfiles($a) $userdocfiles]
        } elseif {[info exists ::Config::DOCTYPE] && $::Config::DOCTYPE == "dev"} {
            set devdistfiles($a) [concat $devdistfiles($a) $userdocfiles]
        } else {
            if {[info exists ::Config::DOCTYPE] && $::Config::DOCTYPE != "bin"} {
                 message "Error: Unknown doctype '$::Config::DOCTYPE'"
                 error "Fatal"
            }
            set bindistfiles($a) [concat $bindistfiles($a) $userdocfiles]
        }
        cd $olddir

        if {![passLabelFilter]} {
            msgout 1 "... ignoring package on ALL"
            continue
        }
        if {${::Config::ONLY} != ""} {
            if {[lsearch [expandAliases ${::Config::ONLY}] $a] < 0} {
                message "... ignoring on $a"
                continue
            }
        }
        if {[info exists ::Config::COPYRIGHT] && ![isPackageInternal]} {
            lappend copyrights($::Config::COPYRIGHT) $::Config::PACKAGE
        }
        if {$::Config::TYPE == "bin"} {
            set base $::Config::PACKAGE
            switch -glob $a {
                Win* {
                    lappend loc_bindistfiles bin/arch-$a-$param(config)/${base}.exe
                    lappend auxfiles($a) bin/arch-$a-$param(config)/${base}.exp
                    lappend auxfiles($a) bin/arch-$a-$param(config)/${base}.idb
                    lappend auxfiles($a) bin/arch-$a-$param(config)/${base}.ilk
                    lappend auxfiles($a) bin/arch-$a-$param(config)/${base}.lib
                    lappend auxfiles($a) bin/arch-$a-$param(config)/${base}.pdb
                    
                    set olddir [pwd]
                    cd $productdir
                    set auxfiles($a) [concat $auxfiles($a) [glob -nocomplain bin/arch-$a-$param(config)/${base}*ib_*]]
                    cd $olddir
                }
                default {
                    lappend loc_bindistfiles bin/arch-$a-$param(config)/${base}
                }
            }
        } elseif {$::Config::TYPE == "copy"} {
        } elseif {$::Config::TYPE == "python"} {
            set base $::Config::PACKAGE
            switch -glob $a {
                Win* {
                    lappend loc_bindistfiles bin/arch-$a-$param(config)/_${base}.pyd
                    lappend auxfiles($a) bin/arch-$a-$param(config)/_${base}.exp
                    lappend auxfiles($a) bin/arch-$a-$param(config)/_${base}.idb
                    lappend auxfiles($a) bin/arch-$a-$param(config)/_${base}.ilk
                    lappend auxfiles($a) bin/arch-$a-$param(config)/_${base}.lib
                    lappend auxfiles($a) bin/arch-$a-$param(config)/_${base}.pdb
                    lappend auxfiles($a) bin/arch-$a-$param(config)/${base}.exp
                    lappend auxfiles($a) bin/arch-$a-$param(config)/${base}.idb
                    lappend auxfiles($a) bin/arch-$a-$param(config)/${base}.ilk
                    lappend auxfiles($a) bin/arch-$a-$param(config)/${base}.lib
                    lappend auxfiles($a) bin/arch-$a-$param(config)/${base}.pdb
                    
                    set olddir [pwd]
                    cd $productdir
                    set auxfiles($a) [concat $auxfiles($a) [glob -nocomplain bin/arch-$a-$param(config)/${base}*ib_*]]
                    cd $olddir
                }
                default {
                    lappend loc_bindistfiles lib/arch-$a-$param(config)/_${base}.so
                }
            }
        } else {
            if {[info exists ::Config::TARGET]} {
                set base $::Config::TARGET
            } else {
                set base $::Config::PACKAGE
            }
            switch -glob $a {
                MacX* {lappend loc_bindistfiles lib/arch-$a-$param(config)/lib${base}.dylib}
                Win* {
                    lappend loc_bindistfiles bin/arch-$a-$param(config)/${base}.dll
                    if {$param(headers) == "all" || [llength ${::Config::INCSRC}] != 0} {
                        lappend loc_devdistfiles bin/arch-$a-$param(config)/${base}.lib
                    }
                    lappend interndistfiles($a) bin/arch-$a-$param(config)/${base}.lib
                    lappend auxfiles($a) bin/arch-$a-$param(config)/${base}.exp
                    lappend auxfiles($a) bin/arch-$a-$param(config)/${base}.idb
                    lappend auxfiles($a) bin/arch-$a-$param(config)/${base}.ilk
                    lappend auxfiles($a) bin/arch-$a-$param(config)/${base}.pdb
                    
                    set olddir [pwd]
                    cd $productdir
                    set auxfiles($a) [concat $auxfiles($a) [glob -nocomplain bin/arch-$a-$param(config)/${base}*ib_*]]
                    cd $olddir
                }
                default {lappend loc_bindistfiles lib/arch-$a-$param(config)/lib${base}.so}
            }
        }

        foreach {src dest} [concatExisting ::Config::COPY ::Config::COPY-$a ::Config::COPY-$a-$param(config)] {
            set exp [expandCopy $src $dest]
            lappend loc_bindistfiles [lindex $exp 1]
            foreach x [lindex $exp 2] {
                lappend loc_bindistfiles $x
            }
        }

        foreach {src dest} [concatExisting ::Config::SYMLINK ::Config::SYMLINK-$a ::Config::SYMLINK-$a-$param(config)] {
            lappend loc_bindistfiles $dest
        }

        foreach {exec} $::Config::EXECWRAPPER {
            switch -glob $a {
                Win* { }
                default {
                    lappend loc_bindistfiles bin/$exec
                    lappend loc_bindistfiles bin/arch
                }
            }
        }

        foreach {src dest} [concatExisting ::Config::COPYDEV ::Config::COPYDEV-$a ::Config::COPYDEV-$a-$param(config)] {
            set exp [expandCopy $src $dest]
            lappend loc_devdistfiles [lindex $exp 1]
            foreach x [lindex $exp 2] {
                lappend loc_devdistfiles $x
            }
        }

        foreach {src dest} [concatExisting ::Config::COPYINTERN ::Config::COPYINTERN-$a ::Config::COPYINTERN-$a-$param(config)] {
            set exp [expandCopy $src $dest]
            lappend interndistfiles($a) [lindex $exp 1]
            foreach x [lindex $exp 2] {
                lappend interndistfiles($a) $x
            }
        }
        
        set loc_bindistfiles [concat $loc_bindistfiles [concatExisting ::Config::SHARE ::Config::NOCVS_SHARE ::Config::NOCVS_SHARE-$a ::Config::NOCVS_SHARE-$a-$param(config)]]
        
        foreach var $::Config::SHARESECURE {
            set dest [file join [file dirname $var ] $::Config::PACKAGE [file tail $var]]
            set loc_bindistfiles [concat $loc_bindistfiles $dest]
        }

        if { [info exists ::Config::SHAREDEV] } {
            set loc_devdistfiles [concat $loc_devdistfiles $::Config::SHAREDEV]
        }
        if { [info exists ::Config::SHAREINTERN] } {
            set interndistfiles($a) [concat $interndistfiles($a) $::Config::SHAREINTERN]
        }

        set loc_bindistfiles [concat $loc_bindistfiles [concatExisting ::Config::DISTEXTRA ::Config::DISTEXTRA-$a ::Config::DISTEXTRA-$a-$param(config)]]

        set loc_devdistfiles [concat $loc_devdistfiles [concatExisting ::Config::DISTEXTRADEV ::Config::DISTEXTRADEV-$a ::Config::DISTEXTRADEV-$a-$param(config)]]

        set interndistfiles($a) [concat $interndistfiles($a) [concatExisting ::Config::DISTEXTRAINTERN ::Config::DISTEXTRAINTERN-$a ::Config::DISTEXTRAINTERN-$a-$param(config)]]

# these are treated in a special way. They are copied to a temporary directory, added to the archives and removed.
        set loc_distonly_bindistfiles [concat $loc_distonly_bindistfiles [concatExisting ::Config::DISTCOPY ::Config::DISTCOPY-$a ::Config::DISTCOPY-$a-$param(config)]]

        set loc_distonly_devdistfiles [concat $loc_distonly_devdistfiles [concatExisting ::Config::DISTCOPYDEV ::Config::DISTCOPYDEV-$a ::Config::DISTCOPYDEV-$a-$param(config)]]

        set distonly_interndistfiles($a) [concat $distonly_interndistfiles($a) [concatExisting ::Config::DISTCOPYINTERN ::Config::DISTCOPYINTERN-$a ::Config::DISTCOPYINTERN-$a-$param(config)]]

# append header files
# Note: we append INCSRC to the internal and the devdist just to be sure they are available
#   in any case in the internal dist
        foreach f $::Config::INCSRC {
            lappend loc_devdistfiles [file join include $::Config::PACKAGE [confineFile $f]]
            lappend interndistfiles($a) [file join include $::Config::PACKAGE [confineFile $f]]
        }
        foreach f $::Config::INCSRCINTERN {
            if { $param(headers) == "all" } {
                lappend loc_devdistfiles [file join include $::Config::PACKAGE [confineFile $f]]
            }
            lappend interndistfiles($a) [file join include $::Config::PACKAGE [confineFile $f]]
        }

# append prepacked stuff
        foreach url [concat [getFilteredPrepacked $::Config::PACKAGE $::Config::PREPACKED {} {}] [getFilteredPrepacked $::Config::PACKAGE $::Config::PREPACKED $a {}] [getFilteredPrepacked $::Config::PACKAGE $::Config::PREPACKED $a $param(config)] ] {
            switch [getPrepackedClassification $url] {
                data {
                    set loc_datadistfiles [concat $loc_datadistfiles [getPrepackedList $url]]
                }
                base {
                    set loc_bindistfiles [concat $loc_bindistfiles [getPrepackedList $url]]
                }
                dev {
                    set loc_devdistfiles [concat $loc_devdistfiles [getPrepackedList $url]]
                }
                interndata
                -
                intern {
                    set interndistfiles($a) [concat $interndistfiles($a) [getPrepackedList $url]]
                }
                default {
                    error "internal error"
                }
            }
        }
        
        if {[isPackageInternal]} {
            set interndistfiles($a) [concat $interndistfiles($a) $loc_bindistfiles]
            set interndistfiles($a) [concat $interndistfiles($a) $loc_datadistfiles]
            set interndistfiles($a) [concat $interndistfiles($a) $loc_devdistfiles]
            set distonly_interndistfiles($a) [concat $distonly_interndistfiles($a) $loc_distonly_bindistfiles]
            set distonly_interndistfiles($a) [concat $distonly_interndistfiles($a) $loc_distonly_devdistfiles]
        } else {
            set bindistfiles($a) [concat $bindistfiles($a) $loc_bindistfiles]
            if { $param(separatedata) } {
                set datadistfiles($a) [concat $datadistfiles($a) $loc_datadistfiles]
            } else {
                set bindistfiles($a) [concat $bindistfiles($a) $loc_datadistfiles]
            }
            set devdistfiles($a) [concat $devdistfiles($a) $loc_devdistfiles]
            set distonly_bindistfiles($a) [concat $distonly_bindistfiles($a) $loc_distonly_bindistfiles]
            set distonly_devdistfiles($a) [concat $distonly_devdistfiles($a) $loc_distonly_devdistfiles]
        }
    }
}

#### Build lists of files that are expected in the product dir.
proc buildProductFileLists {dirs opt} {
    global bindistfiles
    global devdistfiles
    global interndistfiles
    global datadistfiles
    global distonly_bindistfiles
    global distonly_devdistfiles
    global distonly_interndistfiles
    global auxfiles

    foreach a [getRequestedArchs] {
        set bindistfiles($a) [list]
        set devdistfiles($a) [list]
        set interndistfiles($a) [list]
        set datadistfiles($a) [list]
        set distonly_bindistfiles($a) [list]
        set distonly_devdistfiles($a) [list]
        set distonly_interndistfiles($a) [list]
        set auxfiles($a) [list]
    }
    if {[llength $dirs] == 0} {
        runForeachPackage [pwd] getDistFiles $opt
    } else {
        foreach d $dirs {
            if {[string equal [file pathtype $d] "relative"]} {
                set d [file join [pwd] $d]
            }
            runForeachPackage $d getDistFiles $opt
        }
    }
    set runpwd [pwd]
    set productdir [file join [findBuildroot [pwd]] product]
    cd $productdir
#### add special documentation files.
    foreach a [getRequestedArchs] {
        set interndistfiles($a) [concat $interndistfiles($a) [glob -nocomplain share/doc/*/daux] ]
    }
    foreach a [getRequestedArchs] {
        set devdistfiles($a) [concat $devdistfiles($a) [glob-r share/devref] ]
    }
    cd $runpwd
}

