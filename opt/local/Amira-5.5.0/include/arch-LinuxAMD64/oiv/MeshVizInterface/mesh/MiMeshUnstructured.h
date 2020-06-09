/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIMESHUNSTRUCTURED_H
#define _MIMESHUNSTRUCTURED_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <Inventor/STL/vector>

#include <MeshVizInterface/mesh/MiMesh.h>
#include <MeshVizInterface/mesh/geometry/MiGeometryI.h>


/**
* @DTEXT Unstructured mesh abstract interface.
* 
* @ingroup MeshIViz_Mesh
* 
* @DESCRIPTION
*    This interface defines a unstructured mesh. All unstructured meshes 
*    have a common geometry interface: getCoord(i).
*    An unstructured mesh can be either a volume, a surface or a line.
*
*    @see MiMeshUnstructuredI
*    @see MiVolumeMeshUnstructured
*    @see MiSurfaceMeshUnstructured
*    @see MiLineMeshUnstructured
*    @see MiLineMeshCurvilinear
*    @see MiVolumeMeshHexahedronIjk
*    @see MiVolumeMeshUnstructuredIjk
* 
*/
class MiMeshUnstructured : virtual public MiMesh
{
public:
  /**
  * Returns the unstructured geometry of this mesh. 
  */
  virtual const MiGeometryI& getGeometry() const = 0;
};

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
