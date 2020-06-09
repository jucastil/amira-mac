/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MxWedge15CellExtract_h
#define  _MxWedge15CellExtract_h

#include <MeshVizInterface/mesh/geometry/MiGeometryI.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/utility>

class MxTabOfMarchingCase;
class MiVolumeCell;

/**
* @DTEXT Utility class for wedge quadratic cells with 15 nodes.
* 
* @ingroup MeshIViz_Extract_Cell
* 
* @DESCRIPTION
*   Utility class that provides a static implementation of the MiVolumeCell's methods
*   for a quadratic wedge of 15 nodes. This class is provided to make easier the 
*   creation of a class that implements the MiVolumeCell interface for a quadratic
*    wedge of 15 nodes. 
*      - extraction of iso parametric coordinates in a wedge.
*        (see getIsoParametricCoord())
*      - extraction of the weights in a wedge.
*        (see getWeight())
*
*  ATTENTION: this class is not yet finished. When comparing with other 
*  MxXXXCellExtract, some methods are missing. Furthermore this class
*  is not fully tested.
*/
SoINTERNAL class MESHIVIZ_API MxWedge15CellExtract 
{
public:
  
  /**
  * Returns the iso parametric coordinates of the given point in the given cell with the given geometry
  */
  static MbVec3d getIsoParametricCoord(const MiGeometryI& meshGeometry, const MiVolumeCell* wedgeCell, const MbVec3d &point);

  /**
  * Gets the weights of a point in a wedge cell.
  * @see MiVolumeCell::getWeight
  */
  static void getWeight(const MiGeometryI& meshGeometry, const MiVolumeCell* wedgeCell, const MbVec3d &point, std::vector<double>& weights)
  {
    getWeight(getIsoParametricCoord(meshGeometry,wedgeCell,point),weights);
  }

  /**
  * Gets the weights in a wedge cell of a point defined by its iso parametric coordinates.
  */
  static void getWeight(const MbVec3d &ipcoord, std::vector<double>& weights);

  /**
  * Gets the derivs of the point given by its iso parametric coordinates.
  * @internal
  */
  static void getDerivs(const MbVec3d &ipcoord, std::vector<double>& derivs);

  /**
  * Checks if a point is inside the given wedge cell.
  */
  static bool isPointInsideCell(const MiGeometryI& meshGeometry, const MiVolumeCell* wedgeCell, const MbVec3d &point, std::vector<double>& weights)
  {
    MbVec3d pcoord = getIsoParametricCoord(meshGeometry,wedgeCell,point);
    bool inside = ( -1.E-5 < pcoord[0] &&  pcoord[0] < 1 + 1.E-5 &&
                    -1.E-5 < pcoord[1] &&  pcoord[1] < 1 + 1.E-5 &&
                    -1.E-5 < pcoord[2] &&  pcoord[2] < 1 + 1.E-5 &&
                    -1.E-5 < (pcoord[0]+pcoord[1]) &&  (pcoord[0]+pcoord[1]) < 1 + 1.E-5);
    if (inside)
      getWeight(pcoord,weights);
    return inside;
  }

protected:
  static bool initClass();
  static void exitClass();

  static bool            s_isInit;

  static size_t s_imat0[3][9];
  static size_t s_imat1[4][3]; 
  static size_t s_imat2[4][3]; 
  static size_t s_imat3[2][3]; 
  static size_t s_iperm[2][9]; 
};

#endif


