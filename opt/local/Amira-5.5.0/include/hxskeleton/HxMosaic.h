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

/// @addtogroup hxskeleton hxskeleton
/// @{
#ifndef HX_MOSAIC_H
#define HX_MOSAIC_H

#include "HxSkeletonWinDLLApi.h"
#include <Inventor/SbLinear.h>
#include <hxcore/HxSpatialData.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxTightConnection.h>

#include <amiramesh/AmiraMesh.h>

class HxSpatialData;

/** This is a container for HxSpatialData that are stored on disk.
    With the add button you can select files on disk. They will be loaded
    and all HxSpatialData that are created are added to the HxMosaic.
    The Mosaic stores Filename, BoundingBox, Range, TypeId, Transform,
    PrimType, dims and NDataVar of the bricks as parameters.
    They can be accessed via getBrickParameters ().
  */
class HXSKELETON_API HxMosaic : public HxSpatialData {

    HX_HEADER (HxMosaic);

    public:
        ///
        HxPortInfo portInfo;
        ///
        HxPortButtonList portAction;

        ///
        virtual void update ();

        ///
        virtual void compute ();

        /// get over all boundingbox
        virtual void getBoundingBox (float bbox[6]) const;

        ///
        int addBrick (HxSpatialData* dat) {
            return addOrUpdateBrick (dat, -1);
        }

        ///
        int addBrick (const char* filename);

        /// check all bricks against the disk version.
        void updateAllBricks ();

        ///
        int getNumBricks ();
        ///
        HxParamBundle* getBrickParameters (int brick);
        ///
        const McTypeInfo* getBrickTypeId (int brick);
        ///
        //ML HxSpatialData* getBrick (int num);

        McHandle<HxSpatialData> getBrick (int num);
        /// remove a brick
        void removeBrick (int num);

        /** get a brick containing pos, 
            choose the brick in which pos is the furthest away from the border
            */
        HxSpatialData* getBestMatchingBrick (const float* pos);
       
        /** Load bricks touched by box.
          */
        void loadBricksTouchedByBox (const float* box);
        ///
        int saveASCII(const char* filename);
        ///
        static int readAmiraMesh (AmiraMesh* m, const char* filename);

        ///
        virtual int parse(Tcl_Interp* t, int argc, char **argv);
		HxMosaic ();
		~HxMosaic ();
		
        int addOrUpdateBrick (HxSpatialData* dat, int up);
        void calcOverAllParams ();

        
        

    private:
        HxParamBundle* getDescrBundle ();
        float bbox[6];
};

#endif

/// @}
