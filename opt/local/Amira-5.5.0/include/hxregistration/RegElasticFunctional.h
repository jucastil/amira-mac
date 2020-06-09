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
#ifndef REG_ELASTICFUNCTIONAL
#define REG_ELASTICFUNCTIONAL

#include <mclib/McMalloc.h>
#include <mclib/McVec3d.h>
#include <mclib/McPrimType.h>
#include <hxregistration/RegFunctional.h>
#include <hxregistration/RegSplineTransform.h>
#include <hxregistration/RegVoxelEvaluator.h>
#include <hxregistration/hxregistrationAPI.h>


//#define TEST_CONSTRAINTS

#ifdef TEST_CONSTRAINTS
#include <hxregistration/HxBestDirectionOptimizer.h>
#endif



class RegElasticFunctionalThread;
class RegElasticFunctionalRegularThread;

/// Functional subclass. It is used for stacked 3D data, only.
class HXREGISTRATION_API RegElasticFunctional : public RegFunctional 
{
public:
    RegElasticFunctional(const McDArray<HxSpatialData*> &r, McDArray<HxSpatialData*> &m, 
        RegInterpolator i, RegParametricTransform *t,RegMetric *me, RegOptimizerCallback* cb,
        RegDataClass dM, HxLandmarkSet* lm = NULL, bool fP=false );

    virtual ~RegElasticFunctional();
   
    /// Return weighted combination of similarity and landmarks distance.
    virtual double getWeightedResult( double metric) const;

    /// Like evaluate(), but remember transformed and interpolated values from model
    virtual double evaluateAndCache();

	virtual double evaluateAndCacheWithRegularizer();
    
    /// Re-evaluate functional after change in subvolume VolumeOfInfluence[idx] 
    virtual double evaluateIncremental( int idx, float delta = 0 );

	virtual double evaluateIncrementalWithRegularizer ( int idx );
    
    /// Evaluate functional for the complete volume and return gradient
    virtual double evaluate( McDVector<double> &gradient, double step, int unconstrained=0 );
    
    /// Evaluate functional for the complete volume
    virtual double evaluate();

	virtual double evaluateWithRegularizer();

    ///Is needed by HxElasticRegistration to create result in current resolution level
    HxRegScalarField3 *getModel() {return dynamic_cast<HxRegScalarField3 *>(model[0]);}
    
    ///Is needed by HxElasticregistration to create result in current resolution level
    McDArray<HxSpatialData*> getReference() {return reference;}
    
#ifdef REG_USE_HX_OPTIMIZE
    bool getAdaptiveFixParameters() {return AdaptiveFixParameters;}
    
    int getGridRegularization() {return GridRegularization;}

    ///Needed for prolongation/ restriction. 
    int getRefinements() {return Refinements;}
#endif

    /// This functional uses mEval, but derived classes use their own interpolation.
    virtual void resetEval();

    /**Has to be called before actual use of functional because transform
    *object is shared by several functionals.*/
    virtual void init();
    
    void setJacobianConstraintWeight(float j) {JacobianConstraintWeight = j;}
    
    void setGridEnergyWeight(float g) {GridEnergyWeight = g;}

    void setLandmarkWeight(float l) {landmarkWeight = l;}
    
    RegSplineTransform *Xform;
    
#ifdef REG_USE_HX_OPTIMIZE
    void setRefinements(int refinements) {Refinements = refinements;}

    void setGridRegularization(int value1) {GridRegularization = value1;}
#endif

    ///Friends can be great helpers ...
    friend class RegElasticFunctionalThread;
    friend class RegElasticFunctionalRegularThread;

#ifdef TEST_CONSTRAINTS
    void setOptimizer(HxBestDirectionOptimizer * o) { optimizer = o; }
    
    double getConstraint();
    
    double getConstraintIncremental(int idx);
    
    void testDeformationConstraints ();    
#endif
    
    
     
private:
    double evaluateLandmarks() const;

#ifdef REG_USE_HX_OPTIMIZE
    /** Is passed during creation in createFunctional(..). Gives the number of
    * refinements which are supposed to having been executed when minimization on this
    * level starts. This info is needed for prolongation/ restriction.*/
    int Refinements;

    /** Tells if grid shall be regularized using gauss filter (for passive grid
    * points only).*/
    int GridRegularization;
#endif    
	
    McDArray <RegElasticFunctionalThread*> myThreads;

    McDArray <HxFieldEvaluator*> myThreadsEvals;
    
    McDArray <HxLocation3*> myThreadsLocs;


 

protected: 
	/// Needed for incremental metric calculation (local support of CPG)
	RegMetric *incrementalMetric;

	/// Flag indicating if a 2d/ 2d registration is performed
	bool twoD;

    int referenceDims[3];
    
    ///Stores the max. extent of the VOIs for the control points at current resolution level (in terms of voxels)
    int MaxExtentVOI[3];
    
    ///In order to make calls to getTransformedGridIncremental(..) thread safe, caller must provide data structures.
    float *delta_plane, *delta_line;
	///For jacobian
	float *delta_d1x_plane, *delta_d1y_plane, *delta_d1_line;
	///For grid energy
	float *delta_d2x_plane, *delta_d2y_plane, *delta_d2_line, *delta_d1x_d1y_plane;
    
	/// Stores intermediate convolution results (for exploiting separability of B-spline convolution)
    McVec3f *conv_x, *conv_y;
	McVec3d *conv_x_d1, *conv_x_d2;

    ///Determines the grey value interpolation.
    RegDataClass modelDataClass;

    virtual void createThreads();
   
    ///Determines how many threads should be used.
    int getNumberOfProcessors();
    
    short NrOfThreads;
    
    /** Update set of active and passive parameters.
    * This function computes local entropies in the neighborhood of all control
    * points of the Warp transformation. Those control points for which both
    * reference and model image have less than half the maximum entropy in
    * this neighborhood as compared to the rest of the image are set passive.
    * The passive parameters are not considered for gradient computation and
    * therefore save significant computation time.
    */
    virtual void updateFixedControlPoints();
    
    ///Update should be done only once per resolution level.
    bool WarpNeedsFixUpdate;
        
    /** Parameter scaling vector.
    * This array holds the scaling factors for all warp parameters as returned
    * by the transformation class. These factors can be used to equalized all
    * parameter modifications during gradient computation etc.
    */
    float *StepScaleVector;
    
    McVec3f *TransformedPoints;

    McVec3f *TransformedPoints_VOI;

    /**line vectors of the jacobian matrix. We use vectors instead of matrizes because of 
    * faster access with current Amira implementation (8.5 %).*/
    McVec3d *JacobianX, *JacobianY, *JacobianZ;

	/// For 2D only
	McVec3d *JacobianX_VOI, *JacobianY_VOI;

    ///2nd derivatives needed for grid energy
    McVec3d *HessianX, *HessianY, *HessianZ;

    ///mixed derivatives needed for grid energy
    McVec3d *MixedXY, *MixedXZ, *MixedYZ;

	/// For 2D only
	McVec3d *HessianX_VOI, *HessianY_VOI, *MixedXY_VOI;

    //It would be optimal regarding the run time to evaluate the jacobian together with the getTransformedGrid() call;
    //Thid is prohibited by today's main memory size (ref. image of size 256^3 with 35 control points requires 988 MB)
    //McVec3d *JacobianX_VOI, *JacobianY_VOI, *JacobianZ_VOI;

    int *VolumeOfInfluence;
    
    ///Store grey values of transformed model.
    float *WarpedVolume;

    /** Stores jacobian constraint which was computed for each voxel
    * before startig to approximate gradient numerically. */
    float *JacobianConstraintsCache;

    /** Stores grid energy which was computed for each voxel
    * before startig to approximate gradient numerically. */
    float *GridEnergyCache;

    /** Set active and passive warp parameters adaptively.
    * If this flag is set, the functional will adaptively determine active and
    * passive parameters of the warp transformation prior to gradient 
    * computation.
    */
    bool AdaptiveFixParameters;
  
    float JacobianConstraintWeight;

    double JacobianConstraint;

    double GridEnergy;
    
    float GridEnergyWeight;

    float landmarkWeight;

    HxLandmarkSet *landmarks;

    McDArray<McVec3f> *landmarksRef;

    McDArray<McVec3f> *landmarksMod;

    int nLandmarks;

    mclong samples;

    ///for saving during gradient computation.
    double _jacobianConstraint;

    double _gridEnergy;

    mclong _samples;

    ///Tells if we have constraints.
    int regularizationMode;

    ///Needs to be casted to proper data type.
    void* pRef;

    ///Needs to be casted to proper data type.
    void* pMod;

    ///Primitive data type of reference[0].
    McPrimType myPrimType;
 
    RegInterpolator interpolator;

    RegVoxelEvaluator *mEval;
      
#ifdef TEST_CONSTRAINTS
    HxBestDirectionOptimizer * optimizer;
    
    char comment[512];
#endif
};

#endif

/// @}
