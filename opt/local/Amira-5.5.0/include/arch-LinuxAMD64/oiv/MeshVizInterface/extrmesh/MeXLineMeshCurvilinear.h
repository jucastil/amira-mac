/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeXLineMeshCurvilinear_H
#define _MeXLineMeshCurvilinear_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiLineMeshCurvilinear.h>
#include <MeshVizInterface/extrmesh/MeXMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/topology/MeXTopologyI.h>

/**
* @DTEXT Extracted curvilinear line mesh abstract interface.
* 
* @ingroup MeshIViz_ExtractedMesh
* 
* @DESCRIPTION
*    This interface defines a line defined by a list of points connected by edges forming a broken line. 
*    Curvilinear Line meshes do not contain an explicit description for each cell as it is the case for unstructured line meshes.
*
*/
class MeXLineMeshCurvilinear : public MiLineMeshCurvilinear, virtual public MeXMeshUnstructured
{
public:
  /**
  * Returns the topology of this mesh.
  */
  virtual const MeXTopologyI& getTopology() const = 0;

  /**
  * @copydoc MiVolumeMeshUnstructured::getNewClone()
  */
  virtual const MeXLineMeshCurvilinear* getNewClone() const
  {
    throw MiAbstractMethodError("MeXLineMeshCurvilinear::getNewClone()");
  }

};

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
