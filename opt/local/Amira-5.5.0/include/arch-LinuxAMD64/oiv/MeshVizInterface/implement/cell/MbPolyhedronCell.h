/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBPOLYHEDRONCELL_H
#define _MBPOLYHEDRONCELL_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#endif

#include <MeshVizInterface/extractors/MxPolyhedronCellExtract.h>
#include <MeshVizInterface/mesh/cell/MiVolumeCell.h>
#include <MeshVizInterface/implement/MbMeshVizImpl.h>

#include <Inventor/STL/map>

typedef std::map<size_t,size_t> IndexPairMap;
typedef std::map<size_t,size_t>::const_iterator IndexPairMapIterator;
typedef std::pair<IndexPairMapIterator,bool> IndexPairMapRet;

/**
* @DTEXT Build a Polyhedronal cell.
* 
* @ingroup MeshIViz_Implement_Cell
*/
class MbPolyhedronCell : virtual public MiVolumeCell
{
public:

  /** 
  * Construct a Polyhedron defined by its list of facet indices and number of indices per facet.
  */
  template < typename _FacetNodeIter, typename _NumNodeIter>
  MbPolyhedronCell(_FacetNodeIter beginFacetNode, _FacetNodeIter endFacetNode,
                   _NumNodeIter beginNum, _NumNodeIter endNum);

  virtual void getIsosurfTopology(unsigned char UNREF_PARAM(caseId), std::vector< std::pair<size_t,size_t> >& UNREF_PARAM(edgeList) ) const 
  {
  }

  /**
  * Gets the number of facets.
  */
  virtual size_t getNumFacets() const;

  /**
  * Gets the number of edges.
  */
  virtual size_t getNumEdges() const; 

  /**
  * Gets the number of nodes.
  */
  virtual size_t getNumNodes() const; 

  virtual size_t getNodeIndex(size_t nod) const;

    /**
  * Gets the node ids of the given face. For instance 
  * appendNodesIndexOfFacet(0,facetNodes) append in the array facetNodes the 
  * node ids of the first face of this cell.
  * the first node id of this cell.
  * @param facet must be in the interval [0-getNumFacets()]
  * @param facetNodes the returned list of facet nodes indices 
  */
  virtual size_t appendNodesIndexOfFacet (size_t facet, std::vector<size_t>& facetNodes) const;

  /**
  * Appends the array of local node indices belonging to a given facet to facetNodes.
  * @param[in] facet The index of the facet (where 0 <= facet < getNumFacets()).
  * @param facetNodes A vector in which the local node indices of the facet will be appended. 
  * The given vector should not be cleared by this method.
  * The implementation must use the push_back() method to add elements to the vector.
  * @return the number of nodes added.
  */
  virtual size_t appendLocalNodesIndexOfFacet (size_t facet, std::vector<size_t>& facetNodes) const;

  /**
  * Checks if a point is inside or outside a cell.
  */
  virtual bool isPointInsideCell(const MiGeometryI& meshGeometry, const MbVec3d &point, std::vector<double>& weights) const;

  /**
  * Gets the relative size of the cell
  */
  virtual double getRelativeSize(const MiGeometryI* meshGeometry) const;


protected:
  /**
  * Defines a specialized output on stream for MbPolyhedronCell
  */
  virtual std::ostream& toStream(std::ostream& s) const;

  std::vector<size_t> m_nodeIds;
  std::vector< std::vector<size_t> > m_facetNode;
};

//-----------------------------------------------------------------------------
template < typename _FacetNodeIter, typename _NumNodeIter>
inline
MbPolyhedronCell::MbPolyhedronCell(_FacetNodeIter beginFacetNode, _FacetNodeIter endFacetNode,
                                   _NumNodeIter beginNum, _NumNodeIter endNum)
{
  IndexPairMap mapping;
  IndexPairMapRet retPair;
  size_t newIndex = 0;
  std::vector<size_t> localFacetIndex;
  size_t numFacet = std::distance(beginNum,endNum);
  m_facetNode.resize(numFacet);
  _FacetNodeIter itFacetNode = beginFacetNode;
  size_t nf = 0;
  for (_NumNodeIter itNum = beginNum; itNum != endNum; ++itNum, ++nf)
  {
    m_facetNode[nf].reserve(*itNum);
    _FacetNodeIter endIt = itFacetNode+*itNum;
    while ( itFacetNode != endIt )
    {
      retPair = mapping.insert(std::make_pair(*itFacetNode,newIndex));
      if ( retPair.second == false )
        m_facetNode[nf].push_back((*retPair.first).second);
      else
      {
        m_nodeIds.push_back(*itFacetNode);
        m_facetNode[nf].push_back(newIndex++);
      }
      ++itFacetNode;
    }
  }
}

//-----------------------------------------------------------------------------
inline size_t 
MbPolyhedronCell::appendNodesIndexOfFacet (size_t facet, std::vector<size_t>& facetNodes) const
{
  std::vector<size_t>::const_iterator it;
  for ( it = m_facetNode[facet].begin(); it != m_facetNode[facet].end(); ++it )
    facetNodes.push_back(m_nodeIds[*it]);

  return m_facetNode[facet].size();
}

//-----------------------------------------------------------------------------
inline size_t 
MbPolyhedronCell::appendLocalNodesIndexOfFacet (size_t facet, std::vector<size_t>& facetNodes) const
{
  std::vector<size_t>::const_iterator it;
  for ( it = m_facetNode[facet].begin(); it != m_facetNode[facet].end(); ++it )
    facetNodes.push_back(*it);

  return m_facetNode[facet].size();
}

//-----------------------------------------------------------------------------
inline bool 
MbPolyhedronCell::isPointInsideCell(const MiGeometryI& meshGeometry, const MbVec3d &point, std::vector<double>& weights) const
{
  return MxPolyhedronCellExtract::isPointInsideCell(meshGeometry,this,point,weights);
}

//-----------------------------------------------------------------------------
inline double 
MbPolyhedronCell::getRelativeSize(const MiGeometryI* meshGeometry) const
{
  return MxPolyhedronCellExtract::getLongestDistance(*meshGeometry,this);
}

//-----------------------------------------------------------------------------
inline size_t 
MbPolyhedronCell::getNumFacets() const
{
  return m_facetNode.size();
}

//-----------------------------------------------------------------------------
inline size_t 
MbPolyhedronCell::getNumEdges() const
{
  return 0;
}

//-----------------------------------------------------------------------------
inline size_t 
MbPolyhedronCell::getNumNodes() const
{
  return m_nodeIds.size();
}

//-----------------------------------------------------------------------------
inline size_t 
MbPolyhedronCell::getNodeIndex(size_t nod) const
{
  return m_nodeIds[nod];
}

//-----------------------------------------------------------------------------
inline std::ostream& 
MbPolyhedronCell::toStream(std::ostream& s) const
{
  s << "MbPolyhedronCell (";
  size_t numNodes = m_nodeIds.size();
  for (size_t i=0; i<numNodes-1; ++i)
    s << m_nodeIds[i] << ",";
  s << m_nodeIds[numNodes-1];
  s << ")";
  return s;
}

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif


