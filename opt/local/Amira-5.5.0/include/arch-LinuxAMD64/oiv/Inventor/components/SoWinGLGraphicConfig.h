/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_WIN_GL_GRAPHIC_CONFIG_H_
#define _SO_WIN_GL_GRAPHIC_CONFIG_H_

#include <Inventor/components/SoGLGraphicConfig.h>
#include <Inventor/components/SoGLGraphicDevice.h>
class SoGLGraphicDevicePeer;
#ifndef _WIN32
#  define PIXELFORMATDESCRIPTOR void *
#endif

/**
 * @VSGEXT Represents an OpenGL graphics configuration for Microsoft Windows systems.
 * 
 * @ingroup General
 * 
 * @DESCRIPTION
 * This class is a representation of a Microsoft Windows pixel format. Compared to
 * its parent class, this class adds a method to query the system-dependent pixel
 * format information.
 * 
 * @SEE_ALSO
 *    SoGraphicConfigTemplate, SoGLGraphicConfigTemplate, 
 *    SoGraphicConfig, SoGraphicDevice, SoGLGraphicDevice, SoFullSceneAntialiasing.
 * 
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 */
class INVENTOR_API SoWinGLGraphicConfig : public SoGLGraphicConfig {

 public:

  /**
   * Returns TRUE if double buffer mode is enabled, 
   * else FALSE (single buffer mode). 
   */
  virtual SbBool isDoubleBuffer() const;

  /**
   * Returns TRUE if stereo buffer mode is supported.
   */
  virtual SbBool isStereoBuffer() const;

  /**
   * Returns TRUE if the OpenGL graphics configuration is accelerated.
   */
  virtual SbBool isAccelerated() const;

  /**
   * Returns TRUE if the OpenGL graphics configuration has overlays 
   * supported by Open Inventor.
   */
  virtual SbBool hasOverlays() const;

  /**
   * Returns the Z-buffer depth. 
   * If 0 is returned, then there is no Z-buffer.
   */
  virtual void getDepth(int &bits) const;

  /**
   * Returns the indexed color depth. 
   * If 0 is returned, then the Oepng graphics configuration does not 
   * support indexed color.
   */
  virtual void getIndexedColor(int &bits) const;

  /**
   * Returns the color depth (red, green, blue, and alpha). 
   * If (red/green/blue/alpha)Bits are equal to 0, 
   * then the OpenGL graphics configuration does not support RGBA mode.
   */
  virtual void getRGBAColor(int &redBits, 
                    int &greenBits, 
                    int &blueBits, 
                    int &alphaBits) const;

  /**
   * 
   * Returns the floating point color depth (red, green, blue, and alpha). 
   * If (red/green/blue/alpha)Bits are equal to 0, 
   * then the OpenGL graphics configuration does not support floating point RGBA mode.
   */
  virtual void getFloatRGBAColor(int &redBits, 
                         int &greenBits, 
                         int &blueBits, 
                         int &alphaBits) const;

  /**
   * Returns the accumulation buffer depth (red, green, blue, and alpha). 
   * If (red/green/blue/alpha)Bits are equal to 0, 
   * then the OpenGL graphics configuration has no accumulation buffer.
   */
  virtual void getAccum(int &redBits, 
                int &greenBits,
                int &blueBits, 
                int &alphaBits) const;

  /**
   * Returns the stencil buffer depth. 
   * If 0 is returned, then the OpenGL graphics configuration has no stencil buffer.
   */
  virtual void getStencil(int &bits) const;

  /** 
   * Returns the availability of the hardware full-scene antialiasing feature.
   * @param bits returns the number of samples used in the antialiasing algorithm.
   */
  virtual SbBool getFullSceneAntialiasing(int &bits) const;

  /**
   * Returns the pixel format identifier.
   */
  virtual int getPixelFormat() const;

  /**
   * Returns the pixel format descriptor.
   */
  virtual const PIXELFORMATDESCRIPTOR *getPixelFormatDescriptor() const;

 SoINTERNAL public:

  // Prints the content of this graphics configuration to a file.
  virtual void print(FILE *fp) const;

  static SoGLGraphicConfig *getConfig(SoGLGraphicDevicePeer *device,
                                      int pixelFormat, SbBool forceComposition );

  virtual SbBool isValid() const;

 SoINTERNAL protected:

  SoWinGLGraphicConfig(SoGLGraphicDevicePeer *device, int pixelFormat = 0, SbBool forceComposition = FALSE);
  SoWinGLGraphicConfig(SoWinGLGraphicConfig &config);

 private:

  SbBool buildDescription();

  SoGLGraphicDevicePeer *m_device;
  int m_pixelFormat;
  PIXELFORMATDESCRIPTOR m_pfd;
  SbBool m_isValid;

  SbBool m_compositionForced;

  SbBool m_supportMultiSample;
  int m_numSamples;
};

#endif /* _SO_WIN_GL_GRAPHIC_CONFIG_H_ */

