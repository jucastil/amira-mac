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
#ifndef REG_AFFINETRANSFORM
#define REG_AFFINETRANSFORM

#include <hxregistration/RegParametricTransform.h>
#include <hxcore/HxSpatialData.h>
#include <hxfield/HxRegScalarField3.h>
#include <hxregistration/hxregistrationAPI.h>


typedef enum {
    TRANSLATE = 0,
    ANGLES = 3,
    SCALES = 6,
    SHEARS = 9,
    CENTER = 12
} ParamFields;

/// RegParametricTransform subclass.
class HXREGISTRATION_API RegAffineTransform : public RegParametricTransform
{
    public:
    RegAffineTransform(); 

    /// Create transformation from transformations of model and reference.   
    RegAffineTransform (McDArray<HxSpatialData*> &reference, 
                        HxSpatialData *model, 
                        int degreesOfFreedom = 12 );

    void init();

    virtual ~RegAffineTransform();

    /// apply transform to model
    void apply();
    
    SbMatrixd getAmiraMatrix() { return amiraMatrix; }

    void makeIdentityTransform();

    /// Clone inverse of this transformation.
    virtual RegParametricTransform* makeInverse () ;

    /// Clone inverse of this transformation.
    RegAffineTransform* makeInverseAffine () {
       	return dynamic_cast<RegAffineTransform*>( this->makeInverse() );
    }
    
    /** Decompose homogeneous matrix into parameters.
    *@param paramVector After returning from the function, this vector holds the
    * parameters from which the given matrix can be reconstructed.
    *@see paramVector
    *@param transformMatrix The matrix to be decomposed into its defining parameters.
    *@return 1 if decomposition was successful. If matrix was singular, for
    * example, 0 is returned indicating an invalid parameter vector.
    */
    virtual int decomposeMatrix( SbMatrixd& transformMatrix, 
				 McDVector<double> &paramVector); 

    /// Compose this object's transformation matrices from parameter vector.
    void composeMatrix(); 

    RegAffineTransform* getInverse() ;
    
    void updateInverse() ;

    virtual void update();

    /** Create equivalent transformation with different rotational center.
     * In fact, this function only computes a new translation vector reflecting
     * the changed rotation center. The transformation matrix itself is not
     * changed.     */
    void changeCenter ( double* center ) ;

    /** Apply rotation, scaling, and shearing but no translation to vector.
     * This function only uses the upper left 3x3 sub-matrix of matrix to
     * transform a given vector. This is needed for rotation-center changes.
     *@param vM This three-component array holds the rotated, scaled, and
     * sheared vector after return from the function.
     *@param v The vector to be rotated, scaled, and sheared.  */
    void rotateScaleShear ( double vM[3],  double v[3] ) ;    

    /// Get dimension of parameter vector.
    virtual int getParamVectorDim () { return paramVector.size(); }
	
    /** Get dimension of variable parameter vector.
     * The rotation center is not considered variable.
     */
    virtual int getVariableParamVectorDim () { return degreesOfFreedom; }

    /// Set the number of degrees of freedom for this object.
    virtual void setDegreesOfFreedom (  int degreesOfFreedom = 12 );

    /// Get parameter stepping.
    virtual double getParamStep (  int idx,  SbVec3d* modelSize) ;

	

   /**@name Direct parameter modifications.
     */
    //@{
    void addTranslate ( double* xlate ) { 
        for(int i=0;i<3;++i)
            paramVector[TRANSLATE+i] += xlate[i];
	   	this->composeMatrix();
    }
    
    /// Set transformation's translation vector.
    void setTranslate ( double* xlate ) { 
        for(int i=0;i<3;++i)
            paramVector[TRANSLATE+i] = xlate[i];
	   	this->composeMatrix();
    }

    /// Set transformation's rotation angles.
    void setAngles (  double* angles ) { 
        for(int i=0;i<3;++i)
            paramVector[ANGLES+i] = angles[i];
	   	this->composeMatrix();
    }

    /// Set transformation's scaling factors.
    void setScales (  double* scales ) { 
        for(int i=0;i<3;++i)
            paramVector[SCALES+i] =scales[i];
	   	this->composeMatrix();	
    }

    /// Set transformation's shears.
    void setShears (  double* shears ) { 
        for(int i=0;i<3;++i)
            paramVector[SHEARS+i] = shears[i];
	   	this->composeMatrix();
	}

    /// Set transformation's rotation, scaling, and shearing center.
    void setCenter (  double* center ) {
        for(int i=0;i<3;++i)
            paramVector[CENTER+i] = center[i];
	   	this->composeMatrix();       	
    }
    //@}

  
    private:
        
    /** Set transformation matrix.
     * This implementation DOES NOT update the associated inverse transformation.      */
    void setTmpMatrixDirect( SbMatrixd m) 
    {
        tmpMatrix = m;
        this->decomposeMatrix(); 
    }        
    
    void setAmiraMatrixDirect( SbMatrixd m) {amiraMatrix = m;}
    
    /// Set the number of degrees of freedom for this object without side effects.
    virtual void setDegreesOfFreedomDirect (  int n = 12 ) { degreesOfFreedom = n; }

    McDArray<HxSpatialData*> reference; 
    
    HxSpatialData *model;


	/// Intermediate transformation matrix for model 
	/// (needed for calculating parameters which represent rotation, scale and shear separately).
    SbMatrixd tmpMatrix;
    
	/** Homogeneous transformation matrix in Inventor notation. 
     * Vectors are transformed by right-multiplication with this matrix, i.e.
     * v being a vector, the transformed vector is (v matrix).     */
    SbMatrixd amiraMatrix;
    
    /** Actual number of degrees of freedom.
     * This value should be one out of four choices: 6 (rigid transformation), 
     * 7 (rigid with global scaling), 9 (rigid with componentwise scaling), or
     * 12 (full affine). The number of elements of the parameter vector does NOT
     * change, even in the 7 DOF case. Then, all scaling factors are simply kept
     * equal.     */
    int degreesOfFreedom;

    // save previous value of parameter 6 for case 7 (rigid with global scaling)
    double mSaveParam6;

    RegAffineTransform *inverseTransform;

    /// Decompose this object's transformation matrix (tmpMatrix!!!) into parameter vector.
    int decomposeMatrix();
};

#endif

/// @}
