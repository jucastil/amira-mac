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

#ifndef  _SO_VRMLINDEXEDTRIANGLE_STRIP_SET_
#define  _SO_VRMLINDEXEDTRIANGLE_STRIP_SET_

#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/VRMLnodes/SoVRMLTriangle.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLIndexedTriangleStripSet
//
// An SoVRMLIndexedTriangleStripSet represents a 3D shape composed of strips
// of triangles. 
//
//////////////////////////////////////////////////////////////////////////////

#ifndef IV_STRICT
// Deprecated feature; specifying USE_REST_OF_VERTICES as the last
// value in the numVertices field will use all the points in the
// coordinate array.
#define SO_TRI_STRIP_SET_USE_REST_OF_VERTICES   (-1)
#endif

class SoCoordinateElement;

/**
 * Indexed triangle strip set shape node.\ @NO_ACTION
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
 *   An SoVRMLIndexedTriangleStripSet represents a 3D shape composed of 
 *   strips of triangles as depicted in the following figure.
 *
 *   @IMAGE TriangleStripSet.gif
 *
 *   SoVRMLIndexedTriangleStripSet uses the indices in its #index field 
 *   to specify the triangle strips by connecting vertices from the #coord 
 *   field. An index of "-1" indicates that the current strip has ended 
 *   and the next one begins. The last strip may be (but does not have to be) 
 *   followed by a "-1". Each strip must have at least three non-coincident 
 *   vertices.
 *
 *   The SoVRMLIndexedTriangleStripSet node is specified in the local 
 *   coordinate system and is affected by the transformations of its 
 *   ancestors. Descriptions of the #color, #coord, #normal, and #texCoord 
 *   fields are provided in the SoVRMLColor, SoVRMLCoordinate, SoVRMLNormal, 
 *   and SoVRMLTextureCoordinate nodes, respectively. If values are 
 *   provided for the #color, #normal, and #texCoord fields, the values are 
 *   applied in the same manner as the values from the #coord field and 
 *   there must be at least as many values as are present in the #coord 
 *   field. The value of the #colorPerVertex field is ignored and always 
 *   treated as TRUE. If the #normal field is not provided, normals will 
 *   be generated as follows:
 *   
 *   If #normalPerVertex is TRUE, the normal for each vertex will be the 
 *   average of the normals for all triangles sharing that vertex. 
 *   
 *   If #normalPerVertex is FALSE, the normal will be generated for the 
 *   current triangle based on the #ccw field. 
 *   
 *   The #solid field determines whether the IndexedTriangleStripSet is visible 
 *   when viewed from the inside.
 *
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLIndexedTriangleStripSet {
 *    @TABLE_FILE_FORMAT
 *       @TR color             @TD NULL
 *       @TR coord             @TD NULL
 *       @TR normal            @TD NULL
 *       @TR texCoord          @TD NULL
 *       @TR ccw               @TD TRUE
 *       @TR colorPerVertex    @TD TRUE
 *       @TR normalPerVertex   @TD TRUE
 *       @TR solid             @TD TRUE
 *       @TR index             @TD []
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
 *       @TR   SoMFInt32   @TD   set_index      
 *       @TR   SoSFNode   @TD   set_color      
 *       @TR   SoSFNode   @TD   set_coord      
 *       @TR   SoSFNode   @TD   set_normal      
 *       @TR   SoSFNode   @TD   set_texCoord
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode   @TD   color_changed      
 *       @TR   SoSFNode   @TD   coord_changed      
 *       @TR   SoSFNode   @TD   normal_changed      
 *       @TR   SoSFNode   @TD   texCoord_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 

 * 
 */ 
class INVENTOR_API SoVRMLIndexedTriangleStripSet : public SoVRMLTriangle {
  
  SO_NODE_HEADER(SoVRMLIndexedTriangleStripSet);
  
 public:
  // Fields
  /**
   * Indices used to specify the triangle strips.
   */
  SoMFInt32            index;
  /**
   * Creates an indexed triangle strip set node with default settings.
   */
  SoVRMLIndexedTriangleStripSet();
  
 SoEXTENDER public:
  // Implement actions
  virtual void GLRender(SoGLRenderAction *action);
  virtual void        generatePick(SoRayPickAction *action, SoNode *node);
  // Generates default normals using the given normal bundle. 
  // Returns TRUE.
  virtual SbBool generateDefaultNormals(SoState *state, SoNormalBundle *nb);
  
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);
  
  // Computes bounding box of triangle strips
  virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);
  
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

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
  
  virtual ~SoVRMLIndexedTriangleStripSet();
  
 private:
  // Blow vpCache when vertexProperty field changes:
  virtual void notify(SoNotList *list);

  // render function
  void doRendering(SoGLRenderAction *action, const SoShapeStyleElement* shapeStyle);
  
  static const int AUTO_CACHE_TSS_MIN_WITHOUT_VP;
  static const int AUTO_CACHE_TSS_MAX;
  };

#endif /* _SO_VRMLINDEXEDTRIANGLE_STRIP_SET_ */
