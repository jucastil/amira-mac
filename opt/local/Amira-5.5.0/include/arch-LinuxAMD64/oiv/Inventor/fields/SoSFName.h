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


#ifndef  _SO_SF_NAME_
#define  _SO_SF_NAME_

#include <Inventor/SbString.h>
#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFName subclass of SoSField. It contains an SbName.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing a name.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A field containing a name. Names are short series of characters generally used
 *   for labels or names, and are stored in a special table designed to allow fast
 *   lookup and comparison. For most purposes, an SoSFString field is probably more
 *   appropriate.
 *   
 *   SoSFNames are written to file as a string of characters. Names must begin with an
 *   underscore or alphabetic character, and must consist entirely of underscores,
 *   alphabetic characters, or numbers.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFName
 * 
 * 
 */ 

class INVENTOR_API SoSFName : public SoSField {

  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFName, SbName, const SbName &);

 public:
  //
  // Some additional convenience functions:
  //

  /**
   * Sets this field to the name equivalent to the given string.
   *
   * [OIV-WRAPPER-NOT-WRAP]
   */
  void        setValue(const char *string);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

};

#endif /* _SO_SF_NAME_ */

