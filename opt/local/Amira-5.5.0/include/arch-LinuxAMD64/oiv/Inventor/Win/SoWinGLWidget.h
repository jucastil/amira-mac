/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/



#ifndef _SO_WIN_GL_WIDGET_H_
#define _SO_WIN_GL_WIDGET_H_


#include <Inventor/Win/SoWinBeginStrict.h>

#include <Inventor/Win/SoWinComponent.h>
#include <Inventor/components/SoGLGraphicConfigTemplate.h>
#include <Inventor/components/SoGLGraphicDevice.h>
#include <Inventor/components/SoGLGraphicConfig.h>

#include <Inventor/devices/SoGLContext.h>

#include <Inventor/nodes/SoFullSceneAntialiasing.h>

#include <Inventor/Gui/SoGuiGLWidget.h>

class SoGLContext;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWinGLWidget
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Component for OpenGL rendering.
 * 
 * @ingroup Win
 * 
 * @DESCRIPTION
 *   This abstract base class provides a C++ wrapper around an OpenGL drawing window.
 *   It allows OpenGL rendering to be performed within a Windows window and is used
 *   by the SoWinRenderArea. SoWinGLWidget uses a parent window with two separate
 *   OpenGL windows (one for single buffering and one for double buffering), with
 *   routines to return the appropriate windows.
 *   
 *   Subclasses only need to redefine the redraw() routine for rendering and
 *   processEvent() routine if they are interested in receiving Windows
 *   messages.
 *
 * @SEE_ALSO
 *    SoWinComponent,
 *    SoWinRenderArea
 * 
 * 
 */ 

class INVENTORW_API SoWinGLWidget : public SoWinComponent 
{
 public:
   
    /** FloatColorBufferSize */
   enum FloatColorBufferSize 
   {
    /**
     * 16-bit rendering per component.
     */
    FLOAT_16_COLOR_BUFFER = SoGuiGLWidget::FLOAT_16_COLOR_BUFFER,
    /**
     * 32-bit rendering per component.
     */
    FLOAT_32_COLOR_BUFFER = SoGuiGLWidget::FLOAT_32_COLOR_BUFFER
  };

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
  GLXContext  getNormalContext() { return m_contextNormal->getGLContext(); }

  SoGLContext* getNormalSoContext() { return m_contextNormal; }


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
  GLXContext  getOverlayContext() { return m_contextOverlay->getGLContext(); }

  SoGLContext* getOverlaySoContext() { return m_contextOverlay; }

  /**
   * Returns the device context (which is needed for SbGlContextHelper::makeCurrent).
   */
  Hdc getNormalDC() const;

  /**
   * Returns the overlay device context (which is needed for SbGlContextHelper::makeCurrent).
   */
  Hdc getOverlayDC() const;

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
  SoWidget getNormalWidget() const;
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
  SoWidget getOverlayWidget() const;
    
  /**
   * Specifies the exact pixel format descriptor for the normal
   * window. This allows the user to create all possible pixel format
   * descriptors supported by OpenGL. The PIXELFORMATDESCRIPTOR structure should be a
   * valid OpenGL pixel format descriptor returned by ChoosePixelFormat(). (The
   * methods for setting the pixel format descriptor are virtual so that derived
   * classes can know when the pixel format descriptor is changing.)
   */
  virtual void setNormalVisual( XVisualInfo* vis );

  /**
   * Returns the pixel format descriptor for the normal window.
   */
  XVisualInfo* getNormalVisual();

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
  virtual void setOverlayVisual( XVisualInfo* vis );

  /**
   * Returns the pixel format descriptor for the overlay window.
   */
  XVisualInfo* getOverlayVisual();

  /**
   * Sets the current pixel format. This method allows an application to
   * set a pixel format that has extended attributes that can't be specified in
   * a PFD struct. The specified format must support OpenGL and drawing to a window.
   * There are not separate methods for normal and overlay windows because the
   * overlay is not a separate window on Win32 computers. 
   * 
   * You can also use environment variable OIV_FORCE_PIXEL_FORMAT to request a pixel
   * format. 
   * 
   * Note: OIV_FORCE_PIXEL_FORMAT can also be used to set special convenience 
   * values (-1, -2, etc.) used for troubleshooting. However, these values are
   * not actually valid pixel formats and are not supported by #setPixelFormat. 
   */
  virtual void setPixelFormat( int format );

  /**
   * Returns the current pixel format. This method allow an application to
   * query a pixel format that has extended attributes that can't be specified in
   * a PFD struct. 
   */
  int getPixelFormat();

  /** 
   * Enables or disables full-scene antialiasing (FSAA). Returns TRUE on success.@BR
   * FSAA is supported via the ARB_multisample OpenGL extension.
   * The ARB_pixel_format OpenGL extension is also required to support this feature.
   * 
   * Note: Use the SoFullSceneAntialiasing node to control FSAA during render traversal.
   *
   * @param enable Enables or disables FSAA rendering.
   * @param quality Specifies the level of quality of the antialiasing rendering.
   * The number of samples used in the antialiasing computation depends on your graphics
   * hardware and on your video driver. NVidia graphics hardware can support 
   * @I number of samples @i * 2 levels
   * of quality (assuming the NV_multisample_filter_hint OpenGL extension is available).@BR
   * The quality value is in the [0..1] interval. 0 is the lowest quality level and 1 is the
   * highest quality level. When set to -1.0 the quality value is the default value for
   * the pixel format.
   * @param filterMask Specifies the types of shapes that should be antialiased 
   * (See SoFullSceneAntialiasing for more info.)
   */
  SbBool setFullSceneAntialiasing( SbBool enable, 
                                   float quality = -1.0,
                                   int filterMask = SoFullSceneAntialiasing::ALL );

  /**
   * Returns TRUE, if full-scene antialiasing (FSAA) is enabled.
   */
  SbBool isFullSceneAntialiasingEnabled() const;

  /**
   * Returns TRUE if FSAA is currently enabled. Also returns the current quality value.
   */
  SbBool getFullSceneAntialiasing( float& quality );

  /** 
   * Returns TRUE if FSAA is supported by current pixel format.
   */
  SbBool isFullSceneAntialiasingAvailable() const;

  /** 
   * @deprecated Method has been renamed. Use isFullSceneAntialiasingAvailable.
   * @DEPRECATED_SINCE_OIV 8.1
   */
  SoDEPRECATED SbBool isFsaaSupported();

  /**  
   * Returns TRUE if high quality full-scene antialiasing (FSAA) is available.
   *
   * This feature requires the GL_MULTISAMPLE_FILTER_HINT_NV extension.
   */
  SbBool isFullSceneAntialiasingHQAvailable() const;

  /**  
   * Enables or disables the high quality mode for full-scene antialiasing (FSAA).
   *
   * This feature requires the GL_MULTISAMPLE_FILTER_HINT_NV extension.
   */
  SbBool setFullSceneAntialiasingHQ( SbBool enable );

  /** 
   * Returns TRUE if the high quality mode for full-scene antialiasing (FSAA) is enabled.
   */
  SbBool isFullSceneAntialiasingHQEnabled() const;

  /**
   * Routine that dynamically changes between single and double buffering. Default
   * is double buffer off. (The SoWinRenderArea subclass makes it double buffer by
   * default.)
   */
  void setDoubleBuffer( SbBool onOrOff );

  /**
   * Returns whether double buffering is on or off.
   */
  SbBool isDoubleBuffer() { return m_guiGLWidget->isDoubleBuffer(); }
    
  /**
   * Included for portability only.
   */
  void setBorder( SbBool onOrOff );

  /**
   * Included for portability only.
   */
  int getBorderSize() { return m_guiGLWidget->getBorderSize(); }

  /**
   * Included for portability only.
   */
  SbBool isBorder() const { return m_guiGLWidget->isBorder(); }
    
  /**
   * Sets drawing to the front buffer. Controls drawing to the front buffer when
   * an obscured portion of the window is exposed. Default: FALSE.
   */
  void setDrawToFrontBufferEnable( SbBool enableFlag );

  /**
   * Returns whether drawing to the front buffer is enabled.
   */
  SbBool isDrawToFrontBufferEnable() const { return m_guiGLWidget->isDrawToFrontBufferEnable(); }

  /**
   * Sets the current cursor. If you are using a viewer class, the viewer will
   * automatically change the cursor depending on the viewer mode. These changes will
   * override the cursor set with this method unless you also call
   * SoWinViewer::setCursorEnabled(FALSE). 
   */
  void setCursor( Cursor newCursor );

  /**
   * Returns the current cursor. 
   */
  Cursor getCursor();      

  /** 
   * Makes the normal rendering context the current context.
   * @deprecated No longer used. use bindNormalContext and unbindNormalContext
   * @DEPRECATED_SINCE_OIV 8.1
   */
  SoDEPRECATED virtual SbBool makeNormalCurrent();

  /**
   * Makes the normal rendering context the current context.
   * Equivalent to makeNormalCurrent() call.
   */
  virtual SbBool bindNormalContext();

  /**
   * unbind the current context (previously bind with bindNormalContext );
   */
  virtual SbBool unbindNormalContext();


  /**
   * Swaps the normal front and back buffers.
   */
  virtual SbBool swapNormalBuffers();

  /**
   * Swaps the overlay front and back buffers.
   */
  SbBool swapOverlayBuffers();

  /**
   * Gets the current graphics configuration template.
   */
  SoGLGraphicConfigTemplate* getGraphicConfigTemplate();

  /**
   * Sets a new graphics configuration template.
   */
  void setGraphicConfigTemplate( SoGLGraphicConfigTemplate* gTemplate );

  /**
   * Enables/disables floating point rendering using 16- or 32-bit components.
   * If TRUE, Open Inventor will automatically render to an offscreen floating point buffer,
   * and copy the resulting image to the screen.
   *
   * To determine if floating point rendering was successfully enabled, 
   * use #getFloatingColorBuffer, below.
   *
   * Using floating point rendering can improve image quality, particularly when
   * many objects are being blended, for example, in volume rendering.
   * This is a convenience method as you could accomplish the same results 
   * setting up a graphic template.
   */
  void setFloatingColorBuffer( SbBool enable, 
                               FloatColorBufferSize size = FLOAT_16_COLOR_BUFFER );

  /**
   * Returns TRUE if floating point rendering is used and its precision.
   */
  void getFloatingColorBuffer( SbBool& enable, FloatColorBufferSize& size );

 SoEXTENDER public:

  // Starting with version 3.0, subclasses should no longer make direct
  // calls to glXMakeCurrent, glXSwapBuffers and glFlush.
  // For RemoteRendering we need to know when MakeCurrent is called
  // (marking the beginning of a frame) and when SwapBuffers or glFlush
  // is called (marking the end of a frame).
  // Subclasses should always use these generic methods.
  void   flush();

 SoINTERNAL public:

  SoGuiGLWidget* getGuiGLWidget() const;
    
  // Synchronise current properties from this object with the current configuration.
  void syncFromCurrentConfig();
  // Synchronise the current template with current properties from this object.
  void syncToCurrentConfigTemplate( PIXELFORMATDESCRIPTOR* newPFD );

  SbBool currentGraphicConfigTemplateIsUsed;
  SoGLGraphicConfigTemplate currentGraphicConfigTemplate;

  // Gets the current graphic device.
  SoGLGraphicDevice* getGraphicDevice();

  // Gets the current graphic configuration.
  SoGLGraphicConfig* getGraphicConfig();

  virtual void posChanged( const SbVec2i32&, const SbVec2i32& );

  // These variables are  public for retro compatibility purposes only.
  // Do not use them directly but call their accessors instead;
  SbBool drawToFrontBuffer;
  SbBool m_isFloatingPointRendering;
  FloatColorBufferSize m_floatingPointRenderingPrecision;

  // These two function are used by SoGui, to call the system dependent version of 
  // these functions. data is a SoWinGLWidget handle.
  static SbBool swapNormalBuffersCB(void *data);
  static SbBool bindNormalCurrentCB(void *data);
  static SbBool unbindNormalCurrentCB(void *data);
  static void* getNormalWindowCB(void *data);

 protected:

  // Update the current device and disable the current configuration.
  // If the given hdc is the same than the current device, the current
  // device is kept and the current configuration is updated with the 
  // current template.
  // If the given hdc is NULL, the current device and configuration are
  // freed and set to NULL.
  void updateCurrentDeviceAndConfig( HDC hdc );
    
  SbBool currentGraphicConfigIsUsed;
  SoGLGraphicConfig* currentGraphicConfig;
  SbBool currentGraphicDeviceIsUsed;
  SoGLGraphicDevice* currentGraphicDevice;

  // Subclasses can pass in a bitwise OR specifying the GL modes
  // (e.g. SO_GLX_RGB | SO_GLX_DOUBLE | SO_GLX_ZBUFFER | SO_GLX_OVERLAY)
  // If buildNow is FALSE, this will not build its widget tree until
  // buildWidget() is explicity called; else, buildWidget() is called here.
  SoWinGLWidget( SoWidget parent = NULL,
                 const char* name = NULL, 
                 SbBool buildInsideParent = TRUE, 
                 int glModes = SO_GLX_RGB, 
                 SbBool buildNow = TRUE,
                 SbBool sync = TRUE );

  SoWinGLWidget( SoWidget parent,
                 const char* name, 
                 SbBool buildInsideParent, 
                 int glModes, 
                 SbBool buildNow,
                 SbBool sync,
                 SoGuiGLWidget* guiGLWidget );

  virtual ~SoWinGLWidget();
    
  // subclasses MUST redefine redraw() to draw in the normal bit planes.
  // redrawOverlay() should be defined if the overlay planes are being
  // used, and processEvent() should be defined if X events are being 
  // received (see eventMask).
  virtual void redraw() = 0;
  virtual void redrawOverlay();
  virtual void processEvent( XAnyEvent* anyevent );
    
  // subclasses can redefine these to do something useful.
  // initGraphic() is called whenever a GLX window gets created
  // sizeChanged() is called whenever the window changes size
  // widgetChanged() is called whenever the widget is changed (i.e. at
  //    initialization or after switching from single->double buffer)
  virtual void initGraphic();
  virtual void initOverlayGraphic();
  virtual void sizeChanged( const SbVec2s& newSize );
  virtual void widgetChanged( SoWidget newWidget );
     
  // sets/gets the size of the glx widget(s) - Note this size could be
  // different from the SoWinComponent::getSize() method which return
  // the size of the component, not necessary the same as the glx widget
  // window (because of extra stuff like the decoration in the viewers).
  void setGlxSize( SbVec2s newSize );
  const SbVec2s& getGlxSize() const { return m_guiGLWidget->getGlxSize(); }
    
  // subclasses can use this routine as the event handler for any
  // devices they wish to get input from.
  static void eventHandler( SoWidget w, SoWinGLWidget* p, XAnyEvent* e, Boolean* b );
    
  // set/get stereo buffering visual. This routine (like setDoubleBuffer)
  // can be called interactively, althought slower since a new window
  // with the needed visual is always created on the fly.
  void setStereoBuffer( SbBool flag );
  SbBool isStereoBuffer() const;
    
  // returns TRUE if main window is in rgb mode, else FALSE for color index mode
  SbBool isRGBMode() const;
    
  // returns the display lists share group for given context:
  int getDisplayListShareGroup( SoGLContext* ctx );

  // set when color index is used
  Colormap getColorMap() const
  { return m_guiGLWidget->getColorMap(); }

  // set when overlay is used
  Colormap getOverlayColorMap() const
  { return m_guiGLWidget->getOverlayColorMap(); }


  SbBool waitForExpose; // prevent redraws until an expose is received
    
  // make those methods protected so enable the SoWinRenderArea to use them
  // directly when it needs to build the widget and get its resources.
  SoWidget buildWidget( SoWidget parent );
  SoWidget getGlxMgrWidget() { return mgrWidget; }

  // _WIN32
  // Add some convenience functions that reduce the number of ifdef's in
  // viewers by hiding these platform dependent operations.
  // We should add these to the UNIX version too.
  void changeCursor( Cursor newCursor );

  // Set/get thread this context belongs to
  DWORD getThreadId() { return dwThreadId; };
  void setThreadId( DWORD id ) { dwThreadId=id; };

  ////////////////////////////////////////////////////////////////////////////////

  virtual void onExpose();
  virtual void onOverlayExpose();

  void destroyNormalWindows(SbBool normalCall=TRUE);

  SbBool m_initialFsaaValueChanged;

 private:

   void constructorCommon( int glModes, SbBool buildNow, SoWidget parent );

   static SbBool onGLFormatChangeCallback( SoGLFormat& format, void* userData );

   HWND createWindow( SoGLFormat* format );

   void destroyWindow( HWND handle );

   void initGLXWidget( SoWidget glx, SoGLFormat* format );
  
  // local vars
  SoWidget mgrWidget;
  SoWidget m_widgetNormal, m_widgetOverlay;
  
  SoGLContext* m_contextNormal;
  SoGLContext* m_contextOverlay;

  SoGuiGLWidget* m_guiGLWidget; //Implementation class for SoXxGLWidget

  // Note for _WIN32:
  // 1) All the "SoWidget" values above are actually type "HWND".
  // 2) The "GLXContext" values above are actually type "HGLRC".

  // For _WIN32 we need a GL context *and* a device context for each
  // GL drawing window (we don't need one for the mgr because we don't
  // plan to ever draw in it).  These correspond to the "ctx..." vars.
  // Note: This plan depends on use of the CS_OWNDC style.
  Hdc m_hdcNormal, m_hdcOverlay;

  // For _WIN32 we also need a logical color palette for each drawing
  // area if we happen to running on an 8bit device...
  HPALETTE palNormal, palOverlay;

  // For _WIN32 we also need to remember our parent and our
  // "ancestor" (the toplevel window that we're descended from).
  SoWidget parent;
  SoWidget ancestor;

  // For _WIN32 we have to simulate the "focus follows pointer" behavior
  // that X provides for free.  Otherwise the app would have to be
  // responsible for giving focus to the GL window and/or the user
  // would have to keep clicking to get focus in the GL window.  Focus
  // is required for the 1-button mouse viewer behaviors like Ctrl-Left
  // Button and so on.  This variable tracks whether we have focus
  // based on the WM_SETFOCUS/WM_KILLFOCUS messages (see glxWindowProc).
  int haveFocus;

  // This flag tracks whether "focus follows pointer" is enabled.
  int stealFocus;

  // For _WIN32 we have to simulate the behavior of X where getting a
  // mouse button down event guarantees you will also get the
  // corresponding button up event.  Otherwise examiner viewer windows
  // get out of sync if a mouse button is released outside the window.
  UINT mouseCaptured;

  // For _WIN32 we have to know the handle of the cursor that's supposed
  // to be displayed currently in the drawing window.  The explanation
  // is too long to fit here...  :-)  OK, actually it's because the
  // viewers want to change the cursor periodically but we can't change
  // the cursor in the class defn or it will change for *all* the GL
  // windows (yuck).  So we have to process the WM_SETCURSOR message in
  // the glxWindowProc.
  HCURSOR currentCursor;

  // We also need (globally for the class) the default cursor to use.
  static HCURSOR defaultCursor;

  DWORD dwThreadId; // thread to which this context belongs -- mmh Apr-99

  int* attribList;
    
  // specify if sizeChanged() should be called when an expose event
  // is received (as opposed to when a resize event is received, where
  // the window hasn't yet been maped to the new size).
  // ??? a GlxDraw bug ?
  SbBool windowResized;

  bool m_isMouseTracking;
    
  // creates a GLX widget of the correct current type and get the current
  // set of windows, color maps, etc...
  void buildNormalGLXWidget( SoGLFormat* format = NULL );
  void buildOverlayGLXWidget( SoGLFormat* format = NULL );
  void destroyGLXWidget( SoWidget& w, SoGLContext*& ctx, SbBool normalWindow );
    
  // callbacks from glx widget
  static void ginitCB( SoWidget w, SoWinGLWidget* p, XtPointer );
  static void overlayGinitCB( SoWidget w, SoWinGLWidget* p, XtPointer ptr );
  static void exposeCB( SoWidget w, SoWinGLWidget* p, XtPointer ptr );
  static void overlayExposeCB( SoWidget w, SoWinGLWidget* p, XtPointer ptr );
  static void resizeCB( SoWidget w, SoWinGLWidget* p, XtPointer ptr );
  static void mgrStructureNotifyCB( SoWidget w, SoWinGLWidget* p, XAnyEvent* e, Boolean* b );

  // Window proc for SoWinGL "manager widget" windows
  static LRESULT CALLBACK mgrWindowProc( Hwnd hwnd, UINT message,
                                         WPARAM wParam, LPARAM lParam );

  // Window proc for SoWinGL drawing windows
  static LRESULT CALLBACK glxWindowProc( Hwnd hwnd, UINT message,
                                         WPARAM wParam, LPARAM lParam );
};

inline void 
SoWinGLWidget::posChanged( const SbVec2i32&, const SbVec2i32& )
{};


#include <Inventor/Win/SoWinEndStrict.h>

#endif // _SO_WIN_GL_WIDGET_H_


