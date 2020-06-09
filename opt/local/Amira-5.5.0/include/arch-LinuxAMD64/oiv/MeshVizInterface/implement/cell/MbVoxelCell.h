/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBVOXELCELL_H
#define _MBVOXELCELL_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/cell/MiVolumeCell.h>
#include <MeshVizInterface/implement/cell/MbHexahedronCell.h>
#include <MeshVizInterface/implement/MbMeshVizImpl.h>

/**
 * @DTEXT  Defines a voxel cell of a volume mesh.
 * 
 * @ingroup MeshIViz_Implement_Cell
 * 
 * @DESCRIPTION
 *    A voxel cell is a parallelepipede of which faces are orthogonal to X, Y, Z axes.
 *    with n0 the closest to the origin.
 *    Each facet is a rectangle not necessarily a square.
 *    The 4 first indices defines a face of the voxel cell. The 4 last indices defines
 *    the opposite face.
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
 
 *    This numerotation must be respected to have the right result returned 
 *    by getVolume()
 * 
 */

class MESHIVIZIMPL_API MbVoxelCell : virtual public MbHexahedronCell
{
public:

  /**
  * Construct an empty voxel cell
  */
  MbVoxelCell():MbHexahedronCell(0,0,0,0,0,0,0,0) {}
  
  /**
  * Construct a voxel cell
  */
  MbVoxelCell(size_t n0, size_t n1, size_t n2, size_t n3,
              size_t n4, size_t n5, size_t n6, size_t n7);

  /**
  * Gets the volume of the cell.
  */
  double getVolume(const MiGeometryI* meshGeometry) const;

  virtual double getRelativeSize(const MiGeometryI* meshGeometry) const;

protected:
  /**
  * Defines a specialized output on stream for MbHexahedronCell
  */
  virtual std::ostream& toStream(std::ostream& s) const;

};

//-----------------------------------------------------------------------------
inline std::ostream& 
MbVoxelCell::toStream(std::ostream& s) const
{
  s << "MbVoxelCell (" << 
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
#  pragma warning( pop )
#endif

#endif

