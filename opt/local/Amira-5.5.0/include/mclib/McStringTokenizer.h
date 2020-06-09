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
#ifndef MC_STRING_TOKENIZER_H
#define MC_STRING_TOKENIZER_H

#include "McWinDLLApi.h"
#include "McString.h"
#include "McHandle.h"
#include "McBitfield.h"

/** This class extracts tokens separated by blank characters from a string.
    Individual tokens may contain blanks if the token is quoted using a
    pair of "-characters or using a backslash. */
class MCLIB_API McStringTokenizer
{
  public:
    /// Initializes the tokenizer with a string.
    McStringTokenizer(const McString& string);

    /// Alternative constructor.
    McStringTokenizer(const char* string);

    virtual ~McStringTokenizer(){}

    /// Assignment operator.
    void operator=(const char* string);

    /// Do we have another token ?
    int hasMoreTokens();

    /// Returns the next token.
    McString& nextToken();

    /// Returns the next token converted to a float number.
    float nextFloat() { return (float)atof(nextToken()); }

    /// Returns the next token converted to a double number.
    double nextDouble() { return atof(nextToken()); }

    /// Returns the next token converted to an int number.
    int nextInt() { return atoi(nextToken()); }

  protected:
    McStringTokenizer(){}
    
    virtual int isSpace(char);
    void skipSpace();
    McString token;
    mclong pos;
    mclong len;
    const char* theString;
};

/** This class extracts tokens separated by any of the chars contained in string deliminiators.    
    Individual tokens may contain a deliminator c by using a backslash \c. */
class MCLIB_API McStringTokenizerGeneral : public McStringTokenizer
{
  public:
    /// Initializes the tokenizer with a string.
    McStringTokenizerGeneral(const McString& string, const char* deliminators);

    /// Alternative constructor.
    McStringTokenizerGeneral(const char* string, const char* deliminators);

  protected:
    McBitfield isDeliminator;
    virtual int isSpace(char);
};


#endif

/// @}
