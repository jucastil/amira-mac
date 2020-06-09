/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Alain Dumesny (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifdef SOQT
#  include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#elif defined(SOWX)
#  include <Inventor/Wx/viewers/SoWxExaminerViewer.h>
#elif defined _WIN32
#  include <Inventor/Win/viewers/SoWinExaminerViewer.h>
#else // _WIN32

#ifndef  _SO_XT_EXAMINER_VIEWER_
#define  _SO_XT_EXAMINER_VIEWER_

#include <Inventor/Xt/viewers/SoXtFullViewer.h>
#include <Inventor/SbLinear.h>
#include <Inventor/Gui/viewers/SoGuiExaminerViewer.h>

// classes used
class SbSphereSheetProjector;
class SoFieldSensor;
class SoSeparator;
class SoSwitch;
class SoTranslation;
class SoScale;
class SoXtBitmapButton;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtExaminerViewer
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
 * @ingroup Xt
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
 *   the object) (Perspective camera) or zoom in and out (Orthographic camera).
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
 *    SoXtFullViewer,
 *    SoXtViewer,
 *    SoXtComponent,
 *    SoXtRenderArea,
 *    SoXtWalkViewer,
 *    SoXtFlyViewer,
 *    SoXtPlaneViewer
 *
 *
 */

class INVENTORXT_API SoXtExaminerViewer : public SoXtFullViewer
{
 public:

   /**
  * Viewing mode.
  */
  enum ViewingMode 
  {
    /**
    * Rotate the camera around the point of interest.
    */
    VIEWING_MODE_SPIN,

    /**
    * Same as VIEWING_MODE_SPIN but add also constrained camera rotation.
    * It modifies the viewer usage described previously as follow:
    *  - @B Ctrl + Left Mouse @b: Rotation around the Z axis
    *  - @B Shift + Left Mouse or @b: Rotation around the X or the Y axis.
    *
    *    If the mouse movement is globally from the left to the right (resp. 
    *    from up to down) the Y axis (resp. X axis) is chosen.
    */
    VIEWING_MODE_SPIN_CONSTRAINED,

    /**
    * Translate the camera in the viewer plane.
    */
    VIEWING_MODE_PAN,

    /**
    * Dolly/Zoom (move forward and backward) to
    *   get closer to or further away from the point of interest.
    */
    VIEWING_MODE_ZOOM
  };

  /**
  * Constrained viewing mode.
  */
  enum ConstrainedViewingMode 
  {
    /**
    * No axis constraints.
    */
    NONE,
    /**
    * Constrains camera rotation around X axis.
    */
    CONSTRAINED_VIEWING_MODE_X,

    /**
    * Constrains camera rotation around Y axis.
    */
    CONSTRAINED_VIEWING_MODE_Y,

    /**
    * Constrains camera rotation around Z axis.
    */
    CONSTRAINED_VIEWING_MODE_Z
  };

  /**
   * Constructor which specifies the viewer type. Please refer to the
   * SoXtViewer reference page for a description of the viewer types.
   */
  SoXtExaminerViewer( SoWidget parent = NULL,
                      const char* name = NULL,
                      SbBool buildInsideParent = TRUE,
                      SoXtFullViewer::BuildFlag flag = SoXtFullViewer::BUILD_ALL,
                      SoXtViewer::Type type = SoXtViewer::BROWSER );
  /**
   * Destructor.
   */
  ~SoXtExaminerViewer();

  /**
   * Sets the viewing mode.
   * This method specifies what is the viewing behavior when the left mouse is 
   * pressed. 
   * The default value is SPIN_VIEWING_MODE.
   */
  void setViewingMode( ViewingMode viewingMode ) ;

  /**
   * Gets the current viewing mode.
   */
  ViewingMode getViewingMode() const
  { return (ViewingMode)m_guiExamViewer->getViewingMode(); }

  /** 
   * Sets the constrained viewing mode.
   * This method is useful to associate a key combination with a constrained mode.
   * Notes: 
   *   - There is no need to set the viewing mode to 
   *     VIEWING_MODE_SPIN_CONSTRAINED to apply a constraint.
   *   - When the constrained mode is set to NONE, the automatic constraints apply
   *     if VIEWING_MODE_SPIN_CONSTRAINED is set.
   *   - This setting is a "one shot". It only applies to the next
   *     mouse button down event.
   */
  void setConstrainedViewingMode( ConstrainedViewingMode mode );

  /**
   * Returns the current constrained viewing mode.
   */
  ConstrainedViewingMode getConstrainedViewingMode() const
  { return m_constrainedMode; }

  /**
   * Shows/hides the point of rotation feedback, which only appears while in viewing
   * mode (default is off).
   */
  void setFeedbackVisibility( SbBool onOrOff );

  /**
   * Returns the rotation feedback flag.
   */
  SbBool isFeedbackVisible() const { return m_guiExamViewer->isFeedbackVisible(); }

  /**
   * Sets the point of rotation feedback size in pixels (default 20 pix).
   */
  void setFeedbackSize( int newSize );

  /**
   * Returns the point of rotation feedback size in pixels.
   */
  int getFeedbackSize() const { return m_guiExamViewer->getFeedbackSize(); }

  /**
   * Enables/disables the spinning animation feature of the viewer (enabled by
   * default). @BR
   * @BR
   * The default value can be set using the environment variable
   * OIV_VIEWER_ANIMATION (0 = OFF, 1 = ON).
   */
  void setAnimationEnabled( SbBool onOrOff );

  /**
   * Returns whether spin animation is enabled.
   */
  SbBool isAnimationEnabled() { return m_guiExamViewer->isAnimationEnabled(); }

  /**
   * Stops animation, if it is occurring.
   */
  void stopAnimating();

  /**
   * Queries if the viewer is currently animating.
   */
  SbBool isAnimating() { return m_guiExamViewer->isAnimating(); }

  //
  // redefine these to add Examiner viewer functionality
  //
  virtual void viewAll();
  virtual void resetToHomePosition();
  virtual void setCamera( SoCamera* cam );
  virtual void setViewing( SbBool onOrOff );
  virtual void setCursorEnabled( SbBool onOrOff );
  virtual void setSeekMode( SbBool onOrOff );

  /** 
   * Roll the camera based on cursor motion.
   * @param newLocator The new cursor position. 
   * The coordinates are in pixels with x in the range [0,window width-1] and
   * y in the range [0,window height-1] with min y at the bottom and min x on the left.
   */
  virtual void rollCamera( const SbVec2s& newLocator );


  /** 
   * Spin the camera based on cursor motion.
   * @param newLocator The new cursor position. 
   * The coordinates are in normalized device coordinates with x and y in the
   * range [0,1] with min y at the bottom and min x on the left.
   */
  virtual void spinCamera( const SbVec2f& newLocator );

  /** 
   * Spin the constrained camera based on cursor motion.
   * @param newLocator The new cursor position. 
   * The coordinates are in normalized device coordinates with x and y in the
   * range [0,1] with min y at the bottom and min x on the left.
   * @param axisIndex the axis index:
   * - X = 0
   * - Y = 1
   * - Z = 2
   */
  virtual void spinConstrainedCamera( const SbVec2f& newLocator, int axisIndex );

  /**
   * Move the camera on the z axis based on cursor motion.
   * This corresponds to pressing left and middle mouse buttons or pressing 
   * control + shift + left mouse button.
   * @param newLocator The new cursor position. 
   * The coordinates are in pixels with x in the range [0,window width-1] and
   * y in the range [0,window height-1] with min y at the bottom and min x on the left.
   */
  virtual void dollyCamera( const SbVec2s& newLocator );

  /** 
   * Same as dollyCamera but reversed.
   * @param newLocator The new cursor position. 
   * The coordinates are in pixels with x in the range [0,window width-1] and
   * y in the range [0,window height-1] with min y at the bottom and min x on the left.
   */
  virtual void reverseDollyCamera( const SbVec2s& newLocator );

  /** 
   * Pans the camera based on cursor motion.
   * @param newLocator The new cursor position. 
   * The coordinates are in normalized device coordinates with x and y in the
   * range [0,1] with min y at the bottom and min x on the left.
   */
  virtual void panCamera( const SbVec2f& newLocator );

  SoEXTENDER public:

  /**
   * Rotates the camera around focal point by given incremental rotation
   * (Given rotation is concatenated onto the current camera rotation)
   */
  virtual void rotateCamera( const SbRotation& rot );

  /** 
   * Constrains the camera to spin around the specified axis. @BR
   * For instance giving true, true, false will prevent the camera from 
   * rotating around the Z axis. Default is free rotation.
   * 
   * @param x If false, rotation around x axis is allowed.
   * @param y If false, rotation around y axis is allowed.
   * @param z If false, rotation around z axis is allowed.
   */
  void constrainCameraRotation( bool x = false, bool y = false, bool z = false );

  SoINTERNAL public:

  SoGuiExaminerViewer* getGuiExaminerViewer() const;


  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoXtExaminerViewer::buildWidget()
  // when they are ready for it to be built.
   SoEXTENDER public:
    SoXtExaminerViewer( SoWidget parent,
                        const char* name,
                        SbBool buildInsideParent,
                        SoXtFullViewer::BuildFlag flag,
                        SoXtViewer::Type type,
                        SbBool buildNow,
                        SbBool sync = TRUE );

 protected:
  // redefine these
  virtual SbString getDefaultWidgetName() const;
  virtual SbString getDefaultTitle() const;
  virtual SbString getDefaultIconTitle() const;

  // redefine those routines to do viewer specific stuff
  virtual void processEvent( XAnyEvent* anyevent );
  virtual void actualRedraw();

  // Get X resources for the widget.
  SoWidget buildWidget( SoWidget parent );

  // Define those thumb wheels to rotate the object
  virtual void bottomWheelMotion( float newVal );
  virtual void leftWheelMotion( float newVal );
  virtual void rightWheelMotion( float newVal );

  // redefine those routines to also stop animation if any
  virtual void bottomWheelStart();
  virtual void leftWheelStart();

  // add viewer preference stuff
  virtual void createPrefSheet();

  // add some viewer buttons
  virtual void createViewerButtons( SoWidget parent );

  // Define this to bring the viewer help card
  virtual void openViewerHelpCard();

 private:
  // viewer state variables
  Cursor spinCursor, panCursor, dollyCursor, seekCursor;
  SbBool firstBuild; // set FALSE after buildWidget called once

  // point of rotation feedback vars
  void createFeedbackNodes();

  // variables used for doing spinning animation
  unsigned long lastMotionTime;
  static void visibilityChangeCB( void* pt, SbBool visible );

  void setViewerMode();
  void updateViewerMode( unsigned int state );
  void switchMode( int newMode );
  void updateCursor();
  void defineCursors();

  // preference sheet stuff
  SoWidget createExamPrefSheetGuts( SoWidget parent );
  static void animPrefSheetToggleCB( SoWidget w, SoXtExaminerViewer* v, void* data );

  // point of rotation pref sheet stuff
  int feedbackSizeWheelVal;
  SoWidget feedbackLabel[2], feedbackField, feedbackSizeWheel;
  static void feedbackSizeWheelCB( SoWidget w, SoXtExaminerViewer* v, XtPointer* d );
  static void feedbackSizeFieldCB( SoWidget w, SoXtExaminerViewer* v, void* data );
  static void feedbackPrefSheetToggleCB( SoWidget w, SoXtExaminerViewer* v, void* data );
  void toggleFeedbackWheelSize( SoWidget toggle );

  // push button vars and callbacks
  SoXtBitmapButton* buttonList[10];
  static void camPushCB( SoWidget w, SoXtExaminerViewer* v, void* data);

  // this is called by both constructors
  void constructorCommon( SbBool buildNow );

  SoGuiExaminerViewer* m_guiExamViewer; // Implementation class for SoXxExaminerViewer

  // Viewer state variables
  SoGuiExaminerViewer::ViewingSpinType m_viewingSpinType;
  ConstrainedViewingMode m_constrainedMode; // Constrained viewing type
};

#endif  /* _SO_XT_EXAMINER_VIEWER_ */

#endif // _WIN32


