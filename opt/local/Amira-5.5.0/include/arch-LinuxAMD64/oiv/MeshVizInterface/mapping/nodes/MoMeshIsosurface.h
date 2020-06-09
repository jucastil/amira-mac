/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MO_MESHISOSURFACE_
#define  _MO_MESHISOSURFACE_

#include <MeshVizInterface/mesh/MiSurfaceMeshUnstructured.h>
#include <MeshVizInterface/MbVec3.h>

#include <MeshVizInterface/mapping/nodes/MoMeshRepresentation.h>

#include <Inventor/fields/SoSFFloat.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class MiIsosurfExtractUnstructured;
class MiIsosurfExtractUnstructuredIjk;
class MiIsosurfExtractIjk;
class MiVolumeMeshUnstructured;
class MiVolumeMeshUnstructuredIjk;
class MiVolumeMeshHexahedronIjk;
class MiVolumeMeshRegular;
class MiVolumeMeshRectilinear;
class MiVolumeMeshCurvilinear;

/**
 * @DTEXT  Rendering node that displays an isosurface of a volume mesh.
 * 
 * @ingroup MeshIViz_Mapping_Representation
 * 
 * @DESCRIPTION
 *  An isosurface is an unstructured surface mesh defined by all the points having the specified value 
 *  in the scalar data set. 
 *  The scalar set used to extract the isosurface is defined by the inherited isoScalarSetId field. 
 *  This is an index into the list of scalar sets existing in the traversal state
 *  (see the MoScalarSetxxx nodes).  If this scalar set is defined per cell, a new internal dataset 
 *  bound per node will be automatically computed and cached to perform the isosurface extraction.
 *
 *  The isosurface can be colored using a scalar set defined in the colorScalarSetId inherited field.
 *  To disable coloring set this field to -1.
 *  Rendering can be modified using various property nodes (see the SEE ALSO section).
 *
 * @note When applied to an unstructured volume mesh (see MiVolumeMeshUnstructred) with undefined 
 *       MiVolumeCell::getIsosurfTopology(), for instance in polyhedral cells and non-linear cells, 
 *       an MoTessellator node must be added to the scenegraph beforehand. 
 *
 * @FILE_FORMAT_DEFAULT
 *    MeshIsosurface {
 *    @TABLE_FILE_FORMAT
 *       @TR colorScalarSetId           @TD 0
 *       @TR parallel                   @TD TRUE
 *       @TR isovalue                   @TD 0.0
 *       @TR isoScalarSetId             @TD 0
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *  MoCellFilter, MoColorMapping, MoDrawStyle, MoMaterial, MoTessellator @BR
 *  MiIsosurfExtractIjk, 
 *  MiIsosurfExtractUnstructured,
 *  MiIsosurfExtractUnstructuredIjk
 * 
 */

class MESHIVIZDM_API MoMeshIsosurface : public MoMeshRepresentation {

  SO_NODE_HEADER(MoMeshIsosurface) ;

 public:

  /**
   * Constructor.
   */
  MoMeshIsosurface() ;

  /**
   * Isovalue to display. Default is 0.0.
   */
  SoSFFloat  isovalue;

  /**
  * Field representing the scalar set node to be used to compute the iso value.
  * During traversal of the scene graph, scalar set nodes are accumulated in
  * a list of scalar sets.  isoScalarSetId is an index into this list. Default is 0.
  * If this scalar set is defined per cell, a new internal dataset 
  * defined per node will be automatically computed and cached to perform the isosurface extraction.
   */
  SoSFInt32  isoScalarSetId;

  //@{
  /** 
  * Get extractor for reuse outside this node. 
  * @note  The returned pointer may be null if a mesh has not been set in the scene graph 
  * or if no render action has traversed the scene graph. 
  * Use the method corresponding to the type of mesh stored in the scene graph. 
  * 
  */
  const MiIsosurfExtractUnstructured*    getUnstructuredExtractor();
  const MiIsosurfExtractUnstructuredIjk* getUnstructuredIjkExtractor();
  const MiIsosurfExtractIjk*             getIjkExtractor();
  //@}

  /** 
  * @deprecated use getIjkExtractor() instead.
  * @DEPRECATED_SINCE_OIV 8.5
  */
  const MiIsosurfExtractIjk*             getRegularExtractor();

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 SoEXTENDER public:
  virtual void doExtract(SoAction *action);
  virtual const MiMesh* getExtractedMesh(MeshType& meshType);

  // computes the extract of the data set corresponding to the given index in the state list from the current representation's extractor.
  virtual const MiScalardSetI* extractScalarSetI(SoState * state,size_t scalarSetId) ;

  // computes the extract of the data set corresponding to the given index in the state list from the current representation's extractor.
  virtual const MiVec3dSetI* extractVec3SetI(SoState * state,size_t vec3SetId) ;


 protected:
  virtual ~MoMeshIsosurface() ;  

  void clear();

  template<typename _MeshInterface, typename _Extractor, typename _ScalarSet, typename _ColorScalarSet, typename _CellFilter>
  void doExtract(SoState * state,const _MeshInterface* mesh, _Extractor** extractor);

  template<typename _Extractor, typename _ScalarSet, typename _ColorScalarSet, typename _CellFilter>
  void extract(SoState * state,_Extractor* extractor,const _ColorScalarSet* colorSet,const _CellFilter *cellFilter);

  // Extractors used internally
  MiIsosurfExtractUnstructured*    m_isoExtractU;
  MiIsosurfExtractUnstructuredIjk* m_isoExtractUIjk;
  MiIsosurfExtractIjk*             m_isoExtractIjk;

} ;

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MO_MESHISOSURFACE_ */



