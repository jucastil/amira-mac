/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _MO_ACTIONNODE_
#define  _MO_ACTIONNODE_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/actions/SoDistributeAction.h>
#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>

/**
* @DTEXT Utility class that provides default action handling for MeshViz nodes.
* 
* @ingroup MeshIViz_Mapping_Attributes
*/

class MESHIVIZDM_API MoActionNode : public SoNode {
	SO_NODE_ABSTRACT_HEADER(MoActionNode) ;

SoEXTENDER public:

  // These virtual functions implement all of the actions for nodes
  // Most of the default implementations call doAction().
  virtual void GLRender(SoGLRenderAction * action);
  virtual void callback(SoCallbackAction * action);
  virtual void getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void getMatrix(SoGetMatrixAction * action);
  virtual void handleEvent(SoHandleEventAction * action);
  virtual void pick(SoPickAction * action);
  virtual void rayPick(SoRayPickAction *action);
  virtual void search(SoSearchAction * action);
  virtual void write(SoWriteAction *action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);
  virtual void distribute(SoDistributeAction *action);

SoINTERNAL public:

  static void initClass();
  static void exitClass();

protected:

  MoActionNode();
  virtual ~MoActionNode();

};

#endif /* _MO_ACTIONNODE_  */

