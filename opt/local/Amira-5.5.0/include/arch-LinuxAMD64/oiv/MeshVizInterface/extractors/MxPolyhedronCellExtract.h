/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MxPolyhedronCellExtract_h
#define  _MxPolyhedronCellExtract_h

#include <MeshVizInterface/mesh/geometry/MiGeometryI.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/utility>

class MiVolumeCell;

/**
 * @DTEXT Utility class for polyhedron cells.
 * 
 * @ingroup MeshIViz_Extract_Cell
 * 
 * @DESCRIPTION
 *   Utility class that provides a static implementation of the MiVolumeCell's methods
 *   for a polyhedron cell. This class is provided to make easier the 
 *   creation of a class that implements the MiVolumeCell interface for a polyhedron
 *   cell. 
 *      - value of the weights (aka shape functions) in a polyhedron cell
 *        (see getWeight())
 *      - localization test (see isPointInsideCell())
 *
 *   This implementation of getWeight() method assumes that a polyhedron is
 *   defined as a set of oriented polygons such that their normal is pointing
 *   to the inside ( each facet vertices are ordered in an counter-clockwise direction
 *   looking from the inside).
 *
 */
class MESHIVIZ_API MxPolyhedronCellExtract 
{
public:

  /**
  * Gets the barycentric weights in the given polyhedron cell of the given point.
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
  meshGeometry.getCoord(polyhedronCell->getNodeIndex(i)) 
  @endverbatim
  * for each i with 0 <= i < polyhedronCell->getNumNodes()
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] polyhedronCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the N values weights[0,N-1], where N=polyhedronCell->getNumNodes().
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to N (at least) before calling this method, using for instance
  *    the weights.resize(N)
  */
  static void getWeight(const MiGeometryI& meshGeometry, const MiVolumeCell* polyhedronCell, const MbVec3d &point, std::vector<double>& weights);

  /**
  * Gets the longest distance inside the given polyhedron cell
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] polyhedronCell The input cell.
  */
  static double getLongestDistance(const MiGeometryI& meshGeometry, const MiVolumeCell* polyhedronCell);

  /**
  * Gets the shortest distance inside the given polyhedron cell
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] polyhedronCell The input cell.
 */
  static double getShortestDistance(const MiGeometryI& meshGeometry, const MiVolumeCell* polyhedronCell);

  /**
  * Checks if a point is inside the given polyhedron cell. All weights must be positive. 
  * This static method helps to implement the method MiCell::isPointInsideCell(meshGeometry,point,weights) 
  * for a polyhedron cell.
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
  meshGeometry.getCoord(polyhedronCell->getNodeIndex(i)) 
  @endverbatim
  * for each i with 0 <= i < polyhedronCell->getNumNodes()
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] polyhedronCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the N values weights[0,N-1], where N=polyhedronCell->getNumNodes().
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to N (at least) before calling this method, using for instance
  *    the weights.resize(N)
  */
  static bool isPointInsideCell(const MiGeometryI& meshGeometry, const MiVolumeCell* polyhedronCell, const MbVec3d &point, std::vector<double>& weights);

  /**
  * Computes the average normal to a planar or almost-planar polygon facet of a the given polyhedron cell.
  * This is done by using Newell's method.
  * @param[in] facet The number of the facet in the polyhedron cell.
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] polyhedronCell The input cell.
  */
  static MbVec3d getFacetNormal(size_t facet, const MiGeometryI& meshGeometry, const MiVolumeCell *polyhedronCell);

protected:

  static bool initClass();
  static void exitClass();
  static double cot(const MbVec3d& v1, const MbVec3d& v2);


  static bool            s_isInit;


};

#endif 

