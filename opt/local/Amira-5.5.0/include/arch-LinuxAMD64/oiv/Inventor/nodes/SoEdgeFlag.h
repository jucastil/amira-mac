/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_EDGE_FLAG
#define _SO_EDGE_FLAG

#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/nodes/SoNode.h>

class SoBevelAction;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoEdgeFlag
//
//  Node used to mark or unmark edges in the different shapes.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Class to mark/unmark edges for beveling.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   This node defines the current marked/unmarked edges for all subsequent shapes.
 *   
 *   The marking/unmarking of the edges is specified using an @B int_32t @b array.
 *   The meaning of this array and its elements depends on the shape it is applied
 *   to.
 *   
 *   SoIndexedFaceSet, SoVRMLIndexedFaceSet @UL
 *   @LI
 *       For an SoIndexedFaceSet or SoVRMLIndexedFaceSet, each element of the array is an
 *       index in the #SoIndexedShape::coordIndex field. The vertex corresponding to this index is
 *       the first vertex of the edge. The other vertex of the edge is the next vertex in
 *       the face according to the order of the vertices in the SoIndexedFaceSet or
 *       SoVRMLIndexedFaceSet array. If the next element in the array is -1 (end of
 *       face), the next vertex is the first vertex of the current face (as for edge
 *       (5,3) in the example below). Otherwise, the next vertex is the next element in
 *       the array (as for edge (1,2) in the example below). The same edge can appear in
 *       two different faces, but it is not necessary to mark it in both faces; only one
 *       mark per edge is needed.
 *       
 *       Example:
 *       
 *          @TABLE_0B
 *             @TR               @TD 0 @B 1 @b 2 3 4 5 @B 6 @b 7 8 9 10 11
 *             @TR coordIndex =  @TD [ 0, @B 1 @b, @B 2 @b, -1, @B 3 @b, 4, @B 5 @b, -1, 2, 1, 3, -1 ]
 *             @TR edgeMarks =   @TD [ 1 => edge (1, 2),
 *             @TR               @TD 6 => edge (5, 3) ]
 *          @TABLE_END 
 *       
 *   @li
 *   @ul SoFaceSet @UL
 *   @LI
 *       
 *       For an SoFaceSet, the marking is a little different from the SoIndexedFaceSet.
 *       Each element is an index directly in the coordinate array. This corresponds to
 *       the first vertex of the edge; the other is the next vertex in the same face. As
 *       each face description in the coordinate array is cyclic, the other vertex is
 *       either the next vertex in the array, or the first vertex of the face if it is
 *       the end of the face.
 *       
 *       Example:
 *       
 *          @TABLE_0B
 *             @TR coordinates =  @TD [{0.0, 1.0, 1.0},        @TD // 0 ... start face 1
 *             @TR &nbsp;         @TD @B {0.0, 0.0, 1.0} @b,   @TD // @B 1 @b
 *             @TR &nbsp;         @TD @B {1.0, 0.0, 1.0} @b,   @TD // 2
 *             @TR &nbsp;         @TD
 *             @TR &nbsp;         @TD @B {0.0, 1.0, 1.0} @b,   @TD // 3 ... start face 2
 *             @TR &nbsp;         @TD {0.0, 0.0, 1.0},         @TD // 4
 *             @TR &nbsp;         @TD @B {1.0, 0.0, 0.0} @b ]  @TD // @B 5 @b
 *             @TR numVertices =  @TD [ 3, 3 ]
 *             @TR edgeMarks =    @TD [ 1=> edge ({0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}),
 *             @TR &nbsp;         @TD &nbsp;&nbsp;5 => edge ({1.0, 0.0, 0.0}, {0.0, 1.0, 1.0}) ]
 *          @TABLE_END 
 *       
 *   @li
 *   @ul SoTriangleStripSet @UL
 *   @LI
 *       
 *       For an SoTriangleStripSet, marking an edge is very different from the previous
 *       two nodes. If @I m @i is a mark, the edge corresponding is computed as
 *       follows: @BR
 *         . the first vertex is int(@I m @i/2), @BR
 *         . the opposite vertex in the edge is int(@I m @i/2) + @I m @i\%2 + 1; if
 *           (@I m @i\%2) = 0, this is the next vertex, otherwise this is the vertex just
 *           after, in the coordinate array.
 *       
 *       Example:
 *       
 *          @TABLE_0B
 *             @TR coordinates =  @TD [ @B {0.0, 1.0, 1.0} @b,         @TD // @B 0  @b= int(1/2)
 *             @TR &nbsp;         @TD {0.0, 0.0, 1.0},                 @TD // 1
 *             @TR &nbsp;         @TD @B {1.0, 0.0, 1.0} @b,           @TD // 2 = int(1/2) + 1 + (1\%2)
 *             @TR &nbsp;         @TD {1.0, 1.0, 1.0},                 @TD // 3
 *             @TR &nbsp;         @TD @B {0.0, 1.0, 1.0} @b,           @TD // @B 4  @b= int(8/2)
 *             @TR &nbsp;         @TD @B {1.0, 0.0, 0.0} @b ]          @TD // 5 = int(8/2) + 1 +
 *       (8\%2)
 *             @TR edgeMarks =    @TD [ 1=>edge({0.0, 1.0, 1.0}, {1.0, 0.0, 1.0}),
 *             @TR &nbsp;         @TD &nbsp;&nbsp;8 =>edge({0.0, 1.0, 1.0}, {1.0, 0.0, 0.0}) ]
 *          @TABLE_END 
 *   
 *   @li
 *   @ul SoIndexedTriangleStripSet @UL
 *   @LI
 *       
 *       An SoIndexedTriangleStripSet works like an SoTriangleStripSet, except that the
 *       #SoIndexedShape::coordIndex array is used instead of the coordinate
 *       array.
 *       
 *   @li
 *   @ul SoQuadMesh @UL
 *   @LI
 *       
 *       For an SoQuadMesh, the principle is the same as for SoTriangleStripSet. If
 *       @I m @i is the mark, then the corresponding edge is (@I m @i/2, @I n @i)
 *       where @I n @i is: @BR
 *         . the vertex just at the right of the vertex @I m @i/2 if (@I m @i\%2) = 0, @BR
 *         . the vertex just below if (@I m @i\%2) = 1.
 *       
 *       Example:
 *       
 *          @TABLE_0B
 *             @TR coordinates =   @TD [ @B {0.0, 1.0, 1.0} @b, {0.0, 2.0, 2.0}, {0.0, 3.0, 3.0},
 *             @TR &nbsp;          @TD @B {1.0, 0.0, 1.0} @b, {2.0, 0.0, 2.0}, {3.0, 0.0, 3.0},
 *             @TR &nbsp;          @TD {0.0, 1.0, 0.0}, @B {0.0, 2.0, 0.0} @b, @B {0.0, 3.0, 0.0} @b ]
 *             @TR edgeMarks =     @TD [ 1=> edge({0.0, 1.0, 1.0}, {1.0, 0.0, 1.0}),
 *             @TR &nbsp;          @TD 14 => edge({0.0, 2.0, 0.0}, {0.0, 3.0, 0.0}) ]
 *          @TABLE_END 
 *   
 *   @li
 *   @ul SoCube, SoVRMLBox @UL
 *   @LI
 *       
 *       For an SoCube or an SoVRMLBox, edges are identified as shown below:
 *       
 *       @IMAGE EDGEFLG2.gif 
 *       
 *       For each value between [0,11] in the flag array, the corresponding edge is
 *       marked/unmarked.
 *       
 *   @li
 *   @ul SoCone, SoVRMLCone @UL
 *   @LI
 *       
 *       For an SoCone or an SoVRMLCone, only the edges of the base can be
 *       marked/unmarked. The flag array must contain at least one value greater than or
 *       equal to 0 to mark/unmark the edges of the base.
 *       
 *   @li
 *   @ul SoCylinder, SoVRMLCylinder @UL
 *   @LI
 *       
 *       For an SoCylinder or an SoVRMLCylinder, only two values in the flag array are
 *       significant:
 *         - array index 0: mark/unmark the edges around the bottom of the cylinder,
 *         - array index 1: mark/unmark the edges around the top of the cylinder.
 *   @li
 *   @ul
 * 
 * @FILE_FORMAT_DEFAULT
 *    EdgeFlag {
 *    @TABLE_FILE_FORMAT
 *       @TR edgeMarked     @TD -1
 *       @TR edgeUnmarked   @TD -1
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
      Sets: SoEdgeFlagElement
 * 
 * @SEE_ALSO
 *    SoBevelAction,
 *    SoBevelProperty,
 *    SoVertexFlag
 * 
 * 
 */ 

class INVENTOR_API SoEdgeFlag : public SoNode
{
  SO_NODE_HEADER(SoEdgeFlag);

 public:
  // Edges can be marked using an int array. The values of the array determinate the edges to mark.
  // These values are interpreted differently by the different shapes.
  SoMFInt32 edgeMarked;

  /**
   * These are the fields for marked/unmarked edges.
   * 
   */
  SoMFInt32 edgeUnmarked;

  /**
   * Constructor.
   */
  SoEdgeFlag();

 SoEXTENDER public:
  virtual void  doAction(SoAction *action);
  virtual void  getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void  callback(SoCallbackAction *action);
  virtual void  pick(SoPickAction *action);
  virtual void  getPrimitiveCount(SoGetPrimitiveCountAction *action);
  virtual void  bevel(SoBevelAction *action);

 SoINTERNAL public:
  static void   initClass();
  static void   exitClass();

 protected:
  virtual ~SoEdgeFlag();
};

#endif

