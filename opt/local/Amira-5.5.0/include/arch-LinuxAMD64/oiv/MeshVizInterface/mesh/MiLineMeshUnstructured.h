/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MILINEMESHUNSTRUCTURED_H
#define _MILINEMESHUNSTRUCTURED_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiMeshUnstructuredI.h>
#include <MeshVizInterface/mesh/topology/MiLineTopologyExplicitI.h>

/**
* @DTEXT Unstructured Line mesh abstract interface.
* 
* @ingroup MeshIViz_Mesh
* 
* @DESCRIPTION
*    This interface defines an unstructured line mesh. 
*    This is a list of MiLineCell segments.   
* 
*/
class MiLineMeshUnstructured : virtual public MiMeshUnstructuredI
{
public:
  /**
  * Returns the topology of this mesh.
  */
  virtual const MiLineTopologyExplicitI& getTopology() const = 0;

  /**
  * @copydoc MiVolumeMeshUnstructured::getNewClone() const
  */
  virtual const MiLineMeshUnstructured* getNewClone() const
  {
    throw MiAbstractMethodError("MiLineMeshUnstructured::getNewClone()");
  }

protected: //PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */
  virtual std::ostream& toStream(std::ostream& s) const
  {
    s << "#MiLineMeshUnstructured" << std::endl;
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
