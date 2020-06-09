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

/// @addtogroup hxneuro hxneuro
/// @{
#ifndef HXPROJECTIONVIEWCURSOR_H
#define HXPROJECTIONVIEWCURSOR_H

#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoTransform.h>

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortColorList.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxTightConnection.h>
#include <hxneuro/HxProjectionView.h>

class SoCoordinate3;
class SoLineSet;
class SoSeparator;
class SoMaterial;
class SoEventCallback;
class SoMouseButtonEvent;

/// Provides a 3D cursor for the projection view module
class HXNEURO_API HxProjectionViewCursor : public HxCompModule {

    HX_HEADER(HxProjectionViewCursor);

  protected:
    ~HxProjectionViewCursor();

    McHandle<SoSeparator> separator;
    McHandle<SoEventCallback> soEvent;
    McHandle<SoLineSet> soLineset;
    McHandle<SoSphere> sphere;
    McHandle<SoTransform> transform;
    McHandle<SoMaterial> material;
    McHandle<SoCoordinate3> coordinates;
    McHandle<HxProjectionView> pview;
    
    void makeGeom();
    void pickEvent(SoEventCallback* eventCB);    
    void addToLandmarks();
    void clearLandmarks();
    static void pickEventCB(void *userData, SoEventCallback *eventCB);
    McVec3f thePoint, theComputedPoint;
    McVec3i theIndex;

  public:
    /// Constructor.
    HxProjectionViewCursor();

    /// Color of the 3D cursor.
    HxPortColorList portColor;

    /// Options: 0=show 3D sphere
    HxPortToggleList portOptions;

    /// Size of the cursor sphere.
    HxPortFloatSlider portSize;

    /// Landmark set: 0=Add to, 1=Clear
    HxPortButtonList portLandmarkSet;
    
    /// Compute method.
    virtual void compute();

    /// Tcl-command interface.
    int parse(Tcl_Interp* t, int argc, char **argv);

    /// Save network support
    void savePorts(FILE* fp);

    /// Returns standard module color (lightgoldenrod)
    McColor getIconColor();
};

#endif

/// @}
