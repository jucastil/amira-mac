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

/// @addtogroup molio molio
/// @{
#ifndef WRITERBASE_H
#define WRITERBASE_H

#include "MolIOWinDLLApi.h"

#include <stdio.h>

extern "C" char* itoa2(int n);

//--------------------------------------------------------
//          writer

class MOLIO_API writer {
protected:
    // pointer to file-stream to which we write to
    FILE* stream; 
public:
    /// Constructor, file @c filename will be opened
    writer(const char* filename);
    /// Destructor, file will be closed
    ~writer();

    /// returns whether file could be opened
    bool isOpen() const;

    /// write to stream
    void write(const char* str);
    void write(int i);
    void write(float f);
    /** write to stream and fill out all endpos-startpos 
        columns the content will be aligned according
        to justify (see enum) **/
    void writeColumns(
        const char* str,
        int startPos,
        int endPos,
        short unsigned int justify=RIGHT);
    void writeColumns(
        int i,
        int startPos,
        int endPos,
        short unsigned int justify=RIGHT);
    void writeColumns(
        float f,
        int startPos,
        int endPos,
        short unsigned int justify=RIGHT);
    /// alignment constants needed for writeColumns parameter justify
    enum justify { RIGHT,LEFT,CENTER};
};

#endif

/// @}
