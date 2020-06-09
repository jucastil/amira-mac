/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Howard Look (MMM yyyy)
** Modified by : Paul Isaacs (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SB_PLANE_PROJECTOR_
#define _SB_PLANE_PROJECTOR_

#include <Inventor/projectors/SbProjector.h>

/**
 * Plane projector.
 * 
 * @ingroup Projectors
 * 
 * @DESCRIPTION
 *   SbPlaneProjector projects the mouse onto a plane. This is typically used to
 *   write interactive 3D manipulators and viewers.
 * 
 * @SEE_ALSO
 *    SbCylinderProjector,
 *    SbCylinderPlaneProjector,
 *    SbCylinderSectionProjector,
 *    SbCylinderSheetProjector,
 *    SbLineProjector,
 *    SbSpherePlaneProjector,
 *    SbSphereProjector,
 *    SbSphereSectionProjector,
 *    SbSphereSheetProjector
 * 
 * 
 */ 

class INVENTOR_API SbPlaneProjector : public SbProjector
{
 public:
  
  /**
   * Constructor. The default plane passes through the origin and is oriented
   * perpendicular to the Z axis.
   */
  SbPlaneProjector(SbBool orient = FALSE);
    
  /**
   * Constructor which is passed a plane. If orient to eye is TRUE, the plane will be
   * reoriented to the eye.
   */
  SbPlaneProjector(const SbPlane &plane,
                   SbBool orient = FALSE);

  /**
   * Destructor.
   */
  virtual ~SbPlaneProjector() {};

  /**    
   * Returns an instance that is a copy of this instance. The caller
   * is responsible for deleting the copy when done.
   */
  virtual SbProjector *    copy() const;
  /**
   * Applies the projector using the given point, returning the
   * point in three dimensions that it projects to.
   * The point should be normalized from 0-1, with (0,0) at
   * the lower-left.
   */
  virtual SbVec3f     project(const SbVec2f &point);
  /**
   * Applies the projector using the given line in world coordinates,
   * returning the point in three dimensions that it projects to.
   * New for v3.0.
   */
  virtual SbVec3f intersect( const SbLine &line );

  /**
   * Sets the plane to use.
   */
  void                setPlane(const SbPlane &plane);

  /**
   * Gets the plane to use.
   */
  const SbPlane &     getPlane() const                  { return plane; }

  /**
   * Sets whether the projector should be oriented towards the eye. If
   * @B orientToEye @b is set to TRUE, the given plane's direction is ignored, and
   * the plane will be oriented to the eye. It will pass through the same point from
   * the origin defined by the original dir * dist. Set to FALSE if the plane's
   * direction should remain in working space.
   */
  void                setOrientToEye(SbBool orientToEye);
  /**
   * Gets whether the projector should be oriented towards the eye. 
   */
  SbBool              isOrientToEye() const           { return orientToEye; }

  /**
   * Gets a vector on this plane given two normalized mouse positions.
   */
  virtual SbVec3f     getVector(const SbVec2f &mousePosition1,
                                const SbVec2f &mousePosition2);
                                            
  /**
   * Gets a vector given the current mouse point. Uses the last point on this
   * projector from the previous call to getVector() or
   * setStartPostion(). Do not use this if the working space transform is
   * changing since the new point will be in a different space than the old one.
   */
  virtual SbVec3f     getVector(const SbVec2f &mousePosition);
                                            
  /**
   * Sets the initial mouse position.
   */
  void                setStartPosition(const SbVec2f &mousePosition)
    { lastPoint = project(mousePosition); }

  /**
   * Sets the initial position from a point on the projector.
   */
  void                setStartPosition(const SbVec3f &point)
    { lastPoint = point; }
 protected:

  SbPlane     plane;
  SbBool      orientToEye;    // TRUE is plane should be oriented to eye.
  SbBool      needSetup;      // Set TRUE when plane or orientToEye changes.
  SbPlane     nonOrientPlane; // Non-EyeOriented plane.

  SbVec3f     lastPoint;      // Cached last point.

  void        setupPlane();   // Sets up plane orientation, if necessary.

};

#endif /* _SB_PLANE_PROJECTOR_ */

