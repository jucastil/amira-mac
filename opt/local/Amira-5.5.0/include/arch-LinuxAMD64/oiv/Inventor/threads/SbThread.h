/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Julien Chaplier (MMM yyyy)
** Modified by : Nicolas Daguise (MMM yyyy)
** Modified by : David Beilloin (MMM yyyy)
**=======================================================================*/


#ifndef _TGS_SB_THREAD_H_
#define _TGS_SB_THREAD_H_

#include <Inventor/SbBase.h>
#include <Inventor/STL/list>

#if defined(_WIN32)
#pragma warning( push )
#pragma warning( disable: 4290 4251 )
#endif

class SbThreadMutex;

/**
 * @VSGEXT Portable thread class.
 * 
 * @ingroup Threads
 * 
 * @DESCRIPTION
 *   This class provides a portable representation of a thread. It is implemented
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
 *    SbThreadAutoReadLock,
 *    SbThreadAutoWriteLock,
 *    SbThreadBarrier,
 *    SbThreadMutex,
 *    SbThreadRWMutex
 * 
 * 
 */ 

class INVENTORBASE_API SbThread
{
 public:
#ifdef OIV_NET_DOC
	 /**
	 * Creates a new thread. The thread will immediately begin executing the specified
	 * function, which will be passed the @B userData @b reference. Typically
	 * @B userData @b will point to a struct or class containing information the
	 * thread needs to initialize.
	 */

#else
	 /**
	 * Creates a new thread. The thread will immediately begin executing the specified
	 * function, which will be passed the @B userData @b pointer. Typically
	 * @B userData @b will point to a struct or class containing information the
	 * thread needs to initialize.
	 */

#endif //OIV_NET_DOC
	 static SbThread* create( void *(threadRoutine)(void* _userData), void *structData);

  /**
   * Destroys the specified thread. Note that, in general, threads are automatically
   * destroyed by the operating system when the application (process) exits.
   */
  static void destroy(SbThread *);

  /**
   * Signals the specified thread that it should terminate ASAP.
   * This is a non-blocking call. Then user should call destroy to wait for real thread termination.
   */
  static void kill(SbThread *thread);

  /**
   * Returns true if another thread or process requested termination of this thread.
   * It is particularly useful for stopping an infinitely looping worker thread.
   */
  static SbBool isStopRequested();

  /**
   * Valid Priorities values and behavior are OS dependent.
   * on WINDOWS platforms
   *    priority is in the range [ THREAD_PRIORITY_LOWEST .. THREAD_PRIORITY_HIGHEST ]
   * on UNIX it depends on the current scheduling policy (which is SCHED_OTHER by default)
   *    see sched_get_priority_min/sched_get_priority_max for details in manpage 
   *    of the given UNIX System.
   */

  /**
   * Increase thread priority of value unit.
   * @return 0 on success.
   */
  static int increasePriorityLevel( int value = 1 );

  /**
   * Decrease thread priority of value unit.
   * @return 0 on success.
   */
  static int decreasePriorityLevel( int value = 1 );

  /**
   * Return the priority of the current thread.
   */
  static int getPriorityLevel();

  /**
   * Set the priority of the current thread.
   * @return 0 on success.
   */
  static int setPriorityLevel( int );

  /**
   * Returns a unique id identifying the current thread. Actually returns the native
   * (pthreads or Win32) thread id.
   */
  static SbThreadId_t getCurrentThreadId();

  /** 
   * Assign a debug name to a thread.
   *
   * Note: Only some platforms/compilers have the capability to use/show thread names.
   *
   * Note: Currently only implemented on Windows platforms and only in the Debug build.
   */
  static void setName(const SbThreadId_t &threadId, const char* threadName);

SoINTERNAL public:
  /** 
   * Yield processor to any other thread that is waiting to execute.
   */
  static bool switchThread();

  /** 
   * returns true if (the given) thread is running 
   */
  SbBool isRunning() { return bIsRunning; }

  /** 
   * makes the thread wait for a given period (ms)
   */
  static void sleep_ms( int dT_ms );
  

 protected:
  SbThread(void);
  ~SbThread(void);

 // Launcher
 static void * threadTaskLauncher( void *_threadLancher );
 bool bIsRunning;  // true while running (false after exit)

private:

#ifdef _WIN32
  SbHandle threadHandle;
#endif

  SbThreadId_t threadId;
  typedef std::list< SbThread* > SbThreadList;
  static SbThread::SbThreadList m_threadList;
  static SbThreadMutex m_threadListMutex;
  bool m_mustStop;
};


#if defined(_WIN32)
#pragma warning( pop )
#endif

#endif //_TGS_SB_THREAD_H_

