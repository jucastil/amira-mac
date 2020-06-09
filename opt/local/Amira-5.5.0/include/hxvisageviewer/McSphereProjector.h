#ifndef MC_SPHERE_PROJECTOR_H
#define MC_SPHERE_PROJECTOR_H

#include "McProjector.h"
#include "McSphere.h"

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
 *    McLineProjector,
 *    McPlaneProjector,
 *    SbSpherePlaneProjector,
 *    SbSphereSectionProjector,
 *    SbSphereSheetProjector
 * 
 * @MODIFICATIONS_ENHANCEMENTS @I Copyright (C) 1997-2002 TGS ALL RIGHTS RESERVED @i
 * 
 */ 

class McSphereProjector : public McProjector
{
 public:
  /**
   * Applies the projector using the given point, returning the
   * point in three dimensions that it projects to.
   * The point should be normalized from 0-1, with (0,0) at the lower-left.
   */
  virtual McVec3f     project(const McVec2f &point) = 0;
  /**
   * Applies the projector using the given line in world coordinates,
   * returning the point in three dimensions that it projects to.
   * New for v3.0.
   */
  virtual McVec3f intersect( const McLine &line ) = 0;

  /**
   * Applies the projector using the given point, returning the point in three
   * dimensions that it projects to. This also returns in @B rot @b a rotation on
   * the surface of the sphere from the last projected point to this one. The passed
   * @B point @b should be normalized (i.e. lie in the range [0.0,1.0]), with (0,0)
   * at the lower-left.
   */
  McVec3f             projectAndGetRotation(const McVec2f &point,
                                            McRotation &rot);

  /**
   * Gets a rotation given two points on this sphere projector. The rotation will be
   * on the surface of the sphere.
   */
  virtual McRotation  getRotation(const McVec3f &point1,
                                  const McVec3f &point2) = 0;

  /**
   * Sets the sphere on which to project points. The default sphere has radius
   * 1.0.
   */
  void                setSphere(const McSphere &sph);

  /**
   * Gets the sphere on which to project points.
   */
  const McSphere &    getSphere() const                 { return sphere; }

  /**
   * Sets whether the projector should always be oriented towards the eye. Set
   * to FALSE if the tolerance should be evaluated in working space.
   */
  void                setOrientToEye(bool orientToEye);
  /**
   * Gets whether the projector should always be oriented towards the eye. 
   */
  bool              isOrientToEye() const           { return orientToEye; }

  /**
   * Sets whether the projector should intersect the half of the sphere that
   * faces the eye. Set to FALSE if the projector should intersect with the rear
   * half.
   */
  void                setFront(bool inFront);
  /**
   * Gets whether the projector should intersect the half of the sphere that
   * faces the eye. 
   */
  bool              isFront()       const   { return intersectFront; }
  /**
   * Gets whether the projector should intersect the half of the sphere that
   * faces the eye.
   */
  bool              isPointInFront( const McVec3f &point ) const;
  /**
   * Sets the transform space to work in.
   */
  virtual void            setWorkingSpace(const McMat4f &space);

  /**
   * Destructor.
   */
  ~McSphereProjector(){};
    
 protected:
  // Constructors
  // The default sphere to use has a radius of 1.0 and is centered at (0,0,0).
  McSphereProjector(bool orientToEye);
  McSphereProjector(const McSphere &s, bool orientToEye);

  // Are intersections done on the front half (if not, they're done on
  // the back half) of the sphere?
  bool      intersectFront;

  // Just like sphere::intersect, except always returns
  // the intersection that is in "front".
  bool      intersectSphereFront(const McLine &l, McVec3f &result);

  McSphere  sphere;                 // The sphere being used.
  bool      orientToEye;            // TRUE if always oriented to eye.
  bool      needSetup;              // Set TRUE whenever sphere, work space
  // or orientation changes.

  // cached last point on this projector
  McVec3f   lastPoint;
};

#endif

