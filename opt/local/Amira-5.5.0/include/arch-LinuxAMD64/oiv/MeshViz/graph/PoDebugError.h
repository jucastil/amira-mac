/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (May 1996)
**=======================================================================*/


                                                             /* include files */
#ifndef  _PO_DEBUG_ERROR_
#define  _PO_DEBUG_ERROR_

#include <MeshViz/PbBasic.h>


#include <Inventor/errors/SoError.h>


#ifdef ERROR
#  undef ERROR
#endif

/*----------------------------------------------------------------------------*/

PoINTERNAL class MESHVIZ_API PoDebugError : public SoError {
 public:
  enum Severity {
    ERROR,     // Error
    WARNING,   // Just a warning
    INFO       // No error, just information
  } ;
  
  // Sets/returns handler callback for PoDebugError class
  static void setHandlerCallback(SoErrorCB *cb, void *data);                                         
  static SoErrorCB *getHandlerCallback() { return handlerCB ; }
  static void *getHandlerData()          { return cbData ; }
  
  // Returns type identifier for PoDebugError class
  static SoType getClassTypeId()        { return classTypeId ; }
  
  // Returns type identifier for error instance
  virtual SoType getTypeId() const ;
  
  // Returns severity of error (for use by handlers)
  PoDebugError::Severity getSeverity() const { return severity ; }
  
  // Posts an error
  static void post(const char *methodName,
                   const char *formatString ...) ;
  
  // Posts a warning
  static void postWarning(const char *methodName, const char *formatString ...) ;
  
  // Posts an informational (non-error) message
  static void postInfo(const char *methodName, const char *formatString ...) ;

 PoINTERNAL public:
  // Initializes PoDebugError class
  static void initClass();

 protected:
  // Returns handler callback (and data) to use for a given instance
  virtual SoErrorCB *getHandler(void *&data) const ;
  
 private:
  static void postP(Severity sever, const char *methodName, const char *errorString) ;

  static SoType         classTypeId ;   // Type id of PoDebugError class
  static SoErrorCB      *handlerCB ;    // Handler callback for class
  static void           *cbData ;       // User data for callback
  
  Severity              severity ;      // Severity of error
} ;
/*----------------------------------------------------------------------------*/

#endif /* _PO_DEBUG_ERROR_ */

