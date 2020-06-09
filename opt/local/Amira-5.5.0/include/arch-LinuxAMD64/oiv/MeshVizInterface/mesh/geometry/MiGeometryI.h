/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIGEOMETRYI_H
#define _MIGEOMETRYI_H

#include <MeshVizInterface/mesh/geometry/MiGeometry.h>

/**
* @DTEXT Generic geometry interface for unstructured meshes.
* 
* @ingroup MeshIViz_Mesh_Geometry
* 
* @DESCRIPTION
*    Generic geometry interface accessible via one index.
*    This type of geometry is typically used by unstructured mesh interfaces. 
* 
*/
class MESHIVIZ_API MiGeometryI : virtual public MiGeometry
{
public:
  /**
  * Returns the i-th coordinate of this geometry.
  */
  virtual MbVec3d getCoord(size_t i) const = 0;
};


#endif 
