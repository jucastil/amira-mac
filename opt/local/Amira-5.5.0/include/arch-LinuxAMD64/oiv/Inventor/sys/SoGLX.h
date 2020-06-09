/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined(SO_GLX_H)
#define SO_GLX_H

#include <Inventor/sys/SoGL.h>

#if defined(_WIN32)
#  include <Inventor/sys/wglew.h>
#else

#ifdef __APPLE__
#  include <OpenGL/OpenGL.h>
#  include <OpenGL/gl.h>
#else

# if !defined(SOWX)
#   include <X11/Intrinsic.h>
# endif

#  include <Inventor/sys/glxew.h>
#endif

//solve conflict between Qt and X11
#if defined(SOQT)

#    undef KeyPress
#    undef KeyRelease

// For SoQGLWidget
#    undef CursorShape

// For DialogViz qt widgets from QtGui
#if defined(Bool)
   typedef Bool X11_Bool;
#endif

#    undef Bool

// For QDir
#    undef Unsorted

// For QSlider
#    undef Above
#    undef Below

// For QStyleOption
#    undef None
// We need None sometimes...
#define  X11_None 0L

// #    undef FocusOut
// #    undef FocusIn
// #    undef Above

//solve conflict about INT32 and INT8 both defined into Qt and X11
#  define INT32 X11_INT32
#  define INT8 X11_INT8
#  undef INT32
#  undef INT8

#endif // InventorQt4_EXPORTS

#endif

#endif // SO_GLX_H
