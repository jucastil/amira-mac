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
#ifndef MC_RAWDATA2D_H
#define MC_RAWDATA2D_H

#include <assert.h>
#include "McPrimType.h"
#include "McWinDLLApi.h"

/** This class manages a 2D array of untyped items. The size of an
    individual element has to be defined explicitly by the user. The class
    provides constructors which allow one to access already existing
    user-controlled memory. By specifying a special parameter
    @c bytesPerLine the class allows to handle padded or aligned arrays.
    @see McRawData3D, McData2D, McData3D, McTypedData2D, McTypedData3D
*/

class MCLIB_API McRawData2D
{
  public:
    /// The default constructor allocates no memory.
    McRawData2D();

    /** Copy constructor. If the other McRawData2D object references external
        memory this object will reference the same external memory. If the other
        McRawData2D object has local memory this object also allocates local
        memory and copies the data into it. */
    McRawData2D(const McRawData2D& other);

    /// This constructor allocates a contiguous array of given size.
    McRawData2D(int nx, int ny, int elemSize);

    /** This constructor references a contiguous block of external memory.
	The memory is not freed in the destructor. In order to really pass control
        over an existing memory segment to the class use the commit() method. */
    McRawData2D(int nx, int ny, int elemSize, void* data);

    /** This initializes the array with an existing block of non-contiguous memory.
        The memory is not freed in the destructor.  */
    McRawData2D(int nx, int ny, int elemSize, int bytesPerLine, void* data);

    /** This initializes the array with an existing block of non-contiguous memory.
        The memory is not freed in the destructor.  */
    McRawData2D(int nx, int ny, int elemSize, int bytesPerPixel, int bytesPerLine, void* data);

    /// Destructor frees any memory allocated by the class itself.
    ~McRawData2D();

    /** Assignment operator. If the other McRawData2D object references external
        memory this object will reference the same external memory. If the other
        McRawData2D object has local memory this object also allocates local
        memory and copies the data into it. */
    McRawData2D& operator=(const McRawData2D& other);

    /// Returns address of data item with given index pair.
    void* address(int i, int j) const {
	assert(i>=0 && j>=0 && i<nx && j<ny);
	return (&data[j*(mculong)bytesPerLine+i*(mculong)bytesPerPixel]);
    }

    /// Returns true if data is stored in one big block.
    int isContiguous() const;

    /// Returns true if the data is stored locally.
    int islocal() const { return (toFree!=0); }

    /** Copies the data into local memory. The method allocates memory and copies
        the data into it so that no external memory is referenced any more. The
        memory is contiguous then. */
    void makeLocal();

    /// Initializes the data to zero.
    void clear();

    /// Returns x dimension of array.
    int sizeX() const { return nx; }

    /// Returns y dimension of array.
    int sizeY() const { return ny; }

    /// Returns pointer to dimensions vector.
    const int* dims() const { return &nx; }

    /// Returns the size of an single array element in bytes.
    int getElemSize() const { return elemSize; }

    /// Returns the number of bytes of a scanline in x-direction.
    int getBytesPerPixel() const { return bytesPerPixel; }
  
    /// Returns the number of bytes of a scanline in x-direction.
    int getBytesPerLine() const { return bytesPerLine; }

    /// Reallocates the 2D array to match the new dimensions.
    void init(int nx, int ny, int elemSize);

    /** This initializes the array with an existing block of memory.
	The memory is not freed in the destructor. In order to really
	pass control over an existing memory segment to the class use
	the commit() method. */
    void init(int nx, int ny, int elemSize, void* data);

    /** This initializes the array with an existing block of
	non-contiguous memory. The memory is not freed in the destructor.  */
    void init(int nx, int ny, int elemSize, int bytesPerLine, void* data);

    /** This initializes the array with an existing block of
	non-contiguous memory. The memory is not freed in the destructor.  */
    void init(int nx, int ny, int elemSize, int bytesPerPixel,
        int bytesPerLine, void* data);

    /** This method passes control over an existing block of memory to
        the class. The given memory is handled as if it has been allocated
	by the class itself. In particular, it is freed in the destructor
	using free(). Therefore, it should be allocated by malloc() and
	not by the C++ new operator. */
    void commit(int nx, int ny, int elemSize, void* data);

    /** This method copies the data values from an other data object to	the
        memory this object points to. This is especially useful to copy
        contiguous memory to non-contiguous memory. The other object must
        have same dimensions and primtype size. On success true is returned. */
    bool copyData(const McRawData2D& other);

    /// Returns pointer to the first element of the array.
    char* dataPtr() const { return data; }

  protected:
    int nx;
    int ny;
    mculong elemSize;
    int bytesPerPixel;
    int bytesPerLine;
    char* data;
    char* toFree;

    void cleanup();
};

#endif

/// @}
