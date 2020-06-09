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

/// @addtogroup hxregistration hxregistration
/// @{
#ifndef HX_VOXELREGISTRATION
#define HX_VOXELREGISTRATION

#include <mclib/McDArray.h>

#include <hxfield/HxUniformLabelField3.h>
#include <hxfield/HxStackedLabelField3.h>

#include <hxcore/HxCompModule.h>
#include <hxcore/HxMessage.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxConnection.h>

#include <hxarith/HxResample.h>

#include <hxfield/HxRegScalarField3.h>
#include <hxfield/HxLattice3.h>

#ifdef REG_USE_HX_OPTIMIZE
    #include <hxoptimize/McOptimizer.h>
    #include <hxoptimize/McMultilevelOptimizer.h>
    #include <hxregistration/RegObjFunction.h>
#endif

#include "RegFunctional.h"
#include "RegParametricTransform.h"
#include "RegAffineTransform.h"
#include "RegOptimizerCallback.h"
#include "HxOptimizer.h"
#include "RegStack.h"
#include "RegTypesAndMacros.h"
#include "hxregistrationAPI.h"

enum { METRIC_NMI = 0, METRIC_MI = 1, METRIC_EUCLIDIAN = 2, METRIC_CORRELATION = 3, METRIC_LABELDIFF = 4 };

enum { OPTIMIZER_EXTENSIVEDIRECTION = 0, OPTIMIZER_BESTNEIGHBOUR = 1,
       OPTIMIZER_NEWTON = 2, OPTIMIZER_CG = 3, OPTIMIZER_LINESEARCH = 4};

enum { OPTIONS_IGNOREFINEST = 0, OPTIONS_FIXPARAMS = 1, OPTIONS_FIXOLDPARAMS = 2 };

enum { OPTIONS_LOCALIZER = 0, OPTIONS_FASTMODE = 1 };


/** Generic multiresolution voxel-registration class. It should be noted
* that the transformations being computed are rather reverse transformations, which
* give for every voxel the location where the resulting grey value is to be taken from.
*/
class HXREGISTRATION_API HxVoxelRegistration : public HxCompModule, public RegOptimizerCallback
{

public:
    HxVoxelRegistration();
    virtual ~HxVoxelRegistration();

    /// update method
    virtual void update();

    virtual RegFunctional* createFunctional(McDArray<HxSpatialData*>  &ref,
       McDArray<HxSpatialData*> &mod, int prolongations = -1, int dataLevel = -1) = 0;

    /// compute method
    virtual void compute() = 0;

    virtual void trace(char *comment)
    {
      HxMessage::Info(comment);
    }

    /// Optimization algorithm to use.
    HxPortMultiMenu portOptimizer;

    ///For LineSearch.
    HxPortToggleList portExtensiveSearch;

    /// initial and final step size.
    HxPortFloatTextN portStep;

    /// Use gradient optimizer on finest n resolution levels.
    HxPortFloatTextN portNLevelsGradient;

    /// Biggest number of voxels to be averaged when downsampling (2x2x2).
    HxPortIntTextN portCoarsestResolution;

    /// Metric to use.
    HxPortMultiMenu portMetric;

    /// min and max grey values for reference histogram
    HxPortFloatTextN portHistogramRangeRef;

    /// min and max grey values for model histogram
    HxPortFloatTextN portHistogramRangeMod;

    /// Determining number of bins is non-trivial (especially for float data)
    HxPortIntTextN portHistogramBins;

    /// Secondary input connection to reference dataset (required)
    HxConnection portReference;

    /// Options are different for affine and elastic registration.
    HxPortToggleList portOptions;

    /// Register localizer.
    HxPortToggleList portOptions2;

    /// Show ports for extended options.
    HxPortToggleList portExtendedOptions;

    /// Align centers, align principal axes, register.
    HxPortButtonList portAction;



protected:
    virtual void createTransform() = 0;

    void calculateMaxCoverage();

#ifdef REG_USE_HX_OPTIMIZE
    virtual void createOptimizers();

    ///prolongations must be cast to McDArray< McDArray<int> > *.
    virtual int getProlongationsPerDataLevel() = 0;
#endif

    /** Do registration.
    * This function must be called to start the multiresolution optimization
    * using the specified parameters.
    */
    virtual void doRegistration();

    virtual void doResampling(void *arrayRef, McVec3i &coarsest, void *arrayMod = NULL);

    ///Sample in appropriate fashion: (box/ gauss/...)-filtered, voting etc.
    virtual void downsample(HxRegScalarField3* object, HxRegScalarField3*& nextObj, McVec3i &sampling, RegDataClass dc);

    ///get minimum distance between voxels
    void getMinDelta(McVec3d &minDelta, McVec3i &sorted, int refOrMod=0,
        int dimension=3);

        /** Get dimension.
        * dimension = 3:     3D registration
        * dimension = 0,1,2: 2D registration 'orthogonal' to 0, 1 or 2
        * return value -1 if even a 2D registration can't be done.
    */
    int getDimension(int iref=0);

    /** Initialize registration.
    * This function is called by Register before any other operations. It can
    * be overloaded to open status dialog windows, etc. Derived implementations
    * should call their base class' initRegistration first.
    */
    virtual int initRegistration () ;

    ///Method is called by sampleReference once voxel isotropy is reached.
    virtual void sampleInIsotropy(McVec3i &samplingRef, bool *sampleAgain, McVec3i &coarsest, int dimension);

    ///Sample model according to reference. Is called by sampleReference(..).
    virtual void sampleModel(McVec3i &sorted, McVec3i &samplingRef, McVec3i &samplingMod,
        McVec3d &deltaOrigRef, McVec3d &deltaMod, int dimension);

    ///Set lock to prevent compute method to be called recursively during the
    //HxData::fire() mechanism
    void setLock() { lock = 1; }

    void resetLock() { lock = 0; }

    ///lock to prevent compute method to be called recursively during the
    //HxData::fire() mechanism
    short lock;

    McDArray<HxSpatialData*> reference;

    McDArray<HxSpatialData*> model;

    double maxCoverage;

    /** mDimension = 3:     3D registration
    *   mDimension = 0,1,2: 2D registration 'orthogonal' to 0, 1 or 2
    */
    int mDimension;

    unsigned int mNumThreads;

    ///Nearest neighbour for label fields, trilinear for others
    RegInterpolator interpolator;

    RegDataClass dataClassRef;

    RegDataClass dataClassMod;

    /// Current / final transformation.
    RegParametricTransform *transform;

    ///Functional stack for resolution steps in optimization.
    RegStack<RegFunctional *> *functionalStack;

    ///Functional that is currently used for optimization
    RegFunctional *currentFunctional;

    /// Pointer to optimizer object.
    HxOptimizer *optimizer;

    /// determines how fast the sampling reaches the user defined coarsest resolution
    int sampleFactor;

    /// Factor between optimization step sizes.
    double stepFactor;

    /** Enter resolution level.
    * This function is called before entering each resolution level. It is
    * be used to get the new value for numbers of degrees of freedom and possibly
    * to do more resolution specific things.
    *@param level Index of the current resolution level. 0 is first (coarsest),
    * subsequent (finer) resolutions have increasing numbers.
    *@param total Total number of resolution levels.
    */
    virtual void enterResolution(int level, int total, RegFunctional* f = NULL){}

    virtual void doResolution(int index, int numResolutionLevels, RegFunctional* currentFunctional,
                              double initialStepSize, double finalStepSize);

    /** Finish resolution level.
    * This function is called after every resolution level. It should do any
    * necessary cleanups resulting from the previous call to EnterRegistration.
    *@return If the current level is finished, 1 is returned. Otherwise, ie.
    * if the derived class requests another run of the same level, 0 may be
    * returned. This is used for example by the affine registration in order
    * to make repeated runs of the same level with different numbers of degrees
    * of freedom. Be careful not to create any inifinite loops.
    */
    virtual int doneResolution(int level, int total) { return 1; };

    ///Cleanup
    virtual void doneRegistration();

    /** Update reference.
    *  AffineRegistration: there may be more than one reference
    *  ElasticRegistration: only one reference
    */
    virtual void updateReference();

    const int useReferenceForResampling;

    int ignoreFinestLevel;

    HxResample* sampler;

#ifdef REG_USE_HX_OPTIMIZE
    virtual void createObjFunction(RegTimer *t = NULL) {mObjFunction = new
        RegObjFunction(this, t);}

    /// objective function encapsulating RegFunctionals
    RegObjFunction* mObjFunction;

    McMultilevelOptimizer* mOptimizer;

    /**The size of mProlongations gives the number of data resolution levels.
    * Its content are parameters describing the kind of prolongations for each
    * level, e.g. for affine registrations one ore more numbers of degrees of
    * freedom. */
    McDArray< McDArray<int> > mProlongations;
#endif
};

#endif

/// @}
