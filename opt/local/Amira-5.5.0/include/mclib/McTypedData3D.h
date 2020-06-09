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
#ifndef MC_TYPEDDATA3D_H
#define MC_TYPEDDATA3D_H

#include "McWinDLLApi.h"
#include "McPrimType.h"
#include "McTypedPointer.h"
#include "McRawData3D.h"

class McTypedData2D;

/** This class manages a 3D array of typed items. In addition to the
    base class it stores an additional McPrimType variable which
    specifies the primitive data type of the elements. */

class MCLIB_API McTypedData3D : public McRawData3D {

public:
    /** Build an empty McTypedData3D */
    McTypedData3D();

    /** This constructor allocates an array of @c nx*ny*nz elements
	of specified type. */
    McTypedData3D(int nx, int ny, int nz, McPrimType type, int nDataVar=1);

    /** This constructor allocates an array of @c d[0]*d[1]*d[2] elements.
	of specified type. */
    McTypedData3D(const int *dims, McPrimType type, int nDataVar=1);

    /** This constructor initializes the array with an existing block of
        memory. The memory is not freed in the destructor. */
    McTypedData3D(int nx, int ny, int nz, McTypedPointer data, int nDataVar=1);

    /// This constructor differs from the one above only in its signature.
    McTypedData3D(const int *dims, McTypedPointer data, int nDataVar=1);

    /// Destructor.
    ~McTypedData3D();

    /// Reallocates the 3D array to match the new dimensions.
    void init(int nx, int ny, int nz, McPrimType type, int nDataVar=1);

    /** Initializes the array with existing memory. The memory is not freed
        in the destructor. */
    void init(int nx, int ny, int nz, McTypedPointer data, int nDataVar=1);

    /// Returns the primitive data type.
    McPrimType primType() const { return myPrimType; }

    /// Returns the number of data variables per element.
    int nDataVar() const { return myNumDataVar; }

    /// Overloaded method. Also sets the primitive data type correctly.
    void getSlice(int orientation, int sliceNumber,
                  McTypedData2D& result, int copyData=0) const;

  protected:
    int myNumDataVar;
    McPrimType myPrimType;
};

#endif

/// @}
