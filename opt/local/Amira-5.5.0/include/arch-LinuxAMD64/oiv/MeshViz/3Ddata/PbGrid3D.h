/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_GRID3D_
#define  _PB_GRID3D_

#include <MeshViz/3Ddata/PbMesh3D.h>

/**
 * @DTEXT  Defines an abstract grid volume mesh.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *   This class defines a mesh of which topology is a regular grid made of num_x 
 *   * num_y * num_z nodes. Each node with index (i,j,k) in the mesh (except for 
 *   points along the  mesh border) is connected to six points with indices 
 *   (i+1,j,k), (i,j+1,k), (i-1,j,k), (i,j-1,k), (i,j,k-1), (i,j,k+1). 
 *  
 *   The values on the mesh nodes are defined by the PbMesh::addValuesSet() method, 
 *   where argument val is an array of num_x * num_y * num_z floats. 
 * 
 */
class MESHVIZ_API PbGrid3D : public PbMesh3D {


 public:

  /**
   * Constructor. See also PbMesh for more explanations about data duplication.
   */
  PbGrid3D(SbBool is_data_duplicate=TRUE) : PbMesh3D(is_data_duplicate) {};

  /**
   * Copy constructor.
   */
  PbGrid3D(const PbGrid3D &mesh);

  /**
   * Destructor.
   */
  ~PbGrid3D();

  /**
   * Assignment operator.
   */
  PbGrid3D& operator=(const PbGrid3D &mesh) ;

  /**
   * Defines a volume mesh geometry. The size of the x array depends on 
   * the derived class that calls this method. It is either num_x or
   * num_x * num_y * num_z. Idem for y and z array.
   */
  void setGeometry(int num_x, int num_y, int num_z, const float *x, const float *y, const float *z);

  /**
   * Gets the mesh geometry.
   * [OIV-WRAPPER-ARG NO_WRAP,NO_WRAP,NO_WRAP,ARRAY{num_x},ARRAY{num_y},ARRAY{num_z}]
   */
  void getGeometry(int &num_x, int &num_y, int &num_z, const float* &x, const float* &y, const float* &z) const;

  /**
   * Gets the coordinates of a node defined by its index.
   */
  virtual SbVec3f getNodeCoord(int nod_index) const=0;

  /**
   * Gets the coordinates of a node defined by its i,j,k indices on the grid.
   */
  virtual SbVec3f getNodeCoord(int i, int j, int k) const=0;

  /**
   * Gets the dimensions num_x, num_y, num_z of the grid.
   */
  void getDim(int &num_x, int &num_y, int &num_z) const { num_x = numX; num_y = numY; num_z = numZ;};

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
   * Gets the list of index of cells that are adjacent (by a facet) to cell_index.
   * Two cells are adjacent by facet is they own at least one mesh's facet in common  
   */
  virtual void getAdjacentCellsIndByFacet(int cell_index, PbArrayOfInt &adjacent_cells) const;

  /**
   * Calculates indices i,j,k that verify    (i*num_y + j)*num_z + k 
   */
  void  getNodeIndices(int nod_index, int &i, int &j, int &k) const;

  /**
   * Calculates indices i,j,k that verify    cell_index = (i*(num_y-1) + j)*(num_z-1) + k 
   */
  void  getCellIndices(int cell_index, int &i, int &j, int &k) const;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  void meshSkin(PoMeshSkin *_PoMeshSkin) const;

  virtual int evaluateSkinFacesNum() const { 
    return 2*((numZ-1)*(numY-1) + (numZ-1)*(numX-1) + (numX-1)*(numY-1));
  }

  int * getCellNodeIds(int i, int j, int k) const;
  int * getCellNodeIds(int cell_index) const;

  void print(FILE *fp) const;
  void printInfo() const {print(stdout);};

 protected:
  virtual void grid3DSkin(PoMeshSkin *_PoMeshSkin) const = 0;

  PbGrid3D(int num_x, int num_y, int num_z, SbBool isDataDuplicate=TRUE) ;
  void setDim(int num_x, int num_y, int num_z);
  virtual void setXYZGeometry(int num_x, int num_y, int num_z, const float *x, const float *y, const float *z)=0;
  virtual void getXYZGeometry(const float* &x, const float* &y, const float* &z) const=0;
  int   numX,numY,numZ;

  // node ids of the mutable private cell
  // each time the getCell or getTopoCell is called, m_cellNodeIds is updated
  mutable int m_cellNodeIds[8]; 

 private:
  void copy(const PbGrid3D &mesh) ;
  void destroy();
} ;

/*---------------------------------------------------------------------------*/

// calculate indices i,j,k that verify    nod_index = (i*numY + j)*numZ + k 
inline void
PbGrid3D::getNodeIndices(int nod_index, int &i, int &j, int &k) const
{
  int tmp;
  k = nod_index % numZ;   
  tmp = (nod_index-k) / numZ;           // tmp = i*numY + j
  j = tmp % numY;
  i = (tmp-j) / numY;
}

// calculate indices i,j,k that verify    cell_index = (i*(numY-1) + j)*(numZ-1) + k 
inline void
PbGrid3D::getCellIndices(int cell_index, int &i, int &j, int &k) const
{
  register int ny=numY-1, nz=numZ-1;
  int tmp;
  k = cell_index % nz;   
  tmp = (cell_index-k) / nz;           // tmp = i*ny + j
  j = tmp % ny;
  i = (tmp-j) / ny;
}

// set dimensions of the grid
inline void
PbGrid3D::setDim(int num_x, int num_y, int num_z)
{
  numX = num_x;
  numY = num_y;
  numZ = num_z;
  numMeshNodes = numX * numY * numZ;
  m_numMeshCells = (numX-1) * (numY-1) * (numZ-1);
  updateTopologyId();
}

inline int * 
PbGrid3D::getCellNodeIds(int cell_index) const
{
  int i, j, k;
  getCellIndices(cell_index, i, j, k);
  return getCellNodeIds(i,j,k);
}

#define NSI_(i,j,k)  numZ*((j)+(i)*numY) + (k)
inline int * 
PbGrid3D::getCellNodeIds(int i, int j, int k) const
{
  m_cellNodeIds[4] = (m_cellNodeIds[0] = NSI_(i  ,j  ,k  )) + 1;
  m_cellNodeIds[5] = (m_cellNodeIds[1] = NSI_(i+1,j  ,k  )) + 1;
  m_cellNodeIds[6] = (m_cellNodeIds[2] = NSI_(i+1,j+1,k  )) + 1;
  m_cellNodeIds[7] = (m_cellNodeIds[3] = NSI_(i  ,j+1,k  )) + 1;
  return m_cellNodeIds;
}

#endif /* _PB_GRID3D_ */







