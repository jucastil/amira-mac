/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
// SbElapsedTime.h

#ifndef _SB_ELAPSED_TIME_H_
#define _SB_ELAPSED_TIME_H_

#include <Inventor/SbBase.h>
#include <Inventor/SbTime.h>
#include <Inventor/STL/iostream>

/**
 * @VSGEXT Class for measuring elapsed time with high resolution.
 *
 * @ingroup Basics
 *
 * @DESCRIPTION
 *   This measures elapsed time in seconds. It uses the highest resolution timer
 *   available on the system, to allow measuring very short intervals.  There is
 *   no guarantee the timer resolution will be better than SbTime (which is used
 *   if no better method is available).
 *
 *
 */

class INVENTORBASE_API SbElapsedTime {

 public:
  /**
   * Constructor (initializes timer)
   */
  SbElapsedTime();

  /**
   * Resets timer.
   */
  void reset();

  /**
   * Gets elapsed time in seconds.
   */
  double getElapsed() const;

  /**
   * Gets elapsed time.
   */
  SbTime getElapsedTime() const;

 SoINTERNAL public:
  /**
   * Does this system have a hi-res timer?
   */
  static SbBool hasHiResTimer();

  /**
   * Writes the time to the specified output stream.
   */
  INVENTORBASE_API friend std::ostream& operator << (std::ostream& os, const SbElapsedTime& t);

 private:

  // Does this system have a hi-res timer?
  static SbBool haveHiRes;

  // Set by constructor and reset method
  SbTime m_startTime;

#ifdef _WIN32
  // Frequency of high performance counter
  static double m_frequency;

  // Set by constructor and reset method
  LARGE_INTEGER m_startCount;
#endif
#ifdef sun
  // Set by constructor and reset method
  hrtime_t m_startCount;
#endif
};

#endif //_SB_ELAPSED_TIME_H_

