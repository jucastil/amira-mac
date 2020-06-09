/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_GL_GRAPHIC_DEVICE_PEER_H_
#define _SO_GL_GRAPHIC_DEVICE_PEER_H_

#include <Inventor/components/SoGLGraphicDevice.h>
#include <Inventor/components/SoGraphicConfig.h>
#include <Inventor/components/SoGLGraphicConfigTemplate.h>

#include <Inventor/STL/algorithm>
#include <Inventor/STL/functional>
#include <Inventor/STL/set>
#include <Inventor/STL/vector>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

typedef std::vector<SoGraphicConfig *> SoGraphicConfigList;
typedef std::set<int, std::less<int> > SoSamplesList;

/**
 * @VSGEXT Defines an OpenGL graphics device.
 * 
 * @ingroup General
 * 
 * @DESCRIPTION
 * This class is an abstraction of the internal part of a graphics device 
 * for OpenGL. It could be based on:
 *   - either an MS-Windows handler device context (HDC),
 *   - or X-windows graphics display (Display *),
 *   - or any other graphics device depending on the system (MacOS, etc.)
 *
 * This class declares or implements all required methods used in the
 * SoGLGraphicDevice class. This class is not inherited from SoGLGraphicDevice
 * but it is viewed and used as a peer in the OpenGL graphics device class.
 * 
 * @SEE_ALSO
 *    SoGraphicConfigTemplate, SoGLGraphicConfigTemplate, 
 *    SoGraphicConfigCompare, SoGLGraphicConfigCompare, 
 *    SoGraphicConfig, SoGraphicDevice, SoGLGraphicDevice.
 * 
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 */
SoINTERNAL class INVENTOR_API SoGLGraphicDevicePeer {

 public:

  /**
   * Destructor.
   */
  virtual ~SoGLGraphicDevicePeer();

  /**
   * Returns the list of all the graphics modes
   * supported by this OpenGL graphics device.
   */
  virtual SoGraphicConfigList &getGraphicConfigsList();

  /** 
   * Returns the list of all the available number of samples
   * supported by this OpenGL graphics device.
   */
  virtual SoSamplesList &getSamplesParseTab();

  /**
   * Returns the default template used by Open Inventor.
   */
  virtual SoGLGraphicConfigTemplate getDefaultGraphicConfigTemplate() = 0;

  /**
   * Returns a template according to the given graphics configuration.
   */
  virtual SoGLGraphicConfigTemplate getGraphicConfigTemplate(SoGLGraphicConfig *graphicConfig) = 0;

#if defined(_WIN32)
  /**
   * @WIN32_ONLY Returns the HDC corresponding to this graphics device. 
   */
  virtual HDC getHDC() = 0;
#elif defined(__APPLE__)
  /**
   * @MACOSX_ONLY Returns the window handle (WindowPtr).
   */
  virtual SbGlContextHelper::Display getDisplay() = 0;
#else
  /**
   *  @UNIX_ONLY Returns the Display * corresponding to this graphics device.
   */
  virtual Display *getDisplay() = 0;
#endif
  /**
   * Returns the type of device.
   */
  virtual SoGLGraphicDevice::DeviceType getType() = 0;


 protected:

  /**
   * Builds the whole OpenGL graphics configurations list.
   */
  virtual void buildGraphicConfigsList() = 0;

  /**
   * Deletes all the elements of the configurations list.
   */
  virtual void clearGraphicConfigsList() = 0;

  /**
   * The OpenGL graphics configurations list.
   */
  SoGraphicConfigList m_configs;

  /**
   * The OpenGL graphics samples list.
   */
  SoSamplesList m_samplesParseTab; // 255 multisample levels ...
};
#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _SO_GL_GRAPHIC_DEVICE_PEER_H_ */

