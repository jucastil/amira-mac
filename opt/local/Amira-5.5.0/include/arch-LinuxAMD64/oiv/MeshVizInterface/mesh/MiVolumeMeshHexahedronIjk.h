/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MiVolumeMeshHexahedronIjk_H
#define _MiVolumeMeshHexahedronIjk_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiMeshUnstructured.h>
#include <MeshVizInterface/mesh/MiMeshIjk.h>
#include <MeshVizInterface/mesh/topology/MiHexahedronTopologyExplicitIjk.h>

/**
* @DTEXT IJK Hexahedron volume mesh abstract interface.
* 
* @ingroup MeshIViz_Mesh
* 
* @DESCRIPTION
*    An IJK Hexahedron Volume mesh is similar to an MiMeshCurvilinear except that adjacent cells 
*    may have different nodes (identified by node indices). 
*    This type of mesh can be used to define "faults", as in a petroleum reservoir model. 
*
*    Cells must be defined explicitly as a set of hexahedrons where each node is given independently of the adjacent cells.  
*
*  @see MiVolumeMeshCurvilinear for IJK meshes where adjacent cells share the same points.
*  @see MiVolumeMeshVertexHexahedronIjk for IJK meshes where hexahedrons are defined by explicit vertices.
*  @see MbVolumeMeshHexahedronIjk for a basic implementation.
* 
*/
class MiVolumeMeshHexahedronIjk : virtual public MiMeshUnstructured, virtual public MiMeshIjk
{
public:
  /**
  * Returns the topology of this mesh.
  */
  virtual const MiHexahedronTopologyExplicitIjk& getTopology() const = 0;

  /**
  * @copydoc MiVolumeMeshUnstructured::getNewClone() const
  */
  virtual const MiVolumeMeshHexahedronIjk* getNewClone() const
  {
    throw MiAbstractMethodError("MiVolumeMeshHexahedronIjk::getNewClone()");
  }

protected://PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */
  virtual std::ostream& toStream(std::ostream& s) const
  {
    s << "#MiVolumeMeshHexahedronIjk" << std::endl;
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
