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
#ifndef VS_BONE_REMOVAL_SLICE_H
#define VS_BONE_REMOVAL_SLICE_H

#include <mclib/McWatch.h>
#include <mclib/McDArray.h>
#include <mclib/McConnectedComponents.h>

#include <vsvolren/VsVolume.h>

#include "VsSegmentationAPI.h"

/// Segmentation of one slice based on a threshold segmentation.
class VSSEGMENTATION_API VsBoneRemovalSlice {

    public:
        VsBoneRemovalSlice();

        ~VsBoneRemovalSlice();

        bool init(VsVolume* volume, const int* dims, 
                  const float* voxelSize,
                  float thresholdLowHU,
                  float thresholdHighHU,
                  float thresholdStepHU);

        bool setImageData(void* imageData, McPrimType imageType);                  

        bool setTableLabels(unsigned char* tableLabels);                  

        void setParams(float lowerBoundBone, float upperBoundVessel);

        int findBoneSeedPointsInLegs(McVec3i seedPoints[2], bool getCenter,
                                     int numPointsToBeExcluded=0,
                                     McVec3i *pointsToBeExcluded=NULL);

        bool doSegmentation();

        unsigned char* getLabels()
        {
            return mLabels;
        }

        bool getTimes(float &timeThresholding, float &timeFillHoles, 
                      float &timeOpening, float &timeFindConnected, 
                      float &timeFloodFill);

        bool opening(unsigned char* labels, 
                     unsigned char material, 
                     int nGrow, int* box);

        bool opening(unsigned char* labels, 
                     unsigned char material, 
                     int nGrow);

        static void fromLabels(mculong numBytes, unsigned char *labels, unsigned char material, unsigned char *dst);
        static void toLabels(mculong numBytes, unsigned char *labels, unsigned char material, unsigned char *src);

        bool findDisconnectedRegions(bool preserveVessels=false, int *bbox=NULL);

        bool thresholding(float minVal, float maxVal, 
                          unsigned char material);

        int findConnectedComponents(unsigned char* labels,
                                    float lowerBoundBone,
                                    float upperBoundVessel,
                                    bool dosort, bool dolabel, 
                                    bool verbose);                     

        McDArray<McConnectedComponents::Component> mComponents;

    protected:
        //-------------------------------------------------------------------
        // 2D methods
        //-------------------------------------------------------------------
        bool fillHoles(unsigned char* labels, 
                       unsigned char material);

        bool fillHolesSlow(unsigned char* labels, 
                           unsigned char material);

        bool growSelection(unsigned char* labels, 
                           unsigned char material, 
                           int nGrow);

        bool erode(unsigned char* labels, 
                   unsigned char material, 
                   int nGrow);

        bool dilate(unsigned char* labels, 
                    unsigned char material, 
                    int nGrow);

        bool closing(unsigned char* labels, 
                     unsigned char material, 
                     int nGrow);

        float getMaxImageValInLabel(unsigned char* labels, 
                                    unsigned char material);

        // returns number of pixels filled
        int floodFill(unsigned char* labels, 
                      int iseed, int jseed, 
                      unsigned char replaceMaterial, 
                      unsigned char byMaterial,
                      int *inbox,
                      int *outbox);

        // returns number of pixels filled
        int floodFill(unsigned char* labels, 
                      int iseed, int jseed, 
                      unsigned char replaceMaterial, 
                      unsigned char byMaterial,
                      int *outbox);

        //-------------------------------------------------------------------
        // member variables
        //-------------------------------------------------------------------
        VsVolume *mVolume;

        void* mImageData;

        McPrimType mImageType; 

        int mDims[2];

        float mVoxelSize[2];

        float mThresholdLowHU, mThresholdHighHU, mThresholdStepHU;

        float mLowerBoundBone, mUpperBoundVessel;

        unsigned char* mThresholdLabeling;

        unsigned short *mComponentsLabeling;

        McDArray<int> mMapId2Component;

        unsigned char* mLabels;

        unsigned char* mTableLabels;

        McWatch mWatch;

        float mTimeThresholding, mTimeFillHoles, mTimeOpening, 
            mTimeFindConnected, mTimeFloodFill;
    };

#endif

/// @}
