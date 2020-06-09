/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MbPolyhedronCellsSet_H
#define _MbPolyhedronCellsSet_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#pragma warning(disable:4251)
#endif

#include <MeshVizInterface/mesh/topology/MiVolumeTopologyExplicitI.h>
#include <MeshVizInterface/implement/topology/MbTopologyI.h>
#include <MeshVizInterface/implement/cell/MbPolyhedronCell.h>

#include <Inventor/STL/algorithm>

/**
* @DTEXT Build a set of Polyhedron.
* 
* @ingroup MeshIViz_Implement_Topology
*/
class MbPolyhedronCellsSet : virtual public MiVolumeTopologyExplicitI, public MbTopologyI
{
public:

  /** 
  * Construct an empty set of Polyhedrons.
  */
  MbPolyhedronCellsSet();

  /** 
  * Defines a new list of Polyhedrons according to a list of facet indices,
  * the number of indices per facet and the number of facet per polyhedrons
  */
  template <typename _FacetNodeIter, typename _NumNodeIter, typename _NumFacetIter>
  void assign(_FacetNodeIter beginFacetNode, _FacetNodeIter endFacetNode,
              _NumNodeIter beginNumNode, _NumNodeIter endNumNode,
              _NumFacetIter beginNumFacet, _NumFacetIter endNumFacet);

  /**
  * Returns the i-th cell of this set.
  */
  virtual const MbPolyhedronCell* getCell(size_t cellId) const;

  /**
  * Returns the number of cells in the set.
  */
  virtual size_t getNumCells() const;

  /**
  * Returns the first node index in this polyhedral geometry.
  */
  virtual size_t getBeginNodeId() const
  {
    return m_beginNodeId;
  }

  /**
  * Returns the end node index in this polyhedral geometry.
  */
  virtual size_t getEndNodeId() const
  {
    return m_endNodeId;
  }

protected:
  std::vector<MbPolyhedronCell> m_cells;
  size_t m_beginNodeId;
  size_t m_endNodeId;
};


//-----------------------------------------------------------------------------
inline
MbPolyhedronCellsSet::MbPolyhedronCellsSet()
: m_beginNodeId(0), m_endNodeId(0)
{
}


//-----------------------------------------------------------------------------
inline const MbPolyhedronCell* 
MbPolyhedronCellsSet::getCell(size_t cellId) const
{
  if (hasDeadCells() && isDead(cellId)) throw "Error accessing dead cells";
  return &(m_cells[cellId]);
}

//-----------------------------------------------------------------------------
inline size_t
MbPolyhedronCellsSet::getNumCells() const 
{
  return m_cells.size();
}

//-----------------------------------------------------------------------------
template <typename _FacetNodeIter, typename _NumNodeIter, typename _NumFacetIter>
inline void 
MbPolyhedronCellsSet::assign(_FacetNodeIter beginFacetNode, _FacetNodeIter endFacetNode,
                             _NumNodeIter beginNumNode, _NumNodeIter endNumNode,
                             _NumFacetIter beginNumFacet, _NumFacetIter endNumFacet)
{
  size_t numCells = std::distance(beginNumFacet,endNumFacet);
  m_beginNodeId = std::numeric_limits<size_t>::max();

  m_cells.clear();
  m_cells.reserve(numCells);
  _FacetNodeIter beginFacet, itFacetNode = beginFacetNode;
  _NumNodeIter beginNum, itNumNode = beginNumNode;
  for (_NumFacetIter itNum = beginNumFacet; itNum != endNumFacet; ++itNum)
  { 
    beginNum = itNumNode;
    beginFacet = itFacetNode;
    while ( itNumNode != beginNum + *itNum )
    {
      for ( size_t i =0; i < *itNumNode; ++i)
      {
       if ( *itFacetNode + 1 > m_endNodeId) 
         m_endNodeId = *itFacetNode + 1;
        if ( *itFacetNode < m_beginNodeId) 
         m_beginNodeId = *itFacetNode;
        ++itFacetNode;
      }
      ++itNumNode;
    }
    m_cells.push_back(MbPolyhedronCell(beginFacet,itFacetNode,beginNum,itNumNode));    
  }
  m_timeStamp = MxTimeStamp::getTimeStamp();
}

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif

