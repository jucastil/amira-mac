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

/// @addtogroup vssegmentation vssegmentation
/// @{
#ifndef VS_BONE_REMOVAL_VOLUME_H
#define VS_BONE_REMOVAL_VOLUME_H

#include <mclib/McWatch.h>
#include <mclib/McVec3i.h>
#include <mclib/McBox3i.h>
#include <mclib/McBitfield.h>
#include <mclib/McProgressInterface.h>

#include <vsvolren/VsVolume.h>

#include "VsSegmentationAPI.h"

/// Bone removal methods for whole volume.

class VSSEGMENTATION_API VsBoneRemovalVolume {

public:
    VsBoneRemovalVolume();

    ~VsBoneRemovalVolume();

    bool init(VsVolume* volume, const int* dims,
              float vx, float vy, float vz,
              void* imageData, McPrimType imageType,
              unsigned char* labelData,
              int stepMin, int stepMax);

    bool segmentPelvicRegion(
        McDArray<McVec3i> &seedPointsVessels, 
        McDArray<McVec3i> &seedPointsBone, 
        int nGrow, McProgressInterface* progress);

    bool segmentLegs3D(
        McDArray<McVec3i> &seedPointsRight, 
        McDArray<McVec3i> &seedPointsLeft, 
        int thresholdHU, int nGrowBone, 
        float lowerBoundBone, int upperBoundFill,
        int minSlicePreserve=-1, int maxSlicePreserve=-1,
        McProgressInterface* progress=0);

protected:
    //-------------------------------------------------------------------
    // 3D methods
    //-------------------------------------------------------------------

    bool getImageStatistics(McVec3i &seedPoint,
                            int radiusInPixels,
                            float &min, float &max, 
                            float &mean, float &median);

    bool checkSelectionInBone(McBox3i box);

    McVec3i findSuitableSeedPoint(McVec3i &seedPoint,
                                  int radiusInPixels,
                                  float &min, float &max, 
                                  float &mean,
                                  McDArray<McVec3i> &formerSeedPoints);

    // returns number of voxels selected
    mculong regionGrowing3D(McVec3i seedPoint,
                            float minVal, float maxVal, 
                            bool sameMaterialOnly,
                            int *bbox);

    //bool erode3D(unsigned char material, 
    //                bool lockOtherMaterials,
    //                int nGrow);

    bool dilate3D(unsigned char material, 
                    bool lockOtherMaterials,
                    int nGrow);
    bool fillHolesAllSlices(unsigned char material, int orientation=2, 
                            int xmin=-1, int xmax=-1,
                            int ymin=-1, int ymax=-1,
                            int zmin=-1, int zmax=-1);

    //-------------------------------------------------------------------
    // member variables
    //-------------------------------------------------------------------
    VsVolume *mVolume;
    
    void* mImageData;

    McPrimType mImageType; 

    int mDims[3];

    int mInitialStepMin;
    int mInitialStepMax;

    float mVoxelSize[3];

    unsigned char* mLabels;

    McBitfield mSelection;

    McWatch mWatch;
};

#endif

/// @}
