/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CELLEDGE_
#define  _PO_CELLEDGE_

#include <MeshViz/3Ddata/PoCellShape.h>

/**
 * @DTEXT  Builds egdes of a cell of a mesh.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *    The cell is defined by its index in the current mesh (see PoCellShape).
 *    The current mesh is either the one defined by PoMesh::setMesh() or (if 
 *    this method is not called) the one defined in a special node inherited 
 *    during the traversal. This node has a type derived from PoMeshProperty.
 * @CATALOG_PARTS_INCLUDE pocelledges.cat.html
 * 
 * 
 */
class MESHVIZ_API PoCellEdges : public PoCellShape {
  
  SO_KIT_HEADER(PoCellEdges) ;
  
  SO_KIT_CATALOG_ENTRY_HEADER(groupCellEdges) ;
  // Define fields for new parts


 public:

  /**
   * Constructor.
   */
  PoCellEdges() ;

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild() ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  void drawEdges(const PbCell *cell);

 protected:
  virtual ~PoCellEdges() ;  
  // Destructor

  // Methods
  virtual void setDefaultOnNonWritingFields();
  virtual void addElementsAllCaches() ;
  virtual void preRebuild();
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_CELLEDGE_ */


