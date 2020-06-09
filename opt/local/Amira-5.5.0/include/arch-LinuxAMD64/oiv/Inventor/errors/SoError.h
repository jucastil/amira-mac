/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (Feb 2010)
**=======================================================================*/

#ifndef  _SO_ERROR
#define  _SO_ERROR

#include <Inventor/SbBase.h>
#include <Inventor/SbString.h>
#include <Inventor/SoTypedObject.h>

class SoError;
class SoBase;
class SoEngine;
class SoNode;
class SoPath;

/**
 * Error handling callbacks are of this type.
 * [OIV-WRAPPER NAME{ErrorCallback}]
 */
typedef void    SoErrorCB(const SoError *error, void *data);

/**
 * Error handling base class.
 *
 * @ingroup errors
 *
 * @DESCRIPTION
 *   SoError is the base class for all error classes, which provide error handling
 *   for applications. There are two facets to errors: posting and handling. An error
 *   is posted when some bad condition occurs. Posting is done primarily by the Open
 *   Inventor library itself, but extenders can post their own errors. Posting an
 *   error creates an instance of the appropriate error class (or subclass) and then
 *   passes it to the active error handler. The default handler just prints an
 *   appropriate message to stderr. Applications can override this behavior by
 *   supplying a different handler (by specifying a \oivnetdoc delegate \else callback \endoivnetdoc).
 *   Some implementations of the Open Inventor window system specific layer provide
 *   alternate ways to display an error message, for example SoConsole.
 *
 *   Each subclass of SoError supports the setHandlerCallback() method, which
 *   is used to set the \oivnetdoc delegate \else callback \endoivnetdoc to handle errors. The \oivnetdoc delegate \else callback \endoivnetdoc for
 *   a specific error class is always used in preference to that of any base classes
 *   when handling errors. The error instance passed to a \oivnetdoc delegate \else callback \endoivnetdoc is \oivnetdoc disposed \else deleted \endoivnetdoc
 *   immediately after the \oivnetdoc delegate \else callback \endoivnetdoc is called; an application that wishes to save
 *   information from the instance has to copy it out first.
 *
 *   Each error class contains a run-time class type id (SoType) that can be used to
 *   determine the type of an instance. The base class defines a character string
 *   that represents a detailed error message that is printed by the default handler.
 *   All handlers are called by the SoError::handleError() method. When debugging,
 *   you can set a breakpoint on this method to stop right before an error is
 *   handled.
 *
 * @SEE_ALSO
 *    SoDebugError,
 *    SoMemoryError,
 *    SoReadError,
 *    SoGLError
 *
 */

class INVENTORBASE_API SoError: public SoTypedObject {

 public:
  /**
   * Sets handler callback for SoError class.
   */
  static void setHandlerCallback(SoErrorCB *cb, void *data);
  /**
   * Returns handler callback for SoError class.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  static SoErrorCB* getHandlerCallback();
  /**
   * Returns handler data for SoError class.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  static void* getHandlerData();

  /**
   * Returns debug string containing full error information from instance.
   */
  const SbString& getDebugString() const { return debugString; }

  /**
   * Returns type identifier for SoError class.
   */
  static SoType getClassTypeId();

  /**
   * Returns type identifier for error instance.
   */
  virtual SoType getTypeId() const;

  /**
   * Destructor
   */
  virtual ~SoError() {}

  /**
   * Posts an error. The debugString will be created from the given
   * arguments, which are in printf() format
   */
  SoPRINTF static void post(const char *formatString ...);

SoEXTENDER public:
#if 0
  // These are convenience functions that return a printable string
  // representing the given object. For example, a node is
  // represented by name (if it has one) and by address; the
  // returned string will be something like:
  //    node named "squid" at address 0x1004dcba
  static SbString     getString(const SoNode *node);
  static SbString     getString(const SoPath *path);
  static SbString     getString(const SoEngine *engine);
#endif

 SoINTERNAL public:
  // Initializes SoError class
  static void         initClass();
  static void         exitClass();

  static SoErrorCB* getDefaultHandlerCB() { return defaultHandlerCB; }

 protected:
  // The default error handler callback - it just prints to stderr
  static void defaultHandlerCB(const SoError *error, void *data);

  // Returns handler callback (and data) to use for a given instance
  virtual SoErrorCB * getHandler(void *&data) const;
  virtual bool isInit() const;

  // Sets/appends to the debug string
  void setDebugString(const SbString& string)
    { debugString = string; }
  void appendToDebugString(const SbString& string)
    { debugString += string; }

  // Calls appropriate handler for an error instance. Application
  // writers can set breakpoints at this when debugging.
  void handleError();

  /** 
   * Sets the initial capacity of the debug string, useful
   * for SoMemoryError because it cannot alloc memory...
   */ 
  virtual void setDebugStringCapacity( int capacity );

 private:
  // Type id of SoError class
  static SoType classTypeId;
  // Handler callback for SoError class
  static SoErrorCB *handlerCB;
  // User data for callback
  static void *cbData;
  // TRUE if handler initialized
  static SbBool wasInitted;
  // Detailed error message string
  SbString debugString;
  // The getString() methods use this one
  static SbString getBaseString(const SoBase *base, const char *what);
  // allow to disable user error handler and keep everything in stderr.
  // see SoPreferences env var OIV_FORCE_DEFAULT_ERROR_HANDLER
  static SbBool s_forceDefaultHandler;
};

#endif /* _SO_ERROR */
