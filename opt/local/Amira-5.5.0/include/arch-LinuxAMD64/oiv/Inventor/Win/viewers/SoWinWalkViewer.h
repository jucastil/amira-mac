/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/



#ifndef  _SO_WIN_WALK_VIEWER_
#define  _SO_WIN_WALK_VIEWER_

#include <Inventor/Win/SoWinBeginStrict.h>

#include <Inventor/Win/viewers/SoWinConstrainedViewer.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbTime.h>

#include <Inventor/Gui/viewers/SoGuiWalkViewer.h>

class   SoFieldSensor;

/**
 * @VSGEXT Viewer component which moves the camera in a plane.
 * 
 * @ingroup Win
 * 
 * @DESCRIPTION
 *   The paradigm for this viewer is a walk-through of an architectural model. Its
 *   primary behavior is forward, backward, and left/right turning motion while
 *   maintaining a constant "eye level". It is also possible to stop and look around
 *   at the scene. The eye level plane can be disabled, allowing the viewer to
 *   proceed in the "look at" direction, as if on an escalator. The eye level plane
 *   can also be translated up and down - similar to an elevator.
 * 
 * @USAGE
 *  (For 3-button mouse only.)
 *   
 *   @B Left Mouse: @b Walk mode. Click down and move up and down for fowards and
 *   backwards motion. Move right and left for turning. Speed increases exponentially
 *   with the distance from the mouse-down origin.
 *   
 *   @B Middle Mouse or @BR
 *   Ctrl + Left Mouse: @b Translate up, down, left, and right.
 *   
 *   @B Ctrl + Middle Mouse: @b Tilt the camera up/down and right/left. This allows
 *   you to look around while stopped.
 *   
 *   @B "s" + Left Mouse: @b Alternative to the Seek button. Press (but do not hold
 *   down) the "s" key, then click on a target object.
 *   
 *   @B "u" + Left Mouse: @b Press (but do not hold down) the "u" key, then click on
 *   a target object to set the "up" direction to the surface normal. By default +y
 *   is the "up" direction.
 *   
 *   @B Right Mouse: @b Open the popup menu.
 *   
 *   @B ALT @b: (Win32) When the viewer is in selection (a.k.a. pick) mode, pressing
 *   and holding the ALT key temporarily switches the viewer to viewing mode. When
 *   the ALT key is released, the viewer returns to selection mode. Note: If any of
 *   the mouse buttons are currently depressed, the ALT key has no effect.
 *
 *   @B Keypad '-': @b Decrease viewer speed by 0.5.
 *
 *   @B Keypad '+': @b Increase viewer speed by 2.
 * 
 * @SEE_ALSO
 *    SoWinFullViewer,
 *    SoWinViewer,
 *    SoWinComponent,
 *    SoWinRenderArea,
 *    SoWinPlaneViewer,
 *    SoWinExaminerViewer,
 *    SoWinFlyViewer
 * 
 * 
 */ 

class INVENTORW_API SoWinWalkViewer : public SoWinConstrainedViewer 
{
 public:
    
  /**
   * Constructor which specifies the viewer type. Please refer to 
   * SoWinViewer for a description of the viewer types. [_WIN32] Note:
   * On Windows, the constructor will not create a new top level window -- you must
   * pass a valid window handle for the @B parent @b parameter and pass TRUE for
   * @B buildInsideParent @b.
   */
  SoWinWalkViewer( SoWidget parent = NULL,
                   const char* name = NULL, 
                   SbBool buildInsideParent = TRUE, 
                   SoWinFullViewer::BuildFlag flag = SoWinFullViewer::BUILD_ALL, 
                   SoWinViewer::Type type = SoWinViewer::BROWSER );
  /**
   * Destructor.
   */
  ~SoWinWalkViewer();
    
  //
  // redefine these to add Walk viewer functionality
  //
  virtual void setViewing( SbBool onOrOff );
  virtual void setCamera( SoCamera* cam );
  virtual void setCursorEnabled( SbBool onOrOff );
    
  // This is redefined to prevent the camera type from being changed 
  virtual void setCameraType( SoType type );

  /**
   * Set viewer speed multiplier (default is 1).
   */
  void setViewerSpeed( float speed ) { m_guiWalkViewer->setViewerSpeed( speed ); }

  /**
   * Get viewer speed multiplier
   */
  float getViewerSpeed() const { return m_guiWalkViewer->getViewerSpeed(); }

  virtual void setSeekMode( SbBool onOrOff );

  SoINTERNAL public:

  SoGuiWalkViewer* getGuiWalkViewer() const;
    
 protected:
  
  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoWinWalkViewer::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER SoWinWalkViewer( SoWidget parent,
                              const char* name, 
                              SbBool buildInsideParent, 
                              SoWinFullViewer::BuildFlag flag, 
                              SoWinViewer::Type type, 
                              SbBool buildNow );
            
  // redefine these
  virtual SbString getDefaultWidgetName() const;
  virtual SbString getDefaultTitle() const;
  virtual SbString getDefaultIconTitle() const;
    
  // redefine those routines to do viewer specific stuff
  virtual void processEvent( XAnyEvent* anyevent );
  virtual void actualRedraw();
  virtual void rightWheelMotion( float newVal );
  virtual void mouseWheelMotion( float newVal );
  virtual void dollyCamera( float dist );
    
  // redefine this to add the extra thumbwheel on the left side
  virtual SoWidget buildLeftTrim( SoWidget parent );
    
  // add viewer preference stuff
  virtual void createPrefSheet();
    
  // Define this to bring the viewer help card
  virtual void openViewerHelpCard();
    
 private:
  SoGuiWalkViewer* m_guiWalkViewer;

  // viewer state variables
  Cursor tiltCursor;

  // extra decoration vars
  int heightWheelVal;

  static void heightWheelCB( SoWinWalkViewer* p, XtPointer* d );
    
  void updateViewerMode( unsigned int state );
  void switchMode( int newMode );
  void updateCursor();

  // this is called by both constructors
  void constructorCommon( SbBool buildNow );

  // Utility function called from processEvent
  void processPopupItem( int item );
};

#include <Inventor/Win/SoWinEndStrict.h>

#endif  /* _SO_WIN_WALK_VIEWER_ */

