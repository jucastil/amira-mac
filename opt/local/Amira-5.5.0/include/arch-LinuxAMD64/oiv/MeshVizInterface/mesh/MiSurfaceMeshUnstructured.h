/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MISURFACEMESHUNSTRUCTURED_H
#define _MISURFACEMESHUNSTRUCTURED_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiMeshUnstructuredI.h>
#include <MeshVizInterface/mesh/topology/MiSurfaceTopologyExplicitI.h>

/**
* @DTEXT Unstructured surface mesh abstract interface.
* 
* @ingroup MeshIViz_Mesh
* 
* @DESCRIPTION
*    This interface defines a an unstructured surface mesh. It can contain any type of 
*    surface cell, like triangle, quadrangle, etc...
* 
*/
class MiSurfaceMeshUnstructured : virtual public MiMeshUnstructuredI
{
public:
  /**
  * Returns the topology of this mesh.
  */
  virtual const MiSurfaceTopologyExplicitI& getTopology() const = 0;

  /**
  * @copydoc MiVolumeMeshUnstructured::getNewClone() const
  */
  virtual const MiSurfaceMeshUnstructured* getNewClone() const
  {
    throw MiAbstractMethodError("MiSurfaceMeshUnstructured::getNewClone()");
  }

protected: //PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */
  virtual std::ostream& toStream(std::ostream& s) const 
  {
    s << "#SurfaceMeshUnstructured" << std::endl;
    s << "#Geometry I" << std::endl;
    for(size_t i=getTopology().getBeginNodeId(); i<getTopology().getEndNodeId(); ++i)
      s << i << ": " << getGeometry().getCoord(i) << std::endl;
    s << getTopology() << std::endl;
    return s;
  }

};

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
