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

/// @addtogroup hxcolor hxcolor
/// @{
#ifndef HX_STEREO_TEST_PATTERN_H
#define HX_STEREO_TEST_PATTERN_H

#include <hxcolor/HxColorWinDLLApi.h>

#include <mclib/McHandle.h>
#include <hxcore/HxModule.h>
#include <hxcore/HxController.h>
#include <hxcore/HxPortToggleList.h>
#include <Inventor/nodes/SoCallback.h>

class SoGLRenderAction;

/// Display custom text in viewer window.

class HXCOLOR_API HxStereoTestPattern : public HxModule {

  HX_HEADER(HxStereoTestPattern);

  public:
    /// Constructor.
    HxStereoTestPattern();

    /// Toggles checkerboard background on or off
    HxPortToggleList portPattern;

    /// Compute method.
    virtual void compute();

    /// Tcl-command interface.
    int parse(Tcl_Interp* t, int argc, char **argv);

    /// Empty, annotations are never clipped.
    virtual void clipGeom(HxPlanarMod* planarMod, int viewerMask = 0xffff);

    /// Size of text used for the annotation (default=14).
    int pointSize;

  protected:
    virtual ~HxStereoTestPattern();

    McHandle<SoCallback> callback;
    void render(SoGLRenderAction* renderAction);
    static void renderCallback(void* userData, SoAction* action);
};

#endif

/// @}
