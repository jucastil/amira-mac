/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Alain Dumesny (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_WINDOW_ELEMENT
#define  _SO_WINDOW_ELEMENT

#include <Inventor/elements/SoSubElement.h>
#include <Inventor/helpers/SbGlContextHelper.h>

class SoGLRenderAction;

/**
*   Stores the current window attributes.
*
*   @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current window attributes. The current window
*   is defined as the OpenGL window underneath the cursor - or NULL if the
*   cursor is not over an OpenGL window.
*
*   @SEE_ALSO
*   SoWinRenderArea, SoXtRenderArea, SoQtRenderArea
*/

SoEXTENDER_Documented class INVENTOR_API SoWindowElement : public SoElement {

  SO_ELEMENT_HEADER(SoWindowElement);

 public:
  /**
  *  Always returns TRUE, since this element should never be a
  *  criterion for cache invalidation.
  */
  virtual SbBool      matches(const SoElement *elt) const;

  /**
  *  Create and return a copy of this element.
  */
  virtual SoElement   *copyMatchInfo() const;

  // Sets the window, context, and glRenderAction info
#ifdef _WIN32
  /**
  *  Under Windows, the types are actually:
  *  Window     = HWND
  *  GLXContext = HGLRC
  *  Display    = HDC
  *
  *  So why don't we just use those types?
  *  In non-MFC Win32 programs, these types are all "void *",
  *  but MFC redefines these types to "struct _something *".
  *  So if we used HWND etc here, the mangled names would not
  *  match for MFC programs.  Better to just force void*.
  *
  *  Note: The fourth argument is "Display".  On Windows we
  *        don't normally use this for anything, but here it
  *        is convenient to use it to store the window's DC,
  *        since that value is needed to call SbGlContextHelper::makeCurrent.
  */

  static void         set(SoState *state, void *window, void *context,
                          void *display, SoGLRenderAction *glAction);

#elif defined __APPLE__
  /**
  *  Sets the window, context, and glRenderAction info.
  */
  static void         set(SoState *state, SbGlContextHelper::Drawable window, SbGlContextHelper::GLContext context,
                          SbGlContextHelper::Display display, SoGLRenderAction *glAction);
#else
  /**
  *  Sets the window, context, and glRenderAction info.
  */
  static void         set(SoState *state, Window window, SbGlContextHelper::GLContext context,
                          SbGlContextHelper::Display display, SoGLRenderAction *glAction);
#endif

#ifdef _WIN32
  /**
  *  Returns the current window, context, and glRenderAction.
  */
  static void get(SoState *state, void *&window, void *&context,
                  void *&display, SoGLRenderAction *&glAction);

#elif defined __APPLE__
  /**
  *  Returns the current window, context, and glRenderAction.
  */
  static void get(SoState *state, SbGlContextHelper::Drawable &window, SbGlContextHelper::GLContext &context,
                  SbGlContextHelper::Display &display, SoGLRenderAction *&glAction);

#else
  /**
  *  Returns the current window, context, and glRenderAction.
  */
  static void get(SoState *state, Window &window, SbGlContextHelper::GLContext &context,
                  SbGlContextHelper::Display &display, SoGLRenderAction *&glAction);
#endif

  /**
  *  Push.
  */
  virtual void    push(SoState *state);

 SoINTERNAL public:
  // Initializes the SoWindowElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:

#ifdef _WIN32
  SbGlContextHelper::GLContext context;
  void*   window;
  void *display;
#elif defined __APPLE__
  SbGlContextHelper::GLContext context;
  SbGlContextHelper::Drawable window;
  SbGlContextHelper::Display display;
#else
  Window              window;
  SbGlContextHelper::GLContext context;
  SbGlContextHelper::Display display;
#endif

  SoGLRenderAction    *glRenderAction;

  virtual     ~SoWindowElement();
};

#endif /* _SO_WINDOW_ELEMENT */
