/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_INDEXEDMESH2D_
#define  _PB_INDEXEDMESH2D_

#include <Inventor/STL/vector>

#include <MeshViz/3Ddata/PbMesh2D.h>
class PiContouring;
class PiEdgeList;
class PiEdge;
class PbQuadrangleCell;
class PbTriangleCell;

/**
 * @DTEXT  Defines a surface mesh of polygons.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *    Class to define an indexed 2D mesh. Each cell of this type of mesh is a 
 *    polygon with any number of nodes. Each polygon cell is defined by a list 
 *    of indices in an array of nodes. 
 * 
 *    The nodes coordinates are defined by 2 (or 3) arrays
 *    x_nod, y_nod (and z_nod) of num_nodes floats. The cells are defined by the
 *    array cell_type (size num_cells) and cell_index. cell_type[n] defines the 
 *    number of nodes in the n-th cells: if cell_type[i] = 3, the 
 *    i-th cell is a triangle, if cell_type[i] = 4, it is a quadrangle...
 *    cell_index is an array of S integers, where S = cell_type[0] + cell_type[1]
 *    + ... + cell_type[num_nodes - 1]. cell_index contains the num_cells lists 
 *    of node indices which define each cell topology.
 * 
 *    Each edge of a cell may have 2 references in the mesh, that is, one 
 *    edge is common to 2 cells. The edges which are referred to once in the 
 *    mesh define the limits of the mesh.
 * 
 *    The values on the mesh nodes are defined by the 
 *    PbMesh::addValuesSet(set_index,val) method, where val argument is an 
 *    array of num_nodes floats.
 * 
 */
class MESHVIZ_API PbIndexedMesh2D : public PbMesh2D {


 public:



  /**
   * Constructor of a default simple mesh. See also PbMesh for more explanations about data duplication.
   */
  PbIndexedMesh2D(SbBool is_data_duplicate=TRUE);

  /**
   * Copy constructor.
   */
  PbIndexedMesh2D(const PbIndexedMesh2D &mesh);

  /**
   * Constructor of a 2D surface mesh. See also PbMesh for 
   * more explanations about data duplication.
   */
  PbIndexedMesh2D(int num_nodes, const float *x_nod, const float *y_nod, 
                  int num_cells, const int *cell_index, const int *cell_type,
                  SbBool is_data_duplicate=TRUE) ;

  /**
   * Constructor of a 3D surface mesh. See also PbMesh for 
   * more explanations about data duplication.
   */
  PbIndexedMesh2D(int num_nodes, const float *x_nod, const float *y_nod, const float *z_nod, 
                  int num_cells, const int *cell_index, const int *cell_type,
                  SbBool is_data_duplicate=TRUE) ;

  /**
   * Destructor.
   */
  ~PbIndexedMesh2D() ;

  /**
   * Assignment operator.
   */
  PbIndexedMesh2D& operator=(const PbIndexedMesh2D &mesh) ;

  /**
   * Equality comparison operator.
   */
  MESHVIZ_API friend int operator ==(const PbIndexedMesh2D &m1, const PbIndexedMesh2D &m2);

  /**
   * Inequality comparison operator.
   */
  MESHVIZ_API friend int operator !=(const PbIndexedMesh2D &m1, const PbIndexedMesh2D &m2)
  { return !(m1 == m2); }

  /**
   * Sets a new 2D geometry
   */
  void setGeometry(int num_nodes, const float *x_nod, const float *y_nod, 
                   int num_cells, const int *cell_index, const int *cell_type);

  /**
   * Sets a new 3D geometry
   */
  void setGeometry(int num_nodes, const float *x_nod, const float *y_nod, const float *z_nod, 
                   int num_cells, const int *cell_index, const int *cell_type);

  /**
   * Gets the current mesh geometry (x, y and z nodes coordinates). 
   * [OIV-WRAPPER-ARG NO_WRAP,ARRAY{numNode},ARRAY{numNode},ARRAY{numNode},NO_WRAP,ARRAY{num_cells},ARRAY{num_cells}]
   * [OIVJAVA-WRAPPER PACK{GeometryInfo}]
   */
  void getGeometry(int &numNode, const float* &x_nod, const float* &y_nod, const float* &z_nod,
                   int &num_cells, const int32_t *&cell_index, const int32_t *&cell_type) const ;

  /**
   * Gets the current mesh geometry (x, y nodes coordinates). 
   * [OIV-WRAPPER-ARG NO_WRAP,ARRAY{numNode},ARRAY{numNode},NO_WRAP,ARRAY{num_cells},ARRAY{num_cells}]
   * [OIVJAVA-WRAPPER NAME{get2DGeometry},PACK{GeometryInfo}]
   */
  void getGeometry(int &numNode, const float* &x_nod, const float* &y_nod,
                   int &num_cells, const int32_t *&cell_index, const int32_t *&cell_type) const ;

  /**
   * Gets the mesh nodes coordinates (x,y,z coordinates)
   * [OIV-WRAPPER-ARG NO_WRAP,ARRAY{num_nodes},ARRAY{num_nodes},ARRAY{num_nodes}]
   * [OIVJAVA-WRAPPER PACK{NodesInfo}]
   */
  void getNodes(int &num_nodes, const float* &x_nod, const float* &y_nod, const float* &z_nod) const;

  /**
   * Gets the mesh nodes coordinates (only x,y coordinates)
   * [OIV-WRAPPER-ARG NO_WRAP,ARRAY{num_nodes},ARRAY{num_nodes}]
   * [OIVJAVA-WRAPPER NAME{get2DNodes},PACK{NodesInfo}]
   */
  void getNodes(int &num_nodes, const float* &x_nod, const float* &y_nod) const;

  /**
   * Gets the coordinates of a node.
   */
  virtual SbVec3f getNodeCoord(int nod_index) const;

  /**
   * Gets the list of index of cells that own the node "nod_index".
   */
  virtual void getNodeOwnerCellsInd(int nod_index, PbArrayOfInt &owner_cells) const;

  /**
   * Gets the cell which index is cell_index. Returns NULL if the cell does not exist.
   * Attention! this method returns always the same adress of an internal private cell.
   * This private cell is updated each time getCell is called.
   */
  virtual const PbCell *getCell(int cell_index) const;

  /**
   *  Cell orientation for visualization of 2D surface mesh.
   */
  enum ElemOrientation {
    /**
     *  The cell orientation is kept
     */
    ORIENTATION_AS_IS, 
    /**
     *  Cell is oriented with a normal = (0,0,1)
     */
    ORIENTATION_ZPOS,  
    /**
     *  Cell is oriented with a normal = (0,0,-1)
     */
    ORIENTATION_ZNEG   
  } ;



  /**
   * Changes orientation of cells during visualization of 2D surface mesh. 
   * The ordering of the indices of an cell defines the direction of its normal 
   * vector and so its orientation. When the mesh is visualized in 2D, the direction 
   * of the normal of an cell is either Z+ or Z-. If any cell of the mesh does 
   * not have the same orientation, it can change the representation because the 
   * lighting depends on the orientation.
   */
  virtual void setElemOrientation(ElemOrientation cell_orient);

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:

  void meshLines(PoMeshLines *_PoMeshLines) const; 
  void meshFilled(PoMeshFilled *_PoMeshFilled) const; 
  void meshContouring(PiContouring *_PiContouring, const float *z) const;
  void mesh2DVec(PoMesh2DVec *mesh_vec) const ;
  SbBool isEmpty() const;

  void print(FILE *fp) const;
  void printInfo() const {print(stdout);};

  ElemOrientation getElemOrientation() const;
  const SbBool * getOrientFlags() const;
  virtual SbVec3f getFirstCellNormal() const;

  void getNodesCoord(const float *z, SoMFVec3f &vertices) const;

  virtual void getLimitIndices(PbArrayOfInt &nodesIndex, PbArrayOfInt &limitSizes) const; 

 protected:
  PbIndexedMesh2D(int num_z, const float *z, SbBool is_data_duplicate=TRUE);

  virtual const PbCell* findContainingCellProtected(const SbVec3f &point, float tolerance, SbVec3f &pcoord, PbArrayOfInt &test_cell) const;
  void updateCellBoundingBox() const;
  virtual void updateOwnerCellsList() const;
  virtual void deleteOwnerCellsList() const;
  void updateBoundingBox() const;

  ElemOrientation elemOrientation;
  SbBool *elemOrientFlags;
  int allocNodes;
  float *xNodes, *yNodes;
  int32_t allocElemIndex, *elemIndex, elemIndexSize;
  int32_t allocElem, *elemType;
  // set vertices coordinates of an indexed mesh
  void setVertices(int num_nodes, const float *x_nod, const float *y_nod);
  
  mutable std::vector<PbArrayOfInt> m_ownerCellsList;

 private:

  void constructDefaultMesh();
  void constructXYGeometry(int num_nodes, const float *x_nod, const float *y_nod, 
                           int num_cells, const int *cell_index, const int *cell_type,
                           SbBool is_data_duplicate);
  void setXYGeometry(int num_nodes, const float *xNode, const float *yNode, 
                     int num_cells, const int *cell_index, const int *cell_type);

  void copy(const PbIndexedMesh2D &mesh) ;
  void destroy();

  PbQuadrangleCell *m_quadrangle;
  PbTriangleCell   *m_triangle;
} ;

/*---------------------------------------------------------------------------*/

#endif /* _PB_INDEXEDMESH2D_ */







