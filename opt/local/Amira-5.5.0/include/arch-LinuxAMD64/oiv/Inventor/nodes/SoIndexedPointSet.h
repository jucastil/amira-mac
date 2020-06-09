/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : F. DELLA MAESTRA (Sep 2005)
**=======================================================================*/

#ifndef  _SO_INDEXED_POINT_SET_
#define  _SO_INDEXED_POINT_SET_

#include <Inventor/nodes/SoIndexedShape.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoIndexedPointSet
//
//  Indexed set of points. Each point consists of one
//  vertex, which is denoted by an integer index (from the
//  coordIndex field) into the current coordinate. Depending on the
//  current material and normal binding values, the materials and
//  normals for the vertices may be accessed in order or
//  indexed. If they are indexed, the materialIndex and normalIndex
//  fields are used. /*Texture coordinates may also be indexed, using
//  the textureCoordIndex field.*/
//
//////////////////////////////////////////////////////////////////////////////
//#define SO_END_POINT_INDEX (-1)

/**
* 
* Indexed point set shape node.
* 
* @ingroup ShapeNodes
* 
* @DESCRIPTION
*
*   This node represents a set of points located at the coordinates specified by the
*   #vertexProperty field (from SoVertexShape) or the current inherited
*   coordinates. For optimal performance, the #vertexProperty field is
*   recommended.
*
*   Each point consists of one
*   vertex, which is denoted by an integer index (from the
*   #coordIndex field) into the current coordinates. Depending on the
*   current material and normal binding values, the materials and
*   normals for the vertices may be accessed in order or
*   indexed. If they are indexed, the materialIndex and normalIndex
*   fields are used.
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
*    IndexedPointSet {
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
*        Draws points based on the current coordinates, normals, materials, drawing
*        style, and so on.
* 
*    SoRayPickAction @BR
*        Picks points based on the current coordinates and transformation. Details about
*        the intersection are returned in an SoPointDetail.
* 
*    SoGetBoundingBoxAction @BR
*        Computes the bounding box that encloses all vertices of the point set with the
*        current transformation applied to them. Sets the center to the average of the
*        coordinates of all points.
* 
*    SoCallbackAction @BR
*        If any point callbacks are registered with the action, they will be
*        invoked for each successive point in the set.
* 
* 
* @SEE_ALSO
*    SoCoordinate3,
*    SoDrawStyle,
*    SoFullSceneAntialiasing,
*    SoPointDetail,
*    SoPointSet,
*    SoVertexProperty
* 
* 
*/ 

class INVENTOR_API SoIndexedPointSet : public SoIndexedShape {

  SO_NODE_HEADER(SoIndexedPointSet);

public:
  // Inherits all fields

  /**
  * Creates an indexed point set node with default settings.
  */
  SoIndexedPointSet();

  SoEXTENDER public:
  /** Implements SoGLRenderAction actions */
  virtual void   GLRender(SoGLRenderAction *action);

  /** 
  * Implements getBoundingBox actions
  * to tell open caches that they contain lines
  */
  virtual void getBoundingBox(SoGetBoundingBoxAction *action);

  /** Implements SoGetPrimitiveCountAction action */
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);

  SoINTERNAL public:

  /** register in database */
  static void initClass();
  /** unregister from database */
  static void exitClass();

protected:
  // Generates points representing point set
  virtual void   generatePrimitives(SoAction *action);

  // really do the rendering part
  virtual void doRendering(SoGLRenderAction *action, const SoShapeStyleElement* shapeStyle);

  virtual void callSetupIndices(const SoShapeStyleElement* shapeStyle,uint32_t useTexCoordsAnyway);

  // return num points for test  
  virtual int getNumPrim();

  // No normal generation
  virtual void shouldGenerateNormals(SoGLRenderAction *action,const SoShapeStyleElement *shapeStyle);


  // says that rendering is PointOrLine
  virtual SbBool isRenderingPointsOrLines(SoGLRenderAction *action);

  // Overrides standard method to create an SoPointDetail instance
  virtual SoDetail*	createPointDetail(SoRayPickAction *action,
    const SoPrimitiveVertex *v,
    SoPickedPoint *pp);

  /** Destructor */
  virtual ~SoIndexedPointSet();

private:
  // This enum is used to indicate the current material or normal binding
  enum Binding {
    OVERALL,
    PER_VERTEX,
    PER_VERTEX_INDEXED
  };

  // Returns current material or normal binding from action's state
  static Binding getMaterialBinding(SoAction* action);
  static Binding getNormalBinding(SoAction* action);
  SbBool              areMaterialsPerPoint(SoAction *action) const;
  SbBool              areNormalsPerPoint(SoAction *action) const;



  // Number of points to draw
  int   numPoints;

};

inline SbBool 
SoIndexedPointSet::isRenderingPointsOrLines(SoGLRenderAction *)
{
  return TRUE;
}

#endif /* _SO_INDEXED_POINT_SET_ */
