/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeXSurfaceMeshCurvilinear_H
#define _MeXSurfaceMeshCurvilinear_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/extrmesh/geometry/MeXGeometryIj.h>
#include <MeshVizInterface/extrmesh/MeXMeshIj.h>
#include <MeshVizInterface/mesh/MiSurfaceMeshCurvilinear.h>

/**
* @DTEXT Extracted curvilinear surface mesh abstract interface.
* 
* @ingroup MeshIViz_ExtractedMesh
* 
* @DESCRIPTION
*    A Curvilinear Surface mesh is similar to a MiMeshIJ except that nodes are 
*    organized in a (NUMI+1,NUMJ+1) array where they can be accessed by (i,j) indices.
*    So each node located inside the mesh (not on a border) is shared by four cells. 
*    However, the nodes are not evenly spaced as they can be in the MiSurfaceMeshRectilinear or MiSurfaceMeshRegular.
*
*    @note Notice that, the virtual methods are the same as in the parent class. 
*    The RTTI system is used by some extraction algorithms to identify the mesh type in order to implement some specific 
*    optimization based on the properties described above. 
* 
*/
class MeXSurfaceMeshCurvilinear : public MiSurfaceMeshCurvilinear, virtual public MeXMeshIj
{
public:
  /**
  * Returns the geometry of this mesh. 
  */
  virtual const MeXGeometryIj& getGeometry() const = 0;

  /**
  * @copydoc MiVolumeMeshUnstructured::getNewClone() const
  */
  virtual const MeXSurfaceMeshCurvilinear* getNewClone() const
  {
    throw MiAbstractMethodError("MeXSurfaceMeshCurvilinear::getNewClone()");
  }

};

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
