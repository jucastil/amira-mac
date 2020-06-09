/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/




#ifndef _SO_WIN_MP_GL_WIDGET_H_
#define _SO_WIN_MP_GL_WIDGET_H_

#include <Inventor/sys/port.h>

#include <Inventor/Win/SoWinBeginStrict.h>

#include <Inventor/Win/SoWinComponent.h>

#include <Inventor/MP/Xt/SbConfig.h>

/*
 * Defines used when specifying the glModes flag to the constructor.
 * (used instead of the glx.h defines which do overlap)
 */
#define SO_GLX_RGB      (1<<0)
#define SO_GLX_DOUBLE   (1<<1)
#define SO_GLX_ZBUFFER  (1<<2)
#define SO_GLX_OVERLAY  (1<<3)
#define SO_GLX_STEREO   (1<<4)

class SoGLContext;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWinMPGLWidget
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @SCVEXT MultiPipe component for OpenGL rendering.
 * 
 * @ingroup ScaleVizMultiPipe
 * 
 * @DESCRIPTION
 *   This is the MultiPipe version of SoWinGLWidget. 
 * 
 * 
 */ 

class INVENTORW_API SoWinMPGLWidget : public SoWinComponent 
{
 public:
    
  /**
   * Gets the normal GL window, which is
   * needed as an argument to SbGlContextHelper::makeCurrent() when drawing in the normal
   * planes.
   * 
   * Note: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   */
  virtual Window getNormalWindow();

  /**
   * Gets the overlay GL window, which is
   * needed as an argument to SbGlContextHelper::makeCurrent() when drawing in overlay
   * planes.
   * 
   * Note1: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   * 
   * Note2: Overlay planes are supported only if the graphics board supports overlay
   * planes.
   */
  Window      getOverlayWindow();
  /**
   * Gets the normal context, which is
   * needed as an argument to SbGlContextHelper::makeCurrent() when drawing in the normal
   * planes.
   * 
   * Note: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   */
  SoGLContext* getNormalContext()      { return ctxNormal; }
  /**
   * Gets the overlay context, which is
   * needed as an argument to SbGlContextHelper::makeCurrent() when drawing in the overlay
   * planes.
   * 
   * Note1: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   * 
   * Note2: Overlay planes are supported only if the graphics board supports overlay
   * planes.
   */
  SoGLContext* getOverlayContext()     { return ctxOverlay; }

  /**
   * Returns the normal device context (which is needed for SbGlContextHelper::makeCurrent).
   * Same as getNormalDC(0).
   */
  Hdc getNormalDC()  { return hdcNormal; }

  /**
   * Returns the overlay device context (which is needed for SbGlContextHelper::makeCurrent).
   * Same as getOverlayDC(0).
   */
  Hdc getOverlayDC( ) { return hdcOverlay; }


#ifndef HIDDEN_FROM_DOC
  // Jim's thing for now, not really public
  Hdc copyWindowBits() ;
#endif // HIDDEN_FROM_DOC

  /**
   * By default the GLWidget "steals" focus whenever the cursor moves over it. This
   * roughly simulates the UNIX/X "focusFollowsCursor" behavior (which has no
   * equivalent in Win32) and allows the Ctrl and Shift keys to be detected for
   * 1-button mouse behaviors. Sometimes you want to this off however, like when
   * you're typing in the zoom field.
   */
  void setStealFocus( SbBool onOrOff ) { stealFocus = onOrOff; };
  /**
   * Gets the normal window handle, which is
   * needed as an argument to SbGlContextHelper::makeCurrent() when drawing in the normal 
   * planes.
   * 
   * Note: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   */
   
  SoWidget      getNormalWidget()       { return (glModes & SO_GLX_DOUBLE) ? doubleBufferWidget : singleBufferWidget; }
  /**
   * Gets the overlay window handle, which is
   * needed as an argument to SbGlContextHelper::makeCurrent() when drawing in the overlay
   * planes.
   * 
   * Note1: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   * 
   * Note2: Overlay planes are supported only if the graphics board supports overlay
   * planes.
   */
  SoWidget       getOverlayWidget()      { return overlayWidget; }

  // Note: On Windows, XVisualInfo is defined as PIXELFORMATDESCRIPTOR.
  // Also note that setOverlayVisual() has no effect on Win32 machines
  // because the overlay is not a separate window.
  //

  /**
   * Specifies the exact pixel format descriptor for the normal
   * window. This allows the user to create all possible pixel format
   * descriptors supported by OpenGL. The PIXELFORMATDESCRIPTOR structure should be a
   * valid OpenGL pixel format descriptor returned by ChoosePixelFormat(). (The
   * methods for setting the pixel format descriptor are virtual so that derived
   * classes can know when the pixel format descriptor is changing.)
   */
  virtual void    setNormalVisual(XVisualInfo *vis);
  /**
   * Returns the pixel format descriptor for the normal window.
   */
  XVisualInfo *   getNormalVisual();
  /**
   * Specifies the exact pixel format descriptor for the
   * overlay window. This allows the user to create all possible pixel format
   * descriptors supported by OpenGL. The PIXELFORMATDESCRIPTOR structure should be a
   * valid OpenGL pixel format descriptor returned by ChoosePixelFormat(). (The
   * methods for setting the pixel format descriptor are virtual so that derived
   * classes can know when the pixel format descriptor is changing.)
   * 
   * Note: Overlay planes are supported only if the graphics board supports overlay
   * planes.
   */
  virtual void    setOverlayVisual(XVisualInfo *vis);
  /**
   * Returns the pixel format descriptor for the overlay window.
   */
  XVisualInfo *   getOverlayVisual();


  /**
   * Sets the current pixel format. This method allows an application to
   * set a pixel format that has extended attributes that can't be specified in
   * a PFD struct. The specified format must support OpenGL and drawing to a window.
   * There are not separate methods for normal and overlay windows because the
   * overlay is not a separate window on Win32 computers. 
   * 
   * You can also use environment variable OIV_FORCE_PIXEL_FORMAT to request a pixel
   * format.
   */
  virtual void    setPixelFormat( int format );
  /**
   * Returns the current pixel format. This method allow an application to
   * query a pixel format that has extended attributes that can't be specified in
   * a PFD struct. 
   */
  int             getPixelFormat();
    
  /**
   * Routine that dynamically changes between single and double buffering. Default
   * is double buffer off. (The SoWinRenderArea subclass makes it double buffer by
   * default.)
   */
  void        setDoubleBuffer(SbBool onOrOff);
  /**
   * Returns whether double buffering is on or off.
   */
  SbBool      isDoubleBuffer()            { return (glModes & SO_GLX_DOUBLE); }
    
  /**
   * Included for portability only.
   */
  void        setBorder(SbBool onOrOff);
  /**
   * Included for portability only.
   */
  int         getBorderSize() {return borderSize;} ;
  /**
   * Included for portability only.
   */
  SbBool      isBorder() const            { return borderSize != 0; }
    
  /**
   * Sets drawing to the front buffer. Controls drawing to the front buffer when
   * an obscured portion of the window is exposed. Default: FALSE.
   */
  void        setDrawToFrontBufferEnable(SbBool enableFlag);
  /**
   * Returns whether drawing to the front buffer is enabled.
   */
  SbBool      isDrawToFrontBufferEnable() const   { return enableDrawToFrontBuffer; }

  /**
   * Sets the current cursor. If you are using a viewer class, the viewer will
   * automatically change the cursor depending on the viewer mode. These changes will
   * override the cursor set with this method unless you also call
   * SoWinViewer::setCursorEnabled(FALSE). 
   */
  void setCursor(Cursor newCursor);
  /**
   * Returns the current cursor. 
   */
  Cursor getCursor();  

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

  /**
   * Swaps the normal front and back buffers.
   */
  SbBool swapNormalBuffers();
 
  /**
   * Swaps the overlay front and back buffers.
   */ 
  SbBool swapOverlayBuffers() { return (wglSwapLayerBuffers( (HDC)hdcOverlay ,WGL_SWAP_OVERLAY1)); };

  SoINTERNAL public:
  SoGLContext* m_glContext;

 protected:
    
  // Subclasses can pass in a bitwise OR specifying the GL modes
  // (e.g. SO_GLX_RGB | SO_GLX_DOUBLE | SO_GLX_ZBUFFER | SO_GLX_OVERLAY)
  // If buildNow is FALSE, this will not build its widget tree until
  // buildWidget() is explicity called; else, buildWidget() is called here.
  SoWinMPGLWidget(SoWidget parent = NULL,
                  const char *name = NULL, 
                  SbBool buildInsideParent = TRUE, 
                  int glModes = SO_GLX_RGB, 
                  SbBool buildNow = TRUE);
  virtual ~SoWinMPGLWidget();
    
  // subclasses MUST redefine redraw() to draw in the normal bit planes.
  // redrawOverlay() should be defined if the overlay planes are being
  // used, and processEvent() should be defined if X events are being 
  // received (see eventMask).
  virtual void        redraw() = 0;
  virtual void        redrawOverlay();
  virtual void        processEvent(XAnyEvent *anyevent);
    
  // subclasses can redefine these to do something useful.
  // initGraphic() is called whenever a GLX window gets created
  // sizeChanged() is called whenever the window changes size
  // widgetChanged() is called whenever the widget is changed (i.e. at
  //    initialization or after switching from single->double buffer)
  virtual void        initGraphic();
  virtual void        initOverlayGraphic();
  virtual void        sizeChanged(const SbVec2s &newSize);
  virtual void        widgetChanged(SoWidget newWidget);
        
  virtual void initViewportRegion(int);
    
  // sets/gets the size of the glx widget(s) - Note this size could be
  // different from the SoWinComponent::getSize() method which return
  // the size of the component, not necessary the same as the glx widget
  // window (because of extra stuff like the decoration in the viewers).
  void                setGlxSize(SbVec2s newSize);
  const SbVec2s &     getGlxSize() const                      { return glxSize; }

  // subclasses can use this routine as the event handler for any
  // devices they wish to get input from.
  static void eventHandler(SoWidget, SoWinMPGLWidget *, XAnyEvent *, Boolean *);
    
  // set/get stereo buffering visual. This routine (like setDoubleBuffer)
  // can be called interactively, althought slower since a new window
  // with the needed visual is always created on the fly.
  void                setStereoBuffer(SbBool flag);
  SbBool              isStereoBuffer()  { return (glModes & SO_GLX_STEREO); }
    
  // returns TRUE if main window is in rgb mode, else FALSE for color index mode
  SbBool              isRGBMode()         { return (glModes & SO_GLX_RGB); }
    
  // returns the display lists share group for given context:
  int                 getDisplayListShareGroup( SoGLContext* ctx );

  Colormap            colorMap;       // set when color index is used
  Colormap            overlayColorMap; // set when overlay is used

  SbBool              waitForExpose;     // prevent redraws until an expose is received
  SbBool              drawToFrontBuffer; // used by RA to draw new scenes to front buffer
    
  // make those methods protected so enable the SoWinRenderArea to use them
  // directly when it needs to build the widget and get its resources.
  SoWidget              buildWidget(SoWidget parent);
  SoWidget              getGlxMgrWidget()               { return mgrWidget; }

  ////////////////////////////// _WIN32 //////////////////////////////
  // Add some convenience functions that reduce the number of ifdef's in
  // viewers by hiding these platform dependent operations.
  // We should add these to the UNIX version too.
  void                changeCursor( Cursor newCursor );
  
  SbConfig * mpConfig;

  int pipeContextIdOffset; // pipes should not reuse context ids
  void raiseMainViewer(SbBool); // raise/lower main viewer

  // Set/get thread this context belongs to.
  DWORD getThreadId() { return dwThreadId; };
  void setThreadId(DWORD id) { dwThreadId=id; };

  ////////////////////////////////////////////////////////////////////////////////

  virtual void onExpose();
  virtual void onOverlayExpose();

 private:
  // local vars
  SoWidget     mgrWidget;
  SoWidget     doubleBufferWidget, singleBufferWidget, overlayWidget;
  SoGLContext* ctxNormal, *ctxOverlay, *ctxSingle, *ctxDouble;

  SbVec2s     glxSize; // size of glx widgets which is always up to date
  SbBool      enableDrawToFrontBuffer;

  // Note for WIN32:
  // 1) All the "SoWidget" values above are actually type "HWND".
  // 2) The "GLXContext" values above are actually type "HGLRC".

  // For WIN32 this struct functionally replaces attribList
  PIXELFORMATDESCRIPTOR pfd;
  int                   m_nPixelFormat;

  // For WIN32 these are saved because XGetVisualInfo doesn't exist...
  PIXELFORMATDESCRIPTOR pfdNormal, pfdOverlay, pfdSingle, pfdDouble;

  // For WIN32 we need a GL context *and* a device context for each
  // GL drawing window (we don't need one for the mgr because we don't
  // plan to ever draw in it).  These correspond to the "ctx..." vars.
  // Note: This plan depends on use of the CS_OWNDC style.

  Hdc hdcNormal, hdcOverlay, hdcSingle, hdcDouble;

  // For WIN32 we also need a logical color palette for each drawing
  // area if we happen to running on an 8bit device...

  // pointers for dynamic allocations
  HPALETTE palNormal, palOverlay, palSingle, palDouble;

  // For WIN32 we also need to remember our parent and our
  // "ancestor" (the toplevel window that we're descended from).
  SoWidget parent;
  SoWidget ancestor;

  // For WIN32 we have to simulate the "focus follows pointer" behavior
  // that X provides for free.  Otherwise the app would have to be
  // responsible for giving focus to the GL window and/or the user
  // would have to keep clicking to get focus in the GL window.  Focus
  // is required for the 1-button mouse viewer behaviors like Ctrl-Left
  // Button and so on.  This variable tracks whether we have focus
  // based on the WM_SETFOCUS/WM_KILLFOCUS messages (see glxWindowProc).
  int haveFocus;

  // This flag tracks whether "focus follows pointer" is enabled.
  int stealFocus;

  // For WIN32 we have to simulate the behavior of X where getting a
  // mouse button down event guarantees you will also get the
  // corresponding button up event.  Otherwise examiner viewer windows
  // get out of sync if a mouse button is released outside the window.
  UINT mouseCaptured;

  // For WIN32 we have to know the handle of the cursor that's supposed
  // to be displayed currently in the drawing window.  The explanation
  // is too long to fit here...  :-)  OK, actually it's because the
  // viewers want to change the cursor periodically but we can't change
  // the cursor in the class defn or it will change for *all* the GL
  // windows (yuck).  So we have to process the WM_SETCURSOR message in
  // the glxWindowProc.
  HCURSOR currentCursor;

  // We also need (globally for the class) the default cursor to use.
  static HCURSOR defaultCursor;

  DWORD dwThreadId; // thread to which this context belongs

  int* attribList;
  int  glModes;
  int  borderSize;
    
  // specify if sizeChanged() should be called when an expose event
  // is received (as opposed to when a resize event is received, where
  // the window hasn't yet been maped to the new size).
  // ??? a GlxDraw bug ?
  SbBool windowResized;
    
  // creates a GLX widget of the correct current type and get the current
  // set of windows, color maps, etc...
  void buildNormalGLXWidget(XVisualInfo *vis = NULL);
  void buildOverlayGLXWidget(XVisualInfo *vis = NULL);
  void destroyNormalWindows();
  void destroyGLXWidget(SoWidget &w, SoGLContext* &ctx, SbBool normalWindow);
    
  // callbacks from glx widget
  static void ginitCB(SoWidget, SoWinMPGLWidget *, XtPointer);
  static void overlayGinitCB(SoWidget, SoWinMPGLWidget *, XtPointer ptr);
  static void exposeCB(SoWidget, SoWinMPGLWidget *, XtPointer);
  static void overlayExposeCB(SoWidget, SoWinMPGLWidget *, XtPointer);
  static void resizeCB(SoWidget, SoWinMPGLWidget *, XtPointer);
  static void mgrStructureNotifyCB(SoWidget, SoWinMPGLWidget *, XAnyEvent *, Boolean *);

#if defined(_WIN32)
  // Window proc for SoWinGL "manager widget" windows
  static LRESULT CALLBACK mgrWindowProc( Hwnd hwnd, UINT message,
                                         WPARAM wParam, LPARAM lParam );

  // Window proc for SoWinGL drawing windows
  static LRESULT CALLBACK glxWindowProc( Hwnd hwnd, UINT message,
                                         WPARAM wParam, LPARAM lParam );
#endif // _WIN32
 SoINTERNAL public:
  static void mpGinitCB(SoWidget, SoWinMPGLWidget *, XtPointer); 
};

#if defined(_WIN32)
#include <Inventor/Win/SoWinEndStrict.h>
#endif // _WIN32

#endif // _SO_WIN_GL_WIDGET_H_


