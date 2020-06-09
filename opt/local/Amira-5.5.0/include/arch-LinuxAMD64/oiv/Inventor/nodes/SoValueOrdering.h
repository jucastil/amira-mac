/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
/*---------------------------------------------------------------------
 *  Header file for "SoValueOrdering", 
 *   SoRenderList-derived group node.
 *
 *  Created: bga 31-March-97
 *  Modified:
 *------------------------------------------------------------*/


#ifndef _SO_VALUE_ORDERING_HH
#define _SO_VALUE_ORDERING_HH 1

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoRenderList.h>

class SoAlarmSensor;
class SoIdleSensor;

#ifndef HIDDEN_FROM_DOC
// Extend the SoRenderObject to contain the data we want to store
/** [OIV-WRAPPER-NO-WRAP] */
class INVENTOR_API SoValueRenderObject : public SoRenderObject {
 public:
  SoValueRenderObject(const SoPath* p) 
    : SoRenderObject(p) 
    { minTris = 0; numTris = 0; substitute = NULL; };
  
  virtual ~SoValueRenderObject() { 
    if (substitute!=NULL) { substitute->unref(); substitute = NULL; } };
  SbVec3f center;
  float   rad_sq;
  SbBox3f bbox;
  int32_t numTris, minTris;
  float   renderValue;
  SoNode  *substitute;
};
#endif // HIDDEN_FROM_DOC

/**
 * @VSGEXT Group node derived from SoRenderList that alters the decimation of shapes below
 * it depending on their rendering value as approximated by their size on the
 * screen. This makes it possible to render scenes with large numbers of shapes
 * without needing LOD nodes.
 * 
 * @ingroup GroupNodes LMV
 * 
 * @DESCRIPTION
 *   The SoValueOrdering node uses the functionality from SoRenderList to create a
 *   list of paths to the shapes beneath it. It then traverses the linear list and
 *   determines the rendering value and cost of each shape. The rendering value is
 *   based on the object's approximate screen size and its cost is based on a count
 *   of the number of primitives the shape contains.
 *   
 *   During each render traversal, the @B ValueOrdering @b node determines how many
 *   primitives a shape deserves based on its rendering value. If the shape contains
 *   multiple levels of detail, then the @B ValueOrdering @b node will choose the
 *   correct level of detail. However, this node also has two techniques that allow
 *   it to handle scenes that do not contain levels of detail: bounding box
 *   substitutes and drop culling. 
 *   
 *   With drop culling enabled, a user can specify a size in pixels such that when the
 *   shape is less than this size, the shape is not rendered.
 *   
 *   If bounding box substitutes are enabled and the @B ValueOrdering @b node
 *   calculates that the number of triangles that the object deserves is closer to 12
 *   (the number of triangles in a bounding box) than to the minimum number of
 *   triangles the shape can draw, then the @B ValueOrdering @b node will draw a
 *   bounding box instead of the shape.
 *   
 *   If decimate substitutes are enabled, then the @B ValueOrdering @b will apply an
 *   SoGlobalSimpifyAction to shapes that it determines need simplification.
 *   Sometimes a shape has so many triangles that neither the bounding box nor the
 *   shape is a satisfactory choice given the shape's calculated value. In this case,
 *   the @B ValueOrdering @b will create and use a simplified version. The
 *   simplification is done when Inventor has been idle for over a second.
 *   
 *   If low value culling is enabled, then the shape will not be rendered if the
 *   @B ValueOrdering @b node decides that its value in triangles is not even worth
 *   rendering a bounding box. This will happen if the decimation percentage value is
 *   set very low.
 *   
 *   The typical scenario where this node is useful is in CAD model assembly viewing,
 *   where all or most of the scene is visible, but lots of details may be so small
 *   that there is no point in drawing them until the user zooms in on them.
 *   Replacing such detail with its bounding box is adequate in many cases and does
 *   not have the disk and memory costs, along with the preprocessing time,
 *   associated with maintaining multiple levels of detail.
 *
 * @FILE_FORMAT_DEFAULT
 *    ValueOrdering {
 *    @TABLE_FILE_FORMAT
 *       @TR dropCulling              @TD TRUE
 *       @TR dropScreenArea           @TD 5
 *       @TR boundingBoxSubstitutes   @TD TRUE
 *       @TR decimateSubstitutes      @TD TRUE
 *       @TR lowValueCulling          @TD TRUE
 *       @TR adjustDecimation         @TD TRUE
 *       @TR isHead                   @TD TRUE
 *       @TR renderCaching            @TD AUTO
 *       @TR boundingBoxCaching       @TD AUTO
 *       @TR renderCulling            @TD AUTO
 *       @TR pickCulling              @TD AUTO
 *       @TR fastEditing              @TD DISABLE
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoGetPrimitiveCountAction @BR
 *        Uses value calculation to influence traversal. All other actions use standard
 *        SoSeparator traversal.
 * 
 * 
 * @SEE_ALSO
 *    SoGetPrimitiveCountAction,
 *    SoLevelOfSimplification,
 *    SoOctreeOrdering,
 *    SoRenderList
 * 
 * 
 */ 

class INVENTOR_API SoValueOrdering : public SoRenderList {

  SO_NODE_HEADER(SoValueOrdering);

 public:
#ifdef OIV_NET_DOC
	 /**
	 * Default constructor. @BR
	 *
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
	 SoValueOrdering();

#ifdef OIV_NET_DOC
	 /**
	 * Constructor that takes approximate number of children as a hint. @BR
	 *
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
	 SoValueOrdering(int numChildren);
   
  // Fields
  /**
   * Enables culling of shapes that are too small on the screen.
   * 
   */
  SoSFBool dropCulling;
  /**
   * Sets threshold in pixels for drop culling.
   * 
   */
  SoSFUInt32 dropScreenArea;
  /**
   * Allows @B ValueOrdering @b node to adjust decimation percentage value depending
   * on the shape's rendering value.
   * 
   */
  SoSFBool adjustDecimation;
  /**
   * Enables use of bounding boxes for shapes whose rendering value is too low to
   * render the shape itself. 
   * 
   */
  SoSFBool boundingBoxSubstitutes;
  /**
   * If true, then this node will automatically decide when a decimated version of a
   * shape needs to be created. It will apply an SoGlobalSimplifyAction, and use the
   * results instead of the shape when needed.
   * 
   */
  SoSFBool decimateSubstitutes;
  /**
   * Enables culling of shapes whose rendering value is too low.
   * 
   */
  SoSFBool lowValueCulling;
    
 SoEXTENDER public:
  // These implement supported actions
  virtual void  getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void  GLRenderBelowPath(SoGLRenderAction *action);
  virtual void  pick(SoPickAction *action);
  virtual void  getPrimitiveCount(SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  // Generic traversal of children, handles scene graph as if
  // this was just a SoSeparator node
  virtual void  doStandardTraversal(SoAction *action);
 
  // Spatial traversal of children
  virtual void  doSpatialTraversal(SoAction *action);
  
  // Virtual callbacks for when changes are made to the RenderObject list.
  virtual SoRenderObject *createRenderObject(const SoPath *path);
  virtual void removingRenderObject(SoRenderObject *);
  virtual SbBool isFieldChangeImportant(SoNode *triggerNode,
                                        SoField* triggerField);
  virtual void renderObjectChanged(SoRenderObject *);
  virtual void ourFieldChanged(SoField *);

 protected:
  // Destructor
  virtual ~SoValueOrdering();

 private:
  // Common code for the two constructors:
  void commonConstructor();
 
  SoGetBoundingBoxAction *bbAction;
  SoGetPrimitiveCountAction *countAction;
    
  SbPList changeQueue;
  void insertInChangedQueue(void*);
  void updateChangedQueue();
  void updateRenderObject(SoValueRenderObject*);
    
  int32_t totalTris;
  double maxError;
  SbIntList needsDecimating;
  SoAlarmSensor *decimateIdle;
  static void decimateIdleCB(void* data, SoSensor*) {
    ((SoValueOrdering*)data)->decimateMaxError(); };
  void decimateMaxError();
    
};

#endif

