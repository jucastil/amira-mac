/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_NUMERIC_DISPLAY_FORMAT_
#define  _PO_NUMERIC_DISPLAY_FORMAT_

#include <MeshViz/nodes/PoNode.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFEnum.h>

class PbNumericDisplayFormat ;
class SoFieldSensor ;

/**
 * @DTEXT  Node to define the numeric display format.
 * 
 * @ingroup MeshVizMisc
 * 
 * @DESCRIPTION
 *    This node defines the current numeric display format for all subsequent 
 *    MeshViz representations which display numeric values.
 *    This node is used to define the numerical display format of mumerical values
 *    to be displayed. There are three formats available: automatic format, 
 *    floating point format, integer format. The automatic format selects the 
 *    best format adapted to the domain of values to be displayed. 
 *    The floating point format and the integer format divide the numerical value
 *    to be displayed by the power of ten, and then display it in the selected 
 *    format.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoNumericDisplayFormat {
 *    @TABLE_FILE_FORMAT
 *       @TR formatType @TD AUTO_FORMAT
 *       @TR numDecimal @TD 0
 *       @TR tenPower @TD 0
 *    @TABLE_END
 *    }
 * 
 * 
 */

class MESHVIZ_API PoNumericDisplayFormat : public PoNode {

  SO_NODE_HEADER(PoNumericDisplayFormat) ;
  

 public:

  /**
   *  Type of format.
   */
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

  /* Fields */

  /**
   * Defines the type of format.
   */
  SoSFEnum  formatType ;

  /**
   * Defines the number of decimals placed after the decimal point.
   * Used only if the format is FLOAT_FORMAT.
   */
  SoSFShort numDecimal ;

  /**
   * Defines the power of ten divisor.
   * Unused if the format is AUTO_FORMAT.
   */
  SoSFShort tenPower ;

  /* Methods */

  /**
   * Constructor.
   */
  PoNumericDisplayFormat() ;

  /*----------------------------------------------------------------------------*/

  
 SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  virtual ~PoNumericDisplayFormat() ;
  
 private:
  static void formatChangedCB(void *data, SoSensor *) ;
  
  SbBool                 m_formatChanged ;
  PbNumericDisplayFormat *m_format ;
  SoFieldSensor          *m_formatTypeSensor ;
  SoFieldSensor          *m_numDecimalSensor ;
  SoFieldSensor          *m_tenPowerSensor ;
} ; 
/*----------------------------------------------------------------------------*/

#endif /* _PO_NUMERIC_DISPLAY_FORMAT_  */

