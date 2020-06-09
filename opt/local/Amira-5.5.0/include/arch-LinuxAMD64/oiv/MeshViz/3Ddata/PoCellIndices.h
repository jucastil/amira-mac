/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CELLINDICE_
#define  _PO_CELLINDICE_

#include <MeshViz/3Ddata/PoCellShape.h>

/**
 * @DTEXT  Builds text indices of a cell of a mesh.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *    The node's indices and the cell's index are visualized.
 *    The node index in the mesh and node's relative index in the
 *    cell are both displayed. For instance if the 3rd node index 
 *    of a cell is 3218, the string "n3 = 3128" is drawn 
 *    near this node's position. This allows you to check node 
 *    ordering in a cell.
 *  
 *    The strings can be moved away or brought nearer the node position 
 *    by using the #offset field.
 * 
 *    The cell is defined by its index in the current mesh (see PoCellShape).
 *    The current mesh is either defined by PoMesh::setMesh() or (if 
 *    this method is not called) defined in a special node inherited 
 *    during traversal. This node has a type derived from PoMeshProperty.
 * @CATALOG_PARTS_INCLUDE pocellindices.cat.html
 * 
 * 
 */
class MESHVIZ_API PoCellIndices : public PoCellShape {
  
  SO_KIT_HEADER(PoCellIndices) ;
  
  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(nodesIndexSep);
  SO_KIT_CATALOG_ENTRY_HEADER(nodesIndexApp);
  SO_KIT_CATALOG_ENTRY_HEADER(nodesIndexGroup);

  SO_KIT_CATALOG_ENTRY_HEADER(cellIndexSep);
  SO_KIT_CATALOG_ENTRY_HEADER(cellIndexApp);
  SO_KIT_CATALOG_ENTRY_HEADER(cellIndexGroup);


 public:

  /**
   * Constructor.
   */
  PoCellIndices() ;

  /* Fields */

  /**
   * Factor of the cell's size that specifies the distance of the 
   * nodes indices representation to the position of these nodes.
   */
  SoSFFloat offset;  

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild() ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual ~PoCellIndices() ;  
  // Destructor.

  // Methods
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields();

 private:
  // Sensors
  FieldSensorList m_fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     m_fieldList ;

  void drawNodesIndex(const PbCell *cell, SoGroup *group);
  void drawCellIndex(const PbCell *cell, SoGroup *group);
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_CELLINDICE_ */


