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
#ifndef _TAG_InStreamDataFile_h
#define _TAG_InStreamDataFile_h


#ifdef NEWSTYLE_IOSTREAM
#include <fstream>
using std::ifstream;
using std::ios;
#include <iosfwd>
using std::streampos;
#else
#include <fstream.h>
#endif

#include <mclib/McList.h>

#include "ZMFWinDLLApi.h"

#include "StreamDataFile.h"

#include "NumType.h"

///
class ZMF_API InStreamDataFile : public StreamDataFile 
{
    struct OpenFileRecord : public McLink {
        /// 
        InStreamDataFile & referencer;

        ////
        ifstream is;
        
        ///
        OpenFileRecord(const char * name, InStreamDataFile & ref)
            : referencer(ref),
#if defined(HX_OS_WIN) || defined(HX_OS_MAC)
              is(name,ios::in|ios::binary)
#else
              is(name,ios::in)
#endif
        {
            if (!is.good()) {
                throw StreamBad();
            }
        }
    };

    static McList<OpenFileRecord> openFiles;
    
    OpenFileRecord * fileRecord;

    ifstream & supplyFile();

    streampos theOffset;

public:
    ///
    InStreamDataFile(const char *filename) 
        : StreamDataFile(filename),
          fileRecord(0)
    { }

    ~InStreamDataFile();
    
    void setOffset(streampos offset);
    streampos getOffset();
    
    void readChars(char *p,int cnt);
    void readNum(void *p,int cnt,NumType::basetypes t);
    int  readChar();
    void readInt2(int &a);
    void readInt4(int &a);
    void readDim(int &a);
};

#endif

/// @}
