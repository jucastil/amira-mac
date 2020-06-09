/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (Fev 2011)
**=======================================================================*/
#ifndef  _MbLineMeshCurvilinear_H
#define  _MbLineMeshCurvilinear_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiLineMeshCurvilinear.h>
#include <MeshVizInterface/implement/mesh/MbMesh.h>
#include <MeshVizInterface/implement/topology/MbLineTopologyI.h>
#include <MeshVizInterface/MbVec3.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/iostream>

/**
 * @DTEXT  Defines a curvilinear mesh of lines.
 * 
 * @ingroup MeshIViz_Implement_Mesh
 * 
 * @DESCRIPTION

 * 
 */
template <typename _CoordT=MbVec3d, typename _ScalarT=double, typename _Vec3T=MbVec3d>
class MbLineMeshCurvilinear : virtual public MiLineMeshCurvilinear, public MbMesh<_CoordT,_ScalarT,_Vec3T>
{

public:
  /**
   * Constructor of a line mesh. 
   */
  template <typename _Vec3Iter>
  MbLineMeshCurvilinear(_Vec3Iter beginCoord, _Vec3Iter endCoord);

  /**
  * Defines dead cells
  */
  template <typename _BoolIter>
  void setDeadCells(_BoolIter beginId, _BoolIter endId)
  {
    m_topology.assignDeadFlags(beginId,endId);
  }

  virtual const MiTopologyI& getTopology() const;

protected:
  virtual std::ostream& toStream(std::ostream& s) const;

  MbLineTopologyI m_topology;
};


//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
template <typename _Vec3Iter>
inline MbLineMeshCurvilinear<_CoordT,_ScalarT,_Vec3T>::MbLineMeshCurvilinear(
  _Vec3Iter beginCoord, _Vec3Iter endCoord
  ) :
   MbMesh<_CoordT,_ScalarT,_Vec3T>(beginCoord,endCoord),
   m_topology(std::distance(beginCoord,endCoord)-1)
{
}


//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
inline const MiTopologyI&
MbLineMeshCurvilinear<_CoordT,_ScalarT,_Vec3T>::getTopology() const
{
  return m_topology;
}

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
inline std::ostream& 
MbLineMeshCurvilinear<_CoordT,_ScalarT,_Vec3T>::toStream(std::ostream& s) const
{
  s << "# MbLineMeshCurvilinear " << std::endl;

  MiLineMeshCurvilinear::toStream(s);
  MbMesh<_CoordT,_ScalarT,_Vec3T>::toStream(s);

  return s;
}

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif







