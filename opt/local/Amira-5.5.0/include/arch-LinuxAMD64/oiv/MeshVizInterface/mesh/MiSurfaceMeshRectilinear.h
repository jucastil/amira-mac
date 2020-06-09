/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MISURFACEMESHRECTILINEAR_H
#define _MISURFACEMESHRECTILINEAR_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiMeshIj.h>
#include <MeshVizInterface/mesh/geometry/MiSurfaceGeometryRectilinear.h>

/**
* @DTEXT Rectilinear surface mesh abstract interface.
* 
* @ingroup MeshIViz_Mesh
* 
* @DESCRIPTION
*    This interface is similar to MiSurfaceMeshRegular except that the nodes are not equally spaced along each axis.
*    Nodes are defined by a set of NUMI points on I, NUMJ points on J. 
*    Thus each cell is still a parallelogram but its surface depends on the spacing between two consecutive values of I and J.
*
*    @note The virtual methods are the same as in the parent class. 
*    The RTTI system is used by some extraction algorithms to identify the mesh type in order to implement some specific 
*    optimization based on the properties described above. 
* 
*/
class MiSurfaceMeshRectilinear : virtual public MiMeshIj
{
public:
  /**
  * Returns the geometry of this mesh. 
  */
  virtual const MiSurfaceGeometryRectilinear& getGeometry() const = 0;

  /**
  * @copydoc MiVolumeMeshUnstructured::getNewClone() const
  */
  virtual const MiSurfaceMeshRectilinear* getNewClone() const
  {
    throw MiAbstractMethodError("MiSurfaceMeshRectilinear::getNewClone()");
  }

protected: //PROTECTED_TO_DOCUMENT
   /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */
  virtual std::ostream& toStream(std::ostream& s) const
  {
    s << "#SurfaceMeshRectilinear" << std::endl;
    s << getTopology() << std::endl;
    s << getGeometry() << std::endl;
    return s;
  }

};

#endif
