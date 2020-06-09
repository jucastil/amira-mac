/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_CARTESIANGRID3D_
#define  _PB_CARTESIANGRID3D_

#include <MeshViz/3Ddata/PbGrid3D.h>

class PbHexahedronCell;

/**
 * @DTEXT  Defines a cartesian grid volume mesh.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *    Class to define a mesh represented by a 3D grid with cartesian coordinates. This 
 *    mesh is defined by a matrix num_x * num_y * num_z points forming (num_x - 1) * 
 *    (num_y - 1) * (num_z - 1) hexahedrons. Each point with index (i, j,k) in the mesh 
 *    (except for points along the mesh border) is connected to six points with indices 
 *    (i+1,j,k), (i,j+1,k), (i-1,j,k), (i,j-1,k), (i,j,k+1), (i,j,k-1). The values on the mesh 
 *    nodes are defined by the addValuesSet() method, where val argument is an array 
 *    of num_x * num_y * num_z floats.
 * 
 */
class MESHVIZ_API PbCartesianGrid3D : public PbGrid3D {


 public:

  /**
   * Constructor. See also PbMesh for more explanations about data duplication.
   */
  PbCartesianGrid3D(SbBool is_data_duplicated=TRUE) ;

  /**
   * Copy constructor.
   */
  PbCartesianGrid3D(const PbCartesianGrid3D &);

  /**
   * Constructor of a volume mesh. See also PbMesh for more explanations about data duplication.
   */
  PbCartesianGrid3D(int num_x, int num_y, int num_z, const float *xnod, const float *ynod, const float *znod, 
                    SbBool is_data_duplicated=TRUE) ;

  /**
   * Destructor.
   */
  ~PbCartesianGrid3D() ;

  /**
   * Assignment operator.
   */
  PbCartesianGrid3D& operator=(const PbCartesianGrid3D &mesh) ;

  /**
   * Equality comparison operator.
   */
  MESHVIZ_API friend int operator ==(const PbCartesianGrid3D &m1, const PbCartesianGrid3D &m2);

  /**
   * Inequality comparison operator.
   */
  MESHVIZ_API friend int operator !=(const PbCartesianGrid3D &m1, const PbCartesianGrid3D &m2)
  { return !(m1 == m2); }

  /**
   * Set new node coordinates without modifying the mesh topology.
   * For performance reasons, this method should be called instead of setGeometry when doing
   * a mesh deformation animation. It allows to update the coordinates of a existing level surface,
   * skin, cross section etc, without rebuilding them totally.
   */
  void setCoordinates(const float *xnod, const float *ynod, const float *znod);

  /**
   * Get the current coordinates of the nodes of this mesh.
   * Idem as getXYZGeometry.
   * @param size_xnod : size of the array xnod ( = num nodes of this mesh)
   * @param size_ynod : size of the array ynod ( = num nodes of this mesh)
   * @param size_znod : size of the array znod ( = num nodes of this mesh)
   */
  void getCoordinates(const float* &xnod, const float* &ynod, const float* &znod,
                      int &size_xnod, int &size_ynod, int &size_znod) const {
    xnod = x[0][0]; 
    ynod = y[0][0];
    znod = z[0][0];
    size_xnod = size_ynod = size_znod = numMeshNodes;
  }

  /**
   * Gets the mesh geometry. xa-ya-za can be used like a matrix (i.e. xa[i][j][k])
   * [OIV-WRAPPER-NO-WRAP]
   */
  void getGeometry(int &num_x, int &num_y, int &num_z, const float*** &xa, const float*** &ya, const float*** &za) const;

  /**
   * Gets the mesh geometry. xa-ya-za must be used like a vector (i.e. xa[n])
   * [OIV-WRAPPER-ARG NO_WRAP,NO_WRAP,NO_WRAP,ARRAY{num_x},ARRAY{num_y},ARRAY{num_z}]
   */
  void getGeometry(int &num_x, int &num_y, int &num_z, const float* &xa, const float* &ya, const float* &za) const {
    PbGrid3D::getGeometry(num_x,num_y,num_z,xa,ya,za);
  };

  /**
   * Gets the cell which index is cell_index. Returns NULL if the cell does not exist,
   * otherwise returns always a PbHexahedronCell object. 
   * Attention! this method returns always the same adress of an internal private cell.
   * This private cell is updated each time getCell is called.
   */
  virtual const PbCell *getCell(int cell_index) const;

  /**
   * Gets the coordinates of a node defined by its index.
   */
  virtual SbVec3f getNodeCoord(int nod_index) const;

  /**
   * Gets the coordinates of a node defined by its i,j,k indices on the grid.
   */
  SbVec3f getNodeCoord(int i, int j, int k) const {return SbVec3f(x[i][j][k],y[i][j][k],z[i][j][k]);};

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  
  float getLongestEdgeLength();
  // Gets the length of the longest edge of the mesh

  void meshCrossSection(PoMeshCrossSection *cross_section) const; 
  void meshCrossContour(PoMeshCrossContour *cross_contour) const ; 
  void meshSkeleton(PoMeshSkeleton *skeleton, const float *nod_values, 
                    float *x_cont, float *y_cont,float *z_cont) const; 
  void mesh3DVec(PoMesh3DVec *mesh_vec) const ;
  void print(FILE *fp) const;
  void printInfo() const {print(stdout);};

  // get a cell, but this cell has'nt coordinate specified
  virtual const PbCell *getTopoCell(int cell_index) const;

 protected:
  PbCartesianGrid3D(int num_x, int num_y, int num_z, SbBool is_data_duplicate=TRUE) ;
  void  updateCellBoundingBox() const;
  void setXYZGeometry(int num_x, int num_y, int num_z, const float *x, const float *y, const float *z);
  void getXYZGeometry(const float* &x, const float* &y, const float* &z) const;
  virtual void grid3DSkin(PoMeshSkin *_PoMeshSkin) const;

 private:
  void updateBoundingBox() const;

  float ***x, ***y, ***z;

  void copy(const PbCartesianGrid3D &mesh) ;
  void destroy();

  mutable PbHexahedronCell *m_hexahedron;

} ;

/*---------------------------------------------------------------------------*/

#endif /* _PB_CARTESIANGRID3D_ */







