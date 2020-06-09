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
#  include <Inventor/Qt/viewers/SoQtConstrainedViewer.h>
#elif defined _WIN32
#  include <Inventor/Win/viewers/SoWinConstrainedViewer.h>
#else // _WIN32

#ifndef  _SO_XT_CONSTRAINED_VIEWER_
#define  _SO_XT_CONSTRAINED_VIEWER_

#include <Inventor/Xt/viewers/SoXtFullViewer.h>
#include <Inventor/SbBox.h>
#include <Inventor/Gui/viewers/SoGuiConstrainedViewer.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtConstrainedViewer
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Base viewer class which adds camera constraints given a world up direction.
 * 
 * @ingroup Xt
 * 
 * @DESCRIPTION
 *   This is a base class for the SoXtWalkViewer and SoXtFlyViewer component viewers.
 *   This class adds methods and convenience routines available to subclasses to
 *   constrain the camera given a world up direction. This prevents the camera from
 *   looking upside down. By default the +Y direction is used.
 * 
 * @SEE_ALSO
 *    SoXtFullViewer,
 *    SoXtViewer,
 *    SoXtComponent,
 *    SoXtRenderArea,
 *    SoXtWalkViewer,
 *    SoXtFlyViewer
 * 
 * 
 */ 

class INVENTORXT_API SoXtConstrainedViewer : public SoXtFullViewer 
{
 public:
    
  /**
   * Specifies the upward direction of the viewer. This up direction is used by the
   * viewers to constrain the camera when tilting up/down, and also used when
   * rotating the camera right/left. The default is the +Y (0,1,0) direction.
   */
  void setUpDirection ( const SbVec3f& newUpDirection );
  /**
   * Returns the upward direction of the viewer.
   */
  SbVec3f getUpDirection() { return m_guiConstViewer->getUpDirection(); }
    
  //
  // redefine these to add constrained viewer functionality
  //
  virtual void setCamera( SoCamera* newCam );
  virtual void saveHomePosition();
  virtual void resetToHomePosition();
  virtual void recomputeSceneSize();

  SoINTERNAL public:
  SoGuiConstrainedViewer* getGuiConstrainedViewer() const;

  // Retro compatibility only
  SbVec3f upDirection;
  float sceneHeight, sceneSize;
    
 protected:
  SoXtConstrainedViewer( SoWidget parent,
                         const char* name, 
                         SbBool buildInsideParent, 
                         SoXtFullViewer::BuildFlag flag, 
                         SoXtViewer::Type type, 
                         SbBool buildNow,
                         SbBool sync = TRUE );
    
  SoXtConstrainedViewer( SoWidget parent,
                         const char* name, 
                         SbBool buildInsideParent, 
                         SoXtFullViewer::BuildFlag flag, 
                         SoXtViewer::Type type, 
                         SbBool buildNow,
                         SbBool sync,
                         SoGuiConstrainedViewer* guiConstViewer );

  ~SoXtConstrainedViewer();
    
  // Tilts the camera, restraining it to 180 degree rotation from the
  // up direction. A positive angle tilts the camera up.
  virtual void tiltCamera( float deltaAngle );
    
  // Redefine these to do constrained viewing tasks.
  // The bottom wheel rotates the camera around the up direction, the
  // left wheel tilts the camera up/down constraning to 180 degree from
  // the up direction. 
  virtual void bottomWheelMotion( float newVal );
  virtual void leftWheelMotion( float newVal );
    
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

#endif  /* _SO_XT_CONSTRAINED_VIEWER_ */

#endif // _WIN32


