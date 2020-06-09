/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MO_MESHSKIN_
#define  _MO_MESHSKIN_

#include <MeshVizInterface/mesh/MiSurfaceMeshUnstructured.h>
#include <MeshVizInterface/MbVec3.h>

#include <MeshVizInterface/mapping/nodes/MoMeshRepresentation.h>

#include <Inventor/fields/SoSFPlane.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class MiSkinExtractUnstructured;
class MiSkinExtractUnstructuredIjk;
class MiSkinExtractIjk;
class MiSkinExtractRectilinear;
class MiSkinExtractCurvilinear;

class MiVolumeMeshUnstructured;
class MiVolumeMeshUnstructuredIjk;
class MiVolumeMeshHexahedronIjk;
class MiVolumeMeshVertexHexahedronIjk;
class MiVolumeMeshRegular;
class MiVolumeMeshRectilinear;
class MiVolumeMeshCurvilinear;

class MoSurfaceMesh;
class MoLineMesh;

/**
 * @DTEXT  Rendering node that displays the skin of a volume mesh.
 * 
 * @ingroup MeshIViz_Mapping_Representation
 * 
 * @DESCRIPTION
 *  The skin of a mesh is an unstructured surface mesh made up of all the faces that belong to only one cell.
 *
 *  The mesh can be colored using a scalar set defined in the colorScalarSetId inherited field.
 *  This is an index into the list of scalar sets existing in the traversal state
 *  (see the MoScalarSetxxx nodes). To disable coloring set this field to -1.
 *  Rendering can be modified using various property nodes (see the SEE ALSO section).
 *
 * @FILE_FORMAT_DEFAULT
 *    MeshSkin {
 *    @TABLE_FILE_FORMAT
 *       @TR colorScalarSetId           @TD 0
 *       @TR parallel                   @TD TRUE
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *  MoCellFilter, MoColorMapping, MoDrawStyle, MoMaterial, @BR
 *  MiSkinExtractIjk,
 *  MiSkinExtractUnstructured,
 *  MiSkinExtractUnstructuredIjk
 * 
 */

class MESHIVIZDM_API MoMeshSkin : public MoMeshRepresentation {

  SO_NODE_HEADER(MoMeshSkin) ;

 public:

  /**
   * Constructor.
   */
  MoMeshSkin() ;

  //@{
  /** 
  * Get extractor for reuse outside this node. 
  * @note  The returned pointer may be null if a mesh has not been set in the scene graph 
  * or if no render action has been called before.
  */
  const MiSkinExtractUnstructured* getUnstructuredExtractor();
  const MiSkinExtractUnstructuredIjk* getUnstructuredIjkExtractor();
  const MiSkinExtractIjk* getIjkExtractor();
  //@}

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 SoEXTENDER public:
  virtual void doExtract(SoAction *action);
  virtual const MiMesh* getExtractedMesh(MeshType& meshType);

  // computes the extract of the data set corresponding to the given index in the state list from the current representation's extractor.
  // a skin always returns a MiScalardSetI
  const MiScalardSetI* extractScalarSetI(SoState * state,size_t scalarSetId) ;

  // computes the extract of the data set corresponding to the given index in the state list from the current representation's extractor.
  // a skin always returns a MiVec3dSetI
  const MiVec3dSetI* extractVec3SetI(SoState * state,size_t vec3SetId);

 protected:
  virtual ~MoMeshSkin() ;  
  template<typename _MeshT> friend class MxMeshSkin;

  void clear();

  template<typename _MeshInterface, typename _Extractor, typename _ScalarSet, typename _CellFilter>
  void doExtract(SoState * state,const _MeshInterface* mesh, _Extractor** extractor);

  // Extractors used internally
  MiSkinExtractUnstructured*    m_skinExtractU;
  MiSkinExtractUnstructuredIjk* m_skinExtractUIjk;
  MiSkinExtractIjk*             m_skinExtractIjk;

  MoSurfaceMesh* m_skin;
  MoLineMesh* m_lineskin;
  
} ;

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MO_MESHSKIN_ */



