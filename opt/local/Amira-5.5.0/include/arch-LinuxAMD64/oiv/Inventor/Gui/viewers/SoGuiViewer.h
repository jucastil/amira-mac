/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jun 2007)
**=======================================================================*/

#ifndef SO_GUI_VIEWER
#define SO_GUI_VIEWER

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGuiViewer
//
// SoXXViewer implementation class
//
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/Gui/SoGuiRenderArea.h>
#include <Inventor/SbElapsedTime.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBitMask.h>

class SoCallbackList;

// classes
class SoNode;
class SoDirectionalLight;
class SoGroup;
class SoRotation;
class SoCamera;
class SoDrawStyle;
class SoLightModel;
class SoFieldSensor;
class SoGuiViewer;
class SoGetBoundingBoxAction;
class SoSeparator;
class SoShadowGroup;
class SoSwitch;
class SoComplexity;
class SoPackedColor;
class SoMaterialBinding;
class SoSFTime;
class SoNodeSensor;
class SoGetPrimitiveCountAction;
class SoStereoViewer;
class SoBaseStereo;
class SoDepthBuffer;
class SoPerfCounter;

#ifndef HIDDEN_FROM_DOC
// callback function prototypes
typedef void SoGuiViewerCB( void* userData, void* viewer );
typedef void SoGuiViewerCameraTypeChangeCB( void* userData, SoCamera* camera, void* viewer );

// Large Model Viewing notification callbacks for
// frames per second and decimation percentage:
typedef void SoGuiViewerFPSCB( float fps, void* userData, void* viewer );
typedef void SoGuiViewerDecimationPercentageCB( float percentage, void* userData, void* viewer );
#endif

/** [OIV-WRAPPER-NO-WRAP] */
class INVENTORGUI_API SoGuiViewer : public SoGuiRenderArea
{
#ifndef HIDDEN_FROM_DOC
  SO_FIELDCONTAINER_HEADER( SoGuiViewer );
#endif

SoINTERNAL public:
  SoSFBool stereoActive;
  SoSFEnum stereoType;
  SoSFBitMask stereoColorMask;
  SoSFBool hiddenLine;

  enum StereoViewType
  {
    // Monoscopic viewing
    NO_STEREO_VIEW     = 0,
    // Two views interlaced in a single image
    INTERLACED_STEREO  = 1,
    // Each view displayed in a half screen
    HALF_SCREEN_STEREO = 2,
    // Two views superimposed on a single image
    RAW_STEREO         = 3,
    // Ditto
    OPENGL_STEREO      = 3,
    // Each view is displayed through a color filter
    ANAGLYPH_STEREO    = 4,
    // Ditto
    ANAGLYPH           = 4,
#ifndef HIDDEN_FROM_DOC
    // Uses the SSDI library to set the stereo
    SSDI_STEREO        = 5,
#endif

    PASSIVE_STEREO     = 6
  };


  enum Color
  {
    RED = 0x01,
    GREEN = 0x02,
    BLUE = 0x04
  };

  // An EDITOR viewer will create a camera under the user supplied scene
  // graph (specified in setSceneGraph()) if it cannot find one in the
  // scene and will leave the camera behind when supplied with a new scene.
  //
  // A BROWSER viewer will also create a camera if it cannot find one in
  // the scene, but will place it above the scene graph node (camera will
  // not appear in the user supplied scene graph), and will automatically
  // remove it when another scene is supplied to the viewer.
  enum Type
  {
    /**
     *  Camera views scene, but is not added to scene
     */
    BROWSER,
    /**
     *  Camera is added to user's scene
     */
    EDITOR
  };

  //
  // list of possible drawing styles
  //
  // Note: Refer to the SoXxViewer man pages for a complete
  // description of those draw styles.
  //
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

  //
  // list of different buffering types
  //
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

  //
  // list of decimation strategies
  //
  enum DecimationStrategy
  {
    /**
     *  Decimation is not changed
     */
    NORMAL,
    /**
     *  Try to fix number of triangles drawn
     */
    FIXED_NUM_TRIANGLES,
    /**
     *  Try to fix frames per second
     */
    FRAMES_PER_SECOND,
    /**
     *  Use given decimation percentage
     */
    FIXED_PERCENTAGE
  };

  // Classic cursors are all white and tend to disappear over white
  // geometry or white background.  New styles avoid that problem
  enum CursorStyle
  {
    /**
     *  Standard Open Inventor cursors
     */
    CLASSIC,
    /**
     *  Improved cursors using XOR
     */
    XOR,
    /**
     *  Improved cursors using "shadow"
     */
    SHADOW
  };

  // Arrow key direction enum
  enum Direction
  {
    AKP_UP,
    AKP_DOWN,
    AKP_RIGHT,
    AKP_LEFT
  };

  /**
   * Constructor.
   */
  SoGuiViewer();

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
   * Gets the scene graph to render.
   */
  virtual SoNode* getSceneGraph();

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
   * This function saves the scenegraph to an IV file.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE SbBool saveSceneGraph( const char* fileName );


  /**
   * This function saves the scenegraph to an IV file.
   *
   */
  SbBool saveSceneGraph( const SbString& fileName );

  /**
   * Sets the camera type that will be created by the viewer if no cameras are
   * found in the scene graph (see SoPerspectiveCamera and SoOrthographicCamera). By
   * default an SoPerspectiveCamera will be created if no cameras are found.
   *
   * Note: The set method will only take effect the next time a scene graph is
   * specified (and if no cameras are found).
   */
  virtual void setCameraType( SoType type );

  /**
   * Gets the camera type that will be created by the viewer if no cameras are
   * found in the scene graph (see SoPerspectiveCamera and SoOrthographicCamera).
   */
  SoType getCameraType();

  /**
   * If TRUE, an SoPerspectiveCamera's heightAngle is preserved
   * if the camera is changed to an SoOrthographicCamera and
   * then toggled back to an SoPerspectiveCamera. Default is FALSE.
   */
  virtual void setPreserveCameraHeightAngle( SbBool flag );

  /**
   * Query whether the SoPerspectiveCamera's heightAngle is preserved
   * if the camera is changed to an SoOrthographicCamera and
   * then toggled back to an SoPerspectiveCamera.
   */
  virtual SbBool isCameraHeightAnglePreserved() const;

  /**
   * If FALSE, the seek functionality is disabled for an
   * SoOrthographicCamera. Default is TRUE.
   */
  virtual void enableSeekWithOrtho( SbBool flag );

  /**
   * Query whether the seek functionality is enabled for
   * an SoOrthographicCamera.
   */
  virtual SbBool isSeekWithOrthoEnabled() const;

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
   * Queries if the headlight is on.
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
   * Queries the current drawing style in the main view.
   */
  SoGuiViewer::DrawStyle getDrawStyle( SoGuiViewer::DrawType type );

  /**
   * Sets the current buffering type in the main view (default
   * SoGuiViewer::BUFFER_DOUBLE).
   */
  virtual void setBufferingType( BufferType type );

  /**
   * Gets the current buffering type in the main view.
   */
  SoGuiViewer::BufferType getBufferingType();

  /**
   * Sets whether the viewer is turned on or off. When turned on, events are
   * consumed by the viewer. When viewing is off, events are processed by the
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
   * Queries whether the viewer is turned on or off. See setViewing() for details.
   */
  SbBool isViewing() const;

  /**
   * Sets whether the viewer is allowed to change the cursor over the renderArea
   * window. When disabled, the cursor is not defined by the viewer and will not change
   * as the mode of the viewer changes. When re-enabled, the viewer will reset it to
   * the appropriate icon.
   *
   * Disabling the cursor enables the application to set the cursor directly on the
   * viewer window or on any parent widget of the viewer. This can be used when
   * setting a busy cursor on the application shell.
   */
  virtual void setCursorEnabled( SbBool flag );

  /**
   * Queries whether the viewer is allowed to change the cursor over the renderArea
   * window.
   */
  SbBool isCursorEnabled() const;

  /**
   * Sets the auto clipping plane. When auto clipping is ON, the camera near and
   * far planes are dynamically adjusted to be as tight as possible around the
   * objects being viewed. When OFF, the user is expected to manually set those
   * planes within the preference sheet (default is on).
   * Default is ON.
   *
   * The default value can be set using the environment variable
   * OIV_AUTO_CLIPPING (0 = FALSE, 1 = TRUE).
   */
  void setAutoClipping( SbBool flag );

  /**
   * Queries if stereo viewing is on or off on the viewer. See setStereoViewing()
   * for additional info.
   */
  virtual SbBool isStereoViewing();

  /**
   * Queries if auto clipping is ON.
   */
  SbBool isAutoClipping() const;

  /**
   * Sets the stereo offset. See setStereoViewing() for additional info.
   */
  void setStereoOffset( float dist );

  /**
   * Returns the stereo offset. See setStereoViewing() for additional info.
   */
  float getStereoOffset();

  /**
   * When the viewer is in seek mode, left mouse clicks initiate a pick, and the
   * viewer changes its orientation and position to look at the picked object. This
   * routine tells the seeking viewer whether to orient the camera towards the picked
   * point (detail on), or the center of the object's bounding box (detail off).
   * Default is detail on.
   */
  void setDetailSeek( SbBool onOrOff );

  /**
   * Queries whether the viewer is in seek mode.
   */
  SbBool isDetailSeek();

  /**
   * Sets the time a seek takes to change to the new camera location. A value of zero
   * seeks directly to the point without any animation. Default value is 2 seconds.
   *
   * For historical reasons, setting the seek time to zero causes the viewer to stay
   * in seek mode. If you want the camera to move immediately to its new position and
   * still have the viewer leave seek mode after moving the camera, set the seek time
   * to a very small non-zero value.
   *
   * The default value can be set using the environment variable
   * OIV_SEEK_TIME.
   */
  void setSeekTime( float seconds );

  /**
   * Queries the seek time.
   */
  float getSeekTime();

  /**
   * This can be used to let the viewer know that the scene graph has changed so that
   * the viewer can recompute things like speed which depend on the scene graph size.
   * Note: This routine is automatically called whenever setSceneGraph() is
   * called.
   */
  virtual void recomputeSceneSize();

  // --- Large Model Viewing additions:

  /**
   * Sets strategy to use to decide on decimation value.
   * Default is normal. @BR
   * @BR
   * The default value can be set using the environment variable
   * OIV_DECIMATION_STRATEGY.
   * Valid values are NORMAL, FIXED_NUM_TRIANGLES, FRAMES_PER_SECOND, FIXED_PERCENTAGE.
   */
  void setDecimationStrategy( DecimationStrategy strategy );
  /**
   * Gets strategy to use to decide on decimation value.
   */
  DecimationStrategy getDecimationStrategy() const;

  /**
   * Sets goal number of triangles for the viewer to try to render.
   * Default is 10000.@BR
   * @BR
   * The default value can be set using the environment variable
   * OIV_DECIMATION_GOAL_NUM_OF_TRIANGLES.
   */
  void setGoalNumberOfTriangles( int32_t goal );

  /**
   * Gets goal number of triangles for the viewer to try to render.
   */
  int32_t getGoalNumberOfTriangles();

  /**
   * Sets goal frames per second for the viewer to try to render.
   * Default is 8.0. @BR
   * @BR
   * The default value can be set using the environment variable
   * OIV_DECIMATION_GOAL_FPS.
   */
  void setGoalFramesPerSecond( float goal );

  /**
   * Gets goal frames per second for the viewer to try to render.
   */
  float getGoalFramesPerSecond();

  /**
   * Sets fixed percentage for the viewer to render (0.0 to 1.0)
   * Default is 1.0. @BR
   * @BR
   * The default value can be set using the environment variable
   * OIV_DECIMATION_PERCENTAGE (0.0 to 1.0).
   */
  void setFixedPercentage( float percent );

  /**
   * Gets fixed percentage for the viewer to render (0.0 to 1.0)
   */
  float getFixedPercentage();

  /**
   * If this flag is set, the viewer will render at full resolution when it sits
   * still for a certain period of time.
   * Default is false.
   *
   * The default value can be set using the environment variable
   * OIV_FULL_RENDER_WHEN_STILL (0 = FALSE, 1 = TRUE).
   */
  void enableFullRenderingWhenStill( SbBool onOff );

  /**
   * Queries if the viewer will render at full resolution when it sits still for
   * a certain period of time.
   */
  SbBool isFullRenderingWhenStill();

  void setStill( SbBool isStill );
  /**
   * Returns whether the viewer is currently still.
   */
  SbBool isStillNow();

  /**
   * Sets how many frames should be timed before frames per second callback is
   * called, default is -1, The value -1 means that the callback is called every 0.5 
   * seconds. 
   */
  void setNumSamples( int numFrames );

  /**
   * Returns how many frames should be timed before frames per second callback is
   * called. The value -1 means that the callback is called every 0.5 seconds.
   */
  int getNumSamples();

  /**
   * Returns the Decimation Percentage the viewer used in its last render.
   */
  float getCurrentDecimationPercentage();

  // Implementing methods from the pure virtual class from SoStereoViewer
  virtual SoCamera* getViewerCamera();
  virtual SbBool isViewerDoubleBuffer();
  virtual void actualRendering();
  virtual void adjustClippingPlanes();
  virtual const SbVec2s& getSize();
  void setStereoViewType( SoBaseStereo* stereo );
  SoBaseStereo* getStereoViewType();
  void reverseStereoView( SbBool reverse );
  SbBool isStereoViewReversed();
  virtual void setStereoAbsoluteAdjustments( SbBool absolute );
  virtual SbBool isStereoAbsoluteAdjustments() const;
  virtual void setStereoBalance( float balance, SbBool nearFrac = false );
  virtual float getStereoBalance();
  virtual SbBool isStereoBalanceNearFrac();
  virtual void setStereoActive( SbBool activate ) ;
  virtual SbBool isStereoActive() ;
  void setViewport( short left, short bottom, short width, short height ) ;
  void getViewport( short& left, short& bottom, short& width, short& height ) ;

  SoSeparator* getSceneRoot();

  /**
   * Sets the cursor style.
   * The standard Open Inventor (CLASSIC) cursors use all white pixels, which can be
   * difficult to see over light colored geometry or background. The XOR and SHADOW
   * style cursors are much easier to see. The XOR style cursors that have a "hand"
   * shape differ from the other styles in that the cursor hotspot is at the tip of
   * the index finger. This generally works better for picking.
   *
   * The cursor can also be specified using environment variable OIV_CURSOR_STYLE,
   * where the values 0, 1, and 2 specify Classic, XOR, and Shadow cursors
   * respectively.
   *
   * Note: This method only has an effect if #setCursorEnabled is set to TRUE.
   */
  virtual void setCursorStyle( CursorStyle style );

  /**
   * Returns the cursor style.
   */
  CursorStyle getCursorStyle() const;

  /**
   * Sets the auto clipping tolerance value. Auto clipping normally sets the near
   * and far clip planes based on the scene's bounding box. If the camera is inside
   * the scene bounding box, the near plane is moved in front of the camera using
   * @B tolerance @b*bbox size. The default is 0.001.
   *
   * The default value can be set using the environment variable
   * OIV_AUTO_CLIP_TOLERANCE.
   */
  void setAutoClipTolerance ( float tolerance );

  /**
   * Gets the auto clipping tolerance value.
   */
  float getAutoClipTolerance () const;

  /**
    * Sets the sub-scene graph to be used for #viewAll computation.
    * If this sub-scene graph contains a camera, this camera will be used
    * as the viewer camera.
    * Otherwise the first camera of the scene graph will be used.
    * If no camera found, the viewer will create its own before the root.
    * When #viewAll computes the bounding box that will be used
    * for determining where to position the camera, it will base its
    * computation on this sub-scene graph rather than on the entire scene graph.
    *
    * It is useful to specify a sub-scene graph when, for instance, you are
    * using a second camera in the scene, followed by annotation. With this method
    * you can exclude the annotation from the viewAll bounding box computation.
    *
    * This method can also be useful when using PoView/PoSceneView.
    * As the viewer uses the first camera it finds, it could find the camera
    * of a PoView/PoSceneView. The bounding box would be computed based on the
    * sub-scene graph owned by this PoView/PoSceneView. Thus the global bounding
    * box of the whole scene would be wrong, causing some clipping problems
    * when viewing.
    */
  virtual void setCameraSceneGraph( SoNode* cameraSceneGraph );

  /**
   * Gets the sub-scene graph to be viewed. See setCameraSceneGraph().
   */
  SoNode* getCameraSceneGraph();

  /**
   * Adds a shadow group to the scene graph and turns it on if true.
   * The shadow group's @I method @i field is set to VARIANCE_SHADOW_MAP.
   */
  void enableShadows( bool onOrOff );

  /** 
   * Returns TRUE if shadows are enabled.
   */
  SbBool isEnableShadows();

  /** 
   * Gets the current SoShadowGroup node in scene graph.
   */
  SoShadowGroup* getShadowGroup();

  /**
   * Enable/disable moving the camera with the mouse wheel,
   * TRUE by default
   */
  void enableMouseWheelDolly( SbBool onOff );
  SbBool isMouseWheelEnabled() const;

  SbBool isInteractive() const;

  // This routine will toggle the current camera from perspective to
  // orthographic, and from orthographic back to perspective.
  virtual void toggleCameraType();

  /**
   * Set the viewer into/out of seek mode (default OFF). Actual
   * seeking will not happen until the viewer decides to,
   * for example, on a mouse click.
   *
   * Note: Setting the viewer out of seek mode while the camera is being
   * animated will stop the animation at the current location.
   */
  virtual void setSeekMode( SbBool flag );
  SbBool isSeekMode() const;

  // Accessor and mutator for the member m_interactiveFlag
  void setInteractiveFlag( SbBool flag );
  SbBool getInteractiveFlag() const;

  // Accessor and mutator for the member m_stillDrawStyle
  void setStillDrawStyle( DrawStyle style );
  DrawStyle getStillDrawStyle() const;

  // Accessor and mutator for the member m_interactiveDrawStyle
  void setInteractiveDrawStyle( DrawStyle style );
  DrawStyle getInteractiveDrawStyle() const;

  // Accessor and mutator for the member m_seekStartTime
  void setSeekStartTime( SbTime seekTime );
  SbTime getSeekStartTime() const;

  // Accessor and mutator for the member m_newCamOrientation
  void setNewCamOrientation( SbRotation newOrientation );
  SbRotation getNewCamOrientation() const;

  // Accessor and mutator for the member m_newCamOrientation
  void setSeekPoint( SbVec3f newOrientation );
  SbVec3f getSeekPoint() const;

  // Accessor and mutator for the member m_viewerSpeed
  void setViewerSpeed( float speed );
  float getViewerSpeed() const;

  // Mutator for the member m_headlightFlag
  void setHeadLightFlag( SbBool flag );

  // Accessor and Mutator for the member m_createdCursors
  void setCreatedCursors( SbBool flag );
  SbBool getCreatedCursors() const;

  // Mutator for the member m_interactiveCount
  void setInteractiveCount( int count );

  // Accessor for the member m_finishCBList
  SoCallbackList* getFinishCBList();

  // Accessor and mutator for the member m_checkForDrawStyle
  void setCheckForDrawStyle( SbBool flag );
  SbBool getCheckForDrawStyle() const;

  // Accessor and mutator for the member m_type
  void setType( Type type );
  Type getType() const;

  // Accessor and mutator for the member m_viewerRealTime
  void setRealTime( SoSFTime* type );
  SoSFTime* getRealTime() const;

  // Enable DirectViz
  virtual void enableDirectViz( SbBool flag );

  virtual void internalEnableDirectViz( SbBool flag );

  // Accessor and mutator for the member m_directVizFlag
  void setDirectVizFlag( SbBool enable );
  SbBool getDirectVizFlag() const;

  // Accessor and mutator for the member m_seekDistance
  void setSeekDistance( float seekDistance );
  float getSeekDistance();

  // Accessor and mutator for the member m_sceneSize
  void setSceneSize( float size );
  float getSceneSize();

  // Retro compatibility accessors
  SbBool getComputeSeekVariables() const { return m_computeSeekVariables; }
  float getPreviousHeightAngle() { return m_previousHeightAngle; }
  SbVec3f getSeekNormal() { return m_seekNormal; }
  SbVec3f getNewCamPosition() { return m_newCamPosition; }

  // Seek sensor accessors
  void setSeekSensor( SoFieldSensor* s );
  SoFieldSensor* getSeekSensor() const;

  // Accessor for the member m_createdCamera
  SbBool getCreatedCamera() const;

  void setViewer( void* viewer );

  // redefine this to call the viewer setBufferingType() method instead.
  virtual void setDoubleBuffer( SbBool flag );

  // Writes to file the scene graph
  //
  // @UNICODE_WARNING
  SoNONUNICODE static void writeScene( SoNode* node, const char* filename );

  // Writes to file the scene graph
  static void writeScene( SoNode* node, const SbString& filename );

  // Callbacks
  void setCameraTypeChangeCallback( SoGuiViewerCameraTypeChangeCB* callback, void* userdata );
  void addStartCallback( SoGuiViewerCB* f, void* userData = NULL );
  void addFinishCallback( SoGuiViewerCB* f, void* userData = NULL );
  void removeStartCallback( SoGuiViewerCB* f, void* userData = NULL );
  void removeFinishCallback( SoGuiViewerCB* f, void* userData = NULL );

  /**
   * Registers frames per second callback.
	 * [OIV-WRAPPER-CUSTOM-CODE]
   */
  void setFramesPerSecondCallback( SoGuiViewerFPSCB* callback, void* userData = NULL );

  /**
   * Registers decimation percentage callback.
	 * [OIV-WRAPPER-CUSTOM-CODE]
   */
  void setDecimationPercentageCallback( SoGuiViewerDecimationPercentageCB* callback, void* userData = NULL );

  SbBool isZBufferOff();

  void arrowKeyPressed( Direction direction );

  //Inner public class
  class CameraFields {
  public:
    CameraFields();
    SbBool isModified( SoCamera* cam );
    void setCameraFields( SoCamera* cam );

  private:
    int m_viewportMapping;
    SbVec3f m_position;
    SbRotation m_orientation;
    float m_aspectRatio;
    float m_nearDistance;
    float m_farDistance;
    float m_focalDistance;
    float m_height;
  };

  // ----------------------- Extension usage -----------------------------------

  virtual void afterRealizeHook();

  virtual void  adjustCameraClippingPlanes();

  // Invokes the start and finish viewing callbacks. Subclasses NEED to call
  // those routines when they start and finish doing interactive viewing
  // operations so that correct interactive drawing style and buffering
  // types, as well as application callbacks, gets set and called properly.
  //
  // Those routines simply increment and decrement a counter. When the counter
  // changes from 0->1 the start viewing callbacks are called. When the counter
  // changes back from 1->0 the finish viewing callbacks are called.
  // The counter approach enables different parts of a viewer to call those
  // routines withough having to know about each others (which is not
  void interactiveCountInc();
  void interactiveCountDec();
  int getInteractiveCount();

  //
  // This routine is used by subclasses to initiate the seek animation. Given a
  // screen mouse location, this routine will return the picked point
  // and the normal at that point. It will also schedule the sensor to animate
  // if necessary. The routine retuns TRUE if something got picked...
  //
  // Note: if detailSeek is on, the point and normal correspond to the exact
  // 3D location under the cursor.
  // if detailSeek if off, the object bbox center and the camera
  // orientation are instead returned.
  SbBool seekToPoint( const SbVec2s& mouseLocation );

  // Subclasses CAN redefine this to interpolate camera position/orientation
  // while the seek animation is going on (called by animation sensor).
  // The parameter t is a [0,1] value corresponding to the animation percentage
  // completion. (i.e. a value of 0.25 means that animation is only 1/4 of the way
  // through).
  virtual void interpolateSeekAnimation( float t );
  virtual void computeSeekFinalOrientation();

  // redefine this routine to adjust the camera clipping planes just
  // before doing a redraw. The sensor will be unschedule after the camera
  // is changed in the base class to prevent a second redraw from occuring.
  virtual void actualRedraw();

  // This is called during a paste.
  // Subclasses may wish to redefine this in a way that
  // keeps their viewing paradigm intact.
  virtual void changeCameraValues( SoCamera* newCamera );

  // Override redraw() in order to calculate render time including
  // frame buffer switch
  virtual void preViewerRedraw();
  virtual void postViewerRedraw();

  // Subclasses may override this function to change way that
  // viewer tries to calculate decimation percentage for
  // DecimationStrategy FRAMES_PER_SECOND.
  // Given goal frames per second, timeTaken in last render,
  // and last decimation value used, this function should return
  // decimation percentage value to use in next render.
  virtual float decimationForFramesPerSecond( float fps,
                                              double lasttime,
                                              float lastDec );
  // Subclasses may override this function to change way that
  // viewer tries to calculate decimation percentage for
  // DecimationStrategy FIXED_NUM_TRIANGLES.
  // Given goal number of triangles to reach, this function
  // should return decimation percentage value to use.
  virtual float decimationForNumTriangles( uint32_t numTris );

  // Convenience routines which subclasses can use when drawing viewer
  // feedback which may be common across multiple viewers. There is for
  // example a convenience routine which sets an orthographics projection
  // and a method to draw common feedback like the roll anchor (used by
  // a couple of viewers).
  //
  // All drawing routines assume that the window and projection is
  // already set by the caller.
  //
  // set an ortho projection of the glx window size - this also turns
  // zbuffering off and lighting off (if necessary).
  static void setFeedbackOrthoProjection( const SbVec2s& size );
  // restores the zbuffer and lighting state that was changed when
  // setFeedbackOrthoProjection() was last called.
  static void restoreGLStateAfterFeedback();
  // draws a simple 2 colored cross at given position
  static void drawViewerCrossFeedback( SbVec2s loc );
  // draws the anchor feedback given center of rotation and mouse location
  static void drawViewerRollFeedback( SbVec2s center, SbVec2s loc );

  void setCurrentDrawStyle( SoGuiViewer::DrawStyle style );

  void doBoxZoom( int x1, int y1, int x2, int y2 );
  void setZoomMode( SbBool zoomMode );
  SbBool isZoomModeEnabled() const;
  void setSeekDistAsPercentage( SbBool seekDist );

protected:

  /**
   * Destructor.
   */
  virtual ~SoGuiViewer();

  SoShadowGroup* getShadowGroup() const { return m_shadowGroup; };

  SoGetBoundingBoxAction* m_sceneSizeBBoxAction;
  static void seekAnimationSensorCB( void* p, SoSensor* sensor );

  // ----------------------- Private usage -------------------------------------

private:

  void doRendering();
  static void drawStyleStartCallback( void* userData, void* v );
  static void drawStyleFinishCallback( void* userData, void* v );
  static void changeCB( void* thisp, SoSensor* sensor );
  void changeSensorCalled();

  // local tree variables
  SoSeparator* m_sceneRoot; // root node given to the RA
  SoNode* m_sceneGraph; // user supplied scene graph
  void* m_viewerPtr;

  // global vars
  SoNode* m_cameraSceneGraph;
  SoType m_cameraType;
  SoCamera* m_camera; // camera being edited
  SoGuiViewer::Type m_type;
  SbBool m_viewingFlag; // FALSE when the viewer is off
  SbBool m_directVizFlag; // TRUE if DirectViz rendering is enabled
  SbBool m_interactiveFlag; // TRUE while doing interactive work
  BufferType m_bufferType;
  SbBool m_cursorEnabledFlag;
  float m_sceneSize; // the larger of the X,Y,Z scene BBox
  static SoSFTime* m_viewerRealTime; // pointer to "realTime" global field
  SbBool m_firstLeftRender;
  float m_viewerSpeed;

  // camera original values, used to restore the camera
  SbBool m_createdCamera;
  SbVec3f m_origPosition;
  SbRotation m_origOrientation;
  float m_origNearDistance;
  float m_origFarDistance;
  float m_origFocalDistance;
  float m_origHeight;

  // headlight variables
  SbBool m_headlightFlag; // true when headlight in turned on
  SoGroup* m_headlightGroup;
  SoDirectionalLight* m_headlightNode;
  SoRotation* m_headlightRot;

  // current state vars
  SbBool m_preserveHeightAngle;
  SbBool m_seekWithOrtho;
  SbBool m_mouseWheelEnable;
  float  m_previousHeightAngle;
  CameraFields* m_prevCam;
  SoBaseStereo* m_stereoViewType;
  SbBool m_stereoActive;
  float m_farDistS;
  float m_nearDistS;

  // draw style vars
  SbBool m_checkForDrawStyle;
  DrawStyle m_stillDrawStyle, m_interactiveDrawStyle;
  SoSwitch* m_drawStyleSwitch; // on/off draw styles
  SoDrawStyle* m_drawStyleNode; // LINE vs POINT
  SoLightModel* m_lightModelNode; // BASE_COLOR vs PHONG
  SoComplexity* m_complexityNode; // low complexity & texture off
  SoPackedColor* m_colorNode; // hidden line first pass
  SoMaterialBinding *m_matBindingNode; // hidden line first pass
  SoDepthBuffer *m_depthBuffer ; // depth buffer parameters

  // shadows
  SoShadowGroup* m_shadowGroup;
  bool m_shadowGroupCurrState;

  // auto clipping vars and routines
  SbBool m_autoClipFlag;
  float m_minimumNearPlane; // minimum near plane as percentage of far
  SoGetBoundingBoxAction* m_autoClipBboxAction;

  // seek animation vars
  SbBool m_detailSeekFlag;
  float m_seekAnimTime;
  SbBool m_seekModeFlag; // TRUE when seek turned on externally
  SoFieldSensor* m_seekAnimationSensor;

  // Decimation strategy additions
  DecimationStrategy m_decStrategy;
  SbBool m_isStill, m_doFullRendering, m_wasStill;
  int32_t m_goalTris; // Goal Number of Triangles
  float m_goalFps; // Goal Frames Per Second
  float m_decPercentage; // Fixed percentage
  float m_lastDecimationValue; // Last decimation value and render time
  double m_lastRenderTime; // used when (strategy==FRAMES_PER_SECOND)

  SoPerfCounter* m_fpsCounter;

  int m_lastDirection;
  SoGetPrimitiveCountAction* m_primCountAction;
  SoNodeSensor* m_motionSensor;

  // Frames per second calculating:
  int m_numSamples;
  SoGuiViewerFPSCB* m_fpsUserCallback;
  void* m_fpsUserData;

  // For release 2.6 we added the concept of cursor "style", at least
  // on Windows, and moved the definition variables and methods up to
  // this class (protected not private!) so subclasses can override
  // the cursor definitions if they need/want to.
  //
  // We now have "classic", XOR and "shadow" style cursors (new in v2.6)
  SoGuiViewer::CursorStyle m_cursorStyle;
  // Previously declared in subclasses (before v2.6)
  // Note that each subclass viewer uses a subset of these standard
  // cursor names.  Note that the Fly and Walk viewers used slightly
  // different names (that were too generic) for their specific cursors
  // (the last two in the list) prior to v2.6.
  SbBool m_createdCursors;

  // interactive viewing callbacks
  SoCallbackList* m_startCBList;
  SoCallbackList* m_finishCBList;

  // variables used for interpolating seek animations
  SbVec3f m_seekPoint, m_seekNormal;
  SbBool m_computeSeekVariables;
  SbTime m_seekStartTime;
  SbRotation m_oldCamOrientation, m_newCamOrientation;
  SbVec3f m_oldCamPosition, m_newCamPosition;
  float m_oldCamHeight;
  float m_seekDistance;
  SbBool m_seekDistAsPercentage; // percentage/absolute flag

  // flag indicating whether a render traversal is in
  // progress.
  SbBool m_isWinRedrawing;

  // Camera type change callback
  SoGuiViewerCameraTypeChangeCB* m_viewerCameraTypeChangeCallback;
  void* m_viewerCameraTypeChangeCallbackUserData;

  // Decimation Percentage callback
  SoGuiViewerDecimationPercentageCB* m_decimationUserCallback;
  void* m_decimationUserData;

  SbBool m_zoomMode;
};

#endif // SO_GUI_VIEWER


