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

/// @addtogroup hxdeconv hxdeconv
/// @{
#ifndef HX_DECONVOLUTION
#define HX_DECONVOLUTION

#include <mclib/McString.h>
#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortSeparator.h>
#include <hxfield/HxUniformScalarField3.h>
#include <hxdeconv/hxdeconvAPI.h>
#include <hxdeconv/HxDeconvStepper.h>

/** . */
class HXDECONV_API HxDeconvolution : public HxCompModule {
    
    HX_HEADER(HxDeconvolution);
    
public:
    /// Constructor.
    HxDeconvolution();
    
    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();
    
    /// Connection to kernel.
    HxConnection portKernel;
    
    /// Border width.
    HxPortIntTextN portBorderWidth;

    /// Number of iterations.
    HxPortIntSlider portNumIter;

    /// Intial estimate: 0=constant, 1=input data, 2=previous result
    HxPortRadioBox portInitialEstimate;
    enum { INIT_CONST=0, INIT_INPUT=1, INIT_PREVIOUS=2 };

    /// Overrelaxation: 0=none, 1=fixed, 2=optimized
    HxPortRadioBox portOverrelaxation;
    enum { OVER_NONE=0, OVER_FIXED=1, OVER_OPTIMIZED=2 };

    /// Regularization: 0=none, 1=Good's Roughness  (defined in HxDeconvStepper)
    HxPortRadioBox portRegularize;
    
    /// Penalty Weight
    HxPortFloatTextN portPenaltyWeight;
    enum { PENALTY_WEIGHT=0};

    /// Overrelaxation: 0=standard, 1=blind  (defined in HxDeconvStepper)
    HxPortRadioBox portMethod;
    enum { METHOD_STANDARD=0, METHOD_BLIND=1};

    HxPortSeparator portSeparate;

    /// PSF Parameters
    HxPortFloatTextN portPSFParameters;
    enum { PSF_NA=0, PSF_LAMBDA=1, PSF_N=2};

    HxPortRadioBox portMicMode;
    enum { MODE_WIDEFIELD=0, MODE_CONFOCAL=1};

    /// DoIt button.
    HxPortDoIt portDoIt;

    /// Action button.
    HxPortButtonList portAction;

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// stores the scaling, if a result was written
    double ResultScaling;
    
protected:
    /// Destructor.
    ~HxDeconvolution();
    int numThreads;
    int checkPointInterval;
    McString checkPointBaseFilename;
    bool writePSFCheckPoints;

    float relSamplingDistX,relSamplingDistY,relSamplingDistZ;  // relative sampling: data sampling / required sampling
    
    void computeInitialEstimate(HxDeconvStepper * DS);
    void loadKernel(HxDeconvStepper * DS,HxRegScalarField3* fieldKernel);

    void copyEstimateIntoResult(HxDeconvStepper * DS ,HxRegScalarField3* field, float scale=1.0);

    void checkSampling(HxRegScalarField3* field, const char * name, bool writeRel=false);  // checks, if the data was sampled appropriately
    int deconvolve(HxDeconvStepper * DS);  // If OverOptimizes, Holmes method for overrelaxation is used
    void submitBatchJob();

    virtual int canCreateData(HxData* data, McString& createCmd);
};


#endif

/// @}
