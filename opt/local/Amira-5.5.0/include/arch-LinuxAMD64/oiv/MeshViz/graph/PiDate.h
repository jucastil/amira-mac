/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Feb 1996)
**=======================================================================*/



#ifndef  _PI_DATE_
#define  _PI_DATE_

#include <MeshViz/PbBasic.h>

/*----------------------------------------------------------------------------*/

PoINTERNAL class MESHVIZ_API PiDate {
 public:
  // Types
  enum Language {
    ENGLISH,
    FRANCAIS,
    DEUTSCH,
    ESPANOL
  } ;

  enum StepType {
    STEP_UNKNOWN,
    STEP_SECONDS,
    STEP_MINUTES,
    STEP_HOURS,
    STEP_DAYS,
    STEP_MONTHS,
    STEP_YEARS
  } ;

  // field for date
  int   year ;           /* year number */
  int   month ;          /* month number in the year (1 a 12) */
  int   day ;            /* day number in the month (1 a 31) */
  int   dayWeek ;        /* day number in the week (0=monday,1=tuesday...) */
  int   hour ;           /* hour from 0 to 23 */
  int   minute ;         /* minute from 0 to 59 */
  float second ;         /* second from 0 to 59.9999 */

  // Constructors
  PiDate() ; // Init the date at 1/01/1970 0h 0min 0sec
  PiDate(const char *dateStr, const char *format) 
    { setDateString(dateStr, format) ; }

  // Set the internal members from a string (date) which is at
  // date format, format.
  // 0 is return if the date is set, the number of the incorrect character
  // otherwise.
  // The format is supposed to be correct.
  int setDateString(const char *dateStr, const char *format) ;

  // All this array have a significative value from the index 1
  // the index 0 contains no significative value.
  static const char**  getDays(Language lang) ;       // 8 strings  return
  static const char**  getMonths(Language lang) ;     // 12 strings return
  static const int*    getNumDaysPerMonth() ;         // 12 integers return
  static const int*    getNumDaysParMonthBissex() ;   // 12 integers return

  // Differences in days between 2 dates
  static int getDeltaDays(const PiDate &date1, const PiDate &date2) ;
  int getDeltaDays(PiDate &date) const 
    { return getDeltaDays(*this, date) ; }

  // Return day week (MONDAY = 1, TUESDAY = 2, ...)
  static int getDayWeek(const PiDate &date) ;
  int getDayWeek() const 
    { return getDayWeek(*this) ; }

  // Increment a date according to a step
  // date is modified
  static void incDateStep(float step, StepType stepType, PiDate &date) ;
  void incDateStep(float step, StepType stepType)
    { incDateStep(step, stepType, *this) ; }

  // Operator -
  friend PiDate operator-(const PiDate &date1, const PiDate &date2) ;
  
  // Operator ==
  friend int operator==(const PiDate &date1, const PiDate &date2) ;
  
  // Operator !=
  friend int operator!=(const PiDate &date1, const PiDate &date2)
  { return !(date1 == date2) ; }

  // Operator <
  friend int operator<(const PiDate &date1, const PiDate &date2) ;

  // Operator >
  friend int operator>(const PiDate &date1, const PiDate &date2)
    { return !(date1 < date2) ; }

  // Operator <=
  friend int operator<=(const PiDate &date1, const PiDate &date2)
  { return ((date1 < date2) || (date1 == date2)) ; }

  // Operator >=
  friend int operator>=(const PiDate &date1, const PiDate &date2)
  { return ((date1 > date2) || (date1 == date2)) ; }

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PI_DATE_ */
