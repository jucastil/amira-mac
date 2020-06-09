/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeXGeometryRegular_H
#define _MeXGeometryRegular_H

#include <MeshVizInterface/mesh/geometry/MiGeometryRegular.h>

/**
* @DTEXT Extracted generic parallelepiped, rectangular or straight line geometry.
* 
* @ingroup MeshIViz_ExtractedMesh_Geometry
* 
* @DESCRIPTION
*    A generic abstract interface for a parallelepiped geometry,
*    a rectangle geometry or a straight line geometry.
*    The geometry is given by two points defining two extremities.
*    (see getMin() and getMax()).
* 
*/
class MeXGeometryRegular : public MiGeometryRegular
{

};

#endif
