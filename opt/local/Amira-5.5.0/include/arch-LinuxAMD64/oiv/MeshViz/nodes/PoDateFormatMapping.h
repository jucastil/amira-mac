/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_DATE_FORMAT_MAPPING_
#define  _PO_DATE_FORMAT_MAPPING_

#include <MeshViz/nodes/PoNode.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFString.h>

class PbDateFormatMapping ;
class SoFieldSensor ;

/**
 * @DTEXT  Node to define date format and mapping.
 * 
 * @ingroup GraphProperty
 * 
 * @DESCRIPTION
 *   This node defines the current date format and mapping for all MeshViz
 *   representations which use it.
 *   This node is used to define date input format and association between 
 *   dates and coordinates (date mapping).
 * 
 *   Date format is defined by a string of characters consisting of only the 
 *   following letters: ",',h,H, d,D, m,M, y,Y
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
 *   The date format is as follows
 * 
 *      ["] ['] [H | h] [d] [D] [m | M] [y | Y] in any order.
 * 
 *   The format may include the letters ", ', H or h (exclusive), d, and D,
 *   m or M (exclusive), and y or Y (exclusive), but these letters may be in 
 *   any order. Each letter may only be used once. If the format is incorrect, 
 *   an error message is generated and the current date format is not modified.
 *    
 *   Examples:
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
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoDateFormatMapping {
 *    @TABLE_FILE_FORMAT
 *       @TR date1 @TD "1-01-70"
 *       @TR date2 @TD "2-01-70"
 *       @TR coord1 @TD 0
 *       @TR coord2 @TD 1
 *       @TR format @TD "dmy"
 *    @TABLE_END
 *    }
 * 
 * 
 */

class MESHVIZ_API PoDateFormatMapping : public PoNode {

  SO_NODE_HEADER(PoDateFormatMapping) ;
  

 public:

  /* Fields */

  /**
   * Defines the first date for the association between dates and coordinates 
   * (date mapping).
   * date1 corresponds to the coord1 and date2 corresponds to the coord2.
   */
  SoSFString date1 ;

  /**
   * Defines the second date for the association between dates and coordinates 
   * (date mapping).
   */
  SoSFString date2 ;

  /**
   * Defines the first coordinate for the association between dates and 
   * coordinates (date mapping).
   */
  SoSFFloat  coord1 ;

  /**
   * Defines the second coordinate for the association between dates and 
   * coordinates (date mapping).
   */
  SoSFFloat  coord2 ;

  /**
   * Defines the format for dates.
   */
  SoSFString format ;

  /* Methods */

  /**
   * Constructor.
   */
  PoDateFormatMapping() ;

  /**
   * Returns the coordinate associated to a date
   * @return TRUE is returned if the input date is correct,
   * @return FALSE otherwise.
   * [OIVJAVA-WRAPPER-RETURN-TYPE SUCCESS_FLAG{throw new IllegalArgumentException()}]
   */
  SbBool getCoordinate(const char *date, float &coord) ;

  /*----------------------------------------------------------------------------*/

  
 SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  virtual ~PoDateFormatMapping() ;

 private:
  static void formatChangedCB(void *data, SoSensor *) ;
  static void dateCoordChangedCB(void *data, SoSensor *) ;

  void updateDateFormatMapping() ;
  
  SbBool              m_formatChanged ;
  SbBool              m_dateCoordChanged ;
  PbDateFormatMapping *m_format ;
  SoFieldSensor       *m_date1Sensor ;
  SoFieldSensor       *m_date2Sensor ;
  SoFieldSensor       *m_coord1Sensor ;
  SoFieldSensor       *m_coord2Sensor ;
  SoFieldSensor       *m_formatSensor ;

} ; 
/*----------------------------------------------------------------------------*/

#endif /* _PO_DATE_FORMAT_MAPPING_  */

