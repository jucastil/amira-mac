/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MxQuadrangleCellExtract_h
#define  _MxQuadrangleCellExtract_h

#include <MeshVizInterface/mesh/geometry/MiGeometryI.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/utility>

class MiSurfaceCell;

/**
 * @DTEXT Utility class for quadrangle cells.
 * 
 * @ingroup MeshIViz_Extract_Cell
 * 
 * @DESCRIPTION
 *   Utility class that provides a static implementation of the MiSurfaceCell's methods
 *   in a quadrangle cell. This class is provided to make easier the 
 *   creation of a class in the application that implements the MiSurfaceCell  
 *   interface for a quadrangle cell. 
 *      - value of iso parametric coordinates in a linear quadrangle cell.
 *        (see getIsoParametricCoord())
 *      - value of the 4 weights (aka shape functions) in a quadrangle cell.
 *        (see getWeight())
 *      - localization test (see isPointInsideCell())
 *
 * The following image shows the nodes numbering used by this class. 
 * The weights (see getWeight()), 
 * and parametric coordinates (see getIsoParametricCoord()) are 
 * defined according to this node numbering. 
 * @IMAGE LinearQuadrangle4.png "Nodes numbering"
 *
 */
class MESHIVIZ_API MxQuadrangleCellExtract 
{
public:

  /**
  * Computes the iso parametric coordinates of the given point in the given cell with the given geometry.
  * As computing the iso parametric coordinates of a point needs the coordinates of the cell's nodes, 
  * the given quadrangleCell is assumed to contain 4 nodes. 
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
     meshGeometry.getCoord(quadrangleCell->getNodeIndex(i)) 
    @endverbatim
  * for each i in the range [0-3].
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] quadrangleCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  */
  static MbVec3d getIsoParametricCoord(const MiGeometryI& meshGeometry, const MiSurfaceCell* quadrangleCell, const MbVec3d &point);
  
  /**
  * Returns the iso parametric coordinates of one of the 4 nodes of a quadrangle cell.
  * This static method helps to implement the method MiCell::getIsoParametricCoord().
  * @param [in] nodeIndex Must be defined in the range [0-3]
  */
  static MbVec3d getIsoParametricCoord(size_t nodeIndex);

  /**
  * Gets the weights in the given cell of the given point. This static method 
  * helps to implement the method MiCell::getWeight(meshGeometry,point,weights) 
  * for a quadrangle cell. As computing the weights of a point
  * needs the coordinates of the cell's nodes, the given quadrangleCell is 
  * assumed to contain 4 nodes. 
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
     meshGeometry.getCoord(quadrangleCell->getNodeIndex(i)) 
    @endverbatim
  * for each i in the range [0-3].
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] quadrangleCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the 4 values weights[0-3]. 
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 4 (at least) before calling this method, using for instance
  *    the weights.resize(4)
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
  * @param[out] weights This method computes the 4 values weights[0-3].           
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 4 (at least) before calling this method, using for instance
  *    the weights::resize(4)
  */
  static void getWeight(const MbVec3d &ipcoord, std::vector<double>& weights)
  {
    double rm, sm;

    rm = 1. - ipcoord[0];
    sm = 1. - ipcoord[1];

    weights[0] = rm*sm;
    weights[1] = ipcoord[0]*sm;
    weights[2] = ipcoord[0]*ipcoord[1];
    weights[3] = rm*ipcoord[1];
  }

  /**
  * Gets the value of the derivatives of the shape functions (aka weights) at the point given by 
  * its iso parametric coordinates.
  * @param[in] ipcoord The iso parametric coordinates of the input point. The reference
  *            space for the iso parametric coordinates is assumed to be [0-1]. Thus any
  *            point inside the cell has iso parametric coordinates in the interval [0-1].
  * @param[out] derivs This method computes the 12 values derivs[0-11].   
  *    It assumes the derivs vector array has been already allocated.
  *    Its size must be set to 12 (at least) before calling this method, using for instance
  *    the derivs::resize(12)
  */
  static void getDerivs(const MbVec3d &ipcoord, std::vector<double>& derivs);

  /**
  * Checks if a point is inside or outside a quadrangle cell.
  * This static method helps to implement the method 
  * MiCell::isPointInsideCell(meshGeometry,point,weights) for a quadrangle cell.
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] quadrangleCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the 4 values weights[0-3] if the point is inside the cell. 
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 4 (at least) before calling this method, using for instance
  *    the weights::resize(4)
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
  * Gets the longest edge of a quadrangle cell
  */
  static double getLongestEdgeLength(const MiGeometryI& meshGeometry, const MiSurfaceCell* cell);

  /**
  * Gets the shortest edge of a quadrangle cell
  */
  static double getShortestEdgeLength(const MiGeometryI& meshGeometry, const MiSurfaceCell* cell);

protected:

  static bool initClass();
  static void exitClass();

  static bool   s_isInit;
  static double s_nodesIsoParametricCoords[4][3];
};

#endif 

