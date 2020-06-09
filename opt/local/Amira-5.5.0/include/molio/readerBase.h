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

/// @addtogroup molio molio
/// @{
#ifndef READERBASE_H
#define READERBASE_H
#include <molio/MolIOWinDLLApi.h>
#include <stdio.h>
#include <mclib/McHashTable.h>
#define MAXBUFFER 1000

/** the reader classes allow simple reading of strings
    floats and ints from a file stream while offering
    additional functionality like parseline-control,
    whitespace culling and type checking **/


/// Exception: Thrown when parse error occurs
struct Parse_Error {
public:
    const char* text;
    Parse_Error(const char* s="") {text=s;}
};

/** --------------------------------------------------------
    reader (abstract)
    base class for all file-readers
**/

class MOLIO_API reader {
protected:
    enum {SIGN,LEFTVAL,RIGHTVAL,ESIGN,EXPVAL};
    /// pointer to stream that is to be parsed                                                          
    FILE* stream; 
    /// buffer for reading in strings
    char token[MAXBUFFER+1];
    /// current line number in stream
    int parseline; 
    /** maps all stream positions returned by getstreampos
       to the corresponding lineNumbers to allow line numbers
       to be reset when calling setStreamPos **/
    McHashTable<long,int> streamPosToLineNumber;
public:
    /// Constructor: will open a stream of file @c filename 
    reader(const char* filename);
    /// Destructor: will close stream
    ~reader();
    /// Skip len chars - stop if an EOL is encountered 
    void skipChars(unsigned short len); 
    /// jump to the beginning of the next line
    void nextLine(); 
    /// Check whether current token equals string @c str
    bool equals (const char* str) const;
    /// Check whether token is an int value
    bool isInt() const;
    /// Check whether token is a float value
    bool isFloat() const;
    /// get current parse line number
    int getLine() const {return parseline;}
    /// returns the current stream postion
    void getStreamPos(long& pos);
    /** set the stream position to @c pos, This function should be only used
        with values which have been previously obtained by getStreamPos
        as otherwise the lineNumbers will become incorrect **/
    void setStreamPos(long pos);
    /// return whether stream could be opened
    bool isOpen() const;
    /** eof is set to true if end of file has been reached
        is reset if we jump somewhere else (via setStreamPos) **/
    bool eof;

};

/** ---------------------------------------------------------------------
    tokenizer - 
    tokenizes file for seperationchar-orientated parsing
**/

class MOLIO_API tokenizer : public reader {
public:
    /// Constructor: will open a stream of file @c filename 
    tokenizer(const char * filename ) : reader(filename) { }
    /// Get next token while eating up whitespaces and tabs
    void getToken(); 
    /// Get next token while eating up newlines whitespaces and tabs
    void getNextToken();
    /// get next float
    float getFloat();
    /// get next int value
    int getInt(); 
    /// get next String (allocated in static memory) 
    char* getString();
    /// get Remainder of line as String (allocated in static memory) 
    char* getLineString();
    /// get Remainder of line as String (allocated in static memory) 
    char* getUntrimmedLineString();
};
     
/** ---------------------------------------------------------------
    lengthizer
    tokenizes istream for length(column)-orientated parsing
**/

class MOLIO_API lengthizer : public reader{
protected:
    // internal pointer to token
    char* tok;
public:
    /// Constructor: will open a stream of file @c filename 
    lengthizer(const char * filename) : reader(filename) {
        tok=token;
    }
    /// Get token in the next (length) columns
    void getToken(unsigned char length); 
    /// get float in the next length columns
    float getFloat(unsigned char length); 
    /// get int in the next length columns
    int getInt(unsigned char length); 
    /// get next String (allocated in mem of token) 
    char* getString(unsigned char length); 
    /** get next String and write it direclty into resStr
        without using internal mem of token **/
    void getString(char* resStr, unsigned char length);
    /// get Remainder of line as String (allocated in static memory) 
    char* getUntrimmedLineString();
};

#endif

                       

/// @}
