/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIVOLUMEMESHRECTILINEAR_H
#define _MIVOLUMEMESHRECTILINEAR_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiMeshIjk.h>
#include <MeshVizInterface/mesh/geometry/MiVolumeGeometryRectilinear.h>

/**
* @DTEXT Rectilinear volume mesh abstract interface.
* 
* @ingroup MeshIViz_Mesh
* 
* @DESCRIPTION
*    This interface is similar to MiVolumeMeshRegular except that the nodes are not equally spaced in I, J and K.
*    Nodes are defined by a set of NUMI points on I, NUMJ points on J and NUMK points on K. 
*    Thus each cell is still a parallelepiped but its volume depends on the spacing between two consecutive values of I,J and K.
*
*    @note The virtual methods are the same as in the parent class. 
*    The RTTI system is used by some extraction algorithms to identify the mesh type in order to implement some specific 
*    optimization based on the properties described above. 
* 
*/
class MiVolumeMeshRectilinear : virtual public MiMeshIjk
{
public:
  /**
  * Returns the geometry of this mesh. 
  */
  virtual const MiVolumeGeometryRectilinear& getGeometry() const = 0;

  /**
  * @copydoc MiVolumeMeshUnstructured::getNewClone() const
  */
  virtual const MiVolumeMeshRectilinear* getNewClone() const
  {
    throw MiAbstractMethodError("MiVolumeMeshRectilinear::getNewClone()");
  } 

protected: //PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */
  virtual std::ostream& toStream(std::ostream& s) const 
  { 
    s << "#MiVolumeMeshRectilinear" << std::endl;
    s << getTopology() << std::endl;
    s << getGeometry() << std::endl;
    return s;
  }

};

#endif
