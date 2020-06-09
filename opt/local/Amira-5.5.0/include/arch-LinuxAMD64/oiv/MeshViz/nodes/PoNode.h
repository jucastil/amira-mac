/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_NODE_
#define  _PO_NODE_

#include <Inventor/nodes/SoNode.h>

/**
 * @DTEXT  Abstract base class for all MeshViz nodes.
 * 
 * @ingroup MeshVizMisc
 * 
 * @DESCRIPTION
 *   This node is the abstract base class for all MeshViz nodes.
 * 
 */

class MESHVIZ_API PoNode : public SoNode {
  SO_NODE_ABSTRACT_HEADER(PoNode) ;

 SoEXTENDER public:
  virtual void  doAction(SoAction *action) =0;
  virtual void  callback(SoCallbackAction *action) ;
  virtual void  GLRender(SoGLRenderAction *action) ;
  virtual void  getBoundingBox(SoGetBoundingBoxAction *action) ;
  virtual void  getMatrix(SoGetMatrixAction *action) ;
  virtual void  handleEvent(SoHandleEventAction *action) ;
  virtual void  pick(SoPickAction *action) ;
  virtual void  search(SoSearchAction *action) ;
  virtual void  write(SoWriteAction *action) ;
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);


  /*----------------------------------------------------------------------------*/
  
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  static void initClasses() ;
	static void exitClasses() ;
  
 protected:
  PoNode() ;
  virtual ~PoNode() ;   
} ; 
/*----------------------------------------------------------------------------*/

#endif /* _PO_NODE_ */

