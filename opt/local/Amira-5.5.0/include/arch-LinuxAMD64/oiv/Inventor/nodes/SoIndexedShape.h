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


#ifndef  _SO_INDEXED_SHAPE_
#define  _SO_INDEXED_SHAPE_

#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/nodes/SoVertexShape.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoIndexedShape
//
//  Abstract indexed shape node class. All nodes derived from this
//  (such as SoIndexedFaceSet and SoIndexedLineSet) are shapes
//  that are constructed from vertices defined by indexing into the
//  current coordinates. The coordinate indices are stored in the
//  coordIndex field, which is used by all subclasses.
//
//  One rule is used: all coordinate indices less than 0 may be used
//  for special purposes, such as to denote the end of a face or
//  polyline. This means that all indices < 0 can be ignored safely
//  when looking at vertices.
//
//  Depending on the current material, normal, and texture coordinate
//  binding values, materials, normals, and texture coordinates may be
//  accessed in order or may be indexed using the materialIndex,
//  normalIndex, and textureCoordIndex fields.
//
//////////////////////////////////////////////////////////////////////////////
class SoFieldSensor ;

/**
 * Abstract base class for all indexed vertex-based shapes.
 * 
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 *   This node is the abstract base class for all vertex-based shapes that are
 *   constructed from indices, including SoIndexedFaceSet, SoIndexedTriangleStripSet,
 *   and SoIndexedLineSet. SoIndexedShape defines fields that are used in all of its
 *   subclasses.
 *   
 *   All subclasses of SoNonIndexedShape construct objects by using the coordinates
 *   specified by the #vertexProperty field (from SoVertexShape), or the
 *   current inherited coordinates. The #coordIndex field defined by this class
 *   contains the indices into the current coordinates of the vertices of the shape.
 *   These indices are also used for materials, normals, or texture coordinates when
 *   the appropriate binding is PER_VERTEX_INDEXED.
 *   
 *   Material and normal bindings are interpreted as follows for each subclass:
 *   
 *   
 *      @TABLE_0B
 *         @TR OVERALL             @TD One material for the entire shape.
 *         @TR PER_PART            @TD Specific to the subclass.
 *         @TR PER_PART_INDEXED    @TD Same as PER_PART, using indices from the #materialIndex or
 *   #normalIndex field.
 *         @TR PER_FACE            @TD Specific to the subclass.
 *         @TR PER_FACE_INDEXED    @TD Same as PER_FACE, using indices from the #materialIndex or
 *   #normalIndex field.
 *         @TR PER_VERTEX          @TD One material per vertex.
 *         @TR PER_VERTEX_INDEXED  @TD One material per vertex, using indices from the #materialIndex or
 *   #normalIndex field.
 *      @TABLE_END 
 *   
 *   When any _INDEXED binding is used for materials or normals, the
 *   #materialIndex or #normalIndex field is used to determine the
 *   indices for the materials or normals. If this field contains a single value of
 *   -1 (the default), the coordinate indices from the #coordIndex field are
 *   used as well for materials or normals. When the binding is PER_VERTEX_INDEXED,
 *   indices in these fields that correspond to negative indices in #coordIndex
 *   are skipped; for other index bindings all the values in the fields are used, in
 *   order.
 *   
 *   Explicit texture coordinates (as defined by SoTextureCoordinate2) may be bound to
 *   vertices of an indexed shape consecutively (if the texture coordinate binding is
 *   PER_VERTEX) or by using the indices in the #textureCoordIndex field (if
 *   the binding is PER_VERTEX_INDEXED). As with all vertex-based shapes, if there is
 *   a current texture but no texture coordinates are specified, a default texture
 *   coordinate mapping is calculated using the bounding box of the shape.
 *   
 *   Be sure that the indices contained in the #coordIndex,
 *   #materialIndex, #normalIndex, and #textureCoordIndex fields
 *   are valid with respect to the current state, or errors will occur.
 * 
 * @FILE_FORMAT_DEFAULT
 *    This is an abstract class. See the reference page of a derived class for the
 *   format and default values.
 * 
 * @SEE_ALSO
 *    SoIndexedFaceSet,
 *    SoIndexedLineSet,
 *    SoIndexedTriangleStripSet,
 *    SoMaterialBinding,
 *    SoNonIndexedShape,
 *    SoNormalBinding,
 *    SoShapeHints,
 *    SoTextureCoordinateBinding
 * 
 * 
 */ 

class INVENTOR_API SoIndexedShape : public SoVertexShape {

  SO_NODE_ABSTRACT_HEADER(SoIndexedShape);

 public:
  /**
   * The indices of the coordinates that the shape uses as its vertices. The
   * coordinates connect to form faces, lines, or other shapes. Each subclass defines
   * special negative indices to use to indicate separation between faces, lines, and
   * so on.
   */
  SoMFInt32           coordIndex;
  /**
   * The indices of the materials that are used for
   * the shape. This field is used only when the material binding is one of the
   * _INDEXED bindings. By default, the value of this field indicates that the
   * coordinate indices should be used for materials as well.
   */
  SoMFInt32           materialIndex;
  /**
   * The indices of the normals that are used for
   * the shape. This field is used only when the normal binding is one of the
   * _INDEXED bindings. By default, the value of this field indicates that the
   * coordinate indices should be used for normals as well.
   */
  SoMFInt32           normalIndex;
  /**
   * The indices of the texture coordinates that are used for
   * the shape. This field is used only when the texture coordinate binding is one of the
   * _INDEXED bindings. By default, the value of this field indicates that the
   * coordinate indices should be used for texture coordinates as well.
   */
  SoMFInt32           textureCoordIndex;

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
  
  /**
   * This handles pointPicking mode.
   */
  virtual void rayPick(SoRayPickAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  // Constructor - makes this abstract
  SoIndexedShape();

  // max auto caching test
  virtual int getMaxTestValueForAutoCache()
  {return coordIndex.getNum();}

  // auto caching test
  virtual int getMinTestValueForAutoCache()
  {return coordIndex.getNum();}

  // Returns TRUE if texture coordinates should be indexed
  static SbBool       areTexCoordsIndexed(SoAction *action);

  // Starting at a given index in the coordIndex array, figure out
  // how many vertices there are before either the end of the array
  // or the next 'border' index
  int getNumVerts(int startCoord);

  // Setup for fast rendering.  This should be called by subclasses,
  // which can then use the textureI/colorI/normalI arrays (which
  // will either point to one of the coordIndex arrays, or to a
  // consective array of integers.  This must be called AFTER the
  // vpCache has been filled in.
  void                setupIndices(int numParts, int numFaces,
                                   SbBool needNormals, SbBool needTexCoords,
                                   SbBool needTexCoords3);

  // These must not be called unless setupIndices has been called first:
  const int32_t *     getNormalIndices() const
    { return (normalI ? normalI : getConsecutiveIndices()); }
  const int32_t *     getColorIndices() const 
    { return (colorI ? colorI : getConsecutiveIndices()); }
  const int32_t *     getTexCoordIndices() const 
    { return (texCoordI ? texCoordI : getConsecutiveIndices()); }

  // return the greatest indice used.
  virtual int32_t getMaxVertexUsed() const;

  // return the number of vertex to use
  virtual int32_t getNumVertexUsed() const;

  // Keep indices up to date if things change
  virtual void        notify(SoNotList *list);

  virtual ~SoIndexedShape();

  // helper function used internally to build connectivity of an indexed shape
  static inline void updateConnectivity(const int curVert, const int _index, int32_t *connectIndex, int32_t *connectivity);

 private:

  // Internal routines used to allocate sequential indices so the
  // same rendering loops can be used for indexed or non-indexed
  // cases:
  int32_t* allocateSequentialWithHoles();

  // These are filled in by the setupIndices routine:
  const int32_t *texCoordI;
  const int32_t *colorI;
  const int32_t *normalI;

  unsigned char materialBinding;
  unsigned char normalBinding;
  unsigned char texCoordBinding;

  mutable int32_t m_maxVertexUsed;
  mutable int32_t m_numVertexUsed;
  
  bool bAlloc_texCoordI;  // == true if texCoordI was allocated
  bool bAlloc_colorI;     // == true if colorI  was allocated
  bool bAlloc_normalI;    // == true if normalI was allocated
};

// inline functions declaration
void 
SoIndexedShape::updateConnectivity(const int curVert, const int _index, int32_t *connectIndex, int32_t *connectivity)
{
  if ( _index >=0 )
  {
    int32_t lastConnect = connectIndex[_index];
    if ( lastConnect==-1 )
    {
      connectivity[curVert]= curVert;
    }
    else
    {
      connectivity[curVert] = connectivity[lastConnect];
      connectivity[lastConnect] = curVert;
    }
    connectIndex[_index] = curVert;
  }
}

#endif /* _SO_INDEXED_SHAPE_ */

