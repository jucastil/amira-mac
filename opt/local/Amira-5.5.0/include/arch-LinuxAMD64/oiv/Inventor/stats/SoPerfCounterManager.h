/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David BEILLOIN (Oct 2005)
**=======================================================================*/


#ifndef SO_PERF_COUNTER_MANAGER_H
#define SO_PERF_COUNTER_MANAGER_H

#include <Inventor/SbString.h>
#include <Inventor/SbTime.h>

class SoPerfCounterManagerImpl;
class SoPerfCounter;

/**
 * Performance Counter Manager.
 * 
 * @ingroup Statistics
 * 
 * @DESCRIPTION
 *   Manage a set of predefined and user defined performance counters (SoPerfCounter).
 * 
 * @SEE_ALSO
 *    SoPerfCounter
 */
class INVENTOR_API SoPerfCounterManager {
public:
  
  /**
   * Returns the existing instance.
   */
  static SoPerfCounterManager* getInstance();

  /**
   * Returns TRUE if performance counting is activated.
   * see OIV_PERFCOUNTER_ENABLE SoPreferences variables to activate it.
   */
  static SbBool isEnabled();
  
  /**
   * Resets all counters.
   */
  void resetAll();

  /** 
   * Removes disabled counters.
   * @M_SINCE 8.1
   */
  void removeDisabledCounters() const;

  /**
   * Get the instance of a specific counter.
   * Returns NULL if the counter has not been registered.
   */
  SoPerfCounter* getCounter( SbName name );

  /** 
   * Sets the refresh counter rate. @BR
   * Passing SbTime(0) disables the embedded performance schedule reporting.
   */
  void setInterval( const SbTime &intvl );
   
  /** 
   * Gets the refresh counter rate. @BR
   * A 0 (zero) value means the embedded performance schedule reporting is disabled.
   */
  SbTime getInterval();

  /**
   * Logs counter in an output file.
   */
  void log();

  /**
   * Logs counter in defined output and reset counters.
   */
  void update();

  /**
   * Register a new SoPerfCounter to the performance counter manager.
   * Adding an existing counter (by name), the perf counter registering fails.
   * Calling this method doesn't imply the manager is working with the counter:
   * to start to work with this counter you have to call the getCounter() method.
   * Passed SoPerfCounter pointer must be allocated using new() operator.
   * If the given coutner alreday exists it will be deleted when registerCounter
   * returns.
   */
  static SbBool registerCounter( SoPerfCounter* );

  /**
   * Disable a SoPerfCounter from logging by the performance counter manager.
   * Returns NULL if the counter is not existing (by name).
   */
  static SoPerfCounter* disableCounter( SbName name );

SoINTERNAL public:

  /** Returns the n-th registered counters. */
  SoPerfCounter* getCounter( int n );
  
  /**
   * End with the Performance Counter Manager.
   * All registered counters are automatically destroyed at this step.
   */
  static void finish();

  SoPerfCounterManagerImpl* m_soPerfCounterManagerImpl;

private:
  /** Returns the Performance Counter Manager created instance */
  static SoPerfCounterManager* Instance();

  /** Performance Counter Manager destructor */
  ~SoPerfCounterManager();

  /** Performance Counter Manager constructor */
  SoPerfCounterManager();

};

#endif // SO_PERF_COUNTER_MANAGER_H

/**/
