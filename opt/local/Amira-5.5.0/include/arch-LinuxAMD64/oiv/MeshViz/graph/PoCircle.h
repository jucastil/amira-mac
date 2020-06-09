/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CIRCLE_
#define  _PO_CIRCLE_

#include <MeshViz/graph/PoGraphMaster.h>

/**
 * @DTEXT  Abstract class for 2D circle representation.
 * 
 * @ingroup GraphMisc
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZ_API PoCircle : public PoGraphMaster {
  
  SO_KIT_HEADER(PoCircle) ;
  
  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(circle) ;
  

 public:

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  PoCircle() ;
  // Conctructor

  virtual ~PoCircle() ;
  // Destructor

  virtual void   setDefaultOnNonWritingFields() ;
  // Methods
} ;
/*----------------------------------------------------------------------------*/

#endif /*  _PO_CIRCLE_ */

