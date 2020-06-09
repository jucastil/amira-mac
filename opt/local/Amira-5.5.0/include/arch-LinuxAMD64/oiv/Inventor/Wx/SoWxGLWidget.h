/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jul 2007)
**=======================================================================*/

#ifndef SO_WX_GLWIDGET
#define SO_WX_GLWIDGET

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWxGLWidget
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/Wx/SoWxComponent.h>
#include <Inventor/Wx/SoWxGLX.h>

#include <Inventor/nodes/SoFullSceneAntialiasing.h>

#include <Inventor/Gui/SoGuiGLWidget.h>

#define MGRWIDGET_ID 101
#define ATTRIBLIST_END 0
#define NO_OP -1 // Used in the attribute list passed to the wxGLCanvas as a noop.

typedef std::set<int, std::less<int> > SoSamplesList;

/**
 * @VSGEXT Component for OpenGL rendering.
 * 
 * @ingroup Wx
 * 
 * @DESCRIPTION
 *   This abstract base class provides a C++ wrapper around an OpenGL widget.
 *   It allows OpenGL rendering to be performed within a widget and is
 *   used by the SoWxRenderArea. SoWxGLWidget uses a parent window with two separate
 *   OpenGL widgets (one for single and one for double buffering), with
 *   routines to return the appropriate windows.
 *   
 *   Subclasses only need to redefine the redraw() routine for rendering and
 *   processEvent() routine if they are interested in receiving wx events.
 * 
 * @SEE_ALSO
 *    SoWxComponent,
 *    SoWxRenderArea
 * 
 * 
 */ 

class SoGuiGLWidget;
class SoWxGLX;
class SoGLContext;

class INVENTORWX_API SoWxGLWidget : public SoWxComponent
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
   * 
   */
  int getColorMapSize();
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
	virtual wxWindow* getNormalWindow();

  /**
   * Gets the current normal context, which is
   * needed as an argument to glXMakeCurrent() (on Xt) 
   * or SbGlContextHelper::makeCurrent() (on Windows) when drawing in the normal
   * planes.
   * 
   * Note: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   */
  wxGLContext* getNormalContext() { return m_wxContextNormal; }

  SoGLContext* getNormalSoContext() { return m_contextNormal; }

  /**
   * Gets the current normal widget.
   * 
   * Note: This should @B not @b be cached by users because it will change as
   * single/double buffering changes.
   */
  SoWxGLX* getNormalWidget();

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
  SoWxGLX* getOverlayWidget() { return NULL; }

#if defined(_WIN32)
  /**
   * Returns the device context (which is needed for SbGlContextHelper::makeCurrent).
   */
  Hdc getNormalDC() { return m_hdcNormal; }
 
  /**
   * Returns the overlay device context (which is needed for SbGlContextHelper::makeCurrent).
   */
  Hdc getOverlayDC() { return m_hdcOverlay; }
#endif

  /**
   * Specifies exactly what the visual should be for the normal window.
   * This allows the user to create all possible visuals supported by OpenGL regarding
   * the features supported by the wxGLCanvas. The @B attribList @b structure should be 
   * a valid list or attributes supported by wxGLCanvas class. 
   * This list will be copied by the SoWxGLWidget; the application is responsible for 
   * freeing the list info when done. 
   *
   * The methods for setting the visual are virtual so that derived classes
   * can know when the visual is changing. 
   */
  virtual void setNormalVisual( int* attribList );

  /**
   * Returns the list of attributes for the normal window.
   */
  int* getNormalVisual();

  /**
   * This shows the component.
   */
  virtual void show();

  /**
   * This hides the component.
   */
  virtual void hide();

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
   * Unbind the current context (previously bind with bindNormalContext );
   */
  virtual SbBool unbindNormalContext();

  /**
   * Swap the normal front and back buffers.
   */
  SbBool swapNormalBuffers();

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

  SoINTERNAL public:

  SoGuiGLWidget* getGuiGLWidget() const;


  SbBool isFsaaSupportHighQuality();
  SbBool isFsaaHighQuality();

  // These two function are used by SoGui, to call the system dependent version of 
  // these functions. data is a SoWinGLWidget handle.
  static SbBool swapNormalBuffersCB(void *data);
  static SbBool bindNormalCurrentCB(void *data);
  static SbBool unbindNormalCurrentCB(void *data);
  static void* getNormalWindowCB(void *data);

 SoEXTENDER public:
        
  // Starting with version 3.0, subclasses should no longer make direct
  // calls to glXMakeCurrent, glXSwapBuffers and glFlush.
  // For RemoteRendering we need to know when MakeCurrent is called
  // (marking the beginning of a frame) and when SwapBuffers or glFlush
  // is called (marking the end of a frame).
  // Subclasses should always use these generic methods.
  void flush();

  static void exposeCB( SoWxGLWidget* p );

  // subclasses can use this routine as the event handler for any
  // devices they wish to get input from.
  static void eventHandler( wxWindow* wxW, SoWxGLWidget* w, wxEvent& wxE, bool* boolean );
  static void showEventHandler( SoWxGLWidget* w, wxShowEvent& wxE );
        
#ifdef _WIN32
  // Set/get thread this context belongs to -- mmh Apr-99
  DWORD getThreadId() { return m_dwThreadId; };
  void setThreadId(DWORD id) { m_dwThreadId = id; };
#endif  
        
  /**
   * Sets the current cursor. If you are using a viewer class, the viewer will
   * automatically change the cursor depending on the viewer mode. These changes will
   * override the cursor set with this method unless you also call
   * SoWxGLWidget::setCursorEnabled(FALSE). 
   */
  void setCursor( wxCursor newCursor );

  /**
   * Returns the current cursor. 
   */
  wxCursor getCursor(); 

 protected:
        
  SoWxGLWidget( wxWindow* parent = NULL,
                const char* name = NULL, 
                SbBool buildInsideParent = TRUE, 
                int glModes = SO_GLX_RGB, 
                SbBool buildNow = TRUE,
                SbBool sync = TRUE );

  SoWxGLWidget( wxWindow* parent,
                const char* name, 
                SbBool buildInsideParent, 
                int glModes, 
                SbBool buildNow,
                SbBool sync,
                SoGuiGLWidget* guiGLWidget );
        
  virtual ~SoWxGLWidget();
        
  // subclasses MUST redefine redraw() to draw in the normal bit planes.
  // redrawOverlay() should be defined if the overlay planes are being
  // used, and processEvent() should be defined if X events are being 
  // received (see eventMask).
  virtual void redraw() = 0;
  virtual void processEvent( wxEvent& anyEvent );
  virtual void visibilityChangeCB( wxShowEvent& showEvent );
        
  // subclasses can redefine these to do something useful.
  // initGraphic() is called whenever a GLX window gets created
  // sizeChanged() is called whenever the window changes size
  // widgetChanged() is called whenever the widget is changed (i.e. at
  // initialization or after switching from single->double buffer)
  virtual void initGraphic();
  virtual void sizeChanged( const SbVec2s& size );
  virtual void posChanged( const SbVec2i32&, const SbVec2i32& ) { /* Do nothing */ };
  virtual void widgetChanged( wxWindow* w );
    
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
        
  // returns the display lists share group for given context:
  int getDisplayListShareGroup( SoGLContext* ctx );
        
  SbBool waitForExpose;
        
  wxPanel* buildWidget( wxWindow* parent, int* attribList = 0 );
  void changeCursor( wxCursor newCursor );
  wxPanel* getGlxMgrWidget() { return m_mgrWidget; }

  bool eventFilter( wxEvent& anEvent );
        
  virtual void onExpose();

SoINTERNAL protected:
  SbBool m_initialFsaaEnable;
  int m_initialFsaaFilterMask;
  SbBool m_initialFsaaValueChanged;
  SbBool m_isFsaaEnable;    // is FSAA is active


 private:

  void constructorCommon( int glModes, SbBool buildNow, SbBool connectionType );
  SoGuiGLWidget* m_guiGLWidget; //Implementation class for SoXxGLWidget

  // Functions used to redirect specific events to eventFilter which takes wxEvents
  void keyboardEvents( wxKeyEvent& redirectedEvent );
  void moveEvents( wxMoveEvent& redirectedEvent );
  void sizeEvents( wxSizeEvent& redirectedEvent );
  void showEvents( wxShowEvent& redirectedEvent );

  // Process close events to invalidate SoGLContexts drawables.
  void internalClose( wxCommandEvent& ce );
        
  // local vars
  wxPanel* m_mgrWidget;
  SoWxGLX* m_doubleBufferWidget; 
  SoWxGLX* m_singleBufferWidget; 
  SoGLContext* m_contextNormal;
  SoGLContext* m_contextSingle;
  SoGLContext* m_contextDouble;

  wxGLContext* m_wxContextNormal;
  wxGLContext* m_wxContextSingle;
  wxGLContext* m_wxContextDouble;
 
#if defined(_WIN32)
  Hdc m_hdcNormal, m_hdcOverlay, m_hdcSingle, m_hdcDouble;
  DWORD m_dwThreadId; // thread to which this context belongs -- mmh Apr-99
#endif // _WIN32
    
  SbBool m_directConnection;

  wxCursor m_currentCursor;
  int* m_attribList; 
  SbBool m_windowResized;
        
  // set of windows, color maps, etc...
  void buildNormalGLXWidget( int* attribList = NULL );

  void destroyNormalWindows();
  void destroyGLXWidget( SoWxGLX* &w, SoGLContext*& ctx, SbBool normalCall );
  void changeGLX();

  // callbacks from glx widget
  static void ginitCB( SoWxGLX* w, SoWxGLWidget* p, void* d );
  static void resizeCB( wxWindow* w, SoWxGLWidget* p, void* d );

  //FSAA
  int getNumSamples(size_t n);
  int findSampleIndex(int findInt);
  void listFSAAMaxSamples();
  SoSamplesList m_samplesParseTab;

  //ginit
  SbBool m_initGLX;
  //changeGLX
  wxFrame* m_dummyFrame;

  // wxWidgets specific : macro that declares an event table
  DECLARE_EVENT_TABLE()
};


#endif // SO_WX_GLWIDGET

