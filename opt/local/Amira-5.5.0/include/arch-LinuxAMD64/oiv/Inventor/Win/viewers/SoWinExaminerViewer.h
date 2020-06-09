/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/



#ifndef _SO_WIN_EXAMINER_VIEWER_
#define _SO_WIN_EXAMINER_VIEWER_

#include <Inventor/Win/SoWinBeginStrict.h>

#include <Inventor/Win/viewers/SoWinFullViewer.h>
#include <Inventor/SbLinear.h>

#include <Inventor/Gui/viewers/SoGuiExaminerViewer.h>

// classes used
class SbSphereSheetProjector;
class SoFieldSensor;
class SoSeparator;
class SoSwitch;
class SoTranslation;
class SoScale;
class SoWinBitmapButton;

//////////////////////////////////////////////////////////////////////////////
//
// Class: SoWinExaminerViewer
//
//  Examiner viewer - allows the user to change the camera position
//  by spinning a sphere in front of the viewpoint.
//
//
//  Keys used by this viewer:
//  -------------------------
//
//  Left Mouse: Tumbles the virtual trackball.
//
//  Middle Mouse: 
//  Ctrl + Left Mouse: Translate up, down, left and right.
//
//  Ctrl + Middle Mouse: 
//  Left + Middle Mouse: Dolly in and out (gets closer to and further
//  away from the object).
//
//  Shift + Ctrl + Left Mouse: Dolly in and out (same as Left + Middle
//  behavior but added by VSG to support the
//  standard Microsoft 2-button mouse).
//
//  \<s\> + click: Alternative to the Seek button. Press (but do not hold 
//               down) the \<s\> key, then click on a target object.
//
//  Right Mouse: Open the popup menu.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Viewer component which uses a virtual trackball to view the data.
 * 
 * @ingroup Win
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
 *   @B ALT:@b When the viewer is in selection (a.k.a. pick) mode, pressing
 *   and holding the ALT key temporarily switches the viewer to viewing mode. When
 *   the ALT key is released, the viewer returns to selection mode. Note: If any of
 *   the mouse buttons are currently depressed, the ALT key has no effect.
 * 
 * @SEE_ALSO
 *    SoWinFullViewer,
 *    SoWinViewer,
 *    SoWinComponent,
 *    SoWinRenderArea,
 *    SoWinWalkViewer,
 *    SoWinFlyViewer,
 *    SoWinPlaneViewer
 * 
 * 
 */ 

class INVENTORW_API SoWinExaminerViewer : public SoWinFullViewer 
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
    CONSTRAINED_VIEWING_MODE_Z,
  };

  /**
   * Constructor which specifies the viewer type. Please refer to 
   * SoWinViewer for a description of the viewer types. [_WIN32] Note:
   * On Windows, the constructor will not create a new top level window -- you must
   * pass a valid window handle for the @B parent @b parameter and pass TRUE for
   * @B buildInsideParent @b.
   */
  SoWinExaminerViewer( SoWidget parent = NULL,
                       const char* name = NULL, 
                       SbBool buildInsideParent = TRUE, 
                       SoWinFullViewer::BuildFlag flag = SoWinFullViewer::BUILD_ALL, 
                       SoWinViewer::Type type = SoWinViewer::BROWSER );
  /**
   * Destructor.
   */
  ~SoWinExaminerViewer();

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

  //////////////////////////////////////////////////////////////////////
  // Constrained viewer.
  /**
   * @VSGEXT Viewing Function: Abstract base class for viewing function classes.
   *
   * @DESCRIPTION
   *   This is the viewing function base class. 
   *
   *   See SoWinExaminerViewer::addFunctionKeyBinding
   *   or SoWinExaminerViewer::addViewingMouseBinding for additional info.
   * 
   * 
   * 
   */  
  class INVENTORW_API SoViewingFunction 
  {
  public:
    /**
     *  Sets the viewer that the function applies to.
     */
    void setViewer(SoWinViewer* viewer) { m_viewer = viewer; }

    /**
     * Applies this manipulation to a specified combination of key and mouse button.
     */
    virtual void apply() const = 0;

    protected:
    SoWinViewer* m_viewer;
  };
 
  /**
   *  
   * @VSGEXT Viewing Function: Rotates the view around a point of interest using a virtual trackball.
   * 
   * @ingroup Win
   *
   * @DESCRIPTION
   *   This class can be used with the SoWinExaminerViewer addFunctionKeyBinding and
   *   addViewingMouseBinding methods to customize the behavior of the viewer.
   *
   *   See SoWinExaminerViewer::addFunctionKeyBinding
   *   or SoWinExaminerViewer::addViewingMouseBinding for additional info.
   * 
   * 
   */  

  class INVENTORW_API SoViewingSphericalRotation : public SoViewingFunction 
  {
  private:
    /**
     * Applies this manipulation.
     */
    void apply() const;
  };
  
  /**
   * @VSGEXT Viewing Function: Translates the camera in the viewer plane.
   *
   * @ingroup Win
   *
   * @DESCRIPTION
   *   This class can be used with the SoWinExaminerViewer addFunctionKeyBinding and
   *   addViewingMouseBinding methods to customize the behavior of the viewer.
   *
   *   See SoWinExaminerViewer::addFunctionKeyBinding
   *   or SoWinExaminerViewer::addViewingMouseBinding for additional info.
   */
  class INVENTORW_API SoViewingTranslation : public SoViewingFunction 
  {
  private:
    /**
     * Applies this manipulation.
     */
    void apply() const;
  };

  /**
   *  
   * @VSGEXT Viewing Function: Rotates the object around the X axis.
   *
   * @ingroup Win
   *
   * @DESCRIPTION
   *   This class can be used with the SoWinExaminerViewer addFunctionKeyBinding and
   *   addViewingMouseBinding methods to customize the behavior of the viewer.
   *
   *   See SoWinExaminerViewer::addFunctionKeyBinding
   *   or SoWinExaminerViewer::addViewingMouseBinding for additional info.
   */
  class INVENTORW_API SoViewingRotationX : public SoViewingFunction 
  {
  private:
    /**
     * Applies this manipulation.
     */
    void apply() const;
  };
  
  /**
   * @VSGEXT Viewing Function: Rotates the object around the Y axis.
   *
   * @ingroup Win
   *
   * @DESCRIPTION
   *   This class can be used with the SoWinExaminerViewer addFunctionKeyBinding and
   *   addViewingMouseBinding methods to customize the behavior of the viewer.
   *
   *   See SoWinExaminerViewer::addFunctionKeyBinding
   *   or SoWinExaminerViewer::addViewingMouseBinding for additional info.
   */
  class INVENTORW_API SoViewingRotationY : public SoViewingFunction 
  {
  private:
    /**
     * Applies this manipulation.
     */
    void apply() const;
  };

  /**
   * @VSGEXT Viewing Function: Rotates the object around the Z axis.
   *
   * @ingroup Win
   *
   * @DESCRIPTION
   *   This class can be used with the SoWinExaminerViewer addFunctionKeyBinding and
   *   addViewingMouseBinding methods to customize the behavior of the viewer.
   *
   *   See SoWinExaminerViewer::addFunctionKeyBinding
   *   or SoWinExaminerViewer::addViewingMouseBinding for additional info.
   */
  class INVENTORW_API SoViewingRotationZ : public SoViewingFunction 
  {
  private:
    /**
     * Applies this manipulation.
     */
    void apply() const;
  };

  /**
   * @VSGEXT Viewing Function: Rotates the object around the screen X axis.
   *
   * @ingroup Win
   *
   * @DESCRIPTION
   *   This class can be used with the SoWinExaminerViewer addFunctionKeyBinding and
   *   addViewingMouseBinding methods to customize the behavior of the viewer.
   *
   *   See SoWinExaminerViewer::addFunctionKeyBinding
   *   or SoWinExaminerViewer::addViewingMouseBinding for additional info.
   */
  class INVENTORW_API SoViewingRotationXViewer : public SoViewingFunction 
  {
  private:
    /**
     * Applies this manipulation.
     */
    void apply() const;
  };

  /**
   *  
   * @VSGEXT Viewing Function: Rotates the object around the screen Y axis.
   * @ingroup Win
   *
   * @DESCRIPTION
   *   This class can be used with the SoWinExaminerViewer addFunctionKeyBinding and
   *   addViewingMouseBinding methods to customize the behavior of the viewer.
   *
   *   See SoWinExaminerViewer::addFunctionKeyBinding
   *   or SoWinExaminerViewer::addViewingMouseBinding for additional info.
   */
  class INVENTORW_API SoViewingRotationYViewer : public SoViewingFunction 
  {
  private:
    /**
     * Applies this manipulation.
     */
    void apply() const;
  };

  /**
   * @VSGEXT Viewing Function: Rotates the object around the screen Z axis.
   *
   * @ingroup Win
   *
   * @DESCRIPTION
   *   This class can be used with the SoWinExaminerViewer addFunctionKeyBinding and
   *   addViewingMouseBinding methods to customize the behavior of the viewer.
   *
   *   See SoWinExaminerViewer::addFunctionKeyBinding
   *   or SoWinExaminerViewer::addViewingMouseBinding for additional info.
   */
  class INVENTORW_API SoViewingRotationZViewer : public SoViewingFunction 
  {
  private:
    /**
     * Applies this manipulation.
     */
    void apply() const;
  };

  /**
   * @VSGEXT Viewing Function: Seek (to quickly move the camera to a desired object or point).
   *
   * @ingroup Win
   *
   * @DESCRIPTION
   *   This class can be used with the SoWinExaminerViewer addFunctionKeyBinding and
   *   addViewingMouseBinding methods to customize the behavior of the viewer.
   *
   *   See SoWinExaminerViewer::addFunctionKeyBinding
   *   or SoWinExaminerViewer::addViewingMouseBinding for additional info.
   */
  class INVENTORW_API SoViewingSeek : public SoViewingFunction 
  {
  private:
    /**
     * Applies this manipulation.
     */
    void apply() const;
  };

  /**
   * @VSGEXT Viewing Function: Dolly (move forward and backward) to get closer to or 
   * further away from the point of interest.
   *
   * @ingroup Win
   *
   * @DESCRIPTION
   *   This class can be used with the SoWinExaminerViewer addFunctionKeyBinding and
   *   addViewingMouseBinding methods to customize the behavior of the viewer.
   *
   *   See SoWinExaminerViewer::addFunctionKeyBinding
   *   or SoWinExaminerViewer::addViewingMouseBinding for additional info.
   */
  class INVENTORW_API SoViewingDolly : public SoViewingFunction 
  {
  private:
    /**
     * Applies this manipulation.
     */
    void apply() const;
  };

  /**
   * @VSGEXT Viewing Function: Reverse Dolly (move backward and forward) to get further to or 
   * closer away from the point of interest.
   *
   * @ingroup Win
   *
   * @DESCRIPTION
   *   This class can be used with the SoWinExaminerViewer addFunctionKeyBinding and
   *   addViewingMouseBinding methods to customize the behavior of the viewer.
   *
   *   See SoWinExaminerViewer::addFunctionKeyBinding
   *   or SoWinExaminerViewer::addViewingMouseBinding for additional info.
   */
  class INVENTORW_API SoViewingReverseDolly : public SoViewingFunction 
  {
  private:
    /**
     * Applies this manipulation.
     */
    void apply() const;
  };

  /**
   * @VSGEXT Viewing Function: Does nothing.
   *
   * @ingroup Win
   *
   * @DESCRIPTION
   *   This class can be used with the SoWinExaminerViewer addFunctionKeyBinding and
   *   addViewingMouseBinding methods to customize the behavior of the viewer.
   *
   *   See SoWinExaminerViewer::addFunctionKeyBinding
   *   or SoWinExaminerViewer::addViewingMouseBinding for additional info.
   */
  class INVENTORW_API SoViewingEmpty : public SoViewingFunction 
  {
  private:
    /**
     * Applies this manipulation.
     */
    void apply() const;
  };

  /**
   * Adds a new function key binding to the viewer. This method allows you
   * to associate a keyboard key with a viewing function, such as rotation or translation.
   * The specified viewing function replaces the viewing function currently associated
   * with the specified key.
   * 
   * A key cannot be associated with more than one viewing function at a time. However,
   * more than one key can be associated with a single viewing function. For
   * example, the S and T keys could each be used to invoke the seek operation.
   */
  virtual void addFunctionKeyBinding( SoKeyboardEvent::Key key, const SoViewingFunction* viewingFunc );

  /**
   * Removes the specified function key binding (if it exists).
   */
  virtual void removeFunctionKeyBinding( SoKeyboardEvent::Key functionKey );

  /**
   * Adds a new mouse binding to the viewer. This method allows you
   * to associate an array of modifier keys (of length numKey) and an array of 
   * mouse buttons (of length numMouseBtn) with a viewing operation, such as rotation
   * or translation.
   * The specified viewing function replaces the viewing function currently associated
   * with the specified key and mouse button sequence.
   *
   * Modifiers (CTRL, SHIFT, CTRL+SHIFT...) can be added in addition to the 
   * mouse buttons chosen. The order of the keys and the mouse buttons is 
   * important. 
   * For example, CTRL+SHIFT+BT1 is different from SHIFT+CTRL+BT1. 
   * Likewise, CTRL+BT1+BT2 is different from CTRL+BT2+BT1.
   *
   * A key and mouse button sequence cannot be associated with more than one viewing
   * function at a time. However,
   * more than one key and mouse button sequence can be associated with a 
   * single viewing function. 
   */
  virtual void addViewingMouseBinding( SoKeyboardEvent::Key* keys = NULL, 
                                       int numKey = 0,
                                       SoMouseButtonEvent::Button *mouseBtn = NULL, 
                                       int numMouseBtn = 0,
                                       const SoViewingFunction *viewingFunc = NULL );
  /**
   * Removes a mouse binding (if it exists). The key and button order is important. 
   * For example, CTRL+SHIFT+BT1 is different from SHIFT+CTRL+BT1. Likewise, CTRL+BT1+BT2
   * is different from CTRL+BT2+BT1.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  virtual void removeViewingMouseBinding( SoKeyboardEvent::Key* keys = NULL,
                                          int numKeys = 0,
                                          SoMouseButtonEvent::Button* mouseBtn = NULL,
                                          int numMouseBtn = 0 );

  // End Constrained viewer.

  //////////////////////////////////////////////////////////////////
  // Defines the list of functions that supports this viewer.
  //////////////////////////////////////////////////////////////////

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
   * default).
   * 
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

  // redefine these to add Examiner viewer functionality
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
  virtual void rollCamera( const SbVec2s &newLocator );

  /** 
   * Spin the camera based on cursor motion.
   * @param newLocator The new cursor position. 
   * The coordinates are in normalized device coordinates with x and y in the
   * range [0,1] with min y at the bottom and min x on the left.
   */
  virtual void spinCamera( const SbVec2f &newLocator );

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
  virtual void dollyCamera( const SbVec2s &newLocator );

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

 protected:

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoWinExaminerViewer::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
    SoWinExaminerViewer( SoWidget parent,
                         const char* name, 
                         SbBool buildInsideParent, 
                         SoWinFullViewer::BuildFlag flag, 
                         SoWinViewer::Type type, 
                         SbBool buildNow,
                         SbBool sync = TRUE );

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
  virtual void mouseWheelMotion( float newVal );

  // redefine those routines to also stop animation if any
  virtual void bottomWheelStart();
  virtual void leftWheelStart();

  // add viewer preference stuff
  virtual void createPrefSheet();

  // add some viewer buttons
  virtual void createViewerButtons( SoWidget parent );

  // build examiner viewer specific popup menu
  // Note: Examiner viewer uses a slightly different popup menu
  // resource that has two more items in the preferences submenu.
  virtual void buildPopupMenu();

  // Define this to bring the viewer help card
  virtual void openViewerHelpCard();

  // It's a long story, but since we can't attach callbacks to a window
  // quite like we can to an Xt widget, it makes more sense for the
  // subclass viewer to handle the buttons it knows about then pass
  // the rest back up to SoWinFullViewer.
  //
  // So WINxx this function must be virtual and protected, not private.
  virtual void pushButtonCB( SoWidget w, int id, void* data );

  virtual void doSpinAnimation();

 private:
  SoGuiExaminerViewer* m_guiExamViewer; // Implementation class for SoXxExaminerViewer

  // Viewer state variables
  SoGuiExaminerViewer::ViewingSpinType m_viewingSpinType;
  ConstrainedViewingMode m_constrainedMode; // Constrained viewing type

  SbBool firstBuild; // set FALSE after buildWidget called once

  // point of rotation feedback vars
  static char* geometryBuffer;

  // variables used for doing spinning animation
  long lastMotionTime;
  static void visibilityChangeCB( void* pt, SbBool visible );

 SoINTERNAL public:

  // viewer state variables
  int m_mouseReady; 
  SbBool m_viewingOnOffFlag;
 
  int m_prevFlag;
  
  void updateViewerMode( unsigned int state );
  void switchMode( int newMode );
  void setViewerMode();
  void updateCursor();

  // push button vars and callbacks
  SoWinBitmapButton* buttonList[10];
  static void camPushCB( SoWidget w, SoWinExaminerViewer* v, void* data );

  // this is called by both constructors
  void constructorCommon( SbBool buildNow );

  // Utility function called from processEvent
  void processPopupItem( int item );
};

#include <Inventor/Win/SoWinEndStrict.h>

#endif /* _SO_WIN_EXAMINER_VIEWER_ */

