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

/// @addtogroup zmf zmf
/// @{
#ifndef _TAG_ZMFExceptions_h
#define _TAG_ZMFExceptions_h

#include <mclib/McString.h>
#include "ZMFWinDLLApi.h"

class SomeType;

class ZMF_API ZMFDataException 
{
    ///
    McDArray<int> path;
    
    ///
    void printPath(ostream & os, SomeType * t);
    
    ///
    char *getPath(SomeType * t);
    
protected:
    /// 
    McString message;
    char pathBuf[256];

public:
    ///
    ZMFDataException(const char * msg) : message(msg) { }

    ///
    void addToPath(int index) { path.append(index); }

    ///
    void print(ostream & os, SomeType * t=0)
    {
        os << "ZIBMolFile data exeption >" << message
           << "<";
        if(t){
            os <<" while reading ";
            printPath(os, t);
            os << "\n";
        }  
    }

    ///
//     char *getMessage(SomeType * t=0)
//     {
//         sprintf(messageBuf, "ZIBMolFile data exeption > %s <", 
//                 (const char*)(message));
//         if(t){
//             sprintf(messageBuf+strlen(messageBuf), 
//                     " while reading %s", getPath(t));
//         }
//         return messageBuf; 
//     }
    
};

class StreamBad : public ZMFDataException 
{
public:
    StreamBad() : ZMFDataException("Stream bad") {}
};

class BadNumExtents : public ZMFDataException 
{
public:
    BadNumExtents() : ZMFDataException("Matrix extents have bad value") {}
};

class CantOpenFile : public ZMFDataException 
{
public:
    CantOpenFile(const char * name) 
        : ZMFDataException("Can't open file : ") 
    { 
        message.stream() << name; 
    }
};

class BadEntryIndex : public ZMFDataException 
{
public:
    BadEntryIndex(int inx) 
        : ZMFDataException("Bad entry index ") 
    {
        message.stream() << inx;
    }
};

class BaseTypeExpected : public ZMFDataException 
{
public:
    BaseTypeExpected(const char * exp, const char *found)
        : ZMFDataException("Expected base type ")
    {
        message.stream() << exp << ", but found base type " << found;
    }
};

class TypeExpected : public ZMFDataException 
{
public:
    TypeExpected(const char * exp, const char *found)
        : ZMFDataException("Expected type ")
    {
        message.stream() << exp << ", but found type " << found;
    }
};

class ForkTypeExpected : public ZMFDataException 
{
public:
    ForkTypeExpected(const char *found)
        : ZMFDataException("Expected type array or struct, but found type ")
    {
        message.stream() << found;
    }
};

class CantFindExternal : public ZMFDataException 
{
public:
    CantFindExternal(const char *filename)
        : ZMFDataException("Couldn't find external file \'")
    {
        message.stream() << filename << "\' ";
    }
};

class OptionalNotAvailable : public ZMFDataException 
{
public:
    OptionalNotAvailable()
        : ZMFDataException("Optional field not available from data file !")
    { }
};


class UnknownStructEntry : public ZMFDataException 
{
public:
    UnknownStructEntry(const char *name)
        : ZMFDataException("Unknown struct entry \'")
    {
        message.stream() << name << "\' ";
    }
};

class TypeUnwritten : public ZMFDataException 
{
public:
    TypeUnwritten()
        : ZMFDataException("TYPE section has not been written to file")
    {}
};

class EOFReached : public ZMFDataException 
{
public:
    EOFReached()
        : ZMFDataException("End of File reached")
    {}
};

class NumRankExpected : public ZMFDataException 
{
public:
    NumRankExpected(int exp, int found) 
        : ZMFDataException("Expected rank ")
    {
        message.stream() << exp << ", but found rank" << found;
    }
};

class UnexpectedMatrixExtents : public ZMFDataException 
{
public:
    UnexpectedMatrixExtents()
        : ZMFDataException("Matrix extents unexpected")
    {}
};


class FixedArraySize : public ZMFDataException 
{
public:
    FixedArraySize()
        : ZMFDataException("Array size is fixed")
    {}
};

class StringSizeMismatch : public ZMFDataException 
{
public:
    StringSizeMismatch()
        : ZMFDataException("String length differs from type declaration")
    {}
};
#endif


/// @}
