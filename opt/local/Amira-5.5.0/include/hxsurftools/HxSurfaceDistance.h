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

/// @addtogroup hxsurftools hxsurftools
/// @{
#ifndef HX_SURFACE_DISTANCE_H
#define HX_SURFACE_DISTANCE_H

#include <mclib/McBox3f.h>

#include <hxcore/HxCompModule.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortInfo.h>

#include <hxsurftools/HxSurfToolsWinDLLApi.h>


class HxSurface;


/// This module computes the one-sided Hausdorff-distance of 2 surfaces.
class HXSURFTOOLS_API HxSurfaceDistance : public HxCompModule {

  HX_HEADER(HxSurfaceDistance);
  
  public:
    /// Constructor.
    HxSurfaceDistance();

    /// Compute method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Connection to 2nd surface.
    HxConnection portSurface2;

    /// Optional ROI
    HxConnection portRoi;

    /// Switch between d(1,2), d(2,1) or two-sided.
    HxPortMultiMenu portDirection;

    /// Consider patches and/or boundary contours.
    HxPortToggleList portTopology;

    /// Maximal distance.
    HxPortFloatTextN portMaxDist;

    /// Maximal distance.
    HxPortFloatTextN portAboveThresh;

    /// Create displacement vector field and/or distance scalar field
    HxPortToggleList portOutput;

    /// Do it button.
    HxPortDoIt portAction;

    /// Info port for mean, dev, rms, and max.
    HxPortInfo portInfo;

    /// Info port for median, above threshold, and corr rms.
    HxPortInfo portInfo2;

    int parse(Tcl_Interp* t, int argc, char **argv);

    /// Recreate the resulting modules
    int canCreateData(HxData* data, McString& createCmd);

  protected:
    /// Destructor.
    ~HxSurfaceDistance();

    int id;

    /// Compute distance.
    void compDistance(HxSurface* surface1, HxSurface* surface2);

    // Array of all distances
    McDArray<float> distance;

    // region of interest
    McBox3f  roi;

    void evaluateDistance(HxSurface* surfaceA, HxSurface* surfaceB);

    float mean;
    float deviation;
    float rms;
    float max;
    float median;
    float aboveThresh;
    float corrRms;

    // Debug: for inverse displacements computation of surface2
    McDArray<int> tris;

};

#endif

/// @}
