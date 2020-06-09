/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MBVOLUMEMESHHEXAHEDRON_H
#define  _MBVOLUMEMESHHEXAHEDRON_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiVolumeMeshUnstructured.h>
#include <MeshVizInterface/mesh/topology/MiVolumeTopologyExplicitI.h>

#include <MeshVizInterface/implement/mesh/volumes/MbVolumeMeshUnstructured.h>
#include <MeshVizInterface/implement/topology/MbHexahedronCellsSet.h>
#include <MeshVizInterface/MbVec3.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/iostream>

/**
 * @DTEXT  Defines a mesh of hexahedrons.
 * 
 * @ingroup MeshIViz_Implement_Mesh
 * 
 * @DESCRIPTION

 * 
 */
template <typename _CoordT=MbVec3d, typename _ScalarT=double, typename _Vec3T=MbVec3d>
class MbVolumeMeshHexahedron : public MbVolumeMeshUnstructured<_CoordT,_ScalarT,_Vec3T>
{

public:

  /**
  * Constructor of an empty mesh. 
  */
  MbVolumeMeshHexahedron() {}


  /**
   * Constructor of a volume mesh. 
   */
  template <typename _Vec3Iter, typename _NodeIdIter>
  MbVolumeMeshHexahedron(_Vec3Iter beginCoord, _Vec3Iter endCoord, 
                          _NodeIdIter beginId, _NodeIdIter endId);

  /**
  * Sets a new topology
  */
  template <typename _NodeIdIter>
  void setTopology(_NodeIdIter beginId, _NodeIdIter endId)
  {
    m_topology.assign(beginId,endId);
  }


  virtual const MbHexahedronCellsSet& getTopology() const;

  /**
  * Defines dead cells
  */
  template <typename _BoolIter>
  void setDeadCells(_BoolIter beginId, _BoolIter endId)
  {
    m_topology.assignDeadFlags(beginId,endId);
  }

protected:
  virtual std::ostream& toStream(std::ostream& s) const;

  MbHexahedronCellsSet m_topology;
};


//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
template <typename _Vec3Iter, typename _NodeIdIter>
inline MbVolumeMeshHexahedron<_CoordT,_ScalarT,_Vec3T>::MbVolumeMeshHexahedron(
  _Vec3Iter beginCoord, _Vec3Iter endCoord, 
  _NodeIdIter beginId, _NodeIdIter endId
  ) :
   MbVolumeMeshUnstructured<_CoordT,_ScalarT,_Vec3T>(beginCoord,endCoord)
{
  setTopology(beginId,endId);
}


//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
inline const MbHexahedronCellsSet&
MbVolumeMeshHexahedron<_CoordT,_ScalarT,_Vec3T>::getTopology() const
{
  return m_topology;
}

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
inline std::ostream& 
MbVolumeMeshHexahedron<_CoordT,_ScalarT,_Vec3T>::toStream(std::ostream& s) const
{
  s << "# MbVolumeMeshHexahedron" << std::endl;
  // output the inherited geometry and dataset
  MbVolumeMeshUnstructured<_CoordT,_ScalarT,_Vec3T>::toStream(s);

  return s;
}

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif







