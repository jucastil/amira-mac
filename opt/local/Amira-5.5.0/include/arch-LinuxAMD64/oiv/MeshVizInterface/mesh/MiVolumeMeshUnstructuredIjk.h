/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIVOLUMEMESHUNSTRUCTUREDIJK_H
#define _MIVOLUMEMESHUNSTRUCTUREDIJK_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiMeshUnstructured.h>
#include <MeshVizInterface/mesh/MiMeshIjk.h>
#include <MeshVizInterface/mesh/topology/MiVolumeTopologyExplicitIjk.h>

/**
* @DTEXT IJK Unstructured volume mesh abstract interface.
* 
* @ingroup MeshIViz_Mesh
* 
* @deprecated use MiVolumeMeshHexahedronIjk instead.
* @DEPRECATED_SINCE_OIV 8.0
*
* @DESCRIPTION
*    An IJK Unstructured Volume mesh is a similar to a MiMeshCurvilinear except that adjacent cells 
*    may have different nodes. This type of mesh can be used to define "faults", as in a
*    reservoir model. 
*    Cells must be defined explicitly as a set of hexahedron where each node is given independently of adjacent cells.  
*
*    @see MiVolumeMeshRectilinear for IJK meshes where adjacent cells share the same points.
* 
*/
class MiVolumeMeshUnstructuredIjk : virtual public MiMeshUnstructured, virtual public MiMeshIjk
{
public:
  /**
  * Returns the topology of this mesh.
  */
  virtual const MiVolumeTopologyExplicitIjk& getTopology() const = 0;

  /**
  * @copydoc MiVolumeMeshUnstructured::getNewClone() const
  */
  virtual const MiVolumeMeshUnstructuredIjk* getNewClone() const
  {
    throw MiAbstractMethodError("MiVolumeMeshUnstructuredIjk::getNewClone()");
  }

protected://PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */
  virtual std::ostream& toStream(std::ostream& s) const
  {
    s << "#MiVolumeMeshUnstructuredIjk" << std::endl;
    s << getTopology() << std::endl;
    s << "#mesh geometry" << std::endl;
    for(size_t i=getTopology().getBeginNodeId(); i<getTopology().getEndNodeId(); ++i)
      s << i << ": " << getGeometry().getCoord(i) << std::endl;
    return s;
  }

};

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
