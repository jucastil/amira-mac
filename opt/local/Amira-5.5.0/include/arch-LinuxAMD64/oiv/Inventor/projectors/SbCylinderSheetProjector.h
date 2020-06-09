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


#ifndef _SB_CYLINDER_SHEET_PROJECTOR_
#define _SB_CYLINDER_SHEET_PROJECTOR_

#include <Inventor/projectors/SbCylinderProjector.h>

/**
 * Cylinder-sheet projector.
 * 
 * @ingroup Projectors
 * 
 * @DESCRIPTION
 *   SbCylinderSheetProjector projects a window space point (usually based on the
 *   mouse location) onto the surface of a cylinder with a hyperbolic sheet draped
 *   over it. This allows smooth transitions onto and off of the cylinder. Two
 *   projected points can produce a rotation along the cylinder's axis. When the
 *   mouse position projects on to the sheet, the rotations will be as if the sheet
 *   is being dragged, causing the cylinder to roll beneath it.
 *   
 *   Incremental changes (delta rotation) can be computed during interactive sessions.
 *   Cylinder projectors are typically used to write interactive 3D manipulators and
 *   viewers.
 * 
 * @SEE_ALSO
 *    SbCylinderSectionProjector,
 *    SbCylinderPlaneProjector,
 *    SbLineProjector,
 *    SbPlaneProjector,
 *    SbSpherePlaneProjector,
 *    SbSphereProjector,
 *    SbSphereSectionProjector,
 *    SbSphereSheetProjector
 * 
 * 
 */ 

class INVENTOR_API SbCylinderSheetProjector : public SbCylinderProjector
{
 public:
  /**
   * Constructor that uses a default cylinder aligned with the Y axis with
   * radius 1.0. The @B orientToEye @b
   * parameter determines whether the sheet is perpendicular to the eye, or
   * perpendicular to the cylinder's Z axis. Setting that parameter to TRUE (the
   * default) specifies that the plane be perpendicular to the eye, which is most
   * often the desired behavior.
   * 
   * The default view volume is undefined, and the working space is identity.
   */
  SbCylinderSheetProjector(SbBool orientToEye = TRUE);

  /**
   * Constructor. The @B orientToEye @b
   * parameter determines whether the sheet is perpendicular to the eye, or
   * perpendicular to the cylinder's Z axis. Setting that parameter to TRUE (the
   * default) specifies that the plane be perpendicular to the eye, which is most
   * often the desired behavior.
   * 
   * The default view volume is undefined, and the working space is identity.
   */
  SbCylinderSheetProjector(const  SbCylinder &cyl,
                           SbBool orientToEye = TRUE);

  /**
   * Destructor.
   */
  ~SbCylinderSheetProjector() {}
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
   * Computes a rotation based on two points on this projector.
   */
  virtual SbRotation  getRotation(const SbVec3f &point1,
                                  const SbVec3f &point2);

 protected:
  // Sets up the tolerance plane.
  // If projecting from a point, call with no parameters.
  // If intersecting a line, pass the line in *working space*.
  virtual void        setupPlane( const SbLine *line = NULL );

  // The projection point in working space.
  SbVec3f             workingProjPoint;
    
  // Information about the plane used for intersection testing.
  SbVec3f     planeDir;               // normal direction
  SbPlane     tolPlane;               // the plane itself

};

#endif /* _SB_CYLINDER_SHEET_PROJECTOR_ */

