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


#ifndef  _SO_ARRAY_
#define  _SO_ARRAY_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoGroup.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoArray
//
//  Array group node: creates an IxJxK array. Each element in the
//  array is drawn by traversing all of the children of this node,
//  saving and restoring state before and after each element. I, J,
//  and K are given by the numElements1, numElements2, and
//  numElements3 fields. The 3D vector separating the centers of
//  adjacent elements in each of the three directions is given by
//  separation1, separation2, and separation3. The origin field
//  indicates whether the array is positioned with the current
//  object-space origin at the center of the first element, the last
//  element, or at the center of all elements.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Group node that creates a regular IxJxK array of copies of its children.
 * 
 * @ingroup GroupNodes
 * 
 * @DESCRIPTION
 *   This group node traverses its children, in order, several times, creating a
 *   regular 3D array of copies of them. The number of copies in each of the three
 *   directions is specified by fields, as are the vectors used to separate the
 *   copies in each of the three dimensions.
 *   
 *   For example, an SoArray node can be used to create a 2x3x4 array of copies of its
 *   children, where the separation vectors between adjacent copies in the three
 *   array dimensions are (1,2,3), (-4,-5,-6), and (7,8,9), respectively. The base
 *   point of the array can be set to one of several values, as described in the
 *   #origin field.
 *   
 *   Copies are traversed so that the first dimension cycles most quickly, followed by
 *   the second, and then the third. This order is important because SoArray sets the
 *   current switch value to N before traversing the children for the Nth time (for
 *   use with inherited switch values - see SoSwitch).
 * 
 * @FILE_FORMAT_DEFAULT
 *    Array {
 *    @TABLE_FILE_FORMAT
 *       @TR numElements1   @TD 1
 *       @TR numElements2   @TD 1
 *       @TR numElements3   @TD 1
 *       @TR separation1    @TD 1 0 0
 *       @TR separation2    @TD 0 1 0
 *       @TR separation3    @TD 0 0 1
 *       @TR origin         @TD FIRST
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction @BR
 *        Traverses all children for each array element, saving and restoring state
 *        before and after each traversal. Sets: SoSwitchElement
 * 
 *    SoSearchAction @BR
 *        Traverses all children once, setting the inherited switch value to
 *        @B SO_SWITCH_ALL @b first.
 * 
 * 
 * @SEE_ALSO
 *    SoMultipleCopy,
 *    SoSwitch
 * 
 * 
 */ 

class INVENTOR_API SoArray : public SoGroup {

  SO_NODE_HEADER(SoArray);

 public:

  // Fields
  /**
   * Number of elements in the 1st dimension
   */
  SoSFShort           numElements1;

  /**
   * Number of elements in the 2nd dimension
   */
  SoSFShort           numElements2;

  /**
   * Number of elements in the 3rd dimension
   */
  SoSFShort           numElements3;

  /**
   * Separation vector in the 1st dimension
   */
  SoSFVec3f           separation1;

  /**
   * Separation vector in the 2nd dimension
   */
  SoSFVec3f           separation2;    

  /**
   * Separation vector in the 3rd dimension
   */
  SoSFVec3f           separation3;

  /** Array origin */
  enum Origin {
    /**
     *  First copy is rendered at the current local origin; all other copies are
     * distributed relative to it 
     */
    FIRST,
    /**
     *  Copies are distributed relative to the center of the array 
     */
    CENTER,
    /**
     *  Last copy is rendered at the current local origin; all other copies are
     * distributed relative to it 
     */
    LAST
  };

  /**
   * Defines the base point from which copies are distributed.
   * Use enum #Origin.  Default is FIRST.
   */
  SoSFEnum            origin;

  /**
   * Creates an array node with default settings.
   */
  SoArray();

  /**
   * Overrides default method on SoNode to return FALSE since arrays
   * are effectively separators
   */
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
  virtual ~SoArray();
};

#endif /* _SO_ARRAY_ */

