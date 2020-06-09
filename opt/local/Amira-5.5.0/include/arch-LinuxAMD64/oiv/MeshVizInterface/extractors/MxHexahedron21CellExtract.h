/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MxHexahedron21CellExtract_h
#define  _MxHexahedron21CellExtract_h

#include <MeshVizInterface/mesh/geometry/MiGeometryI.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/utility>

class MiVolumeCell;

/**
 * @DTEXT Utility class for quadratic hexahedron cells with 21 nodes.
 * 
 * @ingroup MeshIViz_Extract_Cell
 * 
 * @DESCRIPTION
 *   Utility class that provides a static implementation of the MiVolumeCell's methods
 *   for a quadratic hexahedron of 21 nodes. This class is provided to make easier the 
 *   creation of a class that implements the MiVolumeCell interface for a quadratic
 *    hexahedron of 21 nodes. 
 *      - extraction of iso parametric coordinates in an hexahedron
 *        (see getIsoParametricCoord())
 *      - extraction of the weights in a hexahedron
 *        (see getWeight())
 *
 *  ATTENTION: this class is not yet finished. When comparing with other 
 *  MxXXXCellExtract, some methods are missing. Furthermore this class
 *  is not fully tested.
 */
SoINTERNAL class MESHIVIZ_API MxHexahedron21CellExtract 
{
public:

  /**
  * Returns the iso parametric coordinates of the given point in the given cell with the given geometry
  */
  static MbVec3d getIsoParametricCoord(const MiGeometryI& meshGeometry, const MiVolumeCell* hexahedronCell, const MbVec3d &point);
  
  /**
  * Returns the iso parametric coordinates of the given node in the given cell (hexacell)
  */
  static MbVec3d getIsoParametricCoord(size_t nodeIndex);

  /**
  * Gets the weights of a point in a cell.
  * @see MiVolumeCell::getWeight
  */
  static void getWeight(const MiGeometryI& meshGeometry, const MiVolumeCell* hexahedronCell, const MbVec3d &point, std::vector<double>& weights)
  {
    MbVec3d ipcoord = getIsoParametricCoord(meshGeometry,hexahedronCell,point);
    getWeight(ipcoord,weights);
  }

  /**
  * Gets the weights of a point defined by its iso parametric coordinates in an hexahedron cell.
  */
  static void getWeight(const MbVec3d &ipcoord, std::vector<double>& weights);

  /**
  * Gets the derivs of the point given by its iso parametric coordinates.
  * @internal
  */
  static void getDerivs(const MbVec3d &ipcoord, std::vector<double>& derivs);

  /**
  * Checks if a point is inside the given hexahedron cell.
  */
  static bool isPointInsideCell(const MiGeometryI& meshGeometry, const MiVolumeCell* hexahedronCell, const MbVec3d &point, std::vector<double>& weights)
  {
    MbVec3d pcoord = getIsoParametricCoord(meshGeometry,hexahedronCell,point);
    bool inside = ( -1.E-5 < pcoord[0] &&  pcoord[0] < 1 + 1.E-5 &&
                    -1.E-5 < pcoord[1] &&  pcoord[1] < 1 + 1.E-5 &&
                    -1.E-5 < pcoord[2] &&  pcoord[2] < 1 + 1.E-5 );
    if (inside)
      getWeight(pcoord,weights);
    return inside;
  }

  /**
  * Get a triangulation of a facet of this quadratic hexahedron. 
  * @param[in] facet number of the facet. (where: 0 <= face < getNumFacets() ).
  * @param[out] triangleNodeIds  sub triangle node id (where: 0 <= triangleNodeIds[i] < getNumNodes() for each i).
  * @return the number of sub triangles in the facet of the is cell.
  */
  static size_t getSubTriangleNodesIndex(size_t facet, std::vector<size_t>& triangleNodeIds)  
  {
    triangleNodeIds.assign(s_subFacetNode[facet],s_subFacetNode[facet]+18);
    return 6;
  }

protected:

  static bool initClass();
  static void exitClass();

  static bool   s_isInit;
  static double s_nodesIsoParametricCoords[21][3];
  static size_t s_subFacetNode[6][18];
  static size_t s_iperm[2][12];

};

#endif 

