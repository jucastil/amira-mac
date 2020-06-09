/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MbHexahedronTopologyExplicitIjk_H
#define _MbHexahedronTopologyExplicitIjk_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#pragma warning(disable:4251)
#endif

#include <MeshVizInterface/mesh/topology/MiHexahedronTopologyExplicitIjk.h>
#include <MeshVizInterface/implement/topology/MbTopologyIjk.h>

#include <Inventor/SbTime.h>
#include <Inventor/STL/limits>

//-----------------------------------------------------------------------------
/**
* @DTEXT List of volume cells' indices.
* 
* @ingroup MeshIViz_Implement_Topology
* 
* @DESCRIPTION
*    A topology for a unstructured explicit hexahedron mesh Ijk. 
*
*    Hexahedrons are defines as follows:
* <PRE>
*                        J
*                        |
*                        |
*
*                       n3----------n2   facet 0 = 0123   
*                       /|          /|   facet 1 = 4765 
*                     /  |        /  |   facet 2 = 0374
*                   /    |      /    |   facet 3 = 1562    
*                 n7---------n6      |   facet 4 = 0451 
*                  |     |    |      |   facet 5 = 3267 
*                  |    n0----|-----n1    --- I               
*                  |    /     |     /                    
*                  |  /       |   /                      
*                  |/         | /                        
*                 n4---------n5                          
*             
*               /
*             /
*           K
* </PRE>
*/
class MbHexahedronTopologyExplicitIjk : public MiHexahedronTopologyExplicitIjk, public MbTopologyIjk
{
public:
  /**
  * Constructor of an empty topology defined by its size in i,j,k
  */
  MbHexahedronTopologyExplicitIjk(size_t numCellI, size_t numCellJ, size_t numCellK);
  MbHexahedronTopologyExplicitIjk(const MbHexahedronTopologyExplicitIjk& topology);

#ifdef MBMESH_DONT_USE_STL
  ~MbHexahedronTopologyExplicitIjk();
#endif


  /**
  * Returns 8 indices of a cell of this topology. The cell 
  * is identified by three id i,j,k.
  */
  virtual void getCellNodeIndices(size_t i, size_t j, size_t k, size_t& n0, size_t& n1, size_t& n2, size_t& n3,
                                                                size_t& n4, size_t& n5, size_t& n6, size_t& n7) const;

  virtual MiMeshIjk::StorageLayout getStorageLayout() const { return MiMeshIjk::LAYOUT_KJI; }

  size_t getBeginNodeId() const;

  /**
  * Returns the max node id +1 used by this topology. This topology used only 
  * node index in the interval [beginNodeId,EndNodeId[. Thus the maximum node
  * index used by the topology is getEndNodeId() -1 and the number of 
  * nodes used by this topology is getEndNodeId()-getBeginNodeId().
  */
  size_t getEndNodeId() const;

    /**
  * Returns the number of cells on the first logical axis.
  */
  size_t getNumCellsI() const { return m_numI; }

  /**
  * Returns the number of cells on the second logical axis.
  */
  size_t getNumCellsJ() const { return m_numJ; }

  /**
  * Returns the number of cells on the third logical axis.
  */
  size_t getNumCellsK() const { return m_numK; }

  /** 
  * Returns true if the cell of index (i,j,k) should be ignored.
  * This value is ignored if the hasDeadCell() method returns false.
  * The default implementation returns always false.
  * @param (i,j,k) the index of the cell to check
  */ 
  bool isDead(size_t i, size_t j, size_t k) const 
  {
    return MbTopologyIjk::isDead(i,j,k);
  }

  /**
  * Set the nodes indices of cell (i,j,k)
  */
  virtual void setCellNodeIndices(size_t i, size_t j, size_t k, 
                              const size_t* beginId, const size_t* endId);

  /**
  * Returns the number of cells
  */
  size_t getNumCells() const;

protected:
  /**
  * Defines a specialized output on stream 
  */
  virtual std::ostream& toStream(std::ostream& s) const;

#ifndef MBMESH_DONT_USE_STL
  std::vector<size_t> m_indices;
#else
  size_t* m_indices;
#endif

  size_t m_beginNodeId;
  size_t m_endNodeId;

#ifdef MBMESH_DATA_ACCESS_MICROSLEEP
public:
   static size_t s_microsleep;
#endif
};

//-----------------------------------------------------------------------------
inline
MbHexahedronTopologyExplicitIjk::MbHexahedronTopologyExplicitIjk(size_t numCellI, size_t numCellJ, size_t numCellK)
: MbTopologyIjk(numCellI,numCellJ,numCellK), m_beginNodeId(0), m_endNodeId(0)
{
  m_beginNodeId = std::numeric_limits<size_t>::max();
#ifndef MBMESH_DONT_USE_STL
  m_indices.resize(numCellK*m_numIxJ*8);
#else
  m_indices = new size_t[numCellK*m_numIxJ*8];
#endif
}

//-----------------------------------------------------------------------------
#ifdef MBMESH_DONT_USE_STL
inline
MbHexahedronTopologyExplicitIjk::~MbHexahedronTopologyExplicitIjk()
{
  delete[] m_indices;
}
#endif

//-----------------------------------------------------------------------------
#ifndef MBMESH_DONT_USE_STL
inline
MbHexahedronTopologyExplicitIjk::MbHexahedronTopologyExplicitIjk(const MbHexahedronTopologyExplicitIjk& topology)
: MbTopologyIjk(topology), m_indices(topology.m_indices), m_beginNodeId(topology.m_beginNodeId), m_endNodeId(topology.m_endNodeId)
{
}
#else
inline
MbHexahedronTopologyExplicitIjk::MbHexahedronTopologyExplicitIjk(const MbHexahedronTopologyExplicitIjk& topology)
: MbTopologyIjk(topology), m_beginNodeId(topology.m_beginNodeId), m_endNodeId(topology.m_endNodeId)
{
  m_indices = new size_t[m_endNodeId];
  for (size_t i=m_beginNodeId; i!=m_endNodeId; ++i)
    m_indices[i] = topology.m_indices[i];
}
#endif



//-----------------------------------------------------------------------------
inline size_t
MbHexahedronTopologyExplicitIjk::getNumCells() const 
{
  return m_numK*m_numIxJ;
}

//-----------------------------------------------------------------------------
inline 
void 
MbHexahedronTopologyExplicitIjk::getCellNodeIndices(size_t i, size_t j, size_t k, size_t& n0, size_t& n1, size_t& n2, size_t& n3,
                                                                                  size_t& n4, size_t& n5, size_t& n6, size_t& n7) const
{
#ifndef MBMESH_DONT_USE_ASSERT
  if (hasDeadCells() && isDead(i,j,k)) throw "Error accessing dead cells";
#endif

#ifndef MBMESH_DONT_USE_STL
  std::vector<size_t>::const_iterator it = m_indices.begin();
#else
  size_t *it = m_indices;
#endif
  it += getI(i,j,k) * 8;
  n0 = *it++;
  n1 = *it++;
  n2 = *it++;
  n3 = *it++;
  n4 = *it++;
  n5 = *it++;
  n6 = *it++;
  n7 = *it;

#ifdef MBMESH_DATA_ACCESS_MICROSLEEP
  if (s_microsleep>0)
    SbTime::usleep(s_microsleep);
#endif
}

//-----------------------------------------------------------------------------
inline size_t
MbHexahedronTopologyExplicitIjk::getBeginNodeId() const
{
  if (m_endNodeId == 0) 
    return 0;
  else
    return m_beginNodeId;
}

//-----------------------------------------------------------------------------
inline size_t
MbHexahedronTopologyExplicitIjk::getEndNodeId() const
{
  return m_endNodeId;
}

//-----------------------------------------------------------------------------
inline void
MbHexahedronTopologyExplicitIjk::setCellNodeIndices(size_t i, size_t j, size_t k, const size_t* beginId, const size_t* endId)
{
#ifndef MBMESH_DONT_USE_ASSERT
  assert( std::distance(beginId,endId) == 8 );
#endif

#ifndef MBMESH_DONT_USE_STL
  std::vector<size_t>::iterator index = m_indices.begin() + (getI(i,j,k) * 8);
#else
  size_t* index= m_indices + (getI(i,j,k) * 8);
#endif

  size_t nodeId;
  for (const size_t* it = beginId; it != endId; ++it,++index)
  {
    nodeId = *it;
    if (nodeId >= m_endNodeId) 
      m_endNodeId = nodeId + 1;
    if (nodeId < m_beginNodeId) 
      m_beginNodeId = nodeId;
    *index = nodeId;
  }
  m_timeStamp = MxTimeStamp::getTimeStamp();
}

//-----------------------------------------------------------------------------
inline std::ostream&
MbHexahedronTopologyExplicitIjk::toStream(std::ostream& s) const
{
  s << "#Hexahedron topology explicitIjk " << std::endl;
  s << "# num cells" << std::endl;
  s << getNumCells() << std::endl;

  for(size_t i=0; i<m_numI; i++)
    for(size_t j=0; j<m_numJ; j++)
      for(size_t k=0; k<m_numK; k++)
      {
        s << "# cell #("<<i<<","<<j<<","<<k<<")";
        if (hasDeadCells() && isDead(i,j,k))
             s <<"(dead)";
        s << std::endl << "( ";
        size_t pos = getI(i,j,k) * 8;
        for (size_t n = 0; n < 8; ++n)
          s << m_indices[pos + n] << " ";
        s << ")" << std::endl;
      }
  return s;
}

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif
