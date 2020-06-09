/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_3D_DATA_MASTER_
#define  _PO_3D_DATA_MASTER_

#include <MeshViz/graph/PoBase.h>

/**
 * @DTEXT  Base class for all 3DdataMaster objects
 * 
 * @ingroup Mesh
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZ_API Po3DdataMaster : public PoBase {

  SO_KIT_HEADER(Po3DdataMaster) ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
  static void initClasses() ;
	static void exitClass() ;
	static void exitClasses() ;

 protected:
  // Constructor
  Po3DdataMaster() ;
  // Destructor
  virtual ~Po3DdataMaster() ;  
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_3D_DATA_MASTER_ */

