/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIGEOMETRYIJ_H
#define _MIGEOMETRYIJ_H

#include <MeshVizInterface/mesh/geometry/MiGeometry.h>

/**
* @DTEXT Generic geometry interface for structured surface meshes.
* 
* @ingroup MeshIViz_Mesh_Geometry
* 
* @DESCRIPTION
*    Generic geometry interface accessible via two indices.
*    This type of geometry is typically used by curvilinear surface mesh interfaces. 
* 
*/
class MiGeometryIj : virtual public MiGeometry
{
public:
  /**
  * Returns the coordinate (i,j) of this geometry.
  */
  virtual MbVec3d getCoord(size_t i, size_t j) const = 0;
};

#endif
