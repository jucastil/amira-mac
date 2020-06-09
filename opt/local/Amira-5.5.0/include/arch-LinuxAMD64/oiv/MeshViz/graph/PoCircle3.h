/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CIRCLE3_
#define  _PO_CIRCLE3_

#include <MeshViz/graph/PoGraphMaster.h>

/**
 * @DTEXT  Abstract class for 3D circle representation.
 * 
 * @ingroup GraphMisc
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZ_API PoCircle3 : public PoGraphMaster {
  
  SO_KIT_HEADER(PoCircle3) ;
  
  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(circle3) ;
  

 public:

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  PoCircle3() ;
  // Conctructor

  virtual ~PoCircle3() ;
  // Destructor

  virtual void   setDefaultOnNonWritingFields() ;
  // Methods
} ;
/*----------------------------------------------------------------------------*/

#endif /*  _PO_CIRCLE3_ */

