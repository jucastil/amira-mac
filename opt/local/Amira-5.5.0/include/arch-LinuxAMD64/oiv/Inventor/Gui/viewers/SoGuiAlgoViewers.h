/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Tristan MEHAMLI (Dec 2008)
**=======================================================================*/


#ifndef SO_GUI_ALGO_VIEWERS
#define SO_GUI_ALGO_VIEWERS

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGuiAlgoViewers
//
// Provides common and specific algorithms for viewers.
// 
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/Gui/viewers/SoGuiConstrainedViewer.h>

class SbSphereSheetProjector;
class SoExtSelection;
class SoFieldSensor;
class SoMPEGRenderer;
class SoNode;
class SoSwitch;

/** 
 * @VSGEXT Common algorithms for all viewers.
 * 
 * @ingroup GuiBase
 * 
 * @DESCRIPTION
 *   This class provides common viewer algorithms in order to more easily 
 *   create a viewer class from scratch. The algorithms provided deal with 
 *   animations, camera management, etc.
 *   This class regroups algorithms from all the viewer types (examiner,
 *   plane, fly and walk).
 *
 *   There are two ways to use this class:
 *   1) Passed as an argument to the RenderArea.
 *   ex: 
 * <PRE>
 *   SoGuiAlgoViewers* algo = new SoGuiAlgoViewers();
 *   SoXXRenderArea( parent, name, buildInsideParent, getMouseInput, getKeyboardInput, algo );
 * </PRE>
 *
 *   2) Use your own GL widget and call the necessary functions for the
 *   interactions and the rendering. See the demo QtViewer for more information.
 *
 * [OIV-WRAPPER-NO-WRAP]
 */ 
class INVENTORGUI_API SoGuiAlgoViewers : public SoGuiConstrainedViewer
{
public:

  SO_FIELDCONTAINER_HEADER( SoGuiAlgoViewers );

  /** Viewer type flags.
   * This specifies what kind of viewer will be used for some algorithms.
   */
  enum ViewerTypes 
  {
    /**
     * Algorithms for examiner viewer.
     */
    EXAMINER, 
    /**
     * Algorithms for plane viewer.
     */
    PLANE, 
    /**
     * Algorithms for fly viewer.
     */
    FLY, 
    /**
     * Algorithms for walk viewer.
     */
    WALK,
    /**
     * Unknown: default value.
     */
    UNKNOWN
  };

  /** List of possible drawing styles */
  enum DrawStyle
  {
    /**
     *  Unchanged
     */
    VIEW_AS_IS,
    /**
     *  Render only the frontmost lines
     */
    VIEW_HIDDEN_LINE,
    /**
     *  Render without textures
     */
    VIEW_NO_TEXTURE,
    /**
     *  Render low complexity and no texture
     */
    VIEW_LOW_COMPLEXITY,
    /**
     *  Wireframe draw style
     */
    VIEW_LINE,
    /**
     *  Point draw style
     */
    VIEW_POINT,
    /**
     *  Bounding box draw style
     */
    VIEW_BBOX,
    /**
     *  Low complexity wireframe + no depth clearing
     */
    VIEW_LOW_RES_LINE,
    /**
     *  Low complexity point + no depth clearing
     */
    VIEW_LOW_RES_POINT,
    /**
     *  Forces the INTERACTIVE draw style to match STILL
     */
    VIEW_SAME_AS_STILL
  };

  /** List of possible drawing types */
  enum DrawType
  {
    /**
     *  Applies to static rendering
     */
    STILL,
    /**
     *  Applies to rendering while interactive viewing
     */
    INTERACTIVE
  };

  /** List of different buffering types */
  enum BufferType
  {
    /**
     *  Single buffer
     */
    BUFFER_SINGLE,
    /**
     *  Double buffer
     */
    BUFFER_DOUBLE,
    /**
     *  Double buffer while interactive viewing
     */
    BUFFER_INTERACTIVE
  };

  /**
   * Constructor.
   */
  SoGuiAlgoViewers();

  /**
   * Specifies whether algorithms for constrained viewers should be used.
   */
  void setConstrained( SbBool constrained );

  /**
   * Returns TRUE if algorithms for constrained viewers are used.
   */
  SbBool isConstrained() const;

  /**
   * Sets the type of viewer used for the algorithms.
   */
  void setViewerType( ViewerTypes vType );

  /**
   * Returns the current viewer type.
   */
  SoGuiAlgoViewers::ViewerTypes getViewerType() const;

  /**
   * This method resets the render action cache.
   * It is useful to reset cache when the device context used for the rendering is
   * modified (new antialiasing mode, pixel format...)
   */
  void resetRenderAction();

  ////////////////////////
  //* Common algoritms *//
  ////////////////////////
  /**
   * Sets the scene graph to render. Whenever a new scene is supplied
   * the first camera encountered will be by default used as the edited
   * camera, else a new camera will be created. If the scene graph does not
   * contain any light nodes, the viewer inserts a headlight (directional
   * light which is made to follow the camera) immediately after the camera.
   * See the main description of this class for further details.
   */
  virtual void setSceneGraph( SoNode* newScene );

  /**
   * Returns the scene graph to render.
   */
  virtual SoNode* getSceneGraph();

  /**
   * Adds an SoShadowGroup after the headlight and enables it if true.
   * The shadow group's @I method @i field is set to VARIANCE_SHADOW_MAP.
   */
  void enableShadows( bool onOrOff );

  /**
   * Sets the edited camera. Setting the camera is only needed if the first
   * camera found in the scene when setting the scene graph isn't the one the user
   * really wants to edit.
   */
  virtual void setCamera( SoCamera* newCamera );

  /**
   * Gets the edited camera.
   */
  SoCamera* getCamera();

  /**
   * Sets the camera type that will be created by the viewer if no cameras are
   * found in the scene graph (see SoPerspectiveCamera and SoOrthographicCamera). By
   * default an SoPerspectiveCamera will be created if no cameras are found.
   *
   * Note: The set method will only take effect the next time a scene graph is
   * specified (and if no cameras are found). Moreover with fly or walk viewers
   * orthographic cameras don't make sense and are not supported.
   */
  virtual void setCameraType( SoType type );

  /**
   * Gets the camera type that will be created by the viewer if no cameras are
   * found in the scene graph (see SoPerspectiveCamera and SoOrthographicCamera).
   */
  SoType getCameraType();

  /**
   * This routine will toggle the current camera from perspective to
   * orthographic, and from orthographic back to perspective. @BR
   *
   * Note: It is not actually possible to "toggle" the type of a camera.
   * In fact the current camera will be replaced by a new camera of the
   * appropriate type.  Of course the current camera node will be
   * destroyed in the process unless it has been ref'd elsewhere.
   */
  virtual void toggleCameraType();

  /**
   * If TRUE, an SoPerspectiveCamera's heightAngle is preserved
   * if the camera is changed to an SoOrthographicCamera and
   * then toggled back to an SoPerspectiveCamera. Default is FALSE.
   */
  virtual void setPreserveCameraHeightAngle( SbBool flag );

  /**
   * Queries whether the SoPerspectiveCamera's heightAngle is preserved
   * if the camera is changed to an SoOrthographicCamera and
   * then toggled back to an SoPerspectiveCamera.
   */
  virtual SbBool isCameraHeightAnglePreserved() const;

  /**
   * Changes the camera position to view the entire scene (the camera zoom or
   * orientation isn't changed).
   */
  virtual void viewAll();

  /**
   * Saves the camera values.
   */
  virtual void saveHomePosition();

  /**
   * Restores the camera values.
   */
  virtual void resetToHomePosition();

  /**
   * Turns the headlight on/off (default on).@BR
   * @BR
   * The default value can be set using the environment variable
   * OIV_USE_HEADLIGHT (0 = FALSE, 1 = TRUE).
   */
  virtual void setHeadlight( SbBool insertFlag );

  /**
   * Returns TRUE if the headlight is on.
   */
  SbBool isHeadlight();

  /**
   * Returns the headlight node.
   */
  SoDirectionalLight* getHeadlight();

  /**
   * Sets the current drawing style in the main view. The user can specify the
   * INTERACTIVE draw style (draw style used when the scene changes) independently
   * from the STILL style. Default is VIEW_AS_IS draw style for STILL and
   * VIEW_SAME_AS_STILL for INTERACTIVE.
   *
   * The default value can be set using the environment variables
   * OIV_STILL_DRAW_STYLE and OIV_INTERACTIVE_DRAW_STYLE.
   * Valid values are VIEW_AS_IS, VIEW_HIDDEN_LINE, VIEW_NO_TEXTURE, VIEW_LOW_COMPLEXITY,
   * VIEW_LINE, VIEW_POINT, VIEW_BBOX, VIEW_LOW_RES_LINE, VIEW_LOW_RES_POINT for
   * OIV_STILL_DRAW_STYLE and the same plus VIEW_SAME_AS_STILL for OIV_INTERACTIVE_DRAW_STYLE.
   *
   * Possible draw styles are:
   * VIEW_AS_IS - Leaves the objects unchanged.
   *
   * VIEW_HIDDEN_LINE - Renders the object as wireframe, but only shows the object
   * front faces. This is accomplished using a two-pass rendering. In the first pass,
   * the objects are rendered as FILLED using the background BASE_COLOR (this sets up
   * the wanted z-buffer values). The second pass then renders the objects as LINES,
   * while adjusting the z-buffer range to limit overlapping polygons problems.
   *
   * VIEW_NO_TEXTURE - Renders the objects without any textures. This is done by
   * setting the override flag on an empty SoTexture2 node.
   *
   * VIEW_LOW_COMPLEXITY - Renders the objects without any textures and with a low
   * complexity. This is done by setting the override flag on an empty SoTexture2
   * node, and by setting a low complexity value on an SoComplexity node with
   * override set to TRUE.
   *
   * VIEW_LINE - Renders the objects as LINES (no texture) with lighting model set to
   * BASE_COLOR.
   *
   * VIEW_LOW_RES_LINE - Renders the objects as LINES (no texture) using a low
   * complexity, with lighting model set to BASE_COLOR and no depth comparison.
   *
   * VIEW_POINT - Renders the objects as POINTS (no texture) with lighting model set
   * to BASE_COLOR.
   *
   * VIEW_LOW_RES_POINT - Renders the objects as POINTS (no texture) using a low
   * complexity, with lighting model set to BASE_COLOR and no depth comparison.
   *
   * VIEW_BBOX - Renders the objects with complexity BOUNDING_BOX, lighting model set
   * to BASE_COLOR and drawing style LINES (no texture) with no depth comparison.
   *
   * VIEW_SAME_AS_STILL - This only applies to INTERACTIVE draw type. It enables the
   * interactive draw style mode to match the regular draw style mode without having
   * to set it explicitly.
   */
  virtual void setDrawStyle( DrawType type, DrawStyle style );

  /**
   * Returns the current drawing style in the main view.
   */
  DrawStyle getDrawStyle( DrawType type );

  /**
   * Sets the current buffering type in the main view (default
   * BUFFER_DOUBLE).
   */
  virtual void setBufferingType( BufferType type );

  /**
   * Returns the current buffering type in the main view.
   */
  BufferType getBufferingType();

  /**
   * Sets whether the viewer is turned on or off. 
   * When turned on (commonly called viewing mode), events are consumed by the viewer. 
   * When viewing is off (commonly called selection mode), events are processed by the
   * viewer's render area. This means events will be sent down to the scene graph for
   * processing (i.e. picking can occur). Note that if the application has registered
   * an event callback, it will be invoked on every message, whether viewing is
   * turned on or not. However, the return value of this callback (which specifies
   * whether the callback handled the event or not) is ignored when viewing is on.
   * That is, the viewer will process the event even if the callback already did.
   * This is to ensure that the viewing paradigm is not broken (default viewing is
   * on).
   */
  virtual void setViewing( SbBool flag );

  /**
   * Returns TRUE if the viewer is in viewing mode. See setViewing() for details.
   */
  SbBool isViewing() const;

  /**
   * This can be used to let the viewer know that the scene graph has changed so that
   * the viewer can recompute things like speed which depend on the scene graph size.
   * Note: This routine is automatically called whenever setSceneGraph() is
   * called.
   */
  virtual void recomputeSceneSize();

  /**
   * Set the viewer into/out of seek mode (default OFF). Actual
   * seeking will not happen until the viewer decides to,
   * for example, on a mouse click.
   *
   * Note: Setting the viewer out of seek mode while the camera is being
   * animated will stop the animation at the current location.
   */
  virtual void setSeekMode( SbBool onOrOff );

  /**
   * Returns TRUE if viewer is in seek mode.
   */
  SbBool isSeekMode();

  /**
   * This routine is used by subclasses to initiate the seek animation. Given a
   * screen mouse location, this routine will initiate a seek to the picked point
   * and the normal at that point. It will also schedule the sensor to animate
   * if necessary. The routine retuns TRUE if something got picked...
   */
  SbBool seekToPoint( const SbVec2s& mouseLocation );

  /** 
   * Auto clipping routine.
   */
  virtual void adjustCameraClippingPlanes();

  /**
   * Sets box selection mode.
   */
  void setBoxSelectionMode( SbBool on );

  /**
   * Returns TRUE if box selection mode is enabled.
   */
  SbBool isBoxSelection() const;

  /**
   * Sets box drawing mode.
   */
  void setBoxDrawingMode( SbBool on );

  /**
   * Returns TRUE if box drawing mode is enabled.
   */
  SbBool isBoxDrawing() const;

  /**
   * Zooms to the region delimited by the box. @BR
   * (x1, y1) is the top left corner and (x2, y2) is the bottom
   * right corner of the box in pixel coordinates.
   */
  void doBoxZoom( int x1, int y1, int x2, int y2 );

  /** 
   * Rolls the camera based on cursor motion.
   * @param newLocator The new cursor position in pixels. 
   * The coordinates must be defined with x in the range [0,window width] and
   * y in the range [0,window height] with min y at the bottom and min x on the left.
   */
  virtual void rollCamera( const SbVec2s& newLocator );

  /**
   * Moves the camera on the z axis based on cursor motion.
   * Only for Examiner and Plane viewers.
   *
   * @param newLocator The new cursor position in pixels. 
   * The coordinates must be defined with x in the range [0,window width] and
   * y in the range [0,window height] with min y at the bottom and min x on the left.
   */
  virtual void dollyCamera( const SbVec2s& newLocator );

  /**
   * Moves the camera forward by the given amount. Only for Walk and Fly viewers.
   * @param dist Distance the camera will be moved.
   */
  virtual void dollyCamera( float dist );

  /**
   * Same as dollyCamera but reversed. Only for Examiner and Plane viewers.
   *
   * @param newLocator The new cursor position in pixels. 
   * The coordinates must be defined with x in the range [0,window width] and
   * y in the range [0,window height] with min y at the bottom and min x on the left.
   */
  virtual void reverseDollyCamera( const SbVec2s& newLocator );

  /**
   * Pans the camera based on cursor motion. Only for Examiner and Plane viewers.
   *
   * @param newLocator The new cursor position in pixels. 
   * The coordinates must be defined with x in the range [0,window width] and
   * y in the range [0,window height] with min y at the bottom and min x on the left.
   */
  virtual void panCamera( const SbVec2f& newLocator );

  /**
   * Does camera animation for constrained viewers.
   */
  void doCameraAnimation();

  /**
   * Initializes right thumb wheel.
   */
  virtual void rightWheelStart();

  /**
   * Initializes bottom thumb wheel.
   */
  virtual void bottomWheelStart();

  /**
   *  Initializes left thumb wheel.
   */
  virtual void leftWheelStart();

  /**
   * Examiner and constrained viewers:
   * Rotates the camera based on bottom wheel motion.
   *
   * Plane viewer:
   * Translates the camera based on bottom wheel motion.
   */
  virtual void bottomWheelMotion( float newVal );

  /**
   * Examiner and constrained viewers:
   * Rotates the camera based on left wheel motion.
   * 
   * Plane viewer:
   * Translates the camera based on left wheel motion.
   */
  virtual void leftWheelMotion( float newVal );

  /**
   * Makes the camera to zoom based on right wheel motion.
   */
  virtual void rightWheelMotion( float newVal );

  /**
   * Makes the camera to zoom based on mouse wheel motion.
   */
  virtual void mouseWheelMotion( float newVal );

  /**
   * Updates camera position when panning is actived. For Examiner
   * and Plane viewers only.
   */
  void activatePanning();

  /** 
   * Sets the mouse start position.
   *
   * @param mousePosition The new mouse position in pixels. 
   * The coordinates must be defined with x in the range [0,window width] and
   * y in the range [0,window height] with min y at the bottom and min x on the left.
   */
  void setStartMousePositionLocator( const SbVec2s& mousePosition );

  /**
   * Returns the mouse start position in pixels.
   */
  SbVec2s getStartMousePositionLocator() const;

  /** 
   * Sets the current mouse position.
   *
   * @param mousePosition The new mouse position in pixels. 
   * The coordinates must be defined with x in the range [0,window width] and
   * y in the range [0,window height] with min y at the bottom and min x on the left.
   */
  void setCurrentMousePositionLocator( const SbVec2s& mousePosition );

  /**
   * Returns the current mouse position in pixels.
   */
  SbVec2s getCurrentMousePositionLocator() const;

  /** 
   * Sets the previous mouse position.
   *
   * @param mousePosition The new mouse position in pixels. 
   * The coordinates must be defined with x in the range [0,window width] and
   * y in the range [0,window height] with min y at the bottom and min x on the left.
   */
  void setPreviousMousePositionLocator( const SbVec2s& mousePosition );

  /**
   * Returns the previous mouse position in pixels.
   */
  SbVec2s getPreviousMousePositionLocator() const;

  /**
   * Sets the camera position.
   */
  void setCameraPositionLocator( const SbVec3f& camPosition );

  /**
   * Returns the camera position.
   */
  SbVec3f getCameraPositionLocator() const;

  /**
   * Sets the camera focal plane.
   */
  void setCameraFocalPlane( const SbPlane& focalPlane );

  /**
   * Returns the camera focal position.
   */
   SbPlane getCameraFocalPlane() const;

  /**
   * Invokes the start viewing callbacks. This must be called to start doing
   * interactive viewing operations so that correct interactive drawing style 
   * and buffering types, as well as application callbacks, gets set and called 
   * properly.
   */
  void interactiveCountInc();

  /**
   * Invokes the finish viewing callbacks. This must be called to finish doing
   * interactive viewing operations.
   */
  void interactiveCountDec();

  /**
   * Sets the previous animation time.
   */
  void setPrevAnimTime( SbTime previous );

  /**
   * Returns the previous animation time.
   */
  SbTime getPrevAnimTime() const;

  /**
   * Keeps the same camera rotation when seeking.
   */
  virtual void computeSeekFinalOrientation();

  /** 
   * Sets the recorder used for MPEG encoding.
   *
   * @param recorder the recorder to be used.
   *
   * Note: The destruction of the recorder is handled by SoGuiAlgoViewers.
   */
  virtual void setMPEGRecorder( SoMPEGRenderer* recorder );

  /** 
   * Returns the recorder used for MPEG encoding.
   */
  virtual SoMPEGRenderer* getMPEGRecorder() const;

  /**
   * Enables or disables full-scene antialiasing (FSAA). Returns TRUE on success.@BR
   * FSAA requires the @I ARB_multisample@i and @I ARB_pixel_format@i OpenGL extensions.
   *
   * Note: Use the SoFullSceneAntialiasing node to control FSAA during render traversal.
   *
   * @param enable  Enables or disables FSAA rendering.  
   * @param quality  Specifies quality of the antialiasing rendering. @BR
   *   Quality values are in the interval [0..1], where 0 is the lowest quality and 1 is
   *   the highest quality. When set to -1.0 (default) the quality value is the default 
   *   value for the pixel format.  
   *   The number of samples used in the antialiasing computation depends on your graphics
   *   hardware and on your video driver. NVidia graphics hardware can support @I number of 
   *   samples * 2 @i levels of quality (assuming the @I NV_multisample_filter_hint @i
   *   OpenGL extension is available).  
   * @param filterMask  Specifies the types of shapes that should be antialiased. @BR
   *   Default is all shapes. See SoFullSceneAntialiasing for more info.
   */
  SbBool setFullSceneAntialiasing( SbBool enable,
                                   float quality = -1.f, 
                                   int filterMask = SoFullSceneAntialiasing::ALL );

  /**
   * Returns TRUE, if full-scene antialiasing (FSAA) is enabled.
   */
  SbBool isFullSceneAntialiasingEnabled() const;

  /** 
   * Returns the current full-scene antialiasing (FSAA) parameters. 
   * Returns TRUE if FSAA is enabled.
   */
  SbBool getFullSceneAntialiasing( float& quality, int& filterMask ) const;

  /** 
   * Returns TRUE if FSAA is supported by current pixel format.
   */
  SbBool isFullSceneAntialiasingAvailable();

  /**  
   * Returns TRUE if high quality full-scene antialiasing (FSAA) is available.
   *
   * This feature requires the GL_MULTISAMPLE_FILTER_HINT_NV extension.
   */
  SbBool isFullSceneAntialiasingHQAvailable();

  /**  
   * Enables or disables high quality mode for full-scene antialiasing (FSAA).
   *
   * This feature requires the GL_MULTISAMPLE_FILTER_HINT_NV extension.
   */
  SbBool setFullSceneAntialiasingHQ( SbBool enable );

  /** 
   * Returns TRUE if the high quality mode for full-scene antialiasing (FSAA) is enabled.
   */
  SbBool isFullSceneAntialiasingHQEnabled() const;

  /** 
   * Returns the maximum number of samples for full-scene antialiasing (FSAA).
   */
  int getFullSceneAntialiasingMaxSamples() const;

  /**
   * Selects axial view.
   */
  void viewX( bool reverse = false );

  /**
   * Selects frontal view.
   */
  void viewY( bool reverse = false );

  /**
   * Selects sagittal view.
   */
  void viewZ( bool reverse = false );

  /**
   * Returns the scene root of the viewer (drawstyle, camera and headlight + user scene graph)
   * or the user scene graph if there's no scene root
   */
  SoNode* getSceneRoot();

  //////////////////////////
  //* Examiner algoritms *//
  //////////////////////////
  /** 
   * Spins the camera based on cursor motion.
   *
   * @param newLocator The new cursor position in pixels. 
   * The coordinates must be defined with x in the range [0,window width] and
   * y in the range [0,window height] with min y at the bottom and min x on the left.
   */
  virtual void spinCamera( const SbVec2f& newLocator );

  /** 
   * Spin the camera based on cursor motion but constrained to rotation around one axis.
   *
   * @param newLocator The new cursor position in pixels. 
   * The coordinates must be defined with x in the range [0,window width] and
   * y in the range [0,window height] with min y at the bottom and min x on the left.
   * @param axisIndex the axis index:
   * - X = 0
   * - Y = 1
   * - Z = 2
   */
  virtual void spinConstrainedCamera( const SbVec2f& newLocator, int axisIndex );

  /**
   * Starts the spin animation.
   */
  void startSpinAnimation();

  /**
   * Stops the spin animation.
   */
  void stopSpinAnimation();

  /**
   * Rotate the camera for spin animation.
   */
  virtual void doSpinAnimation();

  /**
   * Returns the sphere sheet projector.
   */
  SbSphereSheetProjector* getSphereSheetProjector() const;

  /**
   * Set sphere sheet starting point and resets the animation queue.
   */
  void activateSpinning();

  /**
   * Rotates the camera around focal point by given incremental rotation
   * (Given rotation is concatenated onto the current camera rotation).
   */
  void rotateCamera( const SbRotation& rot );

  /** 
   * Constrains the camera to spin around the specified axis. @BR
   * For instance giving true, true, false will prevent the camera from 
   * rotating around the Z axis.  Default is free rotation.
   * 
   * @param x If false, rotation around x axis is allowed.
   * @param y If false, rotation around y axis is allowed.
   * @param z If false, rotation around z axis is allowed.
   */
  void constrainCameraRotation( bool x = false, bool y = false, bool z = false );

  ///////////////////////
  //* Plane algoritms *//
  ///////////////////////
  /**
   * Moves the camera to be aligned with the given plane.
   * For instance: setPlane( SbVec3f(1, 0, 0), SbVec3f(0, 0, -1) )
   * will align the camera with the X plane.
   */
  void setPlane( const SbVec3f& newNormal, const SbVec3f& newRight );

  /////////////////////
  //* Fly algoritms *//
  /////////////////////

  /**
   * Calculates the maximum speed of the animation.
   */
  void calculateMaxSpeed();

  /**
   * Computes the maximum straight speed.
   */
  void changeMaxStraightSpeed( SbBool increase );

  /**
   * Sets the minimum speed.
   */
  void setMinSpeed( float speed );

  /**
   * Returns the minimum speed.
   */
  float getMinSpeed() const;

  /**
   * Sets the maximum speed.
   */
  void setMaxSpeed( float speed );

  /**
   * Returns the maximum speed.
   */
  float getMaxSpeed() const;

  /**
   * Sets the speed limit.
   */
  void setSpeedLimit( float limit );

  /**
   * Returns the speed limit.
   */
  float getSpeedLimit() const;

  /**
   * Sets the current speed.
   */
  void setCurrentSpeed( float speed );

  /**
   * Returns the current speed.
   */
  float getCurrentSpeed() const;

  /**
   * Sets the maximum straight speed.
   */
  void setMaxStraightSpeed( float speed );

  /**
   * Returns the maximum straight speed.
   */
  float getMaxStraightSpeed() const;

  /**
   * Sets maximum speed multiplier.
   */
  void setMaxSpeedInc( float increment );

  /**
   * Returns maximum speed multiplier.
   */
  float getMaxSpeedInc() const;

  /**
   * Starts the walk animation.
   */
  void startFlyAnimation();

  /**
   * Stops the walk animation.
   */
  void stopFlyAnimation();

  /**
   * Initializes flying animation.
   */
  void activateFlying();
 
  //////////////////////
  //* Walk algoritms *//
  //////////////////////
  /** Walk viewer mode flags.
   * This specifies what mode will be used for the walk viewer camera animation.
   */
  enum WalkViewerMode
  {
    /**
     *  Walking mode (default).
     */
    WALK_MODE, 
    /**
     *  Panning mode.
     */
    PAN_MODE
  };

  /**
   * Updates focal distance.
   */
  void updateCameraFocalPoint();

  /**
   * Sets the camera animation for walk viewers regarding the mode.
   */
  void setWalkViewerAnimMode( WalkViewerMode mode );

  /**
   * Returns the current mode for the walk viewer camera animation.
   */
  SoGuiAlgoViewers::WalkViewerMode getWalkViewerAnimMode() const;

  /**
   * Starts the walk animation.
   */
  void startWalkAnimation();

  /**
   * Stops the walk animation.
   */
  void stopWalkAnimation();

  /**
   * Rotates the camera around focal point by given incremental rotation
   * (Given rotation is concatenated onto the current camera rotation).
   */
  void rotateCamera();

  SoINTERNAL public:

  void setMMode( int mode );
  int getMMode() const;

protected:
  // Destructor.
  virtual ~SoGuiAlgoViewers();

private:
  static void spinAnimationSensorCB( void* v, SoSensor* sensor ); // Examiner
  static void constrainedAnimationSensorCB( void* v, SoSensor* sensor ); // Fly and walk
  static void setFocalPointFinishCallback( void* data, void* v ); // Walk viewer only

  int m_mode;
  SbBool m_constrained; // Used to determine whether the algorithm to use is for constrained viewers.
  ViewerTypes m_vType; // Current viewer type.
  SbBool m_boxDrawing, m_boxSelection, m_firstActivation;
  SoExtSelection* m_selection;
  SoSwitch* m_selectionSwitch;

  SbVec2s m_locator, m_prevPos, m_startPos; // mouse position

  // Sensors for animations
  SoFieldSensor* m_seekAnimationSensor;
  SoFieldSensor* m_spinAnimationSensor;
  SoFieldSensor* m_walkAnimationSensor;
  SoFieldSensor* m_flyAnimationSensor;

  // variables used for spinning animation
  SbSphereSheetProjector* m_sphereSheet;
  SbBool m_computeAverage;
  SbRotation m_averageRotation;
  SbRotation* m_rotBuffer;
  int m_firstIndex, m_lastIndex;
  SbVec3s m_constrainedAxis;

  // Camera translation vars.
  SbVec3f m_locator3D;
  SbPlane m_focalplane;

  // Plane viewer.
  void computeTranslateValues();
  float m_transXspeed, m_transYspeed;

  // Fly viewer.
  float m_minSpeed, m_maxInc, m_speedLimit;
  float m_speed, m_maxSpeed, m_maxStraightSpeed;
  SbTime m_prevAnimTime;

  // Walk viewer.
  WalkViewerMode m_wvMode;
  SbBool m_walkAnimation;
};

#endif // SO_GUI_ALGO_VIEWERS
