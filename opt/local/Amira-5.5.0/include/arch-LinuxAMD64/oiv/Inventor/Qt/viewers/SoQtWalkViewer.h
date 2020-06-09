/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Alain Dumesny (MMM yyyy)
**=======================================================================*/


#ifndef  _SO_QT_WALK_VIEWER_
#define  _SO_QT_WALK_VIEWER_
#include <Inventor/Qt/OivQtCompat.h>
#include <Inventor/Qt/viewers/SoQtConstrainedViewer.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbTime.h>

#include <Inventor/Gui/viewers/SoGuiWalkViewer.h>

class   SoFieldSensor;

/**
 * @VSGEXT Viewer component which moves the camera in a plane.
 * 
 * @ingroup Qt
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
 *   @B Middle Mouse or @b
 *   @B Ctrl + Left Mouse: @b Translate up, down, left, and right.
 *   
 *   @B Ctrl + Middle Mouse: @b Tilt the camera up/down and right/left. This allows
 *   you to look around while stopped.
 *   
 *   @B 's' + Left Mouse: @b Alternative to the Seek button. Press (but do not hold
 *   down) the 's' key, then click on a target object.
 *   
 *   @B Up  + Left Mouse: @b Press (but do not hold down) the Up  key, then click on
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
 * @SEE_ALSO
 *    SoQtFullViewer,
 *    SoQtViewer,
 *    SoQtComponent,
 *    SoQtRenderArea,
 *    SoQtPlaneViewer,
 *    SoQtExaminerViewer,
 *    SoQtFlyViewer
 * 
 * 
 */ 

class INVENTORQT_API SoQtWalkViewer : public SoQtConstrainedViewer
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
  SoQtWalkViewer( QWidget* parent = NULL,
                  const char* name = NULL, 
                  SbBool buildInsideParent = TRUE, 
                  SoQtFullViewer::BuildFlag flag = SoQtFullViewer::BUILD_ALL, 
                  SoQtViewer::Type type = SoQtViewer::BROWSER );
  /**
   * Destructor.
   */
  ~SoQtWalkViewer();
    
  //
  // redefine these to add Walk viewer functionality
  //
  virtual void setViewing( SbBool onOrOff );
  virtual void setCamera( SoCamera* cam );
  virtual void setCursorEnabled( SbBool onOrOff );
  virtual void setSeekMode( SbBool onOrOff );
    
  // This is redefined to prevent the camera type from being changed 
  virtual void setCameraType(SoType type);

  /**
   * Set viewer speed multiplier (default is 1).
   */
  void setViewerSpeed( float speed ) { m_guiWalkViewer->setViewerSpeed( speed ); }
  /**
   * Get viewer speed multiplier
   */
  float getViewerSpeed() const { return m_guiWalkViewer->getViewerSpeed(); }
    
  
  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoQtWalkViewer::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER public:
    SoQtWalkViewer( QWidget* parent,
                    const char* name, 
                    SbBool buildInsideParent, 
                    SoQtFullViewer::BuildFlag flag, 
                    SoQtViewer::Type type, 
                    SbBool buildNow,
                    SbBool sync );

  SoINTERNAL public:

  SoGuiWalkViewer* getGuiWalkViewer() const;
            
 protected:
  // redefine these
  virtual SbString getDefaultWidgetName() const;
  virtual SbString getDefaultTitle() const;
  virtual SbString getDefaultIconTitle() const;
    
  // redefine those routines to do viewer specific stuff
  virtual void processEvent( QEvent* anyevent );
  virtual void actualRedraw();
  virtual void rightWheelMotion( float newVal );
  virtual void mouseWheelMotion( float newVal );
  virtual void dollyCamera( float dist );
    
  // redefine this to add the extra thumbwheel on the left side
  virtual QWidget* buildLeftTrim( QWidget* parent );
    
  // add viewer preference stuff
  virtual void createPrefSheet();
    
  // Define this to bring the viewer help card
  virtual void openViewerHelpCard();
    
private:

  SoGuiWalkViewer* m_guiWalkViewer;
  // viewer state variables
  QCursor tiltCursor;

  // extra decoration vars
  int heightWheelVal;
    
  void updateViewerMode( unsigned int state );
  void switchMode( int newMode );
  void updateCursor();

  // this is called by both constructors
  void constructorCommon( SbBool buildNow );

protected Q_SLOTS:
#ifndef HIDDEN_FROM_DOC
  void extraWheelDrag( int value );
  void extraWheelOther(void);
#endif //HIDDEN_FROM_DOC
};

#endif  /* _SO_QT_WALK_VIEWER_ */

