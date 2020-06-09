/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MO_MESHCYLINDERSLICE_
#define  _MO_MESHCYLINDERSLICE_

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec3f.h>

#include <MeshVizInterface/MbVec3.h>

#include <MeshVizInterface/mapping/nodes/MoMeshRepresentation.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class MiCylinderSliceExtractUnstructured;
class MiCylinderSliceExtractUnstructuredIjk;
class MiCylinderSliceExtractIjk;
class MiVolumeMeshUnstructured;
class MiVolumeMeshUnstructuredIjk;
class MiVolumeMeshHexahedronIjk;
class MiVolumeMeshRegular;
class MiVolumeMeshRectilinear;
class MiVolumeMeshCurvilinear;

/**
 * @DTEXT  Rendering node that displays a cylinder slice of a volume mesh.
 * 
 * @ingroup MeshIViz_Mapping_Representation
 * 
 * @DESCRIPTION
 *  A cylinder slice is an unstructured surface mesh defined by the intersection of an
 *  infinite cylinder with a volume mesh. 
 *  The cylinder is defined by a position, a radius and a direction vector.
 *
 *  The slice can be colored using a scalar set defined in the colorScalarSetId inherited field.
 *  This is an index into the list of scalar sets existing in the traversal state
 *  (see the MoScalarSetxxx nodes). To disable coloring set this field to -1.
 *  Rendering can be modified using various property nodes (see the SEE ALSO section).
 *
 * @FILE_FORMAT_DEFAULT
 *    MeshCylinderSlice {
 *    @TABLE_FILE_FORMAT
 *       @TR colorScalarSetId           @TD 0
 *       @TR parallel                   @TD TRUE
 *       @TR center                     @TD 0,0,0
 *       @TR radius                     @TD 1.0
 *       @TR direction                  @TD 1,0,0
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *  MoCellFilter, MoColorMapping, MoDrawStyle, MoMaterial, @BR
 *  MiCylinderSliceExtractIjk, 
 *  MiCylinderSliceExtractUnstructured,
 *  MiCylinderSliceExtractUnstructuredIjk
 *  
 */

class MESHIVIZDM_API MoMeshCylinderSlice : public MoMeshRepresentation {

  SO_NODE_HEADER(MoMeshCylinderSlice) ;

 public:

  /**
   * Constructor.
   */
  MoMeshCylinderSlice() ;

  /**
   * Specifies the cylinder's center. Default is 0,0,0.
   */
  SoSFVec3f center;

  /**
   * Specifies the cylinder's radius. Value must be greater than 0.0.  Default is 1.
   */
  SoSFFloat radius;

  /**
   * Specifies the cylinder's direction. Default is 1,0,0.
   */
  SoSFVec3f direction;

  //@{
  /** 
  * Get extractor for reuse outside this node. 
  * @note  The returned pointer may be null if a mesh has not been set in the scene graph 
  * or if no render action traversal has been done yet.
  */
  const MiCylinderSliceExtractUnstructured*     getUnstructuredExtractor();
  const MiCylinderSliceExtractUnstructuredIjk*  getUnstructuredIjkExtractor();
  const MiCylinderSliceExtractIjk*              getIjkExtractor();
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
  virtual ~MoMeshCylinderSlice() ;  

  virtual void clear();

  template<typename _MeshInterface, typename _Extractor, typename _ScalarSet, typename _CellFilter>
  void doExtract(SoState * state,const _MeshInterface* mesh, _Extractor** extractor);

  template<typename _Extractor, typename _ScalarSet, typename _CellFilter>
  void extract(SoState * state,_Extractor* extractor, const _ScalarSet* colorSet, const _CellFilter *cellFilter);

  // Extractors used internally
  MiCylinderSliceExtractUnstructured*    m_cylinderSliceExtractU;
  MiCylinderSliceExtractUnstructuredIjk* m_cylinderSliceExtractUIjk;
  MiCylinderSliceExtractIjk*             m_cylinderSliceExtractIjk;

} ;

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MO_MESHCYLINDERSLICE_ */



