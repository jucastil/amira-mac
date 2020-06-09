/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_PIXELCELL_
#define  _PB_PIXELCELL_

#include <MeshViz/3Ddata/PbCell.h>

class PbMesh;

/**
 * @DTEXT  Defines a pixel cell of a surface mesh.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *    A pixel cell is a rectangle of which edges are parallel to X, Y axes.
 * 
 *    Nodes and edges are numbered as following :
 * <PRE>
 *                          3-----------2   edge 0 = 01
 *     j                    |           |   edge 1 = 12
 *                          |           |   edge 2 = 23
 *     |                    |           |   edge 3 = 30      
 *     |                    |           |   
 *     |                    |           |   
 *     x------> i           0-----------1   
 * </PRE>
 * 
 */
class MESHVIZ_API PbPixelCell : public PbCell {


 public:

  /**
   * Constructor of a default simple cell.
   */
  PbPixelCell(const PbMesh *owner_mesh) ;

  /**
   * Copy constructor
   */
  PbPixelCell(const PbPixelCell &cell);

  /**
   * Destructor.
   */
  ~PbPixelCell() ;

  /**
   * Assignment operator.
   */
  PbPixelCell& operator=(const PbPixelCell &cell) ;

  /**
   * Gets the length of the longest edge of the cell.
   */
  float getLongestEdgeLength() const;

  /**
   * Gets the cell's bounding box.
   */
  SbBox3f getBoundingBox() const;

  /**
   * Gets the cell's bounds. Similar to getBoundingBox() but it does not
   * use any SbBox object.
   */
  void getBounds(float &xmin,float &ymin, float &zmin, 
                 float &xmax,float &ymax, float &zmax) const;

  /**
   * Gets the cell's geometric center.
   */
  SbVec3f getCenter() const;

  /**
   * Returns always 0.
   */
  float getVolume() const { return 0.0;}

  /**
   * Gets the area of a cell.
   */
  float getArea() const { return m_dx*m_dy;}

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
   * Get the scalar value of a point in the cell.
   * @param pcoord [in] Parametric [0..1] coordinate of the point inside the cell.
   * @param s [in] The scalar dataset to interpolate
   * @return The interpolated value
   * [OIV-WRAPPER-ARG IN,ARRAY]
   */
  float getValue(const SbVec3f &pcoord, const float *s) const;

  /**
   * Get the vector value of a point in the cell.
   * @param pcoord [in] Parametric [0..1] coordinate of the point inside the cell.
   * @param v [in] The vector dataset to interpolate
   * @return The interpolated value
   * [OIV-WRAPPER-ARG IN,ARRAY]
   */
  SbVec3f getValue(const SbVec3f &pcoord, const SbVec3f *v) const;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  /**
   * Defines a new valid pixel, returns always TRUE.
   * i,j are the index of the first cell's node.
   */
  SbBool set(int index, int *node_ids, 
             float x_min, float y_min, 
             float x_max, float y_max);

  void print(FILE *fp) const;
  // Prints a formatted version of the pixel to the given file pointer

  virtual const int* getNodesLocalIndexOfEdge(int edge) const {
    return c_edgeNodes[edge];
  }

  /*----------------------------------------------------------------------------*/

 protected:
   virtual unsigned char getIsosurfCaseId(SbBoolVector &nodes_sign) const;

 private:

  void copy(const PbPixelCell &cell) ;
  void destroy();

  float m_xmin,m_ymin, m_xmax,m_ymax, m_dx,m_dy;

  static int             c_edgeNodes[4][2]; 
};


inline unsigned char
PbPixelCell::getIsosurfCaseId(SbBoolVector &) const 
{
  return 0;
}

/*---------------------------------------------------------------------------*/

#endif /* _PB_PIXELCELL_ */







