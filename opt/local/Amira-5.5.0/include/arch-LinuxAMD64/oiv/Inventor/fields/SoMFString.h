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


#ifndef  _SO_MF_STRING_
#define  _SO_MF_STRING_

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFString subclass of SoMField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Multiple-value field containing any number of strings.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A multiple-value field that contains any number of strings.
 *   
 *   SoMFStrings are written to file as one or more strings within double quotes. Any
 *   characters (including newlines) may appear within the quotes. To include a
 *   double quote character within the string, precede it with a backslash. For
 *   example:
 *   
 *   <PRE>
 *    [ cowEnizer , "Scene Boy" , "He said, \"I did not!\"" ]
 *    </PRE>
 *    
 * Unicode Support
 * 
 *    Unicode is an industry standard for encoding text of all forms and 
 *    languages for use by computers. Open Inventor supports Unicode 
 *    encoding, which allows internationalization of text in a standard 
 *    cross-platform fashion. 
 *      
 *    String and as well as classes like SoSFString 
 *    support the wchar_t type which is used for Unicode 
 *    strings, and all of the text nodes are able to render Unicode 
 *    strings.
 *
 *    SbString includes methods for construction of Unicode strings,
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
 * 
 */ 

class INVENTOR_API SoMFString : public SoMField {

  // Use standard field stuff
  SO_MFIELD_HEADER(SoMFString, SbString, const SbString &);
  SO_MFIELD_SETVALUESPOINTER_HEADER(SbString);
    
    public:
  //
  // Some additional convenience functions:
  //

  /**
   * Sets @B num @b values, starting at index @B start @b, to the strings in the
   * given character arrays.
   * [OIV-WRAPPER-NOT-WRAP]
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE void  setValues(int start, int num, const char *strings[]);

  /**
   * Deletes all values currently in this field and sets this field to contain only
   * the given string.
   * [OIV-WRAPPER-NOT-WRAP]
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE void  setValue(const char *string);

  /**
   * Sets @B num @b values, starting at index @B start @b, to the strings in the
   * given character arrays.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  void  setValues(int start, int num, const SO_WCHAR_T *strings[]);

  /**
   * Deletes all values currently in this field and sets this field to contain only
   * the given string.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  void  setValue(const SO_WCHAR_T *string);

  /**
   * Convenience function to delete text from consecutive strings.
   * All text from the given character of one line (fromChar in
   * fromLine) to the given character of another line (toChar in
   * toLine), inclusive, is deleted. Any leftover text on fromLine
   * and toLine is merged into one line.
   */
  void  deleteText(int fromLine, int fromChar, int toLine, int toChar);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  void checkUnicode(int index);

};

#endif /* _SO_MF_STRING_ */

