/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (01 2010)
**=======================================================================*/

#if !defined(SO_ERROR_STACK_H)
#define  SO_ERROR_STACK_H

#include <Inventor/errors/SoError.h>

/**
* @VSGEXT Stack debugging handler.
*
* @ingroup errors
*
* @DESCRIPTION
*   SoStackError is used to obtain and/or report the program callstack. 
*
*   The post() method gets the actual callstack and calls a custom callback, 
*   if one is defined, else it dumps the callstack using SoDebugError.
*
*   It is also possible to allow SoStackError to automaticaly report the callstack, 
*   when a signal is reported by the system, by setting OIV_DEBUG_STACKERROR to 1.
*
* @SEE_ALSO
*    SoReadError
*/

class INVENTORBASE_API SoErrorStack : public SoError 
{
public:

  /**
   * This struture contains the description of a stack frame.
   */
  struct StackFrame
  {
    int frameIndex; // Index of this frame in the callstack, 0 is top one.

    SbString functionName; // Function reached in this frame.
    int lineNumber; // Line number in the frame.

    SbString moduleName;  // Module which contains the function.
    SbString moduleDescription; // More information about the module (Type, fullpath...)
  };
  
  /**
   * Sets the handler callback for the SoErrorStack class.
   *
   * @param cb The error callback.
   * @param data Custom data forwarded to the callback, can be NULL.
   */
  static void setHandlerCallback(SoErrorCB *cb, void *data);

  /**
   * Returns the handler callback for the SoErrorStack class.
   *
   * @return The SoErrorCB specified by the setHandlerCallback function.
   */
  static SoErrorCB *getHandlerCallback();

  /**
   * Returns the handler callback data for the SoErrorStack class.
   *
   * @return The void* pointer specified by the setHandlerCallback function.
   */
  static void* getHandlerData();

  /**
   * Returns the type identifier for the SoErrorStack class.
   */
  static SoType getClassTypeId();

  /**
   * Returns the type identifier for an instance of SoErrorStack.
   */
  virtual SoType getTypeId() const;

  /**
   * Posts the current callstack to the application callback or to 
   * SoDebugError if the custom callback was not specified.
   */
  static void post();

  /**
   * Returns the stack frames of the current callback stack.
   *
   * This function is useful to get the stack frames when the 
   * custom callback is called.
   *
   * @return The list of frames in the actual callstack.
   */
  std::vector< SoErrorStack::StackFrame > getStackFrames() const;

  /**
   * This function returns a decoded version of the getStackFrames() function.
   *
   * @return A string which contains a human readable version of the stack.
   */
  SbString getStack() const;

 SoINTERNAL public:

  // Initializes SoErrorStack class
  static void initClass();
  static void exitClass();

private:

  SoErrorStack();
  virtual ~SoErrorStack();

  // Signals handler.
  static void signalHandler(int signo);

  static  SoType s_classTypeId; // Type id of SoDebugError class
  static  SoErrorCB* s_handlerCB; // Handler callback for class
  static  void* s_cbData; // User data for callback

  typedef void (*tHandler)(int);

  // We keep the old handlers in case of, if they are not null we'll call them 
  // in the handler.
  static tHandler s_handlerSIGINT;
  static tHandler s_handlerSIGILL;
  static tHandler s_handlerSIGFPE;
  static tHandler s_handlerSIGSEGV;
  static tHandler s_handlerSIGTERM;
  static tHandler s_handlerSIGABRT;

  // Data for the custom callbacks.
  std::vector< SoErrorStack::StackFrame > m_stack;
  SbString m_decodedStack;
};


#endif // SO_ERROR_STACK_H

