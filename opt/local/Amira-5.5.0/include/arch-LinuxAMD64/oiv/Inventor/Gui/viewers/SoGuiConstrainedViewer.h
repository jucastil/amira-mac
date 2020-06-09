/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jun 2007)
**=======================================================================*/

#ifndef  SO_GUI_CONSTRAINED_VIEWER
#define  SO_GUI_CONSTRAINED_VIEWER

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGuiConstrainedViewer
//
// SoXXViewer implementation class
// 
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/Gui/viewers/SoGuiFullViewer.h>

#ifndef HIDDEN_FROM_DOC
 // Defines
#  define MIN_ANGLE	( 5*M_PI/180. )	// minimum angle between look at 
	  			                          // direction and up direction (in rad)
#endif

/** [OIV-WRAPPER-NO-WRAP] */
class INVENTORGUI_API SoGuiConstrainedViewer : public SoGuiFullViewer 
{
#ifndef HIDDEN_FROM_DOC
  SO_FIELDCONTAINER_HEADER( SoGuiConstrainedViewer );
#endif

SoINTERNAL public:
  /**
   * Constructor.
   */
  SoGuiConstrainedViewer();

  /**
   * Specifies the upward direction of the viewer. This up direction is used by the
   * viewers to constrain the camera when tilting up/down, and also used when
   * rotating the camera right/left. The default is the +Y (0,1,0) direction.
   */
  void setUpDirection( const SbVec3f& newUpDirection );

  /**
   * Returns the upward direction of the viewer.
   */
  SbVec3f getUpDirection();

  // Accessor and mutator for the member m_sceneSize;
  void setSceneSize( float size );
  float getSceneSize () const;

  // Accessor and mutator for the member m_sceneHeight;
  void setSceneHeight( float height );
  float getSceneHeight () const;

  // ----------------------- Extension usage -----------------------------------
    
  //
  // redefine these to add constrained viewer functionality
  //
  virtual void setCamera( SoCamera* newCam );
  virtual void saveHomePosition();
  virtual void resetToHomePosition();
  virtual void recomputeSceneSize();
    
  // Tilts the camera, restraining it to 180 degree rotation from the
  // up direction. A positive angle tilts the camera up.
  virtual void tiltCamera( float deltaAngle );
    
  // Moves the camera forward by the given amount
  virtual void dollyCamera( float dist );
    
  // Redefine these to do constrained viewing tasks.
  // The bottom wheel rotates the camera around the up direction, the
  // left wheel tilts the camera up/down constraning to 180 degree from
  // the up direction. The right wheel moves the camera forward/backward
  // withough constrain (taking the scene size into account).
  virtual void bottomWheelMotion( float newVal );
  virtual void leftWheelMotion( float newVal );
  virtual void rightWheelMotion( float newVal );
  virtual void mouseWheelMotion( float newVal );

  // This is called during a paste.
  // We redefine this to keep the right vector of the camera
  // in a parallel plane.
  virtual void changeCameraValues( SoCamera* newCamera );
    
  // this routine is called by subclasses to find and set the new
  // up direction given the current mouse position. If something is
  // picked, the normal to the object picked will be used to specify
  // the new up direction.
  void findUpDirection( const SbVec2s& mouseLocation );
    
  // this routine checks the camera orientation and makes sure that the
  // current right vector and the ideal right vector (cross between the
  // view vector and world up direction) are the same (i.e. no unwanted
  // roll), else it fixes it. This keeps the up direction valid.
  void checkForCameraUpConstrain();
    
  // Redefine this to keep the up vector when seeking
  virtual void computeSeekFinalOrientation();
  
protected:
  /**
   * Destructor.
   */
  virtual ~SoGuiConstrainedViewer();

  // ----------------------- Private usage -------------------------------------

  private:

  SbVec3f m_origUpDirection; // used to save/reset
  SbVec3f m_upDirection;
  float m_sceneHeight;

  float m_sceneSize;
};

#endif  // SO_GUI_CONSTRAINED_VIEWER

