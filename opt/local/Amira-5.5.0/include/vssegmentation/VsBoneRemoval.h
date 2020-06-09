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
#ifndef HX_BONE_REMOVAL_H
#define HX_BONE_REMOVAL_H

#include <mclib/McBitfield.h>
#include <mclib/McBox3f.h>

#include <vsvolren/Vs.h>
#include <vsvolren/VsInterface.h>
#include <vsvolren/VsRelay.h>

#include <vsvolren/VsData.h>
#include <vsvolren/VsDataAccess.h>
#include <vsvolren/VsVolume.h>
#include <vsvolren/VsBackgroundWorker.h>
#include <vsvolren/VsTaskControl.h>

#include "VsSegmentationAPI.h"

// VS_RELAY_CLASS VsBoneRemoval VsRelay

class HxBoneRemovalInput;
class HxBoneRemovalOutput;

/** Module for bone removal with consideration of vessels. The algorithm
    implemented by this class has been developed for identifying bones
    in large CTA run-off data sets (legs and pelvis). It can not be applied
    to remove bones in other parts of the body like head or neck.
*/   
class VSSEGMENTATION_API VsBoneRemoval : public VsInterface
{
    VS_DECL_INTERFACE        ( VsBoneRemoval )
    VS_DECL_INTERFACE_FACTORY( VsBoneRemoval )
    VS_DECL_INTERFACE_RELAY  ( VsBoneRemoval )

public:
    enum SeedPointType { SEED_POINT_FEMUR, SEED_POINT_PATELLA, SEED_POINT_TIBIA, SEED_POINTS_TIBIA_AND_FIBULA};
        
    /// Constructor.
    VsBoneRemoval( VsMeta * inMeta = 0 );

    /// Destructor.
    ~VsBoneRemoval();

    /// Returns the material name used by this tool, namely <c>Bone</c>.
    static const char* materialName(); // LOCAL_GET

    /// Sets the volume to be segmented.
    void setVolume(VsVolume* volume); // VS_RELAY

    /** Sets bitfield to store the segmentation results. If a bitfield is set,
        the segmented bone voxels are not only marked in the input volume's
        label field but also in the bitfield. The bitfield then can be simply
        written to file using VsLabelTools::writeMaterialToFile(). */
    // This function is removed - of cause relaying this class
    //void setBitfield(McBitfield* bitfield);

    /** Stores the segmentation results (after there were computed). The
        segmented bone voxels are not only marked in the input volume's label
        field. They were also marked in the bitfield. The segmentation results
        will stored by the the function VsLabelTools::writeMaterialToFile()
        for writting the bitfield to a file. */
    void storeBoneBitFieldToFile(VsVolume* volume, const char* user); // VS_RELAY

    /** Loads the in storeBoneBitFieldToFile() saved segmentations. */
    VSRESULT loadBoneBitFieldFromFile(VsVolume* volume,const char* user); // VS_SYNC_CALL

    /** Sets a point inside the aorta. This method MUST be called if the pelvis
        should be segmented, see setSegmentPelvis(). The parameters i,j,k are
        voxel indices in the original volume (level 0). */
    void setAorta(int i, int j, int k); // VS_RELAY

    /** Enable segmentation of pelvis. The default value is true. Segmentation
        of the pelvis requires that a point inside the aorta has been specified
        (see setAorta()) and the lower boundary of the hip has been set (see
        setLowerHip()) or could be successfully computed. */
    void setSegmentPelvis(bool value); // VS_RELAY

    /** Enable segmentation of legs. The default value is true. */
    void setSegmentLegs(bool value); // VS_RELAY

    /** Overwrites slice number of lower boundary of knee. The slice
        number refers to the original volume (level 0). A value of -1 indicates that
        the boundary should be computed automatically. This is the default. */
    void setLowerKnee(int sliceNumber) { mLowerKnee = sliceNumber; } // LOCAL_GET

    /** Overwrites slice number of lower boundary of hip. The slice
        number refers to the original volume (level 0). A value of -1 indicates that
        the boundary should be computed automatically. This is the default. */
    void setLowerHip(int sliceNumber) { mLowerHip = sliceNumber; } // LOCAL_GET

    /** Overwrites slice number of lower boundary of lung. The slice
        number refers to the original volume (level 0). A value of -1 indicates that
        the boundary should be computed automatically. This is the default. */
    void setLowerLung(int sliceNumber) { mLowerLung = sliceNumber; } // LOCAL_GET

    /** Tries to identify the bones in volume set in setVolume(). On default,
        the legs and the pelvis are segmented. Segmentation of the pelvis
        requires that a point in the aorta has been set via setAorta(). */
    VSRESULT compute(VsTaskControl* progress=0); // LOCAL_GET

    /** Start bone removal segmentation in the background. The taskControl
        object can be used to query the status of the job or to cancel it.
        The method returns immediatly. The return value simply indicates if
        the job could be successfully started. The actual result code of the
        computation is reported by VsTaskControl::setCompleted(). */
    VSRESULT computeAsync(VsTaskControl* inTaskControl); // VS_SYNC_CALL

    /** Tries to identify the boundaries between different regions in the
        volume to be segmented. This method is called automatically from
        compute(). Thus there is usually no need to call it separately.

        \param[out] lowerKnee
            Approximately the slice number at which the shinbone and the knee merge.
        \param[out] lowerHip
            Slice number at which thigh and pelvis merge. If no hip was detected in
            the data set, lowerHip will be set to 0.
        \param[out] lowerLung
            Slice number where the lung starts (bottom to top). If no lung is detected
            lowerLung will be set to zero.
        \param[in] progress
            Optional progress interface. If set the method reports progress updates
            and terminates if progress->wasInterrupted() return true. In this case
            the method fails and Vs::lastError() is set to VS::CODE_INTERRUPTED.
        \return VS_OK on success, VS_FAILED otherwise.
            To get extended error information, call Vs::lastError().
    */
    VSRESULT computeBodyPartBoundaries(int& outLowerKnee, int& outLowerHip, int& outLowerLung,
                                       VsTaskControl* inProgress); // VS_SYNC_CALL

    VSRESULT findAorta(McVec3i& outSeedPoint, VsTaskControl* inProgress); // VS_SYNC_CALL

protected:
    

    void initRegionParams();

    //-------------------------------------------------------------------
    // 3D methods
    //-------------------------------------------------------------------
    bool segmentPelvicRegion(McProgressInterface* progress);

    bool segmentLegs(int nRegions, McProgressInterface* progress);

    bool segmentLegs3D(McProgressInterface* progress);

    bool thresholdSegmentation(void* imageData, McPrimType imageType, 
                               const int *dims, float minVal, float maxVal, 
                               unsigned char* labels);   

    bool fillHolesAllSlices(const int *dims, 
                            unsigned char* labels,
                            unsigned char material);

    bool growSelection3D(const int *dims, 
                         unsigned char* labels, 
                         unsigned char material, 
                         int nGrow);

    bool regionGrowing3D(void* imageData, McPrimType imageType, 
                         const int *dims, 
                         unsigned char* labels, 
                         unsigned char material, 
                         float minVal, float maxVal,
                         int nGrow);

    bool classifySlices();

    //-------------------------------------------------------------------
    // 2D methods
    //-------------------------------------------------------------------
    bool thresholdSegmentation2D(void* imageData, McPrimType imageType, 
                                 const int *dims, float minVal, float maxVal, 
                                 unsigned char* labels, int slice,
                                 unsigned char material);

    bool fillHoles2D(const int *dims, unsigned char* labels, int slice, unsigned char material);

    int findConnectedComponents2D(const int *dims, 
                                  unsigned char* labels,
                                  unsigned short *labeledLabels,
                                  int slice, 
                                  bool dosort, bool doclassify, bool dolabel, 
                                  bool verbose);

    bool findBoneSeedPointsInLegs(int slice,
        SeedPointType seedPointType, 
        // 0 right, 1 left, 2,3 seedpoints in fibulas
        McVec3i *seedPoints);

    VsVolume* mVolume;
    McBitfield* mBoneBitfield;
    VsBackgroundWorker mWorker;

    /// image dataset to be labelled
    HxBoneRemovalInput* mInput;

    /// output labelfield
    HxBoneRemovalOutput *mOutput;


    /// info about slice classifications
    enum SliceClassification
    {
        SLICE_UNKNOWN,
        SLICE_LOWER_THIGHS,
        SLICE_UPPER_THIGHS
    };
    McDArray<SliceClassification> mSliceClassifications;

    struct regionParams
    {
        float lowerBoundBone;
        float upperBoundVessel;
    };
    McDArray<regionParams> mRegionParams;

    int mParamThreshold1HU;
    int mParamThreshold2HU;
    int mParamNGrowLegs;
    int mParamNGrow;
    int mParamLowerBoundBoneArea;

    bool mParamVerbose;
    bool mParamTiming;
    
    bool mParamPelvic;
    bool mParamLegs;
    
    //0 Foot;
    //1 Knee1;
    //2 Knee2;
    //3 HipBone;
    //4 Upper;
    int mParamBounds[5];

    int mParamSeedX;
    int mParamSeedY;
    int mParamSeedZ;

    int mLowerKnee;
    int mLowerHip;
    int mLowerLung;
};


/*
This is set of adapter classes that adopt Amira's volume access methods
to vsvolren volume access methods. Created for integration Amira's
BoneRemoval compute module into visage environment.
*/


class HxBoneRemovalLatticeAdapter
{
public:
    HxBoneRemovalLatticeAdapter(const VsDataAccess *aData);
    ~HxBoneRemovalLatticeAdapter();
    
    McPrimType primType() const;
    const int* dims();
    void* dataPtr();
    
private:
    const VsDataAccess *mDataAcc;
    int mDims[3];
};



class HxBoneRemovalInput
{
public:
    HxBoneRemovalInput(const VsDataAccess *aData);
    ~HxBoneRemovalInput();

    void setBoundingBox(const McBox3f &aBox);
    void getBoundingBox(float bbox[6]) const;

    HxBoneRemovalLatticeAdapter lattice;
    
private:
    McBox3f mBox;
};


class HxBoneRemovalOutput
{
public:
    HxBoneRemovalOutput(const VsDataAccess *aData);
    ~HxBoneRemovalOutput();
    

    HxBoneRemovalLatticeAdapter lattice;
};


#endif

/// @}
