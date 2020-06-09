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


#ifndef _SB_SPHERE_PLANE_PROJECTOR_
#define _SB_SPHERE_PLANE_PROJECTOR_

#include <Inventor/projectors/SbSphereSectionProjector.h>

/**
 * Sphere-plane projector.
 * 
 * @ingroup Projectors
 * 
 * @DESCRIPTION
 *   SbSpherePlaneProjector projects a window space point (usually based on the mouse
 *   location) onto a surface defined by a sphere and plane cutting through the
 *   sphere. Two projected points can produce a rotation about the sphere's center.
 *   When the mouse position projects onto the plane, the rotations will be as if the
 *   plane is being dragged, causing the sphere to roll beneath it.
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
 *    SbSphereSheetProjector
 * 
 * 
 */ 

class INVENTOR_API SbSpherePlaneProjector : public SbSphereSectionProjector
{
 public:
  /**
   * Constructor that uses a default sphere centered at the origin with radius
   * 1.0. The position of the plane is
   * specified as a fraction of the sphere radius with the parameter @B edgeTol@b.
   * A tolerance value of 1.0 positions the plane down the center of the sphere. A
   * tolerance value of 0.5 defines the longitudinal plane halfway between the center
   * and the outside edge of the sphere. The default value is 0.9, so that almost half
   * the sphere is in front of the plane. The @B orientToEye @b parameter determines
   * whether the plane is perpendicular to the eye, or perpendicular to the sphere's
   * Z axis. Setting that parameter to TRUE (the default) specifies that the plane be
   * perpendicular to the eye, which is most often the desired behavior.
   * 
   * The default view volume is undefined, and the working space is identity.
   */
  SbSpherePlaneProjector(float edgeTol = 0.9f, SbBool orientToEye = TRUE);

  /**
   * Constructor that uses a supplied sphere. The position of the plane is
   * specified as a fraction of the sphere radius with the parameter @B edgeTol@b.
   * A tolerance value of 1.0 positions the plane down the center of the sphere. A
   * tolerance value of 0.5 defines the longitudinal plane halfway between the center
   * and the outside edge of the sphere. The default value is 0.9, so that almost half
   * the sphere is in front of the plane. The @B orientToEye @b parameter determines
   * whether the plane is perpendicular to the eye, or perpendicular to the sphere's
   * Z axis. Setting that parameter to TRUE (the default) specifies that the plane be
   * perpendicular to the eye, which is most often the desired behavior.
   * 
   * The default view volume is undefined, and the working space is identity.
   */
  SbSpherePlaneProjector( const  SbSphere &sph,
                          float  edgeTol = 0.9f,
                          SbBool orientToEye = TRUE);

  /**
   * Destructor.
   */
  ~SbSpherePlaneProjector() {}
 
  /**   
   * Returns an instance that is a copy of this instance. The caller
   * is responsible for deleting the copy when done.
   */
  virtual SbProjector *    copy() const;
  /**
   * Apply the projector using the given point, returning the
   * point in three dimensions that it projects to.
   * The point should be normalized from 0-1, with (0,0) at the lower-left.
   */
  virtual SbVec3f     project(const SbVec2f &point);
  /**
   * Apply the projector using the given line in world coordinates,
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
  SbRotation          getRotation(const SbVec3f &point1, SbBool tol1, 
                                  const SbVec3f &point2, SbBool tol2);

  // Apply the projector using the given line in working space.
  // Encapsulates code common to project and intersect methods.
  // New for v3.0
  virtual SbVec3f intersectWorkingLine( const SbLine &line );

};

#endif /* _SB_SPHERE_PLANE_PROJECTOR_ */

