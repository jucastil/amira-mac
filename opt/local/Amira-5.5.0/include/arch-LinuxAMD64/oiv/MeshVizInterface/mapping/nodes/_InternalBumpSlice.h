#ifndef HIDDEN_FROM_DOC

/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

/*=======================================================================

***********************INTERNAL USE ONLY*********************************

*********************** DO NOT USE **************************************

**=======================================================================*/

#ifndef _MO_MESHBUMPSLICE_
#define _MO_MESHBUMPSLICE_

#include <MeshVizInterface/mapping/nodes/MoMeshPlaneSlice.h>

#include <Inventor/SbColorRGBA.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class MiPlaneSliceExtractUnstructured;
class MiPlaneSliceExtractUnstructuredIjk;
class MiPlaneSliceExtractIjk;
class MiVolumeMeshUnstructured;
class MiVolumeMeshUnstructuredIjk;
class MiVolumeMeshHexahedronIjk;
class MiVolumeMeshRegular;
class MiVolumeMeshRectilinear;
class MiVolumeMeshCurvilinear;
class MiTopologyExplicitI;
class MiGeometryI;
class MdBumpMapping;


/**
* @DTEXT  INTERNAL USE ONLY, Rendering node that displays a bump slice from a plane of a volume mesh.
* 
* @ingroup MeshIViz_Mapping_Representation
* 
* @DESCRIPTION
*  A bump slice is based on an unstructured surface mesh defined by the intersection of 
*  an arbitrary plane with a volume mesh. This surface is rendered using a bump mapping 
*  method, using a depth parameter to compute the bump value.
*  The plane (an SbPlane) is defined by a direction vector and a distance from the origin.
*
*
* @FILE_FORMAT_DEFAULT
*    MeshBumpSlice {
*    @TABLE_FILE_FORMAT
*       @TR colorScalarSetId           @TD 0
*       @TR depth                      @TD 10.0
*       @TR parallel                   @TD TRUE
*       @TR plane                      @TD 0,0,1,0
*    @TABLE_END
*    }
*
* @SEE_ALSO
*  MoCellFilter, MoColorMapping, MoDrawStyle, MoMaterial, @BR
*  MiPlaneSliceExtractIjk,
*  MiPlaneSliceExtractUnstructured,
*  MiPlaneSliceExtractUnstructuredIjk
* 
*/
class MESHIVIZDM_API MoMeshBumpSlice : public MoMeshPlaneSlice {
  
  SO_NODE_HEADER( MoMeshBumpSlice );

public:

  /**
   * Constructor.
   */
  MoMeshBumpSlice();

  /**
   * The bump factor can be set to control bump mapping value.
   */
  SoSFFloat bumpFactor;

  /*----------------------------------------------------------------------------*/
  SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  SoEXTENDER public:
  virtual void doAction( SoAction *action );

  /**
   * Modify the main color used in shader
   */
  void setColor( const SbVec4f& color );

  /**
   * Return Surface Mesh node.
   */
  virtual MoSurfaceMesh* getSurfaceMeshNode();

protected:

  /**
   * Destructor.
   */
  virtual ~MoMeshBumpSlice();

  virtual void clear();

private:
  // get the cell filter from the state and check it is the good type
  template < typename _CellFilter >
  static const _CellFilter*   getCellFilter(SoState* state);

  // Find initial volume bounds
  void findVolumeBounds( SoAction* action );

  /**
  * Update bump factor parameter in shader
  */
  void updateBumpFactor();

  MdBumpMapping* m_bumpMapping;
};

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MO_MESHBUMPSLICE_ */



#endif //HIDDEN_FROM_DOC