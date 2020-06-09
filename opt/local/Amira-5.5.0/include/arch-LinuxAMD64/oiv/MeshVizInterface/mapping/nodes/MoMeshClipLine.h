/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (October 2009)
**=======================================================================*/
#ifndef  _MO_MESHCLIPLINE_
#define  _MO_MESHCLIPLINE_

#include <MeshVizInterface/MbVec3.h>

#include <MeshVizInterface/mapping/nodes/MoMeshRepresentation.h>

#include <Inventor/fields/SoSFPlane.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class MiClipLineExtractUnstructured;
class MiClipLineExtractIj;
class MiSurfaceMeshUnstructured;
class MiSurfaceMeshRegular;
class MiSurfaceMeshRectilinear;
class MiSurfaceMeshCurvilinear;

/**
 * @DTEXT  Rendering node that displays a clip line of a surface mesh.
 * 
 * @ingroup MeshIViz_Mapping_Representation
 * 
 * @DESCRIPTION
 *  A clip line is an unstructured line mesh defined by the intersection of an arbitrary plane
 *  with a surface mesh. 
 *  The plane (an SbPlane) is defined by a direction vector and a distance from the origin.
 *
 *  The line can be colored using a scalar set defined in the colorScalarSetId inherited field.
 *  This is an index into the list of scalar sets existing in the traversal state
 *  (see the MoScalarSetxxx nodes). To disable coloring set this field to -1.
 *  Rendering can be modified using various property nodes (see the SEE ALSO section).
 *
 * @FILE_FORMAT_DEFAULT
 *    MeshClipLine {
 *    @TABLE_FILE_FORMAT
 *       @TR colorScalarSetId           @TD 0
 *       @TR parallel                   @TD TRUE
 *       @TR plane                      @TD 0,0,1,0
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *  MoCellFilter, MoColorMapping, MoDrawStyle, MoMaterial, @BR
 *  MiClipLineExtractIjk,
 *  MiClipLineExtractUnstructured,
 * 
 */

class MESHIVIZDM_API MoMeshClipLine : public MoMeshRepresentation {

  SO_NODE_HEADER(MoMeshClipLine) ;

 public:

  /**
   * Constructor.
   */
  MoMeshClipLine() ;

  /**
   * Position of the plane slice. Z=0 plane by default.
   */
  SoSFPlane  plane;

  //@{
  /** 
  * Get extractor for reuse outside this node. 
  * @note  The returned pointer may be null if a mesh has not been set in the scene graph 
  * or if no render action traversal has occurred.
  */
  const MiClipLineExtractUnstructured*     getUnstructuredExtractor();
  const MiClipLineExtractIj*               getIjExtractor();
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
  virtual ~MoMeshClipLine() ;  

  virtual void clear();
  virtual void computePlane(MbVec3d& normal, double& distance);

  template<typename _MeshInterface, typename _Extractor, typename _ScalarSet, typename _CellFilter>
  void doExtract(SoState * state,const _MeshInterface* mesh, _Extractor** extractor);

  template<typename _Extractor, typename _ScalarSet, typename _CellFilter>
  void extract(SoState * state,_Extractor* extractor,const _ScalarSet* colorSet,const _CellFilter *cellFilter);

  // Extractors used internally
  MiClipLineExtractUnstructured*    m_clipLineExtractU;
  MiClipLineExtractIj*              m_clipLineExtractIj;

} ;

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MO_MESHPLANESLICE_ */



