/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIMESHIJ_H
#define _MIMESHIJ_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiMesh.h>
#include <MeshVizInterface/mesh/topology/MiTopologyIj.h>

/**
* @DTEXT IJ surface mesh abstract interface.
* 
* @ingroup MeshIViz_Mesh
* 
* @DESCRIPTION
*    This interface defines an IJ surface mesh. All IJ meshes 
*    have a common topology interface to get the number of cells: getNumCellsI(),
*    and getNumCellsJ().
*
*    @see MiSurfaceMeshRegular
*    @see MiSurfaceMeshCurvilinear
*    @see MiSurfaceMeshRectilinear
* 
*/
class MiMeshIj : virtual public MiMesh
{
public:
  /**
  * Returns the topology of this mesh.
  */
  virtual const MiTopologyIj& getTopology() const = 0;
};

#endif

