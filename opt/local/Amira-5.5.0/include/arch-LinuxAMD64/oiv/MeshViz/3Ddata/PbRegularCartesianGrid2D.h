/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_REGULARCARTESIANGRID2D_
#define  _PB_REGULARCARTESIANGRID2D_

#include <MeshViz/3Ddata/PbGrid2D.h>

class PiContouring;
class PoMeshLines;
class PoMeshFilled;
class PoMeshSides;
class PbPixelCell;
class PbQuadrangleCell;

/**
 * @DTEXT  Defines a regular cartesian grid surface mesh.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *    Class to define a surface mesh represented by a grid, with cartesian 
 *    coordinates, of which the lines are parallel to X-axis or Y-axis. This
 *    mesh is said regular because the gap between 2 consecutive parallel lines 
 *    is constant.
 * 
 *    The geometry of such a mesh is defined by the 2 dimensions of its grid
 *    (num_x,num_y), by its bounding box (x_min,y_min,x_max,y_max) and for a 3D
 *    mesh by its z altitudes on each nodes. z is an array of num_x * num_y 
 *    floats. 
 *    
 *    The values on the mesh nodes are defined by the 
 *    PbMesh::addValuesSet(set_index,val) method, where val argument is an 
 *    array of num_x * num_y floats.
 * 
 */
class MESHVIZ_API PbRegularCartesianGrid2D : public PbGrid2D {


 public:

  /**
   * Constructor of a default simple mesh. See also PbMesh for more explanations about data duplication.
   */
  PbRegularCartesianGrid2D(SbBool isDataDuplicate=TRUE) ;

  /**
   * Copy constructor.
   */
  PbRegularCartesianGrid2D(const PbRegularCartesianGrid2D &mesh);

  /**
   * Constructor of a 2D regular grid mesh. See also PbMesh for 
   * more explanations about data duplication.
   */
  PbRegularCartesianGrid2D(int num_x,int num_y, float x_min,float y_min, float x_max,float y_max, SbBool isDataDuplicate=TRUE) ;

  /**
   * Constructor of a 3D regular grid mesh. See also PbMesh for 
   * more explanations about data duplication.
   */
  PbRegularCartesianGrid2D(int num_x,int num_y, float x_min,float y_min, float x_max,float y_max, const float *z, 
                           SbBool isDataDuplicate=TRUE) ;

  /**
   * Constructor of a regular grid mesh, by refining the given other_mesh.
   */
  PbRegularCartesianGrid2D(int num_x,int num_y, 
                           const PbRegularCartesianGrid2D &other_mesh);

  /**
   * Destructor.
   */
  ~PbRegularCartesianGrid2D() ;

  /**
   * Assignment operator.
   */
  PbRegularCartesianGrid2D& operator=(const PbRegularCartesianGrid2D &mesh) ;

  /**
   * Equality comparison operator.
   */
  MESHVIZ_API friend int operator ==(const PbRegularCartesianGrid2D &m1, const PbRegularCartesianGrid2D &m2);

  /**
   * Inequality comparison operator.
   */
  MESHVIZ_API friend int operator !=(const PbRegularCartesianGrid2D &m1, const PbRegularCartesianGrid2D &m2)
  { return !(m1 == m2); }

  /**
   * Defines a new 2D geometry
   */
  void setGeometry(int num_x,int num_y, float x_min,float y_min, float x_max,float y_max);

  /**
   * Defines a new 3D geometry
   */
  void setGeometry(int num_x,int num_y, float x_min,float y_min, float x_max,float y_max, const float *z);

  /**
   * Gets the mesh 2D geometry. 
   */
  void getGeometry(int &num_x,int &num_y, float &x_min,float &y_min, float &x_max,float &y_max) const;

  /**
   * Gets the mesh 3D geometry. Attention! For a 2D mesh, z is NULL.
   * [OIV-WRAPPER-ARG OUT,OUT,OUT,OUT,OUT,OUT,ARRAY{0}]
   */
  void getGeometry(int &num_x,int &num_y, float &x_min,float &y_min, float &x_max,float &y_max, const float *&z) const;

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
   * If the cell exists, it returns a PbPixelCell for a 2D mesh, or a PbQuadrangleCell for a 3D mesh.
   */
  virtual const PbCell* findContainingCell(const SbVec3f &point, float tolerance, SbVec3f &pcoord) const;

  /**
   * Gets the cell which index is cell_index. Returns NULL if the cell does not exist.
   * If the cell exists, it returns a PbPixelCell for a 2D mesh, or a PbQuadrangleCell for a 3D mesh.
   * Attention! This method returns always the same address of an internal private cell.
   * This private cell is updated each time getCell is called.
   */
  virtual const PbCell *getCell(int cell_index) const;

  /**
   * Gets the coordinates of a node defined by its index.
   */
  virtual SbVec3f getNodeCoord(int nod_index) const;

  /**
   * Gets the coordinates of a node defined by its i,j indices on the grid.
   */
  virtual SbVec3f getNodeCoord(int i, int j) const;

  /**
   * Gets the area of the mesh.
   */
  virtual float getArea() const;


 PoINTERNAL public:
  void meshLines(PoMeshLines *_PoMeshLines) const; 
  void meshFilled(PoMeshFilled *_PoMeshFilled) const; 
  void meshSides(PoMeshSides *_PoMeshSides) const; 
  void meshContouring(PiContouring *_PiContouring, const float *z) const;
  void mesh2DVec(PoMesh2DVec *mesh_vec) const ;
  void getLimits(PoMesh2D *_PoMesh2D, Ppoint_list_list3 &limit) const;

  void getNodesCoord(const float *z, SoMFVec3f &vertices) const;
  virtual SbBool hasSidesNormals() const;
  virtual void getSidesNormals(SbVec3f *&normals, 
                               const PbArrayOfInt &limitSizes) const;

  void print(FILE *fp) const;
  void printInfo() const {print(stdout);};

 protected:
  void constructXYGeometry(float x_min,float y_min, float x_max,float y_max, SbBool is_data_duplicate);
  void setXYGeometry(int numX, int numY, const float *x, const float *y);
  void getXYGeometry(const float* &x, const float* &y) const;

 private:
  float m_x[2], m_y[2];
  float m_xmin, m_xmax, m_dx;
  float m_ymin, m_ymax, m_dy;

  void updateBoundingBox() const;
  void copy(const PbRegularCartesianGrid2D &mesh) ;
  void destroy();

  mutable PbPixelCell      *m_pixel;
  mutable PbQuadrangleCell *m_quadrangle;
} ;

/*---------------------------------------------------------------------------*/

inline void
PbRegularCartesianGrid2D::getGeometry(int &num_x,int &num_y, float &x_min,float &y_min, float &x_max,float &y_max) const
{
  num_x = numX; x_min = m_xmin; x_max = m_xmax;
  num_y = numY; y_min = m_ymin; y_max = m_ymax;
}

inline void
PbRegularCartesianGrid2D::getGeometry(int &num_x,int &num_y, float &x_min,float &y_min, float &x_max,float &y_max, const float *&zn) const
{
  num_x = numX; x_min = m_xmin; x_max = m_xmax;
  num_y = numY; y_min = m_ymin; y_max = m_ymax;
  zn = m_zCoord;
}

#endif /* _PB_REGULARCARTESIANGRID2D_ */







