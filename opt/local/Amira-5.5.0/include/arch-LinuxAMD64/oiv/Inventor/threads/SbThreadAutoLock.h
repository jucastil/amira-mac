/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Feb 2008)
**=======================================================================*/

#ifndef _SB_THREAD_AUTO_LOCK_H_
#define _SB_THREAD_AUTO_LOCK_H_

#include <Inventor/SbBase.h>

class SbThreadMutex;
class SbThreadRWMutex;

/**
 * @VSGEXT Provides reliable unlocking of a mutex.
 * 
 * @ingroup Threads
 * 
 * @DESCRIPTION
 *   This class provides reliable unlocking of a mutex.
 *   
 *   An SbThreadMutex object must be created separately. The address of the mutex
 *   object is passed to the constructor, which locks the mutex and saves a reference
 *   to the mutex object. The autolock object should be created on the stack, so each
 *   thread will have its own autolock. The destructor automatically unlocks the
 *   mutex. 
 *   
 *   Because the autolock object is created on the stack, it avoids the need to
 *   explicitly unlock the mutex at every point of exit from the function (a common
 *   source of errors). The mutex will be unlocked when the autolock goes out of
 *   scope.
 *   
 *   Example:
 *   
 *   <PRE> 
 *      // myClass contains a Mutex object named m_mutex
 *      void myClass::someFunction() 
 *      {
 *         // m_mutex is a ptr to an existing SbThreadMutex object
 *         SbThreadAutoLock dummyName( m_mutex );
 *         ... other code ...
 *      } // mutex automatically unlocked
 *   </PRE>
 *    
 * @SEE_ALSO
 *    SbThread,
 *    SbThreadAutoReadLock,
 *    SbThreadAutoWriteLock,
 *    SbThreadBarrier,
 *    SbThreadMutex,
 *    SbThreadRWMutex
 * 
 * 
 */ 

class INVENTORBASE_API SbThreadAutoLock {
 public:
  /**
   * Creates a mutex "autolock" object and automatically calls the mutex lock method.
   * The mutex will be automatically unlocked when the autolock object is destroyed.
   */
  SbThreadAutoLock( SbThreadMutex *mutex );
  SbThreadAutoLock( SbThreadMutex &mutex );

#ifndef HIDDEN_FROM_DOC
  ~SbThreadAutoLock();
#endif // HIDDEN_FROM_DOC

 private:
  SbThreadMutex *m_mutex;
};

/**
 * @VSGEXT Provides reliable unlocking of a read-only mutex.
 * 
 * @ingroup Threads
 * 
 * @DESCRIPTION
 *   This class provides reliable unlocking of a read-only mutex.
 *   
 *   An SbThreadRWMutex object must be created separately. The address of the mutex
 *   object is passed to the constructor, which locks the mutex and saves a reference
 *   to the mutex object. The autolock object should be created on the stack, so each
 *   thread will have its own autolock. The destructor automatically unlocks the
 *   mutex.
 *   
 *   Because the autolock object is created on the stack, it avoids the need to
 *   explicitly unlock the mutex at every point of exit from the function (a common
 *   source of errors). The mutex will be unlocked when the autolock goes out of
 *   scope.
 *   
 *   The unlock() and relock() methods are provided for complex cases where
 *   the lock needs to be temporarily released. If the autolock is explicitly
 *   unlocked, the destructor does nothing.
 *   
 *   Example:
 *   <PRE> 
 *      myClass contains an RWMutex object named m_mutex
 *      void myClass::someFunction()
 *      {
 *         SbThreadAutoReadLock( m_mutex );
 *         ... other code ...
 *      } // mutex automatically unlocked
 *   </PRE>
 * 
 * @SEE_ALSO
 *    SbThread,
 *    SbThreadAutoLock,
 *    SbThreadAutoWriteLock,
 *    SbThreadBarrier,
 *    SbThreadMutex,
 *    SbThreadRWMutex
 * 
 * 
 */ 

class INVENTORBASE_API SbThreadAutoReadLock {
 public:
  /**
   * Creates a mutex "autolock" object and automatically calls the mutex readlock
   * method. The mutex will be automatically unlocked when the autolock object is
   * destroyed.
   */
  SbThreadAutoReadLock( SbThreadRWMutex *mutex );
  SbThreadAutoReadLock( SbThreadRWMutex &mutex );

#ifndef HIDDEN_FROM_DOC
  /**
   * Destructor.
   */
  ~SbThreadAutoReadLock();
#endif

  /**
   * Explicitly unlock the associated mutex. Do not unlock or lock the
   * mutex directly.
   */
  int unlock();
  /**
   * Explicitly relock the associated mutex. Do not unlock or lock the
   * mutex directly.
   */
  int relock();

 private:
  SbThreadRWMutex *m_mutex;
  SbBool           m_isLocked;

};

/**
 * @VSGEXT Provides reliable unlocking of a write-only mutex.
 * 
 * @ingroup Threads
 * 
 * @DESCRIPTION
 *   This class provides reliable unlocking of a write-only mutex.
 *   
 *   An SbThreadRWMutex object must be created separately. The address of the mutex
 *   object is passed to the constructor, which locks the mutex and saves a reference
 *   to the mutex object. The autolock object should be created on the stack, so each
 *   thread will have its own autolock. The destructor automatically unlocks the
 *   mutex. 
 *   
 *   Because the autolock object is created on the stack, it avoids the need to
 *   explicitly unlock the mutex at every point of exit from the function (a common
 *   source of errors). The mutex will be unlocked when the autolock goes out of
 *   scope.
 *   
 *   The unlock() and relock() methods are provided for complex cases where
 *   the lock needs to be temporarily released. If the autolock is explicitly
 *   unlocked, the destructor does nothing. 
 *   
 *   Example:
 *   
 *   <PRE> 
 *      // myClass contains an RWMutex object named m_mutex
 *      void myClass::someFunction()
 *      {
 *         // m_mutex is a ptr to an existing SbThreadRWMutex object
 *         SbThreadAutoWriteLock dummyName( m_mutex );
 *         ... other code ...
 *      } // mutex automatically unlocked
 *   </PRE>
 *    
 * 
 * @SEE_ALSO
 *    SbThread,
 *    SbThreadAutoLock,
 *    SbThreadAutoReadLock,
 *    SbThreadBarrier,
 *    SbThreadMutex,
 *    SbThreadRWMutex
 * 
 * 
 */ 

class INVENTORBASE_API SbThreadAutoWriteLock {
 public:
  /**
   * Creates a mutex "autolock" object and automatically calls the mutex writelock
   * method. The mutex will be automatically unlocked when the autolock object is
   * destroyed.
   */
  SbThreadAutoWriteLock( SbThreadRWMutex *mutex );
  SbThreadAutoWriteLock( SbThreadRWMutex &mutex );

#ifndef HIDDEN_FROM_DOC
  /**
   * Destructor.
   */
  ~SbThreadAutoWriteLock();
#endif

  /**
   * Explicitly unlock the associated mutex. Do not unlock or lock the
   * mutex directly.
   */
  int unlock();
  /**
   * Explicitly relock the associated mutex. Do not unlock or lock the
   * mutex directly.
   */
  int relock();

 private:
  SbThreadRWMutex *m_mutex;
  SbBool           m_isLocked;

};

#endif //_SB_THREAD_AUTO_LOCK_H_
