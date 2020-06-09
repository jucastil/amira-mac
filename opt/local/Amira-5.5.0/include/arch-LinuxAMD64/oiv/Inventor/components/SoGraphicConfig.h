/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_GRAPHIC_CONFIG_H_
#define _SO_GRAPHIC_CONFIG_H_

#include <stdio.h>
#include <Inventor/SbBasic.h>

/**
 * @VSGEXT Abstract base class for graphics configuration classes.
 *
 * @ingroup General
 *
 * @DESCRIPTION
 * This class is an abstraction of a graphics device configuration.
 *
 * @SEE_ALSO
 *    SoGLGraphicConfig, SoGLGraphicDevice, SoGraphicDevice
 *
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 */
class INVENTOR_API SoGraphicConfig {

 SoINTERNAL public:
  virtual ~SoGraphicConfig() {}

  /**
   * Prints the content of this graphics configuration to a file.
   */
  virtual void print(FILE *fp) const = 0;

  /**
   * Prints the content of this graphics configuration to stdout.
   */
  virtual void printInfo() const { print(stdout); };
};

#endif /* _SO_GRAPHIC_CONFIG_H_ */

