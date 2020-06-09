/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIMESHREGULAR_H
#define _MIMESHREGULAR_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiMesh.h>
#include <MeshVizInterface/mesh/geometry/MiGeometryRegular.h>

/**
* @DTEXT Regular mesh abstract interface.
* 
* @ingroup MeshIViz_Mesh
* 
* @DESCRIPTION
*    This interface defines a regular mesh. 
*    A regular mesh has a geometry defined by a bounding box.
*    A regular mesh could be either a volume (a parallelepiped)
*    a surface (a rectangle) or a straight line.
* 
*    @see MiVolumeMeshRegular
*    @see MiLineMeshRegular
*    @see MiSurfaceMeshRegular
*
*/
class MiMeshRegular : virtual public MiMesh
{
public:
  /**
  * Returns the geometry of this mesh. 
  * A MiGeometryRegular represents a regular geometry fully defined by its min and max points.
  */
  virtual const MiGeometryRegular& getGeometry() const = 0;

};

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
