/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_VOXELCELL_
#define  _PB_VOXELCELL_

#include <MeshViz/3Ddata/PbCell.h>
#include <MeshViz/3Ddata/PbHexahedronCell.h>

class PbMesh;
class PiMarchingCase;

/**
 * @DTEXT  Defines a voxel cell of a volume mesh.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *    A voxel is a parallelepipede of which faces are orthogonal to X, Y, Z axes.
 *    Each facet is a rectangle not necessarily a square.
 *    The 4 first indices defines a facet oriented towards the interior of the 
 *    cell.
 * 
 *    Facets, nodes and edges are numbered as following :
 * <PRE>
 *               4-----------7                    facet 0 = 0374  edge 0 = 01
 *              /|          /|       k            facet 1 = 1562  edge 1 = 12
 *            /  |        /  |       |            facet 2 = 0451  edge 2 = 23
 *          /    |      /    |       |            facet 3 = 3267  edge 3 = 30             
 *         5----------6      |       |            facet 4 = 0123  edge 4 = 45               
 *         |     |    |      |       ....... j    facet 5 = 4765  edge 5 = 56
 *         |     0----|------3      .                             edge 6 = 67
 *         |    /     |     /      .                              edge 7 = 74
 *         |  /       |   /       .                               edge 8 = 04
 *         |/         | /        i                                edge 9 = 15
 *         1----------2                                           edge10 = 26
 *                                                                edge11 = 37
 * </PRE>
 *    This numerotation must be respected to have the right result returned 
 *    by getVolume().(i.e. edge 01 on Xaxis, edge 12 on Yaxis, edge 26 on Zaxis)
 * 
 */
class MESHVIZ_API PbVoxelCell : public PbCell {


 public:

  /**
   * Constructor of a default simple cell.
   */
  PbVoxelCell(const PbMesh *owner_mesh) ;

  /**
   * Copy constructor
   */
  PbVoxelCell(const PbVoxelCell &cell);

  /**
   * Destructor.
   */
  ~PbVoxelCell() ;

  /**
   * Assignment operator.
   */
  PbVoxelCell& operator=(const PbVoxelCell &cell) ;

  /**
   * Gets the length of the longest edge of the cell
   */
  virtual float getLongestEdgeLength() const;

  /**
   * Gets the cell's bounding box.
   */
  virtual SbBox3f getBoundingBox() const;

  /**
   * Gets the cell's bounds. Similar to getBoundingBox() but it does not
   * use any SbBox object.
   */
  void getBounds(float &xmin,float &ymin, float &zmin, 
                 float &xmax,float &ymax, float &zmax) const;

  /**
   * Gets the cell's geometric center.
   */
  virtual SbVec3f getCenter() const;

  /**
   * Gets the volume of the cell. 
   */
  virtual float getVolume() const { return m_dx * m_dy * m_dz;}

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

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  /**
   * Defines a new valid voxel. Returns always TRUE.
   */
  SbBool set(int index, int *node_ids, 
             float x_min, float y_min, float z_min, 
             float x_max, float y_max, float z_max);

  virtual const int* getNodesLocalIndexOfEdge(int edge) const {
    return c_edgeNodes[edge];
  }

  void print(FILE *fp) const;
  // Prints a formatted version of the voxel to the given file pointer

  PiMarchingCase* getMCcase(unsigned char mc_case) const {
    return PbHexahedronCell::c_MarchingLookup[mc_case];
  }
  /*----------------------------------------------------------------------------*/

 protected:
   virtual unsigned char getIsosurfCaseId(SbBoolVector &nodes_sign) const;

 private:

  void copy(const PbVoxelCell &cell) ;
  void destroy();

  float m_xmin,m_ymin,m_zmin, m_xmax,m_ymax,m_zmax, m_dx,m_dy,m_dz;
  static int             c_edgeNodes[12][2]; 
};

/*---------------------------------------------------------------------------*/

#endif /* _PB_VOXELCELL_ */







