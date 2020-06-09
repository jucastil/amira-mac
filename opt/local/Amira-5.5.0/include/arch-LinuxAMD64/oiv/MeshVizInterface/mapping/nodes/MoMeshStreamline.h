/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MO_MESHSTREAMLINE_
#define  _MO_MESHSTREAMLINE_

#include <MeshVizInterface/MbVec3.h>

#include <MeshVizInterface/mapping/nodes/MoMeshRepresentation.h>

#include <Inventor/fields/SoSFDouble.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoSFInt32.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class MiStreamlineExtractUnstructured;
class MiStreamlineExtractUnstructuredIjk;
class MiStreamlineExtractIjk;
class MiVolumeMeshUnstructured;
class MiVolumeMeshUnstructuredIjk;
class MiVolumeMeshHexahedronIjk;
class MiVolumeMeshRegular;
class MiVolumeMeshRectilinear;
class MiVolumeMeshCurvilinear;

class MeLineMeshSet;
class MeSetOfVec3dSetI;
class MeSetOfScalardSetI;

/**
 * @DTEXT  Rendering node that displays streamlines of a vector field on a volume mesh.
 * 
 * @ingroup MeshIViz_Mapping_Representation
 * 
 * @DESCRIPTION
 *  Displays a list of MiLineMeshCurvilinear meshes containing streamlines starting from a 
 *  list of source points and probes the input mesh to compute the values at the
 *  streamline nodes (See the SEE ALSO Section for settings). @BR
 *  A streamline is a line that is everywhere tangent to a vector field.
 *  The vector field is specified by the vec3SetId field. This is an index into the list of
 *  vector sets existing in the traversal state (see the MoVec3Setxxx nodes). @BR
 *  
 *  Note: Streamlines are meaningless for unsteady flow, because time is not taken into account 
 *  during the computation of the lines. Streamlines are integrated from a given set of vectors 
 *  using a Runge/Kutta method of order 2 .
 *
 *  The lines can be colored using a scalar set defined in the colorScalarSetId inherited field.
 *  This is an index into the list of scalar sets existing in the traversal state
 *  (see the MoScalarSetxxx nodes). To disable coloring set this field to -1.
 *
 * @FILE_FORMAT_DEFAULT
 *    MeshStreamline {
 *    @TABLE_FILE_FORMAT
 *       @TR colorScalarSetId            @TD 0
 *       @TR parallel                    @TD TRUE
 *       @TR vec3SetId                   @TD 0
 *       @TR startingPoints              @TD 0,0,0
 *       @TR maxLifeTime                 @TD 0
 *       @TR maxLength                   @TD 0
 *       @TR minSpeed                    @TD 0
 *       @TR integrationStepLengthFactor @TD 0.3
 *       @TR maxStepNumber               @TD 0
 *       @TR direction                   @TD FORWARD
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *  MiStreamlineExtractIjk,
 *  MiStreamlineExtractUnstructured,
 *  MiStreamlineExtractUnstructuredIjk,
 *  MiPointProbeIjk,
 *  MiPointProbeUnstructured,
 *  MiPointProbeUnstructuredIjk
 * 
 */

class MESHIVIZDM_API MoMeshStreamline : public MoMeshRepresentation {

  SO_NODE_HEADER(MoMeshStreamline) ;

 public:

  /**
   * Constructor.
   */
  MoMeshStreamline() ;

  /**
  * Field representing the vector set node to be used to compute the streamlines.
  * During traversal of the scene graph, vector set nodes are accumulated in a list of vector sets.
  * vec3Set is an index in this list. Default is 0 meaning to use the first set in the list.
  * @note  This vector set must be defined per node to be valid. 
   */
  SoSFInt32  vec3SetId;

  /**
  * Starting points for the streamline computation. @BR Default is empty.
  */
  SoMFVec3f  startingPoints;

  /**
  * Sets the maximum life time of the streamline. @BR
  * Default is 0, meaning infinite life time.
  */
  SoSFDouble  maxLifeTime;

  /**
  * Sets the maximum length of the streamline. @BR
  * Default is 0, meaning infinite length.
  */
  SoSFDouble  maxLength;

  /**
  * Sets the minimum speed of the streamline. @BR
  * Default is 0, meaning no speed constraint.
  */
  SoSFDouble  minSpeed;

  /**
  * Sets the step length factor for the streamline integration. @BR
  * Default is 0.3.
  */
  SoSFDouble  integrationStepLengthFactor;

  /**
  * Sets the maximum step number during the streamline integration. @BR
  * Default is 0, meaning infinite step number.
  */
  SoSFInt32  maxStepNumber;

  /**
  *  Integration direction
  */
  enum IntegrationDirection {
    FORWARD,  /**< Integration is done in the direction of the vectors. */
    BACKWARD  /**< Integration is done in the inverse of the direction of the vectors. */
  } ;

  /**
  * Sets the direction for the streamline integration. @BR
  * Use enum #IntegrationDirection. Default is FORWARD.
  */
  SoSFEnum  direction;

  //@{
  /** 
  * Get extractor for reuse outside this node. 
  * @note  The returned pointer may be null if a mesh has not been set in the scene graph 
  * or if no render action has been called before. 
  * Use the method corresponding to the type of mesh stored in the scene graph. 
  * 
  */
  const MiStreamlineExtractUnstructured*    getUnstructuredExtractor();
  const MiStreamlineExtractUnstructuredIjk* getUnstructuredIjkExtractor();
  const MiStreamlineExtractIjk*             getIjkExtractor();
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
  virtual ~MoMeshStreamline() ;  

  void clear();
  template<typename _Extractor>
  void setParameters(_Extractor& extractor);
  void getStartPointList(std::vector<MbVec3d> &startPointList);

  template<typename _MeshInterface, typename _Extractor, typename _ScalarSet, typename _Vec3Set, typename _CellFilter>
  void doExtract(SoState * state,const _MeshInterface* mesh, _Extractor** extractor);

  template<typename _Extractor, typename _ScalarSet, typename _Vec3Set, typename _CellFilter>
  void extract(SoState * state,_Extractor* extractor,const _ScalarSet* colorSet, const _CellFilter *cellFilter);

  // Extractors used internally
  MiStreamlineExtractUnstructured*    m_streamlineExtractU;
  MiStreamlineExtractUnstructuredIjk* m_streamlineExtractUIjk;
  MiStreamlineExtractIjk*             m_streamlineExtractIjk;

  // Set of streamlines
  MeLineMeshSet* m_streamlineSet;
  MeSetOfVec3dSetI* m_setOfVec3Set; 
  MeSetOfScalardSetI* m_setOfScalarSet;

} ;

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MO_MESHSTREAMLINE_ */



