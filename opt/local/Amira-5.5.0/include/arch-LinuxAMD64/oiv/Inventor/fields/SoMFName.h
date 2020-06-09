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


#ifndef  _SO_MF_NAME_
#define  _SO_MF_NAME_

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFName subclass of SoMField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Multiple-value field containing any number of names.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A multiple-valued field containing any number of names. Names are short series
 *   of characters generally used for labels or names, and are stored in a special
 *   table designed to allow fast lookup and comparison. For most purposes, an
 *   SoMFString field is probably more appropriate.
 *   
 *   SoMFNames are written to file as one or more strings of characters. Names must
 *   begin with an underscore or alphabetic character, and must consist entirely of
 *   underscores, alphabetic characters, or numbers. When more than one value is
 *   present, all of the values are enclosed in square brackets and separated by
 *   commas; for example:
 *   
 *   <PRE>
 *    [ Fred, Wilma, _Part_01, translationField ]
 *    </PRE>
 *    
 * 
 * 
 */ 

class INVENTOR_API SoMFName : public SoMField {
  
  // Use standard field stuff
  SO_MFIELD_HEADER(SoMFName, SbName, const SbName &);
  SO_MFIELD_SETVALUESPOINTER_HEADER(SbName);
    
    public:
  //
  // Some additional convenience functions:
  //
  
  /**
   * Sets @B num @b values beginning at index @B start @b to the names contained in
   * the given set of character strings.
   * [OIV-WRAPPER-ARG IN,NO_WRAP{strings->Length},ARRAY]
   */
  void setValues(int start, int num, const char *strings[]);

  /**
   * Sets this field to contain one and only one value, given by @B string @b.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  void setValue(const char *string);
 
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

};

#endif /* _SO_MF_NAME_ */

