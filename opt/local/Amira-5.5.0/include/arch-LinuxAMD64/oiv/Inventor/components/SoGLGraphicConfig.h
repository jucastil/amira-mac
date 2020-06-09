/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_GL_GRAPHIC_CONFIG_H_
#define _SO_GL_GRAPHIC_CONFIG_H_

#include <Inventor/components/SoGraphicConfig.h>

#include <Inventor/devices/SoGLFormat.h>

/**
 * @VSGEXT Defines an OpenGL graphics configuration.
 * 
 * @ingroup General
 * 
 * @DESCRIPTION
 * This class is an abstraction of an OpenGL graphics configuration (analogous
 * to a pixel format on Microsoft Windows or a visual on X).
 * It provides methods to inquire what the OpenGL graphics configuration
 * supports: double/single buffer, raw stereo, OpenGL acceleration, overlays,
 * Z-buffer depth size, RGBA/indexed colors and size, accumulation buffer and
 * size, stencil buffer and size, etc. 
 * 
 * @SEE_ALSO
 *    SoGraphicConfigTemplate, SoGLGraphicConfigTemplate, 
 *    SoGraphicConfig, SoGraphicDevice, SoGLGraphicDevice.
 * 
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 */
class INVENTOR_API SoGLGraphicConfig : public SoGraphicConfig {

 public:

  /**
   * Returns TRUE if double-buffer mode is enabled, 
   * else FALSE (single-buffer mode). 
   */
  virtual SbBool isDoubleBuffer() const = 0;

  /**
   * Returns TRUE if stereo buffer mode is supported.
   */
  virtual SbBool isStereoBuffer() const = 0;

  /**
   * Returns TRUE if the OpenGL graphics configuration is accelerated.
   */
  virtual SbBool isAccelerated() const = 0;

  /**
   * Returns TRUE if the OpenGL graphics configuration has overlays 
   * supported by Open Inventor.
   */
  virtual SbBool hasOverlays() const = 0;

  /**
   * Returns the Z-buffer depth. 
   * If 0 is returned, then there is no Z-buffer.
   */
  virtual void getDepth(int &bits) const = 0;

  /**
   * Returns the indexed color depth. 
   * If 0 is returned, then the OpenGL graphics configuration does not 
   * support indexed color.
   */
  virtual void getIndexedColor(int &bits) const = 0;

  /**
   * Returns the color depth (red, green, blue, and alpha). 
   * If (red/green/blue/alpha)Bits are equal to 0, 
   * then the OpenGL graphics configuration does not support RGBA mode.
   */
  virtual void getRGBAColor(int &redBits, 
                            int &greenBits, 
                            int &blueBits, 
                            int &alphaBits) const = 0;

  /**
   * 
   * Returns the floating point color depth (red, green, blue, and alpha). 
   * If (red/green/blue/alpha)Bits are equal to 0, 
   * then the OpenGL graphics configuration does not support floating point RGBA mode.
   */
  virtual void getFloatRGBAColor(int &redBits, 
                                 int &greenBits, 
                                 int &blueBits, 
                                 int &alphaBits) const = 0;

  /**
   * Returns the accumulation buffer depth (red, green, blue, and alpha). 
   * If (red/green/blue/alpha)Bits are equal to 0, 
   * then the OpenGL graphics configuration has no accumulation buffer.
   */
  virtual void getAccum(int &redBits, 
                        int &greenBits,
                        int &blueBits, 
                        int &alphaBits) const = 0;

  /**
   * Returns the stencil buffer depth. 
   * If 0 is returned, then the OpenGL graphics configuration has no stencil buffer.
   */
  virtual void getStencil(int &bits) const = 0;

  /**
   * [OIVJAVA-WRAPPER-RETURN-TYPE SUCCESS_FLAG{throw new IllegalArgumentException()}]
   */
  virtual SbBool getFullSceneAntialiasing(int &bits) const = 0;

 SoINTERNAL public:

  virtual ~SoGLGraphicConfig() {}

  virtual SbBool isValid() const
  { return FALSE; }

  /**
   * Prints the content of this graphics configuration to a file.
   */
  virtual void print(FILE *fp) const = 0;

  const SoGLFormat& getGLFormat() const;

protected:
  
  void setGLFormat( const SoGLFormat& format );

private:
  SoGLFormat m_format;
};


//----------------------------------------------------------------------
inline const SoGLFormat&
SoGLGraphicConfig::getGLFormat() const
{
  return m_format; 
}


//----------------------------------------------------------------------
inline void 
SoGLGraphicConfig::setGLFormat( const SoGLFormat& format )
{ 
  m_format = format; 
}


//----------------------------------------------------------------------

#endif /* _SO_GL_GRAPHIC_CONFIG_H_ */
