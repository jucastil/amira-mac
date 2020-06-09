/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeXSurfaceCell_H
#define _MeXSurfaceCell_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/cell/MiSurfaceCell.h>
#include <MeshVizInterface/extrmesh/cell/MeXCell.h>

/**
* @DTEXT  Defines an abstract cell of an extracted surface mesh.
* 
* @ingroup MeshIViz_ExtractedMesh_Cell
* 
* @DESCRIPTION
*    A surface cell is a polygon element that connects adjacent nodes of a surface mesh.
* 
*/

class MESHIVIZ_API MeXSurfaceCell : public MiSurfaceCell
{
public:
  /**
  * Gets the area of the cell.
  * This method is not pure virtual because it is not used by 
  * extraction classes. However using this method will generate an exception. 
  * An application does not need to override this method if not used.
  * 
  * @param[in] meshGeometry The geometry of the mesh. Used to retrieve the node coordinates
  * of this cell.
  */
  virtual double getArea(const MiGeometryI* UNREF_PARAM(meshGeometry)) const 
  {
    throw MiAbstractMethodError("MeXSurfaceCell::getArea(const MiGeometryI* meshGeometry)");
  }

  /**
  * Gets the unit normal vector to the surface's plane.
  * This method is not pure virtual because it is not used by 
  * extraction classes. However using this method will generate an exception. 
  * An application does not need to override this method if not used.
  * 
  * @param[in] meshGeometry The geometry of the mesh. Used to retrieve the node coordinates
  * of this cell.
  */
  virtual MbVec3d getNormal(const MiGeometryI* UNREF_PARAM(meshGeometry)) const 
  {
    throw MiAbstractMethodError("MeXSurfaceCell::getNormal(const MiGeometryI* meshGeometry)");
  }

};

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif

