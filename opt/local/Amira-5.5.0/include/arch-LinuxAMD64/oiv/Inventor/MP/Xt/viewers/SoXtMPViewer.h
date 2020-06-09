/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#if defined(_WIN32)
#  include <Inventor/MP/Win/viewers/SoWinMPViewer.h>
#else // _WIN32

#ifndef  _SO_XT_MP_VIEWER_
#define  _SO_XT_MP_VIEWER_

#include <Inventor/SoType.h>
#include <Inventor/MP/Xt/SoXtMPRenderArea.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/SbElapsedTime.h>

// classes
class SoNode;
class SoDirectionalLight;
class SoGroup;
class SoRotation;
class SoCamera;
class SoDrawStyle;
class SoLightModel;
class SoFieldSensor;
class SoXtClipboard;
class SoXtMPViewer;
class SoGetBoundingBoxAction;
class SbPList;
class SoSeparator;
class SoSwitch;
class SoComplexity;
class SoPackedColor;
class SoMaterialBinding;
class SoSFTime;
class SoXtInputFocus;
class SoAlarmSensor;
class SoNodeSensor;
class SoGetPrimitiveCountAction;
class SoStereoViewer;
class SoBaseStereo;
class SoTransform;

// callback function prototypes
typedef void SoXtMPViewerCB(void *userData, SoXtMPViewer *viewer);
typedef void SoXtMPViewerCameraTypeChangeCB(void *userData, SoCamera *camera, SoXtMPViewer *viewer);

// Large Model Viewing notification callbacks for 
// frames per second and decimation percentage:
typedef void SoXtMPViewerFPSCB(float fps, void *userData, SoXtMPViewer *viewer);
typedef void SoXtMPViewerDecimationPercentageCB(float percentage, void *userData, SoXtMPViewer *viewer);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtMPViewer
//
//      The Viewer component is the abstract base class for all viewers.
//  It is subclassed from renderArea, adding viewing semantics to Inventor
//  rendering.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Viewer component lowest base class.
 * 
 * @ingroup ScaleVizMultiPipe
 * 
 * @DESCRIPTION
 *   This is the lowest base class for viewer components. This class adds the notion
 *   of a camera to the SoXtMPRenderArea class. Whenever a new scene is specified with
 *   setSceneGraph(), the first camera encountered will be by default used as
 *   the edited camera. If no camera is found in the scene, the viewer will
 *   automatically create one. The viewer will use the first SoVRMLViewpoint
 *   encountered (if any) to define the parameters of the created camera. If the
 *   viewer type is SoXtMPViewer::BROWSER then the camera is told to view the supplied
 *   scene graph but is not added beneath that scene graph root. If the viewer type
 *   is SoXtMPViewer::EDITOR then the camera is added beneath the supplied scene graph
 *   root.
 *   
 *   In addition to automatically creating a camera if needed, this base class also
 *   creates a headlight (directional light which is made to follow the camera),
 *   enables the user to change drawing styles (like wireframe or move wireframe),
 *   and buffering types. This base class also provides a convenient way to have the
 *   camera near and far clipping planes be automatically adjusted to minimize the
 *   clipping of objects in the scene.
 *   
 *   Viewers allow the application to shadow event processing. When the application
 *   registers an event processing callback by calling setEventCallback() the
 *   viewer will invoke this callback for every X event it receives. However, unlike
 *   the render area, the viewer ignores the return value of this callback, and
 *   processes the event as usual. This allows the application to expand viewing
 *   capabilities without breaking the viewing paradigm. It is an easy way to hook up
 *   other devices, like the spaceball, to an existing viewer.
 *   
 *   Depending on the DecimationStrategy, a viewer can control the complexity of a
 *   scene by adjusting the Decimation elements to reach certain goals. The viewer
 *   can attempt to keep a constant frame rate or a constant number of triangles
 *   rendered. The viewer can be set to switch to full detail when the scene is not
 *   moving.
 *   
 *   In order to set the frame rate, the viewer times each render action traversal,
 *   and then adjusts the Decimation percentage to keep the time within a range
 *   depending on the goal frames per second. To fix the number of triangles, the
 *   viewer applies a GetPrimitiveCountAction before each traversal and sets the
 *   DecimationPercentage to the desired percentage of the resulting count.
 *   
 *   If the DecimationStrategy is NORMAL (the default) then nothing special is done.
 *   If the strategy is FIXED_PERCENTAGE, then the same percentage is used for every
 *   render. Also note that FIXED_PERCENTAGE sets the DecimationType to be PERCENTAGE
 *   (all others use AUTOMATIC), which means that instances of SoLOD will not use the camera
 *   position in their calculations, and can therefore be cached.
 *   
 *   The application can add callbacks from the viewer to get the current decimation
 *   level, the current primitive count and the current frames per second. The
 *   decimation level and primitive count callbacks are called every frame. The
 *   frames per second callback is called after a certain number of samples have been
 *   averaged together.
 * 
 * @SEE_ALSO
 *    SoXtComponent,
 *    SoXtMPRenderArea,
 *    SoXtMPExaminerViewer,
 *    SoXtMPWalkViewer,
 *    SoXtMPFlyViewer,
 *    SoXtMPPlaneViewer
 * 
 * 
 */ 

class INVENTORXT_API SoXtMPViewer : public SoXtMPRenderArea
{
 public:

    /**
    * An EDITOR viewer will create a camera under the user supplied scene
    * graph (specified in setSceneGraph()) if it cannot find one in the
    * scene and will leave the camera behind when supplied with a new scene.
    *
    * A BROWSER viewer will also create a camera if it cannot find one in
    * the scene, but will place it above the scene graph node (camera will 
    * not appear in the user supplied scene graph), and will automatically 
    * remove it when another scene is supplied to the viewer.
    */
  enum Type {
    /**
     *  Camera views scene, but is not added to scene 
     */
    BROWSER,
    /**
     *  Camera is added to user's scene 
     */
    EDITOR
  };
  
    /** 
    * list of possible drawing styles
    *
    * Note: Refer to the SoXtMPViewer man pages for a complete 
    * description of those draw styles.
    */
  enum DrawStyle {
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
   
    /** DrawType */
  enum DrawType {
    /**
     *  Applies to static rendering 
     */
    STILL,
    /**
     *  Applies to rendering while interactive viewing 
     */
    INTERACTIVE
  };

    /** list of different buffering types */
  enum BufferType {
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
  
    /** list of decimation strategies */
  enum DecimationStrategy {
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
  
  /**
   * Sets the scene graph to render. Whenever a new scene is supplied
   * the first camera encountered will be by default used as the edited
   * camera, else a new camera will be created.
   */
  virtual void setSceneGraph(SoNode *newScene);
  /**
   * Gets the scene graph to render.
   */
  virtual SoNode *getSceneGraph();
  
  /**
   * Sets the edited camera. Setting the camera is only needed if the first
   * camera found in the scene when setting the scene graph isn't the one the user
   * really wants to edit.
   */
  virtual void setCamera(SoCamera *cam);
  /**
   * Gets the edited camera.
   */
  SoCamera *getCamera() { return camera; }
  
  /**
   * Sets the camera type that will be created by the viewer if no cameras are
   * found in the scene graph (see SoPerspectiveCamera and SoOrthographicCamera). By
   * default an SoPerspectiveCamera will be created if no cameras are found.
   * 
   * Note: The set method will only take effect the next time a scene graph is
   * specified (and if no cameras are found).
   */
  virtual void setCameraType(SoType type);
  /**
   * Gets the camera type that will be created by the viewer if no cameras are
   * found in the scene graph (see SoPerspectiveCamera and SoOrthographicCamera). 
   */
  SoType getCameraType() { return cameraType; }

  /**
   * If TRUE, an SoPerspectiveCamera's heightAngle is preserved
   * if the camera is changed to an SoOrthographicCamera and
   * then toggled back to an SoPerspectiveCamera. Default is FALSE.
   */
  virtual void          setPreserveCameraHeightAngle(SbBool flag)
    {m_preserveHeightAngle = flag; }

  /**
   * Query whether the SoPerspectiveCamera's heightAngle is preserved
   * if the camera is changed to an SoOrthographicCamera and
   * then toggled back to an SoPerspectiveCamera.
   */
  virtual SbBool     isCameraHeightAnglePreserved() const
    {return m_preserveHeightAngle; }

  /**
   * If FALSE, the seek functionality is disabled for an 
   * SoOrthographicCamera. Default is TRUE.
   */
  virtual void          enableSeekWithOrtho(SbBool flag)
    {m_seekWithOrtho = flag; }

  /**
   * Query whether the seek functionality is enabled for
   * an SoOrthographicCamera. 
   */
  virtual SbBool     isSeekWithOrthoEnabled() const
    {return m_seekWithOrtho; }
  
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
   * Defines a callback which is called each time the camera type has changed (change
   * from SoPerspectiveCamera to SoOrthographicCamera or vice versa).
   */
  void setCameraTypeChangeCallback(SoXtMPViewerCameraTypeChangeCB *callback,
                                   void *userdata);
  
  /**
   * Turns the headlight on/off (default on).
   */
  virtual void setHeadlight(SbBool onOrOff);
  /**
   * Queries if the headlight is on.
   */
  SbBool isHeadlight() { return headlightFlag; }
  /**
   * Returns the headlight node.
   */
  SoDirectionalLight *getHeadlight() { return headlightNode; }
  
  /**
   * Sets the current drawing style in the main view. The user can specify the
   * INTERACTIVE draw style (draw style used when the scene changes) independently
   * from the STILL style. Default is VIEW_AS_IS draw style for STILL and
   * VIEW_SAME_AS_STILL for INTERACTIVE. Possible draw styles are:
   * 
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
  virtual void setDrawStyle(SoXtMPViewer::DrawType type, 
                            SoXtMPViewer::DrawStyle style);
  /**
   * Queries the current drawing style in the main view. 
   */
  SoXtMPViewer::DrawStyle getDrawStyle(SoXtMPViewer::DrawType type);
  
  /**
   * Sets the current buffering type in the main view (default
   * SoXtMPViewer::BUFFER_DOUBLE).
   */
  virtual void setBufferingType( SoXtMPViewer::BufferType type);
  /**
   * Gets the current buffering type in the main view.
   */
  SoXtMPViewer::BufferType getBufferingType() { return bufferType; }
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
  virtual void setViewing(SbBool onOrOff);
  /**
   * Queries whether the viewer is turned on or off. See setViewing() for details.
   */
  SbBool isViewing() const { return viewingFlag; };
  
  /**
   * Sets whether the viewer is allowed to change the cursor over the renderArea
   * window. When disabled, the cursor is undefined by the viewer and will not change
   * as the mode of the viewer changes. When re-enabled, the viewer will reset it to
   * the appropriate icon.
   * 
   * Disabling the cursor enables the application to set the cursor directly on the
   * viewer window or on any parent widget of the viewer. This can be used when
   * setting a busy cursor on the application shell. 
   */
  virtual void setCursorEnabled(SbBool onOrOff);
  /**
   * Queries whether the viewer is allowed to change the cursor over the renderArea
   * window. 
   */
  SbBool isCursorEnabled() const { return cursorEnabledFlag; }
  
  /**
   * Sets the auto clipping plane. When auto clipping is ON, the camera near and
   * far planes are dynamically adjusted to be as tight as possible around the
   * objects being viewed. When OFF, the user is expected to manually set those
   * planes within the preference sheet (default is on).
   */
  void setAutoClipping(SbBool onOrOff);
  /**
   * Queries if auto clipping is ON.
   */
  SbBool isAutoClipping() const { return autoClipFlag; }
  
  /**
   * Turns stereo viewing on/off on the viewer (default off). When in stereo mode,
   * which may not work on all machines, the scene is rendered twice (in the left and
   * right buffers) with an offset between the two views to simulate stereo viewing.
   * Stereo glasses have to be used to see the effect. Stereo viewing is only
   * possible with a graphics board that has support for stereo.
   */
  //  virtual void setStereoViewing(SbBool onOrOff);
  /**
   * Queries if stereo viewing is on or off on the viewer. See setStereoViewing()
   * for additional info.
   */
  //  virtual SbBool isStereoViewing();

  /**
   * When the viewer is in seek mode, left mouse clicks initiate a pick, and the
   * viewer changes its orientation and position to look at the picked object. This
   * routine tells the seeking viewer whether to orient the camera towards the picked
   * point (detail on), or the center of the object's bounding box (detail off).
   * Default is detail on.
   */
  void setDetailSeek(SbBool onOrOff) { detailSeekFlag = onOrOff; };
  /**
   * Queries whether the viewer is in seek mode.
   */
  SbBool isDetailSeek() { return detailSeekFlag; }
  
  /**
   * Sets the time a seek takes to change to the new camera location. A value of zero
   * seeks directly to the point without any animation. Default value is 2 seconds.
   */
  void setSeekTime(float seconds) { seekAnimTime = seconds; }
  /**
   * Queries the seek time.
   */
  float getSeekTime() { return seekAnimTime; }
  
  /**
   * Adds start callback routine on the viewer. Start callbacks are
   * called whenever the user starts doing interactive viewing (for example, mouse
   * down), and finish callbacks are called when user is done doing interactive work
   * (for example, mouse up).
   * 
   * Note: The viewer "this" pointer is passed as callback data.
   */
  void addStartCallback(SoXtMPViewerCB *f, void *userData = NULL)
    { startCBList->addCallback((SoCallbackListCB *)f, userData); }
  /**
   * Adds finish callback routines on the viewer. Start callbacks are
   * called whenever the user starts doing interactive viewing (for example, mouse
   * down), and finish callbacks are called when user is done doing interactive work
   * (for example, mouse up).
   * 
   * Note: The viewer "this" pointer is passed as callback data.
   */
  void addFinishCallback(SoXtMPViewerCB *f, void *userData = NULL)
    { finishCBList->addCallback((SoCallbackListCB *)f, userData); }
  /**
   * Removes start callback routine from the viewer. 
   * 
   * Note: The viewer "this" pointer is passed as callback data.
   */
  void removeStartCallback(SoXtMPViewerCB *f, void *userData = NULL)
    { startCBList->removeCallback((SoCallbackListCB *)f, userData); }
  /**
   * Removes finish callback routine from the viewer. 
   * 
   * Note: The viewer "this" pointer is passed as callback data.
   */
  void removeFinishCallback(SoXtMPViewerCB *f, void *userData = NULL)
    { finishCBList->removeCallback((SoCallbackListCB *)f, userData); }
  
  /**
   * Copies the view. @B eventTime @b should be the time of the X event which
   * initiated the copy (e.g. if copy is initiated from a keystroke,
   * @B eventTime @b should be the time in the key down message.)
   */
  void copyView(Time eventTime);
  /**
   * Pastes the view. @B eventTime @b should be the time of the X event which
   * initiated the paste (e.g. if paste is initiated from a keystroke,
   * @B eventTime @b should be the time in the key down message.)
   */
  void pasteView(Time eventTime);
  
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
   */
  void setDecimationStrategy(DecimationStrategy strategy);
  /**
   * Gets strategy to use to decide on decimation value.
   */
  DecimationStrategy getDecimationStrategy() {return decStrategy; };
  
  /**
   * Sets goal number of triangles for the viewer to try to render.
   */
  void setGoalNumberOfTriangles(int32_t goal);
  /**
   * Gets goal number of triangles for the viewer to try to render.
   */
  int32_t getGoalNumberOfTriangles() { return goalTris; };
  
  /**
   * Sets goal frames per second for the viewer to try to render.
   */
  void setGoalFramesPerSecond(float goal);
  /**
   * Gets goal frames per second for the viewer to try to render.
   */
  float getGoalFramesPerSecond() { return goalFps; };
  
  /**
   * Sets fixed percentage for the viewer to render (0.0 to 1.0)
   */
  void setFixedPercentage(float percent);
  /**
   * Gets fixed percentage for the viewer to render (0.0 to 1.0)
   */
  float getFixedPercentage() { return decPercentage; };
  
  /**
   * If this flag is set, the viewer will render at full resolution when it sits
   * still for a certain period of time.
   */
  void enableFullRenderingWhenStill(SbBool onOff);
  /**
   * Queries if the viewer will render at full resolution when it sits still for
   * a certain period of time.
   */
  SbBool isFullRenderingWhenStill() { return doFullRendering; };
  
  /**
   * Returns whether the viewer is currently still.
   */
  SbBool isStillNow() { return isStill; };
  
  /**
   * Registers frames per second callback.
   */
  void setFramesPerSecondCallback(SoXtMPViewerFPSCB *callback, 
                                  void *userData = NULL);
  
  /**
   * Sets how many frames should be timed before frames per second callback is
   * called, default is 10.
   */
  void setNumSamples(int numFrames);
  /**
   * Gets how many frames should be timed before frames per second callback is
   * called.
   */
  int getNumSamples() { return numSamples; };
  
  /**
   * Registers decimation percentage callback.
   */
  void setDecimationPercentageCallback(
                                       SoXtMPViewerDecimationPercentageCB *callback,
                                       void *userData = NULL);
  
  /**
   * Returns the Decimation Percentage the viewer used in its last render.
   */
  float getCurrentDecimationPercentage(); 
  
  /**
   * Always returns NULL on UNIX systems.
   */
  /*  HDC getCurrentDC() {  return NULL; } fkw*/
  
  /**
   * add an SoTransform node just after the viewer's camera
   */
  void insertSceneTransform(void);
  
  /**
   * returns the SoTransform node
   */
  SoTransform * getSceneTransform(void);
  
  /** 
   * returns the SoTransform that modifies the wand
   */
  SoTransform * getWandTransform(void);

  /** 
   *  set the file containing the wand geometry
   */
  void setWandGeometryFile(SbString wandFile);

  /** 
   *  sets the sensor id that tracks the head. If set with value of -1,
   * headtracking is disabled.
   */
  void setHeadTracking(int value);
  
  virtual void navigate(void);
  

 SoINTERNAL public:
  virtual ~SoXtMPViewer();

  // redefine this to call the viewer setBufferingType() method instead.
  virtual void setDoubleBuffer(SbBool onOrOff);

  // redefine this routine to also correctly set the buffering type
  // on the viewer.
  virtual void setNormalVisual(XVisualInfo *);
  
  
  // tell whether create the wand or not. Default is TRUE 
  void useWand(SbBool flag)
    { addWandGroup = flag;};
  
  
  // Implementing methods from the pure virtual class from SoStereoViewer
 
  /*fkw*/ 
  /*   virtual SoCamera * getViewerCamera();
       virtual SbBool isViewerDoubleBuffer();
       virtual void actualRendering();
       virtual void adjustClippingPlanes();
       virtual const SbVec2s& getSize();
       virtual const SbVec2s& getTopLeft() ;
       virtual const SbVec2s& getBottomRight() ;
       void setStereoViewType(SoBaseStereo * stereo);
       SoBaseStereo * getStereoViewType();
       void reverseStereoView(SbBool reverse);
       SbBool isStereoViewReversed();
       virtual void setStereoBalance(float balance);
       virtual float getStereoBalance();
       virtual void setStereoActive(SbBool activate) ;
       virtual SbBool isStereoActive() ;
       // virtual void setStereoOffset(float offset);
       // virtual float getStereoOffset();
       //  void setViewport(short left, short bottom, short width, short height) ;
       //  void getViewport(short &left, short &bottom, short &width, short &height) ;
  */
 public:
  /**
   * Sets the auto clipping tolerance value. Auto clipping normally sets the near
   * and far clip planes based on the scene's bounding box. If the camera is inside
   * the scene bounding box, the near plane is moved in front of the camera using
   * @B tolerance @b*bbox size. The default is 0.001. 
   */
  void setAutoClipTolerance ( float tolerance ) {
    minimumNearPlane = tolerance; };

  /**
   * Gets the auto clipping tolerance value. 
   */
  float getAutoClipTolerance () const
    { return minimumNearPlane; };
    
  SoNode * getViewAllScene() { return viewAllScene;}
  void setViewAllScene(SoNode* node)
  {
    viewAllScene = node;
  }

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
  
 protected:

  SbBool              m_preserveHeightAngle;
  float               m_previousHeightAngle; 
  SbBool              m_seekWithOrtho;

  // Constructor/Destructor
  SoXtMPViewer(SoWidget parent,
               const char *name, 
               SbBool buildInsideParent, 
               Type type, 
               SbBool buildNow);
  
  // global vars
  SoXtMPViewer::Type type;
  SoCamera *camera; // camera being edited
  SbBool viewingFlag; // FALSE when the viewer is off
  SbBool altSwitchBack; // flag to return to PICK after an Alt release
  SbBool cursorEnabledFlag;
  static SoSFTime *viewerRealTime; // pointer to "realTime" global field
  float sceneSize; // the larger of the X,Y,Z scene BBox
  float viewerSpeed; // default to 1.0 - SoXtMPFullViewer add UI to inc/dec
  
  // local tree variables
  SoSeparator *sceneRoot; // root node given to the RA
  SoNode *sceneGraph; // user supplied scene graph
  
  // Subclasses can call this routine to handle a common set of events. A Boolean
  // is returned to specify whether the event was handled by the base class.
  // Currently handled events and functions are :
  // 'Esc' key - toggles viewing on/off
  // When viewing OFF - send all events down the scene graph
  // When camera == NULL - Discard all viewing events
  // 'home' Key - calls resetToHomePosition()
  // 's' Key - toggles seek on/off
  // Arrow Keys - moves the camera up/down/right/left in the viewing plane
  SbBool processCommonEvents(XAnyEvent *xe);
  
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
  //
  void interactiveCountInc();
  void interactiveCountDec();
  int getInteractiveCount() { return interactiveCount; }
  
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
  SbBool seekToPoint(const SbVec2s &mouseLocation);
  
  //
  // Subclasses CAN redefine this to interpolate camera position/orientation
  // while the seek animation is going on (called by animation sensor).
  // The parameter t is a [0,1] value corresponding to the animation percentage
  // completion. (i.e. a value of 0.25 means that animation is only 1/4 of the way
  // through).
  //
  virtual void interpolateSeekAnimation(float t);
  virtual void computeSeekFinalOrientation();
  
  // variables used for interpolating seek animations
  float seekDistance;
  SbBool seekDistAsPercentage; // percentage/absolute flag
  SbBool computeSeekVariables;
  SbVec3f seekPoint, seekNormal;
  SbRotation oldCamOrientation, newCamOrientation;
  SbVec3f oldCamPosition, newCamPosition;
  
  // Externally set the viewer into/out off seek mode (default OFF). Actual
  // seeking will not happen until the viewer decides to (ex: mouse click).
  //
  // Note: setting the viewer out of seek mode while the camera is being
  // animated will stop the animation to the current location.
  virtual void setSeekMode(SbBool onOrOff);
  SbBool isSeekMode() { return seekModeFlag; }
  
  // redefine this routine to adjust the camera clipping planes just
  // before doing a redraw. The sensor will be unschedule after the camera
  // is changed in the base class to prevent a second redraw from occuring.
  virtual void prepareRedraw();
  virtual void actualRedraw();
  virtual void endRedraw(); 
  
  // This is called during a paste.
  // Subclasses may wish to redefine this in a way that
  // keeps their viewing paradigm intact.
  virtual void changeCameraValues(SoCamera *newCamera);
  
  //
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
  static void setFeedbackOrthoProjection(const SbVec2s &glxSize);
  // restores the zbuffer and lighting state that was changed when
  // setFeedbackOrthoProjection() was last called.
  static void restoreGLStateAfterFeedback();
  // draws a simple 2 colored cross at given position
  static void drawViewerCrossFeedback(SbVec2s loc);
  // draws the anchor feedback given center of rotation and mouse location
  static void drawViewerRollFeedback(SbVec2s center, SbVec2s loc);
  
  // redefine this for a better default draw style (need to wait for context)
  virtual void afterRealizeHook();
  
  // auto clipping vars and routines
  SbBool autoClipFlag;
  float minimumNearPlane; // minimum near plane as percentage of far
  SoGetBoundingBoxAction *autoClipBboxAction;
  virtual void adjustCameraClippingPlanes();
  
  // Override redraw() in order to calculate render time including
  // frame buffer switch
  virtual void redraw();
  
  // Subclasses may override this function to change way that 
  // viewer tries to calculate decimation percentage for 
  // DecimationStrategy FRAMES_PER_SECOND.
  // Given goal frames per second, timeTaken in last render, 
  // and last decimation value used, this function should return
  // decimation percentage value to use in next render.
  virtual float decimationForFramesPerSecond(float fps, 
                                             double timeTaken, 
                                             float decimation);
  // Subclasses may override this function to change way that 
  // viewer tries to calculate decimation percentage for 
  // DecimationStrategy FIXED_NUM_TRIANGLES.
  // Given goal number of triangles to reach, this function 
  // should return decimation percentage value to use.
  virtual float decimationForNumTriangles(uint32_t numTris);
  
 private:
  // current state vars
  SoType cameraType;
  BufferType bufferType;
  SbBool interactiveFlag; // TRUE while doing interactive work
  SoXtInputFocus *inputFocus;
  
  
  
  // node to apply the viewAll method to
  // in some cases, we need to apply the viewAll method on 
  // a part of the sceneGraph
  SoNode * viewAllScene;
  
  // draw style vars
  DrawStyle stillDrawStyle, interactiveDrawStyle;
  SbBool checkForDrawStyle;
  SoSwitch *drawStyleSwitch; // on/off draw styles
  SoDrawStyle *drawStyleNode; // LINE vs POINT
  SoLightModel *lightModelNode; // BASE_COLOR vs PHONG
  SoPackedColor *colorNode; // hidden line first pass
  SoMaterialBinding *matBindingNode; // hidden line first pass
  SoComplexity *complexityNode; // low complexity & texture off
  void setCurrentDrawStyle(SoXtMPViewer::DrawStyle style);
  void doRendering();
   
  // copy and paste support
  SoXtClipboard *clipboard;
  static void pasteDoneCB(void *userData, SoPathList *pathList);
   
  // camera original values, used to restore the camera
  SbBool createdCamera;
  SbVec3f origPosition;
  SbRotation origOrientation;
  float origNearDistance;
  float origFarDistance;
  float origFocalDistance;
  float origHeight;
   
  // seek animation vars
  SbBool seekModeFlag; // TRUE when seek turned on externally
  SoFieldSensor *seekAnimationSensor;
  SbBool detailSeekFlag;
  float seekAnimTime;
  SbTime seekStartTime;
  static void seekAnimationSensorCB(void *p, SoSensor *);
   
  // headlight variables
  SoDirectionalLight *headlightNode;
  SoGroup *headlightGroup;
  SoRotation *headlightRot;
  SbBool headlightFlag; // true when headlight in turned on
   
  // interactive viewing callbacks
  int interactiveCount;
  SoCallbackList *startCBList;
  SoCallbackList *finishCBList;
  static void drawStyleStartCallback(void *, SoXtMPViewer *v);
  static void drawStyleFinishCallback(void *, SoXtMPViewer *v);
  static void bufferStartCallback(void *, SoXtMPViewer *v);
  static void bufferFinishCallback(void *, SoXtMPViewer *v);
   
  // set the zbuffer on current window to correct state
  void setZbufferState();
  SbBool isZbufferOff();
  void arrowKeyPressed(KeySym key);
   
  // Decimation strategy additions:
  DecimationStrategy decStrategy;
  int32_t goalTris; // Goal Number of Triangles
  float goalFps; // Goal Frames Per Second
  float decPercentage; // Fixed percentage
  float lastDecimationValue; // Last decimation value and render time 
  int lastDirection;
  double lastRenderTime; // used when (strategy==FRAMES_PER_SECOND)
  SoGetPrimitiveCountAction *primCountAction;
  static SoGLRenderAction::AbortCode renderAbortCB(void *data); 
  SbBool isStill, doFullRendering;
  SoAlarmSensor *stillSensor;
  static void alarmCB(void* thisp, SoSensor*) { ((SoXtMPViewer*)thisp)->stillSensorCalled(); };
  void stillSensorCalled(); 
  SoNodeSensor *motionSensor;
  static void changeCB(void* thisp, SoSensor*) { ((SoXtMPViewer*)thisp)->changeSensorCalled(); };
  void changeSensorCalled();

  // Camera type change callback
  SoXtMPViewerCameraTypeChangeCB *viewerCameraTypeChangeCallback;
  void *viewerCameraTypeChangeCallbackUserData;
  
  // Frames per second calculating:
  int numSamples, curNumSamples;
  double curTotalTime;
  SoXtMPViewerFPSCB *fpsUserCallback;
  void *fpsUserData;
  SbElapsedTime fpsTimer;
   
  // Decimation Percentage callback
  SoXtMPViewerDecimationPercentageCB *decimationUserCallback;
  void *decimationUserData;

  // SoTransform Node that will modify the scene
  // this node is inserted just after the camera 
  // that the viewer is using.
  SoTransform * sceneTransform;
  // TRUE if we are in MP immersive mode
  SbBool addSceneTransform;

  // Wand 
  SoSeparator * wandGroup;
  SoTransform * wandTransform;
  SoSeparator * wandGeometry;
  static const char * defaultWandGeometry;
  SbString wandFileStr;
  SbBool addWandGroup;
  void createWandGroup(void);
  void insertWandGroup(void);
  
  void scaleScene(SoNode * scene);

 protected:
  void * getViewer() {return (void*) this;}


};

#endif /* _SO_XT_MP_VIEWER_ */

#endif // _WIN32


