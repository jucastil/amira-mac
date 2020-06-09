/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/



#ifndef  _SO_WIN_MP_VIEWER_
#define  _SO_WIN_MP_VIEWER_

#if defined(_WIN32)
#  include <Inventor/Win/SoWinBeginStrict.h>
#endif
#include <Inventor/SoType.h>
#include <Inventor/MP/Win/SoWinMPRenderArea.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/SbTime.h>

//#include <Inventor/components/stereo/SoStereoViewer.h>

// classes
class SoFieldSensor;
class SoNode;
class SoDirectionalLight;
class SoGroup;
class SoRotation;
class SoCamera;
class SoDrawStyle;
class SoLightModel;
class SoTimerSensor;
class SoWinClipboard;
class SoWinMPViewer;
class SoGetBoundingBoxAction;
class SbPList;
class SoSeparator;
class SoSwitch;
class SoComplexity;
class SoPackedColor;
class SoMaterialBinding;
class SoBaseColor;
class SoSFTime;
class SoAlarmSensor;
class SoNodeSensor;
class SoGetPrimitiveCountAction;

//class SoStereoViewer;
//class SoBaseStereo;
class SoTransform;


// callback function prototypes
typedef void SoWinMPViewerCB(void *userData, SoWinMPViewer *viewer);
typedef void SoWinMPViewerCameraTypeChangeCB(void *userData, SoCamera *camera, SoWinMPViewer *viewer);

// Large Model Viewing notification callbacks for
// frames per second and decimation percentage:
typedef void SoWinMPViewerFPSCB(float fps, void *userData, SoWinMPViewer *viewer);
typedef void SoWinMPViewerDecimationPercentageCB(float percentage,
                                                 void *userData, SoWinMPViewer *viewer);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWinMPViewer
//
//      The Viewer component is the abstract base class for all viewers.
//  It is subclassed from renderArea, adding viewing semantics to Inventor
//  rendering.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @SCVEXT Multi-Pipe viewer component lowest base class.
 * 
 * @ingroup ScaleVizMultiPipe
 * 
 * @DESCRIPTION
 *   This is the Multi-Pipe version of SoWinViewer.
 *   
 *   The typedefs, enums, and public methods of SoWinMPViewer are exactly the same as
 *   for SoWinViewer (except for the name changes). 
 * 
 * 
 */ 

//class SoWinMPViewer : public SoWinMPRenderArea, public SoStereoViewer {
class INVENTORW_API SoWinMPViewer : public SoWinMPRenderArea {

 public:
  
  //

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
    EDITOR,
  };
  
  /**
   * list of possible drawing styles
   * Note: Refer to the SoWinMPViewer man pages for a complete 
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
    VIEW_SAME_AS_STILL,
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
    INTERACTIVE,
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
    BUFFER_INTERACTIVE,
  };
  
    /**  list of decimation strategies */
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
    * Classic cursors are all white and tend to disappear over white
    * geometry or white background.  New styles avoid that problem
    * (but have quirks of their own of course :-).  Added for v2.6 
    */
  enum CursorStyle {
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
  
  
  //
  // Sets/gets the scene graph to render. Whenever a new scene is supplied
  // the first camera encountered will be by default used as the edited
  // camera, else a new camera will be created.
  //
  virtual void    setSceneGraph(SoNode *newScene);
  virtual SoNode *getSceneGraph();
  
#ifndef HIDDEN_FROM_DOC
  void saveSceneGraph(const char *fileName) ;
#endif //HIDDEN_FROM_DOC
  
  /**
   * Sets the edited camera. Setting the camera is only needed if the first
   * camera found in the scene when setting the scene graph isn't the one the user
   * really wants to edit.
   */
  virtual void    setCamera(SoCamera *cam);
  /**
   * Gets the edited camera. 
   */
  SoCamera        *getCamera()            { return camera; }
  
  /**
   * Sets the camera type that will be created by the viewer if no cameras are
   * found in the scene graph (see SoPerspectiveCamera and SoOrthographicCamera). By
   * default an SoPerspectiveCamera will be created if no cameras are found.
   * 
   * Note: The set method will only take effect the next time a scene graph is
   * specified (and if no cameras are found).
   */
  virtual void    setCameraType(SoType type);
  /**
   * Gets the camera type that will be created by the viewer if no cameras are
   * found in the scene graph (see SoPerspectiveCamera and SoOrthographicCamera). 
   */
  SoType          getCameraType()         { return cameraType; }
     
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
  virtual void    viewAll();
  /**
   * Saves the camera values.
   */
  virtual void    saveHomePosition();
  /**
   * Restores the camera values.
   */
  virtual void    resetToHomePosition();
  
  /**
   * Defines a callback which is called each time the camera type has changed (change
   * from SoPerspectiveCamera to SoOrthographicCamera or vice versa).
   */
  void setCameraTypeChangeCallback(SoWinMPViewerCameraTypeChangeCB *callback,
                                   void *userdata);
  
  /**
   * Turns the headlight on/off (default on).
   */
  void            setHeadlight(SbBool onOrOff);
  /**
   * Queries if the headlight is on.
   */
  SbBool          isHeadlight()           { return headlightFlag; }
  /**
   * Returns the headlight node.
   */
  SoDirectionalLight *getHeadlight()      { return headlightNode; }
  
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
  void setDrawStyle(SoWinMPViewer::DrawType type, 
                    SoWinMPViewer::DrawStyle style);
  /**
   * Queries the current drawing style in the main view. 
   */
  SoWinMPViewer::DrawStyle getDrawStyle(SoWinMPViewer::DrawType type);
  
  /**
   * Sets the current buffering type in the main view (default
   * SoWinViewer::BUFFER_DOUBLE).
   */
  void setBufferingType(SoWinMPViewer::BufferType type);
  /**
   * Gets the current buffering type in the main view.
   */
  SoWinMPViewer::BufferType getBufferingType()       { return bufferType; }
  
  // redefine this to call the viewer setBufferingType() method instead.
  virtual void    setDoubleBuffer(SbBool onOrOff);
  /**
   * Sets whether the viewer is turned on or off. When turned on, messages are
   * consumed by the viewer. When viewing is off, messages are processed by the
   * viewer's render area. This means messages will be sent down to the scene graph
   * for processing (i.e. picking can occur). Note that if the application has
   * registered a message callback, it will be invoked on every message, whether
   * viewing is turned on or not. However, the return value of this callback (which
   * specifies whether the callback handled the message or not) is ignored when
   * viewing is on. That is, the viewer will process the message even if the callback
   * already did. This is to ensure that the viewing paradigm is not broken (default
   * viewing is on).
   */
  virtual void    setViewing(SbBool onOrOff);
  /**
   * Queries whether the viewer is turned on or off. See setViewing() for details.
   */
  SbBool          isViewing() const       { return viewingFlag; };
  
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
  virtual void  setCursorEnabled(SbBool onOrOff);
  /**
   * Queries whether the viewer is allowed to change the cursor over the renderArea
   * window. 
   */
  SbBool            isCursorEnabled() const   { return cursorEnabledFlag; }
  
  /**
   * Sets the auto clipping plane. When auto clipping is ON, the camera near and
   * far planes are dynamically adjusted to be as tight as possible around the
   * objects being viewed. 
   */
  void            setAutoClipping(SbBool onOrOff);
  /**
   * Queries if auto clipping is ON.
   */
  SbBool          isAutoClipping() const          { return autoClipFlag; }
  
  /**
   * Turns stereo viewing on/off on the viewer (default off). 
   * 
   * To insure backward compatibility with older Open Inventor versions, and
   * specifically with the old stereo model, this method still applies to stereo.
   * Like the current stereo model, the old model makes use of an offset to represent
   * the eye separation. However, instead of adapting the view volume, the cameras
   * were rotated toward the default point of focus, creating the stereo viewing
   * angle.
   * 
   * If no type of stereo (from the current stereo model) is set on the viewer and
   * setStereoViewing() is called, then the old stereo model is in effect. Note
   * that setStereoViewing is the method that actually sets OpenGL in stereo mode. If
   * the old stereo model is in effect, then the offset passed to
   * setStereoOffset() is no longer a factor but the actual value used to
   * separate the cameras. In that case, the default value for the offset is 3.
   * 
   * When in stereo mode, which may not work on all machines, the scene is rendered
   * twice (in the left and right buffers) with an offset between the two views to
   * simulate stereo viewing. Stereo glasses may be needed to see the effect. Old
   * style stereo viewing is only possible with a graphics board that has support for
   * stereo.
   * 
   * See SoStereoViewer for information on the current stereo model.
   */
  //  virtual void    setStereoViewing(SbBool onOrOff);
  /**
   * Queries if stereo viewing is on or off on the viewer. See setStereoViewing()
   * for additional info.
   */
  //  virtual SbBool  isStereoViewing();
  /**
   * Sets the stereo offset. See setStereoViewing() for additional info.
   */
  //  void            setStereoOffset(float dist) { stereoOffset = dist; scheduleRedraw() ;}
  /**
   * Returns the stereo offset. See setStereoViewing() for additional info.
   */
  //  float           getStereoOffset()   { return stereoOffset; }
  
  /**
   * When the viewer is in seek mode, left mouse clicks initiate a pick, and the
   * viewer changes its orientation and position to look at the picked object. This
   * routine tells the seeking viewer whether to orient the camera towards the picked
   * point (detail on), or the center of the object's bounding box (detail off).
   * Default is detail on.
   */
  void            setDetailSeek(SbBool onOrOff)   { detailSeekFlag = onOrOff; };
  /**
   * Queries whether detail seek is on.
   */
  SbBool          isDetailSeek()                  { return detailSeekFlag; }
  
  /**
   * Sets the time a seek takes to change to the new camera location. A value of zero
   * seeks directly to the point without any animation. Default value is 2 seconds.
   * 
   * For historical reasons, setting the seek time to zero causes the viewer to stay
   * in seek mode. If you want the camera to move immediately to its new position and
   * still have the viewer leave seek mode after moving the camera, set the seek time
   * to a very small non-zero value.
   */
  void            setSeekTime(float seconds)      { seekAnimTime = seconds; }
  /**
   * Queries the seek time.
   */
  float           getSeekTime()                   { return seekAnimTime; }

#ifdef OIV_NET_DOC
  /**
  * Adds start callback routine on the viewer. Start callbacks are
  * called whenever the user starts doing interactive viewing (for example, mouse
  * down), and finish callbacks are called when user is done doing interactive work
  * (for example, mouse up).
  * 
  * Note: The viewer "this" reference is passed as callback data.
  */

#else
  /**
  * Adds start callback routine on the viewer. Start callbacks are
  * called whenever the user starts doing interactive viewing (for example, mouse
  * down), and finish callbacks are called when user is done doing interactive work
  * (for example, mouse up).
  * 
  * Note: The viewer "this" pointer is passed as callback data.
  */

#endif //OIV_NET_DOC
  void    addStartCallback(SoWinMPViewerCB *f, void *userData = NULL)
    { startCBList->addCallback((SoCallbackListCB *)f, userData); }
#ifdef OIV_NET_DOC
  /**
  * Adds finish callback routine on the viewer. Start callbacks are
  * called whenever the user starts doing interactive viewing (for example, mouse
  * down), and finish callbacks are called when user is done doing interactive work
  * (for example, mouse up).
  * 
  * Note: The viewer "this" reference is passed as callback data.
  */

#else
  /**
  * Adds finish callback routine on the viewer. Start callbacks are
  * called whenever the user starts doing interactive viewing (for example, mouse
  * down), and finish callbacks are called when user is done doing interactive work
  * (for example, mouse up).
  * 
  * Note: The viewer "this" pointer is passed as callback data.
  */

#endif //OIV_NET_DOC
  void    addFinishCallback(SoWinMPViewerCB *f, void *userData = NULL)
    { finishCBList->addCallback((SoCallbackListCB *)f, userData); }
#ifdef OIV_NET_DOC
  /**
  * Removes start callback routine from the viewer.
  * 
  * Note: The viewer "this" reference is passed as callback data.
  */

#else
  /**
  * Removes start callback routine from the viewer.
  * 
  * Note: The viewer "this" pointer is passed as callback data.
  */

#endif //OIV_NET_DOC
  void    removeStartCallback(SoWinMPViewerCB *f, void *userData = NULL)
    { startCBList->removeCallback((SoCallbackListCB *)f, userData); }
#ifdef OIV_NET_DOC
  /**
  * Removes finish callback routine from the viewer.
  * 
  * Note: The viewer "this" reference is passed as callback data.
  */

#else
  /**
  * Removes finish callback routine from the viewer.
  * 
  * Note: The viewer "this" pointer is passed as callback data.
  */

#endif //OIV_NET_DOC
  void    removeFinishCallback(SoWinMPViewerCB *f, void *userData = NULL)
    { finishCBList->removeCallback((SoCallbackListCB *)f, userData); }
  
  /**
   * Copies the view. @B eventTime @b should be the time of the Windows message
   * which initiated the copy (e.g. if copy is initiated from a
   * keystroke, @B eventTime @b should be the time in the key down message.)
   */
  void                copyView(Time eventTime);
  /**
   * Pastes the view. @B eventTime @b should be the time of the Windows message
   * which initiated the paste (e.g. if paste is initiated from a
   * keystroke, @B eventTime @b should be the time in the key down message.)
   */
  void                pasteView(Time eventTime);
  
  // redefine this routine to also correctly set the buffering type
  // on the viewer.
  virtual void    setNormalVisual(XVisualInfo *);
  
  /**
   * This can be used to let the viewer know that the scene graph has changed so that
   * the viewer can recompute things like speed which depend on the scene graph size.
   * Note: This routine is automatically called whenever setSceneGraph() is
   * called.
   */
  virtual void  recomputeSceneSize();
  
  
  // --- Large Model Viewing additions:
  
  /**
   * Sets strategy to use to decide on decimation value.
   */
  void setDecimationStrategy(DecimationStrategy strategy);
  /**
   * Gets strategy to use to decide on decimation value.
   */
  DecimationStrategy getDecimationStrategy() { return decStrategy; };
  
  /**
   * Sets goal number of triangles for the viewer to try to render.
   */
  void    setGoalNumberOfTriangles(int32_t goal);
  /**
   * Gets goal number of triangles for the viewer to try to render.
   */
  int32_t getGoalNumberOfTriangles()  { return goalTris; };
  
  /**
   * Sets goal frames per second for the viewer to try to render.
   */
  void    setGoalFramesPerSecond(float goal);
  /**
   * Gets goal frames per second for the viewer to try to render.
   */
  float getGoalFramesPerSecond()  { return goalFps; };
  
  /**
   * Sets fixed percentage for the viewer to render (0.0 to 1.0)
   */
  void  setFixedPercentage(float percent);
  /**
   * Gets fixed percentage for the viewer to render (0.0 to 1.0)
   */
  float getFixedPercentage()  { return decPercentage; };
  
  /**
   * If this flag is set, the viewer will render at full resolution when it sits
   * still for a certain period of time.
   */
  void   enableFullRenderingWhenStill(SbBool onOff);
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
  void setFramesPerSecondCallback(SoWinMPViewerFPSCB *callback,
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
  int  getNumSamples() { return numSamples; };
  
  /**
   * Registers decimation percentage callback.
   */
  void setDecimationPercentageCallback(SoWinMPViewerDecimationPercentageCB *callback,
                                       void *userData = NULL);
  
  /**
   * Returns the Decimation Percentage the viewer used in its last render.
   */
  float getCurrentDecimationPercentage();
  
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



 public:
  HDC getCurrentDC();
  HDC getCurrentDC( int id );
  
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
  virtual void setCursorStyle( SoWinMPViewer::CursorStyle style );
  /**
   * Returns the cursor style.
   */
  SoWinMPViewer::CursorStyle getCursorStyle() { return cursorStyle; };
  
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

 SoINTERNAL public:
  virtual ~SoWinMPViewer();
    
  // tell whether create the wand or not. Default is TRUE 
  void useWand(SbBool flag)
    { addWandGroup = flag;};
  
 protected:
  // Constructor/Destructor
  SoWinMPViewer(SoWidget parent,
                const char *name, 
                SbBool buildInsideParent, 
                Type type,   // Removed class qualifier from enum --mmh 1/12/95
                SbBool buildNow);
  
  // global vars
  SoWinMPViewer::Type   type;
  SoCamera            *camera;        // camera being edited
  SbBool              viewingFlag;    // FALSE when the viewer is off
  SbBool              m_preserveHeightAngle;
  float               m_previousHeightAngle; 
 
  // global vars new in v2.1
  SbBool                altSwitchBack;  // flag to return to PICK after an Alt release
  SbBool                cursorEnabledFlag;
  static SoSFTime       *viewerRealTime;  // pointer to "realTime" global field
  float         sceneSize;   // the larger of the X,Y,Z scene BBox
  float         viewerSpeed; // default to 1.0 - SoXtFullViewer add UI to inc/dec
  
  // For release 2.6 we added the concept of cursor "style", at least
  // on Windows, and moved the definition variables and methods up to
  // this class (protected not private!) so subclasses can override
  // the cursor definitions if they need/want to.
  //
  // We now have "classic", XOR and "shadow" style cursors (new in v2.6)
  SoWinMPViewer::CursorStyle cursorStyle;
  
  // Previously declared in subclasses (before v2.6)
  // Note that each subclass viewer uses a subset of these standard
  // cursor names.  Note that the Fly and Walk viewers used slightly
  // different names (that were too generic) for their specific cursors
  // (the last two in the list) prior to v2.6.
  SbBool createdCursors;
  HCURSOR normalCursor,   // std arrow
    dollyCursor, panCursor, rollCursor, seekCursor,
    spinCursor, upCursor, flyCursor, walkCursor;
  
  // Load cursor definitions from resource file.
  // previously declared in subclasses (before v2.6).
  // Subclasses may override, but are not required to do so
  // unless they need more or different cursor definitions.
  virtual void defineCursors();
  
  // Subclasses should (and do) override this method! (new in v2.6)
  // (The setCursorStyle method calls this to force a dynamic change)
  virtual void updateCursor() {};
  
#ifdef __sgi
  // set to TRUE when we are using the SGI specific stereo extensions
  // which enables us to emulate OpenGL stereo on most machines.
  SbBool              useSGIStereoExt;
#endif
  
  // local tree variables
  SoSeparator         *sceneRoot;     // root node given to the RA
  SoNode              *sceneGraph;    // user supplied scene graph
  
  // Subclasses can call this routine to handle a common set of events. A Boolean
  // is returned to specify whether the event was handled by the base class.
  // Currently handled events and functions are :
  //      'Esc' key - toggles viewing on/off
  //      When viewing OFF - send all events down the scene graph
  //      When camera == NULL - Discard all viewing events
  //      'home' Key - calls resetToHomePosition()
  //      's' Key - toggles seek on/off
  //      Arrow Keys - moves the camera up/down/right/left in the viewing plane
  SbBool          processCommonEvents(XAnyEvent *xe);
  
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
  void            interactiveCountInc();
  void            interactiveCountDec();
  int             getInteractiveCount()       { return interactiveCount; }
  
  //
  // This routine is used by subclasses to initiate the seek animation. Given a
  // screen mouse location, this routine will return the picked point
  // and the normal at that point. It will also schedule the sensor to animate
  // if necessary. The routine retuns TRUE if something got picked...
  //
  // Note: if detailSeek is on, the point and normal correspond to the exact 
  //      3D location under the cursor.
  //      if detailSeek if off, the object bbox center and the camera 
  //      orientation are instead returned.
  SbBool          seekToPoint(const SbVec2s &mouseLocation);
  
  //
  // Subclasses CAN redefine this to interpolate camera position/orientation
  // while the seek animation is going on (called by animation sensor).
  // The parameter t is a [0,1] value corresponding to the animation percentage
  // completion. (i.e. a value of 0.25 means that animation is only 1/4 of the way
  // through).
  //
  virtual void    interpolateSeekAnimation(float t);
  virtual void    computeSeekFinalOrientation();
  
  // variables used for interpolating seek animations
  float           seekDistance;
  SbBool          seekDistAsPercentage; // percentage/absolute flag
  SbBool          computeSeekVariables;
  SbVec3f         seekPoint, seekNormal;
  SbRotation      oldCamOrientation, newCamOrientation;
  SbVec3f         oldCamPosition, newCamPosition;
  
  // Externally set the viewer into/out off seek mode (default OFF). Actual
  // seeking will not happen until the viewer decides to (ex: mouse click).
  //
  // Note: setting the viewer out of seek mode while the camera is being
  // animated will stop the animation to the current location.
  virtual void    setSeekMode(SbBool onOrOff);
  SbBool          isSeekMode()                    { return seekModeFlag; }
  
  // redefine this routine to adjust the camera clipping planes just
  // before doing a redraw. The sensor will be unschedule after the camera
  // is changed in the base class to prevent a second redraw from occuring.
  virtual void    prepareRedraw();
  virtual void    actualRedraw();
  virtual void    endRedraw();
  
  // This is called during a paste.
  // Subclasses may wish to redefine this in a way that
  // keeps their viewing paradigm intact.
  virtual void    changeCameraValues(SoCamera *newCamera);
  
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
  static void   setFeedbackOrthoProjection(const SbVec2s &glxSize);
  // restores the zbuffer and lighting state that was changed when
  // setFeedbackOrthoProjection() was last called.
  static void   restoreGLStateAfterFeedback();
  // draws a simple 2 colored cross at given position
  static void     drawViewerCrossFeedback(SbVec2s loc);
  // draws the anchor feedback given center of rotation and mouse location
  static void     drawViewerRollFeedback(SbVec2s center, SbVec2s loc);
  
  //
  // set the right zbuffer state (based on the current draw style) whenever
  // the window changes.
  //
  // HACK: redefines this routine from SoWinMPRenderArea to also check to make
  // sure that SoWinMPViewer::setBufferingType() is updated if users call 
  // SoWinGLWidget::setDoubleBuffer() instead.
  //
  virtual void        widgetChanged(SoWidget);
  
  // redefine this for a better default draw style (need to wait for context)
  virtual void  afterRealizeHook();
  
  // auto clipping vars and routines
  SbBool                autoClipFlag;
  float         minimumNearPlane;   // minimum near plane as percentage of far
  SoGetBoundingBoxAction *autoClipBboxAction;
  virtual void  adjustCameraClippingPlanes();
  
  
  // Override redraw() in order to calculate render time including
  // frame buffer switch
  virtual void redraw();
  
  // Subclasses may override this function to change way that
  // viewer tries to calculate decimation percentage for
  // DecimationStrategy FRAMES_PER_SECOND.
  // Given goal frames per second, timeTaken in last render,
  // and last decimation value used, this function should return
  // decimation percentage value to use in next render.
  virtual float   decimationForFramesPerSecond(float fps,
                                               double timeTaken, float decimation);
  // Subclasses may override this function to change way that
  // viewer tries to calculate decimation percentage for
  // DecimationStrategy FIXED_NUM_TRIANGLES.
  // Given goal number of triangles to reach, this function
  // should return decimation percentage value to use.
  virtual float   decimationForNumTriangles(uint32_t numTris);

  SbBool              m_seekWithOrtho;

  //  SoBaseStereo * stereoViewType ;

 private:
  // current state vars
  SoType              cameraType;
  BufferType          bufferType;
  SbBool              interactiveFlag; // TRUE while doing interactive work
   
  // draw style vars
  DrawStyle           stillDrawStyle, interactiveDrawStyle;
  SbBool              checkForDrawStyle;
  SoSwitch            *drawStyleSwitch;   // on/off draw styles
  SoDrawStyle         *drawStyleNode;     // LINE vs POINT
  SoLightModel        *lightModelNode;    // BASE_COLOR vs PHONG
  SoPackedColor       *colorNode;
  // hidden line first pass
  SoMaterialBinding    *matBindingNode;
  // hidden line first pass
  SoComplexity        *complexityNode;    // low complexity & texture off
  void                setCurrentDrawStyle(SoWinMPViewer::DrawStyle style);
  void                doRendering();
   
  // copy and paste support
  SoWinClipboard       *clipboard;
  static void         pasteDoneCB(void *userData, SoPathList *pathList);
   
  // camera original values, used to restore the camera
  SbBool              createdCamera;
  SbVec3f             origPosition;
  SbRotation          origOrientation;
  float               origNearDistance;
  float               origFarDistance;
  float               origFocalDistance;
  float               origHeight;
   
  // seek animation vars
  SbBool              seekModeFlag; // TRUE when seek turned on externally
  SoFieldSensor      *seekAnimationSensor;
  SbBool              detailSeekFlag;
  float               seekAnimTime;
  SbTime              seekStartTime;
  static void         seekAnimationSensorCB(void *p, SoSensor *);
   
  // headlight variables
  SoFieldSensor       *headlightSensor;   // attached to camera
  SoDirectionalLight  *headlightNode;
  SoGroup             *headlightGroup;
  SoRotation          *headlightRot;
  SbBool              headlightFlag;  // true when headlight in turned on
  static void         headlightSensorCB(void *, SoSensor *);
   
  // interactive viewing callbacks
  int                 interactiveCount;
  SoCallbackList      *startCBList;
  SoCallbackList      *finishCBList;
  static void         drawStyleStartCallback(void *, SoWinMPViewer *v);
  static void         drawStyleFinishCallback(void *, SoWinMPViewer *v);
  static void         bufferStartCallback(void *, SoWinMPViewer *v);
  static void         bufferFinishCallback(void *, SoWinMPViewer *v);
   
  // Attach/detach headlightSensor.
  static void visibilityChangeCB(void *pt, SbBool visible);
   
  // set the zbuffer on current window to correct state
  void                setZbufferState();
  SbBool              isZbufferOff();
  void                arrowKeyPressed(KeySym key);
   
  // Decimation strategy additions:
  DecimationStrategy decStrategy;
  int32_t goalTris;       // Goal Number of Triangles
  float   goalFps;        // Goal Frames Per Second
  float   decPercentage;  // Fixed percentage
  float   lastDecimationValue;  // Last decimation value and render time
  double   lastRenderTime;      // used when (strategy==FRAMES_PER_SECOND)
  int lastDirection; // changed decimation up or down last time?
  SoGetPrimitiveCountAction *primCountAction, *userCountAction;
  SbBool isStill, doFullRendering;
  SoAlarmSensor *stillSensor;
  static void alarmCB(void* thisp, SoSensor*)
    { ((SoWinMPViewer*)thisp)->stillSensorCalled(); };
  void stillSensorCalled();
  SoNodeSensor *motionSensor;
  static void changeCB(void* thisp, SoSensor*)
    { ((SoWinMPViewer*)thisp)->changeSensorCalled(); };
  void changeSensorCalled();
   
  // Camera type change callback
  SoWinMPViewerCameraTypeChangeCB *viewerCameraTypeChangeCallback;
  void *viewerCameraTypeChangeCallbackUserData;
   
  // Frames per second calculating:
  int numSamples, curNumSamples;
  double curTotalTime;
  SoWinMPViewerFPSCB  *fpsUserCallback;
  void             *fpsUserData;
   
  // Decimation Percentage callback
  SoWinMPViewerDecimationPercentageCB  *decimationUserCallback;
  void         *decimationUserData;
   
  // flag indicating whether a render traversal is in
  // progress.
  SbBool          isWinRedrawing;

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
};

#if defined(_WIN32)
#  include <Inventor/Win/SoWinEndStrict.h>
#endif

#endif  /* _SO_WIN_VIEWER_ */

