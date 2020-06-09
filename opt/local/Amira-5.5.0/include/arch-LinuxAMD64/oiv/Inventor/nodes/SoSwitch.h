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


#ifndef  _SO_SWITCH_
#define  _SO_SWITCH_

#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/nodes/SoGroup.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoSwitch
//
//  Switch group node: traverses only the child indicated by integer
//  "whichChild" field. If this field is SO_SWITCH_NONE, no children
//  are traversed, while SO_SWITCH_INHERIT means inherit the index
//  from the current switch state, doing a modulo operation to make
//  sure the child index is within the correct bounds of the switch
//  node.
//
//////////////////////////////////////////////////////////////////////////////

/** Possible value of SoSwitch::whichChild : Don't traverse any children        */
#define SO_SWITCH_NONE          (-1)

/** Possible value of SoSwitch::whichChild : Inherit value from state           */
#define SO_SWITCH_INHERIT       (-2)

/** Possible value of SoSwitch::whichChild : Traverse all children              */
#define SO_SWITCH_ALL           (-3)

/**
 * Group node that traverse one chosen child.
 * 
 * @ingroup GroupNodes
 * 
 * @DESCRIPTION
 *   This group node usually traverses only one or none of its children. It
 *   implements an operation similar to the switch statement in C. One can use this
 *   node to switch on and off the effects of some properties or to switch between
 *   different properties.
 *   
 *   The #whichChild field specifies the index of the child to traverse, where
 *   the first child has index 0.
 *   
 *   A value of #SO_SWITCH_NONE (-1, the default) means do not traverse any children. A
 *   value of #SO_SWITCH_INHERIT (-2) allows the index to be inherited from a
 *   previously-encountered SoSwitch node or from certain other nodes (such as
 *   SoArray or SoMultipleCopy) that set the switch value. A value of #SO_SWITCH_ALL
 *   (-3) traverses all children, making the switch behave exactly like a regular
 *   SoGroup.
 * 
 * @FILE_FORMAT_DEFAULT
 *    Switch {
 *    @TABLE_FILE_FORMAT
 *       @TR whichChild   @TD -1
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoGetMatrixAction,  SoHandleEventAction,  SoRayPickAction @BR
 *        Traverses the chosen child or children. Sets: SoSwitchElement
 * 
 *    SoSearchAction @BR
 *        If the action's Searching-All flag is set, always traverses all children.
 *        Otherwise, traverses just the chosen child or children.
 * 
 * 
 * @SEE_ALSO
 *    SoArray,
 *    SoLevelOfDetail,
 *    SoMultipleCopy,
 *    SoPathSwitch
 * 
 * 
 */ 

class INVENTOR_API SoSwitch : public SoGroup {

  SO_NODE_HEADER(SoSwitch);

 public:
  // Fields
  /**
   * Index of the child to traverse, or one of #SO_SWITCH_NONE, #SO_SWITCH_INHERIT, or
   * #SO_SWITCH_ALL.
   * 
   */
  SoSFInt32           whichChild;

  /**
   * Creates a switch node with default settings.
   */
  SoSwitch();

  /**
   * Constructor that takes approximate number of children.
   */
  SoSwitch(int nChildren);

  // Overrides method in SoNode to return FALSE if there is no
  // selected child or the selected child does not affect the state.
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
  virtual void        write(SoWriteAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  virtual void notify(SoNotList *list);

 protected:
  /**
   * Destructor.
   */
  virtual ~SoSwitch();

 private:
  // Traverses correct child. If matchIndex >=0, child index must match
  void                doChild(SoAction *action, int matchIndex = -1);
};

#endif /* _SO_SWITCH_ */

