/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_GL_GRAPHIC_CONFIG_TEMPLATE_H_
#define _SO_GL_GRAPHIC_CONFIG_TEMPLATE_H_

#include <Inventor/components/SoGraphicConfigTemplate.h>

class SoGLGraphicConfigTemplateSync;

/**
 * @VSGEXT Defines an OpenGL graphics configuration template.
 * 
 * @ingroup General
 * 
 * @DESCRIPTION
 * An OpenGL graphics configuration template is a set of graphics 
 * preferences used to choose the best OpenGL graphics configuration
 * (SoGLGraphicConfig) available on an OpenGL graphics device 
 * (SoGLGraphicDevice).
 *
 * There are many different criteria: double/single buffer, 
 * raw stereo, OpenGL acceleration, overlays, Z-buffer depth size, 
 * RGBA/indexed colors and size, accumulation buffer and size, stencil
 * buffer and size, etc. 
 * Every criterion is required, or forbidden, or preferred. 
 * The preferred criterion can be extended to an integer weight:
 * SoGraphicConfigTemplate::PREFERRED (equal to 1), 2, 3, 4, 10, 100, 
 * 1000, and so forth.
 * The sum of all weights determines if one graphics configuration is 
 * better than another.
 * 
 * The default values are: 
 * - Double buffer is REQUIRED;
 * - Stereo buffer is FORBIDDEN;
 * - Accelerated OpenGL is REQUIRED;
 * - Depth buffer is REQUIRED; its size is greater than 0;
 * - Non-indexed color is REQUIRED; its R/G/B/A sizes are greater than 0;
 * - Indexed color is FORBIDDEN;
 * - Accumulation buffer is PREFERRED (weight 1); its R/G/B/A sizes are greater than 0;
 * - Stencil buffer is PREFERRED(weight 1); its size is greater than 0;
 * - Overlays are PREFERRED(weight 1).
 * - Full-scene antialiasing is FORBIDDEN.
 * 
 * @SEE_ALSO
 *    SoGraphicConfigTemplate, SoGLGraphicConfigTemplate, 
 *    SoGraphicConfigCompare, SoGLGraphicConfigCompare, 
 *    SoGraphicConfig, SoGLGraphicConfig, SoGLGraphicDevice, SoFullSceneAntialiasing.
 * 
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 */
class INVENTOR_API SoGLGraphicConfigTemplate : public SoGraphicConfigTemplate {

 public:

  /**
   * Constructor.
   */
  SoGLGraphicConfigTemplate();

  /**
   * Destructor.
   */
  virtual ~SoGLGraphicConfigTemplate();

  /**
   * Indicates if the graphics configuration graphicConfig fits this template.
   * Returns TRUE if all REQUIRED fields in the template are active
   * in graphicConfig and if all FORBIDDEN fields in the template are 
   * inactive in graphicConfig.
   */
  virtual SbBool isGraphicsConfigSupported(SoGraphicConfig &graphicConfig) const;

  /**
   * Sets the double buffer mode preference.
   */
  void setDoubleBuffer(SoGraphicConfigTemplate::Preference pref);

  /**
   * Returns the double buffer mode preference. 
   */
  SoGraphicConfigTemplate::Preference getDoubleBuffer() const;

  /**
   * Sets the stereo buffer mode preference.
   */
  void setStereoBuffer(SoGraphicConfigTemplate::Preference pref);

  /**
   * Returns the stereo buffer preference. 
   */
  SoGraphicConfigTemplate::Preference getStereoBuffer() const;

  /**
   * Sets the graphics acceleration preference.
   */
  void setAccelerated(SoGraphicConfigTemplate::Preference pref);

  /**
   * Returns the graphics acceleration preference.
   */
  SoGraphicConfigTemplate::Preference getAccelerated() const;

  /**
   * Sets the overlays preference.
   */
  void setOverlays(SoGraphicConfigTemplate::Preference pref);

  /**
   * Returns the overlay preference.
   */
  SoGraphicConfigTemplate::Preference getOverlays() const;

  /**
   * Sets the depth buffer preferences. @BR
   * minBits and maxBits are the minimum and maximum required sizes.
   * The required size must be greater than or equal to minBits, and less 
   * than or equal to maxBits. The maximum size is always preferred. 
   * If pref is FORBIDDEN, the min/max values are ignored.
   */
  void setDepth(SoGraphicConfigTemplate::Preference pref, 
                int minBits = 0,
                int maxBits = INT_MAX);

  /**
   * Returns the depth buffer preference and sizes.
   * [OIVJAVA-WRAPPER PACK{DepthBufferInfo}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE NAME{priority}]
   */
  SoGraphicConfigTemplate::Preference getDepth(int &minBits,
                                               int &maxBits) const;

  /**
   * Sets the indexed color preferences.@BR
   * REQUIRED means indexed color mode and FORBIDDEN means RGBA or floating point RGBA mode.
   * minBits and maxBits are the minimum and maximum required size.
   * The required size must be greater than or equal to minBits, and less than 
   * or equal to maxBits. The maximum size is always preferred. 
   * If pref is FORBIDDEN, the min/max values are ignored.
   */
  void setIndexedColor(SoGraphicConfigTemplate::Preference pref,
                       int minBits = 0,
                       int maxBits = INT_MAX);

  /**
   * Returns the indexed color mode and sizes.
   * [OIVJAVA-WRAPPER PACK{IndexedColorInfo}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE NAME{priority}]
   */
  SoGraphicConfigTemplate::Preference getIndexedColor(int &minBits,
                                                      int &maxBits) const;

  /**
   * 
   * Returns TRUE if floating point RGBA is used.
   */
  SbBool isFloatRGBAColor() const;

  /**
   * Sets the color preferences.@BR
   * REQUIRED means RGBA mode and FORBIDDEN means indexed color mode.
   * min(red/green/blue/alpha)Bits and max(red/green/blue/alpha)Bits 
   * are the minimum and maximum required sizes.
   * The required size must be greater than or equal to the 
   * min(red/green/blue/alpha)Bits, and less than or equal to 
   * max(red/green/blue/alpha)Bits. The maximum size is always preferred. 
   * If pref is FORBIDDEN, the min/max values are ignored.
   */
  void setRGBAColor(SoGraphicConfigTemplate::Preference pref,
                    int minRedBits = 0, 
                    int minGreenBits = 0, 
                    int minBlueBits = 0, 
                    int minAlphaBits = 0,
                    int maxRedBits = INT_MAX, 
                    int maxGreenBits = INT_MAX, 
                    int maxBlueBits = INT_MAX, 
                    int maxAlphaBits = INT_MAX);

  /**
   * Returns the color preferences.
   * [OIVJAVA-WRAPPER PACK{ColorInfo}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE NAME{priority}]
   */
  SoGraphicConfigTemplate::Preference getRGBAColor(int &minRedBits, 
                                                   int &minGreenBits, 
                                                   int &minBlueBits, 
                                                   int &minAlphaBits,
                                                   int &maxRedBits, 
                                                   int &maxGreenBits, 
                                                   int &maxBlueBits, 
                                                   int &maxAlphaBits) const;


  /**
   * Sets the float color preferences.@BR
   * REQUIRED means RGBA mode and FORBIDDEN means indexed color mode.
   * min(red/green/blue/alpha)Bits and max(red/green/blue/alpha)Bits 
   * are the minimum and maximum required sizes.
   * The required size must be greater than or equal to the 
   * min(red/green/blue/alpha)Bits, and less than or equal to 
   * max(red/green/blue/alpha)Bits. The maximum size is always preferred. 
   * If pref is FORBIDDEN, the min/max values are ignored.
   */
  void setFloatRGBAColor(SoGraphicConfigTemplate::Preference pref,
                         int minFloatRedBits   = 15, 
                         int minFloatGreenBits = 15, 
                         int minFloatBlueBits  = 15, 
                         int minFloatAlphaBits = 15,
                         int maxFloatRedBits   = 16, 
                         int maxFloatGreenBits = 16,
                         int maxFloatBlueBits  = 16, 
                         int maxFloatAlphaBits = 16);
  /**
   * Returns the float color preferences.
   * [OIVJAVA-WRAPPER PACK{FloatRGBAColorInfo}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE NAME{priority}]
   */
  SoGraphicConfigTemplate::Preference getFloatRGBAColor(int &minFloatRedBits, 
                                                        int &minFloatGreenBits, 
                                                        int &minFloatBlueBits, 
                                                        int &minFloatAlphaBits,
                                                        int &maxFloatRedBits, 
                                                        int &maxFloatGreenBits, 
                                                        int &maxFloatBlueBits, 
                                                        int &maxFloatAlphaBits) const;


  /**
   * Sets the accumulation preferences.@BR 
   * min(red/green/blue/alpha)Bits and max(red/green/blue/alpha)Bits 
   * are the minimum and maximum required sizes.
   * The required size must be greater than or equal to
   * min(red/green/blue/alpha)Bits, and less than or equal to  
   * max(red/green/blue/alpha)Bits. The maximum size is always preferred. 
   * If pref is FORBIDDEN, the min/max values are ignored.
   */
  void setAccum(SoGraphicConfigTemplate::Preference pref,
                int minRedBits = 0, 
                int minGreenBits = 0, 
                int minBlueBits = 0, 
                int minAlphaBits = 0,
                int maxRedBits = INT_MAX, 
                int maxGreenBits = INT_MAX, 
                int maxBlueBits = INT_MAX, 
                int maxAlphaBits = INT_MAX);

  /**
   * Returns the accumulation buffer preferences.
   * [OIVJAVA-WRAPPER PACK{AccBufferInfo}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE NAME{priority}]
   */
  SoGraphicConfigTemplate::Preference getAccum(int &minRedBits, 
                                               int &minGreenBits, 
                                               int &minBlueBits, 
                                               int &minAlphaBits,
                                               int &maxRedBits, 
                                               int &maxGreenBits, 
                                               int &maxBlueBits, 
                                               int &maxAlphaBits) const;

  /**
   * Sets the stencil preferences.@BR
   * REQUIRED means indexed color mode and FORBIDDEN means RGBA mode.
   * minBits and maxBits are the minimum and maximum required size.
   * The required size must be greater than or equal to minBits, and less 
   * than or equal to maxBits. The maximum size is always preferred. 
   * If pref is FORBIDDEN, the minBits and maxBits values are ignored.
   */
  void setStencil(SoGraphicConfigTemplate::Preference pref,
                  int minBits = 0,
                  int maxBits = INT_MAX);

  /**
   * Returns the stencil preferences.
   * [OIVJAVA-WRAPPER PACK{StencilInfo}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE NAME{priority}]
   */
  SoGraphicConfigTemplate::Preference getStencil(int &minBits,
                                                 int &maxBits) const;

  /** 
   * Sets the full-scene antialiasing preferences. @BR
   * Full-scene anti-aliasing by supersampling usually means that each full frame
   * is rendered at double (2x), quadruple (4x), ...,  the display resolution, and then down-sampled to match
   * the display resolution. So a 2x FSAA would render four supersampled pixels for each single pixel of each frame.
   * minFsaaBits and maxFsaaBits are integer values specifying the minimum and maximum required number of samples
   * to use during antialiasing computation.
   * The required number of samples must be greater than or equal to minFsaaBits, and less 
   * than or equal to maxFsaaBits. The maximum number of samples is always preferred.
   * If pref is FORBIDDEN, the min/max values are ignored.
   */
  void setFullSceneAntialiasing( SoGraphicConfigTemplate::Preference pref,
                                 int minFsaaBits = 0,
                                 int maxFsaaBits = INT_MAX );

  /** 
   * Returns the full-scene antialiasing preference and number of samples.
   * [OIVJAVA-WRAPPER PACK{AntialiasingInfo}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE NAME{priority}]
   */
  SoGraphicConfigTemplate::Preference getFullSceneAntialiasing( int &minFsaaBits,
                                                                int &maxFsaaBits) const;

SoINTERNAL public:

  SoGLGraphicConfigTemplateSync* getSynchronizer() const;
  void setSynchronizer( SoGLGraphicConfigTemplateSync* );

  SoGLGraphicConfigTemplate( const SoGLGraphicConfigTemplate& );

  /**
   * Assignment operators for character string, SbString.
   */
  SoGLGraphicConfigTemplate &operator =(const SoGLGraphicConfigTemplate &gc);

 private:
  SoGLGraphicConfigTemplateSync* m_synchronizer;
};

// INLINE METHODS
inline SoGLGraphicConfigTemplateSync*
SoGLGraphicConfigTemplate::getSynchronizer() const
{
  return m_synchronizer;
}

#endif /* _SO_GL_GRAPHIC_CONFIG_TEMPLATE_H_ */

