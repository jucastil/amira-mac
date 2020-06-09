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
#ifndef HX_DECONVSTEPPER
#define HX_DECONVSTEPPER

#ifdef USE_COMPLIB
    #include <algo.h>
    #include <fft.h>
#else
    #ifdef THREADS
        #include <fftw_threads.h>
        #include <rfftw_threads.h>
    #else
        #include <fftw.h>
        #include <rfftw.h>
    #endif
#endif

#include <hxfield/HxUniformScalarField3.h>

typedef float Real;

// #define dbgprintf theMsg->printf
#define dbgprintf(a,b)

enum RegMethod { REGULARIZE_NONE=0, REGULARIZE_INTEN=1, REGULARIZE_GOODS=1};

class HxDeconvStepper
{
public:
    HxDeconvStepper();
    virtual ~HxDeconvStepper();

    void setNumThreads(int howMany);
    int getNumThreads() const { return numThreads; }

    virtual bool init(HxRegScalarField3* fieldData, HxRegScalarField3* fieldKern, int * BorderWidth, float BackgroundVal);
    virtual void updateRegularization(enum RegMethod RegularizationMethod,float PenaltyWeight,
                                      float relSamplingX, float relSamplingY, float relSamplingZ);
    virtual void InitialConst();
    virtual void InitialCopy(HxLattice3* latData, double scale);
    virtual void loadKernel(HxLattice3* latKernel);
    virtual double copyEstimateIntoResult(HxLattice3* latKernel, float scale, bool CopyKernel=false);

    virtual void finalize();
    virtual void prepareForDeconv()=0;  // will compute Fourier-transforms and so on
    virtual float DoStep(float & alpha, int StepNr, int nSteps)=0;  // will perform a deconvolution step

    virtual bool sameSize(const int* latticeDims);

    double Integral(Real * a = 0);

    Real* memKernel;  // can be acessed from outside to be filled with data
    Real* memLambda;
    void computeKernelTransform(bool forward=true);

protected:
    static const double EPSILON;

    int numThreads; // number of threads to be used

    void divideIntoData(Real* dst, Real* src, Real BackgroundValue);
    void setBorderRegion(Real* mem);
    void ExchangeArrays(Real * & A, Real * & B);
    void multiplyComplexReverse(Real* a, Real* b, Real factor);
    void multiplyComplex(Real* a, Real* b, Real* c, Real factor);
    void multiplyComplex(Real* a, Real* b, Real factor);
    double computeKernelCopy (Real* dst, HxLattice3* latKernel,const int * dimsKern,
        const int * dimsPhys, const int * dimsMath);

    int fftInit();
    void fftForward(Real*);
    void fftBackward(Real*);
    void fftFree();
    float fftcompensate;  // a factor compensating for a single fft with dimPhys sizes

    HxRegScalarField3* fieldData;   // init will fill in the data and lattice
    HxRegScalarField3* fieldKern;
    HxRegScalarField3* fieldRes;
    HxRegScalarField3* fieldResPSF;
    HxLattice3* latData;
    HxLattice3* latKern;
    float BackgroundValue;  // stores the background-value, needed in the deconvolution
    const int* dimsData;
    const int* dimsKern;
    int BorderWidth[3];
    int dimsMath[3];  // dimensions including border, but not FFT-extra sizes
    int dimsPhys[3];  // dimensions including borders and FFT-extra sizes
    int nBytes ;      // Number of BYTES as calculated from Phs sizes

    void debugData(Real* data, char * name);
};

#endif

/// @}
