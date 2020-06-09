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
#ifndef REG_ELASTICFUNCTIONALREGULAR_THREAD
#define REG_ELASTICFUNCTIONALREGULAR_THREAD


#include <hxcore/HxThread.h>
#include <hxregistration/RegElasticFunctionalRegular.h>

/// Functional thread.
class RegElasticFunctionalRegularThread : public HxThread
{
public:
	
    RegElasticFunctionalRegularThread(RegElasticFunctionalRegular *ma, short nr, 
    float *sV, McPrimType pt, void *pR, void *pM, float *bb, unsigned char ex, 
    int *rd, int *md, int *voi, RegSplineTransform* xf, float &fx, float &fy, float &fz, 
       McDArray<McVec3f> *lm, int nlm, float lmw);

    /** Only jacobianX and jacobianY have to be passed, since storage of convoluted
	results is possible in 2D only (same for hessian/ mixed).*/
    void init(McDVector<double> pV, double *gr, double &st, int &un, double &cu, 
    mclong sa, float *wv, float *gec, float *jcc, int *mev, McVec3f *tp, 
    double ge, double jc, float gew, float jcw, McVec3d* jacobianX, McVec3d* jacobianY,
	McVec3d* hessianX, McVec3d* hessianY, McVec3d* mixedXY) ;


	virtual ~RegElasticFunctionalRegularThread() 
	{
		if (incrementalMetric)
			delete incrementalMetric;

		if ( regularizationMode != REG_NO_CONSTRAINTS && !twoD)    
		{
			if ( TransformedPoints )
				mcfree(( TransformedPoints ) );
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
		}

		if ( TransformedPoints_VOI )
			mcfree( TransformedPoints_VOI );

		if (HessianX_VOI)
			mcfree( HessianX_VOI );
		if (HessianY_VOI)
			mcfree( HessianY_VOI );
		if (MixedXY_VOI)
			mcfree( MixedXY_VOI );
		if (JacobianX_VOI)
			mcfree( JacobianX_VOI );
		if (JacobianY_VOI)
			mcfree( JacobianY_VOI );	 

		if (delta_plane)
			mcfree(delta_plane);     
		if (delta_d1x_plane)
			mcfree(delta_d1x_plane);
		if (delta_d1y_plane)
			mcfree(delta_d1y_plane);
		if (delta_d2x_plane)
			mcfree(delta_d2x_plane);
		if (delta_d2y_plane)
			mcfree(delta_d2y_plane);
		if (delta_d1x_d1y_plane)
			mcfree(delta_d1x_d1y_plane);
		if (delta_line)
			mcfree(delta_line); 
		if (delta_d1_line)
			mcfree(delta_d1_line); 
		if (delta_d2_line)
			mcfree(delta_d2_line);   
	}

    
    
    double getWeightedResult( double metric );

    
private:
    ///In case of multithreaded implementation, do the incremental evaluation here.
    virtual void run ();

    double evaluateLandmarks() ;

    double evaluateIncremental( int idx, float delta);

    double evaluateIncrementalWithRegularizer ( int idx, float delta);
    
	RegMetric* incrementalMetric;

	bool twoD;

    ///Controls the threads.
    RegElasticFunctionalRegular* master;
    
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

    ///Needs to be casted to proper data type.
    void* pRef;

    ///Needs to be casted to proper data type.
    void *pMod;

    ///Primitive data type of reference[0].
    McPrimType myPrimType;
    
    ///Every Thread needs its own step vector.
    float *StepScaleVector;

    int *VolumeOfInfluence;

    float *WarpedVolume;
    
    /** Stores jacobian constraint which was computed for each voxel
    * before startig to approximate gradient numerically. */
    float *JacobianConstraintsCache;

    /** Stores grid energy which was computed for each voxel
    * before startig to approximate gradient numerically. */
    float *GridEnergyCache;

    McDArray<McVec3f> *landmarks;
   
    int nLandmarks;

    float landmarkWeight;

    McVec3f *TransformedPoints;

    int *MaxExtentVOI;

    McVec3f *TransformedPoints_VOI;
    
    ///line vectors of the jacobian matrix for one x-row 
    McVec3d *JacobianX, *JacobianY, *JacobianZ;

	/// For 2D only
	McVec3d *JacobianX_VOI, *JacobianY_VOI;

    ///2nd derivatives needed for grid energy
    McVec3d *HessianX, *HessianY, *HessianZ;

    ///mixed derivatives needed for grid energy
    McVec3d *MixedXY, *MixedXZ, *MixedYZ;

	/// For 2D only
	McVec3d *HessianX_VOI, *HessianY_VOI, *MixedXY_VOI;

    ///In order to make calls to getTransformedGridIncremental(..) thread safe, caller must provide data structures.
    float *delta_plane, *delta_line;

	///For jacobian
	float *delta_d1x_plane, *delta_d1y_plane, *delta_d1_line;
	///For grid energy
	float *delta_d2x_plane, *delta_d2y_plane, *delta_d2_line, *delta_d1x_d1y_plane;

    RegSplineTransform* Xform;

    ///For Mean Squared Difference calculation.
    mclong _samples;

    float JacobianConstraintWeight;

    double _jacobianConstraint;

    double _gridEnergy;
    
    float GridEnergyWeight;
    
    ///Tells if we have constraints.
    int regularizationMode;

    ///For loc/ eval substitution.
    float *BBoxMod;

    int *referenceDims;

    int *modelDims;
    
    //For CREATE_LOCATION    
    unsigned char extent;

    float fx, fy, fz;

};

#endif



/// @}
