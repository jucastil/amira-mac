/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIGEOMETRYIJK_H
#define _MIGEOMETRYIJK_H

#include <MeshVizInterface/mesh/geometry/MiGeometry.h>

/**
* @DTEXT Generic geometry interface for structured volume meshes.
* 
* @ingroup MeshIViz_Mesh_Geometry
* 
* @DESCRIPTION
*    Generic geometry interface accessible via three indices.
*    This type of geometry is typically used by structured volume meshes interfaces. 
* 
*/
class MESHIVIZ_API MiGeometryIjk : virtual public MiGeometry
{
public:
  /**
  * Returns the coordinate (i,j,k) of this geometry.
  */
  virtual MbVec3d getCoord(size_t i, size_t j, size_t k) const = 0;
};

#endif
