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


#ifndef _SB_CYLINDER_SECTION_PROJECTOR_
#define _SB_CYLINDER_SECTION_PROJECTOR_

#include <Inventor/projectors/SbCylinderProjector.h>

/**
 * Cylinder-section projector.
 * 
 * @ingroup Projectors
 * 
 * @DESCRIPTION
 *   SbCylinderSectionProjector projects a window space point (usually based on the
 *   mouse location) onto the section of a cylinder that has been sliced by a plane.
 *   Two projected points can produce a rotation along the cylinder's axis. The
 *   tolerance slice can be specified as a fraction of the radius of the cylinder.
 *   The projection point will not extend beyond the sliced portion of the
 *   cylinder.
 *   
 *   Incremental changes (delta rotation) can be computed during interactive sessions.
 *   Cylinder projectors are typically used to write interactive 3D manipulators and
 *   viewers.
 * 
 * @SEE_ALSO
 *    SbCylinderPlaneProjector,
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

class INVENTOR_API SbCylinderSectionProjector : public SbCylinderProjector
{
 public:
  /**
   * Constructor that uses a default cylinder aligned with the Y axis with
   * radius 1.0. The position of the plane
   * which slices the cylinder into a section is specified as a fraction of the
   * cylinder radius with the parameter @B edgeTol@b. A tolerance value of 1.0
   * positions the plane down the center of the cylinder. A tolerance value of 0.5
   * defines the longitudinal plane halfway between the center and the outside edge
   * of the cylinder. The default value is 0.9, so that almost half the cylinder is in
   * front of the plane. The @B orientToEye @b parameter determines whether the
   * plane is perpendicular to the eye, or perpendicular to the cylinder's Z axis.
   * Setting that parameter to TRUE (the default) specifies that the plane be
   * perpendicular to the eye, which is most often the desired behavior.
   * 
   * The default view volume is undefined, and the working space is identity.
   */
  SbCylinderSectionProjector(float  edgeTol = 0.9f,
                             SbBool orientToEye = TRUE);

  /**
   * Constructor. The position of the plane
   * which slices the cylinder into a section is specified as a fraction of the
   * cylinder radius with the parameter @B edgeTol@b. A tolerance value of 1.0
   * positions the plane down the center of the cylinder. A tolerance value of 0.5
   * defines the longitudinal plane halfway between the center and the outside edge
   * of the cylinder. The default value is 0.9, so that almost half the cylinder is in
   * front of the plane. The @B orientToEye @b parameter determines whether the
   * plane is perpendicular to the eye, or perpendicular to the cylinder's Z axis.
   * Setting that parameter to TRUE (the default) specifies that the plane be
   * perpendicular to the eye, which is most often the desired behavior.
   * 
   * The default view volume is undefined, and the working space is identity.
   */
  SbCylinderSectionProjector( const SbCylinder &cyl,
                              float edgeTol = 0.9f,
                              SbBool orientToEye = TRUE);

  /**
   * Destructor.
   */
  ~SbCylinderSectionProjector() {}
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
   * New for v3.0
   */
  virtual SbVec3f intersect( const SbLine &line );
  /**
   * Computes a rotation based on two points on this projector.
   */
  virtual SbRotation  getRotation(const SbVec3f &point1,
                                  const SbVec3f &point2);

  /**
   * Sets the edge tolerance as a fraction of the radius of the cylinder. If
   * this is 1.0, the projector is a half cylinder. If this is 0.1, the projector is a
   * slice of the cylinder with radius 0.1*radius. Default is 0.9.
   */
  void                setTolerance(float edgeTol);

  /**
   * Gets the edge tolerance as a fraction of the radius of the cylinder.
   */
  float               getTolerance() const              { return tolerance; }

  /**
   * Finds whether this point on the cylinder or tolerance plane is within tolerance.
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

  // Information about the ring tolerance.
  float               tolerance;  // the edge tolerance
  float               tolDist;    // dist from planeLine to cylinder
    
  // Information about the plane used for intersection testing.
  SbVec3f     planeDir;               // normal direction
  SbLine      planeLine;              // line parallel to axis, but in plane
  float       planeDist;              // distance from cylinder center
  SbPlane     tolPlane;               // the plane itself

};

#endif /* _SB_CYLINDER_SECTION_PROJECTOR_ */


