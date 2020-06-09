/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#if defined(_WIN32)
#  include <Inventor/MP/Win/SoWinMPGLWidget.h>
#else // _WIN32

#ifndef _SO_XT_MP_GL_WIDGET_H_
#define _SO_XT_MP_GL_WIDGET_H_

#include <Inventor/helpers/SbGlContextHelper.h>
#include <Inventor/Xt/SoXtComponent.h>

/*
 * Defines used when specifying the glModes flag to the constructor.
 * (used instead of the glx.h defines which do overlap)
 */
#define SO_GLX_RGB (1<<0)
#define SO_GLX_DOUBLE (1<<1)
#define SO_GLX_ZBUFFER (1<<2)
#define SO_GLX_OVERLAY (1<<3)
#define SO_GLX_STEREO (1<<4)

#include <Inventor/MP/Xt/SbConfig.h>

class SoGLContext;

//////////////////////////////////////////////////////////////////////////////
//
// Class: SoXtMPGLWidget
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Component for OpenGL rendering.
 *
 * @ingroup ScaleVizMultiPipe
 *
 * @DESCRIPTION
 *   This abstract base class provides a C++ wrapper around the GLwMDraw window
 *   object. It allows OpenGL rendering to be performed within a Motif window and is
 *   used by the SoXtMPRenderArea. SoXtMPGLWidget uses a parent window with two separate
 *   GLwMDraw window objects (one for single and one for double buffering), with
 *   routines to return the appropriate windows.
 *
 *   Subclasses only need to redefine the redraw() routine for rendering and
 *   processEvent() routine if they are interested in receiving X events.
 *
 * @SEE_ALSO
 *    SoXtComponent,
 *    SoXtMPRenderArea
 *
 *
 */

class INVENTORXT_API SoXtMPGLWidget : public SoXtComponent {

 public:


  unsigned long getOverlayTransparentPixel();
  int getOverlayColorMapSize();
  int getColorMapSize();

  /**
   * Gets the current normal GL window, which is
   * needed as an argument to glXMakeCurrent() when drawing in the normal
   * planes.
   *
   * Note: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   */
  virtual Window getNormalWindow();

  /**
   * Gets the current overlay GL window, which is
   * needed as an argument to glXMakeCurrent() when drawing in the
   * overlay planes.
   *
   * Note: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   */
  Window getOverlayWindow();

  /**
   * Gets the current normal context, which is
   * needed as an argument to glXMakeCurrent() when drawing in the normal
   * planes.
   *
   * Note: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   */
  SoGLContext* getNormalContext() { return ctxNormal; }
  /**
   * Gets the current overlay context, which is
   * needed as an argument to glXMakeCurrent() when drawing in the
   * overlay planes.
   *
   * Note: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   */
  SoGLContext* getOverlayContext() { return ctxOverlay; }

  /**
   * Gets the current normal widget, which is
   * needed as an argument to glXMakeCurrent() when drawing in the normal
   * planes.
   *
   * Note: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   */
  SoWidget getNormalWidget() { return (glModes & SO_GLX_DOUBLE) ? doubleBufferWidget : singleBufferWidget; }
  /**
   * Gets the current overlay widget, which is
   * needed as an argument to glXMakeCurrent() when drawing in the
   * overlay planes.
   *
   * Note: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   */
  SoWidget getOverlayWidget() { return overlayWidget; }

  //
  // Specify exactly what the visual should be for the normal and overlay
  // window. This allows the user to create all possible visuals supported
  // by OpenGL. The XVisualInfo structure should be a valid OpenGL visual
  // returned by glXChooseVisual().
  //
#if defined(sun) || defined(__linux__)
  virtual void setSunOverlayBackgroundIndex();
#endif
  /**
   * Specify exactly what the visual should be for the normal window.
   * This allows the user to create all possible visual supported by OpenGL. The
   * @B XVisualInfo @b structure should be a valid OpenGL visual returned by
   * @B glXChooseVisual @b(). This structure will be copied by the SoXtMPGLWidget; the
   * application is responsible for freeing the visual info with @B XFree @b() when
   * done. (The methods for setting the visual are virtual so that derived classes
   * can know when the visual is changing.)
   */
  virtual void setNormalVisual(XVisualInfo *vis);
  /**
   * Returns the visual for the normal window.
   */
  XVisualInfo *getNormalVisual();
  /**
   * Specify exactly what the visual should be for the overlay window.
   * This allows the user to create all possible visual supported by OpenGL. The
   * @B XVisualInfo @b structure should be a valid OpenGL visual returned by
   * @B glXChooseVisual @b(). This structure will be copied by the SoXtMPGLWidget; the
   * application is responsible for freeing the visual info with @B XFree @b() when
   * done. (The methods for setting the visual are virtual so that derived classes
   * can know when the visual is changing.)
   */
  virtual void setOverlayVisual(XVisualInfo *vis);
  /**
   * Returns the visual for the overlay window.
   */
  XVisualInfo *getOverlayVisual();

  /**
   * Routine that dynamically changes between single and double buffering. Default
   * is double buffer off. (The SoXtMPRenderArea subclass makes it double buffer by
   * default.)
   */
  virtual void setDoubleBuffer(SbBool onOrOff);
  /**
   * Returns whether double buffering is on or off.
   */
  SbBool isDoubleBuffer()
    { return ((glModes & SO_GLX_DOUBLE) ? 1 : 0); }
  /**
   * Shows and hides the border around the OpenGL windows (thickness 3). Default is no
   * border (FALSE). (The SoXtMPRenderArea subclass defaults turns the border on by
   * default.)
   */
  //
  // shows/hides a border of thickness 3 around the glx widgets. This
  // if OFF by default, but turned on by the render area.
  //
  void setBorder(SbBool onOrOff);
  /**
   * Returns whether the border is on or off.
   */
  SbBool isBorder() const { return borderSize != 0; }

  /**
   * Sets drawing to the front buffer. Controls drawing to the front buffer when
   * an obscured portion of the window is exposed. Default: TRUE.
   */
  void setDrawToFrontBufferEnable(SbBool enableFlag);

  /**
   * Queries drawing to the front buffer.
   */
  SbBool isDrawToFrontBufferEnable() const { return enableDrawToFrontBuffer; }

  /**
   * Queries the size of the virtual multipipe window.
   */
  SbVec2s getVirtualSize(void) { return mpConfig->getVirtualSize(); }

  /**
   * Convert a point in native window coordinates, typically
   * with Y increasing down, to Open Inventor (and OpenGL)
   * device coordinates with Y increasing up.
   *
   * The @I Window @i parameter is not required (may be NULL)
   * unless using "InsideOut" mode.  In this case it is
   * necessary to determine which window's height to use
   * for the conversion.
   *
   * Typically this method is used to convert the position
   * of a window system event.
   */
  SbVec2s winToDC( int x, int y, Window w = NULL ) const;

  /**
   * Convert a point in Open Inventor device coordinates
   * (same as OpenGL - pixels with Y increasing up) to
   * normalized device coordinates (0..1).
   *
   * The @I Window @i parameter is not required (may be
   * NULL) unless using "InsideOut" mode.  In this case it
   * is necessary to determine which window's dimensions
   * to use for the conversion.
   */
  SbVec2f DCtoNDC( SbVec2s pos, Window w = NULL ) const;

  SoINTERNAL public:
  SoGLContext* m_glContext;

 SoEXTENDER public:

  // Starting with version 3.0, subclasses should no longer make direct
  // calls to glXMakeCurrent, glXSwapBuffers and glFlush.
  // For RemoteRendering we need to know when MakeCurrent is called
  // (marking the beginning of a frame) and when SwapBuffers or glFlush
  // is called (marking the end of a frame).
  // Subclasses should always use these generic methods.

  /** 
   * @deprecated No longer used. use bindNormalContext and unbindNormalContext
   * Makes the normal rendering context the current context.
   * @DEPRECATED_SINCE_OIV 8.1
   */
  SoDEPRECATED SbBool makeNormalCurrent();

  /**
   * Makes the normal rendering context the current context. 
   * Equivalent to makeNormalCurrent() call.
   */
  SbBool bindNormalContext();

  /**
   * unbind the current context (previously bind with bindNormalContext );
   */
  SbBool unbindNormalContext();

  SbBool swapNormalBuffers();
  SbBool makeOverlayCurrent();
  SbBool swapOverlayBuffers();
  void   flush();

  // check if the context is direct
  SbBool ctxIsDirect();

 protected:

  // Subclasses can pass in a bitwise OR specifying the GL modes
  // (e.g. SO_GLX_RGB | SO_GLX_DOUBLE | SO_GLX_ZBUFFER | SO_GLX_OVERLAY)
  // If buildNow is FALSE, this will not build its widget tree until
  // buildWidget() is explicity called; else, buildWidget() is called here.
  SoXtMPGLWidget(SoWidget parent = NULL,
                 const char *name = NULL,
                 SbBool buildInsideParent = TRUE,
                 int glModes = SO_GLX_RGB,
                 SbBool buildNow = TRUE);

#if defined(sun) || defined(__linux__) || defined(__hpux)
  SoXtMPGLWidget(SoWidget parent,
                 const char *name,
                 SbBool buildInsideParent,
                 int glModes,
                 SbBool buildNow,
                 SbBool connectionType);
#endif

  virtual ~SoXtMPGLWidget();

  // subclasses MUST redefine redraw() to draw in the normal bit planes.
  // redrawOverlay() should be defined if the overlay planes are being
  // used, and processEvent() should be defined if X events are being
  // received (see eventMask).
  virtual void redraw() = 0;
  virtual void redrawOverlay();
  virtual void processEvent(XAnyEvent *anyevent);

  // subclasses can redefine these to do something useful.
  // initGraphic() is called whenever a GLX window gets created
  // sizeChanged() is called whenever the window changes size
  // widgetChanged() is called whenever the widget is changed (i.e. at
  // initialization or after switching from single->double buffer)
  virtual void initGraphic();
  virtual void initOverlayGraphic();
  virtual void sizeChanged(const SbVec2s &newSize);
  virtual void widgetChanged(SoWidget newWidget);

  virtual void initViewportRegion(int);

  // sets/gets the size of the glx widget(s) - Note this size could be
  // different from the SoXtComponent::getSize() method which return
  // the size of the component, not necessary the same as the glx widget
  // window (because of extra stuff like the decoration in the viewers).
  void setGlxSize(SbVec2s newSize);
  const SbVec2s &getGlxSize() const { return glxSize; }

  // subclasses can use this routine as the event handler for any
  // devices they wish to get input from.
  static void eventHandler(SoWidget, SoXtMPGLWidget *, XAnyEvent *, Boolean *);

  // set/get stereo buffering visual. This routine (like setDoubleBuffer)
  // can be called interactively, althought slower since a new window
  // with the needed visual is always created on the fly.
  void setStereoBuffer(SbBool flag);
  SbBool isStereoBuffer()
    { return ((glModes & SO_GLX_STEREO) ? 1 : 0); }

  // returns TRUE if main window is in rgb mode (FALSE if color index)
  SbBool isRGBMode()
    { return ((glModes & SO_GLX_RGB) ? 1 : 0); }

#if defined(sun) || defined(__linux__)
  void allocCell(Display *display, Colormap cmap, XColor *colorcells,
                 int ncolors, int colorMapSize);
#endif

  // returns the display lists share group for given context:
  int getDisplayListShareGroup( SoGLContext* ctx );

  Colormap colorMap; // set when color index is used
  Colormap overlayColorMap; // set when overlay is used
  int colorMapSize;
  int overlayColorMapSize;

  SbBool waitForExpose; // prevent redraws until an expose is received
  SbBool drawToFrontBuffer; // used by RA to draw new scenes to front buffer

  // make those methods protected to enable the SoXtMPRenderArea to use them
  // directly when it needs to build the widget and get its resources.
  SoWidget buildWidget(SoWidget parent);
  SoWidget getGlxMgrWidget() { return mgrWidget; }

  unsigned long transparentPixel;

  int pipeContextIdOffset; // pipes should not reuse context ids
  void raiseMainViewer(SbBool); // raise/lower main viewer

  SbConfig *mpConfig;

  SbBool renderInFrontBuffer;

  virtual void onExpose();
  virtual void onOverlayExpose();
  virtual void onMPExpose();
  virtual void onMPOverlayExpose();

 private:
  // local vars
  SoWidget mgrWidget;
  SoWidget doubleBufferWidget, singleBufferWidget, overlayWidget;
  SoGLContext* ctxNormal, *ctxOverlay, *ctxSingle, *ctxDouble;
  SbVec2s glxSize; // size of glx widgets which is always up to date
  int *attribList;
  int glModes;
  int borderSize;
  SbBool enableDrawToFrontBuffer;

  // specify if sizeChanged() should be called when an expose event
  // is received (as opposed to when a resize event is received, where
  // the window hasn't yet been maped to the new size).
  // ??? a GlxDraw bug ?
  SbBool windowResized;

  SbBool directConnection;

  // creates a GLX widget of the correct current type and get the current
  // set of windows, color maps, etc...
  void buildNormalGLXWidget(XVisualInfo *vis = NULL);
  void buildOverlayGLXWidget(XVisualInfo *vis = NULL);
#if defined(sun) || defined(__linux__)
  void buildSunOverlayWindow(SoWidget glx, SoXtMPGLWidget *p);
#endif
  void destroyNormalWindows();
  void destroyGLXWidget(SoWidget &w, SoGLContext* &ctx, SbBool normalWindow);

  // callbacks from glx widget
  static void ginitCB(SoWidget, SoXtMPGLWidget *, XtPointer);
  static void overlayGinitCB(SoWidget, SoXtMPGLWidget *, XtPointer);
  static void exposeCB(SoWidget, SoXtMPGLWidget *, XtPointer);
  static void overlayExposeCB(SoWidget, SoXtMPGLWidget *, XtPointer);
  static void resizeCB(SoWidget, SoXtMPGLWidget *, XtPointer);


 SoINTERNAL public:
  static void mpGinitCB(SoWidget, SoXtMPGLWidget *, XtPointer);
  static void mpExposeCB(SoWidget, SoXtMPGLWidget *, XtPointer);
  static void mpOverlayGinitCB(SoWidget, SoXtMPGLWidget *, XtPointer);
  static void mpOverlayExposeCB(SoWidget, SoXtMPGLWidget *, XtPointer);

  static void mgrDestroyCB(SoWidget, SoXtMPGLWidget *, XtPointer);


};

#endif // _SO_XT_GL_WIDGET_H_

#endif // _WIN32


