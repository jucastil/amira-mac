/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MBSURFACEMESHPOLYGON_H
#define  _MBSURFACEMESHPOLYGON_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/implement/mesh/surfaces/MbSurfaceMeshUnstructured.h>
#include <MeshVizInterface/implement/topology/MbPolygonCellsSet.h>
#include <MeshVizInterface/MbVec3.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/iostream>

/**
 * @DTEXT  Defines a mesh of polygons.
 * 
 * @ingroup MeshIViz_Implement_Mesh
 * 
 * @DESCRIPTION

 * 
 */
template <typename _CoordT=MbVec3d, typename _ScalarT=double, typename _Vec3T=MbVec3d>
class MbSurfaceMeshPolygon : public MbSurfaceMeshUnstructured<_CoordT,_ScalarT,_Vec3T>
{

public:

  /**
   * Constructor of a surface mesh. 
   */
  template <typename _Vec3Iter, typename _NodeIdIter, typename _numNodeIter>
  MbSurfaceMeshPolygon(_Vec3Iter beginCoord, _Vec3Iter endCoord, 
                       _NodeIdIter beginId, _NodeIdIter endId,
                       _numNodeIter beginNum, _numNodeIter endNum);

  /**
  * Sets a new topology
  */
  template <typename _NodeIdIter, typename _numNodeIter>
  void setTopology(_NodeIdIter beginId, _NodeIdIter endId,
                   _numNodeIter beginNum, _numNodeIter endNum);

  /**
  * Defines dead cells
  */
  template <typename _BoolIter>
  void setDeadCells(_BoolIter beginId, _BoolIter endId)
  {
    m_topology.assignDeadFlags(beginId,endId);
  }

  virtual const MbPolygonCellsSet& getTopology() const;

protected:
  virtual std::ostream& toStream(std::ostream& s) const;

  MbPolygonCellsSet m_topology;
};


//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
template <typename _Vec3Iter, typename _NodeIdIter, typename _numNodeIter>
inline MbSurfaceMeshPolygon<_CoordT,_ScalarT,_Vec3T>::MbSurfaceMeshPolygon(
  _Vec3Iter beginCoord, _Vec3Iter endCoord, 
  _NodeIdIter beginId, _NodeIdIter endId,
  _numNodeIter beginNum, _numNodeIter endNum
  ) :
   MbSurfaceMeshUnstructured<_CoordT,_ScalarT,_Vec3T>(beginCoord,endCoord)
{
  setTopology(beginId,endId,beginNum,endNum);
}


//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
inline const MbPolygonCellsSet&
MbSurfaceMeshPolygon<_CoordT,_ScalarT,_Vec3T>::getTopology() const
{
  return m_topology;
}



//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
template <typename _NodeIdIter, typename _numNodeIter>
inline void 
MbSurfaceMeshPolygon<_CoordT,_ScalarT,_Vec3T>::setTopology(_NodeIdIter beginId, _NodeIdIter endId,
                                                           _numNodeIter beginNum, _numNodeIter endNum)
{
  m_topology.assign(beginId,endId,beginNum,endNum);
}


//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
inline std::ostream& 
MbSurfaceMeshPolygon<_CoordT,_ScalarT,_Vec3T>::toStream(std::ostream& s) const
{
  s << "# MbSurfaceMeshPolygon" << std::endl;

  // output the inherited geometry and dataset
  MbSurfaceMeshUnstructured<_CoordT,_ScalarT,_Vec3T>::toStream(s);

  return s;
}

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif







