/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Howard Look (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
** Modified by : Paul Isaacs (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SB_SPHERE_SHEET_PROJECTOR_
#define _SB_SPHERE_SHEET_PROJECTOR_

#include <Inventor/projectors/SbSphereProjector.h>

/**
 * Sphere-sheet projector.
 * 
 * @ingroup Projectors
 * 
 * @DESCRIPTION
 *   SbSphereSheetProjector projects a window space point (usually based on the mouse
 *   location) onto the surface of a sphere with a hyperbolic sheet draped over it.
 *   This allows smooth transitions onto and off of the sphere. Two projected points
 *   can produce a rotation about the sphere's center. When the mouse position
 *   projects on to the sheet, the rotations will be as if the sheet is being
 *   dragged, causing the sphere to roll beneath it.
 *   
 *   Incremental changes (delta rotation) can be computed during interactive sessions.
 *   Sphere projectors are typically used to write interactive 3D manipulators and
 *   viewers.
 * 
 * @SEE_ALSO
 *    SbCylinderProjector,
 *    SbCylinderPlaneProjector,
 *    SbCylinderSectionProjector,
 *    SbCylinderSheetProjector,
 *    SbLineProjector,
 *    SbPlaneProjector,
 *    SbSpherePlaneProjector
 * 
 * 
 */ 

class INVENTOR_API SbSphereSheetProjector : public SbSphereProjector
{
 public:
  /**
   * Constructor that uses a default sphere centered at the origin with radius
   * 1.0. The @B orientToEye @b parameter
   * determines whether the sheet is perpendicular to the eye, or perpendicular to
   * the sphere's Z axis. Setting that parameter to TRUE (the default) specifies that
   * the sheet be perpendicular to the eye, which is most often the desired
   * behavior.
   * 
   * The default view volume is undefined, and the working space is identity.
   */
  SbSphereSheetProjector(SbBool orientToEye = TRUE);

  /**
   * Constructor that uses a supplied sphere. The @B orientToEye @b parameter
   * determines whether the sheet is perpendicular to the eye, or perpendicular to
   * the sphere's Z axis. Setting that parameter to TRUE (the default) specifies that
   * the sheet be perpendicular to the eye, which is most often the desired
   * behavior.
   * 
   * The default view volume is undefined, and the working space is identity.
   */
  SbSphereSheetProjector(const SbSphere &sph,
                         SbBool orientToEye = TRUE);

  /**
   * Destructor.
   */
  ~SbSphereSheetProjector() {}
  /**    
   * Returns an instance that is a copy of this instance. The caller
   * is responsible for deleting the copy when done.
   */
  virtual SbProjector *    copy() const;
  /**
   * Applies the projector using the given point, returning the
   * point in three dimensions that it projects to.
   * The point should be normalized from 0-1, with (0,0) at the lower-left.
   */
  virtual SbVec3f     project(const SbVec2f &point);
  /**
   * Applies the projector using the given line in world coordinates,
   * returning the point in three dimensions that it projects to.
   * New for v3.0.
   */
  virtual SbVec3f intersect( const SbLine &line );
  /**
   * Computes a rotation based on two points on this projector.
   */
  virtual SbRotation  getRotation(const SbVec3f &point1,
                                  const SbVec3f &point2);

 protected:
  // Sets up the plane use to project on to.
  // If projecting from a point, call with no parameters.
  // If intersecting a line, pass the line in *working space*.
  virtual void        setupPlane( const SbLine *line = NULL );

  // The projection point in working space.
  SbVec3f             workingProjPoint;
    
  // Information about the plane used for intersection testing.
  SbVec3f     planePoint;             // point on plane
  SbVec3f     planeDir;               // normal direction
  float       planeDist;              // distance from sphere center
  SbPlane     tolPlane;               // the plane itself

};

#endif /* _SB_SPHERE_SHEET_PROJECTOR_ */

