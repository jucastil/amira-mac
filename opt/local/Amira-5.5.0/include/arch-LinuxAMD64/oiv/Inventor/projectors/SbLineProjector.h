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


#ifndef _SB_LINE_PROJECTOR_
#define _SB_LINE_PROJECTOR_

#include <Inventor/projectors/SbProjector.h>

/**
 * Line projector.
 * 
 * @ingroup Projectors
 * 
 * @DESCRIPTION
 *   SbLineProjector projects a 2D point, typically the location of the cursor, onto
 *   a 3D line.
 * 
 * @SEE_ALSO
 *    SbCylinderProjector,
 *    SbCylinderPlaneProjector,
 *    SbCylinderSectionProjector,
 *    SbCylinderSheetProjector,
 *    SbPlaneProjector,
 *    SbSpherePlaneProjector,
 *    SbSphereProjector,
 *    SbSphereSectionProjector,
 *    SbSphereSheetProjector
 * 
 * 
 */ 

class INVENTOR_API SbLineProjector : public SbProjector
{
 public:
  /**
   * Constructor. The default line passes through the origin and is
   * aligned with the Y axis.
   */
  SbLineProjector();

  /**
   * Destructor.
   */
  virtual ~SbLineProjector() {};
    
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
   * Applies the projector using the given point, returning the
   * point in three dimensions that it projects to and the status.
   * The point should be normalized from 0-1, with (0,0) at the lower-left.
   */
  virtual SbBool      project(const SbVec2f &point, SbVec3f &projectedPoint);
  /**
   * Applies the projector using the given line in world coordinates,
   * returning the point in three dimensions that it projects to.
   * New for v3.0.
   */
  virtual SbVec3f intersect( const SbLine &line );

  /**
   * Sets the line on which to project 2D points.
   */
  void                setLine(const SbLine &line);
  /**
   * Gets the line on which to project 2D points.
   */
  const SbLine &      getLine() const           { return line; }

  /**
   * Gets a vector on this line given two normalized mouse points.
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
   * Sets the initial position from a mouse position.
   */
  void                setStartPosition(const SbVec2f &mousePosition)
    { lastPoint = project(mousePosition); }

  /**
   * Sets the initial position from a point on the projector.
   */
  void                setStartPosition(const SbVec3f &point)
    { lastPoint = point; }
 protected:

  SbLine      line;
  SbVec3f     lastPoint;

};

#endif /* _SB_LINE_PROJECTOR_ */

