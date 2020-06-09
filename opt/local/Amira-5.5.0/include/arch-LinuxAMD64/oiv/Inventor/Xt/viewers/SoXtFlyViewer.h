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
#  include <Inventor/Qt/viewers/SoQtFlyViewer.h>
#elif defined _WIN32
#  include <Inventor/Win/viewers/SoWinFlyViewer.h>
#else // _WIN32

#ifndef  _SO_XT_FLY_VIEWER_
#define  _SO_XT_FLY_VIEWER_

#include <Inventor/Xt/viewers/SoXtConstrainedViewer.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbTime.h>
#include <Inventor/Gui/viewers/SoGuiFlyViewer.h>

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
 * @ingroup Xt
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

class INVENTORXT_API SoXtFlyViewer : public SoXtConstrainedViewer 
{
 public:
    
  /**
   * Constructor which specifies the viewer type. Please refer to the
   * SoXtViewer reference page for a description of the viewer types.
   */
  SoXtFlyViewer( SoWidget parent = NULL, 
                 const char* name = NULL, 
                 SbBool buildInsideParent = TRUE, 
                 SoXtFullViewer::BuildFlag flag = SoXtFullViewer::BUILD_ALL,
                 SoXtViewer::Type type = SoXtViewer::BROWSER );

  /**
   * Destructor.
   */
  ~SoXtFlyViewer();
    
  // redefine these to add fly viewer functionality
  virtual void setViewing( SbBool onOrOff );
  virtual void resetToHomePosition();
  virtual void setCamera( SoCamera* cam );
  virtual void setCursorEnabled( SbBool onOrOff );
  virtual void setSeekMode( SbBool onOrOff );
    
  // This is redefined to prevent the camera type from being changed 
  virtual void setCameraType( SoType type );

  // set/get minimum speed in word coodinate / second
  // default value is 0, meaning the minimum speed is computed according to scene graph extent
  void setMinSpeed( float speed );
  float getMinSpeed();

  // set/get speed multiplier. default value is 1.5
  void setSpeedMultiplier( float speedInc );
  float getSpeedMultiplier();

  SoINTERNAL public:

  SoGuiFlyViewer* getGuiFlyViewer() const;
  
  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoXtFlyViewer::buildWidget()
  // when they are ready for it to be built.
   SoEXTENDER public:
    SoXtFlyViewer( SoWidget parent, 
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
  virtual void rightWheelMotion( float newVal );
    
  // add viewer preference stuff
  virtual void createPrefSheet();
    
  // Define this to bring the viewer help card
  virtual void openViewerHelpCard();
    
 private:
  // viewer state variables
  Cursor viewerCursor, seekCursor, upCursor;
  SbRotation camStartOrientation;
    
  // preference sheet stuff
  SoWidget createFlyPrefSheetGuts( SoWidget parent );
  static void incPrefSheetButtonCB( SoWidget w, SoXtFlyViewer* v, void* data);
  static void decPrefSheetButtonCB( SoWidget w, SoXtFlyViewer* v, void* data );
    
  void defineCursors();
  void switchMode( int newMode );
  void changeMaxStraightSpeed( SbBool increase );

  // this is called by both constructors
  void constructorCommon( SbBool buildNow );

  SoGuiFlyViewer* m_guiFlyViewer;
};

#endif  /* _SO_XT_FLY_VIEWER_ */

#endif // _WIN32


