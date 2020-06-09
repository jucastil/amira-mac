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
#ifndef HX_PLOT2COLORFIELD_H
#define HX_PLOT2COLORFIELD_H

#include <hxplot/PzPlotWinDLLApi.h>

#include <mclib/McColor.h>
#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortButtonList.h>

class PzPlot;
class HxUniformColorField3;

/// Displays a plot window within Amira's viewer

class HXPLOT_API HxPlot2ColorField : public HxCompModule {

    HX_HEADER(HxPlot2ColorField);

  public:

    /// Constructor.
    HxPlot2ColorField();

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    ///
    virtual int autoConnect(HxObject* primary);

    /// To select plot window ~n case of more than one plot window
    HxPortMultiMenu portWhichPlot;

    /// Options: 0=draw frame around plot, 1=transparent background
    HxPortToggleList portOptions;
    enum { ANTIALIAS=0 };

    /// To adjust transparency
    HxPortFloatSlider portTransparency;

    /// To set antiAlias factor
    HxPortIntSlider portAntiAlias;

    /// Size of rectangle in pixels or relative to 1000x1000 window.
    HxPortFloatTextN portResolution;

    /// Open the plot window edit window or show/hide the original plot window
    HxPortButtonList portActions;
    enum { EDIT=0 };

    /// saves settings
    void savePorts(FILE* fp);

    /// Tcl-command interface.
    int parse(Tcl_Interp* t, int argc, char** argv);

  protected:

    virtual ~HxPlot2ColorField();

    int width, height;

    McColor bgColor;

    int numPlotWindows;
    int whichPlotWindow;
    PzPlot* plotWindow;
    HxUniformColorField3* colorField;

    void createPlotImage(bool fromCallback);

    static void plotUpdateCallback(PzPlot* plotmodule, void* clientdata);
};

#endif

/// @}
