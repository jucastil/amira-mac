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
#ifndef HX_DSO
#define HX_DSO

/* That's really tricky:
   - with hpux 32bit we have to use the shl_... stuff
   - with hpux 64bit we have to use the dl... stuff
   There is a compatibility mode but it doesn't work properly.
*/
#ifndef AMIRA64
#define HPUX_USE_SHL
#endif

#ifdef HX_OS_WIN
    #include <windows.h>
#else
    #if defined(__hpux) && defined(HPUX_USE_SHL)
        #include <dl.h>
        #include <errno.h>
    #else
        #include <dlfcn.h>
    #endif
#endif

#include <hxcore/HxAmiraWinDLLApi.h>
#include <mclib/McDArray.h>

class McString;
class McFilename;

/** Wrapper for dynamic linking of shared libraries. It is possible
    to link and unlink a shared library, to get symbols from it, and 
    to call functions with 0 to 5 arguments from the library. When the
    library is opened the routine @c amirapackage_<name>_init is called,
    provided it exists (here @c <name> denotes the plain name of the
    shared library without any pre- or postfixes).

    In order to execute a function "f" defined in the library, one of
    the overloaded execute() methods can be called. No name mangling is
    applied to the function name. Therefore, the function f should
    either be declared as extern "C" or a mangled function name should
    be passed as an argument to execute(). The first approach is the
    preferred one because it is not platform-dependent.

    All variants of execute() expect void* arguments as parameters.
    If "f" expects arguments of some other type, you may cast these
    arguments to void*, provided the size of the expected arguments
    matches that of void*. In order to be compatible with 64-bit
    architectures, "f" should use mclong instead of just int for its
    input parameters.
    
    If this is not the case, you should retrieve a pointer to "f" by
    calling getSymbol(), and then call this function explicitly
    instead of using execute().
 */
class HXCORE_API HxDSO {

  public:
    /// Default constructor.
    HxDSO();

    /// This constructor tries to open the specified library.
    HxDSO(const char* path);

    /// Destructor.
    ~HxDSO();

    /// Tries to link a shared library, returns 0 on success.
    int open(const char* path);

    /// Unlinks the shared library.
    void close();

    /// Unlinks the shared library.
    void closeUnload();

    /// Checks if shared library is open.
    int isOpen() { return (handle!=0); }

    /// Execute f()
    void execute(const char* f);

    /// Execute f(void*)
    void execute(const char* f, void*);

    /// Execute f(void*, void*)
    void execute(const char* f, void*, void*);

    /// Execute f(void*, void*, void*)
    void execute(const char* f, void*, void*, void*);

    /// Execute f(void*, void*, void*, void*)
    void execute(const char* f, void*, void*, void*, void*);

    /// Execute f(void*, void*, void*, void*, void*)
    void execute(const char* f, void*, void*, void*, void*, void*);

    /// Execute f()
    void* executePtr(const char* f);

    /// Execute f(void*)
    void* executePtr(const char* f, void*);

    /// Execute f(void*, void*)
    void* executePtr(const char* f, void*, void*);

    /// Execute f(void*, void*, void*)
    void* executePtr(const char* f, void*, void*, void*);

    /// Execute f(void*, void*, void*, void*)
    void* executePtr(const char* f, void*, void*, void*, void*);

    /// Execute f(void*, void*, void*, void*, void*)
    void* executePtr(const char* f, void*, void*, void*, void*, void*);

    /// Execute f()
    int executeInt(const char* f);

    /// Execute f(void*)
    int executeInt(const char* f, void*);

    /// Execute f(void*, void*)
    int executeInt(const char* f, void*, void*);

    /// Execute f(void*, void*, void*)
    int executeInt(const char* f, void*, void*, void*);

    /// Execute f(void*, void*, void*, void*)
    int executeInt(const char* f, void*, void*, void*, void*);

    /// Execute f(void*, void*, void*, void*, void*)
    int executeInt(const char* f, void*, void*, void*, void*, void*);

    /** Retrieves the given symbol from the shared library. No name
        mangling is applied to the symbol name. */
    void* getSymbol(const char* name);

    /** Ensure the given library name match the platform required name.
        I.E: hxcore -> hxcore.dll on windows
             hxcore -> libhxcore.so on linux 
             libhxcore.so -> hxcore.dll on windows*/
    static McFilename fixName(const McFilename& name);
  protected:
    int tryOpen(const char* path, McString& msg);

    void fixPath(McFilename& path);

#if defined(_WIN32)
    HINSTANCE handle;
#elif defined(__hpux) && defined(HPUX_USE_SHL)
    shl_t handle;
#else
    void* handle;
#endif

public:
    /// Verbose mode: 0=report failure of open() (default), 1=debug mode
    static int verbose;

    /** List of paths where to look for shared libraries, used by the
        open method. */
    static McDArray<char*> dsoSearchPath;
};

#endif

/// @}
