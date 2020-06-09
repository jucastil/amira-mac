/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (May 2007)
**=======================================================================*/


#ifndef  _SB_THREAD_SEMAPHORE__
#define  _SB_THREAD_SEMAPHORE__

#include <Inventor/SbBase.h>

/**
 * Semaphore management
 * 
 * @VSGEXT
 * @ingroup Threads
 * 
 * @DESCRIPTION
 * Class managing a semaphore.
 * A semaphore is a non-negative integer count and is generally
 * used to coordinate  access to resources. The initial semaphore
 * count is set to the number of free resources, then threads
 * slowly increment and decrement the count as resources are
 * added and removed. If the semaphore count drops to zero, which
 * means no available resources, threads attempting to decrement the
 * semaphore will block until the count is greater than zero.
 *
 * @SEE_ALSO
 * 
 * 
 */ 

class INVENTORBASE_API SbThreadSemaphore {

public:
  /**
   * Semaphore constructor. MaxCount is the maximum count of the counter.
   * If maxCount isn't specified (=-1), it will be initialized to initialCount.
   * If maxCount is set to -2 it will be initialized to maximum value allowed 
   * by the system (unlimited semaphore behavior).
   */
  SbThreadSemaphore(int initialCount, int maxCount = -1);

  /**
   * Destructor.
   */
  ~SbThreadSemaphore();

  void wait();
  /**
   * Try to acquire the semaphore. If the semaphore count drops to zero, which
   * means no available resources, the thread attempting to decrement the
   * semaphore will block until the count is greater than zero 
   * (meaning that another thread called release).
   *
   * The time out parameter specifies how many milliseconds to wait
   * before checking for release 
   * of the semaphore. By default there is no wait.
   */
  SbBool trywait( const unsigned int timeout_ms = 0);

  /**
   * Releases the semaphore. This call increases the semaphore count.
   */
  void release();

  /**
   * Allows adding or removing resources.
   */
  void changeCount(int);

protected:
  void* m_semHandle;
};

#endif //  _SB_THREAD_SEMAPHORE__
