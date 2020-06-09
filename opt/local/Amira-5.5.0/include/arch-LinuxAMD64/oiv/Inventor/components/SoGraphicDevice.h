/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_GRAPHIC_DEVICE_H_
#define _SO_GRAPHIC_DEVICE_H_

#include <Inventor/components/SoGraphicConfigTemplate.h>
#include <Inventor/components/SoGraphicConfig.h>

#include <Inventor/components/SoGraphicConfig.h>

/**
 * @VSGEXT Abstract base class for graphics device classes.
 *
 * @ingroup General
 *
 * @DESCRIPTION
 * This class is an abstraction of a graphics device, e.g.,
 * a printer, a graphics window, or an offscreen buffer.
 * It provides methods to query the supported graphics
 * configurations and to sort them according to a graphics template.
 *
 * @SEE_ALSO
 *    SoGraphicConfigTemplate, SoGLGraphicConfigTemplate,
 *    SoGraphicConfigCompare, SoGLGraphicConfigCompare,
 *    SoGraphicConfig, SoGLGraphicConfig, SoGLGraphicDevice.
 *
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 */
class INVENTOR_API SoGraphicDevice {

 public:

  /**
   * Destructor
   */
  virtual ~SoGraphicDevice() {}

  /**
   * Returns the best graphics configuration according to the
   * user's specifications.
   *
   * The method used to choose the "best" graphics configuration is very simple:
   * It selects a list of supported graphics configurations according to the
   * user's specifications given by graphicConfigTemplate
   * (see SoGraphicConfigTemplate::isGraphicsConfigSupported).
   * The chosen graphics configuration is the graphics configuration of this list that has
   * the maximum sum of the weight values of the PREFERRED available fields.
   */
  virtual SoGraphicConfig *getBestGraphicConfig(const SoGraphicConfigTemplate &temp) = 0;

  /**
   * Returns the number of the graphics configurations supported
   * by this device.
   */
  virtual size_t getNum() = 0;

  /**
   * Returns the n-th of all the graphics configurations supported
   * by this device.
   */
  virtual SoGraphicConfig *getGraphicConfig(size_t n) = 0;

  /**
   * Returns the number of the graphics configurations supported
   * by this device and the given template.
   */
  virtual size_t getNum(const SoGraphicConfigTemplate &temp) = 0;

  /**
   * Returns the best nth of all the graphics configurations supported
   * by this device and sorted according to the given template.
   */
  virtual SoGraphicConfig *getGraphicConfig(const SoGraphicConfigTemplate &temp, size_t n) = 0;

  /**
   * Returns the default graphics configuration.
   */
  virtual SoGraphicConfig *getDefaultGraphicConfig() = 0;
};

#endif /* _SO_GRAPHIC_DEVICE_H_ */

