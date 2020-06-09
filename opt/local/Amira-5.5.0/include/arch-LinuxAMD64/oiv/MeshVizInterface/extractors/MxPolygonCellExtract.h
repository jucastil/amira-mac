/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MxPolygonCellExtract_h
#define  _MxPolygonCellExtract_h

#include <MeshVizInterface/mesh/geometry/MiGeometryI.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/utility>

class MiSurfaceCell;

/**
* @DTEXT Utility class for polygon cells.
* 
* @ingroup MeshIViz_Extract_Cell
* 
* @DESCRIPTION
*   Utility class that provides a static implementation of the MiVolumeCell interface methods
*   for a polygon cell. This class is provided to make it easier to create 
*   a class that implements the MiVolumeCell interface for a polygon cell. 
*
*      - Value of the weights (aka shape functions) in a polygon cell
*        (see getWeight())
*      - Localization test (see isPointInsideCell())
*
*/
class MESHIVIZ_API MxPolygonCellExtract 
{
public:

  /**
  * Gets the barycentric weights in the given polygon cell of the given point. This static method 
  * helps to implement the method MiCell::getWeight(meshGeometry,point,weights) 
  * for a polygon cell. 
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
  meshGeometry.getCoord(polygonCell->getNodeIndex(i)) 
  @endverbatim
  * for each i with 0 <= i < polygonCell->getNumNodes()
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] polygonCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the N values weights[0,N-1], where N=polygonCell->getNumNodes().
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to N (at least) before calling this method, using for instance
  *    the weights.resize(N)
  */
  static void getWeight(const MiGeometryI& meshGeometry, const MiSurfaceCell* polygonCell, const MbVec3d &point, std::vector<double>& weights);

  /**
  * Gets the longest edge of a polygon cell
  */
  static double getLongestEdgeLength(const MiGeometryI& meshGeometry, const MiSurfaceCell* polygonCell);

  /**
  * Gets the shortest edge of a polygon cell
  */
  static double getShortestEdgeLength(const MiGeometryI& meshGeometry, const MiSurfaceCell* polygonCell);

  /**
  * Checks if a point is inside the given polygon cell.
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
  meshGeometry.getCoord(polygonCell->getNodeIndex(i)) 
  @endverbatim
  * for each i with 0 <= i < polygonCell->getNumNodes()
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] polygonCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the N values weights[0,N-1], where N=polygonCell->getNumNodes().
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to N (at least) before calling this method, using for instance
  *    the weights.resize(N)
  */
  static bool isPointInsideCell(const MiGeometryI& meshGeometry, const MiSurfaceCell* polygonCell, const MbVec3d &point, std::vector<double>& weights);

  /**
  * Computes the area of all planar or almost-planar irregular polygon (convex and concave).
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] polygonCell The input cell.
  */
  static double getArea(const MiGeometryI& meshGeometry, const MiSurfaceCell* polygonCell);

  /**
  * Computes the average normal to the given planar or almost-planar polygon cell.
  * This is done by using Newell's method.
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] polygonCell The input cell.
  */
  static MbVec3d getNormal(const MiGeometryI& meshGeometry, const MiSurfaceCell *polygonCell);

protected:

  static bool initClass();
  static void exitClass();
  static double cot(const MbVec3d& v1, const MbVec3d& v2, const MbVec3d& normal);

  static bool   s_isInit;

};

#endif 

