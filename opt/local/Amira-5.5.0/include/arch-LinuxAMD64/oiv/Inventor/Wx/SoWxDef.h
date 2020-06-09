/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jul 2007)
**=======================================================================*/


#ifndef SO_WX_DEF
#define SO_WX_DEF

#include <Inventor/helpers/SbGlContextHelper.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Header: SoWxDef
//
//////////////////////////////////////////////////////////////////////////////

#ifndef Widget
#define SoWidget wxWindow*

// Defined for compatibility purpose
// We disbale this when internally compiling OivSuite
#ifndef LIBRARYBUILD
#  define Widget wxWindow*
#endif

#endif

#ifdef _WIN32

// Redefine X data types in _WIN32 terms
#define XColor      UINT
#define Boolean     BOOLEAN
#define Colormap    UINT
typedef SbGlContextHelper::Display Display;
#define XVisualInfo PIXELFORMATDESCRIPTOR
#define WindowWx    HWND
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

#else //UNIX

#define WindowWx Window
typedef void* XtPointer;
typedef char Boolean;
typedef union _XEvent XEvent;
typedef void (*XtEventHandler) (struct _WidgetRec*, void*, XEvent*, Boolean*);

#endif 

#endif //SO_WX_DEF
