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


#ifndef  _SO_POINT_SET_
#define  _SO_POINT_SET_

#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/nodes/SoNonIndexedShape.h>

class SoState;
class SoTextureCoordinateBundle;
class SoTextureCoordinate3Bundle;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoPointSet
//
//  Set of points, using the current coordinates. The startIndex field
//  gives the starting coordinate index for the first point. The number of
//  points to draw is determined by the numPoints field.
//
//////////////////////////////////////////////////////////////////////////////

// This value, when used in the numPoints field, means use the rest of
// the coordinates as points
#define SO_POINT_SET_USE_REST_OF_POINTS (-1)

/**
 * Point set shape node.
 * 
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 *   This node represents a set of points located at the coordinates specified by the
 *   #vertexProperty field (from SoVertexShape) or the current inherited
 *   coordinates. For optimal performance, the #vertexProperty field is
 *   recommended.
 *   
 *   SoPointSet uses the coordinates in order, starting with the first one.
 *   The number of coordinates to use (the number of points in the set) is 
 *   specified by the #numPoints field.  The default value of this field is -1, 
 *   which means to use all the coordinates, so it may not be necessary to 
 *   explicitly set this field.
 *   
 *   The coordinates of the point set are transformed by the current cumulative
 *   transformation. The points are drawn with the current light model and drawing
 *   style (drawing styles FILLED and LINES are treated as POINTS).
 *   
 *   Treatment of the current material and normal binding is as follows: PER_PART,
 *   PER_FACE, and PER_VERTEX bindings bind one material or normal to each point. The
 *   default material binding is OVERALL. The default normal binding is PER_VERTEX.
 *
 *   Shape Antialiasing type is SoShape::POINTS.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PointSet {
 *    @TABLE_FILE_FORMAT
 *       @TR vertexProperty   @TD NULL
 *       @TR startIndex       @TD 0
 *       @TR numPoints        @TD -1
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Draws points based on the current coordinates, normals, materials, drawing
 *        style, and so on.
 * 
 *    SoRayPickAction @BR
 *        Picks points based on the current coordinates and transformation. Details about
 *        the intersection are returned in an SoPointDetail.
 * 
 *    SoGetBoundingBoxAction @BR
 *        Computes the bounding box that encloses all points in the set with the current
 *        transformation applied to them. Sets the center to the average of the
 *        coordinates of all points.
 * 
 *    SoCallbackAction @BR
 *        If any point callbacks are registered with the action, they will be invoked for
 *        each point in the set.
 * 
 * 
 * @SEE_ALSO
 *    SoCoordinate3,
 *    SoDrawStyle,
 *    SoFullSceneAntialiasing,
 *    SoIndexedPointSet,
 *    SoPointDetail,
 *    SoVertexProperty
 * 
 * 
 */ 

class INVENTOR_API SoPointSet : public SoNonIndexedShape {

  SO_NODE_HEADER(SoPointSet);

 public:
  /**
   * Number of points.
   */
  SoSFInt32           numPoints;

  /**
   * Creates a point set node with default settings.
   */
  SoPointSet();

 SoEXTENDER public:
  /** Implements SoGLRenderAction action */
  virtual void        GLRender(SoGLRenderAction *action);

  /**
   * Implements SoGetBoundingBoxAction action
   * Redefined this to tell open caches that they contain points
   */
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);

  /** Implements SoGetPrimitiveCountAction action */
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  // returns the number of PARTS
  inline int getNumParts(void) const { return totalNumVertices; } // PARTS are points (by convention)
  // returns the number of FACES
  inline int getNumFaces(void) const { return totalNumVertices; } // FACES are points (by convention)

  // returns the number of vertices needed
  int getNumVerticesNeeded(void) { return totalNumVertices + startIndex.getValue(); }  

  // Checks if enough vertices, normals, textureCoord, colors...etc...
  bool check_RenderVectors( SoState *state, bool bUseTexCoordsAnyway );


  /** register in database */
  static void         initClass();
  /** unregister from database */
  static void         exitClass();

  virtual void callDEBUGGLRender(SoGLRenderAction *action,uint32_t useTexCoordsAnyway);

 protected:
  // Generates points representing point set
  virtual void        generatePrimitives(SoAction *action);

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

  // Overrides standard method to create an SoPointDetail instance
  virtual SoDetail *  createPointDetail(SoRayPickAction *action,
                                        const SoPrimitiveVertex *v,
                                        SoPickedPoint *pp);

  /** Destructor */
  virtual ~SoPointSet();

  /** Blow vpCache when vertexProperty field changes */
  virtual void notify(SoNotList *list);

 private:
  // Returns TRUE if materials/normals are bound to individual points
  SbBool              areMaterialsPerPoint(SoAction *action) const;
  SbBool              areNormalsPerPoint(SoAction *action) const;
  // internally manage SO_POINT_SET_USE_REST_OF_VERTICES
  bool m_usingUSE_REST;
  bool m_nvNotifyEnabled;
  inline void setNvNotifyEnabled(const bool nvNotifyEnabled)
  { m_nvNotifyEnabled = nvNotifyEnabled; }
  inline bool getNvNotifyEnabled() const
  {return m_nvNotifyEnabled;}

  bool doRenderingVBO(SoGLRenderAction *action, const SoShapeStyleElement* shapeStyle);

  // This stores the total number of vertices; we use this
  // information to influence Separator's auto-caching algorithm
  // (shapes with very few triangles should be cached because
  // traversing them can be expensive, shapes with lots of triangles
  // shouldn't be cached because they'll take up too much memory).
  int totalNumVertices;
};

inline SbBool 
SoPointSet::isRenderingPointsOrLines(SoGLRenderAction *)
{
  return TRUE;
}

#endif /* _SO_POINT_SET_ */

