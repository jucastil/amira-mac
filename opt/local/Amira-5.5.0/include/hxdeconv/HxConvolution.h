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

/// @addtogroup hxdeconv hxdeconv
/// @{
#ifndef HX_CONVOLUTION
#define HX_CONVOLUTION

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortDoIt.h>
#include <hxfield/HxUniformScalarField3.h>
#include <hxdeconv/hxdeconvAPI.h>

/** This module convolves two uniform scalar fields. */
class HXDECONV_API HxConvolution : public HxCompModule {

  HX_HEADER(HxConvolution);
  
  public:
    /// Constructor.
    HxConvolution();

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Connection to kernel.
    HxConnection portKernel;

    /// Border width.
    HxPortIntTextN portBorderWidth;

    /// Options: 0=normalize kernel, 1=add noise to result
    HxPortToggleList portOptions;

    /// Noise level in percent of voxel intensity.
    HxPortFloatSlider portNoiseLevel;

    /// DoIt button.
    HxPortDoIt portAction;

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

  public:
    /// Destructor.
    ~HxConvolution();

    /// Performs the actual computation.
    int convolve();

    /// Helper function that does not depend on user interface
    static bool convolve(HxRegScalarField3 *data, HxRegScalarField3 *kernel, HxRegScalarField3 *result, McVec3i borderWidth, bool normalizeKernel, bool addNoise, float noiseLevel);

    /// Check if given data object can be reconstructed.
    virtual int canCreateData(HxData* data, McString& createCmd);
};

#endif

/// @}