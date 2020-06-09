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


#ifndef  _SO_VRMLPARENT_
#define  _SO_VRMLPARENT_

#include <Inventor/nodes/SoGroup.h>
#include <Inventor/misc/SoChildList.h>
#include <Inventor/fields/SoMFNode.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFVec3f.h>
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLParent
//
//  Abstract base class VRMLParent node: 
//
//////////////////////////////////////////////////////////////////////////////


/**
 * @VSGEXT Abstract base class for all VRML grouping nodes that have children.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   The SoVRMLParent node is the abstract base class for all VRML grouping nodes
 *   that have children.
 * 
 * @FILE_FORMAT_DEFAULT
 *   This is an abstract class. See the reference page of a derived class for the
 *   format and default values.
 *
 * @ACTION_BEHAVIOR
 *      SoSearchAction  @BR
 * 
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN
 *       @TR   SoMFNode    @TD   addChildren
 *       @TR   SoMFNode    @TD   removeChildren
 *       @TR   SoMFNode    @TD   set_children
 *       @TR   SoSFNode    @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoMFNode   @TD   children_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLParent : public SoGroup {

  SO_NODE_ABSTRACT_HEADER(SoVRMLParent);

 public:
 /**
  * Field that contains a list of children nodes.
  *
  */
  SoMFNode  children;
 /**
   * Specifies the metadata node
   * 
   */
  SoSFNode            metadata;
 /**
  * The #bboxCenter and #bboxSize fields specify a bounding box that
  * encloses the SoVRMLParent's children. This is a hint that may be used for
  * optimization purposes. If the specified bounding box is smaller than
  * the actual bounding box of the children at any time, then the results 
  * are undefined. A default #bboxSize value, (-1 -1 -1), implies that
  * the bounding box is not specified.
  * 
  */
  SoSFVec3f bboxCenter;
  /**
  * The #bboxCenter and #bboxSize fields specify a bounding box that
  * encloses the SoVRMLParents's children. See #bboxCenter for details.
  */
  SoSFVec3f bboxSize;


  // Overrides default method on SoNode
  virtual SbBool     affectsState() const;

  /**
   * Adds a child as last one in group
   */
  virtual void                addChild(SoNode *child);

  /**
   * Adds a child so that it becomes the one with the given index
   */
  virtual void                insertChild(SoNode *child, int newChildIndex);

#ifdef OIV_NET_DOC
  /**
  * Returns reference to nth child node
  */

#else
  /**
  * Returns pointer to nth child node
  */

#endif //OIV_NET_DOC
  virtual SoNode *            getChild(int index) const;

  /**
   * Finds index of given child within group
   */
  virtual int                 findChild(const SoNode *child) const;

  /**
   * Returns number of children
   */
  virtual int                 getNumChildren() const;

  /**
   * Removes child with given index from group
   */
  virtual void                removeChild(int index);

  /**
   * Removes first instance of given child from group
   */
  virtual void                removeChild(SoNode *child)
    { removeChild(findChild(child)); }

  /**
   * Removes all children from group
   */
  virtual void                removeAllChildren();

  /**
   * Replaces child with given index with new child
   */
  virtual void                replaceChild(int index, SoNode *newChild);

  /**
   * Replaces first instance of given child with new child
   */
  virtual void                replaceChild(SoNode *oldChild, SoNode *newChild)
    { replaceChild(findChild(oldChild), newChild); }

  // Returns pointer to children
  virtual SoChildList *getChildren() const;

 SoEXTENDER public:
  // Implement actions
  virtual void        search(SoSearchAction *action);
  virtual void        doAction(SoAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 
  virtual SbBool      validateNewFieldValue(SoField *pField,
                                            void *newValue);
 
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

  // Copies the contents of the given node into this instance
  virtual void        copyContents(const SoFieldContainer *fromFC,
                                   SbBool copyConnections);

 protected:
  SoMFNode  addChildren;     //eventIn
  SoMFNode  removeChildren;  //eventIn
  void      processAddChildren();
  void      processRemoveChildren();

  SoVRMLParent();
  // Constructor that takes approximate number of children
  SoVRMLParent(int nChildren);
  virtual ~SoVRMLParent();

  virtual void        notify(SoNotList *);

  // Reads stuff into instance of SoVRMLParent. Returns FALSE on error
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);
  
  int internalSetValue;

};

#endif /* _SO_VRMLPARENT_ */

