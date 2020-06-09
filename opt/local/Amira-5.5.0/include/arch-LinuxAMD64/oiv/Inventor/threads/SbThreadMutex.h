/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Julien Chaplier (MMM yyyy)
**=======================================================================*/


#ifndef _SB_THREAD_MUTEX_H_
#define _SB_THREAD_MUTEX_H_

#include <Inventor/SbBase.h>

// keep this header for compatibility purpose
#include <Inventor/threads/SbThreadAutoLock.h>


#ifdef _WIN32
//#include <process.h>
#else
#ifdef OIV_MULTI_THREADS
#include <pthread.h>
#endif // OIV_MULTI_THREADS
#endif

/**
 * @VSGEXT Portable mutex class.
 *
 * @ingroup Threads
 *
 * @DESCRIPTION
 *   This class provides a portable mutex. It is implemented using the pthreads API
 *   on UNIX/Linux and the Win32 API on Microsoft Windows.
 *
 *   A mutex can be used to protect access to critical data or code that is used by
 *   multiple threads.
 *
 *   It is not necessary to use this class in order to use multiple threads with Open
 *   Inventor. It is provided only as a convenience. (However, note that you should
 *   use pthreads on UNIX/Linux and Win32 on Windows to be certain of compatibility
 *   with Open Inventor.)
 *
 * @SEE_ALSO
 *    SbThread,
 *    SbThreadAutoLock,
 *    SbThreadAutoReadLock,
 *    SbThreadAutoWriteLock,
 *    SbThreadBarrier,
 *    SbThreadRWMutex,
 *    SbThreadSemaphore,
 *    SbThreadSignal
 *
 *
 */

class INVENTORBASE_API SbThreadMutex {

 public:
  /**
   * Creates a mutex.
   */
  SbThreadMutex(const SbBool force = FALSE) ;

#ifndef HIDDEN_FROM_DOC
  ~SbThreadMutex() ;
#endif // HIDDEN_FROM_DOC

  /**
   * Locks the current thread on this mutex. If no other thread has already locked
   * this mutex, the current thread takes ownership of this mutex and can enter
   * inside the mutually exclusive area. Note that the same thread can safely call
   * lock() repeatedly, but will have to call unlock() the same number of
   * times in order to relinquish ownership of this mutex. If another thread is
   * already owner of this mutex, the current thread is blocked until the thread
   * owner relinquishes the mutex through unlock(). If several threads are
   * blocked, only one is unblocked. Returns 0 if successful.
   */
  int lock() ;

  /**
   * Relinquishes ownership of this mutex. If the current thread is owner of this
   * mutex (through a call to lock()), unlock() releases the mutex and
   * unblocks one thread waiting for this mutex to be released. If lock() has
   * been called several times, unlock() must be called the same number of times
   * to actually unlock the mutex. Returns 0 if successful.
   */
  int unlock() ;

  /**
   * Does basically the same as lock, but when a thread tries to gain ownership of
   * this mutex and fails because another thread has already taken ownership of this
   * mutex, trylock() returns FALSE and no lock is actually done. Otherwise,
   * trylock() returns TRUE and the current thread will have at some point to
   * call unlock to relinquish ownership of the mutex.
   */
  SbBool trylock() ;

SoINTERNAL public:
#if defined(__linux__) || defined(__APPLE__) || defined(sun)
  pthread_mutex_t* getMutex() { return mutex; }
#endif

protected:

#ifdef _WIN32
  void* mutex;
#if defined(_DEBUG)
  LONG volatile numLocks;
#endif
#else
  pthread_mutex_t* mutex ;
  pthread_mutexattr_t* mta;
  pthread_t thread_id ;
  int count ;
#endif
};

#endif // _SB_THREAD_MUTEX_H_
