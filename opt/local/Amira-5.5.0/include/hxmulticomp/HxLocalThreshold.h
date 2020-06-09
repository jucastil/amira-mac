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

/// @addtogroup hxmulticomp hxmulticomp
/// @{
#ifndef HX_LOCALTHRESHOLD_H
#define HX_LOCALTHRESHOLD_H

#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxCompModule.h>

#include <hxfield/HxUniformLabelField3.h>

#include "HxMultiCompWinDLLApi.h"

/// Module for some non-local thresholding algorithms
class HXMULTICOMP_API HxLocalThreshold : public HxCompModule
{
    HX_HEADER(HxLocalThreshold);

  public:

    /// Default constructor.
    HxLocalThreshold();

    /// Compute method.
    void compute();

    /// Update method.
    virtual void update();

    HxPortMultiMenu portAlgorithm;

    HxPortToggleList portExport;

    HxPortIntTextN portFilterMask;

    HxPortFloatSlider portLambda;

    HxPortFloatTextN portNormalization;

    HxPortFloatSlider portThreshold1;

    HxPortFloatSlider portThreshold2;

    /// Start computation.
    HxPortDoIt portDoIt;

    typedef enum {
        ALGO_NIBLACK = 0,
        ALGO_OBERLAENDER,
        ALGO_MARDIAHAINSWORTH,
        ALGO_HYSTERESIS,
        ALGO_OTSU,
        ALGO_ISODATA
    } ALGORITHM;

    virtual int canCreateData(HxData* data, McString& createCmd);

  protected:
    McDArray<McHandle<HxUniformScalarField3> > stats; // mean and variance of the currently connected dataset

    template<class T>
    McDArray<McHandle<HxUniformScalarField3> > meanVariance(HxUniformScalarField3 *input, bool reUseStats = true);

    HxUniformScalarField3 *conv(HxUniformScalarField3 *source, HxUniformScalarField3 *kernel);

    /// sets source to a centered Gaussian with a variance defined by 1/6 of max(dims)
    void setToGaussian(HxUniformScalarField3 *source);

    void computeOberlaender(HxUniformScalarField3 *source,
        float lambda,
        HxUniformLabelField3 *labels);

    template<class T>
    void computeOberlaender(HxUniformScalarField3 *source,
        HxUniformScalarField3 *mean, 
        HxUniformScalarField3 *variance,
        float lambda,
        HxUniformLabelField3 *labels);

    void computeNiblack(HxUniformScalarField3 *source,
        float lambda,
        float R,
        HxUniformLabelField3 *labels);

    template<class T>
    void computeNiblack( HxUniformScalarField3 *source,
        HxUniformScalarField3 *mean, 
        HxUniformScalarField3 *variance,
        float lambda, // -0.2
        float R,      // half the maximum of the data range (keeps x/R below 1 for most voxel)
        HxUniformLabelField3 *labels);

    void computeMardiaHainsworth(HxUniformScalarField3 *source, HxUniformLabelField3 *labels);

    template<class T>
    void computeMardiaHainsworth(HxUniformScalarField3 *source, HxUniformLabelField3 *labels);

    void computeOtsu(HxUniformScalarField3 *source, HxUniformLabelField3 *labels);

    template<class T>
    T computeOtsu(HxUniformScalarField3 *source, HxUniformLabelField3 *labels);

    void computeIsoData(HxUniformScalarField3 *source, HxUniformLabelField3 *labels);

    template<class T>
    T computeIsoData(HxUniformScalarField3 *source, HxUniformLabelField3 *labels);

    void computeHysteresis(HxUniformScalarField3 *source, HxUniformLabelField3 *labels);

    template<class T>
    void computeHysteresis(HxUniformScalarField3 *source, HxUniformLabelField3 *labels);

    McVec3i oldResolution; // used to store values before Mardia is switched on
};

#endif

/// @}
