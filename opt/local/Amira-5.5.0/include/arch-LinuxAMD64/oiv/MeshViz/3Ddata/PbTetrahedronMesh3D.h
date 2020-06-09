/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_TETRAHEDRONMESH3D_
#define  _PB_TETRAHEDRONMESH3D_

#include <MeshViz/3Ddata/PbIndexedMesh3D.h>

class PbTetrahedronCell;

/**
 * @DTEXT  Defines a mesh of tetrahedrons.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *    Class to define an indexed 3D mesh made up of tetrahedrons. This mesh is 
 *    defined by a list of tetrahedrons. Each tetrahedron is defined by 4 indices 
 *    of nodes. 
 * 
 *    The nodes coordinates are defined by 3 arrays x_nod, y_nod, z_nod of 
 *    num_nodes floats. The tetrahedrons are defined by the array tetrahedron_index 
 *    of num_tetrahedrons*4 integers. tetrahedron_index[(n*4)+p] is the p-th 
 *    node index of the n-th tetrahedron of the mesh (0 <= p <= 3). Each
 *    tetrahedron must be numbered by repecting the following rule : the 3 first 
 *    indices define a facet of the tetrahedron and orient it towards the interior
 *    of the tetrahedron.
 * 
 *    Each facet of a tetrahedron may have 2 references in the mesh, that is, one 
 *    facet is common to 2 tetrahedrons. The facets which are referred to once 
 *    in the mesh define the mesh skin. 
 * 
 *    The values on the mesh nodes are defined by the 
 *    PbMesh::addValuesSet(set_index,val) method, where val argument is an 
 *    array of num_nodes floats.
 * 
 */
class MESHVIZ_API PbTetrahedronMesh3D : public PbIndexedMesh3D {


 public:

  /**
   * Constructor of a default simple mesh. See also PbMesh for more explanations about data duplication.
   */
  PbTetrahedronMesh3D(SbBool isDataDuplicate=TRUE) ;

  /**
   * Copy constructor
   */
  PbTetrahedronMesh3D(const PbTetrahedronMesh3D &mesh);

  /**
   * Constructor of a volume mesh. See also PbMesh for 
   * more explanations about data duplication.
   */
  PbTetrahedronMesh3D(int num_nodes, const float *x_nod, const float *y_nod, const float *z_nod,
                      int num_tetrahedrons, const int *tetrahedron_index,
                      SbBool is_data_duplicate=TRUE) ;

  /**
   * Destructor
   */
  ~PbTetrahedronMesh3D() ;

  /**
   * Assignment operator.
   */
  PbTetrahedronMesh3D& operator=(const PbTetrahedronMesh3D &mesh) ;

  /**
   * Equality comparison operator.
   */
  MESHVIZ_API friend int operator ==(const PbTetrahedronMesh3D &m1, const PbTetrahedronMesh3D &m2);

  /**
   * Inequality comparison operator.
   */
  MESHVIZ_API friend int operator !=(const PbTetrahedronMesh3D &m1, const PbTetrahedronMesh3D &m2)
  { return !(m1 == m2); }

  /**
   * Sets a new geometry
   */
  virtual void setGeometry(int num_nodes, const float *x_nod, const float *y_nod, const  float *z_nod,
                           int num_tetrahedrons, const int *tetrahedron_index);

  /**
   * Gets the current mesh geometry. tetrahedron_index must be used like a vector 
   * (i.e. tetrahedron_index[n])
   * [OIV-WRAPPER-ARG NO_WRAP,ARRAY{num_nodes},ARRAY{num_nodes},ARRAY{num_nodes},NO_WRAP,ARRAY{num_tetrahedrons}]
   */
  virtual void getGeometry(int &num_nodes, const float *&x_nod, const float *&y_nod, const float *&z_nod,
                           int &num_tetrahedrons, const int *&tetrahedron_index) const;

  /**
   * @deprecated 
   * Gets the current mesh geometry. tetrahedron_index must be used like a matrix.
   * (i.e. tetrahedron_index[cell_index][n], with 0 <= n <= 3)
   * [OIV-WRAPPER-NOT-WRAP]
   */
  virtual void getGeometry(int &num_nodes, const float *&x_nod, const float *&y_nod, const float *&z_nod,
                           int &num_tetrahedrons, const int **&tetrahedron_index) const;

  /**
   * Gets the list of index of cells that own the list of node "nod_indices"
   * (for example nod_indices can be the list of indices of a facet, an edge...)
   */
  virtual void getNodesOwnerCellsInd(const PbArrayOfInt &nod_indices, PbArrayOfInt &owner_cells) const;

  /**
   * Gets the cell which index is cell_index. Returns NULL if the cell does not exist
   * or if it is incorrect (flat), otherwise returns always a PbTetrahedronCell object. 
   * Attention! this method returns always the same adress of an internal private cell.
   * This private cell is updated each time getCell is called.
   */
  virtual const PbCell *getCell(int cell_index) const;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:

  float getLongestEdgeLength();
  // get the length of the longest edge of the mesh

  void meshCrossSection(PoMeshCrossSection *cross_section) const ; 
  void mesh3DVec(PoMesh3DVec *mesh_vec) const ;

  // find the mesh's cell that contain the point, given (optianal) an adjacent cell.
  // returns also the weight of the point in the found cell
  // be carefull : this is a naive method, prefer inherited method findContainingCell
  const PbCell* findContainingCellNaive(const SbVec3f &point, float tolerance, SbVec3f &pcoord, const PbCell *adjacent_cell) ;
  const PbCell* findContainingCellNaive(const SbVec3f &point, float tolerance, SbVec3f &pcoord) ;

  void print(FILE *fp) const;
  void printInfo() const {print(stdout);};

  // get a cell, but this cell has'nt coordinate specified
  virtual const PbCell *getTopoCell(int cell_index) const;

 protected:
  void updateCellBoundingBox() const;
  void updateOwnerCellsList() const;

 private:
  void copy(const PbTetrahedronMesh3D &mesh) ;
  void destroy();
  
  mutable PbTetrahedronCell *m_tetrahedron;
};

/*---------------------------------------------------------------------------*/

#endif /* _PB_TETRAHEDRONMESH3D_ */







