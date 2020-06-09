/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Thierry Dufour (Aug 2002)
** Modified by : Jerome Hummel (MMM yyyy)
**=======================================================================*/
#ifndef __VOLUME_FACE_SET
#define __VOLUME_FACE_SET

#include <Inventor/nodes/SoFaceSet.h>

#include <VolumeViz/nodes/SoVolumeGeometry.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>

class SoVolumeFaceSetDl;
class SoVolumeGeometryVbo;

/**
 * @VREXT Polygonal face shape node for volume data.
 *
 * @ingroup VolumeVizNodes
 *
 * @DESCRIPTION
 *   This node defines a shape which is the intersection of the volume data
 *   defined by an SoVolumeData node and the 3D shape formed by constructing
 *   faces (polygons) from vertices located at the coordinates specified in
 *   the #vertexProperty field (from SoVertexShape) or the current inherited
 *   state.
 *
 *   The shape defined by this intersection is textured using the data
 *   from the current SoVolumeData node and SoTransferFunction node.
 *   For optimal performance, use of the #vertexProperty field is recommended
 *   and the page size (SoVolumeData::setPageSize()) should be as large as
 *   possible.
 *
 *   The #interpolation field controls how the texture is interpolated.
 *
 *   When set to FALSE, the #clipGeometry field allows rendering of the
 *   portion of the geometry that does not intersect the volume data. This
 *   portion is not textured and is rendered as a regular SoFaceSet.
 *
 *   Note: This node uses 3D texturing and is not available if the hardware does not
 *   support this feature.
 *
 *   SoVolumeFaceSet uses the coordinates in order, starting with the first one.
 *   Each face has a number of vertices specified by a value in the #numVertices
 *   field. For example, an SoVolumeFaceSet with #numVertices of [3,4,4] would use
 *   coordinates 1, 2, and 3 for the first face, coordinates 4, 5, 6, and 7 for the
 *   second face, and coordinates 8, 9, 10, and 11 for the third. For improved
 *   performance, arrange all the faces with only 3 vertices at the beginning of the
 *   list, then all faces with 4 vertices, and finally all other faces.
 *
 *   The number of values in the #numVertices field indicates the number of
 *   faces in the set.
 *
 *   The coordinates of the face set are transformed by the current cumulative
 *   transformation. The faces are drawn with the current light model and drawing
 *   style.
 *
 *   Treatment of the current material and normal binding is as follows: The PER_PART
 *   and PER_FACE bindings specify a material or normal for each face. The _INDEXED
 *   bindings are equivalent to their non-indexed counterparts. The default material
 *   binding is OVERALL. The default normal binding is PER_VERTEX.
 *
 *   If any normals (or materials) are specified, Open Inventor assumes you
 *   have provided
 *   the correct number of them, as indicated by the binding. You will see unexpected
 *   results if you specify fewer normals (or materials) than the shape requires. If
 *   no normals are specified, they will be generated automatically.
 *
 *   If any texture coordinates are specified, SoVolumeFaceSet simply ignores them.
 *
 *   NOTE: A face set may render or pick incorrectly if any of its polygons are
 *   self-intersecting or non-planar.
 *
 *     Note: The volume size and orientation (like geometry) can be modified by
 *     transformation nodes in the scene graph and this in turn modifies the
 *     appearance of volume rendering nodes like SoVolumeFaceSet.
 *     However the same transformation must be applied to the volume data node
 *     and all volume rendering nodes associated with that volume.  So effectively
 *     any transformation nodes that affect the volume must be placed @B before @b
 *     the volume data node.
 *
 * @FILE_FORMAT_DEFAULT
 *    VolumeFaceSet {
 *    @TABLE_FILE_FORMAT
 *       @TR vertexProperty   @TD NULL
 *       @TR startIndex       @TD 0
 *       @TR numVertices      @TD -1
 *       @TR clipGeometry     @TD TRUE
 *       @TR offset           @TD 0
 *       @TR interpolation    @TD LINEAR
 *       @TR useVbo           @TD TRUE
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *    @B SoGLRenderAction @b @BR
 *        Draws faces based on the current coordinates, normals, materials, drawing
 *        style, and so on.
 *
 *    @B SoRayPickAction @b @BR
 *        Picks faces based on the current coordinates and transformation. Details about
 *        the intersection are returned in an SoFaceDetail.
 *
 *    @B SoGetBoundingBoxAction @b @BR
 *        Computes the bounding box that encloses all vertices of the face set with the
 *        current transformation applied to them. Sets the center to the average of the
 *        coordinates of all vertices.
 *
 *    @B SoCallbackAction @b @BR
 *        If any triangle callbacks are registered with the action, they will be invoked
 *        for each successive triangle generated from each face in the set.
 *
 *
 * @SEE_ALSO
 *    SoVolumeData,
 *    SoTransferFunction,
 *    SoROI,
 *    SoCoordinate3,
 *    SoDrawStyle,
 *    SoVolumeIndexedFaceSet,
 *    SoVolumeIndexedTriangleStripSet,
 *    SoVolumeTriangleStripSet,
 *    SoFaceDetail,
 *    SoVertexProperty
 *
 *
 */

class VOLUMEVIZ_API SoVolumeFaceSet : public SoFaceSet, public SoVolumeGeometry
{
  SO_NODE_HEADER(SoVolumeFaceSet);

public :

  /**
   * Specifies to clip the geometry at the volume boundaries.
   * The SoROI node also affects the clipping process. Default is TRUE.
   */
  SoSFBool clipGeometry;

  /**
   * Sets an offset value used for computing the texture coordinates.
   * The texture coordinate for each vertex will be taken from a point @B offset @b
   * units away from the vertex.
   * The offset is measured in the direction of the vertex normal.
   * By default the offset is equal to 0 (no offset). When using this feature,
   * a vertex normal must exist for every vertex. If vertex normals are not
   * supplied, Open Inventor will compute vertex normals in the usual way except
   * that the crease angle will be fixed at PI in order to assure that a vertex
   * normal is computed at every vertex.
   */
  SoSFFloat offset;

  /** Interpolation mode */
  enum Interpolation {
    /** Nearest */
    NEAREST,
    /** Linear (Default) */
    LINEAR
  };

  /**
   * Texture interpolation. @BR
   * Use enum #Interpolation. Default is LINEAR.
   */
  SoSFEnum interpolation;

  /**
   * @deprecated. Use the SoShapeHints::useVBO field to enable or disable use of Vextex Buffer Objects for rendering. @BR
   * Default is TRUE.
   * If set to TRUE then SoShapeHints::useVBO is used.
   * If set to FALSE then VBO usage is disabled.
   * @DEPRECATED_SINCE_OIV 8.5
   */
  SoSFBool useVbo;

  /**
   * Constructor.
   */
  SoVolumeFaceSet();

SoEXTENDER public:
  static void initClass();
  static void exitClass();

  // Implements actions
  virtual void	GLRender(SoGLRenderAction *action);
  virtual void computeBBox(SoAction *action, SbBox3f &box,
                           SbVec3f &center);
SoINTERNAL public:
  /** Handle field change */
  virtual void notify(SoNotList *list);

protected:
  /** Render the inventor shape */
  virtual void shapeRender(SoGLRenderAction* action);

  /** Render the bounding box for the given shape */
  virtual void GLRenderBoundingBox(SoGLRenderAction* action);

  /** Convert triangle strip to indexed triangles */
  virtual void generateIndices();

  /** Set indices for vbo rendering */
  virtual void setupVbo();

  /** Create needed render interfaces */
  virtual void createRenderInterfaces();

  /** Really compute the bounding box for the shape */
  virtual void getBBox(SoAction *action, SbBox3f &box, SbVec3f &center);

  /** return the number of vertices to render might be -1 if not yet defined */
  virtual int getNumPrim();

  using SoVolumeGeometry::doRendering;

private:
  int m_numPrim;
};

#endif //__VOLUME_FACE_SET
