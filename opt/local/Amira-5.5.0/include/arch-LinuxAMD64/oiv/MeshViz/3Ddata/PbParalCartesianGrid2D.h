/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_PARALCARTESIANGRID2D_
#define  _PB_PARALCARTESIANGRID2D_

#include <MeshViz/3Ddata/PbCartesianGrid2D.h>

class PiContouring;
class PoMeshLines;
class PoMeshFilled;
class PoMeshSides;
class SbVec2f;
class PbPixelCell;
class PbQuadrangleCell;

/**
 * @DTEXT  Defines a parallel cartesian grid surface mesh.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *    Class to define a surface mesh represented by a grid, with cartesian coordinates, 
 *    of which the lines are parallel to X-axis or Y-axis. This mesh is defined 
 *    by num_y vertical lines and num_x horizontal lines. x is an array of num_x 
 *    floats, and y is an array of num_y floats.
 *    
 *    The values on the mesh nodes are defined by the 
 *    PbMesh::addValuesSet(set_index,val) method, where val argument is an 
 *    array of num_x * num_y floats.
 * 
 */
class MESHVIZ_API PbParalCartesianGrid2D : public PbCartesianGrid2D {


 public:

  /**
   * Constructor of a default simple mesh. See also PbMesh for more explanations about data duplication.
   */
  PbParalCartesianGrid2D(SbBool isDataDuplicate=TRUE) ;

  /**
   * Copy constructor.
   */
  PbParalCartesianGrid2D(const PbParalCartesianGrid2D &mesh);

  /**
   * Constructor of a 2D parallel grid mesh. See also PbMesh for 
   * more explanations about data duplication.
   */
  PbParalCartesianGrid2D(int num_x, int num_y, const float *x, const float *y, SbBool isDataDuplicate=TRUE) ;

  /**
   * Constructor of a 3D parallel grid mesh. See also PbMesh for 
   * more explanations about data duplication.
   */
  PbParalCartesianGrid2D(int num_x, int num_y, const float *x, const float *y, const float *z, SbBool isDataDuplicate=TRUE) ;

  /**
   * Destructor.
   */
  ~PbParalCartesianGrid2D() ;

  /**
   * Assignment operator.
   */
  PbParalCartesianGrid2D& operator=(const PbParalCartesianGrid2D &mesh) ;

  /**
   * Equality comparison operator.
   */
  MESHVIZ_API friend int operator ==(const PbParalCartesianGrid2D &m1, const PbParalCartesianGrid2D &m2);

  /**
   * Inequality comparison operator.
   */
  MESHVIZ_API friend int operator !=(const PbParalCartesianGrid2D &m1, const PbParalCartesianGrid2D &m2)
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
  void meshContouring(PiContouring *_PiContouring, const float *z) const;
  void mesh2DVec(PoMesh2DVec *mesh_vec) const ;

  void getNodesCoord(const float *z, SoMFVec3f &vertices) const;
  virtual SbBool hasSidesNormals() const;
  virtual void getSidesNormals(SbVec3f *&normals, 
                               const PbArrayOfInt &limitSizes) const;

  void print(FILE *fp) const;
  void printInfo() const {print(stdout);};

 protected:
  void constructXYGeometry(const float *xn, const float *yn, SbBool is_data_duplicate);
  void setXYGeometry(int num_x, int num_y, const float *x, const float *y);
  void getXYGeometry(const float* &x, const float* &y) const;

 private:
  float *x, *y;

  void updateBoundingBox() const;
  void copy(const PbParalCartesianGrid2D &mesh) ;
  void destroy();

  mutable PbPixelCell      *m_pixel;
  mutable PbQuadrangleCell *m_quadrangle;
} ;

/*---------------------------------------------------------------------------*/

#endif /* _PB_PARALCARTESIANGRID2D_ */







