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

/// @addtogroup hxplot hxplot
/// @{
#ifndef _PZ_INTERPRETER_H
#define _PZ_INTERPRETER_H

//#include <tcl.h>
//#include <stdarg.h>
//#include <mclib/McDArray.h>
//#include <mclib/McServerSocket.h>
#include <hxcore/HxInterpreter.h>
#include <hxplot/PzPlotWinDLLApi.h>


/** Provides the global Tcl command interpreter. The interpreter can be
    accessed via the global pointer theInterpreter. Developers can
    use this pointer in order to evaluate Tcl code, to add or remove new
    Tcl commands, or to set, get, or link Tcl variables. */

class HXPLOT_API PzInterpreter : public HxInterpreter {

  public:
    /// Constructor.
    PzInterpreter();

    /// Destructor.
    ~PzInterpreter();

    /// Evaluate a command in global scope and return result of command.
    const char* eval(const char* cmd);

    /// Evaluate a command in global scope and return result of command in result and status code as return value (TCL_OK, ...).
    int eval(const char* cmd, McString& result);

    /// Evaluate a command in global scope and return result of command.
    const char* eval(const char* cmd,
                     HxInterpreter::TCLErrorHandlingPolicy handleError);

    /// Evaluate a command in global scope and return result of command in result and status code as return value (TCL_OK, ...).
    int eval(const char* cmd, McString& result,
             HxInterpreter::TCLErrorHandlingPolicy handleError);

    /// Compose a new command and pass it to @c eval
    const char* evalf(const char* format, ...);
    
    /** Evaluate commands defined in a file.
        @p interruptable, @p updateMainTitle and @p forceAutoRedraw
        are silently ignored.
    */
    int evalFile(const char* file, int interruptable = 0,
                 bool updateMainTitle = true, bool forceAutoRedraw = true);

    /** Register a new Plot command.
        Returns 1 on success, 0 if command already exists.
    */
    void registerCmd(const char* name, Tcl_CmdProc* proc, ClientData ptr,
                     Tcl_CmdDeleteProc* delProc = NULL);

    /** Register a new Plot command.
        Returns 1 on success, 0 if command already exists.
        If @p overload is 1 command is registered by any means.
    */
    int registerCmd(const char* name, Tcl_CmdProc* proc, ClientData ptr,
                    int overload, Tcl_CmdDeleteProc* delProc = NULL);

    /// Send a command to a running Amira.
    static int sendCmd(const char* host, int port, const char* fmt, ...);

    /// Read method, used by AmriaScript file format.
    static int loadScript(const char* filename);

    static HxInterpreter*& getTheInterpreter();

  protected:

    void handleTclError(const char* cmd, int ret,
                        HxInterpreter::TCLErrorHandlingPolicy policy);

    friend class PzMessage;
};

#ifdef theInterpreter
#undef theInterpreter
#define theInterpreter PzInterpreter::getTheInterpreter()
#endif

#endif

/// @}
