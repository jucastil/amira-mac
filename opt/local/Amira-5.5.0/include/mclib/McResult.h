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
#ifndef MCRESULT_H
#define MCRESULT_H

#define INCLUDE_CASSERT

#include <stdarg.h>
#include "McHandle.h"
#include "McHandable.h"

#undef check

/** This class provides a standard condition that is returned by any
    operation and reports about the outcome of the operation.
    Objects of this class can be efficiently passed by value since they
    only contain a single pointer and no virtual methods.
    The class provides a code a unique module code, an error code unique
    within that module and a status. Also a textual description and error
    specific data can be contained in the this object.
    The condition code is maintained by the object of class @McResultBase
    pointed to.
    When using exceptions, a "throw" may directly take this object as a
    parameter.
*/
class MCLIB_API McResult
{
public:

    /// Standard return codes
    enum Code
    {
        CODE_OK                = 0x0000 + 0,
        CODE_INVALIDARGUMENT   = 0x0000 + 1,
        CODE_INTERNALERROR     = 0x0000 + 2,
        CODE_NODATA            = 0x0000 + 3,
        CODE_NOTSUPPORTED      = 0x0000 + 4,
        CODE_READONLY          = 0x0000 + 5,
        CODE_OUTOFRANGE        = 0x0000 + 6,
        CODE_NOTIMPLEMENTED    = 0x0000 + 7,
        CODE_OUTOFMEMORY       = 0x0000 + 8,
        CODE_FALSE             = 0x0000 + 9,
        CODE_UNDEFINED         = 0x0000 + 10,
        CODE_INTERRUPTED       = 0x0000 + 11,

        /// OpenGL error codes
        CODE_GL_INVALID_ENUM        = 0x0500 + 0,
        CODE_GL_INVALID_VALUE       = 0x0500 + 1,
        CODE_GL_INVALID_OPERATION   = 0x0500 + 2,
        CODE_GL_STACK_OVERFLOW      = 0x0500 + 3,
        CODE_GL_STACK_UNDERFLOW     = 0x0500 + 4,
        CODE_GL_OUT_OF_MEMORY       = 0x0500 + 5,

        // mappings from errno.h
        CODE_EPERM             = 0x1000 + 1,
        CODE_ENOENT            = 0x1000 + 2,
        CODE_ESRCH             = 0x1000 + 3,
        CODE_EINTR             = 0x1000 + 4,
        CODE_EIO               = 0x1000 + 5,
        CODE_ENXIO             = 0x1000 + 6,
        CODE_E2BIG             = 0x1000 + 7,
        CODE_ENOEXEC           = 0x1000 + 8,
        CODE_EBADF             = 0x1000 + 9,
        CODE_ECHILD            = 0x1000 + 10,
        CODE_EAGAIN            = 0x1000 + 11,
        CODE_ENOMEM            = 0x1000 + 12,
        CODE_EACCES            = 0x1000 + 13,
        CODE_EFAULT            = 0x1000 + 14,
        CODE_EBUSY             = 0x1000 + 16,
        CODE_EEXIST            = 0x1000 + 17,
        CODE_EXDEV             = 0x1000 + 18,
        CODE_ENODEV            = 0x1000 + 19,
        CODE_ENOTDIR           = 0x1000 + 20,
        CODE_EISDIR            = 0x1000 + 21,
        CODE_EINVAL            = 0x1000 + 22,
        CODE_ENFILE            = 0x1000 + 23,
        CODE_EMFILE            = 0x1000 + 24,
        CODE_ENOTTY            = 0x1000 + 25,
        CODE_EFBIG             = 0x1000 + 27,
        CODE_ENOSPC            = 0x1000 + 28,
        CODE_ESPIPE            = 0x1000 + 29,
        CODE_EROFS             = 0x1000 + 30,
        CODE_EMLINK            = 0x1000 + 31,
        CODE_EPIPE             = 0x1000 + 32,
        CODE_EDOM              = 0x1000 + 33,
        CODE_ERANGE            = 0x1000 + 34,
        CODE_EDEADLK           = 0x1000 + 36,
        CODE_ENAMETOOLONG      = 0x1000 + 38,
        CODE_ENOLCK            = 0x1000 + 39,
        CODE_ENOSYS            = 0x1000 + 40,
        CODE_ENOTEMPTY         = 0x1000 + 41,
        CODE_EILSEQ            = 0x1000 + 42,

        CODE_Force32           = 0xffffffff
    };


    ////////////////////////////////////////
    // methods
    ////////////////////////////////////////

    /// Default constructor (sets code to OK).
    McResult();

    /// Copy constructor.
    McResult( const McResult & inResult );

    /// Constructor.
    McResult( int inCode, const char * inText = "", const char * inData = "", bool inGlobal=false );

    /// Constructor.
    McResult( int inLine, const char * inFile, const char * inText, const char * inData );

    /// Constructor.
    McResult( int inCode, int inLine, const char * inFile, const char * inText, const char * inData );

    /// Destructor.
    ~McResult();

    /// Creates copy of error and add user information, e.g. name of not-writable directory
    const McResult duplicate( const char * info=0 ) const;

    /** Notifies an error if condition is bad. This method calls a callback specified with
        setNotificationCallback(). If no such callback has been set, the method just returns. */
    const McResult & notify() const;

    /** Set notification routine to be called by notify(). */
    static void setNotificationCallback( void (*notify)(const McResult&,void*), void* userData);

    /// Throws an error if condition is bad.
    const McResult & check() const;

    /// Returns the status code identifier for this object..
    int code() const;

    /// Returns the line number in source code.
    int line() const;

    /// Returns the error message text for this object.
    const char * text() const;

    /// Returns source file name this object.
    const char * file() const;

    /// Returns the error specific data.
    const char * data() const;

    /// Returns true if data() returns not an empty string.
    bool hasData() const;

    /// Returns true if status is OK.
    bool ok() const;

    /// Returns true on failure.
    bool failed() const;

    /// Compares two results based on module and result code.
    bool operator==(const McResult& arg) const;

    /// Assignment operator.
    McResult & operator=( const McResult & o );

    /// Conversion operator to bool, returns true if code is OK.
    operator bool() const;

protected:
    /// ref counted pointer to base object containing the attributes
    class McResultBase * mBase;
};

////////////////////////////////////////////////////////////////////////////////
// Standard result objects
////////////////////////////////////////////////////////////////////////////////

extern MCLIB_API const McResult McOK;
extern MCLIB_API const McResult McFALSE;

extern MCLIB_API const McResult McINVALIDARGUMENT;
extern MCLIB_API const McResult McINTERNALERROR;
extern MCLIB_API const McResult McNODATA;
extern MCLIB_API const McResult McNOTSUPPORTED;
extern MCLIB_API const McResult McREADONLY;
extern MCLIB_API const McResult McOUTOFRANGE;
extern MCLIB_API const McResult McNOTIMPLEMENTED;
extern MCLIB_API const McResult McOUTOFMEMORY;
extern MCLIB_API const McResult McINTERRUPTED;

extern MCLIB_API const McResult McEPERM;
extern MCLIB_API const McResult McENOENT;
extern MCLIB_API const McResult McESRCH;
extern MCLIB_API const McResult McEINTR;
extern MCLIB_API const McResult McEIO;
extern MCLIB_API const McResult McENXIO;
extern MCLIB_API const McResult McE2BIG;
extern MCLIB_API const McResult McENOEXEC;
extern MCLIB_API const McResult McEBADF;
extern MCLIB_API const McResult McECHILD;
extern MCLIB_API const McResult McEAGAIN;
extern MCLIB_API const McResult McENOMEM;
extern MCLIB_API const McResult McEACCES;
extern MCLIB_API const McResult McEFAULT;
extern MCLIB_API const McResult McEBUSY;
extern MCLIB_API const McResult McEEXIST;
extern MCLIB_API const McResult McEXDEV;
extern MCLIB_API const McResult McENODEV;
extern MCLIB_API const McResult McENOTDIR;
extern MCLIB_API const McResult McEISDIR;
extern MCLIB_API const McResult McEINVAL;
extern MCLIB_API const McResult McENFILE;
extern MCLIB_API const McResult McEMFILE;
extern MCLIB_API const McResult McENOTTY;
extern MCLIB_API const McResult McEFBIG;
extern MCLIB_API const McResult McENOSPC;
extern MCLIB_API const McResult McESPIPE;
extern MCLIB_API const McResult McEROFS;
extern MCLIB_API const McResult McEMLINK;
extern MCLIB_API const McResult McEPIPE;
extern MCLIB_API const McResult McEDOM;
extern MCLIB_API const McResult McERANGE;
extern MCLIB_API const McResult McEDEADLK;
extern MCLIB_API const McResult McENAMETOOLONG;
extern MCLIB_API const McResult McENOLCK;
extern MCLIB_API const McResult McENOSYS;
extern MCLIB_API const McResult McENOTEMPTY;
extern MCLIB_API const McResult McEILSEQ;


////////////////////////////////////////////////////////////////////////////////
// Macros
////////////////////////////////////////////////////////////////////////////////

#ifndef __TIMESTAMP__
#define __TIMESTAMP__ ""
#endif

/// macro that executes a command. if the return value is zero it returns an error, otherwise McOK
#define MCCK(CMD) ( \
    (CMD) \
    ? \
    McOK \
    : \
    McResult( McResult::CODE_INTERNALERROR, __LINE__, __FILE__, "" , McString(0,"assertion=[%s] %s", #CMD, "timestamp=["__TIMESTAMP__"]") ) \
)

/// macro that executes a command. if the return value is zero it calls notify and returns that error, otherwise McOK
#define MCCK_N(CMD) ( \
    (CMD) \
    ? \
    McOK \
    : \
    McResult( McResult::CODE_INTERNALERROR, __LINE__, __FILE__, "" , McString(0,"assertion=[%s] %s", #CMD, "timestamp=["__TIMESTAMP__"]") ).notify() \
)

/// macro that executes a command. if the return value is zero it calls check and returns that error, otherwise McOK
#define MCCK_C(CMD) ( \
    (CMD) \
    ? \
    McOK \
    : \
    McResult( McResult::CODE_INTERNALERROR, __LINE__, __FILE__, "" , McString(0,"assertion=[%s] %s", #CMD, "timestamp=["__TIMESTAMP__"]") ).check() \
)

/// macro that executes a command. if the return value is zero it returns an error, otherwise McOK
#define MCCK_ASS(CODE,CMD) ( \
    (CMD) \
    ? \
    McOK \
    : \
    McResult( CODE, __LINE__, __FILE__, "" , McString(0,"assertion=[%s] %s", #CMD, "timestamp=["__TIMESTAMP__"]") ) \
)

/// macro that executes a command. if the return value is zero it returns an error, otherwise McOK
#define MCCK_ASS(CODE,CMD) ( \
    (CMD) \
    ? \
    McOK \
    : \
    McResult( CODE, __LINE__, __FILE__, "" , McString(0,"assertion=[%s] %s", #CMD, "timestamp=["__TIMESTAMP__"]") ) \
)

/// macro that executes a command. if the return value is zero it returns an error with the given description, otherwise McOK
#define MCCK_ASS3(CODE,CMD,DESC) ( \
    (CMD) \
    ? \
    McOK \
    : \
    McResult( CODE, __LINE__, __FILE__, DESC , McString(0,"assertion=[%s] %s", #CMD, "timestamp=["__TIMESTAMP__"]") ) \
)

/// macro that returns the McResult-argument from the current function if it failed
#define MC_RETURN(RES) do{{ McResult r(RES); if(r.failed()) return r; }}while(0)

/// macro that converts an errno-code to the McResult-code
#define MC_E2C(E) ((int)(E) + 0x1000)

#endif

/// @}
