/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_QT_DEF_
#define _SO_QT_DEF_

#include <Inventor/helpers/SbGlContextHelper.h>

// avoid conflict with declaration made in X headers
//#if defined (Bool)
//#undef Bool
//#endif

#if !defined(Widget)

#if defined(SoWidget)
# undef SoWidget
#endif

#define SoWidget QWidget*

// Defined for compatibility purpose
// We disbale this when internally compiling OivSuite
#ifndef LIBRARYBUILD
#  define Widget QWidget*
#endif

#endif


//
// WIN32
// 
#ifdef _WIN32

// Redefine X data types in _WIN32 terms
#define XColor      UINT
#define Boolean     BOOLEAN
#define Colormap    UINT
typedef SbGlContextHelper::Display Display; 
#define XVisualInfo PIXELFORMATDESCRIPTOR
#define WindowQt    HWND
#define GLXContext  HGLRC
#define Hdc         HDC

// Event types
#define XEvent      MSG

// Redefine Xt and Motif data types in _WIN32 terms
#define XtPointer      PVOID
#define XtEventHandler FARPROC
#define XtAppContext   UINT

#include "tchar.h"

// XVisualInfo corresponds to PIXELFORMATDESCRIPTOR rather than
// "pixel format" because under Windows, pixel formats are per
// drawable rather than per display (like visuals under X).  In
// other words, under Windows we can't get the description of a
// pixel format unless we have a valid device context and that
// is often inconvenient.
//
// Note that PIXELFORMATDESCRIPTOR also takes the place of GLX's
// "attribList" (which it is conceptually closer to).

#define XVisualInfo PIXELFORMATDESCRIPTOR

//
// APPLE
// 
#elif defined __APPLE__

#undef Display
typedef int Display;
#define XColor      UINT
typedef WId WindowQt;
typedef WId Window;

// Event types
typedef struct OpaqueEventHandlerCallRef* EventHandlerCallRef;
#define XEvent     OpaqueEventHandlerCallRef

#define XtPointer      void*
#define XtEventHandler void*

//
// UNIX
// 
#else

#define WindowQt Window
typedef void* XtPointer;
typedef char Boolean;
typedef union _XEvent XEvent;
typedef void (*XtEventHandler) (struct _WidgetRec*, void*, XEvent*, Boolean*);

// we use XColorPointer typedef to avoid X header dependency in puvlic API headers
// XColorPointer is equivalent to XColor*
typedef void* XColorPointer;

#endif 

#endif //_SO_QT_DEF_
