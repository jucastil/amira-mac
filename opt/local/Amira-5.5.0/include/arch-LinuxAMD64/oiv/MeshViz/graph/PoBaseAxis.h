/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_BASE_AXIS_
#define  _PO_BASE_AXIS_

#include <MeshViz/graph/PoGraphMaster.h>

/**
 * @DTEXT  Base class for all axis objects.
 * 
 * @ingroup GraphAxis
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZ_API PoBaseAxis : public PoGraphMaster {

  SO_KIT_HEADER(PoBaseAxis) ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  PoBaseAxis(SoCallbackCB *actionCallback=NULL) ;
  // Constructor

  virtual ~PoBaseAxis() ;  
  // Destructor
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_BASE_AXIS_  */

