/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_INDEXEDMESH3D_
#define  _PB_INDEXEDMESH3D_

#include <MeshViz/3Ddata/PbMesh3D.h>

class PbHexahedronCell;
class PbTetrahedronCell;
class PbWedgeCell;
class PbPyramidCell;

/**
 * @DTEXT  Defines a volume mesh of polyhedrons.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *    Class to define an indexed 3D mesh. Each cell of this type of mesh is a 
 *    polyhedron with 4, 5, 6 or 8 nodes. Each polyhedron is defined by a list 
 *    of node indices.
 * 
 *    The nodes coordinates are defined by 3 arrays x_nod, y_nod, z_nod of 
 *    num_nodes floats. The cells are defined by the array cell_type (size 
 *    num_cells) and cell_index. cell_type[n] defines the number of nodes in the 
 *    n-th cells: if cell_type[i] = 4, the i-th cell is a tetrahedron, if 
 *    cell_type[i] = 5 it is a pyramid, if cell_type[i] = 6 it is a prism, and 
 *    if cell_type[i] = 8 it is an hexahedron. cell_index is an array of S 
 *    integers, where S = cell_type[0] + cell_type[1] + ... + cell_type[num_nodes - 1]. 
 *    cell_index contains the num_cells lists of node indices which define each 
 *    cell topology.
 * 
 *    Each facet of a cell may have 2 references in the mesh, that is, one 
 *    facet is common to 2 cells. The facets which are referred to once in the 
 *    mesh define the mesh skin. 
 * 
 *    The values on the mesh nodes are defined by the 
 *    PbMesh::addValuesSet(set_index,val) method, where val argument is an 
 *    array of num_nodes floats.
 * 
 */
class MESHVIZ_API PbIndexedMesh3D : public PbMesh3D {


 public:



  /**
   * Constructor of a default simple mesh. See also PbMesh for more explanations about data duplication.
   */
  PbIndexedMesh3D(SbBool is_data_duplicate=TRUE);

  /**
   * Copy constructor
   */
  PbIndexedMesh3D(const PbIndexedMesh3D &mesh);

  /**
   * Constructor of a 3D volume mesh. See also PbMesh for 
   * more explanations about data duplication.
   */
  PbIndexedMesh3D(int num_nodes, const float *x_nod, const float *y_nod, const float *z_nod,
                  int num_cells, const int *cell_index, const int *cell_type,
                  SbBool is_data_duplicate=TRUE) ;

  /**
   * Destructor
   */
  ~PbIndexedMesh3D() ;

  /**
   * Assignment operator.
   */
  PbIndexedMesh3D& operator=(const PbIndexedMesh3D &mesh) ;

  /**
   * Equality comparison operator.
   */
  MESHVIZ_API friend int operator ==(const PbIndexedMesh3D &m1, const PbIndexedMesh3D &m2);

  /**
   * Inequality comparison operator.
   */
  MESHVIZ_API friend int operator !=(const PbIndexedMesh3D &m1, const PbIndexedMesh3D &m2)
  { return !(m1 == m2); }

  /**
   * Sets a new geometry
   */
  void setGeometry(int num_nodes, const float *x_nod, const float *y_nod,  const float *z_nod,
                   int num_cells, const int *cell_index, const int *cell_type);

  /**
   * Set new node coordinates without modifying the mesh topology.
   * For performance reasons, this method should be called instead of setGeometry when doing
   * a mesh deformation animation. It allows to update the coordinates of a existing level surface,
   * skin, cross section etc, without rebuilding them totally.
   */
  void setCoordinates(const float *x_nod, const float *y_nod, const float *z_nod);

  /**
   * Get the current coordinates of the nodes of this mesh.
   * @param size_xnod : size of the array xnod
   * @param size_ynod : size of the array ynod
   * @param size_znod : size of the array znod
   */
  void getCoordinates(const float* &xnod, const float* &ynod, const float* &znod,
                      int &size_xnod, int &size_ynod, int &size_znod) const {
    xnod = xNodes;
    ynod = yNodes;
    znod = zNodes;
    size_xnod = size_ynod = size_znod = numMeshNodes;
  }

  /**
   * Gets the current mesh geometry
   * [OIV-WRAPPER-ARG NO_WRAP,ARRAY{num_nodes},ARRAY{num_nodes},ARRAY{num_nodes},NO_WRAP,ARRAY{num_cells},ARRAY{num_cells}]
   * [OIVJAVA-WRAPPER PACK{GeometryInfo}]
   */
  void getGeometry(int &num_nodes, const float* &x_nod, const float* &y_nod, const float* &z_nod,
                   int &num_cells, const int *&cell_index, const int *&cell_type) const ;

  /**
   * Gets the mesh nodes coordinate arrays
   * [OIV-WRAPPER-ARG NO_WRAP,ARRAY{num_nodes},ARRAY{num_nodes},ARRAY{num_nodes}]
   * [OIVJAVA-WRAPPER PACK{NodesInfo}]
   */
  void getNodes(int &num_nodes, const float* &x_nod, const float* &y_nod, const float* &z_nod) const;

  /**
   * Gets the coordinates of a node.
   */
  virtual SbVec3f getNodeCoord(int nod_index) const { return SbVec3f(xNodes[nod_index],yNodes[nod_index],zNodes[nod_index]);};

  /**
   * Gets the list of index of cells that own the node "nod_index".
   */
  virtual void getNodeOwnerCellsInd(int nod_index, PbArrayOfInt &owner_cells) const;

  /**
   * Gets the cell which index is cell_index. Returns NULL if the cell does not exist
   * or if it is incorrect (ie flat tetrahedron).
   * Attention! this method returns always the same adress of an internal private cell.
   * This private cell is updated each time getCell is called.
   */
  virtual const PbCell *getCell(int cell_index) const;


 PoINTERNAL public:

  // get the length of the longest edge of the mesh
  float getLongestEdgeLength();

  void meshSkin(PoMeshSkin *mesh_skin) const ; 
  void meshSkinFilter(PoMeshSkin *_PoMeshSkin,const PoCellFilter* cellFilter) const; // will be removed
  void meshCrossSection(PoMeshCrossSection *cross_section) const; 
  void meshCrossContour(PoMeshCrossContour *cross_contour) const; 
  void meshSkeleton(PoMeshSkeleton *skeleton, const float *nod_values, 
                    float *x_cont, float *y_cont,float *z_cont) const; 
  void mesh3DVec(PoMesh3DVec *mesh_vec) const ;
  SbBool isEmpty() const;
  void print(FILE *fp) const;
  void printInfo() const {print(stdout);};

  // get a cell, but this cell has'nt coordinate specified
  virtual const PbCell *getTopoCell(int cell_index) const;

 protected:
  void updateCellBoundingBox() const;
  virtual void updateOwnerCellsList() const;
  virtual void deleteOwnerCellsList() const;
  void updateBoundingBox() const;

  int allocNodes;
  float *xNodes, *yNodes, *zNodes;
  int  allocElemIndex, *elemIndex, elemIndexSize;
  int allocElem, *elemType;
  // set vertices coordinates of a indexed mesh
  void setVertices(int num_nodes, const float *x_nod, const float *y_nod, const float *z_nod);

  mutable PbArrayOfInt *m_ownerCellsList;

  // list of the first index of each cell of this mesh
  mutable PbArrayOfInt m_firstIndexOfCell;

 private:
  void copy(const PbIndexedMesh3D &mesh) ;
  void destroy();
  PbHexahedronCell     *m_hexahedron;
  PbTetrahedronCell    *m_tetrahedron;
  PbWedgeCell          *m_wedge;
  PbPyramidCell        *m_pyramid;
} ;


inline void 
PbIndexedMesh3D::meshSkinFilter(PoMeshSkin *,const PoCellFilter* ) const
{}

/*---------------------------------------------------------------------------*/

#endif /* _PB_INDEXEDMESH3D_ */







