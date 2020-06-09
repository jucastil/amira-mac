/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_DATE_FORMAT_MAPPING_
#define  _PB_DATE_FORMAT_MAPPING_

#include <MeshViz/graph/PbBase.h>
#include <Inventor/SbString.h>
#include <MeshViz/graph/PiDate.h>

/**
 * @DTEXT  Defines the date format and mapping.
 * 
 * @ingroup MeshVizMisc
 * 
 * @DESCRIPTION
 *    This class is used to define date input format and association between 
 *    dates and coordinates (date mapping).
 * 
 *    Date format is defined by a string of characters consisting of only the 
 *    following letters: ",',h,H, d,D, m,M, y,Y
 * <PRE>
 *      "        the date includes a number of seconds defined by a float  
 *               or integer value
 *      '        the date includes a number of minutes in 1 or 2 characters
 *      h or H   the date includes an hour in 2 characters
 *      D        the date includes a day of the week in 3 characters
 *      d        the date includes a day of the month in 2 characters
 *      M        the date includes the month defined by its first 4 letters
 *      m        the date includes the number of the month in 2 characters
 *      Y        the date includes the year in 4 characters
 *      y        the date includes the year in the 20th century in 2 characters 
 *               (the last 2)
 * </PRE>
 *    The date format is as follows
 * 
 *      ["] ['] [H | h] [d] [D] [m | M] [y | Y] in any order.
 * 
 *    The format may include the letters ", ', H or h (exclusive), d, and D,
 *    m or M (exclusive), and y or Y (exclusive), but these letters may be in 
 *    any order. Each letter may only be used once. If the format is incorrect, 
 *    an error message is generated and the current date format is not modified.
 *    
 *    Examples:
 * <PRE>
 *      date format      input date       date obtained
 *      
 *      Ddmy             TUE-10-03-92     Tuesday 10 March 1992
 *      Ddmy             TUE/10 03 92     Tuesday 10 March 1992
 *      ymd              92/03/10         10 March 1992
 *      Ymd              1992.03.10       10 March 1992
 *      dh               10-23            11 p.m. on the 10th
 *      Y                1992             1992
 *      MdY              SEPT.23.1992     23 September 1992
 * </PRE>
 *   Comments:
 *      - days, months and years may be separated by any number of separating 
 *        characters (any non-alphanumerical character).
 *      - Graph Master always checks the day of the week in relation to the number of 
 *        days in the month. If the day does not correspond to the number, Graph Master 
 *        corrects it.
 *      - Graph Master checks the number of the day in the month. If this number is 
 *        greater than the number of days in that month, Graph Master only takes the last 
 *        day of the month (taking leap years into account for the month of February)
 *
 * 
 */

class MESHVIZ_API PbDateFormatMapping : public PbBase {


 public:

  /**
   * Default constructor.
   */
  PbDateFormatMapping() ;

  /**
   * Copy constructor.
   */
  PbDateFormatMapping(const PbDateFormatMapping &dateFormatMap) ;

  /**
   * Constructor.
   */
  PbDateFormatMapping(const char *date1, const char *date2, 
                      float coord1, float coord2, const char *format = NULL) ;

  /**
   * Constructor.
   */
  PbDateFormatMapping(const SbString& date1, const SbString& date2, 
                      float coord1, float coord2, const SbString& format = "" ) ;

  /**
   * Assignment operator.
   */
  PbDateFormatMapping& operator=(const PbDateFormatMapping &dateFormatMap) ;

  /**
   * Set the format for dates.
   * 0 is return if the format is correct, otherwise
   * the number of the first incorrect character in the format (begin at 1).
   * The default format is "dmy".
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE int setFormat(const char *format) ;

  /**
   * Set the format for dates.
   * 0 is return if the format is correct, otherwise
   * the number of the first incorrect character in the format (begin at 1).
   * The default format is "dmy".
   */
  int setFormat(const SbString& format) ;

  /**
   * Gets the format for dates.
   */
  SbString getFormat() const 
    { return m_dateFormat; }

  /**
   * Defines an association between dates and coordinates (date mapping). The 
   * dates must be in the same format as defined by the method setFormat(). 0 is 
   * returned, if the mapping is correct, 1 if the date1 is incorrect, 2 if the date2 is 
   * incorrect, and 3 if date1 and date2 are identical. By default date1 is equal to 
   * "1-01-70", date2 is equal to "2-01-70", coord1 is equal to 0 and coord2 is 
   * equal to 1.
   * 0 is return if the mapping of dates is correct
   * 1 if the first date is incorrect
   * 2 if the second date is incorrect
   * 3 if date1 == date2
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE int setDateMapping(const char *date1, const char *date2, 
                     float coord1, float coord2) ;

  /**
   * Defines an association between dates and coordinates (date mapping). The 
   * dates must be in the same format as defined by the method setFormat(). 0 is 
   * returned, if the mapping is correct, 1 if the date1 is incorrect, 2 if the date2 is 
   * incorrect, and 3 if date1 and date2 are identical. By default date1 is equal to 
   * "1-01-70", date2 is equal to "2-01-70", coord1 is equal to 0 and coord2 is 
   * equal to 1.
   * 0 is return if the mapping of dates is correct
   * 1 if the first date is incorrect
   * 2 if the second date is incorrect
   * 3 if date1 == date2
   */
  int setDateMapping(const SbString& date1, const SbString& date2, 
                     float coord1, float coord2) ;

  /**
   * Gets the date mapping.
   */
  void getDateMapping(SbString &date1, SbString &date2,
                      float &coord1, float &coord2) const ;

  /**
   * Returns the coordinate associated to a date according to date mapping. 
   * FALSE is returned, if the format of the date is incorrect.
   *
   * @UNICODE_WARNING
   */
  SbBool getCoordinate(const char *date, float &c) const ;

  /**
   * Returns the coordinate associated to a date according to date mapping. 
   * FALSE is returned, if the format of the date is incorrect.
   * [OIVJAVA-WRAPPER-RETURN-TYPE SUCCESS_FLAG{throw new IllegalArgumentException()}]
   */
  SbBool getCoordinate(const SbString& date, float &c) const ;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  float   getCoordinateP(const PiDate &date) const ;
  PiDate  getDateP(float coord) ;

 private:
  // Used by constructor per copy and affectation operator
  void copy(const PbDateFormatMapping &dateFormatMap, SbBool isConstructorPerCopy) ;

  // Check date format - 0 is return if the
  // format is correct - The error character number is return 
  // otherwise.
  int checkDateFormat() const ;

  // True is return if the interval is correct
  // False otherwise
  void  setDateMappingP(const PiDate &date1, const PiDate &date2, 
                        float coord1, float coord2) ;
  PiDate   m_date1 ;
  float    m_coordinate1, m_coordinate2, m_dateIntervalSecond ;
  SbString m_dateFormat, m_date1Str, m_date2Str ;
  
} ;
/*----------------------------------------------------------------------------*/

#endif /* _PB_DATE_FORMAT_MAPPING_ */

