/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#if defined(_WIN32)
#  include <Inventor/Win/viewers/SoWinWalkViewer.h>
#else // _WIN32

#ifndef  _SO_XT_WALK_VIEWER_
#define  _SO_XT_WALK_VIEWER_

#include <Inventor/MP/Xt/viewers/SoXtMPConstrainedViewer.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbTime.h>

class   SoFieldSensor;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtWalkViewer
//
//      Walk Viewer - changes the camera position by simulating the constrain
//  on someone walking. The up direction is kept at all times, and the camera
//  is moved keeping the eye level the same, regardless of whether the person
//  is looking down or up (looking direction is constrained to 180 degree).
//
//
//      Keys used by this viewer:
//      -------------------------
//
//     Left Mouse: walk mode. Click down and move up/down for fowards/backwards
//          motion.  Move right and left for turning. Speed increases 
//          exponentially with the distance from the mouse-down origin.
//
//     Middle Mouse: 
//     Ctrl + Left Mouse: Translate up, down, left and right.
//
//     Ctrl + Middle Mouse: tilt the camera up/down and right/left. This 
//          allows you to look around while stopped.
//
//     \<s\> + click: Alternative to the Seek button. Press (but do not hold down)
//          the \<s\> key, then click on a target object.
//
//     \<U\>  + click: Press (but do not hold down) the \<U\>  key, then
//          click on a target object to set the "up" direction to the surface
//          normal. By default +y is the "up" direction.
//
//     Right Mouse: Open the popup menu.
//  
//////////////////////////////////////////////////////////////////////////////

/**
 * Viewer component which moves the camera in a plane.
 * 
 * @ingroup ScaleVizMultiPipe
 * 
 * @DESCRIPTION
 *   The paradigm for this viewer is a walk-through of an architectural model. Its
 *   primary behavior is forward, backward, and left/right turning motion while
 *   maintaining a constant "eye level". It is also possible to stop and look around
 *   at the scene. The eye level plane can be disabled, allowing the viewer to
 *   proceed in the "look at" direction, as if on an escalator. The eye level plane
 *   can also be translated up and down - similar to an elevator.
 * 
 * @RESOURCES
 * <PRE>  
 *   !!------------------------------------------------ 
 *   !! Decorations for Walk Viewer !! 
 *   !!------------------------------------------------ 
 *   *IvWalkTitle.labelString: Walk Viewer 
 *   *IvWalkPrefTitle.labelString: Walk Viewer Preference Sheet 
 *   *IvWalkPopupTitle.labelString: Walk Viewer 
 *   *IvWalkIconTitle.labelString: Walk Viewer 
 *   *IvLeftTrimForm.IvH.labelString: H 
 *   !!------------------------------------------------ 
 *   !! Preferences for Walk Viewer !! 
 *   !!------------------------------------------------ 
 *   *IvFormPreference5.IvViewerSpeed.labelString: Viewer speed 
 *   *IvFormPreference5.IvIncrease.labelString: increase 
 *   *IvFormPreference5.IvDecrease.labelString: decrease 
 * </PRE>
 * 
 * @USAGE
 *  (For 3-button mouse only.)
 *   
 *   @B Left Mouse: @b Walk mode. Click down and move up and down for forwards and
 *   backwards motion. Move right and left for turning. Speed increases exponentially
 *   with the distance from the mouse-down origin.
 *   
 *   @B Middle Mouse or @BR
 *   Ctrl + Left Mouse: @b Translate up, down, left, and right.
 *   
 *   @B Ctrl + Middle Mouse: @b Tilt the camera up/down and right/left. This allows
 *   you to look around while stopped.
 *   
 *   @B \<s\> + Left Mouse: @b Alternative to the Seek button. Press (but do not hold
 *   down) the \<s\> key, then click on a target object.
 *   
 *   @B \<U\>  + Left Mouse: @b Press (but do not hold down) the \<U\>  key, then click on
 *   a target object to set the "up" direction to the surface normal. By default +y
 *   is the "up" direction.
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
 *    SoXtPlaneViewer,
 *    SoXtExaminerViewer,
 *    SoXtFlyViewer
 * 
 * 
 */ 

class INVENTORXT_API SoXtMPWalkViewer : public SoXtMPConstrainedViewer {
 public:
    
  /**
   * Constructor which specifies the viewer type. Please refer to the
   * SoXtViewer reference pages for a description of the viewer types.
   */
  SoXtMPWalkViewer(
                   SoWidget parent = NULL,
                   const char *name = NULL, 
                   SbBool buildInsideParent = TRUE, 
                   SoXtMPFullViewer::BuildFlag flag = BUILD_ALL, 
                   SoXtMPViewer::Type type = BROWSER);
  /**
   * Destructor.
   */
  ~SoXtMPWalkViewer();
    
  //
  // redefine these to add Walk viewer functionality
  //
  virtual void    setViewing(SbBool onOrOff);
  virtual void    setCamera(SoCamera *cam);
  virtual void    setCursorEnabled(SbBool onOrOff);
    
  // This is redefined to prevent the camera type from being changed 
  virtual void    setCameraType(SoType type);
        
        
 protected:
  
  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoXtWalkViewer::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
    SoXtMPWalkViewer(
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
  virtual void        actualRedraw();
  virtual void        rightWheelMotion(float);
    
  // redefine this to add the extra thumbwheel on the left side
  virtual SoWidget      buildLeftTrim(SoWidget parent);
    
  // add viewer preference stuff
  virtual void        createPrefSheet();
    
  // Define this to bring the viewer help card
  virtual void        openViewerHelpCard();
    
 private:
  // viewer state variables
  int             mode;
  SbBool          createdCursors;
  /*    Cursor        walkCursor, panCursor, tiltCursor, seekCursor, upCursor;*/
  Cursor          *walkCursor, *panCursor, *tiltCursor, *seekCursor, *upCursor;
  SbVec2s         locator; // mouse position
  SbVec2s         prevPos; // mouse previous location
  SbVec2s         startPos; // mouse starting position
    
  // extra decoration vars
  int             heightWheelVal;
  static void     heightWheelCB(SoWidget, SoXtMPWalkViewer *p, XtPointer *d);
    
  // variables used for doing moving animation
  SoFieldSensor   *animationSensor;
  SbBool          animatingFlag;
  SbTime          prevAnimTime;
  void            startAnimating();
  void            stopAnimating();
  static void     animationSensorCB(void *v, SoSensor *);
    
  void            updateViewerMode(unsigned int state);
  void            switchMode(int newMode);
  void            updateCursor();
  void            defineCursors();
  void            doCameraAnimation();
  void            dollyCamera(float dist);
  void            rotateCamera();
    
  // focal distance update stuff
  void                updateCameraFocalPoint();
  static void         setFocalPointFinishCallback(void *, SoXtMPViewer *);
    
  // this is called by both constructors
  void constructorCommon(SbBool buildNow);
        
  void mpXDefineCursor(Cursor * cursorToSetActive);
        
 public:
  void drawViewerFeedback(void);


};

#endif  /* _SO_XT_MP_WALK_VIEWER_ */

#endif // _WIN32

