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


#ifndef  _SO_VRMLSWITCH_
#define  _SO_VRMLSWITCH_

#include <Inventor/VRMLnodes/SoVRMLParent.h>
#include <Inventor/misc/SoChildList.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoMFNode.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLSwitch
//
//  Switch group node: traverses only the child indicated by integer
//  "whichChild" field. If this field is SO_SWITCH_NONE, no children
//  are traversed, while SO_SWITCH_INHERIT means inherit the index
//  from the current switch state, doing a modulo operation to make
//  sure the child index is within the correct bounds of the switch
//  node.
//
//////////////////////////////////////////////////////////////////////////////

#define SO_SWITCH_NONE          (-1)    /* Don't traverse any children  */
#define SO_SWITCH_INHERIT       (-2)    /* Inherit value from state     */
#define SO_SWITCH_ALL           (-3)    /* Traverse all children        */

/**
 * @VSGEXT Group node that traverses one chosen child.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 * 
 *   @B NOTE:@b This field is not compatible with VRML97.
 *   If you specify a non-default value for this field, when this node
 *   is written to a VRML file, the file will contain this incompatible
 *   field and standard VRML97 file readers will not be able to read it.
 *   See the VRML97 Specification, below.
 * 
 * @VRML2_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the VRML97 specification that are not
 *   present in this help file. The complete VRML97 spec is available at
 *   @B http://www.web3d.org @b.
 *   
 *   The SoVRMLSwitch grouping node traverses zero or one of the nodes specified in
 *   the #choice field.
 *   
 *   See the "Concepts - Grouping and Children Nodes" section which describes
 *   "children nodes" for a details on the types of nodes that are legal values for
 *   #choice.
 *   
 *   The #whichChoice field specifies the index of the child to traverse, where
 *   the first child has index 0. If #whichChoice is less than zero or greater
 *   than the number of nodes in the #choice field then nothing is chosen. 
 *
 *   The #bboxCenter and #bboxSize fields specify a bounding box that
 *   encloses the SoVRMLSwitch's children. This is a hint that may be used for
 *   optimization purposes. If the specified bounding box is smaller than the actual
 *   bounding box of the children at any time, then the results are undefined. A
 *   default #bboxSize value, (-1 -1 -1), implies that the bounding box is not
 *   specified and if needed must be calculated by the browser. See "Concepts -
 *   Bounding Boxes" for a description of the #bboxCenter and #bboxSize
 *   fields.
 *   
 *   Note that all nodes under an SoVRMLSwitch continue to receive and send events
 *   regardless of the value of #whichChoice.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLSwitch {
 *    @TABLE_FILE_FORMAT
 *       @TR choice       @TD [] // VRML97
 *       @TR children     @TD [] // X3D
 *       @TR whichChoice  @TD -1
 *       @TR metadata     @TD NULL
 *       @TR bboxCenter   @TD 0 0 0
 *       @TR bboxSize     @TD -1 -1 -1
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoHandleEventAction,  SoRayPickAction,  SoGetMatrixAction,  SoSearchAction,  SoWriteAction  @BR
 *      Sets: SoSwitchElement
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN 
 *       @TR   SoMFNode    @TD   addChildren // X3D only
 *       @TR   SoMFNode    @TD   removeChildren // X3D only
 *       @TR   SoMFNode    @TD   set_choice  // VRML97 only
 *       @TR   SoMFNode    @TD   set_children  // X3D only
 *       @TR   SoSFInt32   @TD   set_whichChoice
 *       @TR   SoSFNode    @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoMFNode    @TD   choice_changed // VRML97 only
 *       @TR   SoMFNode    @TD   children_changed // X3D only
 *       @TR   SoSFInt32   @TD   whichChoice_changed
 *       @TR   SoSFNode    @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLSwitch : public SoVRMLParent {

  SO_NODE_HEADER(SoVRMLSwitch);

 public:
  // Fields
  /**
   * Nodes to chose from (VRML97 only).
   *
   * In X3D, the list of nodes is specified using the children field 
   * (inherited from SoVRMLParent). 
   *
   * @B NOTE:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when this node
   * is written to a VRML file, the file will contain this incompatible
   * field and standard VRML97 file readers will not be able to read it.
   * 
   */
  SoMFNode            choice;
  /**
   * Specifies the index of the child to traverse.
   * 
   */
  SoSFInt32           whichChoice;
  /**
   * Constructor.
   */
  SoVRMLSwitch();

  /**
   * Constructor that takes approximate number of choices
   */
  SoVRMLSwitch(int nChoices);

  /**
   * Overrides method in SoNode to return FALSE if there is no selected child or the
   * selected child does not affect the state.
   */
  virtual SbBool      affectsState() const;

  /**
   * Adds a choice/child as last one in group
   */
  void                addChoice(SoNode *choice1);

  /**
   * Adds a choice/child so that it becomes the one with the given index
   */
  void                insertChoice(SoNode *choice1, int newLevelIndex);

#ifdef OIV_NET_DOC
  /**
  * Returns reference to nth choice/child node
  */

#else
  /**
  * Returns pointer to nth choice/child node
  */

#endif //OIV_NET_DOC
  SoNode *            getChoice(int index) const;

  /**
   * Finds index of given choice/child within group
   */
  int                 findChoice(const SoNode *choice1) const;

  /**
   * Returns number of choices/children
   */
  int                 getNumChoices() const;

  /**
   * Removes choice/child with given index from group
   */
  void                removeChoice(int index);

  /**
   * Removes first instance of given choice/child from group.
   */
  void                removeChoice(SoNode *choice1)
    { removeChoice(findChoice(choice1)); }

  /**
   * Removes all choices/children from group.
   */
  void                removeAllChoices();

  /**
   * Replaces choice with given index with new choice/child.
   */
  void                replaceChoice(int index, SoNode *newChoice);

  /**
   * Replaces first instance of given choice/child with new choice/child
   */
  void                replaceChoice(SoNode *oldChoice, SoNode *newChoice)
    { replaceChoice(findChoice(oldChoice), newChoice); }

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

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  // Adds a child as last one in group
  void                addChild(SoNode *child);

  // Adds a child so that it becomes the one with the given index
  void                insertChild(SoNode *child, int newChildIndex);

  // Returns pointer to nth child node
  SoNode *            getChild(int index) const;

  // Finds index of given child within group
  int                 findChild(const SoNode *child) const;

  // Returns number of children
  int                 getNumChildren() const;

  // Removes child with given index from group
  void                removeChild(int index);

  // Removes first instance of given child from group
  void                removeChild(SoNode *child)
    { removeChild(findChild(child)); }

  // Removes all children from group
  void                removeAllChildren();

  // Replaces child with given index with new child
  void                replaceChild(int index, SoNode *newChild);

  // Replaces first instance of given child with new child
  void                replaceChild(SoNode *oldChild, SoNode *newChild)
    { replaceChild(findChild(oldChild), newChild); }

  // Copies the contents of the given node into this instance
  virtual void        copyContents(const SoFieldContainer *fromFC,
                                   SbBool copyConnections);
  
 protected:
  SoMFNode  addChildren;     //eventIn
  SoMFNode  removeChildren;  //eventIn
  void      processAddChildren();
  void      processRemoveChildren();

  virtual ~SoVRMLSwitch();
  virtual void        notify(SoNotList *);
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);
  int internalSetValue;

 private:

  // Traverses correct child. If matchIndex >=0, child index must match
  void                doChild(SoAction *action, int matchIndex = -1);
};

#endif /* _SO_VRMLSWITCH_ */

