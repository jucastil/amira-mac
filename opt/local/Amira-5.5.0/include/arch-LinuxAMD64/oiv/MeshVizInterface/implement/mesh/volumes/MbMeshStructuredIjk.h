/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _MBMESHSTRUCTUREDIJK_H
#define _MBMESHSTRUCTUREDIJK_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#  pragma warning(disable:4251)
#endif

#include <MeshVizInterface/mesh/MiMeshIjk.h>
#include <MeshVizInterface/implement/mesh/MbMeshIjk.h>
#include <MeshVizInterface/implement/topology/MbTopologyIjk.h>

/**
 * @DTEXT class defining a structured volume mesh.
 * 
 * @ingroup MeshIViz_Implement_Mesh
 * 
 * @DESCRIPTION

 * 
 */

template <typename _ScalarT=double, typename _Vec3T=MbVec3d>
class MbMeshStructuredIjk : virtual public MiMeshIjk, public MbMeshIjk<_ScalarT,_Vec3T>
{
public:
  /** Constructor */
  MbMeshStructuredIjk(size_t numCellI, size_t numCellJ, size_t numCellK) 
    : m_topology(numCellI,numCellJ,numCellK) 
  {
  }

  virtual const MiTopologyIjk& getTopology() const
  {
    return m_topology;
  }

  /**
  * Defines dead cells
  */
  void setDeadCell(size_t i, size_t j, size_t k, bool isDead=true)
  {
    m_topology.setDeadFlag(i,j,k,isDead);
  }

protected:
  virtual std::ostream& toStream(std::ostream& s) const;

  MbTopologyIjk     m_topology;
};

//-----------------------------------------------------------------------------
template <typename _ScalarT, typename _Vec3T>
inline std::ostream& 
MbMeshStructuredIjk<_ScalarT,_Vec3T>::toStream(std::ostream& s) const
{
  MbMeshIjk<_ScalarT,_Vec3T>::toStream(s);
  return s;
}


#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
