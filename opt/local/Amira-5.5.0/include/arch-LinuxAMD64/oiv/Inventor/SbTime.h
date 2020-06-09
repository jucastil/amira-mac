/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nick Thompson (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SB_TIME_
#define _SB_TIME_

#include <Inventor/sys/port.h>

#ifdef _WIN32
#  include <time.h>
#else
#  include <sys/time.h>
#endif

#include <math.h>
#include <limits.h>
#include <Inventor/SbBase.h>
#include <Inventor/SbString.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbTime
//
//  Representation of a time.  Some parts are not adequately debugged:
//  for example, it is not clear when it is legal to have negative
//  values.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Class for representation of a time.
 * 
 * @ingroup Basics
 * 
 * @DESCRIPTION
 *   This class represents and performs operations on time. Operations may be done in
 *   seconds, seconds and microseconds, or using a @B struct @b @B timeval @b
 *   (defined in@B  time.h @b).
 *
 * @SEE_ALSO
 *    SbElapsedTime
 * 
 * 
 */ 

class INVENTORBASE_API SbTime {

 public:
  /**
   * Default constructor. The time value is not initialized.
   */
  SbTime() {}

  /**
   * Constructor taking seconds. NOTE
   * that an integer parameter will not automatically cast to a double to invoke the
   * constructor taking seconds; that is, SbTime(1) will result in a compilation
   * error. SbTime(1.0) must be used instead. This is to avoid errors in upgrading
   * from an earlier release, in which SbTime(1) had different semantics. In future
   * releases, this distinction will be eliminated, and the effect of SbTime(1.0) and
   * that of SbTime(1) will be identical.
   */
  SbTime(double sec);

  /**
   * Constructor taking seconds and microseconds. 
   */
  SbTime(time_t sec, long usec);

 private:
  // Constructor taking milliseconds
  //
  // NOTE! This constructor has been removed.  Change existing uses of
  //          SbTime(msec)
  // to
  //          time_t secs = msec / 1000;
  //          SbTime(secs, 1000 * (msec - 1000 * sec))
  // The constructor was removed because it led to unexpected results --
  // while SbTime(1.0) results in 1 second, SbTime(1) resulted in 1
  // MILLIsecond).  Its declaration has been kept, as "private", so that 
  // existing code using it will get compilation errors; if it was removed
  // completely, an existing use of SbTime(1) would silently cast to
  // SbTime(1.0) resulting in hard-to-find bugs.  This declaration
  // will be removed entirely in a future release, so that SbTime(1)
  // will be equivalent to SbTime(1.0).
  SbTime(uint32_t msec);

 public:
  /**
   * Constructor taking a struct timeval.
   */
  SbTime(const struct timeval *tv);

  /**
   * Get the current time (seconds since Jan 1, 1970).
   */
  static SbTime getTimeOfDay();

  /**
   * Set to the current time (seconds since Jan 1, 1970).
   */
  void setToTimeOfDay();

  /**
   * Get a zero time.
   */
  static SbTime zero();
  
  /**
   * Sleep for specified time (in msec).
   * 
   */
  static void sleep(const int msec);

  /**
  * Sleep for specified time (in microsec).
  * 
  */
  static void usleep(size_t usec);

#if !defined(_WIN32) && !defined(__NUTC__)
  /**
   * Deprecated. Get a time far, far into the future.
   * Replaced by SbTime::maxTime() method.
   */
  static SbTime max();
#endif

  /**
   * Get a time far, far into the future.
   * Replace the deprecated SbTime::max() method.
   */
  static SbTime maxTime();

  /**
   * Set time from a double (in seconds).
   */
  void setValue(double sec);

  /**
   * Set time from seconds + microseconds.
   */
  void setValue(time_t sec, long usec);

  /**
   * Set time from a struct timeval.
   */
  void setValue(const struct timeval *tv);

  /**
   * Set time from milliseconds.
   */
  void setMsecValue(unsigned long msec);

  /**
   * Get time in seconds as a double.
   * [OIVJAVA-WRAPPER NAME{getDoubleValue}]
   */
  double getValue() const;

  /**
   * Get time in seconds and microseconds.
   * [OIVJAVA-WRAPPER PACK{TimeVal}]
   */
  void getValue(time_t &sec, long &usec) const;

  /**
   * Get time in a struct timeval.
   * [OIV-WRAPPER NO_WRAP]
   */
  void getValue(struct timeval *tv) const;

  /**
   * Get time in milliseconds (for Xt).
   */
  unsigned long getMsecValue() const;

  /**
   * Convert to a string. The default format is seconds with 3 digits of fraction
   * precision. @B fmt @b is a character string that consists of field descriptors
   * and text characters, in a manner analogous to @B printf(). @b Each field
   * descriptor consists of a \% character followed by another character which
   * specifies the replacement for the field descriptor. All other characters are
   * copied from @B fmt @b into the result. The following field descriptors are
   * supported:
   * <PRE>
   *   \%  the `\%' character
   *   D  total number of days
   *   H  total number of hours
   *   M  total number of minutes
   *   S  total number of seconds
   *   I  total number of milliseconds
   *   U  total number of microseconds
   *   h  hours remaining after the days (00-23)
   *   m  minutes remaining after the hours (00-59)
   *   s  seconds remaining after the minutes (00-59)
   *   i  milliseconds remaining after the seconds (000-999)
   *   u  microseconds remaining after the seconds (000000-999999)
   * </PRE>
   * The uppercase descriptors are formatted with a leading `-' for negative times;
   * the lowercase descriptors are formatted fixed width, with leading zeros. For
   * example, a reasonable format string might be "elapsed time: \%M minutes, \%s
   * seconds". The default value of @B fmt, @b "\%S.\%i", formats the time as seconds
   * with 3 digits of fractional precision.
   */
  SbString format(const char *fmt = "%S.%i") const;

#ifdef _WIN32
#  define DEFAULT_FORMAT_DATE   "%#c"
#else  
#  define DEFAULT_FORMAT_DATE   "%A, %D %r"
#endif
  /**
   * Convert to a date string, interpreting the time as seconds since Jan 1, 1970.
   * The default format gives "Tuesday, 01/26/93 11:23:41 AM". See the
   * strftime() reference page for explanation of the format string.
   */
  SbString formatDate(const char *fmt = DEFAULT_FORMAT_DATE) const;

  /**
   * Addition of two times.
   */
  INVENTORBASE_API friend SbTime operator +(const SbTime &t0, const SbTime &t1);

  /**
   * Subtraction of two times.
   */
  INVENTORBASE_API friend SbTime operator -(const SbTime &t0, const SbTime &t1);

  /**
   * Addition of two times which modifies the time structure.
   */
  SbTime &operator +=(const SbTime &tm);

  /**
   * Subtraction of two times which modifies the time structure.
   */
  SbTime &operator -=(const SbTime &tm);

  /**
   * Unary negation.
   */
  SbTime operator -() const;

  /**
   * Multiplication by scalar.
   */
  INVENTORBASE_API friend SbTime operator *(const SbTime &tm, double s);
  /**
   * Multiplication by scalar.
   */
  INVENTORBASE_API friend SbTime operator *(double s, const SbTime &tm);

  /**
   * Destructive multiplication by scalar.
   */
  SbTime &operator *=(double s);

  /**
   * Division by scalar.
   */
  INVENTORBASE_API friend SbTime operator /(const SbTime &tm, double s);

  /**
   * Destructive division by scalar.
   */
  SbTime & operator /=(double s);

  /**
   * Division by another time.
   */
  double operator /(const SbTime &tm) const;

  /**
   * Modulus for two times (remainder when time1 is divided by time2).
   */
  SbTime operator %(const SbTime &tm) const;

  /**
   * Equality operator.
   */
  int operator ==(const SbTime &tm) const;

  /**
   * Inequality operator.
   */
  int operator !=(const SbTime &tm) const;

  /**
   * Relational (less than) operator.
   */
  inline SbBool operator <(const SbTime &tm) const;
  /**
   * Relational (greater than) operator.
   */
  inline SbBool operator >(const SbTime &tm) const;
  /**
   * Relational (less than or equal to) operator.
   */
  inline SbBool operator <=(const SbTime &tm) const;
  /**
   * Relational (greater than or equal to) operator.
   */
  inline SbBool operator >=(const SbTime &tm) const;

 private:
  struct timeval t;

};

inline SbBool
SbTime::operator <(const SbTime &tm) const
{
  if ((t.tv_sec < tm.t.tv_sec) ||
      (t.tv_sec == tm.t.tv_sec && t.tv_usec < tm.t.tv_usec))
    return TRUE;
  else
    return FALSE;
}

inline SbBool
SbTime::operator >(const SbTime &tm) const
{
  if ((t.tv_sec > tm.t.tv_sec) ||
      (t.tv_sec == tm.t.tv_sec && t.tv_usec > tm.t.tv_usec))
    return TRUE;
  else
    return FALSE;
}

inline SbBool
SbTime::operator <=(const SbTime &tm) const
{
  if ((t.tv_sec < tm.t.tv_sec) ||
      (t.tv_sec == tm.t.tv_sec && t.tv_usec <= tm.t.tv_usec))
    return TRUE;
  else
    return FALSE;
}

inline SbBool
SbTime::operator >=(const SbTime &tm) const
{
  if ((t.tv_sec > tm.t.tv_sec) ||
      (t.tv_sec == tm.t.tv_sec && t.tv_usec >= tm.t.tv_usec))
    return TRUE;
  else
    return FALSE;
}

#endif /* _SB_TIME_ */

