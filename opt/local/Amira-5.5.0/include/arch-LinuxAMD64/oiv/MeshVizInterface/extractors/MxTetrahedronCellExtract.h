/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MxTetrahedronCellExtract_h
#define  _MxTetrahedronCellExtract_h

#include <MeshVizInterface/mesh/geometry/MiGeometryI.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/utility>

class MxTabOfMarchingCase;
class MiVolumeCell;

/**
 * @DTEXT Utility class for tetrahedron cells.
 * 
 * @ingroup MeshIViz_Extract_Cell
 * 
 * @DESCRIPTION
 *   Utility class that provides a static implementation of the MiVolumeCell's methods
 *   in a tetrahedron cell. This class is provided to make easier the 
 *   creation of a class in the application that implements the MiVolumeCell  
 *   interface for a tetrahedron cell. 
 *      - extraction of the topology of an isosurface in a tetrahedron.
 *        (see getIsosurfTopology())
 *      - value of iso parametric coordinates in a linear tetrahedron cell.
 *        (see getIsoParametricCoord())
 *      - value of the 4 weights (aka shape functions) in a tetrahedron cell.
 *        (see getWeight())
 *      - localization test (see isPointInsideCell())
 *
 * The following image shows the nodes numbering and the faces numbering used by this class. 
 * The isosurface topology (see getIsosurfTopology()), weights (see getWeight()), 
 * and parametric coordinates (see getIsoParametricCoord()) are 
 * defined according to this node numbering. 
 *
 * @IMAGE LinearTetrahedron4.png "Nodes and faces numbering"
 */
class MESHIVIZ_API MxTetrahedronCellExtract 
{
public:

  /**
  * Returns the isosurface topology of the associated caseId.
  * This method can be used in the getIsosurfTopology(...) implementation of a tetrahedron cell interface to return
  * the information to the isosurface extraction module.
  */
  static void getIsosurfTopology(unsigned char caseId, std::vector< std::pair<size_t,size_t> >& edgeList );

  /**
  * Computes the iso parametric coordinates of the given point in the given cell with the given geometry.
  * As computing the iso parametric coordinates of a point needs the coordinates of the cell's nodes, 
  * the given tetrahedronCell is assumed to contain 4 nodes. 
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
     meshGeometry.getCoord(tetrahedronCell->getNodeIndex(i)) 
    @endverbatim
  * for each i in the range [0-3].
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] tetrahedronCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  */
  static MbVec3d getIsoParametricCoord(const MiGeometryI& meshGeometry, const MiVolumeCell* tetrahedronCell, const MbVec3d &point);
  
  /**
  * Returns the iso parametric coordinates of one of the 4 nodes of a tetrahedron cell.
  * This static method helps to implement the method MiCell::getIsoParametricCoord().
  * @param [in] nodeIndex Must be defined in the range [0-3]
  */
  static MbVec3d getIsoParametricCoord(size_t nodeIndex)
  {
    return MbVec3d(s_nodesIsoParametricCoords[nodeIndex]);
  }

  /**
  * Gets the weights in the given cell of the given point. This static method 
  * helps to implement the method MiCell::getWeight(meshGeometry,point,weights) 
  * for a tetrahedron cell. As computing the weights of a point
  * needs the coordinates of the cell's nodes, the given tetrahedronCell is 
  * assumed to contain 4 nodes. 
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
     meshGeometry.getCoord(tetrahedronCell->getNodeIndex(i)) 
    @endverbatim
  * for each i in the range [0-3].
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] tetrahedronCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the 4 values weights[0-3]. 
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 4 (at least) before calling this method, using for instance
  *    the weights.resize(4)
  */
  static void getWeight(const MiGeometryI& meshGeometry, const MiVolumeCell* tetrahedronCell, const MbVec3d &point, std::vector<double>& weights)
  {
    MbVec3d ipcoord = getIsoParametricCoord(meshGeometry,tetrahedronCell,point);
    getWeight(ipcoord,weights);
  }

  /**
  * Gets the weights of a point defined by its iso parametric coordinates. This 
  * static method helps to implement the method MiCell::getWeight(ipcoord,weights) 
  * for a tetrahedron cell.
  * @param[in] ipcoord The iso parametric coordinates of the input point. The reference
  *            space for the iso parametric coordinates is assumed to be [0-1]. Thus any
  *            point inside the cell has iso parametric coordinates in the interval [0-1].
  * @param[out] weights This method computes the 4 values weights[0-3].           
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 4 (at least) before calling this method, using for instance
  *    the weights::resize(4)
  */
  static void getWeight(const MbVec3d &ipcoord, std::vector<double>& weights)
  {
    ipcoord.getValue(weights[1],weights[2],weights[3]);
    weights[0] = 1.0 - weights[1] - weights[2] - weights[3];
  }

  /**
  * Gets the value of the derivatives of the shape functions (aka weights) at the point given by 
  * its iso parametric coordinates.
  * @param[in] ipcoord The iso parametric coordinates of the input point. The reference
  *            space for the iso parametric coordinates is assumed to be [0-1]. Thus any
  *            point inside the cell has iso parametric coordinates in the interval [0-1].
  * @param[out] derivs This method computes the 18 values derivs[0-17].   
  *    It assumes the derivs vector array has been already allocated.
  *    Its size must be set to 18 (at least) before calling this method, using for instance
  *    the derivs::resize(18)
  */
  static void getDerivs(const MbVec3d &ipcoord, std::vector<double>& derivs);

  /**
  * Checks if a point is inside or outside a tetrahedron cell.
  * This static method helps to implement the method 
  * MiCell::isPointInsideCell(meshGeometry,point,weights) for a tetrahedron cell.
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] tetrahedronCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the 4 values weights[0-3] if the point is inside the cell. 
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 4 (at least) before calling this method, using for instance
  *    the weights::resize(4)
  * @return true if the point is inside the cell.
  */
  static bool isPointInsideCell(const MiGeometryI& meshGeometry, const MiVolumeCell* tetrahedronCell, const MbVec3d &point, std::vector<double>& weights)
  {
    getWeight(getIsoParametricCoord(meshGeometry,tetrahedronCell,point),weights);
    return ( -1.E-5 < weights[0] &&  weights[0] < 1 + 1.E-5 &&
             -1.E-5 < weights[1] &&  weights[1] < 1 + 1.E-5 &&
             -1.E-5 < weights[2] &&  weights[2] < 1 + 1.E-5 &&
             -1.E-5 < weights[3] &&  weights[3] < 1 + 1.E-5);      
  }

  /**
  * Gets the volume of a tetrahedron cell.
  */
  static double getVolume(const MiGeometryI& meshGeometry, const MiVolumeCell* tetrahedronCell);

  /**
  * Gets the normal of the given facet in a tetrahedron cell.
  */
  static MbVec3d getFacetNormal(size_t facetId, const MiGeometryI& meshGeometry, const MiVolumeCell* tetrahedronCell);

  /**
  * Gets the longest edge of a tetrahedron cell
  */
  static double getLongestEdgeLength(const MiGeometryI& meshGeometry, const MiVolumeCell* cell);

  /**
  * Gets the shortest edge of a tetrahedron cell
  */
  static double getShortestEdgeLength(const MiGeometryI& meshGeometry, const MiVolumeCell* cell);

protected:

  static bool initClass();
  static void exitClass();

  static void initMarchingCase0();
  static void initMarchingCase1();
  static void initMarchingCase2();

  static bool                 s_isInit;
  static MxTabOfMarchingCase* s_tabOfMarchingTetra;
  static double               s_nodesIsoParametricCoords[4][3];
};

#endif 

