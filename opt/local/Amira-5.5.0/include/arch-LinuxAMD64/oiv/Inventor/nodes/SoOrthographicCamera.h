/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_ORTHOGRAPHIC_CAMERA_
#define  _SO_ORTHOGRAPHIC_CAMERA_

#include <Inventor/nodes/SoCamera.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoOrthographicCamera
//
//  Orthographic camera node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Orthographic camera node.
 * 
 * @ingroup CameraNodes
 * 
 * @DESCRIPTION
 *   An orthographic camera defines a parallel projection from a viewpoint. This
 *   camera does not diminish objects with distance, as an SoPerspectiveCamera does.
 *   The viewing volume for an orthographic camera is a rectangular parallelepiped (a
 *   box).
 *   
 *   By default, the camera is located at (0,0,1) and looks along the negative z-axis;
 *   the @B position @b and @B orientation @b fields can be used to change these
 *   values. The #height field defines the total height of the viewing volume;
 *   this and the @B aspectRatio @b field determine its width.
 * 
 * @FILE_FORMAT_DEFAULT
 *    OrthographicCamera {
 *    @TABLE_FILE_FORMAT
 *       @TR viewportMapping   @TD ADJUST_CAMERA
 *       @TR position          @TD 0 0 1
 *       @TR orientation       @TD 0 0 1 0
 *       @TR aspectRatio       @TD 1
 *       @TR nearDistance      @TD 1
 *       @TR farDistance       @TD 10
 *       @TR focalDistance     @TD 5
 *       @TR height            @TD 2
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoHandleEventAction,  SoRayPickAction @BR
 *        Sets the viewport and camera information in the state.
 *        Sets: SoFocalDistanceElement, SoProjectionMatrixElement, SoViewportRegionElement
 *              SoViewVolumeElement, SoViewingMatrixElement
 * 
 * @SEE_ALSO
 *    SbViewVolume,
 *    SoPerspectiveCamera
 * 
 * 
 */ 

class INVENTOR_API SoOrthographicCamera : public SoCamera {
  
  SO_NODE_HEADER(SoOrthographicCamera);
  
 public:

  /**
   * Height of the viewing volume.
   */
  SoSFFloat height;
  
  /**
   * Creates an orthographic camera node with default settings.
   */
  SoOrthographicCamera();
  
  /** 
   * Scales the height of the camera, in this case, the #height field.
   */
  virtual void scaleHeight(float scaleFactor);
  
  /** 
   * Fills in a view volume structure, based on the camera. If the
   * useAspectRatio field is not 0.0 (the default), the camera uses
   * that ratio instead of the one it has.
   *
   * Note that in ADJUST_CAMERA mode, Inventor automatically modifies the
   * view volume based on the aspect ratio of the viewport.
   * However the view volume values are not changed, only the
   * values passed to OpenGL. In order to get the modified
   * values (i.e., the actual view volume used to render) you must
   * pass the actual viewport aspect ratio to getViewVolume.
   */
  virtual SbViewVolume getViewVolume(float useAspectRatio = 0.0) const;

 SoINTERNAL public:

  static void initClass();
  static void exitClass();

  /**
   * Computes a view volume from the given parameters.
   */
  virtual SbViewVolume getViewVolume(float useAspectRatio,
                                     float nearDist,
                                     float farDist,
                                     SbVec3f position,
                                     SbRotation orientation) const;
  
  virtual SbViewVolume getViewVolume(SoGLRenderAction *action) 
  { return SoCamera::getViewVolume(action); }

 protected:

  // Positions camera to view passed bounding box with given aspect
  // ratio and current height
  virtual void viewBoundingBox(const SbBox3f &box,
                               float aspect, float slack);
  
  virtual ~SoOrthographicCamera();
};

#endif /* _SO_ORTHOGRAPHIC_CAMERA_ */

