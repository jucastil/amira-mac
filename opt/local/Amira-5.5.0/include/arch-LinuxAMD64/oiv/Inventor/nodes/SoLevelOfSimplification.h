/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_LEVEL_OF_SIMPLIFICATION_
#define  _SO_LEVEL_OF_SIMPLIFICATION_

#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/nodes/SoLOD.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoLevelOfSimplification
//
//  Level-of-simplfication group node. The children of this node typically
//  represent the same object or objects at varying levels of detail,
//  from highest detail to lowest.  
//
//  The group node is derived from SoLOD, and adds a new field
//  "percentages", which can be used to specify how complex
//  a representation each child is.  The first child is assumed
//  to be the 1.0 representation, and then each value in the
//  "percentages" field specifies what percentage reduction
//  this representation is.
//
//  If a full model has 1000 triangles, and there are two lower
//  levels of detail: one with 500 triangles and the other with 250,
//  then the percentages field should be [0.5, 0.25]
//
//  This node will react to the Decimation element, forcing this
//  node to choose the representation with a certain percentage
//  detail. 
//  If DecimationType is LOWEST or HIGHEST, this node will choose
//  the lowest or highest child.
//
//  If DecimationType is PERCENTAGE, and DecimationValue "D",
//  this node will choose Child "i" such that:
//        percentages[i-1] <= D < percentages[i]
//
//  If DeciamtionType is AUTOMATIC, then the child is chosen 
//  based on the range value in the usual SoLOD manner, but
//  no child greater than the value of the DecimationPercentage
//  element will be chosen.  
//
//  You should specify N percentages for N+1 children. 
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Level-of-detail switching node designed for grouping simplified versions of the
 * same shape.
 * 
 * @ingroup GroupNodes LMV
 * 
 * @DESCRIPTION
 *   This group node is used to group the results of simplifying a shape, such that
 *   every child represents the same model but with a different number of primitives.
 *   Since it is derived from SoLOD, it can behave as a distance-based
 *   level-of-detail node; however, it also responds to the decimation percentage
 *   element. It records what percentage decimation each child is, and then chooses
 *   the appropriate child based on the DecimationPercentage and DecimationType
 *   elements.
 *   
 *   You should specify N percentages for N+1 children. If the DecimationType is
 *   HIGHEST or LOWEST, then the @B LevelOfSimplification @b node will automatically
 *   choose the first or last child, respectively. If the DecimationType is
 *   PERCENTAGE, then the node will choose child "i" based on the decimation
 *   percentage element value such that:
 *   
 *   <PRE> 
 *    percentages[i-1] <= DecimationPercentage < percentages[i]
 *    </PRE>
 *    If the DecimationType is AUTOMATIC, then the child is chosen
 *   based on the range value in the usual SoLOD manner, but no child greater than
 *   the value of the DecimationPercentage element will be chosen.
 *   
 *   This node also has a field for recording how many triangles the full detail child
 *   contains. This allows this node to answer an SoGetPrimitiveCountAction
 *   without traversing its children. This is a benefit when some children contain
 *   @B WWWInline @b, a common occurrence. If the children contain some
 *   non-triangle primitives, then the field should be -1 which will force the node
 *   to traverse its children during SoGetPrimitiveCountAction.
 * 
 * @FILE_FORMAT_DEFAULT
 *    LevelOfSimplification {
 *    @TABLE_FILE_FORMAT
 *       @TR percentages    @TD []
 *       @TR numTriangles   @TD -1
 *       @TR center         @TD 0 0 0
 *       @TR range          @TD [ ]
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoRayPickAction,  SoCallbackAction @BR
 *        Only the child with the appropriate level of detail is traversed.
 * 
 *    SoGetPrimitiveCountAction @BR
 *        A child is chosen in the same way as in GLRender. If the #numTriangles
 *        field is greater than 0, the percentage value for this child is multiplied by
 *        the #numTriangles value and this value is added to the PrimitiveCount
 *        without traversing the child. If #numTriangles is less than or equal to 0,
 *        then the child is traversed to get the count.
 *        
 *        Other actions
 *        
 *        Implemented as for SoGroup
 * 
 * 
 * @SEE_ALSO
 *    SoGetPrimitiveCountAction,
 *    SoLOD,
 *    SoOctreeOrdering,
 *    SoRenderList,
 *    SoValueOrdering
 * 
 * 
 */ 

class INVENTOR_API SoLevelOfSimplification : public SoLOD {

  SO_NODE_HEADER(SoLevelOfSimplification);

 public:
  // Fields
  /**
   * Percentage decimation for each child. Should be numbers between 0.0 and 1.0,
   * with 1.0 representing full detail and 0.0 representing bounding box detail.
   * 
   */
  SoMFFloat           percentages;
  /**
   * Number of triangles in highest (1.0) case. Can be -1 if unknown or if children
   * contain primitives other than triangles.
   * 
   */
  SoSFInt32           numTriangles;

  /**
   * Creates level-of-simplification node with default settings.
   */
  SoLevelOfSimplification();

  /**
   * Constructor that takes approximate number of children.
   */
  SoLevelOfSimplification(int nChildren);


 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 SoEXTENDER public:
  // Implement actions:
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

   
 protected:
  virtual ~SoLevelOfSimplification();

  virtual int         whichToTraverse(SoAction *);
};

#endif /* _SO_LEVEL_OF_SIMPLIFICATION_ */

