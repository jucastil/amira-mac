/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Jerome Hummel (May 2006)
**=======================================================================*/

#ifndef _SOMESHGEOMETRY_H
#define _SOMESHGEOMETRY_H

#include <LDM/nodes/SoDataSet.h>
class SoLDMFrontTile;
class SoVolumeReader;
class SoMeshGeometryLDMReader;
/**
 * @RVEXT Mesh geometry definition.
 *
 * @ingroup ReservoirVizNodes
 *
 * @DESCRIPTION
 *    Node defining the geometry of the mesh.
 *    The geometry is given by the inherited field #fileName.
 *    The specified file must be an LDM file built by the LDM converter
 *    (see SoMeshGeometryConverter).
 *
 *    This node must be inserted in the scene graph before any node inherited from
 *    SoMeshShape used to display this mesh.
 *
 *    The inherited field #dataSetId has a default value of 0. The value must be 
 *    different from the data set IDs of any SoMeshProperty nodes applied to the 
 *    mesh.
 *
 *    ReservoirViz supports the following type of meshes:
 *    The mesh is a 3D matrix of ni * nj * nk hexahedron cells. Thus each cell of
 *    the mesh has an implicit and logical position (i,j,k). 
 *
 *    Each cell can be completely disconnected from its neighbors by providing eight corner 
 *    points (for example to define faults) or the cell can share all its points with with
 *    its neighbors allowing the definition of compact meshes. 
 *    
 *    Each cell can have a flag telling if it is active or not (dead cell). Only active cells are considered during rendering. 
 *    The dead cell filtering flag is static to the file. 
 *    For dynamic filtering, use the cell filter mechanism provided by each shape (@see SoMeshShape::setCellFilterFctor).
 *
 * @FILE_FORMAT_DEFAULT
 *    MeshGeometry {
 *    @TABLE_FILE_FORMAT
 *       @TR fileName                   @TD ""
 *       @TR dataSetId                  @TD 0
 *       @TR useCompressedTexture       @TD TRUE
 *       @TR texturePrecision           @TD 8
 *       @TR ldmResourceParameters      @TD NULL
 *       @TR extent                     @TD -1,-1,-1, 1,1,1
 *       @TR customReader               @TD NULL
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *    SoCallbackAction,
 *    SoGLRenderAction,
 *    SoGetBoundingBoxAction,
 *    SoPickAction,
 *    SoWriteAction @BR
 *    Sets mesh geometry parameters in the traversal state.
 *
 * @SEE_ALSO
 *    SoDataSet,
 *    SoMeshGeometryConverter,
 *    SoMeshProperty
 *
 *
 */
class RESERVOIRVIZ_API SoMeshGeometry : public SoDataSet
{
  SO_NODE_HEADER( SoMeshGeometry );

public:

  /** Constructor. */
  SoMeshGeometry();

  /** Destructor. */
  virtual ~SoMeshGeometry();

  SoMeshGeometryLDMReader* getReader();

SoEXTENDER public:
	static void	initClass();
  static void exitClass();

SoINTERNAL public:
  virtual SoLDMFrontTile* getAppropriateFrontTile(SoLDMTileID, SbVec3i32);
  static SoVolumeReader *newAppropriateReader( const SbString& fileExt );
  virtual SoLDMReader* getAppropriateLDMReader( const SbString& pathname );
  virtual SoLDMGeomElement* getAppropriateElement(SoLDMGeometry* v);

  virtual bool isTileShrinked(int tileId);
  virtual bool hasDeadCells();
  virtual bool hasFaults();
  virtual bool isDead(size_t i, size_t j, size_t k);
  virtual SbBool updateDataTex3DPage(SoTransferFunction *, SbVec3i32 &, SoBufferObject*, SbBox3i32 &) { return TRUE; }
  virtual bool doesTileHaveDeadCells(size_t i, size_t j, size_t k);
  SoMeshGeometryLDMReader* m_geomFileReader;

  int m_meshSizeI;
  int m_meshSizeJ;
  int m_meshSizeK;
};

#endif //_SOMESHGEOMETRY_H
