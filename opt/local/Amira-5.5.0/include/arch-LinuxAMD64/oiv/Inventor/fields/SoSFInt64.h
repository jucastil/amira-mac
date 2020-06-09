/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Jul 2007)
**=======================================================================*/


#ifndef  _SO_SF_INT64_
#define  _SO_SF_INT64_

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFInt64 subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing a int32_t integer.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A field containing a single long (64-bit) integer.
 *   
 *   SoSFInt64s are written to file as an integer in decimal, hexadecimal (beginning
 *   with '0x') or octal (beginning with '0') format.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFInt64
 * 
 * 
 */ 

class INVENTOR_API SoSFInt64 : public SoSField {

  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFInt64, int64_t, int64_t);

 SoINTERNAL public:

  static void initClass();
  static void exitClass();

};

#endif /* _SO_SF_INT32_ */

