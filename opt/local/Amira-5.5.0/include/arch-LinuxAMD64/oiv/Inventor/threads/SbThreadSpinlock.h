/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Feb 2008)
**=======================================================================*/

#ifndef _SB_THREAD_SPINLOCK_H_
#define _SB_THREAD_SPINLOCK_H_

#include <Inventor/SbBase.h>
#include <Inventor/threads/SbThread.h>
#include <Inventor/threads/SbThreadMutex.h>

/**
 * @VSGEXT Portable spinlock class.
 * 
 * @ingroup Threads
 * 
 * @DESCRIPTION
 *   This class provides a portable "spinlock". It is implemented using the pthreads
 *   API on UNIX/Linux and the Win32 API on Microsoft Windows.
 *   
 *   A spinlock can be used just like a mutex to protect access to critical data 
 *   or code that is used by multiple threads.  In some cases a spinlock may be
 *   more efficient than a mutex.  But note that this class may be implemented using
 *   a mutex if there is no native support, which is currently the case on UNIX/Linux.
 *   
 *   It is not necessary to use this class in order to use multiple threads with Open
 *   Inventor. It is provided only as a convenience. (However, note that you should
 *   use pthreads on UNIX/Linux and Win32 on Windows to be certain of compatibility
 *   with Open Inventor.)
 * 
 * @SEE_ALSO
 *    SbThread,
 *    SbThreadAutoLock,
 *    SbThreadBarrier,
 *    SbThreadMutex
 * 
 * 
 */ 

class INVENTORBASE_API SbThreadSpinlock
{
 public:
  /**
   * Create a spinlock.
   */
  SbThreadSpinlock() ;
  /**
   * Destructor.
   */
  ~SbThreadSpinlock() ;

  /**
   * Request exclusive access for this spinlock.
   */
  void lock() ;

  /**
   * Release exclusive access.
   */
  void unlock() ;

private:
#if defined(_WIN32)
  LONG volatile m_spinLock;
  SbThreadId_t m_curThread;
  int m_enterCount;
#else
  SbThreadMutex m_spinLock;
#endif
};

#endif // _SB_THREAD_SPINLOCK_H_
