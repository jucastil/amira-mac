/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_HEXAHEDRONMESH3D_
#define  _PB_HEXAHEDRONMESH3D_

#include <MeshViz/3Ddata/PbIndexedMesh3D.h>

class PbHexahedronCell;

/**
 * @DTEXT  Defines a mesh of hexahedrons.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *    Class to define an indexed 3D mesh made up of hexahedrons. This mesh is 
 *    defined by a list of hexahedrons. Each hexahedron is defined by 8 indices 
 *    of nodes. 
 * 
 *    The nodes coordinates are defined by 3 arrays x_nod, y_nod, z_nod of 
 *    num_nodes floats. The hexahedrons are defined by the array hexahedron_index 
 *    of num_hexahedrons*8 integers. hexahedron_index[(n*8)+p] is the p-th 
 *    node index of the n-th hexahedron of the mesh (0 <= p <= 7). Each
 *    hexahedron must be numbered by repecting the following rule : the 4 first 
 *    indices define a facet of the hexahedron and orient it towards the interior
 *    of the hexahedron.
 * 
 *    Each facet of a hexahedron may have 2 references in the mesh, that is, one 
 *    facet is common to 2 hexahedrons. The facets which are referred to once in the 
 *    mesh define the mesh skin. 
 * 
 *    The values on the mesh nodes are defined by the 
 *    PbMesh::addValuesSet(set_index,val) method, where val argument is an 
 *    array of num_nodes floats.
 * 
 */
class MESHVIZ_API PbHexahedronMesh3D : public PbIndexedMesh3D {


 public:

  /**
   * Constructor of a default simple mesh. See also PbMesh for more explanations about data duplication.
   */
  PbHexahedronMesh3D(SbBool isDataDuplicate=TRUE) ;

  /**
   * Copy constructor
   */
  PbHexahedronMesh3D(const PbHexahedronMesh3D &mesh);

  /**
   * Constructor of a volume mesh. See also PbMesh for 
   * more explanations about data duplication.
   */
  PbHexahedronMesh3D(int num_nodes, const float *x_nod, const float *y_nod, const float *z_nod,
                     int num_hexahedrons, const int *hexahedron_index,
                     SbBool is_data_duplicate=TRUE) ;

  /**
   * Destructor
   */
  ~PbHexahedronMesh3D() ;

  /**
   * Assignment operator.
   */
  PbHexahedronMesh3D& operator=(const PbHexahedronMesh3D &mesh) ;

  /**
   * Equality comparison operator.
   */
  MESHVIZ_API friend int operator ==(const PbHexahedronMesh3D &m1, const PbHexahedronMesh3D &m2);

  /**
   * Inequality comparison operator.
   */
  MESHVIZ_API friend int operator !=(const PbHexahedronMesh3D &m1, const PbHexahedronMesh3D &m2)
  { return !(m1 == m2); }

  /**
   * Sets a new geometry
   */
  void setGeometry(int num_nodes, const float *x_nod, const float *y_nod, const  float *z_nod,
                   int num_hexahedrons, const int *hexahedron_index);

  /**
   * Gets the current mesh geometry. hexahedron_index must be used like a vector 
   * (i.e. hexahedron_index[n])
   * [OIV-WRAPPER-ARG NO_WRAP,ARRAY{num_nodes},ARRAY{num_nodes},ARRAY{num_nodes},NO_WRAP,ARRAY{num_hexahedrons}]
   */
  void getGeometry(int &num_nodes, const float *&x_nod, const float *&y_nod, const float *&z_nod,
                   int &num_hexahedrons, const int *&hexahedron_index) const;

  /**
   * @deprecated 
   * Gets the current mesh geometry. hexahedron_index must be used like a matrix.
   * (i.e. hexahedron_index[cell_index][n], with 0 <= n <= 7)
   * [OIV-WRAPPER-NO-WRAP]
   */
  void getGeometry(int &num_nodes, const float *&x_nod, const float *&y_nod, const float *&z_nod,
                   int &num_hexahedrons, const int **&hexahedron_index) const;

  /**
   * Gets the list of index of cells that own the list of node "nod_indices"
   * (for example nod_indices can be the list of indices of a facet, an edge...)
   */
  virtual void getNodesOwnerCellsInd(const PbArrayOfInt &nod_indices, PbArrayOfInt &owner_cells) const;

  /**
   * Gets the cell which index is cell_index. Returns NULL if the cell does not exist,
   * otherwise returns always a PbHexahedronCell object. 
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
  void print(FILE *fp) const;
  void printInfo() const {print(stdout);};
  
  // get a cell, but this cell has'nt coordinate specified
  virtual const PbCell *getTopoCell(int cell_index) const;

 protected:
  void updateCellBoundingBox() const;
  void updateOwnerCellsList() const;

 private:
  void copy(const PbHexahedronMesh3D &mesh) ;
  void destroy();

  mutable PbHexahedronCell *m_hexahedron;
} ;

/*---------------------------------------------------------------------------*/

#endif /* _PB_HEXAHEDRONMESH3D_ */







