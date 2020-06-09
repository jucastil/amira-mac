/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_NUMERIC_DISPLAY_FORMAT_
#define  _PB_NUMERIC_DISPLAY_FORMAT_

#include <MeshViz/graph/PbBase.h>

/**
 * @DTEXT  Class to define a numeric display format.
 * 
 * @ingroup MeshVizMisc
 * 
 * @DESCRIPTION
 *    This class is used to define a numerical display format for numerical values to be 
 *    displayed. There are three formats available: automatic format, floating point 
 *    format, integer format. The default format is the automatic format. The automatic 
 *    format selects the best format adapted to the domain of values to be displayed. 
 *    The floating point format and the integer format divide the numerical value to be 
 *    displayed by the power of ten, and then display it in the selected format.
 * 
 */
class MESHVIZ_API PbNumericDisplayFormat : public PbBase {
  

 public:

  enum FormatType {
    /**
     *  Automatic numerical display format.
     */
    AUTO_FORMAT,   
    /**
     *  Floating-point numerical display format.
     */
    FLOAT_FORMAT,  
    /**
     *  Integer numerical display format.
     */
    INTEGER_FORMAT 
  } ;

  

  /**
   * Constructor.
   */
  PbNumericDisplayFormat(FormatType type = AUTO_FORMAT, int tenPower = 0, 
                         int numDecimal = 0) ;

  /**
   * Copy constructor.
   */
  PbNumericDisplayFormat(const  PbNumericDisplayFormat &format) ;

  /**
   * Sets the numerical display format.
   * If the format is AUTO_FORMAT, numDecimal and tenPower are useless.
   * If the format is FLOAT_FORMAT, numDecimal indicates the number of 
   * decimals placed after the decimal point and tenPower is the power of ten 
   * divisor.
   * If the format is INTEGER_FORMAT, numDecimal is useless.
   */
  void setFormat(FormatType type = AUTO_FORMAT, int tenPower = 0, 
                 int numDecimal = 0) ;

  /**
   * Gets the numerical display format.
   * [OIVJAVA-WRAPPER PACK{Format}]
   */
  void getFormat(FormatType &type, int &tenPower, int &numDecimal) const
    { type = m_formatType ; tenPower = m_tenPowerFormat ; numDecimal = m_numDecimalFormat ; }

  /**
   * Assignment operator.
   */
  PbNumericDisplayFormat& operator=(const PbNumericDisplayFormat &format) ;
 private:
  void copy(const PbNumericDisplayFormat &format, SbBool isConstructorPerCopy) ;
  // Used by constructor per copy and affectation operator

  FormatType m_formatType ;
  int        m_tenPowerFormat ;
  int        m_numDecimalFormat ;
} ;

/*---------------------------------------------------------------------------*/

#endif /* _PB_NUMERIC_DISPLAY_FORMAT_ */


