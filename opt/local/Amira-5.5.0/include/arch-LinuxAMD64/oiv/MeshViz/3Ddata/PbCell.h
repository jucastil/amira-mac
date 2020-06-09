/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_CELL_
#define  _PB_CELL_

#include <Inventor/SbBox.h>
#include <Inventor/SbLinear.h>
#include <MeshViz/graph/PbBase.h>
#include <MeshViz/misc/PbArrayOfInt.h>
#include <Inventor/STL/vector>

#ifdef __hpux
// hpux stl implementation does not support vector<bool> optimization
// or does not provide any allocator for this type.
// To avoid unresolved symbol, this optimized datatype can NOT be used. 
typedef std::vector<char> SbBoolVector;
#else
typedef std::vector<bool> SbBoolVector;
#endif

class PbArrayOfFloat;
class PoMesh3D;
class PiMarchingCase;

/**
 * @DTEXT  Defines an abstract cell of a mesh.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *    A cell is a "simple" basic volume or surface element that 
 *    connects adjacent nodes of a mesh.
 * 
 */
class MESHVIZ_API PbCell : public PbBase {


 public:

  /**
   * Constructor
   */
  PbCell() ;

  /**
   * Copy constructor
   */
  PbCell(const PbCell &cell);

  /**
   * Destructor
   */
  ~PbCell() ;

  /**
   * Assignment operator.
   */
  PbCell& operator=(const PbCell &cell) ;

  /**
   * Gets the length of the longest edge of the cell.
   */
  virtual float getLongestEdgeLength() const = 0;

  /**
   * Gets the cell's bounding box.
   */
  virtual SbBox3f getBoundingBox() const;

  /**
   * Gets the cell's bounds. Similar to getBoundingBox() but it does not
   * use any SbBox object.
   */
  virtual void getBounds(float &xmin,float &ymin, float &zmin, 
                         float &xmax,float &ymax, float &zmax) const;

  /**
   * Gets the cell's geometric center.
   */
  virtual SbVec3f getCenter() const;

  /**
   * Gets the volume of the cell. Returns always 0 for a 2D cell.
   */
  virtual float getVolume() const = 0;

  /**
   * Gets the area of a cell.
   */
  virtual float getArea() const = 0;

  /**
   * Gets the number of facets.
   */
  int getNumFacets() const { return m_numFaces;}; 

  /**
   * Gets the number of edges.
   */
  int getNumEdges() const { return m_numEdges;};  

  /**
   * Gets the number of nodes.
   */
  int getNumNodes() const { return m_numNodes;};  

  /**
   * Gets the index of the cell in the mesh.
   */
  int getIndex() const { return m_index;};        



  /**
   * Gets the coordinate of the nod (nod must be >=0 and < getNumNodes()).
   */
  SbVec3f getNodeCoord(int nod) const { return m_nodeCoord[nod]; };

  /**
   * Gets the index (in the mesh) of a nod (nod must be >=0 and < getNumNodes()).
   */
  int getNodeIndex(int nod) const { return m_nodeIndices[nod]; };

  /**
   * Gets the array of index mesh's nodes that belongs to this cell.
   */
  void getNodesIndex(PbArrayOfInt &nodes_index) const;

  /**
   * Gets the array of 2 index mesh's nodes that belongs to a given edge of this cell.
   * (edge must be >=0 and < getNumEdges())
   */
  virtual void getNodesIndexOfEdge (int edge, PbArrayOfInt &nodes_index) const=0;

  /**
   * Gets the array of index mesh's nodes that belongs to a given facet of this cell.
   * (facet must be >=0 and < getNumFacets()).
   */
  virtual void getNodesIndexOfFacet (int facet, PbArrayOfInt &nodes_index) const=0;

  /**
   * Gets the array of 2 nodes index that belongs to a given edge of this cell.
   * edge must be >=0 and < getNumEdges().
   * each index is >=0 and < getNumNodes()
   */
  virtual void getNodesLocalIndexOfEdge (int edge, PbArrayOfInt &nodes_index) const=0;

  /**
   * Gets the array of node index that belongs to a given facet of this cell.
   * facet must be >=0 and < getNumFacets().
   * each index is >=0 and < getNumNodes().
   */
  virtual void getNodesLocalIndexOfFacet (int facet, PbArrayOfInt &nodes_index) const=0;

  /**
   * Returns 1 if the point is inside the cell, 0 otherwise.
   * Gets also the parametric coordinate of the point and its weights
   * [OIVJAVA-WRAPPER-RETURN-TYPE SUCCESS_FLAG{return null}]
   */
  virtual int locatePoint(const SbVec3f &coord, float tolerance, SbVec3f &pcoord) const = 0;

  /**
   * Gets the weights of a point defined by its parametric coordinates.
   * [OIV-WRAPPER-ARG IN,ARRAY]
   */
  virtual void getWeight(const SbVec3f &pcoord, float *weight) const = 0;

  /**
   * Get the scalar value of a point in the cell.
   * @param pcoord [in] Parametric [0..1] coordinate of the point inside the cell.
   * @param s [in] The scalar dataset to interpolate
   * @return The interpolated value
   * [OIV-WRAPPER-ARG IN,ARRAY]
   */
  virtual float getValue(const SbVec3f &pcoord, const float *s) const;

  /**
   * Get the vector value of a point in the cell.
   * @param pcoord [in] Parametric [0..1] coordinate of the point inside the cell.
   * @param v [in] The vector dataset to interpolate
   * @return The interpolated value
   * [OIV-WRAPPER-ARG IN,ARRAY]
   */
  virtual SbVec3f getValue(const SbVec3f &pcoord, const SbVec3f *v) const;

  /**
   * Gets the scalar value of a point in this cell, given the point's weights.
   * [OIV-WRAPPER-ARG ARRAY,ARRAY]
   */
  float getValue(const float *weight, const float *s) const;

  /**
   * Gets the vector value of a point in this cell, given the point's weights.
   * [OIV-WRAPPER-ARG ARRAY,ARRAY]
   */
  SbVec3f getValue(const float *weight, const SbVec3f *v) const;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  virtual void print(FILE *fp) const;
  // Prints a formatted version of the cell to the given file pointer

  /**  
   * Checks and get the way the vertex of this cell are ordered.
   * Normal ordering is defined for each subclass. Generally
   * normal ordering of 3D cells is effective when the first 3 or 4 vertex indices
   * defines a facet oriented towards the interior of the cell.
   * 
   * @return 0 : reverse ordering
   * @return 1 : normal ordering
   * @return -1 : unknown ordering
   */
  virtual int getOrdering() const { return 1;}

  /**
   * Get the list of node of this cell on the plane, and the list
   * of edges of this cell crossing the plane.
   * The edges_ratio is an array of ratio allowing to compute
   * linear interpolation between the two extremities of the crossing edges.
   * This array has the same size as edges_crossing
   */
  virtual void getEdgesCrossingPlane(SbPlane &plane, 
                                     PbArrayOfInt &nodes_crossing, 
                                     PbArrayOfInt &edges_crossing,
                                     PbArrayOfFloat *edges_ratio) const;

  virtual const int* getNodesLocalIndexOfEdge(int edge) const = 0;

  virtual PiMarchingCase* getMCcase(unsigned char mc_case) const;
  /*----------------------------------------------------------------------------*/

  int addLevelSurfPart(PoMesh3D *mesh, SbBoolVector &nodes_sign, SbBool use_strip_set) const;

  // Defines the topology of a cell, no coord are specified
  // That allow to speed up the PbCellIterator for which no coord are necessary
  void setTopology(int index, int *node_indices) {
    m_nodeIndices = node_indices;
    m_index = index;
  }


  const int *getNodeIndexPtr() const { return m_nodeIndices; }

 protected:
  virtual unsigned char getIsosurfCaseId(SbBoolVector &nodes_sign) const = 0;
  int m_numFaces;
  int m_numEdges;
  int m_numNodes;
  int m_index;            
  int *m_nodeIndices;
  SbVec3f m_nodeCoord[8]; 

  mutable SbBox3f m_bbox;

 private:
  void copy(const PbCell &cell) ;
  void destroy();
};


inline PiMarchingCase* 
PbCell::getMCcase(unsigned char) const 
{
  return NULL;
}

/*---------------------------------------------------------------------------*/

#endif /* _PB_CELL_ */







