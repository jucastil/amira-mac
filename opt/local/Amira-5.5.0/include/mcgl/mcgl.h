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

/// @addtogroup mcgl mcgl
/// @{
#ifndef __MCGL_H__
#define __MCGL_H__

#include "mcglAPI.h"

#ifndef GLEW_MX
    #define GLEW_MX
#endif

#include <Inventor/sys/glew.h>
#if defined(HX_OS_WIN)
    #include <Inventor/sys/wglew.h>
#elif defined(HX_HAS_X11)
    #include <Inventor/sys/glxew.h>
    #ifdef CursorShape
        #undef CursorShape
    #endif
#endif

/** \file
    Encapsulates the OpenGL extension wrangler.

    This file encapsulates the OpenGL extension wrangler library (GLEW).
    GLEW provides efficient run-time mechanisms for determining which
    OpenGL extensions are supported on a target platform. OpenGL core
    and extension functionality are all exposed through this header file.
    In particular, this file provides entry points for OpenGL extension
    functions which normally can only be accessed indirectly by calling
    wglGetProcAddress() or glXGetProcAddress(). In order to check if an
    OpenGL function is actually implemented on a target platform GLEW
    provides macros to check for a particular version of OpenGL, e.g.,
    GLEW_VERSION_1_3 for OpenGL 1.3, or macros to check for a particular
    extension, i.e., GLEW_ARB_vertex_program for ther vertex program
    extension. In addition to entry points for OpenGL extension functions
    GLEW also defines all associated OpenGL constants.

    In addition to the GLEW functionality this file provides a simple
    initialization mechanism allowing to use GLEW in a multi-threaded
    environment with different OpenGL contexts. It also provides the
    macros MCCK_GL, MCGL_CK_N, and MCGL_CK_C which can be used to execute
    an OpenGL command and check the OpenGL error stack afterwards. In case
    of an error a McResult error code is returned, a user-defined error
    notification function is called, or an exception is thrown.

    Instead of including the standard OpenGL header <GL/gl.h> or the
    original GLEW header <GL/glew.h> you should include <mcgl/mcgl.h>.
    If you can't avoid to include the standard OpenGL headers because
    they are used in a third-party library, you have to make sure that
    <mcgl/mcgl.h> is included first.

    Example:

\code
    #include <mcgl/mcgl.h>

    void main()
    {
        ...
        // activate first render context
        wglMakeCurrent(...);
        mcglSetContext(1); // sets function pointer table

        if ( glewIsSupported("GL_VERSION_1_3 GL_ARB_point_parameters") ) {
            ...
            glActiveTexture(...); // part of OpenGL 1.3
            glPointParameterfARB(...);
            ...
        }

        // same check using predefined macros (faster)
        if ( GLEW_VERSION_1_3 && GLEW_ARB_point_parameters ) {
            ...
            glActiveTexture(...); // part of OpenGL 1.3
            glPointParameterfARB(...);
            ...
        }

        // activate second render context
        wglMakeCurrent(...);
        mcglSetContext(2); // sets function pointer table

        if ( WGLEW_ARB_buffer_region ) {
            ...
            wglCreateBufferRegionARB(...);
            ...
        }

        // switch back to first render context
        wglMakeCurrent(...);
        mcglSetContext(1); // uses cached function pointer table
        ...

        MCGL_CK_N( glFoo(...) ); // calls McResult::notify() if glGetError()!=0
    }
\endcode
*/

#ifdef __cplusplus
extern "C" {
#endif

    /* Overrides GLEW functions */
MCGL_API GLEWContext* glewGetContext(bool);
#if defined(HX_OS_WIN)
MCGL_API WGLEWContext* wglewGetContext();
#elif defined(HX_HAS_X11)
MCGL_API SoGLXEW::GLXEWContext* glxewGetContext();
#endif


/** Initializes the mcgl context of the calling thread. This function
    has to be called after a new OpenGL rendering context has been made the
    thread's current rendering context by calling wglMakeCurrent() on Windows
    or glXMakeCurrent() on X11 platforms. The function queries the OpenGL
    capabilities of the current rendering context and initializes the internal
    GLEW function pointer table. */
MCGL_API void mcglInitContext();

/** Initializes or sets the mcgl context of the calling thread. This function
    can be used instead of mcglInitContext() if you are working with different
    OpenGL rendering contexts, and you know that the OpenGL capabilities of
    some of these rendering contexts are identical. It allows you to reuse
    existing mcgl contexts for different such shareable rendering contexts.

    The library maintains a list of mcgl contexts per thread. Each mcgl context
    is identified by a unique number called cacheId. This function makes the
    mcgl context associated with cacheId the calling thread's current mcgl
    context. If there is not yet an mcgl context associated with cacheId a new
    context will be created and initialized based on the current OpenGL rendering
    context. After calling wglMakeCurrent() or glXMakeCurrent() for a different
    OpenGL rendering context, you can reuse an existing mcgl context by calling
    mcglSetContext() with a particular cacheId. It is the responsibility
    of the caller to identify shareable OpenGL rendering contexts and to assign
    them a unique cacheId. Rendering contexts are shareable if they provide
    the same OpenGL capabilities. On Windows also the pixel formats should be
    identical (see documentation of wglGetProcAddress()). */
MCGL_API void mcglSetContext(unsigned int cacheId);

/** CacheId of the current bound context. UINT_MAX if there is none. */
MCGL_API unsigned int mcglGetContext();

/** Clears the mcgl context associated with cacheId. */
MCGL_API void mcglClearContext(unsigned int cacheId);

/** Removes all mcgl contexts. */
MCGL_API void mcglClearAllContexts();

/// Check if GLSL vertex and fragment shaders are available for all contexts.
MCGL_API bool mcglGLSLAvailableAllContexts();

/// Check if GLSL vertex and fragment shaders are available for \c cacheId.
MCGL_API bool mcglGLSLAvailable(unsigned int cacheId);

 /// Check if vertex buffer objects are available for all contexts.
MCGL_API bool mcglVBOsAvailableAllContexts();

/// Check if vertex buffer objects are available for \c cacheId.
MCGL_API bool mcglVBOsAvailable(unsigned int cacheId);

/// Check if the OpenGL vendor is ati
MCGL_API bool mcglIsVendorATI();

/// Check if the OpenGL vendor is NVIDIA
MCGL_API bool mcglIsVendorNVIDIA();


#ifdef __cplusplus
}
#endif

/* ------------------------------------------------------------------------- */

#include <mclib/McResult.h>

/** Helper function used by the MCGL_CK macros. It calls glGetError() in
    order to check if an OpenGL error occurred. If this is the case, it
    creates. Depending on the value of \c action, the error code is simply
    returned (action=0), McResult::notify() method is called (action=1), or
    an exception is thrown by calling McResult::check() (action=2).
    \sa MCGL_CK MCGL_CK_N MCGL_CK_C */
MCGL_API McResult
mcglErrorCheck(const char* cmd, const char* file, unsigned int line, int action);

/** Checked execution of an OpenGL function. This macro executes an OpenGL
    function and then checks if the function generated an OpenGL error. If
    this is the case an appropriate McResult error code is returned. If no
    error was generated McOK is returned. \sa McResult */
#define MCGL_CK(cmd) ( cmd, mcglErrorCheck(#cmd, __FILE__, __LINE__, 0) )

/** Checked execution of an OpenGL function with error notification. This
    macro behaves like MCGL_CK, but in case of an OpenGL error it calls
    McResult::notify() which in turn invokes a user-defined notification
    callback. \sa McResult */
#define MCGL_CK_N(cmd) ( cmd, mcglErrorCheck(#cmd, __FILE__, __LINE__, 1) )

/** Checked execution of an OpenGL function throwing an exception. This
    macro behaves like MCGL_CK, but in case of an OpenGL error it calls
    McResult::check() which in turn throws an exception with the McResult
    as a parameter. \sa McResult*/
#define MCGL_CK_C(cmd) ( cmd, mcglErrorCheck(#cmd, __FILE__, __LINE__, 2) )

#define MCGL_CK0   mcglErrorCheck("", __FILE__, __LINE__, 0)
#define MCGL_CK_N0 mcglErrorCheck("", __FILE__, __LINE__, 1)
#define MCGL_CK_C0 mcglErrorCheck("", __FILE__, __LINE__, 2)

/* ------------------------------------------------------------------------- */

#if defined(HX_OS_WIN)
#  define mcglGetProcAddress(name) wglGetProcAddress((LPCSTR)name)
#else
#  if defined(__APPLE__)
#    define mcglGetProcAddress(name) NSGLGetProcAddress(name)
#  else
#    if defined(__sgi) || defined(__sun) || defined (HX_OS_HPUX)
       extern "C" void* dlGetProcAddress (const GLubyte* name);
#      define mcglGetProcAddress(name) dlGetProcAddress((const GLubyte*)name)
#    else /* __linux */
#      define mcglGetProcAddress(name) (*glXGetProcAddressARB)((const GLubyte*)name)
#    endif
#  endif
#endif

/* ------------------------------------------------------------------------- */

#include "mcglShaderARB.h"
#include "mcglShaderGLSL.h"

#include <mclibthreaded/McMutex.h>

#include "McDeferredDeleteMap.h"
#include "McTexture.h"

#include "McShaderUniform.h"
#include "McShaderMacro.h"
#include "McShader.h"
#include "McShaderTechnique.h"
#include "McShaderProgram.h"


#endif /* __MCGL_H__ */

/// @}
