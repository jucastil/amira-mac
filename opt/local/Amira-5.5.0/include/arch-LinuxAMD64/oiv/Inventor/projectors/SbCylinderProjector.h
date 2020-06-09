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


#ifndef _SB_CYLINDER_PROJECTOR_
#define _SB_CYLINDER_PROJECTOR_

#include <Inventor/projectors/SbProjector.h>

/**
 * Cylinder projector.
 * 
 * @ingroup Projectors
 * 
 * @DESCRIPTION
 *   SbCylinderProjector is an abstract base class for projectors that use a cylinder
 *   in their projection. The getRotation() method for an SbCylinderProjector
 *   will always return a rotation that is about the axis of the cylinder. Cylinder
 *   projectors are typically used to write interactive 3D manipulators and viewers.
 * 
 * @SEE_ALSO
 *    SbCylinderPlaneProjector,
 *    SbCylinderSectionProjector,
 *    SbCylinderSheetProjector,
 *    SbLineProjector,
 *    SbPlaneProjector,
 *    SbSpherePlaneProjector,
 *    SbSphereProjector,
 *    SbSphereSectionProjector,
 *    SbSphereSheetProjector
 * 
 * 
 */ 

class INVENTOR_API SbCylinderProjector : public SbProjector
{
 public:
  /**
   * Destructor.
   */
  virtual ~SbCylinderProjector() {};

  /**
   * Applies the projector using the given point, returning the
   * point in three dimensions that it projects to.
   * The point should be normalized from 0-1, with (0,0) at the lower-left.
   */
  virtual SbVec3f     project(const SbVec2f &point) = 0;
  /**
   * Applies the projector using the given line in world coordinates,
   * returning the point in three dimensions that it projects to.
   * New for v3.0
   */
  virtual SbVec3f intersect( const SbLine &line ) = 0;

  /**
   * Applies the projector using the given point, returning the point in three
   * dimensions that it projects to. This also returns in @B rot @b a rotation about
   * the axis of the cylinder from the last projected point to this one. The passed
   * @B point @b should be normalized (i.e. lie in the range [0.0,1.0]), with (0,0)
   * at the lower-left.
   * [OIVJAVA-WRAPPER-RETURN-TYPE NO_WRAP]
   */
  SbVec3f             projectAndGetRotation(const SbVec2f &point,
                                            SbRotation &rot);

  /**
   * Gets a rotation given two points on this cylinder projector. The rotation will be
   * about the axis of the cylinder.
   */
  virtual SbRotation  getRotation(const SbVec3f &point1,
                                  const SbVec3f &point2) = 0;

  /**
   * Sets the cylinder on which to project points. The default cylinder is
   * aligned with the Y axis and has radius 1.0.
   */
  void                setCylinder(const SbCylinder &cyl);

  /**
   * Gets the cylinder on which to project points.
   */
  const SbCylinder &  getCylinder() const             { return cylinder; }

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
   * Sets whether the projector should intersect the half of the cylinder that
   * faces the eye. Set to FALSE if the projector should intersect with the rear
   * half.
   */
  void                setFront(SbBool isFront);
  /**
   * Gets whether the projector should intersect the half of the cylinder that
   * faces the eye. 
   */
  SbBool              isFront()       const   { return intersectFront; }
  /**
   * Gets whether the projector should intersect the half of the cylinder that
   * faces the eye. 
   */
  SbBool              isPointInFront( const SbVec3f &point ) const;
  /**
   *  Sets the transform space to work in.
   */   
  virtual void        setWorkingSpace(const SbMatrix &space);
    
 protected:
  // Constructors
  // The default cylinder to is centered about the Y axis and
  // has a radius of 1.0.
  SbCylinderProjector(SbBool orientToEye);
  SbCylinderProjector(const  SbCylinder &cyl,
                      SbBool orientToEye);

  // Are intersections done on the front half ( if not, they're done on th e
  // back half) of the cylinder?
  SbBool      intersectFront;

  // Just like cylinder::intersect, except always returns
  // the intersection that is in "front".
  SbBool      intersectCylinderFront(const SbLine &line, SbVec3f &result);

  SbCylinder  cylinder;               // Cylinder for this projector.
  SbBool      orientToEye;            // TRUE if always oriented to eye.
  SbBool      needSetup;              // Set TRUE whenever cylinder,
  // work space or orientation changes.

  // Cached last point on this projector. Subclasses must set
  // this in their project and getRotation methods.
  SbVec3f     lastPoint;

};


#endif /* _SB_CYLINDER_PROJECTOR_ */

