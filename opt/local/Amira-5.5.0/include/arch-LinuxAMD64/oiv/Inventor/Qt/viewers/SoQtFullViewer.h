/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Alain Dumesny (MMM yyyy)
**=======================================================================*/


#ifndef  _SO_QT_FULL_VIEWER_
#define  _SO_QT_FULL_VIEWER_
#include <Inventor/Qt/OivQtCompat.h>

#include <QtGui/QScrollBar>
#include <QtGui/QPushButton>
#include <QtCore/QString>
#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QAction>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>

#include <Inventor/Qt/viewers/SoQtViewer.h>

#include <Inventor/SbPList.h>

#include <Inventor/Gui/viewers/SoGuiFullViewer.h>

#include <QtCore/QPointer>

// classes used
class SoFieldSensor;
class SoQtThumbWheel;
class SoStereoDialog;
class QLineEdit;
class SoRecordDialog;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoQtFullViewer
//
//      The SoQtFullViewer component class is the abstract base class for all
//  viewers which include a decoration around the rendering area. The 
//  decoration is made of thumbwheels, sliders and push/toggle buttons. There
//  is also a popup menu which includes all of the viewing options and methods.
//
//////////////////////////////////////////////////////////////////////////////

/**
* @VSGEXT Base viewer class which adds a decoration around the rendering area.
* 
* @ingroup Qt
* 
* @DESCRIPTION
*   This is a base class used by all viewer components. The class adds a decoration
*   around the rendering area which includes thumb wheels, a zoom slider and push
*   buttons. This base class also includes a viewer popup menu and a preference
*   sheet with generic viewing functions. The constructors for the various
*   subclasses of SoQtFullViewer provide a flag for specifying whether the
*   decoration and popup menus should be built.
* 
* @SEE_ALSO
*    SoQtViewer,
*    SoQtComponent,
*    SoQtRenderArea,
*    SoQtExaminerViewer,
*    SoQtWalkViewer,
*    SoQtFlyViewer,
*    SoQtPlaneViewer
* 
* 
*/ 

class INVENTORQT_API SoQtFullViewer : public SoQtViewer 
{

  Q_OBJECT

public:
  /** Build flags.
   * This specifies what should be build by default in the constructor
   */
  enum BuildFlag 
  {
    /**
    *  Doesn't build anything extra 
    */
    BUILD_NONE          = 0x00, 
    /**
    *  Build the decoration only 
    */
    BUILD_DECORATION    = 0x01, 
    /**
    *  Build the popup menu only 
    */
    BUILD_POPUP         = 0x02, 
    /**
    *  Build everything by default 
    */
    BUILD_ALL           = 0xff 
  };

  /**
  * Shows/hides the viewer component trim (default on). See the viewer constructor to
  * prevent the decoration from being built.
  *
  * The default value can be set using the environment variable
  * OIV_VIEWER_DECORATION (0 = OFF, 1 = ON).
  */
  virtual void setDecoration( SbBool onOrOff );

  /**
  * Returns whether the viewer component trim is on or off.
  */
  SbBool isDecoration() { return m_guiFullViewer->isDecoration(); }

  /** 
   * Enables/disables the viewer popup menu (default enabled). See the viewer
   * constructor to prevent the popup menu from being built.
   *
   * The default value can be set using the environment variable
   * OIV_VIEWER_POPUP_MENU (0 = OFF, 1 = ON).
   *
   * Description or equivalent function for each submenu of this popup menu:
   * - Functions: Manage the position of the camera:
   *   -> Home see resetToHomePosition()
   *   -> Set home see saveHomePosition()
   *   -> View all see viewAll()
   *   -> Seek see seekToPoint(const SbVec2s& mouseLocation)
   * - DrawStyle: Manage the draw style and buffering style:
   *   -> see setDrawStyle(DrawType type, DrawStyle style)
   *   -> see setBufferingType(BufferType type)
   * - Viewing: see setViewing()
   * - Decorations: see setDecoration()
   * - FullScreen: see setFullScreen()
   * - HeadLight: see setHeadlight()
   * - Preferences:
   *   -> Seek to point: Enables/disables seek mode (like the 'S' key)
   *   -> Auto clip planes: Enables/disables automatic clipping
   *   -> Stereo: Opens the stereo dialog
   *   -> Full scene antialiasing: see setFullSceneAntialiasing()
   *   -> Record: Opens the recording dialog
   *   -> DirectViz: Opens the DirectViz ray tracing dialog
   *   -> Rotation axes: Shows/hides the rotation axes
   */
  void setPopupMenuEnabled( SbBool trueOrFalse );

  /**
  * Returns whether the viewer popup menu is enabled or disabled.
  */
  SbBool isPopupMenuEnabled() { return m_guiFullViewer->isPopupMenuEnabled(); }

  /**
  * Enables application-specific popup menu.
  */
  void setClientPopupMenu( QMenu* menu );

  /**
  * Returns TRUE if an application-specific popup menu is installed.
  */
  SbBool isClientPopupMenuInstalled() { return (ClientPopup!= NULL); }

  /**
  * Returns application push button parent.
  */
  QWidget* getAppPushButtonParent() const { return appButtonForm; }

  /**
  * Adds application push button, which will be placed in the left
  * hand side decoration trim.
  * Buttons are appended to the end of the list.
  *
  * Note: The button bitmaps should be 28-by-28 pixels to fit nicely into the
  * decoration trim like the other viewer buttons.
  */
  void addAppPushButton( SoQtButton* newButton );

  /**
  * Adds application push button, which will be placed in the left
  * hand side decoration trim.
  * Buttons are inserted at the desired index.
  *
  * Note: The button bitmaps should be 24-by-24 pixels to fit nicely into the
  * decoration trim like the other viewer buttons.
  */
  void insertAppPushButton( SoQtButton* newButton, int index );

  /**
  * Removes specified application push button.
  */
  void removeAppPushButton( SoQtButton* oldButton );

  /**
  * Returns index of specified push button.
  */
  int findAppPushButton( SoQtButton* oldButton ) { return appButtonList->find(oldButton); }

  /**
  * Returns number of application push buttons.
  */
  int lengthAppPushButton() { return appButtonList->getLength(); }

  /**
  * Returns the render area window handle.
  */
  QWidget* getRenderAreaWidget() { return raWidget; }

  // redefine these from the base class
  virtual void setViewing( SbBool onOrOff );

  virtual void setCamera( SoCamera* cam );
  virtual void hide();
  virtual void setHeadlight( SbBool onOrOff);
  virtual void setDrawStyle( SoQtViewer::DrawType type, SoQtViewer::DrawStyle style );
  virtual void setBufferingType( SoQtViewer::BufferType type );

  /** 
   * Returns the current stereo dialog.
   */
  virtual SoStereoDialog* getStereoDialog() { return stereoDialogBox; }

  /** 
   * Sets the stereo dialog the viewer should use.
   */
  void setStereoDialog( SoStereoDialog* newDialog );

  /** 
   * Pointer to the root of the popup menu.
   */
  QPointer<QMenu> mainPopup;

  /** 
   * Pointer to the Functions submenu.
   */
  QPointer<QMenu> funcPopup;

  /**
   * Pointer to the Draw Style submenu.
   */
  QPointer<QMenu> drawPopup;

  /**
   * Pointer to the Preferences submenu.
   */
  QPointer<QMenu> prefPopup;

  /** 
   * In this version we track the currently "check marked" menu
   * item in the Draw Style submenu (only one checked at a time).
   *
   * Tracks the checkmark for "Still" draw style.
   */
  QAction* curPopupDrawItem;

  /*
   * Tracks the checkmark for "Moving" draw style.
   */
  QAction* curPopupMoveItem;

  /*
   * Tracks the checkmark for the buffering draw style.
   */
  QAction* curPopupBufferItem;

  /** 
   * Popup menu provided by a client (i.e. application program) of the viewer.
   */
  QPointer<QMenu> ClientPopup;

  SoINTERNAL public:
  virtual ~SoQtFullViewer();

  SoGuiFullViewer* getGuiFullViewer() const;

  virtual void openStereoDialog();
  virtual void openRecordDialog();

  virtual void setViewingMode( int viewingMode ) {};

  // retro compatibilty, don't use them directly. Call their accessors.
  float rightWheelVal, leftWheelVal, bottomWheelVal; 
  SbBool popupEnabled;

protected:
  // Constructor/Destructor
  SoQtFullViewer( QWidget* parent,
    const char* name, 
    SbBool buildInsideParent, 
    SoQtFullViewer::BuildFlag flag,             
    SoQtViewer::Type type, 
    SbBool buildNow,
    SbBool sync );

  SoQtFullViewer( QWidget* parent,
    const char* name, 
    SbBool buildInsideParent, 
    SoQtFullViewer::BuildFlag flag,             
    SoQtViewer::Type type, 
    SbBool buildNow,
    SbBool sync,
    SoGuiFullViewer* guiFullViewer );

  // general decoration vars
  QWidget         *mgrWidget; // form which manages all other widgets
  QWidget         *raWidget;  // render area widget

  QPointer<QWidget> leftTrimForm, bottomTrimForm, rightTrimForm;
  QWidget*        subMgrWidget;
  QHBoxLayout*    subHbl; // subMgrWidget layout

  QPointer<QWidget>         zoomForm;
  QLineEdit       *zoomField;
  QScrollBar      *zoomSlider;
  SoFieldSensor   *zoomSensor; // attached to camera zoom field

  // thumb wheel vars
  SoQtThumbWheel  *rightWheel, *bottomWheel, *leftWheel , *extraWheel;

  QPointer<QWidget>         extraTrimForm;
  float           extraWheelVal;
  QString         extraWheelStr;
  int             extraLabelHeight;
  QWidget         *extraWheelLabel;    //Handle of static control

  // static control that contains all the viewer
  // buttons on the right side
  QPointer<QWidget>         vwrButtonForm;

  QBrush          backgroundBrush;    //Used to paint control bkgds

  QString         rightWheelStr, bottomWheelStr, leftWheelStr;
  QLabel          *rightWheelLabel, *bottomWheelLabel, *leftWheelLabel, *zoomLabel;

  // widget list of viewer buttons
  SbPList         *viewerButtonWidgets;

  int numFullVwrButtons;

  // Subclasses should override this function (in addition to
  // createViewerButtons), handle selection if it's a button they
  // added and if not kick it back up to this function.
  virtual void pushButtonCB( int id );

  // The button widget should be used as the parent widget
  // when creating new buttons
  QWidget         *getButtonWidget() const { return appButtonForm; }

  // popup menu vars
  QWidget         *popupWidget, *popupToggleWidgets;
  QWidget         *drawStyleWidgets, *bufferStyleWidgets[3];
  QString         popupTitle;

  //
  // Build/destroy decoration routines
  //
  QWidget             *buildWidget( QWidget* parent );

  virtual void        buildDecoration();
  virtual QWidget     *buildLeftTrim( QWidget* parent );
  virtual QWidget     *buildBottomTrim( QWidget* parent );
  virtual QWidget     *buildRightTrim( QWidget* parent );
  virtual QWidget     *buildZoomSlider( QWidget* parent );
  QWidget             *buildAppButtons( QWidget* parent );
  QWidget             *buildViewerButtons( QWidget* parent );
  virtual void        createViewerButtons( QWidget* parent );

  //
  // popup menu build routines
  //
  virtual void buildPopupMenu();

  virtual void destroyPopupMenu();
  void setPopupMenuString( const QString& name );
  QWidget* buildFunctionsSubmenu( QWidget* popup );
  QWidget* buildDrawStyleSubmenu( QWidget* popup );

  // Display the main or the client popup menu
  virtual void displayPopupMenu( QPoint point );

  // Subclasses SHOULD redefine these to do viewer specific tasks
  // since these do nothing in the base class. those routines are
  // called by the thumb wheels whenever they rotate.
  virtual void rightWheelMotion( float f );
  virtual void bottomWheelMotion( float f);
  virtual void leftWheelMotion( float f );

  // Subclasses can redefine these to add viewer functionality. They
  // by default call start and finish interactive viewing methods.
  // (defined in the base class).
  virtual void rightWheelStart();
  virtual void bottomWheelStart();
  virtual void leftWheelStart();
  virtual void rightWheelFinish();
  virtual void bottomWheelFinish();
  virtual void leftWheelFinish();

  // Subclasses SHOULD set those wheel string to whatever functionality
  // name they are redefining the thumb wheels to do. Default names are
  // "Motion X, "Motion Y" and "Motion Z" for bottom, left and right wheels.
  void setBottomWheelString( const QString& name );
  void setLeftWheelString( const QString& name );
  void setRightWheelString( const QString& name );

  // Subclasses SHOULD redefine the openViewerHelpCard() routine to bring 
  // their help card (called by push button and popup menu entry).
  // They can simply call SoQtComponent::openHelpCard() to open their
  // specific help card.
  virtual void openViewerHelpCard();

  // redefine this to load the popup menu colormap
  virtual void afterRealizeHook();

protected:
  QPointer<QWidget> appButtonForm;

  int SO_WHEEL_DELTA;

  virtual void setSeekButton( SbBool onOff );

private:
  void constructorCommon( SoQtFullViewer::BuildFlag buildFlag, SbBool buildNow );

  SoGuiFullViewer* m_guiFullViewer; // Implementation class for SoXxFullViewer

  SbBool firstBuild; // set FALSE after buildWidget called once
  SbBool m_seekState;

  // app button vars
  SbPList* appButtonList;
  void doAppButtonLayout( int start, SoQtButton* newButton );

  SoStereoDialog *stereoDialogBox;
  SoRecordDialog* m_recordDialogBox;

  // zoom slider vars and routines
  SbVec2f zoomSldRange;
  void setCameraZoom( float zoom );
  float getCameraZoom();
  void setZoomSliderPosition( float zoom );
  void setZoomFieldString( float zoom );

  static void zoomSensorCB( void* d, SoSensor* s );

  // push buttons vars and callbacks
  SoQtButton* buttonList[10];

  // pref sheet variables
  QWidget* prefSheetShellWidget;
  char* prefSheetStr;

  // seek dist pref sheet vars and callbacks
  int seekDistWheelVal;
  QWidget* seekDistField;

  // clipping plane pref sheet callbacks and variables
  QWidget* clipWheelForm;
  int clipNearWheelVal, clipFarWheelVal;
  QWidget* clipNearField, clipFarField;

  // stereo viewing pref sheet callbacks and variables
  QWidget* stereoWheelForm, stereoField, stereoLabel;
  int stereoWheelVal;

  void UPDATE_CHECKMARK( QAction* curItem, QAction* item );

  QVBoxLayout*    mgrVbl; // mgrWidget layout

protected:

  //pixmap
  QPixmap IDB_PUSH_PICK;
  QPixmap IDB_PUSH_VIEW;
  QPixmap IDB_PUSH_HELP;
  QPixmap IDB_PUSH_HOME;
  QPixmap IDB_PUSH_SETHOME;
  QPixmap IDB_PUSH_VIEWALL;
  QPixmap IDB_PUSH_SEEK;
  QPixmap IDB_PUSH_GRAYSEEK;

  // Popup menu: need this to have a link to the menu items.
  QAction* IDM_DPOPUP_ASIS;
  QAction* IDM_DPOPUP_HLINE;
  QAction* IDM_DPOPUP_NOTEX;
  QAction* IDM_DPOPUP_LOWRES;
  QAction* IDM_DPOPUP_WIRE;
  QAction* IDM_DPOPUP_POINTS;
  QAction* IDM_DPOPUP_BBOX;
  //move style
  QAction* IDM_DPOPUP_MSAMEAS ;
  QAction* IDM_DPOPUP_MNOTEX;
  QAction* IDM_DPOPUP_MLOWRES;
#ifdef _WIN32
  QAction* IDM_DPOPUP_MHLINE;
#endif
  QAction* IDM_DPOPUP_MWIRE;
  QAction* IDM_DPOPUP_MPOINTS;
  QAction* IDM_DPOPUP_MBBOX;
  //buffer
  QAction* IDM_DPOPUP_SBUFFER;
  QAction* IDM_DPOPUP_DBUFFER;
  QAction* IDM_DPOPUP_IBUFFER;
  //preference menu
  QAction* IDM_PPOPUP_SEEK;
  QAction* IDM_PPOPUP_CLIP;
  QAction* IDM_PPOPUP_SPIN;
  QAction* IDM_PPOPUP_AXES;
  QAction* IDM_PPOPUP_STEREO;
  QAction* IDM_PPOPUP_FSAA;
  QAction* IDM_PPOPUP_RECORD;
  //mainPopup 
  QAction* IDM_MPOPUP_DIRECTVIZ;
  QAction* IDM_MPOPUP_VIEWING;
  QAction* IDM_MPOPUP_DECORAT;
  QAction* IDM_MPOPUP_FULLSCREEN;
  QAction* IDM_MPOPUP_HLIGHT;

#ifndef HIDDEN_FROM_DOC
  protected Q_SLOTS:
    //slot for thumbwheel
    /**
     *
     */
    void leftWheelDrag( int value );
    void leftWheelOther();
    void rightWheelDrag( int value );
    void rightWheelOther();
    void bottomWheelDrag( int value );
    void bottomWheelOther();

    /**
     *
     */
    void slotPushPickButton();
    void slotPushViewButton();
    void slotPushHelpButton();
    void slotPushHomeButton();
    void slotPushSetHomeButton();
    void slotPushViewAllButton();
    void slotPushSeekButton();

    //Q_SLOTS for popup menu
    /**
     *
     */
    void slot_popup_home();
    void slot_popup_setHome();
    void slot_popup_viewAll();
    void slot_popup_seek();

    //preference menu
    /**
     *
     */
    void slot_popup_seekToPoint();
    void slot_popup_clip();
    void slot_popup_stereo();
    void slot_popup_fsaa();
    void slot_popup_recording();

    //mainpopup
    /**
     *
     */
    void slot_popup_viewing();
    void slot_popup_directViz();
    void slot_popup_decoration();
    void slot_popup_fullscreen();
    void slot_popup_headLight();

    //draw style menu
    /**
     *
     */
    void slot_popup_asIs();
    void slot_popup_hiddenLine();
    void slot_popup_noTexture();
    void slot_popup_lowResolution();
    void slot_popup_wireFrame();
    void slot_popup_points();
    void slot_popup_boundingBox();
    void slot_popup_moveSameAsStill();
    void slot_popup_moveNoTexture();
    void slot_popup_moveLowRes();
    void slot_popup_moveWireFrame();
    void slot_popup_movePoints();
    void slot_popup_moveBoundingBox();
    void slot_popup_singleBuffer();
    void slot_popup_doubleBuffer();
    void slot_popup_interactiveBuffer();

#endif // HIDDEN_FROM_DOC

    private Q_SLOTS:
      void visibilityChangeCB( SbBool visible );
      void zoomSliderCB( int value );
      void textChangedSlot();
      void setNum( int value );
      void slot_internalStereoDialogDestroyed();
      void slot_externalStereoDialogDestroyed();
      void slot_internalRecordDialogDestroyed();
};

#endif  /* _SO_QT_FULL_VIEWER_ */
