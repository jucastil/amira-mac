/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MxQuadrangle8CellExtract_h
#define  _MxQuadrangle8CellExtract_h

#include <MeshVizInterface/mesh/geometry/MiGeometryI.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/utility>

class MiSurfaceCell;

/**
* @DTEXT Utility class for quadratic quadrangle cells with 8 nodes.
 * 
 * @ingroup MeshIViz_Extract_Cell
 * 
 * @DESCRIPTION
 *   Utility class that provides a static implementation of the MiSurfaceCell interface methods
 *   for a quadratic quadrangle cell of 8 nodes. This class is provided to make it easier to
 *   create a class that implements the MiSurfaceCell  
 *   interface for a quadratic quadrangle of 8 nodes. 
 *      - Value of iso parametric coordinates in a quadratic quadrangle of 8 nodes
 *        (see getIsoParametricCoord())
 *      - Value of the 8 weights (aka shape functions) in a quadratic quadrangle of 8 nodes
 *        (see getWeight())
 *      - Localization test (see isPointInsideCell())
 *
 * The following image shows the node numbering used by this class. 
 * The weights (see getWeight()), 
 * and parametric coordinates (see getIsoParametricCoord()) are 
 * defined according to this node numbering. 
 *
 * @IMAGE QuadraticQuadrangle8.png "Nodes numbering"
 *
 */
class MESHIVIZ_API MxQuadrangle8CellExtract 
{
public:

  /**
  * Computes the iso parametric coordinates of the given point in the given cell with the given geometry.
  * As computing the iso parametric coordinates of a point needs the coordinates of the cell's nodes, 
  * the given quadrangleCell is assumed to contain 8 nodes. 
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
     meshGeometry.getCoord(quadrangleCell->getNodeIndex(i)) 
    @endverbatim
  * for each i in the range [0-7].
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] quadrangleCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  */
  static MbVec3d getIsoParametricCoord(const MiGeometryI& meshGeometry, const MiSurfaceCell* quadrangleCell, const MbVec3d &point);
  
  /**
  * Returns the iso parametric coordinates of one of the 8 nodes of a quadrangle cell.
  * This static method helps to implement the method MiCell::getIsoParametricCoord().
  * @param [in] nodeIndex Must be defined in the range [0-7]
  */
  static MbVec3d getIsoParametricCoord(size_t nodeIndex)
  {
    return MbVec3d(s_nodesIsoParametricCoords[nodeIndex]);
  }

  /**
  * Gets the weights in the given cell of the given point. This static method 
  * helps to implement the method MiCell::getWeight(meshGeometry,point,weights) 
  * for a quadrangle cell. As computing the weights of a point
  * needs the coordinates of the cell's nodes, the given quadrangleCell is 
  * assumed to contain 8 nodes. 
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
     meshGeometry.getCoord(quadrangleCell->getNodeIndex(i)) 
    @endverbatim
  * for each i in the range [0-7].
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] quadrangleCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the 8 values weights[0-7]. 
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 8 (at least) before calling this method, using for instance
  *    the weights.resize(8)
  */
  static void getWeight(const MiGeometryI& meshGeometry, const MiSurfaceCell* quadrangleCell, const MbVec3d &point, std::vector<double>& weights)
  {
    getWeight(getIsoParametricCoord(meshGeometry,quadrangleCell,point),weights);
  }

  /**
  * Gets the weights of a point defined by its iso parametric coordinates. This 
  * static method helps to implement the method MiCell::getWeight(ipcoord,weights) 
  * for a quadrangle cell.
  * @param[in] ipcoord The iso parametric coordinates of the input point. The reference
  *            space for the iso parametric coordinates is assumed to be [0-1]. Thus any
  *            point inside the cell has iso parametric coordinates in the interval [0-1].
  * @param[out] weights This method computes the 8 values weights[0-7].           
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 8 (at least) before calling this method, using for instance
  *    the weights::resize(8)
  */
  static void getWeight(const MbVec3d &ipcoord, std::vector<double>& weights);

  /**
  * Gets the value of the derivatives of the shape functions (aka weights) at the point given by 
  * its iso parametric coordinates.
  * @param[in] ipcoord The iso parametric coordinates of the input point. The reference
  *            space for the iso parametric coordinates is assumed to be [0-1]. Thus any
  *            point inside the cell has iso parametric coordinates in the interval [0-1].
  * @param[out] derivs This method computes the 24 values derivs[0-23].   
  *    It assumes the derivs vector array has been already allocated.
  *    Its size must be set to 24 (at least) before calling this method, using for instance
  *    the derivs::resize(24)
  */
  static void getDerivs(const MbVec3d &ipcoord, std::vector<double>& derivs);

  /**
  * Checks if a point is inside or outside a quadrangle cell.
  * This static method helps to implement the method 
  * MiCell::isPointInsideCell(meshGeometry,point,weights) for a quadrangle cell.
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] quadrangleCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the 8 values weights[0-7] if the point is inside the cell. 
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 8 (at least) before calling this method, using for instance
  *    the weights::resize(8)
  * @return true if the point is inside the cell.
  */
  static bool isPointInsideCell(const MiGeometryI& meshGeometry, const MiSurfaceCell* quadrangleCell, const MbVec3d &point, std::vector<double>& weights)
  {
    MbVec3d pcoord = getIsoParametricCoord(meshGeometry,quadrangleCell,point);
    bool inside = ( -1.E-5 < pcoord[0] &&  pcoord[0] < 1 + 1.E-5 &&
                    -1.E-5 < pcoord[1] &&  pcoord[1] < 1 + 1.E-5 );
    if (inside)
      getWeight(pcoord,weights);
    return inside;
  }

  /**
  * Gets a triangulation of a quadratic quadrangle of 8 nodes.
  * This static method helps to implement the method MiSurfaceCell::getSubTriangleNodesIndex() 
  * for a quadratic quadrangle of 8 nodes.
  * @param[out] triangleNodeIds Sub triangle node ids (where: 0 <= triangleNodeIds[i] < 8 for each i).
  * @return The number of sub triangles in the cell.
  */
  static size_t getSubTriangleNodesIndex (std::vector<size_t>& triangleNodeIds)
  {
    triangleNodeIds.assign(s_subTriangleNodeIds,s_subTriangleNodeIds+(6*3));
    return 6;
  }

  friend std::ostream& operator << (std::ostream& s, const MxQuadrangle8CellExtract& cell);

protected:
  static double s_nodesIsoParametricCoords[8][3];
  static size_t s_subTriangleNodeIds[6*3];
};

#endif 

