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

/// @addtogroup hxlattice hxlattice
/// @{
#ifndef HX_VOXELSEGMENTATION
#define HX_VOXELSEGMENTATION

#include <hxlattice/HxLatticeWinDLLApi.h>

#include <mclib/McString.h>
#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxfield/HxUniformScalarField3.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortText.h>

class PzPlot;
class PzPlotGroup;
class PzPlotArea;
class PzAxis;
class PzCurve;


/// Implements simple threshold segmentation.

class HXLATTICE_API HxLabelVoxel : public HxCompModule {

  HX_HEADER(HxLabelVoxel);

  public:
    /// Constructor
    HxLabelVoxel();

    /// Update method
    virtual void update();

    /// Compute method
    virtual void compute();

    /// Sets quantization value for histogram.
    void setQuant(int value = 10);

    /// Blank separated list of regions to be extratced.
    HxPortText portRegions;

    /// Boundary between 1. and 2. region.
    HxPortIntSlider portBoundary01;

    /// Boundary between 2. and 3. region.
    HxPortIntSlider portBoundary12;

    /// Boundary between 3. and 4. region.
    HxPortIntSlider portBoundary23;

    /// Boundary between 4. and 5. region.
    HxPortIntSlider portBoundary34;

    /// Options: histogram, remove couch
    HxPortToggleList portOptions;
    enum { SUBVOXEL=0, REMOVECOUCH=1, BUBBLES=2 };

    /// Do it button.
    HxPortDoIt portDoIt;

    /// Action button
    HxPortButtonList portAction;

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    ///
    void savePorts(FILE* fp);

    /// used by HxPlotWindowInterfaceProxy
    PzPlot* doGetPlotWindow(int idx = 0) { return theHistogramPlotWin; }

    /// used by HxPlotWindowInterfaceProxy
    int doGetNumPlotWindows() { return 1; }

  protected:
    ~HxLabelVoxel();

    void doIt();
    void updateHistogram(int);
    int updateBoundaryPorts();
    void removeCouch(int nx, int ny, int nz, unsigned char* vol);

    int theMin, theMax;
    HxLattice3* lattice;

    virtual int canCreateData(HxData* data, McString& createCmd);

  private:
    void createPlotWin();
    void initHistogram();
    void plotHistogram(int);

    void configureCT();
    void configureMR();
    void configureMono();
    void configureUnsignedCT();

    int histogramIsUpToDate;
    int histogramLength;
    int quantHistogramLength;

    float *histogramRange, *histogramValues;
    float theHistogramMinRange, theHistogramMaxRange;
    int quant;
    int doPlot;

    int numRegions;
    int limits[4];
    McString regionNames[5];

    PzPlot      *theHistogramPlotWin;
    PzPlotGroup *histogram;
    PzPlotArea  *anchor;
    PzAxis      *axis;
    PzCurve     *curve[5];
};

#endif

/// @}
