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


#ifndef  _SO_GROUP_
#define  _SO_GROUP_

class SoChildList;
#include <Inventor/nodes/SoNode.h>
#include <Inventor/sensors/SoDataSensor.h>  // for ChangeType
#include <Inventor/fields/SoSFBool.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGroup
//
//  Base group node: all children are traversed.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Base class for all group nodes.
 * 
 * @ingroup GroupNodes
 * 
 * @DESCRIPTION
 *   This node defines the base class for all group nodes. SoGroup is a node that
 *   contains an ordered list of child nodes. The ordering of the child nodes
 *   represents the traversal order for all operations (for example, rendering,
 *   picking, and so on). This node is simply a container for the child nodes and
 *   does not alter the traversal state in any way. During traversal, state
 *   accumulated for a child is passed on to each successive child and then to the
 *   parents of the group (SoGroup does not push or pop traversal state as
 *   SoSeparator does).
 * 
 * @FILE_FORMAT_DEFAULT
 *    Group {
 *    @TABLE_FILE_FORMAT
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoHandleEventAction,  SoRayPickAction @BR
 *        Traverses each child in order.
 * 
 *    SoGetMatrixAction @BR
 *        Does nothing unless the group is in the middle of the path chain the action is
 *        being applied to. If so, the children up to and including the next node in the
 *        chain are traversed.
 * 
 *    SoSearchAction @BR
 *        If searching for group nodes, compares with this group. Otherwise, continues to
 *        search children.
 * 
 *    SoWriteAction @BR
 *        Writes out the group node. This method also deals with any field data
 *        associated with the group node. As a result, this method is used for most
 *        subclasses of SoGroup as well.
 * 
 * 
 * @SEE_ALSO
 *    SoArray,
 *    SoLevelOfDetail,
 *    SoMultipleCopy,
 *    SoPathSwitch,
 *    SoSeparator,
 *    SoSwitch
 * 
 * 
 */ 

class INVENTOR_API SoGroup : public SoNode {
  
  SO_NODE_HEADER(SoGroup);
  
 public:
  /**
   * Whether to ignore this node during bounding box traversal. Default is FALSE.
   */
  SoSFBool boundingBoxIgnoring;

  /**
   * Creates an empty group node.
   */
  SoGroup();

#ifdef OIV_NET_DOC
  /**
  * Constructor that takes approximate number of children. Space is allocated for
  * references to the children, but the group does not contain any actual child nodes.
  */

#else
  /**
  * Constructor that takes approximate number of children. Space is allocated for
  * pointers to the children, but the group does not contain any actual child nodes.
  */

#endif //OIV_NET_DOC
  SoGroup(int nChildren);

  /**
   * Adds a child as last one in group.
   * [OIVJAVA-WRAPPER HELPER_BEGIN{onAddChild(child)}]
   */
  virtual void addChild(SoNode *child);

  /**
   * Adds a child so that it becomes the one with the given index.
   * [OIVJAVA-WRAPPER HELPER_BEGIN{onInsertChild(child, newChildIndex)}]
   */
  virtual void insertChild(SoNode *child, int newChildIndex);

#ifdef OIV_NET_DOC
  /**
  * Returns reference to child node with the given index.
  */

#else
  /**
  * Returns pointer to child node with the given index.
  */

#endif //OIV_NET_DOC
  virtual SoNode *getChild(int index) const;

  /**
   * Finds index of given child within group. Returns -1 if not found.
   */
  virtual int findChild(const SoNode *child) const;

  /**
   * Returns number of children.
   */
  virtual int getNumChildren() const;

  /**
   * Removes child with given index from group.
   * [OIVJAVA-WRAPPER HELPER_BEGIN{onRemoveChild(index)}]
   */
  virtual void removeChild(int index);

  /**
   * Removes first instance of given child from group.
   * [OIVJAVA-WRAPPER HELPER_BEGIN{onRemoveChild(child)}]
   */
  virtual void removeChild(SoNode *child)
    { removeChild(findChild(child)); }

  /**
   * Removes all children from group.
   * [OIVJAVA-WRAPPER HELPER_BEGIN{onRemoveAllChildren()}]
   */
  virtual void removeAllChildren();

  /**
   * Replaces child with given index with new child.
   * [OIVJAVA-WRAPPER HELPER_BEGIN{onReplaceChild(index,newChild)}]
   */
  virtual void replaceChild(int index, SoNode *newChild);

  /**
   * Replaces first instance of given child with new child.
   * [OIVJAVA-WRAPPER HELPER_BEGIN{onReplaceChild(oldChild,newChild)}]
   */
  virtual void replaceChild(SoNode *oldChild, SoNode *newChild)
    { replaceChild(findChild(oldChild), newChild); }

 SoEXTENDER public:

  /** 
   * Used by BoundingBoxAction to known if bounding box computation should 
   * be ignored or not.
   * By default the returned value is given by boundingBoxIgnoring field.
   */
  inline virtual SbBool isBoundingBoxIgnoring() const
  { return boundingBoxIgnoring.getValue(); }

  // Implement actions
  virtual void doAction(SoAction *action);
  virtual void callback(SoCallbackAction *action);
  virtual void GLRender(SoGLRenderAction *action);
  virtual void getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void getMatrix(SoGetMatrixAction *action);
  virtual void handleEvent(SoHandleEventAction *action);
  virtual void pick(SoPickAction *action);
  virtual void search(SoSearchAction *action);
  virtual void write(SoWriteAction *action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  // Returns pointer to children
  virtual SoChildList *getChildren() const;

  // Internal child management following inheritance of classes.
  virtual void internalRemoveChild( int index )                          { removeChild(index); }
  virtual void internalRemoveChild( SoNode *child  )                     { removeChild(findChild(child)); }
  virtual void internalRemoveAllChildren()                               { removeAllChildren(); }
  virtual void internalAddChild( SoNode *child )                         { addChild(child); }
  virtual int internalFindChild( const SoNode *child ) const             { return findChild(child); }
  virtual void internalInsertChild( SoNode *child, int newChildIndex )   { insertChild(child, newChildIndex); }
  virtual SoNode *internalGetChild( int index) const                     { return getChild(index); }
  virtual void internalReplaceChild( int index, SoNode *newChild)        { replaceChild(index, newChild); }
  virtual void internalReplaceChild( SoNode *oldChild, SoNode *newChild) { replaceChild(oldChild,newChild); }
  
  virtual bool isGroup() { return true; }
  
  // Copies the contents of the given node into this instance
  virtual void copyContents(const SoFieldContainer *fromFC, SbBool copyConnections);

 protected:
  SoChildList *children;
  
  // Reads stuff into instance of SoGroup. Returns FALSE on error
  virtual SbBool readInstance(SoInput *in, unsigned short flags);
  
  // Reads just the children into instance of SoGroup. Returns FALSE on error
  virtual SbBool readChildren(SoInput *in);
  
  virtual ~SoGroup();
  
  void commonConstructor();

  inline virtual SoNode::SoNotificationInfo * getNotificationInfo() const
  { return const_cast<SoNotificationInfo*>(&m_notificationInfo); }

  private:
    SoNode::SoNotificationInfo m_notificationInfo;

};


#endif /* _SO_GROUP_ */

