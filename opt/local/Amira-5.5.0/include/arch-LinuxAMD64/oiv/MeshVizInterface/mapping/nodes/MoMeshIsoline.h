/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MO_MESHISOLINE_
#define  _MO_MESHISOLINE_

#include <MeshVizInterface/MbVec3.h>

#include <MeshVizInterface/mapping/nodes/MoMeshRepresentation.h>

#include <Inventor/fields/SoMFFloat.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class MiIsolineExtractUnstructured;
class MiIsolineExtractIj;
class MiSurfaceMeshUnstructured;
class MiSurfaceMeshRegular;
class MiSurfaceMeshRectilinear;
class MiSurfaceMeshCurvilinear;
class MeLineMeshSet;
class MeSetOfVec3dSetI;
class MeSetOfScalardSetI;

/**
 * @DTEXT  Rendering node that displays isolines on a surface mesh.
 * 
 * @ingroup MeshIViz_Mapping_Representation
 * 
 * @DESCRIPTION
 *  Isolines are a collection of unstructured line meshes defined by the points having 
 *  the specified values in the scalar data set. You can specify a list of iso values, 
 *  the period of major contour lines and line patterns for the major and minor contour lines.
 *
 *  The scalar set used to extract the isolines is defined by the isoScalarSetId field. 
 *  This is an index into the list of scalar sets existing in the traversal state
 *  (see the MoScalarSetxxx nodes).  This scalar set must be defined per node to be valid.
 *
 *  The isolines can be colored using a scalar set defined in the colorScalarSetId inherited field.
 *  To disable coloring set this field to -1.
 *
 * @FILE_FORMAT_DEFAULT
 *    MeshIsoline {
 *    @TABLE_FILE_FORMAT
 *       @TR colorScalarSetId           @TD 0
 *       @TR parallel                   @TD TRUE
 *       @TR isovalues                  @TD 0.0
 *       @TR isoScalarSetId             @TD 0
 *       @TR majorPeriod                @TD 3
 *       @TR firstMajor                 @TD 0
 *       @TR majorLinePattern           @TD 0xFFFF
 *       @TR minorLinePattern           @TD 0xFFFF
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *  MoMeshAnnotatedIsoline, @BR
 *  MiIsolineExtractUnstructured, MiIsolineExtractIj
 * 
 */

class MESHIVIZDM_API MoMeshIsoline : public MoMeshRepresentation {

  SO_NODE_HEADER(MoMeshIsoline) ;

 public:

  /**
   * Constructor.
   */
  MoMeshIsoline() ;

  /**
   * List of isovalues to display. Default is empty.
   */
  SoMFFloat  isovalues;

  /**
  * Field representing the scalar set node to be used to compute the iso values.
  * During traversal of the scene graph, scalar set nodes are accumulated in a list of scalar sets.
  * isoScalarSetId is an index into this list. Default is 0.
  * @note This scalar set must be defined per node to be valid. 
   */
  SoSFInt32  isoScalarSetId;
  
  /**
   * Defines the major and the minor contour lines. majorPeriod is the period of 
   * major contour lines. See also firstMajor.
   * By default, majorPeriod = 3.
   */
  SoSFUShort  majorPeriod ;

  /**
   * Defines the first major contour lines. See also majorPeriod.
   * By default, firstMajor = 0.
   */
  SoSFUShort  firstMajor ;

  /**
   * Defines the line pattern for major contour lines. See also majorPeriod.
   * By default, majorLinePattern = 0xFFFF (solid).
   */
  SoSFUShort  majorLinePattern ;

  /**
   * Defines the line pattern for minor contour lines. See also minorPeriod.
   * By default, minorLinePattern = 0xFFFF (solid).
   */
  SoSFUShort  minorLinePattern ;

  //@{
  /** 
  * Get extractor for reuse outside this node. 
  * @note The returned pointer may be null if a mesh has not been set in the scene graph 
  * or if no render action has traversed the scene graph. 
  * Use the method corresponding to the type of mesh stored in the scene graph. 
  * 
  */
  const MiIsolineExtractUnstructured*    getUnstructuredExtractor();
  const MiIsolineExtractIj*              getIjExtractor();
  //@}

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 SoEXTENDER public:
  virtual void doExtract(SoAction * action);
  virtual const MiMesh* getExtractedMesh(MeshType& meshType);

  // computes the extract of the data set corresponding to the given index in the state list from the current representation's extractor.
  virtual const MiScalardSetI* extractScalarSetI(SoState * state,size_t scalarSetId) ;

  // computes the extract of the data set corresponding to the given index in the state list from the current representation's extractor.
  virtual const MiVec3dSetI* extractVec3SetI(SoState * state,size_t vectorSetId) ;

 protected:
  virtual ~MoMeshIsoline() ;  

  void clear();
  void getIsovalueList(std::vector<double> &isovalueList);

  template<typename _MeshInterface, typename _Extractor, typename _ScalarSet, typename _CellFilter>
  void doExtract(SoState * state,const _MeshInterface* mesh, _Extractor** extractor);

  template<typename _Extractor, typename _ScalarSet, typename _CellFilter>
  void extract(SoState * state,_Extractor* extractor,const _ScalarSet* colorSet,const _CellFilter *cellFilter);

  bool isMajor(size_t index);
    
  // Extractors used internally
  MiIsolineExtractUnstructured* m_isoExtractU;
  MiIsolineExtractIj*           m_isoExtractIj;

  // Cached values used for annotated isolines
  const MiSurfaceMeshUnstructured* m_surfaceMeshU;
  const MiSurfaceMeshRegular*      m_surfaceMeshRegular;
  const MiSurfaceMeshRectilinear*  m_surfaceMeshRectilinear;
  const MiSurfaceMeshCurvilinear*  m_surfaceMeshCurvilinear;

  // Set of isoline
  MeLineMeshSet* m_isolineSet;
  MeSetOfVec3dSetI* m_setOfVec3Set; 
  MeSetOfScalardSetI* m_setOfScalarSet;

} ;

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MO_MESHISOLINE_ */



