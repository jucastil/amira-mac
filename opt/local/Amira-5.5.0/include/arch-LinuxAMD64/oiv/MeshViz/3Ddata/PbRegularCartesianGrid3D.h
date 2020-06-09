/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_REGULARCARTESIANGRID3D_
#define  _PB_REGULARCARTESIANGRID3D_

#include <MeshViz/3Ddata/PbGrid3D.h>

class PbVoxelCell;
/**
 * @DTEXT  Defines a regular cartesian grid volume mesh.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *    Class to define a volume mesh represented by a grid, with cartesian 
 *    coordinates, of which the lines are parallel to X-axis, Y-axis or Z-axis.
 *    This mesh is said regular because the gap between 2 consecutive parallel  
 *    lines is constant.
 * 
 *    The geometry of such a mesh is defined by the 3 dimensions of its grid
 *    (num_x, num_y, num_z), and by its bounding box (x_min, y_min, z_min, 
 *    x_max, y_max, z_max)
 *    
 *    The values on the mesh nodes are defined by the 
 *    PbMesh::addValuesSet(set_index, val) method, where val argument is an 
 *    array of num_x * num_y * num_z floats.
 * 
 */
class MESHVIZ_API PbRegularCartesianGrid3D : public PbGrid3D {

 public:

  /**
   * Constructor of a default simple mesh. See also PbMesh for more explanations about data duplication.
   */
  PbRegularCartesianGrid3D(SbBool isDataDuplicate=TRUE);

  /**
   * Copy constructor
   */
  PbRegularCartesianGrid3D(const PbRegularCartesianGrid3D &mesh);

  /**
   * Constructor of a 3D regular grid mesh. See also PbMesh for 
   * more explanations about data duplication.
   */
  PbRegularCartesianGrid3D(int num_x, int num_y, int num_z, 
                           float x_min, float y_min, float z_min, 
                           float x_max, float y_max, float z_max, 
                           SbBool isDataDuplicate = TRUE);

  /**
   * Destructor.
   */
  ~PbRegularCartesianGrid3D();

  /**
   * Assignment operator.
   */
  PbRegularCartesianGrid3D& operator=(const PbRegularCartesianGrid3D &mesh);

  /**
   * Equality comparison operator.
   */
  MESHVIZ_API friend int operator ==(const PbRegularCartesianGrid3D &m1, 
                         const PbRegularCartesianGrid3D &m2);

  /**
   * Inequality comparison operator.
   */
  MESHVIZ_API friend int operator !=(const PbRegularCartesianGrid3D &m1, 
                         const PbRegularCartesianGrid3D &m2)
  { return !(m1 == m2); }

  /**
   * Defines a new geometry
   */
  void setGeometry(int num_x, int num_y, int num_z, 
                   float x_min, float y_min, float z_min, 
                   float x_max, float y_max, float z_max);

  /**
   * Gets the mesh geometry. 
   */
  void getGeometry(int &num_x, int &num_y, int &num_z, 
                   float &x_min, float &y_min, float &z_min, 
                   float &x_max, float &y_max, float &z_max) const;

  virtual const PbCell* findContainingCell(const SbVec3f &point, 
                                           float tolerance, 
                                           SbVec3f &pcoord, 
                                           const PbCell *adjacent_cell) const;

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
   * If the cell exists, it returns a PbVoxelCell.
   */
  virtual const PbCell* findContainingCell(const SbVec3f &point, 
                                           float tolerance, 
                                           SbVec3f &pcoord) const;

  /**
   * Gets the cell which index is cell_index. Returns NULL if the cell does not exist, 
   * otherwise returns always a PbVoxelCell object. 
   * Attention! This method returns always the same address of an internal private cell.
   * This private cell is updated each time getCell is called.
   */
  virtual const PbCell *getCell(int cell_index) const;

  /**
   * Gets the coordinates of a node defined by its index.
   */
  virtual SbVec3f getNodeCoord(int nod_index) const;

  /**
   * Gets the coordinates of a node defined by its i, j, k indices on the grid.
   */
  virtual SbVec3f getNodeCoord(int i, int j, int k) const
    { return SbVec3f(m_xmin+i*m_dx, m_ymin+j*m_dy, m_zmin+k*m_dz); };

  /**
   * Gets the volume of the mesh.
   */
  virtual float getVolume() const
    { return fabs((m_xmax-m_xmin)*(m_ymax-m_ymin)*(m_zmax-m_zmin)); }

  /**
   * Set new node coordinates without modifying the mesh topology.
   * For performance reasons, this method should be called instead of setGeometry when doing
   * a mesh deformation animation. It allows to update the coordinates of a existing level surface,
   * skin, cross section etc, without rebuilding them totally.
   * @param xnod array of 2 floats, min and max x coord
   * @param ynod array of 2 floats, min and max y coord
   * @param znod array of 2 floats, min and max z coord
   */
  void setCoordinates(const float *xnod, const float *ynod, const float *znod);

  /**
   * Get the current coordinates of the nodes of this mesh.
   * @param xnod array of 2 floats, min and max x coord
   * @param ynod array of 2 floats, min and max y coord
   * @param znod array of 2 floats, min and max z coord
   * @param size_xnod : size of the array xnod = 2
   * @param size_ynod : size of the array ynod = 2
   * @param size_znod : size of the array znod = 2
   */
  void getCoordinates(const float* &xnod, const float* &ynod, const float* &znod,
                      int &size_xnod, int &size_ynod, int &size_znod) const {
    xnod = m_x;
    ynod = m_y;
    znod = m_z;
    size_xnod = size_ynod = size_znod = 2;
  }

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  void setBounds(float x_min, float y_min, float z_min, 
                 float x_max, float y_max, float z_max);

  float getLongestEdgeLength();
  // get the length of the longest edge of the mesh

  void meshCrossSection(PoMeshCrossSection *cross_section) const; 
  void meshCrossContour(PoMeshCrossContour *cross_contour) const; 
  void meshSkeleton(PoMeshSkeleton *skeleton, 
                    const float *nod_values, 
                    float *x_cont,
                    float *y_cont, 
                    float *z_cont) const; 
  void mesh3DVec(PoMesh3DVec *mesh_vec) const;
  SbBool isCrossSectionOptimal() const { return TRUE; }

  void print(FILE *fp) const;
  void printInfo() const {print(stdout);};

  // get a cell, but this cell has'nt coordinate specified
  virtual const PbCell *getTopoCell(int cell_index) const;

 protected:
  void constructXYGeometry(float x_min, float y_min, 
                           float x_max, float y_max, 
                           SbBool is_data_duplicate);
  void setXYZGeometry(int num_x, int num_y, int num_z, 
                      const float *x, const float *y, const float *z);
  void getXYZGeometry(const float* &x, const float* &y, const float* &z) const;
  virtual void grid3DSkin(PoMeshSkin *_PoMeshSkin) const;

 private:
  float m_x[2], m_y[2], m_z[2];
  float m_xmin, m_xmax, m_dx;
  float m_ymin, m_ymax, m_dy;
  float m_zmin, m_zmax, m_dz;

  void updateBoundingBox() const;
  void copy(const PbRegularCartesianGrid3D &mesh);
  void destroy();

  mutable PbVoxelCell *m_voxel;
};

/*---------------------------------------------------------------------------*/

inline void
PbRegularCartesianGrid3D::getGeometry(int &num_x, int &num_y, int &num_z, 
                                      float &x_min, float &y_min, float &z_min, 
                                      float &x_max, float &y_max, float &z_max) const
{
  num_x = numX; x_min = m_xmin; x_max = m_xmax;
  num_y = numY; y_min = m_ymin; y_max = m_ymax;
  num_z = numZ; z_min = m_zmin; z_max = m_zmax;
}

#endif /* _PB_REGULARCARTESIANGRID3D_ */







