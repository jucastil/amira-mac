/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _MO_CELLFILTER_
#define  _MO_CELLFILTER_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoNode.h>

#include <MeshVizInterface/mapping/nodes/MoActionNode.h>
#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>
 
class MiCellFilter;
class MiCellFilterI;
class MiCellFilterIj;
class MiCellFilterIjk;

/**
 * @DTEXT Property node that defines a cell filter.
 * 
 * @ingroup MeshIViz_Mapping_Attributes
 * 
 * @DESCRIPTION
 *   Filtering cells is a way to specify which cells are used and which cells are ignored during a mesh extraction.
 *   The application must create a class implementing the MiCellFilter interface.
 *   A cell filter class must implement the method
 *   acceptCell() with either 1, 2 or 3 indices as arguments.
 *   When the method acceptCell() returns false, the cell identified
 *   by these indices is not taken into account by the extraction. 
 *   It is as if the mesh does not contain this cell.
 *
 * @note each time the MiCellFilter is updated, setCellFilter() or touch() must be called
 * to mark the node has modified.
 *
 * @FILE_FORMAT_DEFAULT
 *    CellFilter {
 *    @TABLE_FILE_FORMAT
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *   Sets the current cell filter.  See MoCellFilterElement.
 *
 * @SEE_ALSO
 *    MiCellFilter, MiCellFilterI, MiCellFilterIj, MiCellFilterIjk
 * 
 */
class MESHIVIZDM_API MoCellFilter : public MoActionNode {

  SO_NODE_HEADER(MoCellFilter) ;
  
 public:

  /**
   * Constructor.
   */
  MoCellFilter() ;

  //@{
  /**
   * Sets the cell filter interface. Marks this node as modified by calling touch(). 
   */
  virtual void setCellFilter(MiCellFilterI* cellFilterI);
  virtual void setCellFilter(MiCellFilterIj* cellFilterIj);
  virtual void setCellFilter(MiCellFilterIjk* cellFilterIjk);
  //@}

  /**
  * Reset the cell filter interface to NULL (as if setCellFilter was given a NULL pointer). 
  * Marks this node as modified by calling touch()
  * 
  */
  virtual void reset();

  /**
   * Gets the cell filter interface.
   * Use RTTI to find out which derived class it is.
   */
  virtual const MiCellFilter* getCellFilter();

 /*----------------------------------------------------------------------------*/
  SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
  SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

protected:
  virtual ~MoCellFilter() ;

  MiCellFilter* m_cellFilter;
  CellFilterType m_cellFilterType;

} ; 

#endif /* _MO_CELLFILTER_  */

