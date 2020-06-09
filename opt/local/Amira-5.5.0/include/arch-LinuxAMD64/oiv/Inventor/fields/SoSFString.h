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


#ifndef  _SO_SF_STRING_
#define  _SO_SF_STRING_

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFString subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Field containing a string.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   A field containing an string (sequence of characters).
*   
*   SoSFStrings are written to file as a sequence of ASCII characters in double
*   quotes (optional if the string doesn't contain any whitespace). Any characters
*   (including newlines) may appear within the quotes. To include a double quote
*   character within the string, precede it with a backslash. For example:
*   
*   <PRE>
*    Testing
*    "One, Two, Three"
*    "He said, \"Immel did it!\""
*    </PRE>
*    are all valid strings.
*
*    Note that Unicode characters are not directly supported in 
*    Open Inventor files. Unicode strings are written as if the bytes in
*    the string were a string of 8-bit characters. The string will be 
*    prefixed by "MCS_U_". 
*
* @SEE_ALSO
*    SoField,
*    SoSField,
*    SoMFString
* 
* 
*/ 
#else
/**
* Field containing a string.
* 
* @ingroup fields
* 
* @DESCRIPTION
*   A field containing an string (sequence of characters).
*   
*   SoSFStrings are written to file as a sequence of ASCII characters in double
*   quotes (optional if the string doesn't contain any whitespace). Any characters
*   (including newlines) may appear within the quotes. To include a double quote
*   character within the string, precede it with a backslash. For example:
*   
*   <PRE>
*    Testing
*    "One, Two, Three"
*    "He said, \"Immel did it!\""
*    </PRE>
*    are all valid strings.
*
* Unicode Support
* 
*    Unicode is an industry standard for encoding text of all forms and 
*    languages for use by computers. Open Inventor supports Unicode 
*    encoding, which allows internationalization of text in a standard 
*    cross-platform fashion. 
*      
*    String as well as classes like SoSFString 
*    support the wchar_t type which is used for Unicode 
*    strings, and all of the text nodes are able to render Unicode 
*    strings.
*
*   SbString includes methods for construction of Unicode strings,
*    string operators (=, += ,== ,!=, <, >, <=, >=), as well as a
*    query method (SbString::isUnicode()).
* 
*    To be able to display a particular Unicode character, the 
*    selected font must have a character for that Unicode value. Many
*    fonts do not contain a complete set of Unicode characters.
*    However, the shareware Unicode font file "Code2000" seems to work 
*    well. 
*  
*    Note that Unicode characters are not directly supported in 
*    Open Inventor files. Unicode strings are written as if the bytes in
*    the string were a string of 8-bit characters. The string will be 
*    prefixed by "MCS_U_". 
*
* @SEE_ALSO
*    SoField,
*    SoSField,
*    SoMFString
* 
* 
*/ 
#endif //OIV_NET_DOC

class INVENTOR_API SoSFString : public SoSField {
  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFString, SbString, const SbString &);

 public:
  //
  // Some additional convenience functions:
  //

  /**
   * Convenience method to set the field's value given a character array.
   *[OIV-WRAPPER-NOT-WRAP]
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE void setValue(const char *string);

  /**
   * Convenience method to set the field's value given a character array.
   */
  void setValue(const SO_WCHAR_T *string);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

};

#endif /* _SO_SF_STRING_ */

