/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBVOLUMEMESHUNSTRUCTUREDIJK_H
#define _MBVOLUMEMESHUNSTRUCTUREDIJK_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiVolumeMeshUnstructuredIjk.h>
#include <MeshVizInterface/mesh/geometry/MiGeometryI.h>

#include <MeshVizInterface/implement/mesh/MbMesh.h>
#include <MeshVizInterface/implement/mesh/MbMeshIjk.h>
#include <MeshVizInterface/implement/geometry/MbMeshGeometry.h>
#include <MeshVizInterface/implement/topology/MbHexahedronCellsSetIjk.h>

#include <MeshVizInterface/MbVec3.h>
#include <Inventor/STL/vector>
#include <Inventor/STL/iostream>

/**
 * @DTEXT Abstract class to define an unstructured mesh .
 * 
 * @ingroup MeshIViz_Implement_Mesh
 * 
 * @DESCRIPTION

 * 
 */
template <typename _CoordT=MbVec3d, typename _ScalarT=double, typename _Vec3T=MbVec3d>
class MbVolumeMeshUnstructuredIjk : virtual public MiVolumeMeshUnstructuredIjk, public MbMesh<_CoordT,_ScalarT,_Vec3T>,
                                    public MbMeshIjk<_ScalarT,_Vec3T>
{

public:
  const MiVolumeTopologyExplicitIjk& getTopology() const 
  {
    return *m_topology;
  }

  /**
  * Sets a new topology
  */
  template <typename _NodeIdIter>
  void setCellNodeIndexes(size_t i, size_t j, size_t k,
                          _NodeIdIter beginId, _NodeIdIter endId)
  {
    m_topology->setCellNodeInds(i,j,k,beginId,endId);
  }

  /**
  * Defines dead cells
  */
  void setDeadCell(size_t i, size_t j, size_t k, bool isDead=true)
  {
    m_topology->setDeadFlag(i,j,k,isDead);
  }

protected:
  // abstract class
  MbVolumeMeshUnstructuredIjk() {}
  template <typename _CoordIter>
  MbVolumeMeshUnstructuredIjk(_CoordIter beginCoord, _CoordIter endCoord);
  /**
  * Defines a specialized output on stream 
  */
  virtual std::ostream& toStream(std::ostream& s) const;
  
  MbVolumeTopologyExplicitIjk* m_topology;
};

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
template <typename _CoordIter>
inline
MbVolumeMeshUnstructuredIjk<_CoordT,_ScalarT,_Vec3T>::MbVolumeMeshUnstructuredIjk(
  _CoordIter beginCoord, _CoordIter endCoord) : MbMesh<_CoordT,_ScalarT,_Vec3T>(beginCoord,endCoord)
{
}



//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
inline std::ostream&
MbVolumeMeshUnstructuredIjk<_CoordT,_ScalarT,_Vec3T>::toStream(std::ostream& s) const
{
  MiVolumeMeshUnstructuredIjk::toStream(s);
  MbMesh<_CoordT,_ScalarT,_Vec3T>::toStream(s);
  MbMeshIjk<_ScalarT,_Vec3T>::toStream(s);
  return s;
}

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif 







