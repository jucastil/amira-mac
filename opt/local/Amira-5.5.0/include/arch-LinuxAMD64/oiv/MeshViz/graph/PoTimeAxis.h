/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_TIME_AXIS_
#define  _PO_TIME_AXIS_

#include <MeshViz/graph/PoAxis.h>
#include <MeshViz/graph/PbDateFormatMapping.h>
#include <MeshViz/graph/PiNumericFormat.h>
#include <MeshViz/graph/PiDate.h>


#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFString.h>


class SoMatrixTransform ;

#ifdef OIV_NET_DOC
/**
* @DTEXT  Class to build a time axis.
* 
* @ingroup GraphAxis
* 
* @DESCRIPTION
*    This class builds a time axis in the plane XY. A time axis is an axis with date 
*    graduations. 
*    
*    The abscissa or ordinate (following "type" field) of the start point of the axis is 
*    startDate. The abscissa or ordinate (following "type" field) of the end point of the 
*    axis is endDate. Both these abscissas and ordinates are computed according to the 
*    association between a dates range and a coordinates range defined by the the current
*    date mapping.
*    
*    Both startDate and endDate are described by character strings. The syntax must 
*    fit the current date format, otherwise the axis is not built.
* 
*    The current date format and the current date mapping are defined as follows :
*    If the method setDateFormatMapping(formatMapping) is called, the current date format 
*    and the current date mapping are defined by "formatMapping". Otherwise the current 
*    date format and the current date mapping are specified in the current 
*    inherited state (cf property node PoDateFormatMapping).
*    
*    Axis graduations are displayed depending on date representation given by the 
*    fields gradRep and timesPeriod. gradRep is a list of representations and 
*    timesPeriod is a list of possible duration. 
*    
*    Let D be the duration between startDate and endDate (date at the start and the end 
*    of the axis), and let Di (0 <= i < gradRep.getNum()) be the set of duration defined 
*    by the parameter timesPeriod. The choice of a representation is done as follows:
* <PRE> 
*    if  D < D0                   the axis is built using representation gradRep[0]
*    if  Di <= D < Di+1           the axis is built using representation gradRep[i+1]
*    if  DgradRep.GetNum()-2 < D  the axis is built using representation 
*                                 gradRep[gradRep.GetNum() -1]
* </PRE>
*    If the duration list is not provided (empty string), the representation is not chosen 
*    depending on D. It is chosen depending on calendar threads given with each 
*    representation.
*    
*    Syntax of the string timesPeriod which defines the set of duration. This is a 
*    rational language defined as follows:
* <PRE>
*    timesPeriod = ([r]U)*
*    where (U) is the time units selected from SEC, MIN, HOU, DAY, YEA
*    where ([r]) optional positive real value defining the number of units (=1 id r is 
*    not defined)
*    ([r]U)* means that [r]U sequence may be repeated 0 or several times
*    The 'space' characters are ignored
*    examples:
*    timesPeriod = "10SEC  20MIN  HOU"
*      defines 3 duration: 10 seconds, 20 minutes et 1 hour
*    timesPeriod = "0.2SEC  30MIN  10DAY  2YEA"
*      defines 4 duration: 0.2 seconds, 30 minutes, 10 day et 2 years
* </PRE>
*    remark: For all units but SEC, only the integer part of (r) is used. Specifying a 
*    decimal part is then useless.
*    
*    A date graduation representation allows the application:
*     - to draw it using different levels, 
*     - to define a date thread between each graduation of a level,
*     - to display for each graduation of a level, one or several components 
*       of the date,
*     - to display any character strings for each graduation.
*
*    A graduation representation is defined by:
*       - the number of graduation level,
*       - for each level
*          - the graduation thread (number of seconds, minutes, hours, days, months or years)
*          - an optional character string before the first indicator
*          - a set of appearance indicators of one of the date components, followed 
*            by an optional character string.
*
*    All levels of graduation are displayed underneath each other for horizontal axes 
*    and side by side for vertical axes. The first level is the closest to the main line of 
*    the axis, the last one is the furthest. Date components are seconds, minutes, hours, 
*    days, months and years.
*    
*    Syntax of the string gradRep[i] which defines the date representation number i. 
*    This is a rational language defined as follows:
* <PRE>
*    gradRep[i] = R(/R)*
*    where (/) stands for the current new line character (attribute of the current 
*    miscellaneous attributes - cf PoAxis description) (it appears before definition of new level) 
*    where (R) is the representation of dates for one level. This rational language is 
*    also defined by:
*    R = [[r]U]  ['string']  ([n]C['string'])*
*    where [[r]U] (optional) defines the thread between 2 following calendar 
*    graduations of a level
*    where ['string'] (optional) is any character strings between quotes
*    where [n]C defines the appearance of one of the date calendar components
*     [n]C = (s) to display the number of seconds (0 to 59.999...) 
*         = (m) to display the number of minutes (0 to 59)
*         = (H) to display the number of hours (0 to 23)
*         = (D) to display the day number in the month (1 to 31)
*         = (nD) to display n first characters of the name of the day of the week
*         = (M) to display number of the month (1 to 12)
*         = (nM) to display n first characters of the name of the month of the year
*         = (Y) or (2Y)to display 2 last digits of the year
*         = (4Y)to display all digits of the year
* </PRE>
*    Characters for the day of the month or month of the year are displayed using 
*    current language defined by the field language.
*    n is an integer value greater than 0.
* 
*    Warning: To insert the quote (') character in the string ['string'], it must be 
*    repeated twice. If the string must only contain (')  character then the string must 
*    be defined as ''''.  To insert a (") in the string a back-slash character (\) must be 
*    added before it.
* 
*    Example 1:
* <PRE>
*    gradRep[i] = "20 SEC 'at'm''''s'sec'  /  1MIN  D 3M Y' ' H'h' m''''  "
* </PRE>
*    defines two levels of graduations:
*       - at the first level: 
*         - graduations are displayed every 20 seconds.
*         - each of the graduations begins with the character string (at) followed by 
*           the number of minutes, the date relating to the graduation, then a (') 
*           character, then the number of seconds, and finally the character string (sec). 
*           For instance: at 12'50sec
*
*       - at the second level:
*         - graduation are displayed for every minutes.
*         - each of the graduations begins with the number of the day in the month, 
*           then the first three characters for the month of the year, then the 2 last digits 
*           of the year, then ( ), then the number of hours, then (h),then the number of 
*           minutes and finally ('). For instance: 3MAR94 18h13'
*
*    Possible appearance of graduation may be for instance:
* <PRE>
*    at11'50sec   at12'10sec  at12'30sec  at12'50sec  at13'10sec  at13'30sec
*                      3MAR94 18h12'   3MAR94 18h13'
* </PRE>
*    
*    Example 2:
* <PRE>
*    gradRep[i] = "5 MIN H'h'm'''' /  DAY D'-'3M  /  YEA 4Y"
* </PRE>
*    defines three levels of graduation:
*       - at the first level: 
*         - graduations are displayed every 5 minutes.
*         - each graduation begins with the number of hours of the date relating to the 
*           graduation, then (h), then the number of minutes followed by (').
*
*       - at the second level:
*         - graduations are displayed for each day.
*         - each graduation begins with the number of the day, then (-), then the first 
*           three characters of the month.
*
*       - at the third level:
*         - graduations are displayed using 4 digits for each year.
*
*    Possible appearance of graduation may be for instance:
* <PRE>
*    11h15'   11h20'   11h25'   11h30'   11h35'   11h40'
*                              3-MAR
*                                1995
* </PRE>
*    
*   - Note 1:
*    With a thread in minutes, each graduation is displayed starting at 0 second.
*    With a thread in hour, each graduation is displayed starting at 0 minute, 0 second.
*    With a thread in day, each graduation is displayed starting at 0 hour, 0 minute, 0 
*    second.
*    With a thread in month, each graduation is displayed starting 1st of the month, 0 
*    hour, 0 minute, 0 second.
*    With a thread in year, each graduation is displayed starting 1st of January, 0 hour, 
*    0 minute, 0 second.
*    When for a specific level, all graduations are out of bounds, then a graduation is 
*    displayed at the middle of the axis. The previous sample shows this with level 2 
*    graduation (3-MARS) and level 3 one (1995).
*    
*   - Note 2:
*    If gradRep.getNum=0 or gradRep[0] = "", Graph Master does its best to display 
*    date graduation using the best possible number of levels and best possible thread. 
*    This choice is only relating to duration between the bounding dates of the axis. 
*    The field timesPeriod is not used.
*    
*   - Note 3:
*    If a representation does not specify the thread type for the first level (i.e. the field 
*    [[r]U] is not defined),  then Graph Master computes the thread relating to D 
*    duration between the boundary dates of the axis. A calendar component (type 
*    [n]C) is automatically chosen by Graph Master and the components defined in the 
*    representation with a lower unit are ignored. For instance, if the representation is 
*    "3D'-'D':'H'h'm''''s / 3M 4Y", and if Graph Master chooses an hour thread, the 
*    minutes and seconds components of the first level won't be displayed, only "3D'-
*    'D':'H'h'" will be used.
*    If a representation specifies the thread unit, but not the number of units (only [r] 
*    is given), then Graph Master also computes this number of units relating to D, but 
*    all calendar components of the representation will be used.
*    
*   - Note 4:
*    If a representation does not specify the thread type for the level 2, 3,... (i.e. the 
*    field [[r]U] is not defined), then Graph Master chooses the current thread unit 
*    depending on previous thread unit. If at level 1, the thread unit is minutes, then 
*    thread units at level 2 will be hours,... Note 3 applies when choosing calendar 
*    components.
*    For instance if the representation is "5MIN 3D'-'D':'H'h'm'''' / m'min'H'h '3D'-'D", 
*    then Graph Master chooses hours as the thread unit for level 2 and only 
*    components 'H'h '3D'-'D" will be used at this level.
* 
* 
* @FILE_FORMAT_DEFAULT
*    PoTimeAxis {
*    @TABLE_FILE_FORMAT
*       @TR gradVisibility @TD VISILITY_DEPEND
*       @TR gradPosition @TD GRAD_DEPEND
*       @TR gradPath @TD PATH_DEPEND
*       @TR gradFontName @TD ""
*       @TR gradFontSize @TD 0
*       @TR gradDistAxis @TD 0
*       @TR gradAddStringVisibility @TD false
*       @TR gradAddString @TD ""
*       @TR marginType @TD REL_MARGIN
*       @TR marginStart @TD 0
*       @TR marginEnd @TD 0
*       @TR titleVisibility @TD VISILITY_DEPEND
*       @TR titlePosition @TD TITLE_DEPEND
*       @TR titlePath @TD PATH_DEPEND
*       @TR titleFontName @TD ""
*       @TR titleFontSize @TD 0
*       @TR titleDistAxis @TD 0
*       @TR titleString @TD ""
*       @TR gridVisibility @TD VISILITY_DEPEND
*       @TR gridLengthGradSide @TD 0
*       @TR gridLengthGradOtherSide @TD 1
*       @TR arrowVisibility @TD VISIBILITY_DEPEND
*       @TR arrowHeight @TD 0.03
*       @TR arrowLength @TD 0.05
*       @TR tickVisibility @TD VISIBILITY_DEPEND
*       @TR tickPosition @TD TICK_GRAD_SIDE
*       @TR tickMainLength @TD 0
*       @TR tickSubLength @TD 0
*       @TR tickSubDef @TD PERIOD_MAIN_TICK
*       @TR tickNumOrPeriod @TD 1
*       @TR tickFirstGrad @TD 1
*       @TR tickLastGrad @TD 1
*       @TR reverseFlag @TD AXIS_REVERSE_DEPEND
*       @TR startDate @TD "1-01-70"
*       @TR endDate @TD "2-01-70"
*       @TR coord @TD 0
*       @TR type @TD X
*       @TR language @TD ENGLISH
*       @TR gradFit @TD GRAD_UNFIT
*       @TR gradRep @TD ""
*       @TR timesPeriod @TD ""
*    @TABLE_END
*    }
* 
* @CATALOG_PARTS_INCLUDE potimeaxis.cat.html
* 
* 
*/

#else
/**
* @DTEXT  Class to build a time axis.
* 
* @ingroup GraphAxis
* 
* @DESCRIPTION
*    This class builds a time axis in the plane XY. A time axis is an axis with date 
*    graduations. 
*    
*    The abscissa or ordinate (following "type" field) of the start point of the axis is 
*    startDate. The abscissa or ordinate (following "type" field) of the end point of the 
*    axis is endDate. Both these abscissas and ordinates are computed according to the 
*    association between a dates range and a coordinates range defined by the the current
*    date mapping.
*    
*    Both startDate and endDate are described by character strings. The syntax must 
*    fit the current date format, otherwise the axis is not built.
* 
*    The current date format and the current date mapping are defined as follows :
*    If the method setDateFormatMapping(formatMapping) is called, the current date format 
*    and the current date mapping are defined by "formatMapping". Otherwise the current 
*    date format and the current date mapping are specified in the current 
*    inherited state (cf property node PoDateFormatMapping).
*    
*    Axis graduations are displayed depending on date representation given by the 
*    fields gradRep and timesPeriod. gradRep is a list of representations and 
*    timesPeriod is a list of possible duration. 
*    
*    Let D be the duration between startDate and endDate (date at the start and the end 
*    of the axis), and let Di (0 <= i < gradRep.getNum()) be the set of duration defined 
*    by the parameter timesPeriod. The choice of a representation is done as follows:
* <PRE> 
*    if  D < D0                   the axis is built using representation gradRep[0]
*    if  Di <= D < Di+1           the axis is built using representation gradRep[i+1]
*    if  DgradRep.getNum()-2 < D  the axis is built using representation 
*                                 gradRep[gradRep.getNum() -1]
* </PRE>
*    If the duration list is not provided (empty string), the representation is not chosen 
*    depending on D. It is chosen depending on calendar threads given with each 
*    representation.
*    
*    Syntax of the string timesPeriod which defines the set of duration. This is a 
*    rational language defined as follows:
* <PRE>
*    timesPeriod = ([r]U)*
*    where (U) is the time units selected from SEC, MIN, HOU, DAY, YEA
*    where ([r]) optional positive real value defining the number of units (=1 id r is 
*    not defined)
*    ([r]U)* means that [r]U sequence may be repeated 0 or several times
*    The 'space' characters are ignored
*    examples:
*    timesPeriod = "10SEC  20MIN  HOU"
*      defines 3 duration: 10 seconds, 20 minutes et 1 hour
*    timesPeriod = "0.2SEC  30MIN  10DAY  2YEA"
*      defines 4 duration: 0.2 seconds, 30 minutes, 10 day et 2 years
* </PRE>
*    remark: For all units but SEC, only the integer part of (r) is used. Specifying a 
*    decimal part is then useless.
*    
*    A date graduation representation allows the application:
*     - to draw it using different levels, 
*     - to define a date thread between each graduation of a level,
*     - to display for each graduation of a level, one or several components 
*       of the date,
*     - to display any character strings for each graduation.
*
*    A graduation representation is defined by:
*       - the number of graduation level,
*       - for each level
*          - the graduation thread (number of seconds, minutes, hours, days, months or years)
*          - an optional character string before the first indicator
*          - a set of appearance indicators of one of the date components, followed 
*            by an optional character string.
*
*    All levels of graduation are displayed underneath each other for horizontal axes 
*    and side by side for vertical axes. The first level is the closest to the main line of 
*    the axis, the last one is the furthest. Date components are seconds, minutes, hours, 
*    days, months and years.
*    
*    Syntax of the string gradRep[i] which defines the date representation number i. 
*    This is a rational language defined as follows:
* <PRE>
*    gradRep[i] = R(/R)*
*    where (/) stands for the current new line character (attribute of the current 
*    miscellaneous attributes - cf PoAxis description) (it appears before definition of new level) 
*    where (R) is the representation of dates for one level. This rational language is 
*    also defined by:
*    R = [[r]U]  ['string']  ([n]C['string'])*
*    where [[r]U] (optional) defines the thread between 2 following calendar 
*    graduations of a level
*    where ['string'] (optional) is any character strings between quotes
*    where [n]C defines the appearance of one of the date calendar components
*     [n]C = (s) to display the number of seconds (0 to 59.999...) 
*         = (m) to display the number of minutes (0 to 59)
*         = (H) to display the number of hours (0 to 23)
*         = (D) to display the day number in the month (1 to 31)
*         = (nD) to display n first characters of the name of the day of the week
*         = (M) to display number of the month (1 to 12)
*         = (nM) to display n first characters of the name of the month of the year
*         = (Y) or (2Y)to display 2 last digits of the year
*         = (4Y)to display all digits of the year
* </PRE>
*    Characters for the day of the month or month of the year are displayed using 
*    current language defined by the field language.
*    n is an integer value greater than 0.
* 
*    Warning: To insert the quote (') character in the string ['string'], it must be 
*    repeated twice. If the string must only contain (')  character then the string must 
*    be defined as ''''.  To insert a (") in the string a back-slash character (\) must be 
*    added before it.
* 
*    Example 1:
* <PRE>
*    gradRep[i] = "20 SEC 'at'm''''s'sec'  /  1MIN  D 3M Y' ' H'h' m''''  "
* </PRE>
*    defines two levels of graduations:
*       - at the first level: 
*         - graduations are displayed every 20 seconds.
*         - each of the graduations begins with the character string (at) followed by 
*           the number of minutes, the date relating to the graduation, then a (') 
*           character, then the number of seconds, and finally the character string (sec). 
*           For instance: at 12'50sec
*
*       - at the second level:
*         - graduation are displayed for every minutes.
*         - each of the graduations begins with the number of the day in the month, 
*           then the first three characters for the month of the year, then the 2 last digits 
*           of the year, then ( ), then the number of hours, then (h),then the number of 
*           minutes and finally ('). For instance: 3MAR94 18h13'
*
*    Possible appearance of graduation may be for instance:
* <PRE>
*    at11'50sec   at12'10sec  at12'30sec  at12'50sec  at13'10sec  at13'30sec
*                      3MAR94 18h12'   3MAR94 18h13'
* </PRE>
*    
*    Example 2:
* <PRE>
*    gradRep[i] = "5 MIN H'h'm'''' /  DAY D'-'3M  /  YEA 4Y"
* </PRE>
*    defines three levels of graduation:
*       - at the first level: 
*         - graduations are displayed every 5 minutes.
*         - each graduation begins with the number of hours of the date relating to the 
*           graduation, then (h), then the number of minutes followed by (').
*
*       - at the second level:
*         - graduations are displayed for each day.
*         - each graduation begins with the number of the day, then (-), then the first 
*           three characters of the month.
*
*       - at the third level:
*         - graduations are displayed using 4 digits for each year.
*
*    Possible appearance of graduation may be for instance:
* <PRE>
*    11h15'   11h20'   11h25'   11h30'   11h35'   11h40'
*                              3-MAR
*                                1995
* </PRE>
*    
*   - Note 1:
*    With a thread in minutes, each graduation is displayed starting at 0 second.
*    With a thread in hour, each graduation is displayed starting at 0 minute, 0 second.
*    With a thread in day, each graduation is displayed starting at 0 hour, 0 minute, 0 
*    second.
*    With a thread in month, each graduation is displayed starting 1st of the month, 0 
*    hour, 0 minute, 0 second.
*    With a thread in year, each graduation is displayed starting 1st of January, 0 hour, 
*    0 minute, 0 second.
*    When for a specific level, all graduations are out of bounds, then a graduation is 
*    displayed at the middle of the axis. The previous sample shows this with level 2 
*    graduation (3-MARS) and level 3 one (1995).
*    
*   - Note 2:
*    If gradRep.getNum=0 or gradRep[0] = "", Graph Master does its best to display 
*    date graduation using the best possible number of levels and best possible thread. 
*    This choice is only relating to duration between the bounding dates of the axis. 
*    The field timesPeriod is not used.
*    
*   - Note 3:
*    If a representation does not specify the thread type for the first level (i.e. the field 
*    [[r]U] is not defined),  then Graph Master computes the thread relating to D 
*    duration between the boundary dates of the axis. A calendar component (type 
*    [n]C) is automatically chosen by Graph Master and the components defined in the 
*    representation with a lower unit are ignored. For instance, if the representation is 
*    "3D'-'D':'H'h'm''''s / 3M 4Y", and if Graph Master chooses an hour thread, the 
*    minutes and seconds components of the first level won't be displayed, only "3D'-
*    'D':'H'h'" will be used.
*    If a representation specifies the thread unit, but not the number of units (only [r] 
*    is given), then Graph Master also computes this number of units relating to D, but 
*    all calendar components of the representation will be used.
*    
*   - Note 4:
*    If a representation does not specify the thread type for the level 2, 3,... (i.e. the 
*    field [[r]U] is not defined), then Graph Master chooses the current thread unit 
*    depending on previous thread unit. If at level 1, the thread unit is minutes, then 
*    thread units at level 2 will be hours,... Note 3 applies when choosing calendar 
*    components.
*    For instance if the representation is "5MIN 3D'-'D':'H'h'm'''' / m'min'H'h '3D'-'D", 
*    then Graph Master chooses hours as the thread unit for level 2 and only 
*    components 'H'h '3D'-'D" will be used at this level.
* 
* 
* @FILE_FORMAT_DEFAULT
*    PoTimeAxis {
*    @TABLE_FILE_FORMAT
*       @TR gradVisibility @TD VISILITY_DEPEND
*       @TR gradPosition @TD GRAD_DEPEND
*       @TR gradPath @TD PATH_DEPEND
*       @TR gradFontName @TD ""
*       @TR gradFontSize @TD 0
*       @TR gradDistAxis @TD 0
*       @TR gradAddStringVisibility @TD FALSE
*       @TR gradAddString @TD ""
*       @TR marginType @TD REL_MARGIN
*       @TR marginStart @TD 0
*       @TR marginEnd @TD 0
*       @TR titleVisibility @TD VISILITY_DEPEND
*       @TR titlePosition @TD TITLE_DEPEND
*       @TR titlePath @TD PATH_DEPEND
*       @TR titleFontName @TD ""
*       @TR titleFontSize @TD 0
*       @TR titleDistAxis @TD 0
*       @TR titleString @TD ""
*       @TR gridVisibility @TD VISILITY_DEPEND
*       @TR gridLengthGradSide @TD 0
*       @TR gridLengthGradOtherSide @TD 1
*       @TR arrowVisibility @TD VISIBILITY_DEPEND
*       @TR arrowHeight @TD 0.03
*       @TR arrowLength @TD 0.05
*       @TR tickVisibility @TD VISIBILITY_DEPEND
*       @TR tickPosition @TD TICK_GRAD_SIDE
*       @TR tickMainLength @TD 0
*       @TR tickSubLength @TD 0
*       @TR tickSubDef @TD PERIOD_MAIN_TICK
*       @TR tickNumOrPeriod @TD 1
*       @TR tickFirstGrad @TD 1
*       @TR tickLastGrad @TD 1
*       @TR reverseFlag @TD AXIS_REVERSE_DEPEND
*       @TR startDate @TD "1-01-70"
*       @TR endDate @TD "2-01-70"
*       @TR coord @TD 0
*       @TR type @TD X
*       @TR language @TD ENGLISH
*       @TR gradFit @TD GRAD_UNFIT
*       @TR gradRep @TD ""
*       @TR timesPeriod @TD ""
*    @TABLE_END
*    }
* 
* @CATALOG_PARTS_INCLUDE potimeaxis.cat.html
* 
* 
*/

#endif //OIV_NET_DOC
class MESHVIZ_API PoTimeAxis : public PoAxis {

  SO_KIT_HEADER(PoTimeAxis) ;


 public:

  /**
   *  Language used for date.
   */
  enum Language {
    /**
     *  The date graduations are displayed in English.
     */
    ENGLISH,   
    /**
     *  The date graduations are displayed in French.
     */
    FRANCAIS,  
    /**
     *  The date graduation are displayed in German.
     */
    DEUTSCH,   
    /**
     *  The date graduations are displayed in Spanish.
     */
    ESPANOL    
  } ;

  enum GradFit {
    /**
     *  The first graduation is in round figures.
     */
    GRAD_FIT,  
    /**
     *  The first graduation is not in round figures.
     */
    GRAD_UNFIT 
  } ;



  /**
   *  Axis orientation.
   */
  enum Type {
    /**
     *  The time axis is a X-axis.
     */
    X,         
    /**
     *  The time axis is a Y-axis.
     */
    Y          
  } ;

  /* Fields */

  /**
   * Start date of the axis. Make sure that this date is in the same format as defined 
   * by the current date format.
   */
  SoSFString startDate ;

  /**
   * End date of the axis. Make sure that this date is in the same format as defined 
   * by the current date format.
   */
  SoSFString endDate ;

  /**
   * Abscissa or ordinate of the axis according to the axis type.
   */
  SoSFFloat  coord ;

  /**
   * Axis type. (X or Y).
   */
  SoSFEnum   type ;

  /**
   * Language of date graduations.
   */
  SoSFEnum   language ;

  /**
   * This flag indicates if the first graduation is in round figures or not.
   */
  SoSFEnum   gradFit ;

  /**
   * List of date representation. If the list is empty, the representation is 
   * automatically computed.
   */
  SoMFString gradRep ;

  /**
   * String containing gradRep.getNum() -1 sub-strings. Each sub-string specifies a 
   * time period used to choose the date representation. If this string is empty, this 
   * choice is automatically made.
   */
  SoSFString timesPeriod ;

  /* Methods */

  /**
   * Constructor.
   */
  PoTimeAxis()
    { init(TRUE) ; }

  /**
   * Constructor.
   */
  PoTimeAxis(const char *_startDate, const char *_endDate, float _coord,
             Type _type = X)
    { init(FALSE, _startDate, _endDate, _coord, _type) ; }

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void rebuild() ;

  /**
   * Sets a reference to a PbDateFormatMapping object for the input date 
   * format and for the association dates, coordinates. If this method is not called
   * (or called passing NULL as argument), this is the date format and date mapping 
   * defined in the current inherited state (defined with the property node
   * PoDateFormatMapping) which are used.
   */
  void setDateFormatMapping(PbDateFormatMapping *formatMapping) ;

  /**
   * Gets a reference to a PbDateFormatMapping object for the input date 
   * format and for the association dates, coordinates.
   */
  const PbDateFormatMapping *getDateFormatMapping() const ;

  /*----------------------------------------------------------------------------*/

 PoINTERNAL public:

  static void initClass() ;
	static void exitClass() ;

  enum Tdate_elem_form {
    TSECOND,
    TMINUTE,
    THOUR,
    TDAY_NUMBER, 
    TWEEK_DAY,
    TMONTH_NUMBER,
    TYEAR_MONTH,
    TYEAR
  } ;

  enum Tdate_step {
    TSTEP_UNKNOWN,
    TSTEP_SECONDS,
    TSTEP_MINUTES,
    TSTEP_HOURS,
    TSTEP_DAYS,
    TSTEP_MONTHS,
    TSTEP_YEARS
  } ;

  struct Tdate_elem {
    int                form_prefixe;  // prefixe du code
    Tdate_elem_form    form;          // code calendaire
    char               *append_str;   // string commentaire apres le code
  } ;


  struct Tdate_axis_level_rep {
    Tdate_step       step;            // unite de pas calendaire du niveau
    float            num_step;        // nombre d'unite de pas
    int              ten_power;       // puis de 10 pour pas seconde
    char             *append_str;     // string commentaire prefixe
    int              num_date_elems;  // nb de code cal par graduation
    Tdate_elem       *date_elems;     // liste des code calendaire
  } ;

  struct Tdate_axis_rep {
    int                   num_level;   // nb de niveaux de l'axe
    Tdate_axis_level_rep  *level_rep;  // liste des rep. par niveau
  } ;

  struct Tdate_interv {
    float        num_units;
    Tdate_step   units;
  } ;

  struct Tdate_list {                        
    int           num_dates;       // nb d'intervalles de date - 1 
    Tdate_interv  *dates;          // liste des dates
  }  ;

 protected:
  // Time axis attr
  struct TimeAxisAttr {
    PbDateFormatMapping *formatMapping ;
    PiDate              startDate ;
    PiDate              endDate ;
    PiNumericFormat     numericFormat ;
    Plane               plane ;
    int                 num_date_limit ;
    PiDate              *date_limit ;
    int                 num_rep ;
    Tdate_axis_rep      *date_axis_rep ;
  } ;

  // Methods
  // Destructor
  virtual ~PoTimeAxis() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;

  // Manage the connection with PbBase objects
  virtual void basicObjectChange(PbBase *basicObj) ;

  // Save all axis attributes which can be modified by MeshViz.
  virtual void saveAxisAttr() ;

  // Overloaded methods
  virtual void preRebuild() ;
  virtual void addElementsAllCaches() ;

 private:
  // Init method
  void init(SbBool isDefault, const char *startDate=NULL, const char *endDate=NULL, 
            float coord=0.0, Type type = X) ;

  // Compute axis tranformation
  void computeTransfo(const SbVec2f &refPoint, SoMatrixTransform *transfo, 
                      float &deltaX, float &deltaY) ;

  // Get the date axis representation
  void getDateAxisRep(const PiDate &date_min, const PiDate &date_max,
                      Tdate_axis_rep &date_rep) ;

  // Copy a date representatiom
  static void copyDateRep(Tdate_axis_rep &dst_date_rep, 
                          const Tdate_axis_rep &src_date_rep) ;

  // Init date step of level 0
  static void initDateStepOfLevel0(Tdate_axis_rep &date_rep, const PiDate &date_delta) ;

  // Init date element
  static void initDateElem(Tdate_axis_level_rep &level_rep) ;

  // Init step, the unit step is given
  static void initDateNumStep(Tdate_axis_level_rep &level_rep, const PiDate &date_delta) ;

  // Free a date axis rep (all fields are free)
  static void freeDateAxisRep(Tdate_axis_rep &axis_rep) ;

  // Free a list of Tdate_axis_rep
  static void freeDateAxisRepList(int num_axis_rep, Tdate_axis_rep *axis_rep_list) ;

  // Compute automactic date representation
  void initAutoRep(const PiDate &date_delta, Tdate_axis_rep &date_rep) ;

  // Choose best date representation from a list of date representation
  void chooseBestDateRep(int num_rep, const Tdate_axis_rep *rep, 
                         const PiDate &date_delta, Tdate_axis_rep &date_rep) ;

  // Get list of graduations
  void getGradList(const PiDate &date_1, const PiDate &date_2, 
                   GradFit grad_fit,
                   const Tdate_axis_level_rep &level_rep,
                   int &num_gradu, char ***gradu_string_list,
                   float **x_gradu_list) ;

  // Get first date graduation
  void getFirstDateGrad(const PiDate &date_1, const PiDate &date_2, 
                        Tdate_step step, float float_step, GradFit
                        grad_fit, PiDate &date_ref) ;

  // Get string associated to a internal date
  void getStringDate(const PiDate &date, int form_prefixe, 
                     Tdate_elem_form form, char *string_date) ;

  // Build date graduations
  void buildDateGrads(const PiDate &date_1, const PiDate &date_2, 
                      const Tdate_axis_rep &date_rep, SoGroup *group) ;

  // Set date axis representation from the two associated fields
  // gradRep and timesPeriod.
  void setDateAxisRep() ;

  //--------- All this methods are used for the parser of timesPeriod --------
  static void parseDateList(char *form, Tdate_list *dl, int *err_ind) ;
  static void parseDateListNewDate(double num_units, int units) ;
  static Tdate_list *date_list ;
  friend int tpdlparse(void);
  friend int tpdllex(void) ;

  //--------- All this methods are used for the parser of gradRep ------------
  static void parseAxisRep(char *form, int n_l, Tdate_axis_rep *da_rep, 
                           int *err_ind) ;
  static void parseAxisRepNewLevel(double num_step, int step, char *append_str) ;
  static void parseAxisRepAddToLevel(int form_prefixe, int form, char *append_str) ;
  static Tdate_axis_rep *date_axis_rep ;
  friend int tpaxparse(void) ;
  friend int tpaxlex(void) ;

  // Computed axis attributes
  TimeAxisAttr timeAxisAttr ;

  // Date format and mapping
  PbDateFormatMapping *m_dateFormatMapping, m_defaultDateFormatMapping ;

  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_TIME_AXIS_ */

