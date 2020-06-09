/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MISURFACEGEOMETRYRECTILINEAR_H
#define _MISURFACEGEOMETRYRECTILINEAR_H

#include <MeshVizInterface/mesh/geometry/MiGeometry.h>

/**
* @DTEXT Generic rectilinear surface geometry.
* 
* @ingroup MeshIViz_Mesh_Geometry
* 
* @DESCRIPTION
*    This interface is used by MiSurfaceMeshRectilinear to access the geometry describing a rectilinear surface mesh.
*
*    @note
*    The existing representation nodes that use this type of 
*    geometry currently only handle geometry on the XY, YZ or ZX plane even 
*    though getNormal() could define any plane for this geometry.
* 
*/
class MiSurfaceGeometryRectilinear : virtual public MiGeometry
{
public:
  /**
  * Returns the i-th coordinate along the X axis.
  */
  virtual double getX(size_t i) const = 0;

  /**
  * Returns the j-th coordinate along the Y axis.
  */
  virtual double getY(size_t j) const = 0;

  /**
  * Returns the normal of the plane on which the rectilinear mesh is defined.
  * @return (0,0,1) by default (defining the plane XY).
  */
  virtual MbVec3d getNormal() const 
  {
    return MbVec3d(0,0,1);
  }

  /**
  * Returns the distance to the origin of the plane on which the rectilinear mesh is defined.
  * @return 0 by default.
  */
  virtual double getDistance() const 
  {
    return 0;
  }

};

#endif
