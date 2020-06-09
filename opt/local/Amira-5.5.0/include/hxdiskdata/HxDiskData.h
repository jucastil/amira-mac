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

/// @addtogroup hxdiskdata hxdiskdata
/// @{
#ifndef HX_DISK_DATA_H
#define HX_DISK_DATA_H

#include "HxDiskDataWinDLLApi.h"

#include <amiramesh/AmiraMesh.h>
#include <hxexternaldata/HxExternalData.h>

#include <mclib/McFilename.h>

class LatticeManager;

class HXDISKDATA_API HxDiskData : public HxExternalData {

    HX_DATA_HEADER (HxDiskData);

    protected:
        /// 
        HxDiskData (const int dims[3], int nDataVar, McPrimType primType, LatticeManager* lm);

        /// we're refcounted
        ~HxDiskData ();
    public:
        /// Amira reader method
        static int readAmiraMesh (AmiraMesh* m, const char* filename);
        /// create new diskdata
        static HxDiskData* create (const char* amFile, const char* datPath
                , const int dims[3], int nDataVar, McPrimType pType
                , const float bbox[6]);
        /// update all subsampling levels on disk
        void updateAllLevels ();
       
        /// HxExternalData Interface
        virtual int getBlock(const BlockRequest* request);

        /// HxExternalData Interface
        virtual bool isWritable ();

        /// HxExternalData Interface
        virtual int putBlock(const BlockRequest* request); 

        /// HxExternalData Interface
        virtual void getBoundingBox (float b[6]) const {
            memcpy (b, bbox, 6 * sizeof (float));
        };

        /// HxExternalData Interface
        virtual bool canSaveParameters () const {
            return 1;
        }

        /// HxExternalData Interface
        virtual int saveParameters (const HxParamBundle& p);

        /// useful function
        virtual void clear ();
        
        ///
        virtual int parse(Tcl_Interp* t, int argc, char **argv);
    private:
        LatticeManager* latticeManager;
        float bbox[6];
        McFilename datPath;
        McFilename amPath;

        int saveDescription (const char* amFile, const HxParamBundle* more = 0);
};

#endif

/// @}
