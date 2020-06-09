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
#ifndef HXINTERPOLATE_LABELS_H
#define HXINTERPOLATE_LABELS_H

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortRadioBox.h>

#include "HxGiWinDLLApi.h"
#include "GiSelection3D.h"
#include <hxfield/HxUniformLabelField3.h>

#include <mclib/McVec2f.h>
#include <mclib/McData3D.h>

class HXSEGEDITOR_API HxInterpolateLabels : public HxCompModule {

    HX_HEADER(HxInterpolateLabels);

public:
    HxInterpolateLabels();
    
    ~HxInterpolateLabels();

    HxPortMultiMenu portMaterial;
    HxPortIntTextN portInterSlices;
    HxPortRadioBox portAlgorithm;
    HxPortRadioBox portSpeed;
    
    HxPortButtonList portAction;
    
    virtual void update();

    virtual void compute();
    
protected:
    /// input label field
    HxUniformLabelField3* source;
    HxParamBundle* materials;
    int nA;
    
    /// parameters of input field
    int dimsIn[3];
    float voxelsize[3];
    float *bbox;
    McVec3f origin,scale;

    /// output label field
    HxUniformLabelField3* intpolField;
    McString labelOut;
    
    /// parameters of input field
    int dimsOut[3];
    
    /// intermediate slices
    int intslc,step;
    
    /// Run interpolation as batch job (1=on)
    int isBatch;

    int speed;

    /// interpolate materials of input field
    void interpol();
    
    /// interpolate one material
    void interpol(int label);

    int interpolateBlock(int j, McData3D<float>& avgFunc, int label, int s2, int mode);

    /// .
    void getProcessingSeq(McDArray<unsigned char>& labelSeq);
    
    /// .
    //void interpolDistField(McData3D<unsigned char>* data3D);
    void interpolDistField(GiSelection3D* data3D);
    
    /// Submit interpolation as batch job
    void submitBatchJob(void);

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);
};

#endif

/// @}
