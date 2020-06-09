/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : David Beilloin (Mar 2010)
**=======================================================================*/


#ifndef  _SO_INDEXED_LINE_SET_
#define  _SO_INDEXED_LINE_SET_

#include <Inventor/nodes/SoIndexedShape.h>

class SoState;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoIndexedLineSet
//
//  Indexed set of (poly)lines. Each line consists of 2 or more
//  vertices, each of which is denoted by an integer index (from the
//  coordIndex field) into the current coordinates. Depending on the
//  current material and normal binding values, the materials and
//  normals for the lines or vertices may be accessed in order or
//  indexed. If they are indexed, the materialIndex and normalIndex
//  fields are used. Texture coordinates may also be indexed, using
//  the textureCoordIndex field.
//
//////////////////////////////////////////////////////////////////////////////

// This coordinate index indicates that the current line ends and the
// next line begins
#define SO_END_LINE_INDEX       (-1)

/**
 * Indexed polyline shape node.
 * 
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 *   This node represents a 3D shape formed by constructing polylines from vertices
 *   located at the coordinates specified in the #vertexProperty field (from
 *   SoVertexShape), or the current inherited coordinates. For optimal performance,
 *   the #vertexProperty field is recommended.
 *   
 *   SoIndexedLineSet uses the indices in the #coordIndex field (from
 *   SoIndexedShape) to specify the polylines. An index of SO_END_LINE_INDEX (-1)
 *   indicates that the current polyline has ended and the next one begins.
 *   
 *   The coordinates of the line set are transformed by the current cumulative
 *   transformation. The lines are drawn with the current drawing style 
 *   (drawing style FILLED is treated as LINES). The lines are drawn with the
 *   current light model if normals are supplied for the line set. Otherwise,
 *   the lines are not lit, i.e., they are rendered with light model BASE_COLOR.
 *   
 *   Treatment of the current material and normal binding is as follows: The PER_PART
 *   binding specifies a material or normal for each segment of the line. The
 *   PER_FACE binding specifies a material or normal for each polyline. PER_VERTEX
 *   specifies a material or normal for each vertex. The corresponding _INDEXED
 *   bindings are the same, but use the #materialIndex or #normalIndex
 *   indices (see SoIndexedShape). The default material binding is OVERALL. The
 *   default normal binding is PER_VERTEX_INDEXED
 *   
 *   The current complexity value has no effect on the rendering of indexed line sets.
 *
 *   Shape Antialiasing type is SoShape::LINES.
 * 
 * @FILE_FORMAT_DEFAULT
 *    IndexedLineSet {
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
 *    SoLineDetail,
 *    SoLineSet,
 *    SoVertexProperty
 * 
 * 
 */ 

class INVENTOR_API SoIndexedLineSet : public SoIndexedShape {

  SO_NODE_HEADER(SoIndexedLineSet);

 public:
  // Inherits all fields

  /**
   * Creates an indexed line set node with default settings.
   */
  SoIndexedLineSet();

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

  /** register in database */
  static void initClass();
  /** unregister from database */
  static void exitClass();

 protected:
  // Generates line segments representing line set
  virtual void generatePrimitives(SoAction *action);

  // count the number of primitives in the shape
  virtual void countPrim();

  // really do the rendering part
  virtual void doRendering(SoGLRenderAction *action, const SoShapeStyleElement* shapeStyle);

  virtual void callSetupIndices(const SoShapeStyleElement* shapeStyle,uint32_t useTexCoordsAnyway);

  // invalid test
  virtual SbBool numPrimInvalid(){return numPolylines < 0 ;}

  // return num lines for test  
  virtual int getNumPrim(){return numPolylines;}

  // says wether to generate normals
  virtual void shouldGenerateNormals(SoGLRenderAction *action,const SoShapeStyleElement *shapeStyle);


  // says that rendering is PointOrLine
  virtual SbBool isRenderingPointsOrLines(SoGLRenderAction *action);

  // Overrides standard method to create an SoLineDetail instance
  virtual SoDetail *  createLineSegmentDetail(SoRayPickAction *action,
                                              const SoPrimitiveVertex *v1,
                                              const SoPrimitiveVertex *v2,
                                              SoPickedPoint *pp);

  /** Destructor */
  virtual ~SoIndexedLineSet();

  /** Reset numVertices/numSegments/numPolylines when notified */
  virtual void        notify(SoNotList *list);
 private:
  // This enum is used to indicate the current material or normal binding
  enum Binding {
    OVERALL,
    PER_SEGMENT,    PER_SEGMENT_INDEXED,
    PER_LINE,       PER_LINE_INDEXED,
    PER_VERTEX,     PER_VERTEX_INDEXED
  };

  // Returns current material or normal binding from action's state
  static Binding getMaterialBinding(SoAction *action);
  static Binding getNormalBinding(SoAction *action);

    
  // Number of polylines, number of line segments, and vertices per polyline
  int         numSegments;
  int         numPolylines;
  int *       numVertices;

};

inline SbBool 
SoIndexedLineSet::isRenderingPointsOrLines(SoGLRenderAction *)
{
  return TRUE;
}

#endif /* _SO_INDEXED_LINE_SET_ */
    

