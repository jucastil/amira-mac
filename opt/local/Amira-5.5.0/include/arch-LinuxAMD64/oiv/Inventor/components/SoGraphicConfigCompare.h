/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_GRAPHIC_CONFIG_COMPARE_H_
#define _SO_GRAPHIC_CONFIG_COMPARE_H_

#include <Inventor/components/SoGraphicConfigTemplate.h>
#include <Inventor/components/SoGraphicConfig.h>

/**
 * @VSGEXT Defines an graphics compare object used to compare two
 * SoGraphicConfig objects according to an SoGraphicConfigTemplate object.
 *
 * @ingroup General
 *
 * @DESCRIPTION
 * This class allows the comparison of two graphics configurations.
 * To sort the list of its supported graphics configurations, a graphics device
 * need a predicate object which type is SoGraphicConfigCompare class or
 * derived from.
 * It takes the  graphics template in parameter to define the right order.
 * This order should be absolute (non ambiguous).
 *
 * @SEE_ALSO
 *    SoGraphicConfigTemplate, SoGLGraphicConfigTemplate,
 *    SoGraphicConfigCompare, SoGLGraphicConfigCompare,
 *    SoGraphicConfig, SoGraphicDevice, SoGLGraphicDevice.
 *
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 */
class INVENTOR_API SoGraphicConfigCompare {

 public:
  virtual ~SoGraphicConfigCompare() {}

  SoGraphicConfigCompare(const SoGraphicConfigTemplate *temp = NULL);

  virtual SbBool operator()(SoGraphicConfig* const&gc1,
                            SoGraphicConfig* const&gc2) const = 0;

  const SoGraphicConfigTemplate *m_predicateTemplate;
};

#endif /* _SO_GRAPHIC_CONFIG_COMPARE_H_ */

