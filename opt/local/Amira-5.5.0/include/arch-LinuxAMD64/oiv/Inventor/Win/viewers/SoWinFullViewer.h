/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/



#ifndef  _SO_WIN_FULL_VIEWER_
#define  _SO_WIN_FULL_VIEWER_

#include <Inventor/Win/SoWinBeginStrict.h>

#include <Inventor/Win/viewers/SoWinViewer.h>
#include <Inventor/SbPList.h>
#include <Inventor/Gui/viewers/SoGuiFullViewer.h>

// classes used
class  SoFieldSensor;
class  SoWinBitmapButton;
class  SoWinGDIThumbWheel;
class SoStereoDialog;

typedef void PushAppButtonCB( SoWidget w, int id,  void* pushData,  void* userData );
typedef void RedrawAppButtonCB( LPDRAWITEMSTRUCT lpdis,  void* userData ) ;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWinFullViewer
//
//      The SoWinFullViewer component class is the abstract base class for all
//  viewers which include a decoration around the rendering area. The 
//  decoration is made of thumbwheels, sliders and push/toggle buttons. There
//  is also a popup menu which includes all of the viewing options and methods.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Base viewer class which adds a decoration around the rendering area.
 * 
 * @ingroup Win
 * 
 * @DESCRIPTION
 *   This is a base class used by all viewer components. The class adds a decoration
 *   around the rendering area which includes thumb wheels, a zoom slider and push
 *   buttons. This base class also includes a viewer popup menu and a preference
 *   sheet with generic viewing functions. The constructors for the various
 *   subclasses of SoWinFullViewer provide a flag for specifying whether the
 *   decoration and popup menus should be built.
 * 
 * @SEE_ALSO
 *    SoWinViewer,
 *    SoWinComponent,
 *    SoWinRenderArea,
 *    SoWinExaminerViewer,
 *    SoWinWalkViewer,
 *    SoWinFlyViewer,
 *    SoWinPlaneViewer
 * 
 * 
 */ 

class INVENTORW_API SoWinFullViewer : public SoWinViewer 
{
 public:

  /** This specifies what should be build by default in the constructor */
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
   * Create the next instance of fullviewer w/wo the buttonbar
   * [OIV-WRAPPER-NOT-WRAP]
   */
  static void setDoButtonBar( SbBool onOrOff );

  /**
   * Returns whether the buttonbar is enabled or disabled.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  static SbBool isDoButtonBar() { return SoWinFullViewer::doButtonBar; }
    
  /** 
   * The callbacks in this list will be invoked after the action
   * selected from the viewer popup has been performed.  This 
   * applies to actions selected from only from the viewer popup,
   * not from the clients popup.  Note that it is possible to
   * add the viewer's pre-defined popup as a submenu of the
   * client's popup.  In this case the callbacks in this list
   * are still invoked after actions selected from the viewer
   * popup are performed. The callback data for the callback is
   * a pointer to the SoWinFullViewer object.
   */
  SoCallbackList popupPostCallback;

  /** 
   * The callbacks in this list are invoked immediately prior to
   * display of the popup menu, regardless of whether it is the
   * pre-defined viewer menu or a menu installed by the client
   * application.  The callback data for the callback is
   * a pointer to the SoWinFullViewer object.
   */
  SoCallbackList popupPreCallback;

  /**
   * Enables application-specific popup menu.
   */
  void setClientPopupMenu( Hmenu hmenu );

  /**
   *  Returns TRUE if an application-specific popup menu is installed.
   */
  SbBool isClientPopupMenuInstalled() { return (hClientPopup!= NULL); }

  /**
   * Returns application push button parent.
   */
  SoWidget getAppPushButtonParent() const { return appButtonForm; }

  /**
   * Adds application push button, which will be placed in the left
   * hand side decoration trim.
   * Buttons are appended to the end of the list.
   *
   * Note: The button bitmaps should be 24-by-24 pixels to fit nicely into the
   * decoration trim like the other viewer buttons.
   */
  void addAppPushButton( SoWidget newButton );

  /**
   * Adds application push button, which will be placed in the left
   * hand side decoration trim.
   * Buttons are inserted at the desired index.
   *
   * Note: The button bitmaps should be 24-by-24 pixels to fit nicely into the
   * decoration trim like the other viewer buttons.
   */
  void insertAppPushButton( SoWidget newButton, int index );

  /**
   * Removes specified application push button.
   */
  void removeAppPushButton( SoWidget oldButton );

  /**
   * Returns index of specified push button.
   */
  int findAppPushButton( SoWidget oldButton ) { return appButtonList->find( oldButton ); }

  /**
   * Returns number of application push buttons.
   */
  int lengthAppPushButton() { return appButtonList->getLength(); }
    
  /**
   * Returns the render area window handle.
   */
  SoWidget getRenderAreaWidget() { return raWidget; }
    
  // redefine these from the base class
  virtual void setViewing( SbBool onOrOff );
  virtual void setCamera( SoCamera* cam );
  virtual void hide();
  virtual void setHeadlight( SbBool onOrOff );
  virtual void setDrawStyle( SoWinViewer::DrawType type,
                             SoWinViewer::DrawStyle style );
  virtual void setBufferingType( SoWinViewer::BufferType type );

  // Allow app, eg. 3SA, to control this if desired.
  SoStereoDialog* getStereoDialog() { return stereoDialogBox; }
  void setStereoDialog( SoStereoDialog *newDialog ) { stereoDialogBox = newDialog; }

  /** 
   * Pointer to the popup menu container.
   */
  Hmenu  rootPopup; 
  
  /** 
   * Pointer to the root of the popup menu.
   */
  Hmenu mainPopup; 

  /** 
   * Pointer to the Functions submenu.
   */
  Hmenu funcPopup;

  /**
   * Pointer to the Draw Style submenu.
   */
  Hmenu drawPopup;

  /**
   * Pointer to the Preferences submenu.
   */
  Hmenu prefPopup;

  /** 
   * In this version we track the currently "check marked" menu
   * item in the Draw Style submenu (only one checked at a time).
   *
   * Tracks the checkmark for "Still" draw style.
   */
  UINT curPopupDrawItem;

  /*
   * Tracks the checkmark for "Moving" draw style.
   */
  UINT curPopupMoveItem;

  /*
   * Tracks the checkmark for the buffering draw style.
   */
  UINT curPopupBufferItem;

  /** 
   * Popup menu provided by a client (i.e. application program) of the viewer.
   */
  Hmenu  hClientPopup;

  void addPushAppButtonCallback( PushAppButtonCB* cb, void* data = NULL ) 
  {
    customPushBtnCB = cb;
    customPushBtnData = data;
  }
  void addRedrawAppButtonCallback( RedrawAppButtonCB* cb, void* data = NULL )
  {
    customRedrawBtnCB = cb;
    customRedrawBtnData = data;
  }

 SoINTERNAL public:
  virtual ~SoWinFullViewer();
    
  SoGuiFullViewer* getGuiFullViewer() const;

  // retro compatibilty, don't use them directly. Call their accessors.
  float rightWheelVal, leftWheelVal, bottomWheelVal; 
  SbBool popupEnabled;

 protected:
  // Constructor/Destructor
  SoWinFullViewer( SoWidget parent,
                   const char* name, 
                   SbBool buildInsideParent, 
                   SoWinFullViewer::BuildFlag flag,             //Removed class name qualifier from enum --mmh
                   SoWinViewer::Type type, 
                   SbBool buildNow,
                   SbBool sync );

  SoWinFullViewer( SoWidget parent,
                   const char* name, 
                   SbBool buildInsideParent, 
                   SoWinFullViewer::BuildFlag flag,
                   SoWinViewer::Type type, 
                   SbBool buildNow,
                   SbBool sync,
                   SoGuiFullViewer* guiFullViewer );
    
  // general decoration vars
  SbBool decorationFlag;
  SoWidget mgrWidget; // form which manages all other widgets
  SoWidget raWidget;  // render area widget
  SoWidget leftTrimForm, bottomTrimForm, rightTrimForm;

  static SbBool doButtonBar;
    
  int SO_WHEEL_DELTA;

  // zoom slider vars
  SoWidget zoomForm, zoomField, zoomSlider;
  SoFieldSensor* zoomSensor; // attached to camera zoom field
    
  // thumb wheel vars

  // For _WIN32 use frame window to hold instance of thumbwheel class.
  // Note: The "extra" wheel is only used by certain viewers, eg. the
  //       Walk viewer has a "Height" wheel.  It always appears above
  //       the left wheel.  This is a little more complicated under
  //       Windows because there's no such thing as a "form widget". :-)
  SoWinGDIThumbWheel* rightWheel, *bottomWheel, *leftWheel , *extraWheel;

  SoWidget extraTrimForm;
  float extraWheelVal;
  char* extraWheelStr;
  int extraLabelHeight;
  SoWidget extraWheelLabel;    //Handle of static control

  // static control that contains all the viewer
  // buttons on the right side
  SoWidget vwrButtonForm;

  HBRUSH backgroundBrush;    //Used to paint control bkgds

  char* rightWheelStr, *bottomWheelStr, *leftWheelStr;
  SoWidget rightWheelLabel, bottomWheelLabel, leftWheelLabel;
    
  // widget list of viewer buttons
  SbPList* viewerButtonWidgets;

  // For _WIN32 we have to use a slightly more complicated scheme to
  // allow subclasses to add their own buttons.  The viewerButtonWidgets
  // list includes both the "standard" FullVwr buttons and the subClass
  // buttons, so we need to remember how many are the FullVwr buttons.
  int numFullVwrButtons;

  // Subclasses should override this function (in addition to
  // createViewerButtons), handle selection if it's a button they
  // added and if not kick it back up to this function.
  virtual void pushButtonCB( SoWidget w, int id,  void* data );

  // We need this with WINxx to transmit events when they occur on
  // appButtonForm. Note that data contains the code (type HIWORD)
  // of the event that can be one of BN_DBLCLK, BN_DOUBLECLICKED,
  // BN_CLICKED, BN_PUSHED, BN_UNPUSHED
  // An application willing not to use this callback, will need
  // to assign another window proc to appButtonForm.
  // For UNIX, the application only need to assign a callback to
  // each button.
  // The default behaviour is to call a custom callback
  virtual void pushAppButtonCB( SoWidget w, int id,  void* data ) 
  {
    if ( customPushBtnCB )
      customPushBtnCB( w, id, data, customPushBtnData );
  }

  // subclasses should override this function or add a custom
  // redraw callback (see addRedrawAppButtonCallback) in order to
  // specify the redraw behaviour of the application buttons. Note
  // that the widget concerned by the call to this callback
  // function can be obtained with lpdis->hwndItem
  virtual void redrawAppButtonCB( LPDRAWITEMSTRUCT lpdis ) 
  {
    if ( customRedrawBtnCB )
      customRedrawBtnCB( lpdis, customRedrawBtnData );
  }

    
  // The button widget should be used as the parent widget
  // when creating new buttons
  SoWidget getButtonWidget() const { return appButtonForm; }
    
  // popup menu vars
  SoWidget popupWidget, *popupToggleWidgets;
  SoWidget* drawStyleWidgets, bufferStyleWidgets[3];
  char* popupTitle;
    
  //
  // Build/destroy decoration routines
  //
  SoWidget buildWidget( SoWidget parent );
  void buildLeftWheel( SoWidget parent );
    
  virtual void buildDecoration( SoWidget parent );
  virtual SoWidget buildLeftTrim( SoWidget parent );
  virtual SoWidget buildBottomTrim( SoWidget parent );
  virtual SoWidget buildRightTrim( SoWidget parent );
  virtual SoWidget buildZoomSlider( SoWidget parent );
  SoWidget buildAppButtons( SoWidget parent );
  SoWidget buildViewerButtons( SoWidget parent );
  virtual void createViewerButtons( SoWidget parent );
    
  //
  // popup menu build routines
  //
  virtual void buildPopupMenu();
  virtual void openStereoDialog();
  virtual void openRecordDialog();
  virtual void switchFSAAMode();

  virtual void destroyPopupMenu();
  void setPopupMenuString( const char* name );
  SoWidget buildFunctionsSubmenu( SoWidget popup );
  SoWidget buildDrawStyleSubmenu( SoWidget popup );

  // For windows we have to explicitly make the popup visible (this
  // gives us a chance to update all the checkmarks too).
  virtual int displayPopupMenu( int x, int y, Hwnd owner );

    
  //
  // Preference sheet build routines
  //
  void setPrefSheetString( const char* name );
  virtual void createPrefSheet();
  void createPrefSheetShellAndForm( SoWidget& shell, SoWidget& form );
  void createDefaultPrefSheetParts( SoWidget widgetList[], int &num, SoWidget form );
  void layoutPartsAndMapPrefSheet( SoWidget widgetList[], int num, SoWidget form, SoWidget shell );
  SoWidget createSeekPrefSheetGuts( SoWidget parent );
  SoWidget createSeekDistPrefSheetGuts( SoWidget parent );
  SoWidget createZoomPrefSheetGuts( SoWidget parent );
  SoWidget createClippingPrefSheetGuts( SoWidget parent );
  SoWidget createStereoPrefSheetGuts( SoWidget parent );
    
  // Subclasses SHOULD redefine these to do viewer specific tasks
  // since these do nothing in the base class. those routines are 
  // called by the thumb wheels whenever they rotate.
  virtual void rightWheelMotion( float f );
  virtual void bottomWheelMotion( float f );
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
  void setBottomWheelString( const char* name );
  void setLeftWheelString( const char* name );
  void setRightWheelString( const char* name );
    
  // Subclasses SHOULD redefine the openViewerHelpCard() routine to bring 
  // their help card (called by push button and popup menu entry).
  // They can simply call SoWinComponent::openHelpCard() to open their
  // specific help card.
  virtual void openViewerHelpCard();
    
  // redefine this to load the popup menu colormap
  virtual void afterRealizeHook();

  virtual void setSeekButton( SbBool onOff );

 private:
  void constructorCommon( SoWinFullViewer::BuildFlag buildFlag, SbBool buildNow, const char* name );

  static void clientResize(HWND handle, int x, int y, int  width, int height, BOOL repaint);

  SbBool firstBuild; // set FALSE after buildWidget called once

  SoGuiFullViewer* m_guiFullViewer; // Implementation class for SoXxFullViewer

  // app button vars
  SoWidget appButtonForm;
  SbPList* appButtonList;
  void doAppButtonLayout( int start );

  SoStereoDialog* stereoDialogBox;

  // zoom slider vars and routines
  SbVec2f zoomSldRange;
  void setCameraZoom( float zoom );
  float getCameraZoom();
  void setZoomSliderPosition( float zoom );
  void setZoomFieldString( float zoom );

  static void zoomSliderCB( SoWidget w, SoWinFullViewer* p, XtPointer* ptr );
  static void zoomFieldCB( SoWidget w, SoWinFullViewer* v, XtPointer* ptr );

  static void zoomSensorCB( void* v, SoSensor* s );
    
  // push buttons vars and callbacks
  SoWinBitmapButton* buttonList[10];
    
  // pref sheet variables
  SoWidget prefSheetShellWidget;
  char* prefSheetStr;

  // seek dist pref sheet vars and callbacks
  int seekDistWheelVal;
  SoWidget seekDistField;

  // clipping plane pref sheet callbacks and variables
  SoWidget clipWheelForm;
  int clipNearWheelVal, clipFarWheelVal;
  SoWidget clipNearField, clipFarField;

  // stereo viewing pref sheet callbacks and variables
  SoWidget stereoWheelForm, stereoField, stereoLabel;
  int stereoWheelVal;

  // zoom slider sensor activation 
  static void visibilityChangeCB( void* pt, SbBool visible );

  // callback functions for thumbwheels
  static void rightWheelCB ( SoWinFullViewer* v, XtPointer* d );
  static void bottomWheelCB( SoWinFullViewer* v, XtPointer* d );
  static void leftWheelCB  ( SoWinFullViewer* v, XtPointer* d );

  // Window proc for SoWinFullViewer "manager widget" windows
  static LRESULT CALLBACK mgrWindowProc( Hwnd hwnd, UINT message,
                                         WPARAM wParam, LPARAM lParam );

  // Window proc for SoWinFullViewer "button container" windows
  static LRESULT CALLBACK btnWindowProc( Hwnd hwnd, UINT message,
                                         WPARAM wParam, LPARAM lParam );

  // Window proc for SoWinFullViewer "application button container" windows
  static LRESULT CALLBACK appBtnWindowProc( Hwnd hwnd, UINT message,
                                            WPARAM wParam, LPARAM lParam );

  // Window proc for SoWinFullViewer text entry window (zoomfield)
  static LRESULT CALLBACK txtWindowProc( Hwnd hwnd, UINT message,
                                         WPARAM wParam, LPARAM lParam );

  PushAppButtonCB* customPushBtnCB;
  RedrawAppButtonCB* customRedrawBtnCB;
   void* customPushBtnData, *customRedrawBtnData;

  static int s_isAttRunning;

  // Save original wndProc for windows we're subclassing
#ifdef STRICT
  WNDPROC origBtnWndProc;
  WNDPROC origAppBtnWndProc;
  WNDPROC origTxtWndProc;
#else
  FARPROC origBtnWndProc ;
  FARPROC origAppBtnWndProc;
  FARPROC origTxtWndProc ;
#endif

  // Utility function to draw the viewer decorations
  // (Yes, we have to do this "by hand" for Windows)
  static void drawDecorations( SoWinFullViewer* p, Hwnd hwnd, Hdc hdc );
};

#include <Inventor/Win/SoWinEndStrict.h>
#endif  /* _SO_WIN_FULL_VIEWER_ */

