/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Ludovic PEINE (May 2007)
**=======================================================================*/


#ifndef  SC_GET_BOUNDING_BOX_ACTION
#define  SC_GET_BOUNDING_BOX_ACTION

#include <Inventor/actions/SoGetBoundingBoxAction.h>

class ScGetBoundingBoxAction;
class SbViewportRegion;

typedef void ScGetBoundingBoxCallback( void*, ScGetBoundingBoxAction* );

/**
 * @SCVEXT Defines a distributed bounding box action.
 * 
 * @ingroup ScaleVizAction
 * 
 * @DESCRIPTION
 * 
 * The ScGetBoundingBoxAction class provides a simple way to distribute an SoGetBoundingBoxAction
 * across a cluster. 
 *
 * Several distribution modes are available:
 *    - LOCAL_ONLY: action is only applied by the application. 
 *    - CLUSTER_ONLY: action is only applied by the OIRUs. 
 *    - ALL: both the application and the OIRUs apply the given action.
 *
 * When OIRUs are involved (i.e., in CLUSTER_ONLY and ALL modes), they apply the action 
 * on their own part of the scene graph. The application gets back the result 
 * via the callback defined by the user.
 *
 * This class can be used in all compositing modes (flat, tile, depth, and local compositing).
 *
 * @SEE_ALSO
 *    SoGetBoundingBoxAction
 *
 *
 */

class SCALEVIZ_API ScGetBoundingBoxAction : public SoGetBoundingBoxAction
{
  SO_ACTION_HEADER(ScGetBoundingBoxAction);

public:

  /**
   * Constructor. 
   *
   * @param viewportRegion  viewport region to use for picking 
   * @param distribMode     specifies the way the action should be distributed
   * @param callback        pointer to the function used to get the result of the action
   * @param userData        pointer to user data
   */
  ScGetBoundingBoxAction(
    const SbViewportRegion &viewportRegion,
    SoAction::DistribMode distribMode = SoAction::LOCAL_ONLY,
    ScGetBoundingBoxCallback* callback = NULL, 
    void* userData = NULL );

  /**
   * Destructor
   */
#ifndef HIDDEN_FROM_DOC
  ~ScGetBoundingBoxAction();
#endif // HIDDEN_FROM_DOC

  /**
   *    Applies action to the graph rooted by a node.
   */
  virtual void apply(SoNode *node);

SoINTERNAL public:
  static void initClass();
  static void exitClass();
  virtual bool mustTraverseDepth() { return true; }

private:
  // Pointer to the user callback
  ScGetBoundingBoxCallback* m_getBoundingBoxCallback;  

  // Pointer to user data
  void* m_data;
};

#endif // SC_GET_BOUNDING_BOX_ACTION

/**/
