/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_PROFILE_
#define  _PO_PROFILE_

#include <MeshViz/nodes/PoNode.h>

/**
 * @DTEXT  Abstract base class for all profile nodes.
 * 
 * @ingroup GraphProperty
 * 
 * @DESCRIPTION
 *    This node is the abstract base for profile nodes.
 *    A profile defines a 2D polygon which is used for charting representations
 *    which use them to build their geometry.
 * 
 */

class MESHVIZ_API PoProfile : public PoNode {
  
  SO_NODE_ABSTRACT_HEADER(PoProfile) ;
  

 public:

  /*----------------------------------------------------------------------------*/

  
 SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;
  
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  PoProfile() ;
  // Constructor.
  
  virtual ~PoProfile() ;
  
} ;
/*----------------------------------------------------------------------------*/

#endif /* _PO_PROFILE_ */

