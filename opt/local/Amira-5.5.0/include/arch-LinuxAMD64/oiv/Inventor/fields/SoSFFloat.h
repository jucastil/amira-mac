/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SF_FLOAT_
#define  _SO_SF_FLOAT_

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFFloat subclass of SoSField.
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
 *   SoSFFloats are written to file in standard scientific notation.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFFloat
 * 
 * 
 */ 

class INVENTOR_API SoSFFloat : public SoSField {

  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFFloat, float, float);

 SoINTERNAL public:
  static void         initClass();
  static void exitClass();

};

#endif /* _SO_SF_FLOAT_ */

