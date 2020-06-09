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


#ifndef _SB_SPHERE_SECTION_PROJECTOR_
#define _SB_SPHERE_SECTION_PROJECTOR_

#include <Inventor/projectors/SbSphereProjector.h>

/**
 * Sphere-section projector.
 * 
 * @ingroup Projectors
 * 
 * @DESCRIPTION
 *   SbSphereSectionProjector projects a window space point (usually based on the
 *   mouse location) onto the section of a sphere that has been sliced by a plane.
 *   Two projected points can produce a rotation about the sphere's center. The
 *   tolerance slice can be specified as a fraction of the radius of the sphere. The
 *   projection point will not extend beyond the sliced portion of the sphere.
 *   
 *   Incremental changes (delta rotation) can be computed during interactive sessions.
 *   Sphere projectors are typically used to write interactive 3D manipulators and
 *   viewers.
 * 
 * @SEE_ALSO
 *    SbCylinderProjector,
 *    SbCylinderSectionProjector,
 *    SbCylinderPlaneProjector,
 *    SbCylinderSheetProjector,
 *    SbLineProjector,
 *    SbPlaneProjector,
 *    SbSpherePlaneProjector,
 *    SbSphereSheetProjector
 * 
 * 
 */ 

class INVENTOR_API SbSphereSectionProjector : public SbSphereProjector
{
 public:
  /**
   * Constructor that uses a default sphere centered at the origin with radius
   * 1.0. The position of the plane which
   * slices the sphere into a section is specified as a fraction of the sphere radius
   * with the parameter @B edgeTol@b. A tolerance value of 1.0 positions the plane
   * down the center of the sphere. A tolerance value of 0.5 defines the longitudinal
   * plane halfway between the center and the outside edge of the sphere. The default
   * value is 0.9, so that almost half the sphere is in front of the plane. The
   * @B orientToEye @b parameter determines whether the plane is perpendicular to
   * the eye, or perpendicular to the sphere's Z axis. Setting that parameter to TRUE
   * (the default) specifies that the plane be perpendicular to the eye, which is
   * most often the desired behavior.
   * 
   * The default view volume is undefined, and the working space is identity.
   */
  SbSphereSectionProjector(float  edgeTol = 0.9f,
                           SbBool orientToEye = TRUE);

  /**
   * Constructor that uses a supplied sphere. The position of the plane which
   * slices the sphere into a section is specified as a fraction of the sphere radius
   * with the parameter @B edgeTol@b. A tolerance value of 1.0 positions the plane
   * down the center of the sphere. A tolerance value of 0.5 defines the longitudinal
   * plane halfway between the center and the outside edge of the sphere. The default
   * value is 0.9, so that almost half the sphere is in front of the plane. The
   * @B orientToEye @b parameter determines whether the plane is perpendicular to
   * the eye, or perpendicular to the sphere's Z axis. Setting that parameter to TRUE
   * (the default) specifies that the plane be perpendicular to the eye, which is
   * most often the desired behavior.
   * 
   * The default view volume is undefined, and the working space is identity.
   */
  SbSphereSectionProjector(const SbSphere &sph,
                           float edgeTol = 0.9f, 
                           SbBool orientToEye = TRUE);

  /**
   * Destructor.
   */
  ~SbSphereSectionProjector() {}
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

  /**
   * Sets the edge tolerance as a fraction of the radius of the sphere. If
   * this is 1.0, the projector is a hemisphere. If this is 0.1, the projector is a
   * slice of the sphere with radius 0.1*radius. Default is 0.9.
   */
  void                setTolerance(float edgeTol);

  /**
   * Gets the edge tolerance as a fraction of the radius of the sphere.
   */
  float               getTolerance() const              { return tolerance; }

  /**
   * Sets the radial rotation factor. When the mouse is dragged off the edge
   * of the sphere, the mouse motion can be classified as either tangential (moving
   * in a circle around the sphere) or radial (moving toward or away from the
   * center). The tangential motion will always map to a rotation around the center,
   * (like the hands of a clock). The radial motion, by default, has no effect. But
   * if you set the @B radialFactor @b to be > 0.0, this motion will make the sphere
   * rotate as if the mouse is pulling the top of the sphere out toward the mouse. If
   * @B radialFactor @b = 1.0, then pulling has a `normal' feel (that is, the mouse
   * motion causes the same amount of rotation as if you had rotated by hitting the
   * actual surface of the sphere). Default is 0.0
   */
  void                setRadialFactor(float rad = 0.0) { radialFactor = rad;}
  /**
   * Gets the radial rotation factor.
   */
  float               getRadialFactor() const  { return radialFactor; }

  /**
   * Finds whether this point on the sphere or tolerance plane is within tolerance.
   */
  SbBool              isWithinTolerance(const SbVec3f &point);
    
 protected:
  
  // Sets up the tolerance slice.
  // If projecting from a point, call with no parameters.
  // If intersecting a line, pass the line in *working space*.
  virtual void        setupTolerance( const SbLine *line = NULL );

  // Apply the projector using the given line in working space.
  // Encapsulates code common to project and intersect methods.
  // New for v3.0
  virtual SbVec3f intersectWorkingLine( const SbLine &line );

  // Information about the slice tolerance.
  float               tolerance;  // the edge tolerance
  float               tolDist;    // dist from planePoint to tolerance slice

  float               radialFactor;
    
  // Information about the plane used for intersection testing.
  SbVec3f     planePoint;             // point on plane
  SbVec3f     planeDir;               // normal direction
  float       planeDist;              // distance from sphere center
  SbPlane     tolPlane;               // the plane itself

};

#endif /* _SB_SPHERE_SECTION_PROJECTOR_ */


