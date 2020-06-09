/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CELLSHAPE_
#define  _PO_CELLSHAPE_

#include <Inventor/fields/SoSFVec3f.h>
#include <MeshViz/3Ddata/PoMesh.h>

class PbCell;

/**
 * @DTEXT  Abstract representation of a cell of a mesh.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *    The cell is defined by its index in the current mesh. The current
 *    mesh is either the one defined by PoMesh::setMesh() or (if this 
 *    method is not called) the one defined in a special node inherited during
 *    the traversal. This node has a type derived from PoMeshProperty.
 * 
 */
class MESHVIZ_API PoCellShape : public PoMesh {
  
  SO_KIT_HEADER(PoCellShape) ;
  

 public:

  /**
   * Constructor.
   */
  PoCellShape() ;

  /* Fields */

  /**
   * Cell index.
   */
  SoSFInt32 cellIndex;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  // Destructor
  virtual ~PoCellShape() ;  

  // Methods
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields();

 private:
  // Sensors
  FieldSensorList m_fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     m_fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_CELLSHAPE_ */


