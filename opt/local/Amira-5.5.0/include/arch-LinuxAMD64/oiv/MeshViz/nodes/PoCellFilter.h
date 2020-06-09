/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CELL_FILTER_
#define  _PO_CELL_FILTER_

#include <MeshViz/nodes/PoNode.h>

/**
 * @DTEXT  Interface class defining a filter of cells.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *   This abstract class specifies the interface used to filter cells.
 *   Filtering cells is a way to specify which cells are used to 
 *   build the mesh representation. When the method acceptCell() returns FALSE,
 *   this cell is not taken into account by the representation. It is as if the
 *   mesh did not contain this cell.
 * 
 *   In order to define a custom cell filter, you must create a class derived 
 *   from this class. The custom cell filter
 *   can be based either on a cell's index or its value.
 *   The data set used to check if #acceptCell returns TRUE or FALSE is the current
 *   data set during the traversal selected by the field PoMesh::valuesIndexForCellFilter.
 * 
 *   WARNING: At this time, the classes inherited from PoMesh2D ignore the cell filter.
 * 
 * [OIVJAVA-WRAPPER CUSTOM_CODE]
 */

class MESHVIZ_API PoCellFilter : public PoNode {
  SO_NODE_ABSTRACT_HEADER(PoCellFilter) ;

 public:

  /**
   * Returns TRUE if the cell is accepted. Accepted cells are used to build a shape.
   * @param cell_index the index of the cell to be checked.
   * @param cell_value the value of the cell to be checked. This value is an element
   * of the scalar data set currently selected by the representation (see PoMesh::valuesIndexForCellFilter).
   */
  virtual SbBool acceptCell(int cell_index, float cell_value) const =0;


  /*----------------------------------------------------------------------------*/
 SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;
  virtual void  write(SoWriteAction *action);

 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  PoCellFilter() ;
  virtual ~PoCellFilter() ;

} ;

inline void
PoCellFilter::write(SoWriteAction *)
{}

/*----------------------------------------------------------------------------*/

#endif /* _PO_VALUE_FILTER_ */


