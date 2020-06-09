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

/// @addtogroup hxiso hxiso
/// @{
#ifndef HX_ISOSURFACE_H
#define HX_ISOSURFACE_H

#include <hxiso/HxIsoWinDLLApi.h>

#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>
#include <hxsurface/HxTriBase.h>

#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxConnection.h>

class HxUniformScalarField3;

/// This class implements isosurface algorithms for regular scalar fields.

class HXISO_API HxIsosurface : public HxTriBase {

  HX_HEADER(HxIsosurface);

  public:
    /// Default constructor.
    HxIsosurface();

    /// Updates user interface even when module is disabled.
    virtual void update();

    /// Invokes actual computation.
    virtual void compute();

    /// Threshold of the isosurface.
    HxPortFloatSlider portThreshold;

    /// Options: 0=compact cubes, 1=downsample
    HxPortToggleList portOptions;

    /// Number of voxels to be averaged when downsampling (2x2x2).
    HxPortIntTextN portResolution;

    /// Optionally use a point probe to set the threshold value.
    HxConnection portPointProbe;

    /// Number of cores for parallel computation.
    /// Not really used for now, only present for compatibility reasons (ClimatViz project).
    HxPortIntSlider portCoreNum;
	    
    /// Do it button.
    HxPortDoIt portAction;

    /// Tcl-commands interface.
    int parse(Tcl_Interp* t, int argc, char** argv);

    /** Sets an external intersection routine. The routine is used to
	determine the exact position of the isosurface along intersected
	edges. The arguments @c ia and @c ib specify the indices of two
	neighbouring grid vertices, ia = (k*dims[1]+j)*dims[0]+i. The
	routine is supposed to return a number between 0 and 1. */
    void setIntersectionCallback(float (*f)(int ia, int ib, HxObject* object),
	HxObject* object);

    /// Save sate method.
    virtual void savePorts(FILE* fp);

  protected:
    virtual ~HxIsosurface();

    // Was computeSurface() called after last parameter change?
    bool surfaceUpToDate;

    // Used by compact cubes (don't weld vertices paramCC...1-paramCC)
    float paramCC;

    McHandle<HxObject> intersectionCallbackObject;
    float (*intersectionCallback)(int, int, HxObject*);

    HxUniformScalarField3* resample();

    /// Does the computation if HxRegScalarFild3 is connected. 
    void computeRegScalarField3(); 

    /// Does the computation for HxScalarBlockStructuredField3
    void computeBlockScalarField3();
};

#endif


/// @}
