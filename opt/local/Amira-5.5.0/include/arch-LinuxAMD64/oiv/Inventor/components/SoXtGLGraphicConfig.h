/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_XT_GL_GRAPHIC_CONFIG_H_
#define _SO_XT_GL_GRAPHIC_CONFIG_H_

#include <Inventor/components/SoGLGraphicConfig.h>
#include <Inventor/components/SoGLGraphicDevice.h>
#include <Inventor/helpers/SbGlContextHelper.h>

class SoGLGraphicDevicePeer;

/**
 * @VSGEXT Represents an OpenGL graphics configuration for UNIX/Linux (Xt-based) 
 *  systems.
 * 
 * @ingroup General
 * 
 * @DESCRIPTION
 * 
 * This class is a representation of an XVisualInfo struct or a GLXFBConfig. Compared to
 * its parent class, this class adds a method to query the system-dependent
 * XVisualInfo or GLXFBConfig struct.
 * 
 * @SEE_ALSO
 *    SoGraphicConfigTemplate, SoGLGraphicConfigTemplate, 
 *    SoGraphicConfig, SoGraphicDevice, SoGLGraphicDevice.
 * 
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 */
class INVENTOR_API SoXtGLGraphicConfig : public SoGLGraphicConfig  {

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
   * If 0 is returned, then the OpenGL graphics configuration does not 
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
   * Returns the X visual information.
   */
  SbGlContextHelper::VisualInfo getXVisualInfo();

#ifndef __hpux
  /**
   * Returns the Frame Buffer Configuration.
   */
  GLXFBConfig *getFBConfig();
#endif

 SoINTERNAL public:

  // Prints the content of this graphics configuration to a file.
  virtual void print(FILE *fp) const;

  static SoGLGraphicConfig *getConfig(SoGLGraphicDevicePeer *device, SbGlContextHelper::VisualInfo visual);

#ifndef __hpux
  static SoGLGraphicConfig *getConfig(SoGLGraphicDevicePeer *device,
                                      GLXFBConfig *fbConfig);
#endif

  virtual SbBool isValid() const;

  static int getMaxFsaaSamples();

  virtual ~SoXtGLGraphicConfig();

 SoINTERNAL protected:

  SoXtGLGraphicConfig(SoGLGraphicDevicePeer *device, SbGlContextHelper::VisualInfo visual);
#ifndef __hpux
  SoXtGLGraphicConfig(SoGLGraphicDevicePeer *device, GLXFBConfig fbConfig);
#endif
  SoXtGLGraphicConfig(SoXtGLGraphicConfig &config);

 private:

  SbBool buildDescription();

  SbBool m_supportMultiSample;
  int m_numSamples;

  SoGLGraphicDevicePeer *m_device;
  SbGlContextHelper::VisualInfo m_visual;
#ifndef __hpux
  GLXFBConfig m_fbConfig;
#endif
  SbBool m_isValid;
  int m_bufferBits;
  int m_level;
  SbBool m_isIndexedColor;
  SbBool m_isDoubleBuffer;
  SbBool m_supportsStereo;
  int m_redBits, m_greenBits, m_blueBits, m_alphaBits;
  int m_auxBuffers;
  int m_depthBits;
  int m_stencilBits;
  int m_accumRedBits, m_accumGreenBits, m_accumBlueBits, m_accumAlphaBits;
};

#endif /* _SO_XT_GL_GRAPHIC_CONFIG_H_ */



