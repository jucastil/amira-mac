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


#ifndef _SB_PROJECTOR_
#define _SB_PROJECTOR_

#include <Inventor/SbLinear.h>

/**
 * Base class for representing projectors.
 * 
 * @ingroup Projectors
 * 
 * @DESCRIPTION
 *   SbProjector is the base class for all projector classes. Projector classes are
 *   used to convert from window space (usually based on the mouse location) into a
 *   3D point. This is done by projecting the window coordinate as a 3D vector onto a
 *   geometric function in 3-space, and computing the intersection point. Most
 *   projectors actually compute incremental changes and produce incremental
 *   rotations and translation as needed. Projectors are used to write 3D interactive
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
 *    SbSphereProjector,
 *    SbSphereSectionProjector,
 *    SbSphereSheetProjector
 * 
 * 
 */ 

class INVENTOR_API SbProjector
{
 public:
  /**
   * Destructor.
   */
  virtual ~SbProjector() {};

  /**
   * Apply the projector using the given point, returning the point in three
   * dimensions that it projects to. The point should be normalized (lie in the range
   * [0.0,1.0]), with (0,0) at the lower-left.
   */
  virtual SbVec3f project(const SbVec2f &point) = 0;
  /**
   * Applies the projector using the given line in world coordinates,
   * returning the point in three dimensions that it projects to.
   * Note: For the projectors that support "orientToEye", setting
   * this flag to TRUE causes the projector to orient to the line
   * when the intersect method is called.
   * New for v3.0.
   */
  virtual SbVec3f intersect( const SbLine &line ) = 0;

  /**
   * Set the view volume to use for the projection. This is typically
   * supplied from SoCamera::getViewVolume().
   */
  virtual void setViewVolume(const SbViewVolume &vol);

  /**
   * Get the view volume to use for the projection.
   */
  const SbViewVolume &getViewVolume() const { return viewVol; }
    
  /**
   * Set the transform space to work in. This matrix should transform working
   * space coordinates into world space. The default matrix is identity, meaning that
   * the default working space is world space.
   */
  virtual void setWorkingSpace(const SbMatrix &space);

  /**
   * Get the transform space to work in. 
   */
  const SbMatrix &getWorkingSpace() const { return workingToWorld ; }

  /**
   * Creates and returns an exact copy of the projector.
   */
  virtual SbProjector *copy() const = 0;

 protected:
  // Default constructor.
  // The default view volume is undefined.
  // The default working space is identity (world space).
  SbProjector();

  // Given this mouse point, return the line it projects to
  // in working space.
  SbLine getWorkingLine(const SbVec2f &point) const;
  
  SbViewVolume viewVol;
  SbMatrix worldToWorking, workingToWorld;
};

#endif /* _SB_PROJECTOR_ */

