/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Mar 2011)
** Modified by : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _SO_INDEXED_TRIANGLE_SET_
#define  _SO_INDEXED_TRIANGLE_SET_

#include <Inventor/nodes/SoIndexedShape.h>

class SoNormalBundle;
class SoCoordinateElement;
class SoShapeStyleElement;
class SoVolumeIndexedTriangleSet;

//@TOBEWRAPPED
/**
* Indexed triangle shape node.
* 
* @ingroup ShapeNodes
* 
* @DESCRIPTION
*   This node represents a 3D shape defined by a set of triangles.
*   This shape node constructs triangles from the vertices located at the coordinates 
*   specified in the #vertexProperty field (from SoVertexShape), or the current 
*   inherited state. For optimal performance, the #vertexProperty field is recommended.
*
*   SoIndexedTriangleSet uses the indices in the coordIndex field (from SoIndexedShape)
*   to specify the vertices of the triangles. Each triangle is specified by three
*   indices.  Unlike SoIndexedFaceSet (for example) no -1 values are needed or allowed.
*   The number of triangles is the number of indices divided by three.
*
*   The vertices of the faces are transformed by the current transformation matrix.
*   The faces are drawn with the current light model and drawing style.
*   
*   Treatment of the current material and normal binding is as follows: The PER_PART
*   and PER_FACE bindings specify a material or normal for each triangle. PER_VERTEX
*   specifies a material or normal for each vertex. The corresponding _INDEXED
*   bindings are the same, but use the #materialIndex or #normalIndex
*   indices (see SoIndexedShape). The default material binding is OVERALL. The
*   default normal binding is PER_VERTEX_INDEXED.
*   
*   If any normals (or materials) are specified, Open Inventor assumes you provided
*   the correct number of them, as indicated by the binding. You will see unexpected
*   results if you specify fewer normals (or materials) than the shape requires. If
*   no normals are specified, they will be generated automatically.
*   
*   Textures are applied as described for the SoIndexedShape class.
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
*   @NODE_SINCE_OIV 8.6
*
* @FILE_FORMAT_DEFAULT
*    IndexedFaceSet {
*    @TABLE_FILE_FORMAT
*       @TR vertexProperty      @TD NULL
*       @TR coordIndex          @TD 0
*       @TR materialIndex       @TD -1
*       @TR normalIndex         @TD -1
*       @TR textureCoordIndex   @TD -1
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
*        Computes the bounding box that encloses all vertices of the face set with the
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
*    SoFaceDetail,
*    SoTriangleSet,
*    SoFullSceneAntialiasing,
*    SoVertexProperty,
*    SoShapeHints
* 
* 
*/ 

class INVENTOR_API SoIndexedTriangleSet : public SoIndexedShape {

  SO_NODE_HEADER(SoIndexedTriangleSet);

 public:
  // Inherits fields

  /**
   * Creates an indexed triangle set node with default settings.
   */
  SoIndexedTriangleSet();

 SoEXTENDER public:
  // Implements actions

  /** @copydoc SoIndexedShape::GLRender */
  virtual void GLRender(SoGLRenderAction *action);

  /** @copydoc SoIndexedShape::generateDefaultNormals */
  virtual void generateDefaultNormals(SoState *state,
    const SbVec3f *coords,
    int numCoords, 
    SoNormalBundle *nb,
    SbBool storeRef = FALSE);

  /** @copydoc SoIndexedShape::getPrimitiveCount */
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);
                                                  
 SoINTERNAL public:

  /** @copydoc SoIndexedShape::initClass */
  static void initClass();

  /** @copydoc SoIndexedShape::exitClass */
  static void exitClass();

  virtual int getNumNeededNormals(SoState *state);

 protected:
  // This enum is used to indicate the current material or normal binding
  enum Binding {
    OVERALL, PER_FACE, PER_FACE_INDEXED, PER_VERTEX,
    PER_VERTEX_INDEXED
  };

  virtual SbBool shouldGenerateTexture3DCoordinates(){return TRUE;}

  virtual void callSetupIndices(const SoShapeStyleElement* shapeStyle,uint32_t useTexCoordsAnyway);

  //Wether to check or not 3d tex coords
  virtual SbBool checkTex3Coords(){return TRUE;}

  // Compute the number of vertices. This is just an approximation,
  //so using 5 verts per unknown polygon is close enough. 
  virtual int getNumPrim()
  {
    if (totalNumVertices==-1) 
      setupNumTrisQuadsFaces(); 
    return totalNumVertices;
  }

  int getNumPrim(int& _numTris )
  {
    if (totalNumVertices==-1)
      setupNumTrisQuadsFaces();
    _numTris = numTris;
    return totalNumVertices;
  }

  virtual void countPrim(){setupNumTrisQuadsFaces();}

  virtual SbBool numPrimInvalid(){return numTris < 0 ;}

  // Generates triangles representing faces
  virtual void        generatePrimitives(SoAction *action);

  // render function
  virtual void doRendering(SoGLRenderAction *action, const SoShapeStyleElement* shapeStyle);

  // Overrides standard method to create an SoFaceDetail instance
  virtual SoDetail *  createTriangleDetail(SoRayPickAction *action,
                                           const SoPrimitiveVertex *v1,
                                           const SoPrimitiveVertex *v2,
                                           const SoPrimitiveVertex *v3,
                                           SoPickedPoint *pp);

  // set numTris/Quads/Faces to -1 when notified
  virtual void        notify(SoNotList *list);

  // destructor
  virtual ~SoIndexedTriangleSet();

 private:

  // used internally by doRendering
  // return true if shape was correctly drawn.
  bool doRenderingVBO(SoGLRenderAction *action, const SoShapeStyleElement* shapeStyle);
  bool doRenderingNonIndexedVBO(SoGLRenderAction *action, const SoShapeStyleElement* shapeStyle);

  // Saves normal binding when generating primitives for picking
  Binding             savedNormalBinding;

  // Returns current material or normal binding from action's state
  static Binding getMaterialBinding(SoAction *action);
  Binding getNormalBinding(SoAction *action, SoNormalBundle *nb);

  // Set number of triangles/quads/faces, based on coordIndex array.
  void setupNumTrisQuadsFaces();
    
  // Number of triangles
  int     numTris, totalNumVertices;

  // optimized normal generation when no creaseAngle is defined.
  void buildPerFaceNormals(SoState *state,const SbVec3f *coords, const int numCoords, SoNormalBundle *nb);

  // optimized version of connectivity computation when tolerance factor is 0.0
  int32_t *buildConnectivity(const SbVec3f *coords, const int numCoords);

 private:
  friend class SoVolumeIndexedTriangleSetDl;
  friend class SoVolumeIndexedTriangleSet;
};

#endif /* _SO_INDEXED_TRIANGLE_SET_ */
