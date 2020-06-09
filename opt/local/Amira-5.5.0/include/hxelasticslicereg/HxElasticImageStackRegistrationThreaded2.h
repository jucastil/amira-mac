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

/// @addtogroup hxelasticslicereg hxelasticslicereg
/// @{
#ifndef HX_ELASTICIMAGESTACKREGISTRATIONTHREADED2
#define HX_ELASTICIMAGESTACKREGISTRATIONTHREADED2

#include "HxElasticSliceRegWinDLLApi.h"
#include "ElasticImageStackRegistrationThread2.h"
#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxData.h>
#include <mclib/McDVector.h>
#include <fftw3/fftw3.h>


class HxLattice;


#define MAX_LEVELS 5
#define EPS 0.00001

class HXELASTICSLICEREG_API HxElasticImageStackRegistrationThreaded2: public HxCompModule {

    HX_HEADER(HxElasticImageStackRegistrationThreaded2);

  public:
    /** Constructor. */
    HxElasticImageStackRegistrationThreaded2();

    /** Destructor. */
    ~HxElasticImageStackRegistrationThreaded2();

    /** Update method. */
    virtual void update();

    /** Compute method. */
    virtual void compute();

    /** portDataN is used for lower resolutions of the portData data set when
     * a single 3D image stack is registered.*/
    HxConnection portData1;
    HxConnection portData2;
    HxConnection portData3;
    HxConnection portData4;

    /** Input field for material parameters lambda and mu */
    HxPortFloatTextN portMaterialParameters;

    /** Select fixed material parameters or auto-estimation */
    HxPortRadioBox portParameterMethod;

    /** Select interpolation method */
    HxPortMultiMenu portInterpolation;

    /** Maximum distance a voxel can move per iteration */
    HxPortFloatTextN portMaxStep;

    /** Number of iterations */
    HxPortIntTextN portIterations;

    /** port for setting mMaxImprovementFactor */
    HxPortFloatTextN portMaxImprovementFactor;

    /** Number of slices to use for force calculation. For improved robustness,
     * portWindowWidth().getValue() slices above and below the current slice are 
     * used. Value can be set for each resolution level separately. */
    HxPortIntTextN portWindowWidth;

    /** Weighting for slices within window */
    HxPortMultiMenu portWeighting;

    /** Using this option the influence of bad slices 
      (for which the error function is larger than the average plus 2x 
      standarddeviation) is reduced */
    HxPortToggleList portPenelizeBadSlices;

    /** Reduction factor for bad slices */
    HxPortFloatTextN portPenaltyBadSlices;

    /** Number of threads */
    HxPortIntTextN portThreads;

    /** Max. memory footprint */
    HxPortIntTextN portMaxMem;

    /** Do it button. */
    HxPortDoIt portAction;

    //HxPortFloatTextN portScale;

    /** Tcl command interface. */
    virtual int parse(Tcl_Interp * t, int argc, char **argv);

    /** performs the actual registration */
    void doIt (bool useOld=false);

    /** called by threads to get a slice number to process */
    int getTemplateSliceNum();

    const int* getDims() const { return mDims; }

    int getWindowWidth() const { return mWindowWidth; }

    float getMaxStep() const { return mMaxStep; }

   /** Get/set the length of the longest deformation vector.
    *  Used for normalization in the initialization step */
    float getTotalMaxLength() const { return mTotalMaxLength; }
    void setTotalMaxLength(const float val) { mTotalMaxLength = val; }


    /** Read image slice sliceNum from lattice lat and put it in data. 
     *  Enough space has to be allocated before calling this function. */
    void readImage(HxLattice* lat, const int sliceNum, unsigned char* data);

    /* Write data into lattice at slice sliceNum */
    void writeImage(HxMutableLattice* lat, const int sliceNum, const unsigned char* data);

    /** Read slice sliceNum of pairs of floats from lattice lat and put it in data. 
     * Enough space has to be allocated before calling this function. */
    void readDeformData(HxLattice* lat, const int sliceNum, float* data);

    /* Write 2*dims[0]*dims[1] float elements stored in data into lattice 
     * at slice sliceNum */
    void writeDeformData(HxMutableLattice* lat, const int sliceNum, const float* data);

    /** Compute the weighting factors for the neighboring wWidth slices above and
     *  the wWidth slices below slice z. The 2*wWidth values are stored after each
     *  other in w */
    void computeWeights(const int wWidth, const int z, const int maxZ, 
        McDVector<float>& w);

    /** Compute difference image diffIm for stack registration using
     *  2*windowWidth surrounding slices, weighted with weights.*/
    void computeDifferenceImageStack(const McDArray<unsigned char*>& ref, const McDVector<float>& weights, 
        const int windowWidth, const unsigned char* templ, float* diffIm);

    /** Compute the force fields */
    void computeForces(const float* diffIm, const unsigned char* templ, 
        fftwf_complex* f, fftwf_complex* g);

    /** Solves the linear system, writes the resulting deformation vectors for this
     *  step in us and vs */
    void solveLinearSystem(fftwf_complex* f, fftwf_complex* g, float* us, float* vs);

    /** Computes the maximum length of the vectors formed by the corresponding
     * components of vx and vy */
    float computeMaxVectorLength(const int xDim, const int yDim, const float* vx, const float* vy);


    bool isInitializingParams() { return mIsInitializingParams; }

    /** Adds the incremental vectors of this step to the total deformation vectors
     *  for the current level. */
    //void computeTotalDeformation(bool revert);

    /** Apply deformation vectors to the original image(s)*/
    void computeTransformedSlice(const unsigned char* image, const float* uv, unsigned char* outImage);
    void computeTransformedStack(HxMutableLattice* lat);

    void setSliceError(int z, float e) {
        mcassert (z>=0 && z <= mSliceErrors.size());
        mSliceErrors[z] = e;
    }

    /** Compute the L2 norm of two images */
    float computeError (const unsigned char* i1, const unsigned char* i2, 
        const mclong xDim, const mclong yDim);

    float computeErrorStack (HxLattice* lat);

    void updateComputeErrorProgress();
    void updateDoIterationProgress();
    void updateComputeTransformedStackProgress();

    // Counter mutexes
    HxMutex& getTemplateSliceNumberMutex() {return mTemplateSliceNumberMutex;}
    HxMutex& getTotalMaxLengthMutex() {return mTotalMaxLengthMutex;}
    HxMutex& getSliceErrorMutex() {return mSliceErrorMutex;}
    HxMutex& getRegistrationMutex() {return mRegistrationMutex;}
    HxMutex& getComputeTransformedStackMutex() {return mComputeTransformedStackMutex;}

    // Data Mutexes
    HxMutex& getInputImageDataMutex() {return mInputImageDataMutex;}
    HxMutex& getDeformDataMutex() {return mDeformDataMutex;}
    HxMutex& getTemplateDataMutex() {return mTemplateDataMutex;}
    HxMutex& getTemplateDataTmpMutex() {return mTemplateDataTmpMutex;}

    void lockMutex(HxMutex& m) {m.lock();}
    void unlockMutex(HxMutex& m) {m.unlock();}


  private:
      enum DataLocation {IN_CORE, OUT_OF_CORE};

    int mNumberOfThreads;
    McDArray<ElasticImageStackRegistrationThread2*> mRegistrationThreads;
    McDArray<ComputeErrorThread2*> mErrorThreads;
    McDArray<ComputeTransformedStackThread2*>mComputeTransformedStackThreads;

    int mNumberOfSlices;
    int mCurrentTemplateSliceNumber;

    // Counter mutexes
    HxMutex mTemplateSliceNumberMutex;
    HxMutex mTotalMaxLengthMutex;
    HxMutex mSliceErrorMutex;
    HxMutex mRegistrationMutex;
    HxMutex mComputeTransformedStackMutex;

    // Data Mutexes
    HxMutex mInputImageDataMutex;
    HxMutex mDeformDataMutex;
    HxMutex mTemplateDataMutex;
    HxMutex mTemplateDataTmpMutex;

    float *mD1, *mD2, *mD4;

    bool mIsInitializingParams;

    const int* mDims;

    fftwf_plan mPlan, mInvPlan;

    int mWindowWidth;

    float mMaxStep;
    float mTotalMaxLength;

    /** If mCurrentError/mPreviousError is above this value, the last deformation increment is reverted 
    and computations for the current level are stopped */
    float mMaxImprovementFactor;

    int mLevel;
    int mNumLevels;

    int mErrorThreadCount;
    int mRegistrationThreadCount;
    int mTotalDeformationThreadCount;
    int mComputeTransformedStackThreadCount;

    /**  2D Stencils */
    float mS1[3][3], mS2[3][3], mS3[3][3], mS4[3][3];

    /** Input Data */
    McHandle<HxLattice> origImageDataLat[MAX_LEVELS];
    McHandle<HxLattice> referenceLat;

    /** Input Data, points to in-core copy when possible */
    McHandle<HxData> inputImageData[MAX_LEVELS];
    McHandle<HxLattice> inputImageDataLat[MAX_LEVELS];

    /** Output Data */
    McHandle<HxData> templateData[MAX_LEVELS];
    McHandle<HxMutableLattice> templateDataLat[MAX_LEVELS];

    /** Deform Data */
    McHandle<HxData> deformData[MAX_LEVELS];
    McHandle<HxMutableLattice> deformDataLat[MAX_LEVELS];

    /** Output Data */
    McHandle<HxData> templateDataTmp[MAX_LEVELS];
    McHandle<HxMutableLattice> templateDataTmpLat[MAX_LEVELS];

 
    McDArray<DataLocation> origImageDataLocation;
    McDArray<DataLocation> inputImageDataLocation;
    McDArray<DataLocation> templateDataLocation;
    McDArray<DataLocation> templateDataTmpLocation;
    McDArray<DataLocation> deformDataLocation;


    float mInitialError, mPreviousError, mCurrentError;
    int mIterations, mMaxIterations;

    /** Weights for all slices */
    McDArray <float> mSliceWeights;

    McDArray <float> mSliceErrors;


    void setDataLocations();

    /** returns the number of levels of the multiresolution pyramid */
    int getNumberOfLevels();

    /** resets input ports to default values */
    void resetPorts();
    
    /** resets the displacement vector field for level level */
    void resetDeformData(const int level);

    /** computes the matrix stencils */
    void computeStencils(const float lambda, const float mu);

    /** return the 2x2 Moore-Penrose pseudo inverse matrix for a given index (i,j)
     *  in an image of size MxN */
    void getDInv(const int i, const int j, const int M, const int N, float* InvB);

    /** compute matrices with values of mD1, mD2, mD4 */
    void computeDMatrices();


    /** Creates the output lattices. One image lattice and one deform (2 element vector)
     *  lattice is created for each level. returns 1 in case of error */
    //int createOutputData();

    bool createOutOfCoreData();
    bool createInCoreImageData(const int level);
    void deleteInCoreImageData(const int level);
    bool createInCoreDeformData(const int level);
    void deleteInCoreDeformData(const int level);


    /** Copies the contents of unsigned char lattice inLat into outLat.
     *  No consistency checks are performed */
    void copyImageLattice(HxLattice* inLat, HxMutableLattice* outLat);

    /** Supersample the deformation vector grid of mLevel+1 and
     *  fill the deformation grid at level mLevel */
    void prolongateDeformData();

 
    /** Performs one iteration of the algorithm for the stack registration*/
    void doIterationStack(const bool reverse=false) ;
   
    void exchangeOutDataWithOutDataTmp(const int level);
    //int createStepDeformData();


    void writeSliceWeights(HxData* d);
    void readSliceWeights(HxData* d);
    void printSliceWeights();

};


#endif



/// @}
