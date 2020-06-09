/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_XT_GL_GRAPHIC_DEVICE_H_
#define _SO_XT_GL_GRAPHIC_DEVICE_H_

#include <Inventor/components/SoGLGraphicDevicePeer.h>

/**
 * @VSGEXT Represents the internal part of an OpenGL graphics device 
 * on UNIX systems (Xt-based systems).
 * 
 * @ingroup General
 * 
 * @DESCRIPTION
 * This class represents a X-windows graphics display (Display *).
 * It is used as an internal part of a graphics device for OpenGL.
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
SoINTERNAL class INVENTOR_API SoXtGLGraphicDevice : public SoGLGraphicDevicePeer {

 public:

  /**
   * Constructor.
   */
  SoXtGLGraphicDevice(Display *, SoGLGraphicDevice::DeviceType dt = SoGLGraphicDevice::WINDOW);

  /**
   * Destructor.
   */
  ~SoXtGLGraphicDevice();

  /**
   * Returns a template corresponding to the given graphics configuration.
   */
  SoGLGraphicConfigTemplate getGraphicConfigTemplate(SoGLGraphicConfig *graphicConfig);

#if defined(_WIN32)
  /**
   * Returns the internal HDC value.
   */
  HDC getHDC();
#elif defined(__APPLE__)
  /**
   * Returns the window handle (WindowPtr).
   */
  WindowPtr getWindowPtr();
#else
  /**
   * Returns the internal display.
   */
  Display *getDisplay();
#endif
  /**
   * Returns the default template used by Inventor.
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
   * Build the whole OpenGL graphics configs list.
   */
  virtual void buildGraphicConfigsList();

  /**
   * Deletes all the elements of the configs list.
   */
  virtual void clearGraphicConfigsList();

 private:

  Display *m_display;  
  SoGLGraphicDevice::DeviceType m_deviceType;

};

#endif /* _SO_XT_GL_GRAPHIC_DEVICE_H_ */

