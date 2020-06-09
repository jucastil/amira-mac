/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup amiramesh amiramesh
/// @{
#ifndef HX_PARSE_UTILS_H
#define HX_PARSE_UTILS_H

#if (defined(_WIN32) && defined(_LIB)) || defined(NOAMIRA)
#define NO_TCL
#endif

#ifndef NO_TCL
#include <tcl.h>
#else
#define Tcl_Interp void
#define TCL_ERROR 0
#define TCL_OK 0
#endif
#include <stdarg.h>
#include <mclib/McDArray.h>
#include <amiramesh/AmiraMeshWinDLLApi.h>

/** Initializes a toplevel Tcl parse method. This macro should be used
    at the begining of a toplevel parse method. Such a method might
    look as follows:

    int parse(Tcl_Interp* t, int argc, char **argv)
    {
        TCL_PARSE_INIT(argc,argv);

        if (CMD("a")) {
            // command a...
        }
        else if (CMD("b")) {
            // command b...
        }
        else return CMD::usage(t,cmd);

        return TCL_OK;
    }

    When the parse method is called @c argv[0] points to the command
    name and @c argc is at least 1. The macro checks if any additional
    arguments are present. If not, i.e., if argc is equal to 1, it
    modifies @c argv so that an additional argument "help" is present.
    At the same time it sets @c argc to 2. The "help" argument is
    interpreted in CMD::usage(), which should be the called after
    all other CMD() tests. The usage command returns a list of all
    possible commands, i.e., commands tested with the CMD() macro. */
#define TCL_PARSE_INIT(argc,argv) \
    Tcl_ParseInit(argc,argv); \
    char *cmd = argv[1]

/** Checks for a Tcl subcommand. This macro should be used in Tcl
    parse methods to check if the first argument of a toplevel
    command is a certain subcommand. The macro compares the variable
    @c cmd against the name of the subcommand @c text. If also
    appends @c text to the list of all subcommands. This list is
    returned by CMD::usage() when no other subcommand matches. */
#define CMD(text) (cmdCheck(cmd,text,0))

#define ERR_UNKNOWNCMD 1
#define ERR_WRONGARGNUM 2
#define CMD2(text,help) (cmdCheck(cmd,text,help))
#define ASSERTARG(n) if (argc!=(n)) return cmdError(t,ERR_WRONGARGNUM,cmd);

struct AMIRAMESH_API CmdInfo
{
    const char* cmd;
    const char* help;

    CmdInfo(const char* _cmd, const char* _help) {
        cmd = _cmd;
        help = _help;
    }

    CmdInfo() { cmd=help=0; }

    static int usage(Tcl_Interp* t, const char* cmd);
    static int compare(const CmdInfo&, const CmdInfo&);
};

#define cmdInfo getCmdInfo()

extern AMIRAMESH_API McDArray<CmdInfo>& getCmdInfo();
extern AMIRAMESH_API int cmdError(Tcl_Interp* t, int error, const char* cmd);
extern AMIRAMESH_API void Tcl_VaSetResult(Tcl_Interp* t, const char* format, ...);
extern AMIRAMESH_API void Tcl_VaAppendResult(Tcl_Interp* t, const char* format, ...);
extern AMIRAMESH_API void Tcl_VaAppendElement(Tcl_Interp* t, const char* format, ...);
extern AMIRAMESH_API void Tcl_ParseInit(int& argc, char**& argv);

inline int cmdCheck(const char* cmd, const char* text, const char* help) {
    cmdInfo.append(CmdInfo(text,help));
    return (strcmp(cmd,text) == 0);
}

#endif

/// @}
