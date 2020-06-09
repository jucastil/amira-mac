/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_POLARGRID2D_
#define  _PB_POLARGRID2D_

#include <MeshViz/3Ddata/PbGrid2D.h>
class PiContouring;


/**
 * @DTEXT  Defines a polar grid surface mesh.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *    Class to define a surface mesh represented by a grid with polar coordinates.
 *    This mesh is defined by a matrix num_r * num_t points forming (num_r - 1) *
 *    (num_t - 1) quadrangles. Each point with index (i, j) in the mesh (except 
 *    for points along the mesh border) is connected to four points with indices
 *    (i+1,j), (i,j+1), (i-1,j), (i,j-1). r is an array of num_r radius, t an 
 *    array of num_t angles, and z an array of num_r * num_t floats.
 * 
 *    The values on the mesh nodes are defined by the 
 *    PbMesh::addValuesSet(set_index,val) method, where val argument is an 
 *    array of num_r * num_t floats.
 * 
 */
class MESHVIZ_API PbPolarGrid2D : public PbGrid2D {


 public:

  /**
   * Constructor of a default simple mesh. See also PbMesh for more explanations about data duplication.
   */
  PbPolarGrid2D(SbBool isDataDuplicate=TRUE) ;

  /**
   * Copy constructor.
   */
  PbPolarGrid2D(const PbPolarGrid2D &mesh);

  /**
   * Constructor of a 2D surface mesh. See also PbMesh for 
   * more explanations about data duplication.
   */
  PbPolarGrid2D(int num_r, int num_t, const float *r, const float *t, SbBool isDataDuplicate=TRUE) ;

  /**
   * Constructor of a 3D surface mesh. See also PbMesh for 
   * more explanations about data duplication.
   */
  PbPolarGrid2D(int num_r, int num_t, const float *r, const float *t, const float *z, SbBool isDataDuplicate=TRUE) ;

  /**
   * Destructor.
   */
  ~PbPolarGrid2D() ;

  /**
   * Assignment operator.
   */
  PbPolarGrid2D& operator=(const PbPolarGrid2D &mesh) ;

  /**
   * Equality comparison operator.
   */
  MESHVIZ_API friend int operator ==(const PbPolarGrid2D &m1, const PbPolarGrid2D &m2);

  /**
   * Inequality comparison operator.
   */
  MESHVIZ_API friend int operator !=(const PbPolarGrid2D &m1, const PbPolarGrid2D &m2)
  { return !(m1 == m2); }

  /**
   * Returns always NULL.
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
  void constructXYGeometry(const float *rn, const float *tn, SbBool is_data_duplicate);
  void setXYGeometry(int num_r, int num_t, const float *x, const float *y);
  void getXYGeometry(const float* &x, const float* &y) const;

 private:
  float *r, *t;

  void updateBoundingBox() const;
  void copy(const PbPolarGrid2D &mesh) ;
  void destroy();
} ;

/*---------------------------------------------------------------------------*/

#endif /* _PB_POLARGRID2D_ */







