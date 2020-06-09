/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBWEDGECELL_H
#define _MBWEDGECELL_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#endif

#include <MeshVizInterface/extractors/MxWedgeCellExtract.h>
#include <MeshVizInterface/mesh/cell/MiVolumeCell.h>
#include <MeshVizInterface/implement/MbMeshVizImpl.h>

class PiMarchingCase;

/**
* @DTEXT  Defines an Wedge cell of a volume mesh.
* 
* @ingroup MeshIViz_Implement_Cell
* 
* @DESCRIPTION
*    An Wedge cell has 6 faces which can be in any plane of
*    the 3D space. Each face is a quadrangle not necessarily a square.
*    The 4 first indices defines the polygon of a face of the
*    Wedge. The 4 last indices defines the polygon of the 
*    opposite face.
* 
*    Facets and nodes are numbered as following :
* <PRE>
*                                   n2               facet 0 = 012   
*                                   x                facet 1 = 354   
*                                . / \               facet 2 = 0253  
*                             .   /   \              facet 3 = 1452     
*                          .     /     \             facet 4 = 0341   
*                       .       /       \                            
*                  n5          /         \                           
*                  x          /           \                          
*                 / \     n0 x-------------x n1                      
*                /   \    .             .            
*               /     \.             .       
*              /    .  \          .          
*             /  .      \      .        
*            /.          \  .           
*        n3 x-------------x n4
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
class MESHIVIZIMPL_API MbWedgeCell : virtual public MiVolumeCell
{
public:

  /** 
  * Construct an Wedge.
  */
  MbWedgeCell(size_t n0, size_t n1, size_t n2, size_t n3, size_t n4, size_t n5);

  /**
  * Gets the volume of the cell.
  */
  double getVolume(const MiGeometryI* meshGeometry) const
  {
    return MxWedgeCellExtract::getVolume(*meshGeometry,this);
  }

  /**
  * Gets the number of facets.
  */
  virtual size_t getNumFacets() const { return 5; }

  /**
  * Gets the number of edges.
  */
  virtual size_t getNumEdges() const { return 9; }

  /**
  * Gets the number of nodes.
  */
  virtual size_t getNumNodes() const { return 6; }

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
  * @param facet must be in the interval [0-4] because an Wedges contains 
  *        5 faces.
  * @param facetNodes the returned list of facet nodes indices 
  */
  virtual size_t appendNodesIndexOfFacet (size_t facet, std::vector<size_t>& facetNodes) const;

  virtual void getIsosurfTopology(unsigned char caseId, std::vector< std::pair<size_t,size_t> >& edgeList ) const
  {
    MxWedgeCellExtract::getIsosurfTopology(caseId, edgeList);
  }

  virtual unsigned char getMarchingCaseId(std::vector<bool> &nodesSign, size_t beginNodeId=0) const;


  virtual double getRelativeSize(const MiGeometryI* meshGeometry) const 
  {
    return MxWedgeCellExtract::getLongestEdgeLength(*meshGeometry,this);
  }

  //Reimplemented from MiCell 
  virtual bool isPointInsideCell(const MiGeometryI& meshGeometry, const MbVec3d &point, std::vector<double>& weights) const 
  {
    return MxWedgeCellExtract::isPointInsideCell(meshGeometry,this,point,weights);
  }

protected:
  /**
  * Defines a specialized output on stream for MbWedgeCell
  */
  virtual std::ostream& toStream(std::ostream& s) const;

  size_t m_nodeIds[6];
  static size_t s_facetNode[5][4];
};

//-----------------------------------------------------------------------------
inline
MbWedgeCell::MbWedgeCell(size_t n0, size_t n1, size_t n2, size_t n3,
                                   size_t n4, size_t n5)
{
  m_nodeIds[0] = n0;
  m_nodeIds[1] = n1;
  m_nodeIds[2] = n2;
  m_nodeIds[3] = n3;
  m_nodeIds[4] = n4;
  m_nodeIds[5] = n5;
}



//-----------------------------------------------------------------------------
inline std::ostream& 
MbWedgeCell::toStream(std::ostream& s) const
{
  s << "MbWedgeCell (" << 
    m_nodeIds[0] << "," << 
    m_nodeIds[1] << "," << 
    m_nodeIds[2] << "," << 
    m_nodeIds[3] << "," << 
    m_nodeIds[4] << "," << 
    m_nodeIds[5] <<  
    ")";
  return s;
}

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif


