/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Thierry Dufour (Nov 2002)
**=======================================================================*/

#ifndef  _SO_INDEXED_QUAD_MESH_
#define  _SO_INDEXED_QUAD_MESH_

#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/nodes/SoIndexedShape.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoIndexedQuadMesh
//
//  Shape node with implicit quadrilateral connectivity. The number of
//  vertices in each row and column of the quadMesh is given by the
//  verticesPerRow and verticesPerColumn fields. The current
//  coordinates are taken in order (starting at startIndex) to form
//  the rows of the quadMesh; i.e., the first verticesPerColumn vertices
//  form the first row of the quadMesh, the next verticesPerColumn
//  vertices form the next row, and so on. It is an error if there are
//  not enough coordinates. If materials or normals are bound to
//  vertices, they will begin at startIndex, as well; otherwise, they
//  will start at index 0.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Indexed quadrilateral mesh shape node.
 * 
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 *   This shape node constructs quadrilaterals out of vertices. The vertices may be
 *   specified in the #vertexProperty field (from SoVertexShape), or by the
 *   current inherited coordinates. For optimal performance, the
 *   #vertexProperty field is recommended.
 *
 *   SoIndexedQuadMesh uses the indices in the #coordIndex field, in order, starting
 *   with the first one. The number of vertices in the columns and rows of the mesh
 *   are specified by the #verticesPerColumn and #verticesPerRow fields. (Note that
 *   these numbers are 1 greater than the number of quadrilaterals per row and per
 *   column.)
 *   
 *   For example, an SoIndexedQuadMesh with #verticesPerColumn of 3, and
 *   #verticesPerRow of 4 would use coordinates 1, 2, 3, and 4 for the first
 *   row of vertices, coordinates 5, 6, 7, and 8 for the second row, and coordinates
 *   9, 10, 11, and 12 for the third (last) row. The result is a mesh of 3
 *   quadrilaterals across by 2 down.
 *   
 *   The coordinates of the mesh are transformed by the current cumulative
 *   transformation. The mesh is drawn with the current light model and drawing
 *   style.
 *   
 *   Treatment of the current material and normal binding is as follows: The PER_PART
 *   binding specifies a material or normal for each row of the mesh. The PER_FACE
 *   binding specifies a material or normal for each quadrilateral. The corresponding
 *   _INDEXED bindings are the same, but use the #materialIndex or #normalIndex
 *   indices (see SoIndexedShape). The default material binding is OVERALL. The
 *   default normal binding is PER_VERTEX_INDEXED.
 *   
 *   If any normals (or materials) are specified, Open Inventor assumes you provide
 *   the correct number of them, as indicated by the binding. You will see unexpected
 *   results if you specify fewer normals (or materials) than the shape requires. If
 *   no normals are specified, they will be generated automatically.
 *
 *   NOTE: A quad mesh may not render or pick correctly if any of its polygons are
 *   self-intersecting or non-planar.
 * 
 *   OpenGL Vertex Arrays are used
 *     - if they are available, @I and@i
 *     - the environment variable IV_NO_VERTEX_ARRAY is not set, @I and@i
 *     - the #materialIndex, #normalIndex, and #textureCoordIndex fields
 *       are exactly identical to the #coordIndex field, or are set to
 *       their default value (i.e., -1).
 *   
 *   OpenGL Vertex Buffer Objects, which speed up rendering of non-cached indexed shapes,
 *   can be used only if Vertex Arrays are used and the environment variable OIV_NO_VBO is not set. 
 *   See SoShapeHints::useVBO documentation for details.
 *
 * @FILE_FORMAT_DEFAULT
 *    IndexedQuadMesh {
 *    @TABLE_FILE_FORMAT
 *       @TR vertexProperty      @TD NULL
 *       @TR coordIndex          @TD -1
 *       @TR materialIndex       @TD -1
 *       @TR normalIndex         @TD -1
 *       @TR textureCoordIndex   @TD -1
 *       @TR verticesPerColumn   @TD 0
 *       @TR verticesPerRow      @TD 0
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Draws a mesh based on the current coordinates, normals, materials, drawing
 *        style, and so on.
 * 
 *    SoRayPickAction @BR
 *        Picks on the mesh based on the current coordinates and transformation. Details
 *        about the intersection are returned in an SoFaceDetail.
 * 
 *    SoGetBoundingBoxAction @BR
 *        Computes the bounding box that encloses all vertices of the mesh with the
 *        current transformation applied to them. Sets the center to the average of the
 *        coordinates of all vertices.
 * 
 *    SoCallbackAction @BR
 *        If any triangle callbacks are registered with the action, they will be invoked
 *        for each successive triangle forming the quadrilaterals of the mesh.
 * 
 * 
 * @SEE_ALSO
 *    SoCoordinate3,
 *    SoDrawStyle,
 *    SoFaceDetail,
 *    SoFullSceneAntialiasing,
 *    SoIndexedFaceSet,
 *    SoIndexedTriangleStripSet,
 *    SoQuadMesh,
 *    SoVertexProperty
 * 
 * 
 */ 

class INVENTOR_API SoIndexedQuadMesh : public SoIndexedShape {

  SO_NODE_HEADER(SoIndexedQuadMesh);

 public:
  // Fields
  /**
   * Number of vertices per column.
   */
  SoSFInt32   verticesPerColumn;
  /**
   * Number of vertices per row.
   */
  SoSFInt32   verticesPerRow;

  /**
   * Creates an indexed quadrilateral mesh node with default settings.
   */
  SoIndexedQuadMesh();

 SoEXTENDER public:
  // Implement actions
  virtual void        GLRender(SoGLRenderAction *action);

  // Generates default normals using the given normal bundle. 
  // Returns TRUE.
  virtual void      generateDefaultNormals(SoState *state,
                                            const SbVec3f *coords,
                                            int numCoords, 
                                            SoNormalBundle *nb,
                                            SbBool storeRef = FALSE);

  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  int getNumRows(void) const;  // returns the number of Rows
  int getNumCols(void) const;  // returns the number of Columns
  int getNumQuads(void) const; // returns the number of Quads
  int getNumMeshVerts(void) const; // returns the number of vertices of the Quad Mesh 

  // returns the number of PARTS
  inline int getNumParts(void) const { return getNumRows(); }// PARTS are ROWS   

  // returns the number of FACES
  inline int getNumFaces(void) const { return getNumQuads(); } // FACES are Quads 

  // returns the number of vertices needed
  int getNumVerticesNeeded(void) { return getNumMeshVerts(); }  

  // Checks if enough vertices, normals, textureCoord, colors...etc...
  bool check_RenderVectors( SoState *state, bool bUseTexCoordsAnyway );

  // Generic version of  Generate default normals 
  void generateDefaultNormals_QuadMesh(SoState *state, const SbVec3f *vecPQuadCoord[], SbVec3f normals[] );

  virtual void callDEBUGGLRender(SoGLRenderAction *action,uint32_t useTexCoordsAnyway);

  static void initClass();
  static void exitClass();
 protected:
  // This enum is used to indicate the current material or normal binding
  enum Binding {
    OVERALL,
    PER_ROW,     PER_ROW_INDEXED,
    PER_QUAD,    PER_QUAD_INDEXED,
    PER_VERTEX,  PER_VERTEX_INDEXED
  };
  // Generates triangles representing rows
  virtual void        generatePrimitives(SoAction *action);

  // Overrides standard method to create an SoFaceDetail instance
  virtual SoDetail *createTriangleDetail(SoRayPickAction *action,
                                         const SoPrimitiveVertex *v1,
                                         const SoPrimitiveVertex *v2,
                                         const SoPrimitiveVertex *v3,
                                         SoPickedPoint *pp);

  virtual void callSetupIndices(const SoShapeStyleElement* shapeStyle,uint32_t useTexCoordsAnyway);

  //max auto caching test
  virtual int getMaxTestValueForAutoCache(){return totalNumVertices;}
  
  //min auto caching test
  virtual int getMinTestValueForAutoCache(){return verticesPerColumn.getValue();}

  //Approx number of primitives
  virtual void countPrim(){
    totalNumVertices = verticesPerColumn.getValue()* verticesPerRow.getValue();}

  //return number of primitives
  virtual int getNumPrim(){return totalNumVertices;}

  //invalid test
  virtual SbBool numPrimInvalid(){return totalNumVertices < 0 ;}

  // render function
  void doRendering(SoGLRenderAction *action, const SoShapeStyleElement* shapeStyle);

  virtual ~SoIndexedQuadMesh();

 private:

  // Returns current material or normal binding from action's state
  static Binding      getMaterialBinding(SoAction *action);
  Binding      getNormalBinding(SoAction *action, SoNormalBundle* nb);

  // Saves normal binding when generating primitives for picking
  Binding             savedNormalBinding;

  // Returns index (of material or normal) based on given binding
  static int getBindIndex(Binding binding, int vert, int row, int quad, const int32_t *indices);

  virtual int getNumNeededNormals(SoState *state);

  // Blow vpCache when vertexProperty field changes:
  virtual void        notify(SoNotList *list);

  // This stores the total number of vertices; we use this
  // information to influence Separator's auto-caching algorithm
  // (shapes with very few triangles should be cached because
  // traversing them can be expensive, shapes with lots of triangles
  // shouldn't be cached because they'll take up too much memory).
  int totalNumVertices;
};

inline int SoIndexedQuadMesh::getNumNeededNormals(SoState *)
{
  return verticesPerColumn.getValue() *   verticesPerRow.getValue();
}


#endif /* _SO_INDEXED_QUAD_MESH_ */
