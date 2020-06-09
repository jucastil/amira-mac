/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/




#ifndef  _SO_WIN_MP_FULL_VIEWER_
#define  _SO_WIN_MP_FULL_VIEWER_

#if defined(_WIN32) 
#  include <Inventor/Win/SoWinBeginStrict.h>
#endif
#include <Inventor/MP/Win/viewers/SoWinMPViewer.h>
#include <Inventor/SbPList.h>

// classes used
class  SoFieldSensor;
class  SoWinBitmapButton;

#if defined(_WIN32) 
class  SoWinGDIThumbWheel;
#else
class  SoWinResource;
#endif

#  if defined(_WIN32)
class SoStereoDialog;
#  endif

typedef void PushAppButtonCB(SoWidget w, int id, void *pushData, void *userData);
typedef void RedrawAppButtonCB(LPDRAWITEMSTRUCT lpdis, void *userData) ;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWinMPFullViewer
//
//      The SoWinMPFullViewer component class is the abstract base class for all
//  viewers which include a decoration around the rendering area. The 
//  decoration is made of thumbwheels, sliders and push/toggle buttons. There
//  is also a popup menu which includes all of the viewing options and methods.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @SCVEXT Multi-Pipe base viewer class which adds a decoration around the rendering area.
 * 
 * @ingroup ScaleVizMultiPipe
 * 
 * @DESCRIPTION
 *   This is the Multi-Pipe version of SoWinFullViewer. 
 *   
 *   The typedefs, enums, and public methods of SoWinMPFullViewer are exactly the same
 *   as for SoWinFullViewer (except for the name change). 
 * 
 * 
 */ 

class INVENTORW_API SoWinMPFullViewer : public SoWinMPViewer {
 public:
    /** This specifies what should be build by default in the constructor  */
  enum BuildFlag {
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
    
  //
  // Show/hide the viewer component trims (default ON)
  //
  void            setDecoration(SbBool onOrOff);
  SbBool          isDecoration()          { return decorationFlag; }
    
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
  void            setPopupMenuEnabled(SbBool trueOrFalse);
  SbBool          isPopupMenuEnabled()    { return popupEnabled; }

  //
  // Create the next instance of fullviewer w/wo the buttonbar
  // (default is WITH)
  //
  static void     setDoButtonBar(SbBool onOrOff);
  static SbBool   isDoButtonBar() { return SoWinMPFullViewer::doButtonBar; }
    
  /**
   * The callbacks in this list will be invoked after the action
   * selected from the viewer popup has been performed.  This 
   * applies to actions selected only from the viewer popup,
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


  // Method to enable application program specific popup menu
  void                    setClientPopupMenu(Hmenu hmenu);

  // Is an application specific popup menu installed
  SbBool                  isClientPopupMenuInstalled() {return (hClientPopup!= NULL);};

  //
  // Add/remove push buttons for the application, which will be placed 
  // in the left hand side decoration trim.
  // The add() method appends the button to the end of the list, while 
  // insert() places the button at the specified index (starting at 0).
  //
  // returns the parent widget, which is needed when creating new buttons
  // NOTE that this will be NULL if the decoration is NOT created in the
  // constructor (see the BuildFlag) until it is shown.
  //
  // Note: for WIN32 only: when inserting an application button, if the
  // property PROP_THIS has not been affected to this widget, it is
  // automatically affected with the current viewer object. If you wish
  // to add it manually (SetProp(widget, PROP_THIS, ...)), use only a viewer
  // object. You might also want to add a PROP_CALLDATA property (type is int)
  // in order to specify the id of the button. This id is passed as the
  // second argument to pushAppButtonCB.
  SoWidget          getAppPushButtonParent() const { return appButtonForm; }
  void            addAppPushButton(SoWidget newButton);
  void            insertAppPushButton(SoWidget newButton, int index);
  void            removeAppPushButton(SoWidget oldButton);
  int             findAppPushButton(SoWidget oldButton)
    { return appButtonList->find(oldButton); }
  int             lengthAppPushButton()
    { return appButtonList->getLength(); }
    
  SoWidget          getRenderAreaWidget()   { return raWidget; }
    
  // redefine these from the base class
  virtual void    setViewing(SbBool onOrOff);
  virtual void    setCamera(SoCamera *cam);
  virtual void    hide();
  virtual void    setHeadlight(SbBool onOrOff);
  virtual void    setDrawStyle(SoWinMPViewer::DrawType type,
                               SoWinMPViewer::DrawStyle style);
  virtual void    setBufferingType(SoWinMPViewer::BufferType type);

  // Allow app, eg. 3SA, to control this if desired.
  SoStereoDialog *getStereoDialog()
    { return stereoDialogBox; }
  void               setStereoDialog( SoStereoDialog *newDialog )
    { stereoDialogBox = newDialog; }

  /**
   * Pointers to the popup menu and its submenus
   */
  Hmenu  rootPopup, mainPopup, funcPopup, drawPopup, prefPopup;

  /**
   * In this version we track the currently "check marked" menu
   * item in the drawstyle popup (only one checked at a time).
   */
  UINT   curPopupDrawItem, curPopupMoveItem, curPopupBufferItem;

  /**
   * Popup menu provided by a client (i.e. application program) of the viewer.
   */
  Hmenu  hClientPopup;

  void addPushAppButtonCallback(PushAppButtonCB *cb, void * data = NULL) {
    customPushBtnCB = cb;
    customPushBtnData = data;
  }
  void addRedrawAppButtonCallback(RedrawAppButtonCB *cb, void * data = NULL) {
    customRedrawBtnCB = cb;
    customRedrawBtnData = data;
  }

 SoINTERNAL public:
  virtual ~SoWinMPFullViewer();
    
 protected:
  // Constructor/Destructor
  SoWinMPFullViewer(SoWidget parent,
                    const char *name, 
                    SbBool buildInsideParent, 
                    BuildFlag flag,             //Removed class name qualifier from enum --mmh
                    SoWinMPViewer::Type type, 
                    SbBool buildNow);
    
  // general decoration vars
  SbBool          decorationFlag;
  SoWidget          mgrWidget; // form which manages all other widgets
  SoWidget          raWidget;  // render area widget
  SoWidget          leftTrimForm, bottomTrimForm, rightTrimForm;

  static SbBool   doButtonBar;
    
  // zoom slider vars
  SoWidget          zoomForm, zoomField, zoomSlider;
  SoFieldSensor   *zoomSensor; // attached to camera zoom field
    
  // thumb wheel vars
#if defined(_WIN32) 
  // For WIN32 use frame window to hold instance of thumbwheel class.
  // Note: The "extra" wheel is only used by certain viewers, eg. the
  //       Walk viewer has a "Height" wheel.  It always appears above
  //       the left wheel.  This is a little more complicated under
  //       Windows because there's no such thing as a "form widget". :-)
  SoWinGDIThumbWheel  *rightWheel, *bottomWheel,
    *leftWheel , *extraWheel;

  SoWidget          extraTrimForm;
  float           extraWheelVal;
  char            *extraWheelStr;
  int             extraLabelHeight;
  SoWidget          extraWheelLabel;    //Handle of static control

  // static control that contains all the viewer
  // buttons on the right side
  SoWidget          vwrButtonForm;

  HBRUSH          backgroundBrush;    //Used to paint control bkgds
#else
  SoWidget          rightWheel, bottomWheel, leftWheel;
#endif // _WIN32
  char            *rightWheelStr, *bottomWheelStr, *leftWheelStr;
  float           rightWheelVal, bottomWheelVal, leftWheelVal;
  SoWidget          rightWheelLabel, bottomWheelLabel, leftWheelLabel;
    
  // widget list of viewer buttons
  SbPList         *viewerButtonWidgets;
#if defined(_WIN32) 
  // For WIN32 we have to use a slightly more complicated scheme to
  // allow subclasses to add their own buttons.  The viewerButtonWidgets
  // list includes both the "standard" FullVwr buttons and the subClass
  // buttons, so we need to remember how many are the FullVwr buttons.
  int numFullVwrButtons;

  // Subclasses should override this function (in addition to
  // createViewerButtons), handle selection if it's a button they
  // added and if not kick it back up to this function.
  virtual void pushButtonCB(SoWidget, int id, void *);

  // We need this with WINxx to transmit events when they occur on
  // appButtonForm. Note that data contains the code (type HIWORD)
  // of the event that can be one of BN_DBLCLK, BN_DOUBLECLICKED,
  // BN_CLICKED, BN_PUSHED, BN_UNPUSHED
  // An application willing not to use this callback, will need
  // to assign another window proc to appButtonForm.
  // For UNIX, the application only need to assign a callback to
  // each button.
  // The default behaviour is to call a custom callback
  virtual void pushAppButtonCB(SoWidget w, int id, void *data) {
    if (customPushBtnCB)
      customPushBtnCB(w, id, data, customPushBtnData);
  }

  // subclasses should override this function or add a custom
  // redraw callback (see addRedrawAppButtonCallback) in order to
  // specify the redraw behaviour of the application buttons. Note
  // that the widget concerned by the call to this callback
  // function can be obtained with lpdis->hwndItem
  virtual void    redrawAppButtonCB(LPDRAWITEMSTRUCT lpdis) {
    if (customRedrawBtnCB)
      customRedrawBtnCB(lpdis, customRedrawBtnData) ;
  }

#endif
    
  // The button widget should be used as the parent widget
  // when creating new buttons
  SoWidget          getButtonWidget() const { return appButtonForm; }
    
  // popup menu vars
  SbBool          popupEnabled;
  SoWidget          popupWidget, *popupToggleWidgets;
  SoWidget          *drawStyleWidgets, bufferStyleWidgets[3];
  char            *popupTitle;
    
  //
  // Build/destroy decoration routines
  //
  SoWidget              buildWidget(SoWidget parent);
  void                buildLeftWheel(SoWidget parent);
    
  virtual void        buildDecoration(SoWidget parent);
  virtual SoWidget      buildLeftTrim(SoWidget parent);
  virtual SoWidget      buildBottomTrim(SoWidget parent);
  virtual SoWidget      buildRightTrim(SoWidget parent);
  virtual SoWidget      buildZoomSlider(SoWidget parent);
  SoWidget              buildAppButtons(SoWidget parent);
  SoWidget              buildViewerButtons(SoWidget parent);
  virtual void        createViewerButtons(SoWidget parent);
    
  //
  // popup menu build routines
  //
  virtual void        buildPopupMenu();
  virtual void        openStereoDialog();

  virtual void        destroyPopupMenu();
  void                setPopupMenuString(const char *name);
  SoWidget              buildFunctionsSubmenu(SoWidget popup);
  SoWidget              buildDrawStyleSubmenu(SoWidget popup);
#if defined(_WIN32) 
  // For windows we have to explicitly make the popup visible (this
  // gives us a chance to update all the checkmarks too).
  virtual int         displayPopupMenu( int x, int y, Hwnd owner );
#endif
    
  //
  // Preference sheet build routines
  //
  void            setPrefSheetString(const char *name);
  virtual void    createPrefSheet();
  void            createPrefSheetShellAndForm(SoWidget &shell, SoWidget &form);
  void            createDefaultPrefSheetParts(SoWidget widgetList[], 
                                              int &num, SoWidget form);
  void            layoutPartsAndMapPrefSheet(SoWidget widgetList[], 
                                             int num, SoWidget form, SoWidget shell);
  SoWidget          createSeekPrefSheetGuts(SoWidget parent);
  SoWidget          createSeekDistPrefSheetGuts(SoWidget parent);
  SoWidget          createZoomPrefSheetGuts(SoWidget parent);
  SoWidget          createClippingPrefSheetGuts(SoWidget parent);
  SoWidget          createStereoPrefSheetGuts(SoWidget parent);
    
  // Subclasses SHOULD redefine these to do viewer specific tasks
  // since these do nothing in the base class. those routines are 
  // called by the thumb wheels whenever they rotate.
  virtual void        rightWheelMotion(float);
  virtual void        bottomWheelMotion(float);
  virtual void        leftWheelMotion(float);
    
  // Subclasses can redefine these to add viewer functionality. They
  // by default call start and finish interactive viewing methods.
  // (defined in the base class).
  virtual void        rightWheelStart();
  virtual void        bottomWheelStart();
  virtual void        leftWheelStart();
  virtual void        rightWheelFinish();
  virtual void        bottomWheelFinish();
  virtual void        leftWheelFinish();
    
  // Subclasses SHOULD set those wheel string to whatever functionality
  // name they are redefining the thumb wheels to do. Default names are
  // "Motion X, "Motion Y" and "Motion Z" for bottom, left and right wheels.
  void                setBottomWheelString(const char *name);
  void                setLeftWheelString(const char *name);
  void                setRightWheelString(const char *name);
    
  // Subclasses SHOULD redefine the openViewerHelpCard() routine to bring 
  // their help card (called by push button and popup menu entry).
  // They can simply call SoWinComponent::openHelpCard() to open their
  // specific help card.
  virtual void        openViewerHelpCard();
    
  // redefine this to load the popup menu colormap
  virtual void    afterRealizeHook();

  virtual void setSeekButton(SbBool onOff);

 private:
  SbBool          firstBuild; // set FALSE after buildWidget called once
 // SbBool          m_seekButtonState;
  // app button vars
  SoWidget          appButtonForm;
  SbPList         *appButtonList;
  void            doAppButtonLayout(int start);

  SoStereoDialog *stereoDialogBox;
    
  // zoom slider vars and routines
  SbVec2f         zoomSldRange;
  void            setCameraZoom(float zoom);
  float           getCameraZoom();
  void            setZoomSliderPosition(float zoom);
  void            setZoomFieldString(float zoom);

  static void     zoomSliderCB(SoWidget, SoWinMPFullViewer *, XtPointer *);
  static void     zoomFieldCB(SoWidget, SoWinMPFullViewer *, XtPointer *);

  static void     zoomSensorCB(void *, SoSensor *);
    
  // push buttons vars and callbacks
  SoWinBitmapButton  *buttonList[10];
    
  // pref sheet variables
  SoWidget          prefSheetShellWidget;
  char            *prefSheetStr;
    
  // seek dist pref sheet vars and callbacks
  int             seekDistWheelVal;
  SoWidget          seekDistField;
    
  // clipping plane pref sheet callbacks and variables
  SoWidget          clipWheelForm;
  int             clipNearWheelVal, clipFarWheelVal;
  SoWidget          clipNearField, clipFarField;
    
  // stereo viewing pref sheet callbacks and variables
  SoWidget          stereoWheelForm, stereoField, stereoLabel;
  int             stereoWheelVal;

    
  // zoom slider sensor activation 
  static void visibilityChangeCB(void *pt, SbBool visible);

  // callback functions for thumbwheels
  static void rightWheelCB ( SoWinMPFullViewer *v, XtPointer *d );
  static void bottomWheelCB( SoWinMPFullViewer *v, XtPointer *d );
  static void leftWheelCB  ( SoWinMPFullViewer *v, XtPointer *d );

  // Window proc for SoWinMPFullViewer "manager widget" windows
  static LRESULT CALLBACK mgrWindowProc( Hwnd hwnd, UINT message,
                                         WPARAM wParam, LPARAM lParam );

  // Window proc for SoWinMPFullViewer "button container" windows
  static LRESULT CALLBACK btnWindowProc( Hwnd hwnd, UINT message,
                                         WPARAM wParam, LPARAM lParam );

  // Window proc for SoWinMPFullViewer "application button container" windows
  static LRESULT CALLBACK appBtnWindowProc( Hwnd hwnd, UINT message,
                                            WPARAM wParam, LPARAM lParam );

  // Window proc for SoWinMPFullViewer text entry window (zoomfield)
  static LRESULT CALLBACK txtWindowProc( Hwnd hwnd, UINT message,
                                         WPARAM wParam, LPARAM lParam );

  PushAppButtonCB *customPushBtnCB;
  RedrawAppButtonCB *customRedrawBtnCB;
  void *customPushBtnData, *customRedrawBtnData;

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
  static void drawDecorations( SoWinMPFullViewer *p, Hwnd hwnd, Hdc hdc );

};

#include <Inventor/Win/SoWinEndStrict.h>


#endif  /* _SO_WIN_FULL_VIEWER_ */

