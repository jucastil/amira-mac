/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Alain Dumesny (MMM yyyy)
**=======================================================================*/


#ifndef  _SO_QT_FLY_VIEWER_
#define  _SO_QT_FLY_VIEWER_
#include <Inventor/Qt/OivQtCompat.h>
#include <Inventor/Qt/viewers/SoQtConstrainedViewer.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbTime.h>

#include <Inventor/Gui/viewers/SoGuiFlyViewer.h>

class   SoFieldSensor;

/**
 * @VSGEXT Viewer component for flying through space, with a constant world up.
 * 
 * @ingroup Qt
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
 * @USAGE
 *  (For 3-button mouse only.)
 *
 *   @B Left Mouse: @b Click to increase speed.
 *   
 *   @B 's' + Left Mouse: @b Alternative to the Seek button. Press (but do not hold
 *   down) the 's' key, then click on a target object.
 *   
 *   @B Up  + Left Mouse: @b Press (but do not hold down) the Up  key, then click on
 *   a target object to set the "up" direction to the surface normal. By default +y
 *   is the "up" direction.
 *   
 *   @B Middle Mouse: @b Click to decrease speed.
 *   
 *   @B Left and Middle Mouse: @b Click both simultaneously to stop.
 *   
 *   @B Ctrl: @b Hold the key down to stop and rotate the viewpoint.
 *   
 *   @B Right Mouse: @b Open the popup menu.
 *   
 *   @B ALT: @b (Win32) When the viewer is in selection (a.k.a. pick) mode, pressing
 *   and holding the ALT key temporarily switches the viewer to viewing mode. When
 *   the ALT key is released, the viewer returns to selection mode. Note: If any of
 *   the mouse buttons are currently depressed, the ALT key has no effect.
 * 
 * @SEE_ALSO
 *    SoQtFullViewer,
 *    SoQtViewer,
 *    SoQtComponent,
 *    SoQtRenderArea,
 *    SoQtWalkViewer,
 *    SoQtExaminerViewer,
 *    SoQtPlaneViewer
 * 
 * 
 */ 

class INVENTORQT_API SoQtFlyViewer : public SoQtConstrainedViewer 
{

  Q_OBJECT

    public:
    
  /**
   * Constructor which specifies the viewer type. Please refer to 
   * SoQtViewer for a description of the viewer types. [_WIN32] Note:
   * On Windows, the constructor will not create a new top level window -- you must
   * pass a valid window handle for the @B parent @b parameter and pass TRUE for
   * @B buildInsideParent @b.
   */
  SoQtFlyViewer( QWidget* parent = NULL,
                 const char* name = NULL, 
                 SbBool buildInsideParent = TRUE, 
                 SoQtFullViewer::BuildFlag flag = SoQtFullViewer::BUILD_ALL,
                 SoQtViewer::Type type = SoQtViewer::BROWSER );
  /**
   * Destructor.
   */
  ~SoQtFlyViewer();
    
  // redefine these to add fly viewer functionality
  virtual void setViewing( SbBool onOrOff );
  virtual void resetToHomePosition();
  virtual void setCamera( SoCamera* cam );
  virtual void setCursorEnabled( SbBool onOrOff );
  virtual void setSeekMode( SbBool onOrOff );
    
  // This is redefined to prevent the camera type from being changed 
  virtual void setCameraType( SoType type );

  /** 
   * Sets the minimum speed in world coodinate / second. 
   * Default value is 0, meaning the minimum speed is computed according to scene graph extent.
   */
  void  setMinSpeed( float speed );

  /** 
   * Returns the minimum speed.
   */
  float getMinSpeed();

  /** 
   * Sets the speed multiplier. Default value is 1.5.
   */
  void  setSpeedMultiplier( float speedInc );

  /**
   * Returns the speed multiplier.
   */
  float getSpeedMultiplier();
    
  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoQtFlyViewer::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER public:

  SoQtFlyViewer( QWidget* parent,
    const char* name, 
    SbBool buildInsideParent, 
    SoQtFullViewer::BuildFlag flag, 
    SoQtViewer::Type type, 
    SbBool buildNow,
    SbBool sync = true );

  SoINTERNAL public:

  SoGuiFlyViewer* getGuiFlyViewer() const;

protected:

  // redefine these
  virtual SbString getDefaultWidgetName() const;
  virtual SbString getDefaultTitle() const;
  virtual SbString getDefaultIconTitle() const;

  // redefine those routines to do viewer specific stuff
  virtual void processEvent( QEvent* anyevent );
  virtual void actualRedraw();
  virtual void rightWheelMotion( float newVal);
  virtual void mouseWheelMotion( float newVal );

  // add viewer preference stuff
  virtual void createPrefSheet();

  // Define this to bring the viewer help card
  virtual void openViewerHelpCard();

private:

  SoGuiFlyViewer* m_guiFlyViewer;

  // viewer state variables
  SbRotation camStartOrientation;

  void        switchMode( int newMode );
  void        changeMaxStraightSpeed( SbBool increase );

  // this is called by both constructors
  void constructorCommon( SbBool buildNow );
};

#endif  /* _SO_QT_FLY_VIEWER_ */

