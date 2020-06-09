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
#ifndef MC_TYPEDDATA2D_H
#define MC_TYPEDDATA2D_H

#include "McWinDLLApi.h"
#include "McPrimType.h"
#include "McTypedPointer.h"
#include "McRawData2D.h"

/** This class manages a 2D array of typed items. In addition to the
    base class it stores an additional McPrimType variable which
    specifies the primitive data type of the elements. It also stores
    the number of data variables per element. In this way it is possible
    to represent multi-component data such as RGBA color images.
*/

class MCLIB_API McTypedData2D : public McRawData2D {

public:
    /// Default constructor requires to call init() later on.
    McTypedData2D();

    /** Copy constructor. If the other McTypedData2D object references external
        memory this object will reference the same external memory. If the other
        McTypedData2D object has local memory this object also allocates local
        memory and copies the data into it. */
    McTypedData2D(const McTypedData2D& other);

    /// This constructor allocates a contiguous array of given size and type.
    McTypedData2D(int nx, int ny, McPrimType type, int nDataVar=1);

    /// This constructor references a contiguous block of external memory.
    McTypedData2D(int nx, int ny, McTypedPointer data, int nDataVar=1);

    /// This constructor also references a contiguous block of external memory.
    McTypedData2D(const int *dims, McTypedPointer data, int nDataVar=1);

    /// This contructor references a non-contiguous block of external memory.
    McTypedData2D(int nx, int ny, int bytesPerPixel, int bytesPerLine,
        McTypedPointer data, int nDataVar=1);

    /// Destructor.
    ~McTypedData2D();

    /** Assignment operator. If the other McTypedData2D object references external
        memory this object will reference the same external memory. If the other
        McTypedData2D object has local memory this object also allocates local
        memory and copies the data into it. */
    McTypedData2D& operator=(const McTypedData2D& other);

    /// For resizing with reallocation.
    void init(int nx, int ny, McPrimType type, int nDataVar=1);

    /// For resizing with existing external data.
    void init(int nx, int ny, McTypedPointer data, int nDataVar=1);

    /// Also for resizing with existing external data.
    void init(const int* dims, McTypedPointer data, int nDataVar=1);

    /// For resizing with existing data in non-contiguous external memory...
    void init(int nx, int ny, int bPP, int bytesPerLine, McTypedPointer data, int nDataVar=1);

    /// Returns primitive data type.
    McPrimType primType() const { return myPrimType; }

    /// Returns the number of data variables per element.
    int nDataVar() const { return myNumDataVar; }

    /// Returns a typed pointer to the first data element.
    McTypedPointer typedPtr() const { return McTypedPointer(dataPtr(),myPrimType); }

  protected:
    int myNumDataVar;
    McPrimType myPrimType;

  friend class McTypedData3D;
};

#endif

/// @}
