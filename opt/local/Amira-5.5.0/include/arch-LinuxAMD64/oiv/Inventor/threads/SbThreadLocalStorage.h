/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2008)
**=======================================================================*/


#ifndef _SB_THREAD_LOCAL_STORAGE_H_
#define _SB_THREAD_LOCAL_STORAGE_H_

#include <Inventor/SbBase.h>
#include <Inventor/STL/list>
#include <Inventor/STL/vector>
#include <Inventor/STL/map>
#include <Inventor/threads/SbThreadSpinlock.h>

#if defined(_WIN32)
#pragma warning( push )
#pragma warning(disable:4251)
#endif //_WIN32

typedef void SoInitTLSClassCB();
typedef void SoExitTLSClassCB();

/**
 * Requests allocation of thread local storage. This macro
 * should be called within initClass(). The structName argument
 * should be the structure (the type name) defining what size
 * of memory should be allocated for each thread, for this class
 */
#define SB_THREAD_INIT_CLASS(_className_,_structName_) \
  _className_::MT_Id = SbThreadLocalStorage::createStorage(sizeof(struct _className_::_structName_), _className_::initTLSClass, _className_::exitTLSClass, __FUNCTION__ );

/**
 * Requests deallocation of thread local storage. This macro
 * should be called within exitClass(). The structName argument
 * should be the structure (the type name) defining what size
 * of memory should be allocated for each thread, for this class
 */
#define SB_THREAD_EXIT_CLASS(_className_) \
  SbThreadLocalStorage::deleteStorage( _className_::MT_Id );

/**
 * Gets direct access to current thread storage inside variable.
 */
#define GET_THREAD_LOCAL_VAR(_className_, _structName_, _varName_) \
  \
  ((static_cast<struct _className_::_structName_ *> (SbThreadLocalStorage::getStorage(_className_::MT_Id)))->_varName_)

/**
 * Returns pointer to current thread storage for defined class.
 */
#define GET_THREAD_LOCAL_STORAGE(_className_) \
  \
  (static_cast<void *> (SbThreadLocalStorage::getStorage(_className_::MT_Id)))

/**
 * Defines headers for required member variables in thread storage management.
 */
#define SB_THREAD_TLS_HEADER() \
SoINTERNAL public: \
  /** TLS storage unique id */ \
  static size_t MT_Id; \
  /** TLS storage initialization method */ \
  static void initTLSClass(); \
  /** TLS storage cleanup method */ \
  static void exitTLSClass()


/**
 * Defines source for required member variables in thread storage management.
 */
#define SB_THREAD_TLS_SOURCE( _className_ ) \
\
  /** Unique Id to reference access TLS data associated to this class through getStorage method */ \
  size_t _className_::MT_Id = -1

/** Compatiblity define SoNodeTLS to SbThreadLocalStorage. */
#ifndef SoNodeTLS
#define SoNodeTLS SbThreadLocalStorage
#endif

/**
 * @VSGEXT Thread Local Storage (TLS) class.
 *
 * @ingroup Threads
 *
 * @DESCRIPTION
 *   This class allows to create thread local data storage.
 *   This allow to manage per thread static global variables
 *   in multithread mode.
 *
 * Example on how to use the Thread Local Storage (TLS):
 *
 * In this example we move static variables s_myStaticVar1 and 
 * s_myStaticVar2 of the class MyClass to Thread Local Storage,
 *
 * - Original myClass implementation : @BR
 *   <PRE>
 *       class myClass
 *       {
 *          
 *          static void initClass();
 *          static void exitClass();
 *          ... 
 *          static int    s_myStaticVar1;
 *          static float* s_myStaticVar2;
 *          ...
 *       }
 *
 *       void myClass::initClass()
 *       {
 *         s_myStaticVar1 = 32;
 *         s_myStaticVar2 = new float[32];
 *       }
 *
 *       void myClass::exitClass()
 *       {
 *         s_myStaticVar1 = 0;
 *         delete [] s_myStaticVar2;
 *       }
 *      
 *   </PRE>
 * 
 * - Modified myClass implementation to support use TLS : @BR
 *   <PRE>
 *       class myClass
 *       {
 *          
 *          static void initClass();
 *          static void exitClass();
 *
 *          // Declare necessary members and methods for TLS usage
 *          SB_THREAD_TLS_HEADER();
 *          ...
 *          // structure to handle per thread static variables
 *          struct MTstruct {
 *            int    s_myStaticVar1;
 *            float* s_myStaticVar2;
 *          }
 *          ...
 *       }
 *
 *       void myClass::initClass()
 *       {
 *         // register and reserve space for TLS
 *         SB_THREAD_INIT_CLASS(myClass, MTstruct);
 *       }
 *
 *       void myClass::exitClass()
 *       {
 *       }
 *
 *       void myClass::initTLSClass()
 *       {
 *         // get access to TLS and init/allocate variables once per thread
 *         struct myClass::MTstruct * mtstruct = (struct myClass::MTstruct *)GET_THREAD_LOCAL_STORAGE(myClass) ;
 *         mtstruct->s_myStaticVar1 = 32;
 *         mtstruct->s_myStaticVar2 = new float[32];
 *       }
 *
 *       void myClass::exitTLSClass()
 *       {
 *         // get access to TLS and deallocate variables once per thread
 *         struct myClass::MTstruct * mtstruct = (struct myClass::MTstruct *)GET_THREAD_LOCAL_STORAGE(myClass) ;
 *         delete [] mtstruct->s_myStaticVar2;
 *       }
 *   </PRE>
 *
 * - Each time a variable in Thread Local Storage is used, the structure
 *   containing this variable needs to be fetched using the following macro :
 *   <PRE>
 *       struct myClass::MTstruct * mtstruct = (struct myClass::MTstruct *) GET_THREAD_LOCAL_STORAGE(myClass) ;
 *   </PRE>
 *   The variables can then be used as, for example: mtstruct->variable1. @BR
 *   Another macro exists to bring back one single variable of the structure : @BR
 *   <PRE>
 *       GET_THREAD_LOCAL_VAR(myClass, MTstruct, variable1)
 *   </PRE>
 *
 * @SEE_ALSO
 *    SbThread,
 *    SbThreadAutoLock,
 *    SbThreadAutoReadLock,
 *    SbThreadAutoWriteLock,
 *    SbThreadBarrier,
 *    SbThreadRWMutex,
 *    SbThreadSignal
 *
 *
 */

class INVENTORBASE_API SbThreadLocalStorage
{
 public:
  /**
   * Creates or updates the local storage for the current thread.
   * Requests that 'size' bytes of storage should be allocated
   * for all threads for the calling class.
   * Returns a unique Id to be used by getStorage method to access
   * the storage.
   */
  static size_t createStorage(const size_t byteSize, SoInitTLSClassCB* initFunc=NULL, SoExitTLSClassCB* exitFunc=NULL, const char* funcName=NULL);

  /**
   * Deletes the local storage for all threads.
   */
  static void deleteStorage( size_t id );

  /**
   * Returns a pointer on the storage for the given Id.
   * This storage is guaranteed to be local to the current thread.
   * The size of the storage is the same than what was requested
   * by createStorage, unless the pointer returned is NULL.
   */
  static void *getStorage(const size_t classThreadId);

SoEXTENDER public:
  /**
   * Creates or updates the local storage for the current thread. @BR
   * This is different from creating the thread key, since here we
   * access the local storage that is attached to that key for the
   * current thread. This method can be called several times for the
   * same thread. It should be called after initClass and after an
   * OIV class has asked for storage creation (see createStorage).
   * createStorage can be called several times before calling
   * initThreadLocalStorage, but the storage shouldn't be accessed
   * (via getStorage) after createStorage until a call to
   * initThreadLocalStorage.
   */
  static void initThreadLocalStorage();

  /**
   * Frees all memory for the local storage associated with the
   * current thread. initThreadLocalStorage can be called after
   * closeThreadLocalStorage to reinitialize the storage.
   */
  static void closeThreadLocalStorage();

  /**
   * Free storage allocated for threadLocalStorage.
   * ThreadLocalStorage will be enabled again by calling initThreadLocalStorage()
   * for each running threads;
   */
  static void exitThreadLocalStorage();

SoINTERNAL public:
  /**
   * Initializes the SbThreadLocalStorage class.
   * Creates the thread key that will be used by all threads
   * accessing the thread local storages
   */
  static void initClass();

  /**
   * Finalizes the SbThreadLocalStorage class.
   * Deletes the thread key associated with the storage.
   */
  static void exitClass();

  /**
   * Return the TLS struct StructName of the class ClassName
   * eg: getTlsStruct<MTStruct, MyClass>(this);
   */
  template<typename StructName, typename ClassName>
  static StructName*
  getStruct()
  {
    return static_cast<StructName*>(SbThreadLocalStorage::getStorage(ClassName::MT_Id));
  }

  /**
   * Return the TLS struct StructName of the class ClassName
   * eg: getTlsStruct<MTStruct>(this);
   */
  template<typename StructName, typename ClassName>
  static StructName*
  getStruct(const ClassName*)
  {
    return getStruct<StructName, ClassName>();
  }

private:
  /** used by ScaleViz Multipipe to initialized all TLS as in the mail thread */
  static void checkInitTLS();

  // Storage info class to handle TLS info for each storage
  class StorageInfo
  {
  public:
    // size of the storage
    size_t size;

    // init storage function callback
    SoInitTLSClassCB* initFunc;

    // exit storage function callback
    SoExitTLSClassCB* exitFunc;

    // default constructor
    StorageInfo() : size(0),initFunc(NULL),exitFunc(NULL) {}
  };

  // global spinlock to protect access to s_storageInfoList
  static SbThreadSpinlock s_storageInfoListLock;

  // global ordered list of StorageInfo
  typedef std::vector<StorageInfo*> SoStorageInfoList;
  static SoStorageInfoList s_storageInfoList;

  // list of thread pointer data
  typedef std::vector<void*> SoStorageList;
  // list used in non-MT mode
  static SoStorageList* s_threadStorageList;
  // return the storageList (from TLS or static vars depending on MT mode)
  static SoStorageList* getThreadStorage();

};

#ifndef HIDDEN_FROM_DOC

class INVENTORBASE_API SbThreadStorageBase
{
  SB_THREAD_TLS_HEADER();

public:
  /** Clear this storage. */
  virtual void cleanStorage( ) = 0;

  static void initClass();
  static void exitClass();

  void* getValue() const;
  void Register( void* );

  typedef std::map< SbThreadStorageBase*, void* > SbThreadStorageMap;
  typedef std::list< SbThreadStorageMap* > SbThreadStorageGlobalList;

  struct MTstruct
  {
    SbThreadStorageMap* threadStorageMap;
  };

protected:
  SbThreadStorageBase();
  virtual ~SbThreadStorageBase();

  static SbThreadStorageGlobalList s_threadStorageGlobalList;
  static SbThreadSpinlock s_threadStorageGlobalMutex;
};

#endif // HIDDEN_FROM_DOC

#if defined(_WIN32)
#pragma warning(pop)
#endif //_WIN32


#endif //_SB_THREAD_LOCAL_STORAGE_H_

/**/
