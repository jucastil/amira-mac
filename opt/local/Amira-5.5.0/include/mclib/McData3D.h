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
#ifndef MC_DATA3D_H
#define MC_DATA3D_H

#include "McWinDLLApi.h"
#include "McRawData3D.h"

/** This template class manages a 3D array of items of type @c T. The class
    is directly derived from @c McRawData3D. It provides convenience
    constructors and methods to obtain a reference to a typed data item.
    It does not define any variables in addition to the base class.
    This means, that an instance of type @c McRawData3D may safely be
    downcasted to @c McData3D<T>, if the instance is known to store
    data items of type @c T.
    @see McRawData2D, McRawData3D, McData2D, McTypedData2D, McTypedData3D
*/

template<class T>
class McData3D : public McRawData3D
{
  public:
    /// Access data items via an index triple.
    T& get(int i, int j, int k) const { return *(T*)address(i,j,k); }

    /// The default constructor allocates no memory.
    McData3D() { }

    /// This constructor allocates an array of given size.
    McData3D(int nx, int ny, int nz)
	: McRawData3D(nx, ny, nz, sizeof(T)) { }

    /** This initializes the array with an existing block of memory.
	The memory is not freed in the destructor. In order to really
	pass control over an existing memory segment to the class use
	the commit() method. */
    McData3D(int nx, int ny, int nz, T* data)
	: McRawData3D(nx, ny, nz, sizeof(T), data) { }


    /// Reallocates the 3D array to match the new dimensions.
    void init(int nx, int ny, int nz) {
	McRawData3D::init(nx, ny, nz, sizeof(T));
    }

    /** This initializes the array with an existing non-contiguous block
        of memory. The data memory is not freed in the destructor. */
    void init(int nx, int ny, int nz, T* data) {
	McRawData3D::init(nx, ny, nz, sizeof(T), data);
    }

    /** This method passes control over an existing block of memory to
        the class. The given memory is handled as if it has been allocated
	by the class itself. In particular, it is freed in the destructor
	using free(). Therefore, it should be allocated by malloc() and
	not by the C++ new operator. */
    void commit(int nx, int ny, int nz, T* data) {
	McRawData3D::commit(nx, ny, nz, sizeof(T), data);
    }

    /// Pointer to first data item
    T* dataPtr() { return (T*) data; }

    const T* dataPtr() const { return (T*) data; }

};

#endif

/// @}
