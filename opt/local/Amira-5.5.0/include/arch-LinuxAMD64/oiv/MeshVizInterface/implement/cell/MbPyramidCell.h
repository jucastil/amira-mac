/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBPYRAMIDCELL_H
#define _MBPYRAMIDCELL_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#endif

#include <MeshVizInterface/extractors/MxPyramidCellExtract.h>
#include <MeshVizInterface/mesh/cell/MiVolumeCell.h>
#include <MeshVizInterface/implement/MbMeshVizImpl.h>

class PiMarchingCase;

/**
* @DTEXT  Defines an Pyramid cell of a volume mesh.
* 
* @ingroup MeshIViz_Implement_Cell
* 
* @DESCRIPTION
*    A pyramid cell has 5 faces which can be in any plane of
*    3D space. It has 4 triangle faces and 1 quadrangle face.
*    The 4 first indices define the base quadrangle face.
* 
*    Faces and nodes are numbered as following :
* <PRE>
*                  
*                n4
*                x                           facet 0 = 0123
*               /| \ .                       facet 1 = 041 
*              / |  \   .                    facet 2 = 142 
*             /  |   \     .                 facet 3 = 243
*            /   |    \       .              facet 4 = 340
*           /    |     \         .                        
*          /  n3 x------\----------x n2                    
*         /    '         \       '                          
*        /  '             \   '                              
*    n0 x------------------x n1
*
* </PRE>
* 
*   - The first face is defined by the first 4 nodes of the cell.
*   - The other faces are numbered as above.
*
*  Thus, appendNodesIndexOfFacet(0,faceNodes) appends the 
*  first 4 nodes of the cell in the array faceNodes.
*/
class MESHIVIZIMPL_API MbPyramidCell : virtual public MiVolumeCell
{
public:

  /** 
  * Construct an Pyramid.
  */
  MbPyramidCell(size_t n0, size_t n1, size_t n2, size_t n3, size_t n4);

  /**
  * Gets the volume of the cell.
  */
  double getVolume(const MiGeometryI* meshGeometry) const
  {
    return MxPyramidCellExtract::getVolume(*meshGeometry,this);
  }

  /**
  * Gets the number of facets.
  */
  virtual size_t getNumFacets() const { return 5; }

  /**
  * Gets the number of edges.
  */
  virtual size_t getNumEdges() const { return 8; }

  /**
  * Gets the number of nodes.
  */
  virtual size_t getNumNodes() const { return 5; }

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
  * @param facet must be in the interval [0-4] because an Pyramids contains 
  *        5 faces.
  * @param facetNodes returned facet nodes 
  */
  virtual size_t appendNodesIndexOfFacet (size_t facet, std::vector<size_t>& facetNodes) const;

  virtual void getIsosurfTopology(unsigned char caseId, std::vector< std::pair<size_t,size_t> >& edgeList ) const
  {
    MxPyramidCellExtract::getIsosurfTopology(caseId, edgeList);
  }

  virtual unsigned char getMarchingCaseId(std::vector<bool> &nodesSign, size_t beginNodeId=0) const;

  virtual double getRelativeSize(const MiGeometryI* meshGeometry) const 
  {
    return MxPyramidCellExtract::getLongestEdgeLength(*meshGeometry,this);
  }

  //Reimplemented from MiCell 
  virtual bool isPointInsideCell(const MiGeometryI& meshGeometry, const MbVec3d &point, std::vector<double>& weights) const 
  {
    return MxPyramidCellExtract::isPointInsideCell(meshGeometry,this,point,weights);
  }


protected:
  /**
  * Defines a specialized output on stream for MbHexahedronCell
  */
  virtual std::ostream& toStream(std::ostream& s) const;

  size_t m_nodeIds[5];
  static size_t s_facetNode[5][4];
};

//-----------------------------------------------------------------------------
inline
MbPyramidCell::MbPyramidCell(size_t n0, size_t n1, size_t n2, size_t n3,
                                   size_t n4)
{
  m_nodeIds[0] = n0;
  m_nodeIds[1] = n1;
  m_nodeIds[2] = n2;
  m_nodeIds[3] = n3;
  m_nodeIds[4] = n4;
}



//-----------------------------------------------------------------------------
inline std::ostream& 
MbPyramidCell::toStream(std::ostream& s) const
{
  s << "MbPyramidCell (" << 
    m_nodeIds[0] << "," << 
    m_nodeIds[1] << "," << 
    m_nodeIds[2] << "," << 
    m_nodeIds[3] << "," << 
    m_nodeIds[4] <<  
    ")";
  return s;
}

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif


