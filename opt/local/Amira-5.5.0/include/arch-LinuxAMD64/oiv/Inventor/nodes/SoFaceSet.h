/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_FACE_SET_
#define  _SO_FACE_SET_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/nodes/SoNonIndexedShape.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoFaceSet
//
//  Set of faces. Each face consists of 3 or more vertices, taken in
//  order from the current coordinates. The startIndex field gives the
//  starting coordinate index for the first face. The number of
//  vertices in each face is determined by successive entries in the
//  numVertices field.
//
//////////////////////////////////////////////////////////////////////////////

// This value, when used in the numVertices field, means that the
// corresponding face should use the rest of the vertices
#define SO_FACE_SET_USE_REST_OF_VERTICES        (-1)

class SoCoordinateElement;
class SoNormalBundle;
class SoState;
class SoVolumeFaceSet;

/**
 * Polygonal face shape node.
 *
 * @ingroup ShapeNodes
 *
 * @DESCRIPTION
 *   This node represents a 3D shape formed by constructing faces (polygons) from
 *   vertices located at the coordinates specified in the #vertexProperty field
 *   (from SoVertexShape), or the current inherited state. For optimal performance,
 *   the #vertexProperty field is recommended.
 *
 *   SoFaceSet is a general purpose polygon rendering node.  It can render 
 *   triangles, quadrilaterals, and other types of polygons or any combination thereof.
 *   SoFaceSet supports both convex and non-convex polygons (unlike OpenGL).
 *   However polygons are assumed to be convex by default. Rendering non-convex
 *   polygons in this mode may produce incorrect results.  Enable non-convex
 *   polygons using the faceType field of an SoShapeHints node.  In this mode
 *   SoFaceSet will automatically convert non-convex polygons, if necessary,
 *   to faces that the hardware can handle.  SoFaceSet can also directly
 *   handle complex polygons with "holes".  See the following paragraphs.  If your
 *   geometry is defined entirely by triangles it may be more convenient and more
 *   efficient to use an SoTriangleSet node.
 *
 *   If SoShapeHints is not used, or if the SoShapeHints::windingType field is equal to
 *   NO_WINDING_TYPE, SoFaceSet defines a set of faces. It uses the coordinates in order, starting with the first one.
 *   Each face
 *   has a number of vertices specified by a value in the #numVertices field.
 *   For example, an SoFaceSet with #numVertices of [3,4,4] would use
 *   coordinates 1, 2, and 3 for the first face, coordinates 4, 5, 6, and 7 for the
 *   second face, and coordinates 8, 9, 10, and 11 for the third. For improved
 *   performance, arrange all the faces with only 3 vertices at the beginning of the
 *   list, then all faces with 4 vertices, and finally all other faces.
 *   The number of values in the #numVertices field indicates the number of
 *   faces in the set.  The default value (-1) means to use all the coordinates
 *   to define a single face.
 *
 *   If SoShapeHints is used with a SoShapeHints::windingType field is different from NO_WINDING_TYPE,
 *   SoFaceSet defines a complex (multi-contour) face.
 *   It uses the coordinates in order, starting with the first one. Each contour has
 *   a number of vertices specified by a value in the #numVertices field.
 *   For example, an SoFaceSet with #numVertices of [3,4,4] would use
 *   coordinates 1, 2, and 3 for the first contour, coordinates 4, 5, 6, and 7 for the
 *   second contour, and coordinates 8, 9, 10, and 11 for the third.
 *   The number of values in the #numVertices field indicates the number of
 *   contours in the complex face.
 *
 *   The coordinates of the face set are transformed by the current cumulative
 *   transformation. The faces are drawn with the current light model and drawing
 *   style.
 *
 *   Treatment of the current material and normal binding is as follows: The PER_PART
 *   and PER_FACE bindings specify a material or normal for each face. The _INDEXED
 *   bindings are equivalent to their non-indexed counterparts. The default material
 *   binding is OVERALL. The default normal binding is PER_VERTEX.
 *
 *   If any normals (or materials) are specified, Open Inventor assumes you provide
 *   the correct number of them, as indicated by the binding. You will see unexpected
 *   results if you specify fewer normals (or materials) than the shape requires. If
 *   no normals are specified, they will be generated automatically.
 *
 *   NOTE: A face set may not render or pick correctly if any of its polygons are
 *   self-intersecting or non-planar.
 *
 *   OpenGL Vertex Arrays are used
 *     - if they are available, @I and@i
 *     - the environment variable IV_NO_VERTEX_ARRAY is not set, @I and@i
 *   
 *   OpenGL Vertex Buffer Objects, which speed up rendering of non-cached indexed shapes,
 *   can be used only if Vertex Arrays are used and the environment variable OIV_NO_VBO is not set. 
 *   See SoShapeHints::useVBO documentation for details.
 *
 * @FILE_FORMAT_DEFAULT
 *    FaceSet {
 *    @TABLE_FILE_FORMAT
 *       @TR vertexProperty   @TD NULL
 *       @TR startIndex       @TD 0
 *       @TR numVertices      @TD -1
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Draws faces based on the current coordinates, normals, materials, drawing
 *        style, and so on.
 *
 *    SoRayPickAction @BR
 *        Picks faces based on the current coordinates and transformation. Details about
 *        the intersection are returned in an SoFaceDetail.
 *
 *    SoGetBoundingBoxAction @BR
 *        Computes the bounding box that encloses all vertices of the face set with the
 *        current transformation applied to them. Sets the center to the average of the
 *        coordinates of all vertices.
 *
 *    SoCallbackAction @BR
 *        If any triangle callbacks are registered with the action, they will be invoked
 *        for each successive triangle generated from each face in the set.
 *
 *
 * @SEE_ALSO
 *    SoCoordinate3,
 *    SoDrawStyle,
 *    SoFaceDetail,
 *    SoFullSceneAntialiasing,
 *    SoIndexedFaceSet,
 *    SoShapeHints,
 *    SoTriangleSet,
 *    SoVertexProperty
 *
 */

class INVENTOR_API SoFaceSet : public SoNonIndexedShape {

  SO_NODE_HEADER(SoFaceSet);

 public:

  /**
   * Number of vertices per face or per contour.
   */
  SoMFInt32           numVertices;

  /**
   * Creates a face set node with default settings.
   */
  SoFaceSet();

 SoEXTENDER public:
  // Implement actions
  virtual void        GLRender(SoGLRenderAction *action);

  virtual void  getPrimitiveCount(SoGetPrimitiveCountAction *action);

  // Generates default normals using the given normal bundle.
  // Returns TRUE.
  virtual void      generateDefaultNormals(SoState *state,
                                            const SbVec3f *coords,
                                            int numCoords,
                                            SoNormalBundle *nb,
                                            SbBool storeRef = FALSE);

  // Compute transformations from Modelling coordinate to tangent space (facet space).
  virtual SbMatrix3* computeVtxTangentSpaceMat(const float *bumpTexCoords, int &numMat) const ;

 SoINTERNAL public:
  static void  initClass();
  static void  exitClass();

 protected:

  // This enum is used to indicate the current material or normal binding
  enum Binding {
    OVERALL, PER_FACE, PER_VERTEX
  };

  //shape must check shape hints in GlRender
  virtual SbBool shouldCheckShapeHints(){ return TRUE;}

  //Test function
  virtual SbBool shapeHintsTest(){ return (numQuads > 0 || numPolys > 0);}

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

  ~SoFaceSet();

SoINTERNAL public:
  // returns the number of PARTS
  inline int getNumParts(void) const { return numTris + numQuads + numPolys; } 

  // returns the number of FACES
  inline int getNumFaces(void) const { return numTris + numQuads + numPolys; } 

  // returns the number of vertices needed
  int getNumVerticesNeeded(void) { return totalNumVertices + startIndex.getValue(); }  

    // Checks if enough vertices, normals, textureCoord, colors...etc...
  bool check_RenderVectors( SoState *state, bool bUseTexCoordsAnyway );

  // set numTris/Quads/Faces to -1, checks SO_USE_REST_OF_VERTICES
  // when notified
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
  int     numTris, numQuads, numPolys, totalNumVertices;

  static const int AUTO_CACHE_FS_MIN_WITHOUT_VP;

  static const int AUTO_CACHE_FS_MAX;

  friend class SoVolumeFaceSetDl;
};

#endif /* _SO_FACE_SET_ */

