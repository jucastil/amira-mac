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


#ifndef  _SO_TRIANGLE_STRIP_SET_
#define  _SO_TRIANGLE_STRIP_SET_

#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/nodes/SoNonIndexedShape.h>
#include <Inventor/nodes/SoVertexProperty.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTriangleStripSet
//
//  Triangle strip set node. Each strip in the set consists of n
//  vertices located at consecutive entries in the current
//  coordinates. The startIndex field gives the starting coordinate
//  index for the first strip. If materials or normals are bound to
//  vertices, they will begin at that index, as well; otherwise, they
//  will start at index 0.  The number of vertices in each strip is
//  determined by successive entries in the numVertices field.
//
//////////////////////////////////////////////////////////////////////////////

class SoCoordinateElement;
class SoVolumeTriangleStripSet;

#ifndef IV_STRICT
// Deprecated feature; specifying USE_REST_OF_VERTICES as the last
// value in the numVertices field will use all the points in the
// coordinate array.
#define SO_TRI_STRIP_SET_USE_REST_OF_VERTICES   (-1)
#endif

/**
 * Triangle strip set shape node.
 *
 * @ingroup ShapeNodes
 *
 * @DESCRIPTION
 *   This shape node constructs triangle strips out of vertices. The vertices may be
 *   specified in the #vertexProperty field (from SoVertexShape), or by the
 *   current inherited coordinates. For optimal performance, the
 *   #vertexProperty field is recommended.
 *
 *   SoTriangleStripSet is one of the fastest ways of drawing polygonal objects in
 *   Open Inventor. It uses the current coordinates, in order, starting with the
 *   first one. The values in the #numVertices field indicate the number of
 *   vertices to use for each triangle strip in the set. The number of values in this
 *   field determines the number of strips.
 *
 *   For example, if #numVertices has the values [3,5], coordinates 1, 2, and 3
 *   would be used for the first triangle strip and coordinates 4, 5, 6, 7, and 8
 *   would be used for the second strip. This would result in 1 triangle in the first
 *   strip and 3 in the second.
 *
 *   The coordinates of the strips are transformed by the current cumulative
 *   transformation. The strips are drawn with the current light model and drawing
 *   style.
 *
 *   Treatment of the current material and normal binding is as follows: The PER_PART
 *   binding specifies a material or normal for each strip of the set. The PER_FACE
 *   binding specifies a material or normal for each triangle. The _INDEXED bindings
 *   are equivalent to their non-indexed counterparts. The default normal binding is
 *   PER_VERTEX. The default material binding is OVERALL.
 *
 *   If any normals (or materials) are specified, Open Inventor assumes you provide
 *   the correct number of them, as indicated by the binding. You will see unexpected
 *   results if you specify fewer normals (or materials) than the shape requires. If
 *   no normals are specified, they will be generated automatically.
 *
 *   To render triangles that are not in strips, see the SoTriangleSet node.
 *
 * @FILE_FORMAT_DEFAULT
 *    TriangleStripSet {
 *    @TABLE_FILE_FORMAT
 *       @TR vertexProperty   @TD NULL
 *       @TR startIndex       @TD 0
 *       @TR numVertices      @TD -1
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Draws a strip set based on the current coordinates, normals, materials, drawing
 *        style, and so on.
 *
 *    SoRayPickAction @BR
 *        Picks on the strip set based on the current coordinates and transformation.
 *        Details about the intersection are returned in an SoFaceDetail.
 *
 *    SoGetBoundingBoxAction @BR
 *        Computes the bounding box that encloses all vertices of the strip set with the
 *        current transformation applied to them. Sets the center to the average of the
 *        coordinates of all vertices.
 *
 *    SoCallbackAction @BR
 *        If any triangle callbacks are registered with the action, they will be invoked
 *        for each successive triangle forming the strips of the set.
 *
 *
 * @SEE_ALSO
 *    SoCoordinate3,
 *    SoDrawStyle,
 *    SoFaceDetail,
 *    SoFaceSet,
 *    SoFullSceneAntialiasing,
 *    SoIndexedTriangleStripSet,
 *    SoQuadMesh,
 *    SoTriangleSet,
 *    SoVertexProperty
 *
 *
 */

class INVENTOR_API SoTriangleStripSet : public SoNonIndexedShape {

  SO_NODE_HEADER(SoTriangleStripSet);

 public:
  // Fields
  /**
   * Number of vertices in each triangle strip. The number of strips is equal to the
   * number of values in this field.
   */
  SoMFInt32 numVertices;

  /**
   * Creates a triangle strip set node with default settings.
   */
  SoTriangleStripSet();

 SoEXTENDER public:
  /**
   * Implement SoGLRenderAction actions
   */
  virtual void GLRender(SoGLRenderAction *action);

  /**
   * Generates default normals using the given normal bundle.
   * Returns TRUE.
   */
  virtual void      generateDefaultNormals(SoState *state,
                                            const SbVec3f *coords,
                                            int numCoords,
                                            SoNormalBundle *nb,
                                            SbBool storeRef = FALSE);

  /**
   * Implement SoGetPrimitiveCountAction actions
   */
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  // returns the number of PARTS
  inline int getNumStrips(void) const { return numVertices.getNum(); }

  // returns the number of PARTS
  inline int getNumParts(void) const { return getNumStrips(); }// PARTS are strips   

  // returns the number of FACES
  inline int getNumFaces(void) const { return totalNumVertices - 2 * getNumStrips(); } // FACES are triangles 

  // returns the number of vertices needed
  int getNumVerticesNeeded(void) { return totalNumVertices + startIndex.getValue(); }  

  // Checks if enough vertices, normals, textureCoord, colors...etc...
  bool check_RenderVectors( SoState *state, bool bUseTexCoordsAnyway );



  static void initClass();
  static void exitClass();

  //Typedef of pointer to method on TriangleStripSet;
  //This will be used to simplify declaration and initialization.
  typedef void (SoTriangleStripSet::*PMTSS)(SoGLRenderAction *);

  // Compute transformations from Modelling coordinate to tangent space (facet space).
  virtual SbMatrix3* computeVtxTangentSpaceMat(const float *bumpTexCoords, int &numMat) const ;

 protected:

  // Generates triangles representing strips
  virtual void generatePrimitives(SoAction *action);

  SbBool m_usingUSE_REST;

  SbBool m_nvNotifyEnabled;

  void setNvNotifyEnabled(SbBool nvNotifyEnabled)
  {
    m_nvNotifyEnabled = nvNotifyEnabled;
  }

  SbBool getNvNotifyEnabled(){return m_nvNotifyEnabled;}

  //Free memory
  virtual void exitRender(SoState *state,int stateFlag,
                  SoTextureCoordinateBundle *tcb,
                  SoTextureCoordinate3Bundle *tc3b);

  virtual void callDEBUGGLRender(SoGLRenderAction *action,uint32_t useTexCoordsAnyway);

  virtual int getNumPrim(){return totalNumVertices;}

  // count primitives
  virtual void countPrim();

  // return num vertices for test
  virtual int getNumVert();

  // auto caching test
  virtual int getMaxTestValueForAutoCache(){return totalNumVertices;}

  // auto caching test
  virtual int getMinTestValueForAutoCache(){return totalNumVertices;}

  // invalid test
  virtual SbBool numPrimInvalid(){return totalNumVertices < 0 ;}
  
  // render function
  void doRendering(SoGLRenderAction *action, const SoShapeStyleElement* shapeStyle);

  // Overrides standard method to create an SoFaceDetail instance
  virtual SoDetail *createTriangleDetail(SoRayPickAction *action,
                                         const SoPrimitiveVertex *v1,
                                         const SoPrimitiveVertex *v2,
                                         const SoPrimitiveVertex *v3,
                                         SoPickedPoint *pp);

  virtual ~SoTriangleStripSet();

SoINTERNAL public:
  // Blow vpCache when vertexProperty field changes:
  virtual void notify(SoNotList *list);

private:
  // This stores the total number of vertices; we use this
  // information to influence Separator's auto-caching algorithm
  // (shapes with very few triangles should be cached because
  // traversing them can be expensive, shapes with lots of triangles
  // shouldn't be cached because they'll take up too much memory).
  int totalNumVertices;

  static const int AUTO_CACHE_TSS_MIN_WITHOUT_VP;
  static const int AUTO_CACHE_TSS_MAX;

  friend class SoVolumeTriangleStripSetDl;
};

#endif /* _SO_TRIANGLE_STRIP_SET_ */
