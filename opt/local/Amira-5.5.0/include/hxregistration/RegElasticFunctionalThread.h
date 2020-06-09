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
#ifndef REG_ELASTICFUNCTIONALTHREAD
#define REG_ELASTICFUNCTIONALTHREAD


#include <hxcore/HxThread.h>
#include <hxfield/HxFieldEvaluator.h>
#include <hxfield/HxLoc3Regular.h>
#include <hxregistration/RegElasticFunctional.h>


/// Functional thread.
class RegElasticFunctionalThread : public HxThread
{
public:
    RegElasticFunctionalThread(RegElasticFunctional *ma, short nr, 
    float *sV, HxFieldEvaluator* eM, HxLocation3* lo, McPrimType pt, void *pR, int *rd, 
       McDArray<McVec3f> *lm, int nlm, float lmw);
        

    void init(McDVector<double> pV, double *gr, double st, int un, double cu, mclong sa, float *gec, float *jcc,
        int *mev, McVec3f *tp, double ge, double jc, float gew, float jcw);

    
    virtual ~RegElasticFunctionalThread() 
	{
		if (incrementalMetric)
			delete incrementalMetric;

        if ( TransformedPoints_VOI )
            mcfree( TransformedPoints_VOI );

        if ( regularizationMode != REG_NO_CONSTRAINTS )     
            if ( TransformedPoints )
                mcfree( TransformedPoints );

        if (JacobianX)
            mcfree( JacobianX );
        if (JacobianY)
            mcfree( JacobianY );
        if (JacobianZ)
            mcfree( JacobianZ );
        if (HessianX)
            mcfree( HessianX );
        if (HessianY)
            mcfree( HessianY );
        if (HessianZ)
            mcfree( HessianZ );
        if (MixedXY)
            mcfree( MixedXY );
        if (MixedXZ)
            mcfree( MixedXZ );
        if (MixedYZ)
            mcfree( MixedYZ );
        
        if (delta_plane)
            mcfree(delta_plane);    
        if (delta_line)
            mcfree(delta_line);   
    }
    

    double getWeightedResult( double metric );

    
private:
    ///In case of multithreaded implementation, do the incremental evaluation here.
    virtual void run ();
    
    double evaluateLandmarks() ;

    /// Re-evaluate functional after change in subvolume VolumeOfInfluence[idx] 
    double evaluateIncremental( int idx, float delta = 0 );

	double evaluateIncrementalWithRegularizer ( int idx );

	RegMetric* incrementalMetric;

    ///Controls the threads.
    RegElasticFunctional* master;
    
    short threadNr;
    
    ///Stores result of evaluateAndCache(). Needed by threads.
    double CurrentMetricResult;
    
    ///The gradient vector to be filled by the threads.
    double* Gradient;
    
    ///Needed for threads.
    float Step;
    
    ///Needed for threads.
    int Unconstrained;
    
    ///Every Thread needs its own parameter vector.
    McDVector<double> paramVector;

    McVec3f *TransformedPoints;

    /** Stores jacobian constraint which was computed for each voxel
    * before startig to approximate gradient numerically. */
    float *JacobianConstraintsCache;

    /** Stores grid energy which was computed for each voxel
    * before startig to approximate gradient numerically. */
    float *GridEnergyCache;

    McDArray<McVec3f> *landmarks;
   
    int nLandmarks;

    float landmarkWeight;

    int *MaxExtentVOI;

    McVec3f *TransformedPoints_VOI;
    
    ///line vectors of the jacobian matrix for one x-row 
    McVec3d *JacobianX, *JacobianY, *JacobianZ;

    ///2nd derivatives needed for grid energy
    McVec3d *HessianX, *HessianY, *HessianZ;

    ///mixed derivatives needed for grid energy
    McVec3d *MixedXY, *MixedXZ, *MixedYZ;    

    ///In order to make calls to getTransformedGridIncremental(..) thread safe, caller must provide data structures.
    float *delta_plane, *delta_line;    

    float JacobianConstraintWeight;

    double _jacobianConstraint;

    double _gridEnergy;

    mclong _samples;
    
    float GridEnergyWeight;
    
    ///Tells if we have constraints.
    int regularizationMode;

    ///Needs to be casted to proper data type.
    void* pRef;

    ///Primitive data type of reference[0].
    McPrimType myPrimType;
    
    ///Every Thread needs its own step vector.
    float *StepScaleVector;

    ///Performs interpolation
    HxFieldEvaluator* evalMod;
    
    ///Needed for interpolation
    HxLocation3* locMod;
    
    int *referenceDims;
};

#endif



/// @}
