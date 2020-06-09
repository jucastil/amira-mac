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

/// @addtogroup hximproc hximproc
/// @{
#ifndef MC_DIFFUSION_FILTER
#define MC_DIFFUSION_FILTER


#include <mclib/McDArray.h>
#include <mclib/McFilename.h>
#include <mclib/McVec3f.h>
#include <mclib/McProgressInterface.h>
#include <math.h>

#include <hxcore/HxMessage.h>

//#include <hximproc/HxImprocWinDLLApi.h>

class   McDiffusionFilter {

// MC_ABSTRACT_HEADER(McDiffusionFilter);

 public:
    
	enum FilterType {ISO,AN_ISO,EDGE};

	enum NumericType {EXPLICIT,NUM_AOS};

    enum DiffusivityType {LINEAR,EXP,FRAC,STEP,TUKEY};

	enum RegularizationType {NONE,AOS,OPT,CONV};

	enum GradientType {CENTRAL,DIRECTION,GAUSS,SOBEL};

	/// sigma is standard dev. of gaussian used for regularization of the image in gradient
	/// determination. lambda is a factor in the diffusivity function of diffType type.
	/// totalTime of filtering. tau is time step.
	McDiffusionFilter(McDArray<float>& sigmas,McDArray<float>& lambdas, float totalTime, float tau,
		FilterType fType = ISO,NumericType nType=NUM_AOS, DiffusivityType dType=EXP,
		RegularizationType rType=AOS,GradientType gType=CENTRAL);

	/// diffusion filter src to dst. dst gets same primitive type as src! Internal single precision float is used
    int filter(McPrimType primType, McDArray<mculong>& dims, McDArray<float>& size,
			void* src, void* dst, McProgressInterface* progress=0);

	int filterAnisotropic(McProgressInterface* progress);

	int regularizeOnly(McPrimType primType, McDArray<mculong>& dims, McDArray<float>& size,
			void* src, void* dst, McProgressInterface* progress=0);

	/// regularization (pre-smoothing)
	void smooth();

	/// gaussian smoothing by linear diffusion using AOS scheme.  
	virtual void smoothAOS()=0;

	/// smoothing with optimized rotation invariance (Scharr)
	virtual void gradientOpt()=0;

	virtual void gradientCentral()=0;

	virtual void gradVecOpt()=0;

	virtual void gradVecCentral()=0;

	virtual void smoothGauss()=0;

	/// smooth one line. Can be used for the higher dimensional cases.
	/// Implementation as linear diffusion filtering (AOS scheme)
	void smoothAOSLine(int start,int incr, int n);

	/// helper method for smoothAOS
	void smoothDecompose(int n, float r);

	/// smoothing with optimized rotation invariance (Scharr)
	void smoothOptLine(int start, int incr, int n);

	/// standard convolution with gaussian kernel?
	void smoothGaussLine(int start, int incr, int n, McDArray<float>& kernel, McDArray<float>& border);

	/// determines absolute gradient. Result in array g.
	/// gradient kernel is given by variable gradientType
	void absGradient();

	/// determines gradient vector
	void gradient();

	/// central differences ([1,0,-1]/2)
	void absCentralGradientLine(int start, int incr, int n);

	void centralGradientLine(int start, int incr, int n, int dir);

	/// optimized direction? 

	void diffusion();

	virtual void diffusionExplicit()=0;

	virtual void diffusionAOS()=0;

	void filterLineExplicit(int start, int incr, int n,float fac);

	void filterLineExplicitAniso(int start, int incr, int n, float fac,int dir);

	void filterLineAOS(int start, int incr, int n, float fac, int m);

	void filterLineAOSAniso(int start, int incr, int n, float fac, int m, int dir);

	/// determine diffusivity. Diffusivity Type is given in variable diffType. In place in g.
	virtual void diffusivity();
	
	/// creates look-up table for the chosen diffusivity function
	void createLookUpTable(int nLookUps);

	/// different diffusivity functions
    float gFunc(float x, float dummy){ return 1;}

    float gFuncExp(float x, float lambda){
        if (x==0) return 1.;
        return (1-exp(-3.315/pow(x/lambda,4)));
    }

    float gFuncFrac(float x, float lambda){
		return (1/(1+x/(lambda*lambda)));}

    float gFuncStep(float x, float lambda){
		return (x<lambda) ? 1 : 0;
    }

	float gFuncTukey(float x, float lambda){
		float val = ( 1 - ((x/lambda)*(x/lambda)));
		return (x<=lambda) ? (0.5*val*val) : 0;
	}

	float sigma;

	McDArray<float> sigmas;

	float lambda;

	McDArray<float> lambdas;

	FilterType filtType;

	NumericType numType;

	DiffusivityType diffType;

	RegularizationType regType;

	GradientType gradType;

	float totalTime;

	float tau;

	McDArray<McDArray<float> > gLookUp;

    /// result
    McDArray<float> u;

    /// regularized u
    McDArray<float> v;

	/// temporary copy of data
    McDArray<float> f;

    McDArray<float> g;

	McDArray<McDArray<float> > gVec;

//    virtual int explicitFilterStep(float timeStepLen) = 0;

//    virtual int implicitFilterStep(float timeStepLen) = 0;

//    virtual int aosFilterStep(float timeStepLen) = 0;


 protected:

	McDiffusionFilter(float sigma, float lambda, float T, float timeStep, 
		NumericType nType, DiffusivityType dType, RegularizationType rType,GradientType gType);

    int initialize(McPrimType primType, void* src);

    /// Thomas (not me!) Alg. for LR-Decomp. of tridiagonal Matrices
    /// It is supposed that all arrays are initialized!
    void LRsolve(int n);

    /// Like LRsolve, but without forward and backward substituition
    void LRdecomp(int n);

    /// forward and backward substitution, when matrix is already decomposed.
    void LRsubstitute(int n);

    /// fill bands of tridiagonal matrix and right hand side!
    void fillBands(int direction, int block);

    /// diagonal elements of tridiagonal matrix
    McDArray<float> alpha;

    /// upper band
    McDArray<float> beta;

    /// lower band
    McDArray<float> gamma;


    // take better a const pointer! 
    //McDArray<float> data;

    /// right hand side
    McDArray<float> d;

    McDArray<float> l;
    // McDArray<float> r; not needed, because r=beta!
    McDArray<float> m;
    McDArray<float> y;   // temprorary memory!

    McDArray<mculong> dims;

    McDArray<float> size;    

    /// number of data elements: N1*N2* .. *Nm
    mculong N;
    
	float lookUpStep;

};

#endif 

/// @}
