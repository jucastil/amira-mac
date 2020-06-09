/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MILINEMESHCURVILINEAR_H
#define _MILINEMESHCURVILINEAR_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiMeshUnstructured.h>
#include <MeshVizInterface/mesh/topology/MiTopologyI.h>

/**
* @DTEXT Curvilinear Line mesh abstract interface.
* 
* @ingroup MeshIViz_Mesh
* 
* @DESCRIPTION
*    This interface specifies a line defined by a list of points connected by edges forming a broken line. 
*    Curvilinear Line meshes do not contain an explicit description for each cell as is the case for unstructured line meshes.
*
*/
class MiLineMeshCurvilinear : virtual public MiMeshUnstructured
{
public:
  /**
  * Returns the topology of this mesh.
  */
  virtual const MiTopologyI& getTopology() const = 0;

  /**
  * @copydoc MiVolumeMeshUnstructured::getNewClone()
  */
  virtual const MiLineMeshCurvilinear* getNewClone() const
  {
    throw MiAbstractMethodError("MiLineMeshCurvilinear::getNewClone()");
  }

protected: //PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */
  virtual std::ostream& toStream(std::ostream& s) const
  {
    size_t numCell = getTopology().getNumCells();
    s << "#num cell " << std::endl;
    s << numCell << std::endl;
    s << "#mesh geometry" << std::endl;
    if(numCell)
      for(size_t i=0; i<=getTopology().getNumCells();i++)
        s << i <<": " <<getGeometry().getCoord(i)<< std::endl;
    return s;
  }

};

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
