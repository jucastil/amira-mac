/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeXSurfaceMeshUnstructured_H
#define _MeXSurfaceMeshUnstructured_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiSurfaceMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/MeXMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/topology/MeXSurfaceTopologyExplicitI.h>

/**
* @DTEXT Extracted unstructured surface mesh abstract interface.
* 
* @ingroup MeshIViz_ExtractedMesh
* 
* @DESCRIPTION
*    This interface defines an extracted unstructured surface mesh. It can contain any type of 
*    surface cell, like triangle, quadrangle, etc...
* 
*/
class MeXSurfaceMeshUnstructured : public MiSurfaceMeshUnstructured, virtual public MeXMeshUnstructured
{
public:
  /**
  * Returns the topology of this mesh.
  */
  virtual const MeXSurfaceTopologyExplicitI& getTopology() const = 0;

  /**
  * @copydoc MiVolumeMeshUnstructured::getNewClone() const
  */
  virtual const MeXSurfaceMeshUnstructured* getNewClone() const
  {
    throw MiAbstractMethodError("MeXSurfaceMeshUnstructured::getNewClone()");
  }

};

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
