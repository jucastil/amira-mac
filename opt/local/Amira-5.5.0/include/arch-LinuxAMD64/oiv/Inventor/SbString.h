/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SB_STRING_
#define _SB_STRING_

#include <string.h>
#include <wchar.h>
#include <stdarg.h>

#include <Inventor/SoInventorBase.h>
#include <Inventor/SbBase.h>
#include <Inventor/STL/string>
#include <Inventor/STL/ostream>
#include <Inventor/STL/vector>

/**
 * Class for smart character strings.
 *
 * @ingroup Basics
 *
 * @DESCRIPTION
 * The class SbString provides functions to manage strings of Latin-1
 * (ASCII) or Unicode characters.
 *
 * About Unicode:
 *
 * For more information about the Unicode standard, see http://unicode.org
 *
 * - On Microsoft Windows platforms the Unicode string is stored in utf16,
 * while on Unix/Linux based systems (including MacOSX) it uses utf32.
 * In order to get the best performance the user should use Latin1 functions
 * or WideChar functions.
 *
 * - On Microsoft Windows platforms there is no difference
 * between WideChars and Utf16 because these platforms use Utf16.
 *
 * - On Unix platforms converting between utf16 and WideChars is not free and
 * the user should try to use wide chars as much as possible.
 *
 * - Nokia's Qt toolkit uses Utf16 as internal storage, so to convert a string from
 *   or to a QString use the toUtf16 and fromUtf16 functions.
 *
 * - All access to files on the system should be done using the class
 * SbFileHelper which supports Unicode file names.
 *
 * About SO_WCHAR_T:
 *
 * This macro was introduced in order to have generic code across Windows and Linux
 * platforms. Because on Linux platforms wchar_t doesn't have the same type as on
 * the Windows platform, it was decided to add this macro to keep a common size on both
 * systems.
 *
 * Since OpenInventor 8.0 there are separate functions and it is possible to use functions,
 * on both systems, which use the same data size. Most of the time it's better to use utf16
 * functions when the size of the characters must be constant whatever is the platform.
 *
 * SO_WCHAR_T is now deprecated and should not be used except for specific issues.
 *
 * About locales:
 *
 * In order to read values in IV files the initClass function overwrites some locales using
 * the setlocales function provided by the standard lib C. Setting the locale after the
 * init of OpenInventor can break reading IV files.
 *
 * @M_SINCE OIV 8.0
 *
 * Since OpenInventor 8.0 SbString has many new functions for string manipulation:
 *  - New functions to convert strings to numbers.
 *  - New functions to convert numbers to strings.
 *  - Find functions to find sub-strings within a string.
 *  - SbString now supports "null" strings.
 *
 * @EXAMPLE
 *
 * 1) Construction of a string from a regular Latin-1/Ascii C string.
 * <PRE>
 *   SbString s = "This is my string.";
 *   or
 *   SbString s = SbString().fromLatin1( "This is my string." );
 *   or
 *   SbString s( "This is my string." );
 * </PRE>
 * 2) Construction of a string from a WideChar string (wchar_t string).
 * <PRE>
 *   SbString s = L"This is my WideChar string";
 *   or
 *   SbString s = SbString().fromWideChar( L"This is my string." );
 *   or
 *   SbString s = SbString( myStdWString );
 * </PRE>
 * 3) Conversion SbString <-> QString
 *
 * - To set an SbString from a QString:
 * <PRE>
 *   SbString s = SbString().fromUtf16( qStr.utf16() );
 * </PRE>
 *
 * - To set a QString from an SbString:
 * <PRE>
 * QString s = QString::fromUtf16( sbStr.toUtf16() );
 * </PRE>
 *
 * 4) Find/Contains examples:
 *
 * - SbString( "This is my string" ).contains( "Hello" ) returns false.
 *
 * - SbString( "This is my string" ).contains( "my" ) returns true.
 *
 * - SbString( "This is my string" ).containsAny( "aze" ) returns false.
 *
 * - SbString( "This is my string" ).containsAny( "Tzw" ) returns true.
 *
 * - SbString( "This is my string" ).find( "Zoo" ) returns SbString::npos.
 *
 * - SbString( "This is my string" ).find( "is" ) returns 2.
 *
 * - SbString( "This is my string" ).findLast( "i" ) returns 14.
 *
 * - SbString( "This is my string" ).findAny( "s" ) returns 3.
 *
 * 5) Number to string
 *
 * - SbString().setNum( 4, 16 ) produces the string "0x4".
 *
 * - SbString().setNum( 0.5 ) produces the string "0.5".
 *
 * 6) String to Number
 *
 * - SbString( "5" ).toInt( &result ) will return 5 and set the result boolean to true.
 *
 * - SbString( "aa" ).toInt( &result ) will return an undefined value and
 * set the result boolean to false.
 *
 * @SEE_ALSO
 *    SbName SbFileHelper
 *
 *
 * [OIV-WRAPPER-NO-WRAP]
 */

class INVENTORBASE_API SbString {
 public:

  /**
   * Default constructor. The string is initially empty.
   */
  SbString();

  /**
   * Constructor that takes an STL string.
   */
  SbString(const std::string &std_string);

  /**
   * Constructor that takes an STL wstring.
   */
  SbString(const std::wstring &std_wstring);

  /**
   * Constructor that takes a character string.
   */
  SbString(const char *str);

  /**
   * Constructor that takes the subset of
   * a character string from start to end (inclusive). @BR
   * For example, SbString("Testing",1,3) creates the string "est".
   */
  SbString(const char *str, int start, int end);

  /**
   * Constructor that takes the subset of
   * a wide char string from start to end (inclusive). @BR
   * For example, SbString("Testing",1,3) creates the string "est".
   */
  SbString(const wchar_t *str, int start, int end);


  /**
   * Constructor that takes an SbString.
   */
  SbString(const SbString &str);

  /**
   * Constructor that takes a wide character string.
   */
  SbString( const wchar_t* str );

  /**
   * Destructor.
   */
  ~SbString();

  /**
   * This constant is used to indicate when a find string action failed.
   * It defines a non-existing position.
   */
  static const int npos;

  /**
   * Returns TRUE if the string is empty. @BR
   * i.e. if length() == 0; otherwise returns FALSE. Null strings are also empty.
   * See makeEmpty().
   */
  SbBool isEmpty() const;

  /**
   * Returns TRUE if the string is a null string. @BR
   * A null string has never been initialized. See makeNull().
   */
  SbBool isNull() const;

  /**
   * Returns length of string (zero if null or empty).
   */
  int getLength() const;

  /**
   * Sets string to be the empty string (""). @BR
   * Note: @B freeOld @b is no longer used, it is kept for compatibility.
   * Formerly if freeOld was TRUE (default), any old storage was freed up.
   */
  void makeEmpty( const SbBool freeOld = TRUE );

  /**
   * Makes the current string null (same as uninitialized).
   */
  void makeNull();

  /**
   * Returns a new string containing the sub-string from @B startChar @b (position) to
   * @B endChar, @b inclusive. @BR  If @B endChar @b is -1 (the default), the sub-string
   * from @B startChar @b until the end is returned.
   */
  SbString getSubString(int startChar, int endChar = -1) const;

  /**
   * Deletes the characters from @B startChar @b to @B endChar, @b inclusive, from
   * the string. @BR If @B endChar @b is -1 (the default), all characters from
   * @B startChar @b until the end are deleted.
   */
  void deleteSubString(int startChar, int endChar = -1);

  /**
   * Returns TRUE if the string contains the specified substring.
   */
  SbBool contains( const SbString& str ) const;

  /**
   * Returns the position of the first occurence of the specified substring. @BR
   * If not found, returns @B npos @b.
   */
  int find( const SbString& str ) const;

  /**
   * Returns the position of the last occurence of any character contained in the
   * specified sub string. @BR
   * If not found, returns @B npos @b.
   */
  int findLast( const SbString& str ) const;

  /**
   * Returns TRUE if any of the characters listed in the str parameter exist in the string.
   */
  SbBool containsAny( const SbString& str ) const;

  /**
   * Returns the position of the first occurence of any character contained in the
   * specified sub string. @BR
   * If not found, returns @B npos @b.
   */
  int findAny( const SbString& str ) const;

  /**
   * This function replaces all the occurence of #patternStr by the new string #substStr.
   */
  void replace( const SbString& patternStr, const SbString& substStr );

  // Conversion functions

  /**
   * Returns a lowercase copy of the string. @BR
   * See also: upper()
   */
  SbString lower() const;

  /**
   * Returns an uppercase copy of the string. @BR
   * See also: lower()
   */
  SbString upper() const;

  /**
   * Sets the string to a formatted numeric value.
   * @B base @b must be one of the following values or the result is an empty string:
   * - 2 : Formatted using "%b" (Windows only)
   * - 8 : Formatted using "%o"
   * - 10 : Formatted using "%d"
   * - 16 : Formatted using "0x%x"
   */
  SbString& setNum( short value, int base = 10 );

  /**
   * @copydoc setNum
   */
  SbString& setNum( unsigned short value, int base = 10 );

  /**
   * @copydoc setNum
   */
  SbString& setNum( int value, int base = 10 );

  /**
   * @copydoc setNum
   */
  SbString& setNum( unsigned int value, int base = 10 );

  /**
   * @copydoc setNum
   */
  SbString& setNum( long value, int base = 10 );

  /**
   * @copydoc setNum
   */
  SbString& setNum( unsigned long value, int base = 10 );

  /**
   * Sets the string to a formatted numeric value.
   */
  SbString& setNum( double value );

  /**
   * Sets the string to a formatted numeric value.
   */
  SbString& setNum( float value );

  /**
   * Returns the numeric value represented by the string. @BR
   * Returns 0 if the conversion fails.
   * Optional parameter @B ok @b is set to TRUE if the conversion
   * was successful, else to FALSE.
   */
  unsigned short toUShort( SbBool* ok = NULL ) const;

  /**
   * @copydoc toUShort
   */
  short toShort( SbBool* ok = NULL ) const;

  /**
   * @copydoc toUShort
   */
  unsigned int toUInt( SbBool* ok = NULL ) const;

  /**
   * @copydoc toUShort
   */
  int toInt( SbBool* ok = NULL ) const;

  /**
   * @copydoc toUShort
   */
  unsigned long toULong( SbBool* ok = NULL ) const;

  /**
   * @copydoc toUShort
   */
  long toLong( SbBool* ok = NULL ) const;

  /**
   * @copydoc toUShort
   */
  float toFloat( SbBool* ok = NULL ) const;

  /**
   * @copydoc toUShort
   */
  double toDouble( SbBool* ok = NULL ) const;


  // Unicode conversion functions

  // - Unicode managment functions

  /**
   * Returns TRUE if the string contains Unicode characters.
   */
  SbBool isUnicode() const;

  // - From

  /**
   * Set the string from a Latin-1/ASCII C string.
   */
  SbString& fromLatin1( const char* str );

  /**
   * Set the string from a UTF-16 string.
   */
  SbString& fromUtf16( const unsigned short* str );

  /**
   * Set the string from a wide char string.
   */
  SbString& fromWideChar( const wchar_t* str );

  // - To

  /**
   * Returns the string as a Latin-1/ASCII C string.
   */
  const char* toLatin1() const;

  /**
   * Returns the string as a UTF-16 string
   */
  unsigned short* toUtf16() const;

  /**
   * Returns the string as a wide char string.
   */
  const wchar_t* toWideChar() const;

  /**
   * Returns the string as an STL wstring.
   */
  std::wstring toStdWString() const;

  /**
   * Returns the string as an STL string.
   */
  std::string toStdString() const;

  // Operators

  /**
   * Concatenation operator "+=" for SbString, SbString.
   */
  SbString &operator +=( const SbString& str );

  /**
   * Concatenation operator "+=" for string, SbString.
   */
  SbString &operator +=( const char *str );

  /**
   * Assignment operator for SbString.
   */
  SbString &operator =(const SbString &str);

  /**
   * Assignment operator for character string.
   */
  SbString &operator =(const char *str);


  /**
  * Returns a string which is the result of concatenating the string s1 and the string s2.
  */
  INVENTORBASE_API friend const SbString operator+( const SbString &s1, const SbString &s2 );

  /**
   * Equality operator for SbString / SbString comparison. @BR
   * The equality operator (==) returns TRUE if the values
   * of its operands are equal, FALSE otherwise.
   */
  INVENTORBASE_API friend int operator ==(const SbString &str1, const SbString &str2);

  /**
   * Equality operator for SbString / char* comparison. @BR
   * The equality operator (==) returns TRUE if the values
   * of its operands are equal, FALSE otherwise.
   */
  INVENTORBASE_API friend int operator ==(const SbString &str, const char *s);

  /**
   * Equality operator for char* / SbString comparison. @BR
   * The equality operator (==) returns TRUE if the values
   * of its operands are equal, FALSE otherwise.
   */
  INVENTORBASE_API friend int operator ==(const char *s, const SbString &str);

  /**
   * Inequality operator for SbString / SbString comparison. @BR
   * The inequality operator (!=) returns FALSE if its
   * operands are equal, TRUE otherwise.
   */
  INVENTORBASE_API friend int operator !=(const SbString &str1, const SbString &str2);

  /**
   * "less than" relational operator for SbString @BR
   * Returns TRUE if the first operand is less than the second,
   * FALSE otherwise.
   */
  INVENTORBASE_API friend bool operator < (const SbString &str1, const SbString &str2);

  /**
   * "greater than" relational operator for SbString @BR
   * Returns TRUE if the first operand is greater than the second,
   * FALSE otherwise.
   */
  INVENTORBASE_API friend bool operator > (const SbString &str1, const SbString &str2);

  /**
   * "less than or equal" relational operator for SbString @BR
   * Returns TRUE if the first operand is less than or equal to the second,
   * FALSE otherwise.
   */
  INVENTORBASE_API friend bool operator <= (const SbString &str1, const SbString &str2);

  /**
   * "greater than or equal" relational operator for SbString @BR
   * Returns TRUE if the first operand is greater than or equal to the second,
   * FALSE otherwise.
   */
  INVENTORBASE_API friend bool operator >= (const SbString &str1, const SbString &str2);

  /**
   * Writes the string to the specified output stream.
   */
  INVENTORBASE_API friend std::ostream& operator << (std::ostream& os, const SbString& str)
  {
    if (str.isUnicode())
      return os << str.toUtf8();

    return os << str.toLatin1();
  }


  /**
   * Returns a reasonable hash key for string.
   */
  uint32_t hash() const;

  // Deprecated functions

  /**
   * Constructor that takes an integer to be turned
   * into a string. For example, SbString(1234) creates the string "1234".
   *
   * @UNICODE_WARNING
   * Use the setNum() methods instead.
   */
  SoNONUNICODE SbString( const int digitString );

  /**
   * Returns pointer to the character string.
   *
   * @UNICODE_WARNING
   * Use the toLatin1() method instead.
   */
  SoNONUNICODE const char *getString() const;

  /**
   * Returns pointer to the std::string.
   *
   * @UNICODE_WARNING
   * Use the toSTDString() method instead.
   */
  SoNONUNICODE const std::string &getSString() const;

  /**
   * Builds a formatted string from the format string cformat and an arbitrary list of arguments.
   * The format string supports all the escape sequences of printf() in the standard C library.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE SbString & sprintf(const char * cformat, ... );

  /**
   * Write into string using vprintf() syntax.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE SbString & vprintf(const char * cformat, va_list arg);

  /**
  * This is an overloaded member function, provided for convenience.
  * It behaves essentially like the above function.
  *
  * @UNICODE_WARNING
  */
  SoNONUNICODE INVENTORBASE_API friend const SbString operator+( const SbString &s1, const char *s2 );

  /**
  * This is an overloaded member function, provided for convenience.
  * It behaves essentially like the above function.
  *
  * @UNICODE_WARNING
  */
  SoNONUNICODE INVENTORBASE_API friend const SbString operator+( const char *s1, const SbString &s2 );

  /**
  * Returns the character at index i, or 0 if i is beyond the length of the string.
  *
  * @UNICODE_WARNING
  */
  SoNONUNICODE char operator[]( int i ) const;

  /**
   * Unary "not" operator; returns TRUE if string is empty ("").
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE int operator !() const;

  /**
   * Equality operator for SbString / std::string comparison. @BR
   * The equality operator (==) returns TRUE if the values
   * of its operands are equal, FALSE otherwise.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE INVENTORBASE_API friend int operator ==(const SbString &str, const std::string &s);

  /**
   * Equality operator for std::string / SbString comparison. @BR
   * The equality operator (==) returns TRUE if the values
   * of its operands are equal, FALSE otherwise.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE INVENTORBASE_API friend int operator ==(const std::string &s, const SbString &str);

  /**
   * Inequality operator for SbString / char* comparison. @BR
   * The inequality operator (!=) returns FALSE if its
   * operands are equal, TRUE otherwise.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE INVENTORBASE_API friend int operator !=(const SbString &str, const char *s);

  /**
   * Inequality operator for char* / SbString comparison. @BR
   * The inequality operator (!=) returns FALSE if its
   * operands are equal, TRUE otherwise.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE INVENTORBASE_API friend int operator !=(const char *s, const SbString &str);

  /**
   * "less than" relational operator for SbString / char* that returns
   * TRUE if the first operand is less than the second,
   * FALSE otherwise.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator < (const SbString &str, const char *s);

  /**
   * "less than" relational operator for char* / SbString that returns
   * TRUE if the first operand is less than the second,
   * FALSE otherwise.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator < (const char *s, const SbString &str);

  /**
   * "less than" relational operator for SbString / std::string that returns
   * TRUE if the first operand is less than the second,
   * FALSE otherwise.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator < (const SbString &str, const std::string &s);

  /**
   * "less than" relational operator for std::string / SbString that returns
   * TRUE if the first operand is less than the second,
   * FALSE otherwise.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator < (const std::string &s, const SbString &str);

  /**
   * "greater than" relational operator for SbString / char* that returns
   * TRUE if the first operand is greater than the second,
   * FALSE otherwise.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator > (const SbString &str, const char *s);

  /**
   * "greater than" relational operator for char* / SbString that returns
   * TRUE if the first operand is greater than the second,
   * FALSE otherwise.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator > (const char *s, const SbString &str);

  /**
   * "greater than" relational operator for SbString / std::string that returns
   * TRUE if the first operand is greater than the second,
   * FALSE otherwise.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator > (const SbString &str, const std::string &s);

  /**
   * "greater than" relational operator for std::string / SbString that returns
   * TRUE if the first operand is greater than the second,
   * FALSE otherwise.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator > (const std::string &s, const SbString &str);

  /**
   * "less than or equal" relational operator for SbString / char* that returns
   * TRUE if the first operand is less than or equal to the second,
   * FALSE otherwise.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator <= (const SbString &str, const char *s);

  /**
   * "less than or equal" relational operator for char* / SbString that returns
   * TRUE if the first operand is less than or equal to the second,
   * FALSE otherwise.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator <= (const char *s, const SbString &str);

  /**
   * "less than or equal" relational operator for SbString / std::string that returns
   * TRUE if the first operand is less than or equal to the second,
   * FALSE otherwise.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator <= (const SbString &str, const std::string &s);

  /**
   * "less than or equal" relational operator for std::string / SbString that returns
   * TRUE if the first operand is less than or equal to the second,
   * FALSE otherwise.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator <= (const std::string &s, const SbString &str);

  /**
   * "greater than or equal" relational operator for SbString / char* that returns
   * TRUE if the first operand is greater than or equal to the second,
   * FALSE otherwise.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator >= (const SbString &str, const char *s);

  /**
   * "greater than or equal" relational operator for char* / SbString that returns
   * TRUE if the first operand is greater than or equal to the second,
   * FALSE otherwise.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator >= (const char *s, const SbString &str);

  /**
   * "greater than or equal" relational operator for SbString / std::string that returns
   * TRUE if the first operand is greater than or equal to the second,
   * FALSE otherwise.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator >= (const SbString &str, const std::string &s);

  /**
   * "greater than or equal" relational operator for std::string / SbString that returns
   * TRUE if the first operand is greater than or equal to the second, FALSE otherwise.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator >= (const std::string &s, const SbString &str);

///////////////////////////////////////////////////////////////////////////////////////////
// Wide String
///////////////////////////////////////////////////////////////////////////////////////////

  /**
   * Returns pointer to the character string.
   */
  SoNONUNICODE const SO_WCHAR_T *wgetString() const;

  /**
   * Returns pointer to the stl::wstring.
   */
   SoNONUNICODE const std::wstring &wgetSString() const;

  /**
   * Assignment operator for character string, SbString.
   */
  SoNONUNICODE SbString &operator =(const SO_WCHAR_T *str);

  /**
   * Concatenation operator "+=" for SbString.
   */
  SoNONUNICODE SbString &operator +=(const SO_WCHAR_T *str);

  /**
   * Equality operator for SbString / wchar_t* comparison.
   * The equality operator (==) returns TRUE if the values
   * of its operands are equal, FALSE otherwise.
   */
  SoNONUNICODE INVENTORBASE_API friend int operator ==(const SbString &str, const SO_WCHAR_T *s);

  /**
   * Equality operator for wchar_t* / SbString comparison.
   * The equality operator (==) returns TRUE if the values
   * of its operands are equal, FALSE otherwise.
   */
  SoNONUNICODE INVENTORBASE_API friend int operator ==(const SO_WCHAR_T *s, const SbString &str);

  /**
   * Equality operator for SbString / std::wstring comparison.
   * The equality operator (==) returns TRUE if the values
   * of its operands are equal, FALSE otherwise.
   */
  SoNONUNICODE INVENTORBASE_API friend int operator ==(const SbString &str, const std::wstring &s);

  /**
   * Equality operator for std::wstring / SbString comparison.
   * The equality operator (==) returns TRUE if the values
   * of its operands are equal, FALSE otherwise.
   */
  SoNONUNICODE INVENTORBASE_API friend int operator ==(const std::wstring &s, const SbString &str);

  /**
   * Inequality operator for SbString / wchar_t* comparison.
   * The inequality operator (!=) returns FALSE if its
   * operands are equal, TRUE otherwise.
   */
  SoNONUNICODE INVENTORBASE_API friend int operator !=(const SbString &str, const SO_WCHAR_T *s);

  /**
   * Inequality operator for wchar_t* / SbString comparison.
   * The inequality operator (!=) returns FALSE if its
   * operands are equal, TRUE otherwise.
   */
  SoNONUNICODE INVENTORBASE_API friend int operator !=(const SO_WCHAR_T *s, const SbString &str);

  /**
   * "less than" relational operator for SbString / wchar_t* that returns
   * TRUE if the first operand is less than the second,
   * FALSE otherwise.
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator < (const SbString &str, const SO_WCHAR_T *s);

  /**
   * "less than" relational operator for wchar_t* / SbString that returns
   * TRUE if the first operand is less than the second,
   * FALSE otherwise.
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator < (const SO_WCHAR_T *s, const SbString &str);

  /**
   * "less than" relational operator for SbString / std::wstring that returns
   * TRUE if the first operand is less than the second,
   * FALSE otherwise.
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator < (const SbString &str, const std::wstring &s);

  /**
   * "less than" relational operator for std::wstring / SbString that returns
   * TRUE if the first operand is less than the second,
   * FALSE otherwise.
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator < (const std::wstring &s, const SbString &str);

  /**
   * "greater than" relational operator for SbString/wchar_t* that returns
   * TRUE if the first operand is greater than the second,
   * FALSE otherwise.
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator > (const SbString &str, const SO_WCHAR_T *s);

  /**
   * "greater than" relational operator for wchar_t* / SbString that returns
   * TRUE if the first operand is greater than the second,
   * FALSE otherwise.
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator > (const SO_WCHAR_T *s, const SbString &str);

  /**
   * "greater than" relational operator for SbString/std::wstring that returns
   * TRUE if the first operand is greater than the second,
   * FALSE otherwise.
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator > (const SbString &str, const std::wstring &s);

  /**
   * "greater than" relational operator for std::wstring / SbString that returns
   * TRUE if the first operand is greater than the second,
   * FALSE otherwise.
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator > (const std::wstring &s, const SbString &str);

  /**
   * "less than or equal" relational operator for SbString / wchar_t* that returns
   * TRUE if the first operand is less than or equal to the second,
   * FALSE otherwise.
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator <= (const SbString &str, const SO_WCHAR_T *s);

  /**
   * "less than or equal" relational operator for wchar_t* / SbString that returns
   * TRUE if the first operand is less than or equal to the second,
   * FALSE otherwise.
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator <= (const SO_WCHAR_T *s, const SbString &str);

  /**
   * "less than or equal" relational operator for SbString / std::wstring that returns
   * TRUE if the first operand is less than or equal to the second,
   * FALSE otherwise.
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator <= (const SbString &str, const std::wstring &s);

  /**
   * "less than or equal" relational operator for std::wstring / SbString that returns
   * TRUE if the first operand is less than or equal to the second,
   * FALSE otherwise.
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator <= (const std::wstring &s, const SbString &str);

  /**
   * "greater than or equal" relational operator for SbString / wchar_t* that returns
   * TRUE if the first operand is greater than or equal to the second,
   * FALSE otherwise.
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator >= (const SbString &str, const SO_WCHAR_T *s);

  /**
   * "greater than or equal" relational operator for wchar_t* / SbString that returns
   * TRUE if the first operand is greater than or equal to the second,
   * FALSE otherwise.
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator >= (const SO_WCHAR_T *s, const SbString &str);

  /**
   * "greater than or equal" relational operator for SbString / std::wstring that returns
   * TRUE if the first operand is greater than or equal to the second,
   * FALSE otherwise.
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator >= (const SbString &str, const std::wstring &s);

  /**
   * "greater than or equal" relational operator for std::wstring / SbString that returns
   * TRUE if the first operand is greater than or equal to the second,
   * FALSE otherwise.
   */
  SoNONUNICODE INVENTORBASE_API friend bool operator >= (const std::wstring &s, const SbString &str);

SoINTERNAL public:

  /**
   * This function construct a string from a UTF8 string.
   *
   * This function is used for UTF8 file access on Unix platforms.
   */
  SbString& fromUtf8( const char* str );


  /**
   * This function convert this string to UTF8.
   *
   * This function is used for UTF8 file access on Unix platforms.
   */
  const char* toUtf8() const;

  static uint32_t hash(const char *s);    // Hash function
  static uint32_t hash(const SO_WCHAR_T *s); // Hash function

  static inline bool isDigit(const int c);
  static inline bool isSpace(const int c);

  /** Split string intoa world list */
  void split(std::vector<SbString>& tokens) const;

  /**
   * This function sets the string capacity.
   * That means the string can use nBytes of memory without doing any re-allocation.
   *
   * @param nBytes The new capacity, in bytes, of the string.
   */
  void setCapacity( int nBytes );


SoINTERNAL public:

  static void initClass();

  static void exitClass();

#ifdef WIN32
# define SB_LOCALE_DATA_TYPE _locale_t
# define SB_LOCALE_ALLOC_FUNC _create_locale
# define SB_LOCALE_FREE_FUNC _free_locale
# define SB_LOCALE_STRTOD_FUNC _strtod_l
# define SB_LOCALE_STRTOL_FUNC _strtol_l
# define SB_LOCALE_SPRINTF_FUNC _sprintf_l
# define SB_LOCALE_SNPRINTF_FUNC _snprintf_l
# define SB_LOCALE_SCANF_FUNC _scanf_l
# define SB_LOCALE_SSCANF_FUNC _sscanf_l
# define SB_LOCALE_FSCANF_FUNC _fscanf_l
# define SB_LOCALE_VPRINTF _vprintf_l
# define SB_LOCALE_FPRINTF_FUNC _fprintf_l
# define SB_LOCALE   , (SB_LOCALE_DATA_TYPE)SbString::getLocaleObject()
#else
# define SB_LOCALE_DATA_TYPE locale_t
# define SB_LOCALE_ALLOC_FUNC newlocale
# define SB_LOCALE_FREE_FUNC freelocale
# define SB_LOCALE_STRTOD_FUNC strtod
# define SB_LOCALE_STRTOL_FUNC strtol
# define SB_LOCALE_SPRINTF_FUNC ::sprintf
# define SB_LOCALE_FPRINTF_FUNC fprintf
# define SB_LOCALE_SNPRINTF_FUNC snprintf
# define SB_LOCALE_SCANF_FUNC scanf
# define SB_LOCALE_SSCANF_FUNC sscanf
# define SB_LOCALE_FSCANF_FUNC fscanf
# define SB_LOCALE_VPRINTF vprintf
# define SB_LOCALE   
#endif

  static float toFloat_l( const char* str, SbBool* ok = NULL );

  static double toDouble_l( const char* str, SbBool* ok = NULL );

  static long toLong_l( const char* str, SbBool* ok = NULL );

  static void toString_l( char* str, const char* format, float num );

  static void toString_l( char* str, const char* format, double num );

  static void* getLocaleObject();

  //****************************************************************************************
  // Returns a new SbString from the input string, without any tailing blank char (space or tab)
  static SbString trimRight( const SbString & _str ); 

  //****************************************************************************************
  // Returns a new SbString from the input string, without any leading blank char (space or tab)
  static SbString trimLeft( const SbString & _str );

  //****************************************************************************************
  // Returns a new SbString from the input string, without any leading nor tailing blank char (space or tab)
  static SbString trim( const SbString & _str );

private:

  // For old functions
  static void buildLocaleCache();
  static bool localeCacheInitialized;
  static bool localeDigitCache[256];
  static bool localeSpaceCache[256];

  std::wstring m_data;
  std::string m_cdata;

  mutable std::wstring m_tmpData;
  mutable std::string m_tmpCData;

  bool m_isNull;


#if !defined(_WIN32)
  // On non win32 platforms wchar_t uses 4 bytes so we must keep
  // a utf16 buffer for the toUtf16 function.
  mutable unsigned short* m_utf16Buffer;
#endif
};


inline SbBool
SbString::isEmpty() const
{
  return (isNull() || (getLength() == 0));
}

inline SbBool
SbString::isNull() const
{
  return m_isNull;
}

inline bool SbString::isDigit(const int c)
{ 
  if ((c < 0) || (c>=256))
    return false;

  if (!localeCacheInitialized)
    buildLocaleCache();
  return localeDigitCache[c];
}

inline bool SbString::isSpace(const int c)
{
  if (!localeCacheInitialized)
    buildLocaleCache();
  return localeSpaceCache[c];
}

#include <Inventor/SbName.h>

#endif // _SB_STRING_
