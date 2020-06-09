/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIVOLUMEMESHCURVILINEAR_H
#define _MIVOLUMEMESHCURVILINEAR_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiMeshIjk.h>
#include <MeshVizInterface/mesh/geometry/MiGeometryIjk.h>

/**
* @DTEXT Curvilinear volume mesh abstract interface.
* 
* @ingroup MeshIViz_Mesh
* 
* @DESCRIPTION
*    A Curvilinear volume mesh is similar to a MiVolumeMeshIJK except that nodes are 
*    organized in a (NUMI+1,NUMJ+1,NUMK+1) array where they can be accessed by (i,j,k) indices.
*    So each node located inside the mesh (not on a border) is shared by eight cells. 
*    However, the nodes are not evenly spaced as they can be in the MiVolumeMeshRectilinear or MiVolumeMeshRegular.
*
*    @see MiVolumeMeshUnstructuredIJK for IJK meshes where adjacent cells do not share points.
*    @note Notice that, the virtual methods are the same as in the parent class. 
*    The RTTI system is used by some extraction algorithms to identify the mesh type in order to implement some specific 
*    optimization based on the properties described above. 
* 
*/
class MiVolumeMeshCurvilinear : virtual public MiMeshIjk
{
public:
  /**
  * Returns the geometry of this mesh. 
  */
  virtual const MiGeometryIjk& getGeometry() const = 0;

  /**
  * @copydoc MiVolumeMeshUnstructured::getNewClone() const
  */
  virtual const MiVolumeMeshCurvilinear* getNewClone() const
  {
    throw MiAbstractMethodError("MiVolumeMeshCurvilinear::getNewClone()");
  } 

protected: //PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */
  virtual std::ostream& toStream(std::ostream& s) const 
  { 
    s << "#MiVolumeMeshCurvilinear" << std::endl;
    s << getTopology() << std::endl;
    s << getGeometry() << std::endl;
    return s;
  }
};

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
