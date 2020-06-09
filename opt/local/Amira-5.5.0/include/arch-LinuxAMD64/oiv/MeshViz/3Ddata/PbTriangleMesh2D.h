/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_TRIANGLEMESH2D_
#define  _PB_TRIANGLEMESH2D_

#include <MeshViz/3Ddata/PbIndexedMesh2D.h>
class PiContouring;
class PbTriangleCell;

/**
 * @DTEXT  Defines a surface mesh of triangles.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *    Class to define an indexed 2D mesh made up of triangles cells. This mesh 
 *    is defined by a list of triangles. Each triangles is defined by 3 
 *    indices of nodes. 
 * 
 *    The nodes coordinates are defined by 2 (or 3) arrays x_nod, y_nod, (and 
 *    z_nod) of num_nodes floats. The triangles are defined by the array 
 *    triangle_index of num_triangles*3 integers. triangle_index[(n*3)+p] 
 *    is the p-th node index of the n-th triangle of the mesh (0 <= p <= 3). 
 * 
 *    Each edge of a triangle may have 2 references in the mesh, that is, one 
 *    edge is common to 2 triangles. The edges which are referred to once in the 
 *    mesh define the limits of the mesh.
 * 
 *    The geometry of this mesh can be defined also from a points field. In this
 *    case the Voronoi method is used to build the triangle mesh.
 * 
 *    The values on the mesh nodes are defined by the 
 *    PbMesh::addValuesSet(set_index,val) method, where val argument is an 
 *    array of num_nodes floats.
 * 
 */
class MESHVIZ_API PbTriangleMesh2D : public PbIndexedMesh2D {


 public:

  /**
   * Constructor of a default simple mesh. See also PbMesh for more explanations about data duplication.
   */
  PbTriangleMesh2D(SbBool isDataDuplicate=TRUE) ;

  /**
   * Copy constructor.
   */
  PbTriangleMesh2D(const PbTriangleMesh2D &mesh);

  /**
   * Constructor of a 2D surface mesh. See also PbMesh for 
   * more explanations about data duplication.
   */
  PbTriangleMesh2D(int num_nodes, const float *x_nod, const float *y_nod,
                   int num_triangles, const int32_t *triangle_index,
                   SbBool is_data_duplicate=TRUE) ;

  /**
   * Constructor of a 3D surface mesh. See also PbMesh for 
   * more explanations about data duplication.
   */
  PbTriangleMesh2D(int num_nodes, const float *x_nod, const float *y_nod, const float *z_nod,
                   int num_triangles, const int32_t *triangle_index,
                   SbBool is_data_duplicate=TRUE) ;

  /**
   * Destructor.
   */
  ~PbTriangleMesh2D();

  /**
   * Assignment operator.
   */
  PbTriangleMesh2D& operator=(const PbTriangleMesh2D &mesh) ;

  /**
   * Equality comparison operator.
   */
  MESHVIZ_API friend int operator ==(const PbTriangleMesh2D &m1, const PbTriangleMesh2D &m2);

  /**
   * Inequality comparison operator.
   */
  MESHVIZ_API friend int operator !=(const PbTriangleMesh2D &m1, const PbTriangleMesh2D &m2)
  { return !(m1 == m2); }

  /**
   * Sets a new 2D geometry
   */
  void setGeometry(int num_nodes, const float *x_nod, const float *y_nod,
                   int num_triangles, const int *triangle_index);

  /**
   * Set a new 2D geometry from a points field.
   * The triangulation is realized by the DELAUNAY method.
   */
  void setGeometry(int numPoints, const float *xPointsField, const float *yPointsField) ;

  /**
   * Sets a new 3D geometry
   */
  void setGeometry(int num_nodes, const float *x_nod, const float *y_nod, const float *z_nod,
                   int num_triangles, const int *triangle_index);

  /**
   * Gets the current mesh geometry (x, y nodes coordinates). 
   * [OIV-WRAPPER-ARG NO_WRAP,ARRAY{num_nodes},ARRAY{num_nodes},NO_WRAP,ARRAY{num_triangles}]
   */
  void getGeometry(int &num_nodes, const float *&x_nod, const float *&y_nod,
                   int &num_triangles, const int32_t *&triangle_index) const;

  /**
   * Gets the current mesh geometry (x, y and z nodes coordinates). 
   * [OIV-WRAPPER-ARG NO_WRAP,ARRAY{num_nodes},ARRAY{num_nodes},ARRAY{0},NO_WRAP,ARRAY{num_triangles}]
   */
  void getGeometry(int &num_nodes, const float *&x_nod, const float *&y_nod, const float* &z_nod,
                   int &num_triangles, const int32_t *&triangle_index) const;

  /**
   * Gets the current mesh geometry (x, y nodes coordinates). triangle_index 
   * must be used like a matrix. (i.e. triangle_index[cell_index][n], with 0 <= n < 3)
   * [OIV-WRAPPER-NO-WRAP]
   */
  void getGeometry(int &num_nodes, const float *&x_nod, const float *&y_nod,
                   int &num_triangles, const int32_t **&triangle_index) const;

  /**
   * Gets the current mesh geometry (x, y  and z nodes coordinates). triangle_index 
   * must be used like a matrix. (i.e. triangle_index[cell_index][n], with 0 <= n < 3)
   * [OIV-WRAPPER-NO-WRAP]
   */
  void getGeometry(int &num_nodes, const float *&x_nod, const float *&y_nod, const float* &z_nod,
                   int &num_triangles, const int32_t **&triangle_index) const;

  /**
   * Gets the list of index of cells that own the node "nod_index".
   */
  virtual void getNodesOwnerCellsInd(const PbArrayOfInt &nod_indices, PbArrayOfInt &owner_cells) const;

  /**
   * Gets the cell which index is cell_index. Returns NULL if the cell does not exist,
   * otherwise returns always a PbTriangleCell object. 
   * Attention! this method returns always the same adress of an internal private cell.
   * This private cell is updated each time getCell is called.
   */
  virtual const PbCell *getCell(int cell_index) const;

  /**
   * Changes orientation of cells during visualization of 2D surface mesh. 
   * The ordering of the indices of an cell defines the direction of its normal 
   * vector and so its orientation. When the mesh is visualized in 2D, the direction 
   * of the normal of an cell is either Z+ or Z-. If any cell of the mesh does 
   * not have the same orientation, it can change the representation because the 
   * lighting depends on the orientation.
   */
  void setElemOrientation(ElemOrientation elem_orient);


 PoINTERNAL public:

  void meshLines(PoMeshLines *_PoMeshLines) const; 
  void meshFilled(PoMeshFilled *_PoMeshFilled) const; 
  void meshContouring(PiContouring *_PiContouring, const float *z) const;
  void mesh2DVec(PoMesh2DVec *mesh_vec) const ;

  virtual void getLimitIndices(PbArrayOfInt &nodesIndex, PbArrayOfInt &limitSizes) const; 
  virtual void getOneLimit(int, PbArrayOfInt&);

  void evaluateFaultNode(int fault_node, const PbArrayOfInt &adjacent_nodes, 
                         int first_fault_node_id, int num_set, float **val);
  void evaluateFaultNodeWithDerivs(int fault_node, const PbArrayOfInt &adjacent_nodes, 
                                   int first_fault_node_id, int num_set, float **val);

  virtual int getAdjacentCellAround(int cellIndex, PbArrayOfInt &edge);

  void print(FILE *fp) const;
  void printInfo() const {print(stdout);};

 protected:
  virtual const PbCell* findContainingCellProtected(const SbVec3f &point, float tolerance, SbVec3f &pcoord, PbArrayOfInt &test_cell) const;
  void updateCellBoundingBox() const;
  void updateOwnerCellsList() const;

 private:

  void constructXYGeometry(int num_nodes, const float *x_nod, const float *y_nod, 
                           int num_triangles, const int32_t *triangle_index,
                           SbBool is_data_duplicate);
  void setXYGeometry(int num_nodes, const float *x_nod, const float *y_nod, 
                     int num_triangles, const int *triangle_index);

  SbBool m_isVoronoiGeometry ;
  int32_t **triangleIndex;

  void copy(const PbTriangleMesh2D &mesh) ;
  void destroy();

  mutable PbTriangleCell *m_triangle;
};

/*---------------------------------------------------------------------------*/

#endif /* _PB_TRIANGLEMESH2D_ */







