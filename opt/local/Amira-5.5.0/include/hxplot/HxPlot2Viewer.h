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

/// @addtogroup hxplot hxplot
/// @{
#ifndef HX_PLOT2VIEWER_H
#define HX_PLOT2VIEWER_H

#include <hxplot/PzPlotWinDLLApi.h>

#include <Inventor/SbLinear.h>
#include <Inventor/nodes/SoCallback.h>

#include <mclib/McHandle.h>
#include <mclib/McColor.h>
#include <hxcore/HxModule.h>
#include <hxcore/HxTightConnection.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortDoIt.h>

class PzPlot;

/// Displays a plot window within Amira's viewer

class HXPLOT_API HxPlot2Viewer : public HxModule {

  HX_HEADER(HxPlot2Viewer);

  public:

    /// Constructor.
    HxPlot2Viewer();

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    ///
    virtual int autoConnect(HxObject* primary);

    /// To select plot window ~n case of more than one plot window
    HxPortMultiMenu portWhichPlot;

    /// Options: 0=draw frame around plot, 1=transparent background
    HxPortToggleList portOptions1;
    enum { WITHFRAME=0, TRANSPBG=1 };

    /// Options: 0=position rel to viewer in ndc, 1=cycle position
    HxPortToggleList portOptions2;
    enum { RELPOS=0, CYCLEPOS=1 };

    /// To adjust transparency
    HxPortFloatSlider portTransparency;

    /// X and y position in pixel, negative values relative to right and top.
    HxPortIntTextN portPosition;

    /// X and y position in normalised coordinates.
    HxPortFloatTextN portNdcPosition;

    /// Size of rectangle in pixels or relative to 1000x1000 window.
    HxPortFloatTextN portSize;

    /// Open the plot window edit window or show/hide the original plot window
    HxPortButtonList portActions;
    enum { EDIT=0, SHOWPLOTWIN=1 };

    /// saves settings
    void savePorts(FILE* fp);

    /// Tcl-command interface.
    int parse(Tcl_Interp* t, int argc, char** argv);

  protected:

    virtual ~HxPlot2Viewer();

    int width, height;
    int orgx, orgy;

    McColor frColor, bgColor;
    McHandle<SoCallback> callback;

    int numPlotWindows;
    int whichPlotWindow;
    PzPlot* plotWindow;
    unsigned char* plotImage;
    int numChannels;

    bool showExtraPlotWindow;

    void getPlotImage(bool fromCallback);

    void render(SoGLRenderAction* renderAction);

    static void plotUpdateCallback(PzPlot* plotmodule, void* clientdata);

    static void renderCallback(void* userData, SoAction* action);
};

#endif

/// @}
