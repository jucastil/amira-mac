/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MO_MESHSURFACE_
#define  _MO_MESHSURFACE_

#include <MeshVizInterface/mapping/nodes/MoMeshRepresentation.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class MiTessellatedSurfaceExtract;
class MxSurfaceMeshUnstructuredDeadCellFromCellFilter;
class MxSurfaceMeshRegularDeadCellFromCellFilter;
class MxSurfaceMeshRectilinearDeadCellFromCellFilter;
class MxSurfaceMeshCurvilinearDeadCellFromCellFilter;
class MiSurfaceMeshUnstructured;
class MoSurfaceMesh;

/**
 * @DTEXT  Rendering node that displays a surface mesh.
 * 
 * @ingroup MeshIViz_Mapping_Representation
 * 
 * @DESCRIPTION
 *  This class just gets the MoMesh node from the scene graph and creates an MoSurfaceMesh node to display it.
 *  The MoMesh stored in the scene graph must be a surface mesh.
 *
 *  @note It only performs an extraction for quadratic meshes and in this case, a MoTessellator must be set 
 *        in the scenegraph for proper rendering.
 *
 *  The mesh can be colored using a scalar set defined in the colorScalarSetId inherited field.
 *  This is an index into the list of scalar sets existing in the traversal state
 *  (see the MoScalarSetxxx nodes). To disable coloring set this field to -1.
 *  Rendering can be modified using various property nodes (see the SEE ALSO section).
 *
 * @FILE_FORMAT_DEFAULT
 *    MeshSurface {
 *    @TABLE_FILE_FORMAT
 *       @TR colorScalarSetId           @TD 0
 *       @TR parallel                   @TD TRUE
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *  MoCellFilter, MoColorMapping, MoDrawStyle, MoMaterial, @BR
 *  MoMesh, MoSurfaceMesh, MoTessellator
 *
 */

class MESHIVIZDM_API MoMeshSurface : public MoMeshRepresentation {

  SO_NODE_HEADER(MoMeshSurface) ;

 public:

  /**
   * Constructor.
   */
  MoMeshSurface() ;

  /**
   * No extraction in this node so always returns NULL.
   */
  virtual const MiMesh* getExtractedMesh(MeshType& UNREF_PARAM(meshType)) { return NULL; };

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 SoEXTENDER public:
  virtual void doExtract(SoAction *action);

 protected:
  virtual ~MoMeshSurface() ;  

  void clear();

  template<typename _MeshInterface, typename _Adaptor>
  void doExtract(SoState * state,const _MeshInterface* mesh, _Adaptor*& adaptor);

  template <typename _MeshInterface, class _ScalarSet>
  void display(SoState * state,const _MeshInterface* mesh, const _ScalarSet* colorSet);

  template<typename _CellFilter, typename _Mesh, typename _Adaptor>
  void setCellFilter(_CellFilter* cellFilter, _Mesh*& mesh, _Adaptor*& adaptor);

  const MiScalardSetI* getColorScalarSetI(SoState* state);
  const MiScalardSetIj* getColorScalarSetIj(SoState* state);

  /**
   * Transform surface before displaying it.
   * In this node, nothing is done.
   */
  virtual void transformSurface( const MiSurfaceMeshUnstructured*& mesh, const MiScalardSetI*& colorSet,
                                 SoState* state );

  /**
   * Return Surface Mesh node.
   */
  virtual MoSurfaceMesh* getSurfaceMeshNode();

  MiTessellatedSurfaceExtract* m_tessellatorExtract;

  MxSurfaceMeshUnstructuredDeadCellFromCellFilter* m_meshCellFilterAdaptor;
  MxSurfaceMeshRegularDeadCellFromCellFilter* m_meshRegularCellFilterAdaptor;
  MxSurfaceMeshRectilinearDeadCellFromCellFilter* m_meshRectilinearCellFilterAdaptor;
  MxSurfaceMeshCurvilinearDeadCellFromCellFilter* m_meshCurvilinearCellFilterAdaptor;
  size_t m_cellFilterTS;
} ;

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MO_MESHSURFACE_ */



