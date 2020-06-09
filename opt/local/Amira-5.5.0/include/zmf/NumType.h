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
#ifndef _TAG_NumType_h
#define _TAG_NumType_h

#include "ZMFWinDLLApi.h"
#include "SomeType.h"
#include <mclib/McDArray.h>

class StreamData;

/** Multi-dimensional numerical data. */
class ZMF_API NumType : public SomeType {
public:

    /// If the dimension is not specified by the data type
    enum { dimFree = -1 };

    /** The supported element types (i=signed int, u=unsigned int,
        f=float). */
    enum basetypes { i1, u1, i2, u2, i4, u4, i8, u8, f4, f8, f16 };

    /// Constructor
    NumType(enum basetypes t = i4,int rank = 0) : basetype(t)
    { setRank(rank); }
    /// Constructor with extents array
    NumType(enum basetypes t,int nDims, int * extents) : basetype(t)
    { setExtents(nDims, extents); }
    
    ///
    virtual const char *typeName() { return "num"; }

    ///
    const char * baseTypeName();

    /// Sets the element type
    bool setBaseType(bool isint,bool isunsigned,int nbytes);
    /// Sets the rank
    void setRank(int rank);

    /// Return element type
    virtual enum basetypes getBaseType() { return basetype; }
    /// Return bytes in an element
    virtual int getBaseSize();
    /// Returns rank
    virtual int getRank() { return theExtents.size(); }
    /// True if element are of integer type
    virtual bool isInteger();

    /// Get extents
    virtual const McDArray<int> & getExtents() { return theExtents; }
    /// Get extent of dimension @c dim, counted from 0.
    virtual int getExtents(int dim) { return theExtents[dim]; }

    /// Set extents, array from 0..rank-1
    virtual void setExtents(int nDims, const int * e) { 
        theExtents.clear();
        theExtents.append(nDims, e);
    }
    /// Set a single dimension's extent
    virtual void setExtents(int idim,int iextent) {
        theExtents[idim] = iextent;
    }

    ///
    virtual void print_(ostream &os,int indent = 0);

    ///
    StreamData * getStreamData(InStreamDataFile * F, long off);

protected:
    enum basetypes basetype;
    McDArray<int> theExtents;
};    

// ///
// class NumTypeWriter : public SomeTypeWriter
// {
// public:
//     ///
//     NumTypeWriter(NumType * t) : theType(t) {}

// protected :
//     ///
//     void writeMatrixInt(OutStreamDataFile * F, int * ptr, 
//                      int nDims, const int * e);

//     ///
//     void writeMatrixReal(OutStreamDataFile * F, float * ptr, 
//                       int nDims, const int * e);

//     ///
//     void writeInteger(OutStreamDataFile * F, int value);

//     ///
//     void writeReal(OutStreamDataFile * F, double value);

// private :
//     McHandle<NumType> theType; 
// };

#endif

/// @}
