/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_GRAPH_MASTER_
#define  _PO_GRAPH_MASTER_

#include <MeshViz/graph/PoBase.h>


/**
 * @DTEXT  Abstract base class for all Graph Master classes. 
 * 
 * @ingroup graph
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZ_API PoGraphMaster : public PoBase {

  SO_KIT_ABSTRACT_HEADER(PoGraphMaster) ;

  /*----------------------------------------------------------------------------*/

 PoINTERNAL public:
  static void initClass() ;
  static void initClasses() ;
	static void exitClass() ;
	static void exitClasses() ;

 protected:
  PoGraphMaster(SoCallbackCB *actionCallback=NULL) ;
  // Constructor

  virtual ~PoGraphMaster() ;  
  // Destructor

  virtual void   copyContents(const SoFieldContainer *fromFC,
                                   SbBool copyConnections); 
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_GRAPH_MASTER_  */

