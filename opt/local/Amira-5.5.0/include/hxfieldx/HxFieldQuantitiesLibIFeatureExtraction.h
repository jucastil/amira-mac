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

/// @addtogroup hxfieldx hxfieldx
/// @{
#ifndef HXFIELDX_HXFIELDQUANTITIESLIBIFEATUREEXTRACTION_H
#define HXFIELDX_HXFIELDQUANTITIESLIBIFEATUREEXTRACTION_H


#include <hxfieldx/HxFieldQuantitiesLibTypes.h>
#include <hxfieldx/HxFieldWinDLLApi.h>


/** Implements determinant of a 2x2 matrix.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityDeterminant2
    : public HxFieldQuantityImplementationDup< HxFieldQuantityDeterminant2 >
{
    //Construction / Deconstruction
public:
    HxFieldQuantityDeterminant2();
    virtual ~HxFieldQuantityDeterminant2();

    //Methods
public:
    ///Determinant can be computed, if we have four components.
    bool canBeComputed() const;

    ///Determinant is a scalar.
    int getNDataVar() const;

    ///Computes Determinant.
    void computeQuantity();

    //Attributes
private:
    const float* Primary;
};



/** Implements determinant of a 3x3 matrix.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityDeterminant3
    : public HxFieldQuantityImplementationDup< HxFieldQuantityDeterminant3 >
{
    //Construction / Deconstruction
public:
    HxFieldQuantityDeterminant3();
    virtual ~HxFieldQuantityDeterminant3();

    //Methods
public:
    ///Determinant can be computed, if we have nine components.
    bool canBeComputed() const;

    ///Determinant is a scalar.
    int getNDataVar() const;

    ///Computes Determinant.
    void computeQuantity();

    //Attributes
private:
    const float* Primary;
};



/** Implements eigenvalues of a 3x3 matrix.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityEigenValues3
    : public HxFieldQuantityImplementationDup< HxFieldQuantityEigenValues3 >
{
    //Construction / Deconstruction
public:
    HxFieldQuantityEigenValues3();
    virtual ~HxFieldQuantityEigenValues3();

    //Methods
public:
    ///EigenValues can be computed, if we have nine components.
    bool canBeComputed() const;

    ///EigenValues is a vector with 6 components: Re1, Im1; Re2, Im2; Re3, Im3
    int getNDataVar() const;

    ///Computes EigenValues.
    void computeQuantity();

    //Attributes
private:
    const float* Primary;
};


/** Implements eigenvectors of a 3x3 matrix.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityEigenVectors3
    : public HxFieldQuantityImplementationDup< HxFieldQuantityEigenVectors3 >
{
    //Construction / Deconstruction
public:
    HxFieldQuantityEigenVectors3();
    virtual ~HxFieldQuantityEigenVectors3();

    //Methods
public:
    ///EigenVectors can be computed, if we have nine components.
    bool canBeComputed() const;

    ///EigenVectors is a vector with 3 components.
    int getNDataVar() const;

    ///Computes EigenVectors.
    void computeQuantity();

    //Attributes
private:
    const float* Primary;
};


/** Implements eigenvectors of a 3x3 matrix.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityEigenValuesAreComplex3
    : public HxFieldQuantityImplementationDup< HxFieldQuantityEigenValuesAreComplex3 >
{
    //Construction / Deconstruction
public:
    HxFieldQuantityEigenValuesAreComplex3();
    virtual ~HxFieldQuantityEigenValuesAreComplex3();

    //Methods
public:
    ///Can be computed, if we have nine components.
    bool canBeComputed() const;

    ///Is a scalar.
    int getNDataVar() const;

    ///Computes quant.
    void computeQuantity();

    //Attributes
private:
    const float* Primary;
};



/** Implements the Theisel field for 2D time-dependent vector fields.

This is a feature flow field to track critical points
in 2D time-dependent vector fields.
Given a 2D time-dependent vector field
\f[
\newcommand{\vv}{{\mathbf v}}
\vv(x,y,t) = 
\left(
\begin{array}{c}
u(x,y,t) \\
v(x,y,t) \\
\end{array}
\right)
\f]
the Theisel field is defined by
\f[
\newcommand{\ff}{{\mathbf f}}
\newcommand{\vv}{{\mathbf v}}
\ff(x,y,t) = \mbox{grad}(u) \times \mbox{grad}(v) 
= 	\left(
\begin{array}{c}
u_x \\
u_y \\
u_t \\
\end{array}
\right)
\times
\left(
\begin{array}{c}
v_x \\
v_y \\
v_t \\
\end{array}
\right)
= 
\left(
\begin{array}{c}
\det(\vv_y,\vv_t)  \\
\det(\vv_t,\vv_x) \\
\det(\vv_x,\vv_y) \\
\end{array}
\right).
\f]

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityTrackCPFFF2D
    : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityTrackCPFFF2D>
{
    //Construction / Deconstruction
public:
    HxFieldQuantityTrackCPFFF2D();
    virtual ~HxFieldQuantityTrackCPFFF2D();

    //Methods
public:
    void computeQuantity();

    //Attributes
private:
    const float* Jacobian;
};




/** Implements the Theisel field for 3D time-dependent vector fields.

This is a feature flow field to track critical points
in 3D time-dependent vector fields.
Given a 3D time-dependent vector field
\f[
\newcommand{\vv}{{\mathbf v}}
\vv(x,y,z,t) = 
\left(
\begin{array}{c}
u(x,y,z,t) \\
v(x,y,z,t) \\
w(x,y,z,t) \\
\end{array}
\right)
\f]
the Theisel field is defined by
\f[
\newcommand{\ff}{{\mathbf f}}
\newcommand{\vv}{{\mathbf v}}
\ff(x,y,z,t)
= \left( \begin{array}{c}
+ \det(\vv_y, \vv_z, \vv_t)\\
- \det(\vv_z, \vv_t, \vv_x)\\
+ \det(\vv_t, \vv_x, \vv_y)\\
- \det(\vv_x, \vv_y, \vv_z)
\end{array}
\right).
\f]

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityTrackCPFFF3D
    : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityTrackCPFFF3D>
{
    //Construction / Deconstruction
public:
    HxFieldQuantityTrackCPFFF3D();
    virtual ~HxFieldQuantityTrackCPFFF3D();

    //Methods
public:
    void computeQuantity();

    //Attributes
private:
    const float* Jacobian;
};





/** Implements tracking of critical points for 2D multi-time vector fields.

@todo Description.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityTrackCPDoubleTimeFFF2DS
    : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityTrackCPDoubleTimeFFF2DS>
{
    //Construction / Deconstruction
public:
    HxFieldQuantityTrackCPDoubleTimeFFF2DS();
    virtual ~HxFieldQuantityTrackCPDoubleTimeFFF2DS();

    //Methods
public:
    void computeQuantity();

    //Attributes
private:
    const float* Jacobian;
};







/** Implements tracking of critical points for 2D multi-time vector fields.

@todo Description.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityTrackCPDoubleTimeFFF2DT
    : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityTrackCPDoubleTimeFFF2DT>
{
    //Construction / Deconstruction
public:
    HxFieldQuantityTrackCPDoubleTimeFFF2DT();
    virtual ~HxFieldQuantityTrackCPDoubleTimeFFF2DT();

    //Methods
public:
    void computeQuantity();

    //Attributes
private:
    const float* Jacobian;
};








/** Implements tracking of fold bifurcations in multi-time fields.

This is a feature flow field to track fold bifurcations
in 2D multi-time-dependent vector fields.
Given a 2D multi-time-dependent vector field

@todo Description.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityTrackFoldFFF2D
    : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityTrackFoldFFF2D>
{
    //Construction / Deconstruction
public:
    HxFieldQuantityTrackFoldFFF2D();
    virtual ~HxFieldQuantityTrackFoldFFF2D();

    //Methods
public:
    void computeQuantity();

    //Attributes
private:
    const float* Jacobian;
    const float* Hessian;
};





/** Implements zeros of fold-fold bifurcations in multi-time fields.

@todo Description.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityZeroFoldFoldS2D
    : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityZeroFoldFoldS2D>
{
    //Construction / Deconstruction
public:
    HxFieldQuantityZeroFoldFoldS2D();
    virtual ~HxFieldQuantityZeroFoldFoldS2D();

    //Methods
public:
    void computeQuantity();

    //Attributes
private:
    const float* Primary;
    const float* Jacobian;
    const float* Hessian;
};






/** Implements zeros of fold-fold bifurcations in multi-time fields.

@todo Description.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityZeroFoldFoldT2D
    : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityZeroFoldFoldT2D>
{
    //Construction / Deconstruction
public:
    HxFieldQuantityZeroFoldFoldT2D();
    virtual ~HxFieldQuantityZeroFoldFoldT2D();

    //Methods
public:
    void computeQuantity();

    //Attributes
private:
    const float* Primary;
    const float* Jacobian;
    const float* Hessian;
};



/** Implements zeros of fold bifurcations in time-dependent 2D vector fields.

@todo Description.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityZeroFold2D
    : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityZeroFold2D>
{
    //Construction / Deconstruction
public:
    HxFieldQuantityZeroFold2D();
    virtual ~HxFieldQuantityZeroFold2D();

    //Methods
public:
    void computeQuantity();

    //Attributes
private:
    const float* Primary;
    const float* Jacobian;
};



/** Implements zeros of fold bifurcations in time-dependent 3D vector fields.

@todo Description.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityZeroFold3D
    : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityZeroFold3D>
{
    //Construction / Deconstruction
public:
    HxFieldQuantityZeroFold3D();
    virtual ~HxFieldQuantityZeroFold3D();

    //Methods
public:
    void computeQuantity();

    //Attributes
private:
    const float* Primary;
    const float* Jacobian;
};



/** Implements zeros of Hopf bifurcations in time-dependent 2D vector fields.

@todo Description.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityZeroHopf2D
    : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityZeroHopf2D>
{
    //Construction / Deconstruction
public:
    HxFieldQuantityZeroHopf2D();
    virtual ~HxFieldQuantityZeroHopf2D();

    //Methods
public:
    void computeQuantity();

    //Attributes
private:
    const float* Primary;
    const float* Jacobian;
};



/** Implements zeros of Hopf-fold bifurcations in multi-time fields.

@todo Description.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityZeroHopfFoldS2D
    : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityZeroHopfFoldS2D>
{
    //Construction / Deconstruction
public:
    HxFieldQuantityZeroHopfFoldS2D();
    virtual ~HxFieldQuantityZeroHopfFoldS2D();

    //Methods
public:
    void computeQuantity();

    //Attributes
private:
    const float* Primary;
    const float* Jacobian;
    const float* Hessian;
};





/** Implements zeros of Hopf-fold bifurcations in multi-time fields.

@todo Description.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityZeroHopfFoldT2D
    : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityZeroHopfFoldT2D>
{
    //Construction / Deconstruction
public:
    HxFieldQuantityZeroHopfFoldT2D();
    virtual ~HxFieldQuantityZeroHopfFoldT2D();

    //Methods
public:
    void computeQuantity();

    //Attributes
private:
    const float* Primary;
    const float* Jacobian;
    const float* Hessian;
};





/** Implements tracking of Hopf bifurcations in multi-time fields.

This is a feature flow field to track Hopf bifurcations
in 2D multi-time-dependent vector fields.
Given a 2D multi-time-dependent vector field

@todo Description.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityTrackHopfFFF2D
    : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityTrackHopfFFF2D>
{
    //Construction / Deconstruction
public:
    HxFieldQuantityTrackHopfFFF2D();
    virtual ~HxFieldQuantityTrackHopfFFF2D();

    //Methods
public:
    void computeQuantity();

    //Attributes
private:
    const float* Jacobian;
    const float* Hessian;
};







/** Implements type of a critical point of a 2D vector field.

@todo Description.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityCPType2D
    : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityCPType2D>
{
    //Construction / Deconstruction
public:
    HxFieldQuantityCPType2D();
    virtual ~HxFieldQuantityCPType2D();

    //Methods
public:
    void computeQuantity();

    //Attributes
private:
    const float* Jacobian;
};



/** Implements a feature flow field (FFF) pointing into the direction
    where the original vector field keeps same direction,
    but not necessarily same magnitude.

    This is meant for 3D steady vector fields,
    but could also be extended to other dimensions.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityFFFSameDir3D
    : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityFFFSameDir3D>
{
//Construction / Deconstruction
public:
    HxFieldQuantityFFFSameDir3D();
    virtual ~HxFieldQuantityFFFSameDir3D();

//Methods
public:
    void computeQuantity();

//Attributes
private:
    const float* Primary;
    const float* Jacobian;
};



/** Implements a scalar field which gives the local behavior
    of a 3D vector field in a plane perpendicular to the flow direction.

    Negative values indicate saddle behavior, positive values indicate source/sink behavior.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityVFLocalPlanarBehavior
    : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityVFLocalPlanarBehavior>
{
//Construction / Deconstruction
public:
    HxFieldQuantityVFLocalPlanarBehavior();
    virtual ~HxFieldQuantityVFLocalPlanarBehavior();

//Methods
public:
    void computeQuantity();

//Attributes
private:
    const float* Primary;
    const float* FFFSameDir;
};



/** Implements a vector field which can be used to stabilize FFF integration.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityTrackCPFFFStabilization
    : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityTrackCPFFFStabilization>
{
//Construction / Deconstruction
public:
    HxFieldQuantityTrackCPFFFStabilization();
    virtual ~HxFieldQuantityTrackCPFFFStabilization();

//Methods
public:
    void computeQuantity();

//Attributes
private:
    const float* Primary;
    const float* Jacobian;
    const float* FeatureFlowField;
};





/** Implements zeros of ridge lines.

@todo Description.

@author Jan Sahner
*/
class HXFIELDX_API HxFieldQuantityZeroRidge
    : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityZeroRidge>
{
    //Construction / Deconstruction
public:
    HxFieldQuantityZeroRidge();
    virtual ~HxFieldQuantityZeroRidge();

    //Methods
public:
    void computeQuantity();

    //Attributes
private:
    const float* Jacobian;
    const float* Hessian;
};

/** Implements ridge tangents.

@todo Description.

@author Jan Sahner
*/
class HXFIELDX_API HxFieldQuantityTrackSpaceRidge
    : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityTrackSpaceRidge>
{
    //Construction / Deconstruction
public:
    HxFieldQuantityTrackSpaceRidge();
    virtual ~HxFieldQuantityTrackSpaceRidge();

    //Methods
public:
    void computeQuantity();

    //Attributes
private:
    // saves the previously computed Result
    float prevRidDir[3];

    const float* Jacobian;
    const float* Hessian;
};


/** Implements coplanarity written as pv problem.

@todo Description.

@author Jan Sahner
*/
class HXFIELDX_API HxFieldQuantityPathVCLPV
    : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityPathVCLPV>
{
    //Construction / Deconstruction
public:
    HxFieldQuantityPathVCLPV();
    virtual ~HxFieldQuantityPathVCLPV();

    //Methods
public:
    void computeQuantity();

    //Attributes
private:
    const float* Primary;
    const float* Jacobian;

};
/** Implements Sujudi/Haimes written as pv problem.

@todo Description.

@author Jan Sahner
*/
class HXFIELDX_API HxFieldQuantitySujudiHaimes
    : public HxFieldQuantityImplementationFixedDim<HxFieldQuantitySujudiHaimes>
{
    //Construction / Deconstruction
public:
    HxFieldQuantitySujudiHaimes();
    virtual ~HxFieldQuantitySujudiHaimes();

    //Methods
public:
    void computeQuantity();

    //Attributes
private:
    const float* Primary;
    const float* Jacobian;

};


/** Implements e(J)||e(J^T).

@todo Description.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityelleT
    : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityelleT>
{
    //Construction / Deconstruction
public:
    HxFieldQuantityelleT();
    virtual ~HxFieldQuantityelleT();

    //Methods
public:
    void computeQuantity();

    //Attributes
private:
    const float* Jacobian;
};

/** Implements acceleration computation as scalar.

	@todo new feature for extracting coherent structures in time dependent fields

    @author Jens Kasten
*/
class HXFIELDX_API HxFieldQuantityAcceleration2DT
    : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityAcceleration2DT>
{
//Construction / Deconstruction
public:
    HxFieldQuantityAcceleration2DT();
    virtual ~HxFieldQuantityAcceleration2DT();

//Methods
public:
    void computeQuantity();

//Attributes
private:
    const float* Primary;
    const float* Jacobian;
};



#endif //HXFIELDX_HXFIELDQUANTITIESLIBIFEATUREEXTRACTION_H


/// @}
