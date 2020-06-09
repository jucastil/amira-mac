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

/// @addtogroup hxsegeditor hxsegeditor
/// @{
#ifndef HXINTERPOLATE_LABELSM_H
#define HXINTERPOLATE_LABELSM_H

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortToggleList.h>

#include "HxGiWinDLLApi.h"
#include "Contour2D.h"
//#include <hxfield/HxUniformLabelField3.h>
//#include <hxfield/HxStackedLabelField3.h>
#include <hxfield/HxLattice3.h>
#include <hxfield/HxLabelLattice3.h>
#include <hxfield/HxRegScalarField3.h>

#include <mclib/McVec2f.h>
#include <mclib/McData3D.h>

//  Creates new Label Field with intermediate slices
//  and interpolates materials between original slices
//  using distance fields.

class HXSEGEDITOR_API HxInterpolateLabelsM : public HxCompModule {

    HX_HEADER(HxInterpolateLabelsM);

public:
    HxInterpolateLabelsM();

    ~HxInterpolateLabelsM();

    HxPortMultiMenu portMaterial;
    HxPortIntTextN portInterSlices;

    HxPortFloatTextN portSliceDistance;

//    HxPortRadioBox portBorder;
    HxPortRadioBox portInterpolation;

    HxPortDoIt portAction;

    virtual void update();

    virtual void compute();

protected:
    /// input label field
    HxRegScalarField3* source;
    HxLattice3* lattice;
    HxLattice3* latticeOut;
    HxParamBundle* materials;
    int nA;

    /// parameters of input field
    int dimsIn[3];
    int ddims[2];
    int dnn;

    /// uniform or stacked label field?
    int isStacked;

    int outputIsStacked;

    int nMultipleInside, nNoInside;

    float voxelsize[3];
    float bbox[6];
    McVec3f origin,scale;
    McDArray<float> zCoordsIn;
    McDArray<float> zCoordsOut;
    McDArray<int> mapStackedSlices;

    /// output label field
    HxRegScalarField3* intpolField;
    McString labelOut;

    /// parameters of output field
    int dimsOut[3];

    /// intermediate slices
    int intslc,step;

    /// Run interpolation as batch job (1=on)
    int isBatch;

    /// Actual minimal value of distance field for all labels.
    McDArray<float> minDistAll;

    /// interpolate materials of input field
    void interpol();

    /// interpolate one material
    void interpol(int label);

    /// Propagate mask: find 'shallow' regions
    void propagateMask2d(McDArray<unsigned char> &mask);

    /// 2d laplace smoothing of distance field in 'shallow' regions
    void laplaceSmoothing(McDArray<float> &df,
                          McDArray<unsigned char> &mask);

    /// Modify distance field in interior regions
    void modifyInteriorRegions(McDArray< McDArray<float> > &df3);

    /// 3d propagation of distance field in exterior regions
    void propagateExterior(McDArray< McDArray<float> > &df3);

    /// 3d propagation of distance field in interior regions
    void propagateInterior(McDArray< McDArray<float> > &df3);

    /// 3d propagation of distance field
    void propagate3d(McDArray< McDArray<float> > &df3);

    /// interpolate one material (2.5d version)
    void interpol3d(int label, int allRegions);

    /// Initialize distance field (1)
    void initDistField1(int slice, int label, float* result);

    /// Initialize distance field (2) (not used)
    void initDistField2(int slice, int label, float* result);

    /// generate 2d distance field
    void genDistField(int slice, int label, float* result) ;

    /// smooth contour
    void smoothcontour(Contour2D& c2d, float z);

    /// detect empty slice: min(df) > 0
    int isEmptySlice(McDArray<float> &df);

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);
    int debug;
};

#endif

/// @}
