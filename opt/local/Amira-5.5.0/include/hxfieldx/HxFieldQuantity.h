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
#ifndef HX_FIELD_QUANTITY
#define HX_FIELD_QUANTITY

#include "HxFieldWinDLLApi.h"
#include <string.h>

template <class A, class B> class McHashTable;

/** \brief Class describing the quantities that can be evaluated on fields.
This class wraps the string into a persistent version 
and provides some helper methods.
*/
class HXFIELDX_API HxFieldQuantity {
public:
	HxFieldQuantity () {
		mName = Invalid;
	}

	/** 
	*/
	explicit HxFieldQuantity (const char* name);

	/* default copy and assignment operators are fine
	HxFieldQuantity(const& HxFieldQuantity);
	const HxFieldQuantity& operator= (const HxFieldQuantity&);
	*/ 

	// TODO: move pointers to namespace

	/** Invalid flag.
	*/
	static const char* Invalid;

	/** The primary quantity is the data itself.
	*/
	static const char* Primary;

	/** The alpha channel indicates if the field is defined at a certain position.
		Evaluates to 0 if the field is not defined and to 1 if the field is defined.
	*/
	static const char* AlphaChannel;

	/** The Jacobian (first derivative) of the field.

		A Matrix with dV*d entries, where dV is the number of components of the Primary Type
		and d is the dimensionality of the field.
	*/
	static const char* Jacobian;

	/** Returns the hessian (second derivative) of the field.	    
	*/
	static const char* Hessian;

	/** Returns the third derivative of the field.	    
	*/
	static const char* Derivative3;

	/** Returns the fourth derivative of the field.	    
	*/
	static const char* Derivative4;




	/** Returns the scalar field \b magnitude of the original field.

		@see HxFieldQuantityMagnitude
	*/
	static const char* Magnitude;


	/** The divergence of a vector field v.

		Returns the scalar field \f$\partial_x u + \partial_y v + \partial_z w\f$.
		This is the amount of mass that is lost/gained at a specific point.
	*/
	static const char* Divergence;

	/** The curl (rotation) of a vector field v.

		Returns the vector field \f$\nabla \times v\f$.
	*/
	static const char* Curl;

	/** The helicity of a vector field v in 3 dimensions.

		Returns the scalar field \f$\langle \text{curl}, v\rangle\f$.
	*/
	static const char* Helicity;



	/** Determinant of the Jacobian. @todo: Obsolete, please remove.
	*/
	static const char* DetJacobian;

	/** EigenValues of the Jacobian. @todo: Obsolete, please remove.
	*/
	static const char* EValJacobian;

	/** EigenVectors of the Jacobian. @todo: Obsolete, please remove.
	*/
	static const char* EVecJacobian;


	/** Determinant of the Hessian. @todo: Obsolete, please remove.
	*/
	static const char* DetHessian;

	/** EigenValues of the Hessian. @todo: Obsolete, please remove.
	*/
	static const char* EValHessian;

	/** EigenVectors of the Hessian. @todo: Obsolete, please remove.
	*/
	static const char* EVecHessian;


	/** Determinant of the primary.
	*/
	static const char* Determinant;

	/** EigenValues of the primary.
		
		@todo Idea: Use a 'silent' quantity called "EigenAnalysis".
		This one will compute all that stuff and the others will simply use that memory.
	*/
	static const char* EigenValues;

	/** EigenVectors of the primary.
	*/
	static const char* EigenVectors;

	/** Whether we have imaginary eigenvalues or not.
	*/
	static const char* EigenValuesAreComplex;


  /** Metric Tensor
  */

  static const char* MetricTensor;


	/** The tensor field \f$\Omega^2+S^2\f$ of a vector field.
	
		where \f$\Omega=\frac12(D+D^t)\f$, \f$S=\frac12(D-D^t)\f$,
		is the symmetric and antisymmetric part of the Jacobian \f$D\f$
		of the vector field respectively. 

		Furthermore, the quantities #Lambda2 and #QHunt build upon this quantity.
	*/
	static const char* Omega2S2;


	/** The scalar field \f$\lambda_2\f$ of a vector field.
	
		This is the second largest Eigenvalue of the Matrix \f$\Omega^2+S^2\f$,
		where \f$\Omega=\frac12(D+D^t)\f$, \f$S=\frac12(D-D^t)\f$,
		the symmetric and antisymmetric part of the Jacobian \f$D\f$
		of the vector field respectively. 

		Places with \f$\lambda_2 < 0\f$ are considered as vortices.

		It was introduced by J. JEONG and F. HUSSAIN:
		On the identification of a vortex, J. Fluid Mech (1995) vol 285, pp 69-94
	*/
	static const char* Lambda2;

	/** The scalar field QHunt \f$Q\f$ is the field \f$-\text{trace}(\Omega^2+S^2)\f$,
		with \f$\Omega\f$ and \f$S\f$ as above (#Lambda2).

		Places with \f$Q > 0\f$ are considered as vortices.

		It was introduced by J. HUNT, A. WRAY, P. MOIN: 
		Eddies, streams and convergence zones in turbulent flows,
		Center for Turbulence Research Report CTR-S88, p193
	*/
	static const char* QHunt;

	/** The scalar field OkuboWeiss returns a scalar field indicating vortex regions
		by Jacobian:Jacobian^t, the scalar product of the two matrices 3x3 Jacobian and Jacobian^t
		interpreted as 9-vectors.

		@todo Explain difference to QHunt.
	*/
	static const char* OkuboWeiss;


	/** Zeros of this field are extremum lines (ridge and valley lines)
		of the scalar field P,Q - computed with nonnormalized gradient- and beta
	*/
	static const char* ZeroRidge;


	/** Tangent field to  Extremum Lines (ridge and valley Lines) of the scalar Field	    
	*/
	static const char* TrackSpaceRidge;


	/** Zeros of this Field are Fold bifurcations.
	*/
	static const char* ZeroFoldBifurcations;

	/** Zeros of this Field are Hopf bifurcations, if Jacobian has complex eigenvalues.
	*/
	static const char* ZeroHopfBifurcations;

	/** The stream lines of this vector field represent the paths of the critical points.
	*/
	static const char* TrackCPFFF;

	/** The stream lines of this vector field represent the paths of critical points in double-time dependent vector fields.
	*/
	static const char* TrackCPDoubleTimeFFFS;

	/** The stream lines of this vector field represent the paths of critical points in double-time dependent vector fields.
	*/
	static const char* TrackCPDoubleTimeFFFT;

	/** The stream lines of this vector field represent the paths of fold bifurcations.
	*/
	static const char* TrackFoldFFF;

	/** The stream lines of this vector field represent the paths of Hopf bifurcations.
	*/
	static const char* TrackHopfFFF;

	/** Zeros of this Field are Fold-Fold bifurcations in s.
	*/
	static const char* ZeroFoldFoldBifurcationsS;

	/** Zeros of this Field are Fold-Fold bifurcations in t.
	*/
	static const char* ZeroFoldFoldBifurcationsT;


	/** Zeros of this Field are Hopf-Fold bifurcations in s.
	*/
	static const char* ZeroHopfFoldBifurcationsS;

	/** Zeros of this Field are Hopf-Fold bifurcations in t.
	*/
	static const char* ZeroHopfFoldBifurcationsT;


	///Returns type of critical point
	static const char* TypeCriticalPoint;


	///FFF pointing into the direction where the vector field keeps same direction,
	///but not necessarily magnitude. This is meant for 3D steady vector fields,
	///but could also be extended to other dimensions.
	static const char* FFFSameDirection;

	///Local behavior of a 3D vector field in a plane perpendicular to the flow direction.
	///Negative values indicate saddle behavior, positive values indicate source/sink behavior.
	static const char* VFLocalPlanarBehavior;

	///Stabilizes FFF integration.
	static const char* TrackCPFFFStabilization;



	/** Tangent field to lines resulting from the Parallel Vector operator in 3D Space

	*/
	static const char* TrackSpaceParallelVectors;

	/** Zeros of this field are Parallel lines

	*/
	static const char* ZeroParallelVectors;

	/** Tangent field to lines resulting from the Parallel Vector operator in Time

	*/
	static const char* TrackTimeParallelVectors;




	//THE FOLLOWING char* SHOULD BE REMOVED ENTIRELY.

	/** Tangent field to  Extremum Lines (ridge and valley Lines) of the scalar Field, computed by a field with quantities P,Q -for a normalized gradient- and betta	    
	*/
	static const char* ValleyDir;
	static const char* RidgeDirBGN;
	/** Tangent field to  Extremum Lines (ridge and valley Lines) of the scalar Field, computed by a field with quantities P,Q -for a normalized gradient- and betta-gamma	       
	*/
	static const char* RidgeDirBGGN;
	/** Tangent field to  Extremum Lines (ridge and valley Lines) of the scalar Field, computed by a field with quantities P,Q -for a nonnormalized gradient- and betta-gamma	      	    
	*/
	static const char* RidgeDirBGGU;

	/** Zeros of this Field are Extremum Lines (ridge and valley Lines) of the scalar Field;
	BGN = beta, gradient normalized -> P,Q -computed with normalized gradient- and beta
	*/
	static const char* ValleyZero;

	static const char* RidgeZeroBGN;
	/** Zeros of this Field are Extremum Lines (ridge and valley Lines) of the scalar Field;
	BGGN = beta-gamma, gradient normalized -> P,Q -computed with normalized gradient- and (beta-gamma)
	*/
	static const char* RidgeZeroBGGN;
	/** Zeros of this Field are Extremum Lines (ridge and valley Lines) of the scalar Field;
	BGGU = beta-gamma, gradient normalized -> P,Q -computed with nonnormalized gradient- (and beta-gamma)
	*/
	static const char* RidgeZeroBGGU;


	/** Eigenvalues of the Hessian of the ridge defining scalar field.

	*/
	static const char* RidgeEV;


	/** Holds 1 , if gradient is EV of Hessian. 
	*/
	static const char* CheckGradientAsEVCosCrit;

	/** Holds zeros , if gradient is EV of Hessian. 
	*/
	static const char* CheckGradientAsEV;

	/** gives the time-derivative of the first 3 dimensions of a field
	*/
	static const char* del_tSpatialPrimary;

	/** gives the second derivatives del_tj vi for j=x, y, z of the first 3 dimensions i=1, 2, 3 of a field
	as natural: j=x in column 1, j=z in column 3; i=1 in row 1, i=3 in row 3
	*/
	static const char* del_tSpatialJacobian;


	/** The spatial Jacobian at time step t. A Matrix with d*3 entries, where d is the dimensionality of the Primary Type. 
	*/
	static const char* SpatialJacobian;

	/** Returns the spatial hessian of the original field

	*/
	static const char* SpatialHessian;

	/** The scalar field Div (Divergence) of a vector field v in 3 dimensions. 
	Returns the vector field \f$\del_x u + \del_y v + \del_z w\f$ at a timestep t. 
	This is the amount of mass that is lost/gained at a specific point.
	*/
	static const char* SpatialDiv;

	/** The Curl (Rotation) of a vector field.v in 3 dimensions. 
	Returns the vector field \f$\nabla \times v(t)\f$ at a timestep t. 
	*/
	static const char* SpatialCurl;

	/** The Helicity  of a vector field.v in 3 dimensions. 
	Returns the scalar field \f$<Curl, v(t)>\f$ at a timestep t. 
	*/
	static const char* SpatialHelicity;

	/** PathVCLPV has nDataVar 7 the first 3 entries contain f[i]-f[3]*v[i], the second three contain e[0], e[1], e[2], 
    where f is the Eigenvector to EigenValue 0, e is the other real Eigenvalue, and v is the flow itself.
    the last states 1.0f if the Jacobian has complex EValues, 0.0f otherwise. 
	*/
	static const char* PathVCLPV;

	/** SujudiHaimesPV has nDataVar 8 the first 3 entries contain v[i], the second three contain Gradient(v)*v, 
    entry 6 states 1.0f if the Jacobian has complex EValues, 0.0f otherwise. 
	entry 7 is the complex arg of the conjugate EV. 
	*/
	static const char* SujudiHaimesPV;

	/** elleT has nDataVar 8 the first 3 entries contain e(J), the second three contain e(J^T),
		entry 6 states 1.0f if the Jacobian has complex EValues, 0.0f otherwise.
		entry 7 is the complex arg of the conjugate EV.
	*/
	static const char* elleT;

    /** Acceleration2DT has nDataVar 1. 
        the saved value is the norm (eucl) of the local acceleration.        
	*/
    static const char* Acceleration2DT;

    /**
     * Ridgeness (nDataVar N)
     */
    static const char* RidgenessND;

    /**
     * Valleyness (nDataVar N)
     */
    static const char* ValleynessND;



	/** equality op */
	bool operator== (const HxFieldQuantity& other) const {
		return mName == other.mName || strcmp (mName, other.mName) == 0;
	}

	/** optimized equality op without constructing a HxFieldQuantity first */
	bool operator== (const char* other) const {
		return mName == other || strcmp (mName, other) == 0;
	}

	/** inequality op */
	bool operator!= (const HxFieldQuantity& other) const {
		return !(*this == other);
	}

	/** inequality op */
	bool operator!= (const char* other) const {
		return !(*this == other);
	}


	/** get the name of the type */
	const char* getName () const {
		return mName;
	}

	const char* getShortName () const {
		const char* match = strrchr (mName, '#');
		return match ? match + 1 : mName;
	}

	/** check if the type name is known. */
	static bool isKnown (const char* name);

private:
	static McHashTable<const char*, const char*>& toPersistentMap ();

	const char* mName;
};

#endif

/// @}
