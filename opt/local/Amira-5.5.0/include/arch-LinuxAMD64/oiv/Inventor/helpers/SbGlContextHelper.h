/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Benjamin GRANGE (Dec 2008)
**=======================================================================*/


#ifndef SB_GL_CONTEXT_HELPER_H
#define SB_GL_CONTEXT_HELPER_H

#include <Inventor/SbBase.h>

#if defined(_WIN32)
#elif defined(__APPLE__)
typedef struct _CGLContextObject *CGLContextObj;
typedef struct _CGLPixelFormatObject *CGLPixelFormatObj;
typedef unsigned int CGDirectDisplayID;
#else
typedef struct _XDisplay Display;
typedef unsigned long GLXDrawable;
typedef unsigned long GLXPixmap;
#ifdef __sun
typedef struct __glXContextRec *GLXContext;
#else
typedef struct __GLXcontextRec *GLXContext;
#endif
typedef unsigned long GLXFBConfigID;
typedef unsigned long GLXWindow;
typedef unsigned long GLXPbuffer;
typedef unsigned long Colormap;
typedef unsigned long Pixmap;
typedef unsigned long Window;
#if !defined(BUILDING_SB_GL_CONTEXT_HELPER)
typedef struct __GLXFBConfigRec *GLXFBConfig;
#endif
#endif

class SoGLContext;

/**
 * Class encapsulating information about an OpenGL context:
 * a handle on an OpenGL context and its id.
 */
class SbGLShareContext
{
public:
  /** Handle on OpenGL context */
  SoGLContext *shareContext;
  /**
   * Corresponding shared context Id
   * managed by upper layer viewer class.
   */
  int shareContextID;

SoINTERNAL public:

  /** [OIVJAVA-WRAPPER VISIBILITY{Public}] */
  SbGLShareContext();

  /** [OIVJAVA-WRAPPER VISIBILITY{Public}] */
  SbGLShareContext(SoGLContext *shareContext, int shareContextID);

  /** [OIVJAVA-WRAPPER VISIBILITY{Public}] */
  SoGLContext * getContext();

  /** [OIVJAVA-WRAPPER VISIBILITY{Public}] */
  int getContextGroupId();
};


inline
SbGLShareContext::SbGLShareContext()
{
  shareContext = NULL;
  shareContextID = 0;
}

inline 
SbGLShareContext::SbGLShareContext(SoGLContext* _shareContext, int _shareContextID)
{
  shareContext = _shareContext;
  shareContextID = _shareContextID;
}

inline SoGLContext * 
SbGLShareContext::getContext()
{
  return shareContext;
}

inline int
SbGLShareContext::getContextGroupId()
{
  return shareContextID;
}

/**
 * Platform indepent functions for OpenGL context handling
 */
namespace SbGlContextHelper
{
#ifdef _WIN32
  typedef HDC Display;
  typedef HGLRC GLContext;
  typedef PIXELFORMATDESCRIPTOR* VisualInfo;
  typedef int Drawable;
#elif defined(__APPLE__)
  #undef Display
  typedef unsigned int Display;
  typedef CGLContextObj GLContext;
  typedef CGLPixelFormatObj VisualInfo;
  typedef void* Drawable;
#else
  typedef ::Display* Display;
  typedef GLXContext GLContext;
  typedef void* VisualInfo;
  typedef GLXDrawable Drawable;
#endif

  /** Return the current active context */
  INVENTORGL_API GLContext getCurrentContext();

  /** Return the current active display */
  INVENTORGL_API Display getCurrentDisplay();

  /** Return the current active drawable */
  INVENTORGL_API Drawable getCurrentDrawable();

  /** 
   * Returns the VisualInfo used for the specified drawable.
   * Use releaseVisualInfo() to free the returned pointer.
   */
  
  INVENTORGL_API VisualInfo getWindowVisualInfo(Display dpy, Drawable drawable);

  
  /** Release a VisualInfo returned by getWindowVisualInfo() */
  INVENTORGL_API void releaseVisualInfo(VisualInfo visualInfo);

  /**
   * Create a new context
   * @param dpy specifies the display (device context on win32)
   * @param vis specifies the visual (must be set to 0 on win32)
   * @param shareList context to sharelist with (0 means no sharing); it is not used on win32, use shareContext for sharing.
   * @param direct set to true for direct rendering (meaningless on win32)
   * @param layer Layer on which we want to create the context, 0 (default) for the main plane.
   */
  INVENTORGL_API GLContext createContext(Display dpy, VisualInfo vis, GLContext shareList, 
                                         bool direct, int layer = 0);

  /** Destroy given context */
  INVENTORGL_API bool destroyContext(Display dpy, GLContext ctx);

  /**
   * Make given context current
   * @param dpy specifies the display (device context on win32)
   * @param drawable specifies a drawable (0 on win32)
   * @param ctx specifies the OpenGL context to switch to.
   */
  INVENTORGL_API bool makeCurrent(Display dpy, Drawable drawable, GLContext ctx);

  /**
   * Tries to share passed context
   * @param dpy specifies the display (device context on win32)
   * @param srcCtx specifies the previously existing context
   * @param newCtx specifies the context to share with previously existing context srcCtx.
   * This function only applies on Microsoft Windows Platform.
   * Please refer to wglShareLists() to know more about context sharing.
   */
  INVENTORGL_API bool shareContext( Display dpy, GLContext srcCtx, GLContext newCtx );
}

#endif
