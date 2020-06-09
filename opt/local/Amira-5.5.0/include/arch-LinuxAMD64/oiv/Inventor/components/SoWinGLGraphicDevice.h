/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_WIN_GL_GRAPHIC_DEVICE_H_
#define _SO_WIN_GL_GRAPHIC_DEVICE_H_

#include <Inventor/components/SoGLGraphicDevicePeer.h>

/**
 * @VSGEXT Represents the internal part of an OpenGL graphics device 
 * on Windows systems.
 * 
 * @ingroup General
 * 
 * @DESCRIPTION
 * This class represents a _WIN32 handler device context (HDC).
 * It is used as internal part of a graphics device for OpenGL.
 * This class declares or implements all required methods used in the
 * SoGLGraphicDevice class. This class is inherited from SoGLGraphicDevicePeer
 * which is viewed and used as a peer in the OpenGL graphics device class.
 * 
 * @SEE_ALSO
 *    SoGraphicConfigTemplate, SoGLGraphicConfigTemplate, 
 *    SoGraphicConfigCompare, SoGLGraphicConfigCompare, 
 *    SoGraphicConfig, SoGraphicDevice, SoGLGraphicDevice.
 * 
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 */
SoINTERNAL class INVENTOR_API SoWinGLGraphicDevice : public SoGLGraphicDevicePeer {

 public:

  /**
   * Constructor.
   */
   SoWinGLGraphicDevice(HDC hdc, SoGLGraphicDevice::DeviceType dt);

  /**
   * Destructor.
   */
  ~SoWinGLGraphicDevice();

  /**
   * Returns a template corresponding to the given graphics configuration.
   */
  SoGLGraphicConfigTemplate getGraphicConfigTemplate(SoGLGraphicConfig *graphicConfig);

  /**
   * Returns the internal HDC value.
   */
  HDC getHDC();

  /**
   * Returns the window handle (WindowPtr).
   */
  WindowPtr getWindowPtr();

  /**
   *  Returns the internal Display * value.
   */
  UINT *getDisplay();

  /**
   * Returns the default template used by Open Inventor.
   * The template depends on the following environment variables:
   *   - OIV_COMPAT_24, 
   *   - OIV_REQUIRE_STENCIL, 
   *   - OIV_NO_OVERLAYS, 
   *   - OIV_FORCE_PIXEL_FORMAT.
   */
  SoGLGraphicConfigTemplate getDefaultGraphicConfigTemplate();

  /**
   * Returns the type of device.
   */
  SoGLGraphicDevice::DeviceType getType() {return m_deviceType;};

 SoINTERNAL public:

  SoGLGraphicConfigTemplate getDefaultGraphicConfigTemplate(SbBool, SbBool, SbBool, SbBool, SbBool);

 protected:

  /**
   * Build the whole OpenGL graphic configs list.
   */
   virtual void buildGraphicConfigsList();

  /**
   * Deletes all the elements of the configs list.
   */
  virtual void clearGraphicConfigsList();

 private:

  HDC m_hdc;
  SoGLGraphicDevice::DeviceType m_deviceType;
  SbBool m_forceComposition;
};

#endif /* _SO_WIN_GL_GRAPHIC_DEVICE_H_ */

