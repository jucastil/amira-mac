/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Alain Dumesny (MMM yyyy)
** Modified by : David Mott (MMM yyyy)
**=======================================================================*/


#ifndef _SO_QT_GLWIDGET_
#define _SO_QT_GLWIDGET_

#include <Inventor/Qt/SoQtComponent.h>

#include <Inventor/Qt/OivQtCompat.h>
#include <Inventor/devices/SoGLFormat.h>

#include <Inventor/Gui/SoGuiGLWidget.h>
#include <Inventor/nodes/SoFullSceneAntialiasing.h>

#include <QtCore/Qt>

// FSAA
typedef std::set<int, std::less<int> > SoSamplesList;

#if !defined(_WIN32)
class SoQtRemoteRenderInfo;
#endif // _WIN32

#include <QtCore/QPointer>

/*
 * Defines used when specifying the glModes flag to the constructor.
 * (used instead of the glx.h defines which do overlap)
 */
#define SO_GLX_RGB (1<<0)
#define SO_GLX_DOUBLE (1<<1)
#define SO_GLX_ZBUFFER (1<<2)
#define SO_GLX_OVERLAY (1<<3)
#define SO_GLX_STEREO (1<<4)
#define SO_GLX_STENCIL (1<<5)

class QVBoxLayout;
class QCursor;
class SoGLContext;

class SoQGLContextProxy;
class SoQGLWidgetProxy;
class QGLFormat;
class QGLContext;

#if defined(_WIN32)
#pragma warning (push)
#pragma warning (disable : 4996)
#endif

/**
 * @VSGEXT Component for OpenGL rendering.
 *
 * @ingroup Qt
 *
 * @DESCRIPTION
 *   This abstract base class provides a C++ wrapper around an OpenGL widget.
 *   It allows OpenGL rendering to be performed within a widget and is
 *   used by the SoQtRenderArea. SoQtGLWidget uses a parent window with two separate
 *   OpenGL widgets (one for single and one for double buffering), with
 *   routines to return the appropriate windows.
 *
 * Since Open Inventor 8.0, the OpenGL widget is a QGLWidget.
 * More information about this class can be found on-line in the Qt
 * documentation.  Some useful methods include grabFrameBuffer, which
 * returns the current rendered image as a QImage object.
 *
 *   Subclasses only need to redefine the redraw() routine for rendering and
 *   processEvent() routine if they are interested in receiving Q events.
 *
 * @SEE_ALSO
 *    SoQtComponent,
 *    SoQtRenderArea
 *
 *
 */

class INVENTORQT_API SoQtGLWidget : public SoQtComponent
{
  Q_OBJECT

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
   * Sets the overlay transparent pixel.
   */
  void setOverlayTransparentPixel( unsigned long pixel );

  /** 
   * Returns the overlay color map size.
   */
  int getOverlayColorMapSize();

  /** 
   * Sets the overlay color map size.
   */
  void setOverlayColorMapSize( int size );

  /** 
   * Returns the color map size.
   */
  int getColorMapSize();

  /** 
   * Sets the color map size.
   */
  void setColorMapSize( int size );

  /**
   * Gets the normal GL window (window system identifier of the widget), which is
   * needed as an argument to glXMakeCurrent() (on Xt)
   * or SbGlContextHelper::makeCurrent() (on Windows) when drawing in the normal
   * planes.
   *
   * Note: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   */
  virtual WindowQt getNormalWindow();

  /**
   *
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
  WindowQt getOverlayWindow();

  /**
   * Gets the current normal context, which is
   * needed as an argument to glXMakeCurrent() (on Xt)
   * or SbGlContextHelper::makeCurrent() (on Windows) when drawing in the normal
   * planes.
   *
   * Note: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   */
  QGLContext* getNormalContext();
  SoGLContext* getNormalSoContext();

  /**
   * Gets the current overlay context, which is
   * needed as an argument to glXMakeCurrent() when drawing in the
   * overlay planes.
   *
   * Note: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   */
  QGLContext* getOverlayContext();
  SoGLContext* getOverlaySoContext();

  /**
   * Gets the current normal widget. @BR
   * Since Open Inventor 8.0, this widget is a QGLWidget.
   * More information about this class can be found on-line in the Qt
   * documentation.  Some useful methods include grabFrameBuffer, which
   * returns the current rendered image as a QImage object.
   *
   * The actual class returned by this method is an instance of 
   * SoQGLWidgetProxy, which is an Open Inventor internal class derived
   * from QGLWidget.  The instance can be used as a QGLWidget, but note
   * that Open Inventor manages OpenGL itself, so it does not implement
   * the initializeGL, paintGL, etc methods.
   *
   * Note: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   */
  QWidget* getNormalWidget();

  /**
   * Gets the current overlay widget, which is
   * needed as an argument to glXMakeCurrent() when drawing in the
   * overlay planes. @BR
   * Since Open Inventor 8.0, this widget is a QGLWidget.
   * More information about this class can be found on-line in the Qt
   * documentation.
   *
   * Note: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   */
  QWidget* getOverlayWidget();

  /** 
   * Returns the QGLFormat currently used.
   */
  QGLFormat* getNormalFormat();

  /** 
   * Sets the visual/pixel format for the normal window. @BR
   * This allows the user to create all possible visuals supported by OpenGL. The
   * OpenGL drivers or accelerated hardware may or may not support advanced features
   * such as alpha channel or stereographic viewing. If you request some features that
   * the driver/hardware does not provide when you set the @B QGLFormat @b, you will get
   * a rendering context with the nearest subset of features.
   *
   * The methods for setting the visual are virtual so that derived classes
   * can know when the visual is changing.
   */
  virtual void setNormalVisual( QGLFormat* vis );

  virtual void setNormalVisual( const SoGLFormat& format );


  /**
   * @deprecated no longer used.
   * use setNormalVisual(QGLFormat*).
   * @DEPRECATED_SINCE_OIV 8.0
   */
  virtual void setNormalVisual( SbGlContextHelper::VisualInfo vis );

  /**
   * Returns the @B QGLFormat @b for the normal window.
   */
  QGLFormat* getNormalVisual();

  /**
   * Specify exactly what the visual should be for the overlay window.
   * This allows the user to create all possible visual supported by OpenGL. The
   * @B XVisualInfo @b structure should be a valid OpenGL visual returned by
   * @B glXChooseVisual @b(). This structure will be copied by the SoQtGLWidget; the
   * application is responsible for freeing the visual info with @B XFree @b() when
   * done. (The methods for setting the visual are virtual so that derived classes
   * can know when the visual is changing.)
   */
  virtual void setOverlayVisual( QGLFormat* vis );

  virtual void setOverlayVisual( const SoGLFormat& format );

  /** 
   * @deprecated no longer used.
   * use setOverlayVisual(QGLFormat*).
   * @DEPRECATED_SINCE_OIV 8.0
   */
  SoDEPRECATED virtual void setOverlayVisual( SbGlContextHelper::VisualInfo vis );

  /**
   * Returns the @B QGLFormat @b for the overlay window.
   */
  QGLFormat* getOverlayVisual();

  /**
   * This shows the component.
   */
  virtual void show();

  /**
   * This hides the component.
   */
  virtual void hide();

  /**
   * Routine that dynamically changes between single and double buffering. Default
   * is double buffer off. (The SoQtRenderArea subclass makes it double buffer by
   * default.)
   */
  virtual void setDoubleBuffer( SbBool onOrOff );

  /**
   * Returns whether double buffering is on or off.
   */
  SbBool isDoubleBuffer() { return m_guiGLWidget->isDoubleBuffer(); }

  /**
   * Included for portability only.
   */
  void  setBorder( SbBool onOrOff );

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
   * an obscured portion of the window is exposed. Default: TRUE.
   */
  void setDrawToFrontBufferEnable( SbBool enableFlag );

  /**
   * Queries drawing to the front buffer.
   */
  SbBool isDrawToFrontBufferEnable() const { return m_guiGLWidget->isDrawToFrontBufferEnable(); }

  /** 
   * @deprecated No longer used. use bindNormalContext and unbindNormalContext
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
   * Swaps the normal front and back buffers. 
   */
  virtual SbBool swapNormalBuffers();

  /**
   * Makes the overlay rendering context the current context.
   */
  SbBool makeOverlayCurrent();

  /**
   * Makes the overlay rendering context the current context. 
   * Equivalent to makeOverlayCurrent() call.
   */
  virtual SbBool bindOverlayContext();

  /**
   * unbind the current context (previously bind with bindOverlayContext );
   */
  virtual SbBool unbindOverlayContext();

  /**
   * Swaps the overlay front and back buffers. Equivalent to calling
   */
  SbBool swapOverlayBuffers();

  /**
   * Sets the current cursor. If you are using a viewer class, the viewer will
   * automatically change the cursor depending on the viewer mode. These changes will
   * override the cursor set with this method unless you also call
   * SoQtGLWidget::setCursorEnabled(FALSE).
   */
  virtual void setCursor( const QCursor& newCursor );

  /**
   * Returns the current cursor.
   */
  QCursor getCursor() const;

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
   * @deprecated Method hsa been renamed. Use isFullSceneAntialiasingAvailable
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

  SoINTERNAL public:
#if !defined(_WIN32) && !defined(__APPLE__) //UNIX
  // WARNING : Workaround only available for Amira/Avizo
  // These methods should be removed when the GraphicConfigs will be implemented for Qt.
  void setAttribList( const int* newAttribList );
  int* getAttribList() const;
#endif // UNIX

  SoGuiGLWidget* getGuiGLWidget() const;

  // These variables are  public for retro compatibility purposes only.
  // Do not use them directly but call their accessors instead;
  SbBool drawToFrontBuffer;

  // These two function are used by SoGui, to call the system dependent version of
  // these functions. data is a SoWinGLWidget handle.
  static SbBool swapNormalBuffersCB( void *data );
  static SbBool bindNormalCurrentCB( void *data );
  static SbBool unbindNormalCurrentCB( void *data );
  static void* getNormalWindowCB( void *data );
  static void* getCurrentDisplayCB(void *data);

 SoEXTENDER public:

  // Starting with version 3.0, subclasses should no longer make direct
  // calls to glXMakeCurrent, glXSwapBuffers and glFlush.
  // For RemoteRendering we need to know when MakeCurrent is called
  // (marking the beginning of a frame) and when SwapBuffers or glFlush
  // is called (marking the end of a frame).
  // Subclasses should always use these generic methods.
  void   flush();

#if !defined(__APPLE__) && !defined(_WIN32) //UNIX
  // Pbuffers are a limited resource.  By default use of Pbuffers for
  // remote rendering is enabled, but it might make sense to disable
  // it for less important windows (like UI components drawn with OpenGL).
  // Must be called after creating the widget but before it is realized.
  void setRemoteRenderPbufferEnable( SbBool enable )
    { m_remoteRenderPbufferEnable = enable; }

  SbBool isRemoteRenderPbufferEnable() const
    { return m_remoteRenderPbufferEnable; }

  float getLowResPercent() {return m_lowResPercent;}
#endif

 protected:

  SoQtGLWidget( QWidget* parent = NULL,
                const char* name = NULL,
                SbBool buildInsideParent = TRUE,
                int glModes = SO_GLX_RGB,
                SbBool buildNow = TRUE,
                SbBool sync = TRUE );

  SoQtGLWidget( QWidget* parent,
                const char* name,
                SbBool buildInsideParent,
                int glModes,
                SbBool buildNow,
                SbBool sync,
                SoGuiGLWidget* guiGLWidget );

#if defined(sun) || defined(__linux__) || defined(__hpux)
  SoQtGLWidget( QWidget* parent,
                const char* name,
                SbBool buildInsideParent,
                int glModes,
                SbBool buildNow,
                SbBool sync,
                SbBool connectionType );

  SoQtGLWidget( QWidget* parent,
                const char* name,
                SbBool buildInsideParent,
                int glModes,
                SbBool buildNow,
                SbBool sync,
                SbBool connectionType,
                SoGuiGLWidget* guiGLWidget );
#endif

  virtual ~SoQtGLWidget();

  ////////////////////////////////////////////////////////////////////////
  // EVENTS

  virtual void paintEvent( QPaintEvent* );

  virtual void resizeEvent( QResizeEvent* );

  virtual void closeEvent( QCloseEvent* );

  virtual void focusInEvent( QFocusEvent* );

  virtual void focusOutEvent( QFocusEvent* );

  virtual void showEvent( QShowEvent* );

  virtual void hideEvent( QHideEvent* );

  virtual void moveEvent( QMoveEvent* );

  virtual void keyPressEvent( QKeyEvent* );

  virtual void keyReleaseEvent( QKeyEvent* );

  virtual void mouseMoveEvent( QMouseEvent* );
  
  virtual void mousePressEvent( QMouseEvent* );

  virtual void mouseReleaseEvent( QMouseEvent* );

  virtual void mouseDoubleClickEvent( QMouseEvent* );

  virtual void wheelEvent( QWheelEvent* );

  bool eventFilter( QObject* object, QEvent* event );

  // subclasses can use this routine as the event handler for any
  // devices they wish to get input from.
  static void eventHandler( QWidget* w, SoQtGLWidget* glw, QEvent* qe, bool* b );

  // This function is overloaded by the render area to set the window element
  virtual void onFocusEvent(SbBool hasFocus);

  ////////////////////////////////////////////////////////////////////////


  // subclasses MUST redefine redraw() to draw in the normal bit planes.
  // redrawOverlay() should be defined if the overlay planes are being
  // used, and processEvent() should be defined if X events are being
  // received (see eventMask).
  virtual void redraw() = 0;
  virtual void redrawOverlay();
  virtual void processEvent( QEvent* anyevent );

  void performPaint();

  // subclasses can redefine these to do something useful.
  // initGraphic() is called whenever a GLX window gets created
  // sizeChanged() is called whenever the window changes size
  // widgetChanged() is called whenever the widget is changed (i.e. at
  //    initialization or after switching from single->double buffer)
  virtual void initGraphic();
  virtual void initOverlayGraphic();
  virtual void sizeChanged( const SbVec2s& size );
  virtual void posChanged( const SbVec2i32&, const SbVec2i32& ) {};
  virtual void widgetChanged( QWidget* w );

  // sets/gets the size of the glx widget(s) - Note this size could be
  // different from the SoWinComponent::getSize() method which return
  // the size of the component, not necessary the same as the glx widget
  // window (because of extra stuff like the decoration in the viewers).
  void  setGlxSize( SbVec2s newSize );
  const SbVec2s& getGlxSize() const { return m_guiGLWidget->getGlxSize(); }

  // set/get stereo buffering visual. This routine (like setDoubleBuffer)
  // can be called interactively, althought slower since a new window
  // with the needed visual is always created on the fly.
  void setStereoBuffer( SbBool flag );
  SbBool isStereoBuffer() { return (m_guiGLWidget->getGLModes() & SO_GLX_STEREO); }

  // returns TRUE if main window is in rgb mode (FALSE if color index)
  SbBool isRGBMode() { return (m_guiGLWidget->getGLModes() & SO_GLX_RGB); }

#if defined(sun) || defined(__linux__)
  void allocCell( Display* display, Colormap cmap, XColorPointer colorcells,
                  int ncolors, int colorMapSize );
#endif

  SbBool waitForExpose;

  QWidget* buildWidget( QWidget* parent );
  void changeCursor( QCursor newCursor );
  QWidget* getGlxMgrWidget() { return (QWidget*) mgrWidget; }

  virtual void onExpose();
  virtual void onOverlayExpose();

  // ----- RemoteRender additions (v3.0) -----
  // FSAA
  SbBool m_initialFsaaValueChanged;

#if !defined(_WIN32) && !defined(__APPLE__)
  enum RemoteRenderEnabled  // Possible values for remote rendering
  {
    OFF,                      // Never use remote rendering
    ON,                       // Always try to use remote rendering
    AUTO                      // Use if remote does not support GLX (default)
  };
  RemoteRenderEnabled   m_remoteRenderMode;  // See possible values above
  SoQtRemoteRenderInfo* m_remoteRenderInfo;  // Opaque type for internal state
  SbBool                m_remoteRenderPbufferEnable; // Can we use a Pbuffer?
  SbBool                m_lowResRender;      //Is Low Resolution Render Mode in use?
  float                 m_lowResLowPercent;  //lowest value of m_lowResPercent
  float                 m_lowResHighPercent; //highest value of m_lowResPercent
  float                 m_lowResPercent;    //percent of the window sent thru the network

  void remoteRenderInit();                // Init member vars
  void remoteRenderCleanup();             // Free allocated resources
  void remoteRenderGinitCB( QWidget* );     // Create pixmap and other stuff
  GLXContext remoteRenderLowResRenderGinitCB( QWidget* ); //Same for LowResRender configuration : return Remote Context
  void remoteRenderResizeCB();            // Resize pixmap
  void remoteRenderSendImage();           // Send rendered image to remote display
  void remoteRenderSendLowResRender();    // send low Resolution image to remote display
  SbGlContextHelper::VisualInfo remoteRenderChooseVisual();        // Find visual for remote window
  void remoteRenderFatalError( const char* methodName, const char* message );

  void setLowResLowPercent( float percent ) { m_lowResLowPercent = percent; }
  void setLowResHighPercent( float percent ) { m_lowResHighPercent = percent; }
  float getLowResLowPercent() const { return m_lowResLowPercent; }
  float getLowResHighPercent() const { return m_lowResHighPercent;}

  virtual void setLowResPercent( float newLowres ) { m_lowResPercent = newLowres; }
#endif

 private:

   void constructorCommon( SbBool buildNow, SbBool connectionType );
   SoGuiGLWidget* m_guiGLWidget; //Implementation class for SoXxGLWidget

  // local vars
  QPointer<QWidget>   mgrWidget;

  QVBoxLayout*        mgrVbl;

  SoQGLContextProxy*       m_context;
  QWidget*            m_widget;

  SoGLFormat m_overlayVis;

  // Flags used when the stereo is set from environment variables.
  bool m_stereoActiveDelayed; 
  bool m_stereoBufferFlag;

#if defined(sun) || defined(__linux__) || defined(__hpux)
  SbBool directConnection;
#endif

  QCursor currentCursor;
  int* attribList;

  SbBool windowResized;

  // set of windows, color maps, etc...
  void buildNormalGLXWidget( SoGLFormat* format = NULL );
  void buildOverlayGLXWidget( SoGLFormat* format = NULL );

  void destroyNormalWindows();
  void destroyGLXWidget( SbBool normalCall );

  void destroyOverlayWidget( SbBool normalCall );
  void destroyNormalWidget( SbBool normalCall );

  friend class SoQGLWidgetProxy;

  // callbacks from glx widget
  static void ginitCB( QWidget* w, SoQtGLWidget* glw, void* v );
  static void overlayGinitCB( QWidget* glx, SoQtGLWidget* p, void* v );
  static void exposeCB( QWidget* w, SoQtGLWidget* glw, void* v );
  static void overlayExposeCB( QWidget* w, SoQtGLWidget* glw, void* v );
  static void resizeCB( QWidget* w, SoQtGLWidget* glw, void* v );

  static SbBool onGLFormatChangeCallback( SoGLFormat& format, void* userData );

  SbBool remoteRenderGinitCB_pbuffer( QWidget* );
};

#if defined(_WIN32)
#pragma warning (pop)
#endif


#endif // _SO_QT_GLWIDGET_

