/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIVOLUMEMESHUNSTRUCTURED_H
#define _MIVOLUMEMESHUNSTRUCTURED_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/geometry/MiGeometryI.h>
#include <MeshVizInterface/mesh/MiMeshUnstructuredI.h>
#include <MeshVizInterface/mesh/topology/MiVolumeTopologyExplicitI.h>
#include <Inventor/STL/vector>



/**
* @DTEXT Unstructured volume mesh abstract interface.
* 
* @ingroup MeshIViz_Mesh
* 
* @DESCRIPTION
*    This interface defines an unstructured volume mesh. It can contain any type of 
*    volume cell, like tetrahedrons, hexahedrons etc.
* 
*/
class MiVolumeMeshUnstructured : virtual public MiMeshUnstructuredI
{
public:
  /**
  * Returns the topology of this mesh. 
  */
  virtual const MiVolumeTopologyExplicitI& getTopology() const = 0;

  /**
  * Gets a new clone of this mesh. This method creates and returns a new instance
  * of the class of this object by copying all fields of this instance.
  * The application is responsible for deleting the new instance returned.
  * This method is not pure virtual because it is not always necessary to get
  * a copy of a mesh. However the mesh instances returned by any extraction 
  * method are always cloneable.
  * By default this method throws an exception of type MiAbstractMethodError.
  */
  virtual const MiVolumeMeshUnstructured* getNewClone() const
  {
    throw MiAbstractMethodError("MiVolumeMeshUnstructured::getNewClone()");
  }

protected: //PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */
  virtual std::ostream& toStream(std::ostream& s) const 
  {
    s << "#MiVolumeMeshUnstructured" << std::endl;
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
