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
#ifndef MCDARRAY_3D_H
#define MCDARRAY_3D_H

#include <assert.h>
#include "McWinDLLApi.h"

#ifdef HX_HAS_STDIOSTREAM
    #include <new>
#else
    #include <new.h>
#endif

#include "McVec3i.h"
#include "McMalloc.h"

/** This class provides a dynamic array of C++ objects. C++
    constructors and destructors are called correctly.
    This class requires the template parameter class to have a
    public default constructor.

    The elements of an instance of @c McDArray3D can be accessed by means
    of the three-dimensional index @c operator() or by the linear index
    @c operator[]. Safety is provided by

        @li automatic memory management in constructor and destructor
            preventing memory leaks
        @li checking of array bounds when accessing elements with the
            indexing operators (only when compiled without @c -DNDEBUG).


    @c McDArray3Ds may be used as arguments for standard C functions
    requiring pointers through a cast operator.

*/

template<class T> class McDArray3D
{
  public:
    /**@name Constructors and Destructors */
    //@{
    /// Default constructor, allocates no memory at all.
    McDArray3D() : data(0) {
    dims[0] = dims[1] = dims[2] = 0;
    }

    /// Copy constructor.
    McDArray3D(const McDArray3D& old) : data(0) {
	int i;
	for (i=0; i<3; i++)
	    dims[i] = old.getDims()[i];

	data = (T*) malloc(dims[0]*dims[1]*dims[2]*sizeof(T));

	for (i=0; i<getNumElements(); i++)
	    data[i] = old[i];
    }

     /** This constructor allocates an array containing default elements. */
    McDArray3D(int sizeX, int sizeY, int sizeZ) {
	dims[0] = sizeX;
	dims[1] = sizeY;
	dims[2] = sizeZ;

	data = (T*) malloc(dims[0]*dims[1]*dims[2]*sizeof(T));

	for (int i=0; i<getNumElements(); i++)
	    new (&data[i]) T;
    }

     /// Destructor.
     ~McDArray3D() {
	 clear();
	 if (data) free(data);
     }
    //@}

    /// Initialize all elements of the array with @c t (assignment).
    void fill(const T& t) {
 	T *end = data+getNumElements();
 	for (T* ptr=data; ptr<end; ptr++)
 	    *ptr = t;
    }

     /**@name Acces Code */
    //@{

    /// Index operator.
    T& operator()(int x, int y, int z) {
	assert(x>=0 && x<dims[0] && y>=0 && y<dims[1] && z>=0 && z<dims[2]);
	return data[dims[0]*(z*dims[1] + y) + x];
    }

    /// Const version of index operator.
    const T& operator()(int x, int y, int z) const {
	assert(x>=0 && x<dims[0] && y>=0 && y<dims[1] && z>=0 && z<dims[2]);
	return data[dims[0]*(z*dims[1] + y) + x];
    }

    /// Alternative index operator for the use with McFloodFill.
    T& get(int x, int y, int z) {
	assert(x>=0 && x<dims[0] && y>=0 && y<dims[1] && z>=0 && z<dims[2]);
	return data[dims[0]*(z*dims[1] + y) + x];
    }

    /// 3D index operator.
    T&  operator[](const McVec3i& idx) {
        return operator()(idx[0],idx[1],idx[2]);
    }

    /// Const version of 3D index operator.
    const T& operator[](const McVec3i& idx) const {
        return operator()(idx[0],idx[1],idx[2]);
    }

    /// Linear index operator.
    T&  operator[](int n) {
 	assert(n>=0 && n<dims[0]*dims[1]*dims[2]);
 	return data[n];
    }

     /// Const version of linear index operator.
     const T& operator[](int n) const {
 	assert(n>=0 && n<dims[0]*dims[1]*dims[2]);
 	return data[n];
     }

    /// Returns pointer to array data.
    operator T* () { return data; }

    /// Returns const pointer to array data.
    operator const T* () const  { return data; }

    /// Returns pointer to array data.
    T* dataPtr() { return data; }

    /// Returns const pointer to array data.
    const T* dataPtr() const  { return data; }
    //@}

    /// Removes all elements.
    void clear() {
 	for (int i=0 ; i<getNumElements() ; i++)
 	    (&data[i])->~T();
	dims[0]=dims[1]=dims[2]=0;
    }

    /// Returns number of elements in array.
    int getNumElements() const { return dims[0]*dims[1]*dims[2]; }

    /// Returns dimensions of array.
    const int* getDims() const {return dims; }

    /** Assignment operator. Assigning an lvalue @c McDArray3D to a
        rvalue @c McDArray3D involves resizing the lvalue to the rvalues
        @c size() and assigning all elements individually. */
    McDArray3D& operator=(const McDArray3D& rhs) {
	resize(rhs.getDims());
	for (int i=0; i<rhs.getNumElements(); i++)
	    data[i] = rhs.data[i];
	return *this;
    }

    /// Returns dimension of array.
    int sizeX() const {return dims[0];}

    ///
    int sizeY() const {return dims[1];}

    ///
    int sizeZ() const {return dims[2];}

    /** Changes the size to the new dimensions.  The old values are kept,
	but they will appear at different indices after the resize. @c McDArray3D
	does not reserve extra memory in advance, as @c McDArray does.
	The routine returns the new total number of array elements. */
    int resize(int sizeX, int sizeY, int sizeZ) {
	assert(sizeX>=0 && sizeY>=0 && sizeZ>=0);

	int oldsize = getNumElements();
	int newsize = sizeX*sizeY*sizeZ;
	int i;

	// if array is made smaller, destruct the extra elements
	for (i=newsize ; i<oldsize ; i++)
	    (&data[i])->~T();

	if (dims[0]!=sizeX || dims[1]!=sizeY || dims[2]!=sizeZ) {
	    dims[0] = sizeX;
	    dims[1] = sizeY;
	    dims[2] = sizeZ;

	    if (newsize){
		if (data)
		    data = (T*) realloc(data, newsize*sizeof(T));
		else
		    data = (T*) malloc(newsize*sizeof(T));
	    } else {
		if (data)
		    free(data);
		data = 0;
	    }
	}

	for (i=oldsize; i<newsize; i++)
	    new (&data[i]) T;

	return(newsize);
    }

protected:

	// wrapper for resize(int, int, int)
    int resize(const int *newSize) {
		assert(newSize != 0);
		return(resize(newSize[0],newSize[1],newSize[2]));
	}

    int dims[3];

     T *data;
};

#endif

/// @}
