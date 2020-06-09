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
#ifndef REG_VOXEL_CUBIC_SPLINE_TRANSFORM
#define REG_VOXEL_CUBIC_SPLINE_TRANSFORM


#include <mclib/McMalloc.h>
#include <hxregistration/RegCubicSplineTransform.h>

#include <hxregistration/hxregistrationAPI.h>



/** B-spline-based local deformation for voxel data along with computation of 
characteristics of the transformation such as 1st, 2nd and mixed derivatives which can be used 
to compute penalty terms like grid energy, jacobian constraint or metric tensor.
*/
class HXREGISTRATION_API RegVoxelCubicSplineTransform : public RegCubicSplineTransform
{
    public:    
    RegVoxelCubicSplineTransform(int dimension, bool fastMode);

    virtual ~RegVoxelCubicSplineTransform()
    {
        if (Cx)
            mcfree(Cx);
        if (Cy)
            mcfree(Cy);
        if (Cz)
            mcfree(Cz); 
        
        if (landmarksRef) 
            delete(landmarksRef);
    }

    virtual void setReference( HxSpatialData *reference );
    
    void setLandmarks(HxLandmarkSet* landmarksRef);

     /// Get the volume which is influenced by one control point.
    virtual void getVolumeOfInfluence ( int idx, float *fromVoI, float *toVoI, int fastMode=-1 );
    
    /// Precompute the spline polynomials for every grid dimension 
    virtual void precomputeInterpolants();

    void precomputeInterpolantsLandmarks();

    void getTransformedGridLandmark( int *pos, 
        McVec3f& transformedPoint ) 
    {
        getTransformedGridLandmark( pos, transformedPoint, paramVector);
    }

    void getTransformedGridLandmark( int *pos, McVec3f& transformedPoint, McDVector<double> &pV ); 

    


/*************************************************************************************
This is the most ineffecient implementation for computation of the voxel transformation. 
It performs recomputation of all the 64 control points which interpolate one voxel.
It is left for the sake of instructiveness.
**************************************************************************************/    
    ///Computes new positions of one transformed voxel
    virtual void getTransformedGrid( int *pos, McVec3f& tpos, McDVector<double> &pV ) ;


/*************************************************************************************
This implementation for computation of the voxel transformation is a compromise
between efficiency regarding speed and storage. It avoids redundant recomputations for the yz
planes, but requires storage for only one x-line. 
Currently, it is not used durig registration.
**************************************************************************************/     

/*************************************************************************** 
Efficient implementations for computation of 1st, 2nd and mixed derivatives
which are needed for grid energy, jacobian constraint and metric tensor.
These are computed along with the voxel transformation which saves us one ore two 
extra traversals of the voxel grid.
The incremental change of the transformation during numerical approximation of the 
gradient cannot be exploited currently (like in getTransformedGridComplete()
and getTransformedGridIncremental() ), because this consumes too much main memory.
***************************************************************************/
   
    virtual void getTransformedGridSequence ( McVec3f *v, McVec3d *d2x, McVec3d *d2y,
        McVec3d *d2z, McVec3d *dxy, McVec3d *dxz, McVec3d *dyz, McVec3d *jacobianX, 
        McVec3d *jacobianY, McVec3d *jacobianZ, const int numPoints, int *pos ) ;

    virtual void getTransformedGridSequence ( McVec3f *v, McVec3d *d2x, McVec3d *d2y, McVec3d *d2z,
        McVec3d *dxy, McVec3d *dxz, McVec3d *dyz, McVec3d *jacobianX, 
        McVec3d *jacobianY, McVec3d *jacobianZ, const int numPoints, int *pos, McDVector<double> &pV );


/*************************************************************************************
This is the optimal implementation for computation of the voxel transformation. 
The incremental change of the transformation during numerical approximation of the 
gradient is completely exploited. The tradeoff is enormous consumption of main memory.
**************************************************************************************/
    ///Computes new positions of transformed voxels for the whole image
    virtual void getTransformedGridComplete ( McVec3f *v, McVec3f *conv_x, McVec3f *conv_y ) ;
    
    /** Updates new positions of transformed voxels for the VOI which i affected by moving the respective control point
    *@param delta discretization step for approximating partial derivative.
    *@param delta_line stores the deltas for each voxel in the line affected by movement of control point 
    *@param idx.
    */
    void getTransformedGridIncremental ( int idx, McVec3f *tPoint_VOI, McVec3f *tPoint, int *voi, 
        float *delta_plane, float *delta_line, float delta);

     /**Updates new positions of transformed voxels for the VOI which i affected by moving the respective control point
    *@param delta discretization step for approximating partial derivative.
    */
    void getTransformedGridIncremental ( McDVector<double> &pV, int idx, McVec3f *tPoint_VOI, McVec3f *tPoint, int *voi, 
        float *delta_plane, float *delta_line, float delta);


/*************************************************************************************
This would be the optimal implementation for computation of 1st, 2nd 
and mixed derivatives along with the voxel transformation. 
We cannot use this implementation currently, because it consumes too much main memory.
**************************************************************************************/

    void getTransformedGridCompleteWithRegularization2D ( McVec3f *conv_x, McVec3d *conv_x_d1, McVec3f *conv_y, McVec3d *conv_y_d1x, McVec3d *conv_y_d1y,
	 McVec3d *conv_x_d2, McVec3d *conv_y_d2x, McVec3d *conv_y_d2y, McVec3d *conv_y_dxdy) ;
    
    void getTransformedGridIncrementalWithRegularization2D ( int idx, 
        McVec3f *tPoint, McVec3f *tPoint_voi, 
		McVec3d *tPoint_d1x, McVec3d *tPoint_d1x_voi, McVec3d *tPoint_d1y, McVec3d *tPoint_d1y_voi,
		McVec3d *tPoint_d2x, McVec3d *tPoint_d2x_voi, McVec3d *tPoint_d2y, McVec3d *tPoint_d2y_voi,
		McVec3d *tPoint_dx_dy, McVec3d *tPoint_dx_dy_voi, int *voi, 
        float *delta_plane, float *delta_d1x_plane, float *delta_d1y_plane, float *delta_d2x_plane, float *delta_d2y_plane,
		float *delta_d1x_d1y_plane, float *delta_line, float *delta_d1_line, float *delta_d2_line, float delta );

    void getTransformedGridIncrementalWithRegularization2D ( McDVector<double> &pV, int idx, 
        McVec3f *tPoint, McVec3f *tPoint_voi, 
		McVec3d *tPoint_d1x, McVec3d *tPoint_d1x_voi, McVec3d *tPoint_d1y, McVec3d *tPoint_d1y_voi,
		McVec3d *tPoint_d2x, McVec3d *tPoint_d2x_voi, McVec3d *tPoint_d2y, McVec3d *tPoint_d2y_voi,
		McVec3d *tPoint_dx_dy, McVec3d *tPoint_dx_dy_voi, int *voi, 
        float *delta_plane, float *delta_d1x_plane, float *delta_d1y_plane, float *delta_d2x_plane, float *delta_d2y_plane,
		float *delta_d1x_d1y_plane, float *delta_line, float *delta_d1_line, float *delta_d2_line, float delta);



/*************************************************************************************
This is the most ineffecient implementation for computation of 1st derivatives. 
These methods were called AFTER traversing the whole voxel grid
for computing the voxel transformation such wasting a lot of time. 
To be removed.
**************************************************************************************/ 
     /// Return Jacobian constraint of the current transformation grid.
    double getJacobianConstraint() ;

    /// Compute sequence of Jacobian determinants from given grid location.
    void getJacobianDeterminant ( McDVector<double> &pV, McDVector<double> & values, McVec3i &pos, 
        const int numberOfPoints = 1 );
   
    


        

   
private:
    int nLandmarks;
        
    ///For every landmark its approximating spline values
    _TCoeff *Cx_Landmark, *Cy_Landmark, *Cz_Landmark;

    McDArray<McVec3f> *landmarksRef;

    
    ///Depends on resolution level because of precomputation of interpolants
    HxRegScalarField3 *ReferenceField;

    int referenceDims[3];

	/// Flag indicating if a 2d/ 2d registration is performed
	bool twoD;

    _TCoeff* Cx;
    _TCoeff* Cy;
    _TCoeff* Cz;
   
};

#endif	

/// @}
