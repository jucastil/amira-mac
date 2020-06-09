/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MbSurfaceMeshQuadrangle_H
#define  _MbSurfaceMeshQuadrangle_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/implement/mesh/surfaces/MbSurfaceMeshUnstructured.h>
#include <MeshVizInterface/implement/topology/MbQuadrangleCellsSet.h>
#include <MeshVizInterface/MbVec3.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/iostream>

/**
 * @DTEXT  Defines a mesh of quadrangle.
 * 
 * @ingroup MeshIViz_Implement_Mesh
 * 
 * @DESCRIPTION

 * 
 */
template <typename _CoordT=MbVec3d, typename _ScalarT=double, typename _Vec3T=MbVec3d>
class MbSurfaceMeshQuadrangle : public MbSurfaceMeshUnstructured<_CoordT,_ScalarT,_Vec3T>
{

public:

  /**
   * Constructor of a surface mesh. 
   */
  template <typename _Vec3Iter, typename _NodeIdIter>
  MbSurfaceMeshQuadrangle(_Vec3Iter beginCoord, _Vec3Iter endCoord, 
                       _NodeIdIter beginId, _NodeIdIter endId);

  /**
  * Sets a new topology
  */
  template <typename _NodeIdIter>
  void setTopology(_NodeIdIter beginId, _NodeIdIter endId);

  /**
  * Defines dead cells
  */
  template <typename _BoolIter>
  void setDeadCells(_BoolIter beginId, _BoolIter endId)
  {
    m_topology.assignDeadFlags(beginId,endId);
  }

  virtual const MbQuadrangleCellsSet& getTopology() const;

protected:
  virtual std::ostream& toStream(std::ostream& s) const;

  MbQuadrangleCellsSet m_topology;
};


//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
template <typename _Vec3Iter, typename _NodeIdIter>
inline MbSurfaceMeshQuadrangle<_CoordT,_ScalarT,_Vec3T>::MbSurfaceMeshQuadrangle(
  _Vec3Iter beginCoord, _Vec3Iter endCoord, 
  _NodeIdIter beginId, _NodeIdIter endId
  ) :
   MbSurfaceMeshUnstructured<_CoordT,_ScalarT,_Vec3T>(beginCoord,endCoord)
{
  setTopology(beginId,endId);
}


//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
inline const MbQuadrangleCellsSet&
MbSurfaceMeshQuadrangle<_CoordT,_ScalarT,_Vec3T>::getTopology() const
{
  return m_topology;
}



//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
template <typename _NodeIdIter>
inline void 
MbSurfaceMeshQuadrangle<_CoordT,_ScalarT,_Vec3T>::setTopology(_NodeIdIter beginId, _NodeIdIter endId)
{
  m_topology.assign(beginId,endId);
}


//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
inline std::ostream& 
MbSurfaceMeshQuadrangle<_CoordT,_ScalarT,_Vec3T>::toStream(std::ostream& s) const
{
  s << "# MbSurfaceMeshQuadrangle" << std::endl;

  // output the inherited geometry and dataset
  MbSurfaceMeshUnstructured<_CoordT,_ScalarT,_Vec3T>::toStream(s);

  return s;
}

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif







