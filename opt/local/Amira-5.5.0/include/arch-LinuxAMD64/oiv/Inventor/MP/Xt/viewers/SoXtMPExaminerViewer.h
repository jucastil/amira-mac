/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#if defined(_WIN32)
#  include <Inventor/MP/Win/viewers/SoWinMPExaminerViewer.h>
#else // _WIN32

#ifndef  _SO_XT_MP_EXAMINER_VIEWER_
#define  _SO_XT_MP_EXAMINER_VIEWER_

#include <Inventor/MP/Xt/viewers/SoXtMPFullViewer.h>
#include <Inventor/SbLinear.h>

// classes used
class SbSphereSheetProjector;
class SoFieldSensor;
class SoSeparator;
class SoSwitch;
class SoTranslation;
class SoScale;
class SoXtBitmapButton;
class SoXtCursor;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtMPExaminerViewer
//
//      Examiner viewer - allows the user to change the camera position
//  by spinning a sphere in front of the viewpoint.
//
//
//      Keys used by this viewer:
//      -------------------------
//
//      Left Mouse: Tumbles the virtual trackball.
//
//      Middle Mouse: 
//      Ctrl + Left Mouse: Translate up, down, left and right.
//
//      Ctrl + Middle Mouse: 
//      Left + Middle Mouse: Dolly in and out (gets closer to and further
//                          away from the object).
//
//      \<s\> + click: Alternative to the Seek button. Press (but do not hold 
//                  down) the \<s\> key, then click on a target object.
//
//      Right Mouse: Open the popup menu.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Viewer component which uses a virtual trackball to view the data.
 * 
 * @ingroup ScaleVizMultiPipe
 * 
 * @DESCRIPTION
 *   The Examiner viewer component allows you to rotate the view around a point of
 *   interest using a virtual trackball. The viewer uses the camera
 *   @B focalDistance @b field to figure out the point of rotation, which is usually
 *   set to be at the center of the scene. In addition to allowing you to rotate the
 *   camera around the point of interest, this viewer also allows you to translate
 *   the camera in the viewer plane, as well as dolly (move forward and backward) to
 *   get closer to or further away from the point of interest. The viewer also
 *   supports seek to quickly move the camera to a desired object or point.
 * 
 * @RESOURCES
 * <PRE>  
 *   !!------------------------------------------------ 
 *   !! Preferences for Examiner Viewer 
 *   !!------------------------------------------------ 
 *   *IvFormExaminer1.IvEnableSpinAnimation.labelString: Enable spin animation 
 *   *IvFormExaminer1.IvShowPointOfRotationAxes.labelString: Show point of rotation axes 
 *   *IvFormExaminer1.IvAxesSize.labelString: axes size 
 *   *IvFormExaminer1.IvPixels.labelString: pixels 
 *   !!------------------------------------------------ 
 *   !! Decorations for Examiner Viewer !! 
 *   !!------------------------------------------------ 
 *   *IvExamTitle.labelString: Examiner Viewer 
 *   *IvExamPrefTitle.labelString: Examiner Viewer Preference Sheet 
 *   *IvExamPopupTitle.labelString: Examiner Viewer 
 *   *IvExamIconTitle.labelString: Examiner Viewer 
 *   *IvExamRotx.labelString: Rotx 
 *   *IvExamRoty.labelString: Roty 
 *   *IvExamZoom.labelString: Zoom 
 *   *IvExamDolly.labelString: Dolly 
 * </PRE>
 * 
 * @USAGE
 *  (For 3-button mouse only.)
 *   
 *   @B Left Mouse: @b Rotate the virtual trackball.
 *   
 *   @B Middle Mouse or @BR
 *   Ctrl + Left Mouse: @b Translate up, down, left, right.
 *   
 *   @B Ctrl + Middle Mouse or @BR
 *   Left + Middle Mouse: @b Dolly in and out (gets closer to and further away from
 *   the object).(Perspective camera) or zoom in and out (Orthographic camera).
 *   
 *   @B \<s\> + Left Mouse: @b Alternative to the Seek button. Press (but do not hold
 *   down) the \<s\> key, then click on a target object. 
 *   
 *   @B Right Mouse: @b Open the popup menu.
 *   
 *   @B ALT: @b When the viewer is in selection (a.k.a. pick) mode, pressing and
 *   holding the ALT key temporarily switches the viewer to viewing mode. When the
 *   ALT key is released, the viewer returns to selection mode. Note: If any of the
 *   mouse buttons are currently depressed, the ALT key has no effect.
 * 
 * @SEE_ALSO
 *    SoXtMPFullViewer,
 *    SoXtMPViewer,
 *    SoXtComponent,
 *    SoXtMPRenderArea,
 *    SoXtMPWalkViewer,
 *    SoXtMPFlyViewer,
 *    SoXtMPPlaneViewer
 * 
 * 
 */ 

class INVENTORXT_API SoXtMPExaminerViewer : public SoXtMPFullViewer {
 public:
  /**
   * Constructor which specifies the viewer type. Please refer to the
   * SoXtMPViewer reference page for a description of the viewer types.
   */
  SoXtMPExaminerViewer(
                       SoWidget parent = NULL,
                       const char *name = NULL, 
                       SbBool buildInsideParent = TRUE, 
                       SoXtMPFullViewer::BuildFlag flag = BUILD_ALL, 
                       SoXtMPViewer::Type type = BROWSER);
  /**
   * Destructor.
   */
  ~SoXtMPExaminerViewer();
    
  /**
   * Shows/hides the point of rotation feedback, which only appears while in viewing
   * mode (default is off).
   */
  void        setFeedbackVisibility(SbBool onOrOff);
  /**
   * Returns the rotation feedback flag.
   */
  SbBool      isFeedbackVisible() const       { return feedbackFlag; }
    
  /**
   * Sets the point of rotation feedback size in pixels (default 20 pix).
   */
  void        setFeedbackSize(int newSize);
  /**
   * Returns the point of rotation feedback size in pixels.
   */
  int         getFeedbackSize() const         { return (int)feedbackSize; }
    
  /**
   * Enables/disables the spinning animation feature of the viewer (enabled by
   * default).
   */
  void        setAnimationEnabled(SbBool onOrOff);
  /**
   * Returns whether spin animation is enabled.
   */
  SbBool      isAnimationEnabled()            { return animationEnabled; }
    
  /**
   * Stops animation, if it is occurring.
   */
  void        stopAnimating();
  /**
   * Queries if the viewer is currently animating.
   */
  SbBool      isAnimating()                   { return animatingFlag; }
    
  //
  // redefine these to add Examiner viewer functionality
  //
  virtual void        viewAll();
  virtual void        resetToHomePosition();
  virtual void        setCamera(SoCamera *cam);
  virtual void        setViewing(SbBool onOrOff);
  virtual void        setCursorEnabled(SbBool onOrOff);
    
  /**
   * Sets the specified cursor active inside all MultiPipe windows. 
   * If cursor is NULL, the default arrow cursor is used.
   */
  void setCursor(SoXtCursor *cursor);

  /**
   * Returns a pointer to a newly created SoXtCursor instance, which
   * can then be customized with a pixmap, colors, etc.
   */
  SoXtCursor * newCursor(void);

 protected:
  
  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoXtMPExaminerViewer::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
    SoXtMPExaminerViewer(
                         SoWidget parent,
                         const char *name, 
                         SbBool buildInsideParent, 
                         SoXtMPFullViewer::BuildFlag flag, 
                         SoXtMPViewer::Type type, 
                         SbBool buildNow);
            
  // redefine these
  virtual SbString    getDefaultWidgetName() const;
  virtual SbString    getDefaultTitle() const;
  virtual SbString    getDefaultIconTitle() const;
    
  // redefine those routines to do viewer specific stuff
  virtual void        processEvent(XAnyEvent *anyevent);
  virtual void        setSeekMode(SbBool onOrOff);
    
  virtual void  prepareRedraw();
  virtual void        actualRedraw();
  virtual void  endRedraw();
    
  // Get X resources for the widget.
  SoWidget              buildWidget(SoWidget parent);
    
  // Define those thumb wheels to rotate the object
  virtual void        bottomWheelMotion(float newVal);
  virtual void        leftWheelMotion(float newVal);
  virtual void        rightWheelMotion(float newVal);
    
  // redefine those routines to also stop animation if any
  virtual void        bottomWheelStart();
  virtual void        leftWheelStart();
    
  // add viewer preference stuff
  virtual void        createPrefSheet();
    
  // add some viewer buttons
  virtual void        createViewerButtons(SoWidget parent);
    
  // Define this to bring the viewer help card
  virtual void        openViewerHelpCard();
    
 private:
  // viewer state variables
  int             mode;
  SbBool          createdCursors;
  SoXtCursor      *spinCursor, *panCursor, *dollyCursor, *seekCursor;
  SbSphereSheetProjector *sphereSheet;
  SbVec2s         locator; // mouse position
  SbBool          firstBuild; // set FALSE after buildWidget called once
    
  // point of rotation feedback vars
  SbBool          feedbackFlag;
  float           feedbackSize;
  SoSeparator     *feedbackRoot;
  SoSwitch        *feedbackSwitch;
  SoTranslation   *feedbackTransNode;
  SoScale         *feedbackScaleNode;
  static const char *geometryBuffer;
  void            createFeedbackNodes();
    
  // variables used for doing spinning animation
  SbBool          animationEnabled, animatingFlag;
  SoFieldSensor   *animationSensor;
  SbRotation      *rotBuffer;
  int             firstIndex, lastIndex;
  unsigned long   lastMotionTime;
  SbRotation      averageRotation;
  SbBool          computeAverage;
  static void     animationSensorCB(void *v, SoSensor *s);
  static void     visibilityChangeCB(void *pt, SbBool visible);
  void            doSpinAnimation();
    
  // camera panning vars
  SbVec3f         locator3D;
  SbPlane         focalplane;
    
  void            updateViewerMode(unsigned int state);
  void            switchMode(int newMode);
  void            updateCursor();
  void            defineCursors();
  void            rotateCamera(const SbRotation &rot);
  void            panCamera(const SbVec2f &newLocator);
  void            spinCamera(const SbVec2f &newLocator);
  void            dollyCamera(const SbVec2s &newLocator);
    
  // preference sheet stuff
  SoWidget          createExamPrefSheetGuts(SoWidget parent);
  static void     animPrefSheetToggleCB(SoWidget, SoXtMPExaminerViewer *, void *);
    
  // point of rotation pref sheet stuff
  int             feedbackSizeWheelVal;
  SoWidget          feedbackLabel[2], feedbackField, feedbackSizeWheel;
  static void     feedbackSizeWheelCB(SoWidget, SoXtMPExaminerViewer *p, XtPointer *d);
  static void     feedbackSizeFieldCB(SoWidget, SoXtMPExaminerViewer *, void *);
  static void     feedbackPrefSheetToggleCB(SoWidget, SoXtMPExaminerViewer *, void *);
  void            toggleFeedbackWheelSize(SoWidget toggle);
    
  // push button vars and callbacks
  SoXtBitmapButton  *buttonList[10];
  static void     camPushCB(SoWidget, SoXtMPExaminerViewer *, void *);

  // this is called by both constructors
  void constructorCommon(SbBool buildNow);

};

#endif  /* _SO_XT_EXAMINER_VIEWER_ */

#endif // _WIN32


