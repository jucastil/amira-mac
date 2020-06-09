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
#ifndef MC_RAWDATA3D_H
#define MC_RAWDATA3D_H

#include "McWinDLLApi.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "McPrimType.h"

class McRawData2D;

/** This class manages a 3D array of untyped items. The size of an
    individual element has to be defined explicitly by the user. The class
    provides constructors which allow one to access already existing
    user-controlled memory. The elements of the 3D array are always
    supposed to be arranged in contiguous order, i.e., without any
    padding. The class McRawData2D can be used to easily access
    a 2D slice of the 3D array oriented either in xy-, xz-, or
    yx-direction
    @see McRawData2D, McData2D, McData3D, McTypedData2D, McTypedData3D
*/

class MCLIB_API McRawData3D
{
  public:
    /// Specifies the orientation of an orthogonal slice.
    enum Orientation {
        /// yz-direction
        YZ = 0,
        /// xz-direction
        XZ = 1,
        /// xy-direction (default)
        XY = 2
    };

    /// Default constructor, allocates no memory.
    McRawData3D();

    /// This constructor allocates an array of @c nx*ny*nz elements of given size.
    McRawData3D(int nx, int ny, int nz, int elemSize);

    /** This constructor initializes the array with an existing block of
        memory. The memory is not freed in the destructor. In order to
        really pass control over an existing memory segment to the class
        you may use the commit method. */
    McRawData3D(int nx, int ny, int nz, int elemSize, void* data);

    /// Destructor frees any memory allocated by the class itself.
    ~McRawData3D();

    /// Reallocates the 3D array to match the new dimensions.
    void init(int nx, int ny, int nz, int elemSize);

    /** Initializes the array with existing memory. The memory is not freed
        in the destructor. In order to really pass control over an existing
        memory segment to the class you may use the commit method. */
    void init(int nx, int ny, int nz, int elemSize, void* data);

    /// Reallocates the 3D array without changing the element size.
    void resize(int nx, int ny, int nz) { init(nx, ny, nz, elemSize); }

    /// Initializes the data volume to zero.
    void clear() const { memset(data,0,elemSize*dims[0]*dims[1]*dims[2]); }

    /// Returns address of the data item specified by @c i,j,k.
    void* address(int i, int j, int k) const {
	assert(i>=0 && j>=0 && k>=0 && i<dims[0] && j<dims[1] && k<dims[2]);
	return (&data[elemSize*((k*(mculong)dims[1]+j)*(mculong)dims[0]+i)]);
    }

    /// Returns address offset of item @c i,j,k, i.e., @c (k*ny+j)*nx+i.
    mculong getOffset(int i, int j, int k) const {
	assert(i>=0 && j>=0 && k>=0 && i<dims[0] && j<dims[1] && k<dims[2]);
	return (k*(mculong)dims[1]+j)*(mculong)dims[0]+i;
    }

    /// Returns address offset of item @c i,j,k in non-default orientation.
    mculong getOffset(int i, int j, int k, int orientation) const ;

    /// Returns the dimensions of the 3D array.
    const int* getDims() const { return dims; }

    /** Returns the dimensions of the 3D array. If a non-default
        orientation is specified the dimensions are permuted as necessary. */
    void getDims(int dims[3], int orientation=XY) const;

    /** This method differs from the one above only in its signature.
	@param orientation either XY, XZ, or YZ
	@param nx the x dimension of a slice in specified @c orientation.
	@param ny the y dimension of a slice in specified @c orientation.
	@param numSlices the number of slices in specified @c orientation.
     */
    void getDims(int orientation, int& nx, int& ny, int& numSlices) const;

    /// Returns x dimension of array.
    int sizeX() const { return dims[0]; }

    /// Returns y dimension of array.
    int sizeY() const { return dims[1]; }

    /// Returns z dimension of array.
    int sizeZ() const { return dims[2]; }

    /// Returns the size of an single array element in bytes.
    int getElemSize() const { return elemSize; }

    /// Returns the total number of elements.
    mculong getNumElems() const { return (mculong)dims[0]*(mculong)dims[1]*(mculong)dims[2]; }

    /** Get information to access a slice in the 3D array. The arguments
        @c orientation and @c sliceNumber define the slice to be accessed. The
        variables @c first, @c bytesPerPixel, and @c bytesPerLine are set on
        return. These variables can be used for example to initialize an
        instance of type McRawData2D. */
    void accessSlice(int orientation, int sliceNumber, void*& first,
                  int& bytesPerPixel, int& bytesPerLine) const;

    /** Get information to access a slice in the 3D array. The arguments
        @c orientation and @c sliceNumber define the slice to be accessed. On
        return the parameter @c result is initialized properly. Unless
        @c copyData is set no dedicated memory is allocated for the 2D
        slice and no data is copied. */
    void getSlice(int orientation, int sliceNumber,
                  McRawData2D& result, int copyData=0) const;

    /** Copy a 2D slice into the 3D array. The dimensions and the element
        size of the 2D slice must fit the dimensions and the element size
        of the target slice. */
    void putSlice(int orientation, int sliceNumber, const McRawData2D& src);

    /** This method passes control over an existing block of memory to
        the class. The given memory is handled as if it has been allocated
	by the class itself. In particular, it is freed in the destructor
        using free(). It should be allocated by malloc() and not by the C++
        new operator. */
    void commit(int nx, int ny, int nz, int elemSize, void* data);

    /// Returns pointer to the first element of the array.
    void* dataPtr() const { return data; }

    /** This methods exchanges the internal data pointer with an
        user-defined pointer. The user-defined memory will be freed in
        the destructor. The dimensions of the array are not changed
        at all. Therefore, @c data must point to an array with identical
        dimensions and element size. On return, @c data points to the
        previous location of the data array. */
    void swapDataPtr(void*& data);

  protected:
    int dims[3];
    mculong elemSize;
    char* data;
    char* toFree;

    void cleanup();
};

#endif

/// @}
