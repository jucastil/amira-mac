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


#ifndef  _SO_READ_ERROR
#define  _SO_READ_ERROR

#include <Inventor/SbBasic.h>
#include <Inventor/errors/SoError.h>

class SoInput;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoReadError
//
//  This class is used for all errors reported while reading Inventor
//  data files.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Read error handling.
 *
 * @ingroup errors
 *
 * @DESCRIPTION
 *   SoReadError is used for errors reported while reading files. @BR
 *   See SoError for full discussion of error handling in Open Inventor.
 *
 * @SEE_ALSO
 *    SoDebugError,
 *    SoMemoryError,
 *    SoGLError
 */

class INVENTOR_API SoReadError : public SoError {

 public:
  /**
   * Sets handler callback for SoReadError class.
   */
  static void setHandlerCallback(SoErrorCB *cb, void *data);

  /**
   * Returns handler callback for SoReadError class.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static SoErrorCB* getHandlerCallback();

  /**
   * Returns handler data for SoReadError class.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void* getHandlerData();

  /**
   * Returns type identifier for SoReadError class.
   */
  static SoType getClassTypeId();

  /**
   * Returns type identifier for error instance
   */
  virtual SoType getTypeId() const;

  /**
   * Posts an error
   * [OIV-WRAPPER-NO-WRAP]
   */
  SoPRINTFPREFIX(2,3) static void post(const SoInput *in, const char *formatString ...);

 SoINTERNAL public:
  // Initializes SoReadError class
  static void initClass();
  static void exitClass();
  static SoErrorCB* getDefaultHandlerCB() { return defaultHandlerCB; }

 protected:
  // Returns handler callback (and data) to use for a given instance
  virtual SoErrorCB* getHandler(void *&data) const;
  virtual bool isInit() const;

 private:
  // Type id of SoReadError class
  static SoType classTypeId;
  // Handler callback for class
  static SoErrorCB* handlerCB;
  // User data for callback
  static void* cbData;
  // TRUE if handler initialized
  static SbBool wasInitted;
};

#endif /* _SO_READ_ERROR */
