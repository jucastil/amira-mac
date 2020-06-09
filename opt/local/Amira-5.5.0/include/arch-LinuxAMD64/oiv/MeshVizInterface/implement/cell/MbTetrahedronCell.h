/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBTETRAHEDRONCELL_H
#define _MBTETRAHEDRONCELL_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#endif

#include <MeshVizInterface/extractors/MxTetrahedronCellExtract.h>
#include <MeshVizInterface/mesh/cell/MiVolumeCell.h>
#include <MeshVizInterface/implement/MbMeshVizImpl.h>

class PiMarchingCase;

/**
* @DTEXT Build a tetrahedron cell.
* 
* @ingroup MeshIViz_Implement_Cell
* 
* @DESCRIPTION
*    A tetrahedron cell has 4 faces which can be in anywhere in
*    the 3D space. Each face is a triangle.
* 
*    Facets and nodes are numbered as following :
* <PRE>
*                       n2
*
*                      /|\
*                     / | \                  
*                    /  |  \                  
*                   /   |   \                  the face n0,n1,n2
*                  /    |    \                 is oriented towards
*                 /     |     \                the interior of the cell
*             n0 x------|------x n1
*                 \     |     /
*                  \    |    /
*                   \   |   /
*                    \  |  /
*                     \ | /
*                      \|/
*                       x 
*
*                       n3
* </PRE>
*/
class MESHIVIZIMPL_API MbTetrahedronCell : virtual public MiVolumeCell
{
public:

  /** 
  * Construct a tetrahedron.
  */
  MbTetrahedronCell(size_t nodeId0, size_t nodeId1, size_t nodeId2, size_t nodeId3);

  /**
  * Gets the volume of the cell. 
  */
  double getVolume(const MiGeometryI* meshGeometry) const
  {
    return MxTetrahedronCellExtract::getVolume(*meshGeometry,this);
  }

  /**
  * Gets the number of facets.
  */
  virtual size_t getNumFacets() const { return 4; }

  /**
  * Gets the number of edges.
  */
  virtual size_t getNumEdges() const { return 6; }

  /**
  * Gets the number of nodes.
  */
  virtual size_t getNumNodes() const { return 4; }

  virtual size_t getNodeIndex(size_t nod) const { return m_nodeIds[nod]; }

  virtual size_t appendNodesIndexOfFacet (size_t facet, std::vector<size_t>& facetNodes) const;
  
  virtual void getIsosurfTopology(unsigned char caseId, std::vector< std::pair<size_t,size_t> >& edgeList ) const
  {
    MxTetrahedronCellExtract::getIsosurfTopology(caseId, edgeList);
  }

  virtual unsigned char getMarchingCaseId(std::vector<bool> &nodesSign, size_t beginNodeId=0) const;

  //Reimplemented from MiCell 
  virtual MbVec3d getIsoParametricCoord(size_t indexNode) const
  {
    return MxTetrahedronCellExtract::getIsoParametricCoord(indexNode);
  }

  virtual double getRelativeSize(const MiGeometryI* meshGeometry) const 
  {
    return MxTetrahedronCellExtract::getLongestEdgeLength(*meshGeometry,this);
  }

  //Reimplemented from MiCell 
  virtual bool isPointInsideCell(const MiGeometryI& meshGeometry, const MbVec3d &point, std::vector<double>& weights) const 
  {
    return MxTetrahedronCellExtract::isPointInsideCell(meshGeometry,this,point,weights);
  }

protected:
  /**
  * Defines a specialized output on stream for MbTetrahedronCell
  */
  virtual std::ostream& toStream(std::ostream& s) const;

  size_t m_nodeIds[4];
  static size_t s_facetNode[4][3];
};

//-----------------------------------------------------------------------------
inline
MbTetrahedronCell::MbTetrahedronCell(size_t nodeId0, size_t nodeId1, size_t nodeId2, size_t nodeId3)
{
  m_nodeIds[0] = nodeId0;
  m_nodeIds[1] = nodeId1;
  m_nodeIds[2] = nodeId2;
  m_nodeIds[3] = nodeId3;
}

//-----------------------------------------------------------------------------
inline size_t 
MbTetrahedronCell::appendNodesIndexOfFacet (size_t facet, std::vector<size_t>& facetNodes) const
{
  facetNodes.push_back(m_nodeIds[s_facetNode[facet][0]]);
  facetNodes.push_back(m_nodeIds[s_facetNode[facet][1]]);
  facetNodes.push_back(m_nodeIds[s_facetNode[facet][2]]);
  return 3;
}

//-----------------------------------------------------------------------------
inline std::ostream& 
MbTetrahedronCell::toStream(std::ostream& s) const
{
  s << "MbTetrahedronCell (" << 
    m_nodeIds[0] << "," << 
    m_nodeIds[1] << "," << 
    m_nodeIds[2] << "," << 
    m_nodeIds[3] << 
    ")";
  return s;
}

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif


