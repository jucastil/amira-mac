/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Ronen Barzel (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SF_BOOL_
#define  _SO_SF_BOOL_

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFBool subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing a single Boolean value.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A field containing a single Boolean (true or false) value.
 *   
 *   SoSFBools may be written to file as "0" (representing FALSE), "1", "TRUE", or
 *   "FALSE".
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFBool
 * 
 * 
 */ 

class INVENTOR_API SoSFBool : public SoSField {

  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFBool, SbBool, SbBool);

 SoINTERNAL public:
  static void         initClass();
  static void exitClass();

};

#endif /* _SO_SF_BOOL_ */

