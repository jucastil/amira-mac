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
#ifndef REG_CUBIC_SPLINE_TRANSFORM
#define REG_CUBIC_SPLINE_TRANSFORM



#include <mclib/McMalloc.h>
#include <hxregistration/RegSplineTransform.h>

#include <hxregistration/hxregistrationAPI.h>
#include <hxlandmark/HxLandmarkSet.h>

/** B-spline-based local deformation. In this class, all the stuff independent
* form data type of deformed objects is represented i.e. the things related
* to the control grid only.
*/
class HXREGISTRATION_API RegCubicSplineTransform : public RegSplineTransform
{
public:    
    RegCubicSplineTransform(int imgDim, bool fastMode);
    
    virtual ~RegCubicSplineTransform()
    { }
    
    virtual HxLandmarkSet *createControlPoints(HxLandmarkSet *controlPoints = NULL);
    
    virtual void getGridSpacing();
    
    /// Refine transformation.
    virtual void refineNoInterpolants ( const int factor = 2 );
    
    virtual void setModel( HxSpatialData *model ); 
    
    /// Return bending energy of the current transformation grid.
    virtual double getGridEnergy( McDVector<double> &pV ) ;
    
    /** Return grid bending energy at one control point.
    *@param cp The control point where the bending energy is to be evaluated.
    */
    virtual double getGridEnergy( const double *cp ) ;
    
    double getGlobalScaling() {return GlobalScaling;}

    /// Compute the value of a given approximating spline function.
    static double approxSpline ( const int k, const double t ) {
        switch (k) {
        case 0: return approxSpline0( t );
        case 1: return approxSpline1( t );
        case 2: return approxSpline2( t );
        case 3: return approxSpline3( t );
        default: return 0;
        }
    }
    
    /// Compute a value of the 0th approximating spline function.
    static double approxSpline0 ( const double t ) {
        return (( (1-t) * (1-t) * (1-t) ) / 6);
    };
    
    /// Compute a value of the 1st approximating spline function.
    static double approxSpline1 ( const double t ) {
        return (( 4 + t * t * ( 3 * t - 6 ) ) / 6);
    };
    
    /// Compute a value of the 2nd approximating spline function.
    static double approxSpline2 ( const double t ) {
        return (( 1 + t * (3 + t * (3 - 3*t))) / 6);
    };
    
    /// Compute a value of the 3rd approximating spline function.
    static double approxSpline3 ( const double t ) {
        return (t*t*t/6);
    };  
    
    /// Compute the derivative of a given approximating spline function.
    static double derivApproxSpline ( const int k, const double t ) {
        switch (k) {
        case 0: return derivApproxSpline0( t );
        case 1: return derivApproxSpline1( t );
        case 2: return derivApproxSpline2( t );
        case 3: return derivApproxSpline3( t );
        default: return 0;
        }
    }
    
    /// Compute the derivative of the 0th approximating spline function.
    static double derivApproxSpline0 ( const double t ) {
        return  (-(1-t) * (1-t) / 2);
    };
    
    /// Compute derivative of the 1st approximating spline function.
    static double derivApproxSpline1 ( const double t ) {
        return (3*t*t/2-2*t);
    };
    
    /// Compute derivative of the 2nd approximating spline function.
    static double derivApproxSpline2 ( const double t ) {
        return (( 1 + 2*t - 3*t*t ) / 2);
    };
    
    /// Compute derivative of the 3rd approximating spline function.
    static double derivApproxSpline3 ( const double t ) {
        return (t*t/2);
    };  
    
    
    /// Compute the derivative of a given approximating spline function.
    static double deriv2ndApproxSpline ( const int k, const double t ) {
        switch (k) {
        case 0: return deriv2ndApproxSpline0( t );
        case 1: return deriv2ndApproxSpline1( t );
        case 2: return deriv2ndApproxSpline2( t );
        case 3: return deriv2ndApproxSpline3( t );
        default: return 0;
        }
    }
    
    /// Compute the 2nd derivative of the 0th approximating spline function.
    static double deriv2ndApproxSpline0 ( const double t ) {
        return  (-t+1);
    };
    
    /// Compute 2nd derivative of the 1st approximating spline function.
    static double deriv2ndApproxSpline1 ( const double t ) {
        return (3*t-2);
    };
    
    /// Compute 2nd derivative of the 2nd approximating spline function.
    static double deriv2ndApproxSpline2 ( const double t ) {
        return (1-3*t);
    };
    
    /// Compute 2nd derivative of the 3rd approximating spline function.
    static double deriv2ndApproxSpline3 ( const double t ) {
        return (t);
    };  
    
    
protected:
/**@name Precomputed spline coefficients, precomputed derivative spline coefficients.
* @param spline Holds the precomputed spline coefficient for deforming the
* voxel locations in the associated deformed grid.
* @param splineDerivative Holds the precomputed derivative of the spline coefficient.
* This allows for rapid evaluation of the Jacobian determinant.
    */
    struct _TCoeff : public RegSplineTransform::TCoeff
    {
        double spline[4];
        double splineDerivative[4];
        double spline2ndDerivative[4];
    };
    
    /// Precomputed global scaling of initial affine transformation.
    double GlobalScaling;
    
    /// Relative offsets of all control points in a 4 x 4 x 4 neighbourhood.
    int GridPointOffset[48];
    
    double JacobianConstraint;
    
    ///Store per voxel jacobian constraint values.
    McDVector<double> JacobianConstraintsCache;
};

#endif	

/// @}
