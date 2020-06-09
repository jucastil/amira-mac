/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_LOD_
#define  _SO_LOD_

#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoGroup.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoLOD
//
//  Level-of-detail group node. The children of this node typically
//  represent the same object or objects at varying levels of detail,
//  from highest detail to lowest.  The world-space distance of the
//  eye from the transformed center of the LOD is computed, and one
//  child is drawn, based on the values in the ranges field.
//
//  More precisely, if the distance from the eyepoint to the
//  transformed center is D and the ranges array contains LAST_RANGE+1
//  values (numbered 0...LAST_RANGE), then:
//
//  D < ranges[0]  : Child 0 is drawn
//  ranges[i-1] < D < ranges[i] : Child i is drawn
//  D > ranges[LAST_RANGE] : Child LAST_RANGE+1 is drawn
//
//  So, you should specify N ranges and N+1 children.  If you specify
//  too few children, the last child will be used for the extra
//  ranges.  If you specify too few ranges, the extra children will
//  never be used.
//
//  Add an SoInfo node as a child if you want a level of detail
//  that doesn't draw anything.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Distance-based level-of-detail switching group node.
 * 
 * @ingroup GroupNodes VRML1
 * 
 * @DESCRIPTION
 *   This group node is used to allow applications to switch between various
 *   representations of objects automatically. The children of this node typically
 *   represent the same object or objects at varying levels of detail, from highest
 *   detail to lowest. The distance from the world-space eye point to the transformed
 *   center of the LOD is computed, and one child is drawn, based on the values in
 *   the ranges field.
 *   
 *   More precisely, if the distance from the world-space eyepoint to the transformed
 *   center is D and the ranges array contains LAST_RANGE+1 values (numbered
 *   0...LAST_RANGE), then:
 *   
 *   <PRE> 
 *    if D < ranges[0] : Child 0 is drawn
 *    else if ranges[i-1] < D < ranges[i] : Child i is drawn
 *    else if D > ranges[LAST_RANGE] : Child LAST_RANGE+1 is drawn
 *    </PRE>
 *    Thus, N ranges and N+1 children should be specified. If you specify too
 *   few children, the last child will be used for the extra ranges. If you specify
 *   too few ranges, the extra children will never be used.
 *   
 *   It is often useful to define the lowest detail child to be an SoInfo node. This
 *   causes the object to completely disappear if it is far enough away from the
 *   eyepoint. Defining the highest detail child to be an SoInfo node can also be
 *   useful if you want the object to disappear if it gets too close to the eyepoint.
 * 
 * @FILE_FORMAT_DEFAULT
 *    LOD {
 *    @TABLE_FILE_FORMAT
 *       @TR center   @TD 0 0 0
 *       @TR range    @TD [ ]
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoRayPickAction,  SoCallbackAction @BR
 *        Only the child with the appropriate level of detail is traversed.
 *        
 *        @B Other actions @b
 *        
 *        All implemented as for SoGroup.
 * 
 * 
 * @SEE_ALSO
 *    SoSwitch,
 *    SoGroup
 * 
 * 
 */ 

class INVENTOR_API SoLOD : public SoGroup {

  SO_NODE_HEADER(SoLOD);

 public:
  // Fields
  /**
   * World-space distances to use as switching criteria.
   * 
   */
  SoMFFloat           range;
  /**
   * Object-space center of the model.
   * 
   */
  SoSFVec3f           center;

  /**
   * Creates a distance-based level-of-detail node with default settings.
   */
  SoLOD();

  /**
   * Constructor that takes approximate number of children.
   */
  SoLOD(int nChildren);

 SoEXTENDER public:
  // Implement actions:
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        rayPick(SoRayPickAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

  // These methods make render traversal faster by implementing
  // different rendering paths corresponding to different action
  // path codes.
  virtual void        GLRenderBelowPath(SoGLRenderAction *action);
  virtual void        GLRenderInPath(SoGLRenderAction *action);
  virtual void        GLRenderOffPath(SoGLRenderAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoLOD();

  virtual int         whichToTraverse(SoAction *);
};

#endif /* _SO_LOD_ */

