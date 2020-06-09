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
** Modified by : AJO (May 2011)
**=======================================================================*/


#ifndef  _SO_INDEXED_FACE_SET_
#define  _SO_INDEXED_FACE_SET_

#include <Inventor/nodes/SoIndexedShape.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoIndexedFaceSet
//
//  Indexed set of faces. Each face consists of 3 or more vertices,
//  each of which is denoted by an integer index (from the coordIndex
//  field) into the current coordinates. Depending on the current
//  material and normal binding values, the materials and normals for
//  the faces or vertices may be accessed in order or indexed. If they
//  are indexed, the materialIndex and normalIndex fields are used.
//
//////////////////////////////////////////////////////////////////////////////


// This coordinate index indicates that the current face ends and the
// next face begins.  Use this for simple (1 contour) polygons.
#define SO_END_FACE_INDEX       (-1)

// If SoShapeHints is used with a windingType other than NO_WINDING_TYPE,
// this coordinate index indicates that the current contour ends
// and the next contour begins.
#define SO_END_CONTOUR_INDEX    (-1)

// This coordinate index indicates that the current complex face (block
// of contours) ends.
#define SO_END_POLYGON_INDEX    (-2)

class SoNormalBundle;
class SoCoordinateElement;
class SoShapeStyleElement;
class SoVolumeIndexedFaceSet;
#ifdef OIV_NET_DOC
/**
* Indexed polygonal face shape node.
* 
* @ingroup ShapeNodes
* 
* @DESCRIPTION
*   This node represents a 3D shape formed by constructing faces (polygons) from
*   vertices located at the coordinates specified in the #vertexProperty field
*   (from SoVertexShape), or the current inherited state. For optimal performance,
*   the #vertexProperty field is recommended.
*
*   If SoShapeHints is not used, or if windingType field from SoShapeHints is equal to 
*   NO_WINDING_TYPE, SoIndexedFaceSet uses the indices in the #coordIndex field (from
*   SoIndexedShape) to specify simple polygonal faces. An index of SO_END_FACE_INDEX
*   (-1) indicates that the current face has ended and the next one begins. For
*   improved performance, arrange all the faces with only 3 vertices at beginning of
*   the list, then all faces with 4 vertices, and finally all other faces.
*
*   If SoShapeHints is used with a windingType field other than NO_WINDING_TYPE, 
*   SoIndexedFaceSet uses the indices in the coordIndex field (from SoIndexedShape)
*   to specify complex polygonal faces (possibly) made up of multiple contours.
*   An index of SO_END_CONTOUR_INDEX (-1) indicates that the current
*   contour has ended and that the next one begins. An index of SO_END_POLYGON_INDEX (-2)
*   indicates that the current complex face (group of contours) has ended.
*   After the end of a complex face, you can create another complex face, and so on.
*
*   The vertices of the faces are transformed by the current transformation matrix.
*   The faces are drawn with the current light model and drawing style.
*   
*   Treatment of the current material and normal binding is as follows: The PER_PART
*   and PER_FACE bindings specify a material or normal for each face. PER_VERTEX
*   specifies a material or normal for each vertex. The corresponding _INDEXED
*   bindings are the same, but use the #materialIndex or #normalIndex
*   indices (see SoIndexedShape). The default material binding is OVERALL. The
*   default normal binding is PER_VERTEX_INDEXED.
*   
*   If any normals (or materials) are specified, Open Inventor assumes you provide
*   the correct number of them, as indicated by the binding. You will see unexpected
*   results if you specify fewer normals (or materials) than the shape requires. If
*   no normals are specified, they will be generated automatically.
*   
*   Textures are applied as described for the SoIndexedShape class.
*   
*   NOTE: An indexed face set may not render or pick correctly if any of its polygons
*   are self-intersecting or non-planar.
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
*    SoFaceSet,
*    SoFullSceneAntialiasing,
*    SoVertexProperty,
*    SoShapeHints
* 
* 
*/ 
#else
/**
* Indexed polygonal face shape node.
* 
* @ingroup ShapeNodes
* 
* @DESCRIPTION
*   This node represents a 3D shape formed by constructing faces (polygons) from
*   vertices located at the coordinates specified in the #vertexProperty field
*   (from SoVertexShape), or the current inherited state. For optimal performance,
*   the #vertexProperty field is recommended.
*
*   SoIndexedFaceSet is a general purpose polygon rendering node.  It can render 
*   triangles, quadrilaterals, and other types of polygons or any combination thereof.
*   SoIndexedFaceSet supports both convex and non-convex polygons (unlike OpenGL).
*   However polygons are assumed to be convex by default. Rendering non-convex
*   polygons in this mode may produce incorrect results.  Enable non-convex
*   polygons using the faceType field of an SoShapeHints node.  In this mode
*   SoIndexedFaceSet will automatically convert non-convex polygons, if necessary,
*   to faces that the hardware can handle.  SoIndexedFaceSet can also directly
*   handle complex polygons with "holes".  See the following paragraphs.  If your
*   geometry is defined entirely by triangles it may be more convenient and more
*   efficient to use an SoIndexedTriangleSet node.
*
*   If SoShapeHints is not used, or if windingType field from SoShapeHints is equal to 
*   NO_WINDING_TYPE, SoIndexedFaceSet uses the indices in the #coordIndex field (from
*   SoIndexedShape) to specify simple polygonal faces. An index of SO_END_FACE_INDEX
*   (-1) indicates that the current face has ended and the next one begins. For
*   improved performance, arrange all the faces with only 3 vertices at beginning of
*   the list, then all faces with 4 vertices, and finally all other faces.
*
*   If SoShapeHints is used with a windingType field other than NO_WINDING_TYPE, 
*   SoIndexedFaceSet uses the indices in the coordIndex field (from SoIndexedShape)
*   to specify complex polygonal faces (possibly) made up of multiple contours.
*   An index of SO_END_CONTOUR_INDEX (-1) indicates that the current
*   contour has ended and that the next one begins. An index of SO_END_POLYGON_INDEX (-2)
*   indicates that the current complex face (group of contours) has ended.
*   After the end of a complex face, you can create another complex face, and so on.
*
*   @B Skeleton to create a polygon with holes@b
*
*   <pre> 
*   1) Choose a winding rule with windingType field from SoShapeHints.
*
*            SoShapeHints *myShapeHints = new SoShapeHints;
*            myShapeHints->windingType = SoShapeHints::ODD_TYPE;
*
*   2) Create list of contours.
*
*            static int32_t indices[21] =  {
*                        0,  3,  1,      SO_END_CONTOUR_INDEX,  
*                        5,  6,  4,      SO_END_POLYGON_INDEX, // To end the first polygon.
*                        0,  7,  3,      SO_END_CONTOUR_INDEX,
*                        10, 9,  8,      SO_END_CONTOUR_INDEX,
*                        9,  7,  0,  8,  SO_END_POLYGON_INDEX  // To end the second polygon.
*                        };
*
*   Note: The last polygon must end with either SO_END_POLYGON_INDEX or SO_END_CONTOUR_INDEX or nothing
*
*            static int32_t indices[21] =  {
*                        0,  3,  1,      SO_END_CONTOUR_INDEX,  
*                        5,  6,  4,      SO_END_POLYGON_INDEX, 
*                        0,  7,  3,      SO_END_CONTOUR_INDEX,
*                        10, 9,  8,      SO_END_CONTOUR_INDEX,
*                        9,  7,  0,  8
*                        };
*  </pre>
*
*   The vertices of the faces are transformed by the current transformation matrix.
*   The faces are drawn with the current light model and drawing style.
*   
*   Treatment of the current material and normal binding is as follows: The PER_PART
*   and PER_FACE bindings specify a material or normal for each face. PER_VERTEX
*   specifies a material or normal for each vertex. The corresponding _INDEXED
*   bindings are the same, but use the #materialIndex or #normalIndex
*   indices (see SoIndexedShape). The default material binding is OVERALL. The
*   default normal binding is PER_VERTEX_INDEXED.
*   
*   If any normals (or materials) are specified, Open Inventor assumes you provide
*   the correct number of them, as indicated by the binding. You will see unexpected
*   results if you specify fewer normals (or materials) than the shape requires. If
*   no normals are specified, they will be generated automatically.
*   
*   Textures are applied as described for the SoIndexedShape class.
*   
*   NOTE: An indexed face set may not render or pick correctly if any of its polygons
*   are self-intersecting or non-planar.
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
*    IndexedFaceSet {
*    @TABLE_FILE_FORMAT
*       @TR vertexProperty      @TD NULL
*       @TR coordIndex          @TD -1
*       @TR materialIndex       @TD -1
*       @TR normalIndex         @TD -1
*       @TR textureCoordIndex   @TD -1
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
*    SoFaceSet,
*    SoFullSceneAntialiasing,
*    SoIndexedTriangleSet,
*    SoShapeHints,
*    SoVertexProperty
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoIndexedFaceSet : public SoIndexedShape {

  SO_NODE_HEADER(SoIndexedFaceSet);

 public:
  // Inherits fields

  /**
   * Creates an indexed face set node with default settings.
   */
  SoIndexedFaceSet();

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);

 // Generates default normals using the given normal bundle. 
  // Returns TRUE.
  virtual void      generateDefaultNormals(SoState *state,
                                            const SbVec3f *coords,
                                            int numCoords, 
                                            SoNormalBundle *nb,
                                            SbBool storeRef = FALSE);

  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);
                                                  
 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  virtual int getNumNeededNormals(SoState *state);

 protected:
  // This enum is used to indicate the current material or normal binding
  enum Binding {
    OVERALL, PER_FACE, PER_FACE_INDEXED, PER_VERTEX,
    PER_VERTEX_INDEXED
  };

  //Wether to check or not shapeHints
  virtual SbBool shouldCheckShapeHints(){ return TRUE;}

  virtual SbBool shouldGenerateTexture3DCoordinates(){return TRUE;}

  virtual void callSetupIndices(const SoShapeStyleElement* shapeStyle,uint32_t useTexCoordsAnyway);

  //Wether to check or not 3d tex coords
  virtual SbBool checkTex3Coords(){return TRUE;}

  virtual SbBool shapeHintsTest(){ return (numQuads > 0 || numFaces > 0);}

  // Compute the number of vertices. This is just an approximation,
  //so using 5 verts per unknown polygon is close enough. 
  virtual int getNumPrim()
  {
    if (totalNumVertices==-1) 
      setupNumTrisQuadsFaces(); 
    return totalNumVertices;
  }

  int getNumPrim(int& _numTris, int&_numQuads, int& _numFaces )
  {
    if (totalNumVertices==-1)
      setupNumTrisQuadsFaces();
    _numTris = numTris;
    _numQuads = numQuads;
    _numFaces = numFaces;
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
  virtual ~SoIndexedFaceSet();

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
    
  // Number of triangles, quads, (n>4)-vertex faces
  int     numTris, numQuads, numFaces, totalNumVertices;

  // used in desindexed VBO mode for polygons.
  GLsizei* m_countArray;
  GLint*   m_offsetArray;

  // optimized normal generation when no creaseAngle is defined.
  void buildPerFaceNormals(SoState *state,const SbVec3f *coords, const int numCoords, SoNormalBundle *nb);

  // optimized version of connectivity computation when tolerance factor is 0.0
  int32_t *buildConnectivity(const SbVec3f *coords, const int numCoords);

  static const int AUTO_CACHE_IFS_MIN_WITHOUT_VP;
  static const int AUTO_CACHE_IFS_MAX;

 private:
  friend class SoVolumeIndexedFaceSetDl;
  friend class SoVolumeIndexedFaceSet;
};

#endif /* _SO_INDEXED_FACE_SET_ */
