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
#ifndef REG_SPLINE_TRANSFORM
#define REG_SPLINE_TRANSFORM

#include <mclib/McBox3f.h>
#include <mclib/McBox3i.h>
#include <mclib/McDArray3D.h>
#include <mclib/McVec3d.h>
#include <mclib/McVec3f.h>
#include <hxfield/HxLattice3.h>
#include <hxfield/HxRegScalarField3.h>
#include <hxfield/HxRegVectorField3.h>
#include <hxlandmark/HxLandmarkSet.h>
#include <hxregistration/RegParametricTransform.h>
#include <hxregistration/hxregistrationAPI.h>




class HxElasticRegistration;

/// RegParametricTransform subclass for spline transforms.
class HXREGISTRATION_API RegSplineTransform : public RegParametricTransform
{
public:
    RegSplineTransform(int imgDim, bool fastMode);
    
    virtual ~RegSplineTransform();
        
    ///Apply inverse affine transform of the model to the control grid.
    void applyModelTransformInv();
    
    ///Apply affine transform of the model to the control grid.
    void applyModelTransform();

    ///Apply inverse affine transform of the model to the control grid.
    virtual void applyModelTransformInv(McDVector<double> &pV);
    
    ///Apply affine transform of the model to the control grid.
    virtual void applyModelTransform(McDVector<double> &pV);

    ///Needs to be called when deformation is to be reconstructed later (HxApplyBSplineTransform).
    inline void setInterpolatedSpaceBoundary(float bbox[6]) 
    {        
        InterpolatedSpaceBoundary.setValue(bbox[0], bbox[1], bbox[2], bbox[3], bbox[4], bbox[5]);
    }

    inline void resetInterpolatedSpaceBoundary() 
    {        
        InterpolatedSpaceBoundary.makeEmpty();
    }    

    ///Is called during creation of functionals in order to find max. image volume
    void updateInterpolatedSpaceBoundary( McBox3f &bbox );
    
    ///Correct boundaries for initial grid position: make it alittle bit bigger
    void correctInterpolatedSpaceBoundary(float correction[3]);
    
    virtual void setReference( HxSpatialData *reference );

    virtual void setModel( HxSpatialData *model );  
    
    void setControlGridSize( int x, int y, int z );
    
    //Get step size (discretization) for approximating the gradient numerically.
    virtual double getParamStep ( int idx, SbVec3d *vol = NULL );
    
    /// Regularize (smooth) transformation ^= gauss filter on grid.
    /// Changes only the fixed points.
    void smoothGrid( const float weight0 = 2, const float weight1 = 1);
    
    void setControlPoints( HxLandmarkSet *points );
    
	/// The standard representation of a B-spline transform is a vector field.
	/// This method sets the control grid (params, gridSize, interpolatedSpace, spacing)
	/// via a predefined vector field. No interpolation coefficents are determined!  
	void setControlPoints( HxRegVectorField3* vecField);

	/// Returns a vector field representing the spline transform.
	HxRegVectorField3* getControlPoints();

    ///Needed for fixing old control points.
    void setNewControlPoints();
    
    ///Needed for fixing old control points.
    void setAllControlPointsNew();
    
    ///Needed for fixing control points when there VOI is of low entropy
    void setControlPointActive();
    
    ///Needed for fixing control points when there VOI is of low entropy
    void setControlPointInactive( int ctrl );
    

    ///Computes new positions of one transformed point
    void getTransformedGrid( int *pos, McVec3f &point ) {
        this->getTransformedGrid( pos, point, paramVector );
    }
    
    ///Computes new positions of one transformed point
    virtual void getTransformedGrid( int *pos, McVec3f &point, McDVector<double> &pV ) = 0;
    


    virtual void getTransformedGridSequence ( McVec3f *v, McVec3d *d2x, McVec3d *d2y,
        McVec3d *d2z, McVec3d *dxy, McVec3d *dxz, McVec3d *dyz, McVec3d *jacobianX, 
		McVec3d *jacobianY, McVec3d *jacobianZ, const int numPoints, int *pos ){} ;

    virtual void getTransformedGridSequence ( McVec3f *v, McVec3d *d2x, McVec3d *d2y, McVec3d *d2z,
        McVec3d *dxy, McVec3d *dxz, McVec3d *dyz, McVec3d *jacobianX, 
		McVec3d *jacobianY, McVec3d *jacobianZ, const int numPoints, int *pos, McDVector<double> &pV ){};
    
    ///Computes new positions of transformed voxels for the whole image
    virtual void getTransformedGridComplete ( McVec3f *v, McVec3f *conv_x, McVec3f *conv_y ) {};
        


    /**Must return full size of paramVector here, because inactive parameters 
    * are NOT necessessarily located at the end!*/
    virtual int  getVariableParamVectorDim() {  return paramVector.size(); }
    
    virtual int getParamVectorDim () {  return paramVector.size(); }
    
    ///Different warps use different spacings
    virtual void getGridSpacing() = 0;

    McVec3f * getInverseGridSpacing() {return &InverseGridSpacing;}
    
    virtual void getVolumeOfInfluence ( int idx, float *fromVol, float *toVol, int fastMode=-1 ) = 0;
    
    virtual HxLandmarkSet *createControlPoints(HxLandmarkSet *controlPoints = NULL);
    
	/// Refines control grid and coefficients. Additionally new interpolants are 
	/// are precomputed.
    void refine ( const int factor = 2 );
    
	/// Refines control grid and coefficients like refine(), but NO interpolants 
	/// are precomputed.
	virtual void refineNoInterpolants (const int factor = 2) = 0;

    /// Precompute the spline polynomials  
    virtual void precomputeInterpolants() = 0;
    
    void update();

    ///Control grid representation.
    HxLandmarkSet *ControlPoints;  
    
    ///The dimensions of the control grid.
    McVec3i cpgDim;
    
    /**@name Precomputed grid indices, interpolation coefficients
    * @param g Holds the precomputed grid index of the deformed grid's
    * voxel with respect to the control point grid of this deformation.
    * @param f Holds the relative position (range 0..1) of the deformed
    * grid's element with respect to the control point cells of this 
    * deformation. These values are required for fast computation of the
    * interpolated deformation at the deformed grid's nodes.
    */
    struct TCoeff
    {
        int g;
        float f;
    };
    
    ///Needed for fixing old control points.
    bool *ControlPointNew;
    
    friend class HxElasticRegistration;
    
    ///Affine trafo of model can be considerered in the registration.
    bool modelHasTrafo;
        
    ///Boundary of the space which can be inetrpolated by the control grid.
    McBox3f InterpolatedSpaceBoundary;

    McVec3f GridSpacing;
 
    ///Affine trafo of model
    SbMatrix transMatrix;

 
protected:   
	/// Dimension of images (2==2D, 3==3D).
	int imgDim;

    ///Affine trafo of model
    float transMatrix00, transMatrix01, transMatrix02, transMatrix03;
    float transMatrix10, transMatrix11, transMatrix12, transMatrix13;
    float transMatrix20, transMatrix21, transMatrix22, transMatrix23;
    float transMatrix30, transMatrix31, transMatrix32, transMatrix33;
    
    ///Inverse affine trafo of model
    SbMatrix transMatrixInv;
    float transMatrixInv00, transMatrixInv01, transMatrixInv02, transMatrixInv03;
    float transMatrixInv10, transMatrixInv11, transMatrixInv12, transMatrixInv13;
    float transMatrixInv20, transMatrixInv21, transMatrixInv22, transMatrixInv23;
    float transMatrixInv30, transMatrixInv31, transMatrixInv32, transMatrixInv33;
    
    ///Serves as a backup, recomputation of original in case model has a transform paramVector is not needed.
    McDVector<double> paramVector_beforeTransform;

    ///Flag which tells if the corect order of calls to applyModelTransformInv and applyModelTransform is followed.
    bool paramVectorWasTransformed;

    void controlPoints2Params();
    
    void params2ControlPoints();
    
    McVec3f InverseGridSpacing;
    
    ///Needed for fixing control points when there VOI is of low entropy
    bool *ControlPointActive;  
    
    /// Offset of next control grid column.
    int nextI;
    
    /// Offset of next control grid row.
    int nextJ;
    
    /// Offset for next row and column.
    int nextIJ;
    
    /// Offset for next plane.
    int nextK;
    
    /// Offset for next plane and column.
    int nextIK;
    
    /// Offset for next plane and row.
    int nextJK;
    
    /// Offset for next plane, row, and column.
    int nextIJK;
   
     ///This member might be useless. Subclasses cast it to HxRegScalarField3, e.g.
    HxSpatialData *Reference;
   
    /// Only transformations of the model are of interest: does not depend on resolution level.
    HxSpatialData *Model;
    
    /// Flag for fast but inaccurate computation.
    bool FastMode;

  };

#endif	

/// @}
