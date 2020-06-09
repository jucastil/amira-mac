/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_MESHSKIN_
#define  _PO_MESHSKIN_

#include <MeshViz/3Ddata/PoMesh3D.h>

class PbIndexedMesh3D;
class PbTetrahedronMesh3D;
class PbHexahedronMesh3D;
class PbCartesianGrid3D;
class PbParalCartesianGrid3D;
class PbRegularCartesianGrid3D;
class PoCellFilter;

/**
 * @DTEXT  Representation of the mesh skin.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *    Class to build the skin of the current volume mesh. The exterior and
 *    the interior boundaries of the mesh are displayed. See PoMesh for more 
 *    explanations about the current mesh. If the current mesh is an indexed
 *    mesh (class PbIndexedMesh3D, PoIndexedMesh3D and derived), the skin
 *    is defined by the list of facets which belong to only one cell.
 *    
 *    If the field PoMesh::valuesIndex is not defined (or if coloringType = 
 *    COLOR_INHERITED), the representation uses only one inherited color.  
 *    If the field PoMesh::valuesIndex is defined (and if coloringType != 
 *    COLOR_INHERITED), the representation is colored by using the current 
 *    data mapping applied to each mesh node value. (see PoMesh for more 
 *    explanations about the current data-mapping).
 * 
 *    The vector data of the mesh for this representation is unused.
 * @CATALOG_PARTS_INCLUDE pomeshskin.cat.html
 * 
 * 
 */
class MESHVIZ_API PoMeshSkin : public PoMesh3D {

  SO_KIT_HEADER(PoMeshSkin) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(groupSkin) ;


 public:

  /**
   * Constructor.
   */
  PoMeshSkin() ;

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild() ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

  void indexedMeshSkin(PbIndexedMesh3D *mesh) ;
  void cartGrid3DSkin(PbCartesianGrid3D *mesh) ;
  void paralCartGrid3DSkin(PbParalCartesianGrid3D *mesh) ;
  void regularGrid3DSkin(PbRegularCartesianGrid3D *mesh) ;

  void grid3DSkinFilter(const PbGrid3D *mesh,const PoCellFilter* cellFilter);

 protected:
  // Destructor
  virtual ~PoMeshSkin() ;  
  virtual void setDefaultOnNonWritingFields();
  virtual void addElementsAllCaches() ;
  virtual void preRebuild();

  /*----------------------------------------------------------------------------*/
 private:
  void updateUnStSkinColors() ;
  void updateUnStSkinTextures();

  void updateUnStSkinGeometry(PbIndexedMesh3D *mesh) ;
  void updateUnStSkinTopology() ;
  void updateUnStSkinData() ;
  void updateUnStSkinShape() ;

  void updateUnStSkinTopologyContouring(const PbIndexedMesh3D *mesh);
  void updateUnStSkinShapeContouring(const PbIndexedMesh3D *mesh);

  void updateGridSkinGeometry(const PbGrid3D *mesh) ;
  void updateGridSkinFilterTopology(const PbGrid3D *mesh) ;

  void updateGridSkinTopology(const PbGrid3D *mesh, SbBool add_normals) ;
  void updateGridSkinColors(PbGrid3D *mesh);
  void updateGridSkinTextures(PbGrid3D *mesh);

  void updateCartGridSkinGeometry(const PbCartesianGrid3D *mesh) ;
  void updateCartGridSkinContouringGeo(const PbCartesianGrid3D *mesh);

  void updateParalGridSkinGeometry(const PbParalCartesianGrid3D *mesh) ;
  void updateParalGridSkinContouringGeo(const PbParalCartesianGrid3D *mesh);

  void updateRegularGridSkinGeometry(const PbRegularCartesianGrid3D *mesh) ;
  void updateRegularGridSkinContouringGeo(const PbRegularCartesianGrid3D *mesh);

  void updateGridSkinContouringTopo(const PbGrid3D *mesh);

  uint32_t m_topoStateId; // id defining the state of the last PiMeshSkin used 

  SbBool m_lastBuiltWithFilter;
  SbBool m_topologyRebuilt;
};

/*----------------------------------------------------------------------------*/

#endif /* _PO_MESHSKIN_ */



