/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_SEARCH_DEPTH_OFFSET_ACTION_
#define _SO_SEARCH_DEPTH_OFFSET_ACTION_

#include <Inventor/actions/SoSearchAction.h>

#ifndef HIDDEN_FROM_DOC

/**
* Depth Offset nodes search action.
*
* @ingroup actions
*
* @DESCRIPTION
*    This is a internal pre-rendering action used by Open Inventor to 
*    compute the global scene depth offset range that will be used for
*    projection matrix modification.
*
*/
class INVENTOR_API SoSearchDepthOffsetAction : public SoSearchAction
{
  SO_ACTION_HEADER(SoSearchDepthOffsetAction);

public:
  /** Constructor. */
  SoSearchDepthOffsetAction();

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  /** Return a new instance */
  static SoAction* createCb();
};

#endif // HIDDEN_FROM_DOC

#endif // _SO_SEARCH_DEPTH_OFFSET_ACTION_
