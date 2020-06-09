/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MICELLFILTERIJK_H
#define _MICELLFILTERIJK_H

#include <MeshVizInterface/mesh/cell/MiCellFilter.h>

/**
* @DTEXT  Interface class defining a cell filter for structured volume meshes.
* 
* @ingroup MeshIViz_Mesh_Cell
* 
* @DESCRIPTION
*   This abstract class specifies the interface used for filtering cells on structured volume meshes.@BR
*
*   Filtering cells is a way to specify which cells are used to 
*   build the mesh representation. @BR
*
*   When the method acceptCell(i,j,k) returns false,
*   the cell specified by (i,j,k) is not taken into account by the extraction. 
*   It is as if the mesh does not contain this cell.@BR
* 
*   In order to define a custom cell filter for a structured volume mesh, create a class derived 
*   from this class. 
*
* @SEE_ALSO
*   MoCellFilter
* 
*/
class MiCellFilterIjk : virtual public MiCellFilter
{
public:
  /**
  * Returns true if the cell is accepted. Accepted cells are used to during the extract process.
  * @param (i,j,k) indexes of the cell to be checked.
  */
  virtual bool acceptCell(size_t i, size_t j, size_t k) const =0;
};



#endif







