/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_TOP_LEVEL_DIALOG_
#define  _SO_TOP_LEVEL_DIALOG_

#include <DialogViz/dialog/SoDialogViz.h>
#include <DialogViz/dialog/SoTopComponent.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFVec2i32.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>

class SbPlaneProjector;
class SoDialogAuditor;
class SoText3;
class SoTranslation;
class SoTransform;
class SoScale;

class SoMenuBar;

/** 
 * @VSGEXT Top Level Dialog node.
 *
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *   The SoTopLevelDialog class manages a list of SoTopComponent children.
 *   Typically, a top level component is composed of at most one SoMenuBar
 *   and a set of SoDialogComponents.
 *   You can add, insert, and remove top components (SoTopComponent) by using the addChild(),
 *   insertChild(), and removeChild() methods.
 *
 *   The SoTopLevelDialog components has numerous sizing constraints. In fact, the user can define
 *   the #width and #height of the dialog window, and can also add size limits to it using the fields
 *   #minWidth, #minHeight, #maxWidth, and #maxHeight. The limits will be considered when the
 *   #resizable field is set to TRUE. Otherwise, the size of the window is static and the minimize
 *   and maximize title bar buttons are removed on Windows systems.
 *
 *   @B Note@b: While 2D rendering, when triggering the window close button, the window is only hidden. If this dialog is
 *   the main window of an application (i.e., @B buildInsideParent@b parameter has been defined as TRUE),
 *   the dialog window is destroyed and the application is ended.
 *   Otherwise, the dialog window is not destroyed until closeDialog() is called.
 *
 *   You can change the parts in any instance of this top level component using setPart().
 *   The default part geometries are defined as resources for this SoTopLevelDialog class.
 *   They are detailed below in the Catalog Parts section of the online reference page
 *   for this class. You can make your program use different default resources for the
 *   parts by copying the file $OIVHOME/data/DialogViz/Skins/default/TopLevelDialog.iv
 *   into your own directory, editing the file, and then setting the environment
 *   variable DIALOGVIZ_SKINS_DIR to be a path to that directory, or by using the
 *   setSkinDirectory() method in your application.
 *
 * @FILE_FORMAT_DEFAULT
 *   TopLevelDialog {
 *   @TABLE_FILE_FORMAT
 *       @TR width                   @TD 0
 *       @TR height                  @TD 0
 *       @TR position                @TD 0 0 
 *       @TR position3D              @TD 0 0 0
 *       @TR resizable               @TD TRUE
 *       @TR minWidth                @TD 0
 *       @TR maxWidth                @TD 0
 *       @TR minHeight               @TD 0
 *       @TR maxHeight               @TD 0
 *       @TR margin                  @TD 0
 *       @TR rowSpacing              @TD 0
 *       @TR verticalScrollBar       @TD TRUE
 *       @TR horizontalScrollBar     @TD TRUE
 *       @TR scrollPolicy            @TD AUTO
 *       @TR windowResizedByChildren @TD FALSE
 *       @TR modalFrame              @TD FALSE
 *       @TR hideChildren            @TD FALSE
 *       @TR // fields from SoDialogViz
 *       @TR enable                  @TD TRUE
 *       @TR label                   @TD ""
 *       @TR labelAlignment          @TD RIGHT
 *       @TR auditorID               @TD ""
 *   @TABLE_END
 *   }
 *
 * @CATALOG_PARTS_INCLUDE sotopleveldialog.cat.html
 *
 * @SEE_ALSO
 *   SoTopComponent,
 *   SoMenuBar,
 *   SoDialogComponent
 *
 */

class DIALOGVIZ_API SoTopLevelDialog : public SoDialogViz
{
  SO_DG_HEADER(SoTopLevelDialog);

 public:

  /**
   * Preferred width of the top component. Default is zero.
   * The default value zero indicates that the width of the top component will be 
   * computed automatically according to its content.
   */
  SoSFInt32 width;

  /**
   * Preferred height of the top component. Default is zero.
   * The default value zero indicates that the height of the top component will be 
   * computed automatically according to its content.
   */
  SoSFInt32 height;


  /**
   * Window screen coordinates. Default position is (0,0).
   */
  SoSFVec2i32 position;

  /**
   * Window world coordinate position when rendering in 3D. Default is (0,0,0).
   */
  SoSFVec3f position3D;

  /**
   * Window world coordinate position when rendering in 3D and minimized.
   */
  SoSFVec3f minimized3DPosition;

  /**
   * Indicates if the top component can be resized or not, Default is TRUE.
   */
  SoSFBool resizable;
  
  /**
   * Controls and indicates whether the dialog is minimized or not. Default is FALSE.
   *  @FIELD_SINCE_OIV 8.1
   */
  SoSFBool minimized;

  /**
   * Indicates whether minimized and full size dialog have independant 3D position or not. Default is TRUE.
   *  @FIELD_SINCE_OIV 8.1
   */
  SoSFBool independentMinimizedPosition;
  
  /**
   * Minimum top component width. Default is zero.
   * The default value zero indicates no minimum value is specified.
   */
  SoSFInt32 minWidth;

  /**
   * Maximum top component width. Default is zero.
   * The default value zero indicates no minimum value is specified.
   */
  SoSFInt32 maxWidth;

  /**
   * Minimum top component height. Default is zero.
   * The default value zero indicates no minimum value is specified.
   */
  SoSFInt32 minHeight;

  /**
   * Maximum top component height. Default is zero.
   * The default value zero indicates no minimum value is specified.
   */
  SoSFInt32 maxHeight;

  /**
   * Margin width. Default is zero.
   */
  SoSFInt32 margin;

  /**
   * Space between each child. Default is zero.
   */
  SoSFInt32 rowSpacing;

  enum ScrollVisibility {
    /** Scroll bar never displayed. */
    NEVER,
    /** Scroll bar always visible. */
    ALWAYS,
    /** Automatic scroll bar: displayed when needed (default). */
    AUTO
  };

  /**
   * Controls how vertical scrollbar appears. Default value is AUTO.
   */
  SoSFEnum vScrollVisibility;

  /**
   * Controls how horizontal scrollbar appears. Default value is AUTO.
   */
  SoSFEnum hScrollVisibility;

  /**
   * Controls the window sizing when a child is added or removed. 
   * If FALSE, the window is not resized; scrollbars appear if needed. Default is FALSE.
   */
  SoSFBool windowResizedByChildren;

  /**
   * Sets window property. If TRUE, the window will have a border and
   * title bar but will not be resizeable. Default is FALSE.
   */
  SoSFBool modalFrame;

  /** 
   * When rendering DialogViz as a scene, children can be hidden while the SoTopLevelDialog
   * frame is moving by setting this field to TRUE. (Default is FALSE).
   * Hiding children during moves is recommended in order to preserve the frame rate while
   * moving. This is all the more useful when the 3D DialogViz window is complex.
   * Note: This field is not used in 2D mode.
   */
  SoSFBool hideChildren;

  /**
   * Constructor.
   */
  SoTopLevelDialog();

  /**
   * Builds the dialog window. If @B buildInsideParent@b is set to FALSE, a window is
   * created; its title is the field @B label @b of SoDialogViz.
   * If @B buildInsideParent@b is set to TRUE, the dialog is created inside
   * the @B parent@b window.
   */
  void buildDialog(SoWidget parent, SbBool buildInsideParent = FALSE);

  /**
   * Destroys the dialog window.
   */
  void close();

  /**
   * Shows the tolLevelDialog widget.
   */
  virtual void show();

  /**
   * Hides the topLevelDialog widget.
   */
  virtual void hide();

  /**
   * Adds a dialogAuditor to the current topLevelDialog component.
   */
  void addAuditor(SoDialogAuditor* auditor);

  /**
   * Removes the defined DialogAuditor from the auditor list.
   */
  void removeAuditor(SoDialogAuditor* auditor);

  /**
  * Applies all DialogAuditors in the auditor list.
  */
  void applyAuditors();

  /**
   * Retrieves the DialogViz object from the specified auditorID field in an SoTopLevelDialog
   * structure. NULL is returned if auditorID string is not found.
   */
  SoDialogViz* searchForAuditorId(SbString id);

  /**
   * Adds a child as last one in group.
   */
  virtual void addChild(SoTopComponent *child);

  /**
   * Adds a child so that it becomes the one with the given index.
   */
  virtual void insertChild(SoTopComponent *child, int newChildIndex);

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
  virtual int findChild(const SoTopComponent *child) const;

  /**
   * Removes child with given index from group.
   */
  virtual void removeChild(int index);

  /**
   * Removes first instance of given child from group.
   */
  virtual void removeChild(SoTopComponent *child);

  /**
   * Removes all children from group.
   */
  virtual void removeAllChildren();

  /**
   * Replaces child with given index with new child.
   */
  virtual void replaceChild(int index, SoTopComponent *newChild);

  /**
   * Replaces first instance of given child with new child.
   */
  virtual void replaceChild(SoTopComponent *oldChild, SoTopComponent *newChild);

/*==============================================================================*/
 SoINTERNAL public:

  //update from minimized state
  void updateMinimizedState();

  //Returns computed top level dialog size
  SbVec3f getTopLevelSize(){ return topLevelFrameScale->scaleFactor.getValue();}

  void buildWidget(SoWidget parent, SbVec2i32 &, SbVec2i32 &, SbBool isActive2d);
  void updateDialogBuild(SbBool is2dRender);
  void fixSizeWithBorder(SbVec2i32 &size, int revert = 1);
  SoWidget getBaseWidget() {return m_baseWidget;};
  SoWidget getWidget();

  static void initClass();
  static void exitClass();

  void setCurrentFocusedWidget(SoWidget widget);
  void setCurrentScrolledWidget(SoWidget widget);
  SoWidget getCurrentScrolledWidget();
  SoWidget getCurrentFocusedWidget();

  SbBool destroyDialog();
  void setScrollProperties();
  void setPosition(SbVec2i32& pos);
  void setSize(int32_t sw, int32_t sh, int32_t smw, int32_t smh, int32_t smmw, int32_t smmh);
  void updateTopLevelWidgetScrollPosition();
  void updateAfterSceneGraphChange();
  virtual void resetSize();

  void setDefaultState();
  void getDefaultState(SbVec2i32 &size, SbVec2i32 &min, SbVec2i32 &max);

  SoMenuBar* widgetHasMenuBar();
  void* getLayout();
  void updateChildren();
  void updateTopLevelWidget(SbVec2i32 &rSize);

  // Internal child management following inheritance of classes.
  virtual void internalRemoveChild( int index )                          { removeChild(index); }
  virtual void internalRemoveChild( SoNode *child  )                     { removeChild(findChild(dynamic_cast<SoTopComponent*>(child))); }
  virtual void internalRemoveAllChildren()                               { removeAllChildren(); }
  virtual void internalAddChild( SoNode *child );
  virtual int internalFindChild( const SoNode *child ) const;
  virtual void internalInsertChild( SoNode *child, int newChildIndex );
  virtual SoNode *internalGetChild( int index) const                     { return getChild(index); }
  virtual void internalReplaceChild( int index, SoNode *newChild);
  virtual void internalReplaceChild( SoNode *oldChild, SoNode *newChild) { replaceChild(dynamic_cast<SoTopComponent*>(oldChild),dynamic_cast<SoTopComponent*>(newChild)); }

 protected:

  virtual SoChildList *getChildren() const;
  
  // Reads stuff into instance of SoGroup. Returns FALSE on error
  virtual SbBool readInstance(SoInput *in, unsigned short flags);
  
  // Reads just the children into instance of SoGroup. Returns FALSE on error
  virtual SbBool readChildren(SoInput *in);
  
  SoWidget     m_baseWidget;
  SbBool     m_buildInside;
  SoWidget     m_topLevelWidget;
  SoWidget     m_topLevelWidgetXt;
  SoWidget     m_topForm;
    
  virtual ~SoTopLevelDialog();
  void    getDefaultSize(SbVec2i32 &size, SbVec2i32 &min, SbVec2i32 &max);
  void    getSize(SbVec2i32 &size, SbVec2i32 &min, SbVec2i32 &max);

  void resetChangedStatus();  // Notified changes

  // Details of change (only valid during notification)
  SoNode*                  changedChild;
  int                      changedIndex;
  SoDataSensor::ChangeType changeType;

 private:

  FIELD_SENSOR(minimized);
  FIELD_SENSOR(margin);
  FIELD_SENSOR(modalFrame);
  FIELD_SENSOR(resizable);
  FIELD_SENSOR(rowSpacing);
  FIELD_SENSOR(position);
  FIELD_SENSOR(position3D);
  FIELD_SENSOR(minimized3DPosition);
  FIELD_SENSOR(independentMinimizedPosition);
  FIELD_SENSOR(width);
  FIELD_SENSOR(height);
  FIELD_SENSOR(minWidth);
  FIELD_SENSOR(minHeight);
  FIELD_SENSOR(maxWidth);
  FIELD_SENSOR(maxHeight);

  int        m_numberOfChildren;
  SbBool     m_firstBuild;
  SoWidget     m_currentFocusedWidget;
  SoWidget     m_currentScrolledWidget;
  SoWidget     m_menu;
  void*      m_layout;
  SbBool     m_isFirstBuild;
  int        m_arrayNumChildren;
  SbVec2i32* m_childrenMax;
  SbVec2i32* m_childrenMin;
  SbVec2i32* m_childrenSize;
  int        m_cptToResize;
  SbBool     m_hScrollVisible;
  SbBool     m_vScrollVisible;
  SoWidget     m_clipWindowXt;
  SoWidget     m_vertSBXt;
  SoWidget     m_horzSBXt;
  int        m_borderWidth;
  int        m_borderHeight;
  int        m_menuHeight;
  int        m_titleHeight;

  SbVec2i32  m_initSize;
  SbVec2i32  m_initMinSize;
  SbVec2i32  m_initMaxSize;

  void computeNewChildrenHeight(SbVec2i32 &rSize);
  void createBaseWidget(SoWidget parent);
  int m_scrollWidth;
  void createTopLevelWidget();
  void initWidgetConstant();
  void setChildrenComponentSize();
  void setChildrenLabelSize();
  void updateBaseWidget();
  void updateChildrenSizeDB();
  void computeSize(SbVec2i32 &rSize, SbVec2i32 & pos);

  void changeRowSpacing();
  void changeResizable();
  void changeModalFrame();
  void changePosition();
  void changeMinMaxSize();

  virtual void changeEnable();
  virtual void changeLabel();
  virtual void changeWidth();
  virtual void changeHeight();

  virtual void applyAuditor(SoDialogViz* dlgCpt);

  virtual void      updateFromSensor(SoSensor* sensor);
  SoDialogAuditor* m_defaultAuditor;

///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:
  static char* TopLevelDialog; //Internal default skin.
  static void change3DSkin();
  static SbBool isSkinLoaded();
  static void setSkinLoaded(SbBool loaded);

  virtual void show3D(SbBool show);

protected:

  SO_DG_CATALOG_ENTRY_HEADER( frameSep    );
  SO_DG_CATALOG_ENTRY_HEADER( frame       );
  SO_DG_CATALOG_ENTRY_HEADER( labelSep    );
  SO_DG_CATALOG_ENTRY_HEADER( labelProp   );
  SO_DG_CATALOG_ENTRY_HEADER( minSep      );
  SO_DG_CATALOG_ENTRY_HEADER( minSwtch    );
  SO_DG_CATALOG_ENTRY_HEADER( minPressed  );
  SO_DG_CATALOG_ENTRY_HEADER( minReleased );


private:
  
  SbPlaneProjector* m_planeProj;
  SbVec3f m_worldRestartPt; // used if SHIFT key goes down to 
  SbVec3f m_initialPos;
  float m_mTopLevelCachedDepth;
  SbBool m_firstMinimization;
  static SbBool m_isSkinLoaded;

  SoScale* topLevelFrameScale;
  SoText3* topLevelLabel;
  SoTranslation* topLevelFrameTranslation, *topLevelMinTranslation, *topLevelLabelTranslation;
  SoTransform* topLevelFrameTransform;

  void create3DTopLevelDialog();
  void update3DTopLevelDialog();
  void update3DChildren();
  void update3DChildrenPosition();
  void update3DLabel();

  void minimize3DDialog();
  void restore3DDialog();
  void show3DChildren(SbBool show);

  virtual void change3DLabel();
  virtual void change3DPosition();

  static void startCB3D( void *, SoDragger *inDragger );
  void draggerStartCallback3D();
  static void motionCB3D( void *, SoDragger *inDragger );
  void draggerMotionCallback3D();
  static void finishCB3D( void *, SoDragger *inDragger );
  void draggerFinishCallback3D();

 SoEXTENDER public:
  virtual void getBoundingBox(SoGetBoundingBoxAction* action);
  virtual void rayPick(SoRayPickAction *action);
  virtual void search(SoSearchAction *action);
  virtual void write(SoWriteAction *action);

///////////////////////////////////////////////////////////////////////////////////////

};

#endif // _SO_TOP_LEVEL_DIALOG_
