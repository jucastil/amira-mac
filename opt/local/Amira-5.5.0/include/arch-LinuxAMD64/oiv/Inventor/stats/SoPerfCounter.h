/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David BEILLOIN (Oct 2005)
**=======================================================================*/


#ifndef _SO_PERF_COUNTER_H_
#define _SO_PERF_COUNTER_H_

#include <Inventor/stats/SoSubPerfCounter.h>
#include <Inventor/threads/SbThreadMutex.h>

/** 
 * Abstract base class for Performance Counter.
 * 
 * @ingroup Statistics
 * 
 * @DESCRIPTION
 *   Defines the basic methods to define a performance counter.
 * 
 * @SEE_ALSO
 *    SoPerfCounterManager
 * 
 */
class INVENTOR_API SoPerfCounter {

public:

  typedef double SoPerfCounterValue;

  /**
   * Reset the counter
   */
  virtual void reset() = 0;

  /**
   * Returns the Type of current class.
   */
  static SoType getClassTypeId();

  /**
   * Returns the type of current instance.
   */
  virtual SoType getTypeId() const;

  /**
   * Returns the name of current counter; 
   */
  char* getName() { return (char*)m_name.getString(); }

  /**
   * Returns the description of current counter; 
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE char* getDescription() { return (char*)m_description.toLatin1(); }

  /**
   * Returns the description of current counter; 
   */
   SbString getStringDescription() { return m_description; }

  /**
   * Returns the value of the counter.
   */
  SoPerfCounterValue getValue();

  /**
   * Set the counter value.
   */
  virtual void setValue( SoPerfCounterValue value )  { m_mutex->lock(); m_value = value;  m_mutex->unlock(); }

  /** 
   * Sets the scale factor.
   * @M_SINCE 8.1
   */
  void setScale( SoPerfCounterValue scale ) { m_scale = scale; }

  /**
   * Returns the scale factor.
   * @M_SINCE 8.1
   */
  SoPerfCounterValue getScale() const { return m_scale; }

  /** 
   * Returns the type of the counter.
   * @M_SINCE 8.1
   */
  SbString getType() const { return m_type; }

  /**
   * Returns the module of the counter.
   * @M_SINCE 8.1
   */
  SbString getModule() const { return m_module; }

  /**
   * Returns the level of the counter.
   * @M_SINCE 8.1
   */
  SbString getStringLevel() const;

  /** 
   * Returns the level of the counter.
   * @M_SINCE 8.1
   */
  int getLevel() const { return m_level; }

  /**
   * Returns TRUE if the counter results of an operation between other counters.
   * @M_SINCE 8.1
   */
  bool isCustom() const { return m_isCustom; }

  /** 
   * Returns the name of the first parent.
   * @M_SINCE 8.1
   */
  SbName getFirstParent() const { return m_firstParent; }

  /** 
   * Returns the name of the second parent.
   * @M_SINCE 8.1
   */
  SbName getSecondParent() const { return m_secondParent; }

  /** 
   * Sets the name of the first parent.
   * @M_SINCE 8.1
   */
  void setFirstParent( SbName firstParent ) { m_firstParent = firstParent; }

  /**
   * Sets the name of the second parent.
   * @M_SINCE 8.1
   */
  void setSecondParent( SbName secondParent ) { m_secondParent = secondParent; }

  /** 
   * Returns the operation made between the two parents.
   * @M_SINCE 8.1
   */
  SbString getOperation() const { return m_operation; }

  /** 
   * Sets the operation made between the two parents.
   * @M_SINCE 8.1
   */
  void setOperation( SbString operation ) { m_operation = operation; }
  
  /**
   * Increments/Decrements counter value by 'value'.
   */
  virtual void increment( SoPerfCounterValue value ) { m_mutex->lock(); m_value += value; m_mutex->unlock(); }
  virtual void decrement( SoPerfCounterValue value ) { m_mutex->lock(); m_value -= value; m_mutex->unlock(); }

  /**
   * Sets/Gets counter id.
   */
  void setID( int id ) { m_id = id; }
  int getID() { return m_id; }

  /**
   * Sets/Gets the use state.
   */
  void setEnable( bool e ) { m_enable = e; }
  bool isEnabled() { return m_enable; }

  /** 
   * Various levels for a counter.
   * @M_SINCE 8.1
   */
  enum LevelEnum
  {
    LOW = 0,
    MEDIUM = 1,
    HIGH = 2
  };

SoINTERNAL public:

  /**
   * Initialize SoPerfCounter class.
   */
  static void initClass();

  /**
   * End with SoPerfCounter class
   */
  static void exitClass();

  /**
   * Destructor
   */
  virtual ~SoPerfCounter();

protected:
 
  /** 
   * Constructor.
   * Creates a counter.
   * @param name Name of the counter.
   * @param description What the counter does.
   * @param module The module in which it is relevant to use this counter.
   * @param level The qualification level required to use this counter.
   * @param custom TRUE if the counter results of an operation between other counters. If it is
   * the case, you will have to set the names of the two parents and the operation with the appropriate methods.
   */
  SoPerfCounter( const SbString& name, const SbString& description,
                 const SbString& module = "no module", const LevelEnum level = MEDIUM, bool custom = false );

  /** 
   * Counter type. @BR
   * A : accumulation @BR
   * S : state
   * @M_SINCE 8.1
   */
  SbString m_type;

  /**
   * Counter name.
   */
  SbName m_name;

  /**
   * Counter description.
   */
  SbString m_description;

  /**
   * Counter value.
   */
  SoPerfCounterValue m_value;

  /** 
   * A scale factor applied to the value.
   * @M_SINCE 8.1
   */
  SoPerfCounterValue m_scale;

  /** 
   * Counter's level. @BR
   * low/medium/high
   * @M_SINCE 8.1
   */
  enum LevelEnum m_level;

  /** 
   * Counter's module.
   * @M_SINCE 8.1
   */
  SbString m_module;

  /** 
   * If it's a counter based on the operation between other ones.
   * @M_SINCE 8.1
   */
  bool m_isCustom;

  /** 
   * Counter first parent.
   * @M_SINCE 8.1
   */
  SbName m_firstParent;
 
  /** 
   * Counter second parent.
   * @M_SINCE 8.1
   */
  SbName m_secondParent;

  /** 
   * The operation made between the parents.
   * @M_SINCE 8.1
   */
  SbString m_operation;

  /** 
   * @M_SINCE 8.1
   */
  SbThreadMutex* m_mutex;

private:

  /** 
   * Inits the perfcounter.
   * @M_SINCE 8.1
   */
  void init();

  static bool m_isInitialized;
  static SoType m_classTypeId;
  int m_id;
  bool m_enable;

};

#endif // _SO_PERF_COUNTER_H_

/**/
