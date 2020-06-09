/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
/*==============================================================================
*   Classes     : SoOcclusionCulling
*   Author(s)   : Jerome Hummel
*   Date        : 4-18-2002
*==============================================================================
*
* Description : Inserted at the top of a scene graph,
* this node will perform an occlusion culling test.
*
*============================================================================*/

#ifndef SO_OCC_CULLING_H
#define SO_OCC_CULLING_H

#include <Inventor/nodes/SoRenderList.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>



class SoOcclusionCulling;

/**
 * This callback is called at the end of each SoOcclusionCulling traversal to let
 * the application know how many objects have been occluded by the node.
 * [OIV-WRAPPER NAME{ReportCB}]
 */
typedef void SoOcclusionReportCB(SoOcclusionCulling *, 
                                 int numObj,
                                 int numRendered, 
                                 int numOccluders, 
                                 void *userData);

/**
 * @VSGEXT Group node derived from SoRenderList that performs an OpenGL-based 
 * occlusion culling test on its list of render objects.
 * 
 * @ingroup GroupNodes LMV
 * 
 * @DESCRIPTION
 *   The SoOcclusionCulling node uses the functionality from SoRenderList to create a
 *   list of paths to the shapes beneath it. It then reorganizes the list of shapes
 *   from front to back to perform an OpenGL-based occlusion culling test.
 *   The result is that render objects completely hidden by another visible object are 
 *   not rendered. For instance, if the camera is inside an object, only the object 
 *   containing the camera will be drawn (because that's the only object
 *   that the camera can see).
 *
 *   The SoOcclusionCulling node depends on the graphics board having support
 *   for the OpenGL GL_HP_occlusion_test extension. If this OpenGL extension is not
 *   supported, the SoOcclusionCulling node will have no effect on the display
 *   of the scene graph.
 *
 *   If the occlusionCulling node is below another culling node (for instance, an 
 *   octree and an occlusion culling node) then it will use the renderObject list 
 *   computed by the RenderList above it (the octree). In this particular case,
 *   the isHead field (from SoRenderList) must be initialized to FALSE. Otherwise
 *   the node will create its own renderObject list, which is unnecessary and time 
 *   consuming at scene graph creation time.
 *
 * @FILE_FORMAT_DEFAULT
 *    OcclusionCulling {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching        @TD AUTO
 *       @TR boundingBoxCaching   @TD AUTO
 *       @TR renderCulling        @TD AUTO
 *       @TR pickCulling          @TD AUTO
 *       @TR fastEditing          @TD DISABLE
 *       @TR isHead               @TD TRUE
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *  Actions use standard SoSeparator traversal.
 * 
 * @SEE_ALSO
 *    SoRenderList,
 *    SoOctreeOrdering
 * 
 * 
 */ 
class INVENTOR_API SoOcclusionCulling : public SoRenderList
{
  SO_NODE_HEADER(SoOcclusionCulling); 

 public:

#ifdef OIV_NET_DOC
	 /**
	 * Constructor. @BR
	 */

#else
	 /**
	 * Constructor. @BR
	 * 
	 * Note: Do not modify an instance of this node or any of its children
	 * unless this node has a ref count greater than zero. If the
	 * node is itself the child of a grouping node then the ref
	 * count is automatically greater than zero, otherwise you must
	 * explicitly increment the ref count by calling the ref() method.   
	 */

#endif //OIV_NET_DOC
	 SoOcclusionCulling();

  /**
   * This callback can be used to get render statistics: the number of objects 
   * actually rendered versus the number of objects that would have been rendered 
   * without the occlusion culling node.
   * [OIV-WRAPPER EVENT_NAME{ReportCallback}]
   */
  static void setReportCB(SoOcclusionReportCB *func, void *data);
  
  /**
   * Specifies the number of pixels below which the object will be culled.
   * The graphics board must support the GL_NV_occlusion_query OpenGL extension,
   * otherwise this method has no effect.
   */
  void setThreshold(unsigned int threshold);
  
  /**
   * Returns the pixel threshold.
   */
  unsigned int getThreshold(void);
  
  /**
   * Enabling this option may speed up rendering.
   * During the first frame, a list of occluders (objects that occlude others) 
   * will be computed. 
   * Then during the next N frames, only previously occluded objects will be
   * tested against the previous occluders.
   */
  void setApproximateOcclusion(SbBool enable);
  
  /**
   * Returns TRUE if approximate occlusion is On. 
   */
  SbBool isApproximateOcclusion(void);

  /**
   * When approximate occlusion is On, after @B num @b frames, the list of occluders
   * will be recalculated. 
   */
  void setNumFrame(unsigned int num);
  
  /**
   * Returns the number of frames between recalculation of the list of occluders
   * when approximate occlusion is On.
   */
  unsigned int getNumFrame(void);
  
  /**
   * By default, and if the hardware supports it, during the n-1 frames where occluders
   * are not retested, occluded objects are tested with a more efficient test using
   * the GL_NV_occlusion_query extension. If you prefer that the GL_NV_occlusion_query
   * extension not be used, pass TRUE to this function; the GL_HP_occlusion_test 
   * extension will be used instead.
   */
  void setUseHPExtension(SbBool enable);

  
  /**
   * Returns TRUE if the GL_HP_occlusion_test test is used instead of
   * GL_NV_occlusion_query test. See #setUseHPExtension.
   */
  SbBool getUseHPExtension(void)
    { return useHP; }

 SoEXTENDER public:
  // These implement supported actions
  virtual void  getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void  rayPick(SoRayPickAction *action);
  virtual void  getPrimitiveCount(SoGetPrimitiveCountAction *action);
  virtual void  GLRenderBelowPath(SoGLRenderAction *action);
  
 SoINTERNAL public:
  /**
   *  Sets up type identifier and file format name information for the class.
   */
  static void initClass();
  static void exitClass();
 
 protected :
  // Generic traversal of children, handles scene graph as if
  // this was just a SoSeparator node
  virtual void  doStandardTraversal(SoAction *action);
  
  // Spatial traversal of children
  virtual void  doSpatialTraversal(SoAction *action);
  
  virtual ~SoOcclusionCulling();
  
  int renderTransObjs(SoAction* action, SoRenderObjectList* vTransObject, SbBool);
  int occlusionTestNV(SoAction*, SoRenderObjectList *list, SoRenderObjectList *transparencyList, SbBool);
  int occlusionTestHP(SoAction*, SoRenderObjectList *list, SoRenderObjectList *transparencyList, SbBool, int startIndex);
  
  private :
    void commonConstructor();
  
  static SoOcclusionReportCB* userReportCB;
  static void *userData;
  
  unsigned int pixelThreshold;
  unsigned int frameCounter;
  unsigned int numFrame; // all objects are retested after numFrame frames
  SbBool approximateOcclusion;
  SbBool useHP;
  SbBool turnedOff;
  SbBool notSorted; 
};

#endif

