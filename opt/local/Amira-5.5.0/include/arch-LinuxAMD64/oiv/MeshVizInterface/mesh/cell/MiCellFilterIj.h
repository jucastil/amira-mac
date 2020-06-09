/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MICELLFILTERIJ_H
#define _MICELLFILTERIJ_H

#include <MeshVizInterface/mesh/cell/MiCellFilter.h>

/**
* @DTEXT  Interface class defining a cell filter for structured surface meshes.
* 
* @ingroup MeshIViz_Mesh_Cell
* 
* @DESCRIPTION
*   This abstract class specifies the interface used for filtering cells on structured surface meshes.@BR
*
*   Filtering cells is a way to specify which cells are used to 
*   build the mesh representation. @BR
*   
*   When the method acceptCell(i,j) returns false,
*   the cell specified by (i,j) is not taken into account by the extraction. 
*   It is as if the mesh does not contain this cell.@BR
* 
*   In order to define a custom cell filter for a structured surface mesh, create a class derived 
*   from this class. 
*
* @SEE_ALSO
*   MoCellFilter
* 
*/
class MiCellFilterIj : virtual public MiCellFilter
{
public:
  /**
  * Returns true if the cell is accepted. Accepted cells are used during the extraction process.
  * @param (i,j) indices of the cell to be checked.
  */
  virtual bool acceptCell(size_t i, size_t j) const =0;
};



#endif 







