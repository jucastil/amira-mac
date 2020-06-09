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

/// @addtogroup hxdataprobe hxdataprobe
/// @{
#ifndef HX_LINESET_PROBE
#define HX_LINESET_PROBE

#include <hxdataprobe/HxDataprobeWinDLLApi.h>
#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortFloatSlider.h>

class PzPlot;
class HxSplineProbe;
class HxLineSetProbeNotifier;

class HXDATAPROBE_API HxLineSetProbe : public HxCompModule 
{

    HX_HEADER(HxLineSetProbe);

public:
    ///
    HxLineSetProbe();

    ///
    HxConnection  portLineSet;

    ///
    HxPortRadioBox portVectorComp;
    
    ///
    HxPortToggleList portAverage;
    
    ///
    HxPortFloatSlider portRadius;
    
    ///
    HxPortFloatSlider portLongitudWidth;

    ///
    HxPortButtonList portSamplesButton;

    ///
    virtual void update();
    
    ///
    void info();

    /// returns the dimension of the sample values
    int nDataVar();

    /// used by HxPlotWindowInterfaceProxy
    PzPlot* doGetPlotWindow(int idx = 0);

    /// used by HxPlotWindowInterfaceProxy
    int doGetNumPlotWindows();

    /** Reimplemented for internal reasons. The method shows or hides
        the plot window. Afterwards, it calls HxModule::setViewerMask(). */
    virtual void setViewerMask(int mask, int masterMask=0xffffffff);

    ///
    virtual int parse(Tcl_Interp* t, int argc, char **argv);
protected:

    virtual ~HxLineSetProbe();

    void storeData();
private:
    void setNumProbe(int n);

    McDArray<HxSplineProbe*> mSplineProbe;
    HxLineSetProbeNotifier* mPortNotifier;
};

#endif // HX_LINESET_PROBE


/// @}
