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


#ifndef  _SO_CAMERA_
#define  _SO_CAMERA_

#include <Inventor/SbBox.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFEnum.h>

class SbViewportRegion;
class SoState;


// Callback function prototypes

class SoCamera ;
typedef void SoCameraCB( SoCamera *camera, SoGLRenderAction* action );

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoCamera
//
//  Abstract base class Camera node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Abstract base class for camera nodes.
 *
 * @ingroup CameraNodes
 *
 * @DESCRIPTION
 *   This is the abstract base class for all camera nodes. It defines the common
 *   methods and fields that all cameras have. Cameras are used to view a scene. When
 *   a camera is encountered during rendering, it sets the projection and viewing
 *   matrices and viewport appropriately; it does not draw geometry. Cameras should
 *   be placed before any shape nodes or light nodes in a scene graph; otherwise,
 *   those shapes or lights cannot be rendered properly. Cameras are affected by the
 *   current transformation, so you can position a camera by placing a transformation
 *   node before it in the scene graph. The default position and orientation of a
 *   camera is at (0,0,1) looking along the negative z-axis.
 *
 *   You can also use a node kit to create a camera; see the reference page for
 *   SoCameraKit.
 *
 * @SEE_ALSO
 *    SoOrthographicCamera,
 *    SoPerspectiveCamera,
 *    SoCameraKit
 *
 *
 */

class INVENTOR_API SoCamera : public SoNode {

  SO_NODE_ABSTRACT_HEADER(SoCamera);

 public:
   /** Viewport mapping */
  enum ViewportMapping {
    /**
     *  Crops the viewport within the current window, so that the aspect ratio matches
     * that of the camera. As the window size changes, the aspect ratio remains
     * unchanged. The cropped region is drawn as a filled gray area.
     */
    CROP_VIEWPORT_FILL_FRAME = 0,
    /**
     *  Crops the viewport, but draws a thin frame around the viewport
     */
    CROP_VIEWPORT_LINE_FRAME = 1,
    /**
     *  Crops the viewport, but gives no visual feedback as to the viewport dimensions
     * within the window
     */
    CROP_VIEWPORT_NO_FRAME   = 2,

    /**
     *  Adjusts the camera aspect ratio and height to make it fit within the given
     * window. (The camera's fields are not affected, just the values sent to the
     * graphics library.)
     */
    ADJUST_CAMERA            = 3,
    /**
     *  Do nothing. Camera image may become stretched out of proportion
     */
    LEAVE_ALONE              = 4
  };

  // NOTE: These fields are here so that all camera subclasses do
  // not have to define them separately. However, all subclasses
  // DO have to set up field data with these fields in them to make
  // things work properly.

  // Fields
  /**
   * Defines how to map the rendered image into the current viewport, when the aspect
   * ratio of the camera differs from that of the viewport.
   * Use enum #ViewportMapping. Default is ADJUST_CAMERA.
   */
  SoSFEnum              viewportMapping;
  /**
   * The location of the camera viewpoint.
   *
   */
  SoSFVec3f             position;
  /**
   * The orientation of the camera viewpoint, defined as a rotation of the viewing
   * direction from its default (0,0,-1) vector.
   *
   */
  SoSFRotation  orientation;
  /**
   * The ratio of camera viewing width to height. This value must be greater than
   * 0.0. There are several standard camera aspect ratios defined in SoCamera.h.
   *
   */
  SoSFFloat             aspectRatio;
  /**
   * The distance from the camera viewpoint to the near clipping plane.
   *
   */
  SoSFFloat             nearDistance;
  /**
   * The distance from the camera viewpoint to the far clipping plane.
   *
   */
  SoSFFloat             farDistance;
  /**
   * The distance from the viewpoint to the point of focus. This is typically ignored
   * during rendering, but may be used by some viewers to define a point of
   * interest.
   *
   */
  SoSFFloat       focalDistance;

  /**
   * Sets the orientation of the camera so that it points toward the given target
   * point while keeping the "up" direction of the camera parallel to the positive
   * y-axis. If this is not possible, it uses the positive z-axis as "up."
   */
  void          pointAt(const SbVec3f &targetPoint);

  /**
   * Scales the height of the camera. Perspective cameras scale their
   * @B heightAngle @b fields, and orthographic cameras scale their @B height @b
   * fields.
   */
  virtual void  scaleHeight(float scaleFactor) = 0;

#ifdef OIV_NET_DOC
  /**
   * Returns a view volume object, based on the camera's viewing parameters. @BR
   * This object can be used, for example, to get the view and projection matrices,
   * to project 2D screen coordinates into 3D space and to project 3D coordinates
   * into screen space.
   *
   * If the useAspectRatio parameter is 0.0 (the default), the camera uses the
   * current value of the #aspectRatio field to compute the view volume.
   *
   * NOTE: In ADJUST_CAMERA mode (the default), the view volume returned when
   * useAspectRatio = 0, is not (in general) the actual view volume used for
   * rendering.  Using this view volume to project points will not (in general)
   * produce the correct results.
   *
   * This is because, in ADJUST_CAMERA mode, Inventor automatically modifies the
   * view volume to match the aspect ratio of the current viewport.  This avoids 
   * the distortion that would be caused by "stretching" the view volume when it
   * is mapped into the viewport. However the view volume values are not changed,
   * only the values passed to OpenGL. In order to get the modified values (i.e., 
   * the actual view volume used for rendering) you must pass the actual viewport
   * aspect ratio to getViewVolume. You can get the current viewport from the
   * renderArea or viewer object that contains the Open Inventor window.
   *
   * Also note that in ADJUST_CAMERA mode, when the viewport aspect ratio is
   * less than 1, Open Inventor automatically scales the actual rendering view 
   * volume by the inverse of the aspect ratio (i.e. 1/aspect). The getViewVolume 
   * method does not automatically apply this adjustment. So a correct query of
   * the actual rendering view volume can be done like this:
   *
   * \code
   *   // Given a viewer object, get the actual rendering view volume
   *   float aspect = Viewer.GetViewportRegion().GetViewportAspectRation();
   *   SbViewVolume vvol = Camera.GetViewVolume( aspect );
   *   if (aspect < 1)
   *     vvol.Scale( 1 / aspect );
   * \endcode
   */
#else
  /**
   * Returns a view volume object, based on the camera's viewing parameters. @BR
   * This object can be used, for example, to get the view and projection matrices,
   * to project 2D screen coordinates into 3D space and to project 3D coordinates
   * into screen space.
   *
   * If the useAspectRatio parameter is 0.0 (the default), the camera uses the
   * current value of the #aspectRatio field to compute the view volume.
   *
   * NOTE: In ADJUST_CAMERA mode (the default), the view volume returned when
   * useAspectRatio = 0, is not (in general) the actual view volume used for
   * rendering.  Using this view volume to project points will not (in general)
   * produce the correct results.
   *
   * This is because, in ADJUST_CAMERA mode, Inventor automatically modifies the
   * view volume to match the aspect ratio of the current viewport.  This avoids 
   * the distortion that would be caused by "stretching" the view volume when it
   * is mapped into the viewport. However the view volume values are not changed,
   * only the values passed to OpenGL. In order to get the modified values (i.e., 
   * the actual view volume used for rendering) you must pass the actual viewport
   * aspect ratio to getViewVolume. You can get the current viewport from the
   * renderArea or viewer object that contains the Open Inventor window.
   *
   * Also note that in ADJUST_CAMERA mode, when the viewport aspect ratio is
   * less than 1, Open Inventor automatically scales the actual rendering view 
   * volume by the inverse of the aspect ratio (i.e. 1/aspect). The getViewVolume 
   * method does not automatically apply this adjustment. So a correct query of
   * the actual rendering view volume can be done like this:
   *
   * \code
   *   // Given a viewer object, get the actual rendering view volume
   *   float aspect = pViewer->getViewportRegion().getViewportAspectRation();
   *   SbViewVolume vvol = pCamera->getViewVolume( aspect );
   *   if (aspect < 1)
   *     vvol.scale( 1 / aspect );
   * \endcode
   */
#endif //OIV_NET_DOC
  virtual SbViewVolume getViewVolume(float useAspectRatio = 0.0) const = 0;


  /**
   * Sets the camera to view the scene rooted by the given node.
   * The near and far clipping planes will be positioned slack bounding
   * sphere radii away from the bounding box's center. A value of 1.0 will make the
   * near and far clipping planes the tightest around the bounding sphere.
   *
   * The node applies an SoGetBoundingBoxAction to the scene graph to get the
   * bounding box of the entire scene. The bounding box will only include shapes 
   * that are actually traversed. For example the bounding box will not include 
   * shapes under an SoSwitch with whichChild set to SO_SWITCH_NONE. The action 
   * does not consider the visibility of shapes that are traversed. In other words
   * the bounding box will include shapes that are invisible (SoDrawStyle), shapes
   * that are clipped (SoClipPlane), etc.  Use an SoBBox node to exclude shapes 
   * from the bounding box computation.  Bounding boxes are automatically cached at
   * SoSeparator nodes, so getting the bounding box is very fast when the scene
   * graph has not been changed.
   */
  void          viewAll(SoNode *sceneRoot,
                        const SbViewportRegion &vpRegion,
                        float slack = 1.0);
  /**
   * Sets the camera to view the scene defined by the
   * given path. The near and far clipping planes will be positioned slack bounding
   * sphere radii away from the bounding box's center. A value of 1.0 will make the
   * near and far clipping planes the tightest around the bounding sphere.
   *
   * See note about bounding boxes in the sceneRoot version of this method.
   */
  void          viewAll(SoPath *path,
                        const SbViewportRegion &vpRegion,
                        float slack = 1.0);

  /**
   * Sets the camera to view the region defined by the given bounding box.
   * The near and far clipping planes will be positioned the radius of the bounding
   * sphere away from the bounding box's center.
   *
   * See note about bounding boxes in the sceneRoot version of this method.
   */
  void          viewAll(const SbBox3f& bbox, 
                        const SbViewportRegion &vpRegion);

  /**
   * Returns the viewport region this camera would use to render into the given
   * viewport region, accounting for cropping.
   */
  SbViewportRegion      getViewportBounds(const SbViewportRegion &region) const;

  /**
   * Sets the stereo offset (the distance of each eye from the camera position).
   * The right eye is moved plus offset and the left eye is moved minus offset.
   * Default is 0.7. The default can be set using OIV_STEREO_OFFSET environment variable.
   */
  void  setStereoAdjustment(float adjustment)
    { m_stereoAdjustment = adjustment ; }

  /**
   * Queries the stereo offset.
   */
  float getStereoAdjustment() const
    { return _stereoAdjustment ; }

  /**
  * Specifies if stereo adjustments are absolute. FALSE by default.
  *
  * The default non-absolute mode allows the stereo settings to be valid over a range
  * of different view volume settings. If you chose absolute mode, you are responsible
  * for modifying the stereo settings (if necessary) when the view volume changes.
  *
  * When absolute mode is TRUE, stereo offset and balance are used as follows
  * for the right eye view:
  * <PRE>
  * StereoCameraOffset = getStereoAdjustment();
  * FrustumAsymmetry   = getBalanceAdjustment();
  *
  * glTranslated (-StereoCameraOffset, 0, 0);
  * glFrustum (FrustumLeft + FrustumAsymmetry, FrustumRight + FrustumAsymmetry,
  *            FrustumBottom, FrustumTop, NearClipDistance, FarClipDistance);</PRE>
  *
  * The left eye view is symmetric.
  *
  * When absolute mode is FALSE, stereo offset and balance are used as follows for the
  * right eye view:
  *
  * Xrange is right minus left (i.e., first two arguments of glFrustum) and
  * multiply that difference by the ratio of the distance to the desired plane
  * of zero parallax to the near clipping plane distance.
  * <PRE>
  * StereoCameraOffset   = Xrange * 0.035 * getStereoAdjustment();
  * FrustumAsymmetry     = -StereoCameraOffset * getBalanceAdjustment();
  * ZeroParallaxDistance = (NearClipDistance + FarClipDistance)/0.5;
  *
  * FrustumAsymmetry *= NearClipDistance / ZeroParallaxDistance;
  *
  * glTranslated (-StereoCameraOffset, 0, 0);
  * glFrustum (FrustumLeft + FrustumAsymmetry, FrustumRight + FrustumAsymmetry,
  *            FrustumBottom, FrustumTop, NearClipDistance, FarClipDistance);</PRE>
  * The left eye view is symmetric.
  *
  * Not virtual pure for compatiblity reasons.
  */
  void setStereoAbsoluteAdjustments( SbBool absolute )
    { m_stereoAbsoluteAdjustments = absolute; };

  /**
   * Queries the stereo absolute adjustment state.
   */
  SbBool getStereoAbsoluteAdjustment() const
    { return _stereoAbsoluteAdjustments ; }

  /**
   * Sets the stereo balance (the position of the zero parallax plane) and specifies whether
   * the balance value is defined as a fraction of the camera near distance.
   *
   * Note: Since the projection matrix always depends on the camera's near plane, in
   * some cases it may be necessary to detect changes to the camera near plane and
   * adjust by setting a new stereo balance value.  Open Inventor will make these
   * adjustments automatically if the @B nearFrac @b parameter is set to TRUE.
   * In this case the stereo balance value is defined as a fraction of the camera
   * near distance.
   *
   * Default balance is 1.0. The default can be set using the OIV_STEREO_BALANCE environment variable.
   * Default nearFrac is FALSE. The default can be set using the OIV_STEREO_BALANCE_NEAR_FRAC environment variable.
   */
  void  setBalanceAdjustment(float adjustment, SbBool nearFrac = false)
    { m_balanceAdjustment = adjustment ;
      m_balanceNearFrac = nearFrac; }

  /**
   * Queries the parallax balance.
   */
  float getBalanceAdjustment() const
    { return _balanceAdjustment; }

  /**
   * Returns TRUE if the stereo balance adjustement is defined as a fraction
   * of the camera near distance.
   */
  SbBool isBalanceAdjustmentNearFrac() const
    { return _balanceNearFrac; }

  /** Stereo mode */
  enum StereoMode {
    /**
     *  Monoscopic (i.e., non-stereo) viewing
     */
    MONOSCOPIC,
    /**
     *  Left eye view
     */
    LEFT_VIEW,
    /**
     *  Right eye view
     */
    RIGHT_VIEW
  };

  /**
   * Sets the stereo mode. If the previous mode was MONOSCOPIC, the current
   * #position is saved. If the parameter mode is MONOSCOPIC, the saved value
   * is restored in #position. When rendering in stereo mode, set left view,
   * render, set right view, render and then restore to monoscopic mode.
   */
  void  setStereoMode(StereoMode mode);

  /**
   * Queries the stereo mode.
   */
  StereoMode    getStereoMode() const;

  /**
   * Allows the camera to render in stereo. Default value is TRUE.
   */
  void allowStereo(SbBool);

 SoEXTENDER public:
  virtual void  doAction(SoAction *action);
  virtual void  callback(SoCallbackAction *action);
  virtual void  GLRender(SoGLRenderAction *action);
  virtual void  getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void  handleEvent(SoHandleEventAction *action);
  virtual void  rayPick(SoRayPickAction *action);
  virtual void  getPrimitiveCount(SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  static void           initClass();
  static void           exitClass();

  // Set a callback at the end of SoCamera::GLRender().
  static void   setPostCallback( SoCameraCB *f ) ;

  /**
   * Computes a view volume from the given parameters.
   * [OIV-WRAPPER VISIBILITY{PublicProtected}]
   */
  virtual SbViewVolume getViewVolume(float aspectRatio,
                                     float nearDist,
                                     float farDist,
                                     SbVec3f position,
                                     SbRotation rotation) const = 0;

  virtual SbViewVolume getViewVolume(SoGLRenderAction *action);

  static SbVec3f fromObjectSpace(const SbVec3f &vector, const SbMatrix &matrix, const SbViewportRegion &vpr);
  static SbVec3f toObjectSpace(const SbVec3f &pixel, const SbMatrix &matrix, const SbViewportRegion &vpr);

  /** Retun adjusted viewvolume (ie: the one used by inventor) */
  SbViewVolume getViewVolume(SoState *state);

  /** Set to true if the camera is used for a shadowmap render */
  inline void setLightCamera(bool flag);

  /** True if the camera is used for a shadowmap render */
  inline bool isLightCamera() const;

  /** return last viewport region when traversed
   * used internally for highlight action.
   */
  const SbViewportRegion &getLastViewportRegion() const
  { return m_lastVpRegion; }

 protected:
  SoCamera();                         // Makes this abstract
  virtual ~SoCamera();

  // Subclasses must define this method, which changes the position
  // and clipping planes of a camera to view the passed bounding box
  // using the given aspect ratio, without changing the height
  // scaling.
  virtual void        viewBoundingBox(const SbBox3f &box,
                                      float aspect, float slack) = 0;

  // Returns amount to jitter camera in normalized device
  // coordinates (after projection) for anti-aliasing during
  // multi-pass rendering
  virtual void        jitter(int numPasses, int curPass,
                             const SbViewportRegion &vpReg,
                             SbVec3f &jitterAmount) const;

 private:
  // Computes the view volume the camera represents, given a viewport region
  void                computeView(const SbViewportRegion &vpReg,
                                  SbViewVolume &viewVol,
                                  SbBool &changeRegion,
                                  SoState *state);

  // Computes the view volume, given wall coordinates
  void        computeView_Wall(const SbViewportRegion &vpReg,
                               SbViewVolume &viewVol,
                               SbBool &changeRegion,
                               SoState *state);

  // Sets relevant info in elements in state
  void                setElements(SoAction *action,
                                  SbViewVolume &viewVol,
                                  SbBool setRegion,
                                  const SbViewportRegion &vpReg,
                                  SbBool doJitter,
                                  const SbVec3f &jitterAmount);

  // Draws cropping frame when rendering
  void                drawFrame(SoGLRenderAction *action,
                                const SbViewportRegion &vpReg,
                                const SbViewportRegion &croppedReg);

  // adjust bounding box if void
  void tuneBbox(SbBox3f& bbox);


  // Returns a 2D sample point within a pixel
  static void         getJitterSample(int numPasses, int curPass,
                                      SbVec2f &samplePoint);

  SbBool m_stereoAbsoluteAdjustments;
  float  m_stereoAdjustment, m_balanceAdjustment;
  SbBool m_balanceNearFrac;
  StereoMode m_stereoMode ;

  SbBool _stereoAbsoluteAdjustments;
  float  _stereoAdjustment, _balanceAdjustment;
  SbBool _balanceNearFrac;
  StereoMode _stereoMode ;
  SbBool _modeInRender;

  // Camera orientation, different from 'orientation' if not in monoscopic mode
  // AND camera is orthographic
  SbRotation normalOrientation;

  // if false, the camera will not compute view volume for stereo
  SbBool stereoIsAllowed;

  /** Set to true if the camera is used for a shadowmap render */
  bool m_lightCamera;

  static SoCameraCB* s_cameraPostCB ;

  /** used for bbox highlight */
  SbViewportRegion m_lastVpRegion;
};

/*******************************************************************************/
void
SoCamera::setLightCamera(bool flag)
{
  m_lightCamera = flag;
}

/*******************************************************************************/
bool
SoCamera::isLightCamera() const
{
  return m_lightCamera;
}

//////////////////////////////////////////////////////////////////////////////
//
// Commonly used camera aspect ratios
//

#define SO_ASPECT_SQUARE        1.00         /* Square (1.000)               */
#define SO_ASPECT_VIDEO         1.333333333  /* Video (0.75)                 */
#define SO_ASPECT_35mm_ACADEMY  1.371        /* 35mm, Academy ap (.72939460) */
#define SO_ASPECT_16mm          1.369        /* 16mm cinema (.730460189)     */
#define SO_ASPECT_35mm_FULL     1.33333      /* 35mm cinema, full ap (0.75)  */
#define SO_ASPECT_70mm          2.287        /* 70 mm unsqueezed (.43725404) */
#define SO_ASPECT_CINEMASCOPE   2.35         /* Cinemascope (.425531914)     */
#define SO_ASPECT_HDTV          1.777777777  /* HDTV (16:9)                  */
#define SO_ASPECT_PANAVISION    2.361        /* Panavision (.423549343)      */
#define SO_ASPECT_35mm          1.5          /* 35mm still camera (.666666)  */
#define SO_ASPECT_VISTAVISION   2.301        /* Vistavision (.434593654)     */

#endif /* _SO_CAMERA_ */

