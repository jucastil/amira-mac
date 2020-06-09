/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/



#if defined(_WIN32)
#  include <Inventor/MP/Win/viewers/SoWinMPFullViewer.h>
#else // _WIN32

#ifndef _SO_XT_MP_FULL_VIEWER_
#define _SO_XT_MP_FULL_VIEWER_

#include <Xm/Xm.h>
#include <Inventor/MP/Xt/viewers/SoXtMPViewer.h>
#include <Inventor/SbPList.h>
#include <Inventor/components/stereo/SoStereoDialog.h>

// classes used
class   SoXtResource;
class   SoXtBitmapButton;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtMPFullViewer
//
//      The SoXtMPFullViewer component class is the abstract base class for all
//  viewers which include a decoration around the rendering area. The 
//  decoration is made of thumbwheels, sliders and push/toggle buttons. There
//  is also a popup menu which includes all of the viewing options and methods.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Base viewer class which adds a decoration around the rendering area.
 * 
 * @ingroup ScaleVizMultiPipe
 * 
 * @DESCRIPTION
 *   This is a base class used by all viewer components. The class adds a decoration
 *   around the rendering area that includes thumb wheels, a zoom slider and push
 *   buttons. This base class also includes a viewer popup menu and a preference
 *   sheet with generic viewing functions. The constructors for the various
 *   subclasses of SoXtMPFullViewer provide a flag for specifying whether the
 *   decoration and popup menus should be built.
 * 
 * @RESOURCES
 * <PRE>  
 *   !!------------------------------------------------ 
 *   !! FUNCTIONS MENU 
 *   !!------------------------------------------------ 
 *   *IvMenu.IvFunctions1.labelString: Functions 
 *   *IvFunctions2.IvHelp.labelString: Help 
 *   *IvFunctions2.IvHome.labelString: Home 
 *   *IvFunctions2.IvSetHome.labelString: Set Home 
 *   *IvFunctions2.IvViewAll.labelString: View All 
 *   *IvFunctions2.IvSeek.labelString: Seek 
 *   *IvFunctions2.IvCopyView.labelString: Copy View 
 *   *IvFunctions2.IvPasteView.labelString: Paste View 
 *   !!------------------------------------------------ 
 *   !! DRAW STYLE MENU 
 *   !!------------------------------------------------ 
 *   *IvMenu.IvDrawStyle1.labelString: Draw Style 
 *   *IvDrawStyle2.IvAsIs.labelString: as is 
 *   *IvDrawStyle2.IvHiddenLine.labelString: hidden line 
 *   *IvDrawStyle2.IvNoTexture.labelString: no texture 
 *   *IvDrawStyle2.IvLowResolution.labelString: low resolution 
 *   *IvDrawStyle2.IvWireFrame.labelString: wireframe 
 *   *IvDrawStyle2.IvPoints.labelString: points 
 *   *IvDrawStyle2.IvBoundingBoxNoDepth.labelString: bounding box ( no depth ) 
 *   *IvDrawStyle2.IvMoveSameAsStill.labelString: move same as still 
 *   *IvDrawStyle2.IvMoveNoTexture.labelString: move no texture. 
 *   *IvDrawStyle2.IvMoveLowRes.labelString: move low res 
 *   *IvDrawStyle2.IvMoveWireFrame.labelString: move wireframe 
 *   *IvDrawStyle2.IvMoveLowResWireFrameNoDepth.labelString: move low res wire frame ( no depth ) 
 *   *IvDrawStyle2.IvMovePoints.labelString: move points 
 *   *IvDrawStyle2.IvMoveLowResPointsNoDepth.labelString: move low res points ( no depth ) 
 *   *IvDrawStyle2.IvMoveBoundingBoxNoDepth.labelString: move bounding box ( no depth ) 
 *   *IvDrawStyle2.IvSingleBuffer.labelString: single buffer 
 *   *IvDrawStyle2.IvDoubleBuffer.labelString: Double buffer 
 *   *IvDrawStyle2.IvInteractiveBuffer.labelString: interactive buffer 
 *   !!------------------------------------------------ 
 *   *IvMenu.IvViewing.labelString: Viewing 
 *   !!------------------------------------------------ 
 *   *IvMenu.IvDecoration.labelString: Decoration 
 *   !!------------------------------------------------ 
 *   *IvMenu.IvHeadlight.labelString: Headlight 
 *   !!------------------------------------------------ 
 *   *IvMenu.IvPreferences.labelString: Preferences ...  
 *   
 *   !!------------------------------------------------ 
 *   !! PREFERENCES 
 *   !!------------------------------------------------ 
 *   *IvFormPreference1.IvSeekAnimationTime.labelString: Seek animation time 
 *   *IvFormPreference1.IvSeconds.labelString: seconds 
 *   *IvFormPreference1.IvSeekTo.labelString: Seek to: 
 *   *IvFormPreference1.IvPoint.labelString: point 
 *   *IvFormPreference1.IvObject.labelString: object 
 *   *IvFormPreference2.IvSeekDistance.labelString: Seek distance: 
 *   *IvFormPreference2.IvPercentage.labelString: percentage 
 *   *IvFormPreference2.IvAbsolute.labelString: absolute 
 *   *IvZoomForm.IvCameraZoom.labelString: Camera zoom 
 *   *IvZoomForm.IvZoomSliderRangesFrom.labelString: Zoom slider ranges from: 
 *   *IvZoomForm.IvTo.labelString: to: 
 *   *IvZoomForm.IvZoomSlider.labelString: Zoom slider 
 *   *IvZoomForm.IvZoomField.labelString: Zoom field 
 *   *IvZoomForm.IvZoomFrom.labelString: Zoom from 
 *   *IvZoomForm.IvZoomTo.labelString: Zoom to 
 *   *IvFormPreference3.IvAutoClippingPlanes.labelString: Auto clipping planes 
 *   *IvFormPreference4.IvStereoViewing.labelString: Stereo Viewing 
 *   *IvFormPreference6.IvNearPlane.labelString: near plane 
 *   *IvFormPreference6.IvFarPlane.labelString: far plane 
 *   *IvStereoThumbForm.IvCameraRotation.labelString: Camera rotation  
 * </PRE>
 * 
 * @SEE_ALSO
 *    SoXtMPViewer,
 *    SoXtComponent,
 *    SoXtMPRenderArea,
 *    SoXtMPExaminerViewer,
 *    SoXtMPWalkViewer,
 *    SoXtMPFlyViewer,
 *    SoXtMPPlaneViewer
 * 
 * 
 */ 

class INVENTORXT_API SoXtMPFullViewer : public SoXtMPViewer
{
 public:
    /** This specifies what should be build by default in the constructor  */
  enum BuildFlag {
    /**
     *  Doesn't build anything extra 
     */
    BUILD_NONE = 0x00, 
    /**
     *  Build the decoration only 
     */
    BUILD_DECORATION = 0x01, 
    /**
     *  Build the popup menu only 
     */
    BUILD_POPUP = 0x02, 
    /**
     *  Build everything by default 
     */
    BUILD_ALL = 0xff
  };
  
  /**
   * Shows/hides the viewer component trim (default on). See the viewer constructor to
   * prevent the decoration from being built.
   */
  void setDecoration(SbBool onOrOff);
  /**
   * Returns whether the viewer component trim is on or off.
   */
  SbBool isDecoration() { return decorationFlag; }
  
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
  void setPopupMenuEnabled(SbBool trueOrFalse);
  /**
   * Returns whether the viewer popup menu is enabled or disabled.
   */
  SbBool isPopupMenuEnabled() { return popupEnabled; }
  
  /**
   * Returns the parent widget, which is needed when creating new buttons. @BR
   * Note that if the decoration is not created in the constructor, this will be NULL
   * until the decoration is shown. 
   */
  SoWidget getAppPushButtonParent() const { return appButtonForm; }
  /**
   * Adds application push button, which will be placed in the left
   * hand side decoration trim. Adding buttons appends them to the end of the list. 
   *
   * Note: The button pixmaps should be 24-by-24 pixels size to nicely fit into the
   * decoration trim like the other viewer buttons. 
   */
  void addAppPushButton(SoWidget newButton);
  /**
   * Adds application push button, which will be placed in the left
   * hand side decoration trim. Inserting buttons 
   * places them at the desired index.
   *
   * Note: The button pixmaps should be 24-by-24 pixels size to nicely fit into the
   * decoration trim like the other viewer buttons. 
   */
  void insertAppPushButton(SoWidget newButton, int index);
  /**
   * Removes specified application push button.
   */
  void removeAppPushButton(SoWidget oldButton);
  /**
   * Returns index of specified push button.
   */
  int findAppPushButton(SoWidget oldButton)
    { return appButtonList->find(oldButton); }
  /**
   * Returns number of application push buttons.
   */
  int lengthAppPushButton()
    { return appButtonList->getLength(); }
  
  /**
   * Returns the render area widget.
   */
  SoWidget getRenderAreaWidget() { return raWidget; }
  
  // redefine these from the base class
  virtual void setViewing(SbBool onOrOff);
  virtual void setHeadlight(SbBool onOrOff);
  virtual void setDrawStyle(SoXtMPViewer::DrawType type, 
                            SoXtMPViewer::DrawStyle style);
  virtual void setBufferingType(SoXtMPViewer::BufferType type);
  virtual void setCamera(SoCamera *cam);
  virtual void hide();
  
 /** 
  * Pointer to the stereo dialog
  */
  SoStereoDialog* m_stereoDialogBox;
  
 SoINTERNAL public:
  virtual ~SoXtMPFullViewer();
  
 protected:
  // Constructor/Destructor
  SoXtMPFullViewer(SoWidget parent,
                   const char *name, 
                   SbBool buildInsideParent, 
                   BuildFlag flag, 
                   SoXtMPViewer::Type type, 
                   SbBool buildNow);
  
  // general decoration vars
  SbBool decorationFlag;
  SoWidget mgrWidget; // form which manages all other widgets
  SoWidget raWidget; // render area widget
  SoWidget leftTrimForm, bottomTrimForm, rightTrimForm;
  
  // thumb wheel vars
  SoWidget rightWheel, bottomWheel, leftWheel;
  char *rightWheelStr, *bottomWheelStr, *leftWheelStr;
  float rightWheelVal, bottomWheelVal, leftWheelVal;
  SoWidget rightWheelLabel, bottomWheelLabel, leftWheelLabel;
  
  // widget list of viewer buttons
  SbPList *viewerButtonWidgets;
  
  // The button widget should be used as the parent widget
  // when creating new buttons
  SoWidget getButtonWidget() const { return appButtonForm; }
  
  // popup menu vars
  SbBool popupEnabled;
  SoWidget popupWidget, *popupToggleWidgets;
  SoWidget *drawStyleWidgets, *bufferStyleWidgets;
  char *popupTitle;
  
  //
  // Build/destroy decoration routines
  //
  SoWidget                buildWidget(SoWidget parent);
  void          buildLeftWheel(SoWidget parent);
  
  virtual void  buildDecoration(SoWidget parent);
  virtual SoWidget        buildLeftTrim(SoWidget parent);
  virtual SoWidget        buildBottomTrim(SoWidget parent);
  virtual SoWidget        buildRightTrim(SoWidget parent);
  SoWidget                buildAppButtons(SoWidget parent);
  SoWidget                buildViewerButtons(SoWidget parent);
  virtual void  createViewerButtons(SoWidget parent);
  
  //
  // popup menu build routines
  //
  virtual void  buildPopupMenu();
  virtual void  buildMPPopupMenu(SbPipe *);

  virtual void  destroyPopupMenu();
  void          setPopupMenuString(const char *name);
  SoWidget                buildFunctionsSubmenu(SoWidget popup);
  SoWidget                buildDrawStyleSubmenu(SoWidget popup);
  
  //
  // Preference sheet build routines
  //
  void   setPrefSheetString(const char *name);
  virtual void createPrefSheet();
  void   createPrefSheetShellAndForm(SoWidget &shell, SoWidget &form);
  void   createDefaultPrefSheetParts(SoWidget widgetList[], 
                                     int &num, SoWidget form);
  void   layoutPartsAndMapPrefSheet(SoWidget widgetList[], 
                                    int num, SoWidget form, SoWidget shell);
  SoWidget         createSeekPrefSheetGuts(SoWidget parent);
  SoWidget         createSeekDistPrefSheetGuts(SoWidget parent);
  SoWidget         createZoomPrefSheetGuts(SoWidget parent);
  SoWidget         createClippingPrefSheetGuts(SoWidget parent);
  SoWidget         createStereoPrefSheetGuts(SoWidget parent);
  SoWidget         createSpeedPrefSheetGuts(SoWidget parent);
  
  // Subclasses SHOULD redefine these to do viewer specific tasks
  // since these do nothing in the base class. those routines are 
  // called by the thumb wheels whenever they rotate.
  virtual void  rightWheelMotion(float);
  virtual void  bottomWheelMotion(float);
  virtual void  leftWheelMotion(float);
  
  // Subclasses can redefine these to add viewer functionality. They
  // by default call start and finish interactive viewing methods.
  // (defined in the base class).
  virtual void  rightWheelStart();
  virtual void  bottomWheelStart();
  virtual void  leftWheelStart();
  virtual void  rightWheelFinish();
  virtual void  bottomWheelFinish();
  virtual void  leftWheelFinish();
  
  // Subclasses SHOULD set those wheel string to whatever functionality
  // name they are redefining the thumb wheels to do. Default names are
  // "Motion X, "Motion Y" and "Motion Z" for bottom, left and right wheels.
  void          setBottomWheelString(const char *name);
  void          setLeftWheelString(const char *name);
  void          setRightWheelString(const char *name);
  
  // Subclasses SHOULD redefine the openViewerHelpCard() routine to bring 
  // their help card (called by push button and popup menu entry).
  // They can simply call SoXtComponent::openHelpCard() to open their
  // specific help card.
  virtual void  openViewerHelpCard();

  virtual void setSeekButton(SbBool onOff); 
  
 private:
  SbBool        firstBuild; // set FALSE after buildWidget called once
   
  // app button vars
  SoWidget        appButtonForm;
  SbPList       *appButtonList;
   
  void  doAppButtonLayout(int start);
   
  // this is called the first time the widget is built
  void  getResources(SoXtResource *xr);
   
  // popup menu callbacks
  static void popMenuCallback(SoWidget, SoXtMPFullViewer *, XEvent *, Boolean *);
  static void drawStyleMenuPick(SoWidget, int id, void *);
  static void bufferStyleMenuPick(SoWidget, int id, void *);
  static void menuPick(SoWidget, int id, XmAnyCallbackStruct *);
   
  // push buttons vars and callbacks
  SoXtBitmapButton *buttonList[10];
  static void   pushButtonCB(SoWidget, int id, void *);
   
  // pref sheet variables
  SoWidget        prefSheetShellWidget;
  char  *prefSheetStr;
  static void   prefSheetDestroyCB(SoWidget, SoXtMPFullViewer *, void *);
  static void   stereoSheetDestroyCB(SoWidget, SoXtMPFullViewer *, void *);
   
  // seek pref sheet callbacks
  static void   seekPrefSheetFieldCB(SoWidget, SoXtMPFullViewer *, void *);
  static void   seekPrefSheetToggle1CB(SoWidget, SoWidget, void *);
  static void   seekPrefSheetToggle2CB(SoWidget, SoWidget, void *);
   
  // zoom pref sheet vars and callbacks
  SoWidget        *zoomWidgets;
  SbVec2f       zoomSldRange;
  void          setCameraZoom(float zoom);
  float         getCameraZoom();
  void  setZoomSliderPosition(float zoom);
  void  setZoomFieldString(float zoom);
  static void   zoomSliderCB(SoWidget, SoXtMPFullViewer *, XtPointer *);
  static void   zoomFieldCB(SoWidget, SoXtMPFullViewer *, XtPointer *);
  static void   zoomPrefSheetMinFieldCB(SoWidget, SoXtMPFullViewer *, void *);
  static void   zoomPrefSheetMaxFieldCB(SoWidget, SoXtMPFullViewer *, void *);
   
  // seek dist pref sheet vars and callbacks
  int           seekDistWheelVal;
  SoWidget        seekDistField;
  static void   seekDistWheelCB(SoWidget, SoXtMPFullViewer *v, XtPointer *d);
  static void   seekDistFieldCB(SoWidget, SoXtMPFullViewer *, void *);
  static void   seekDistPercPrefSheetToggleCB(SoWidget, SoWidget, void *);
  static void   seekDistAbsPrefSheetToggleCB(SoWidget, SoWidget, void *);
   
  // clipping plane pref sheet callbacks and variables
  SoWidget        clipWheelForm;
  int           clipNearWheelVal, clipFarWheelVal;
  SoWidget        clipNearField, clipFarField;
  static void   clipPrefSheetToggleCB(SoWidget, SoWidget, void *);
  static void   clipNearWheelCB(SoWidget, SoXtMPFullViewer *v, XtPointer *d);
  static void   clipFarWheelCB(SoWidget, SoXtMPFullViewer *v, XtPointer *d);
  static void   clipFieldCB(SoWidget, SoXtMPFullViewer *, void *);
   
  // stereo viewing pref sheet callbacks and variables
  SoWidget        stereoWheelForm, stereoField, stereoLabel;
  int           stereoWheelVal;
  static void   stereoPrefSheetToggleCB(SoWidget, SoWidget, void *);
  static void   stereoWheelCB(SoWidget, SoXtMPFullViewer *, XtPointer *);
  static void   stereoFieldCB(SoWidget, SoXtMPFullViewer *, void *);
   
  // dolly speed pref sheet callbacks
  static void   speedIncPrefSheetButtonCB(SoWidget, SoXtMPFullViewer *, void *);
  static void   speedDecPrefSheetButtonCB(SoWidget, SoXtMPFullViewer *, void *);
   
  // callback functions for thumbwheels
  static void rightWheelCB(SoWidget, SoXtMPFullViewer *v, XtPointer *d);
  static void bottomWheelCB(SoWidget, SoXtMPFullViewer *v, XtPointer *d);
  static void leftWheelCB(SoWidget, SoXtMPFullViewer *v, XtPointer *d);

};

#endif  /* _SO_XT_FULL_VIEWER_ */

#endif // _WIN32


