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
#ifndef HX_POINT_PROBE
#define HX_POINT_PROBE

#include <hxdataprobe/HxDataProbe.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortButtonList.h>
#include <hxfield/HxTetraGrid.h>
#include <hxfield/HxLoc3Tetra.h>
#include <hxfield/HxScalarField3.h>
#include <hxfield/HxVectorField3.h>
#include <hxfield/HxComplexVectorField3.h>

//#define POINTPROBE_CREATECLUSTER
#ifdef POINTPROBE_CREATECLUSTER
#  include <hxcluster/HxCluster.h>
#endif

class PzPlotGroup;
class PzPlotArea;
class PzCurve;
class PzPlot;
class PzAxis;
class PzPolarAxis;
class PzBaseAxis;

///
class HXDATAPROBE_API HxPointProbe : public HxDataProbe {

  HX_HEADER(HxPointProbe);
  
  public:
    ///
    HxPointProbe();

    ///
    HxPortToggleList portAverage;

    ///
    HxPortFloatSlider portRadius;

    ///
    HxPortButtonList portPlotWinButton;

    ///
    virtual void update();

    ///
    virtual void compute();

    ///
    void info();

    /// used by HxPlotWindowInterfaceProxy
    PzPlot* doGetPlotWindow(int idx = 0) { return myPlotWin; }

    /// used by HxPlotWindowInterfaceProxy
    int doGetNumPlotWindows() { return 1; }

    /** Reimplemented for internal reasons. The method shows or hides
        the plot window. Afterwards, it calls HxModule::setViewerMask(). */
    virtual void setViewerMask(int mask, int master=0xffff);

    ///
    void savePorts(FILE* fp);

    ///
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /** Get scalar value (1st component's value in case of vector field)
	for the currently selected 3D point.
    */ 
    float  getCurrentScalarValue() const
    {
	    return sampledValue[0];
    }
	    
  protected:

    ~HxPointProbe();

    int                 inGrid, numVals;
    McDArray<float>     sampledValue;

    PzPlotGroup        *pointprobeGroup;
    PzPlotArea         *anchor;
    PzCurve            *result;
    PzBaseAxis         *axis;
    PzAxis             *caxis;
    PzPolarAxis        *paxis;
    PzPlot             *myPlotWin;
    bool                usePolarAxis;

#ifdef POINTPROBE_CREATECLUSTER
    HxCluster *cluster;
#endif

  private:

    void getAverage(SbVec3f &pCurr, McDArray<float>& sVals);

    void commonInit();

    int getSample(SbVec3f point);

    void checkPlotWin();

    static int storeVals(float *to, float *from, SbVec3f norm, int type,
                         int vcomp, int skip);

    float              *myColours;
    float               sample[6];
    bool                plotButtonPressed;
};

#endif // HX_POINT_PROBE

/// @}
