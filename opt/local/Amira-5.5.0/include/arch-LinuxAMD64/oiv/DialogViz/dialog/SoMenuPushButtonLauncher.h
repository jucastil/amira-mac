/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_MENU_PUSH_BUTTON_LAUNCHER_
#define  _SO_MENU_PUSH_BUTTON_LAUNCHER_

#include <DialogViz/dialog/SoMenuPushButton.h>
#include <DialogViz/dialog/SoTopLevelDialog.h>

/**
 * @VSGEXT Menu pushButtonLauncher node.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This node defines a push button item for a dialog menu with a special
 *   built-in behavior: The user can use this node to launch top level dialog window(s),
 *   without defining any specific callback to do it.
 *   You can add, insert and remove top level dialogs (SoTopLevelDialog) by using addChild(),
 *   insertChild() and removeChild() methods. 
 * 
 * @FILE_FORMAT_DEFAULT
 *   MenuPushButtonLauncher {
 *   @TABLE_FILE_FORMAT
 *       @TR // fields from SoDialogViz
 *       @TR enable           @TD TRUE
 *       @TR label            @TD ""
 *       @TR labelAlignment   @TD LEFT
 *       @TR auditorID      @TD ""
 *   @TABLE_END
 *   }
 *
 * @CATALOG_PARTS
 * @ref SoMenuPushButton_CatalogParts @BR
 *
 * @SEE_ALSO
 *   SoMenuCheckBoxLauncher,
 *   SoMenuPushButton
 *
 */

class DIALOGVIZ_API SoMenuPushButtonLauncher : public SoMenuPushButton  
{
  SO_DG_HEADER(SoMenuPushButtonLauncher);

 public:

  /**
   * Constructor
   */
  SoMenuPushButtonLauncher();

  /**
   * Retrieves the DialogViz object from the specified auditorID field in an SoMenuPushButtonLauncher
   * structure. NULL is returned if auditorID string is not found.
   */
  SoDialogViz* searchForAuditorId(SbString id);

  /**
   * Adds a child as last one in group.
   */
  virtual void addChild(SoTopLevelDialog *child);

  /**
   * Adds a child so that it becomes the one with the given index.
   */
  virtual void insertChild(SoTopLevelDialog *child, int newChildIndex);

  /**
   * Returns pointer to child node with the given index.
   */
  virtual SoNode *getChild(int index) const;

  /**
   * Returns number of children.
   */
  virtual int getNumChildren() const;

  /**
   * Finds index of given child within group. Returns -1 if not found.
   */
  virtual int findChild(const SoTopLevelDialog *child) const;

  /**
   * Removes child with given index from group.
   */
  virtual void removeChild(int index);

  /**
   * Removes first instance of given child from group.
   */
  virtual void removeChild(SoTopLevelDialog *child);

  /**
   * Removes all children from group.
   */
  virtual void removeAllChildren();

  /**
   * Replaces child with given index with new child.
   */
  virtual void replaceChild(int index, SoTopLevelDialog *newChild);

  /**
   * Replaces first instance of given child with new child.
   */
  virtual void replaceChild(SoTopLevelDialog *oldChild, SoTopLevelDialog *newChild);


/*==============================================================================*/
SoINTERNAL public:
  // Returns pointer to children
  virtual SoChildList *getChildren() const;

  static  void initClass();
  static  void exitClass();
  virtual void buildMenu(void* parent, SbBool isActive2d, int index = -1);
  virtual void menuEvent(void* parent, int itemId);

  // Internal child management following inheritance of classes.
  virtual void internalRemoveChild( int index )                          { removeChild(index); }
  virtual void internalRemoveChild( SoNode *child  )                     { removeChild(findChild(dynamic_cast<SoTopLevelDialog*>(child))); }
  virtual void internalRemoveAllChildren()                               { removeAllChildren(); }
  virtual void internalAddChild( SoNode *child )                         { addChild(dynamic_cast<SoTopLevelDialog*>(child)); }
  virtual int internalFindChild( const SoNode *child ) const             { return findChild(dynamic_cast<const SoTopLevelDialog*>(child)); }
  virtual void internalInsertChild( SoNode *child, int newChildIndex )   { insertChild(dynamic_cast<SoTopLevelDialog*>(child), newChildIndex); }
  virtual SoNode *internalGetChild( int index) const                     { return getChild(index); }
  virtual void internalReplaceChild( int index, SoNode *newChild)        { replaceChild(index, dynamic_cast<SoTopLevelDialog*>(newChild)); }
  virtual void internalReplaceChild( SoNode *oldChild, SoNode *newChild) { replaceChild(dynamic_cast<SoTopLevelDialog*>(oldChild),dynamic_cast<SoTopLevelDialog*>(newChild)); }

protected:

  // Reads stuff into instance of SoGroup. Returns FALSE on error
  virtual SbBool readInstance(SoInput *in, unsigned short flags);
  
  // Reads just the children into instance of SoGroup. Returns FALSE on error
  virtual SbBool readChildren(SoInput *in);
  
  virtual      ~SoMenuPushButtonLauncher();

  void resetChangedStatus();  // Notified changes

  // Details of change (only valid during notification)
  SoNode*                  changedChild;
  int                      changedIndex;
  SoDataSensor::ChangeType changeType;

private:
  int m_numberOfChildren;

SoEXTENDER public:
  virtual void search(SoSearchAction *action);
  virtual void rayPick(SoRayPickAction *action);
  virtual void write(SoWriteAction *action);

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:

protected:
  virtual void draggerStartCallback3D();
  virtual void draggerFinishCallback3D();

///////////////////////////////////////////////////////////////////////////////////////

};

#endif // _SO_MENU_PUSH_BUTTON_LAUNCHER_
