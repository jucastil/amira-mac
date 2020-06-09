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

/// @addtogroup mclib mclib
/// @{
#ifndef _MC_ASSERT_H__
#define _MC_ASSERT_H__

#include "McWinDLLApi.h"
#include <assert.h>

#include <stdarg.h>
#include <stdio.h>

enum McDebugLevel {
      MCDL_EMERG = 0
    , MCDL_ALERT
    , MCDL_CRIT
    , MCDL_ERR
    , MCDL_WARNING
    , MCDL_NOTICE
    , MCDL_INFO
    , MCDL_DEBUG
};

/** @addtogroup mclib_mcassert Debugging, Callstack, Assertions, Precondition, Postcondition

    \brief Debugging macros
  
By using
\code
#include <mclib/McAssert.h>
\endcode
you have a number of debugging macros at your fingertips which are a lot more useful than a
simple assert. A quick summary:
   - Specific macros supporting 'Design by Contract' (http://archive.eiffel.com/doc/manuals/technology/contract/)
     are provided as mcrequire(), mcensure() and mcassert().
   - You can place mcenter() at function entries to enable printing of callstacks.
   - mcerror() lets you indicate critical errors.
   - mcdebug() lets you print debug messages of various severity levels. The levels
     are the same used normally for syslogging.  mcdebug is only used for
     printing messages. Don't expect it to enfore error handling.  If you need
     stronger error handling use mcrequire(), mcensure(), mcassert() and
     mcerror(). The debugging levels are the following:
        - 0: MCDL_EMERG, amira is unusable
        - 1: MCDL_ALERT, the situation has to be avoided
        - 2: MCDL_CRIT,
        - 3: MCDL_ERR, erronous behaviour
        - 4: MCDL_WARNING
        - 5: MCDL_NOTICE
        - 6: MCDL_INFO
        - 7: MCDL_DEBUG
        - >7: less important DEBUG
   - every macro has two flavors, e.g. mcensure() and mcensure_debug().
        The version postfixed by '_debug' will always be removed in production code (if NDEBUG is defined).
        The default versions may be kept by defining MC_ASSERT_DEBUG, otherwise they will be removed in production code.
   - You can configure all this during runtime using:
        - app debug level:
            - level == 0: MCDL_ERR and lower gets printed.
            - level >0: MCDL_WARNING, ...
            - level <0: MCDL_CRIT ...
        - app debugfuncfilter [list [!] func1 func2 ...]:
            Messages are only printed if one of the
            funcs is matched. If the first entry in the list is "!" only, if
            none of the funcs is matched. Only the member part of the function is
            tested.
        - app debugfilefilter [list [!] file1 file2 ...]
        - app debugpackagefilter [list [!] package1 package2 ...]
   - If the environment variable AMIRA_DEBUG is set, debugging will be enabled even before main is entered.
   - If amira is running, a thread safe assertion handler is running (McThreadedAssertionHandler).
        Violations of pre- and postconditions, assertions and mcerros will trigger a popup
        and allow the user to choose how to proceed (Abort, Ignore Once, Ignore Always).

A good idea may be to create a file debug.hx, like:
\verbatim
# Amira Script

echo "enabling debugging"
app debug 10
app debugpackagefilter hxlattice4
app debugfuncfilter { ! putget }
\endverbatim
And use it with amira/bin/start debug.hx to enable debugging at startup or load $AMIRA_ROOT/debug.hx to enable
debugging at runtime.

  @{
*/

class McAssertionHandlerInit;

/**
 */
class MCLIB_API McAssertionHandler {
    public:
        enum IgnoreCriticalError {
              CE_DONT_IGNORE = 0
            , CE_IGNORE
        };
        typedef IgnoreCriticalError (*criticalCB_t) (const char* msg);

        virtual ~McAssertionHandler ();

        virtual IgnoreCriticalError assertFailed (IgnoreCriticalError ignore, const char* assertion, const char* file, int line) = 0;
        virtual IgnoreCriticalError requireFailed (IgnoreCriticalError ignore, const char* require, const char* file, int line) = 0;
        virtual IgnoreCriticalError ensureFailed (IgnoreCriticalError ignore, const char* ensure, const char* file, int line) = 0;
        virtual IgnoreCriticalError criticalError (IgnoreCriticalError ignore, const char* error, const char* file, int line) = 0;

        virtual void enter (int level, const char* func, const char* package, const char* file) = 0;
        virtual void exit () = 0;

        /** level (like syslog):
         *    - 0: EMERG, amira is unusable
         *    - 1: ALERT, the situation has to be avoided
         *    - 2: CRIT,
         *    - 3: ERR, erronous behaviour
         *    - 4: WARNING
         *    - 5: NOTICE
         *    - 6: INFO
         *    - 7: DEBUG
         *    - >7: less important DEBUG
         *
         *  Per default level <= 3 will be printed.
         */
        virtual void debug (int level, const char* str, va_list arg) = 0;

        static void setAssertionHandler (McAssertionHandler* handler);

        static McAssertionHandler* handler () {
            return thehandler;
        }

        /** No debugging if level < 0
         *  The larger the level the more debugging info will be printed.
         */
        static void setDebugLevel (int level) {
            debuglevel = level;
        }

        int getDebugLevel () {
            return debuglevel;
        }

        static const char* getDebugLevelName (int level);

        /** \brief Sets a list of function names (member part only)
         *  which must match if a
         *  MCVL_FILTERED_... verbosity level is selected. If
         *  the first filter is "!" none of the following names
         *  must match.
         */
        static void setFuncFilter (int argc, const char** argv) {
            funcfilter = argv;
            funcfiltercount = argc;
        }

        /** \brief Sets a list of package names
         *  which must match if a
         *  MCVL_FILTERED_... verbosity level is selected. If
         *  the first filter is "!" none of the following names
         *  must match.
         */
        static void setPackageFilter (int argc, const char** argv) {
            packagefilter = argv;
            packagefiltercount = argc;
        }

        /** \brief Sets a list of file names (basename only)
         *  which must match if a
         *  MCVL_FILTERED_... verbosity level is selected. If
         *  the first filter is "!" none of the following names
         *  must match.
         */
        static void setFileFilter (int argc, const char** argv) {
            filefilter = argv;
            filefiltercount = argc;
        }

        static bool hasAnyFilter () {
            return funcfiltercount || filefiltercount || packagefiltercount;
        }

        class FunctionGuard {
            public:
                FunctionGuard (int level, const char* name, const char* packagename, const char* filename) {
                    McAssertionHandler::handler ()->enter(level, name, packagename, filename);
                }
                ~FunctionGuard () {
                    McAssertionHandler::handler ()->exit();
                }
        };
    protected:
        McAssertionHandler ();

        static const char** funcfilter;
        static int funcfiltercount;
        static const char** filefilter;
        static int filefiltercount;
        static const char** packagefilter;
        static int packagefiltercount;

        friend class McAssertionHandlerInit;
    private:
        // we want to have this as a static (global) variable to allow setting it from a debugger
        static int debuglevel;
        static McAssertionHandler* thehandler;
};

class MCLIB_API McAssertionHandlerInit {
    public:
        McAssertionHandlerInit ();
        ~McAssertionHandlerInit ();
    private:
        static int count;
};

// if we're not compiling McAssert.cpp, ensure that the thehandler will be initialized
// by creating one static instance of our initialization class per translation unit
// see http://www.cs.utexas.edu/users/downing/Papers/Globals-2004.html for details
#ifndef MC_ASSERT_CPP
static McAssertionHandlerInit ensureAssertionHandlerInit;
#endif

// the do-while is necessary to prevent the curlys marking an if/while/for-block
//
//  if (exp)
//      mcassert(exp2);
//  else
//      ...
//
// without the dowhile -> error: illegal else without matching if

#if defined (NDEBUG) && !defined (MC_ASSERT_DEBUG) // no debugging at all

#define mcrequire(EX) do { } while (0)
#define mcassert(EX) do { } while (0)
#define mcensure(EX) do { } while (0)

#define mcerror(EX) do { } while (0)

#define mcenter(NAME) do { } while (0)
#define mcenter1(NAME) do { } while (0)
#define mcenter2(NAME) do { } while (0)
#define mcenter3(NAME) do { } while (0)
#define mcenter4(NAME) do { } while (0)

#else // full debugging

// In classic DbC (Design-by-Contract), use "require" at the top of methods to check:
// - Was the method called with the right state?
// - Was the method called with the right parameters?
#define mcrequire(EX) do{{ if ( !(EX) ) { \
    const char* file = __FILE__; \
    const int line = __LINE__; \
    const char* expr = # EX ; \
    static McAssertionHandler::IgnoreCriticalError ignore = McAssertionHandler::CE_DONT_IGNORE; \
    if (ignore == McAssertionHandler::CE_DONT_IGNORE) { \
        ignore = McAssertionHandler::handler ()->requireFailed (ignore, expr, file, line); \
    } \
}}}while(0)

// In classic DbC (Design-by-Contract), use "assert" half-way through a method to check:
// - Is the method currently doing the right thing?
#define mcassert(EX) do{{ if ( !(EX) ) { \
    const char* file = __FILE__; \
    const int line = __LINE__; \
    const char* expr = # EX ; \
    static McAssertionHandler::IgnoreCriticalError ignore = McAssertionHandler::CE_DONT_IGNORE; \
    if (ignore == McAssertionHandler::CE_DONT_IGNORE) { \
        ignore = McAssertionHandler::handler ()->assertFailed (ignore, expr, file, line); \
    } \
}}}while(0)

// In classic DbC (Design-by-Contract), use "ensure" at the end of methods to check:
// - Is the method returning the right values?
// - Has the method left the app in the right state?
#define mcensure(EX) do{{ if ( !(EX) ) { \
    const char* file = __FILE__; \
    const int line = __LINE__; \
    const char* expr = # EX ; \
    static McAssertionHandler::IgnoreCriticalError ignore = McAssertionHandler::CE_DONT_IGNORE; \
    if (ignore == McAssertionHandler::CE_DONT_IGNORE) { \
        ignore = McAssertionHandler::handler ()->ensureFailed (ignore, expr, file, line); \
    } \
}}}while(0)

#define mcerror(EX) do{ \
    const char* file = __FILE__; \
    const int line = __LINE__; \
    const char* expr = # EX ; \
    static McAssertionHandler::IgnoreCriticalError ignore = McAssertionHandler::CE_DONT_IGNORE; \
    if (ignore == McAssertionHandler::CE_DONT_IGNORE) { \
        ignore = McAssertionHandler::handler ()->criticalError (ignore, expr, file, line); \
    } \
}while(0)

// tricky stuff to get a macro expanded to a string, search google for "cpp stringification"
#define MCxstr(s) MCstr(s)
#define MCstr(s) #s
#define mcenter(NAME) McAssertionHandler::FunctionGuard mcassert_functionguard( MCDL_DEBUG, NAME, MCxstr(PACKAGEID), __FILE__ )

// less important methods
#define mcenter1(NAME) McAssertionHandler::FunctionGuard mcassert_functionguard( MCDL_DEBUG + 1, NAME, MCxstr(PACKAGEID), __FILE__ )
#define mcenter2(NAME) McAssertionHandler::FunctionGuard mcassert_functionguard( MCDL_DEBUG + 2, NAME, MCxstr(PACKAGEID), __FILE__ )
#define mcenter3(NAME) McAssertionHandler::FunctionGuard mcassert_functionguard( MCDL_DEBUG + 3, NAME, MCxstr(PACKAGEID), __FILE__ )

// for inner loop methods
#define mcenter4(NAME) McAssertionHandler::FunctionGuard mcassert_functionguard( MCDL_DEBUG + 4, NAME, MCxstr(PACKAGEID), __FILE__ )

#endif // END of MC_ASSERT_DEBUG block


// _debug versions will be removed in production code
#ifdef NDEBUG
#define mcassert_debug(EX) do { } while (0)
#define mcrequire_debug(EX) do { } while (0)
#define mcensure_debug(EX) do { } while (0)
#define mcerror_debug(EX) do { } while (0)
#define mcenter_debug(NAME) do { } while (0)
#define mcenter1_debug(NAME) do { } while (0)
#define mcenter2_debug(NAME) do { } while (0)
#define mcenter3_debug(NAME) do { } while (0)
#define mcenter4_debug(NAME) do { } while (0)
#else
#define mcassert_debug(EX) mcassert(EX)
#define mcrequire_debug(EX) mcrequire(EX)
#define mcensure_debug(EX) mcensure(EX)
#define mcerror_debug(EX) mcensure(EX)
#define mcenter_debug(NAME) mcenter(EX)
#define mcenter1_debug(NAME) mcenter1(EX)
#define mcenter2_debug(NAME) mcenter2(EX)
#define mcenter3_debug(NAME) mcenter3(EX)
#define mcenter4_debug(NAME) mcenter4(EX)
#endif

inline void mcdebug (int level, const char* format, ...) {
#if !defined (NDEBUG) || defined (MC_ASSERT_DEBUG)
    va_list args;
    va_start(args, format);
    McAssertionHandler::handler ()->debug (level, format, args);
    va_end (args);
#endif
}

inline void mcdebug (const char* format, ...) {
#if !defined (NDEBUG) || defined (MC_ASSERT_DEBUG)
    va_list args;
    va_start(args, format);
    McAssertionHandler::handler ()->debug (MCDL_DEBUG, format, args);
    va_end (args);
#endif
}

inline void mcdebug_debug (int level, const char* format, ...) {
#if !defined (NDEBUG)
    va_list args;
    va_start(args, format);
    McAssertionHandler::handler ()->debug (level, format, args);
    va_end (args);
#endif
}

inline void mcdebug_debug (const char* format, ...) {
#if !defined (NDEBUG)
    va_list args;
    va_start(args, format);
    McAssertionHandler::handler ()->debug (MCDL_DEBUG, format, args);
    va_end (args);
#endif
}

/** @} */

#endif

/// @}
