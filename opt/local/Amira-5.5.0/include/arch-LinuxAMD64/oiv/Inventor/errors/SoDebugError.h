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
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_DEBUG_ERROR
#define  _SO_DEBUG_ERROR

#include <Inventor/errors/SoError.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDebugError
//
//  This class is used for all errors reported from the debugging
//  version of the Inventor library. These errors are typically
//  programmer errors, such as passing a NULL pointer or an
//  out-of-range index. The post() method takes the name of the
//  Inventor method that detected the error, to aid the programmer in
//  debugging.
//
//////////////////////////////////////////////////////////////////////////////

/**
* Debug error handling.
*
* @ingroup errors
*
* @DESCRIPTION
*   SoDebugError is used for all errors reported from the debugging version of the
*   Open Inventor library. These errors are typically programmer errors, such as
*   passing a null reference or an out-of-range index. The post() method takes
*   the name of the Open Inventor method that detected the error, to aid the
*   programmer in debugging.
*
*   See SoError for full discussion of error handling in Open Inventor.
*
*   See SoError for full discussion of error handling in Open Inventor.
*
* @SEE_ALSO
*    SoMemoryError,
*    SoReadError,
*    SoGLError
* [OIVJAVA-WRAPPER-CLASS NO_WRAP]
*/

class INVENTORBASE_API SoDebugError : public SoError {

 public:
   /** Error severity */
  enum Severity {
#if defined(_WIN32) || defined(__NUTC__)
    /** Error */
    SERROR,     // Error
#else
    /**
     *  Error
     */
    ERROR,
#endif
    /**
     *  Just a warning
     */
    WARNING,
    /**
     *  No error, just information
     */
    INFO
  };

  /**
   * Sets handler callback for SoDebugError class.
   */
  static void setHandlerCallback(SoErrorCB *cb, void *data);
  /**
   * Returns handler callback for SoDebugError class.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static SoErrorCB *getHandlerCallback();
  /**
   * Returns handler data for SoDebugError class.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void *getHandlerData();

  /**
   * Returns type identifier for SoDebugError class.
   */
  static SoType getClassTypeId();

  /**
   * Returns type identifier for error instance
   */
  virtual SoType getTypeId() const;

  /**
   * Returns severity of error (for use by handlers).
   */
  SoDebugError::Severity getSeverity() const { return severity; }

  /**
   * Posts an error
   * [OIV-WRAPPER-NO-WRAP]
   */
  SoPRINTFPREFIX(2,3) static void post(const char *methodName, const char *formatString ...);

  /**
   * Posts a warning
   * [OIV-WRAPPER-NO-WRAP]
   */
  SoPRINTFPREFIX(2,3) static void postWarning(const char *methodName, const char *formatString ...);

  /**
   * Posts an informational (non-error) message
   * [OIV-WRAPPER-NO-WRAP]
   */
  SoPRINTFPREFIX(2,3) static void postInfo(const char *methodName, const char *formatString ...);

 SoINTERNAL public:
  // Initializes SoDebugError class
  static void initClass();
  static void exitClass();

  static SoErrorCB* getDefaultHandlerCB() { return defaultHandlerCB; }

 protected:
  // Returns handler callback (and data) to use for a given instance
  virtual SoErrorCB *getHandler(void *&data) const;
  virtual bool isInit() const;

 private:
  static  SoType classTypeId; // Type id of SoDebugError class
  static  SoErrorCB *handlerCB; // Handler callback for class
  static  void *cbData; // User data for callback
  static SbBool wasInitted; // TRUE if handler initialized

  Severity severity;    // Severity of error

};

#endif /* _SO_DEBUG_ERROR */
