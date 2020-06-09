/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MO_MESHOUTLINE_
#define  _MO_MESHOUTLINE_

#include <MeshVizInterface/mesh/MiSurfaceMeshUnstructured.h>
#include <MeshVizInterface/MbVec3.h>

#include <MeshVizInterface/mapping/nodes/MoMeshRepresentation.h>

#include <Inventor/fields/SoSFPlane.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class MiOutlineExtractUnstructured;
class MiOutlineExtractUnstructuredIjk;
class MiOutlineExtractIjk;
class MiOutlineExtractIj;

class MiSurfaceMeshUnstructured;
class MiVolumeMeshUnstructured;
class MiVolumeMeshUnstructuredIjk;
class MiVolumeMeshHexahedronIjk;
class MiVolumeMeshRegular;
class MiVolumeMeshRectilinear;
class MiVolumeMeshCurvilinear;

/**
 * @DTEXT  Rendering node that displays the outline of a mesh.
 * 
 * @ingroup MeshIViz_Mapping_Representation
 * 
 * @DESCRIPTION
 *  The outline of a mesh is an unstructured line mesh made up of all the edges that belong to only 
 *  one cell. Internal edges of a mesh will not be displayed except when they are adjacent to dead cells.
 *
 *  The outline can be colored using a scalar set specified in the colorScalarSetId inherited field. 
 *  This is an index into the list of scalar sets existing in the traversal state
 *  (see the MoScalarSetxxx nodes). To disable coloring set this field to -1.
 *
 * @FILE_FORMAT_DEFAULT
 *    MeshOutline {
 *    @TABLE_FILE_FORMAT
 *       @TR colorScalarSetId           @TD 0
 *       @TR parallel                   @TD TRUE
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *  MiOutlineExtractIj,
 *  MiOutlineExtractIjk,
 *  MiOutlineExtractUnstructured,
 *  MiOutlineExtractUnstructuredIjk
 *
 */

class MESHIVIZDM_API MoMeshOutline : public MoMeshRepresentation {

  SO_NODE_HEADER(MoMeshOutline) ;

 public:

  /**
   * Constructor.
   */
  MoMeshOutline() ;

  //@{
  /** 
  * Get extractor for reuse outside this node. 
  * @note  The returned pointer may be null if a mesh has not been set in the scene graph 
  * or if no render action traversal has been done yet.
  */
  const MiOutlineExtractUnstructured* getUnstructuredExtractor();
  const MiOutlineExtractUnstructuredIjk* getUnstructuredIjkExtractor();
  const MiOutlineExtractIjk* getIjkExtractor();
  const MiOutlineExtractIj*  getIjExtractor();
  //@}

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 SoEXTENDER public:
  virtual void doExtract(SoAction *action);
  virtual const MiMesh* getExtractedMesh(MeshType& meshType);

  // computes the extract of the data set corresponding to the given index in the state list from the current representation's extractor.
  // a outline always returns a MiScalardSetI
  const MiScalardSetI* extractScalarSetI(SoState * state,size_t scalarSetId) ;

  // computes the extract of the data set corresponding to the given index in the state list from the current representation's extractor.
  // a outline always returns a MiVec3dSetI
  const MiVec3dSetI* extractVec3SetI(SoState * state,size_t vec3SetId);

 protected:
  virtual ~MoMeshOutline() ;  

  void clear();

  template<typename _MeshInterface, typename _Extractor, typename _ScalarSet, typename _CellFilter>
  void doExtract(SoState * state,const _MeshInterface* mesh, _Extractor** extractor);

  template<typename _Extractor, typename _ScalarSet, typename _CellFilter>
  void extract(SoState * state,_Extractor* extractor,const _ScalarSet* colorSet,const _CellFilter *cellFilter);

  // Extractors used internally
  MiOutlineExtractUnstructured*    m_outlineExtractU;
  MiOutlineExtractUnstructuredIjk* m_outlineExtractUIjk;
  MiOutlineExtractIjk*             m_outlineExtractIjk;
  MiOutlineExtractIj*             m_outlineExtractIj;

} ;

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MO_MESHOUTLINE_ */



