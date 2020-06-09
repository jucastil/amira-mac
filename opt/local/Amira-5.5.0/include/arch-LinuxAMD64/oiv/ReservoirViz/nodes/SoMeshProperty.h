/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Thierry Dufour (May 2006)
**=======================================================================*/

#ifndef _SOMESHPROPERTY_H
#define _SOMESHPROPERTY_H

#include <LDM/nodes/SoDataSet.h>
class SoLDMFrontTile;
class SoVolumeReader;

/**
* @RVEXT Mesh property data set definition.
*
* @ingroup ReservoirVizNodes
*
* @DESCRIPTION
*    Node defining a property data set associated with the mesh.
*    The property is given by the inherited field #fileName.
*    The given file must be an LDM file built by the LDM converter
*    (see SoBaseLDMConverter).
*
*    This node must be inserted in the scene graph before any node inherited from
*    SoMeshShape used to display this mesh. Obviously, a node defining
*    the mesh geometry (see SoMeshGeometry) must also be inserted.
*
*    Multiple SoMeshProperty nodes can be inserted in a scene graph and combined
*    together in the GPU to do render compositing (SoShaderProgram).
*    However the default fragment shader in ReservoirViz applies only the inherited
*    property having the #dataSetId of 1. (Note: 1 is the default value of the
*    #dataSetId field).
*
*    In order to compose several data sets in the GPU, all of the property nodes inherited
*    during the scene graph traversal must have a different value for their
*    #dataSetId field, and a custom fragment shader must be inserted in the scene graph
*    (see SoShaderProgram). The #dataSetId field is used to differentiate
*    SoMeshProperty nodes when doing render compositing.
*
*    Render compositing is a way of combining multiple data sets at render time
*    using a fragment shader. The data sets can each have their own transfer function
*    or they can all use the same one.
*    Render compositing can be used, for example, to realize
*    RGB blending with a different input for each channel (multi-channel rendering).
*    The number of data sets to compose is limited by the number of OpenGL texture
*    units supported by the graphics board. This number is returned by the
*    #getMaxNumDataSets function.
*
*   Some rules must be observed when doing render compositing:
*   - Compositing will only be enabled between SoMeshProperty nodes having different #dataSetId
*     field values.
*   - SoMeshProperty nodes used for a specific composition must all have the same data set dimensions
*     (number of cells in I, J, and K).
*   - Each SoMeshProperty node has its own resource settings (see SoLDMResourceParameters).
*     The resources required for the composition is the sum of the resources from
*     all of the SoDataSet nodes involved.
*
*   When using a fragment shader to do render compositing, texture coordinates can be retrieved from
*   texture unit 0.
*   By default all transfer functions (see SoTransferFunction) are stored in a 2D image in texture unit 0.
*   However this default behavior can be changed through SoPreferences using the variable
*   IVVR_TF_TEX_UNIT.
*   You must not set #dataSetID to the texture unit used to store the transfer functions.
*
*
* @FILE_FORMAT_DEFAULT
*    MeshProperty {
*    @TABLE_FILE_FORMAT
*       @TR dataSetId       @TD 1
*    @TABLE_END
*    }
*
* @SEE_ALSO
*    SoDataSet,
*    SoConverter,
*    SoMeshGeometry,
*    SoMeshShape,
*    SoShaderProgram
*
*
*/
class RESERVOIRVIZ_API SoMeshProperty : public SoDataSet
{
  SO_NODE_HEADER( SoMeshProperty );

public:

  /**
   * Constructor.
   */
  SoMeshProperty();

  /**
   * Destructor.
   */
  virtual ~SoMeshProperty();

  /** 
  * Returns the property value at the given position.
  * This method can be used in cell filters functors used in shapes when applying data filtering.
  * @param (i,j,k) indices of the cell to be checked.
  */
  float getPropValue(size_t i, size_t j, size_t k);

SoEXTENDER public:
	static void initClass();
  static void exitClass();

SoINTERNAL public:

  virtual SoLDMFrontTile* getAppropriateFrontTile( SoLDMTileID, SbVec3i32 );
  static SoVolumeReader *newAppropriateReader( const SbString& fileExt );
  virtual SoLDMReader* getAppropriateLDMReader( const SbString& pathname );
  virtual SoLDMGeomElement* getAppropriateElement( SoLDMGeometry* v );

private:
  size_t ijk2i(size_t i, size_t j, size_t k) const;
  float * m_tileProp;
  SoLDMTileID m_lastTileID;
  SbVec3i32 m_tileDim;

};

#endif //_SOMESHPROPERTY_H
