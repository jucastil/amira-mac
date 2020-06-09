/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G.TALLEC (May 2007)
**=======================================================================*/

#ifndef _SB_SPHERICALPROJECTION_
#define _SB_SPHERICALPROJECTION_

#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h>
#include <Inventor/projection/SbProjection.h>

class SoProjection;

/**
 * Spherical coordinate projection.
 * 
 * @ingroup Basics
 * 
 * @DESCRIPTION
 * 
 *  This class performs a spherical coordinate projection and is
 *  normally used with an SoProjection or SoGeoProjection node.
 *
 *  Spherical coordinates can be represented using the usual coordinate
 *  classes (SbVec3f, SoMFVec3f, etc) but the three values are considered to be
 *  - Longitude: an angle measured in degrees in the interval [-180,180]
 *  - Latitude: an angle measured in degrees in the interval [-90,90]
 *  - Altitude (or radius): a distance in 3D units greater than zero
 *  
 *  The parameters are :
 *
 *     @TABLE_1B
 *     @TR @B Name @b  @TD @B Type @b  @TD @B Index @b @TD @B Default @b
 *     @TR radius      @TD float       @TD 0           @TD 0
 *     @TR scaleRatio  @TD float       @TD 1           @TD 1
 *     @TABLE_END
 *
 *  The @I radius @i parameter is an offset added to each altitude value
 *  before projection.  This is useful when the altitude values are,
 *  for example, relative to sea level.
 *
 *  The @I scaleRatio @i parameter is a multiplicative ratio applied to
 *  altitude values before projection.  This is useful to exaggerate
 *  altitudes for visualization purposes.
 * 
 *  The spherical projection of a point P(lon,lat,alt) is computed as follows:
 *  @code 
 *    newLon = lon * degreeToRadians
 *    newLat = lat * degreeToRadians
 *    newRadius = radius + alt * scaleRatio
 *  
 *    x = newRadius*cos(newlat)*cos(newlon)
 *    y = newRadius*cos(newlat)*sin(newlon)
 *    z = newRadius*sin(newlat)
 *  @endcode
 *
 * @SEE_ALSO
 * 
 *  SbProjection,
 *  SoProjection
 *
 */

class INVENTOR_API SbSphericalProjection : public SbProjection
{
public:

  /**
   * Constructor
   */
  SbSphericalProjection();

  /**
   * Constructor
   */
  SbSphericalProjection(SoProjection* node);

  /**
   * Destructor
   */
  virtual ~SbSphericalProjection();

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

#endif // _SB_SPHERICALPROJECTION_
