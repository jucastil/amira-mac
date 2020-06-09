/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeXSurfaceGeometryRectilinear_H
#define _MeXSurfaceGeometryRectilinear_H

#include <MeshVizInterface/mesh/geometry/MiSurfaceGeometryRectilinear.h>

/**
* @DTEXT Generic extracted rectilinear surface geometry.
* 
* @ingroup MeshIViz_ExtractedMesh_Geometry
* 
* @DESCRIPTION
*    This interface is used by MeXSurfaceMeshRectilinear to access the geometry describing an extracted rectilinear surface mesh.
*
*    @note
*    The existing representation nodes that use this type of 
*    geometry currently only handle geometry on the XY, YZ or ZX plane even 
*    though getNormal() could define any plane for this geometry.
* 
*/
class MeXSurfaceGeometryRectilinear : public MiSurfaceGeometryRectilinear
{
public:

};

#endif
