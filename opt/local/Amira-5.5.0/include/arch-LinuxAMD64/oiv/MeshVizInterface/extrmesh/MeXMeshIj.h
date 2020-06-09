/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeXMeshIj_H
#define _MeXMeshIj_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiMeshIj.h>
#include <MeshVizInterface/extrmesh/topology/MeXTopologyIj.h>

/**
* @DTEXT Extracted IJ surface mesh abstract interface.
* 
* @ingroup MeshIViz_ExtractedMesh
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
class MeXMeshIj : virtual public MiMeshIj
{
public:
  /**
  * Returns the topology of this mesh.
  */
  virtual const MeXTopologyIj& getTopology() const = 0;
};

#endif

