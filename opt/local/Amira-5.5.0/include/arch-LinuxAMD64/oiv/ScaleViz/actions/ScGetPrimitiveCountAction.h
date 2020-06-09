/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Ludovic PEINE (May 2007)
**=======================================================================*/



#ifndef  SC_GET_PRIMITIVE_COUNT_ACTION
#define  SC_GET_PRIMITIVE_COUNT_ACTION

#include <Inventor/actions/SoGetPrimitiveCountAction.h>

class ScGetPrimitiveCountAction;

typedef void ScGetPrimitiveCountCallback( void*, ScGetPrimitiveCountAction* );

/**
 * @SCVEXT Defines a distributed primitive count action.
 * 
 * @ingroup ScaleVizAction
 * 
 * @DESCRIPTION
 * 
 * The ScGetPrimitiveCountAction class provides a simple way to distribute an SoGetPrimitiveCountAction
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
 *    SoGetPrimitiveCountAction
 *
 *
 */

class SCALEVIZ_API ScGetPrimitiveCountAction : public SoGetPrimitiveCountAction
{
  SO_ACTION_HEADER(ScGetPrimitiveCountAction);

public:


  /**
   * Constructor 
   *
   * @param distribMode    specify the way the action may be distributed
   * @param callback       pointer to the function used to get the result of the action
   * @param userData       pointer to user data
   */
	ScGetPrimitiveCountAction(
    SoAction::DistribMode distribMode = SoAction::LOCAL_ONLY,
    ScGetPrimitiveCountCallback* callback = NULL,
    void* userData = NULL
    );

  /**
   * Destructor
   */
#ifndef HIDDEN_FROM_DOC
  ~ScGetPrimitiveCountAction();
#endif //HIDDEN_FROM_DOC

  /**
   *    Applies action to the graph rooted by a node.
   */
  virtual void apply( SoNode* node );


SoINTERNAL public:
  static void initClass();
  static void exitClass();
  virtual bool mustTraverseDepth() { return true; }

private:
  // Callback used to get action result
  ScGetPrimitiveCountCallback* m_getPrimCountCallback;

  // Pointer to user data
  void* m_data;
};

#endif // SC_GET_PRIMITIVE_COUNT_ACTION

/**/
