/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MiMeshIjk_H
#define _MiMeshIjk_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiMesh.h>
#include <MeshVizInterface/mesh/topology/MiTopologyIjk.h>

/**
* @DTEXT IJK volume mesh abstract interface.
* 
* @ingroup MeshIViz_Mesh
* 
* @DESCRIPTION
*    This interface defines an IJK volume mesh. All IJK meshes 
*    have a common topology interface to get the number of cells: getNumCellsI(),
*    getNumCellsJ() and getNumCellsK().
* 
*    @see MiVolumeMeshRectilinear
*    @see MiVolumeMeshCurvilinear
*    @see MiVolumeMeshRegular
*    @see MiVolumeMeshHexahedronIjk
*    @see MiVolumeMeshVertexHexahedronIjk
* 
*/
class MiMeshIjk : virtual public MiMesh
{
public:

  /**
  * Hint about data organization in memory. 
  * This information aims at optimizing the data traversal for extractors.
  * Enum values covering all possible cases for internal data layout in memory.  
  * For instance LAYOUT_KJI means that: 
  *   - data (i+1,j,k) is consecutive in memory to the data (i,j,k) and,
  *   - the row of data (j+1,k) is consecutive in memory to the row of data (j,k) and,
  *   - the slice of data (k+1) is consecutive in memory to the slice of data (k) 
  * The fastest way to go through the data with such layout is to perform the following triple loop
  * @verbatim
    for each k with 0 <= k < numK
      for each j with 0 <= j < numJ
        for each i with 0 <= i < numI
    @endverbatim
  */
  enum StorageLayout { 
    LAYOUT_IJK, LAYOUT_IKJ,
    LAYOUT_JKI, LAYOUT_JIK, 
    LAYOUT_KJI, LAYOUT_KIJ,
    LAYOUT_UNKNOWN
  } ;

  /**
  * Returns the topology of this mesh.
  */
  virtual const MiTopologyIjk& getTopology() const = 0;

protected: //PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */
  virtual std::ostream& toStream(std::ostream& s) const 
  { 
    s << "#mesh topology" << std::endl;
    s << "#numCellsI" << std::endl;
    s << getTopology().getNumCellsI() << std::endl;
    s << "#numCellsJ" << std::endl;
    s << getTopology().getNumCellsJ() << std::endl;
    s << "#numCellsK" << std::endl;
    s << getTopology().getNumCellsK() << std::endl;
    return s;
  }

};

#endif
