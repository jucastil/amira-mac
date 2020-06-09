/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul Isaacs (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_NODE_KIT_LIST_PART_
#define  _SO_NODE_KIT_LIST_PART_

#include <Inventor/misc/SoChildList.h>
#include <Inventor/fields/SoSFName.h>
#include <Inventor/fields/SoMFName.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodekits/SoNodekitParts.h>
#include <Inventor/nodekits/SoBaseKit.h>

class SoGroup;

class SoGetMatrixAction;
class SoGLRenderAction;
class SoGetBoundingBoxAction;
class SoHandleEventAction;
class SoSearchAction;
class SoSearchAction;
class SoCallbackAction;

////////////////////////////////////////////////////////////////////
//    Class: SoNodeKitListPart
//
////////////////////////////////////////////////////////////////////

/**
 * Group node with restricted children.
 * 
 * @ingroup nodekits
 * 
 * @DESCRIPTION
 *   This node class is very similar to SoGroup with the exception that it specifies
 *   restrictions on the type of children that it allows. It is used by nodekits to
 *   restrict child types within @B list parts @b (see the reference page for
 *   SoBaseKit).
 *   
 *   By default, any kind of child may be added. Methods of this class allow you to
 *   restrict the type of allowable children, and to lock down the types so that this
 *   type list may no longer be altered.
 *   
 *   Inside the SoNodeKitListPart is a @B container @b node, which in turn contains
 *   the @B children @b. The @B container @b node is a hidden child, and the type
 *   of node used may be set with setContainerType(). In this way, you can
 *   make the nodekitlist behave like a group, a separator, or any other subclass of
 *   group. The @B container @b is not accessible so that the nodekitlist may retain
 *   control over what kinds of children are added.
 * 
 * @FILE_FORMAT_DEFAULT
 *    NodeKitListPart {
 *    @TABLE_FILE_FORMAT
 *       @TR containerTypeName   @TD "Group"
 *       @TR childTypeNames      @TD ""
 *       @TR containerNode       @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoBaseKit,
 *    SoNodeKit,
 *    SoNodeKitDetail,
 *    SoNodeKitPath,
 *    SoNodekitCatalog,
 *    SoSceneKit,
 *    SoSeparatorKit,
 *    SoShapeKit,
 *    SoWrapperKit
 * 
 * 
 */ 

class INVENTOR_API SoNodeKitListPart : public SoNode {

  SO_NODE_HEADER(SoNodeKitListPart);

 public:

  /**
   * Constructor.
   */
  SoNodeKitListPart();

  /**
   * Gets the type of node used as the @B container @b.
   */
  SoType         getContainerType() const;
  /**
   * Sets the type of node used as the @B container @b.
   */
  void           setContainerType( SoType newContainerType );

  /**
   * Returns the permitted child node types. By default, any type of node is
   * permitted, so the list contains one entry of type SoNode.
   */
  const SoTypeList &getChildTypes() const;
  /**
   * Permits the node type typeToAdd as a child. The first time the
   * addChildType() method is called, the default of SoNode is overridden and
   * only the new typeToAdd is permitted. In subsequent calls to
   * addChildType(), the typeToAdd is added to the existing types.
   */
  void             addChildType( SoType typeToAdd );

  /**
   * Returns whether a node of type typeToCheck may be added as a child.
   */
  SbBool        isTypePermitted( SoType typeToCheck ) const;
  /**
   * Returns whether the node child may be added to this list. This will return TRUE
   * if the type of child is one of the permissible child types.
   */
  SbBool        isChildPermitted( const SoNode *child ) const;

  /**
   * Sends a string to the set() method on the container node. This is how you
   * can set the value of a switch node if the container node is an SoSwitch, for
   * example.
   */
  void containerSet( const SbString& fieldDataString );


  /**
   * This function permanently locks the permitted child types and the container type
   * permanently. Calls to setContainerType() and addChildType() will
   * have no effect after this function is called.
   */
  void   lockTypes(); 
  /**
   * Returns whether the permitted child types and the container type are locked
   * (i.e. cannot be changed). See lockTypes()
   */
  SbBool isTypeLocked() const { return areTypesLocked; }

  /**
   * Adds child as last one in nodekit. 
   * This is one of several functions used to edit the children. They parallel those of
   * SoGroup, except that they always check the child types against those which are
   * permissible. See SoGroup for details.
   */
  void                addChild(SoNode *child);
  /**
   * Adds a child so that it becomes the one with the given index.
   * This is one of several functions used to edit the children. They parallel those of
   * SoGroup, except that they always check the child types against those which are
   * permissible. See SoGroup for details.
   */
  void                insertChild(SoNode *child, int childIndex);
#ifdef OIV_NET_DOC
  /**
  * Returns reference to child node with the given index.
  * This is one of several functions used to edit the children. They parallel those of
  * SoGroup, except that they always check the child types against those which are
  * permissible. See SoGroup for details.
  */

#else
  /**
  * Returns pointer to child node with the given index.
  * This is one of several functions used to edit the children. They parallel those of
  * SoGroup, except that they always check the child types against those which are
  * permissible. See SoGroup for details.
  */

#endif //OIV_NET_DOC
  SoNode              *getChild(int index) const;
  /**
   * Finds index of given child within nodekit. Returns -1 if not found.
   * This is one of several functions used to edit the children. They parallel those of
   * SoGroup, except that they always check the child types against those which are
   * permissible. See SoGroup for details.
   */
  int                 findChild(const SoNode *child) const;
  /**
   * Returns the number of children in the nodekit.
   * This is one of several functions used to edit the children. They parallel those of
   * SoGroup, except that they always check the child types against those which are
   * permissible. See SoGroup for details.
   */
  int                 getNumChildren() const;
  /**
   * Removes child with given index from the nodekit.
   * This is one of several functions used to edit the children. They parallel those of
   * SoGroup, except that they always check the child types against those which are
   * permissible. See SoGroup for details.
   */
  void                removeChild(int index);
  /**
   * Removes first instance of given child from nodekit.
   * This is one of several functions used to edit the children. They parallel those of
   * SoGroup, except that they always check the child types against those which are
   * permissible. See SoGroup for details.
   */
  void                removeChild(SoNode *child)
    { removeChild( findChild(child)); }
  /**
   * Replaces child with given index with new child.
   * This is one of several functions used to edit the children. They parallel those of
   * SoGroup, except that they always check the child types against those which are
   * permissible. See SoGroup for details.
   */
  void                replaceChild(int index, SoNode *newChild);
  /**
   * Replaces first instance of given child with new child.
   * This is one of several functions used to edit the children. They parallel those of
   * SoGroup, except that they always check the child types against those which are
   * permissible. See SoGroup for details.
   */
  void                replaceChild( SoNode *oldChild, SoNode *newChild)
    { replaceChild(findChild(oldChild), newChild); }

  // Depending on the type of the container, this may
  // or may not affect the state.
  virtual SbBool affectsState() const;


 SoEXTENDER public:

  // These functions implement all actions for nodekits.
  virtual void doAction( SoAction *action );
  virtual void callback( SoCallbackAction *action );
  virtual void GLRender( SoGLRenderAction *action );
  virtual void getBoundingBox( SoGetBoundingBoxAction *action );
  virtual void getMatrix(SoGetMatrixAction *action );
  virtual void handleEvent( SoHandleEventAction *action );
  virtual void pick( SoPickAction *action );
  virtual void search( SoSearchAction *action );
  virtual void getPrimitiveCount (SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  // Returns pointer to children
  virtual SoChildList *getChildren() const;

 protected:

  SoGroup *getContainerNode();

  // Reads in from file. Takes care of setting parts and stuff.
  virtual SbBool readInstance(SoInput *in, unsigned short flags);

  SoChildList *children;

  // Copies the contents of the given nodekit into this instance
  virtual void        copyContents(const SoFieldContainer *fromFC,
                                   SbBool copyConnections);

 protected:
  virtual ~SoNodeKitListPart();

 private:
  SoSFName containerTypeName;
  SoMFName childTypeNames;
  SoSFNode containerNode;

  SoTypeList childTypes;

  SbBool  areTypesLocked;

  friend class SoBaseKit;

};

#endif  /* _SO_NODE_KIT_LIST_PART_ */

