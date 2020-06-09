/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_INDEXED_TRIANGLE_STRIP_SET_
#define  _SO_INDEXED_TRIANGLE_STRIP_SET_

#include <Inventor/nodes/SoIndexedShape.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/nodes/SoVertexProperty.h>
#include <Inventor/nodes/SoSeparator.h>

class SoCoordinateElement;
class SoVolumeIndexedTriangleStripSet;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoIndexedTriangleStripSet
//
//  Indexed set of triangles strips.  Strips are separated by the
//  special index SO_END_STRIP_INDEX (-1).  The N indices in the strip
//  define N-2 triangles, which are formed by indexing into the
//  current coordinates. Depending on the current material and normal
//  binding values, the materials and normals for the triangles or
//  vertices may be accessed in order or indexed. If they are indexed,
//  the materialIndex and normalIndex fields are used.
//
//////////////////////////////////////////////////////////////////////////////

// This coordinate index indicates that the current triangle ends and the
// next triangle begins
#define SO_END_STRIP_INDEX      (-1)

class SoNormalBundle;
class SoCoordinateElement;

/**
 * Indexed triangle strip set shape node.
 *
 * @ingroup ShapeNodes
 *
 * @DESCRIPTION
 *   This shape node constructs triangle strips out of vertices located at the
 *   coordinates specified in the #vertexProperty field (from SoVertexShape),
 *   or the current inherited coordinates. For optimal performance, the
 *   #vertexProperty field is recommended.
 *
 *   SoIndexedTriangleStripSet uses the indices in the #coordIndex field (from
 *   SoIndexedShape) to specify the vertices of the triangle strips. An index of
 *   SO_END_STRIP_INDEX (-1) indicates that the current strip has ended and the next
 *   one begins.
 *
 *   The vertices of the faces are transformed by the current transformation matrix.
 *   The faces are drawn with the current light model and drawing style.
 *
 *   Treatment of the current material and normal binding is as follows: PER_PART
 *   specifies a material or normal per strip. PER_FACE binding specifies a material
 *   or normal for each triangle. PER_VERTEX specifies a material or normal for each
 *   vertex. The corresponding _INDEXED bindings are the same, but use the
 *   #materialIndex or #normalIndex indices (see SoIndexedShape). The
 *   default material binding is OVERALL. The default normal binding is
 *   PER_VERTEX_INDEXED
 *
 *   If any normals (or materials) are specified, Open Inventor assumes you provide
 *   the correct number of them, as indicated by the binding. You will see unexpected
 *   results if you specify fewer normals (or materials) than the shape requires. If
 *   no normals are specified, they will be generated automatically.
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
 *   To render triangles that are not in strips, see the SoIndexedTriangleSet node.
 *
 * @FILE_FORMAT_DEFAULT
 *    IndexedTriangleStripSet {
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
 *    SoFullSceneAntialiasing,
 *    SoIndexedFaceSet,
 *    SoIndexedTriangleSet,
 *    SoTriangleStripSet,
 *    SoVertexProperty
 *
 *
 */

class INVENTOR_API SoIndexedTriangleStripSet : public SoIndexedShape {

  SO_NODE_HEADER(SoIndexedTriangleStripSet);


 public:
  /**
   * Returns number of strips.
   */
  int getNumStrips(void){countStripsAndTris();return numStrips;};

  /**
   * Returns number of triangles.
   */
  int getNumTriangles(void){countStripsAndTris();return numTriangles;};

  // Constructor
  /**
   * Creates an indexed triangle strip set node with default settings.
   */
  SoIndexedTriangleStripSet();

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);

  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

 // Generates default normals using the given normal bundle.
  virtual void      generateDefaultNormals(SoState *state,
                                            const SbVec3f *coords,
                                            int numCoords,
                                            SoNormalBundle *nb,
                                            SbBool storeRef = FALSE);
  virtual int getNumNeededNormals(SoState *state);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  // This enum is used to indicate the current material or normal binding
  enum Binding {
    OVERALL,
    PER_STRIP,      PER_STRIP_INDEXED,
    PER_TRIANGLE,   PER_TRIANGLE_INDEXED,
    PER_VERTEX,     PER_VERTEX_INDEXED
  };

  // Generates triangles representing strips
  virtual void        generatePrimitives(SoAction *action);

  // count primitives
  virtual void countPrim(){countStripsAndTris();}

  // return num strips for test
  virtual int getNumPrim(){return numStrips;}

  // return num vertices for test
  virtual int getNumVert();

  virtual void callSetupIndices(const SoShapeStyleElement* shapeStyle,uint32_t useTexCoordsAnyway);

  // invalid test
  virtual SbBool numPrimInvalid(){return numStrips < 0 ;}

  // render function
  void doRendering(SoGLRenderAction *action, const SoShapeStyleElement* shapeStyle);

  // Overrides standard method to create an SoFaceDetail instance
  virtual SoDetail *  createTriangleDetail(SoRayPickAction *action,
                                           const SoPrimitiveVertex *v1,
                                           const SoPrimitiveVertex *v2,
                                           const SoPrimitiveVertex *v3,
                                           SoPickedPoint *pp);

  ~SoIndexedTriangleStripSet();

SoINTERNAL public:
  // Reset numVertices/numStrips when notified
  virtual void        notify(SoNotList *list);

 private:

   // optimized normal generation when no creaseAngle is defined.
   void buildPerVertexNormals(SoState *state,const SbVec3f *coords, const int numCoords, SoNormalBundle *nb);

   // optimized version of connectivity computation when tolerance factor is 0.0
   int32_t *buildConnectivity(const SbVec3f *coords, const int numCoords);

  // Returns current material or normal binding from action's state
  static Binding getMaterialBinding(SoAction *action);
  Binding getNormalBinding(SoAction *action, SoNormalBundle *nb);

  // Fill in numStrips, numTriangles and numVertices[]
  void countStripsAndTris();

  // Number of strips, total number of triangles, and number of
  // vertices per strip:
  int         numStrips;
  int         numTriangles;
  int *       numVertices;

  static const int AUTO_CACHE_ITSS_MIN_WITHOUT_VP;

  static const int AUTO_CACHE_ITSS_MAX;


 private:
  friend class SoVolumeIndexedTriangleStripSetDl;
};

#endif /* _SO_INDEXED_TRIANGLE_STRIP_SET_ */

