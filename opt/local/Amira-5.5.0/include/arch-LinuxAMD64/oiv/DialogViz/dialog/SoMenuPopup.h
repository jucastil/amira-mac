/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_MENU_POPUP_
#define  _SO_MENU_POPUP_

#include <DialogViz/dialog/SoMenuItem.h>

class SoDialogAuditor;

/**
 * @VSGEXT Menu Popup node.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This node creates either a pulldown menu if it is inserted in an SoMenuBar or
 *   a cascade menu mechanism if it is inserted in an SoMenuPopup.
 *   A SoMenuPopup node consists in a set of SoMenuItem nodes.
 *   You can add, insert and remove menu items (SoMenuItem) by using addChild(),
 *   insertChild() and removeChild() methods.
 *
 *   You can change the parts in any instance of this menu popup using setPart().
 *   The default part geometries are defined as resources for this SoMenuPopup class.
 *   They are detailed below in the Catalog Parts section of the online reference page
 *   for this class. You can make your program use different default resources for the
 *   parts by copying the file $OIVHOME/data/DialogViz/Skins/default/MenuPopup.iv
 *   into your own directory, editing the file, and then setting the environment
 *   variable DIALOGVIZ_SKINS_DIR to be a path to that directory, or by using the
 *   setSkinDirectory() method in your application.
 *
 * @CATALOG_PARTS_INCLUDE somenupopup.cat.html
 *
 * @SEE_ALSO
 *   SoMenuItem,
 *   SoMenuCheckBox,
 *   SoMenuCheckBoxLauncher,
 *   SoMenuPushButton,
 *   SoMenuPushButtonLauncher,
 *   SoMenuFileSelection,
 *   SoMenuRadioButtons,
 *   SoMenuSeparator
 *
 */

class DIALOGVIZ_API SoMenuPopup : public SoMenuItem  
{
  SO_DG_HEADER(SoMenuPopup);

 public:

  /**
   * Constructor
   */
  SoMenuPopup();

  /**
   * Add a dialogAuditor to current menuPopup component.
   */
  void addAuditor(SoDialogAuditor* auditor);

  /**
   * Remove the defined DialogAuditor from the auditor list.
   */
  void removeAuditor(SoDialogAuditor* auditor);

  /**
   * Retrieves the DialogViz object from the specified auditorID field in an SoMenuPopup
   * structure. NULL is returned if auditorID string is not found.
   */
  SoDialogViz* searchForAuditorId(SbString id);

  /**
   * Adds a child as last one in group.
   */
  virtual void addChild(SoMenuItem *child);

  /**
   * Adds a child so that it becomes the one with the given index.
   */
  virtual void insertChild(SoMenuItem *child, int newChildIndex);

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
  virtual int findChild(const SoMenuItem *child) const;

  /**
   * Removes child with given index from group.
   */
  virtual void removeChild(int index);

  /**
   * Removes first instance of given child from group.
   */
  virtual void removeChild(SoMenuItem *child);

  /**
   * Removes all children from group.
   */
  virtual void removeAllChildren();

  /**
   * Replaces child with given index with new child.
   */
  virtual void replaceChild(int index, SoMenuItem *newChild);

  /**
   * Replaces first instance of given child with new child.
   */
  virtual void replaceChild(SoMenuItem *oldChild, SoMenuItem *newChild);

  /*==============================================================================*/
 SoINTERNAL public:
  // Returns pointer to children
  virtual SoChildList *getChildren() const;

  virtual void buildMenu(void* parent, SbBool isActive2d, int index = -1);
  static  void initClass();
  static  void exitClass();
  virtual void updateFromSensor(SoSensor* sensor);
  virtual void destroyNoDeleteMenuItem();
  virtual SbVec2i32 getItemInitSize();
  virtual void updateAfterSceneGraphChange();

  // Internal child management following inheritance of classes.
  virtual void internalRemoveChild( int index )                          { removeChild(index); }
  virtual void internalRemoveChild( SoNode *child  )                     { removeChild(findChild(dynamic_cast<SoMenuItem*>(child))); }
  virtual void internalRemoveAllChildren()                               { removeAllChildren(); }
  virtual void internalAddChild( SoNode *child )                         { addChild(dynamic_cast<SoMenuItem*>(child)); }
  virtual int internalFindChild( const SoNode *child ) const             { return findChild(dynamic_cast<const SoMenuItem*>(child)); }
  virtual void internalInsertChild( SoNode *child, int newChildIndex )   { insertChild(dynamic_cast<SoMenuItem*>(child), newChildIndex); }
  virtual SoNode *internalGetChild( int index) const                     { return getChild(index); }
  virtual void internalReplaceChild( int index, SoNode *newChild)        { replaceChild(index, dynamic_cast<SoMenuItem*>(newChild)); }
  virtual void internalReplaceChild( SoNode *oldChild, SoNode *newChild) { replaceChild(dynamic_cast<SoMenuItem*>(oldChild),dynamic_cast<SoMenuItem*>(newChild)); }

 protected:

  // Reads stuff into instance of SoGroup. Returns FALSE on error
  virtual SbBool readInstance(SoInput *in, unsigned short flags);
  
  // Reads just the children into instance of SoGroup. Returns FALSE on error
  virtual SbBool readChildren(SoInput *in);
  
  virtual      ~SoMenuPopup();
  virtual void changeLabel();
  virtual void changeEnable();

  void resetChangedStatus();  // Notified changes

  // Details of change (only valid during notification)
  SoNode*                  changedChild;
  int                      changedIndex;
  SoDataSensor::ChangeType changeType;

private:
  int m_numberOfChildren;
  void* m_menuPopupWin;
  SbBool m_firstBuild;


  void insertMenuItem(int index);
  void updateMenuItem();

  virtual void applyAuditor(SoDialogViz* dlgCpt);

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:
  static char* MenuPopup; //Internal default skin.
  static void change3DSkin();
  static SbBool isSkinLoaded();
  static void setSkinLoaded(SbBool loaded);

  virtual void get3DDefaultSize(SbVec3f& size);
          void show3DChildren(SbBool show);
  virtual void change3DPosition();
          void update3DChildren();
          void update3DChildrenSize();

protected:
  SO_DG_CATALOG_ENTRY_HEADER( frameSep      );
  SO_DG_CATALOG_ENTRY_HEADER( frameSwitch   );
  SO_DG_CATALOG_ENTRY_HEADER( released      );
  SO_DG_CATALOG_ENTRY_HEADER( pressed       );
  SO_DG_CATALOG_ENTRY_HEADER( shapeReleased );
  SO_DG_CATALOG_ENTRY_HEADER( shapePressed  );

  SoScale* menuPopupFrameScale;
  SoTranslation* menuPopupFrameTranslation;
  SoTransform* menuPopupFrameTransform;

  virtual void set3DInactive();

private:
  SbBool m_isOpenPopup;
  float m_mPopupCachedDepth;
  float m_mChildrenCachedDepth;
  static SbBool m_isSkinLoaded;

  void create3DPopup(int index);
  void update3DPopup();

  static void startCB3D( void *, SoDragger *inDragger );
  virtual void draggerStartCallback3D();

SoEXTENDER public:
  virtual void getBoundingBox(SoGetBoundingBoxAction* action);
  virtual void rayPick(SoRayPickAction *action);
  virtual void search(SoSearchAction *action);
  virtual void write(SoWriteAction *action);

///////////////////////////////////////////////////////////////////////////////////////

};

#endif // _SO_MENU_POPUP_
