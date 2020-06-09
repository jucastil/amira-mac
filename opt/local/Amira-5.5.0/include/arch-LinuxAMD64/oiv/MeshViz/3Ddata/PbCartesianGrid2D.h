/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_CARTESIANGRID2D_
#define  _PB_CARTESIANGRID2D_

#include <MeshViz/3Ddata/PbGrid2D.h>

class PiContouring;
class PbQuadrangleCell;

/**
 * @DTEXT  Defines a cartesian grid surface mesh.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *    Class to define a mesh represented by a grid with cartesian coordinates. This mesh 
 *    is defined by a matrix num_x * num_y points forming (num_x - 1) * (num_y - 1) 
 *    quadrangles. Each point with index (i, j) in the mesh (except for points along the 
 *    mesh border) is connected to four points with indices (i+1,j), (i,j+1), (i-1,j),
 *    (i,j-1). x, y and z are array of num_x * num_y floats.
 * 
 *    The values on the mesh nodes are defined by the PbMesh::addValuesSet() method, 
 *    where val argument is an array of num_x * num_y floats.
 * 
 */
class MESHVIZ_API PbCartesianGrid2D : public PbGrid2D {


 public:

  /**
   * Constructor of a default simple mesh. See also PbMesh for more explanations about data duplication.
   */
  PbCartesianGrid2D(SbBool is_data_duplicated=TRUE) ;

  /**
   * Copy constructor.
   */
  PbCartesianGrid2D(const PbCartesianGrid2D &);

  /**
   * Constructor of a 2D surface mesh. See also PbMesh for 
   * more explanations about data duplication.
   */
  PbCartesianGrid2D(int num_x, int num_y, const float *x, const float *y, SbBool is_data_duplicated=TRUE) ;

  /**
   * Constructor of a 3D surface mesh. See also PbMesh for 
   * more explanations about data duplication.
   */
  PbCartesianGrid2D(int num_x, int num_y, const float *x, const float *y, const float *z, SbBool is_data_duplicated=TRUE) ;

  /**
   * Destructor.
   */
  ~PbCartesianGrid2D() ;

  /**
   * Assignment operator.
   */
  PbCartesianGrid2D& operator=(const PbCartesianGrid2D &mesh) ;

  /**
   * Equality comparison operator.
   */
  MESHVIZ_API friend int operator ==(const PbCartesianGrid2D &m1, const PbCartesianGrid2D &m2);

  /**
   * Inequality comparison operator.
   */
  MESHVIZ_API friend int operator !=(const PbCartesianGrid2D &m1, const PbCartesianGrid2D &m2)
  { return !(m1 == m2); }

  /**
   * Gets the mesh 2D geometry. xa-ya can be used like a matrix (i.e xa[i][j])
   * [OIV-WRAPPER-NO-WRAP]
   */
  void getGeometry(int &num_x, int &num_y, const float** &xa, const float** &ya) const;

  /**
   * Gets the mesh 3D geometry. xa-ya-za can be used like a matrix (i.e xa[i][j])
   * Attention! For a 2D mesh, za is NULL.
   * [OIV-WRAPPER-NO-WRAP]
   */
  void getGeometry(int &num_x, int &num_y, const float** &xa, const float** &ya, const float**&za) const;

  /**
   * Gets the mesh 2D geometry. xa-ya must be used like a vector (i.e. xa[n])
   * [OIV-WRAPPER-ARG NO_WRAP,NO_WRAP,ARRAY{num_x},ARRAY{num_y}]
   */
  void getGeometry(int &num_x, int &num_y, const float* &xa, const float* &ya) const {
    PbGrid2D::getGeometry(num_x,num_y,xa,ya);
  };

  /**
   * Gets the mesh 3D geometry. xa-ya-za can be used like a vector (i.e. xa[n]).
   * Attention! For a 2D mesh, z is NULL.
   * [OIV-WRAPPER-ARG NO_WRAP,NO_WRAP,ARRAY{num_x},ARRAY{num_y},ARRAY{0}]
   */
  void getGeometry(int &num_x, int &num_y, const float* &xa, const float* &ya, const float* &za) const {
    PbGrid2D::getGeometry(num_x,num_y,xa,ya,za);
  };

  /**
   * Gets the cell which index is cell_index. Returns NULL if the cell does not exist,
   * otherwise returns always a PbQuadrangleCell object. 
   * Attention! this method returns always the same adress of an internal private cell.
   * This private cell is updated each time getCell is called.
   */
  virtual const PbCell *getCell(int cell_index) const;

  /**
   * Gets the coordinates of a node defined by its index on the grid.
   */
  virtual SbVec3f getNodeCoord(int nod_index) const;

  /**
   * Gets the coordinates of a node defined by its i,j indices on the grid.
   */
  virtual SbVec3f getNodeCoord(int i, int j) const;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  
  void meshLines(PoMeshLines *_PoMeshLines) const; 
  void meshFilled(PoMeshFilled *_PoMeshFilled) const; 
  void meshContouring(PiContouring *_PiContouring, const float *z) const;
  void mesh2DVec(PoMesh2DVec *mesh_vec) const ;

  void getNodesCoord(const float *z, SoMFVec3f &vertices) const;

  void print(FILE *fp) const;
  void printInfo() const {print(stdout);};

 protected:
  virtual const PbCell* findContainingCellProtected(const SbVec3f &point, float tolerance, SbVec3f &pcoord, PbArrayOfInt &test_cell) const;
  PbCartesianGrid2D(int num_x, int num_y, SbBool is_data_duplicate=TRUE) ;
  PbCartesianGrid2D(int num_x, int num_y, const float *z, SbBool is_data_duplicate=TRUE) ;
  void constructXYGeometry(const float *xn, const float *yn, SbBool is_data_duplicate);
  void setXYGeometry(int num_x, int num_y, const float *x, const float *y);
  void getXYGeometry(const float* &x, const float* &y) const;

 private:
  float **x, **y;

  void updateBoundingBox() const;
  void copy(const PbCartesianGrid2D &mesh) ;
  void destroy();

  mutable PbQuadrangleCell *m_quadrangle;
} ;

/*---------------------------------------------------------------------------*/

#endif /* _PB_CARTESIANGRID2D_ */







