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

/// @addtogroup hxperfusion hxperfusion
/// @{
#ifndef HXCOMPUTEPERFUSION
#define HXCOMPUTEPERFUSION

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortDoIt.h>

#include <mclib/McVec2f.h>
#include <mclib/McDMatrix.h>

#include "HxPerfusionWinDLLApi.h"

class SoEventCallback;
class HxUniformScalarField3;
class HxUniformLabelField3;
class HxSpreadSheet;

/** Class computing blood perfusion from a series of data volumes and a trace. */
class HXPERFUSION_API HxComputePerfusion : public HxCompModule {

    HX_HEADER(HxComputePerfusion);

public:
    HxComputePerfusion();
    ~HxComputePerfusion();

    virtual void update();

    /** Start the computation after pressing Apply */
    virtual void compute();

    /** Enable advanced options */
    HxPortToggleList portOptions;

    /** Sample AIF/VOF */
    HxPortButtonList portSample;

    /** Select the algorithm for computation */
    HxPortRadioBox portAlgorithm;

    /** Time between two frames in seconds */
    HxPortFloatSlider portInterFrameTime;

    /** Enable smoothing of raw data before computation */
    HxPortToggleList portSmoothing;

    /** Set the smoothing kernel size */
    HxPortIntTextN portSmoothingKernelSize;

    /** Set the smoothing kernel sigma */
    HxPortFloatTextN portSmoothingKernelSigma;

    /** Do it button. */
    HxPortDoIt portAction;

    /** Connection to point probe module for sampling function */
    HxConnection portTrace;

    /// only voxel inside the mask (>0) are used for computation
    HxConnection portMask;

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Check if given data object can be reconstructed.
    virtual int canCreateData(HxData* data, McString& createCmd);

    /// Save ports.
    virtual void savePorts(FILE* fp);
 
    /// how many phases should be used to compute the pre-contrast baseline
    HxPortIntSlider portBaseLine;
    /// limit the analysis to less phases
    HxPortIntSlider portLimitAnalysis;
    // 
    HxPortFloatSlider portDensityFactor;
    //
    HxPortFloatSlider portInHemaValueLargeVessel;
    //
    HxPortFloatSlider portInHemaRatioSmallToLargeVessel;
    //
    HxPortFloatSlider portInTikhonovDelta;
    //
    HxPortFloatSlider portSNR;

    HxPortFloatSlider portSearchRadius;

    HxPortToggleList portFilterFunctionVoxels;

    HxPortFloatSlider portMinUptakeDiff;

    HxPortFloatSlider portMaxStartValue;
private:
    struct DataPerVoxel
    {
        McDArray<float> samples;
        mclong sampleIndex;
        float uptake;
    };
    enum VesselType { ARTERY = 1, VEIN = 2};

    McDArray<float> getFunctionFromSpreadsheet(HxSpreadSheet* spreadsheet, McString columnName,
        float &minValue, float &maxValue);
    template <class T> bool updateReformat( int limitAnalysis, bool smoothing,
        McVec2i smoothingKernelSize, McVec2f smoothingKernelSigma );
    template <class T> HxUniformScalarField3* filterRawData( HxUniformScalarField3 *current, 
        McVec2i smoothingKernelSize, McVec2f smootingKernelSigma);
    template <class T> void computePerfusion(McDArray<McHandle<HxUniformScalarField3> > &reformat,
        HxUniformScalarField3* cbf,
        HxUniformScalarField3* cbv,
        HxUniformScalarField3* mtt,
        McDArray<float> &aif,
        McDArray<float> &vof,
        int inPreContrastSamples,
        HxUniformLabelField3* mask,
        float TE);
    McDMatrix<double> getRegularizedPseudoInverse(McDMatrix<double>& MP,double alpha);
    static void pickCallbackCB(void *userData, SoEventCallback* node);
    void pickCallback(SoEventCallback* node);
    // create a spreadsheet object
    void createTableOfSamples(McVec3f point, McString name);
    void plotSpreadsheet(HxSpreadSheet *spreadsheet);
    void addCallback(); // if called the callback is active (needs selected this)

    template <class T> void samplePoints(McVec3f pos, int stepsX, int stepsY, McPrimType primType, McDArray<DataPerVoxel> &dataPerVoxel, HxUniformLabelField3 *labelField, unsigned char labelValue);
    bool determineInputFunction(McVec3f point, HxSpreadSheet *spreadsheet, float &min, float &max, 
        int col0, int col1, unsigned char labelValue);

    HxUniformScalarField3 *getFirstVolume();

    // each entry is one slice through time
    McDArray<McHandle<HxUniformScalarField3> > reformat;
    // the times associated with each image
    McDArray<float> time_values;

    bool pickCallbackRegistered;
    VesselType mPickVesselType;

    bool mValidDataConnected;
    int mNumVolumes;
    bool mIsCT; // CT or MR data sets
    bool needsReformat;
    float TE; // echo time (in case of MR)
    bool mCreateLabelField;
    float mAIFMin;
    float mAIFMax;
    float mVOFMin;
    float mVOFMax;
};

#endif

/// @}
