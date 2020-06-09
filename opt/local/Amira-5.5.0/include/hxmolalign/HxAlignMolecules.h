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

/// @addtogroup hxmolalign hxmolalign
/// @{
#ifndef HX_ALIGNPSEUDOMOLECULES
#define HX_ALIGNPSEUDOMOLECULES

#include <hxmolalign/HxMolAlignWinDLLApi.h>

#include <mclib/McHandle.h>

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortRadioBox.h>

class HxMolecule;

/// 
class HXMOLALIGN_API HxAlignMolecules : public HxCompModule {
    
    HX_HEADER(HxAlignMolecules);

public:
    /// Constructor.
    HxAlignMolecules();

    /// Compute method.
    virtual void compute();

    /// Update method.
    virtual void update();

    /// Optional second input
    HxConnection portInputB;

    /// Optional slave object
    HxConnection portSlave;

    /// 
    HxPortRadioBox portMode;

    ///
    HxPortToggleList portOptions;
    
    /// 
    HxPortIntSlider portTransforms;

    ///
    HxPortMultiMenu portAlignLevel;
    
    ///
    HxPortSeparator portSeparator;
    
    ///
    HxPortButtonList  portCustomAlignLevel;
    
    /// Do it button.
    HxPortDoIt portAction;

    
    /// Tcl command interface
    int parse(Tcl_Interp* t, int argc, char **argv);

    void savePorts(FILE* fp);

protected:
    ///
    virtual ~HxAlignMolecules();
    
    ///
    int optimize(SbMatrix &transf, int tId=-1);

    ///
    void applyStep(const SbMatrix &delta);
    ///
    int getNextStep(int step, SbMatrix &delta);
    ///
    bool initialize();
    ///
    void computeRealCogB(McVec3f &cogB);
    ///
    void computeTransformedPositions();
    ///
    void setStartPos(int currentStep, McVec3f &rCogB);
    ///
    void setStartTransform(int sourceVert[4], McVec3f &rCogB);
        
    void printDistance(int tId);
    
    void align();

    bool upToDate;
    
    ///
    McDArray<McDArray<McVec3f> >  positionsA;
    
    ///
    McDArray<McDArray<McVec3f> >  positionsB;

    ///
    McDArray<McDArray<int> > atomIdsA;
    McDArray<McDArray<int> > atomIdsB;
    
    ///
    McDArray<McDArray<float> >  weightA;
    
    ///
    McDArray<McDArray<float> >  weightB;
    
    ///
    McVec3f cogA, cogB;

    ///
    float wSumB;

    ///
    McVec3f oldAmom;

    /// 
    float globForce;
    
    /// 
    McDArray<SbMatrix> transf;

    /// 
    McDArray<float> dist;

    /// 
    float epsilon;
    /// Number of starting positions
    int nTrials;

    ///
    float bbDiag;

    int stopWorking;
    int verbose;

    McHandle<HxMolecule> inputB, inputA;

    McHandle<HxSpatialData> slave;

    ///
    McDArray<int> levelMapA;
    
    ///
    McDArray<int> levelMapB;
    
};

#endif

/// @}
