/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_WEDGECELL_
#define  _PB_WEDGECELL_

#include <MeshViz/3Ddata/PbCell.h>

#ifdef USE_IOSTREAM
#  include <iostream>
#endif

class PbMesh;
class PiMarchingCase;

/**
 * @DTEXT  Defines a wedge cell of a volume mesh.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *    A wedge cell has 5 facets which can be in any plane of
 *    3D space. It has 2 triangle facets and 3 quadrangle facets.
 *    The 3 first indices define a triangle facet oriented towards
 *    the interior of the cell.
 * 
 *    Facets, nodes, and edges are numbered as follows:
 * <PRE>
 *                  
 *                                   n2               facet 0 = 012   edge 0 = 01 
 *                                   x                facet 1 = 354   edge 1 = 12
 *                                . / \               facet 2 = 0253  edge 2 = 20
 *                             .   /   \              facet 3 = 1452  edge 3 = 34   
 *                          .     /     \             facet 4 = 0341  edge 4 = 45 
 *                       .       /       \                            edge 5 = 53
 *                  n5          /         \                           edge 6 = 03
 *                  x          /           \                          edge 7 = 14
 *                 / \     n0 x-------------x n1                      edge 8 = 25
 *                /   \    .             .            
 *               /     \.             .       
 *              /    .  \          .          
 *             /  .      \      .        
 *            /.          \  .           
 *        n3 x-------------x n4
 *                                                        
 * </PRE>
 * 
 */
class MESHVIZ_API PbWedgeCell : public PbCell {


 public:

  /**
   * Constructor of a default simple cell.
   */
  PbWedgeCell(const PbMesh *owner_mesh) ;

  /**
   * Copy constructor.
   */
  PbWedgeCell(const PbWedgeCell &cell);

  /**
   * Destructor.
   */
  ~PbWedgeCell() ;

  /**
   * Assignment operator.
   */
  PbWedgeCell& operator=(const PbWedgeCell &cell) ;

  /**
   * Returns the length of the longest edge of the cell.
   */
  virtual float getLongestEdgeLength() const;

  /**
   * Returns the volume of the cell. 
   */
  virtual float getVolume() const;

  /**
   * Always returns 0.
   */
  virtual float getArea() const { return 0.0;}

  /**
   * Returns the array of the 2 index mesh's nodes that belong to a given edge of this cell.
   * Edge must be >=0 and < 9.
   */
  virtual void getNodesIndexOfEdge (int edge, PbArrayOfInt &nodes_index) const;

  /**
   * Returns the array of index mesh's nodes that belong to a given facet of this cell.
   * Facet must be >=0 and < 5.
   */
  virtual void getNodesIndexOfFacet (int facet, PbArrayOfInt &nodes_index) const;

  /**
   * Returns the array of the 2 node indices that belong to a given edge of this cell.
   * Edge must be >=0 and < 9.
   * Each index is >=0 and < 6.
   */
  virtual void getNodesLocalIndexOfEdge (int edge, PbArrayOfInt &nodes_index) const;

  /**
   * Returns the array of node indices that belong to a given facet of this cell.
   * Facet must be >=0 and < 5.
   * Each index is >=0 and < 6.
   */
  virtual void getNodesLocalIndexOfFacet (int facet, PbArrayOfInt &nodes_index) const;

  /**
   * Returns 1 if the point is inside the cell, 0 otherwise.
   * Returns also the parametric coordinates of the point.
   */
  virtual int locatePoint(const SbVec3f &coord, float tolerance, SbVec3f &pcoord) const;

  /**
   * Returns the 6 weights of a point defined by its parametric coordinates.
   */
  virtual void getWeight(const SbVec3f &pcoord, float *weight) const;

  /**
   * Returns the derivs of a point defined by its parametric coordinates.
   * [OIV-WRAPPER-ARG IN,ARRAY{18}]
   */
  void getDerivs(const SbVec3f &pcoord, float *weight) const;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  /**
   * Defines a new valid wedge. Always returns TRUE.
   */
  SbBool set(int index, int *node_ids, float *x, float *y, float *z);

  void print(FILE *fp) const;
  // Prints a formatted version of the wedge to the given file pointer

  /** @see PbCell::getOrdering() */
  virtual int getOrdering() const;

  virtual const int* getNodesLocalIndexOfEdge(int edge) const {
    return c_edgeNodes[edge];
  }

  PiMarchingCase* getMCcase(unsigned char mc_case) const {
    return c_MarchingLookup[mc_case];
  }

#ifdef USE_IOSTREAM
  friend std::ostream& operator << (std::ostream& s, PbWedgeCell &cell);
#endif
	
	static SbBool init();
	static void finish();
  /*----------------------------------------------------------------------------*/

 protected:
   virtual unsigned char getIsosurfCaseId(SbBoolVector &nodes_sign) const;

 private:

  void copy(const PbWedgeCell &cell) ;
  void destroy();

  static PiMarchingCase* addMC(PiMarchingCase *mcase);
  static PiMarchingCase* addMCBoth(PiMarchingCase *mcase);

  static int             c_edgeNodes[9][2]; 
  static PiMarchingCase* c_MarchingLookup[64];
  static SbBool          c_isInit;
  static int             c_count;
};

/*---------------------------------------------------------------------------*/

#endif /* _PB_WEDGECELL_ */







