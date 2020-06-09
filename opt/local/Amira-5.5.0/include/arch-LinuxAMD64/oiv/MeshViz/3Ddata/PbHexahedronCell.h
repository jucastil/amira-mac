/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_HEXAHEDRONCELL_
#define  _PB_HEXAHEDRONCELL_

#include <MeshViz/3Ddata/PbCell.h>

#ifdef USE_IOSTREAM
#  include <iostream>
#endif

class PbMesh;
class PiMarchingCase;

/**
 * @DTEXT  Defines an hexahedron cell of a volume mesh.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *    An hexahedron cell has 6 facets which can be in any plane of
 *    the 3D space. Each facet is a quadrangle not necessarily a square.
 *    The 4 first indices defines a facet oriented towards the interior of the 
 *    cell.
 * 
 *    Facets, nodes and edges are numbered as following :
 * <PRE>
 *                        4-----------7   facet 0 = 0374  edge 0 = 01
 *                       /|          /|   facet 1 = 1562  edge 1 = 12
 *                     /  |        /  |   facet 2 = 0451  edge 2 = 23
 *                   /    |      /    |   facet 3 = 3267  edge 3 = 30      
 *                  5----------6      |   facet 4 = 0123  edge 4 = 45      
 *                  |     |    |      |   facet 5 = 4765  edge 5 = 56
 *                  |     0----|------3                   edge 6 = 67
 *                  |    /     |     /                    edge 7 = 74
 *                  |  /       |   /                      edge 8 = 04
 *                  |/         | /                        edge 9 = 15
 *                  1----------2                          edge10 = 26
 *                                                        edge11 = 37
 * </PRE>
 * 
 */
class MESHVIZ_API PbHexahedronCell : public PbCell {

 public:

  /**
   * Constructor of a default simple cell.
   */
  PbHexahedronCell(const PbMesh *owner_mesh) ;

  /**
   * Copy constructor
   */
  PbHexahedronCell(const PbHexahedronCell &cell);

  /**
   * Destructor.
   */
  ~PbHexahedronCell() ;

  /**
   * Assignment operator.
   */
  PbHexahedronCell& operator=(const PbHexahedronCell &cell) ;

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
   * (edge must be >=0 and < 12)
   */
  virtual void getNodesIndexOfEdge (int edge, PbArrayOfInt &nodes_index) const;

  /**
   * Gets the array of index mesh's nodes that belongs to a given facet of this cell.
   * (facet must be >=0 and < 6)
   */
  virtual void getNodesIndexOfFacet (int facet, PbArrayOfInt &nodes_index) const;

  /**
   * Gets the array of 2 nodes index that belongs to a given edge of this cell.
   * edge must be >=0 and < 12.
   * Each index in nodes_index is >=0 and < 8.
   */
  virtual void getNodesLocalIndexOfEdge (int edge, PbArrayOfInt &nodes_index) const;

  /**
   * Gets the array of node index that belongs to a given facet of this cell.
   * facet must be >=0 and < 6.
   * Each index is >=0 and < 8.
   */
  virtual void getNodesLocalIndexOfFacet (int facet, PbArrayOfInt &nodes_index) const;

  /**
   * Returns 1 if the point is inside the cell, 0 otherwise.
   * Gets also the parametric coordinate of the point .
   */
  virtual int locatePoint(const SbVec3f &coord, float tolerance, SbVec3f &pcoord) const;

  /**
   * Gets the 8 weights of a point defined by its parametric coordinates.
   */
  virtual void getWeight(const SbVec3f &pcoord, float *weight) const;

  /**
   * Gets the derivs of a point defined by its parametric coordinates.
   * [OIV-WRAPPER-ARG IN,ARRAY{24}]
   */
  void getDerivs(const SbVec3f &pcoord, float *weight) const;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  /**
   * Defines a new valid hexahedron. Returns always TRUE.
   */
  SbBool set(int index, int *node_ids, float *x, float *y, float *z);

  void print(FILE *fp) const;
  // Prints a formatted version of the hexahedron to the given file pointer

  /** @see PbCell::getOrdering() */
  virtual int getOrdering() const;

  virtual const int* getNodesLocalIndexOfEdge(int edge) const {
    return c_edgeNodes[edge];
  }

  // not private because used by PbVoxelCell
  static PiMarchingCase* c_MarchingLookup[256];
/*----------------------------------------------------------------------------*/
  PiMarchingCase* getMCcase(unsigned char mc_case) const {
    return c_MarchingLookup[mc_case];
  }
  //  static std::vector< int >* getMCStripSet(unsigned char mc_case);
  //  static std::vector< int >* getMCFaceSet(unsigned char mc_case);
#ifdef USE_IOSTREAM
  friend std::ostream& operator << (std::ostream& s, PbHexahedronCell &cell);
#endif

	static SbBool    init();
	static void			 finish();

/*----------------------------------------------------------------------------*/
 protected:
   virtual unsigned char getIsosurfCaseId(SbBoolVector &nodes_sign) const;

 private:

  void copy(const PbHexahedronCell &cell) ;
  void destroy();

  static PiMarchingCase* addMC(PiMarchingCase *mcase);
  static PiMarchingCase* addMCBoth(PiMarchingCase *mcase);

  static int             c_edgeNodes[12][2]; 
  static SbBool          c_isInit;
  static size_t          c_numInit;

  static int             c_count;
};

/*---------------------------------------------------------------------------*/

#endif /* _PB_HEXAHEDRONCELL_ */







