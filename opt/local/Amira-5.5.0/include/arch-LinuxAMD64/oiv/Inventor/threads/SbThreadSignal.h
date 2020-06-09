/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (May 2007)
**=======================================================================*/


#ifndef SB_THREAD_SIGNAL_H
#define SB_THREAD_SIGNAL_H

#include <Inventor/sys/port.h>
#include <Inventor/SbBase.h>

#include <Inventor/threads/SbThreadSpinlock.h>

class SbThreadMutex;

#if !defined (WIN32)
#include <pthread.h>
#endif

/**
 * @VSGEXT Portable signal class.
 *
 * @ingroup Threads
 *
 * @DESCRIPTION
 *   This class provides a portable "condition variable" object. Condition variables
 *   are used when one thread wants to wait until another thread has finished doing
 *   something: the first thread "waits" on the condition variable, the second thread
 *   "signals" the condition variable when it is done. It is implemented
 *   using the pthreads API on UNIX/Linux and the Win32 API on Microsoft Windows.
 *
 *   It is not necessary to use this class in order to use multiple threads with Open
 *   Inventor. It is provided only as a convenience. However, note that you should
 *   use pthreads on UNIX/Linux and Win32 on Windows to be certain of compatibility
 *   with Open Inventor.
 *
 *   NOTE: Inventor mutex classes cannot be used to synchronize threads
 *   unless multi-thread support is enabled by, for example,
 *   calling SoDB::threadInit instead of SoDB::init.
 *
 * @SEE_ALSO
 *    SbThreadAutoLock,
 *    SbThreadBarrier,
 *    SbThreadMutex,
 *    SbThreadRWMutex
 *
 */

class INVENTORBASE_API SbThreadSignal
{
public:

  /**
   * Constructor.
   */
  SbThreadSignal( SbThreadMutex* mtx );

  /**
   * Destructor.
   */
  ~SbThreadSignal( );

  /**
   * Signals one thread that is waiting on this object.
   */
  void signalOne( );

  /**
   * Signals all threads that are waiting
   * on this object.
   */
  void signalAll( );

  /**
   * Waits for a signal notification. When called, it goes to sleep
   * awaiting a subsequent notification from another thread (via the
   * signalOne or signalAll methods).
   */
  void wait( );

  /**
   * Waits for a signal notification or timeout milliseconds have elapsed.
   * If the timeout elapses before the signal is notified, the function
   * returns FALSE to the caller, signifying that a timeout has occurred.
   */
  SbBool trywait( const unsigned int timeout_ms );

private:
  SbThreadMutex* m_signalMtx;

#if defined(_WIN32)
  HANDLE m_events[2];
  uint32_t m_waitersCount;
  SbThreadSpinlock m_spinlock;

#elif defined (__linux__) || defined(__APPLE__) || defined(sun)
  pthread_cond_t m_event;
  bool m_automatic;
  bool m_active;

#else
  // Not implemented yet.
#endif
};

#endif // SB_THREAD_SIGNAL_H

/**/
