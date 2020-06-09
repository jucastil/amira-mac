/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MbVolumeMeshPolyhedron_H
#define  _MbVolumeMeshPolyhedron_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiVolumeMeshUnstructured.h>
#include <MeshVizInterface/mesh/topology/MiVolumeTopologyExplicitI.h>

#include <MeshVizInterface/implement/mesh/volumes/MbVolumeMeshUnstructured.h>
#include <MeshVizInterface/implement/topology/MbPolyhedronCellsSet.h>
#include <MeshVizInterface/MbVec3.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/iostream>

/**
 * @DTEXT  Defines a mesh of Polyhedrons.
 * 
 * @ingroup MeshIViz_Implement_Mesh
 * 
 * @DESCRIPTION

 * 
 */
template <typename _CoordT=MbVec3d, typename _ScalarT=double, typename _Vec3T=MbVec3d>
class MbVolumeMeshPolyhedron : public MbVolumeMeshUnstructured<_CoordT,_ScalarT,_Vec3T>
{

public:

  /**
  * Constructor of an empty mesh. 
  */
  MbVolumeMeshPolyhedron() {}


  /**
  * Constructor of a volume mesh. 
  */
  template <typename _Vec3Iter, typename _FacetNodeIter, typename _NumNodeIter, typename _NumFacetIter>
    MbVolumeMeshPolyhedron(_Vec3Iter beginCoord, _Vec3Iter endCoord, 
                           _FacetNodeIter beginFacetNode, _FacetNodeIter endFacetNode,
                           _NumNodeIter beginNumNode, _NumNodeIter endNumNode,
                           _NumFacetIter beginNumFacet, _NumFacetIter endNumFacet);

  /**
  * Sets a new topology
  */
  template <typename _FacetNodeIter, typename _NumNodeIter, typename _NumFacetIter>
  void setTopology(_FacetNodeIter beginFacetNode, _FacetNodeIter endFacetNode,
                   _NumNodeIter beginNumNode, _NumNodeIter endNumNode,
                   _NumFacetIter beginNumFacet, _NumFacetIter endNumFacet)
  {
    m_topology.assign(beginFacetNode,endFacetNode,beginNumNode,endNumNode,beginNumFacet,endNumFacet);
  }


  virtual const MbPolyhedronCellsSet& getTopology() const;

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

  MbPolyhedronCellsSet m_topology;
};


//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
  template <typename _Vec3Iter, typename _FacetNodeIter, typename _NumNodeIter, typename _NumFacetIter>
inline MbVolumeMeshPolyhedron<_CoordT,_ScalarT,_Vec3T>::MbVolumeMeshPolyhedron(
  _Vec3Iter beginCoord, _Vec3Iter endCoord, 
  _FacetNodeIter beginFacetNode, _FacetNodeIter endFacetNode,
  _NumNodeIter beginNumNode, _NumNodeIter endNumNode,
  _NumFacetIter beginNumFacet, _NumFacetIter endNumFacet
  ) :
   MbVolumeMeshUnstructured<_CoordT,_ScalarT,_Vec3T>(beginCoord,endCoord)
{
  setTopology(beginFacetNode,endFacetNode,beginNumNode,endNumNode,beginNumFacet,endNumFacet);
}


//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
inline const MbPolyhedronCellsSet&
MbVolumeMeshPolyhedron<_CoordT,_ScalarT,_Vec3T>::getTopology() const
{
  return m_topology;
}

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
inline std::ostream& 
MbVolumeMeshPolyhedron<_CoordT,_ScalarT,_Vec3T>::toStream(std::ostream& s) const
{
  s << "# MbVolumeMeshPolyhedron" << std::endl;
  // output the inherited geometry and dataset
  MbVolumeMeshUnstructured<_CoordT,_ScalarT,_Vec3T>::toStream(s);

  return s;
}

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif







