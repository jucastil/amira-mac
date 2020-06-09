/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeXSurfaceMeshRectilinear_H
#define _MeXSurfaceMeshRectilinear_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/extrmesh/MeXMeshIj.h>
#include <MeshVizInterface/mesh/MiSurfaceMeshRectilinear.h>
#include <MeshVizInterface/extrmesh/geometry/MeXSurfaceGeometryRectilinear.h>

/**
* @DTEXT Extracted rectilinear surface mesh abstract interface.
* 
* @ingroup MeshIViz_ExtractedMesh
* 
* @DESCRIPTION
*    This interface is similar to MiSurfaceMeshRegular except that the nodes are not equally spaced along each axis.
*    Nodes are defined by a set of NUMI points on I, NUMJ points on J. 
*    Thus each cell is still a parallelogram but its surface depends on the spacing between two consecutive values of I and J.
*    @note The virtual methods are the same as in the parent class. 
*    The RTTI system is used by some extraction algorithms to identify the mesh type in order to implement some specific 
*    optimization based on the properties described above. 
* 
*/
class MeXSurfaceMeshRectilinear : public MiSurfaceMeshRectilinear, virtual public MeXMeshIj
{
public:
  /**
  * Returns the geometry of this mesh. 
  */
  virtual const MeXSurfaceGeometryRectilinear& getGeometry() const = 0;

  /**
  * @copydoc MiVolumeMeshUnstructured::getNewClone() const
  */
  virtual const MeXSurfaceMeshRectilinear* getNewClone() const
  {
    throw MiAbstractMethodError("MeXSurfaceMeshRectilinear::getNewClone()");
  }

};

#endif
