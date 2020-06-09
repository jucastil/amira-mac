/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_GRAPHIC_CONFIG_TEMPLATE_H_
#define _SO_GRAPHIC_CONFIG_TEMPLATE_H_

#include <limits.h>
#include <Inventor/components/SoGraphicConfig.h>

/**
 * @VSGEXT Abstract base class for graphics configuration template classes.
 *
 * @ingroup General
 *
 * @DESCRIPTION
 * This abstract class allows you to specify a set of graphics preferences.
 * It can be used to choose a particular configuration of a graphics device.
 * A graphics configuration matches this template only if
 *   - all REQUIRED fields are "active"
 *   - all FORBIDDEN fields are "inactive"
 *
 * @SEE_ALSO
 *    SoGraphicConfigTemplate, SoGLGraphicConfigTemplate,
 *    SoGraphicConfig, SoGLGraphicConfig, SoGLGraphicDevice.
 *
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 */
class INVENTOR_API SoGraphicConfigTemplate
{

 public:

  /**
   * Constructor.
   */
  SoGraphicConfigTemplate();

  /**
   * Destructor.
   */
  virtual ~SoGraphicConfigTemplate() {}

  /**
   * Priority requirement
   */
  enum Preference {
    /**
     * Means crucial and absolutely required.
     */
    REQUIRED = INT_MAX,
    /**
     * Means "better if available" but not crucial. Any other positive int value
     * correspond to a priority level (the max priority correspond to REQUIRED).
     */
    PREFERRED = 16,
    /**
     * Means absolutely forbidden.
     */
    FORBIDDEN = 0
  };

  /**
   * Indicates if the graphics configuration graphicConfig fits this template.
   * Returns TRUE if all REQUIRED fields in the template are active
   * in graphicConfig and if all FORBIDDEN fields in the template are
   * inactive in graphicConfig.
   */
  virtual SbBool isGraphicsConfigSupported(SoGraphicConfig &graphicConfig) const = 0;

};

#endif /* _SO_GRAPHIC_CONFIG_TEMPLATE_H_ */

