/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MO_MESHINTERPOLATEDLOGICALSLICE_
#define  _MO_MESHINTERPOLATEDLOGICALSLICE_

#include <MeshVizInterface/MbVec3.h>

#include <MeshVizInterface/mapping/nodes/MoMeshRepresentation.h>

#include <Inventor/fields/SoSFPlane.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class MiInterpolatedLogicalSliceExtractUnstructuredIjk;
class MiInterpolatedLogicalSliceExtract;
class MiVolumeMeshUnstructuredIjk;
class MiVolumeMeshHexahedronIjk;
class MiVolumeMeshRegular;
class MiVolumeMeshRectilinear;
class MiVolumeMeshCurvilinear;

/**
 * @DTEXT  Rendering node that displays an interpolated logical slice of a volume mesh.
 * 
 * @ingroup MeshIViz_Mapping_Representation
 * 
 * @DESCRIPTION
 *  An interpolated logical slice is similar to MoMeshLogicalSlice except that instead of 
 *  displaying the slice only on the face of the cells, it can interpolate a slice inside cells. 
 *  This is done by providing a floating point value representing the offset along the specified axis.
 *
 *  The slice can be colored using a scalar set defined in the colorScalarSetId inherited field.
 *  This is an index into the list of scalar sets existing in the traversal state
 *  (see the MoScalarSetxxx nodes). To disable coloring set this field to -1.
 *  Rendering can be modified using various property nodes (see the SEE ALSO section).
 *
 * @FILE_FORMAT_DEFAULT
 *    MeshInterpolatedLogicalSlice {
 *    @TABLE_FILE_FORMAT
 *       @TR colorScalarSetId           @TD 0
 *       @TR parallel                   @TD TRUE
 *       @TR sliceValue                 @TD 0
 *       @TR sliceAxis                  @TD SLICE_I
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *  MoMeshLogicalSlice, @BR
 *  MoCellFilter, MoColorMapping, MoDrawStyle, MoMaterial, @BR
 *  MiInterpolatedLogicalSliceExtract, 
 *  MiInterpolatedLogicalSliceExtractUnstructuredIjk
 * 
 */

class MESHIVIZDM_API MoMeshInterpolatedLogicalSlice : public MoMeshRepresentation {

  SO_NODE_HEADER(MoMeshInterpolatedLogicalSlice) ;

 public:

  /**
   * Constructor.
   */
  MoMeshInterpolatedLogicalSlice() ;

  /**
   * Value of the slice to display between 0 and NUM CELL. Default is 0.
   */
  SoSFFloat  sliceValue;

  /**
  * Slice axis
  */
  enum SliceAxis {
    SLICE_I, /**< Slice at I constant */
    SLICE_J, /**< Slice at J constant */
    SLICE_K  /**< Slice at K constant */
  };

  /**
  * The axis along which the logical slice will be computed.
  * Use enum #SliceAxis. Default is SLICE_I.
  */
  SoSFEnum  sliceAxis;

  //@{
  /** 
  * Get extractor for reuse outside this node. 
  * @note The returned pointer may be null if a mesh has not been set in the scene graph 
  * or if no render action has traversed the scene graph.
  */
  const MiInterpolatedLogicalSliceExtractUnstructuredIjk*  getUnstructuredIjkExtractor();
  const MiInterpolatedLogicalSliceExtract*                 getIjkExtractor();
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
  virtual const MiVec3dSetI* extractVec3SetI(SoState * state,size_t vec3SetId) ;

 protected:
  virtual ~MoMeshInterpolatedLogicalSlice() ;  

  virtual void clear();

  template<typename _MeshInterface, typename _Extractor, typename _ScalarSet, typename _CellFilter>
  void doExtract(SoState * state,const _MeshInterface* mesh, _Extractor** extractor);

  template<typename _Extractor, typename _ScalarSet, typename _CellFilter>
  void extract(SoState * state,_Extractor* extractor,const _ScalarSet* colorSet, const _CellFilter *cellFilter);

  // Extractors used internally
  MiInterpolatedLogicalSliceExtractUnstructuredIjk* m_interpolatedLogicalSliceExtractUIjk;
  MiInterpolatedLogicalSliceExtract*             m_interpolatedLogicalSliceExtractIjk;

} ;

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MO_MESHINTERPOLATEDLOGICALSLICE_ */



