/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Julien Chaplier (MMM yyyy)
**=======================================================================*/

#ifndef _SB_THREAD_RW_MUTEX_H_
#define _SB_THREAD_RW_MUTEX_H_

#include <Inventor/SbBase.h>

#include <Inventor/threads/SbThread.h>
#include <Inventor/threads/SbThreadSpinlock.h>

// keep this header for compatibility purpose
#include <Inventor/threads/SbThreadAutoLock.h>


// used to store all the thread which are currently read locked.
#include <Inventor/STL/vector>

#if defined(_WIN32)
  // Disables some warnings  -----------------------------------------------------------------------
  #pragma warning(push)
  #pragma warning( disable : 4290 ) // For functions which declare the use of exceptions.
  #pragma warning( disable : 4251 ) // dll -interface
#else
#ifdef OIV_MULTI_THREADS
#include <pthread.h>
#endif // OIV_MULTI_THREADS
#endif

class SbThreadSemaphore;

/**
 * @VSGEXT Portable readers/writer lock class.
 * 
 * @ingroup Threads
 * 
 * @DESCRIPTION
 *   This class provides read/write blocking. It is implemented using the pthreads
 *   API on UNIX/Linux and the Win32 API on Microsoft Windows.
 *   
 *   A readers/writer lock works like this: @BR
 *   Any number of threads can hold a read lock on this object at the same time.
 *   While any thread holds a read lock on this object, all requests for a write
 *   lock will block.  Conversely, only one thread can hold a write lock on this
 *   object at any time.  While a thread holds a write lock on this object, all
 *   requests for a read lock @I by other threads @i will block.  As a convenience,
 *   the thread holding the write lock may obtain any number of read locks, as long
 *   as all read locks are released before the write lock is released.
 *
 *   A readers/writer lock is appropriate for a resource that is frequently "read"
 *   (its value accessed) and is not often modified.  Particularly if the "read"
 *   access must be held for a significant amount of time.  (If all accesses, both
 *   read and write, are quite short then it may be more efficient to use the
 *   SbThreadMutex class.)  For example, the SoDB::readlock and SoDB::writelock
 *   methods use an SbThreadRWMutex to control access to the scene graph.  All
 *   Open Inventor actions automatically call SoDB::readlock to gain read access
 *   before beginning a traversal.  This allows, for example, multiple render
 *   threads to safely traverse ("read") the scene graph in parallel.
 *
 *   Generally, acquiring a read or write lock on an SbThreadRWMutex is more
 *   expensive (takes more time) than acquiring a lock on an SbThreadMutex.
 *   As with any synchronization object, failure to release a lock will usually
 *   result in a "deadlock" situation that prevents the application from running.
 *   SbThreadAutoReadLock and SbThreadAutoWriteLock provide a "safe" way to
 *   acquire a lock that will be automatically released when the object goes
 *   out of scope.
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
 *    SbThreadMutex
 * 
 * 
 */ 

class INVENTORBASE_API SbThreadRWMutex
{
 public:
  /**
   * Create a read/write mutex.
   */
  SbThreadRWMutex(const SbBool force = FALSE);
  /**
   * Destructor.
   */
  ~SbThreadRWMutex();

  /**
   * Request a write lock (exclusive access) for this mutex. Returns zero if
   * successful.
   */
  int writelock();

  /**
   * Release a write lock. Returns zero if successful.
   */
  int writeunlock();

  /**
   * Request a read lock (non-exclusive access) for this mutex. Returns zero if
   * successful.
   */
  int readlock();

  /**
   * Release a read lock. Returns zero if successful.
   */
  int readunlock();

SoINTERNAL public:

  // returns if someone has a lock on this mutex (even current thread)
  // it is particularly usefull to check if the mutex can be deleted or not.
  SbBool isUsed() const;

  // version adapted for r/w try-locking. It is a little slower
  // than the regular trylock. Synonymous for trywritelock. No
  // trylock should be done within a readlock on the same mutex.
  // !!! Not fully implemented
  SbBool trywritelock();

  // Equivalent to readlock but does not block if the reader cannot
  // lock the mutex and returns FALSE. Otherwise returns TRUE.
  // !!! Not fully implemented
  SbBool tryreadlock();

private:

  /**
   * The main mutex which provides secured access to the counters, ...
   */
  SbThreadMutex* m_rwMutex;

  /**
   * Read locks count.
   */
  int m_readLocksCount;

  /**
   * Write locks count.
   */
  int m_writeLocksCount;

  /**
   * The identifier of the thread which owns the write lock.
   */
  SbThreadId_t m_writerThreadId;

  /**
   * List of identifiers of threads which have locked the mutex in reading mode.
   */
  std::vector<SbThreadId_t> m_readerThreadIds;

  /**
   * Handle on the write semaphore.
   */
  SbThreadSemaphore* m_writeSemaphore;

  /**
   * Spin lock to get exclusive access to a portion of code.
   */
  SbThreadSpinlock m_writerThreadSpinLock;

  /**
   * Spin lock to get exclusive access to a portion of code.
   * To avoid any addition or delete of a thread inside the tracking list during a search.
   */
  SbThreadSpinlock  m_readerThreadListSpinLock;

  /**
   * Specifies if the thread is one of the reader thread.
   *  @param  threadId  Identifier of the thread to be queried.
   *  @return True if the specified thread is one of the reader thread, False otherwise.
   */
  bool isReaderThread( SbThreadId_t threadId );

  /**
   * Adds the thread in the internal list of reader threads.
   *  @param  threadId  Identifier of the thread to be added.
   */
  void addReaderThread( SbThreadId_t threadId );

  /**
   * Returns the number of read locks which have been made by the given thread.
   *  @param  threadId  Identifier of the thread to be queried.
   *  @return The number of read locks.
   */
  int getReadLocksCount( SbThreadId_t threadId );

  /**
   * Removes the thread from the internal list of reader threads.
   *  @param  threadId  Identifier of the thread to be removed.
   */
  void removeReaderThread( SbThreadId_t threadId );

};

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif //_SB_THREAD_RW_MUTEX_H_
