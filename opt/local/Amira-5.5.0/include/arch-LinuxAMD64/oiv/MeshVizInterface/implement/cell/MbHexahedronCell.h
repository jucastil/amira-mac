/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBHEXAHEDRONCELL_H
#define _MBHEXAHEDRONCELL_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#endif

#include <MeshVizInterface/extractors/MxHexahedronCellExtract.h>
#include <MeshVizInterface/mesh/cell/MiVolumeCell.h>
#include <MeshVizInterface/implement/MbMeshVizImpl.h>

class PiMarchingCase;

/**
* @DTEXT  Defines an hexahedron cell of a volume mesh.
* 
* @ingroup MeshIViz_Implement_Cell
* 
* @DESCRIPTION
*    An hexahedron cell has 6 faces which can be in anywhere in
*    the 3D space. Each face is a quadrangle not necessarily a square.
*    The 4 first indices defines the polygon of a face of the
*    hexahedron. The 4 last indices defines the polygon of the 
*    opposite face.
* 
*    Facets and nodes are numbered as following :
* <PRE>
*                       n3----------n2   facet 0 = 0123    
*                       /|          /|   facet 1 = 4765 
*                     /  |        /  |   facet 2 = 0374
*                   /    |      /    |   facet 3 = 1562    
*                 n7---------n6      |   facet 4 = 0451 
*                  |     |    |      |   facet 5 = 3267 
*                  |    n0----|-----n1                   
*                  |    /     |     /                    
*                  |  /       |   /                      
*                  |/         | /                        
*                 n4---------n5                          
*                                                        
* </PRE>
* 
*   - The first face is defined by the first 4 nodes of the cell.
*   - The second face is defined by the first 4 nodes of the cell.
*   - The other faces are numbered as above.
*
*  Thus, appendNodesIndexOfFacet(0,faceNodes) appends the 
*  first 4 nodes of the cell in the array faceNodes, and 
*  appendNodesIndexOfFacet(1,faceNodes) appends the 
*  4 last nodes of the cell in the array faceNodes.
*/
class MESHIVIZIMPL_API MbHexahedronCell : virtual public MiVolumeCell
{
public:

  /** 
  * Construct an hexahedron.
  */
  MbHexahedronCell(size_t n0, size_t n1, size_t n2, size_t n3,
                   size_t n4, size_t n5, size_t n6, size_t n7);

  /**
  * Gets the volume of the cell.
  */
  virtual double getVolume(const MiGeometryI* meshGeometry) const
  {
    return MxHexahedronCellExtract::getVolume(*meshGeometry,this);
  }

  /**
  * Gets the number of facets.
  */
  virtual size_t getNumFacets() const { return 6; }

  /**
  * Gets the number of edges.
  */
  virtual size_t getNumEdges() const { return 12; }

  /**
  * Gets the number of nodes.
  */
  virtual size_t getNumNodes() const { return 8; }

  /**
  * Gets a node id of this cell. For instance getNodeIndex(0) returns
  * the first node id of this cell.
  * @param nod must be in the interval [0-7]
  */
  virtual size_t getNodeIndex(size_t nod) const
  {
    return m_nodeIds[nod];
  }

  /**
  * Gets the node ids of the given face. For instance 
  * appendNodesIndexOfFacet(0,facetNodes) append in the array facetNodes the 
  * node ids of the first face of this cell.
  * the first node id of this cell.
  * @param facet must be in the interval [0-5] because an hexahedrons contains 
  *        6 faces.
  * @param facetNodes the returned list of facet nodes indices 
  */
  virtual size_t appendNodesIndexOfFacet (size_t facet, std::vector<size_t>& facetNodes) const;

  virtual size_t appendLocalNodesIndexOfFacet (size_t facet, std::vector<size_t>& facetNodes) const;


  virtual void getIsosurfTopology(unsigned char caseId, std::vector< std::pair<size_t,size_t> >& edgeList ) const
  {
    MxHexahedronCellExtract::getIsosurfTopology(caseId, edgeList);
  }

  virtual unsigned char getMarchingCaseId(std::vector<bool> &nodesSign, size_t beginNodeId=0) const;

  //Reimplemented from MiCell 
  virtual MbVec3d getIsoParametricCoord(size_t indexNode) const
  {
    return MxHexahedronCellExtract::getIsoParametricCoord(indexNode);
  }

  virtual double getRelativeSize(const MiGeometryI* meshGeometry) const 
  {
    return MxHexahedronCellExtract::getLongestEdgeLength(*meshGeometry,this);
  }

  //Reimplemented from MiCell 
  virtual bool isPointInsideCell(const MiGeometryI& meshGeometry, const MbVec3d &point, std::vector<double>& weights) const 
  {
    return MxHexahedronCellExtract::isPointInsideCell(meshGeometry,this,point,weights);
  }


protected:
  /**
  * Defines a specialized output on stream for MbHexahedronCell
  */
  virtual std::ostream& toStream(std::ostream& s) const;


  size_t m_nodeIds[8];
  static size_t s_facetNode[6][4];
};

//-----------------------------------------------------------------------------
inline
MbHexahedronCell::MbHexahedronCell(size_t n0, size_t n1, size_t n2, size_t n3,
                                   size_t n4, size_t n5, size_t n6, size_t n7)
{
  m_nodeIds[0] = n0;
  m_nodeIds[1] = n1;
  m_nodeIds[2] = n2;
  m_nodeIds[3] = n3;
  m_nodeIds[4] = n4;
  m_nodeIds[5] = n5;
  m_nodeIds[6] = n6;
  m_nodeIds[7] = n7;
}

//-----------------------------------------------------------------------------
inline size_t 
MbHexahedronCell::appendNodesIndexOfFacet (size_t facet, std::vector<size_t>& facetNodes) const
{
  facetNodes.push_back(m_nodeIds[s_facetNode[facet][0]]);
  facetNodes.push_back(m_nodeIds[s_facetNode[facet][1]]);
  facetNodes.push_back(m_nodeIds[s_facetNode[facet][2]]);
  facetNodes.push_back(m_nodeIds[s_facetNode[facet][3]]);
  return 4;
}

//-----------------------------------------------------------------------------
inline size_t 
MbHexahedronCell::appendLocalNodesIndexOfFacet (size_t facet, std::vector<size_t>& facetNodes) const
{
  facetNodes.push_back(s_facetNode[facet][0]);
  facetNodes.push_back(s_facetNode[facet][1]);
  facetNodes.push_back(s_facetNode[facet][2]);
  facetNodes.push_back(s_facetNode[facet][3]);
  return 4;
}

//-----------------------------------------------------------------------------
inline std::ostream& 
MbHexahedronCell::toStream(std::ostream& s) const
{
  s << "MbHexahedronCell (" << 
    m_nodeIds[0] << "," << 
    m_nodeIds[1] << "," << 
    m_nodeIds[2] << "," << 
    m_nodeIds[3] << "," << 
    m_nodeIds[4] << "," << 
    m_nodeIds[5] << "," << 
    m_nodeIds[6] << "," << 
    m_nodeIds[7] <<  
    ")";
  return s;
}

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif


