/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MxHalfPyramidCell_h
#define _MxHalfPyramidCell_h

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#endif

#include <MeshVizInterface/extractors/MxTetrahedronCellExtract.h>
#include <MeshVizInterface/mesh/cell/MiVolumeCell.h>


/**
* @internal 
* Used only to check if a point is inside a pyramid by splitting the pyramid 
* into 2 tetrahedrons.
*
* NOTE: This class should not be used by applications, and may not exist in future releases.
*/
SoINTERNAL class MESHIVIZ_API MxHalfPyramidCell : virtual public MiVolumeCell
{
public:

  void setNodeIds(size_t nodeId0, size_t nodeId1, size_t nodeId2, size_t nodeId3)
  {
    m_nodeIds[0] = nodeId0;
    m_nodeIds[1] = nodeId1;
    m_nodeIds[2] = nodeId2;
    m_nodeIds[3] = nodeId3;
  }

  virtual size_t getNodeIndex(size_t nod) const { return m_nodeIds[nod]; }

  virtual bool isPointInsideCell(const MiGeometryI& meshGeometry, const MbVec3d &point, std::vector<double>& weights) const 
  {
    return MxTetrahedronCellExtract::isPointInsideCell(meshGeometry,this,point,weights);
  }

  void getWeight(const MiGeometryI& meshGeometry,const MbVec3d& point, std::vector<double>& weights) const 
  {
    return MxTetrahedronCellExtract::getWeight(meshGeometry,this,point,weights);
  }

  virtual size_t getNumFacets() const { return 4; }
  virtual size_t getNumEdges() const { return 6; }
  virtual size_t getNumNodes() const { return 4; }
  virtual size_t appendNodesIndexOfFacet (size_t, std::vector<size_t>&) const { return 0; }
  virtual void getIsosurfTopology(unsigned char, std::vector< std::pair<size_t,size_t> >& ) const {}


protected:
  size_t m_nodeIds[4];
};

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif


