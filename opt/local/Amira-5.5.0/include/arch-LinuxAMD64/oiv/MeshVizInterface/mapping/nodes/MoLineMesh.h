/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
** Modified by : Martial Bonaventure  (Jan 2011)
**=======================================================================*/
#ifndef  _MO_LINEMESH_
#define  _MO_LINEMESH_

#include <MeshVizInterface/mapping/nodes/MoMeshBaseRepresentation.h>

#include <MeshVizInterface/mesh/data/MiDataSetI.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class SoState;

template <typename _MeXMeshT> class MeXMeshUnstructuredAdaptor;
template <typename _T> class MeXDataSetIAdaptor;
class MxLineMeshUnstructuredFromRegular;
class MxLineMeshUnstructuredFromCurvilinear;

class MeXLineMeshUnstructured;
class MeXLineMeshCurvilinear;
class MiLineMeshUnstructured;
class MiLineMeshRegular;
class MiLineMeshCurvilinear;
class MiMesh;

class MxLineSceneGraph;

/**
 * @DTEXT  Rendering node that displays a line mesh.
 * 
 * @ingroup MeshIViz_Mapping_Representation
 * 
 * @DESCRIPTION
 *    Class to display a graphical representation of a line mesh. 
 *    The line is given by one of the setLineMesh methods
 *    depending on the type of input mesh.@n
 *    @note This class is used internally by all mesh representations producing line meshes. 
 *    It can be used by any custom nodes containing an extractor. 
 *    For displaying a line mesh stored in the scene graph using an MoMesh node, 
 *    use the MoMeshLine node instead. 
 *
 * @FILE_FORMAT_DEFAULT
 *    LineMesh {
 *    }
 *
 * @SEE_ALSO
 *  MoMeshLine
 * 
 */
class MESHIVIZDM_API MoLineMesh : public MoMeshBaseRepresentation {

  SO_NODE_HEADER(MoLineMesh) ;

 public:

  /**
   * Constructor.
   */
  MoLineMesh() ;

  //@{
  /** 
  * Set the line mesh and the scalar set used for coloring the line.
  * One method exists for each type of mesh.
  */
  void setLineMesh(const MeXLineMeshUnstructured* mesh, const MeXScalardSetI* scalarSet = NULL); 
  void setLineMesh(const MeXLineMeshCurvilinear*  mesh, const MeXScalardSetI* scalarSet = NULL);

  void setLineMesh(const MiLineMeshUnstructured* mesh, const MiScalardSetI* scalarSet = NULL);
  void setLineMesh(const MiLineMeshRegular*      mesh, const MiScalardSetI* scalarSet = NULL);
  void setLineMesh(const MiLineMeshCurvilinear*  mesh, const MiScalardSetI* scalarSet = NULL);
  //@}
  
  /**
  * Clears the cached value as if setLineMesh was given a null pointer.
  */
  void clear();

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 SoEXTENDER public:
  virtual void rayPick(SoRayPickAction *action);
  virtual void doAction(SoAction * action);
  virtual const MiMesh* getExtractedMesh(MeshType& meshType);
  template< typename _MeshT, typename _ScalarSetT>
  void setMesh(const _MeshT* mesh, const _ScalarSetT*  scalarSet = NULL)
  {
    setLineMesh(mesh,scalarSet);
  }

private:
  // internal method that sets the input mesh depending on the its type.
  template< typename _MeshT, typename _ScalarSetT>
  void setInternalLineMesh(const _MeshT* mesh, const _ScalarSetT*  scalarSet);
  // internal method to sets the input dataset, called by  setInternalSurfaceMesh()
  // when using an adaptator, the adapted mesh must have been set first.
  template<typename _ScalarSetT>
  const MeXScalardSetI* setInternalDataSet(const _ScalarSetT*  scalarSet);

  // adaptor to convert input mesh if no extraction
  MeXMeshUnstructuredAdaptor<MeXLineMeshUnstructured>* m_extrLineMeshAdaptor;
  MeXDataSetIAdaptor<double>*                          m_extrScalarSetAdaptor;

protected:
  virtual ~MoLineMesh() ;  

  void fillPrimitives(SoState* state);

  virtual bool haveValuesChanged(SoState* state);
  // check the extracted line and return false if changed
  bool checkLineCache();

  // stores the extracted mesh and scalarset
  const MeXLineMeshUnstructured*  m_extrLineMesh;
  const MeXScalardSetI*           m_extrScalarSet;

  MeshType m_meshType;
  size_t m_lineTopoTimeStamp;
  size_t m_lineGeomTimeStamp;
  size_t m_scalarSetTimeStamp;
  size_t m_colorMapTimeStamp;

  bool   m_rebuildTopology;
  bool   m_rebuildGeometry;
  bool   m_rebuildScalarSet;

  MxLineSceneGraph* m_innerSceneGraph;
} ;

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _MO_LINEMESH_ */



