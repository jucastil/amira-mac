/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MiGeometryHexahedronIjk_H
#define _MiGeometryHexahedronIjk_H

#include <MeshVizInterface/mesh/geometry/MiGeometry.h>

/**
* @DTEXT Generic geometry interface for hexahedron mesh Ijk.
* 
* @ingroup MeshIViz_Mesh_Geometry
* 
* @DESCRIPTION
*    Generic geometry interface representing a 3D grid of hexahedron cells,
*    where each hexahedron is defined explicitly with 8 independent coordinates.
*    Each hexahedron is accessible via 3 indices (i,j,k).
*
*    This type of geometry is typically used by the MiVolumeMeshVertexHexahedronIjk interface. 
* 
*    The vertices of each hexahedron are numbered as follows (see getCellCoords for more details):
* <PRE>
*                        J
*                        |
*                        |
*
*                       n3----------n2   
*                       /|          /|   
*                     /  |        /  |   
*                   /    |      /    |       
*                 n7---------n6      |   
*                  |     |    |      |    
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
*/
class MESHIVIZ_API MiGeometryHexahedronIjk : virtual public MiGeometry
{
public:
  /**
  * Returns the coordinates of the hexahedron (i,j,k) cell.
  * The vertices of each hexahedron are numbered as follows :
  *   - The first 4 vertices define the "bottom" face of the hexahedron. 
  *     This face is on the logical IJ plane K=k.
  *   - The last 4 vertices define the "top" face of the hexahedron. 
  *     This face is on the logical IJ plane K=k+1.
  * @IMAGE MiGeometryHexahedronIjk.png "Vertices numbering"
  *
  * @param i [in] the id of this hexahedron on the axis I. 0 <= i < meshTopologyIjk.getNumCellsI().
  * @param j [in] the id of this hexahedron on the axis J. 0 <= j < meshTopologyIjk.getNumCellsJ().
  * @param k [in] the id of this hexahedron on the axis K. 0 <= k < meshTopologyIjk.getNumCellsK().
  * @param v0,v7 [out] the 8 vertices of the hexahedron (i,j,k).
  */
  virtual void getCellCoords(size_t i, size_t j, size_t k, MbVec3d& v0, MbVec3d& v1, MbVec3d& v2, MbVec3d& v3,
                                                           MbVec3d& v4, MbVec3d& v5, MbVec3d& v6, MbVec3d& v7) const = 0;
};

#endif
