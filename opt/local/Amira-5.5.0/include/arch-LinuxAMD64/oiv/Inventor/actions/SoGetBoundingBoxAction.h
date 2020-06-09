/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SO_GET_BOUNDING_BOX_ACTION_
#define _SO_GET_BOUNDING_BOX_ACTION_

#include <Inventor/SbBox.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/actions/SoSubAction.h>

//////////////////////////////////////////////////////////////////////////////
//
//    Class: SoGetBoundingBoxAction
//
//    For computing a bounding box enclosing objects defined by a scene
//    graph. The box is a rectangular prism whose sides are aligned with
//    the coordinate axes, and is represented as an SbBox3f. It also
//    computes the center point, which is defined differently for
//    different objects.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Computes bounding box of a scene.
 * 
 * @ingroup actions
 * 
 * @DESCRIPTION
 *   This class is used to compute a 3D bounding box enclosing objects defined by a
 *   scene graph. The box is a rectangular prism. The action also computes the center
 *   point, which is defined differently for different objects. (For example, the
 *   center of an SoFaceSet is the average of its vertices' coordinates.) For a
 *   group, the center point is defined as the average of the centers of all shapes
 *   in it.
 *   
 *   Each bounding box is calculated as an SbXfBox3f, where the transformation matrix
 *   is defined so that the bounding box can be stored in the object space of the
 *   SoShape. When two bounding boxes are combined by a group node, the combination
 *   is performed so as to produce the smaller untransformed box. The result of the
 *   calculation by the action can be returned as an SbXfBox3f or as a
 *   world-space-aligned SbBox3f.
 *   
 *   To calculate the bounding box of a subgraph bounded by two paths, specify the
 *   left edge of the subgraph with setResetPath(), and apply the action to
 *   the path that defines the right edge of the subgraph. The accumulated bounding
 *   box and transformation will be reset when the tail of the reset path is
 *   traversed.
 *   
 *   If the subgraph being traversed does not contain any shapes, the returned
 *   bounding box will be empty (that is, SbBox3f::isEmpty() will return TRUE).
 *
 *   The SoBBox node can be used to specify the bounding box for a shape or portion
 *   of the scene graph. This is useful, for example, to avoid the cost of computing
 *   the bounding box of a large (or frequently changing) geometry. The SoBBox node
 *   can also be used to specify that a shape or portion of the scene graph should
 *   not be included in the bounding box calculation.  This is useful, for example,
 *   to avoid considering screen aligned "annotation" graphics like legends.
 *
 *   Bounding boxes are used internally by Open Inventor to optimize rendering,
 *   picking, culling and other operations.  For example, the standard viewer
 *   classes apply an SoGetBoundingBoxAction to the scene graph when automatic
 *   adjustment of the near and far clipping planes is enabled (which is the default).
 *
 *   Bounding boxes are cached by some grouping nodes, primarily SoSeparator.
 *   When this action is applied to a scene graph, it will use the cached bounding
 *   box whenever possible.  So querying the bounding box of a (relatively) static
 *   scene graph is normally very fast.  Open Inventor automatically detects when
 *   bounding caches become invalid and they are re-computed the next time an
 *   SoGetBoundingBoxAction is applied.
 *
 *   The bounding box will only include shapes that are actually traversed.
 *   For example the bounding box will not include shapes under an SoSwitch with
 *   whichChild set to SO_SWITCH_NONE.
 *
 *   NOTE: The action does not consider the visibility of shapes that are traversed.
 *   In other words the bounding box will include shapes that are invisible because
 *   of an SoDrawStyle, shapes that are clipped out because of an SoClipPlane, etc.
 *   Use SoBBox if necessary to exclude shapes from the bounding box computation.
 *
 *   Sets: SoViewportRegionElement
 *
 * @EXAMPLE
 *   \oivnetdoc
 *     \code
 *     // Get bounding box using current viewport on screen
 *     SoGetBoundingBoxAction gba = new SoGetBoundingBoxAction();
 *     gba.Apply( rootNode );
 *     SbBox3f bbox = gba.GetBoundingBox();
 *     \endcode
 *   \else
 *     \code
 *     // Get bounding box using current viewport on screen
 *     SoGetBoundingBoxAction gba( pViewer->getViewportRegion() );
 *     gba.apply( pRootNode );
 *     SbBox3f bbox = gba.getBoundingBox();
 *     \endcode
 *   \endoivnetdoc
 * 
 * @SEE_ALSO
 *    SbBox3f,
 *    SbXfBox3f,
 *    SoGetMatrixAction,
 *    SoBBox
 * 
 * 
 */ 

class INVENTOR_API SoGetBoundingBoxAction : public SoAction
{
  SO_ACTION_HEADER(SoGetBoundingBoxAction);

 public:
  /**
   * Constructor. @BR
   * Even though the bounding box computation may not involve a window per se, 
   * some nodes need the size of the viewport to determine their size in 3D
   * coordinates.  For example the size of an SoText2 is a fixed value in device
   * coordinates, but the corresponding size in 3D depends on the current camera.
   *
   * Usually it is convenient to get the actual viewport region from the viewer
   * as shown in the example above.  However if the scene graph does not contain
   * any viewport dependent nodes then any values can be used.
   */
  SoGetBoundingBoxAction(const SbViewportRegion &viewportRegion);

  // Destructor
#ifndef HIDDEN_FROM_DOC
  virtual ~SoGetBoundingBoxAction();
#endif // HIDDEN_FROM_DOC

  /**
   * Sets current viewport region to use for action.
   */
  void setViewportRegion(const SbViewportRegion &newRegion);

  /**
   * Returns current viewport region to use for action.
   */
  const SbViewportRegion &getViewportRegion() const;

  /**
   * Returns computed bounding box in world space.
   */
  SbBox3f getBoundingBox() const;

  /**
   * Returns computed bounding box before transformation into world space.
   */
  SbXfBox3f &getXfBoundingBox();

  /**
   * Returns computed center point in world space.
   */
  const SbVec3f &getCenter() const;

  /**
   * Set this flag to TRUE if you want the returned bounding box to be in the space
   * of whatever camera is in the graph. Camera space is defined to have the
   * viewpoint at the origin, with the direction of view along the negative z axis.
   * This space can be used to determine distances of objects from the camera.
   */
  void setInCameraSpace(SbBool flag);

  /**
   * Returns camera space flag.
   */
  SbBool isInCameraSpace() const;

  /** Set a path to do a resetTransform/resetBoundingBox on. The default
   * is to do the reset right before the given path.
   */
  enum ResetType {    // Which things get reset:
    /**
     *  Transformation 
     */
    TRANSFORM = 0x01,
    /**
     *  Bounding box 
     */
    BBOX = 0x02,
    /**
     *  Both transform and bounding box 
     */
    ALL = 0x03
  };

  /**
   * If a non-NULL path is specified, the action will reset the computed bounding box
   * to be empty and/or the current transformation to identity. The
   * @B resetBefore @b flag indicates whether to perform the reset before or after
   * the tail node of the path is traversed.
   */
  void setResetPath(const SoPath *path,
                    SbBool resetBefore = TRUE,
                    ResetType what = ALL);
  /**
   * Returns the current reset path, or NULL.
   */
  const SoPath *getResetPath() const;
  /**
   * Returns TRUE if the current reset path is not NULL.
   */
  SbBool isResetPath() const;
  /**
   * Returns TRUE if the @B resetBefore @b flag was specified for the reset path.
   */
  SbBool isResetBefore() const;
  /**
   * Returns what flags were specified to be reset for the reset path.
   */
  SoGetBoundingBoxAction::ResetType getWhatReset() const;

 SoEXTENDER public:

  // Call these methods at beginning and end (respectively) of
  // the getBoundingBox action for each node. (SoNode calls these in
  // its static method for this action.)
  void checkResetBefore();
  void checkResetAfter();

  // Extends the current bounding box by the given bounding box,
  // after transforming it by the current value of the
  // SoLocalBBoxMatrixElement
  void extendBy(const SbBox3f &box);
  void extendBy(const SbXfBox3f &box);

  void extendBy(const SbBox3d &box);
  void extendBy(const SbXfBox3d &box);

  // Sets the center of the bounding box to the given point, which,
  // if transformCenter is TRUE, is first transformed by the current
  // value of the SoLocalBBoxMatrixElement. After this is called,
  // isCenterSet will return TRUE, unless resetCenter is called.
  // Shapes should setCenter() to whatever is appropriate (e.g.
  // left-justified text might set the center to be the start of the
  // string) with transformCenter set to TRUE.    Groups are
  // responsible for averaging the centers if more than one shape
  // sets the center; when setting the center to the average of
  // transformed centers, pass FALSE for transformCenter.
  void setCenter(const SbVec3f &center, SbBool transformCenter);
  void setCenter(const SbVec3d &center, SbBool transformCenter);

  SbBool isCenterSet() const;
  void resetCenter();

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  // Initiates action on graph
  virtual void beginTraversal(SoNode *node);

 private:
  SbXfBox3f box;             // Bounding box
  SbVec3f center;            // Center point
  SbBool cameraSpace;        // Bounding box in camera space?
  const SoPath *resetPath;   // path to reset transform
  SbBool resetBefore;        // reset before or after?
  ResetType resetWhat;       // which things get reset?
  SbViewportRegion vpRegion; // Current viewport region
  SbBool centerSet;          // setCenter() called?

  // check to see if the reset parameters are met, if so, do the
  // reset transform and reset bbox
  void checkReset(SbBool resetBefore);

};

#endif /* _SO_GET_BOUNDING_BOX_ACTION_ */

