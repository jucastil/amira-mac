/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_CALLBACK_
#define  _SO_CALLBACK_

#include <Inventor/SbLinear.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoCallback
//
//  The SoCallback node is a general mechanism that allows
//  applications to insert callback functions into a scene graph. The
//  callback function registered with the node is called each time
//  that node is traversed to perform any scene graph action. When the
//  callback function is called, it is passed a pointer to the action
//  being traversed and a user-data pointer that is registered with
//  the callback function. A NULL callback function pointer means that
//  no function will be called.
//
//////////////////////////////////////////////////////////////////////////////

/** Callback functions registered with this node should be of this type.
 * [OIV-WRAPPER NAME{CallbackCB}]
 */
typedef void SoCallbackCB(void *userData, SoAction *action);

#ifdef OIV_NET_DOC
/**
* Provides custom behavior during actions.
* 
* @ingroup nodes
* 
* @DESCRIPTION
*   This node provides a general mechanism for inserting delegates into a
*   scene graph. The delegate registered with the node is called each time
*   the node is traversed while performing any scene graph action. A reference to the action 
*	being performed and a user data are passed as invocation arguments. 
* 
* @FILE_FORMAT_DEFAULT
*    Callback {
*    @TABLE_FILE_FORMAT
*    @TABLE_END
*    }
* 
* @ACTION_BEHAVIOR
*    SoGLRenderAction,  SoGetBoundingBoxAction,  SoPickAction @BR
*        Calls the specified delegate for all actions.
* 
* 
* @SEE_ALSO
*    SoAction,
*    SoCallbackAction,
*    SoEventCallback
* 
* 
*/ 
#else
/**
* Provides custom behavior during actions.
* 
* @ingroup nodes
* 
* @DESCRIPTION
*   This node provides a general mechanism for inserting callback functions into a
*   scene graph. The callback function registered with the node is called each time
*   the node is traversed while performing any scene graph action. The callback
*   function is passed a pointer to the action being performed and a user data
*   pointer registered with the callback function. You can use this node to make
*   nonstandard OpenGL calls while rendering. If you do, be careful not to interfere
*   with Open Inventor's use of OpenGL.
*   
*   If you use a callback node for GL rendering, you should be careful to follow
*   render caching rules. If your callback node can make different rendering calls
*   each time it is traversed, it cannot be cached. In such a case, the node should
*   invalidate any open caches, as in the following example:
*   <PRE> 
*    void myCallbackFunc(void *d, SoAction *action) {
*      if ( action->isOfType(SoGLRenderAction::getClassTypeId()) ) { 
*        // Make my custom GL calls
*        ((MyClass *) d)->myRender();
*    
*        // Invalidate the state so that a cache is not made
*        SoCacheElement::invalidate(action->getState());
*      }
*    }
*   </PRE>
* 
* @FILE_FORMAT_DEFAULT
*    Callback {
*    @TABLE_FILE_FORMAT
*    @TABLE_END
*    }
* 
* @ACTION_BEHAVIOR
*    SoGLRenderAction,  SoGetBoundingBoxAction,  SoPickAction @BR
*        Calls the specified callback function for all actions.
* 
* 
* @SEE_ALSO
*    SoAction,
*    SoCallbackAction,
*    SoEventCallback
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoCallback : public SoNode {

  SO_NODE_HEADER(SoCallback);

 public:
  /**
   * Creates a callback node with default settings.
   */
  SoCallback();

  /**
   * Sets pointer to callback function and user data. By default, the function
   * pointer in the node is NULL and does nothing.
   * [OIV-WRAPPER EVENT_NAME{CallbackHandler}]
   */
  void setCallback(SoCallbackCB *func, void *localUserData = NULL)
    { callbackFunc = func; callbackData = localUserData; }

 SoEXTENDER public:

  // Traversal methods for all the actions:
  virtual void doAction(SoAction *action);
  virtual void callback(SoCallbackAction *action);
  virtual void GLRender(SoGLRenderAction *action);
  virtual void getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void getMatrix(SoGetMatrixAction *action);
  virtual void handleEvent(SoHandleEventAction *action);
  virtual void pick(SoPickAction *action);
  virtual void search(SoSearchAction *action);
  virtual void write(SoWriteAction *action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);
  
 SoINTERNAL public:

  static void initClass();
  static void exitClass();
  
 protected:

  virtual ~SoCallback();
  
  // Copies the contents of the given node into this instance
  virtual void copyContents(const SoFieldContainer *fromFC,
                            SbBool copyConnections);
  
 private:

  // Function to call
  SoCallbackCB *callbackFunc;
  // User data to pass it
  void *callbackData;
};

#endif /* _SO_CALLBACK_ */

