/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MO_MESHSPHERESLICE_
#define  _MO_MESHSPHERESLICE_

#include <MeshVizInterface/MbVec3.h>

#include <MeshVizInterface/mapping/nodes/MoMeshRepresentation.h>

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec3f.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class MiSphereSliceExtractUnstructured;
class MiSphereSliceExtractUnstructuredIjk;
class MiSphereSliceExtractIjk;
class MiVolumeMeshUnstructured;
class MiVolumeMeshUnstructuredIjk;
class MiVolumeMeshHexahedronIjk;
class MiVolumeMeshRegular;
class MiVolumeMeshRectilinear;
class MiVolumeMeshCurvilinear;

/**
 * @DTEXT  Rendering node that displays a sphere slice of a volume mesh.
 * 
 * @ingroup MeshIViz_Mapping_Representation
 * 
 * @DESCRIPTION
 *  A sphere slice is an unstructured surface mesh defined by the intersection of a 
 *  sphere with a volume mesh. The sphere is defined by its center position and radius.
 *
 *  The slice can be colored using a scalar set defined in the colorScalarSetId inherited field.
 *  This is an index into the list of scalar sets existing in the traversal state
 *  (see the MoScalarSetxxx nodes). To disable coloring set this field to -1.
 *  Rendering can be modified using various property nodes (see the SEE ALSO section).
 *
 * @FILE_FORMAT_DEFAULT
 *    MeshSphereSlice {
 *    @TABLE_FILE_FORMAT
 *       @TR colorScalarSetId           @TD 0
 *       @TR parallel                   @TD TRUE
 *       @TR center                     @TD 0,0,0
 *       @TR radius                     @TD 1.0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *  MoCellFilter, MoColorMapping, MoDrawStyle, MoMaterial, @BR
 *  MiSphereSliceExtractIjk,
 *  MiSphereSliceExtractUnstructured,
 *  MiSphereSliceExtractUnstructuredIjk
 *
 */

class MESHIVIZDM_API MoMeshSphereSlice : public MoMeshRepresentation {

  SO_NODE_HEADER(MoMeshSphereSlice) ;

 public:

  /**
   * Constructor.
   */
  MoMeshSphereSlice() ;

  /**
   * Specifies the shpere's center. Default is 0,0,0.
   */
  SoSFVec3f center;

  /**
   * Specifies the sphere's radius. Value must be greater than 0.0. Default is 1.
   */
  SoSFFloat radius;

  //@{
  /** 
  * Get extractor for reuse outside this node. 
  * @note  The returned pointer may be null if a mesh has not been set in the scene graph 
  * or if no render action traversal has been done yet.
  */
  const MiSphereSliceExtractUnstructured*     getUnstructuredExtractor();
  const MiSphereSliceExtractUnstructuredIjk*  getUnstructuredIjkExtractor();
  const MiSphereSliceExtractIjk*              getIjkExtractor();
  //@}

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
  virtual const MiVec3dSetI* extractVec3SetI(SoState * state,size_t scalarSetId) ;

 protected:
  virtual ~MoMeshSphereSlice() ;  

  virtual void clear();

  template<typename _MeshInterface, typename _Extractor, typename _ScalarSet, typename _CellFilter>
  void doExtract(SoState * state,const _MeshInterface* mesh, _Extractor** extractor);

  template<typename _Extractor, typename _ScalarSet, typename _CellFilter>
  void extract(SoState * state,_Extractor* extractor,const _ScalarSet* colorSet, const _CellFilter *cellFilter);

  // Extractors used internally
  MiSphereSliceExtractUnstructured*    m_sphereSliceExtractU;
  MiSphereSliceExtractUnstructuredIjk* m_sphereSliceExtractUIjk;
  MiSphereSliceExtractIjk*             m_sphereSliceExtractIjk;

} ;

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MO_MESHSPHERESLICE_ */



