/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MBHEXAHEDRONMESHIJK_H
#define  _MBHEXAHEDRONMESHIJK_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiVolumeMeshHexahedronIjk.h>
#include <MeshVizInterface/implement/mesh/MbMesh.h>
#include <MeshVizInterface/implement/mesh/MbMeshIjk.h>
#include <MeshVizInterface/implement/topology/MbHexahedronTopologyExplicitIjk.h>
#include <MeshVizInterface/MbVec3.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/iostream>

/**
 * @DTEXT  Defines a meshIjk of hexahedrons as a pillar mesh.
 * 
 * @ingroup MeshIViz_Implement_Mesh
 * 
 * @DESCRIPTION
 *
 * Hexahedrons are defined as follows:
 *
 * <PRE>
 *                        S
 *                        |
 *                        |
 *
 *                       n3----------n2       
 *                       /|          /|   
 *                     /  |        /  |   
 *                   /    |      /    |      
 *                 n7---------n6      |  
 *                  |     |    |      |    
 *                  |    n0----|-----n1    --- R               
 *                  |    /     |     /                    
 *                  |  /       |   /                      
 *                  |/         | /                        
 *                 n4---------n5                          
 *             
 *               /
 *             /
 *           T
 * </PRE>
 * 
 */
template <typename _CoordT=MbVec3d, typename _ScalarT=double, typename _Vec3T=MbVec3d>
class MbHexahedronMeshIjk : public MiVolumeMeshHexahedronIjk, public MbMesh<_CoordT,_ScalarT,_Vec3T>,
                            public MbMeshIjk<_ScalarT,_Vec3T>
{

public:
  /**
  * Constructor of an empty mesh. 
  */
  MbHexahedronMeshIjk(size_t numCellI, size_t numCellJ, size_t numCellK) :
  m_topology(numCellI,numCellJ,numCellK)
  { 
  }
  /**
   * Constructor of a volume mesh. 
   */
  template <typename _Vec3Iter>
  MbHexahedronMeshIjk(size_t numCellI, size_t numCellJ, size_t numCellK,
                      _Vec3Iter beginCoord, _Vec3Iter endCoord);

  const MiHexahedronTopologyExplicitIjk& getTopology() const 
  {
    return m_topology;
  }

  /**
  * Defines hexahedron cell indices
  */
  template <typename _NodeIdIter>
  void setCellNodeIndices(size_t i, size_t j, size_t k,
                          _NodeIdIter beginId, _NodeIdIter endId)
  {
    m_topology.setCellNodeIndices(i,j,k,beginId,endId);
  }

  /**
  * Defines dead cells
  */
  void setDeadCell(size_t i, size_t j, size_t k, bool isDead=true)
  {
    m_topology.setDeadFlag(i,j,k,isDead);
  }

  void touch()
  {
    m_topology.touch();
    this->m_geometry.touch();
  }

protected:
  virtual std::ostream& toStream(std::ostream& s) const;

  MbHexahedronTopologyExplicitIjk m_topology;

};


//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
template <typename _Vec3Iter>
inline MbHexahedronMeshIjk<_CoordT,_ScalarT,_Vec3T>::MbHexahedronMeshIjk(
  size_t numCellI, size_t numCellJ, size_t numCellK,
  _Vec3Iter beginCoord, _Vec3Iter endCoord
  ) :
 MbMesh<_CoordT,_ScalarT,_Vec3T>(beginCoord,endCoord),
 m_topology(numCellI,numCellJ,numCellK)
{
}

//-----------------------------------------------------------------------------
template <typename _CoordT, typename _ScalarT, typename _Vec3T>
inline std::ostream& 
MbHexahedronMeshIjk<_CoordT,_ScalarT,_Vec3T>::toStream(std::ostream& s) const
{
  s << "# MbHexahedronMeshIjk" << std::endl;
  // output the inherited geometry and dataset
  MiVolumeMeshHexahedronIjk::toStream(s);
  MbMesh<_CoordT,_ScalarT,_Vec3T>::toStream(s);
  MbMeshIjk<_ScalarT,_Vec3T>::toStream(s);
  return s;

}

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif







