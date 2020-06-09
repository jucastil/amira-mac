/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeXVolumeMeshUnstructured_H
#define _MeXVolumeMeshUnstructured_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiVolumeMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/MeXMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/topology/MeXVolumeTopologyExplicitI.h>
#include <Inventor/STL/vector>



/**
* @DTEXT Extracted unstructured volume mesh abstract interface.
* 
* @ingroup MeshIViz_ExtractedMesh
* 
* @DESCRIPTION
*    This interface defines an extracted unstructured volume mesh. It can contain any type of 
*    volume cell, like tetrahedrons, hexahedrons etc.
* 
*/
class MeXVolumeMeshUnstructured : public MiVolumeMeshUnstructured, virtual public MeXMeshUnstructured
{
public:
  /**
  * Returns the topology of this mesh. 
  */
  virtual const MeXVolumeTopologyExplicitI& getTopology() const = 0;

  /**
  * Gets a new clone of this mesh. This method creates and returns a new instance
  * of the class of this object by copying all fields of this instance.
  * The application is responsible for deleting the new instance returned.
  * This method is not pure virtual because it is not always necessary to get
  * a copy of a mesh. However the mesh instances returned by any extraction 
  * method are always cloneable.
  * By default this method throws an exception of type MiAbstractMethodError.
  */
  virtual const MeXVolumeMeshUnstructured* getNewClone() const
  {
    throw MiAbstractMethodError("MeXVolumeMeshUnstructured::getNewClone()");
  }

};

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
