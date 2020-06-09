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

/// @addtogroup zmf zmf
/// @{
#ifndef _TAG_ZIBMolFileWriter_h_
#define _TAG_ZIBMolFileWriter_h_

#include "ZMFWinDLLApi.h"

#include "SomeType.h"
#include "ForkType.h"
#include <mclib/McHandable.h>

#include "OutStreamDataFile.h"

/** Files containing structured data.
    Simply call @c write() to open a structured file. */
class ZMF_API ZIBMolFileWriter : public McHandable {
public:
    ZIBMolFileWriter();

    /// Load a data file
    bool write(const char *filename);
    ///
    bool writeStructuredHeader(SomeType *type);
    ///
    SomeType *typ() { return thetype; }
    ///
    static ostream * errorstream;

    ///
    void writeInteger(int value);
    ///
    void writeByteMatrix(int N, const int * ext, const signed char * data);
    ///
    void writeIntegerMatrix(int N, const int * ext, const int * data);
    ///
    void writeFloat(float value);
    ///
    void writeFloatMatrix(int N, const int * ext, const float * data);
    ///
    void writeArraySize(int size);
    ///
    void writeString(const char *text);
    ///
    void printPath(ostream & os);

protected:
    ///
    McString header;
    ///
    bool isBigEndian;
    ///
    long dataStart;
    ///
    McHandle<SomeType> thetype;

    ///
    McHandle<OutStreamDataFile> outfile;

    struct PathEntry {
        PathEntry(SomeType * t=0) 
            : type(t), dim(0), ix(0) 
        {
            ForkType * ft = dynamic_cast<ForkType *>(type.ptr());
            if(ft) dim = ft->numEntries();
        }

        McHandle<SomeType> type;
        int dim;
        int ix;
    };

    ///
    McDArray<PathEntry> path;
    ///
    void stepPath();

    ///
    SomeType * getCurrentType();

    ///
    bool endOfFileFlag;
};

#endif

/// @}
