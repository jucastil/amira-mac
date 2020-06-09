/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_INTERVAL_CELL_FILTER_
#define  _PO_INTERVAL_CELL_FILTER_

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <MeshViz/nodes/PoCellFilter.h>

class SoFieldSensor ;

/**
 * @DTEXT Node class to define a filter of cells.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 * 
 * This filter accepts only those cells whose value is either inside or outside a float interval.
 *
 * [OIVJAVA-WRAPPER CUSTOM_CODE]
 */

class MESHVIZ_API PoIntervalCellFilter : public PoCellFilter {
  SO_NODE_HEADER(PoIntervalCellFilter) ;

 public:

  PoIntervalCellFilter() ;

  /**
   * Specifies the min limit of the float interval.
   * 
   */
  SoSFFloat min;

  /**
   * Specifies the max limit of the float interval.
   */
  SoSFFloat max;

  /**
   * Specifies if accepted cells are those whose value is inside or outside the
   * interval ]min,max[.
   * @param in If TRUE, the cell is accepted if min < v && v < max, where v is the value of cell
   * to be checked.
   * @param in If FALSE, the cell is accepted if v <= min || max <= v, where v is the value of cell
   * to be checked.
   * 
   */
  SoSFBool  in;

  /**
   * See PoCellFilter::acceptCell(). 
   * @param cell_index The cell index is ignored by this filter as it checks only 
   * the value of the cell.
   */
  SbBool acceptCell(int cell_index, float cell_value) const;

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual ~PoIntervalCellFilter() ;


 private:
  static void changeCB(void *data, SoSensor *) ;

  SbBool        m_filterChanged;
  SoFieldSensor *m_minSensor;
  SoFieldSensor *m_maxSensor;
  SoFieldSensor *m_inSensor;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_INTERVAL_CELL_FILTER_ */


