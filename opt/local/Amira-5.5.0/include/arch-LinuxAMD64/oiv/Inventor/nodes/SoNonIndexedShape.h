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


#ifndef  _SO_NON_INDEXED_SHAPE_
#define  _SO_NON_INDEXED_SHAPE_

#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/nodes/SoVertexShape.h>
#include <Inventor/nodes/SoVertexProperty.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoNonIndexedShape
//
//  Abstract nonindexed shape node class. All nodes derived from this
//  (such as SoFaceSet and SoTriangleStripSet) are shapes constructed
//  from vertices defined by consecutive entries in the current
//  coordinates. The startIndex field gives the index into the current
//  coordinates at which the shape begins.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Abstract base class for all non-indexed vertex-based shapes.
 * 
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 *   This node is the abstract base class for all vertex-based shapes that are not
 *   constructed from indices, such as SoFaceSet, SoLineSet, and SoQuadMesh.
 *   
 *   All subclasses of SoNonIndexedShape construct objects by using the coordinates
 *   specified in the #vertexProperty field (from SoVertexShape), or the
 *   current inherited coordinates. The #startIndex field defined by this class
 *   is now obsolete, and is provided here only for compatibility with old files and
 *   programs.
 *   
 *   The subclass decides what to do with this and any subsequent coordinates. The
 *   shape is drawn with the current lighting model and drawing style and is
 *   transformed by the current transformation matrix.
 *   
 *   Material, normal, and texture coordinate bindings for shapes derived from this
 *   class ignore any index specifications. That is, a binding value of
 *   PER_FACE_INDEXED is treated the same way as PER_FACE, and so on.
 *   
 *   If there aren't sufficient values in the current coordinates, material, or
 *   texture coordinates, errors will occur.
 * 
 * @FILE_FORMAT_DEFAULT
 *    This is an abstract class. See the reference page of a derived class for the
 *   format and default values.
 * 
 * @SEE_ALSO
 *    SoFaceSet,
 *    SoIndexedShape,
 *    SoLineSet,
 *    SoPointSet,
 *    SoQuadMesh,
 *    SoTriangleStripSet,
 *    SoVertexProperty
 * 
 * 
 */ 

class INVENTOR_API SoNonIndexedShape : public SoVertexShape {

  SO_NODE_ABSTRACT_HEADER(SoNonIndexedShape);

 public:
  /**
   * Obsolete field, provided only for compatibility reasons. Index of first
   * coordinate of shape.
   * 
   */
  SoSFInt32           startIndex;

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  // Redefines this to invalidate normal cache
  virtual void notify(SoNotList *list);

 SoEXTENDER public:
  /**
   * This handles AABB bounding box computation for all shapes derived
   * from this class. It sets the bounding box to contain all
   * vertices of the shape, assuming that the shape uses the
   * coordinates indexed by all non-negative values in the
   * coordIndex field. It also sets the center to the average of the
   * vertices' coordinates.
   */
  virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);

  /**
   * This handles OOBB bounding box computation for all shapes derived
   * from this class. It sets the bounding box to contain all
   * vertices of the shape, assuming that the shape uses the
   * coordinates indexed by all non-negative values in the
   * coordIndex field. It also sets the center to the average of the
   * vertices' coordinates.
   */
  virtual void computeBBox(SoAction *action, SbXfBox3d &box, SbVec3d &center);

 protected:
  /** Constructor - makes this abstract */
  SoNonIndexedShape();

  /**
   * This is a convenience method to simplify the job of computing
   * AABB bounding boxes for subclasses; it can be called from a
   * subclass's computeBBox() method. It sets the given bounding box
   * to contain all vertices of the shape, assuming that the shape
   * uses the numVertices coordinates beginning at the value in
   * startIndex. (If numVertices is negative, it uses all
   * coordinates from startIndex on.) It also sets the center to the
   * average of the vertices' coordinates.
   */
  void computeCoordBBox(SoAction *action, int numVertices, SbBox3f &box, SbVec3f &center);

  /**
   * This is a convenience method to simplify the job of computing
   * OOB bounding boxes for subclasses; it can be called from a
   * subclass's computeBBox() method. It sets the given bounding box
   * to contain all vertices of the shape, assuming that the shape
   * uses the numVertices coordinates beginning at the value in
   * startIndex. (If numVertices is negative, it uses all
   * coordinates from startIndex on.) It also sets the center to the
   * average of the vertices' coordinates.
   */
  void computeCoordBBox(SoAction *action, int numVertices, SbXfBox3d &box, SbVec3d &center);

  virtual ~SoNonIndexedShape();
};

#endif /* _SO_NON_INDEXED_SHAPE_ */

