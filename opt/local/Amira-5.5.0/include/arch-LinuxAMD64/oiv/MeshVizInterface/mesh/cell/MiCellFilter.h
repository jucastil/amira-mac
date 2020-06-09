/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MICELLFILTER_H
#define _MICELLFILTER_H

#include <MeshVizInterface/MxMeshIViz.h>

/**
* @DTEXT  Interface class defining a cell filter.
* 
* @ingroup MeshIViz_Mesh_Cell
* 
* @DESCRIPTION
*   This abstract class specifies the interface used for filtering cells.@BR
*
*   Filtering cells is a way to specify which cells are used and which cells are ignored during the mesh extraction.@BR
*
*   Each class implementing MiCellFilter must implement an
*   acceptCell() method with either 1, 2 or 3 indices as arguments.@BR
*
*   When the acceptCell() method returns false, the cell identified
*   by these indices is not taken into account by the extraction. 
*   It is as if the mesh does not contain this cell.@BR
* 
*   In order to define a custom cell filter, create a class derived 
*   from one of the following classes. 
* 
*   @see MiCellFilterI
*   @see MiCellFilterIj
*   @see MiCellFilterIjk
*
*/
class MiCellFilter 
{
public:
  virtual ~MiCellFilter() {}

  /**
  * Returns a time stamp on this filter. When the content of the filter 
  * changes, the time stamp must increase. The time stamp allows MeshViz 
  * to be aware about any change to this filter.
  */
  virtual size_t getTimeStamp() const = 0;
};

#endif 







