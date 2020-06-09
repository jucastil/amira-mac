/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Author(s) (MMM yyyy)
** Modified by : David Mott (MMM yyyy)
** Modified by : Alain Dumesny (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SO_SCENE_MANAGER_
#define _SO_SCENE_MANAGER_

#include <Inventor/SbColor.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/helpers/SbGlContextHelper.h>
#include <Inventor/threads/SbThreadSpinlock.h>

class SoNodeSensor;
class SoEvent;
class SoHandleEventAction;
class SoNode;
class SoSceneManager;
class SoSensor;
class SoSFTime;
class SoOneShotSensor;
class SoGLRenderFromPBuffer;
class SoGLContext;
class SoSceneManagerSync;

// callback function prototypes
/**
 * [OIV-WRAPPER NAME{RenderCB}]
 */
typedef void SoSceneManagerRenderCB(void *userData, SoSceneManager *mgr);

#ifndef HIDDEN_FROM_DOC

typedef SoAction* SoActionConstructorCB();


typedef bool SoMPRenderCB( SoSceneManager* mgr,SoGLContext* viewerContext );

#endif

#if defined(_WIN32)
#pragma warning( push )
#pragma warning( disable: 4251 ) // 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
#endif

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoSceneManager
//
//  Class which performs Inventor rendering and event handling
//  on a scene graph.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Manages scene graph rendering and event handling.
 *
 * @ingroup General
 *
 * @DESCRIPTION
 *   SoSceneManager provides Open Inventor rendering and event handling inside a
 *   window provided by the caller. The scene manager is able to render in only a
 *   portion of a window if desired. The SoWinRenderArea class employs an
 *   SoSceneManager, and handles most all the details for setting up a window,
 *   converting Windows messages to Open Inventor events, automatically redrawing the
 *   scene when necessary, and so on. It is simplest to use a render area when
 *   rendering in an entire window. The SoSceneManager class is available for
 *   programmers not using the SoXt / SoWin / SoQt or SoWx libraries.
 *
 * @SEE_ALSO
 *    SoWinRenderArea,
 *    SoGLRenderAction,
 *    SoHandleEventAction
 *
 *
 */

class INVENTOR_API SoSceneManager {
 public:
  /**
   * Constructor.
   */
  //new constructor : use the number of GLWidget. 1 is the default value.
  SoSceneManager(int nb = 1);
  /**
   * Destructor.
   */
  virtual ~SoSceneManager();

  /**
   * Applies an SoGLRenderAction to the scene graph managed here. The caller is
   * responsible for setting up a window to render into.
   * If @param clearWindow is @B TRUE @b, this clears the graphics window before rendering.
   * If @param clearZbuffer is @B TRUE @b, the z buffer will be cleared before rendering.
   */
  virtual void render(SbBool clearWindow = TRUE, SbBool clearZbuffer = TRUE
#ifndef HIDDEN_FROM_DOC // internal undocumented parameters.
    , int id = 0, bool force = false
#endif
    );

  /**
   * Processes the passed event by applying an SoHandleEventAction to the scene graph
   * managed here. Returns TRUE if the event was handled by a node.
   */
  virtual SbBool      processEvent(const SoEvent *event);
  /**
   * Reinitializes graphics. This should be called, for instance, when there is a new
   * window.
   */
  void                reinitialize();

  /**
   * Schedules a redraw for some time in the near future. If there is no render
   * \oivnetdoc delegate \else callback \endoivnetdoc set, or this is not active, no redraw will be scheduled.
   */
  void                scheduleRedraw();

  /**
   * Sets the scene graph which is managed here. This is the Open Inventor
   * scene which will be traversed for rendering and event processing.
   */
  virtual void        setSceneGraph(SoNode *newScene);
  /**
   * Gets the scene graph which is managed here. This is the Open Inventor
   * scene which will be traversed for rendering and event processing.
   */
  virtual SoNode *    getSceneGraph() const;

  /**
   * Sets the size of the window in which the scene manager should render.
   * This size must be set before render() and processEvent() are
   * called.
   */
  void                setWindowSize(const SbVec2s &newSize, const float &newScale = 1.0);
  /**
   * Gets the size of the window in which the scene manager should render.
   */
  const SbVec2s &     getWindowSize() const;

  /**
   * Sets the size of the viewport within the window. Default is to
   * render the entire window region.
   */
  void                setSize(const SbVec2s &newSize, const float &newScale = 1.0);
  /**
   * Gets the size of the viewport within the window.
   */
  const SbVec2s &     getSize() const;
  /**
   * Sets the origin of the viewport within the window.
   * The origin (0,0) is the lower left corner of
   * the window.
   */
  void                setOrigin(const SbVec2s &newOrigin);
  /**
   * Gets the origin of the viewport within the window.
   */
  const SbVec2s &     getOrigin() const;

  // Sets/gets current viewport region to use for rendering.
  // This can be used instead of setting the size and origin separately.
  void        setViewportRegion(const SbViewportRegion &newRegion);
  const SbViewportRegion &getViewportRegion() const;

  /**
   * Sets the window background color when in RGB mode. This is the color the
   * scene manager viewport is cleared to when render() is called with
   * its clearWindow parameter set to @B TRUE @b. Default is black (0,0,0).
   *
   * The default value can be set using the environment variable
   * OIV_BACKGROUND_COLOR. Specify three floats (R, G, B) in the range 0. to 1.,
   * separated by spaces.
   */
  void                setBackgroundColor(const SbColor &c);
  /**
   * Gets the window background color when in RGB mode.
   */
  const SbColor &     getBackgroundColor() const  { return bkgColor; }

  /**
   * Sets the window background color when in color index mode. This is the
   * color the scene manager viewport is cleared to when render() is called
   * with its clearWindow parameter set to @B TRUE @b. Default is black (index 0).
   */
  void                setBackgroundIndex(int index);
  /**
   * Gets the window background color when in color index mode.
   */
  int                 getBackgroundIndex() const  { return bkgIndex; }

  /**
   * Sets the color mode (TRUE - RGB mode, FALSE - color map mode). Default is
   * RGB mode. Only a subset of Open Inventor nodes will render correctly in color
   * map mode. Basically, when in color index mode, lighting should be turned off
   * (the @B model @b field of SoLightModel should be set to @B BASE_COLOR @b), and
   * the SoColorIndex node should be used to specify colors.
   */
  void                setRGBMode(SbBool onOrOff);
  /**
   * Gets the color mode (TRUE - RGB mode, FALSE - color map mode).
   */
  SbBool              isRGBMode() const           { return rgbMode; }

  /**
   * Activates the scene manager. The scene manager will only employ
   * sensors for automatic redraw while it is active. Typically, the scene manager
   * should be activated whenever its window is visible on the screen, and
   * deactivated when its window is closed or iconified.
   */
  virtual void        activate();
  /**
   * Deactivates the scene manager. The scene manager will only employ
   * sensors for automatic redraw while it is active. Typically, the scene manager
   * should be activated whenever its window is visible on the screen, and
   * deactivated when its window is closed or iconified.
   */
  virtual void        deactivate();

  /**
   * The render callbackprovides a mechanism for automatically redrawing the scene
   * in response to changes in the scene graph. The scene manager employs a sensor to
   * monitor scene graph changes. When the sensor is triggered, the render callback
   * registered here is invoked. The callback should set up its graphics window, then
   * call the scene manager render() method. If the callback is set to NULL
   * (the default), auto-redraw is turned off.
   */
  void                setRenderCallback(
                                        SoSceneManagerRenderCB *f,
                                        void *userData = NULL);
  /**
   * Returns @B TRUE @b if there is currently a render \oivnetdoc delegate \else callback \endoivnetdoc registered.
   */
  SbBool              isAutoRedraw() const { return (renderCB != NULL); }

  /**
   * Sets the priority of the redraw sensor. Sensors are processed based on
   * priority, with priority values of 0 processed immediately. The default priority
   * for the scene manager redraw sensor is 10000.
   */
  void                setRedrawPriority(uint32_t priority);
  /**
   * Gets the priority of the redraw sensor.
   */
  uint32_t    getRedrawPriority() const;

  /**
   * Gets the default priority of the redraw sensor.
   */
  static uint32_t getDefaultRedrawPriority() { return 10000; }

  /**
   * Enables the realTime global field update which normally happen right
   * after a redraw.
   */
  static void         enableRealTimeUpdate(SbBool flag);
  /**
   * Returns whether realTime global field updating is enabled.
   */
  static SbBool       isRealTimeUpdateEnabled();

  /**
   * Sets the antialiasing used for rendering. There are two kinds of antialiasing
   * available: smoothing and multipass antialiasing. If smoothing is set to TRUE,
   * smoothing is enabled. Smoothing uses OpenGL's line- and point-smoothing features
   * to provide cheap antialiasing of lines and points. The value of numPasses
   * controls multipass antialiasing. Each time a render action is applied, Open
   * Inventor renders the scene numPasses times from slightly different camera
   * positions, averaging the results. numPasses can be from one to 255, inclusive.
   * Setting numPasses to one disables multipass antialiasing. You can use either,
   * both, or neither of these antialiasing techniques. By default, both smoothing
   * and multipass antialiasing are disabled.
   */
  void            setAntialiasing(SbBool smoothing, int numPasses);
  /**
   * Gets the antialiasing used for rendering.
   */
  void            getAntialiasing(SbBool &smoothing, int &numPasses) const;


  /**
   * Sets the OpenGL context to be shared by the scene manager.
   * This avoids the necessity to re-generate textures and display lists if
   * they are already available in another OpenGL context
   * (another viewer context, for instance).
   */
  void setShareContext(SbGLShareContext sc, SbBool issc = TRUE) {m_shareContext = sc; m_isShareContext = issc;};

  SoEXTENDER public:
  void updateRealTimeSensor();

  /**
   * User supplied render action. Highlights fall into this category.
   * SceneManager will never delete a render action passed to this method.
   * return the renderAction 0.
   * [OIVJAVA-WRAPPER VISIBILITY{Public}]
   */
  void                setGLRenderAction(SoGLRenderAction *ra);

  /**
   * Gets the GLRenderAction used for rendering.
   * [OIVJAVA-WRAPPER VISIBILITY{Public}]
   */
  SoGLRenderAction    *getGLRenderAction() const { return renderAction[0]; }

  //Multi GLWidget case
  void            setGLRenderAction(SoGLRenderAction *ra, int i);
  SoGLRenderAction    *getGLRenderAction(int i) const { return renderAction[i]; }

  /**
   * User supplied handle event action. This should not be done in
   * the middle of event handling. Passing NULL turns event handling off.
   * SceneManager will never delete a handle event action passed to
   * this method.
   * [OIVJAVA-WRAPPER VISIBILITY{Public}]
   */
  void                setHandleEventAction(SoHandleEventAction *hea);

  /**
   * Gets the HandleEventAction used.
   * [OIVJAVA-WRAPPER VISIBILITY{Public}]
   */
  SoHandleEventAction *getHandleEventAction() const { return handleEventAction; }

  /**
   * Indicates that the scene manager is in interactive mode or not.
   * This is usually called by Inventor viewer classes, but it is also usefull
   * for custom application viewer.
   *
   * It mainly setup SoInteractionElement for all used actions (preRenderAction and renderAction).
   */
  void setInteractive(SbBool flag);



 SoINTERNAL public:
  typedef std::list<SoSceneManager*> SceneManagerList;

  void setFloatingColorBuffer(SbBool enable, int size);

  // indicate if we need to call glViewport for the given pipe id
  inline bool needToSetViewport(const int id=0) const
  { return m_perPipeData[id].m_needToSendVP; }

  inline void setNeedToSetViewport(const int id=0)
  { m_perPipeData[id].m_needToSendVP=true; }

  static void finish();
  void allowRedraw(SbBool);
  void activate2ndSensor();
  void deactivate2ndSensor();
  SbBool getRenderActionCreatedHereState(){return raCreatedHere;}

  SoSceneManagerSync* getSynchronizer();
  void setSynchronizer( SoSceneManagerSync* );

  static void setMPRenderCallback( SoMPRenderCB* f);
  int updateMPRenderAction( int count );

  inline int getNumRenderActions() const;

  /** Ask all SceneManagers containing given node to redraw. */
  static void scheduleRedraw(SoNode* node);

  /** Schedule a forced redraw, which is guaranteed to be done */
  void scheduleForcedRedraw();

  /** Returns true if a dragger is interacting */
  bool isDraggerInteracting() const;

  /** set m_draggerInteracting to true for all scene managers
   * containing node
   */
  static void setDraggerInteracting(SoNode* node);

  /**
   * TODO: Replace with the SbType create instance mechanism
   * Add an action to apply before the GLRenderAction
   */
  static void addPreActionConstructorCb(SoActionConstructorCB* actionConstructor);

  /**
   * TODO: Replace with the SbType create instance mechanism
   * Remove an action to apply before the GLRenderAction
   */
  static void removePreActionConstructorCb(SoActionConstructorCB* actionConstructor);

  /** Return list of scnemanager containing node */
  static void getSceneManagerList(SoNode* node, SceneManagerList& mgrList);

 protected:
  SbBool m_isFloatingPointRendering;
  int m_floatingPointRenderingPrecision;
  SoGLRenderFromPBuffer** m_glRenderFromPBuffer;
  SbGLShareContext m_shareContext;
  SbBool m_isShareContext;

  SoSceneManagerRenderCB* renderCB;
  static SoMPRenderCB* mpRenderCB;

  void                    *renderCBData;
  SbBool              isActive() const { return active; }

  // This tells the app it is time to redraw by invoking the renderCB.
  void                redraw();
  void                fastEditRenderSceneRules(SoSensor *sensor);
  void                updateRenderAction(SoSensor* sensor, SbBool forceRebuilding=FALSE);

 private:
  typedef std::vector<SoAction*> ActionVector;
  /** List of actions for a given render id */
  typedef std::vector<ActionVector> ActionMap;

  typedef std::set<SoActionConstructorCB*> PreActionConstructorCbSet;

  /** Apply all prerender actions for given pipe id */
  void applyPreRenderActions(int id);

  void removePreRenderAction(SoType type);

  /** Clear pre render actions of each pipes */
  void removeAllPreRenderActions();
  static void deleteAllPreRenderActions(ActionVector& actionsVec);

  /** Allocate count pre render actions. Old one are deleted. */
  void allocatePreRenderActions(size_t count);

  /** Return list of preRender action to apply on given pipe id */
  const ActionVector& getPreRenderActions(int id);

  static SceneManagerList s_sceneManagerList;
  static SbThreadSpinlock s_sceneManagerListMutex;

  /** Indicate that a dragger is interacting during rendering */
  void setDraggerInteracting();

  // Copy constructor forbidden
  SoSceneManager( const SoSceneManager& ) {};

  SoSceneManagerSync* m_synchronizer;

  SbBool              raCreatedHere;
  SbBool              heaCreatedHere;

  // as many render action as GLWidget. Dynamic allocation.
  SoGLRenderAction    **renderAction;
  // number of renderActions
  int                     nbRenderActions;

  /** Actions to apply before rendering*/
  ActionMap m_preRenderActions;

  /** List of GL render actions */
  static PreActionConstructorCbSet s_preRenderActionConstructors;

  SoHandleEventAction *handleEventAction;
  SoNode              *scene;
  SoNodeSensor        *sceneSensor;   // attached to root for auto-redraw
  SoNodeSensor        *fastEditSensor;
  SoNodeSensor        *sceneNodeSensor;   // attached to root for auto-redraw
  uint32_t    redrawPriority; // Priority of sceneSensor
  SbBool              active;         // set TRUE if we are active
  SbBool              needZbuffer;

  SbColor             bkgColor;
  int                 bkgIndex;
  SbBool              rgbMode;

  SbBool              m_newRender;

  // static callbacks
  static void         antialiasingCallback(void *);
  static void         sceneSensorCallback(SoSceneManager *, SoSensor *);
  static void         fastEditSensorCallback(SoSceneManager *mgr, SoSensor *sensor);
  static void         sceneNodeSensorCallback(SoSceneManager *, SoSensor *);

  // realTime field update vars and callbacks
  static SbBool       updateRealTime;
  static SoSFTime     *realTime;
  static SoOneShotSensor *realTimeSensor; // touches realTime global field
  static void         realTimeSensorCB();

  // this data are per pipe.
  struct PerPipe_Struct
  {
    // Constructor
    PerPipe_Struct()
    {
      m_needToSendVP = true;
      m_forceRedraw = false;
      m_draggerInteracting = false;
      m_graphicsInitNeeded = true;
    }

    // TRUE when glViewport() needs to be called
    bool m_needToSendVP;
    bool m_forceRedraw;
    bool m_draggerInteracting;
    bool m_graphicsInitNeeded;
  };
  struct PerPipe_Struct* m_perPipeData;

  SbBool m_allowRedraw, m_once;
  static SbBool s_checkGlErrors;

  friend struct SoAllocActionFunctor;
};

// INLINE METHODS
inline SoSceneManagerSync*
SoSceneManager::getSynchronizer()
{
  return m_synchronizer;
}

/*******************************************************************************/
int
SoSceneManager::getNumRenderActions() const
{
  return nbRenderActions;
}

#if defined(_WIN32)
#pragma warning( pop )
#endif

#endif // _SO_SCENE_MANAGER_

