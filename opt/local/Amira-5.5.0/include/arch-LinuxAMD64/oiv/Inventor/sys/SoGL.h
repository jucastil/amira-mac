/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Oct 2009)
**=======================================================================*/
#if !defined( SO_GL_H )
#define SO_GL_H

#if !defined(GLEW_MX)
// Open Inventor use Multi-thread/context glew implementation
#define GLEW_MX
#endif

// GLEW generic dispatch mechanism.
#ifdef GLEW_MX
#  define glewGetContext SoGLContext::glewGetCurrentContextIV
#  if defined (_WIN32)
#    define wglewGetContext SoGLContext::wglewGetCurrentContextIV
#  elif !defined(__APPLE__) || defined(GLEW_APPLE_GLX)
#    define glxewGetContext SoGLContext::glxewGetCurrentContextIV
#  endif // _WIN32
#endif // GLEW_MX

#include <Inventor/sys/glew.h>

#include <Inventor/devices/SoGLContext.h>


#if defined(_WIN32)
#  include <Inventor/sys/wglew.h>
#else
#  define APIENTRY
#  define WINGDIAPI
#endif

#endif // SO_GL_H
