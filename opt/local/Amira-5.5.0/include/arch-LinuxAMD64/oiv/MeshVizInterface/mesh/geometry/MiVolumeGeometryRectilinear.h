/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIVOLUMEGEOMETRYRECTILINEAR_H
#define _MIVOLUMEGEOMETRYRECTILINEAR_H

#include <MeshVizInterface/mesh/geometry/MiGeometry.h>

/**
* @DTEXT Generic rectilinear volume geometry.
* 
* @ingroup MeshIViz_Mesh_Geometry
* 
* @DESCRIPTION
*    This interface is used by MiVolumeMeshRectilinear to access the geometry describing a rectilinear volume mesh.
* 
*/
class MiVolumeGeometryRectilinear : virtual public MiGeometry
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
  * Returns the k-th coordinate along the Z axis.
  */
  virtual double getZ(size_t k) const = 0;
};

#endif
