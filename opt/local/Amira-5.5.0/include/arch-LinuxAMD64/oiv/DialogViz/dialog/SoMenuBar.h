/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_MENU_BAR_
#define  _SO_MENU_BAR_

#include <DialogViz/dialog/SoTopComponent.h>
#include <DialogViz/dialog/SoMenuPopup.h>

class SoDialogAuditor;

/**
 * @VSGEXT Menu bar node.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   This node defines a menu bar component.
 *
 *   @IMAGE MenuBar.jpg
 *
 *   If several @B SoMenuBar@b objects are added to an
 *   SoTopLevelDialog, only the first one is used; the others are ignored.
 *   An @B SoMenuBar @b node consists of a set of SoMenuPopup nodes.
 *   You can add, insert, and remove popup menus (SoMenuPopup) by using 
 *   the addChild(),
 *   insertChild(), and removeChild() methods.
 *
 *   You can change the parts in any instance of this menu bar using setPart().
 *   The default part geometries are defined as resources for this SoMenuBar class.
 *   They are detailed below in the Catalog Parts section of the online reference page
 *   for this class. You can make your program use different default resources for the
 *   parts by copying the file $OIVHOME/data/DialogViz/Skins/default/MenuBar.iv
 *   into your own directory, editing the file, and then setting the environment
 *   variable DIALOGVIZ_SKINS_DIR to be a path to that directory, or by using the
 *   setSkinDirectory() method in your application.
 *
 * @FILE_FORMAT_DEFAULT
 *   MenuBar {
 *   @TABLE_FILE_FORMAT
 *       @TR // fields from SoDialogViz
 *       @TR enable           @TD TRUE
 *       @TR label            @TD ""
 *       @TR labelAlignment   @TD RIGHT
 *       @TR auditorID      @TD ""
 *   @TABLE_END
 *   }
 *
 * @CATALOG_PARTS_INCLUDE somenubar.cat.html
 *
 * @SEE_ALSO
 *  SoTopLevelDialog,
 *  SoMenuPopup,
 *  SoMenuItem
 *
 */

class DIALOGVIZ_API SoMenuBar : public SoTopComponent  
{
  SO_DG_HEADER(SoMenuBar);

 public:

  /**
   * Constructor.
   */
  SoMenuBar();

  /**
   * Adds a DialogAuditor to current menu bar component.
   */
  void addAuditor(SoDialogAuditor* auditor);

  /**
   * Removes the specified DialogAuditor from the auditor list.
   */
  void removeAuditor(SoDialogAuditor* auditor);

  /**
   * Retrieves the DialogViz object from the specified auditorID field in an SoMenuBar
   * structure. NULL is returned if auditorID string is not found.
   */
  SoDialogViz* searchForAuditorId(SbString id);

  /**
   * Adds a child as last one in group.
   */
  virtual void addChild(SoMenuPopup *child);

  /**
   * Adds a child so that it becomes the one with the given index.
   */
  virtual void insertChild(SoMenuPopup *child, int newChildIndex);

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
  virtual int findChild(const SoMenuPopup *child) const;

  /**
   * Removes child with given index from group.
   */
  virtual void removeChild(int index);

  /**
   * Removes first instance of given child from group.
   */
  virtual void removeChild(SoMenuPopup *child);

  /**
   * Removes all children from group.
   */
  virtual void removeAllChildren();

  /**
   * Replaces child with given index with new child.
   */
  virtual void replaceChild(int index, SoMenuPopup *newChild);

  /**
   * Replaces first instance of given child with new child.
   */
  virtual void replaceChild(SoMenuPopup *oldChild, SoMenuPopup *newChild);

/*==============================================================================*/
SoINTERNAL public:
  virtual SoChildList *getChildren() const;

  virtual void   buildWidget(SoWidget parent, SbVec2i32 &, SbVec2i32 & pos, SbBool isActive2d);
  virtual void   destroyWidget();
  static  void   initClass();
  static  void   exitClass();
  virtual void   updateFromSensor(SoSensor* sensor);
  void* getMenu(void* parent);
  void destroyNoDeleteMenuItems();
  void updateChildren();
  virtual void updateAfterSceneGraphChange();

  // Internal child management following inheritance of classes.
  virtual void internalRemoveChild( int index )                          { removeChild(index); }
  virtual void internalRemoveChild( SoNode *child  )                     { removeChild(findChild(dynamic_cast<SoMenuPopup*>(child))); }
  virtual void internalRemoveAllChildren()                               { removeAllChildren(); }
  virtual void internalAddChild( SoNode *child )                         { addChild(dynamic_cast<SoMenuPopup*>(child)); }
  virtual int internalFindChild( const SoNode *child ) const             { return findChild(dynamic_cast<const SoMenuPopup*>(child)); }
  virtual void internalInsertChild( SoNode *child, int newChildIndex )   { insertChild(dynamic_cast<SoMenuPopup*>(child), newChildIndex); }
  virtual SoNode *internalGetChild( int index) const                     { return getChild(index); }
  virtual void internalReplaceChild( int index, SoNode *newChild)        { replaceChild(index, dynamic_cast<SoMenuPopup*>(newChild)); }
  virtual void internalReplaceChild( SoNode *oldChild, SoNode *newChild) { replaceChild(dynamic_cast<SoMenuPopup*>(oldChild),dynamic_cast<SoMenuPopup*>(newChild)); }

protected:
  
  // Reads stuff into instance of SoGroup. Returns FALSE on error
  virtual SbBool readInstance(SoInput *in, unsigned short flags);
  
  // Reads just the children into instance of SoGroup. Returns FALSE on error
  virtual SbBool readChildren(SoInput *in);
  
  virtual ~SoMenuBar();
  virtual void getSize(SbVec2i32 &size, SbVec2i32 &min, SbVec2i32 &max);

  void resetChangedStatus();  // Notified changes

  // Details of change (only valid during notification)
  SoNode*                  changedChild;
  int                      changedIndex;
  SoDataSensor::ChangeType changeType;

private:
  int m_numberOfChildren;
  void*  m_menuBarWin;
  SbBool m_firstBuild;

  void   createMenuBar(SoWidget parent);
  SbBool existMenuBar();
  void   updateMenuBar();
  virtual void changeEnable();
  virtual void applyAuditor(SoDialogViz* dlgCpt);

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:
  static char* MenuBar; //Internal default skin.
  static void change3DSkin();
  static SbBool isSkinLoaded();
  static void setSkinLoaded(SbBool loaded);

  virtual void show3D(SbBool show);
          void show3DChildren(SbBool show);
  virtual void set3DParentTranslation(SbVec3f& tsl);
          void update3DChildrenSize();

protected:
  SO_DG_CATALOG_ENTRY_HEADER( frameSep );
  SO_DG_CATALOG_ENTRY_HEADER( frame    );

  SoScale* menuBarFrameScale;
  SoTranslation* menuBarFrameTranslation;
  SoTransform* menuBarFrameTransform;

private:
  static SbBool m_isSkinLoaded;
  float m_mBarCachedDepth;

  void create3DBar();
  void update3DBar();
  void update3DChildren();
  virtual void change3DPosition();

SoEXTENDER public:
  virtual void getBoundingBox(SoGetBoundingBoxAction* action);
  virtual void rayPick(SoRayPickAction *action);
  virtual void search(SoSearchAction *action);
  virtual void write(SoWriteAction *action);

///////////////////////////////////////////////////////////////////////////////////////

};

#endif // _SO_MENU_BAR_
