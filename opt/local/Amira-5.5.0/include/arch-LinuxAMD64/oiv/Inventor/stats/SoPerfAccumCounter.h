/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David BEILLOIN (Oct 2005)
**=======================================================================*/


#ifndef SO_PERF_ACCUM_COUNTER_H
#define SO_PERF_ACCUM_COUNTER_H

#include <Inventor/stats/SoPerfCounter.h>

/**
 * Performance Accumulation Counter.
 * 
 * @ingroup Statistics
 * 
 * @DESCRIPTION
 *   Defines a performance counter of type accumulation.
 *   A counter is "custom" when its values are the result of an operation between the values of other counters.
 *   This counter is reset once a second.
 * 
 * @SEE_ALSO
 *    SoPerfCounter,
 *    SoPerfStateCounter,
 *    SoPerfCounterManager
 */

class INVENTOR_API SoPerfAccumCounter : public SoPerfCounter {

  SO_PERF_COUNTER_HEADER( SoPerfAccumCounter )

public:


  /**
   * Constructor with SbString.
   * Creates a counter of type "accumulation".
   * @param name Name of the counter.
   * @param description What the counter does.
   * @param module The module in which it is relevant to use this counter.
   * @param level The qualification level required to use this counter.
   * @param custom TRUE if the counter results of an operation between other counters. If it is
   * the case, you will have to set the names of the two parents and the operation with the appropriate methods.
   */
  SoPerfAccumCounter( const SbString& name, const SbString& description,
                      const SbString& module = "no module", const LevelEnum level = MEDIUM, bool custom = false );

  /** 
   * Constructor with char*. 
   * Creates a counter of type "accumulation".
   * @param name Name of the counter.
   * @param description What the counter does.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE SoPerfAccumCounter( const char* name, const char* description );

  /**
   * Destructor
   */
  virtual ~SoPerfAccumCounter();

  /**
   * Reset the counter
   */
  virtual void reset();
};

#endif // SO_PERF_ACCUM_COUNTER_H

/**/
