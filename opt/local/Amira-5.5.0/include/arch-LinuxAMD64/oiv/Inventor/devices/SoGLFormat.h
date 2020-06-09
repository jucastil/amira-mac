/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined( SO_GLFORMAT_H )
#define SO_GLFORMAT_H


#include <Inventor/sys/port.h>
#include <Inventor/SbBase.h>
#include <Inventor/helpers/SbGlContextHelper.h>

/** 
* @VSGEXT OpenGL pixel format management class.
*
* @ingroup GLDevice
*
* @DESCRIPTION
*
* This class provides functions to manage OpenGL pixel formats.
*
*/

class INVENTORGL_API SoGLFormat
{
public:

  /**
   * Default constructor -> we set the default format
   */
  SoGLFormat();

  /**
   * Constructor that uses the default format and stores 
   * the specified display.
   */
  SoGLFormat( const SbGlContextHelper::Display& display );

  /**
   * Constructor that initializes the format from the specified one.
   */
  SoGLFormat( const SoGLFormat& refFormat );

  /**
   * Destructor
   */
  virtual ~SoGLFormat();

  /**
   * Sets the double buffering state of this format.
   */
  void setDoubleBuffersEnabled( const bool enabled );

  /**
   * Returns true if this format is double buffered.
   */
  bool hasDoubleBuffers() const;
 
  /**
   * Returns true if this format has a depth buffer.
   */
  bool hasDepth() const;

  /**
   * Sets the depth buffer state of this format.
   */
  void setDepthEnabled( const bool enable );

  /**
   * Sets the depth buffer bits of this format.
   */
  void setDepthBits( const int bits );

  /**
   * Returns the depth buffer bits of this format.
   */
  int getDepthBits() const;

  /**
   * Returns true if this format has an alpha channel.
   */
  bool hasAlpha() const;

  /**
   * Sets the alpha channel state of this format.
   */
  void setAlphaEnabled( const bool enable );

  /**
   * Returns true if this format has an overlay plane.
   */
  bool hasOverlay() const;

  /**
   * Sets the overlay state of this format.
   */
  void setOverlayEnabled( const bool enabled );

  /**
   * Sets the plane of this format.
   *
   * The plane parameter indicates the OpenGL plane on which the format applies. 
   * Plane 0 is the main OpenGL plane, a negative value indicates an underlay plane,
   * while a positive value indicates an overlay plane.
   *
   * By default the plane is set to the main plane.
   */
  void setPlane( const int plane );
    
  /**
   * Returns the plane of this format.
   */
  int getPlane() const;

  /**
   * Sets the sample buffers state of this format.
   */
  void setSampleBuffersEnabled( const bool enable );

  /**
   * Returns true if this format has sample buffers.
   */
  bool hasSampleBuffers() const;

  /**
   * Sets the samples count of this format.
   */
  void setSamplesCount( const int countSamples );

  /**
   * Returns the samples count of this format.
   */
  int getSamplesCount() const;

  /**
   * Sets the stereo state of this format.
   */
  void setStereoEnabled( const bool enable );

  /**
   * Returns true if this format has stereo.
   */
  bool hasStereo() const;

  /**
   * Sets the RGB state of this format.
   */
  void setRgbEnabled( const bool enabled );

  /**
   * Returns true if this format is RGB.
   */
  bool hasRgb() const;

  void setRedBits(int bits);

  int getRedBits() const;

  void setGreenBits(int bits);

  int getGreenBits() const;

  void setBlueBits(int bits);

  int getBlueBits() const;

  void setAlphaBits(int bits);

  int getAlphaBits() const;

  /**
   * Sets the Float color buffer state of this format.
   */
  void setFloatColorBufferEnabled( const bool enable );

  /**
   * Returns true if this format has a float color buffer.
   */
  bool hasFloatColorBuffer() const;

  /**
   * Sets the stencil buffer state of this format.
   */
  void setStencilBufferEnabled( const bool enabled );

  /**
   * Returns true if this format has a stencil buffer.
   */
  bool hasStencilBuffer() const;

  /**
   * Sets the stencil buffer bits of this format.
   */
  void setStencilBufferBits( const int size );

  /**
   * Returns the stencil buffer bits of this format.
   */
  int getStencilBufferBits() const;

  /**
   * Sets the accumulation buffer state of this format.
   */
  void setAccumBufferEnabled( const bool enabled );

  /**
   * Returns true if this format has an accumulation buffer.
   */
  bool hasAccumBuffer() const;

  /**
   * Sets the accumulation buffer bits of this format.
   */
  void setAccumBufferBits( const int size );

  /**
   * Returns the accumulation buffer bits of this format.
   */
  int getAccumBufferBits() const;

  /**
   * Returns true if this format is available on the system. @BR
   * The display must be valid (see the setDisplay() function).
   */
  bool isAvailable() const;

  /**
   * Returns the supported format which is the nearest available
   * on this system. @BR
   * The display must be valid (see the setDisplay() function).
   */
  SoGLFormat getNearest() const;

  /**
   * Tries to activate the format for the current display. @BR
   * The display must be valid (see the setDisplay() function).
   */
  bool activate();

  /**
   * Returns the display on which this format is attached.
   */
  const SbGlContextHelper::Display& getDisplay() const;

  /**
   * Returns the visual info of the format. @BR
   * Can be NULL if the format has never been activated.
   */
  const SbGlContextHelper::VisualInfo& getVisualInfo() const;

  /**
   * Sets the composition requirement of the pixel format. @BR
   * This requirement is ignored on non-Microsoft platforms and
   * on Windows platforms before Windows Vista.  Requiring composition
   * will automatically disable GDI support for this format (this is a
   * Microsoft limitation).
   *
   * Note: If both setCompositionRequired() and setGDISupportRequired()
   * are set OpenInventor will try to choose a pixel format with
   * composition support. 
   *
   * The default value is false but can be overridden using the 
   * OIV_PFD_SUPPORT_COMPOSITION preference (see SoPreferences).
   */
  void setCompositionRequired( const bool required );

  /**
   * Returns true if composition is required for this pixel format.
   */
  bool isCompositionRequired() const;

  /**
   * Sets the GDI support requirement of the pixel format. @BR
   * This requirement is ignored on non-Microsoft platforms.
   *
   * Note: If both setCompositionRequired() and setGDISupportRequired()
   * are set OpenInventor will try to choose a pixel format with
   * composition support. 
   *
   * The default value is true but setting composition required to true
   * automatically disables GDI support.
   */
  void setGDISupportRequired( const bool required );

  /**
   * Returns true if GDI support is required for this pixel format.
   */
  bool isGDISupportRequired() const;

  /**
   * Sets the hardware acceleration support requirement of this pixel format.
   */
  void setAccelerationRequired(const bool enable);

  /**
   * Returns TRUE if hardware acceleration support is required for this pixel format.
   */
  bool isAccelerationRequired() const;

  /**
   * Returns the default format used.
   */
  static SoGLFormat getDefaultFormat();

  /**
   * Returns the default format for the overlay planes.
   */
  static SoGLFormat getDefaultOverlayFormat();

  /**
   * Sets the display associated with this format.
   */
  void setDisplay( const SbGlContextHelper::Display& display );

  /**
   * Sets the visual info associated with this format.
   *
   * Note: A valid Display must be set using the function setDisplay()
   * before calling this function. On some platforms the display is 
   * needed in order to parse the options stored in the visualInfo.
   */
  void setVisualInfo( const SbGlContextHelper::VisualInfo& visualInfo );

  /**
   * Sets the PFD id associated with this visualInfo.
   */
  void setVisualInfoId( const int viId );

  /**
   * Returns the PFD associated with this visualInfo.
   */
  int getVisualInfoId() const;

  /**
   * Sets the format according to the openGL attributes.
   */
  void setOpenglAttributes( const SbGlContextHelper::Display& display, int pfd, int* attributes, 
                           int* results );

  /**
   * Operator = to copy the data.
   */
  SoGLFormat& operator=( const SoGLFormat& ref );

  /**
   * Specified that a software renderer is required for this format.
   * This option is set to false by default.  If this option is set to
   * true it overrides setAccelerationRequired(). @BR
   * Note: This method is only implemented on Microsoft platforms in order to 
   * use the generic renderer provided by Microsoft. @BR
   * Note: This option is currently checked @B only @b by the QtViewer
   * classes (to switch on or off direct rendering).
   */
  void setSoftwareRendererRequired(const bool enable);

  /**
   * Returns true if the software renderer is required for this format.
   */
  bool isSoftwareRendererRequired() const;

SoINTERNAL public:

  /**
   * Returns TRUE if GDI support is available on this system.
   *
   * This function is available only on MS Windows platforms.
   */
  bool isGDIAvailable() const;

  /**
   * Returns TRUE if the format in RDP mode.
   *
   * This function is available only on MS Windows platforms.
   */
  bool isRDPMode() const;

protected:

  /**
   * Init function used by the constructors...
   */
  void init();

  void resetDetectedData();

private:

  bool m_doubleBuffers;

  bool m_depth;

  int m_depthBits;

  bool m_alpha;

  bool m_overlay;

  int m_plane;

  bool m_sampleBuffers;

  int m_samplesCount;

  bool m_stereo;

  bool m_rgb;

  int m_redBits;

  int m_greenBits;

  int m_blueBits;

  int m_alphaBits;

  bool m_floatColorBuffer;

  bool m_accumBuffer;

  int m_accumBufferBits;

  bool m_stencilBuffer;

  int m_stencilBufferBits;

  bool m_compositionRequired;

  bool m_gidSupportRequired;

  bool m_accelerationRequired;
  
  bool m_softwareRendererRequired;

  bool m_copyVisualInfoOnly;

  SbGlContextHelper::Display m_display;
  SbGlContextHelper::VisualInfo m_visualInfo;
  int m_visualInfoId;
};

#endif // SO_GLFORMAT_H
