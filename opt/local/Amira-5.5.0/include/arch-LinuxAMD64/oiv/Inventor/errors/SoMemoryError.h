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


#ifndef  _SO_MEMORY_ERROR
#define  _SO_MEMORY_ERROR

#include <Inventor/errors/SoError.h>

class SbThreadMutex;
class SoMemoryError;

/**
 * Memory cleanup handling callback.
 *
 * SoMemoryCleanupCB is called when Open Inventor is not able to allocate at 
 * least @I requestedSize @i bytes of memory.
 * This notifies the application that available memory is too low. The application
 * can try to release some memory to allow the allocation to succeed.
 * If the callback returns true then Open Inventor will retry its allocation call.
 *
 * @SEE_ALSO
 *    SoMemoryError::setMemoryCleanupCallback
 *
 * [OIV-WRAPPER NAME{MemoryCleanupCallback}]
 */
typedef bool SoMemoryCleanupCB(const size_t requestedByteSize, void* data);

/**
 * Memory error handling.
 * 
 * @ingroup errors
 * 
 * @DESCRIPTION
 *   SoMemoryError is used for errors reported due to lack of memory.
 *   See SoError for full discussion of error handling in Open Inventor.
 *
 *   The post() method takes a string describing the item that was to be
 *   allocated, such as "cylinder vertex array".
 *
 *   setMemoryCleanupCallback() can be used to set a handler function
 *   that will be called when a memory allocation fails.  The function
 *   can release some memory to allow the allocation to succeed. 
 * 
 * @SEE_ALSO
 *    SoDebugError, SoReadError, SoGLError
 * 
 */ 
class INVENTORBASE_API SoMemoryError : public SoError {

 public:

  /**
   * Sets handler callback for SoMemoryError class.
   */
  static void setHandlerCallback(SoErrorCB *cb, void *data);

  /**
   * Returns handler callback for SoMemoryError class.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static SoErrorCB* getHandlerCallback();

  /**
   * Returns handler data for SoMemoryError class.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void* getHandlerData();

  /**
   * Sets memory cleanup handler callback for SoMemoryError class.
   * [OIV-WRAPPER NAME{setMemoryCleanupHandler}]
   */
  static void setMemoryCleanupCallback(SoMemoryCleanupCB *cb, void * data);

  /**
   * Returns type identifier for SoMemoryError class.
   */
  static SoType getClassTypeId();

  /**
   * Returns type identifier for an instance of this class.
   */
  virtual SoType getTypeId() const;

  /**
   * Posts an error
   */
  static void post(const SbString& whatWasAllocated);

  /**
   * Posts an error
   */
  static void post(const char* whatWasAllocated);

 SoINTERNAL public:
  // Initializes SoMemoryError class
  static void initClass();
  static void exitClass();
  static SoErrorCB* getDefaultHandlerCB() { return defaultHandlerCB; }
  static bool getMemorySpace(const size_t size);

 protected:
  // Returns handler callback (and data) to use for a given instance
  virtual SoErrorCB * getHandler(void *&data) const;
  virtual bool isInit() const;

 private:
  // Type id of SoMemoryError class
  static SoType classTypeId;
  // Handler callback for class
  static SoErrorCB *handlerCB;
  // User data for callback
  static void *cbData;
  // TRUE if handler initialized
  static SbBool wasInitted;

  static SoMemoryError* s_memoryErrorObject;
  static SbThreadMutex* s_threadMutex;
  static SbString* s_memoryErrorString;

  // This allow to avoid infinite loop in this code
  // when user set an error callback that need allocation itself.
  static bool s_memoryFreeSpaceLoop;
  static SoMemoryCleanupCB* s_memoryCleanupCB;
  static void* s_memoryCleanupData;

};

#endif /* _SO_MEMORY_ERROR */

