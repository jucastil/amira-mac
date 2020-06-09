/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G.TALLEC (Oct 2006)
**=======================================================================*/


#ifndef  _SO_DIRECTVIZ_MANAGER_
#define  _SO_DIRECTVIZ_MANAGER_

#include <SoVersion.h>

// On Windows the "comment" pragma will automatically add our DirectViz
// library to the application's link string.
//#  if !defined(SOQT) || defined(LOAD_DIGVIZ_FOR_IVTUNE)

#ifdef _WIN32
#  if defined(_DEBUG)
#    define __DIRECTVIZDLL "DirectVizD.dll"
#    define __DIRECTVIZLIB "DirectVizD.lib"
#  else
#    define __DIRECTVIZDLL "DirectViz.dll"
#    define __DIRECTVIZLIB "DirectViz.lib"
#  endif
#  ifndef DirectViz_EXPORTS
#    ifndef OIV_DISABLE_AUTOLINK
#      pragma comment(lib,__DIRECTVIZLIB)
#    endif
#  endif
#else
#  define __DIRECTVIZDLL "libDirectViz"
#endif

#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFInt32.h> 
#include <Inventor/fields/SoMFInt32.h> 
#include <Inventor/fields/SoSFBool.h> 
#include <Inventor/fields/SoSFFloat.h> 
#include <Inventor/fields/SoSFFieldContainer.h>
#include <Inventor/fields/SoMFBool.h> 
#include <Inventor/fields/SoSFEnum.h> 

class SoSceneManager;
class SoCamera;
class SoNode;
class SoFieldContainer;
class SoFieldSensor;
class SoSensor;
class SoDirectVizShader;
class SoDirectVizRenderAction;
class SoDirectVizRenderManager;
class SoDirectVizCacheManager;
class SoDirectVizOpenRTManager;
class SoDirectVizDialog;
class SoDirectVizAction;

#include <Inventor/SoModule.h>
SO_MODULE_HEADER( SoDirectViz, __DIRECTVIZDLL )

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDirectVizManager
//
// DirectViz rendering manager
// 
//
//////////////////////////////////////////////////////////////////////////////

/**
* @DVEXT Manages ray-traced rendering.
*
* @ingroup DirectViz
* 
* @DESCRIPTION
*  SoDirectVizManager manages ray-traced rendering of scenes. See DirectViz group for the package description. 
*
*  SoDirectVizManager derives from SoNode, however @B it must not be referenced by the application 
*  and must not be inserted in a scene graph. @b  SoDirectVizManager is freed by calling finish().
* 
*  SoDirectVizManager provides general control of DirectViz:
*
*  - Activating ray-traced rendering for a viewer or render area@BR
*    SoDirectVizManager is associated with a scene manager when calling getInstance(). 
*    The scene manager can be retrived from a render area or viewer by calling 
*    SoXtRenderArea::getSceneManager() (or the SoWin or SoQt equivalent).@BR
*    Note that you can activate DirectViz for a viewer without using the SoDirectVizManager class 
*    by calling SoXtViewer::enableDirectViz(), SoWinViewer::enableDirectViz(), or 
*    SoQtViewer::enableDirectViz().@BR
*    As only one scene manager at a time can use ray-traced rendering in the current 
*    release, there can be only one DirectVizManager instance. If DirectViz was already 
*    associated with a scene manager, calling getInstance() with another scene manager will 
*    deactivate DirectViz on the previously associated scene manager. The same
*    applies for viewers and render areas. 
*
*  - Managing interactivity/quality trade-offs: resolution subsampling, progressive resolution, 
*    accumulation for oversampling/antialiasing, recursion depth limit.
*
*  - Enabling/disabling the control dialog
*
*  - Getting information about frame size, time for rendering, current accumulation pass; 
*    number of geometry objects, textures, lights and surface shaders
*
*   - Managing cache files for acceleration structures 
*
* Note: reflection and shadow rays computation use an offset internally used to deflect ray in order to prevent infinite hits.
* This offset is properly initialized to 1e-3, but it may lead to artefacts in some cases (wrong pixels).
* Then, the SoPreference variable DIRECTVIZ_RAY_EPSILON will have to be set to 1e-2 or 1e-1.
*
* @SEE_ALSO
*      SoSceneManager, SoXtRenderArea, SoXtViewer, SoWinRenderArea, SoWinViewer, SoQtRenderArea, SoQtViewer,
*      SoSeparator,
*      SoDirectVizShader
* 
* 
*/ 

class DIRECTVIZ_API SoDirectVizManager : public SoNode{

  SO_NODE_HEADER(SoDirectVizManager);

public:

  /**
  * Destructor
  */
  ~SoDirectVizManager();

  /**
  * Cache states
  */
  enum CacheMode
  {
    /** cache enabled in reading and writing*/
    READ_WRITE_MODE,
    /** cache enabled only in reading*/
    READ_MODE,
    /** cache enabled only in writing*/
    WRITE_MODE
  };

  /**
   * Number of environment lights
   */
  enum EnvLights  
  {
      /** 0 lights */
      ENV_LIGHTS_0,
      /** 2 lights */
      ENV_LIGHTS_2,
      /** 4 lights */
      ENV_LIGHTS_4,
      /** 8 lights */
      ENV_LIGHTS_8,
      /** 16 lights */
      ENV_LIGHTS_16,
      /** 32 lights */
      ENV_LIGHTS_32,
      /** 64 lights */
      ENV_LIGHTS_64,
      /** 128 lights */
      ENV_LIGHTS_128,
      /** 256 lights */
      ENV_LIGHTS_256
  };

  /**
  * Activates/deactivates accumulation passes. @BR
  * Accumulation consists of successive rendering passes resulting in progressive 
  * oversampling of the rendered image, reducing aliasing. Accumulation passes 
  * are started only after a small delay without rendering, i.e. when the viewer is still 
  * and there is  no animation in the scene. Each rendering pass takes a time equivalent 
  * to render a full resolution image. Accumulation is stopped after the current rendering 
  * pass is completed as soon as interaction starts again.
  * Default is TRUE.
  *
  * The initial value can be set using the environment variable DIRECTVIZ _ACCUMULATION.
  * See SoPreferences.
  * The number of successive passes is controlled with the #maxAccumulationValue field.@BR
  */
  SoSFBool accumulation;

  /**
  * Specifies a maximum number of accumulation passes. @BR Must be greater than or equal to 1.
  * Default is 10.
  *
  * The initial value can be set using the environment variable DIRECTVIZ_MAX_ACCUMULATION_VALUE.
  * See SoPreferences.
  */
  SoSFInt32 maxAccumulationValue;

  /** 
  * Activates/deactivates image sub-sampling. @BR
  * Sub-sampling consists of rendering a smaller (i.e., lower resolution) image when the viewer is not still.
  * Sub-sampling is controlled by a factor that represents the ratio between the 
  * rendered image and the full resolution image. Values can range from 0. to 1.0 (full resolution).
  * To set this factor, use the #subSamplingFactor field.
  * Default is TRUE.
  * 
  * The initial value can be set using the environment variable DIRECTVIZ_SUBSAMPLING.
  * See SoPreferences.
  */
  SoSFBool subSampling;

  /**
  * Specifies the sub-sampling factor. @BR Values can range from 0. to 1.
  * Default value is 0.5.
  * The initial value can be set using the environment variable DIRECTVIZ_SUBSAMPLING_FACTOR. 
  * See SoPreferences.
  */
  SoSFFloat subSamplingFactor;

  /**
  * Specifies the recursion depth limit. @BR
  * This is the maximum number of times a single ray can be reflected/refracted - "bounced" within the 
  * scene - when rendering a frame.
  * Reflection (ray reflected by a shape) is enabled when the recursion limit is at least 2.
  * Refraction (ray traversing a shape) is enabled when the recursion limit is at least 3.
  * Default is 20.
  *
  * The initial value can be set using the environment variable DIRECTVIZ_RECURSION_LIMIT.
  * See SoPreferences.
  */
  SoSFInt32 recursionLimit;

  /**
  * Enables/disables recursion when subsampling the scene. @BR
  * Rendering may be sped up during interaction with the scene or when scene is animated 
  * by setting #subRecursion to FALSE: it will force the recursion limit to 1 and
  * therefore prevent reflections and refractions.
  * Default is TRUE.
  *    
  * The initial value can be set using the environment variable DIRECTVIZ_SUB_RECURSION.
  * See SoPreferences.
  */
  SoSFBool subRecursion;

  /**
  * Activates/deactivates rendering with progressive resolution.    @BR
  * Progressive rendering consists of making several render steps between the subsampled image and the full 
  * resolution image.
  * The number of steps can be controlled with the #numProgressiveRenderingSteps field.
  * Default is FALSE.
  *
  * The initial value can be set using the environment variable DIRECTVIZ_PROGRESSIVE_RENDERING.
  * See SoPreferences.
  */
  SoSFBool progressiveRendering;

  /**
  * Specifies the number of steps (intermediate images) between subsampled rendering and full resolution 
  * rendering.  @BR Must be greater than 0.
  * Default is 5.
  *
  * The initial value can be set using the environment variable DIRECTVIZ_RENDER_STEPS.
  * See SoPreferences.
  */
  SoSFInt32 numProgressiveRenderingSteps;

  /**
  * Activates/deactivates ray-traced rendering. @BR
  * If TRUE, ray-traced rendering is enabled. 
  * Default is FALSE.
  */
  SoSFBool rendering;

  /**
  * Enables/disables shadows globally in the scene graph. @BR
  * Default is FALSE.
  *   
  * The initial value can be set using the environment variable DIRECTVIZ_GLOBAL_SHADOW.
  * See SoPreferences.   
  *
  */
  SoSFBool globalShadowing;

  /**
  * Enables/disables adaptive oversampling rendering. @BR
  * Default is FALSE.
  *   
  * Adaptive oversampling reduces aliasing only near aliased pixels in the image.
  * The initial value can be set using the environment variable DIRECTVIZ_ADAPTIVE_OVERSAMPLING.
  * See SoPreferences.   
  * @M_SINCE 7.2
  */
  SoSFBool adaptiveOversampling;

  /**
  * Enables/disables soft shadows globally in the scene graph. @BR
  * Default is FALSE.
  *   
  * The initial value can be set using the environment variable DIRECTVIZ_SOFT_SHADOWS.
  * See SoPreferences.   
  * @M_SINCE 7.2
  */
  SoSFBool softShadows;

  /**
  * Enables/disables fuzzy effects globally in the scene graph. @BR
  * Default is FALSE.
  *   
  * The initial value can be set using the environment variable DIRECTVIZ_FUZZY_LIGHTS.
  * See SoPreferences.   
  * @M_SINCE 7.2
  */
  SoSFBool fuzzyLights;

  /**
  * Enables/disables glossy surfaces effects globally in the scene graph. @BR
  * Default is FALSE.
  *   
  * The initial value can be set using the environment variable DIRECTVIZ_GLOSSY_SURFACES.
  * See SoPreferences.   
  * @M_SINCE 7.2
  */
  SoSFBool glossySurfaces;

  /**
  * Enables/disables environment lighting by specifying the number of lights. @BR
  * When an Environment shader is specified, DirectViz allows extracting fake 
  * lights from the environment texture. Thus, the lighting is performed with 
  * additional lights coming directly from the environment. When combined with 
  * accumulation, the fake lights are taken at different environment texture 
  * positions at each accumulation step. Thus, lights from the entire environment 
  * can be used for illumination, giving a fast and accurate approximation of ambient occlusion.
  * Default is 0.
  *   
  * The initial value can be set using the environment variable DIRECTVIZ_NUM_ENV_LIGHTS.
  * See SoPreferences.   
  * @M_SINCE 8.0
  */
  SoSFEnum numEnvLights;

  /**
  * Intensity scale applied to environment lights defined by #numEnvLights. @BR
  * Default is 1.
  *   
  * The initial value can be set using the environment variable DIRECTVIZ_ENV_LIGHTS_SCALE.
  * See SoPreferences.   
  * @M_SINCE 8.0
  */
  SoSFFloat envLightIntensityScale;

  /**
  * Enables/disables acceleration structure cache file.   @BR 
  * DirectViz file caching consists of saving on disk the internal accelaration structure built 
  * for OpenRTRT objects  corresponding to an Open Inventor scene graph, which can save a significant 
  * amount of time when reloading large scenes.@BR
  * A cache directory must be specified with the #setCacheDirectory method, which will contain the 
  * cache files.
  *  <B>For each scene graph there is exactly one cache file.</B> 
  * A signature is automatically created and written in cache files, so it is not nesessary to 
  * name explicitly cached files. @BR
  * If #fileCaching is set to TRUE, before rendering a new scene, DirectViz will first search in the 
  * cache directory if there is a cache file correponding to the scene signature. 
  * If such cache file exists, DirectViz will directly load OpenRTRT objects from it. 
  * Otherwise, DirectViz will create OpenRTRT objects from the scene graph and save them with the 
  * scene signature in a new cache file in the cache directory.  
  * A cache file can also be specified explicitly with #setCacheFile().
  * Default is FALSE.
  *    
  * The initial value can be set using the environment variable DIRECTVIZ_FILE_CACHING.
  * See SoPreferences.
  */
  SoSFBool fileCaching;

  /**
  * Enables/disables the DirectViz control dialog. @BR
  * DirectViz interactive parameters can be controlled using this dialog with Qt or 
  * Win32 viewers. When set to TRUE, the dialog can be displayed by pressing the 
  * Shift + F8 key (or the key specified in the DIRECTVIZ_DIALOG_SHORTCUT environment variable)
  * Default is TRUE.
  * 
  * The initial value can be set using the environment variable DIRECTVIZ_CONTROL_DIALOG.
  * See SoPreferences.
  */
  SoSFBool controlDialog;

  /**
  * Initalizes the DirectViz classes.  @BR
  * It is not necessary to call this method directly from
  * a user application as DirectViz will be initialized
  * automatically by Open Inventor.
  * [OIV-WRAPPER-NO-WRAP]
  */
  static void init();

  /** 
  * Shuts down the DirectViz module, which includes freeing any
  * internal static memory that it allocated. 
  * Finish methods must be called in the reverse order of the init method calls: 
  * <PRE>    SoDirectVizManager::finish(); 
  *    SoXt::finish(); 
  *    ... </PRE>
  * [OIV-WRAPPER-NO-WRAP]
  */
  static void finish();

  /**
   * Returns TRUE if DirectViz is currently initialized.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static bool isInitialized();

  /**
  * Returns a pointer to a DirectVizManager object associated with the  specified scene 
  * manager.  @BR If DirectViz was already 
  * associated with a scene manager,  calling getInstance() with another scene manager will 
  * deactivate DirectViz on the previously associated scene manager.
  * To retrieve the scene manager corresponding to a viewer or render area, you can use 
  * code similar to:
  * <pre>
  *       pViewer->getSceneManager();</pre>
  */
  static SoDirectVizManager *getInstance(SoSceneManager *mgr);

  /**
  * Gets the current accumulation value.
  */
  int getCurrentAccumValue() const;

  /**
  * Gets the size of rendered image in pixels.
  */
  void getRenderedImageSize(SbVec2s &size) const;

  /**
  * Gets the elapsed time for rendering the last frame in seconds.
  */
  double getLastRenderTime() const;

  /**
  * Specifies cache directory (it must be an absolute path). @BR
  * The initial value can be set using the environment variable DIRECTVIZ_CACHE_DIR.
  * See SoPreferences.
  */
  void setCacheDirectory(SbString directory);

  /**
  * Specifies cache file as an absolute path name. @BR
  * Cache files can be used for either reading or writing depending on mode:<BR>
  * - READ_WRITE_MODE (default): the file is used for both reading and writing.<BR>
  * - READ_MODE: the file is only used for reading. The file will not be erased when a cache is written.<BR>
  * - WRITE_MODE: the file is only used for writing.
  */
  void setCacheFile(SbString file,CacheMode mode = READ_WRITE_MODE);

  /**
  * Returns number of environment lights (see field numEnvLights).
  */
  int getNumEnvironmentLights();

  //----------------------------------------------------------------------------------------------------

  private:

  /**
  * private bool states
  */
  typedef enum{
    FORCE_RENDER = 0,//forcing viewer rendering
    CHECK_STILL_TIME,//must check still time
    GENERATING,//is generating
    SIZE_CHANGED,
    STILL,//is still
    ASK_REDRAW,//redraw asked
    FORCE_REDRAW,//true if redraw forced
    CLEAR_ACCUM_BUFFER,//true if must clear accum buffer
    FIRST_RENDER,//true if first render
    SUBSAMPLED,//true if if last image was subsampled
    FORCE_CAMERA_SETUP,
    FORCE_ACCUMULATION,
    DISABLE_SUBSAMPLING_CHECK,
    PRIVATE_BOOL_STATES
  } privateBoolStates;
  
  /**
  * private int states
  */
  typedef enum{
    CURRENT_ACCUM_VALUE = 0,//current accumulation value
    CURRENT_PROGRESSIVE_RENDER,//current progressive rendering value
    PRIVATE_INT_STATES
  } privateIntStates;

  SoINTERNAL public:

  /**
  * Constructor
  */
  SoDirectVizManager();

  //stop rendering current frame 
  void stopFrame();

  /**
   *  Sets the rendering properties management flag.
   * On ScaleViz oiru, must be set to false
   */
  void setManageRenderingProperties( bool manage );

  /**
   *  Returns manage properties flag
   */
  bool manageRenderingProperties();

  /**
   *  Force camera setup before rendering
   */
  void forceCameraSetup();
  
  /**
  *  Sets the current accumulation buffer id.
  * By default, only one accumulation buffer is created and allocated. One can give the accumulation buffer id before a render.
  * This is used for tile rendering when tiles are rendered in the same OpenRTRT context. 
  */
  void setAccuId( unsigned int accuId );

  /**
   *  Force accumulation
   */
  void forceAccumulation( bool forceAccum );

  /**
   *  Disable subsampling check
   */
  void disableSubSamplingCheck( bool disableCheck );

  //returns enum value corresponding to number of lights
  int getEnvLightsEnumValue( int numLights );

  //returns num env lights corresponding to enum value
  int getNumEnvironmentLights( int enumValue );

  static SoDirectVizManager * getInstance();

  /**
  * object states
  */
  typedef enum{
    ACTIVE=0,
    BUILT
  } DirectVizObjectState;

  /**
  * object types
  */
  typedef enum{
    SEPARATOR=0,
    SHADER,
    ENVIRONMENT,
    TEXTURE,//RESPECT ORDER
    LIGHT,
    SHAPE,
    CAMERA,
    NUMVECTORS,
    OBJECT
  } DirectVizObjectType;

  static void initClass();

  static void exitClass();

  static void setViewer(void *viewer){_viewer = viewer;}

  static void *getViewer(){return _viewer;}

  /**
  * Return number of objects of specified type.
  */
  int getNumRTObjects(DirectVizObjectType t,DirectVizObjectState s) const;

  /**
  * Returns number of objects of specified type.
  */
  int getNumRTObjects(DirectVizObjectType t) const;

  /**
  * Sets recursion limit.
  */
  void setRecursionLimit(int limit,SbBool forceRedraw = true);

  /**
  * return the currently used instance if exist.
  */
  static SoDirectVizManager *instance();

  /**
  * Get cache manager.
  */
  SoDirectVizCacheManager *getCacheMgr();

  /**
  * Get OpenRT manager.
  */
  SoDirectVizOpenRTManager *getOpenRTMgr(){
    return _openRTMgr;
  }

  /**
  * generate a pixmap 
  */
  void generatePixMap();

  void internalEnable(SbBool enable);

  /**
  * Render
  */
  void render(bool forceRender = true);

  /**
  * check cache
  */
  void checkCache(bool startTraversal);

  /**
   * Get scene manager
   */
  SoSceneManager *getSceneManager() const;

  /**
  * Set scene manager
  */
  void setSceneManager(SoSceneManager *sceneManager);

  /**
  * Set camera
  */
  void setCamera(SoCamera *camera);

  /**
  * Set scene root
  */
  void setSceneRoot(SoNode *sceneRoot);

  /**
  * Get shader class corresponding to OIV node
  */
  unsigned int getShaderClass(SoNode *node);

  /**
  * Get shader class corresponding to SoDirectVizShader
  */
  unsigned int getShaderClass(SoDirectVizShader *shader);

  /**
  * Get shader class corresponding to OIV node
  */
  int getShaderClassType(SoNode *node);

  /**
  * Set scene graph
  */
  void setSceneGraph(SoNode *node);

  void setMsg(SbString msg);

  void setDialog(SoDirectVizDialog *dialog){_dialog = dialog;}

  /**
  * Render manager
  */
  SoDirectVizRenderManager *_renderMgr;

  /**
  * current instance
  */
  static SoDirectVizManager *_directVizManager;

  /**
  * control dialog
  */
  SoDirectVizDialog *_dialog;

  SbBool getInitialisationState(){return _openRTInitialized;}

  /**
  * Set quality
  */
  void setQuality(int quality);

  /**
  * init rendering
  */
  bool initRendering();

  /**
  * force a redraw
  */
  void redraw();

  /**
  * internalRedraw
  */
  void internalRedraw(SbBool fromOffscreen = FALSE);

  /**
  * initialisation
  */
  void initialize();

  /**
  * Read config file
  */
  void readConfigFile();

  /**
  * clear
  */
  void clear();

  /**
   * Render action
   */
  SoDirectVizRenderAction *getRenderAction() const;

  /**
  * callback action
  */
  SoDirectVizAction *_directVizAction;

  /**
   * traversed SG
   */
  SoNode *getSceneGraph() const;

  /**
  * image sizes
  */
  SbVec2s _size,_lastSize;

  /**
   *  Store rendering state ( internal parameters , size)
   */
  void storeRenderingState();
  
  /**
   *  Restore rendering state ( internal parameters , size)
   */
  void restoreRenderingState();
 
protected:

    //Stored bool rendering state
    bool m_storedBoolRenderingState[PRIVATE_BOOL_STATES];
    
    //Stored int rendering state
    int m_storedIntRenderingState[PRIVATE_INT_STATES];

    //stored size
    SbVec2s m_storedSize;

    /**
     *  If true, manage rendering properties : accumulation, subsampling.
     * If running ScaleViz, only true on the master, false on oirus.
     * Default is true.
     */
    bool m_manageRenderingProperties;

 private :

  static int s_initRefCount;

  static const char *s_versionString;

  /**
   * notification catcher
   */
  void notify(SoNotList *list);


  /**
  * setup the camera for rendering
  */
  void setupCamera();

  /**
  * scene manager
  */
  SoSFFieldContainer m_sceneManager;

  /**
   * traversed SG
   */
  SoSFFieldContainer m_sceneGraph;
    
  /**
   * old render action
   */
  SoGLRenderAction *_oldAction;

  /**
  * scene manager
  */
  SoSceneManager *_sceneManager;

  /**
   * current camera
   */
  SoSFFieldContainer m_camera;
  SoCamera * getCamera() const;
 
  /**
   * DirectViz Render action
   */
  SoDirectVizRenderAction *_renderAction;

  /**
  * current camera
  */
  SoCamera *_camera;

  /**
  * old recursion limit
  */
  int _oldLimit;

  /**
  * private bool states to be synchronized with ScaleViz 
  */
  SoMFBool _privateBoolState;
  
  /**
  * private int states to be synchronized with ScaleViz 
  */
  SoMFInt32 _privateIntState;
  
  /**
  * Say if running OpenRTRT cluster . DON T SYNCHRONIZE
  */
  SbBool m_clusterMode;

  static SbBool _openRTInitialized;

  /**
  * last image render time
  */
  double _lastRenderTime;

  /**
  * cache manager
  */
  SoDirectVizCacheManager *_cacheMgr;

  /**
  * OpenRT manager
  */
  SoDirectVizOpenRTManager *_openRTMgr;

  static void *_viewer;

  friend class SoDirectVizCacheManager;
  friend class SoDirectVizRenderAction;
  friend class SoDirectVizRenderManager;
  
  /** */
  static bool isGuiBase(const SoFieldContainer *fc);   
};

#endif

