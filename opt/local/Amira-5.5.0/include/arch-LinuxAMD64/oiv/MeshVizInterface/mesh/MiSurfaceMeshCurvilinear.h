/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MISURFACEMESHCURVILINEAR_H
#define _MISURFACEMESHCURVILINEAR_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/geometry/MiGeometryIj.h>
#include <MeshVizInterface/mesh/MiMeshIj.h>

/**
* @DTEXT Curvilinear surface mesh abstract interface.
* 
* @ingroup MeshIViz_Mesh
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
class MiSurfaceMeshCurvilinear : virtual public MiMeshIj
{
public:
  /**
  * Returns the geometry of this mesh. 
  */
  virtual const MiGeometryIj& getGeometry() const = 0;

  /**
  * @copydoc MiVolumeMeshUnstructured::getNewClone() const
  */
  virtual const MiSurfaceMeshCurvilinear* getNewClone() const
  {
    throw MiAbstractMethodError("MiSurfaceMeshCurvilinear::getNewClone()");
  }


protected: //PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */
  virtual std::ostream& toStream(std::ostream& s) const
  {
    s << "#SurfaceMeshCurvilinear" << std::endl;
    s << getTopology() << std::endl;
    s << getGeometry() << std::endl;
    return s;
  }

};

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
