/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#if defined(_WIN32)
#  include <Inventor/Win/viewers/SoWinFlyViewer.h>
#else // _WIN32

#ifndef  _SO_XT_MP_FLY_VIEWER_
#define  _SO_XT_MP_FLY_VIEWER_

#include <Inventor/MP/Xt/viewers/SoXtMPConstrainedViewer.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbTime.h>

class   SoFieldSensor;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtFlyViewer
//
//
//      Keys used by this viewer:
//      -------------------------
//
//  Left Mouse: Click to increase speed.
//  
//  \<s\> + Left Mouse: Alternative to the Seek button. Press (but do not
//      hold down) the \<s\> key, then click on a target object.
//  
//  \<U\>  + Left Mouse: Press (but do not hold down) the \<U\>  key, then
//      click on a target object to set the "up" direction to the surface normal.
//      By default +y is the "up" direction.
//  
//  Middle Mouse: Click to decrease speed.
//  
//  Left and Middle Mouse: Click boths simultaneously to stop.
//  
//  Ctrl: Hold the key down to temporary stop and rotate the viewpoint.
//  
//  Right Mouse: Open the popup menu.
//  
//////////////////////////////////////////////////////////////////////////////

/**
 * Viewer component for flying through space, with a constant world up.
 * 
 * @ingroup ScaleVizMultiPipe
 * 
 * @DESCRIPTION
 *   Fly Viewer - this viewer is intended to simulate flight through space, with a
 *   constant world up direction. The viewer only constrains the camera to keep the
 *   user from flying upside down. No mouse buttons need to be pressed in order to
 *   fly. The mouse position is used only for steering, while mouse clicks are used
 *   to increase or decrease the viewer speed.
 *   
 *   The viewer allows you to tilt your head up/down/right/left and move in the
 *   direction you are looking (forward or backward). The viewer also supports seek
 *   to quickly move the camera to a desired object or point.
 * 
 * @RESOURCES
 * <PRE>  
 *   !!------------------------------------------------ 
 *   !! Decorations for Fly Viewer !! 
 *   !!------------------------------------------------ 
 *   *IvFlyTitle.labelString: Fly Viewer 
 *   *IvFlyPrefTitle.labelString: Fly Viewer Preference Sheet 
 *   *IvFlyPopupTitle.labelString: Fly Viewer 
 *   *IvFlyIconTitle.labelString: Fly Viewer 
 *   !! Same for Walk Viewer !! 
 *   *IvFlyWalkRotate.labelString: Rotate 
 *   !! Same for Walk Viewer !! 
 *   *IvFlyWalkTilt.labelString: Tilt 
 *   !! Same for Walk Viewer !! 
 *   *IvFlyWalkDolly.labelString: Dolly 
 *   !!------------------------------------------------ 
 *   !! Preferences for Fly Viewer !! 
 *   !!------------------------------------------------ 
 *   *FlyPreference.FlyingSpeed.labelString: Flying speed: 
 *   *FlyPreference.Increase.labelString: increase 
 *   *FlyPreference.Decrease.labelString: decrease 
 * </PRE>
 * 
 * @USAGE
 *  (For 3-button mouse only.)
 *   
 *   @B Left Mouse: @b Click to increase speed.
 *   
 *   @B \<s\> + Left Mouse: @b Alternative to the Seek button. Press (but do not hold
 *   down) the \<s\> key, then click on a target object.
 *   
 *   @B \<U\>  + Left Mouse: @b Press (but do not hold down) the \<U\>  key, then click on
 *   a target object to set the "up" direction to the surface normal. By default +y
 *   is the "up" direction.
 *   
 *   @B Middle Mouse: @b Click to decrease speed.
 *   
 *   @B Left and Middle Mouse: @b Click both simultaneously to stop.
 *   
 *   @B Ctrl: @b Hold the key down to temporarily stop and rotate the viewpoint.
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
 *    SoXtExaminerViewer,
 *    SoXtPlaneViewer
 * 
 * 
 */ 

class INVENTORXT_API SoXtMPFlyViewer : public SoXtMPConstrainedViewer {
 public:
    
  /**
   * Constructor which specifies the viewer type. Please refer to the
   * SoXtViewer reference page for a description of the viewer types.
   */
  SoXtMPFlyViewer(
                  SoWidget parent = NULL,
                  const char *name = NULL, 
                  SbBool buildInsideParent = TRUE, 
                  SoXtMPFullViewer::BuildFlag flag = BUILD_ALL,
                  SoXtMPViewer::Type type = BROWSER);
  /**
   * Destructor.
   */
  ~SoXtMPFlyViewer();
    
  //
  // redefine these to add fly viewer functionality
  //
  virtual void    setViewing(SbBool onOrOff);
  virtual void    resetToHomePosition();
  virtual void    setCamera(SoCamera *cam);
  virtual void    setCursorEnabled(SbBool onOrOff);
    
  // This is redefined to prevent the camera type from being changed 
  virtual void    setCameraType(SoType type);

  // set/get minimum speed in word coodinate / second
  // default value is 0, meaning the minimum speed is computed according to scene graph extent
  void  setMinSpeed( float speed );
  float getMinSpeed();

  // set/get speed multiplier. default value is 1.5
  void  setSpeedMultiplier( float speedInc );
  float getSpeedMultiplier();
    
 protected:
  
  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoXtFlyViewer::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
    SoXtMPFlyViewer(
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
    
  // add viewer preference stuff
  virtual void        createPrefSheet();
    
  // Define this to bring the viewer help card
  virtual void        openViewerHelpCard();
    
 private:
  // viewer state variables
  int             mode;
  SbBool          createdCursors;
  //    Cursor        viewerCursor, seekCursor, upCursor;
  Cursor          *viewerCursor, *seekCursor, *upCursor;

  SbVec2s         locator; // mouse position
  SbVec2s         startPos; // mouse starting position
  SbRotation      camStartOrientation;
    
  // variables used for doing moving animation
  SoFieldSensor   *animationSensor;
  SbTime          prevAnimTime;
  float           speed, maxSpeed, maxStraightSpeed;
  float           speedLimit, speedLimitFactor;
  float           minSpeed, maxInc;
    
  // preference sheet stuff
  SoWidget          createFlyPrefSheetGuts(SoWidget parent);
  static void     incPrefSheetButtonCB(SoWidget, SoXtMPFlyViewer *, void *);
  static void     decPrefSheetButtonCB(SoWidget, SoXtMPFlyViewer *, void *);
    
  void            defineCursors();
  void            drawViewerFeedback();
  void            switchMode(int newMode);
  void            changeMaxStraightSpeed(SbBool increase);
  void            calculateMaxSpeed();
  static void     animationSensorCB(void *, SoSensor *);
  void            doCameraAnimation();

  // this is called by both constructors
  void constructorCommon(SbBool buildNow);
        
  // define and undefined cursor in each window created by MP
  void mpXDefineCursor(Cursor *);
  void mpXUndefineCursor(void);

};

#endif  /* _SO_XT_MP_FLY_VIEWER_ */

#endif // _WIN32


