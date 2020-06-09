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
#ifndef VS_VESSEL_SEGMENTATION_H
#define VS_VESSEL_SEGMENTATION_H

#include "VsSegmentationAPI.h"
#include <vsvolren/Vs.h>
#include <vsvolren/VsInterface.h>
#include <vsvolren/VsRelay.h>
#include <vsvolren/VsVolume.h>
#include <vsvolren/VsDataAccess.h>
#include <mclib/McDArray.h>
#include <mclib/McBox3f.h>

// VS_RELAY_CLASS VsVesselSegmentation VsRelay

static const float mpi = 3.14159265358979323846f;

class VSSEGMENTATION_API VsVesselSegmentation : public VsInterface
{
    VS_DECL_INTERFACE        ( VsVesselSegmentation )
    VS_DECL_INTERFACE_FACTORY( VsVesselSegmentation )
    VS_DECL_INTERFACE_RELAY  ( VsVesselSegmentation )

public:

    enum VesselDensityType {
        BRIGHT_ON_DARK = 0,
        DARK_ON_BRIGHT = 1
    };

    VsVesselSegmentation( VsMeta * inMeta = 0 );
    virtual ~VsVesselSegmentation() {}

    virtual VSRESULT setVolume(VsVolume* volume);
    VsVolume* volume() const;

    // The compute function is implemented in the child class:
    // VsThinVesselSegmentation or VsThickVesselSegmentation.
    virtual VSRESULT compute(int numPoints, const McVec3f* points);
    void getCenterline(McDArray<McVec3f>& outCenterline); // VS_SYNC_CALL
    // VsSparseBitData* getResult();
    // VsSparseBitData* takeResult();
    // The getResult function is implemented in the child class:
    // VsThinVesselSegmentation or VsThickVesselSegmentation.
    virtual VSRESULT getResult(VsData* labels, McBox3i& box, int materialIdx);
    void getThickness(McDArray<float> &radii) { radii = mRadii; }

    // constrain algorithm in z direction by zmin, zmax  
    void setZConstraint(bool constraint); // VS_RELAY
    bool zConstraint();

    // sets the vessels density type
    // 0 = bright vessel on dark background
    // 1 = dark vessel on bright background
    void setVesselDensityType(int inDensityType) { mVesselDensityType = inDensityType; }
    int getVesselDensityType() { return mVesselDensityType; }

    static void findCenterOfVessel(VsVolume* volume, McVec3f& pos, int gradCount=2, int numSteps=6);
    
    // TODO: getAverageIntensity() and replaceWith0() in a new class VsSegmentationTools

    // This function relays the getAverageIntensity() from VsCardiacAnalysis to get the
    // average intensity by calling the server.
    void getAverageIntensity( VsData * inData, const McVec3i & inISeed, float & outResult ); // VS_SYNC_CALL
    
    // recenter the whole centerline and find a radius for each point
    void findCenterOfVessel(McDArray<float>& radii, int vmin, int vmax, bool recenter = true);

    void smooth3DPath(int runs, McDArray<McVec3f> &path);

private:
    static bool eval(const VsDataAccess* a, const McVec3f& pos, float& val, McVec3f& gradient);

protected:
    
    void findCenterOfVessel(McVec3f& pos, int gradCount=2, int numSteps=6){ 
        if(mVolume) findCenterOfVessel(mVolume,  pos, gradCount, numSteps);
    };

    void compute3DPath(int idxLevel, McDArray<mculong> &idxPath, McDArray<McVec3f> &path);
    

    // VsSparseBitData* mFilled;
    VsVolume *mVolume; // the volume, the segmentation should be computed on 
    McVec3l mDims;  // dimensions of high resolution
    McVec3l mDims1; // dimensions of low resolution 
    McBox3f mBBox; // bounding box of the volume 
    McBox3f mBBox1; // bounding box of low res volume
    McDArray<McVec3f> mCenterline; // the resulting centerline of the vessel segmentation
    McDArray<float> mRadii; // radius of each centerline point
    bool mZConstraint;
    int mVesselDensityType;
};

#endif


/// @}
