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
#ifndef MC_TYPED_POINTER_H
#define MC_TYPED_POINTER_H

#include "McWinDLLApi.h"
#include "McPrimType.h"

/** Pointer to data with additional type information. This class
    stores a void* pointer together with a McPrimType variable. */

class MCLIB_API McTypedPointer
{
 public:
    /// Constructor for data of type McPrimType::mc_uint8.
    McTypedPointer(unsigned char* d) :
        data(d),
        primtype(d) { }

    /// Constructor for data of type McPrimType::mc_int16.
    McTypedPointer(short* d) :
        data(d),
        primtype(d) { }

    /// Constructor for data of type McPrimType::mc_int32.
    McTypedPointer(int* d) :
        data(d),
        primtype(d) { }

    /// Constructor for data of type McPrimType::mc_float.
    McTypedPointer(float* d) :
        data(d),
        primtype(d) { }

    /// Constructor for data of type McPrimType::mc_double.
    McTypedPointer(double* d) :
        data(d),
        primtype(d) { }

    /// Constructor for data of type McPrimType::mc_uint16.
    McTypedPointer(unsigned short* d) :
        data(d),
        primtype(d) { }

    /// Constructor for data of type McPrimType::mc_uint32.
    McTypedPointer(unsigned int* d) :
        data(d),
        primtype(d) { }

    /// Constructor for data of type McPrimType::mc_int8.
    McTypedPointer(char* d) :
        data(d),
        primtype(d) { }

    /// Constructor for data of type @c type.
    McTypedPointer(void* d, McPrimType type) :
        data(d),
        primtype(type) { }

    /// Returns the data pointer.
    operator void*() {
        return data;
    }

    /// Returns the type of the data.
    McPrimType primType() const {
        return primtype;
    }

    void* data;
    McPrimType primtype;
};

#endif

/// @}
