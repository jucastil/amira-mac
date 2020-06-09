/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _PB_QUADRANGLECELL_
#define  _PB_QUADRANGLECELL_

#include <MeshViz/3Ddata/PbCell.h>

class PbMesh;

/**
 * @DTEXT  Defines a quadrangle cell of a surface mesh.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *    A quadrangle cell is not necessarily a square, it can be a rectangle or 
 *    a lozenge.
 * 
 *    Nodes and edges are numbered as following :
 * <PRE>
 *              3-----------2   edge 0 = 01
 *              |           |   edge 1 = 12
 *              |           |   edge 2 = 23
 *              |           |   edge 3 = 30      
 *              |           |   
 *              |           |   
 *              0-----------1   
 * </PRE>
 * 
 */
class MESHVIZ_API PbQuadrangleCell : public PbCell {


 public:

  /**
   * Constructor of a default simple cell.
   */
  PbQuadrangleCell(const PbMesh *owner_mesh) ;

  /**
   * Copy constructor
   */
  PbQuadrangleCell(const PbQuadrangleCell &cell);

  /**
   * Destructor.
   */
  ~PbQuadrangleCell() ;

  /**
   * Assignment operator.
   */
  PbQuadrangleCell& operator=(const PbQuadrangleCell &cell) ;

  /**
   * Gets the length of the longest edge of the cell
   */
  virtual float getLongestEdgeLength() const;

  /**
   * Returns always 0.
   */
  virtual float getVolume() const { return 0.0; }

  /**
   * Gets the area of a cell.
   */
  virtual float getArea() const;

  /**
   * Gets the array of 2 index mesh's nodes that belongs to a given edge of this cell.
   * (edge must be >=0 and < 4)
   */
  virtual void getNodesIndexOfEdge (int edge, PbArrayOfInt &nodes_index) const;

  /**
   * Gets the array of index mesh's nodes that belongs to a given facet of this cell.
   * (facet must be == 0).
   */
  virtual void getNodesIndexOfFacet (int facet, PbArrayOfInt &nodes_index) const;

  /**
   * Gets the array of 2 nodes index that belongs to a given edge of this cell.
   * edge must be >=0 and < 4.
   * Each index is >=0 and < 4
   */
  virtual void getNodesLocalIndexOfEdge (int edge, PbArrayOfInt &nodes_index) const;

  /**
   * Gets the array of node index that belongs to a given facet of this cell.
   * facet must be == 0.
   * Each index is >=0 and < 4.
   */
  virtual void getNodesLocalIndexOfFacet (int facet, PbArrayOfInt &nodes_index) const;

  /**
   * Returns 1 if the point is inside the cell, 0 otherwise.
   * Gets also the parametric coordinate of the point and its weights
   */
  virtual int locatePoint(const SbVec3f &coord, float tolerance, SbVec3f &pcoord) const;

  /**
   * Gets the 4 weights of a point defined by its parametric coordinates.
   */
  virtual void getWeight(const SbVec3f &pcoord, float *weight) const;

  /**
   * Gets the derivs of a point defined by its parametric coordinates
   * [OIV-WRAPPER-ARG IN,ARRAY{8}]
   */
  void getDerivs(const SbVec3f &pcoord, float *derivs) const;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  /**
   * Defines a new valid 2D quadrangle. node_ids are the 4 nodes index
   * in the arrays x,y.
   * Returns always TRUE.
   */
  SbBool set(int index, int *node_ids, const float *x, const float *y);

  /**
   * Defines a new valid 3D quadrangle.  node_ids are the 4 nodes index
   * in the arrays x,y,z.
   * Returns always TRUE.
   */
  SbBool set(int index, int *node_ids, const float *x, const float *y, const float *z);

  /**
   * Defines a new valid 3D quadrangle with its limits (min,max), and by the 
   * indices i,j of its lower left corner.
   * Returns always TRUE.
   */
  SbBool set(int index, int *node_ids, float x_min, float y_min, float x_max, float y_max, const float *z);

  virtual const int* getNodesLocalIndexOfEdge(int edge) const {
    return c_edgeNodes[edge];
  }

  // Prints a formatted version of the quadrangle to the given file pointer
  void print(FILE *fp) const;

  /*----------------------------------------------------------------------------*/

 protected:
   virtual unsigned char getIsosurfCaseId(SbBoolVector &nodes_sign) const;

 private:

  void copy(const PbQuadrangleCell &cell) ;
  void destroy();
  int locatePointOnXY(const SbVec3f &coord, const SbVec3f &proj_coord, float tolerance, SbVec3f &pcoord, int indx, int indy) const;
  SbVec3f    m_normal;
  SbBool     m_2DCell;
  static int             c_edgeNodes[4][2]; 
};


inline unsigned char
PbQuadrangleCell::getIsosurfCaseId(SbBoolVector &) const
{
  return 0; 
}

/*---------------------------------------------------------------------------*/

#endif /* _PB_QUADRANGLECELL_ */







