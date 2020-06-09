/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIMESH_H
#define _MIMESH_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/MiAbstractMethodError.h>
#include <MeshVizInterface/mesh/topology/MiTopologyIjk.h>

/**
* @DTEXT Abstract mesh interface.
* 
* @ingroup MeshIViz_Mesh
* 
* @DESCRIPTION
*    This interface defines an abstract mesh. 
*    An abstract mesh organizes the domain by using a geometry and a
*    topology. Thus, any implementing class of MiMesh must implement
*    the methods getGeometry() and getTopology().
*    
*    @see MiLineMeshRegular
*    @see MiLineMeshCurvilinear
*    @see MiLineMeshUnstructured 
*    @see MiSurfaceMeshRegular
*    @see MiSurfaceMeshRectilinear
*    @see MiSurfaceMeshCurvilinear
*    @see MiSurfaceMeshUnstructured 
*    @see MiVolumeMeshRegular
*    @see MiVolumeMeshRectilinear
*    @see MiVolumeMeshCurvilinear
*    @see MiVolumeMeshUnstructured 
*    @see MiVolumeMeshHexahedronIjk
*    @see MiVolumeMeshVertexHexahedronIjk
*
*/
class MiMesh
{
public:
  virtual ~MiMesh() {}

  /**
  * Outputs the mesh to a stream using the toStream protected method implemented in all derived classes.
  */
  friend std::ostream& operator << (std::ostream& s, const MiMesh& mesh)
  {
    return mesh.toStream(s);
  }

protected: //PROTECTED_TO_DOCUMENT
  /**
  * Performs an output operation on a stream which is returned afterward.
  * This method is protected since only called by the output operator <<.
  * This method is not pure virtual and output by default the geometry and
  * topology of a mesh. Whenever a different output is needed, this method
  * can be implemented in the subclass to get a different output format.
  * No std::ostream& operator << needs to be defined in any subclass.
  * This allows you to benefit from the virtual inheritance when using the
  * output operator on an abstract class.
  */
  virtual std::ostream& toStream(std::ostream& s) const = 0;

};

#endif
