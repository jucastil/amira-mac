/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Feb 2010)
**=======================================================================*/

#ifndef  _SO_GL_ERROR
#define  _SO_GL_ERROR

#include <Inventor/SbBasic.h>
#include <Inventor/errors/SoError.h>

/**
 * OpenGL rendering error handling.
 *
 * @ingroup errors
 *
 * @DESCRIPTION
 *   SoGLError is used for errors reported by the OpenGL render engine. @BR
 *   See SoError for full discussion of error handling in Open Inventor.
 *
 * @SEE_ALSO
 *    SoDebugError,
 *    SoMemoryError
 */

class INVENTORGL_API SoGLError : public SoError {

 public:
  /**
   * Sets handler callback for SoGLError class.
   */
  static void setHandlerCallback(SoErrorCB *cb, void *data);

  /**
   * Returns handler callback for SoGLError class.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static SoErrorCB* getHandlerCallback();

  /**
   * Returns handler data for SoGLError class.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void* getHandlerData();

  /**
   * Returns type identifier for the SoGLError class.
   */
  static SoType getClassTypeId();

  /**
   * Returns type identifier for an instance of this class.
   */
  virtual SoType getTypeId() const;

  /**
   * Posts an error
   * [OIV-WRAPPER-NO-WRAP]
   */
  SoPRINTFPREFIX(3, 4) static void post(const int openGLErrorCode , const char* glFuncName, const char *formatString ...);

 SoINTERNAL public:
  // Initializes SoGLError class
  static void initClass();
  static void exitClass();
  static SoErrorCB* getDefaultHandlerCB() { return defaultHandlerCB; }

 protected:
  // Returns handler callback (and data) to use for a given instance
  virtual SoErrorCB* getHandler(void *&data) const;
  virtual bool isInit() const;

 private:
  // Type id of SoGLError class
  static SoType classTypeId;
  // Handler callback for class
  static SoErrorCB* handlerCB;
  // User data for callback
  static void* cbData;
  // TRUE if handler initialized
  static SbBool wasInitted;
};

#endif /* _SO_GL_ERROR */
