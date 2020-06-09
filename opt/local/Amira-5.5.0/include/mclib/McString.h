/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup mclib mclib
/// @{
#ifndef _MC_STRING_H
#define _MC_STRING_H

#include "McWinDLLApi.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#ifdef HX_HAS_STDIOSTREAM
    #include <ostream>
    using std::ostream;
    #include <streambuf>
    using std::streambuf;
#else
    #include <iostream.h>
#endif

#include "McDArray.h"
#include "McHandable.h"
#include "McWildMatch.h"
#include "McPrimType.h"
#include "McAssert.h"

#if defined(__hpux) && !defined(_HPUX_SOURCE)
extern "C" {
    int strcasecmp(const char* s1, const char* s2);
    int strncasecmp(const char* s1, const char* s2, size_t n);
}
#endif

class McStringStream;

/// Character Strings.
class MCLIB_API McString : public McDArray<char>, public McHandable
{
    void remove0() { resize(size()-1); }

  public:

    /**@name Constructors/Destructor: */
    //@{

    /// Default constructor.
    McString()
    :   McDArray<char>(0,16), McHandable(), theStream(0)
    {
        append(char(0));
    }

    /// Copy constructor.
    McString( const McString& rhs )
    :   McDArray<char>( rhs ), McHandable(), theStream(0)
    { }


    /// This constructs a McString from a character string.
    McString( const char* str )
    :   McDArray<char>(0,16), McHandable(), theStream(0)
    {
        if (str)
            append(static_cast<mclong>(strlen(str)+1),str);
        else
            append(0);
    }

    /// Constructor taking printf() format
    McString( int inDummy, const char * inFormat, ... )
    :   McDArray<char>(0,16), McHandable(), theStream(0)
    {
        va_list arg;
        va_start(arg, inFormat);
        vprintf(inFormat,arg);
        va_end(arg);
    }

    /// Copy a part from another string.
    McString( const char* str , int start,int len)
    :   McDArray<char>( 0, len+1 ), McHandable(), theStream(0)
    {
        append( len, &str[start] );
        append( char(0) );
    }

    /// Destructor
    ~McString();
    //@}

    /**@name String comparison: */
    //@{

    /// Assignment operator
    McString & operator=( const McString& rhs );

    /// Is equal.
    bool operator==(const char *other) const
    {
        return !(*this!=other);
    }

    /// Is equal.
    bool operator==(char *other) const
    {
        return !(*this!=other);
    }

    /// Is equal.
    bool operator==(const McString& other) const
    {
        return !(*this!=other);
    }

    /// Not equal (using alphabetical order).
    bool operator!=(const char *other) const
    {
        if (!other) {
            // If the McDArray behind the string contains anything, even just
            // the terminating \0, the strings are not equal.
            return length()>-1;
        }
        if ((size_t)length()!=strlen(other)) {
            return true;
        }
        else {
            return strcmp(*this,other)!=0;
        }
    }

    /// Not equal (using alphabetical order).
    bool operator!=(char *other) const
    {
        return *this!=const_cast<const char*>(other);
    }

    /// Not equal (using alphabetical order).
    bool operator!=(const McString& other) const
    {
        if (length()!=other.length()) {
            return true;
        }
        return strcmp(*this,other)!=0;
    }

    /// Less than (using alphabetical order).
    bool operator<(const char *other) const
    {
        return strcmp(*this,other)<0;
    }

    /// Less or equal than (using alphabetical order).
    bool operator<=(const char *other) const
    {
        return strcmp(*this,other)<=0;
    }

    /// Larger than (using alphabetical order).
    bool operator>(const char *other) const
    {
        return strcmp(*this,other)>0;
    }

    /// Larger or equal than (using alphabetical order).
    bool operator>=(const char *other) const
    {
        return strcmp(*this,other)>=0;
    }

    /** Performs a natural string comparison, i.e. digits are interpreted as
        numbers. The comparison is case-insensitive and number take precedence
        over characters. */
    int compareAlphaNumeric(const McString &other) const;

    //@}

    /**@name String manipulation: */
    //@{
    /// Equivalent to *this = "".
    void clear()
    {
        McDArray<char>::clear() ;
        append( char(0) ) ;
    }

    /// Assignment. Initialize string with @c str.
    McString& operator=( const char* str )
    {
        McDArray<char>::clear();
        if (str)
          append(static_cast<mclong>(strlen(str)+1),str);
        else
          append(char(0));
        return *this;
    }

    /// Append @c str to string.
    McString& operator+=(const char* str)
    {
        if (str) {
            remove0();
            append(static_cast<mclong>(strlen(str)+1),str);
        }
        return *this ;
    }

    /// Append single character to string.
    McString& operator+=(char ch)
    {
        (*this)[length()] = ch ;
        append( char(0) ) ;
        return *this ;
    }

    /// Addition.
    McString operator+( const McString& str2 ) const
    {
        McString str(*this);
        str += str2;
        return str;
    }

    /// Addition.
    friend McString operator+( const McString& str1, const char *str2 )
    {
        McString str(str1);
        str += str2;
        return str;
    }

    /// Addition.
    friend McString operator+( const char* str1, const McString& str2 )
    {
        McString str(str1);
        str += str2;
        return str;
    }

    /// returns substring with ix1 being the index of the first char and ix2 being the index of the last
    McString substr(unsigned int ix1,unsigned int ix2) const {
        McString str;
        unsigned int size = ix2-ix1+1,i;
        str.resize(size+1);
        for (i=0;i<size;i++)
            str[i]=(*this)[ix1+i];
        str[i]=0;
        return str;
    }
    
    /// remove an inner section from the string. ix1 is the index of the first char of this section, 
    /// and ix2 is the index of the first char behind the section
    void substrRemove(unsigned int ix1, unsigned int ix2) {
        mcrequire(ix2 >= ix1);
        mcrequire(ix1 < length());
        mcrequire(ix2 < length());    
        for (int i = 0; ix2+i < length(); i++) {
            (*this)[ix1+i] = (*this)[ix2+i];
        }
        setLength(length()-(ix2-ix1));        
    }

    /// Converts string to upper case characters.
    void toUpper()
    {
        for (int i=length()-1; i>=0; i--)
            data[i] = (char)toupper(data[i]);
    }

    /// Converts string to lower case characters.
    void toLower()
    {
        for (int i=length()-1; i>=0; i--)
            data[i] = (char)tolower(data[i]);
    }


    /** Convert string to float.
    @c param returns true if a number can be read  */
    float toFloat(bool &len) const {
        const char* ptr = getString();
        float n=0;
        len = sscanf(ptr, "%f", &n) != 0;
        return n;
    }

    /** Convert string to integer.
    @c param returns true if a number can be read */
    int toInt(bool &len) const {
        const char* ptr = getString();
        int n=0;
        len =  sscanf(ptr, "%d", &n) != 0;
        return n;
    }

    /** Returns whether the string is alphanumeric, i.e. matches [a-zA-Z0-9]* */
    bool isAlnum() const;

    /** Returns whether the string consists of letters, i.e. matches [a-zA-Z]* */
    bool isAlpha() const;

    /** Returns whether the string is numeric, i.e. matches [0-9]* */
    bool isDigit() const;

    /// Returns if string starts with a given prefix.
    bool startsWith(const char* prefix) const;

    /// Remove leading and trailing blanks.
    void unpad()
    {
        int to=length()-1;
        while(to>0 && (*this)[to]==' ') to--;

        int from=0;
        while(from<to && (*this)[from]==' ') from++;

        resize(to+2);
        (*this)[to+1]=0;

        remove(0,from);
    }

    /** Write into string using printf() syntax. It is guaranteed that
        no buffer overflow occurs. */
    char* printf(const char* format, ...);

    /// Write into string using vprintf() syntax.
    char* vprintf(const char* format, va_list arg);


    /// Sets the string to the printed value of a 64 bit int value in base 10.
    void setInt64( const mcint64 inNum );

    /// Returns the string converted to a 64 bit int value to the base 10.
    static mcint64 toInt64(const char*);

    /// Returns the string converted to a 64 bit int value to the base 10.
    mcint64 toInt64() const;

    /// Inserts substring before given position
    void insertStr(int addbefore, const char* str)
    {
        McDArray<char>::insert(addbefore, static_cast<mclong>(strlen(str)), str);
    }

    /// Removes the last \a n characters from the string.
    void removeLast(mclong n=1)
    {
        McDArray<char>::removeLast(n+1);
        append('\0');
    }

    /// Replaces any occurrance of "s1" with "s2" starting at character offset "start"
    void replaceSubStr( const char * s1, const char * s2, size_t start=0 )
    {
        size_t n = strlen(s1);
        if ( n==0 ) return;

        size_t len = length();
        if (start >= len)
            return;

        McString s(data, 0, static_cast<int>(start));
        for (size_t i = start; i < len; i++) {
            if (strncmp(&data[i], s1, n) == 0) {
                s += s2;
                i += n-1;
            } else {
                s += data[i];
            }
        }
        *this = s;
    }

    /// Replaces characters
    void replace( const char c1, const char c2 )
    {
        McString s;
        for (int i = 0; i < length(); i++) {
            if (data[i]==c1)
                data[i]=c2;
        }
    }

    /** Split a copy of the string by a character. All sub-strings separated
        by @c inToken will be put into @c outArr. If @c inToken appears as
        the first or last character of the string, empty strings will be
        inserted into @c outArr. Likewise, two subsequent occurences of @c
        inToken cause an empty string to be inserted into @c outArr. */
    void explode( char inToken, McDArray<McString> & outArr ) const;

    /** Creates a new string enclosed by quotation marks if necessary. The
        resulting string will be recognized as a single token by the class
        McStringTokenizer. On default, quotation marks are only added if the
        string contains white spaces characters. If @c quote_always is true
        quotation marks are added even if the string does not contain white
        spaces. If quotation marks are added but the string itself does
        contain such characters these characters are quoted by a back slash.*/
    McString protect(bool quote_always=false) const;

    //@}

    /**@name Find methods: */
    //@{
    /** Find a substring.
        @return the starting index of the substring or -1 if not found.
    */
    int index(const char *needle) const
    {
        return(index(needle,0));
    }

    /** Find a substring, starting at @c start.
        @return the starting index of the substring or -1 if not found.
    */
    int index(const char *needle,int start) const
    {
        const char *tmp=strstr(&(*this)[start],needle);
        if (tmp==NULL)
            return -1;
        return static_cast<int>(tmp-&(*this)[0]);
    }

    /** find a substring, ignores case.
        @return  the starting index of the substring or -1 if not found.
     */
    int iindex(const char *needle) const
    {
        size_t nl=strlen(needle);
        int imax=length()-static_cast<int>(nl);
        char first=(char)toupper(needle[0]);
        for (int i=0 ; i<=imax ; i++) {
            if (toupper(data[i])==first)
                if (strncasecmp(needle,data+i,nl)==0) {
                    return(i);
                }
        }
        return(-1);
    }

    /** Find element t, starting at @c start.
        @return the index of @c t or -1 if t was not found.*/
    int index (const char t,int start=0) const {
        const char *end=&last();
        for (const char *i=data+start ; i<=end ; i++) {
            if (*i==t){
                return static_cast<int>(i-data);
            }
        }
        return -1;
    }

    /** Find element t, starting at @c start, searching <b>
      backward</b>. If start is -1, search is started at the end.
      @return the index of @c t or -1 if t was not found. */
    int rindex(const char t,int start=-1) const {
        const char *i;
        if (start>=0){
            i=data+start;
        } else {
            i=&last();
        }

        for ( ; i>=data ; i--) {
            if (*i==t){
                return static_cast<int>(i-data);
            }
        }
        return(-1);
    }

    //@}

    /// Number of characters in the string (excluding the terminating \0).
    int length() const{ return size() - 1 ; }

    /// Sets the string to the given length. If the length is increased,
    /// additional characters are uninitialized. If the length in decreased, the
    /// string is truncated.
    void setLength(mclong newsize) {
        newsize=resize(newsize+1);
        data[newsize-1]='\0';
    }

    /// Returns whether a string is the be considered as empty.
    bool isEmpty() const { return length()==0 || data[0]=='\0'; }
    
    /// Returns whether a string contains only whitespace (may be empty, too)
    bool isWhitespace() const {  
        if (isEmpty())
            return true;      
        const char *end=&last();
        for (const char *i=data; i<=end ; i++) {
            if (*i!=' ' && *i!='\r' && *i!='\t' && *i!='\n' && *i!='\0' ){
                return false;
            }
        }        
        return true;
    }

    /// Pointer to the data in C-format.
    char* getString() { return data; }

    /// Const pointer to the data in C-format.
    const char* getString() const { return data; }

    /// Matches string against pattern containing wildcards.
    int matches(const char* pattern) const {
        return mcWildMatch((const char*)(*this), pattern);
    }

    /// Write string to output stream
    inline friend ostream& operator<<(ostream& os, const McString& str)
    { return os << (const char *)str; }

    /// Returns ostream that allows << operations going directly into the McString.
    ostream & stream();

    /// Compares @c n characters of two strings without regard to case.
    static int strncasecmp(const char* s1, const char* s2, size_t n) {
#if defined _WIN32 || defined _WIN64
        return ::_strnicmp(s1,s2,n);
#else
        return ::strncasecmp(s1,s2,n);
#endif
    }

    /// Compares two strings without regard to case.
    static int strcasecmp(const char* s1, const char* s2) {
#if defined _WIN32 || defined _WIN64
        return ::_stricmp(s1,s2);
#else
        return ::strcasecmp(s1,s2);
#endif
    }

  private:

    // Returns the number at the current string location.
    static int parseNumber(const char *&a);

    McStringStream* theStream;
};

#endif

/// @}
