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


#ifndef  _SO_VRMLGROUP_
#define  _SO_VRMLGROUP_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/VRMLnodes/SoVRMLParent.h>
#include <Inventor/fields/SoSFInt32.h>

class SoBoundingBoxCache;
class SoGLCacheList;
class SoPrimitiveCountCache;
class SoDistributeAction;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLGroup
//
//  VRMLGroup group node: state is saved before traversing children
//  and restored afterwards.
//
//////////////////////////////////////////////////////////////////////////////

/** SoSeparator::renderUnitId : Don't traverse any children        */
#define SO_RENDERUNITID_NONE          (-1)

/** SoSeparator::renderUnitId : Inherit value from state           */
#define SO_RENDERUNITID_INHERIT       (-2)

/** SoSeparator::renderUnitId : Traverse all children              */
#define SO_RENDERUNITID_ALL           (-3)

/**
 * @VSGEXT Group node.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   An SoVRMLGroup node is equivalent to an SoVRMLTransform node, without the
 *   transformation fields. 
 * 
 * @VRML2_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the VRML97 specification that are not
 *   present in this help file. The complete VRML97 spec is available at
 *   @B http://www.web3d.org @b.
 *   
 *   An SoVRMLGroup node is equivalent to an SoVRMLTransform node, without the
 *   transformation fields. 
 *   
 *   See the "Concepts - Grouping and Children Nodes" section for a description of the
 *   @B children @b, @B addChildren @b, and @B removeChildren @b fields and
 *   eventIns.
 *   
 *   The #bboxCenter and #bboxSize fields specify a bounding box that
 *   encloses the SoVRMLGroup's children. This is a hint that may be used for
 *   optimization purposes. If the specified bounding box is smaller than the actual
 *   bounding box of the children at any time, then the results are undefined. A
 *   default #bboxSize value, (-1 -1 -1), implies that the bounding box is not
 *   specified and if needed must be calculated by the browser. See "Concepts -
 *   Bounding Boxes" for a description of the #bboxCenter and #bboxSize
 *   fields.
 *   
 *   Note: The following fields -- #renderCaching, #boundingBoxCaching,#directVizCaching, 
 *   #renderCulling, and #pickCulling -- are specific to the Open
 *   Inventor implementation by VSG and are not part of 
 *   the VRML97 specification. These
 *   fields are very useful for performance tuning, but are not written out if the
 *   output file is specified as VRML97 format. See SoSeparator for a discussion of
 *   Open Inventor caching and culling. The field #renderUnitId is likewise not
 *   part of the VRML97 specification. It is used with ScaleViz for cluster rendering.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLGroup {
 *    @TABLE_FILE_FORMAT
 *       @TR children       @TD []
 *       @TR bboxCenter     @TD 0 0 0
 *       @TR bboxSize       @TD -1 -1 -1
 *       @TR metadata       @TD NULL
 *       @TR renderCaching  @TD AUTO (see note above)
 *       @TR boundingBoxCaching @TD AUTO (see note above)
 *       @TR renderCulling  @TD AUTO (see note above)
 *       @TR pickCulling    @TD AUTO (see note above)
 *       @TR directVizCaching     @TD OFF (see note above)
 *       @TR renderUnitId   @TD -1 (see note above)
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoHandleEventAction,  SoRayPickAction,  SoGetMatrixAction,  SoSearchAction,  SoWriteAction  @BR
 *    Sets: SoCacheElement
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoMFNode   @TD   addChildren      
 *       @TR   SoMFNode   @TD   removeChildren      
 *       @TR   SoMFNode   @TD   set_children
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoMFNode   @TD   children_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLGroup : public SoVRMLParent {

  SO_NODE_HEADER(SoVRMLGroup);

 public:
 
    /** Possible values for caching */
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

  // Fields
  /**
   * Whether to cache during rendering traversal.
   * Use enum #CacheEnabled. Default is AUTO.
   * 
   * @B NOTE:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when 
   * this node is written to a VRML file, the file will contain
   * this incompatible field and standard VRML97 file readers 
   * will not be able to read it.
   */
  SoSFEnum renderCaching;

  /**
   * Whether to cache during bounding box traversal.
   * Use enum #CacheEnabled. Default is AUTO.
   * 
   * @B NOTE:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when 
   * this node is written to a VRML file, the file will contain
   * this incompatible field and standard VRML97 file readers 
   * will not be able to read it.
   */
  SoSFEnum boundingBoxCaching;

  /**
   * Whether to cull during rendering traversal.
   * Use enum #CacheEnabled. Default is AUTO.
   * 
   * @B NOTE:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when 
   * this node is written to a VRML file, the file will contain
   * this incompatible field and standard VRML97 file readers 
   * will not be able to read it.
   */
  SoSFEnum renderCulling;

  /**
   * Whether to cull during pick traversal.
   * Use enum #CacheEnabled. Default is AUTO.
   * 
   * @B NOTE:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when 
   * this node is written to a VRML file, the file will contain
   * this incompatible field and standard VRML97 file readers 
   * will not be able to read it.
   */
  SoSFEnum pickCulling;

  /**
  * Whether to cache during DirectViz rendering traversal.
  * Use enum #CacheEnabled. Default is OFF.
  * @B NOTE:@b This field is not compatible with VRML97.
  * If you specify a non-default value for this field, when 
  * this node is written to a VRML file, the file will contain
  * this incompatible field and standard VRML97 file readers 
  * will not be able to read it.
  * @BR
  * @BR
  * @FIELD_SINCE_OIV 7.0
  */
  SoSFEnum directVizCaching;

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
   * Default constructor.
   */
  SoVRMLGroup();

  /**
   * Constructor that takes approximate number of children.
   */
  SoVRMLGroup(int nChildren);

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

  // Implement actions
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        getMatrix(SoGetMatrixAction *action);
  virtual void        rayPick(SoRayPickAction *action);
  /*
    virtual void        pick(SoPickAction *action);
  */
  virtual void        search(SoSearchAction *action);
  virtual void        write(SoWriteAction *writeAction);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);
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

  virtual void        notify(SoNotList *list);

 protected:
  // Returns TRUE if this VRMLGroup can be culled because it is
  // outside the cull volume.  The cullResults flags come from the
  // GLRenderAction->getCullTestResults() method, and track the
  // results of previous cull tests to save work when we know we're
  // completely inside the view volume.
  virtual SbBool      cullTest(SoGLRenderAction *action, int &cullResults);

  virtual ~SoVRMLGroup();

  SoBoundingBoxCache  *bboxCache;     // Cache for bounding boxes
  SoGLCacheList       *cacheList;     // Caches for GL rendering
  SoPrimitiveCountCache *primCountCache;      // Cache for primitive count

  void commonConstructor();

  virtual SoNodeImpl *getNodeImpl();

private:
  int m_numRenderCaches;
};

#endif /* _SO_VRMLGROUP_ */

