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

/// @addtogroup hxtensor hxtensor
/// @{
#ifndef HX_EXTRACTEIGENVALUES
#define HX_EXTRACTEIGENVALUES

#include <hxcore/HxCompModule.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxThread.h>
#include <anna/AnnaExpression.h>
#include <hxfield/HxField3.h>
#include <hxfield/HxLattice3.h>
#include <hxfield/HxRegSym2TensorField3.h>
#include <hxfield/HxRegVectorField3.h>
#include <hxfield/HxRegScalarField3.h>
#include <mclib/McDMatrix.h>
#include <mclib/McDArray.h>

#include "HxTensorWinDLLApi.h"

#include <Inventor/elements/SoElements.h>
#include <Inventor/sensors/SoTimerSensor.h>
#include <time.h>

/** Class that computes the Eigenvalue decomposition from a symmetric
    tensor field given as 6 component vector (Dxx, Dxy, Dxz, Dyy, Dzy, Dzz).

    One the eigenvalues writen by this module a number of compute modules
    can be evaluated. They will generate different scalar measurements on the
    structure. */
class HXTENSOR_API HxExtractEigenvalues : public HxCompModule {

  HX_HEADER(HxExtractEigenvalues);

  public:
    /** Constructor. */
    HxExtractEigenvalues();

    /** Update method. */
    virtual void update();

    /** Compute method. */
    virtual void compute();

    HxPortToggleList portToggles;
    HxPortToggleList portOptions;
    HxConnection portMask;
    HxPortText portExpr;

    /** Do it button. */
    HxPortDoIt portAction;

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    class HxThreadedExtract : public HxThread
    {
    private:
        HxThreadedExtract(){};
    public:
        HxThreadedExtract( HxExtractEigenvalues *extr, int tN, HxRegSym2TensorField3* field, HxRegScalarField3* mask,
             HxRegVectorField3 *opca1, HxRegVectorField3 *opca2, HxRegVectorField3 *opca3, HxRegVectorField3 *oevals,
             AnnaExpression &expr, mculong start, mculong end);
         ~HxThreadedExtract();
         virtual void run();
         void computeExtract(int threadNum, HxRegSym2TensorField3* field, HxRegScalarField3* mask,
             HxRegVectorField3 *opca1, HxRegVectorField3 *opca2, HxRegVectorField3 *opca3, HxRegVectorField3 *oevals,
             AnnaExpression &expr, mculong start, mculong end);

         HxExtractEigenvalues *extract;
         HxRegSym2TensorField3* field;
         HxRegScalarField3* mask;
         HxRegVectorField3 *opca1, *opca2, *opca3;
         HxRegVectorField3 *oevals;
         AnnaExpression *mExpr;
         mculong startVal; mculong endVal;
         int threadNum; // which thread is this?
    };
    void startThreads(void *data, HxRegSym2TensorField3* field, HxRegScalarField3* mask,
        HxRegVectorField3 *opca1, HxRegVectorField3 *opca2, HxRegVectorField3 *opca3, HxRegVectorField3 *oevals,
        AnnaExpression &expr, mculong start, mculong end);
    int numParallelThreads;
    McDArray<long> progress; long end;
    HxMutex *threadmutex;
    SoTimerSensor *oneShotCallback;
    clock_t timerClock;

public:
    /** Destructor. */
    ~HxExtractEigenvalues();

    /// Check if given data object can be reconstructed.
    virtual int canCreateData(HxData* data, McString& createCmd);

    /// Save ports.
    virtual void savePorts(FILE* fp);

};

#endif

/// @}
