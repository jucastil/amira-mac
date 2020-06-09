###
###  This file provides a method "autoinit" which scans a haeder file and
###  creates or updates a run-time initilization file.
###
###  autoinit takes the following parameters:
###      package_name  - name of an Amira package, e.g. hxfield
###      init_file     - name of the init file, typically */init.cpp
###      header_file   - name of the header file to be scanned
###

# check if file is readable, and read its contents into a variable
# filename: name of the file to be read
# varname: name of the variable that the contents are read into
# returns: 1 if file readable, 0 else
proc autoinit_read_file {filename varname} {
    if [file readable $filename] {
        upvar $varname var
        set f [open $filename r]
        set var [read $f]
        close $f
        return 1
    } else {
        return 0
    }
}

# in the given variable, remove parts contained in a C / C++ comment
proc autoinit_remove_comments {varname} {

    upvar $varname txt

    # remove /* */ pairs
    regsub -all {/\*.*?\*/} $txt "" txt

    # remove // to next line break
    regsub -all {//.*?\n} $txt "" txt

    # remove // to end of file
    regsub -all {//.*?$} $txt "" txt
}

# search header file for certain macros, and add initialization commands
#    in the init file accordingly.
proc autoinit {package_name header_file init_modified_varname includes_varname body_varname} {
    upvar $init_modified_varname init_modified
    upvar $includes_varname includes
    upvar $body_varname body

    set head_macros {
        MC_ABSTRACT_HEADER
        MC_ABSTRACT_HEADER2
        MC_HEADER
        MC_HEADER2
        HX_ABSTRACT_HEADER
        HX_HEADER
    }

    set header_exists [autoinit_read_file $header_file header]
    if {!$header_exists} {
        message "$header_file does not exist"
        return
    }

    if { [string first NO_AUTO_INIT $header] >= 0 } {
        message "no auto init for $header_file"
        return
    }

    # remove comments from header file so they will not be searched
    autoinit_remove_comments header

    # scan through header file, look for each occurance of one of the
    #   macros specfied in head_macros
    foreach macro $head_macros {
        set pos -1
        while 1 {
            incr pos 1
            # is the macro there?
            set pos [string first "$macro" $header $pos]
            if {$pos == -1} {break;}

            # match regular expression, and extract the class name
            if {![regexp -start $pos \
                      "$macro *\\((\[^\)\]*)\\)" $header all class_name]} {
                set x [string range $header $pos [expr $pos + 100]]
                incr pos 1
                continue
            }

            if {$class_name == "className"} {
                continue
            }

            set incl "\#include \"[file tail $header_file]\""
            if { [string first $incl $includes] == -1 } {
                set includes "$incl\n$includes"
            }

            set class_name [string trim ${class_name}]
            set classinit "    ${class_name}::initClass();"
            if { [string first $classinit $body] == -1 } {
                set body "$classinit\n$body"
            }
            set init_modified 1
        }
    }
}

proc custominit {init_modified_varname package_name custominit_file
                    includes_varname custompreinit_varname custominit_varname
                    customfinish_varname} {
    upvar $init_modified_varname init_modified
    upvar $includes_varname includes
    upvar $custompreinit_varname custompreinit
    upvar $custominit_varname custominit
    upvar $customfinish_varname customfinish

    set custominit_exists [file exists $custominit_file]
    if { $custominit_exists } {
        if { ![autoinit_read_file $custominit_file custominit_content] } {
            message "Error: Failed to read $custominit_file"
            return
        }

        set init_modified 1

        set includes "#include \"custominit.h\"\n$includes"
        if { [string first {void custompreinit()} $custominit_content] >= 0 } {
            set custompreinit "\n    custompreinit();\n"
        }
        if { [string first {void custominit()} $custominit_content] >= 0 } {
            set custominit "    custominit();\n"
        }
        if { [string first {void customfinish()} $custominit_content] >= 0 } {
            set customfinish "    customfinish();\n"
        }
    }
}

proc autoinitall { package_name dir headers } {
    set init_modified 0

    set includes ""
    set body ""
    foreach x $headers {
        set header [file join $dir $x]
        autoinit $package_name $header init_modified includes body
    }

    set custompreinit ""
    set custominit ""
    set customfinish ""
    set custominit_file [file join $dir custominit.h]
    custominit init_modified $package_name $custominit_file includes custompreinit custominit customfinish

    set init [string map [list \
                            @@PACKAGENAME@@ ${package_name} \
                            @@INCLUDES@@ $includes \
                            @@BODY@@ $body \
                            @@CUSTOMPREINIT@@ $custompreinit \
                            @@CUSTOMINIT@@ $custominit \
                            @@CUSTOMFINISH@@ $customfinish \
                        ] \
{// AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY.  Place custom code in custominit.h.
@@INCLUDES@@

extern "C"
#ifdef _WIN32
__declspec(dllexport)
#endif
void amirapackage_@@PACKAGENAME@@_init()
{
    static bool isInitialized = false;
    if (isInitialized)
      return;

    isInitialized = true;
@@CUSTOMPREINIT@@
@@BODY@@
@@CUSTOMINIT@@}


extern "C"
#ifdef _WIN32
__declspec(dllexport)
#endif
void amirapackage_@@PACKAGENAME@@_finish()
{
    static bool isFinished = false;
    if (isFinished)
      return;

    isFinished = true;

@@CUSTOMFINISH@@}

#if defined(_WIN32)
#  include <windows.h>
BOOL WINAPI DllMain(
    __in  HINSTANCE hinstDLL,
    __in  DWORD fdwReason,
    __in  LPVOID lpvReserved
    )
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        amirapackage_@@PACKAGENAME@@_init();
        break;
    case DLL_PROCESS_DETACH:
        amirapackage_@@PACKAGENAME@@_finish();
        break;
    default:
        ;
    }
    return true;
}
#endif

#if defined(__GNUC__)
void __attribute__((constructor)) soconstructor_@@PACKAGENAME@@() {
    amirapackage_@@PACKAGENAME@@_init();
}

void __attribute__((destructor)) sodestructor_@@PACKAGENAME@@() {
    amirapackage_@@PACKAGENAME@@_finish();
}
#endif
} ]

    set init_file [ file join $dir init.cpp ]
    if { $init_modified } {
        set init_file_exists [autoinit_read_file $init_file oldinit]
        if { $init_file_exists } {
            if { [string compare $init $oldinit] == 0 } {
                return
            }
            message "updated init.cpp"
        } else {
            message "created init.cpp"
        }
        set f [open $init_file w]
        puts -nonewline $f $init
        close $f
    } else {
        if { [file exists $init_file] } {
            message "deleted init.cpp"
            file delete -force $init_file
        }
    }
}
