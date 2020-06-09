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
#ifndef VS_CARDIAC_ANALYSIS_H
#define VS_CARDIAC_ANALYSIS_H

#include <vsvolren/Vs.h>
#include <vsvolren/VsInterface.h>
#include <vsvolren/VsRelay.h>

#include "VsSegmentationAPI.h"
#include <mclib/McDArray.h>
#include <mclib/McVec3f.h>
#include <vsvolren/VsBackgroundWorker.h>
#include <vsvolren/VsTaskControl.h>

// VS_RELAY_CLASS VsCardiacAnalysis VsRelay

class McBitfield;
class McProgressInterface;
class VsData;
class VsVolume;

class VSSEGMENTATION_API VsCardiacAnalysis : public VsInterface
{
    VS_DECL_INTERFACE        ( VsCardiacAnalysis )
    VS_DECL_INTERFACE_FACTORY( VsCardiacAnalysis )
    VS_DECL_INTERFACE_RELAY  ( VsCardiacAnalysis )

public:

    VsCardiacAnalysis( VsMeta * inMeta = 0 );

    enum Zone // names for the 16 zones (from top to bottom)
    {
        BASAL_ANTERIOR = 0,
        BASAL_ANTEROSEPTAL = 1,
        BASAL_INFEROSEPTAL = 2,
        BASAL_INFERIOR = 3,
        BASAL_INFEROLATERAL = 4,
        BASAL_ANTEROLATERAL = 5,

        MID_ANTERIOR = 6,
        MID_ANTEROSEPTAL = 7,
        MID_INFEROSEPTAL = 8,
        MID_INFERIOR = 9,
        MID_INFEROLATERAL = 10,
        MID_ANTEROLATERAL = 11,

        APICAL_ANTERIOR = 12,
        APICAL_SEPTAL = 13,
        APICAL_INFERIOR = 14,
        APICAL_LATERAL = 15
    };

private:
    // Parameters for the function computeAxesAsync
    struct structAxisFunctionParameter
    {
        // in
        VsVolume* volume;
        McVec3f seedPoint;
        // out
        McVec3f axes[3];
        McVec3f center;
        VSRESULT res;
    } mAxisFunctionParameter;

public:
    /// Returns the material name used for "LeftVentricle".
    static const char* nameLeftVentricle(); // LOCAL_GET

    /// Returns the material name used for "Myocardium".
    static const char* nameMyocardium(); // LOCAL_GET

    static VSRESULT getAverageIntensity(VsData* data, const McVec3i& iSeed,
        float& result, int dx=2, int dy=2, int dz=1); // FORBIDDEN_ON_CLIENT

    static VSRESULT getAutoThreshold(VsVolume* volume, const McVec3f& pos,
        float& threshold); // FORBIDDEN_ON_CLIENT

    // call the Axync function as a sync call, because we need a result about if the server already runs the Axes computation
    VSRESULT computeAxesAsync(VsVolume * inVolume, const McVec3f & inSeedPoint, VsTaskControl * inTaskControl); // VS_SYNC_CALL

    VSRESULT computeAxes(VsTaskControl* progress=0); // FORBIDDEN_ON_CLIENT

    bool    isAxisComputed();   // VS_SYNC_CALL
    McVec3f getAxisCenter();    // VS_SYNC_CALL
    McVec3f getAxis(int inDim); // VS_SYNC_CALL

    void touchSegmentation(int iVolume); // VS_RELAY

    // call the Axync function as a sync call, because we need a result about if the server already runs the Segmentation
    VSRESULT computeSegmentationAsync(VsTaskControl* taskControl); // VS_SYNC_CALL

    VSRESULT computeSegmentation(VsTaskControl* progress=0); // FORBIDDEN_ON_CLIENT


    int numVolumes() const; // LOCAL_GET

    void setNumVolumes(int numTimeSteps); // VS_RELAY

    VSRESULT setVolume(int iTimeStep, const McVec3f& center, const McVec3f& longAxis, const McVec3f& shortAxis, VsVolume* volume); // VS_RELAY

    VSRESULT getVolume(int iTimeStep, McVec3f& center, McVec3f& longAxis, McVec3f& shortAxis, VsVolume*& volume); // VS_RELAY

    void setThreshold(int iTimeStep, float threshold); // VS_RELAY

    float threshold(int iTimeStep) const; // LOCAL_GET

    // call the Axync function as a sync call, because we need a result about if the server already runs the Analysis
    VSRESULT computeAnalysisAsync(VsTaskControl* taskControl); // VS_SYNC_CALL
    
    VSRESULT computeAnalysis(VsTaskControl* progress=0); // FORBIDDEN_ON_CLIENT

    //////////////////////////////////////////////////////////////////////
    // BEGIN
    // Functions for saving the results to the client
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    // For now it is only used in the function computeAnalysis()

    /**
        /param[in] inCountOfVulumes is the number of vlumes, which should
                   be initializied befor using the "set" functions below.
    */
    void setResultSize(int inCountOfVulumes); // VS_RELAY

    void setGlobalVolume(int inTimeStep, float & inResult); // VS_RELAY

    /**
        /param[in] inNumberOfResult has to be the value 16
    */
    void setVolumePerSegment(int inTimeStep, int inNumberOfResult, float * inResult); // VS_RELAY

    /**
        /param[in] inNumberOfResult has to be the value 16
    */
    void setDistancePerSegment(int inTimeStep, int inNumberOfResult, float * inResult); // VS_RELAY

    /**
        /param[in] inSegment has the range [0,15]
    */
    void setWallDistancePerSegment(int inTimeStep, int inSegment, McDArray<float> & inWallDistancePerSegment); // VS_RELAY

    void setWallThicknessPerSegment(int inTimeStep, int inSegment, McDArray<float> & inWallThicknessPerSegment); // VS_RELAY

    //////////////////////////////////////////////////////////////////////
    // Functions for saving the results to the client
    // END
    //////////////////////////////////////////////////////////////////////

    VSRESULT getGlobalVolume(int iTimeStep, float& result); // LOCAL_GET

    VSRESULT getVolumePerSegment(int iTimeStep, float result[16]); // LOCAL_GET

    VSRESULT getDistancePerSegment(int iTimeStep, float result[16]); // LOCAL_GET

    VSRESULT getWallDistancePerSegment(int iTimeStep, McDArray<float> wallDistancePerSegment[16]); // LOCAL_GET

    VSRESULT getWallThicknessPerSegment(int iTimeStep, McDArray<float> wallThicknessPerSegment[16]); // LOCAL_GET

    void setZoneResolution( int resPhi,  int resRad); // VS_RELAY

    void getZoneResolution( int& resPhi, int& resRad); // LOCAL_GET

    void clear();

protected:

    int mResPhi;
    int mResRad;

    struct Result {
        float globalVolume;
        float volumePerSegment[16];
        float distancePerSegment[16];
        float thicknessPerSegment[16];
        McDArray<float> wallDistancePerSegment[16]; // each N*M entries
        McDArray<float> wallThicknessPerSegment[16]; // each N*M entries
    };

    struct Input {
        float threshold;
        McVec3f center;
        McVec3f longAxis;
        McVec3f shortAxis;
        VsVolume* volume;
    };

    McDArray<Result> mResults;
    McDArray<Input> mInput;
    VsBackgroundWorker mWorker;
};

const static int lv_countOfSegments = VsCardiacAnalysis::APICAL_LATERAL + 1;

#endif


/// @}
