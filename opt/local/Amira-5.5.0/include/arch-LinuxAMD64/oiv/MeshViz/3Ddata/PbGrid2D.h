/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_GRID2D_
#define  _PB_GRID2D_

#include <MeshViz/3Ddata/PbMesh2D.h>
/**
 * @DTEXT  Defines an abstract grid surface mesh.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *   This class defines a mesh of which topology is a regular grid made of num_x
 *   * num_y nodes. Each node with index (i, j) in the mesh (except for points 
 *   along the  mesh border) is connected to four points with indices (i+1,j), 
 *   (i,j+1), (i-1,j), (i,j-1). 
 *  
 *   The values on the mesh nodes are defined by the PbMesh::addValuesSet() method, 
 *   where val argument is an array of num_x * num_y floats.
 * 
 */
class MESHVIZ_API PbGrid2D : public PbMesh2D {


 public:

  /**
   * Constructor. See also PbMesh for more explanations about data duplication.
   */
  PbGrid2D(SbBool is_data_duplicate=TRUE) : PbMesh2D(is_data_duplicate) {};

  /**
   * Copy constructor.
   */
  PbGrid2D(const PbGrid2D &mesh);

  /**
   * Destructor.
   */
  ~PbGrid2D();

  /**
   * Assignment operator.
   */
  PbGrid2D& operator=(const PbGrid2D &mesh) ;

  /**
   * Defines a 2D surface mesh geometry. The size of the x array depends on 
   * the derived class that calls this method. It is either num_x or
   * num_x * num_y. Idem for y array.
   */
  void setGeometry(int num_x, int num_y, const float *x, const float *y);

  /**
   * Defines a 3D surface mesh geometry. The size of the x array depends on 
   * the derived class that calls this method. It is either num_x or
   * num_x * num_y. Idem for y array. The size of z array is always 
   * num_x * num_y.
   */
  void setGeometry(int num_x, int num_y, const float *x, const float *y, const float *z);

  /**
   * Gets the mesh 2D geometry. 
   * [OIV-WRAPPER-ARG NO_WRAP,NO_WRAP,ARRAY{num_x},ARRAY{num_y}]
   */
  void getGeometry(int &num_x, int &num_y, const float* &x, const float* &y) const;

  /**
   * Gets the mesh 3D geometry.
   * [OIV-WRAPPER-ARG NO_WRAP,NO_WRAP,ARRAY{num_x},ARRAY{num_y},ARRAY{0}]
   */
  void getGeometry(int &num_x, int &num_y, const float* &x, const float* &y, const float* &z) const;

  /**
   * Gets the coordinates of a node defined by its index.
   */
  virtual SbVec3f getNodeCoord(int nod_index) const=0;

  /**
   * Gets the coordinates of a node defined by its i,j indices on the grid.
   */
  virtual SbVec3f getNodeCoord(int i, int j) const=0;

  /**
   * Gets the dimensions num_x, num_y of the grid.
   */
  void getDim(int &num_x, int &num_y) const { num_x = numX; num_y = numY;};

  /**
   * Gets the list of index of cells that own the node "nod_index".
   */
  virtual void getNodeOwnerCellsInd(int nod_index, PbArrayOfInt &owner_cells) const;

  /**
   * Gets the list of index of cells that are adjacent (by a node) to cell_index.
   * Two cells are adjacent by a node is they own at least one mesh's node in common.
   */
  virtual void getAdjacentCellsIndByNode(int cell_index, PbArrayOfInt &adjacent_cells) const;

  /**
   * Gets the list of index of cells that are adjacent (by an edge) to cell_index.
   * Two cells are adjacent by an edge is they own at least one mesh's edge in common  
   */
  virtual void getAdjacentCellsIndByFacet(int cell_index, PbArrayOfInt &adjacent_cells) const;

  /**
   * Calculates indices i,j that verify    nod_index = i*num_y + j
   */
  void  getNodeIndices(int nod_index, int &i, int &j) const;

  /**
   * Calculates indices i,j that verify    cell_index = i*(num_y-1) + j
   */
  void  getCellIndices(int cell_index, int &i, int &j) const;
 PoINTERNAL public:
  int * getCellNodeIds(int i, int j) const;
  int * getCellNodeIds(int cell_index) const;
  virtual SbVec3f getFirstCellNormal() const;

  void print(FILE *fp) const;
  void printInfo() const {print(stdout);};
  virtual void getLimitIndices(PbArrayOfInt &nodesIndex, PbArrayOfInt &limitSizes) const;

 protected:
  virtual void updateCellBoundingBox() const;
  PbGrid2D(int num_x, int num_y, SbBool isDataDuplicate=TRUE) ;
  PbGrid2D(int num_x, int num_y, const float *z, SbBool isDataDuplicate=TRUE) ;
  void setDim(int num_x, int num_y);
  virtual void setXYGeometry(int num_x, int num_y, const float *x, const float *y)=0;
  virtual void getXYGeometry(const float* &x, const float* &y) const=0;
  void setZCoordMatrix(int num_x, int num_y, const float *z);
  int   numX,numY;
  float **z;

  // node ids of the mutable private cell
  // each time the getCell or getTopoCell is called, m_cellNodeIds is updated
  mutable int m_cellNodeIds[4]; 

 private:

  void copy(const PbGrid2D &mesh) ;
  void destroy();
} ;

/*---------------------------------------------------------------------------*/

// calculate indices i,j that verify    nod_index = i*numY + j
inline void
PbGrid2D::getNodeIndices(int nod_index, int &i, int &j) const
{
  j = nod_index % numY;
  i = (nod_index-j) / numY;
}

// calculate indices i,j that verify    cell_index = i*(numY-1) + j
inline void
PbGrid2D::getCellIndices(int cell_index, int &i, int &j) const
{
  j = cell_index % (numY-1);
  i = (cell_index-j) / (numY-1);
}

// set dimensions of the grid
inline void
PbGrid2D::setDim(int num_x, int num_y)
{
  numX = num_x;
  numY = num_y;
  numMeshNodes = numX * numY;
  if (num_x > 1 && num_y > 1) 
    m_numMeshCells = (numX-1) * (numY-1);
  else
    // setDim can be used with (0,0) as argt !
    m_numMeshCells = 0;
}

inline int * 
PbGrid2D::getCellNodeIds(int cell_index) const
{
  int i, j;
  getCellIndices(cell_index, i, j);
  return getCellNodeIds(i,j);
}

inline int * 
PbGrid2D::getCellNodeIds(int i, int j) const
{
  m_cellNodeIds[0] = i*numY+j;
  m_cellNodeIds[1] = (i+1)*numY+j;
  m_cellNodeIds[2] = (i+1)*numY+j+1;
  m_cellNodeIds[3] = i*numY+j+1;
  return m_cellNodeIds;
}

#endif /* _PB_GRID2D_ */







