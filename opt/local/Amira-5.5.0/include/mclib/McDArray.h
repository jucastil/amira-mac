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
#ifndef MCDARRAY_H
#define MCDARRAY_H

#ifdef WIN32
    //4251: class 'McDArray<T>' needs to have dll-interface to be used by clients of class ...
    #pragma warning (disable: 4251)
#endif

#include "McPrimType.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#ifdef HX_HAS_STDIOSTREAM
    #include <new>
#else
    #include <new.h>
#endif

// If this line is removed, clib memory routines are used.
#include "McMalloc.h"

#ifndef MC_MEMFACTOR
    #define MC_MEMFACTOR 1.5
#endif

#ifdef MC_MALLOC_H
    #define mcdarray_malloc(a) ::mcmalloc(a)
    #define mcdarray_realloc(a,b) ::mcrealloc(a,b)
    #define mcdarray_free(a) ::mcfree(a)
#else
    #define mcdarray_malloc(a) ::malloc(a)
    #define mcdarray_realloc(a,b) ::realloc(a,b)
    #define mcdarray_free(a) ::free(a)
#endif

/** This class provides a dynamic array of movable C++ objects. C++
    constructors and destructors are called correctly, but when
    reallocating memory the objects may be moved using @c memmove().
    Therefore you must not store the address of an individual element
    elsewhere. This class requires the template parameter class to have a
    public default constructor.

    The elements of an instance of @c McDArray can be accessed just like
    ordinary C++ array elements by means of the index @c operator[]. Safety
    is provided by

        @li automatic memory management in constructor and destructor
            preventing memory leaks
        @li checking of array bounds when accessing elements with the
            indexing @c operator[] (only when compiled without @c -DNDEBUG).

    In order to support 64-bit architectures the type mclong is used for
    all index variables. mclong (defined in McPrimType.h) is equivalent to
    ssize_t which is either 32-bit or 64-bit, depending on which architecture
    is being used.

    @c McDArrays may easily be extended by inserting or appending elements
    to the @c McDArray or shrunken by removing elements. The method
    <tt>resize(mclong n)</tt> resets the size of the array to <tt>n</tt>, thereby
    possibly appending elements or removing ones. Note that for built-in types
    the default constructor is not called on new elements for efficiency.

    @c McDArrays may be used as arguments for standard C functions
    requiring pointers through a cast operator.

    Internally, a @c McDArray object allocates a block of memory that fits
    up to @c max() elements, only @c size() of them are used. This makes
    extension and shrinking methods perform better.

    @see McSmallArray

    For template functions for searching and comparisons see
    #index(), #rindex() and #mcStandardCompare().
*/

template<class T> class McDArray
{
  public:
    typedef T* iterator;
    typedef const T* const_iterator;

    /// Default constructor, allocates no memory at all.
    McDArray() : thesize(0), themax(0), data(0) { }

    /// Copy constructor.
    McDArray(const McDArray& old) : thesize(0), themax(0), data(0) {
        appendArray(old);
        assert(isConsistent());
    }

    /** This constructor allocates an array containing @c size default
        elements. The internal array is allocated to provide space for
        @c max elements. */
    explicit McDArray(mclong size, mclong max=0) : thesize(0), themax(0), data(0) {
        remax(max,size);
        assert(isConsistent());
    }

    /// Destructor.
    ~McDArray() {
        clear(); // Calls destructors
        if (data) mcdarray_free(data);
    }

    /** Append element @c t to @c McDArray.
        @return Index of appended element.*/
    mclong append(const T& t) {
        insert(thesize, 1, &t);
        return (thesize-1);
    }

    /// STL compatibility function, same as append(const T& t).
    void push_back(const T&t) {
         append(t);
    }

    /** Append @c n elements in @c t to @c McDArray.
        @return Index of first appended element.*/
    mclong append(mclong n, const T t[]) {
        insert(thesize, n, (const T*)t);
        return (thesize-n);
    }

    /** Append all elements in @c t to @c McDArray.
        @return Index of first appended element.*/
    mclong appendArray(const McDArray<T>& t) {
        insertArray(thesize, t);
        return (thesize-t.size());
    }

    /** Append @c n default elements.
        @return Index of first appended element.*/
    mclong appendSpace(mclong n) {
        resize(thesize+n);
        return (thesize-n);
    }

    /// Insert @c n default elements at position specified by @c addBefore.
    void insertSpace(mclong addBefore, mclong n=1) {
        insertMemory(addBefore,n);
        for (mclong j=addBefore; j<addBefore+n; ++j)
            new(&data[j]) T;
    }

    /// Insert @c n elements from @c t at position specified by @c addBefore.
    void insert(mclong addBefore, mclong n, const T t[]) {
        if (n > 0) {
            // Insertion of reference to array entry leads to error if realloc is necessary
            assert(themax-thesize >= n || t < data || t >= data+thesize);
            insertMemory(addBefore, n);
            for (mclong i=0; i<n; ++i)
                new(&data[addBefore+i]) T(t[i]);
        }
    }

    /// Insert all elements of @c t at position specified by @c addBefore.
    void insertArray(mclong addBefore, const McDArray<T>& t) {
        mclong n = t.size();
        if (n > 0) {
            insertMemory(addBefore, n) ;
            // reversed loop allows insertion of array into itself
            for (mclong i=n-1; i>=0; --i)
                new(&data[addBefore+i]) T(t.data[i]);
        }
    }

    /// Insert @c t at position specified by @c addBefore.
    void insert(mclong addBefore, const T& t) {
        // Insertion of a reference (which is in fact a pointer) to the array
        // itself invalidates the pointer if realloc is necessary which moves
        // the array in memory. NOTE: Making a copy of "t" here before calling
        // insertMemory() does not seem to solve the issue, probably due to
        // compiler optimizations.
        assert(themax-thesize >= 1 || &t < data || &t >= data+thesize);
        insertMemory(addBefore, 1);
        new(&data[addBefore]) T(t);
    }

    /// Initialize all elements of the array with @c t (assignment).
    void fill(const T& t) {
        T *end = data+size();
        for (T* ptr=data; ptr<end; ++ptr)
            *ptr = t;
    }

    /// Index operator.
    T&  operator[](mclong n) {
        assert(n>=0 && n<thesize);
        return data[n];
    }

#ifndef _WIN64
    /// Index operator.
    T&  operator[](mcint64 n) {
        assert(n>=0 && n<thesize);
        return data[n];
    }
#endif

    /// Const version of index operator.
    const T& operator[](mclong n) const {
        assert(n>=0 && n<thesize);
        return data[n];
    }

    /// Index operator.
    T&  operator[](mculong n) {
        assert(n< mculong(thesize));
        return data[n];
    }

    /// Const version of index operator.
    const T& operator[](mculong n) const {
        assert(n< mculong(thesize));
        return data[n];
    }

    /** Index operator taking an int instead of a mclong. This
        operator is provided for convenience, because in Visual Studio the mclong
        index operator is not automatically used for int type index variables
        (error multiple overloads have similar conversions). */
    T&  operator[](int n) {
        assert(n>=0 && n<thesize);
        return data[n];
    }

    /** Const index operator taking an int instead of a mclong.
        Some remarks apply as for the non-const int-type index operator. */
    const T& operator[](int n) const {
        assert(n>=0 && n<thesize);
        return data[n];
    }

    /// Index operator
    T & operator[]( unsigned int n )
    {
        assert(n<(unsigned int)thesize);
        return data[n];
    }

    /// Const index operator
    const T& operator[]( unsigned int n ) const
    {
        assert(n<(unsigned int)thesize);
        return data[n];
    }

    /// Returns reference to first element of array.
    T& first() {
        assert(thesize>0);
        return data[0];
    }

    /// Returns const reference to first element of array.
    const T& first() const {
        assert(thesize>0);
        return data[0];
    }

    /// Returns reference to first element (for STL compatibility).
    T& front() { return first(); }

    /// Returns const reference to first element (for STL compatibility).
    const T& front() const { return first(); }

    /// Returns reference to last element of array.
    T& last() {
        assert(thesize>0);
        return data[thesize-1];
    }

    /// Returns const reference to last element of array.
    const T& last() const {
        assert(thesize>0);
        return data[thesize-1];
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

    /// Removes @c n elements starting at @c firstIndexToDelete.
    void remove(mclong firstIndexToDelete=0, mclong n=1) {
        if (n<=0)
            return;
        assert(firstIndexToDelete<thesize && firstIndexToDelete+n<=thesize);

        for (mclong i=firstIndexToDelete; i<firstIndexToDelete+n; ++i)
            data[i].~T();

        mclong rest = thesize-(firstIndexToDelete+n);
        if (rest>0) memmove(&(data[firstIndexToDelete]),
            &(data[firstIndexToDelete+n]), rest*sizeof(T));

        thesize -= n;
    }

    /// Removes the @c n last elements.
    void removeLast(mclong n=1) {
        assert(n<=size() && n>=0);
        for (mclong i=thesize-n; i<thesize; ++i)
            data[i].~T();
        thesize -= n;
    }

    /// Same as append(), allows array to be used as a stack.
    mclong push(const T& t) { return append(t); }

    /** Removes last element of the array. Unless the array is empty the
        last element is copied into @c t and 1 is returned. Otherwise, 0 is
        returned. */
    mclong pop(T& t) {
        if (thesize < 1)
            return 0;
        t = last();
        thesize--;
        data[thesize].~T();
        return 1;
    }

    /// Removes the last element (for STL compatibility).
    void pop_back() {
         if (thesize < 1 )
             return;
         thesize--;
         data[thesize].~T();
    }

    /// Removes all elements.
    void clear() {
        for (mclong i=0; i<thesize; ++i)
            ((T*)&data[i])->~T();
        thesize=0;
    }

    /// Returns number of elements in array.
    mclong size() const { return thesize; }

    /// Sets size to @c newsize and returns new number of elements.
    mclong resize(mclong newsize) {
        if (newsize<0)
            newsize=0;

        for (mclong i=newsize ; i<thesize ; ++i)
            ((T*)&data[i])->~T();

        if (newsize>themax) {
            mclong nmax = (mclong)(MC_MEMFACTOR*thesize);
            if (nmax<newsize) nmax=newsize;
            remax(nmax, newsize);
        }

        // Only call the default constructor on non-built-in types for
        // efficiency, otherwise "T()" would need to be passed to "new" (see
        // Stroustrup §6.2.8 and §10.4.11).
        for (mclong j = thesize; j<newsize; ++j)
            new(&data[j]) T;

        thesize=newsize;
        return thesize;
    }

    /** Returns the number of elements which fit into the internal buffer
        of the array. This number may be somewhat larger than the actual
        number of elements in the array as returned by @c size(). */
    mclong getMax() const { return themax; }

    /** Reset size of internal buffer. The value of @c max() is reset
        to @c newMax thereby setting @c size() to @c newSize. However, if
        @c newSize has a value @c < 0 (as the default argument does)
        @c size() remains unchanged and @c max() is set to <tt>MAX(size(),
        newMax)</tt>. Hence, calling @c remax() without the default
        arguments, will reduce the memory consumption to a minimum. In
        no instance @c max() will be set to a value less than 0 (even
        if specified).
        @return The number that @c max() is reduced.
    */
    mclong remax(mclong newMax=-1, mclong newSize=-1) {
        mclong oldsize = thesize;
        mclong oldmax = themax;
        mclong i;

        if (newMax < 0) newMax = thesize;
        if (newSize < 0) newSize = thesize;
        if (newMax < newSize) newMax = newSize;

        for (i=newSize; i<oldsize; ++i)
            ((T*)&data[i])->~T();

        if (oldmax!=newMax) {
            if (newMax) {
                if (data)
                    data = (T*) mcdarray_realloc(data, mcuint64(newMax)*sizeof(T));
                else data = (T*) mcdarray_malloc(mcuint64(newMax)*sizeof(T));
            } else {
                if (data) mcdarray_free(data);
                data = 0;
            }
            themax = newMax;
        }

        thesize = newSize;
        for (i=oldsize; i<newSize; ++i)
            new(&data[i]) T;

        return oldmax-themax;
    }

    /// Consistency check, returns 1 is array is ok, 0 otherwise.
    int isConsistent() const {
        assert(!(themax<0 || themax<thesize));
        return 1;
    }

    /** Assignment operator. Assigning an lvalue @c McDArray to a
        rvalue @c McDArray involves resizing the lvalue to the rvalues
        @c size() and assigning all elements individually. */
    McDArray& operator=(const McDArray& rhs) {
        resize(rhs.size());
        for (mclong i=0; i<thesize; ++i)
            data[i] = rhs.data[i];
        return *this;
    }

    /** Insert element @c t into a sorted array. The sorting scheme is
        defined by the function @c compare which has to be specified as
        an argument. For many standard data types the global template
        function mcStandardCompare can be used. The compare
        function should return either -1, 0, 1, depending on whether
        the first argument is smaller, equal, or bigger than the second
        one.
        @return The index of the inserted element.
        @see mcStandardCompare */
    mclong insertSorted(const T& t,int (*compare)(const T& t1, const T& t2),
        mclong start=-1, mclong end=-1) {

        if (end==-1)
            end=size();

        if (end-start<=1) {
            insert(start+1,t);
            return(start+1);
        }
        mclong middle=(start+end)/2;
        int res=(*compare)(t,(*this)[middle]);
        if (res<0) /* t < middle */
            return(insertSorted(t,compare,start,middle));

        return(insertSorted(t,compare,middle,end));
    }

    /** Find element @c t in a sorted array. The sorting scheme is
        defined by the function @c compare which has to be specified as
        an argument. For details refer to insertSorted.
        @return The index of the element or -1 if not found.
        @see mcStandardCompare */
    mclong findSorted(const T& t,int (*compare)(const T& t1,const T& t2),
        mclong start=-1, mclong end=-1) const {

        if (end==-1)
            end=size();

        if (end-start<=1) {
            if (start>-1 && compare(t,(*this)[start])==0)
                return(start);
            if (end<size() && compare(t,(*this)[end])==0)
                return(end);
            return(-1);
        }

        mclong middle = (start+end)/2;
        int res = (*compare)(t,(*this)[middle]);
        if (res<0) /* t < middle */
            return(findSorted(t,compare,start,middle));

        return(findSorted(t,compare,middle,end));
    }

    /** Sort array using a compare function. In most cases
        mcStandardCompare can be used as compare function.
        Sorting is done using the quick sort algorithm.
        @see mcStandardCompare */
    void sort(int (*compare)(const T& t1,const T& t2)) {
#ifndef HX_OS_SUNOS
      qsort((void*)data,(size_t)size(),sizeof(T),
              (int (*)(const void *, const void *))compare);
#endif
    }

    /** Swap the elements specified by @c index1 and @c index2. No copy
        constructors are called but the elements are swapped on a per-byte
        basis. */
    void swap(mclong index1, mclong index2) {
        int nBytes = sizeof(T);
        unsigned char* dst1 = (unsigned char*) &(data[index1]);
        unsigned char* dst2 = (unsigned char*) &(data[index2]);
        for (int i=0; i<nBytes; ++i) {
            unsigned char tmp = dst1[i];
            dst1[i] = dst2[i];
            dst2[i] = tmp;
        }
    }

    /** This method exchanges the content of the array with the one in other.
        Only the data pointers are changed, i.e., the method is very fast. */
    void swapWith(McDArray<T>& other) {
        mclong tmp = thesize;
        thesize = other.thesize;
        other.thesize = tmp;

        tmp = themax;
        themax = other.themax;
        other.themax = tmp;

        T* tmpPtr = data;
        data = other.data;
        other.data = tmpPtr;
    }

    /// Reverse the order of all elements of the array.
    void reverse() {
        mclong n2 = size()/2;
        mclong s = size();
        for (mclong i=0; i<n2; ++i)
            swap(i,s-1-i);
    }

    /// Rotate all elements to the left (offset<0) or to the right (offset>0).
    void rotate(mclong offset) {
        mclong n = offset>0 ? offset : -offset;
        mclong s = size();
        T* tmp = (T*) mcdarray_malloc(n*sizeof(T));
        if (offset<0) {
            memcpy(tmp,data,n*sizeof(T));
            memmove(data,data+n,(s-n)*sizeof(T));
            memcpy(data+(s-n),tmp,n*sizeof(T));
        } else {
            memcpy(tmp,data+(s-n),n*sizeof(T));
            memmove(data+n,data,(s-n)*sizeof(T));
            memcpy(data,tmp,n*sizeof(T));
        }
        mcdarray_free(tmp);
    }

    /// Release the own of the data to the user
    void release() {
        thesize = 0;
        themax = 0;
        data = NULL;
    }

    T* begin() {
        return data;
    }

    const T* begin() const {
        return data;
    }

    T* end() {
        return data + thesize;
    }

    const T* end() const {
        return data + thesize;
    }

  protected:
    /// Inserts @c n uninitialized elements at given position.
    void insertMemory(mclong addBefore, mclong n=1) {
        assert(addBefore<=thesize);
        mclong newsize = thesize + n;

        if (newsize>themax) {
            themax = (mclong)(MC_MEMFACTOR*thesize);
            if (themax<newsize) themax=newsize;

            if (data) data = (T*) mcdarray_realloc(data, mcuint64(themax)*sizeof(T));
            else data = (T*) mcdarray_malloc(mcuint64(themax)*sizeof(T));
        }

        if (thesize-addBefore) {
            T* src = data+addBefore;
            T* dst = src+n;
            memmove(dst, src, (thesize-addBefore)*sizeof(T));
        }

        thesize=newsize;
    }

    /// Number of active elements in array.
    mclong thesize;
    /// Number of elements fitting in internal buffer.
    mclong themax;
    /// Pointer to internal buffer.
    T *data;
};

/** \file
    \brief Contains global template functions to be used in
           conjunction with McDArray.

   This file contains some global template function which are often
   used in conjunction with a McDArray. The reason that these method are
   not members of the McDArray itself is that not all types which one may
   want to insert in an array necessarily have a equality operator.
*/
//@}

/** Looks for first occurrence of given element and returns its
    index or -1 if not found. Search starts at index startIdx, which is zero by
    default. */
template<class T>
mclong index(const McDArray<T>& array, const T& elem, mclong startIdx=0)
{
    for (mclong i=startIdx; i<array.size(); ++i)
        if (array[i] == elem) return i;
    return -1;
}

/** Looks for last occurrence of given element and returns its
    index or -1 if not found. Search starts at index startIdx,
    which is array.size()-1 by default. */
template<class T>
mclong rindex(const McDArray<T>& array, const T& elem, mclong startIdx=-1)
{
    mclong i;
    if (startIdx<0)
        startIdx = array.size()-1;
    for (i=startIdx; i>=0; --i)
        if (array[i] == elem) return i;
    return -1;
}

/** This function compares @c t1 and @c t2 by applying the operator<().
    For example, it can be used as a comparator function when calling
    McDArray::sort, McDArray::insertSorted, or
    McDArray::findSorted. */
template<class T>
int mcStandardCompare(const T&t1,const T&t2)
{
    if (t1<t2) return -1;
    if (t2<t1) return 1;
    return 0;
}
//@{

#undef mcdarray_malloc
#undef mcdarray_realloc
#undef mcdarray_free

#endif

/// @}
