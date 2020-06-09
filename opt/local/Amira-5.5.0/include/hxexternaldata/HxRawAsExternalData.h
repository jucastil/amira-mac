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

/// @addtogroup hxexternaldata hxexternaldata
/// @{
#ifndef HX_RAW_AS_EXTERNAL_DATA
#define HX_RAW_AS_EXTERNAL_DATA

#include "HxExternalData.h"
#include <mclib/McFilename.h>

class HXEXTERNALDATA_API HxRawAsExternalData : public HxExternalData {

    HX_DATA_HEADER (HxRawAsExternalData);

    private:
        HxRawAsExternalData (const int dims[3], int nDataVar, McPrimType primType);

    public:
        ~HxRawAsExternalData ();

        static HxRawAsExternalData* open (const char* filename, const int dims[3],
            int nDataVar, bool littleEndian, int skipheader,
            float bbox[6], McPrimType primType);

        static HxRawAsExternalData* open (int n, const char** filenames, const int dims[3],
            int nDataVar, bool littleEndian, int skipheader,
            float bbox[6], McPrimType primType);

        static int readRawAsExternalData (int n, const char** argv);

        static int readAmiraMeshAsExternalData (const char* filename);

        virtual int getBlock(const BlockRequest* request);

        virtual void getBoundingBox (float bb[6]) const {
            for (int i = 0; i < 6; i++) {
                bb[i] = bbox[i];
            }
        };

        /** Set the bounding box.
          */
        virtual void setBoundingBox(float bb[6]);

        /** Parse Tcl commands.
          */
        virtual int parse(Tcl_Interp* t, int argc, char **argv);
    private:
        McDArray<McFilename> files;
        int filehandle;
        int skipHeader;
        bool littleEndian;
        float bbox[6];
};

#endif // HX_RAW_AS_EXTERNAL_DATA

/// @}
