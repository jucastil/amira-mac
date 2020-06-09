/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/



#ifndef  _SO_WIN_CONSTRAINED_VIEWER_
#define  _SO_WIN_CONSTRAINED_VIEWER_

#include <Inventor/Win/SoWinBeginStrict.h>

#include <Inventor/Win/viewers/SoWinFullViewer.h>
#include <Inventor/SbBox.h>

#include <Inventor/Gui/viewers/SoGuiConstrainedViewer.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWinConstrainedViewer
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Base viewer class which adds camera constraints given a world up direction.
 * 
 * @ingroup Win
 * 
 * @DESCRIPTION
 *   This is a base class for the SoWinWalkViewer and SoWinFlyViewer component
 *   viewers. This class adds methods and convenience routines available to
 *   subclasses to constrain the camera given a world up direction. This prevents the
 *   camera from looking upside down. By default the +Y direction is used.
 * 
 * @SEE_ALSO
 *    SoWinFullViewer,
 *    SoWinViewer,
 *    SoWinComponent,
 *    SoWinRenderArea,
 *    SoWinWalkViewer,
 *    SoWinFlyViewer
 * 
 * 
 */ 

class INVENTORW_API SoWinConstrainedViewer : public SoWinFullViewer 
{
 public:
    
  /**
   * Specifies the upward direction of the viewer. This up direction is used by the
   * viewers to constrain the camera when tilting up/down, and also used when
   * rotating the camera right/left. The default is the +Y (0,1,0) direction.
   */
  void setUpDirection( const SbVec3f& newUpDirection );

  /**
   * Returns the upward direction of the viewer.
   */
  SbVec3f getUpDirection() { return m_guiConstViewer->getUpDirection(); }
    
  //
  // redefine these to add constrained viewer functionality
  //
  virtual void setCamera( SoCamera *newCam );
  virtual void saveHomePosition();
  virtual void resetToHomePosition();
  virtual void recomputeSceneSize();

  SoINTERNAL public:

  SoGuiConstrainedViewer* getGuiConstrainedViewer() const;

  SoWinConstrainedViewer( SoWidget parent,
                          const char* name, 
                          SbBool buildInsideParent, 
                          SoWinFullViewer::BuildFlag flag, 
                          SoWinViewer::Type type, 
                          SbBool buildNow,
                          SbBool sync = TRUE );

  // Retro compatibility only
  SbVec3f upDirection;
  float sceneHeight, sceneSize;
    
 protected:

  SoWinConstrainedViewer( SoWidget parent,
                          const char* name, 
                          SbBool buildInsideParent, 
                          SoWinFullViewer::BuildFlag flag, 
                          SoWinViewer::Type type, 
                          SbBool buildNow,
                          SbBool sync,
                          SoGuiConstrainedViewer* guiConstViewer );
  
  ~SoWinConstrainedViewer();
    
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
    
 private:

  void constructorCommon( SbBool buildNow );

  SoGuiConstrainedViewer* m_guiConstViewer; // Implementation class of SoXxConstrainedViewer
};

#include <Inventor/Win/SoWinEndStrict.h>

#endif  /* _SO_WIN_CONSTRAINED_VIEWER_ */

