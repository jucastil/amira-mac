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

/// @addtogroup hxmoledit hxmoledit
/// @{
#ifndef ATTRIBUTEIO_H
#define ATTRIBUTEIO_H

#include <mclib/McString.h>
#include <mclib/McBitfield.h>

class MtGroupAttribute;
class MtGroupingLevel;

/** The following operations are used as commands
    of a meta language
    into which the format string of the Import Attribute
    Tool is tranlated **/

// --------------------------------------------------
// readOperation

class readOperation {
public:
    //
    virtual ~readOperation() {};

    // if debugFile is != NULL all operations will write DEBUG info 
    // while being applied into this stream
    static FILE* debugFile;
    // error text contains info if operation has failed
    McString errorText;
    enum operationType { MATCH, SKIP, JUMP, ATTR, CONTEXT};
    // return operation type
    int type() const;
    // check if of this typd
    bool isOfType(enum operationType) const;
    // constructor
    readOperation(enum operationType);
    // prints operation info and status to a file stream 
    // if stream is omited debugFile will be used
    virtual void print(FILE* f=0) const = 0;
    // applies operation to stream
    virtual bool apply(FILE* f) = 0;
protected:
    // prints error text to file stream
    virtual void printError(FILE*) const;
private:
    int operation;
};

// --------------------------------------------------
// matchOperation

class matchOperation : public readOperation {
public:
    McString text;
    matchOperation(const McString& text);
    virtual void print(FILE* f=NULL) const;
    bool apply(FILE* stream);
    bool reverseApply(FILE* stream);
};



// --------------------------------------------------
// skipOperation

class skipOperation : public readOperation {
public:
    McString chars;
    McBitfield charsBf;
    const readOperation* nextOp;
    skipOperation(const McString& chars);
    virtual void print(FILE* f=NULL) const;
    void setNextOperation(const readOperation* nextOp);
    virtual bool apply(FILE* f);
    /* maps the chars and ranges given in a skipChar specifier
       to a bitfield of the ascii values of the chars to be skipped */
    void skipChars2Bitfield(
        const McString& skipChars,
        McBitfield& skipC) const;
};

// --------------------------------------------------
// jumpOperation

class jumpOperation : public readOperation {
public:
    int width;
    jumpOperation(int width);
    virtual void print(FILE* f=NULL) const;
    virtual bool apply(FILE* f);
};

// --------------------------------------------------
// attrOperation

class attrOperation : public readOperation {
public:
    enum attributeType { STRING, FLOAT,INT};
    int attrType;
    int width;
    MtGroupAttribute* attr;
    McString levelName;
    int levelIx;
    McString attrName;
    McString val;
    attrOperation(
        MtGroupAttribute* attr,
        const McString& levelName,
        int levelIx,
        const McString& attrName,
        const McString& attrType,
        int width);
    virtual void print(FILE* f=NULL) const;
    virtual bool apply(FILE* f);
    /* will read an attribute value from a stream and write it to attrVal
       if width is >-1 then exactly width chars will be read
       if width is -1 it will read chars until some nonAlpha or nonNumeric chars are found
       whitespaces at the start will be skipped */
    bool readAttribute(
        McString& attrVal,
        FILE* stream);
    /* map the attribute type given as a string to the enum type
       used in this class */
    static int typeString2Type(const McString& type);

};

// --------------------------------------------------
// startContextOperation

class startContextOperation : public readOperation {
public:
    int levelIx;
    McString levelName;

    startContextOperation(const McString& levName,int levelIx);
    virtual void print(FILE* f=NULL) const;
    virtual bool apply(FILE* f);
};
#endif

/// @}
