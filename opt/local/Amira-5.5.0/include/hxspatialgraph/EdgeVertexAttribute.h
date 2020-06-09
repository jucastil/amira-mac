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

/// @addtogroup hxspatialgraph hxspatialgraph
/// @{
#ifndef EDGE_VERTEX_ATTRIBUTE_H
#define EDGE_VERTEX_ATTRIBUTE_H

#include "hxspatialgraphAPI.h"

#include <mclib/McPrimType.h>
#include <mclib/McTypedPointer.h>
#include <mclib/McHandable.h>
#include <mclib/McTypedElement.h>
#include <mclib/McDArray.h>
#include <mclib/McTypedData2D.h>

#include "GraphAttribute.h"

class HxSpatialGraph;

class HXSPATIALGRAPH_API EdgeVertexAttribute : public GraphAttribute
{

    EdgeVertexAttribute();

public:

    /// Returns the number of elements
    int size() const { return mSize; }

    /// This constructor allocates a contiguous array of given size and type.
    EdgeVertexAttribute(HxSpatialGraph * sg, const char* name, McPrimType type, int nDataVar=1);

    /// Destructor.
    ~EdgeVertexAttribute();

    /// Set number of elements to numElements (allocate memory if required)
    void init(int numElements);

    // float data access
    float *       floatDataAtIdx(const int idx);
    const float * floatDataAtIdx(const int idx) const;

    float getFloatDataAtIdx(const int idx) const;
    void  setFloatDataAtIdx(const int idx, float value);

    // int data access
    int *       intDataAtIdx(const int idx);
    const int * intDataAtIdx(const int idx) const;

    int   getIntDataAtIdx(const int idx) const;
    void  setIntDataAtIdx(const int idx, int value);

    McTypedElement getValue(const int idx) const;
    void setValue(const int idx, const McTypedElement value);

    /** set the values at the indices \a idx (not inserting!) */
    void setMultipleValues(const McDArray<int>& idx, const McDArray<McTypedElement>& values);

    void setMultipleValues(const McDArray<int>& idx, const McTypedData2D& values);

    /** insert the values in \a values at the corresponding indices \a idx, i.e.
     *  after this operation, the values in \a values can be found at indices \a newValueIndices
     *  It is assumed that \a newValueIndices is sorted from low to high! */
    void insertMultipleValues(const McDArray<int>& newValueIndices, const McTypedData2D& values);

    /** Return the values at indices \a idx, packed in an McTypedData2D array of size (idx.size() x 1) */
    McTypedData2D getValues(const McDArray<int>& idx) const;

    /// Remove the values at indices \a edgeNums
    void removeMultipleValues(const McDArray<int>& idx);

    /// remove num elements starting at position idx
    void remove(const int startidx, const int num = 1);

    /** Reserve space for new items in array (to avoid multiple reallocs) without changing the number of items
     *  The default argument resizes the memory to the actual array size
     *  Newly allocated space is initialized with zero.
     */
    void remax(int newMax = -1);

    /** Set \a numItems items starting with index \a startIndex to zero.
     *  If numItems==-1, all items starting from \a startIndex are set to zero.
     */
    void clearMemory(const int startIndex=0, const int numItems=-1);

private:

    void* dataPtr() {return mData; }
    const void* dataPtr() const {return mData; }

    /// inserts space for num elements before position idx
    void insertBefore(const int addBefore, const int num = 1);

    /// convenience
    void removeLast(const int num = 1);

    /// convenience
    void append(const int num = 1);

    /// copy one single element
    void copy(const int dstIdx, const int srcIdx);


    /// members
    char       *mData;
    int         mSize; // True number of items in array
    int         mMax;  // number of items for which space is allocated

    /// Returns the number of elements
    friend class HxSpatialGraph;
};

#endif

/// @}
