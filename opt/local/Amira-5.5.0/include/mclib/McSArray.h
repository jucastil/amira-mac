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
#ifndef MCSARRAY_H
#define MCSARRAY_H

#include "assert.h"

#include "McWinDLLApi.h"

/** An array with a fixed number of elements. This class is similar
    to McDArray, but the number of elements of the array is fixed
    and cannot be changed. Thus, methods like append or insert are
    not provided. You should access the elements of the array using
    the index operator. */

template<class T, int SIZE> class McSArray
{
  public:
    /// Default constructor.
    McSArray() { }

    /// Copy constructor.
    McSArray(const McSArray& old) {
        *this = old;
    }

    /// Destructor.
    ~McSArray() {}

    /// Initialize all elements of the array with #t# (assignment).
    void fill(const T& t) {
        for (int i=0; i<SIZE; i++)
            (*this)[i] = t;
    }

    /// Index operator.
    T&  operator[](int n) {
        assert(n>=0 && n<SIZE);
        return data[n];
    }

    /// Const version of index operator.
    const T& operator[](int n) const {
        assert(n>=0 && n<SIZE);
        return data[n];
    }

    /// Returns reference to last element of array.
    T& last() {
        assert(SIZE>0);
        return data[SIZE-1];
    }

    /// Returns const reference to last element of array.
    const T& last() const {
        assert(SIZE>0);
        return data[SIZE-1];
    }

    /// Returns reference to last element (for STL compatibility).
    T& back() { return last(); }

    /// Returns const reference to last element (for STL compatibility).
    const T& back() const { return last(); }

    /// Returns pointer to array data.
    operator T* () { return data; }

    /// Returns const pointer to array data.
    operator const T* () const  { return data; }

    /// Returns pointer to array data.
    T* dataPtr() { return data; }

    /// Returns const pointer to array data.
    const T* dataPtr() const  { return data; }

    /// Returns number of elements in array.
    int size() const { return SIZE; }

    /** Assignment operator. Assigning an lvalue #McDArray# to a
        rvalue #McDArray# involves resizing the lvalue to the rvalues
        #size()# and assigning all elements individually. */
    McSArray& operator=(const McSArray<T, SIZE>& rhs) {
        for (int i=0; i<SIZE; i++)
            data[i] = rhs.data[i];
        return *this;
    }

    /** Sort array using a compare function. In most cases
        \Ref{mcStandardCompare} can be used as compare function.
        Sorting is done using the quick sort algorithm.
        @see mcStandardCompare */
    void sort(int (*compare)(const T& t1,const T& t2)) {
        qsort(data,SIZE,sizeof(T),
              (int (*)(const void *, const void *))compare);
    }

    /** Swap the elements specified by #index1# and #index2#. No copy
        constructors are called but the elements are swapped on a per-byte
        basis. */
    void swap(int index1, int index2) {
        int nBytes = sizeof(T);
        unsigned char* dst1 = (unsigned char*) &(data[index1]);
        unsigned char* dst2 = (unsigned char*) &(data[index2]);
        for (int i=0 ; i<nBytes ; i++) {
            unsigned char tmp = dst1[i];
            dst1[i] = dst2[i];
            dst2[i] = tmp;
        }
    }

    /// Reverse the order of all elements of the array.
    void reverse() {
        int n2 = size()/2;
        int s = size();
        for (int i=0 ; i<n2 ; i++)
            swap(i,s-1-i);
    }

    /** Rotate all elements to the left (offset<0) or to the right (offset>0).
     */
    void rotate(int offset) {
        int i;
        int n = offset>0 ? offset : -offset;
        int s = size();
        T tmp[n];
        if (offset<0) {
            for (i=0; i<n; i++)
                tmp[i] = data[i];
            for (i=0; i<s-n; i++)
                data[i] = data[i+n];
            for (i=0; i<n; i++)
                data[i+s-n] = tmp[i];
        } else {
            for (i=0; i<n; i++)
                tmp[i] = data[s-n+i];
            for (i=s-n-1; i>=0; i--)
                data[n+i] = data[i];
            for (i=0; i<n; i++)
                data[i] = tmp[i];
        }
    }

  protected:
    /// The internal buffer
    T data[SIZE];
};

/** \file
    \brief Contains global template functions to be used in
           conjunction with McSArray.

   This file contains some global template functions which are often
   used in conjunction with a McSArray. The reason that these methods are
   not members of the McSArray itself is that not all types which one may
   want to insert in an array necessarily have a equality operator.
*/
//@}

/** Looks for first occurrence of given element and returns its
    index or -1 if not found. Search starts at index startIdx, which is zero by
    default. */
template<class T, int SIZE>
static int index(McSArray<T, SIZE>& array, const T& elem, int startIdx = 0)
{
    for (int i=startIdx; i<array.size(); i++)
        if (array[i] == elem) return i;
    return -1;
}

/** Looks for last occurrence of given element and returns its
    index or -1 if not found. Search starts at index startIdx,
    which is array.size()-1 by default. */
template<class T, int SIZE>
static int rindex(McSArray<T, SIZE>& array, const T& elem, int startIdx = -1)
{
    int i;
    if (startIdx<0)
        startIdx = array.size()-1;
    for ( i=startIdx; i>=0; i--)
        if (array[i] == elem) return i;
    return -1;
}

//@{

#endif

/// @}
