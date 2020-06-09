/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_GL_GRAPHIC_CONFIG_COMPARE_H_
#define _SO_GL_GRAPHIC_CONFIG_COMPARE_H_

#include <Inventor/components/SoGraphicConfigCompare.h>

/**
 * @VSGEXT Defines an OpenGL graphics compare object used to compare two
 * SoGLGraphicConfig objects according to an SoGLGraphicConfigTemplate object.
 *
 * @ingroup General
 *
 * @DESCRIPTION
 * This class allows the comparison of two graphic configurations.
 * To sort the list of its supported graphic configurations, a graphics device
 * needs a predicate object of type SoGraphicConfigCompare class or
 * derived from this class.
 * It takes the  graphics template in parameter to define the right order.
 * This order should be absolute (non ambiguous).
 * SoGLGraphicDevice class uses SoGLGraphicConfigCompare to internally compare
 * SoGLGraphicConfig objects by default.
 *
 * @SEE_ALSO
 *    SoGraphicConfigTemplate, SoGLGraphicConfigTemplate,
 *    SoGraphicConfigCompare, SoGLGraphicConfigCompare,
 *    SoGraphicConfig, SoGraphicDevice, SoGLGraphicDevice.
 *
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 */
class INVENTOR_API SoGLGraphicConfigCompare : public SoGraphicConfigCompare {

 public:
  virtual ~SoGLGraphicConfigCompare() {}

  SoGLGraphicConfigCompare(const SoGraphicConfigTemplate *temp = NULL);

  virtual SbBool operator()(SoGraphicConfig * const&gc1,
                            SoGraphicConfig * const&gc2) const;
};

#endif /* _SO_GL_GRAPHIC_CONFIG_COMPARE_H_ */

