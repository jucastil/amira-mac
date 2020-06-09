/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Apr 2008)
**=======================================================================*/


#ifndef _SB_THREAD_BARRIER_H_
#define _SB_THREAD_BARRIER_H_

#include <Inventor/SbBase.h>

class SbThreadMutex;
class SbThreadSignal;

/**
 * @VSGEXT Portable "barrier" class for synchronizing threads.
 * 
 * @ingroup Threads
 * 
 * @DESCRIPTION
 *   This class provides a portable "barrier" for synchronizing threads. It is
 *   Implemented using the pthreads API on UNIX/Linux and the Win32 API on Microsoft
 *   Windows.
 *   
 *   It is not necessary to use this class in order to use multiple threads with Open
 *   Inventor. It is provided only as a convenience. (However, note that you should
 *   use pthreads on UNIX/Linux and Win32 on Windows to be certain of compatibility
 *   with Open Inventor.)
 *   
 *   A barrier is one type of synchronization construct for threads. It forces a group
 *   of threads to "rendezvous" at a particular point in the code. No thread that
 *   enters the barrier may leave the barrier until all the threads have entered the
 *   barrier.
 *   
 *   Specify the number of threads to be synchronized when you create the barrier
 *   object. Note it is critical for every thread in the "group" to enter the
 *   barrier. There is no other way to release threads already blocked in the
 *   barrier.
 * 
 * @SEE_ALSO
 *    SbThread,
 *    SbThreadAutoLock,
 *    SbThreadAutoReadLock,
 *    SbThreadAutoWriteLock,
 *    SbThreadMutex,
 *    SbThreadRWMutex
 * 
 * 
 */ 

class INVENTORBASE_API SbThreadBarrier
{
 public:
  /**
   * Creates a thread barrier that will block until N threads have entered
   * the barrier.
   */
  SbThreadBarrier( int );

  /**
   * Destructor.
   */
  virtual ~SbThreadBarrier(void); 

  /**
   * Enter the barrier. Each thread to be synchronized should call this method.
   * Returns 1 if the caller was the last thread to enter the barrier, 0 otherwise.
   */
  int enter();

SoINTERNAL public:

  /**
   * Try to enter the barrier. Useful for example to unlock threads at termination.
   */
  void tryenter( const unsigned int timeout_ms );

private:

   int32_t m_numThreads;
   int32_t m_counter;
   SbThreadMutex* m_mutex;
   SbThreadSignal* m_signal;
};

#endif //_SB_THREAD_BARRIER_H_

