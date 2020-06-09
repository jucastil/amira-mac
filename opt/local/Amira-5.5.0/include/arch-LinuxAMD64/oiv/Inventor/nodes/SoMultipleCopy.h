/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Thad Beier (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_MULTIPLE_COPY_
#define  _SO_MULTIPLE_COPY_

#include <Inventor/fields/SoMFMatrix.h>
#include <Inventor/nodes/SoGroup.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoMultipleCopy
//
//  MultipleCopy group node: children are traversed for each matrix in
//  the multiple-value "matrix" field, after transforming the current
//  model matrix by that matrix. State is saved before traversing all
//  children each time and restored afterwards.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Group node that traverses multiple times, applying matrices.
 * 
 * @ingroup GroupNodes
 * 
 * @DESCRIPTION
 *   This group node traverses its children, in order, several times, applying a
 *   different matrix each time. The matrices are stored in the multiple-value
 *   #matrix field. Each matrix is concatenated to the current transformation
 *   matrix, and all of the children are traversed. This allows the user to put
 *   multiple copies of the same data in different locations easily and
 *   efficiently.
 *   
 *   Traversing the <B>N</B>th child sets the current switch value to @B N @b, for
 *   use with inherited switch values (see SoSwitch).
 * 
 * @FILE_FORMAT_DEFAULT
 *    MultipleCopy {
 *    @TABLE_FILE_FORMAT
 *       @TR matrix         @TD 1 0 0 0
 *       @TR                @TD 0 1 0 0
 *       @TR                @TD 0 0 1 0
 *       @TR                @TD 0 0 0 1
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction @BR
 *        Traverses all children for each matrix, saving and restoring state before and
 *        after each traversal. Sets: SoSwitchElement
 * 
 *    SoSearchAction @BR
 *        Traverses all children once, setting the inherited switch value to
 *        SO_SWITCH_ALL first.
 * 
 * 
 * @SEE_ALSO
 *    SoArray,
 *    SoSwitch
 * 
 * 
 */ 

class INVENTOR_API SoMultipleCopy : public SoGroup {

  SO_NODE_HEADER(SoMultipleCopy);

 public:
  // Fields
  /**
   * Set of matrices to apply to children.
   * 
   */
  SoMFMatrix          matrix;

  /**
   * Creates a multiple copy node with default settings.
   */
  SoMultipleCopy();

  // Overrides default method on SoNode to return FALSE since these
  // nodes are effectively separators
  virtual SbBool      affectsState() const;

 SoEXTENDER public:
  // Implement actions
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        handleEvent(SoHandleEventAction *action);
  virtual void        getMatrix(SoGetMatrixAction *action);
  virtual void        search(SoSearchAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoMultipleCopy();
};

#endif /* _SO_MULTIPLE_COPY_ */

