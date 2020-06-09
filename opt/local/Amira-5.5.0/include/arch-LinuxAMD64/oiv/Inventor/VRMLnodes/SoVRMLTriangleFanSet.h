/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_VRMLTRIANGLE_FAN_SET_
#define  _SO_VRMLTRIANGLE_FAN_SET_

#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/VRMLnodes/SoVRMLVertexShape.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLTriangleFanSet
//
// A SoVRMLTriangleFanSet represents a 3D shape composed of triangles 
// that form a fan shape around the first vertex declared in each fan.
//
//////////////////////////////////////////////////////////////////////////////

class SoCoordinateElement;

#ifndef IV_STRICT
// Deprecated feature; specifying USE_REST_OF_VERTICES as the last
// value in the numVertices field will use all the points in the
// coordinate array.
#define SO_TRI_STRIP_SET_USE_REST_OF_VERTICES   (-1)
#endif

/**
 * Triangle fan set shape node.\ @NO_ACTION
 * 
 * @ingroup X3D
 * 
 * @DESCRIPTION
 *   See the X3D Specification, below.
 *
 * @VRMLX3D_SPECIFICATION
 *   This section describes the expected behavior of the node in a conforming X3D
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the X3D specification that are not
 *   present in this help file. The complete X3D spec is available at
 *   @B http://www.web3d.org @b.
 *
 *   An SoVRMLTriangleFanSet represents a 3D shape composed of triangles that form a fan 
 *   shape around the first vertex declared in each fan. 
 *
 *   The #fanCount field describes how many vertices are to be used in each fan from the 
 *   #coordinate field. Coordinates are assigned to each strip by taking #fanCount[n] vertices 
 *   from the #coordinate field. Each value of the #fanCount array must be greater than or equal
 *   to three. It is an error to have a value less than three.
 *
 *   The following figure displays a TriangleFanSet containing a single fan showing the
 *   ordering of the vertices for that fan.
 *
 *   @IMAGE TriangleFanSet.jpg
 *   
 *   The SoVRMLTriangleFanSet node is specified in the local coordinate system and is affected 
 *   by the transformations of its ancestors. Descriptions of the #color, #coord, #normal, and 
 *   #texCoord fields are provided in the Color, Coordinate, Normal, and TextureCoordinate nodes, 
 *   respectively. If values are provided for the #color, #normal, and #texCoord fields, there must 
 *   be at least as many values as are present in the #coord field. The value of the #colorPerVertex 
 *   field is ignored and always treated as TRUE. If the #normal field is not provided, for each 
 *   fan, the normal will be generated as follows: if #normalPerVertex is TRUE, the normal will 
 *   be the average of all triangles within that fan sharing that vertex. For the vertex of the fan, 
 *   the normal will be the average of the contributions of all of the individual face normals. 
 *   If #normalPerVertex is FALSE, the normal will be generated for the current triangle based 
 *   on the ccw field.
 *   
 *   The #solid field determines whether the SoVRMLTriangleFanSet is visible when viewed from 
 *   the inside.
 *   
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLTriangleFanSet {
 *    @TABLE_FILE_FORMAT
 *       @TR color             @TD NULL
 *       @TR coord             @TD NULL
 *       @TR normal            @TD NULL
 *       @TR texCoord          @TD NULL
 *       @TR fanCount          @TD []
 *       @TR ccw               @TD TRUE
 *       @TR colorPerVertex    @TD TRUE
 *       @TR normalPerVertex   @TD TRUE
 *       @TR solid             @TD TRUE
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoRayPickAction,  SoGetBoundingBoxAction,  SoCallbackAction  @BR
 *
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR SoSFNode   @TD set_color  
 *       @TR SoSFNode   @TD set_coord    
 *       @TR SoMFInt32  @TD set_fanCount 
 *       @TR SoSFNode   @TD set_normal  
 *       @TR SoSFNode   @TD set_texCoord
 *       @TR   SoSFNode   @TD   set_metadata    
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR SoSFNode   @TD color_changed 
 *       @TR SoSFNode   @TD coord_changed    
 *       @TR SoMFInt32  @TD fanCount_changed 
 *       @TR SoSFNode   @TD normal_changed  
 *       @TR SoSFNode   @TD texCoord_changed
 *       @TR   SoSFNode   @TD   metadata_changed    
 *    @TABLE_END
 *
 * 
 */ 


class INVENTOR_API SoVRMLTriangleFanSet : public SoVRMLVertexShape {
  
  SO_NODE_HEADER(SoVRMLTriangleFanSet);
  
 public:
  // Fields
  /**
   * Number of vertices in each triangle strip. The number of strips is equal to the
   * number of values in this field.
   */
  SoMFInt32        fanCount;
  /**
   * Indicates whether the vertices are ordered in a counterclockwise direction when
   * viewed from the outside (TRUE) or in a clockwise direction (FALSE).
   * 
   */
  SoSFBool            ccw;
  /**
   * If you know that the shape encloses a volume, set this value to TRUE. 
   * Then backface culling will be performed. 
   * 
   */
  SoSFBool            solid;

  /**
   * Creates a triangle strip set node with default settings.
   */
  SoVRMLTriangleFanSet();
  
 SoEXTENDER public:
  // Implement actions
  virtual void GLRender(SoGLRenderAction *action);
  
  // Generates default normals using the given normal bundle. 
  // Returns TRUE.
  virtual SbBool generateDefaultNormals(SoState *state, SoNormalBundle *nb);
  
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);
  
  // Computes bounding box of triangle strips
  virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);
  
 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  
  //Typedef of pointer to method on TriangleStripSet;
  //This will be used to simplify declaration and initialization.
  typedef void (SoVRMLTriangleFanSet::*PMTSS)(SoGLRenderAction *);
  
  // Compute transformations from Modelling coordinate to tangent space (facet space).
 // virtual SbMatrix3* computeVtxTangentSpaceMat(const float *bumpTexCoords, int &numMat) const ;

 protected:
  // Generates triangles representing strips
  virtual void generatePrimitives(SoAction *action);
  
  // Overrides standard method to create an SoFaceDetail instance
  virtual SoDetail *createTriangleDetail(SoRayPickAction *action,
                                         const SoPrimitiveVertex *v1,
                                         const SoPrimitiveVertex *v2,
                                         const SoPrimitiveVertex *v3,
                                         SoPickedPoint *pp);
  
  virtual ~SoVRMLTriangleFanSet();
  
 private:
  // Blow vpCache when vertexProperty field changes:
  virtual void notify(SoNotList *list);

  // This stores the total number of vertices; we use this
  // information to influence Separator's auto-caching algorithm
  // (shapes with very few triangles should be cached because
  // traversing them can be expensive, shapes with lots of triangles
  // shouldn't be cached because they'll take up too much memory).
  int totalFanCount;
  
  // render function
  void doRendering(SoGLRenderAction *action, const SoShapeStyleElement* shapeStyle);
  
  static const int AUTO_CACHE_TSS_MIN_WITHOUT_VP;
  static const int AUTO_CACHE_TSS_MAX;
  };

#endif /* _SO_VRMLTRIANGLE_FAN_SET_ */
