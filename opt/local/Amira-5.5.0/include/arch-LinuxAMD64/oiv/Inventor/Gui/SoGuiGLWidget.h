/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jun 2007)
**=======================================================================*/

#ifndef SO_GUI_GL_WIDGET_H
#define SO_GUI_GL_WIDGET_H

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGuiGLWidget
//
// SoXXGLWidgets implementation class
// 
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/Gui/SoGuiComponent.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/devices/SoGLFormat.h>
#include <Inventor/nodes/SoFullSceneAntialiasing.h>

class SoGLGraphicConfigTemplate;

#ifndef HIDDEN_FROM_DOC
typedef SbBool (*soGUIDependentCB)(void* data);
typedef void* (*soGUIWindowDependentCB)(void* data);
#endif

/** [OIV-WRAPPER-NO-WRAP] */
class INVENTORGUI_API SoGuiGLWidget : public SoGuiComponent 
{
#ifndef HIDDEN_FROM_DOC
  SO_FIELDCONTAINER_HEADER( SoGuiGLWidget );
#endif

SoINTERNAL public:

  SoSFFieldContainer gcTemplate;
  SoSFBool focus;
  SoSFBool FSAAEnable;
  SoSFFloat FSAAQuality;
  SoSFInt32 FSAAMask;

  enum FloatColorBufferSize 
  {
    /**
      * 16-bit rendering per component.
      */
    FLOAT_16_COLOR_BUFFER = 0,
    /**
      * 32-bit rendering per component.
      */
    FLOAT_32_COLOR_BUFFER = 1
  };
  
  /**
  * Constructor.
  */
  SoGuiGLWidget();

  /**
   * Returns the value of the overlay transparent pixel
   */
  unsigned long getOverlayTransparentPixel();

  /**
   * Sets the value of the overlay transparent pixel
   */
  void setOverlayTransparentPixel( unsigned long pixel );

  /**
   * Sets the size of the overlay color map
   */
  void setOverlayColorMapSize( int size );
  
  /**
   * Returns the size of the overlay color map
   */
  int getOverlayColorMapSize();

  /**
   * Sets the size of the color map
   */
  void setColorMapSize( int size );

  /**
   * Returns the size of the color map
   */
  int getColorMapSize();

  /**
   * Returns whether double buffering is on or off.
   */
  SbBool isDoubleBuffer();

  /**
   * Shows/hides a border of thickness 3 around the glX widgets. This
   * if OFF by default, but turned on by the render area.
   */
  void setBorder( int newValue );

  /**
   * Included for portability only.
   */
  int getBorderSize();

  /**
   * Returns whether the border is on or off.
   */
  SbBool isBorder() const;
 
  /**
   * Sets drawing to the front buffer. Controls drawing to the front buffer when
   * an obscured portion of the window is exposed. Default: TRUE.
   */
  void setDrawToFrontBufferEnable( SbBool enableFlag );

  /**
   * Queries drawing to the front buffer.
   */
  SbBool isDrawToFrontBufferEnable() const;

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

  /**
   * Returns TRUE if floating point rendering is available.
   */
  static SbBool isFloatingColorBufferSupported();

  /**
   * Enables or disables full-scene antialiasing (FSAA). Returns TRUE on success.@BR
   * FSAA requires the @I ARB_multisample@i and @I ARB_pixel_format@i OpenGL extensions.
   *
   * Note: Use the SoFullSceneAntialiasing node to control FSAA during render traversal.
   *
   * @param enable  Enables or disables FSAA rendering.  
   * @param quality  Specifies quality of the antialiasing rendering. @BR
   *   Quality values are in the interval [0..1], where 0 is the lowest quality and 1 is
   *   the highest quality. When set to -1.0 (default) the quality value is the default 
   *   value for the pixel format.  
   *   The number of samples used in the antialiasing computation depends on your graphics
   *   hardware and on your video driver. NVidia graphics hardware can support @I number of 
   *   samples * 2 @i levels of quality (assuming the @I NV_multisample_filter_hint @i
   *   OpenGL extension is available).  
   * @param filterMask  Specifies the types of shapes that should be antialiased. @BR
   *   Default is all shapes. See SoFullSceneAntialiasing for more info.
   */
  SbBool setFullSceneAntialiasing( SbBool enable,
                                   float quality = -1.f, 
                                   int filterMask = SoFullSceneAntialiasing::ALL );

  /**
   * Returns TRUE, if full-scene antialiasing (FSAA) is enabled.
   */
  SbBool isFullSceneAntialiasingEnabled() const;
  SoDEPRECATED SbBool isFsaaEnabled() const;

  /** 
   * Returns the current full-scene antialiasing (FSAA) parameters. 
   * Returns TRUE if FSAA is enabled.
   */
  SbBool getFullSceneAntialiasing( float& quality, int& filterMask ) const;

  /** 
   * Returns TRUE if FSAA is supported by current pixel format.
   */
  SbBool isFullSceneAntialiasingAvailable();

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
  SbBool isFullSceneAntialiasingHQAvailable();
  SoDEPRECATED SbBool isFsaaSupportHighQuality();

  /**  
   * Enables or disables high quality mode for full-scene antialiasing (FSAA).
   *
   * This feature requires the GL_MULTISAMPLE_FILTER_HINT_NV extension.
   */
  SbBool setFullSceneAntialiasingHQ( SbBool enable );
  SoDEPRECATED SbBool setFsaaHighQuality( SbBool enable );

  /** 
   * Returns TRUE if the high quality mode for full-scene antialiasing (FSAA) is enabled.
   */
  SbBool isFullSceneAntialiasingHQEnabled() const;
  SoDEPRECATED SbBool isFsaaHighQuality();

  /** 
   * Returns the maximum number of samples for full-scene antialiasing (FSAA).
   */
  int getFullSceneAntialiasingMaxSamples() const;
  SoDEPRECATED int getFsaaMaxSamplesCount() const;

  /**
   * Sets the glMode member
   * This function updates the format returned by getGLFormat()
   * @param mode the new mode.
   */
  void setGLModes( int mode );

  /**
   * Returns the glMode member.
   */
  int getGLModes() const;

  /**
   * This function allows custom formats to be used by the render area.
   * It is possible to get the current format using getGLFormat() and enable some features
   * or different colors formats.
   * 
   * Returns TRUE on success.
   */
  SbBool setGLFormat( const SoGLFormat& format );

  /**
   * Returns the current OpenGL format used by the render area.
   */
  const SoGLFormat& getGLFormat() const;

  /** 
   * Format of the callback function to provide to the setOnFormatChangeCalback().
   *
   * Returns FALSE if the format is not usable.
   */
  typedef SbBool (*FormatChangeCallback)( SoGLFormat&, void* userData );

  /** 
   * This function sets a callback function which checks and applies new formats.
   * It must destroy and create the OpenGL surfaces according to the new format.
   */
  void setOnFormatChangeCalback( FormatChangeCallback callback, void* userData = NULL );

  /** 
   * Enable double buffering in the current OpenGL configuration.
   *
   * When the function is called the OpenGL surface is recreated.
   *
   * Returns TRUE on success.
   */
  SbBool setDoubleBuffer( SbBool enable );

  /**
   * Enable remote rendering (X11 systems only).
   */
  void setRemoteRendering( bool enable );

  /** 
   * Returns true if remote rendering is enabled (X11 systems only).
   */
  bool isRemoteRendering() const;

  /** 
   * Enable OpenGL "quad buffer" stereo in the current render area.
   * Returns TRUE on success.
   */
  SbBool setStereoEnabled( SbBool enable );

  /** 
   * Returns true if OpenGL stereo is enabled.
   */
  SbBool isStereoEnabled() const;

  // Accessor and mutator for the member m_drawToFrontBuffer
  void setDrawToFrontBuffer( SbBool enable );
  SbBool getDrawToFrontBuffer() const;

  // Accessor and mutator for the member m_overlayColorMap
  void setOverlayColorMap( unsigned long overlayColorMap );
  unsigned long getOverlayColorMap() const;

  // Accessor and mutator for the member m_colorMap
  void setColorMap( unsigned long colorMap );
  unsigned long getColorMap() const;

  // ----------------------- Extension usage -----------------------------------
 
  // sets/gets the size of the glx widget(s) - Note this size could be
  // different from the SoXtComponent::getSize() method which return
  // the size of the component, not necessary the same as the glx widget
  // window (because of extra stuff like the decoration in the viewers).
  void setGlxSize( SbVec2s newSize );
  const SbVec2s& getGlxSize() const;
 
  SbBool isStereoBuffer();
 
  // returns TRUE if main window is in rgb mode (FALSE if color index)
  SbBool isRGBMode();

  // return the graphic config template from field gcTemplate.
  void setGraphicConfigTemplate( SoGLGraphicConfigTemplate* gc );
  SoGLGraphicConfigTemplate* getGraphicConfigTemplate();

  // setup system dependent GLWidget handles.
  void setGLWidgetHandle( const void* glWidgetHandle,
                          soGUIDependentCB swapBufferCB,
                          soGUIDependentCB bindCurrentCB,
                          soGUIDependentCB unbindCurrentCB,
                          soGUIWindowDependentCB getNormalCB,
                          soGUIWindowDependentCB getDisplayCB = NULL);

  // These call are internal public to let IvTune to access them.
  // handle on GLWidget handle/function comming from system independent GUI
  // initialized through setGLWidgetHandle;
  static soGUIDependentCB swapNormalBuffersCB;
  static soGUIDependentCB bindNormalCurrentCB;
  static soGUIDependentCB unbindNormalCurrentCB;
  static soGUIWindowDependentCB getNormalWindowCB;
  static soGUIWindowDependentCB getCurrentDisplayCB;
  void * m_glWidgetHandle;

  virtual void* getNormalWindow() { return getNormalWindowCB(m_glWidgetHandle); }
  virtual void* getDisplay() { return getCurrentDisplayCB(m_glWidgetHandle); }

  virtual SbBool bindNormalContext();
  virtual SbBool unbindNormalContext();

protected:

  /**
  * Destructor.
  */
  virtual ~SoGuiGLWidget();

  static SbBool m_hasFloatBuffer;

// ----------------------- Private usage -------------------------------------
private:

  // local vars
  SbVec2s m_glxSize; // size of glx widgets which is always up to date
  int m_glModes;
  int m_borderSize;

  SoGLFormat m_format;
  FormatChangeCallback m_formatChangeCallback;
  void* m_formatChangeCallbackUserData;
  
  unsigned long m_colorMap; // set when color index is used
  unsigned long m_overlayColorMap; // set when overlay is used
  int m_colorMapSize;
  int m_overlayColorMapSize;

  SbBool m_drawToFrontBuffer; // used by RA to draw new scenes to front buffer
  SbBool m_enableDrawToFrontBuffer;
 
  unsigned long m_transparentPixel;

  SbBool m_isFsaaHighQuality; // is FSAA is high quality level
  int m_isFsaaSupported; // is graphics hardware support FSAA
  int m_isFsaaSupportHighQuality;  // is FSAA support nVidia High quality level.
  mutable int m_fsaaMaxSamplesCount;
  int m_fsaaFilterMask;
  bool m_fsaaEnabled; // We don't want to change the GL format to disable the FSAA!

  bool m_isRemoteRendering;

  SbBool m_isFloatingPointRendering;
  FloatColorBufferSize m_floatingPointRenderingPrecision;

  SoGLGraphicConfigTemplate* m_gcTemplate;
};


#endif // SO_GUI_GL_WIDGET_H


