/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SF_DOUBLE_
#define  _SO_SF_DOUBLE_

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFDouble subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing a floating-point value.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A field that contains one single-precision floating point number.
 *   
 *   SoSFDoubles are written to file in standard scientific notation.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFDouble
 * 
 * 
 */ 

class INVENTOR_API SoSFDouble : public SoSField {

  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFDouble, double, double);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

};

#endif /* _SO_SF_DOUBLE_ */

