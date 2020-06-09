/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIGEOMETRYREGULAR_H
#define _MIGEOMETRYREGULAR_H

#include <MeshVizInterface/mesh/geometry/MiGeometry.h>

/**
* @DTEXT Generic parallelepiped, rectangular or straight line geometry.
* 
* @ingroup MeshIViz_Mesh_Geometry
* 
* @DESCRIPTION
*    A generic abstract interface for a parallelepiped geometry,
*    a rectangle geometry or a straight line geometry.
*    The geometry is given by two points defining two extremities.
*    (see getMin() and getMax()).
* 
*/
class MiGeometryRegular : virtual public MiGeometry
{
protected://PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */  
  virtual std::ostream& toStream(std::ostream& s) const
  {
    s << "#MiGeometryRegular" << std::endl;
    s << "#Min :" << getMin() << std::endl;
    s << "#Max :" << getMax() << std::endl;
    return s;
  }
};

#endif
