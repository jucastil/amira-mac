/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David BEILLOIN (Oct 2005)
**=======================================================================*/


#ifndef SO_PERF_STATE_COUNTER_H
#define SO_PERF_STATE_COUNTER_H

#include <Inventor/stats/SoPerfCounter.h>

/** 
 * Performance State Counter.
 * 
 * @ingroup Statistics
 * 
 * @DESCRIPTION
 *   Defines a performance counter of type state.
 *   A counter is "custom" when its values are the result of an operation between the values of other counters.
 *   Resetting this counter has no effect.
 * 
 * @SEE_ALSO
 *    SoPerfCounter,
 *    SoPerfAccumCounter,
 *    SoPerfCounterManager
 * 
 * 
 */

class INVENTOR_API SoPerfStateCounter : public SoPerfCounter {

  SO_PERF_COUNTER_HEADER( SoPerfStateCounter )

public:

  /** 
   * Constructor with SbString.
   * Creates a counter of type "state".
   * @param name Name of the counter.
   * @param description What the counter does.
   * @param module The module in which it is relevant to use this counter.
   * @param level The qualification level required to use this counter.
   * @param custom TRUE if the counter results of an operation between other counters. If it is
   * the case, you will have to set the names of the two parents and the operation with the appropriate methods.
   */
  SoPerfStateCounter( const SbString& name, const SbString& description,
                      const SbString& module = "no module", const LevelEnum level = MEDIUM, bool custom = false );

  /** 
   * Constructor with char*.
   * Creates a counter of type "state".
   * @param name Name of the counter.
   * @param description What the counter does.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE SoPerfStateCounter( const char* name, const char* description );

  /**
   * Destructor
   */
  virtual ~SoPerfStateCounter();

  /**
   * Resets the counter.
   * Currently this method does not do anything.
   */
  virtual void reset();

};

#endif // SO_PERF_STATE_COUNTER_H

/**/
