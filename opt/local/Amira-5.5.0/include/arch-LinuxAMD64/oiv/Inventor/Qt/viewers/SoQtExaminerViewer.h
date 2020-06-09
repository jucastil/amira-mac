/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Alain Dumesny (MMM yyyy)
**=======================================================================*/


#ifndef _SO_QT_EXAMINER_VIEWER_
#define _SO_QT_EXAMINER_VIEWER_
#include <Inventor/Qt/OivQtCompat.h>
#include <Inventor/Qt/viewers/SoQtFullViewer.h>
#include <Inventor/SbLinear.h>

#include <QtCore/QPointer>
#include <QtGui/QCursor>

#include <Inventor/Gui/viewers/SoGuiExaminerViewer.h>
// classes used
class SbSphereSheetProjector;
class SoFieldSensor;
class SoSeparator;
class SoSwitch;
class SoTranslation;
class SoScale;

class SbTime;

//////////////////////////////////////////////////////////////////////////////
//
// Class: SoQtExaminerViewer
//
//  Examiner viewer - allows the user to change the camera position
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
//  away from the object).
//
//  Shift + Ctrl + Left Mouse: Dolly in and out (same as Left + Middle
//  behavior but added by VSG to support the
//  standard Microsoft 2-button mouse).
//
//      \<s\> + click: Alternative to the Seek button. Press (but do not hold 
//                         down) the \<s\> key, then click on a target object.
//
//      Right Mouse: Open the popup menu.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Viewer component which uses a virtual trackball to view the data.
 * 
 * @ingroup Qt
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
 * @USAGE
 *  (For 3-button mouse only.)
 *   
 *   @B Left Mouse: @b Rotate the virtual trackball.
 *   
 *   @B Middle Mouse or @b
 *   @B Ctrl + Left Mouse: @b Translate up, down, left, right.
 *   
 *   @B Ctrl + Middle Mouse or @BR
 *   Left + Middle Mouse: @b Dolly in and out (gets closer to and further away from
 *   the object).
 *   
 *   @B 's' + Left Mouse: @b Alternative to the Seek button. Press (but do not hold
 *   down) the 's' key, then click on a target object. 
 *   
 *   @B Right Mouse: @b Open the popup menu.
 *  
 *   @B ALT:@b When the viewer is in selection (a.k.a. pick) mode, pressing
 *   and holding the ALT key temporarily switches the viewer to viewing mode. When
 *   the ALT key is released, the viewer returns to selection mode. <br> Note 1: If any of
 *   the mouse buttons are currently depressed, the ALT key has no effect.
 *   <br>Note 2: On UNIX, Open Inventor may lose track of the ALT key state (up or down)
 *   if you release the key outside of the Inventor window. Pressing and releasing
 *   the key inside the Inventor window will allow Open Inventor to once again know
 *   the key's correct state.
 *   <br>Note 3: If your QtExaminerViewer is encapsulated in a QMain window, the
 *    QMenuBar may receive the ALT key press event before the QtExaminerViewer. If this
 *    happens, the ALT key won't have any effect on the viewer's viewing mode.
 * 
 * @SEE_ALSO
 *    SoQtFullViewer,
 *    SoQtViewer,
 *    SoQtComponent,
 *    SoQtRenderArea,
 *    SoQtWalkViewer,
 *    SoQtFlyViewer,
 *    SoQtPlaneViewer
 * 
 * 
 */ 

class INVENTORQT_API SoQtExaminerViewer : public SoQtFullViewer 
{

  Q_OBJECT

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
    * Roll the camera in the viewer plane
    */
    VIEWING_MODE_ROLL,

    /**
    * Dolly/Zoom (move forward and backward) to
    *   get closer to or further away from the point of interest.
    */
    VIEWING_MODE_ZOOM
  } ;

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
  } ;

  /**
   * Constructor which specifies the viewer type. Please refer to 
   * SoQtViewer for a description of the viewer types.
   */
  SoQtExaminerViewer( QWidget* parent = NULL,
                      const char* name = NULL, 
                      SbBool buildInsideParent = TRUE, 
                      SoQtFullViewer::BuildFlag flag = SoQtFullViewer::BUILD_ALL, 
                      SoQtViewer::Type type = SoQtViewer::BROWSER );
  /**
   * Destructor.
   */
  ~SoQtExaminerViewer();

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
   * Enables/disables the spin animation feature of the viewer (enabled by
   * default).@BR
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
   * This corresponds to pressing left and middle mouse buttons, pressing 
   * control + shift + left mouse button or using the mouse wheel.
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

  SoINTERNAL public:

  SoGuiExaminerViewer* getGuiExaminerViewer() const;

  virtual void setViewingMode( int viewingMode ) { setViewingMode( ViewingMode(viewingMode) ); };

  SoEXTENDER public:

  /**
   * Rotates the camera around focal point by given incremental rotation
   * (Given rotation is concatenated onto the current camera rotation)
   */
  virtual void rotateCamera( const SbRotation& rot );

  /**
   * Constrains the camera to spin around the specified axis. @BR
   * For instance giving true, true, false will prevent the camera from 
   * rotating around the Z axis.  Default is free rotation.
   * 
   * @param x If false, rotation around x axis is allowed.
   * @param y If false, rotation around y axis is allowed.
   * @param z If false, rotation around z axis is allowed.
   */
  void constrainCameraRotation( bool x = false, bool y = false, bool z = false );

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoQtExaminerViewer::buildWidget()
  // when they are ready for it to be built.
  SoQtExaminerViewer( QWidget* parent,
                      const char* name, 
                      SbBool buildInsideParent, 
                      SoQtFullViewer::BuildFlag flag, 
                      SoQtViewer::Type type, 
                      SbBool buildNow,
                      SbBool sync = true );
 protected:

  // redefine these
  virtual SbString getDefaultWidgetName() const;
  virtual SbString getDefaultTitle() const;
  virtual SbString getDefaultIconTitle() const;

  // redefine those routines to do viewer specific stuff
  virtual void processEvent( QEvent* anyevent );
  virtual void actualRedraw();

  // Get X resources for the widget.
  QWidget* buildWidget( QWidget* parent );

  // Define those thumb wheels to rotate the object
  virtual void bottomWheelMotion( float newVal );
  virtual void leftWheelMotion( float newVal );
  virtual void rightWheelMotion( float newVal );
  virtual void mouseWheelMotion( float newVal );

  // redefine those routines to also stop animation if any
  virtual void bottomWheelStart();
  virtual void leftWheelStart();

  // add viewer preference stuff
  virtual void createPrefSheet();

  // add some viewer buttons
  virtual void createViewerButtons( QWidget*  parent );

  // build examiner viewer specific popup menu
  // Note: Examiner viewer uses a slightly different popup menu
  // resource that has two more items in the preferences submenu.
  virtual void buildPopupMenu();

  // Define this to bring the viewer help card
  virtual void openViewerHelpCard();

  virtual void pushButtonCB( int id );

  virtual void updateCursor();

  virtual void switchMode( int newMode );

  virtual void doSpinAnimation();

  int mode;

  SbVec2s locator; // mouse position

private:
  SoGuiExaminerViewer* m_guiExamViewer; // Implementation class for SoXxExaminerViewer

  // Viewer state variables
  SoGuiExaminerViewer::ViewingSpinType m_viewingSpinType;
  ConstrainedViewingMode m_constrainedMode; // Constrained viewing type

  SbBool firstBuild; // set FALSE after buildWidget called once

  // variables used for doing spinning animation
  SbTime lastMotionTime;

  void setViewerMode();
  void updateViewerMode( unsigned int state );

  // push button vars and callbacks
  QPointer<SoQtButton> buttonList[10];
  static void camPushCB( SoQtExaminerViewer* v);

  // this is called by both constructors
  void constructorCommon( SbBool buildNow );

  //pixmap
  QPixmap IDB_PUSH_PERSP;
  QPixmap IDB_PUSH_ORTHO;

#ifndef HIDDEN_FROM_DOC
  private Q_SLOTS:
    //slot for cam button
    void slotCamPushButton();

  //preference menu
  void slot_popup_spin();
  void slot_popup_axes();
 
#endif // HIDDEN_FROM_DOC

  private Q_SLOTS:
    void visibilityChangeCB( SbBool visible );

};

#endif /* _SO_QT_EXAMINER_VIEWER_ */
