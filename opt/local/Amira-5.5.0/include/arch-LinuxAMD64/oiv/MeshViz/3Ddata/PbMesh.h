/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_MESH_
#define  _PB_MESH_

#include <Inventor/SbBox.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h>
#include <Inventor/STL/set>

#include <MeshViz/nodes/PoMeshProperty.h>
#include <MeshViz/graph/PbBase.h>
#include <MeshViz/misc/PbArrayOfInt.h>

class PbCell;
template <class _T> class PiSetOfDataSet;


/**
 * @DTEXT  Defines an abstract mesh.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *    A mesh is a set of nodes linked by edges.
 *    A mesh can be a surface mesh (see PbMesh2D) or a volume mesh (see PbMesh3D). 
 *    A surface mesh can be either 2D (its nodes have 2 coordinates) or 3D (its 
 *    nodes have 3 coordinates). Each node is referred by an index named node_index.
 * 
 *    A mesh is composed of a list of cells. A cell is a "simple" basic volume or
 *    surface element that connects adjacent nodes of the mesh. Surface meshes can 
 *    be defined by triangles, quadrangles and polygonal cells. Volume meshes
 *    can be defined by tetrahedrons, hexahedrons, prisms, or pyramid cells. A cell
 *    is defined by the list of node index that it connects. Each cell is referred 
 *    by an index named cell_index.
 *   
 *    A list of value-set can be defined. A value is a scalar (float), string, or
 *    a vector. Each value is located on mesh node, so the number of values 
 *    in a set must be equal to the number of mesh's nodes. 
 *    Each set of values can be named by a string.
 *    If the last argument
 *    is_data_duplicate of a constructor of a derived class is FALSE, the 
 *    values set are not copied by the object. In this case, the method addValuesSet,
 *    addStringsSet and addVecsSet save only the adress of the user data set and it 
 *    user's responsibility to check the validity of data during the existence of the 
 *    mesh object.
 * 
 *    A scalar value set is used to color the representations of the mesh.
 *    A string value set is used by some charting representations.
 *    A vector value set is used to make "hedgehog" vector field representations, 
 *    or streamline representations. Each data-set is referred by an index named 
 *    set_index. This index is used by classes of mesh representation to indicate
 *    which value set must be used for coloring. (see PoMesh::valuesIndex and  
 *    PoMesh::vecsIndex). Mapping a scalar value onto a color is done by PbDataMapping 
 *    or PoDataMapping classes (and derived).
 * 
 */
class MESHVIZ_API PbMesh : public PbBase {


 public:

  /**
   * Data binding. Specifies how data is specified (i.e., per cell or per node)
   * for a data set.
   * 
   */
  enum DataBinding {
    /** The data set contains one data value per cell. */
    PER_CELL = PoMeshProperty::PER_CELL,
    /** The data set contains one data value per node. */
    PER_NODE = PoMeshProperty::PER_NODE
  };


  /**
   * Constructor
   */
  PbMesh(SbBool is_data_duplicated=TRUE) ;

  /**
   * Copy constructor.
   */
  PbMesh(const PbMesh &mesh);

  /**
   * Destructor.
   */
  ~PbMesh() ;

  /**
   * Assignment operator.
   */
  PbMesh& operator=(const PbMesh &mesh) ;

  /**
   * Gets the number of mesh's nodes.
   */
  int getNumNodes() const;

  /**
   * Gets the number of mesh's cells.
   */
  int getNumCells() const;

  /**
   * Gets the coordinates of a node.
   */
  virtual SbVec3f getNodeCoord(int nod_index) const=0;

  /**
   * Gets the bounding box of the mesh.
   */
  SbBox3f getBoundingBox() const;

  /**
   * Returns TRUE if mesh's data are duplicated, FALSE otherwise.
   * If the data are not duplicated, the method addValuesSet, addStringsSet,
   * addVecsSet save only the adress of the user data set. In this
   * case, it user's responsibility to check the validity of data
   * during the existence of the PbMesh object.
   */
  SbBool isDataDuplicated() const { return isDataDuplicate; }

  /**
   * Adds a set of scalar values. The values are located at nodes so the number 
   * of values in a set must be equal to the number of nodes in the mesh.
   * @param set_index the index of the new set added.
   * @param val the array of values. Its size must be the number of nodes.
   * @param set_name string associated with this set of values.
   * 
   * NOTE: This method must be called after a setGeometry method because the size
   * of the argument @I val@i is determined by the number of nodes in the mesh. The setGeometry
   * methods are defined in subclasses of PbMesh.
   */
  virtual void addValuesSet(int set_index, const float *val, const SbString &set_name = "");

  /**
   * Adds a set of scalar values that can be located either at nodes or at cells.
   * Warning: At this time, the PER_CELL data binding is taken into account only by
   * the following classes:
   *   - PoMeshLevelSurf (just for coloring, the level surface of value per cell 
   *                    is not taken into account)
   *   - PoMeshSkin
   *   - PoMeshCrossSection @BR
   * 
   * The other classes use inherited coloring mode when the PER_CELL binding is used. 
   * 
   * @param set_index the index of the new set added.
   * @param val the array of values. Its size must be either the number of nodes
   *            or the number of cells depending on the binding argument.
   * @param binding specifies the location of the values. 
   * @param set_name string associated with this set of values.
   *
   * NOTE: This method must be called after a setGeometry method because the size
   * of the argument @I val@i is determined by the number of nodes in the mesh. The setGeometry
   * methods are defined in subclasses of PbMesh.
   */
  void addValuesSet(int set_index, const float *val, DataBinding binding, const SbString &set_name = "");

  /**
   * Gets the binding of the scalar value set.
   * @param set_index the index of the set of scalar values.
   * @return PER_CELL or PER_NODE, or undefined binding if specified data set
   * does not exist.
   */
  DataBinding getValuesBinding(int set_index) const;

  /**
   * Adds a set of string values . The number of string in a set 
   * must be equal to the number of nodes in the mesh.
   * The set can be optionally named (set_name parameter).
   * [OIV-WRAPPER-ARG IN,ARRAY,IN]
   */
  virtual void addStringsSet(int set_index, const SbString *val, const SbString &set_name = "");

  /**
   * Adds a set of vector values . The number of values in a set 
   * must be equal to the number of nodes in the mesh.
   * The set can be optionally named (set_name parameter).
   * [OIV-WRAPPER-ARG IN,ARRAY,IN]
   */
  virtual void addVecsSet(int set_index, const SbVec3f *val, const SbString &set_name = "");

  /**
   * Gets the name associated to a scalar values set.
   * NULL is returned if the set does not exist.
   * [OIV-WRAPPER-RETURN-TYPE VALUE]
   */
  virtual const SbString* getValuesSetName(int set_index) const ;

  /**
   * Gets the name associated to a string values set.
   * NULL is returned if the set does not exist.
   * [OIV-WRAPPER-RETURN-TYPE VALUE]
   */
  virtual const SbString* getStringsSetName(int set_index) const ;

  /**
   * Gets the name associated to a vec values set.
   * NULL is returned if the set does not exist.
   * [OIV-WRAPPER-RETURN-TYPE VALUE]
   */
  virtual const SbString* getVecsSetName(int set_index) const ;

  /**
   * Gets a set of scalar values.
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{GetValuesBinding(set_index) == DataBindings::PER_CELL? GetNumCells(): GetNumNodes()}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE ARRAY{nativeObject->getValuesBinding(set_index) == ::PbMesh::PER_CELL? nativeObject->getNumCells(): nativeObject->getNumNodes()}]
   */
  virtual const float* getValuesSet(int set_index) const;

  /**
   * Gets a set of string values.
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{GetNumNodes()}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE ARRAY{getNumNodes()}]
   */
  virtual const SbString* getStringsSet(int set_index) const;

  /**
   * Gets a set of vector values.
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{GetNumNodes()}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE ARRAY{getNumNodes()}]
   */
  virtual const SbVec3f* getVecsSet(int set_index) const;

  /**
   * Remove a set of scalar values.
   * @return FALSE if the scalar set does not exist, 
   * @return TRUE otherwise.
   */
  virtual SbBool removeValuesSet(int set_index);

  /**
   * Remove a set of string values
   * @return FALSE if the scalar set does not exist, 
   * @return TRUE otherwise.
   */
  virtual SbBool removeStringsSet(int set_index);

  /**
   * Remove a set of vector values
   * @return FALSE if the vector set does not exist, 
   * @return TRUE otherwise.
   */
  virtual SbBool removeVecsSet(int set_index);

  /**
   * Remove all sets of scalar values.
   */
  virtual void removeAllValuesSet();

  /**
   * Remove all sets of strings values.
   */
  virtual void removeAllStringsSet();

  /**
   * Remove all sets of vector values.
   */
  virtual void removeAllVecsSet();

  /**
   * Gets the number of set of scalar values.
   */
  virtual int getNumValuesSet() const;

  /**
   * Gets the number of set of string values.
   */
  virtual int getNumStringsSet() const;

  /**
   * Gets the number of set of vector values.
   */
  virtual int getNumVecsSet() const;

  /**
   * Gets the min of a set of scalars
   * @return FALSE if the scalar set does not exist, 
   * @return TRUE otherwise.
   * [OIVJAVA-WRAPPER-RETURN-TYPE SUCCESS_FLAG{throw new IllegalArgumentException()}]
   */
  virtual SbBool getMinValuesSet(int set_index, float &min) const;

  /**
   * Gets the min module of a set of vectors
   * @return FALSE if the vector set does not exist, 
   * @return TRUE otherwise.
   * [OIVJAVA-WRAPPER-RETURN-TYPE SUCCESS_FLAG{throw new IllegalArgumentException()}]
   */
  virtual SbBool getMinVecsSet(int set_index, float &min) const;

  /**
   * Gets the max of a set of scalars
   * @return FALSE if the scalar set does not exist, 
   * @return TRUE otherwise.
   * [OIVJAVA-WRAPPER-RETURN-TYPE SUCCESS_FLAG{throw new IllegalArgumentException()}]
   */
  virtual SbBool getMaxValuesSet(int set_index, float &max) const;

  /**
   * Gets the max module of a set of vectors
   * @return FALSE if the vector set does not exist, 
   * @return TRUE otherwise.
   * [OIVJAVA-WRAPPER-RETURN-TYPE SUCCESS_FLAG{throw new IllegalArgumentException()}]
   */
  virtual SbBool getMaxVecsSet(int set_index, float &max) const;

  /**
   * Gets the list of index of cells that own the node "nod_index".
   */
  virtual void getNodeOwnerCellsInd(int nod_index, PbArrayOfInt &owner_cells) const=0;

  /**
   * Gets the list of index of cells that own the list of nodes "nod_indices". "nod_indices" 
   * can be the list of indices of a facet, an edge...For example, if "nod_indices" contains 
   * the 2 indices of the edge's nodes, getNodesOwnerCellsInd returns the list of cell's 
   * that own this edge.
   */
  virtual void getNodesOwnerCellsInd(const PbArrayOfInt &nod_indices, PbArrayOfInt &owner_cells) const;

  /**
   * Gets the list of index of cells that are adjacent (by a node) to cell_index.
   * Two cells are adjacent by a node is they own at least one mesh's node in common.
   */
  virtual void getAdjacentCellsIndByNode(int cell_index, PbArrayOfInt &adjacent_cells) const;

  /**
   * Gets the list of index of cells that are adjacent (by a facet) to cell_index.
   * Two cells are adjacent by a facet is they own at least one mesh's facet in common  
   */
  virtual void getAdjacentCellsIndByFacet(int cell_index, PbArrayOfInt &adjacent_cells) const;

  /**
   * Gets the cell which index is cell_index. Returns NULL if the cell does not exist.
   * Attention! this method returns always the same adress of an internal private cell.
   * This private cell is updated each time getCell is called.
   */
  virtual const PbCell *getCell(int cell_index) const=0;

  /**
   * Gets the smallest cell's bounding box, returns also the index of this cell
   * [OIVJAVA-WRAPPER PACK{CellBox}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE NAME{bbox}]
   */
  virtual SbBox3f getSmallestCellBox(int &cell_index) const;

  /**
   * Gets the biggest cell's bounding box, returns also the index of this cell
   * [OIVJAVA-WRAPPER PACK{CellBox}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE NAME{bbox}]
   */
  virtual SbBox3f getBiggestCellBox(int &cell_index) const;

  /**
   * Gets the volume of the mesh. Returns always 0 for a surface mesh
   */
  virtual float getVolume() const=0;

  /**
   * Gets the area of the mesh. Returns always 0 for a volume mesh
   */
  virtual float getArea() const=0;

  /**
   * [OIVJAVA-WRAPPER PACK{ContainingCell}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE NAME{cell}]
   */
  virtual const PbCell* findContainingCell(const SbVec3f &point, float tolerance, SbVec3f &pcoord, const PbCell *adjacent_cell) const;

  /**
   * Find the mesh's cell that contains the point. If the (optianal) adjacent cell is given,
   * searching the containing cell starts by the cells around this adjacent one. Returns 
   * also the parametric coordinates of the point in the found cell. Parametric coordinates 
   * are the coordinates of the point relative to a topological equivalent unit cell. A point
   * is inside a cell if its parametric coordinates range from 0 to 1. However we use a test with
   * a tolerance value : a point is inside the cell if its parametric coordinates p verify
   * -tolerance <= p <= 1+tolerance. Parametric coordinates are useful to interpolate the
   * value in the cell (see PbCell::getValue).
   * Attention! This method returns always the same address of an internal private cell.
   * This private cell is updated each time findContainingCell is called.
   * [OIVJAVA-WRAPPER PACK{ContainingCell}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE NAME{cell}]
   */
  virtual const PbCell* findContainingCell(const SbVec3f &point, float tolerance, SbVec3f &pcoord) const;

  /**
   * Set new node coordinates without modifying the mesh topology.
   * For performance reasons, this method should be called instead of setGeometry when doing
   * a mesh deformation animation. 
   */
  virtual void setCoordinates(const float *x_nod, const float *y_nod, const float *z_nod);

  /**
   * Get the current coordinates of the nodes of this mesh.
   * @param size_xnod : size of the array xnod
   * @param size_ynod : size of the array ynod
   * @param size_znod : size of the array znod
   * [OIV-WRAPPER-ARG ARRAY{size_xnod},ARRAY{size_ynod},ARRAY{size_znod},NO_WRAP,NO_WRAP,NO_WRAP]
   * [OIVJAVA-WRAPPER PACK{CoordinatesInfo}]
   */
  virtual void getCoordinates(const float* &xnod, const float* &ynod, const float* &znod,
                              int &size_xnod, int &size_ynod, int &size_znod) const;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  // internal use it only for Amira. PER_CELL binding for vec set is never taken into account in 
  // MeshViz representation
  void addVecsSet(int set_index, const SbVec3f *val, DataBinding binding, const SbString &set_name = "");
  DataBinding getVecsBinding(int set_index) const;

  // Gets the length of the longest edge of the mesh
  virtual float getLongestEdgeLength();
  virtual void print(FILE *fp) const;
  void printInfo() const {print(stdout);};
  virtual SbBool isEmpty() const;

  virtual const PbCell *getTopoCell(int cell_index) const;

  uint32_t getGeometryId() const { return m_geometryId; }
  uint32_t getTopologyId() const { return m_topologyId; }
  uint32_t getFltDataSetId(int index) const;
  uint32_t getVecDataSetId(int index) const;
  uint32_t getStrDataSetId(int index) const;

  /*----------------------------------------------------------------------------*/
 protected:
  virtual void updateBoundingBox()const=0;
  virtual void updateCellBoundingBox() const;
  virtual const PbCell* findContainingCellProtected(const SbVec3f &point, float tolerance, SbVec3f &pcoord, PbArrayOfInt &test_cell) const=0;
  
  void updateGeometryId();
  void updateTopologyId();
  void updateFltDataId(uint32_t &id);
  void updateVecDataId(uint32_t &id);
  void updateStrDataId(uint32_t &id);

  SbBool isDataDuplicate;
  int     numMeshNodes;
  int     m_numMeshCells;
  

  SbBool m_longestEdgeLengthIsUpdated;
  float  m_longestEdgeLength;

  mutable SbBox3f m_meshBoundingBox;

  PiSetOfDataSet<float> *m_meshValuesSet;
  PiSetOfDataSet<SbString> *m_meshStringsSet;
  PiSetOfDataSet<SbVec3f> *m_meshVecsSet;

  mutable SbBool  m_meshBoundingBoxIsUpdated;
  mutable SbBool  m_cellBoundingBoxIsUpdated;
  mutable SbBox3f m_smallestCellBoundingBox;
  mutable SbBox3f m_biggestCellBoundingBox;
  mutable int     m_smallestCellInd;
  mutable int     m_biggestCellInd;

  /*----------------------------------------------------------------------------*/
 private:
  // State of the mesh
  uint32_t m_geometryId;  // defines the state of this mesh geometry
  uint32_t m_topologyId;  // defines the state of this mesh topology

  // static state id level
  static  uint32_t sm_nextGeometryId;
  static  uint32_t sm_nextTopologyId;
  static  uint32_t sm_nextFltDataId;
  static  uint32_t sm_nextVecDataId;
  static  uint32_t sm_nextStrDataId;

  mutable PbArrayOfInt m_CellsAlreadyTested;

  void copy(const PbMesh &mesh) ;
  void destroy();
};

/*---------------------------------------------------------------------------*/

inline int 
PbMesh::getNumNodes() const
{ return numMeshNodes; }

inline int 
PbMesh::getNumCells() const
{ return m_numMeshCells; }

inline SbBox3f
PbMesh::getBoundingBox() const 
{ 
  updateBoundingBox();
  return m_meshBoundingBox;
}

inline void
PbMesh::setCoordinates(const float *, const float *, const float *)
{}

inline void
PbMesh::getCoordinates(const float* &, const float* &, const float* &, int &, int &, int &) const
{}

inline const PbCell *
PbMesh::getTopoCell(int) const
{ return NULL; }


#endif /* _PB_MESH_ */







