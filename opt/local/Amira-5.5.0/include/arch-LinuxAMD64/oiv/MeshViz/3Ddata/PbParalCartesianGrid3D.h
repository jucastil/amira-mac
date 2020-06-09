/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_PARALCARTESIANGRID3D_
#define  _PB_PARALCARTESIANGRID3D_

#include <MeshViz/3Ddata/PbCartesianGrid3D.h>
class PbVoxelCell;

/**
 * @DTEXT  Defines a parallel cartesian grid volume mesh.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *    Class to define a volume mesh represented by a grid, with cartesian 
 *    coordinates, where the lines are parallel to X, Y or Z axis. This mesh is 
 *    defined by num_x lines orthogonal to X axis, num_y lines orthogonal to Y 
 *    axis and num_z lines orthogonal to Z axis, and by one or two values at 
 *    each vertices of the mesh. This mesh is comparable to a set of parallel 
 *    PbParalCartesianGrid2D. x is an array of num_x floats, y an array of 
 *    num_y floats, and z an array of num_z floats.
 *    
 *    The values on the mesh nodes are defined by the 
 *    PbMesh::addValuesSet(set_index,val) method, where val argument is an 
 *    array of num_x * num_y * num_z floats.
 * 
 */
class MESHVIZ_API PbParalCartesianGrid3D : public PbCartesianGrid3D {


 public:

  /**
   * Constructor of a default simple mesh. See also PbMesh for more explanations about data duplication.
   */
  PbParalCartesianGrid3D(SbBool isDataDuplicate=TRUE) ;

  /**
   * Copy constructor
   */
  PbParalCartesianGrid3D(const PbParalCartesianGrid3D &);

  /**
   * Constructor of a 3D parallel grid mesh. See also PbMesh for 
   * more explanations about data duplication.
   */
  PbParalCartesianGrid3D(int num_x, int num_y, int num_z, const float *xnod, const float *ynod, const float *znod, SbBool isDataDuplicate=TRUE) ;

  /**
   * Destructor.
   */
  ~PbParalCartesianGrid3D() ;

  /**
   * Assignment operator.
   */
  PbParalCartesianGrid3D& operator=(const PbParalCartesianGrid3D &mesh) ;

  /**
   * Equality comparison operator.
   */
  MESHVIZ_API friend int operator ==(const PbParalCartesianGrid3D &m1, const PbParalCartesianGrid3D &m2);

  /**
   * Inequality comparison operator.
   */
  MESHVIZ_API friend int operator !=(const PbParalCartesianGrid3D &m1, const PbParalCartesianGrid3D &m2)
  { return !(m1 == m2); }

  virtual const PbCell* findContainingCell(const SbVec3f &point, float tolerance, SbVec3f &pcoord, const PbCell *adjacent_cell) const;

  /**
   * Find the mesh's cell that contains the point. If the (optional) adjacent cell is given,
   * searching the containing cell starts by the cells around this adjacent one. Returns 
   * also the parametric coordinates of the point in the found cell. Parametric coordinates 
   * are the coordinates of the point relative to a topologically equivalent unit cell. A point
   * is inside a cell if its parametric coordinates range from 0 to 1. However we use a test with
   * a tolerance value: a point is inside the cell if its parametric coordinates p verify
   * -tolerance <= p <= 1+tolerance. Parametric coordinates are useful to interpolate the
   * value in the cell (see PbCell::getValue).
   * Attention! This method returns always the same address of an internal private cell.
   * This private cell is updated each time #findContainingCell is called.
   * If the cell exists, it returns always a PbVoxelCell object.
   */
  virtual const PbCell* findContainingCell(const SbVec3f &point, float tolerance, SbVec3f &pcoord) const;

  /**
   * Gets the cell which index is cell_index. Returns NULL if the cell does not exist,
   * otherwise returns always a PbVoxelCell object. 
   * Attention! This method returns always the same address of an internal private cell.
   * This private cell is updated each time getCell is called.
   */
  virtual const PbCell *getCell(int cell_index) const;

  /**
   * Gets the coordinates of a node.
   */
  virtual SbVec3f getNodeCoord(int nod_index) const;

  /**
   * Gets the coordinates of a node defined by its i,j,k indices on the grid
   */
  virtual SbVec3f getNodeCoord(int i, int j, int k) const {return SbVec3f(x[i],y[j],z[k]);};

  /**
   * Gets the volume of the mesh.
   */
  virtual float getVolume() const { return fabs((x[numX-1]-x[0])*(y[numY-1]-y[0])*(z[numZ-1]-z[0])); }


  /**
   * Set new node coordinates without modifying the mesh topology.
   * For performance reasons, this method should be called instead of setGeometry when doing
   * a mesh deformation animation. It allows to update the coordinates of a existing level surface,
   * skin, cross section etc, without rebuilding them totally.
   */
  void setCoordinates(const float *xnod, const float *ynod, const float *znod);

  /**
   * Get the current coordinates of the nodes of this mesh.
   * @param num_x : size of the array xnod
   * @param num_y : size of the array ynod
   * @param num_z : size of the array znod
   */
  void getCoordinates(const float* &xnod, const float* &ynod, const float* &znod, 
                      int &num_x, int &num_y, int &num_z) const {
    xnod = x; num_x = numX;
    ynod = y; num_y = numY;
    znod = z; num_z = numZ;
  }

 PoINTERNAL public:

  // get the length of the longest edge of the mesh
  float getLongestEdgeLength();

  void meshCrossSection(PoMeshCrossSection *cross_section) const; 
  void meshCrossContour(PoMeshCrossContour *cross_contour) const ; 
  void meshSkeleton(PoMeshSkeleton *skeleton, const float *nod_values, 
                    float *x_cont, float *y_cont,float *z_cont) const; 
  void mesh3DVec(PoMesh3DVec *mesh_vec) const ;
  SbBool isCrossSectionOptimal() const { return TRUE; }

  void print(FILE *fp) const;
  void printInfo() const {print(stdout);};

  // get a cell, but this cell has'nt coordinate specified
  virtual const PbCell *getTopoCell(int cell_index) const;

 protected:
  void updateCellBoundingBox() const;
  void setXYZGeometry(int num_x, int num_y, int num_z, const float *xa, const float *ya, const float *za);
  void getXYZGeometry(const float* &xa, const float* &ya, const float* &za) const;
  virtual void grid3DSkin(PoMeshSkin *_PoMeshSkin) const;

 private:
  float *x, *y, *z;

  void updateBoundingBox() const;
  void copy(const PbParalCartesianGrid3D &mesh) ;
  void destroy();

  mutable PbVoxelCell *m_voxel;
} ;

/*---------------------------------------------------------------------------*/

#endif /* _PB_PARALCARTESIANGRID3D_ */







