/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

/*---------------------------------------------------------------------
 *  Header file for "SoOctreeOrdering", 
 *   SoRenderList-derived group node.
 *
 *  Created: bga 31-March-97
 *  Modified: Jerome Hummel - Jun 2001 -
 *  -for multithreading. 
 *  -drawing of the octree for debug purpose, permanently (environment variable OIV_DRAWOCTREE)
 *  or controlled by the user (seeOctreeDrawing(), eraseOctreeDrawing())
 *  -add a CB for the user to get the statistics of the octree
 *  (how many objects are rendered by thread,number of objects to render,...)                
 *------------------------------------------------------------*/


#ifndef _SO_OCTREE_ORDERING_HH
#define _SO_OCTREE_ORDERING_HH 1

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoRenderList.h>
#include <Inventor/threads/SbThread.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>

#ifndef HIDDEN_FROM_DOC
class _SoOctreeRenderObjectTree;

// Extend the SoRenderObject to contain the data we want to store
/** [OIV-WRAPPER-NO-WRAP] */
class INVENTOR_API SoOctreeRenderObject : public SoRenderObject 
{

 public:
  
  SoOctreeRenderObject(const SoPath *p) : SoRenderObject(p) 
    { 
    
      flags.rendered = FALSE; flags.inOctree = FALSE; 
      flags.inMoving = FALSE; flags.moving = FALSE; 
    
      name = p->getTail()->getName();
    };
  
  virtual ~SoOctreeRenderObject()  { };
  
  struct 
  {
    unsigned int rendered : 1; 
    unsigned int inOctree : 1; 
    unsigned int inMoving : 1; 
    unsigned int moving   : 1; 
  } flags;
  
  // to get an easyest way to identify the object
  SbName getName(void) { return name; };

  private :
    
    SbName name;
    
};
#endif // HIDDEN_FROM_DOC

//used to allow the user to get the statistics of the render.
class SoOctreeOrdering;
/**
 * This callback is called at the end of each SoOctreeOrdering traversal to let
 * the application know how many objects have been rendered. If several render thread
 * are traversing the octree (MP viewer), each of them will tell how many objects they
 * have rendered according to the frustum associated.
 * [OIV-WRAPPER NAME{ReportCB}]
 */
typedef void SoReportCB(SoOctreeOrdering *node,
                        int numObj,
                        int objRendered,
                        void *userData);


/**
 * @VSGEXT Group node derived from SoRenderList that maintains a transparent octree
 * organization of the shapes below it. This speeds view frustum culling in large
 * scenes in which the viewer moves through the scene and much of the scene is not
 * visible at any given time.
 * 
 * @ingroup GroupNodes LMV
 * 
 * @DESCRIPTION
 *   The SoOctreeOrdering node uses the functionality from SoRenderList to create a
 *   list of paths to the shapes beneath it. It then reorganizes the list of shapes
 *   into an octree division of space. During action traversal, it traverses the
 *   octree instead of the scene graph. This results in a front to back traversal
 *   that quickly skips sections of space that would be culled by the view frustum.
 *   
 *   The OctreeOrdering node draws a bounding box to replace cells in the octree that
 *   contain shapes but that are too small, based on an approximate screen size. If a
 *   larger shape had already been rendered that passes through this cell, the cell
 *   will be culled instead of using the bounding box so that no rendered geometry
 *   will be covered by a bounding box. This behavior can be altered by the fields
 *   listed below.
 *   
 *   To specify the maximum depth during octree ordering, use environment variable
 *   IV_OCTREE_MAX_DEPTH. The default is 8.
 *   
 *   To request an outline of the octree quadrants be drawn as a debugging aid to
 *   allow you to see how your scene is distributed throughout the octree, set
 *   environment variable OIV_DRAW_OCTREE to 1 or use the method #setOctreeDrawing.
 * 
 *   @B Note@b: If an SoOcclusionCulling node is inserted below the SoOctreeOrdering node,
 *   the latter can pass its view-frustum-culled renderObject list to 
 *   the occlusion node, which will perform an occlusion culling test
 *   to reduce even further the number of objects to render. See the #isHead field
 *   of SoRenderList for additional info.
 *
 * @FILE_FORMAT_DEFAULT
 *    OctreeOrdering {
 *    @TABLE_FILE_FORMAT
 *       @TR dropCulling              @TD TRUE
 *       @TR dropScreenArea           @TD 5
 *       @TR boundingBoxSubstitutes   @TD TRUE
 *       @TR useMovingQueue           @TD TRUE
 *       @TR adjustDecimation         @TD TRUE
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
 *    SoGLRenderAction,  SoGetPrimitiveCountAction @BR
 *        Uses octree spatial traversal, rendering front to back. All other actions use
 *        standard SoSeparator traversal. Sets: SoRenderObjectListElement
 * 
 * 
 * @SEE_ALSO
 *    SoSplitGeometryAction,
 *    SoGetPrimitiveCountAction,
 *    SoLevelOfSimplification,
 *    SoRenderList,
 *    SoValueOrdering,
 *    SoOcclusionCulling
 * 
 * 
 */ 

class INVENTOR_API SoOctreeOrdering : public SoRenderList 
{
  
  SO_NODE_HEADER(SoOctreeOrdering);
  
 public:

#ifdef OIV_NET_DOC
	 /**
	 * Default constructor. @BR
	 */

#else
	 /**
	 * Default constructor. @BR
	 * 
	 * Note: Do not modify an instance of this node or any of its children
	 * unless this node has a ref count greater than zero. If the
	 * node is itself the child of a grouping node then the ref
	 * count is automatically greater than zero, otherwise you must
	 * explicitly increment the ref count by calling the ref() method.   
	 */

#endif //OIV_NET_DOC
	 SoOctreeOrdering();
  
#ifdef OIV_NET_DOC
	 /**
	 * Constructor that takes approximate number of children as a hint. @BR
	 */

#else
	 /**
	 * Constructor that takes approximate number of children as a hint. @BR
	 * 
	 * Note: Do not modify an instance of this node or any of its children
	 * unless this node has a ref count greater than zero. If the
	 * node is itself the child of a grouping node then the ref
	 * count is automatically greater than zero, otherwise you must
	 * explicitly increment the ref count by calling the ref() method.   
	 */

#endif //OIV_NET_DOC
	 SoOctreeOrdering(int numChildren);
  
  // Fields
  /**
   * Enables culling of shapes that are too small on the screen.
   */
  SoSFBool dropCulling;
  
  /**
   * Sets threshold in pixels for drop culling and bounding box substitutes.
   */
  SoSFUInt32 dropScreenArea;

  /**
   * Enables use of bounding boxes for cells in the octree that contain shapes, but
   * would appear on the screen smaller than the dropScreenArea threshold. 
   */
  SoSFBool boundingBoxSubstitutes;

  /**
   * Sets how this node should handle moving render objects. If TRUE, then
   * the moving objects are kept in a separate render list, and are not sorted into
   * the octree, meaning that they will not be drop culled. If FALSE, moving
   * objects will be sorted into the octree after each motion, taking more time, but
   * enabling drop and view frustum culling for the moving objects.
   */
  SoSFBool useMovingQueue;

  /**
   * If TRUE, the octree will alter the decimation percentage for objects depending
   * on how large they are in the view. This causes objects closer to the camera to
   * appear in more detail than objects further away.
   */
  SoSFBool adjustDecimation;

  /**
   * This callback can be used to get render statistics: the number of objects in the
   * octree, and the number of objects actually rendered. If the application
   * is using an MP viewer, each render thread will call the callback function 
   * at the end of the octree traversal to let the application know how many objects
   * it rendered. This is useful to see how the rendering work is distributed across the 
   * threads.
   * [OIV-WRAPPER EVENT_NAME{ReportCallback}]
   */
  static void setReportCB(SoReportCB *func, void *userData);

  /**
   * Enables/disables octree drawing. Octree drawing will draw
   * outlines around the octree quadrants, allowing you to see 
   * how your scene is distributed throughout the octree. This
   * can be useful for debugging purposes.
   */
  void setOctreeDrawing(SbBool enable);

  /**
   * Returns TRUE if octree drawing is enabled.
   */
  SbBool isOctreeDrawing(void);

  /**
   * Returns TRUE if the octree is chained with another culling node.
   */
  SbBool isChainingOn(void) 
    { return (coworker != NULL); };

	/**
	 * If handle transparency is turned on, the octree will handle 
	 * transparency and render cache transparent objects. Default is TRUE;
	 */
	 void setHandleTransparency(SbBool handle);
	 SbBool getHandleTransparency();

	/**
	 * Allows to rebuild the octree from scratch.
	 */
	 void reset();

 SoEXTENDER public:
  // These implement supported actions
  virtual void getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void GLRenderBelowPath(SoGLRenderAction *action);
  virtual void rayPick(SoRayPickAction *action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);
  
 SoINTERNAL public:

  static void initClass();
  static void exitClass();
 
  // Set whether the bounding box is called from inside the octree code
  static SbBool m_internalGetBBox;

 protected:
	SbBool m_handleTransparency;
	SbBool m_reset;

  // Generic traversal of children, handles scene graph as if
  // this was just a SoSeparator node
  virtual void doStandardTraversal(SoAction *action);
  
  // Spatial traversal of children
  virtual void doSpatialTraversal(SoAction *action);
  
  // Virtual callbacks for when changes are made to the RenderObject list.
  virtual SoRenderObject *createRenderObject(const SoPath *path);
  virtual void removingRenderObject(SoRenderObject *);
  virtual void renderObjectChanged(SoRenderObject *);
  virtual void ourFieldChanged(SoField *);
  
  // Destructor
  virtual ~SoOctreeOrdering();
  
 private:
  
  static SoReportCB *m_reportCB;
  static void *m_reportUserData;
  
  // Common code for the two constructors:
  void commonConstructor();
  
  SoGetBoundingBoxAction *bbAction;
  SoGetPrimitiveCountAction *countAction;
  
  SbPList movingQueue;
  SbPList changeQueue;
  
  void insertInChangedQueue(void *);
  void updateChangedQueue();
  void updateRenderObject(SoOctreeRenderObject *);
  
  _SoOctreeRenderObjectTree *octreeTree;   
  
  SbThreadMutex *octreeMutex; 
  
  // number of objects to render
  int numObjects;  
  
  SbBool seeOctree; //used to draw the octree or not,
  
  // help function for spatial traversal
  float calculateDecimation(float,float);
  
  void renderTransparentObjs(SoAction *action, 
                             SoRenderObjectList *visibleTransparentObject);
  
  void handleMovingQueue(SoAction *action,SbBool);

  // Whether the environment variable is set
  SbBool isEnvOn;
};

#endif

