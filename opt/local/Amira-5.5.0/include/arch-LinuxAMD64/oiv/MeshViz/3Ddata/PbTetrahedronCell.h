/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_TETRAHEDRONCELL_
#define  _PB_TETRAHEDRONCELL_

#include <MeshViz/3Ddata/PbCell.h>

#ifdef USE_IOSTREAM
#  include <iostream>
#endif

class PiMatrix3;
class PbMesh;
class PiMarchingCase;

/**
 * @DTEXT  Defines an tetrahedron cell of a volume mesh.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *    A tetrahedron cell has 4 facets, 6 edges and 4 nodes. Each facet is a 
 *    triangle.
 *    The 3 first indices defines a facet oriented towards the interior of the 
 *    cell.
 * 
 *    Facets, nodes and edges are numbered as following :
 * <PRE>
 *             2          
 *             x          
 *            /|\         
 *           / | \                  
 *          /  |  \        facet 0 = 012  edge 0 = 01
 *         /   |   \       facet 1 = 023  edge 1 = 12
 *        /    |    \      facet 2 = 031  edge 2 = 20
 *       /     |     \     facet 3 = 132  edge 3 = 03
 *    0 x------|------x 1                 edge 4 = 13
 *       \     |     /                    edge 5 = 23
 *        \    |    /
 *         \   |   /
 *          \  |  /
 *           \ | /
 *            \|/
 *             x 
 *             3
 * </PRE>
 * 
 */
class MESHVIZ_API PbTetrahedronCell : public PbCell {


 public:

  /**
   * Constructor of a default simple cell.
   */
  PbTetrahedronCell(const PbMesh *owner_mesh) ;

  /**
   * Copy constructor
   */
  PbTetrahedronCell(const PbTetrahedronCell &cell);

  /**
   * Destructor.
   */
  ~PbTetrahedronCell() ;

  /**
   * Assignment operator.
   */
  PbTetrahedronCell& operator=(const PbTetrahedronCell &cell) ;

  /**
   * Gets the length of the longest edge of the cell
   */
  virtual float getLongestEdgeLength() const;

  /**
   * Gets the volume of the cell. 
   */
  virtual float getVolume() const;

  /**
   * Returns always 0.
   */
  virtual float getArea() const { return 0.0;}

  /**
   * Gets the array of 2 index mesh's nodes that belongs to a given edge of this cell.
   * (edge must be >=0 and < 6)
   */
  virtual void getNodesIndexOfEdge (int edge, PbArrayOfInt &nodes_index) const;

  /**
   * Gets the array of index mesh's nodes that belongs to a given facet of this cell.
   * (facet must be >=0 and < 4)
   */
  virtual void getNodesIndexOfFacet (int facet, PbArrayOfInt &nodes_index) const;

  /**
   * Gets the array of 2 nodes index that belongs to a given edge of this cell.
   * edge must be >=0 and < 6.
   * Each index in nodes_index is >=0 and < 4.
   */
  virtual void getNodesLocalIndexOfEdge (int edge, PbArrayOfInt &nodes_index) const;

  /**
   * Gets the array of node index that belongs to a given facet of this cell.
   * facet must be >=0 and < 4.
   * Each index is >=0 and < 4.
   */
  virtual void getNodesLocalIndexOfFacet (int facet, PbArrayOfInt &nodes_index) const;

  /**
   * Returns 1 if the point is inside the cell, 0 otherwise.
   * Gets also the parametric coordinate of the point .
   */
  virtual int locatePoint(const SbVec3f &coord, float tolerance, SbVec3f &pcoord) const;

  /**
   * Gets the 4 weights of a point defined by its parametric coordinates.
   */
  virtual void getWeight(const SbVec3f &pcoord, float *weight) const;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  /**
   * Defines a new valid tetrahedron.
   * If the 4 given nodes are on the same plane, return FALSE and does not define a new 
   * tetrahedron, otherwise return TRUE and defines this new tetrahedron.
   */
  SbBool set(int index, int *node_ids, float *x, float *y, float *z);

  void print(FILE *fp) const;
  // Prints a formatted version of the tetrahedron to the given file pointer

  /** @see PbCell::getOrdering() */
  virtual int getOrdering() const;

  virtual const int* getNodesLocalIndexOfEdge(int edge) const {
    return c_edgeNodes[edge];
  }

  PiMarchingCase* getMCcase(unsigned char mc_case) const {
    return c_MarchingLookup[mc_case];
  }

#ifdef USE_IOSTREAM
  friend std::ostream& operator << (std::ostream& s, PbTetrahedronCell &cell);
#endif

	static SbBool init();
	static void finish();
  /*----------------------------------------------------------------------------*/

 protected:
   virtual unsigned char getIsosurfCaseId(SbBoolVector &nodes_sign) const;

 private:

  void copy(const PbTetrahedronCell &cell) ;
  void destroy();

  static PiMarchingCase* addMC(PiMarchingCase *mcase);
  static PiMarchingCase* addMCBoth(PiMarchingCase *mcase);

  mutable PiMatrix3 *m_coordToPcoordMatrix;
  mutable SbVec3f  m_translatePcoord;
  mutable SbBool   m_pcoordTransfoUpdated;

  mutable SbBool  m_isValid;

  static int             c_edgeNodes[6][2]; 
  static PiMarchingCase* c_MarchingLookup[16];
  static SbBool          c_isInit;
  static int             c_count;
};

/*---------------------------------------------------------------------------*/

#endif /* _PB_TETRAHEDRONCELL_ */







