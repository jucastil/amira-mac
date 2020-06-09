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


#ifndef  _SO_LINE_SET_
#define  _SO_LINE_SET_

#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/nodes/SoNonIndexedShape.h>

class SoState;
class SoTextureCoordinateBundle;
class SoTextureCoordinate3Bundle;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoLineSet
//
//  Set of (poly)lines. Each line consists of 2 or more vertices,
//  taken in order from the current coordinates, which are joined to
//  form segments. The startIndex field gives the starting coordinate
//  index for the first line. If materials or normals are bound to
//  vertices, they will begin at that index, as well; otherwise, they
//  will start at index 0.  The number of vertices in each polyline is
//  determined by successive entries in the numVertices field.
//
//////////////////////////////////////////////////////////////////////////////


#ifndef IV_STRICT
// Deprecated feature; specifying USE_REST_OF_VERTICES as the last
// value in the numVertices field will use all the points in the
// coordinate array.
#define SO_LINE_SET_USE_REST_OF_VERTICES        (-1)
#endif


/**
 * Polyline shape node.
 * 
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 *   This node represents a 3D shape formed by constructing polylines from vertices
 *   located at the coordinates specified in the #vertexProperty field (from
 *   SoVertexShape), or the current inherited coordinates. For optimal performance,
 *   the #vertexProperty field is recommended.
 *   
 *   SoLineSet uses the coordinates in order, starting with the first one. Each line
 *   has a number of vertices specified by a value in the #numVertices field.
 *   For example, an SoLineSet with a #numVertices of [3,4,2] would use
 *   coordinates 1, 2, and 3 for the first line, coordinates 4, 5, 6, and 7 for the
 *   second line, and coordinates 8 and 9 for the third.
 *   
 *   The number of values in the #numVertices field indicates the number of
 *   polylines in the set.
 *   
 *   The coordinates of the line set are transformed by the current cumulative
 *   transformation. The lines are drawn with the current drawing style 
 *   (drawing style FILLED is treated as LINES). The lines are drawn with the
 *   current light model if normals are supplied for the line set. Otherwise,
 *   the lines are not lit, i.e., they are rendered with light model BASE_COLOR.
 *   
 *   Treatment of the current material and normal binding is as follows: The PER_PART
 *   binding specifies a material or normal for each segment of the line. The
 *   PER_FACE binding specifies a material or normal for each polyline. The _INDEXED
 *   bindings are equivalent to their non-indexed counterparts. The default material
 *   binding is OVERALL. The default normal binding is PER_VERTEX.
 *   
 *   The current complexity value has no effect on the rendering of line sets.
 *
 *   Shape Antialiasing type is SoShape::LINES.
 * 
 * @FILE_FORMAT_DEFAULT
 *    LineSet {
 *    @TABLE_FILE_FORMAT
 *       @TR vertexProperty   @TD NULL
 *       @TR startIndex       @TD 0
 *       @TR numVertices      @TD -1
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Draws lines based on the current coordinates, normals, materials, drawing
 *        style, and so on.
 * 
 *    SoRayPickAction @BR
 *        Picks lines based on the current coordinates and transformation. Details about
 *        the intersection are returned in an SoLineDetail.
 * 
 *    SoGetBoundingBoxAction @BR
 *        Computes the bounding box that encloses all vertices of the line set with the
 *        current transformation applied to them. Sets the center to the average of the
 *        coordinates of all vertices.
 * 
 *    SoCallbackAction @BR
 *        If any line segment callbacks are registered with the action, they will be
 *        invoked for each successive segment in the line set.
 * 
 * 
 * @SEE_ALSO
 *    SoCoordinate3,
 *    SoDrawStyle,
 *    SoFullSceneAntialiasing,
 *    SoIndexedLineSet,
 *    SoLineDetail,
 *    SoVertexProperty
 * 
 * 
 */ 

class INVENTOR_API SoLineSet : public SoNonIndexedShape {

  SO_NODE_HEADER(SoLineSet);

 public:
  /**
   * Number of vertices per polyline.
   */
  SoMFInt32           numVertices;

  /**
   * Creates a line set node with default settings.
   */
  SoLineSet();

 SoEXTENDER public:
  /** Implements SoGLRenderAction actions */
  virtual void GLRender(SoGLRenderAction *action);

  /** 
   * Implements getBoundingBox actions
   * to tell open caches that they contain lines
   */
  virtual void getBoundingBox(SoGetBoundingBoxAction *action);

  /** Implements SoGetPrimitiveCountAction action */
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);
  
 SoINTERNAL public:
  inline int getNumPolyLines(void) const { return numVertices.getNum(); } 
  // returns the number of PARTS
  inline int getNumParts(void) const { return totalNumVertices - getNumPolyLines(); } // PARTS are segment

  // returns the number of FACES
  inline int getNumFaces(void) const { return getNumPolyLines(); } // FACES are polylines

  // returns the number of vertices needed
  int getNumVerticesNeeded(void) { return totalNumVertices + startIndex.getValue(); }  

  // Checks if enough vertices, normals, textureCoord, colors...etc...
  bool check_RenderVectors( SoState *state, bool bUseTexCoordsAnyway );


  /** register in database */
  static void initClass();
  /** unregister from database */
  static void exitClass();

  virtual void callDEBUGGLRender(SoGLRenderAction *action,uint32_t useTexCoordsAnyway);

 protected:
  // Generates line segments representing line set
  virtual void generatePrimitives(SoAction *action);

  // check if normal should be generated or not.
  virtual void shouldGenerateNormals(SoGLRenderAction *action,const SoShapeStyleElement *shapeStyle);
 
  //Free memory
  virtual void exitRender(SoState *state,int stateFlag,
                  SoTextureCoordinateBundle *tcb,
                  SoTextureCoordinate3Bundle *tc3b);

  // count the number of primitives in the shape
  virtual void countPrim();

  // really do the rendering part
  virtual void doRendering(SoGLRenderAction *action, const SoShapeStyleElement* shapeStyle);

  // invalid test
  virtual SbBool numPrimInvalid(){return totalNumVertices < 0 ;}

  //return number of primitives
  virtual int getNumPrim(){return totalNumVertices;}

  // return num vertices
  virtual int getNumVert();

  //max auto caching test
  virtual int getMaxTestValueForAutoCache(){return totalNumVertices;}
  
  //min auto caching test
  virtual int getMinTestValueForAutoCache(){return totalNumVertices;}

  // says that rendering is PointOrLine
  virtual SbBool isRenderingPointsOrLines(SoGLRenderAction *action);

  // Overrides standard method to create an SoLineDetail instance
  virtual SoDetail *  createLineSegmentDetail(SoRayPickAction *action,
                                              const SoPrimitiveVertex *v1,
                                              const SoPrimitiveVertex *v2,
                                              SoPickedPoint *pp);

  /** Destructor */
  virtual ~SoLineSet();

  /** Blow vpCache when vertexProperty field changes */
  virtual void notify(SoNotList *list);

 private:
  // This enum is used to indicate the current material or normal binding
  enum Binding {
    OVERALL, PER_LINE, PER_SEGMENT, PER_VERTEX
  };

  // Returns current material or normal binding from action's state
  static Binding getMaterialBinding(SoAction *action);
  static Binding getNormalBinding(SoAction *action);

  // internally manage SO_LINE_SET_USE_REST_OF_VERTICES
  bool m_usingUSE_REST;
  bool m_nvNotifyEnabled;
  inline void setNvNotifyEnabled(const bool nvNotifyEnabled)
  { m_nvNotifyEnabled = nvNotifyEnabled; }
  inline bool getNvNotifyEnabled() const
  {return m_nvNotifyEnabled;}

  // This stores the total number of vertices; we use this
  // information to influence Separator's auto-caching algorithm
  // (shapes with very few triangles should be cached because
  // traversing them can be expensive, shapes with lots of triangles
  // shouldn't be cached because they'll take up too much memory).
  int totalNumVertices;
};

inline SbBool 
SoLineSet::isRenderingPointsOrLines(SoGLRenderAction *)
{
  return TRUE;
}

#endif /* _SO_LINE_SET_ */

