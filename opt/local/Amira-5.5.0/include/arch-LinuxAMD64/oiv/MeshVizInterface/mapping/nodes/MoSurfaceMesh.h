/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
** Modified by : Martial Bonaventure  (Jun 2010)
** Modified by : Martial Bonaventure  (Jan 2011)
**=======================================================================*/
#ifndef  _MO_SURFACEMESH_
#define  _MO_SURFACEMESH_

#include <MeshVizInterface/mapping/nodes/MoMeshBaseRepresentation.h>

#include <MeshVizInterface/mesh/data/MiDataSetI.h>
#include <MeshVizInterface/mesh/data/MiDataSetIj.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetIj.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class SoState;
class SoAction;

template <typename _MeXMeshT> class MeXMeshUnstructuredAdaptor;
template <typename _T> class MeXDataSetIAdaptor;

class MeXSurfaceMeshUnstructured;
class MeXSurfaceMeshRegular;
class MeXSurfaceMeshRectilinear;
class MeXSurfaceMeshCurvilinear;
class MiSurfaceMeshUnstructured;
class MiSurfaceMeshRegular;
class MiSurfaceMeshRectilinear;
class MiSurfaceMeshCurvilinear;
class MiMesh;

class MxSurfaceSceneGraph;
/**
 * @DTEXT  Rendering node that displays a surface mesh.
 * 
 * @ingroup MeshIViz_Mapping_Representation
 * 
 * @DESCRIPTION
 *    Class to display a graphical representation of a surface mesh. 
 *    The surface is given by one of the setSurfaceMesh methods
 *    depending on the type of input mesh.@n
 *    @note This class is used internally by all mesh representations producing surface meshes. 
 *    It can be used by any custom nodes containing an extractor. 
 *    For displaying a surface mesh stored in the scene graph using an MoMesh node, 
 *    use the MoMeshSurface node instead. 
 *
 * @FILE_FORMAT_DEFAULT
 *    SurfaceMesh {
 *    }
 *
 * @SEE_ALSO
 *  MoMeshSurface
 * 
 */
class MESHIVIZDM_API MoSurfaceMesh : public MoMeshBaseRepresentation {

  SO_NODE_HEADER(MoSurfaceMesh) ;

 public:

  /**
   * Constructor.
   */
  MoSurfaceMesh() ;

  //@{
  /** 
  * Set the surface mesh and the scalar set used for coloring the surface.
  * One method exists for each type of mesh.
  */
  void setSurfaceMesh(const MeXSurfaceMeshUnstructured* mesh, const MeXScalardSetI*  scalarSet = NULL);
  void setSurfaceMesh(const MeXSurfaceMeshRegular* mesh, const MeXScalardSetIj*  scalarSet = NULL);
  void setSurfaceMesh(const MeXSurfaceMeshRectilinear* mesh, const MeXScalardSetIj*  scalarSet = NULL);
  void setSurfaceMesh(const MeXSurfaceMeshCurvilinear*  mesh, const MeXScalardSetIj* scalarSet = NULL);

  void setSurfaceMesh(const MiSurfaceMeshUnstructured* mesh, const MiScalardSetI*  scalarSet = NULL);
  void setSurfaceMesh(const MiSurfaceMeshRegular*      mesh, const MiScalardSetIj* scalarSet = NULL);
  void setSurfaceMesh(const MiSurfaceMeshRectilinear*  mesh, const MiScalardSetIj* scalarSet = NULL);
  void setSurfaceMesh(const MiSurfaceMeshCurvilinear*  mesh, const MiScalardSetIj* scalarSet = NULL);
  //@}
 
  /** 
  * Set a single geometric normal for the whole surface. 
  * When the surface is planar, setting this overall normal optimizes 
  * the computation of render caches.
  * A geometric normal is used for rendering when lighting is on.
  * Ignored when set to (0,0,0) (default value)
  * @note If both OverallNormal and NormalDataSet are set, NormalDateSet is used and OverallNormal is ignored. 
  */
  void setOverallNormal(const SbVec3f& normal);

  //@{
  /** 
  * Set geometric normals for the surface. 
  * When the surface is planar, setting this overall normal optimizes 
  * the computation of render caches.
  * Geometric normals are used for rendering when lighting is on.
  * When binded to nodes, the surface looks smooth. When binded to cells, the surface looks facetted.
  * Ignored when set to NULL (default value)
  * @note If both OverallNormal and NormalDataSet are set, NormalDateSet is used and OverallNormal is ignored. 
  */
  void setNormalDataSet(const MiVec3dSetI*  normalSet);
  void setNormalDataSet(const MiVec3dSetIj* normalSet);
  //@}

  /**
  * Clears the cached value as if setSurfaceMesh was given a null pointer.
  */
  void clear();

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 SoEXTENDER public:
  virtual void rayPick(SoRayPickAction * action);
  virtual void doAction(SoAction * action);
  virtual const MiMesh* getExtractedMesh(MeshType& meshType);
  void setIgnoreEdgeStyle(bool ignore = true);
  template< typename _MeshT, typename _ScalarSetT>
  void setMesh(const _MeshT* mesh, const _ScalarSetT*  scalarSet = NULL)
  {
    setSurfaceMesh(mesh,scalarSet);
  }

private:
  // internal method that sets the input mesh depending on the its type.
  template< typename _MeshT, typename _ScalarSetT>
  void setInternalSurfaceMesh(const _MeshT* mesh, const _ScalarSetT*  scalarSet = NULL);

  // adaptor to convert input mesh if no extraction
  MeXMeshUnstructuredAdaptor<MeXSurfaceMeshUnstructured>* m_extrSurfaceMeshAdaptor;
  MeXDataSetIAdaptor<double>*                             m_extrScalarSetAdaptor;

protected:
  virtual ~MoSurfaceMesh() ;  

  void fillPrimitives(SoState *state);

  virtual bool haveValuesChanged(SoState* state);
  // check the extracted surface and return false if changed
  bool checkSurfaceCache();
  
  // stores the extracted mesh and scalarset
  const MeXSurfaceMeshUnstructured*         m_extrSurfaceMesh;
  const MeXScalardSetI*                     m_extrScalarSet;
 
  MeshType m_meshType;
  size_t m_surfaceTopoTimeStamp;
  size_t m_surfaceGeomTimeStamp;
  size_t m_scalarSetTimeStamp;
  size_t m_colorMapTimeStamp;

  bool   m_rebuildTopology;
  bool   m_rebuildGeometry;
  bool   m_rebuildScalarSet;

  MxSurfaceSceneGraph* m_innerSceneGraph;

} ;

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MO_SURFACEMESH_ */



