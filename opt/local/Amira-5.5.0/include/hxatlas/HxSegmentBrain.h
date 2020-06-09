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

/// @addtogroup hxatlas hxatlas
/// @{
#ifndef HX_SEGMENTBRAIN_H
#define HX_SEGMENTBRAIN_H

#include "hxatlasAPI.h"

#include <mclib/McVec3f.h>

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortButtonList.h>

class HxUniformScalarField3;
class HxUniformLabelField3;
class HxSurface;

// This module implements brain/background segmentation.
// [It assumes that the data's voxel unit is millimeter.]
class HXATLAS_API HxSegmentBrain : public HxCompModule {

  HX_HEADER(HxSegmentBrain);

  public:
    /// Constructor.
    HxSegmentBrain();

    ~HxSegmentBrain();

    /// Compute method.
    virtual void compute();

    /// Update method.
    virtual void update();

    /// A mask is used to compute the initial mean position
    HxConnection portMask;

    HxPortToggleList portExportSurface;

    /// Option menu
    HxPortToggleList portOptions;

    HxPortButtonList portReset;

    /// Advanced options (do not need to be changed)
    HxPortIntSlider   portIterations;
    HxPortRadioBox    portAutoCenter; // if set the center is computed autom.
    HxPortFloatSlider portEdgeLength; // should be 3.0
    HxPortFloatTextN  portCenter;     // initial position set by updateMask
    HxPortFloatSlider portBt;    
    HxPortFloatSlider portSmoothing; // smoothing factor is applied if its > 0
    HxPortFloatSlider portRMin;       // should be 3.33
    HxPortFloatSlider portRMax;       // should be 10
    HxPortFloatSlider portCSFPortion;           // part of the brain which is CSF
    HxPortFloatSlider portGrayPortion;          // part of the brain which is gray matter
    HxPortFloatSlider portSearchDistanceMinInt; // should be 7
    HxPortFloatSlider portSearchDistanceMaxInt; // should be 3
    HxPortRadioBox    portInterpolation;        // linear or tri-linear
    HxPortFloatSlider portInitialSphereRadius; // in mm
    HxPortIntSlider   portPostSurfaceSmooth; // smoothes the surface at the end of each Apply
    HxPortDoIt        portAction; // Starts or continues the computation

    struct image_description {
        McVec3f centerOfMass;
        float radius;
        float t2;  // robust min
        float t98; // robust max
        float t;
        float tm;  // median intensity inside the sphere
    };

    int canCreateData(HxData* data, McString& createCmd);

protected:
    void advanceOptions( bool visibility );
    void updateMask(HxUniformScalarField3* field);
    // as a side effect this function writes into id
    void updateMask(HxUniformScalarField3* field, float threshold, float t98, float t2);
    void prepareSurface(HxUniformScalarField3* field, bool reset = false); 
    void prepareSurface(HxUniformScalarField3* field, McVec3f position, float radius, float resolution, bool reset = false);
    void updateGradient(HxUniformScalarField3* field);
    void doStep(HxUniformScalarField3* field, HxSurface* surface);
    void convertToLabel(HxUniformScalarField3* field, HxSurface* surface);
    void storeInfo(HxParamBundle* b, HxUniformScalarField3* field);
    void classifyBrain(HxUniformScalarField3* field, HxUniformLabelField3 *labels);
    void smoothSurface(HxSurface* surface, int iterations);
    HxUniformScalarField3* MRF(HxUniformLabelField3* labels, HxUniformScalarField3* field, 
                               float tCSF, float tWhite);



    HxSurface* surface;
    McHandle<HxUniformLabelField3> mask;
    HxUniformLabelField3* brainLabel;
    image_description* id;

    bool needsReset;
};

#endif

/// @}
