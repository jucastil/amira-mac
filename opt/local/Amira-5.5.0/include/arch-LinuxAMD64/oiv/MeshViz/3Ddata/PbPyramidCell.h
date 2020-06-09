/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_PYRAMIDCELL_
#define  _PB_PYRAMIDCELL_

#include <MeshViz/3Ddata/PbCell.h>

#ifdef USE_IOSTREAM
#  include <iostream>
#endif

class PbMesh;
class PiMarchingCase;

/**
 * @DTEXT  Defines a pyramid cell of a volume mesh.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *    A pyramid cell has 5 facets which can be in any plane of
 *    3D space. It has 4 triangle facets and 1 quadrangle facet.
 *    The 4 first indices define the base quadrangle facet oriented towards 
 *    the interior of the cell.
 * 
 *    Facets, nodes and edges are numbered as follows:
 * <PRE>
 *                  
 *                n4
 *                x                           facet 0 = 0123  edge 0 = 01 
 *               /| \ .                       facet 1 = 041   edge 1 = 12
 *              / |  \   .                    facet 2 = 142   edge 2 = 23
 *             /  |   \     .                 facet 3 = 243   edge 3 = 30  
 *            /   |    \       .              facet 4 = 340   edge 4 = 04  
 *           /    |     \         .                           edge 5 = 14
 *          /  n3 x------\----------x n2                      edge 6 = 24
 *         /    '         \       '                           edge 7 = 34
 *        /  '             \   '                              
 *    n0 x------------------x n1
 *
 * </PRE>
 * 
 */
class MESHVIZ_API PbPyramidCell : public PbCell {


 public:

  /**
   * Constructor of a default simple cell.
   */
  PbPyramidCell(const PbMesh *owner_mesh) ;

  /**
   * Copy constructor.
   */
  PbPyramidCell(const PbPyramidCell &cell);

  /**
   * Destructor.
   */
  ~PbPyramidCell() ;

  /**
   * Assignment operator.
   */
  PbPyramidCell& operator=(const PbPyramidCell &cell) ;

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
   * Returns the array of 2 index mesh's nodes that belong to a given edge of this cell.
   * (edge must be >=0 and < 8)
   */
  virtual void getNodesIndexOfEdge (int edge, PbArrayOfInt &nodes_index) const;

  /**
   * Returns the array of index mesh's nodes that belong to a given facet of this cell.
   * (facet must be >=0 and < 5)
   */
  virtual void getNodesIndexOfFacet (int facet, PbArrayOfInt &nodes_index) const;

  /**
   * Returns the array of 2 nodes index that belong to a given edge of this cell.
   * edge must be >=0 and < 8.
   * Each index in nodes_index is >=0 and < 5.
   */
  virtual void getNodesLocalIndexOfEdge (int edge, PbArrayOfInt &nodes_index) const;

  /**
   * Returns the array of node index that belong to a given facet of this cell.
   * facet must be >=0 and < 5.
   * Each index is >=0 and < 5.
   */
  virtual void getNodesLocalIndexOfFacet (int facet, PbArrayOfInt &nodes_index) const;

  /**
   * Returns 1 if the point is inside the cell, 0 otherwise.
   * Returns also the parametric coordinate of the point.
   */
  virtual int locatePoint(const SbVec3f &coord, float tolerance, SbVec3f &pcoord) const;

  /**
   * Returns the 5 weights of a point defined by its parametric coordinates.
   */
  virtual void getWeight(const SbVec3f &pcoord, float *weight) const;

  /**
   * Returns the derivs of a point defined by its parametric coordinates.
   * [OIV-WRAPPER-ARG IN,ARRAY{15}]
   */
  void getDerivs(const SbVec3f &pcoord, float *weight) const;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  /**
   * Defines a new valid pyramid. Always returns TRUE.
   */
  SbBool set(int index, int *node_ids, float *x, float *y, float *z);

  void print(FILE *fp) const;
  // Prints a formatted version of the pyramid to the given file pointer

  /** @see PbCell::getOrdering() */
  virtual int getOrdering() const;

  virtual const int* getNodesLocalIndexOfEdge(int edge) const {
    return c_edgeNodes[edge];
  }
/*----------------------------------------------------------------------------*/

  PiMarchingCase* getMCcase(unsigned char mc_case) const {
    return c_MarchingLookup[mc_case];
  }

#ifdef USE_IOSTREAM
  friend std::ostream& operator << (std::ostream& s, PbPyramidCell &cell);
#endif

	static SbBool init();
	static void finish();

/*----------------------------------------------------------------------------*/

 protected:
   virtual unsigned char getIsosurfCaseId(SbBoolVector &nodes_sign) const;

 private:

  void copy(const PbPyramidCell &cell) ;
  void destroy();

  static PiMarchingCase* addMC(PiMarchingCase *mcase);
  static PiMarchingCase* addMCBoth(PiMarchingCase *mcase);

  static int             c_edgeNodes[8][2]; 
  static PiMarchingCase* c_MarchingLookup[32];
  static SbBool          c_isInit;
  static int             c_count;
};

/*---------------------------------------------------------------------------*/

#endif /* _PB_PYRAMIDCELL_ */







