/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SEPARATOR_
#define  _SO_SEPARATOR_

#include <Inventor/nodes/SoGroup.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/caches/SoGLCacheList.h>
#include <Inventor/threads/SbThreadStorage.h>

class SoBoundingBoxCache;
class SoPrimitiveCountCache;
class SbThreadRWMutex;

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoSeparator
//
//  Separator group node: state is saved before traversing children
//  and restored afterwards.
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/fields/SoSFBitMask.h>

/** SoSeparator::renderUnitId : Don't traverse any children        */
#define SO_RENDERUNITID_NONE          (-1)

/** SoSeparator::renderUnitId : Inherit value from state           */
#define SO_RENDERUNITID_INHERIT       (-2)

/** SoSeparator::renderUnitId : Traverse all children              */
#define SO_RENDERUNITID_ALL           (-3)

/**
 * Group node that saves and restores traversal state.
 * 
 * @ingroup GroupNodes
 * 
 * @DESCRIPTION
 *   This group node performs a push (save) of the traversal state before traversing
 *   its children and a pop (restore) after traversing them. This isolates the
 *   separator's children from the rest of the scene graph. A separator can include
 *   lights, cameras, coordinates, normals, bindings, and all other properties.
 *   Separators are relatively inexpensive, so they can be used freely within
 *   scenes.
 *   
 *   The SoSeparator node provides caching of state during rendering and bounding box
 *   computation. This feature can be enabled by setting the #renderCaching and
 *   #boundingBoxCaching fields. By default, these are set to AUTO, which means
 *   that Open Inventor decides whether to build a cache based on internal
 *   heuristics.
 *
 *   Note that during the caching process, insufficient memory errors can happen, due to
 *   hardware limitations (ex: GPU memory). In this case, to prevent bad rendering or a
 *   crash, Open Inventor will disable caching for the current Separator by setting its renderCaching
 *   policy to OFF. In this case, we recommend to split the Separator's scene graph
 *   into several sub-scene graphs each with a new Separator as the head node.
 *   
 *   The #directVizCaching field is used when DirectViz rendering is enabled. It controls the way DirectViz internal
 *   objects are built. When an SoSeparator node is traversed with directVizCaching set to ON,
 *   DirectViz will build one internal object for all the shapes below, and the directVizCaching
 *   field is ignored for all of the SoSeparator nodes below. 
 *   Default value is OFF.
 *  
 *   Separators can also perform culling during rendering and picking. Culling skips
 *   over traversal of the separator's children if they are not going to be rendered
 *   or picked, based on the comparison of the separator's bounding box with the
 *   current view volume. Culling is controlled by the #renderCulling and
 *   #pickCulling fields. These are also set to AUTO by default; however,
 *   render culling can be expensive (and can interfere with render caching), so the
 *   AUTO heuristics leave it disabled unless specified otherwise.
 *   Note that if renderCulling is ON, the SoSeparator will prohibit auto-caching, so
 *   that no SoSeparator (or other render caching node) above this node in the scene graph
 *   will automatically create a render cache.
 *
 *  The fast editing feature allows you to modify parts of a scene without 
 *  redrawing the entire scene. For example, you could use it to interactively 
 *  move a small object in a large scene that takes a long time to redraw. 
 *  Fast editing must be enabled using SoGLRenderAction::setFastEditSavePolicy.
 * 
 *  The #fastEditing field enables fast editing for the sub-graph under the
 *  SoSeparator. 
 *  Possible values are DISABLE, KEEP_ZBUFFER, and CLEAR_ZBUFFER. 
 *  Using KEEP_ZBUFFER means that the fast edit geometry is depth buffered 
 *  against the other objects in the scene, and using CLEAR_ZBUFFER means 
 *  that the fast edit geometry will be drawn on top of the other objects of 
 *  the scene. If several SoSeparators have the CLEAR_ZBUFFER flag set, they 
 *  are drawn in the order in which they appear in the scene. The last 
 *  separator in the scene will be topmost on the screen.
 *
 *  NOTES:
 *  - Fast editing performance depends on your graphics hardware and driver. 
 *  To use the fast editing feature, the ARB_bufferRegion OpenGL extension 
 *  is required (refer to SoBufferRegion class description).
 *  - When a fast edit object is moved outside the clip planes limit, fast 
 *  editing is temporarily disabled and the entire scene is redrawn.
 *  - This feature is most efficient when the parts of a scene graph to be 
 *  fast edited contain few triangles. 
 *  - The topmost SoSeparator of your scene graph should not enable the fast editing feature.
 *  Otherwise, performance will be very poor. 
 *  - All fast editing sub-graphs are rendered even if only one fast editing sub-graph has changed.
 *  - Currently, the entire viewport is saved and restored during fast editing. 
 *  Therefore, fast editing performance is linked to the size of the viewport: the larger 
 *  the viewport, the longer it will take to save and restore it.
 *  - When using overlay planes, fast edit can cause visual artifacts. @BR
 *  In this case, we recommend setting the OIV_BUFFER_REGION_ENABLE environment
 *  variable to 0. The rendering performance of fast edit will decrease slightly, but
 *  the resulting rendering will be correct.
 *
 * @FILE_FORMAT_DEFAULT
 *    Separator {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching        @TD AUTO
 *       @TR boundingBoxCaching   @TD AUTO
 *       @TR directVizCaching     @TD OFF
 *       @TR renderCulling        @TD AUTO
 *       @TR pickCulling          @TD AUTO
 *       @TR fastEditing          @TD DISABLE
 *       @TR renderUnitID         @TD -1
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoGetMatrixAction,  SoHandleEventAction,  SoRayPickAction,  SoSearchAction @BR
 *        Saves the current traversal state, traverses all children, and restores the
 *        previous traversal state.
 *        Sets: SoCacheElement
 * 
 * @SEE_ALSO
 *    SoSelection,
 *    SoTransformSeparator,
 *    SoBufferRegion,
 *    SoDirectVizManager.
 *    
 * 
 * 
 */ 

class INVENTOR_API SoSeparator : public SoGroup {

  SO_NODE_HEADER(SoSeparator);

 public:

  /** Possible values for caching. */
  enum CacheEnabled {
    /**
     *  Never build a cache 
     */
    OFF,
    /**
     *  Always try to build a cache 
     */
    ON,
    /**
     *  Decide whether to cache based on some heuristic 
     */
    AUTO
  };

  /**
   * Whether to cache during rendering traversal.
   * Use enum #CacheEnabled. Default is AUTO.
   */
  SoSFEnum renderCaching;

  /**
   * Whether to cache during bounding box traversal.
   * Use enum #CacheEnabled. Default is AUTO.
   * 
   */
  SoSFEnum boundingBoxCaching;

  /**
   * Whether to cull during rendering traversal.
   * Use enum #CacheEnabled. Default is AUTO.
   * 
   */
  SoSFEnum renderCulling;

  /**
   * Whether to cull during picking traversal.
   * Use enum #CacheEnabled. Default is AUTO.
   * 
   */
  SoSFEnum pickCulling;

  /**
  *	
  * Whether to cache during OpenRTRT rendering traversal.
  * Use enum #CacheEnabled. Default is AUTO.
  * @BR
  * @BR
  * @FIELD_SINCE_OIV 6.1
  */
  SoSFEnum directVizCaching;

  /** Fast editing policy enumeration values. */
  enum FastEditing {
    /**
     * This SoSeparator node doesn't have Fast Edit behavior.
     */
    DISABLE = 0x01,

    /**
     * This SoSeparator node has a Fast Edit behavior and the children nodes are drawn considering the depth Buffer.
     */
    KEEP_ZBUFFER = 0x02,

    /**
     * This SoSeparator node has a Fast Edit behavior and the children nodes are drawn after the depth Buffer has been cleared.
     */
    CLEAR_ZBUFFER = 0x03
  };

  /**
   * Specifies the fast edit mode of the separator node.
   * Use enum #FastEditing. Default is DISABLE.
   *
   * @FIELD_SINCE_OIV 5.0
   */
  SoSFEnum fastEditing;

  /** 
   * Used during the ScaleViz depth compositing process, this field specifies which 
   * render unit (OIRU) will render the sub scene graph below this separator.
   *
   * - 0, the sub scene graph is rendered on the local machine. 
   * 
   * - > 0, the sub scene graph is rendered by the OIRU with the
   *   specified ID. If the specified renderUnitId is larger than the number
   *   of available render units, 
   *   the sub scene graph is distributed to the specified render unit ID modulo the 
   *   number of render units actually available. That is:@BR @BR
   *   RenderUnitUsed = ((renderUnitId-1)%(ActualNumberOfRenderUnits))+1
   *
   * - -1 (SO_RENDERUNITID_NONE), this separator is not assigned to any OIRU.@BR @BR
   *   NOTE: This is the default value, which means that by default the sub scene graph 
   *   is *not* distributed to any node. In order to use depth compositing, 
   *   you must modify renderUnitId from the default, otherwise nothing will be rendered.
   *
   * - -2 (SO_RENDERUNITID_INHERIT), this separator inherits its value
   *   from parent SoSeparator.
   *
   * - -3 (SO_RENDERUNITID_ALL), the sub scene graph is rendered by all OIRUs.
   *
   * @FIELD_SINCE_OIV 6.1
   */
  SoSFInt32 renderUnitId;

  /**
   * Creates a separator node with default settings.
   */
  SoSeparator();

  /**
   * Constructor that takes approximate number of children.
   */
  SoSeparator(int nChildren);

  /**
   * Sets the maximum number of render caches [@B Deprecated @b].
   * SoDB::setNumRenderCaches is recommended instead of this method.
   */
  SoDEPRECATED static void setNumRenderCaches(int howMany);

  /**
   * Returns the current number of render caches [@B Deprecated @b].
   * SoDB::getNumRenderCaches is recommended instead of this method.
   */
  SoDEPRECATED static int getNumRenderCaches();

 SoEXTENDER public:
  // Overrides default method on SoNode
  virtual SbBool      affectsState() const;

  // Implement actions
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        getMatrix(SoGetMatrixAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        handleEvent(SoHandleEventAction *action);
  virtual void        rayPick(SoRayPickAction *action);
  virtual void        search(SoSearchAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);
  virtual void        clearCacheList();
  virtual void        distribute(SoDistributeAction* action);

  // These methods make render traversal faster by implementing
  // different rendering paths corresponding to different action
  // path codes.
  virtual void        GLRenderBelowPath(SoGLRenderAction *action);
  virtual void        GLRenderInPath(SoGLRenderAction *action);
  virtual void        GLRenderOffPath(SoGLRenderAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  SB_THREAD_TLS_HEADER();

  virtual void        notify(SoNotList *list);

  // return SoNodeImpl private structure info
  // if not yet done, then it is allocated
  virtual SoNodeImpl *getNodeImpl();

  /**
   * return current BBox cache.
   * Particulary useful to reuse already construct bbox cache.
   * (ie. see SoExtSelection optimization)
   */
  SoBoundingBoxCache* getBoundingBoxCache() const
  { return bboxCache; }

#ifdef ADD_MFIELD_DEPLIST
  SoMFInt32 renderUnitDependencies;
#endif

protected:
  // Returns TRUE if this separator can be culled because it is
  // outside the cull volume.  The cullResults flags come from the
  // GLRenderAction->getCullTestResults() method, and track the
  // results of previous cull tests to save work when we know we're
  // completely inside the view volume.
  virtual SbBool cullTest(SoGLRenderAction *action, int &cullResults);

  virtual SbBool readInstance(SoInput *in, unsigned short flags);

  virtual ~SoSeparator();

  int m_numRenderCaches;

private:

  SoBoundingBoxCache* bboxCache; // Cache for bounding boxes
  SbThreadStorage< SoGLCacheList* > m_cacheList; // Caches for GL rendering

  SoPrimitiveCountCache *primCountCache;      // Cache for primitive count
        
  SbThreadRWMutex     *cacheMutex;    // Protects bboxCache and primCountCache
  SbBool bboxCacheIsOpen;

  // bba is in thread local storage now. 
  struct MTstruct {
    SoGetBoundingBoxAction *bba;
  };

  void commonConstructor();

  float m_depthOffsetCachedValue;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif /* _SO_SEPARATOR_ */
