/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeXLineMeshUnstructured_H
#define _MeXLineMeshUnstructured_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiLineMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/MeXMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/topology/MeXLineTopologyExplicitI.h>

/**
* @DTEXT Extracted unstructured line mesh abstract interface.
* 
* @ingroup MeshIViz_ExtractedMesh
* 
* @DESCRIPTION
*    This interface defines an extracted unstructured line mesh. 
*    This is a list of MeXLineCell segments.   
* 
*/
class MeXLineMeshUnstructured : public MiLineMeshUnstructured, virtual public MeXMeshUnstructured
{
public:
  /**
  * Returns the topology of this mesh.
  */
  virtual const MeXLineTopologyExplicitI& getTopology() const = 0;

  /**
  * @copydoc MiVolumeMeshUnstructured::getNewClone() const
  */
  virtual const MeXLineMeshUnstructured* getNewClone() const
  {
    throw MiAbstractMethodError("MeXLineMeshUnstructured::getNewClone()");
  }

};

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
