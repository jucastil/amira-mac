/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MO_MESHGRIDPLANESLICE_
#define  _MO_MESHGRIDPLANESLICE_

#include <MeshVizInterface/MbVec3.h>

#include <MeshVizInterface/mapping/nodes/MoMeshRepresentation.h>

#include <Inventor/fields/SoSFPlane.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class MiGridPlaneSliceExtractUnstructured;
class MiGridPlaneSliceExtractUnstructuredIjk;
class MiGridPlaneSliceExtractIjk;
class MiVolumeMeshUnstructured;
class MiVolumeMeshUnstructuredIjk;
class MiVolumeMeshHexahedronIjk;
class MiVolumeMeshRegular;
class MiVolumeMeshRectilinear;
class MiVolumeMeshCurvilinear;

/**
 * @DTEXT  Rendering node that displays a grid plane slice of a volume mesh.
 * 
 * @ingroup MeshIViz_Mapping_Representation
 * 
 * @DESCRIPTION
 *  A grid plane slice is similar to MoMeshPlaneSlice but the plane is treated as a 
 *  regular grid on which nodes are evaluated using the probing mechanism according
 *  to the specified step size (See the SEE ALSO Section for settings). 
 *  The plane (an SbPlane) is defined by a direction vector and a distance from the origin.
 *
 *  The slice can be colored using a scalar set defined in the colorScalarSetId inherited field.
 *  This is an index into the list of scalar sets existing in the traversal state
 *  (see the MoScalarSetxxx nodes). To disable coloring set this field to -1.
 *  Rendering can be modified using various property nodes (see the SEE ALSO section).
 *
 * @FILE_FORMAT_DEFAULT
 *    MeshGridPlaneSlice {
 *    @TABLE_FILE_FORMAT
 *       @TR colorScalarSetId           @TD 0
 *       @TR parallel                   @TD TRUE
 *       @TR plane                      @TD 0,0,1,0
 *       @TR step                       @TD 1.0
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *  MoCellFilter, MoColorMapping, MoDrawStyle, MoMaterial, @BR
 *  MiGridPlaneSliceExtractIjk, 
 *  MiGridPlaneSliceExtractUnstructured, 
 *  MiGridPlaneSliceExtractUnstructuredIjk. @BR
 *  MiPointProbeUnstructured, MiPointProbeUnstructuredIjk,
 *  MiPointProbeIjk, MiPointProbeIj for probing settings.
 * 
 */

class MESHIVIZDM_API MoMeshGridPlaneSlice : public MoMeshRepresentation {

  SO_NODE_HEADER(MoMeshGridPlaneSlice) ;

 public:

  /**
   * Constructor.
   */
  MoMeshGridPlaneSlice() ;

  /**
   * Position of the grid plane slice. Z=0 plane by default.
   */
  SoSFPlane  plane;

  /**
   * Step between nodes defining grid density. Default is 1.
   */
  SoSFFloat  step;

  //@{
  /** 
  * Get extractor for reuse outside this node. 
  * @note The returned pointer may be null if a mesh has not been set in the scene graph 
  * or if no render action has traversed the scene graph.
  */
  const MiGridPlaneSliceExtractUnstructured*     getUnstructuredExtractor();
  const MiGridPlaneSliceExtractUnstructuredIjk*  getUnstructuredIjkExtractor();
  const MiGridPlaneSliceExtractIjk*              getIjkExtractor();
  //@}

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 SoEXTENDER public:
  virtual void doExtract(SoAction *action);
  virtual const MiMesh* getExtractedMesh(MeshType& meshType);

  // computes the extract of the data set corresponding to the given index in the state list from the current representation's extractor.
  // Grid Plane Slice returns always MiScalardSetIj
  const MiScalardSetIj* extractScalarSetIj(SoState * state,size_t scalarSetId) ;

  // computes the extract of the data set corresponding to the given index in the state list from the current representation's extractor.
  // a grid always returns a MiVec3dSetIj
  const MiVec3dSetIj* extractVec3SetIj(SoState * state,size_t vec3SetId);

 protected:
  virtual ~MoMeshGridPlaneSlice() ;  

  virtual void clear();
  virtual void computePlane(MbVec3d& normal, double& distance);

  template<typename _MeshInterface, typename _Extractor, typename _ScalarSet, typename _CellFilter>
  void doExtract(SoState * state,const _MeshInterface* mesh, _Extractor** extractor);

  template<typename _Extractor, typename _ScalarSet, typename _CellFilter>
  void extract(SoState * state,_Extractor* extractor,const _ScalarSet* colorSet, const _CellFilter *cellFilter);

  // Extractors used internally
  MiGridPlaneSliceExtractUnstructured*    m_gridPlaneSliceExtractU;
  MiGridPlaneSliceExtractUnstructuredIjk* m_gridPlaneSliceExtractUIjk;
  MiGridPlaneSliceExtractIjk*             m_gridPlaneSliceExtractIjk;

} ;

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MO_MESHGRIDPLANESLICE_ */



