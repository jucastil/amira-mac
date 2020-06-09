/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_TRIANGLECELL_
#define  _PB_TRIANGLECELL_

#include <MeshViz/3Ddata/PbCell.h>

class PbMesh;

/**
 * @DTEXT  Defines a triangle cell of a surface mesh.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *    Nodes and edges are numbered as following :
 * <PRE>
 *                  n2
 *                  x
 *                 / \
 *                /   \                  edge 0 = 01
 *               /     \                 edge 1 = 12 
 *              /       \                edge 2 = 20
 *             /         \               
 *            /           \              
 *        n0 x-------------x n1
 * </PRE>
 * 
 */

class MESHVIZ_API PbTriangleCell : public PbCell {

 public:

  /**
   * Constructor of a default simple cell.
   */
  PbTriangleCell(const PbMesh *owner_mesh);

  /**
   * Copy constructor
   */
  PbTriangleCell(const PbTriangleCell &cell);

  /**
   * Destructor.
   */
  ~PbTriangleCell();

  /**
   * Assignment operator.
   */
  PbTriangleCell& operator=(const PbTriangleCell &cell);

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
   * (edge must be >=0 and < 3)
   */
  virtual void getNodesIndexOfEdge (int edge, PbArrayOfInt &nodes_index) const;

  /**
   * Gets the array of index mesh's nodes that belongs to a given facet of this cell.
   * (facet must be == 0).
   */
  virtual void getNodesIndexOfFacet (int facet, PbArrayOfInt &nodes_index) const;

  /**
   * Gets the array of 2 nodes index that belongs to a given edge of this cell.
   * edge must be >=0 and < 3.
   * Each index is >=0 and < 3
   */
  virtual void getNodesLocalIndexOfEdge (int edge, PbArrayOfInt &nodes_index) const;

  /**
   * Gets the array of node index that belongs to a given facet of this cell.
   * facet must be == 0.
   * Each index is >=0 and < 3.
   */
  virtual void getNodesLocalIndexOfFacet (int facet, PbArrayOfInt &nodes_index) const;

  /**
   * Returns 1 if the point is inside the cell, 0 otherwise.
   * Gets also the parametric coordinate of the point and its weights
   */
  virtual int locatePoint(const SbVec3f &coord, float tolerance, SbVec3f &pcoord) const;

  /**
   * Gets the 3 weights of a point defined by its parametric coordinates.
   */
  virtual void getWeight(const SbVec3f &pcoord, float *weight) const;

  /*----------------------------------------------------------------------------*/

 PoINTERNAL public:
  /**
   * Defines a new valid 2D triangle. i0,i1,i2 are the 3 nodes index
   * in the arrays x,y.
   * If the 3 given nodes are on the same line, return FALSE and does not 
   * define a new triangle, otherwise return TRUE and defines this new triangle
   */
  SbBool set(int index, int *node_ids, const float *x, const float *y);

  /**
   * Defines a new valid 3D triangle. i0,i1,i2 are the 3 nodes index
   * in the arrays x,y,z.
   * If the 3 given nodes are on the same line, return FALSE and does not 
   * define a new triangle, otherwise return TRUE and defines this new triangle
   */
  SbBool set(int index, int *node_ids, const float *x, const float *y, const float *z);


  virtual const int* getNodesLocalIndexOfEdge(int edge) const {
    return c_edgeNodes[edge];
  }

  // Prints a formatted version of the triangle to the given file pointer
  void print(FILE *fp) const;

  /*----------------------------------------------------------------------------*/

 protected:
   virtual unsigned char getIsosurfCaseId(SbBoolVector &nodes_sign) const;

 private:

  void copy(const PbTriangleCell &cell);
  void destroy();
  SbBool set(
             const float *x, const float *y, const float *z,
             const float *xc, const float *yc);
  int locatePointOnXY(const SbVec3f &coord, float tolerance, SbVec3f &pcoord, 
                      int indx, int indy) const;

  float m_translateXPcoord, m_translateYPcoord;
  float m_coordToPcoordMatrixMa, m_coordToPcoordMatrixMb,
        m_coordToPcoordMatrixMc, m_coordToPcoordMatrixMd;

  SbVec3f    m_normal;
  SbBool     m_2DCell, m_isValid;
  int        m_ignoredProjCoord;
  static int c_edgeNodes[3][2]; 
};


inline unsigned char
PbTriangleCell::getIsosurfCaseId(SbBoolVector &) const
{
  return 0; 
}

/*---------------------------------------------------------------------------*/

#endif /* _PB_TRIANGLECELL_ */







