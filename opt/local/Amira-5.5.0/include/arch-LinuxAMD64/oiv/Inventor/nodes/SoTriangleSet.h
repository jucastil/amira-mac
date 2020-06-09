/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Mar 2011)
** Modified by : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _SO_TRIANGLE_SET_
#define  _SO_TRIANGLE_SET_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/nodes/SoNonIndexedShape.h>

// This value, when used in the numTriangles field, means that the
// corresponding set should use the rest of the vertices
#define SO_TRIANGLE_SET_USE_REST_OF_VERTICES        (-1)

class SoCoordinateElement;
class SoNormalBundle;
class SoState;
class SoVolumeTriangleSet;

//@TOBEWRAPPED
/**
 * Set of triangles shape node.
 *
 * @ingroup ShapeNodes
 *
 * @DESCRIPTION
 *   This node represents a 3D shape defined by a set of triangles.
 *
 *   This shape node constructs triangles from the vertices located at the coordinates 
 *   specified in the #vertexProperty field (from SoVertexShape), or the current 
 *   inherited state. For optimal performance, the #vertexProperty field is recommended.
 *
 *   Each triangle is defined by three vertices, starting at the beginning of the
 *   vertex list.  The #numTriangles field specifies the number of triangles in the 
 *   set.  By default all vertices are used, in other words the number of triangles
 *   is the number of vertices divided by three.  Setting numTriangles to zero means
 *   there are no triangles in the set (the bounding box is empty and so on).  An
 *   error message is generated in the debug build if there are not enough vertices
 *   to make the specified number of triangles.
 *
 *   The coordinates of the triangle set are transformed by the current cumulative
 *   transformation. The triangles are drawn with the current light model and drawing
 *   style.
 *
 *   Treatment of the current material and normal binding is as follows: The PER_PART
 *   and PER_FACE bindings specify a material or normal for each triangle. The _INDEXED
 *   bindings are equivalent to their non-indexed counterparts. The default material
 *   binding is OVERALL. The default normal binding is PER_VERTEX.
 *
 *   If any normals (or materials) are specified, Open Inventor assumes you provide
 *   the correct number of them, as indicated by the binding. You will see unexpected
 *   results if you specify fewer normals (or materials) than the shape requires. If
 *   no normals are specified, they will be generated automatically.
 *
 *   OpenGL Vertex Arrays are used
 *     - if they are available, @I and@i
 *     - the environment variable IV_NO_VERTEX_ARRAY is not set, @I and@i
 *   
 *   OpenGL Vertex Buffer Objects, which speed up rendering of non-cached indexed shapes,
 *   can be used only if Vertex Arrays are used and the environment variable OIV_NO_VBO is not set. 
 *   See SoShapeHints::useVBO documentation for details.
 *
 *   @NODE_SINCE_OIV 8.6
 *
 * @FILE_FORMAT_DEFAULT
 *    TriangleSet {
 *    @TABLE_FILE_FORMAT
 *       @TR vertexProperty   @TD NULL
 *       @TR startIndex       @TD 0
 *       @TR numTriangles     @TD -1
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Draws triangles based on the current coordinates, normals, materials, drawing
 *        style, and so on.
 *
 *    SoRayPickAction @BR
 *        Picks triangles based on the current coordinates and transformation. Details about
 *        the intersection are returned in an SoFaceDetail.
 *
 *    SoGetBoundingBoxAction @BR
 *        Computes the bounding box that encloses all vertices of the triangle set with the
 *        current transformation applied to them. Sets the center to the average of the
 *        coordinates of all vertices.
 *
 *    SoCallbackAction @BR
 *        If any triangle callbacks are registered with the action, they will be invoked
 *        for each successive triangle generated from each triangle in the set.
 *
 *
 * @SEE_ALSO
 *    SoCoordinate3,
 *    SoDrawStyle,
 *    SoIndexedTriangleSet,
 *    SoFaceDetail,
 *    SoFullSceneAntialiasing,
 *    SoVertexProperty,
 *    SoShapeHints
 *
 *
 */

class INVENTOR_API SoTriangleSet : public SoNonIndexedShape {

  SO_NODE_HEADER(SoTriangleSet);

 public:

  /**
   * Number of triangles in the set.
   * Default is SO_TRIANGLE_SET_USE_REST_OF_VERTICES, meaning to use all the vertices 
   * given, so the number of triangles is number of vertices divided by 3.
   */
  SoSFInt32 numTriangles;

  /**
   * Creates a triangle set node with default settings.
   */
  SoTriangleSet();

 SoEXTENDER public:
  // Implement actions

  /** @copydoc SoNonIndexedShape::GLRender */
  virtual void        GLRender(SoGLRenderAction *action);

  /** @copydoc SoNonIndexedShape::getPrimitiveCount */
  virtual void  getPrimitiveCount(SoGetPrimitiveCountAction *action);

  /** @copydoc SoNonIndexedShape::generateDefaultNormals */
  virtual void  generateDefaultNormals(SoState *state,
    const SbVec3f *coords,
    int numCoords,
    SoNormalBundle *nb,
    SbBool storeRef = FALSE);

  /** @copydoc SoNonIndexedShape::computeVtxTangentSpaceMat */
  virtual SbMatrix3* computeVtxTangentSpaceMat(const float *bumpTexCoords, int &numMat) const ;

 SoINTERNAL public:
  // returns the number of PARTS
  inline int getNumParts(void) const { return numTris; } // PARTS are Triangles

  // returns the number of FACES
  inline int getNumFaces(void) const { return numTris; } // FACES are Triangles

  // returns the number of vertices needed
  int getNumVerticesNeeded(void) { return totalNumVertices + startIndex.getValue(); }  

  // Checks if enough vertices, normals, textureCoord, colors...etc...
  bool check_RenderVectors( SoState *state, bool bUseTexCoordsAnyway );

  /** @copydoc SoNonIndexedShape::initclass */
  static void  initClass();

  /** @copydoc SoNonIndexedShape::exitClass */
  static void  exitClass();

 protected:

  // This enum is used to indicate the current material or normal binding
  enum Binding {
    OVERALL, PER_FACE, PER_VERTEX
  };

  virtual void callDEBUGGLRender(SoGLRenderAction *action,uint32_t useTexCoordsAnyway);

  //Free memory
  virtual void exitRender(SoState *state,int stateFlag,
                  SoTextureCoordinateBundle *tcb,
                  SoTextureCoordinate3Bundle *tc3b);

  // keep track of whether we are using USE_REST_OF_VERTICES
  SbBool m_usingUSE_REST;

  SbBool m_nvNotifyEnabled;

  void setNvNotifyEnabled(SbBool _nvNotifyEnabled)
  {
    m_nvNotifyEnabled = _nvNotifyEnabled;
  }

  SbBool getNvNotifyEnabled(){return m_nvNotifyEnabled;}

  virtual int getMaxTestValueForAutoCache(){return totalNumVertices;}

  virtual int getMinTestValueForAutoCache(){return totalNumVertices;}

  virtual int getNumPrim(){return totalNumVertices;}

  virtual int getNumVert();

  virtual void countPrim(){setupNumTrisQuadsFaces();}

  virtual SbBool numPrimInvalid(){return numTris < 0 ;}

  // Generates triangles representing faces
  virtual void        generatePrimitives(SoAction *action);

  // render function
  void doRendering(SoGLRenderAction *action, const SoShapeStyleElement* shapeStyle);

  // Overrides standard method to create an SoFaceDetail instance
  virtual SoDetail *  createTriangleDetail(SoRayPickAction *action,
                                           const SoPrimitiveVertex *v1,
                                           const SoPrimitiveVertex *v2,
                                           const SoPrimitiveVertex *v3,
                                           SoPickedPoint *pp);

  /** Destructor */
  ~SoTriangleSet();

SoINTERNAL public:
  // reset numTris to -1, to rechecks SO_USE_REST_OF_VERTICES usage when notified
  virtual void        notify(SoNotList *list);

 private:
  
  // used internally by doRendering
  // return true if shape was correctly drawn.
  bool doRenderingVBO(SoGLRenderAction *action, const SoShapeStyleElement* shapeStyle);

  // Returns current material or normal binding from action's state
  static Binding getMaterialBinding(SoAction *action);
  Binding getNormalBinding(SoAction *action, SoNormalBundle *nb);

   virtual int getNumNeededNormals(SoState *state);

  // Set number of triangles/quads/faces, based on coordIndex array.
  void setupNumTrisQuadsFaces();

  // Number of triangles, quads, (n>4)-vertex faces, total vertices
  int     numTris, totalNumVertices;

  friend class SoVolumeTriangleSetDl;
};

#endif /* _SO_TRIANGLE_SET_ */

