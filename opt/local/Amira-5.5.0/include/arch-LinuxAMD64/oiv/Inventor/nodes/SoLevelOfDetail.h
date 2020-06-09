/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_LEVEL_OF_DETAIL_
#define  _SO_LEVEL_OF_DETAIL_

#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/nodes/SoGroup.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoLevelOfDetail
//
//  Level-of-detail group node. The children of this node typically
//  represent the same object or objects at varying levels of detail,
//  from highest detail to lowest. The size of the objects when
//  projected into the viewport is used to determine which version to
//  use (i.e., which child to traverse).
//
//  The size is computed as the area of the screen rectangle enclosing
//  the projection of the 3D bounding box that encloses all of the
//  children. When rendering, this size is compared to the values in
//  the screenArea field. If the size is greater than the first value,
//  child 0 is traversed. If it is smaller than the first, but greater
//  than the second, child 1 is traversed, and so on. If there are
//  fewer children than are required by this rule, the last child is
//  traversed. The screenArea field contains just 0 by default, so the
//  first child is always traversed.
//
//  The size calculation takes the current complexity into account. If
//  the complexity is 0 or is of type BOUNDING_BOX, the last child is
//  always traversed. If the complexity is less than .5, the computed
//  size is scaled down appropriately to use (possibly) a less
//  detailed representation. If the complexity is greater than .5, the
//  size is scaled up. At complexity 1, the first child is always used.
//
//  Picking and the callback action use the same traversal rules as
//  rendering. Bounding boxes are computed to enclose all children (as
//  is needed to compute the projected size). All other actions are
//  implemented as for SoGroup, except that SoLevelOfDetail
//  saves/restores state (like a separator) when applying any action.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Level-of-detail switching group node.
 * 
 * @ingroup GroupNodes
 * 
 * @DESCRIPTION
 *   The children of this node typically represent the same object or objects at
 *   varying levels of detail, from highest detail to lowest. The size of the objects
 *   when projected into the viewport is used to determine which version to use
 *   (i.e., which child to traverse).
 *   
 *   The size is computed as the area of the screen rectangle enclosing the projection
 *   of the 3D bounding box that encloses all of the children. When rendering, this
 *   size is compared to the values in the #screenArea field. If the size is
 *   greater than the first value, child 0 is traversed. If it is smaller than the
 *   first, but greater than the second, child 1 is traversed, and so on. If there
 *   are fewer children than are required by this rule, the last child is traversed.
 *   The #screenArea field contains just 0 by default, so the first child is
 *   always traversed.
 *   
 *   The size calculation takes the current complexity into account. If the complexity
 *   is 0 or is of type BOUNDING_BOX, the last child is always traversed. If the
 *   complexity is less than .5, the computed size is scaled down appropriately to
 *   use (possibly) a less detailed representation. If the complexity is greater than
 *   .5, the size is scaled up. At complexity 1, the first child is always used.
 *   
 *   Note that the SoLOD node is similar to SoLevelOfDetail, except the switching
 *   between levels in the SoLOD node is based on distance from the camera, which is
 *   faster than using screen area.
 * 
 * @FILE_FORMAT_DEFAULT
 *    LevelOfDetail {
 *    @TABLE_FILE_FORMAT
 *       @TR screenArea   @TD 0
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoRayPickAction,  SoCallbackAction @BR
 *        Only the child with the appropriate level of detail is traversed.
 * 
 *    SoGetBoundingBoxAction @BR
 *        The box that encloses all children is computed. (This is the box that is needed
 *        to compute the projected size.)
 *        
 *        @B Other actions @b
 *        
 *        All implemented as for SoGroup.
 * 
 * 
 * @SEE_ALSO
 *    SoLOD,
 *    SoComplexity,
 *    SoSwitch,
 *    SoGroup
 * 
 * 
 */ 

class INVENTOR_API SoLevelOfDetail : public SoGroup {

  SO_NODE_HEADER(SoLevelOfDetail);

 public:
  // Fields
  /**
   * Areas to use for comparison
   * 
   */
  SoMFFloat           screenArea;

  /**
   * Creates a level-of-detail node with default settings.
   */
  SoLevelOfDetail();

  /**
   * Constructor that takes approximate number of children.
   */
  SoLevelOfDetail(int nChildren);

 SoEXTENDER public:
  // Implement actions:
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        rayPick(SoRayPickAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoLevelOfDetail();

 private:
  // This action is used to compute the screen-space bbox
  static SoGetBoundingBoxAction      *bboxAction;
};

#endif /* _SO_LEVEL_OF_DETAIL_ */

