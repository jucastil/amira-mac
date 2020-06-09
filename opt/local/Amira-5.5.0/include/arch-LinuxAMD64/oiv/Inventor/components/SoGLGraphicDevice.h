/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_GL_GRAPHIC_DEVICE_H_
#define _SO_GL_GRAPHIC_DEVICE_H_

#if defined(_WIN32) && !defined(__NUTC__)
#  include <windows.h> // for HDC def
#  ifdef _SO_QT_
#    include <wingdi.h>
#  else
#    include <Inventor/Win/SoWinDef.h>
#  endif
#else
#  include <Inventor/helpers/SbGlContextHelper.h>
#endif
#include <Inventor/sys/port.h>

#include <Inventor/components/SoGraphicDevice.h>
#include <Inventor/components/SoGraphicConfig.h>
#include <Inventor/components/SoGLGraphicConfig.h>
#include <Inventor/components/SoGraphicConfigTemplate.h>
#include <Inventor/components/SoGLGraphicConfigTemplate.h>

class SoGLGraphicDevicePeer;

/**
 * @VSGEXT Represents an OpenGL graphics device.
 * 
 * @ingroup General
 * 
 * @DESCRIPTION
 * This class is an encapsulation of a real graphics device for OpenGL. 
 * It could be:
 *   - a Microsoft Windows device context (HDC)
 *   - an X Windows graphics display (Display *)
 *
 * This class provides convenience methods to get the system-dependent
 * identifier, i.e., the HDC or the Display *.
 * It provides methods to query the supported OpenGL graphics 
 * configurations and to sort them according to the preferences specified
 * in a graphics template.
 * 
 * @SEE_ALSO
 *    SoGraphicConfigTemplate, SoGLGraphicConfigTemplate, 
 *    SoGraphicConfig, SoGraphicDevice, SoGLGraphicDevice.
 * 
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 */
class INVENTOR_API SoGLGraphicDevice : public SoGraphicDevice {

 public:

   /** Device types */
  enum DeviceType {
    /** Window */
    WINDOW = 0,
    /** PBuffer */
    PBUFFER,
    /** Bitmap */
    BITMAP
  };

#if defined(_WIN32)
  /**
   * @WIN32_ONLY Constructor.
   */
  SoGLGraphicDevice(HDC, DeviceType dt = SoGLGraphicDevice::WINDOW);
#elif defined(__APPLE__)
  /**
   * @MACOSX_ONLY Constructor.
   */
  SoGLGraphicDevice(SbGlContextHelper::Display, DeviceType dt = SoGLGraphicDevice::WINDOW);
#else
  /**
   * @UNIX_ONLY Constructor.
   */
  SoGLGraphicDevice(SbGlContextHelper::Display , DeviceType dt = SoGLGraphicDevice::WINDOW);
#endif
  /**
   * Destructor.
   */
  virtual ~SoGLGraphicDevice();

#if defined(_WIN32)
  /**
   * @WIN32_ONLY Allows you to cast HDC to SoGLGraphicDevice.
   */
  SoGLGraphicDevice &operator()(HDC);
#elif defined(__APPLE__)
  /**
   * @MACOSX_ONLY Allows you to cast WindowPtr to SoGLGraphicDevice.
   */
  SoGLGraphicDevice &operator()(SbGlContextHelper::Display);
#else
  /**
   * @UNIX_ONLY Allows you to cast Display * to SoGLGraphicDevice.
   */
  SoGLGraphicDevice &operator()(SbGlContextHelper::Display);
#endif
  /**
   * Returns the best graphics configuration corresponding to the
   * preferences in the specified template.
   */
  SoGraphicConfig *getBestGraphicConfig(const SoGraphicConfigTemplate &temp);

  /**
   * Returns the best graphics configuration corresponding to a graphics
   * template containing the default preferences (see SoGLGraphicConfigTemplate).
   */
  SoGraphicConfig *getDefaultGraphicConfig();

#ifdef OIV_NET_DOC
  /**
  * Returns a template corresponding to the given graphics
  * configuration.
  * 
  * The returned template, if passed to
  * SoGLGraphicDevice.GetBestGraphicConfig, would return the
  * originally specified (or a functionally equivalent) graphicConfig
  * as the best graphic configuration.
  *  
  */
#else
  /**
  * Returns a template corresponding to the given graphics
  * configuration.
  * 
  * The returned template, if passed to
  * SoGLGraphicDevice::getBestGraphicConfig, would return the
  * originally specified (or a functionally equivalent) graphicConfig
  * as the best graphic configuration.
  *
  * For example, if graphicConfig supports an accumulation buffer and
  * its R/G/B/A sizes are respectively 24,24,24,16, then the returned
  * template is set as if you had called:
  * <PRE> 
  *   temp.setAccum(SoGraphicConfigTemplate::REQUIRED, 24, 24, 24, 16, 24, 24, 24, 16); </PRE>
  * 
  * If graphicConfig does not support an accumulation buffer, then
  * the returned template is set as if you had called:
  * <PRE> 
  *   temp.setAccum(SoGraphicConfigTemplate::REQUIRED, 0, 0, 0, 0, 0, 0, 0, 0);  </PRE>
  *
  * It is not guaranteed that the template returned by this method
  * will select @I exactly @i the same graphics configuration as was
  * passed to this method. However, it will select a graphics
  * configuration with the same OpenGL capabilities and values.
  */

#endif //OIV_NET_DOC
  SoGLGraphicConfigTemplate getGraphicConfigTemplate(SoGLGraphicConfig *graphicConfig);

  /**
   * Returns the number of the graphics configurations supported
   * by this device.
   */
  size_t getNum();

  /**
   * Returns the n-th of all the graphics configurations supported
   * by this device.
   */
  SoGraphicConfig *getGraphicConfig(size_t n);

  /**
   * Returns the number of the graphics configurations supported
   * by this device and the given template.
   */
  size_t getNum(const SoGraphicConfigTemplate &temp);

  /**
   * Returns the best nth of all the graphics configurations supported
   * by this device and sorted according to the given template.
   */
  SoGraphicConfig *getGraphicConfig(const SoGraphicConfigTemplate &temp, size_t n);

  /**
   * @WIN32_ONLY Returns the HDC corresponding to this graphics device. 
   */
  HDC getHDC();

  /**
   *  @UNIX_ONLY Returns the Display * corresponding to this graphics device.
   */
#if defined(__APPLE__)
  SbGlContextHelper::Display getDisplay();
#elif !defined(_WIN32)
  SbGlContextHelper::Display getDisplay();
#else
  UINT *getDisplay();
#endif

SoINTERNAL public:
  
  size_t getNumSamplesAvailable();
  /**
   * Returns the n-th of the number sample list.
   */
  int getNumSamples(size_t n);
  int findSampleIndex(int findInt);

 private:

  SoGLGraphicDevicePeer *m_devicePeer;
  void *m_sortedGraphicConfigs;
  SoGLGraphicConfigTemplate m_template;
};

#endif /* _SO_GL_GRAPHIC_DEVICE_H_ */

