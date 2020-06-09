/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Mott (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_CALLBACK_LIST_
#define  _SO_CALLBACK_LIST_

#include <Inventor/SbPList.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoCallbackList
//
//////////////////////////////////////////////////////////////////////////////

// Callback functions that are registered with this class should
// be cast to this type.
typedef void SoCallbackListCB(void *userData, void *callbackData);

/**
 * Manages a list of \oivnetdoc delegates \else callbacks \endoivnetdoc and associated data.
 * 
 * @ingroup General
 * 
 * @DESCRIPTION
 *   This class manages a list of \oivnetdoc delegates \else callbacks \endoivnetdoc and user data. The user can add
 *   a \oivnetdoc delegate \else callback \endoivnetdoc to the list, along with user data. When the \oivnetdoc delegate \else callback \endoivnetdoc is
 *   invoked, it is passed this user data, along with \oivnetdoc delegate \else callback \endoivnetdoc data specified by the
 *   invoking routine. The type of this \oivnetdoc delegate \else callback \endoivnetdoc data is determined by the invoking
 *   routine.
 * 
 * 
 * [OIV-WRAPPER-NO-WRAP]
 */ 

class INVENTOR_API SoCallbackList {
    
 public:

  /**
   * Constructor.
   */
  SoCallbackList();
  /**
   * Destructor.
   */
  ~SoCallbackList();
  
  /**
   * Adds a function to the list of callback functions.
   * At callback time, f will be called with userData as the first
   * parameter, and callback specific data as the second parameter.
   * e.g. (*f)(userData, callbackData);
   */
  void addCallback(SoCallbackListCB *f, void *userData = NULL);
  /**
   * Removes a function from the list of callback functions.
   */
  void removeCallback(SoCallbackListCB *f, void *userData = NULL);
    
  /**
   * Clears all callback functions from the list.
   */
  void clearCallbacks() { list.truncate(0); }
  /**
   * Returns the number of callback functions in the list.
   */
  int getNumCallbacks() const { return list.getLength(); }

  /**
   * Invokes each callback function in the list, passing each function the user data
   * supplied when they were registered here, and @B callbackData @b, the
   * callback-specific data supplied by the caller.
   */
  void invokeCallbacks(void *callbackData);
  
  /**
  * Set the callbacks enabled state.  Callbacks are enabled by default.
  * If callbacks are disabled, invokeCallbacks has no effect.
  */
  void enable(SbBool enableCallbacks){ m_enable = enableCallbacks;}

 private:
  
   //If set tofalse, callbacks will have no effect
   SbBool m_enable;

  // callbackList holds a list of functions and user data
  SbPList list;

};

#endif  /* _SO_CALLBACK_LIST_ */

