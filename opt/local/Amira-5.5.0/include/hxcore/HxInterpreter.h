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

/// @addtogroup hxcore hxcore
/// @{
#ifndef HX_INTERPRETER_H
#define HX_INTERPRETER_H

#include <tcl.h>
#include <stdarg.h>
#include <mclib/McDArray.h>
#include <mclib/McServerSocket.h>
#include <hxcore/HxBase.h>

#ifdef PORT_AMIRA
    #undef PORT_AMIRA
#endif
#define PORT_AMIRA 7175

#ifdef PORT_HTTPD
    #undef PORT_HTTPD
#endif
#define PORT_HTTPD 7000

class McHttpd;
class QWidget;
class QSocketNotifier;
class QxInterpreterNotifier;

/** Provides the global Tcl command interpreter. The interpreter can be
    accessed via the global pointer theInterpreter. Developers can
    use this pointer in order to evaluate Tcl code, to add or remove new
    Tcl commands, or to set, get, or link Tcl variables. */
class HXCORE_API HxInterpreter {
  public:
    /// Constructor.
    HxInterpreter();

    /// Destructor.
    virtual ~HxInterpreter();

    /// Evaluate a command in global scope and return result of command.
    virtual const char* eval(const char* cmd);

    /// Evaluate a command in global scope and return result of command in result and status code as return value (TCL_OK, ...).
    virtual int eval(const char* cmd, McString& result);

    ///
    enum TCLErrorHandlingPolicy { SILENT_IGNORE=0, PRINT_CONSOLE=1, SHOW_DIALOG=2 };

    /// Evaluate a command in global scope and return result of command.
    virtual const char* eval(const char* cmd, TCLErrorHandlingPolicy  handleError);

    /// Evaluate a command in global scope and return result of command in result and status code as return value (TCL_OK, ...).
    virtual int eval(const char* cmd, McString& result, TCLErrorHandlingPolicy handleError);

    /// Compose a new command and pass it to @c eval
    virtual const char* evalf(const char* format, ...);

    /// Evaluate commands defined in a file.
    /// updateMainTitle indicates if the main application title could be updated
    /// by the interpreter when a hx file is evaluated.
    /// By default, viewers auto redraw is forced to ON
    /// when evaluating commands read from the file.
    /// If forceAutoRedraw is false,  the current auto redraw state will remain
    /// unchanged.
    virtual int evalFile(const char* file, int interruptable=0, bool updateMainTitle=true, bool forceAutoRedraw=true);

    /// Register a new Tcl command.
    virtual void registerCmd(const char* name,
        Tcl_CmdProc*, ClientData, Tcl_CmdDeleteProc*);

    /// Delete a Tcl command.
    virtual void deleteCmd(const char* name);

    /// Create new Tcl-variable in global scope associated with 'addr'.
    void linkVar(const char* varName, void* addr, int type);

    /// Remove linked Tcl variable from global scope.
    void unlinkVar(const char* varName);

    /** Sets a global Tcl variable. For example, if name is "a" you can
        access the variable in a Tcl script via "$a". @c flags is a bit
        mask used to control certain properties of the variable. It has
        the same meaning as for the routine Tcl_SetVar(). Usually, it is
        ok use the default value, i.e., no flags set. */
    void setVar(const char * name, const char * value, int flags=0);

    /** Unset a global Tcl variable.  The flags have the same meaning as for
        Tcl_UnsetVar(). */
    void unsetVar(const char* name, int flags=0);

    /// Returns value of Tcl variable, or null, if it does not exist.
    const char* getVar(const char* name);

    /// Evaluates argument as boolean expression using @c expr.
    int expr(const char* string);

    /** Checks if a Tcl procedure @c name has been declared. If so, the
        method returns the number of arguments of the procedure. If not,
        -1 is returned. */
    int checkProc(const char* name);

    /** This function should be called by the GUI components whenever a
        function key was hit. It returns 1 if a corresponding TCL procedure
        was found and executed.*/
    int functionKeyHit(int which, int shift, int ctrl, int alt = 0);

    /** Opens Amira socket (useful for receiving remote commands). If the
        socket cannot be opened at the specified port some other port is
        tried automatically. On success the actual port number is returned.
        Otherwise -1 is returned. */
    int openAmiraSocket(int port=PORT_AMIRA);

    /// Closes Amira socket.
    void closeAmiraSocket();

    /// Returns port where Amira is listening or -1, if socket isn't open.
    int portAmiraSocket() const { return amiraSocket.port(); }

    /// Starts http daemon (useful for starting demos from netscape).
    int startHttpd(int port);

    /// Quits the http daemon.
    void quitHttpd();

    /// Handles accept and read events, only public for internal reasons.
    void handleSocketEvent(int sd);

    /// Returns pointer to global Tcl interpreter object.
    Tcl_Interp* getTclInterp() const { return inter; }

    /// Send a command to a running Amira process.
    static int sendCmd(const char* host, int port, const char* fmt, ...);

    /// Read method, used by AmiraScript file format.
    static int loadScript(const char* filename);

    static HxInterpreter*& getTheInterpreter();

    static int loadsFromNet();

    /** Implements Tcl commands for controlling a Qt widget. This method can
        be called from the parse method of an object associated with a toplevel
        Qt window, such as theMain or theMsg. It implements commands such as
        show, hide, setPosition, getPosition, setSize, getSize, setGeometry,
        and getGeometry. */
    static int widgetParse(QWidget* w, Tcl_Interp* t, int argc, char** argv);

    /** Object to connect Qt signals.
      */
    QxInterpreterNotifier* const mNotifier;

    /**
     *  Convenience method to know if a network is loading.
     */
    bool networkIsLoading() const {return m_networkIsLoading != 0;}

  protected:
    /* The Amira socket is usually bound to port 7175. Via this socket
       Tcl-commands can be send to a running Amira. However, in order to
       activate the socket the user first has to type "app -listen" in
       Amira's console window. This is for security reasons. */
    McServerSocket amiraSocket;

    // Emits a signal when new connections are pending at the amiraSocket.
    QSocketNotifier* amiraSocketNotifier;

    // List of all connections established at the amiraSocket.
    McDArray<QSocketNotifier*> amiraConnections;

    /* The http daemon allows us to start demos using netscape. Usually
       the daemon listens at port 7000. */
    McHttpd* httpd;

    // Emits a signal when new http connections are pending.
    QSocketNotifier* httpdSocketNotifier;

    // List of all connections established by the http daemon.
    McDArray<QSocketNotifier*> httpdConnections;

    // Instance of global tcl interpreter.
    Tcl_Interp *inter;

    // Stack of messages to be displayed in busy dialog.
    McDArray<char*> msgStack;

    virtual void handleTclError(const char* cmd,
                                int ret, TCLErrorHandlingPolicy policy);

    static int appCmd(ClientData, Tcl_Interp*, int, char**);
    static int httpdCmd(ClientData, Tcl_Interp*, int, char**);

    static int addTimeOutCmd(ClientData, Tcl_Interp*, int, char**);
    static int removeTimeOutCmd(ClientData, Tcl_Interp*, int, char**);
    static void tclTimeOutFunc(void* userdata);

    int m_networkIsLoading;
};

#define theInterpreter HxInterpreter::getTheInterpreter()

#endif

/// @}
