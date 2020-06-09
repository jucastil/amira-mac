/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MO_MESHLOGICALSLICE_
#define  _MO_MESHLOGICALSLICE_

#include <MeshVizInterface/mesh/MiSurfaceMeshUnstructured.h>
#include <MeshVizInterface/MbVec3.h>

#include <MeshVizInterface/mapping/nodes/MoMeshRepresentation.h>

#include <Inventor/fields/SoSFUInt32.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class MiLogicalSliceExtractUnstructuredIjk;
class MiLogicalSliceExtractRegular;
class MiLogicalSliceExtractRectilinear;
class MiLogicalSliceExtractCurvilinear;
class MiVolumeMeshUnstructured;
class MiVolumeMeshUnstructuredIjk;
class MiVolumeMeshHexahedronIjk;
class MiVolumeMeshRegular;
class MiVolumeMeshRectilinear;
class MiVolumeMeshCurvilinear;
class MiCellFilterIjk;

/**
 * @DTEXT  Rendering node that displays a logical slice of a structured volume mesh.
 * 
 * @ingroup MeshIViz_Mapping_Representation
 * 
 * @DESCRIPTION
 * A logical slice is an unstructured surface mesh extracted from an IJK volume mesh along the 
 * faces of a "slab" of cells. It is defined by a slice axis, an index and a boolean flag. 
 * 
 * The slice axis can be SLICE_I, SLICE_J or SLICE_K. The index represents a constant value for 
 * I, J or K (whichever is the slice axis). The boolean upperVertex specifies whether the slice 
 * is rendered using the lower or upper vertices (roughly the near or far faces) of the cells.
 *
 * If N is the number of cells on the specified sliceAxis, then the valid range for sliceIndex
 * is 0..N.  As a convenience, when sliceIndex = N, the N-1 cells are used but upperVertex is 
 * automatically considered to be TRUE.
 *
 * The slice can be colored using a scalar set defined in the colorScalarSetId inherited field.
 * This is an index into the list of scalar sets existing in the traversal state
 * (see the MoScalarSetxxx nodes). To disable coloring set this field to -1.
 * Rendering can be modified using various property nodes (see the SEE ALSO section).
 *
 * @FILE_FORMAT_DEFAULT
 *    MeshLogicalSlice {
 *    @TABLE_FILE_FORMAT
 *       @TR colorScalarSetId           @TD 0
 *       @TR parallel                   @TD TRUE
 *       @TR sliceIndex                 @TD 0
 *       @TR sliceAxis                  @TD SLICE_I
 *       @TR upperVertex                @TD FALSE
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *  MoMeshInterpolatedLogicalSlice, @BR
 *  MoCellFilter, MoColorMapping, MoDrawStyle, MoMaterial, @BR
 *  MiLogicalSliceExtractRegular, 
 *  MiLogicalSliceExtractRectilinear,
 *  MiLogicalSliceExtractCurvilinear, 
 *  MiLogicalSliceExtractUnstructuredIjk
 *
 */

class MESHIVIZDM_API MoMeshLogicalSlice : public MoMeshRepresentation {

  SO_NODE_HEADER(MoMeshLogicalSlice) ;

 public:

  /**
   * Constructor.
   */
  MoMeshLogicalSlice() ;

  /**
   * Index of the slice to display. Default is 0.
   */
  SoSFUInt32  sliceIndex;

  /**
  * Slice axis
  */
  enum SliceAxis {
    SLICE_I, /**< Slice at I constant */
    SLICE_J, /**< Slice at J constant */
    SLICE_K  /**< Slice at K constant */
  };

  /**
  * The axis along which the logical slice will be computed defined by the SliceAxis enum.
  * Use enum #SliceAxis. Default is SLICE_I.
  */
  SoSFEnum  sliceAxis;
  
  /**
  * If FALSE (the default), displays the lower part of the cell, otherwise displays the upper part of the cell.
  */
  SoSFBool  upperVertex;

  //@{
  /** 
  * Get extractor for reuse outside this node. 
  * @note  The returned pointer may be null if a mesh has not been set in the scene graph 
  * or if no render action has been called before. 
  * Use the method corresponding to the type of mesh stored in the scene graph. 
  * 
  */
  const MiLogicalSliceExtractRegular*         getRegularExtractor();
  const MiLogicalSliceExtractRectilinear*     getRectilinearExtractor();
  const MiLogicalSliceExtractCurvilinear*     getCurvilinearExtractor();
  const MiLogicalSliceExtractUnstructuredIjk* getUnstructuredIjkExtractor();
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
  virtual const MiScalardSetIj* extractScalarSetIj(SoState * state,size_t scalarSetId) ;

  // computes the extract of the data set corresponding to the given index in the state list from the current representation's extractor.
  virtual const MiVec3dSetI* extractVec3SetI(SoState * state,size_t scalarSetId) ;
  virtual const MiVec3dSetIj* extractVec3SetIj(SoState * state,size_t scalarSetId) ;

 protected:
  virtual ~MoMeshLogicalSlice() ;  

  virtual void clear();

  template<typename _MeshInterface, typename _Extractor, typename _OutputMeshInterface, typename _InputScalarSet, typename _OutputScalarSet>
  void doExtract(SoState * state,const _MeshInterface* mesh, _Extractor** extractor);

  template<typename _Extractor,typename _OutputMeshInterface, typename _InputScalarSet, typename _OutputScalarSet>
  void extract(SoState * state,_Extractor* extractor,const _InputScalarSet* colorSet, const MiCellFilterIjk *cellFilter);

  // Extractors used internally
  MiLogicalSliceExtractRegular*             m_logicalSliceExtractRegular;
  MiLogicalSliceExtractRectilinear*         m_logicalSliceExtractRectilinear;
  MiLogicalSliceExtractCurvilinear*         m_logicalSliceExtractCurvilinear;
  MiLogicalSliceExtractUnstructuredIjk*     m_logicalSliceExtractUIjk;
  
} ;

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MO_MESHLogicalSlice_ */



