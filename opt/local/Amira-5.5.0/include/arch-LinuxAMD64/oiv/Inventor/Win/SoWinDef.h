/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_WIN_DEF_
#define _SO_WIN_DEF_

#include <Inventor/SbBasic.h>

#ifdef _WIN32
#  include <Inventor/Win/SoWinBeginStrict.h>
#  include <windows.h>
#endif
// Redefine X data types in _WIN32 terms
#define ArgList  PLONG

#define Boolean  BOOLEAN

#define WBOOL   int

#define Colormap UINT

#define Cursor   Hcursor

#define WindowPtr HWND

// Stuff for SoWinMouse/Keyboard -- NOTYET: make constants match X
#define EventMask UINT
#define   ButtonPressMask   0x01
#define   ButtonReleaseMask 0x02
#define   PointerMotionMask 0x04
#define   ButtonMotionMask  0x08
#define   KeyPressMask      0x10
#define   KeyReleaseMask    0x20

#define GLXContext HGLRC

#define KeySym UINT

#ifndef True
#define True  TRUE
#endif

#ifndef False 
#define False FALSE
#endif

//#if defined(_AFX)
//#define Widget  PVOID
//#define Window  PVOID
//#define Hinst   PVOID
//#define Hwnd    PVOID
//#define Hdc     PVOID
//#define Hcursor PVOID
//#define Hmenu   PVOID
//#define Hrsrc   PVOID
//#else

#ifndef Widget
#define SoWidget HWND

// Defined for compatibility purpose
// We disbale this when internally compiling OivSuite
#ifndef LIBRARYBUILD
#  define Widget HWND
#endif

#endif

#define Window  HWND
#define Hinst   HINSTANCE
#define Hwnd    HWND
#define Hdc     HDC
#define Hcursor HCURSOR
#define Hmenu   HMENU
#define Hrsrc   HRSRC
//#endif

#define Region HRGN
#define Pixmap HBITMAP

#define Atom ULONG
#define Time time_t

#define XColor UINT

// Event types
#define XEvent       MSG
#ifndef XAnyEvent
#  define XAnyEvent    MSG
#endif
#define XButtonEvent MSG
#define XKeyEvent    MSG
#define XMotionEvent MSG
#define XMouseWheelEvent MSG

// Key codes (basically the same but with different names)
#define XK_ESCAPE   VK_ESCAPE
#define XK_HOME     VK_HOME
#define XK_LEFT     VK_LEFT
#define XK_UP       VK_UP
#define XK_RIGHT    VK_RIGHT
#define XK_DOWN     VK_DOWN
#define XK_s        83

// Redefine Xt and Motif data types in _WIN32 terms
#define XmString char*

#define XtAppContext UINT

#define XtEventHandler FARPROC

#define XtIntervalId UINT

#define XtPointer PVOID

#define XmAnyCallbackStruct void 

#define XtWorkProcId UINT

// XVisualInfo corresponds to PIXELFORMATDESCRIPTOR rather than
// "pixel format" because under Windows, pixel formats are per
// drawable rather than per display (like visuals under X).  In
// other words, under Windows we can't get the description of a
// pixel format unless we have a valid device context and that
// is often inconvenient.
//
// Note that PIXELFORMATDESCRIPTOR also takes the place of GLX's
// "attribList" (which it is conceptually closer to).   --mmh

#define XVisualInfo PIXELFORMATDESCRIPTOR


////////////////////////////////////////////////////////////////////////////
// Functions to implement SoWin on Win32 
//
// Supplying these dummy functions is less ugly than ifdef'ing
// the SoWin code in dozens of places.

INVENTORW_API extern XtAppContext XtWidgetToApplicationContext( SoWidget w );

INVENTORW_API extern UINT *XtDisplay( SoWidget w );

INVENTORW_API extern UINT XtScreen( SoWidget w ) ;

INVENTORW_API extern Window RootWindowOfScreen(UINT s) ;

INVENTORW_API extern Boolean XtIsShell( SoWidget w );

INVENTORW_API extern Boolean XtIsRealized( SoWidget w );

INVENTORW_API extern SoWidget XtParent( SoWidget w );

INVENTORW_API extern Window XtWindow( SoWidget w );

INVENTORW_API extern SoWidget XtWindowToWidget( UINT *d, Window w );


////////////////////////////////////////////////////////////////////////////
// Miscellaneous SGI functions not found in _WIN32

#include "tchar.h"

#undef strdup
#define strdup _tcsdup

#ifdef _WIN32
#include <Inventor/Win/SoWinEndStrict.h>
#endif //_WIN32
#endif //_SO_WIN_DEF_
