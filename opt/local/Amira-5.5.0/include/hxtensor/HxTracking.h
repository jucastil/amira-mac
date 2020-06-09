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

/// @addtogroup hxtensor hxtensor
/// @{
#ifndef HXFIBERTRACKING
#define HXFIBERTRACKING

#include <hxcore/HxCompModule.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortInfo.h>
#include <hxfield/HxField3.h>
#include <hxfield/HxLattice3.h>
#include <hxfield/HxUniformLabelField3.h>
#include <hxfield/HxRegSym2TensorField3.h>
#include <hxfield/HxRegVectorField3.h>
#include <hxfield/HxUniformVectorField3.h>
#include <hxfield/HxUniformScalarField3.h>
#include <hxlines/HxLineSet.h>
#include "HxTensorWinDLLApi.h"

/** Class computing an integration on the first principal direction field.
    It returns a matrix of connection probabilities for the different areas
    and corresponding LineSets for the integration results. */
class HXTENSOR_API HxFiberTracking : public HxCompModule {

  HX_HEADER(HxFiberTracking);
  
  public:
    /** Constructor. */
    HxFiberTracking();

    /** Update method. */
    virtual void update();

    /** Compute method. */
    virtual void compute();

    HxPortInfo portInfo;
    HxPortInfo portInfo2;

    /** a Labelfield, each Exterior(==0) entry will be ignored, the result for
        all other voxel in one region will be pooled (between region interaction) */
    HxConnection portMask;

    /** for the TEND algorithms we need the tensor information */
    HxConnection portTensor;

    /** the Eigenvalues of the PCA1 connected at data */
    HxConnection portEVALS;

    /** allows to enable or disable the local alignment during integration */
    HxPortToggleList portOptions;
    HxPortToggleList portOptions2;

    /** threshold on the fractional anisotropy (FA) do not seeds below */
    HxPortFloatSlider portFASeedThreshold;  /// < seeding the points per voxel
    HxPortFloatSlider portFAStepThreshold;  /// < used as a threshold per point

    /** for the TEND algorithms allow to change the weighting factors */
    HxPortFloatSlider portTensorG;
    HxPortFloatSlider portTensorF;

    /** threshold on the direction of movement for one step */
    HxPortFloatSlider portDirecThreshold;

    /** the stepsize is the size of a single integration step */
    HxPortFloatSlider portStepSize;

    /** the length is the step size, (which is always the vector length == 1) 
        multiplied by the number of steps taken. */
    HxPortFloatSlider portLength;

    /** Do it button. */
    HxPortDoIt portAction;

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

  public:
    /** Destructor. */
    ~HxFiberTracking();

    /// Check if given data object can be reconstructed.
    virtual int canCreateData(HxData* data, McString& createCmd);

    /// Save ports.
    virtual void savePorts(FILE* fp);


    // ugly because we have some static stuff from rk
    HxVectorField3* field;
    HxUniformLabelField3* mask;
    HxRegVectorField3* evals;

    float *xp,**yp,dxsav;
    mculong N; // number of variables in the current integration (3D points)
    double FAStepThreshold;
    double FASeedThreshold;

    HxLocation3 *loc; // used to query the field
    mculong kmax,kount,nrhs;
    int backwardPass; // to indicate for derivs that we do the backward integration now

private:
    // jitter the seed point location inside the voxel
    bool jitter;

    // creates a label field from a given lineset object
    HxData *createLabelField(HxLineSet *lineset, int xres, int yres, int zres, HxRegScalarField3 *labelField=NULL);

    // this rk4
    void rkdumb(float vstart[], int nvar, float x1, float x2, int nstep,
                void (*derivs)(float, float [], float [], HxObject *));
//    void rk4(float y[], float dydx[], int n, float x, float h, float yout[],
//             void (*derivs)(float, float [], float [], HxObject *), HxObject *obj);

    // this is rk5
    void odeint(float ystart[], int nvar, float x1, float x2, float eps, float h1,
                float hmin, int *nok, int *nbad,
                void (*derivs)(float, float [], float [], HxObject *),
                void (*rkqs)(float [], float [], int, float *, float, float, float [],
                float *, float *, void (*)(float, float [], float [], HxObject *), HxObject *));
};
#endif

/// @}
