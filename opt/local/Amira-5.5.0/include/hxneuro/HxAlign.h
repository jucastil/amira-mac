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

/// @addtogroup hxneuro hxneuro
/// @{
#ifndef HX_ALIGN
#define HX_ALIGN


#include <hxneuro/HxNeuroWinDLLApi.h>

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortMultiMenu.h>

#include <mclib/McMat3f.h>

#include <Inventor/SbLinear.h>

class HxField3;
class HxUniformScalarField3;

/// Uses an analytic expression to compute a new field

class HXNEURO_API HxAlign : public HxCompModule {

  HX_HEADER(HxAlign);

  public:
    /// Constructor.
    HxAlign();

    /// Compute method.
    virtual void compute();

    /// Update method.
    virtual void update();

    /// Optional second input
    HxConnection portInputB;    

    ///
    HxPortToggleList portOptions;

    ///
    HxPortMultiMenu portQualityFunc;
    enum { Q_EUCLID=0, Q_PRODUCT, Q_BINARY, Q_BINARY2, Q_CCC, Q_MUT_INF, Q_NORM_MUT_INF };

    ///
    HxPortIntSlider portThreshold;

    ///
    HxPortMultiMenu portInputAMaterial;

    ///
    HxPortMultiMenu portInputBMaterial;

    ///
    //HxPortDoIt portProgram;

    /// Start buttons.
    HxPortButtonList portAction;

    
    /// Tcl command interface
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

  protected:
    virtual ~HxAlign();
   
    ///
    SbVec3f computeCenter(HxUniformScalarField3 *inputA, int field);

    ///
    McMat3f computePrincipalAxes(HxUniformScalarField3 *inputA, 
				 SbVec3f& center, int field);

    /// 
    virtual float qualityFunc(SbMatrix delta);

    ///
    virtual void optimize(float startStep=10,int minResolution=1);

    ///
    virtual void optimizeOneStep(SbMatrix &delta, int &stop, float step);


    int n;
    float optimum;
    int resolutionLevel;
    int stopWorking;
    int verbose;
    float minStepFactor;
    bool forbiddenRotAxis[3];
    float defaultA; // default values for inputA, inputB, inputC,
    float defaultB; // if set() or move() fail

    // box enclosing the label of interest in inputA
    int lblBoxAi[6];
    float lblBoxAf[6];
    
    // Map label using this map before comparison. To ignore labels,
    // map them to NULL.
    unsigned char labelMapA[255], labelMapB[255];
    void prepareLabelMaps();
    unsigned char inputAisLabelField, inputBisLabelField;
    void buildLabelMap();

    // --------------------------------------------------------------------
    //  Variables for mutual information
    // --------------------------------------------------------------------
    mclong sampleCount;
    float baseA,scaleA;
    float baseB,scaleB;
    int numBinsA,numBinsB;
    McDArray<int> histogram2D;

    void initHistogram(HxField3* inputA, HxField3* inputB);
    float getMutualInformation();
    float getNormalisedMutualInformation();
    void getJointEntropy(float& HAB);
    void getMarginalEntropy(float& HA, float& HB);
};

#endif

/// @}
