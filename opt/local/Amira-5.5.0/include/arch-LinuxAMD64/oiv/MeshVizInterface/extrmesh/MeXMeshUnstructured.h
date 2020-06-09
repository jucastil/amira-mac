/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeXMeshUnstructured_H
#define _MeXMeshUnstructured_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/geometry/MeXGeometryI.h>

/**
* @DTEXT Extracted unstructured mesh abstract interface.
* 
* @ingroup MeshIViz_ExtractedMesh
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
*    @see MiVolumeMeshUnstructuredIjk
* 
*/
class MeXMeshUnstructured : virtual public MiMeshUnstructured
{
public:
  /**
  * Returns the unstructured geometry of this mesh. 
  */
  virtual const MeXGeometryI& getGeometry() const = 0;
};

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
