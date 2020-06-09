/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Howard Look (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SB_SPHERE_PROJECTOR_
#define _SB_SPHERE_PROJECTOR_

#include <Inventor/projectors/SbProjector.h>

/**
 * Sphere projector.
 * 
 * @ingroup Projectors
 * 
 * @DESCRIPTION
 *   SbSphereProjector is an abstract base class for projectors that use a sphere in
 *   their projection. Sphere projectors are typically used to write interactive 3D
 *   manipulators and viewers.
 * 
 * @SEE_ALSO
 *    SbCylinderProjector,
 *    SbCylinderPlaneProjector,
 *    SbCylinderSectionProjector,
 *    SbCylinderSheetProjector,
 *    SbLineProjector,
 *    SbPlaneProjector,
 *    SbSpherePlaneProjector,
 *    SbSphereSectionProjector,
 *    SbSphereSheetProjector
 * 
 * 
 */ 

class INVENTOR_API SbSphereProjector : public SbProjector
{
 public:

  /**
   * Applies the projector using the given point, returning the
   * point in three dimensions that it projects to.
   * The point should be normalized from 0-1, with (0,0) at the lower-left.
   */
  virtual SbVec3f     project(const SbVec2f &point) = 0;
  /**
   * Applies the projector using the given line in world coordinates,
   * returning the point in three dimensions that it projects to.
   * New for v3.0.
   */
  virtual SbVec3f intersect( const SbLine &line ) = 0;

  /**
   * Applies the projector using the given point, returning the point in three
   * dimensions that it projects to. This also returns in @B rot @b a rotation on
   * the surface of the sphere from the last projected point to this one. The passed
   * @B point @b should be normalized (i.e. lie in the range [0.0,1.0]), with (0,0)
   * at the lower-left.
   * [OIVJAVA-WRAPPER-RETURN-TYPE WRAP_AS{void}]
   */
  SbVec3f             projectAndGetRotation(const SbVec2f &point,
                                            SbRotation &rot);

  /**
   * Gets a rotation given two points on this sphere projector. The rotation will be
   * on the surface of the sphere.
   */
  virtual SbRotation  getRotation(const SbVec3f &point1,
                                  const SbVec3f &point2) = 0;

  /**
   * Sets the sphere on which to project points. The default sphere has radius
   * 1.0.
   */
  void                setSphere(const SbSphere &sph);

  /**
   * Gets the sphere on which to project points.
   */
  const SbSphere &    getSphere() const                 { return sphere; }

  /**
   * Sets whether the projector should always be oriented towards the eye. Set
   * to FALSE if the tolerance should be evaluated in working space.
   */
  void                setOrientToEye(SbBool orientToEye);
  /**
   * Gets whether the projector should always be oriented towards the eye. 
   */
  SbBool              isOrientToEye() const           { return orientToEye; }

  /**
   * Sets whether the projector should intersect the half of the sphere that
   * faces the eye. Set to FALSE if the projector should intersect with the rear
   * half.
   */
  void                setFront(SbBool inFront);
  /**
   * Gets whether the projector should intersect the half of the sphere that
   * faces the eye. 
   */
  SbBool              isFront()       const   { return intersectFront; }
  /**
   * Gets whether the projector should intersect the half of the sphere that
   * faces the eye.
   */
  SbBool              isPointInFront( const SbVec3f &point ) const;
  /**
   * Sets the transform space to work in.
   */
  virtual void            setWorkingSpace(const SbMatrix &space);

  /**
   * Destructor.
   */
  virtual ~SbSphereProjector() {};
    
 protected:
  // Constructors
  // The default sphere to use has a radius of 1.0 and is centered at (0,0,0).
  SbSphereProjector(SbBool orientToEye);
  SbSphereProjector(const SbSphere &s, SbBool orientToEye);

  // Are intersections done on the front half (if not, they're done on
  // the back half) of the sphere?
  SbBool      intersectFront;

  // Just like sphere::intersect, except always returns
  // the intersection that is in "front".
  SbBool      intersectSphereFront(const SbLine &l, SbVec3f &result);

  SbSphere    sphere;                 // The sphere being used.
  SbBool      orientToEye;            // TRUE if always oriented to eye.
  SbBool      needSetup;              // Set TRUE whenever sphere, work space
  // or orientation changes.

  // cached last point on this projector
  SbVec3f     lastPoint;

};

#endif /* _SB_SPHERE_PROJECTOR_ */

