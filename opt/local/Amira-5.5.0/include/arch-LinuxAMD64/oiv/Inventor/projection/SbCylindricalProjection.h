/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : M.Heck (March 2011)
**=======================================================================*/

#ifndef _SB_CYLINDRICALPROJECTION_
#define _SB_CYLINDRICALPROJECTION_

#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h>
#include <Inventor/projection/SbProjection.h>

/**
 * Cylindrical coordinate projection.
 * 
 * @ingroup Basics
 * 
 * @DESCRIPTION
 * 
 *  This class performs a cylindrical coordinate projection. 
 *
 *  Cylindrical coordinates are: radius, theta (angle), height @BR
 *  Radius and height are 3D units and theta is in radians.
 *
 *  The projection of cylindrical coordinates into XYZ space is:
 *    x = r * cos(theta)
 *    y = r * sin(theta)
 *    z = h
 *
 * @SEE_ALSO
 * 
 *  SbProjection,
 *  SoProjection
 *
 */

class INVENTOR_API SbCylindricalProjection : public SbProjection
{
public:
 
  /**
   * Constructor
   */
  SbCylindricalProjection();

  /**
   * Constructor
   */
  SbCylindricalProjection(SoProjection* node);

  /**
   * Destructor
   */
  virtual ~SbCylindricalProjection();

  /**
   * @copydoc SbProjection::inverse
   */
  virtual void inverse( SbVec3f &point );

  /**
   * Compute projected bounding box
   */
  virtual bool getProjectedBoundingBox( SbBox3f& bbox );

SoEXTENDER_Documented protected:
  /**
  * @copydoc SbProjection::apply
  */
  virtual void apply( SbVec3f &point );
};

#endif // _SB_CYLINDRICALPROJECTION_
