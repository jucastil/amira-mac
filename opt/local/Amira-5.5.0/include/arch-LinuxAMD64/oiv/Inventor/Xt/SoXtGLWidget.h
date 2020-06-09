/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Alain Dumesny (MMM yyyy)
** Modified by : David Mott (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/

#ifdef SOQT
#  include <Inventor/Qt/SoQtGLWidget.h>
#elif defined(SOWX)
#  include <Inventor/Wx/SoWxGLWidget.h>
#elif defined _WIN32
#  include <Inventor/Win/SoWinGLWidget.h>
#else // _WIN32

#ifndef _SO_XT_GL_WIDGET_H_
#define _SO_XT_GL_WIDGET_H_

#include <X11/Intrinsic.h>
#include <Inventor/helpers/SbGlContextHelper.h>
#include <Inventor/Xt/SoXtComponent.h>
#include <Inventor/components/SoGLGraphicConfigTemplate.h>
#include <Inventor/components/SoGLGraphicDevice.h>
#include <Inventor/components/SoGLGraphicConfig.h>
#include <Inventor/devices/SoGLFormat.h>
#include <Inventor/threads/SbThread.h>
#include <Inventor/nodes/SoFullSceneAntialiasing.h>

#include <Inventor/Gui/SoGuiGLWidget.h>

#if defined(sun) || defined(__linux__)
#  define NUM_OVERLAY_PIXELS 8
#endif

class SoXtRemoteRenderInfo;
class SoGLContext;

//////////////////////////////////////////////////////////////////////////////
//
// Class: SoXtGLWidget
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Component for OpenGL rendering.
 *
 * @ingroup Xt
 *
 * @DESCRIPTION
 *   This abstract base class provides a C++ wrapper around the GLwMDraw window
 *   object. It allows OpenGL rendering to be performed within a Motif window and is
 *   used by the SoXtRenderArea. SoXtGLWidget uses a parent window with two separate
 *   GLwMDraw window objects (one for single and one for double buffering), with
 *   routines to return the appropriate windows.
 *
 *   Subclasses only need to redefine the redraw() routine for rendering and
 *   processEvent() routine if they are interested in receiving X events.
 *
 * @SEE_ALSO
 *    SoXtComponent,
 *    SoXtRenderArea
 *
 *
 */

class INVENTORXT_API SoXtGLWidget : public SoXtComponent
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
   * Returns the overlay transparent pixel.
   */
  unsigned long getOverlayTransparentPixel();

  /**
   * Returns the overlay color map size.
   */
  int getOverlayColorMapSize();

  /**
   * Returns the color map size.
   */
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
  SbGlContextHelper::GLContext  getNormalContext() const;

  SoGLContext* getNormalSoContext() const;

  /**
   * Gets the current overlay context, which is
   * needed as an argument to glXMakeCurrent() when drawing in the
   * overlay planes.
   *
   * Note: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   */
  SbGlContextHelper::GLContext  getOverlayContext() const;

  SoGLContext* getOverlaySoContext() const;

  /**
   * Gets the current normal widget, which is
   * needed as an argument to glXMakeCurrent() when drawing in the normal
   * planes.
   *
   * Note: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   */
  SoWidget getNormalWidget() const;

  /**
   * Gets the current overlay widget, which is
   * needed as an argument to glXMakeCurrent() when drawing in the
   * overlay planes.
   *
   * Note: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   */
  SoWidget getOverlayWidget() const;

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
   * This allows the user to create all possible visuals supported by OpenGL. The
   * @B XVisualInfo @b structure should be a valid OpenGL visual returned by
   * @B glXChooseVisual @b(). This structure will be copied by the SoXtGLWidget; the
   * application is responsible for freeing the visual info with @B XFree @b() when
   * done. (The methods for setting the visual are virtual so that derived classes
   * can know when the visual is changing.)
   */
  virtual void setNormalVisual( XVisualInfo* vis );

  /**
   * Returns the visual for the normal window.
   */
  XVisualInfo* getNormalVisual();

  /**
   * Specify exactly what the visual should be for the overlay window.
   * This allows the user to create all possible visuals supported by OpenGL. The
   * @B XVisualInfo @b structure should be a valid OpenGL visual returned by
   * @B glXChooseVisual @b(). This structure will be copied by the SoXtGLWidget; the
   * application is responsible for freeing the visual info with @B XFree @b() when
   * done. (The methods for setting the visual are virtual so that derived classes
   * can know when the visual is changing.)
   */
  virtual void setOverlayVisual( XVisualInfo* vis );

  /**
   * Returns the visual for the overlay window.
   */
  XVisualInfo* getOverlayVisual();

  /**
   * Routine that dynamically changes between single and double buffering. Default
   * is double buffer off. (The SoXtRenderArea subclass makes it double buffer by
   * default.)
   */
  virtual void setDoubleBuffer( SbBool onOrOff );

  /**
   * Returns whether double buffering is on or off.
   */
  SbBool isDoubleBuffer();

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
   * the visual.
   * @param filterMask Specifies the types of shapes that should be antialiased
   * (See SoFullSceneAntialiasing for more info.)
   */
  SbBool setFullSceneAntialiasing ( SbBool enable,
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
   * @deprecated Method has been renamed. Use isFullSceneAntialiasingAvailable
   * Makes the normal rendering context the current context.
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
   * Shows/hides a border of thickness 3 around the glX widgets. This
   * if OFF by default, but turned on by the render area.
   */
  void setBorder( SbBool onOrOff );

  /**
   * Returns whether the border is on or off.
   */
  SbBool isBorder() const { return m_guiGLWidget->isBorder(); }

  /**
   * Sets drawing to the front buffer. Controls drawing to the front buffer when
   * an obscured portion of the window is exposed. Default: TRUE.
   */
  void setDrawToFrontBufferEnable( SbBool enableFlag );

  /**
   * Queries drawing to the front buffer.
   */
  SbBool isDrawToFrontBufferEnable() const { return m_guiGLWidget->isDrawToFrontBufferEnable(); }

  /** 
   * @deprecated No longer used. Use bindNormalContext and unbindNormalContext
   * Makes the normal rendering context the current context.
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
   * Swaps the normal front and back buffers. Equivalent to calling
   * glXSwapBuffers( getDisplay(), getNormalWindow() );
   */
  virtual SbBool swapNormalBuffers();

  /**
   * Makes the overlay rendering context the current context. Equivalent to calling
   * glXMakeCurrent( getDisplay(), getOverlayWindow(), getOverlayContext() );
   */
  SbBool makeOverlayCurrent();

  /**
   * Swaps the overlay front and back buffers. Equivalent to calling
   * glXSwapBuffers( getDisplay(), getOverlayWindow() );
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
  void setFloatingColorBuffer( SbBool enable, FloatColorBufferSize size = FLOAT_16_COLOR_BUFFER );

  /**
   *
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

  // Pbuffers are a limited resource.  By default use of Pbuffers for
  // remote rendering is enabled, but it might make sense to disable
  // it for less important windows (like UI components drawn with OpenGL).
  // Must be called after creating the widget but before it is realized.
  void setRemoteRenderPbufferEnable( SbBool enable ) { m_remoteRenderPbufferEnable = enable; }
  SbBool isRemoteRenderPbufferEnable() const { return m_remoteRenderPbufferEnable; }

  float getLowResPercent() { return m_lowResPercent; }

  // check if the context is direct
  SbBool ctxIsDirect();

 SoINTERNAL public:

  // Synchronise current properties from this object with the current configuration.
  void syncFromCurrentConfig();

  // Synchronise the current template with current properties from this object.
  void syncToCurrentConfigTemplate( XVisualInfo* newvis );

  SbBool currentGraphicConfigTemplateIsUsed;
  SoGLGraphicConfigTemplate currentGraphicConfigTemplate;

  // Gets the current graphic device.
  SoGLGraphicDevice* getGraphicDevice();

  // Gets the current graphic configuration.
  SoGLGraphicConfig* getGraphicConfig();

  SbBool isFsaaSupportHighQuality();
  SbBool isFsaaHighQuality();

  SoGuiGLWidget* getGuiGLWidget() const;

  // returns the display lists share group for given context:
  int getDisplayListShareGroup( SoGLContext* ctx );

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
  static void* getCurrentDisplayCB(void *data);

 protected:

  // Update the current device and disable the current configuration.
  // If the given display is the same than the current device, the current
  // device is kept and the current configuration is updated with the
  // current template.
  // If the given display is NULL, the current device and configuration are
  // freed and set to NULL.
  void updateCurrentDeviceAndConfig( Display* display );

  SbBool currentGraphicConfigIsUsed;
  SoGLGraphicConfig* currentGraphicConfig;
  SbBool currentGraphicDeviceIsUsed;
  SoGLGraphicDevice* currentGraphicDevice;

  // Subclasses can pass in a bitwise OR specifying the GL modes
  // (e.g. SO_GLX_RGB | SO_GLX_DOUBLE | SO_GLX_ZBUFFER | SO_GLX_OVERLAY)
  // If buildNow is FALSE, this will not build its widget tree until
  // buildWidget() is explicity called; else, buildWidget() is called here.
  SoXtGLWidget( SoWidget parent = NULL,
                const char* name = NULL,
                SbBool buildInsideParent = TRUE,
                int glModes = SO_GLX_RGB,
                SbBool buildNow = TRUE,
                SbBool sync = TRUE );
  SoXtGLWidget( SoWidget parent,
                const char* name,
                SbBool buildInsideParent,
                int glModes,
                SbBool buildNow,
                SbBool sync,
                SoGuiGLWidget* guiGLWidget );

  virtual ~SoXtGLWidget();

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
  // initialization or after switching from single->double buffer)
  virtual void initGraphic();
  virtual void initOverlayGraphic();
  virtual void sizeChanged( const SbVec2s& );
  virtual void posChanged( const SbVec2i32&, const SbVec2i32& );
  virtual void widgetChanged( SoWidget newWidget );

  // sets/gets the size of the glx widget(s) - Note this size could be
  // different from the SoXtComponent::getSize() method which return
  // the size of the component, not necessary the same as the glx widget
  // window (because of extra stuff like the decoration in the viewers).
  void setGlxSize( SbVec2s newSize );
  const SbVec2s& getGlxSize() const { return m_guiGLWidget->getGlxSize(); }

  // subclasses can use this routine as the event handler for any
  // devices they wish to get input from.
  static void eventHandler( SoWidget w, SoXtGLWidget* p, XAnyEvent* xe, Boolean* b );

  // set/get stereo buffering visual. This routine (like setDoubleBuffer)
  // can be called interactively, althought slower since a new window
  // with the needed visual is always created on the fly.
  void setStereoBuffer( SbBool flag );
  SbBool isStereoBuffer() { return (m_guiGLWidget->getGLModes() & SO_GLX_STEREO); }

  // returns TRUE if main window is in rgb mode (FALSE if color index)
  SbBool isRGBMode() { return (m_guiGLWidget->getGLModes() & SO_GLX_RGB); }

#if defined(sun) || defined(__linux__)
  void allocCell( Display *display, Colormap cmap, XColor *colorcells, int ncolors, int colorMapSize );
#endif

  // set when color index is used
  Colormap getColorMap() const
  { return m_guiGLWidget->getColorMap(); }

  // set when overlay is used
  Colormap getOverlayColorMap() const
  { return m_guiGLWidget->getOverlayColorMap(); }

  SbBool waitForExpose; // prevent redraws until an expose is received

  // make those methods protected to enable the SoXtRenderArea to use them
  // directly when it needs to build the widget and get its resources.
  SoWidget buildWidget( SoWidget parent );
  SoWidget getGlxMgrWidget() { return mgrWidget; }

  // ----- RemoteRender additions (v3.0) -----
  enum RemoteRenderEnabled     // Possible values for remote rendering
  {
    OFF,                      // Never use remote rendering
    ON,                       // Always try to use remote rendering
    AUTO                      // Use if remote does not support GLX (default)
  };
  RemoteRenderEnabled   m_remoteRenderMode;  // See possible values above
  SbBool                m_remoteRender;      // Is remote rendering being used?
  SoXtRemoteRenderInfo* m_remoteRenderInfo;  // Opaque type for internal state
  SbBool                m_remoteRenderPbufferEnable; // Can we use a Pbuffer?
  SbBool                m_lowResRender;      //Is Low Resolution Render Mode in use?
  float                 m_lowResLowPercent;  //lowest value of m_lowResPercent
  float                 m_lowResHighPercent; //highest value of m_lowResPercent
  float                 m_lowResPercent;    //percent of the window sent thru the network

  void remoteRenderInit();                // Init member vars
  void remoteRenderCleanup();             // Free allocated resources
  void remoteRenderGinitCB( SoWidget w );     // Create pixmap and other stuff
  SbGlContextHelper::GLContext remoteRenderLowResRenderGinitCB( SoWidget w ); //Same for LowResRender configuration : return Remote Context
  void remoteRenderResizeCB();            // Resize pixmap
  void remoteRenderSendImage();           // Send rendered image to remote display
  void remoteRenderSendLowResRender();    // send low Resolution image to remote display
  XVisualInfo* remoteRenderChooseVisual();        // Find visual for remote window
  void remoteRenderFatalError( const char* methodName, const char* message );

  void setLowResLowPercent( float percent ) { m_lowResLowPercent = percent;}
  void setLowResHighPercent( float percent ) { m_lowResHighPercent = percent;}
  float getLowResLowPercent() const { return m_lowResLowPercent;}
  float getLowResHighPercent() const { return m_lowResHighPercent;}

  virtual void setLowResPercent( float newLowres ) {m_lowResPercent = newLowres;}

  // Set/get thread this context belongs to
  SbThreadId_t dwThreadId; // thread to which this context belongs
  SbThreadId_t getThreadId() { return dwThreadId; };
  void setThreadId( SbThreadId_t id ) { dwThreadId=id; };

  virtual void onExpose();
  virtual void onOverlayExpose();

  SbBool m_initialFsaaEnable;
  int m_initialFsaaFilterMask;
  SbBool m_initialFsaaValueChanged;

 private:
  // local vars
  SoWidget mgrWidget;
  SoWidget m_widgetNormal, m_widgetOverlay;

  SoGLContext* m_contextNormal;
  SoGLContext* m_contextOverlay;

  int* attribList;

  // specify if sizeChanged() should be called when an expose event
  // is received (as opposed to when a resize event is received, where
  // the window hasn't yet been maped to the new size).
  // ??? a GlxDraw bug ?
  SbBool windowResized;

  SbBool directConnection;

  // creates a GLX widget of the correct current type and get the current
  // set of windows, color maps, etc...
  void buildNormalGLXWidget( XVisualInfo* vis = NULL );
  void buildOverlayGLXWidget( XVisualInfo* vis = NULL );
#if defined(sun) || defined(__linux__)
  void buildSunOverlayWindow( SoWidget glx, SoXtGLWidget* p );
#endif
  void destroyNormalWindows(SbBool normalCall=TRUE);
  void destroyGLXWidget( SoWidget& w, SoGLContext*& ctx, SbBool normalWindow );

  SoWidget createWindow( SoGLFormat* format );
  void destroyWindow( SoWidget widget );

   static SbBool onGLFormatChangeCallback( SoGLFormat& format, void* userData );

  // callbacks from glx widget
  static void ginitCB( SoWidget w, SoXtGLWidget* v, XtPointer p );
  static void overlayGinitCB( SoWidget glx, SoXtGLWidget* p, XtPointer pt );
  static void exposeCB( SoWidget w, SoXtGLWidget* v, XtPointer p );
  static void overlayExposeCB( SoWidget w, SoXtGLWidget* v, XtPointer p );
  static void resizeCB( SoWidget glx, SoXtGLWidget* p, XtPointer pt );

  int m_nPixelFormat;

  SbBool m_supportFSAA;
  SbBool m_isFsaaEnable;    // is FSAA is active
  SbBool m_currentConfigSupportFsaa;  // is current configuration support FSAA

  // Flags used when the stereo is set from environment variables.
  bool m_stereoActiveDelayed; 
  bool m_stereoBufferFlag;

  SbBool m_singleBufferExpected;

  SoGuiGLWidget* m_guiGLWidget; //Implementation class for SoXxGLWidget

  void constructorCommon( int glModes, SbBool buildNow );

  SbBool remoteRenderGinitCB_pbuffer( SoWidget w );
};

inline void
SoXtGLWidget::posChanged( const SbVec2i32&, const SbVec2i32& )
{}

#endif // _SO_XT_GL_WIDGET_H_

#endif // _WIN32


