/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jul 2007)
**=======================================================================*/

#ifndef  SO_WX_FULL_VIEWER
#define  SO_WX_FULL_VIEWER

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWxFullViewer
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/Wx/viewers/SoWxViewer.h>

#include <Inventor/SbPList.h>
#include <Inventor/Gui/viewers/SoGuiFullViewer.h>

#define BASE_POPUP_MENU_ID wxID_HIGHEST+100
#define LAYOUT_MGRWIDGET_ID 102
#define LAYOUT_SUBMGRWIDGET_ID 103

// classes used
class  SoFieldSensor;
class SoStereoDialog;
class SoGuiFullViewer;
class SoRecordDialog;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWxFullViewer
//
//      The SoWxFullViewer component class is the abstract base class for all
//  viewers which include a decoration around the rendering area. The 
//  decoration is made of thumbwheels, sliders and push/toggle buttons. There
//  is also a popup menu which includes all of the viewing options and methods.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Base viewer class which adds a decoration around the rendering area.
 * 
 * @ingroup Wx
 * 
 * @DESCRIPTION
 *   This is a base class used by all viewer components. The class adds a decoration
 *   around the rendering area which includes thumb wheels, a zoom slider and push
 *   buttons. This base class also includes a viewer popup menu and a preference
 *   sheet with generic viewing functions. The constructors for the various
 *   subclasses of SoWxFullViewer provide a flag for specifying whether the
 *   decoration and popup menus should be built.
 * 
 * @SEE_ALSO
 *    SoWxViewer,
 *    SoWxComponent,
 *    SoWxRenderArea,
 *    SoWxExaminerViewer,
 *    SoWxPlaneViewer
 * 
 * 
 */ 

class INVENTORWX_API SoWxFullViewer : public SoWxViewer 
{
public:
 
    /** BuildFlag */
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
    BUILD_ALL           = 0xff, 
  };
    
  /**
   * Shows/hides the viewer component trim (default on). See the viewer constructor to
   * prevent the decoration from being built.
   *
   * The default value can be set using the environment variable
   * OIV_VIEWER_DECORATION (0 = OFF, 1 = ON).
   */
  void setDecoration( SbBool onOrOff );

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
  void setClientPopupMenu( wxMenu* menu );

  /**
   * Returns TRUE if an application-specific popup menu is installed.
   */
  SbBool isClientPopupMenuInstalled() { return (ClientPopup!= NULL); }

  /**
   * Returns application push button parent.
   */
  wxPanel* getAppPushButtonParent() const { return appButtonForm; }

  /**
   * Adds application push button, which will be placed in the left
   * hand side decoration trim.
   * Buttons are appended to the end of the list.
   *
   * Note: The button bitmaps should be 28-by-28 pixels to fit nicely into the
   * decoration trim like the other viewer buttons.
   */
  void addAppPushButton( wxButton* newButton );

  /**
   * Adds application push button, which will be placed in the left
   * hand side decoration trim.
   * Buttons are inserted at the desired index.
   *
   * Note: The button bitmaps should be 24-by-24 pixels to fit nicely into the
   * decoration trim like the other viewer buttons.
   */
  void insertAppPushButton( wxButton* newButton, int index );

  /**
   * Removes specified application push button.
   */
  void removeAppPushButton( wxButton* oldButton );

  /**
   * Returns index of specified push button.
   */
  int findAppPushButton( wxButton* oldButton ) { return m_appButtonList->find( oldButton ); }

  /**
   * Returns number of application push buttons.
   */
  int lengthAppPushButton() { return m_appButtonList->getLength(); }
    
  /**
   * Returns the render area window handle.
   */
  wxPanel* getRenderAreaWidget() { return raWidget; }
    
  // redefine these from the base class
  virtual void setViewing( SbBool onOrOff );
  
  virtual void setCamera( SoCamera* cam );
  virtual void hide();
  virtual void setHeadlight( SbBool onOrOff );
  virtual void setDrawStyle( SoWxViewer::DrawType type, SoWxViewer::DrawStyle style );
  virtual void setBufferingType( SoWxViewer::BufferType type );

  // Allow app, eg. 3SA, to control this if desired.
  SoStereoDialog* getStereoDialog() { return m_stereoDialogBox; }
  void setStereoDialog( SoStereoDialog* newDialog );

  /** 
   * Pointer to the root of the popup menu.
   */
  wxMenu* mainPopup;

  /** 
   * Pointer to the Functions submenu.
   */
  wxMenu* funcPopup;

  /**
   * Pointer to the Draw Style submenu.
   */
  wxMenu* drawPopup;

  /**
   * Pointer to the Preferences submenu.
   */
  wxMenu* prefPopup;

  /** 
   * In this version we track the currently "check marked" menu
   * item in the Draw Style submenu (only one checked at a time).
   *
   * Tracks the checkmark for "Still" draw style.
   */
  int curPopupDrawItem; 

  /*
   * Tracks the checkmark for "Moving" draw style.
   */
  int curPopupMoveItem;

  /*
   * Tracks the checkmark for the buffering draw style.
   */
  int curPopupBufferItem;

  /** 
   * Popup menu provided by a client (i.e. application program) of the viewer.
   */
  wxMenu* ClientPopup;

 SoINTERNAL public:
  virtual ~SoWxFullViewer();
    
  //virtual void internalEnableDirectViz( SbBool flag ); WX_NOPORT

  SoGuiFullViewer* getGuiFullViewer() const;
  void visibilityChangeCB( wxShowEvent& se );

 protected:
  // Constructor/Destructor
  SoWxFullViewer( wxWindow* parent,
                  const char* name, 
                  SbBool buildInsideParent, 
                  SoWxFullViewer::BuildFlag flag,             
                  SoWxViewer::Type type, 
                  SbBool buildNow,
                  SbBool sync );

  SoWxFullViewer( wxWindow* parent,
                  const char* name, 
                  SbBool buildInsideParent, 
                  SoWxFullViewer::BuildFlag flag,             
                  SoWxViewer::Type type, 
                  SbBool buildNow,
                  SbBool sync,
                  SoGuiFullViewer* guiFullViewer );
    
  // general decoration vars
  wxPanel* mgrWidget; // form which manages all other widgets
  wxPanel* raWidget;  // render area widget
  wxPanel* leftTrimForm, *bottomTrimForm, *rightTrimForm;
  wxPanel* subMgrWidget;

  // zoom slider vars
  wxPanel* zoomForm;
  wxTextCtrl* zoomField;
  wxSlider* zoomSlider;
  SoFieldSensor* zoomSensor; // attached to camera zoom field
    
  // thumb wheel vars
  wxWindow* rightWheel, *bottomWheel, *leftWheel , *extraWheel; 

  wxPanel* extraTrimForm;
  float extraWheelVal;
  char* extraWheelStr;
  int extraLabelHeight;
  wxStaticText* extraWheelLabel;    //Handle of static control

  // static control that contains all the viewer
  // buttons on the right side
  wxPanel* vwrButtonForm;

  char* rightWheelStr, *bottomWheelStr, *leftWheelStr;
  wxStaticText* rightWheelLabel, *bottomWheelLabel, *leftWheelLabel, *zoomLabel;
    
  // widget list of viewer buttons
  SbPList* viewerButtonWidgets;

  int numFullVwrButtons;

  // Subclasses should override this function (in addition to
  // createViewerButtons), handle selection if it's a button they
  // added and if not kick it back up to this function.
  virtual void pushButtonCB( int id );
    
  // The button widget should be used as the parent widget
  // when creating new buttons
  wxPanel* getButtonWidget() const { return appButtonForm; }
    
  // popup menu vars
  wxWindow* popupWidget, *popupToggleWidgets;
  wxWindow* drawStyleWidgets, *bufferStyleWidgets[3];
  char* popupTitle;
    
  //
  // Build/destroy decoration routines
  //
  wxPanel* buildWidget( wxWindow* parent );

  virtual void buildDecoration();
  virtual wxPanel* buildLeftTrim( wxPanel* parent );
  virtual wxPanel* buildBottomTrim( wxPanel* parent );
  virtual wxPanel* buildRightTrim( wxPanel* parent );
  virtual wxPanel* buildZoomSlider( wxPanel* parent );
  wxPanel* buildAppButtons( wxPanel* parent );
  wxPanel* buildViewerButtons( wxPanel* parent );
  virtual void createViewerButtons( wxPanel* parent );
    
  //
  // popup menu build routines
  //
  virtual void buildPopupMenu();
  virtual void openStereoDialog();
  virtual void openRecordDialog();

  virtual void destroyPopupMenu();
  void setPopupMenuString( const char* name );
  wxWindow* buildFunctionsSubmenu( wxWindow* popup );
  wxWindow* buildDrawStyleSubmenu( wxWindow* popup );

  // Display the main or the client popup menu
  virtual void displayPopupMenu();

  // Subclasses SHOULD redefine these to do viewer specific tasks
  // since these do nothing in the base class. those routines are
  // called by the thumb wheels whenever they rotate.
  virtual void rightWheelMotion( float );
  virtual void bottomWheelMotion( float );
  virtual void leftWheelMotion( float );
    
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
  void setBottomWheelString( const char* name );
  void setLeftWheelString( const char* name );
  void setRightWheelString( const char* name );
    
  // Subclasses SHOULD redefine the openViewerHelpCard() routine to bring 
  // their help card (called by push button and popup menu entry).
  // They can simply call SoWxComponent::openHelpCard() to open their
  // specific help card.
  virtual void openViewerHelpCard();
    
  // redefine this to load the popup menu colormap
  virtual void afterRealizeHook();

 protected:
  wxPanel* appButtonForm;

  int SO_WHEEL_DELTA;

  virtual void setSeekButton( SbBool onOff );

  //bitmap
  wxBitmap IDB_PUSH_PICK;
  wxBitmap IDB_PUSH_VIEW;
  wxBitmap IDB_PUSH_HELP;
  wxBitmap IDB_PUSH_HOME;
  wxBitmap IDB_PUSH_SETHOME;
  wxBitmap IDB_PUSH_VIEWALL;
  wxBitmap IDB_PUSH_SEEK;
  wxBitmap IDB_PUSH_GRAYSEEK;

  //popup menu ids
  //functions
  enum Functions
  {
    IDM_DPOPUP_FHOME = BASE_POPUP_MENU_ID,
    IDM_DPOPUP_FSHOME,
    IDM_DPOPUP_FVALL,
    IDM_DPOPUP_FSEEK
  };

  //style
  enum Style
  {
    IDM_DPOPUP_ASIS = BASE_POPUP_MENU_ID + 4,
    IDM_DPOPUP_HLINE,
    IDM_DPOPUP_NOTEX,
    IDM_DPOPUP_LOWRES,
    IDM_DPOPUP_WIRE,
    IDM_DPOPUP_POINTS,
    IDM_DPOPUP_BBOX
  };

  //move style
  enum MoveStyle
  {
    IDM_DPOPUP_MSAMEAS = BASE_POPUP_MENU_ID + 11,
    IDM_DPOPUP_MNOTEX,
    IDM_DPOPUP_MLOWRES,
    IDM_DPOPUP_MWIRE,
    IDM_DPOPUP_MPOINTS,
    IDM_DPOPUP_MBBOX
  };

  //buffer
  enum Buffer
  {
    IDM_DPOPUP_SBUFFER = BASE_POPUP_MENU_ID + 18,
    IDM_DPOPUP_DBUFFER,
    IDM_DPOPUP_IBUFFER
  };

  //preference menu
  enum Menu
  {
    IDM_PPOPUP_SEEK = BASE_POPUP_MENU_ID + 20,
    IDM_PPOPUP_CLIP,
    IDM_PPOPUP_SPIN,
    IDM_PPOPUP_AXES,
    IDM_PPOPUP_STEREO,
    IDM_PPOPUP_FSAA,
    IDM_PPOPUP_RECORDING
  };

  //mainPopup
  enum MainPopup
  {
    //IDM_MPOPUP_DIRECTVIZ = BASE_POPUP_MENU_ID + 25,
    IDM_MPOPUP_VIEWING = BASE_POPUP_MENU_ID + 27,
    IDM_MPOPUP_DECORAT,
    IDM_MPOPUP_FULLSCREEN,
    IDM_MPOPUP_HLIGHT
  };

#ifndef HIDDEN_FROM_DOC
  protected: 
  //slot for thumbwheel
  void leftWheelDrag( wxCommandEvent& ce );
  void leftWheelOther( wxCommandEvent& ce );
  void rightWheelDrag( wxCommandEvent& ce );
  void rightWheelOther( wxCommandEvent& ce );
  void bottomWheelDrag( wxCommandEvent& ce );
  void bottomWheelOther( wxCommandEvent& ce );

  void slotPushPickButton( wxCommandEvent& ce );
  void slotPushViewButton( wxCommandEvent& ce );
  void slotPushHelpButton( wxCommandEvent& ce );
  void slotPushHomeButton( wxCommandEvent& ce );
  void slotPushSetHomeButton( wxCommandEvent& ce );
  void slotPushViewAllButton( wxCommandEvent& ce );
  void slotPushSeekButton( wxCommandEvent& ce );

  //slots for popup menu
  void slot_popup_home( wxCommandEvent& ce );
  void slot_popup_setHome( wxCommandEvent& ce );
  void slot_popup_viewAll( wxCommandEvent& ce );
  void slot_popup_seek( wxCommandEvent& ce );
  
  //preference menu
  void slot_popup_seekToPoint( wxCommandEvent& ce );
  void slot_popup_clip( wxCommandEvent& ce );
  void slot_popup_stereo( wxCommandEvent& ce );
  void slot_popup_fsaa( wxCommandEvent& ce );
  void slot_popup_recording( wxCommandEvent& ce );

  //mainpopup
  void slot_popup_viewing( wxCommandEvent& ce );
  void slot_popup_decoration( wxCommandEvent& ce );
  void slot_popup_fullscreen( wxCommandEvent& ce );
  void slot_popup_headLight( wxCommandEvent& ce );

  //draw style menu
  void slot_popup_asIs( wxCommandEvent& ce );
  void slot_popup_hiddenLine( wxCommandEvent& ce );
  void slot_popup_noTexture( wxCommandEvent& ce );
  void slot_popup_lowResolution( wxCommandEvent& ce );
  void slot_popup_wireFrame( wxCommandEvent& ce );
  void slot_popup_points( wxCommandEvent& ce );
  void slot_popup_boundingBox( wxCommandEvent& ce );
  void slot_popup_moveSameAsStill( wxCommandEvent& ce );
  void slot_popup_moveNoTexture( wxCommandEvent& ce );
  void slot_popup_moveLowRes( wxCommandEvent& ce );
  void slot_popup_moveWireFrame( wxCommandEvent& ce );
  void slot_popup_movePoints( wxCommandEvent& ce );
  void slot_popup_moveBoundingBox( wxCommandEvent& ce );
  void slot_popup_singleBuffer( wxCommandEvent& ce );
  void slot_popup_doubleBuffer( wxCommandEvent& ce );
  void slot_popup_interactiveBuffer( wxCommandEvent& ce );

#endif // HIDDEN_FROM_DOC

 private:

   void constructorCommon( SoWxFullViewer::BuildFlag buildFlag, SbBool buildNow );

   SoGuiFullViewer* m_guiFullViewer; // Implementation class for SoXxFullViewer

  SbBool m_firstBuild; // set FALSE after buildWidget called once
  SbBool m_seekState;

  // app button vars
  SbPList* m_appButtonList;
  void doAppButtonLayout( int start, wxButton* newButton );

  SoStereoDialog* m_stereoDialogBox;
  SoRecordDialog* m_recordDialogBox;
  
  // zoom slider vars and routines
  SbVec2f m_zoomSldRange;
  void setCameraZoom( float zoom );
  float getCameraZoom();
  void setZoomSliderPosition( float zoom );
  void setZoomFieldString( float zoom );

  static void zoomSensorCB( void* data, SoSensor* sensor );
    
  // push buttons vars and callbacks
  wxControl* m_buttonList[10];

  void UPDATE_CHECKMARK( int _curItem, int item );

  void zoomSliderCB( wxCommandEvent& ce );
  void textChangedSlot( wxEvent& e );
  void setNum( int value );
  void slot_internalStereoDialogDestroyed( wxCommandEvent& ce );
  void slot_internalRecordDialogDestroyed( wxCommandEvent& ce );
  void slot_externalStereoDialogDestroyed( wxCommandEvent& ce );
};

#endif  // SO_WX_FULL_VIEWER
