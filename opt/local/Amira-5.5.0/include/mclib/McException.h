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
#ifndef MC_EXCEPTION_H
#define MC_EXCEPTION_H

#include <typeinfo>

#include "McString.h"
#include "McWinDLLApi.h"
#include "McAssert.h"
#include "McStdlib.h"

/** Base class for exceptions in amira. This class can be used
    to describe an unspecified generic exception. An error
    message explaining the exception can be specified in the
    contructor using printf() syntax.

    Note, that all exceptions derived from McException which
    occur during file IO or when an amira module is fired will
    be catched by the amira kernel. However, whenever possible
    exceptions which one knows can occur should be handled by
    the user, rather than by the amira kernel.

    The following code illustrates how to use McException:

    @code
    void f()
    {
        ...
        if (err)
            throw McException("Error in f(), error code = %d", err);
        ...
        if (err)
            mcthrow( McString(0, "Error in f(), error code = %d", err) );
        ...
        if (err)
            mcthrow( "Error in f()" );
    }

    void g()
    {
        ...
        try {
            f();
        } catch (McException& e) {
            HxMessage::error(e.what());
        }
        ...
    }
    @endcode

    @seealso McMemoryException
*/
class MCLIB_API McException
{
  public:
    ///
    McException();

    /// Constructor taking an error message
    McException( McString & inErrorMsg );

    /// Constructor taking an error description in printf() format.
    McException(const char * format, ...);

    // default copy constructor ok.
    // default assignment operator.

    /// Destructor.
    virtual ~McException();

    /// Returns an error description in plain text format.
    virtual const char *what();

    /** Returns a copy of the exception that can be stored
        and rethrown by raise().
        The returned object must be cleaned up using delete.

        You must override doClone() in derived classes
        to provide a copy of the derived type.
        If you don't override, only a copy of a base type
        will be available.
      */
    McException* clone() {
        mcenter ("McException::clone");
        McException* copy = doClone();
        mcensure (typeid(*copy) == typeid(*this) && "did you forget to override doClone() ?");
        return copy;
    }

    /** Throws a copy of this exception.

        You must override doRaise() in derived classes
        to throw a copy of the derived type.
        If you don't override, only a copy of a base type
        will be thrown.
      */
    void raise () {
        mcenter ("McException::raise");
        try {
            doRaise();
        } catch (McException& e) {
            MC_UNREFERENCED_PARAMETER(e);
            mcensure (typeid(e) == typeid(*this) && "did you forget to override doRaise() ?");
            throw;
        }
    }

    /** Add frame and rethrow.

        You must call rethrow() only while handling the exception.
        That is, a naked C++ 'throw;' must rethrow the current
        exception.

        Use raise() instead if you want to tell an exception
        instance to throw itself.
      */
    void rethrow( const char* file, int line, const char* reason );

  protected:
    virtual McException* doClone();
    virtual void doRaise ();

  private:
    McString mReason;
    struct Frame {
        Frame () {};
        Frame (const char* f, int l, const char* r);

        McString file;
        int line;
        McString reason;
    };

    void addFrame( const char* file, int line, const char* reason );
    McDArray<Frame> mFrames;

    void initBacktrace();

    McDArray<McString> mBacktrace;
};

#ifdef NDEBUG
#define mcthrow(MSG) do {{ \
    try { \
        throw McException(); \
    } catch (McException& macro_mcthrow_exception) { \
        macro_mcthrow_exception.rethrow( 0, 0, (const char*)(MSG) ); \
    } \
}} while(0)

#define mcrethrow(EX,MSG) EX.rethrow( 0, 0, (const char*)(MSG) )
#else

/** Capture the callstack and throw an exception of TYPE.
    Anything that can be cast to const char* can be used as MSG.
    A callstack is captured in debug builds (Linux only). */
#define mcthrow(MSG) do {{ \
    try { \
        throw McException(); \
    } catch (McException& macro_mcthrow_exception) { \
        macro_mcthrow_exception.rethrow( __FILE__, __LINE__, (const char*)(MSG) ); \
    } \
}} while (0)
// the do-while is necessary to make it to a single statement
// without being a block which would lead to an unbound "else" in
// the following example
//
//  if (exp)
//      mcexception()
//  else
//      ...

/** Frame an exception with the current context (file, line,
    additional message) and throw it again.

    You must call mcrethrow() only while handling the exception
    EX.  That is, a naked C++ 'throw;' must rethrow EX.

    Anything that can be cast to const char* can be used as MSG.

    The file name and the line number are recorded in debug builds.
*/
#define mcrethrow(EX,MSG) EX.rethrow( __FILE__, __LINE__, (const char*)(MSG) )

#endif
#endif

/// @}
