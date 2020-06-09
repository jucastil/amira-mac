/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MiHexahedronTopologyExplicitIjk_H
#define _MiHexahedronTopologyExplicitIjk_H

#include <MeshVizInterface/mesh/MiMeshIjk.h>
#include <MeshVizInterface/mesh/topology/MiTopologyIjk.h>

//-----------------------------------------------------------------------------
/**
* @DTEXT List of volume cells interface.
* 
* @ingroup MeshIViz_Mesh_Topology
* 
* @DESCRIPTION
*    A generic abstract interface for an unstructured explicit hexahedron volume mesh topology. @BR
*
*    Each hexahedron cell has 6 faces which can be in any plane of
*    the 3D space. Each face is a quadrangle not necessarily a square.
*    The 4 first indices define the polygon of a face of the
*    hexahedron. The 4 last indices define the polygon of the 
*    opposite face.
*
*    Facets and nodes are numbered as follows :
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
*
* @SEE_ALSO
*   MbHexahedronTopologyExplicitIjk
* 
*/
class MiHexahedronTopologyExplicitIjk : public MiTopologyIjk
{
public:
  /**
  * Returns the 8 indices of a cell of this topology. The cell 
  * is identified by three ids i,j,k.
  */
  virtual void getCellNodeIndices(size_t i, size_t j, size_t k, size_t& n0, size_t& n1, size_t& n2, size_t& n3,
                                                                size_t& n4, size_t& n5, size_t& n6, size_t& n7)  const = 0;

  /**
  * Hint about cells organization in memory. 
  * This information aims at optimizing the topology traversal for extractors.
  * Returns the topology internal cells layout in memory as 6 enum values covering all possible cases. 
  * For instance LAYOUT_KJI means that: 
  *   - the cell (i+1,j,k) is consecutive in memory to the cell (i,j,k) and,
  *   - the row of cells (j+1,k) is consecutive in memory to the row of cells (j,k) and,
  *   - the slice of cells (k+1) is consecutive in memory to the slice of cells (k) 
  * The fastest way to go through the cells with such layout is to perform the following triple loop
  * @verbatim
    for each k with 0 <= k < numK
     for each j with 0 <= j < numJ
       for each i with 0 <= i < numI
         topology.getCellNodeIndices(i,j,k,n0, ... ,n7);
    @endverbatim
  * The default implementation returns LAYOUT_UNKNOWN meaning that the cell storage organization is unknown, 
  * for instance when cells are computed on the fly.
  * In that case, extractors perform the topology traversal in the way that minimizes the required 
  * memory for their algorithms. 
  */
  virtual MiMeshIjk::StorageLayout getStorageLayout() const { return MiMeshIjk::LAYOUT_UNKNOWN; }

  /**
  * @copydoc MiVolumeTopologyExplicitI::getEndNodeId()
  */
  virtual size_t getEndNodeId() const = 0;

  /**
  * @copydoc MiVolumeTopologyExplicitI::getBeginNodeId()
  */
  virtual size_t getBeginNodeId() const { return 0; }

 /** 
  * Returns the name of the node.
  * The default implementation returns the node identifier as a string.
  * @param i the index of the node 
  */ 
  virtual std::string getNodeName(size_t i) const { 
    std::ostringstream strstream;
    strstream << i ;
    return strstream.str();
  }

};


#endif
