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


#ifndef  _SO_VRMLSTATICGROUP_
#define  _SO_VRMLSTATICGROUP_

#include <Inventor/fields/SoMFNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoGroup.h>

class SoBoundingBoxCache;
class SoGLCacheList;
class SoPrimitiveCountCache;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLStaticGroup
//
//  VRMLStaticGroup group node: state is saved before traversing children
//  and restored afterwards.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Group node.\ @PARTIAL_ACTION
 *  
 * @ingroup X3D
 * 
 * @DESCRIPTION
 *   See the X3D Specification, below.
 * 
 * @VRMLX3D_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the VRML97 specification that are not
 *   present in this help file. The complete VRML97 spec is available at
 *   @B http://www.web3d.org @b.
 * 
 *   The StaticGroup node contains children nodes which cannot be modified. 
 *   StaticGroup children are guaranteed to not change, send events, 
 *   receive events or contain any USE references outside the StaticGroup. 
 *   
 *   Children of the StaticGroup are guaranteed not to generate events.
 *  
 *   The #bboxCenter and #bboxSize fields specify a bounding box that
 *   encloses the SoVRMLStaticGroup's children. This is a hint that may be used for
 *   optimization purposes. If the specified bounding box is smaller than the actual
 *   bounding box of the children at any time, then the results are undefined. A
 *   default #bboxSize value, (-1 -1 -1), implies that the bounding box is not
 *   specified and if needed must be calculated by the browser. See "Concepts -
 *   Bounding Boxes" for a description of the #bboxCenter and #bboxSize
 *   fields.
 *   
 *   Note: The following fields -- #renderCaching, #boundingBoxCaching,
 *   #renderCulling, and #pickCulling -- are specific to the 
 *   Open Inventor by VSG implementation and are not part of the 
 *   VRML97 specification. These fields are very useful for performance tuning, 
 *   but are not written out if the output file is specified as VRML97 format. 
 *   See SoSeparator for a discussion of Open Inventor caching and culling.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLStaticGroup {
 *    @TABLE_FILE_FORMAT
 *       @TR children     @TD []
 *       @TR bboxCenter   @TD 0 0 0
 *       @TR bboxSize     @TD -1 -1 -1
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoHandleEventAction,  SoRayPickAction,  SoGetMatrixAction,  SoSearchAction,  SoWriteAction  @BR
 *      Sets: SoCacheElement
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 *
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 *
 * 
 */ 

class INVENTOR_API SoVRMLStaticGroup : public SoGroup {

  SO_NODE_HEADER(SoVRMLStaticGroup);

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
  * Field that contains a list of children nodes.
  *
  */
   SoMFNode  children;
 /**
  * The #bboxCenter and #bboxSize fields specify a bounding box that
  * encloses the SoVRMLParent's children. This is a hint that may be used for
  * optimization purposes. If the specified bounding box is smaller than
  * the actual bounding box of the children at any time, then the results 
  * are undefined. A default #bboxSize value, (-1 -1 -1), implies that
  * the bounding box is not specified.
  * 
  */
  SoSFVec3f bboxCenter;
  /**
  * The #bboxCenter and #bboxSize fields specify a bounding box that
  * encloses the SoVRMLParents's children. See #bboxCenter for details.
  */
  SoSFVec3f bboxSize;

  /**
   * Whether to cache during rendering traversal.
   * Use enum #CacheEnabled. Default is AUTO.
   * 
   * @B NOTE:@b This field is not compatible with VRML97/X3D.
   * If you specify a non-default value for this field, when 
   * this node is written to a VRML file, the file will contain
   * this incompatible field and standard VRML97/X3D file readers 
   * will not be able to read it.
   */
  SoSFEnum renderCaching;

  /**
   * Whether to cache during bounding box traversal.
   * Use enum #CacheEnabled. Default is AUTO.
   * 
   * @B NOTE:@b This field is not compatible with VRML97/X3D.
   * If you specify a non-default value for this field, when 
   * this node is written to a VRML file, the file will contain
   * this incompatible field and standard VRML97/X3D file readers 
   * will not be able to read it.
   */
  SoSFEnum boundingBoxCaching;

  /**
   * Whether to cull during rendering traversal.
   * Use enum #CacheEnabled. Default is AUTO.
   * 
   * @B NOTE:@b This field is not compatible with VRML97/X3D.
   * If you specify a non-default value for this field, when 
   * this node is written to a VRML file, the file will contain
   * this incompatible field and standard VRML97/X3D file readers 
   * will not be able to read it.
   */
  SoSFEnum renderCulling;

  /**
   * Whether to cull during pick traversal.
   * Use enum #CacheEnabled. Default is AUTO.
   * 
   * @B NOTE:@b This field is not compatible with VRML97/X3D.
   * If you specify a non-default value for this field, when 
   * this node is written to a VRML file, the file will contain
   * this incompatible field and standard VRML97/X3D file readers 
   * will not be able to read it.
   */
  SoSFEnum pickCulling;

  /**
   * Default constructor.
   */
  SoVRMLStaticGroup();

  /**
   * Constructor that takes approximate number of children.
   */
  SoVRMLStaticGroup(int nChildren);

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
  // Returns TRUE if this VRMLStaticGroup can be culled because it is
  // outside the cull volume.  The cullResults flags come from the
  // GLRenderAction->getCullTestResults() method, and track the
  // results of previous cull tests to save work when we know we're
  // completely inside the view volume.
  virtual SbBool      cullTest(SoGLRenderAction *action, int &cullResults);

  virtual ~SoVRMLStaticGroup();

  int m_numRenderCaches;

  SoBoundingBoxCache  *bboxCache;     // Cache for bounding boxes
  SoGLCacheList       *cacheList;     // Caches for GL rendering
  SoPrimitiveCountCache *primCountCache;      // Cache for primitive count
};

#endif /* _SO_VRMLSTATICGROUP_ */

