/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_TAB_DIALOG_
#define  _SO_TAB_DIALOG_

#include <DialogViz/dialog/SoDialogGroup.h>
#include <DialogViz/SoDialogWidgetList.h>
#include <Inventor/fields/SoMFVec2f.h>

class SoClipPlane;
class SoNodeSensor;
class SoTabDialogAuditor;

/**
 * @VSGEXT Class that creates the dialog tab container.
 * 
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   An SoTabDialog creates multiple pages for the same area of a window. Each page
 *   consists of a set of SoDialogComponents that the application displays when the
 *   user selects the corresponding tab.
 *   You can add, insert, and remove dialog components (SoDialogComponent) by using 
 *   the addChild(), insertChild(), and removeChild() methods.
 *
 *   You can change the parts in any instance of this tab dialog component using setPart().
 *   The default part geometries are defined as resources for this SoTabDialog class.
 *   They are detailed below in the Catalog Parts section of the online reference page
 *   for this class. You can make your program use different default resources for the
 *   parts by copying the file $OIVHOME/data/DialogViz/Skins/default/TabDialog.iv
 *   into your own directory, editing the file, and then setting the environment
 *   variable DIALOGVIZ_SKINS_DIR to be a path to that directory, or by using the
 *   setSkinDirectory() method in your application.
 *
 * @FILE_FORMAT_DEFAULT
 *   TabDialog {
 *   @TABLE_FILE_FORMAT
 *       @TR tabsLocation            @TD TOP
 *       @TR selectedPage            @TD 0
 *       @TR // fields from SoDialogGroup
 *       @TR verticalScrollBar       @TD TRUE
 *       @TR horizontalScrollBar     @TD TRUE
 *       @TR scrollPolicy            @TD AUTO
 *       @TR windowResizedByChildren @TD TRUE
 *       @TR // fields from SoDialogComponent
 *       @TR width                   @TD 0
 *       @TR height                  @TD 0
 *       @TR fixedWidth              @TD FALSE
 *       @TR fixedHeight             @TD FALSE
 *       @TR minWidth                @TD 0
 *       @TR maxWidth                @TD 0
 *       @TR minHeight               @TD 0
 *       @TR maxHeight               @TD 0
 *       @TR margin                  @TD 0
 *       @TR edgeStyle               @TD NONE
 *       @TR labelVisibility         @TD TRUE
 *       @TR // fields from SoDialogViz
 *       @TR enable                  @TD TRUE
 *       @TR label                   @TD ""
 *       @TR labelAlignment          @TD RIGHT
 *       @TR auditorID             @TD ""
 *   @TABLE_END
 *   }
 *
 * @CATALOG_PARTS_INCLUDE sotabdialog.cat.html
 *
 * @SEE_ALSO
 *   SoColumnDialog,
 *   SoRowDialog,
 *   SoDialogGroup
 *
 */

class DIALOGVIZ_API SoTabDialog : public SoDialogGroup  
{
  SO_DG_HEADER(SoTabDialog);

 public:

  enum TabsLocation {
    /** Tabs appear at the top of the control (default). */
    TOP,
    /** Tabs appear at the bottom of the control. This value equals TCS_RIGHT.
     * This style is not supported if you are using ComCtl32.dll version 6.
     */
    BOTTOM,
    /** Tabs appear vertically on the left side of controls.*/
    LEFT,
    /** Tabs appear vertically on the right side of controls.*/
    RIGHT
  };

  /**
   * Specifies location of the tabs. Default value is TOP.
   */
  SoSFEnum tabsLocation;

  /**
   * Specifies currently selected tab page. Default is zero, the first page.
   */
  SoSFInt32 selectedPage;

  /**
   * Constructor.
   */
  SoTabDialog();

  /**
   * Adds a TabDialogAuditor to current TabDialog component.
   */
  void addAuditor(SoTabDialogAuditor* auditor);

  /**
   * Removes the specified TabDialogAuditor from the auditor list.
   */
  void removeAuditor(SoTabDialogAuditor* auditor);

  /*==============================================================================*/
 SoINTERNAL public:
  virtual void buildWidget(SoWidget parent, SbVec2i32& rSize, SbVec2i32& pos, SbBool isActive2d);
  virtual void eventNotify(unsigned int event, uintptr_t param);
  virtual void getDefaultSize(SbVec2i32 &size, SbVec2i32 &min, SbVec2i32 &max);
  static  void initClass();
  static  void exitClass();
  virtual void updateFromSensor(SoSensor* sensor);
  virtual void destroyWidget();

  SoDialogWidgetList m_tabPageWidgetsList;
  SoDialogWidgetList m_tabPageButtonsList;

  void changeTabSelectedPage(SoWidget widg);
  void changeEnableChild(int index);
  void changePageLabel(int index);
  void updateSelectedPage();
  void updateTabPageWidget(int index);
  void updateTabWidget();

  /* === CHILDREN MANAGEMENT === */
  virtual void addChild(SoDialogComponent *child);
  virtual void removeChild(int index);
  virtual void removeChild(SoDialogComponent *child) { removeChild(findChild(child)); }
  virtual void removeAllChildren();
  virtual void insertChild(SoDialogComponent *child, int newChildIndex);
  virtual void replaceChild(int index, SoDialogComponent *newChild);
  virtual void replaceChild(SoDialogComponent *oldChild, SoDialogComponent *newChild) { replaceChild(findChild(oldChild), newChild); }
  virtual void updateAfterSceneGraphChange();

  // Internal child management following inheritance of classes.
  virtual void internalRemoveChild( int index )                          { removeChild(index); }
  virtual void internalRemoveChild( SoNode *child  )                     { removeChild(findChild(dynamic_cast<SoDialogComponent*>(child))); }
  virtual void internalRemoveAllChildren()                               { removeAllChildren(); }
  virtual void internalAddChild( SoNode *child )                         { SoDialogGroup::internalAddChild(child); }
  virtual int internalFindChild( const SoNode *child ) const             { return SoDialogGroup::internalFindChild(child); }
  virtual void internalInsertChild( SoNode *child, int newChildIndex )   { SoDialogGroup::internalInsertChild(child, newChildIndex); }
  virtual SoNode *internalGetChild( int index) const                     { return getChild(index); }
  virtual void internalReplaceChild( int index, SoNode *newChild)        { SoDialogGroup::internalReplaceChild(index, dynamic_cast<SoDialogComponent*>(newChild)); }
  virtual void internalReplaceChild( SoNode *oldChild, SoNode *newChild) { replaceChild(dynamic_cast<SoDialogComponent*>(oldChild),dynamic_cast<SoDialogComponent*>(newChild)); }

  void* getLayout(int index);

 protected:
  virtual      ~SoTabDialog();
  virtual void fixSizeWithBorder(SbVec2i32 &size, int revert = 1);

 private:
  int m_numChildren;
  int m_firstPage;
  int m_previousSelected;
  SoWidget m_tabWidget;
  SoWidget m_arrowLeft;
  SoWidget m_arrowRight;
  SoWidget m_tabContainer;
  SoWidget m_maskLine;

  void createTabWidget();
  void createTabPageWidget(int index);
  void changeArrowState();
  void updateMaskLine();

  void drawItem(uintptr_t param);

  virtual SbVec2i32 getComponentInitSize();
  virtual void      setChildrenComponentSize();
  virtual void      setChildrenLabelSize();

  void changeFirstPageRight();
  void changeFirstPageLeft();
  virtual void changeSelectedPage();
  virtual void changeEnable();
  virtual void changeWidgetEnable(SbBool state);
  
  static void childrenSensor(void *data, SoSensor *sensor);

  FIELD_SENSOR(selectedPage);
  //  FIELD_SENSOR(tabsLocation);

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:
  static char* TabDialog; //Internal default skin.
  static void change3DSkin();
  static SbBool isSkinLoaded();
  static void setSkinLoaded(SbBool loaded);
  void change3DPages();
  void applyDlgCptAuditor();

protected:
  SO_DG_CATALOG_ENTRY_HEADER( pagesSep        );
  SO_DG_CATALOG_ENTRY_HEADER( pageSep         );
  SO_DG_CATALOG_ENTRY_HEADER( pageSwitch      );
  SO_DG_CATALOG_ENTRY_HEADER( labelSep        );
  SO_DG_CATALOG_ENTRY_HEADER( labelSwitch     );
  SO_DG_CATALOG_ENTRY_HEADER( selected        );
  SO_DG_CATALOG_ENTRY_HEADER( unselected      );
  SO_DG_CATALOG_ENTRY_HEADER( textSep         );    
  SO_DG_CATALOG_ENTRY_HEADER( textProp        );
  SO_DG_CATALOG_ENTRY_HEADER( buttonsSep      );
  SO_DG_CATALOG_ENTRY_HEADER( lButtonSep      );
  SO_DG_CATALOG_ENTRY_HEADER( lButtonSwtch    );
  SO_DG_CATALOG_ENTRY_HEADER( lButtonPressed  );
  SO_DG_CATALOG_ENTRY_HEADER( lButtonReleased );
  SO_DG_CATALOG_ENTRY_HEADER( rButtonSep      );
  SO_DG_CATALOG_ENTRY_HEADER( rButtonSwtch    );
  SO_DG_CATALOG_ENTRY_HEADER( rButtonPressed  );
  SO_DG_CATALOG_ENTRY_HEADER( rButtonReleased );
  SO_DG_CATALOG_ENTRY_HEADER( frameSep        );
  SO_DG_CATALOG_ENTRY_HEADER( frame           );

  SoScale *tabFrameScale, *tabButtonsScale, *tabLabelFrameScale;
  SoText3 *tabText;
  SoTransform *tabLabelFrameTransform;
  SoTranslation *tabFrameTranslation, *tabButtonsTranslation, *tabPageTranslation, *tabTextTranslation;
  SoClipPlane *m_clipWidth, *m_clipHeight;

private:
  SoNodeList m_childSwitchList;
  SoNodeList m_labelSwitchList;
  SoNodeList m_labelSepList;
  SoNodeList m_labelTransfList;
  SoNodeList m_labelTranslList;
  SoNodeList m_tabTextList;
  SoNodeList m_tabLabelScaleList;
  SoNodeList m_tabTextTranslList;

  SoMFVec2f m_labelDim;
  float m_mTabCacheDepth;
  int m_prevNumOfChildren;
  int m_frameLabelHeight;
  SbBool m_isUsedClipPlane;
  SbBool m_changeComeFromCB;
  static SbBool m_isSkinLoaded;

  void create3DTabDialog();
  void update3DTabDialog();
  void change3DSelectedPage();
  void update3DTabDialogPage(int index);
  void change3DFirstPageRight();
  void change3DFirstPageLeft();

  virtual void change3DPosition();

  virtual void show3D(SbBool show);
  static void startCB3D( void *, SoDragger *inDragger );
  static void finishCB3D( void *, SoDragger *inDragger );
  void draggerStartCallback3D();
  void draggerFinishCallback3D();

  SoNodeSensor* m_thisNodeSensor;

///////////////////////////////////////////////////////////////////////////////////////

};

#endif // _SO_TAB_DIALOG_
