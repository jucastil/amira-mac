/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Mar 1996)
**=======================================================================*/


#ifndef  _PI_NUMERIC_FORMAT_
#define  _PI_NUMERIC_FORMAT_
/* include files */
#include <Inventor/SbLinear.h>
#include <MeshViz/PbBasic.h>
/* macro & constants */
#define  PDEFAULT_NUMERIC_FORMAT  "%d"
/* classes used  */
class PbNumericDisplayFormat ;

/*----------------------------------------------------------------------------*/

PoINTERNAL class MESHVIZ_API PiNumericFormat {

 public:
  // Constructor
  PiNumericFormat() ;

  // The format is an integer format
  void setFormatInteger(int tenPower) ;
  
  // The format is a floating-point format
  void setFormatFloatingPoint(int numDec, int tenPower) ;

  // The format is compute automatically relative to
  // a real domain and a step.
  void setFormatAuto(float minVal, float maxVal, float step, 
                     SbBool isRounded) ;

  // The format is set by a PbNumericDisplayFormat object and
  // by a list of values
  void setFormat(const PbNumericDisplayFormat *format, int numValues,
                 const float *values, SbBool isRounded = FALSE) ;

  // The format is set by a PbNumericDisplayFormat object and
  // by a the min and max of values
  void setFormat(const PbNumericDisplayFormat *format, float minVal,
                 float maxVal, float step, SbBool isRounded = FALSE) ;
                 
  // Return the ten power of the format
  int getTenPower() const 
    { return tenPowerFormat ; }
  
  // Return the number of decimal of the format
  int getNumDecimal() const
    { return numDecimalFormat ; }

  // Return if TRUE if the format is a floating
  // point format
  SbBool isFloatingPointFormat() const
    { return floatingPointFormat ; }

  // Return the string corresponding to a given value
  // according the format.
  void getString(float value, char *string) const ;
  
 private:
  void findBestFormatOfDomain(float firstVal, float lastVal, float step, 
                              SbBool isRounded) ;

  SbBool floatingPointFormat ;
  int    tenPowerFormat ;
  int    numDecimalFormat ;
  char   valueFormat[12] ;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PI_NUMERIC_FORMAT_ */

