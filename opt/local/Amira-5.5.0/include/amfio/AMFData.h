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

/// @addtogroup amfio amfio
/// @{
#ifndef AMFIO_AMFDATA_H
#define AMFIO_AMFDATA_H

#include "AMFIOWinDLLApi.h"

/// Multi-dimensional parameter of arbitrary type.
class AMFIO_API AMFData
{
public:

    enum DataType {
        // null terminated string
        DT_STRING,
        // 8 bit int char
        DT_INT8,
        // un8 bit int
        DT_UINT8,
        // 16 bit int
        DT_INT16,
        // un16 bit int
        DT_UINT16,
        // 32 bit int
        DT_INT32,
        //
        DT_UINT32,
        // 32bit float 
        DT_FLOAT,
        DT_UNKNOWN
    };
    // return size in byte (-1 for types of variable lenght like string)
    //static int getSize(DataType t);
    static const char* getDataTypeString(DataType t);
    static const DataType getDataType(const char* datatypestr);

};

#endif


/// @}
