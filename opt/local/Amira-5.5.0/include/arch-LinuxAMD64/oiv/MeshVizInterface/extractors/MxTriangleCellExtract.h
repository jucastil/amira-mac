/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MxTriangleCellExtract_h
#define  _MxTriangleCellExtract_h

#include <MeshVizInterface/mesh/geometry/MiGeometryI.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/utility>

class MiSurfaceCell;

/**
 * @DTEXT Utility class for triangle cells.
 * 
 * @ingroup MeshIViz_Extract_Cell
 * 
 * @DESCRIPTION
 *   Utility class that provides a static implementation of the MiSurfaceCell's methods
 *   in a triangle cell. This class is provided to make easier the 
 *   creation of a class in the application that implements the MiSurfaceCell  
 *   interface for a triangle cell. 
 *      - value of iso parametric coordinates in a linear triangle cell.
 *        (see getIsoParametricCoord())
 *      - value of the 3 weights (aka shape functions) in a triangle cell.
 *        (see getWeight())
 *      - localization test (see isPointInsideCell())
 *
 * The following image shows the nodes numbering used by this class. 
 * The weights (see getWeight()), 
 * and parametric coordinates (see getIsoParametricCoord()) are 
 * defined according to this node numbering. 
 *
 * @IMAGE LinearTriangle3.png "Nodes numbering"
 */
class MESHIVIZ_API MxTriangleCellExtract 
{
public:

  /**
  * Computes the iso parametric coordinates of the given point in the given cell with the given geometry.
  * As computing the iso parametric coordinates of a point needs the coordinates of the cell's nodes, 
  * the given triangleCell is assumed to contain 3 nodes. 
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
     meshGeometry.getCoord(triangleCell->getNodeIndex(i)) 
    @endverbatim
  * for each i in the range [0-2].
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] triangleCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  */
  static MbVec3d getIsoParametricCoord(const MiGeometryI& meshGeometry, const MiSurfaceCell* triangleCell, const MbVec3d &point);
  
  /**
  * Returns the iso parametric coordinates of one of the 3 nodes of a triangle cell.
  * This static method helps to implement the method MiCell::getIsoParametricCoord().
  * @param [in] nodeIndex Must be defined in the range [0-2]
  */
  static MbVec3d getIsoParametricCoord(size_t nodeIndex);

  /**
  * Gets the weights in the given cell of the given point. This static method 
  * helps to implement the method MiCell::getWeight(meshGeometry,point,weights) 
  * for a triangle cell. As computing the weights of a point
  * needs the coordinates of the cell's nodes, the given triangleCell is 
  * assumed to contain 3 nodes. 
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
     meshGeometry.getCoord(triangleCell->getNodeIndex(i)) 
    @endverbatim
  * for each i in the range [0-2].
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] triangleCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the 3 values weights[0-2]. 
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 3 (at least) before calling this method, using for instance
  *    the weights.resize(3)
  */
  static void getWeight(const MiGeometryI& meshGeometry, const MiSurfaceCell* triangleCell, const MbVec3d &point, std::vector<double>& weights)
  {
    getWeight(getIsoParametricCoord(meshGeometry,triangleCell,point),weights);
  }

  /**
  * Gets the weights of a point defined by its iso parametric coordinates. This 
  * static method helps to implement the method MiCell::getWeight(ipcoord,weights) 
  * for a triangle cell.
  * @param[in] ipcoord The iso parametric coordinates of the input point. The reference
  *            space for the iso parametric coordinates is assumed to be [0-1]. Thus any
  *            point inside the cell has iso parametric coordinates in the interval [0-1].
  * @param[out] weights This method computes the 3 values weights[0-2].           
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 3 (at least) before calling this method, using for instance
  *    the weights::resize(3)
  */
  static void getWeight(const MbVec3d &ipcoord, std::vector<double>& weights)
  {
    weights[1] = ipcoord[0];
    weights[2] = ipcoord[1];
    weights[0] = 1.0 - weights[1] - weights[2];
  }

  /**
  * Checks if a point is inside or outside a triangle cell.
  * This static method helps to implement the method 
  * MiCell::isPointInsideCell(meshGeometry,point,weights) for a triangle cell.
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] triangleCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the 3 values weights[0-2] if the point is inside the cell. 
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 3 (at least) before calling this method, using for instance
  *    the weights::resize(3)
  * @return true if the point is inside the cell.
  */
  static bool isPointInsideCell(const MiGeometryI& meshGeometry, const MiSurfaceCell* triangleCell, const MbVec3d &point, std::vector<double>& weights)
  {
    getWeight(getIsoParametricCoord(meshGeometry,triangleCell,point),weights);
    return ( -1.E-5 < weights[0] &&  weights[0] < 1 + 1.E-5 &&
             -1.E-5 < weights[1] &&  weights[1] < 1 + 1.E-5 &&
             -1.E-5 < weights[2] &&  weights[2] < 1 + 1.E-5);
  }

  /**
  * Gets the longest edge of a triangle cell
  */
  static double getLongestEdgeLength(const MiGeometryI& meshGeometry, const MiSurfaceCell* cell);

  /**
  * Gets the shortest edge of a triangle cell
  */
  static double getShortestEdgeLength(const MiGeometryI& meshGeometry, const MiSurfaceCell* cell);

protected:

  static double s_nodesIsoParametricCoords[3][3];
};

#endif 

