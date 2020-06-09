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

/// @addtogroup hxstatistics hxstatistics
/// @{
#ifndef HX_CORRELATION_PLOT
#define HX_CORRELATION_PLOT

#include <mclib/McString.h>
#include <mclib/McColor.h>

#include <hxcore/HxCompModule.h>

#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortSeparator.h>

#include <hxfield/HxPortChannelConfig.h>

#include <hxcolor/HxPortColormap.h>
#include <hxcolor/HxColormap256.h>
#include <hxcolor/HxColormap.h>

#include <hxfield/HxUniformScalarField3.h>
#include <mclib/McVec2f.h>

class PzPlot;
class PzEasyPlot;
class PzLattice;
class PzAnnotation;
class PzAxis;
class PzCurve;
class PzPlotGroup;
class PzPlotObject;
class HxColormap;
class HxColormap256;
class HxPortColormap;
class HxMultiChannelField3;

/// Implements 2D histogram segmentation.

class HxCorrelationPlot : public HxCompModule 
{
    HX_HEADER(HxCorrelationPlot);
  
public:

    /// Constructor
    HxCorrelationPlot();

    /// Destructor
    ~HxCorrelationPlot();

    /// 
    int autoConnect( HxObject * primary );

    /// Update method
    void update();

    /// Compute method
    void compute();

    /// Saves state of portAction (is there a plot window or not)
    void savePorts(FILE* fp);

    /// used by HxPlotWindowInterfaceProxy
    PzPlot* doGetPlotWindow(int idx=0) { return (PzPlot*)theHistogramPlotWin; }

    /// used by HxPlotWindowInterfaceProxy
    int doGetNumPlotWindows() { return 1; }

    /// Tcl command interface.
    int parse(Tcl_Interp* t, int argc, char **argv);

    /// timeout method for computing selection data
    void selectionComputeTimeout();


private:

    /// Callback method. It is called by PzPlot to select a region
    static void plotInputCB(PzPlot* plotmodule, void* clientdata, 
                            PzPlotObject* pobj, McDArray<float>x,
                            McDArray<float>y);

    /// Create (if not already exists) the Histogram plot window with everything inside it
    void createTheHistogramPlotWin();

    /// scan convert regions to quickly idfentify selected pixels.
    void getLabelsFromRegions();

    /// extract label field.
    void extract();

    /// compute number of selected voxels and store value in _histogramSelectCount
    void selectionCompute();
    void selectionComputeSchedule();

    ///
    void adjustNumBins(HxPortFloatTextN&);
    
    ///
    void histogramClear();

    ///
    void histogramAlloc( mclong inWidth, mclong inHeight );

    /// compute histogram from input data
    void histogramCompute();

    /// transfers the histogram data to the plot window
    void histogramShow();

    /// get ranges
    void getRange(HxLattice3* lattice, double& fmin, double& fmax, float& nmin, float& nmax);

    ///
    void plotInputCallBack(PzPlotObject* pobj, McDArray<float>x, McDArray<float>y);
    
    ///
    void infoUpdate();

    ///
    void rangeCurvesUpdate();

private:

    /// Second input field (optional).
    HxConnection        portData2;

    /// Defines scaling for the first input field X'(x,y,z) = SCALE * ( X(x,y,z) + OFFSET )
    HxPortFloatTextN    portInput1;

    /// Defines scaling for the seccond input field X'(x,y,z) = SCALE * ( X(x,y,z) + OFFSET )
    HxPortFloatTextN    portInput2;

    /// Defines the value of the gamma correction applied to the histogram
    HxPortFloatSlider   portGammaCorrection;

    /// Colormap (if this is a scalar field).
    HxPortColormap      portColormap;

    /// type of selection
    HxPortRadioBox      portSelectionType;

    // first selection type - manual selection

    /// clear manual regions
    HxPortButtonList    portClear;

    // second selection type - selection by range

    /// range first input
    HxPortFloatTextN    portRange0;
    /// range second input
    HxPortFloatTextN    portRange1;

    /// 
    HxPortSeparator     portSep;

    /// The buttons ShowHistogram and CreateLabelField.
    HxPortButtonList    portAction;

    ///
    HxPortInfo          portInfo0;
    HxPortInfo          portInfo1;
    HxPortInfo          portInfo2;
    HxPortInfo          portInfo3;
    HxPortInfo          portInfo4;
    HxPortInfo          portInfo5;
    HxPortInfo          portInfo6;


    HxLattice3            * _lattice0;
    HxLattice3            * _lattice1;
    McColor                 _color0;
    McColor                 _color1;
    HxColormap256         * _histoCmap;
    
    float                   _gammaCorrection;
    bool                    _isHistogramUpToDate;
    bool                    _isInfoUpToDate;
    bool                    _isSelectCountUpToDate;

    float                   _histogramMin[2];
    float                   _histogramMax[2];
    int                     _histogramDims[2];

    McDArray<mculong>       _histogramData;
    McDArray<mculong>       _histogramInput0;
    McDArray<mculong>       _histogramInput1;
    McDArray<unsigned char> _histogramLabels;
    McDArray<float>         _histogramPlotedData;
    float                   _histogramMSE;          // mean-square-error
    float                   _histogramPSNR;         // peak-signal-noise-ratio   1e20 if infinite
    mculong                 _histogramDataMaxVal;   // maximal value in histogram 
    mculong                 _histogramInputCount0;  // number of voxels in input0 range
    mculong                 _histogramInputCount1;  // number of voxels in input1 range
    mculong                 _histogramInputCount;   // number of voxel pairs in booth ranges -> accepted for the histogram
    mculong                 _histogramSelectCount;  // number of selected voxel pairs in regions or in ranges0+1
    mculong                 _histogramSelectCount0; // number of selected voxel pairs in range 0
    mculong                 _histogramSelectCount1; // number of selected voxel pairs in range 0
    float                   _histogramInputVarianz0;// varianz input0 of input  (1/n-1) * Sum i[1..n] ( (xi-xmean)^2 )
    float                   _histogramInputVarianz1;// varianz input1 of input  (1/n-1) * Sum i[1..n] ( (yi-ymean)^2 )
    float                   _histogramInputCoVarianz;// covarianz of input0 and input1
    float                   _histogramInputCorr;    // input correlation


    /// all regions, selected by the user in PzPlot: exterior, Material 1..n
    McDArray< McDArray<McVec2f> >   _regions;

    /// plot stuff
    int                     _plotNeedUpdate;
    PzEasyPlot            * theHistogramPlotWin;
    PzLattice             * histoLattice;
    PzAxis                * histoAxis;
    PzPlotGroup           * regionsgroup;
    PzPlotGroup           * rangegroup;
    PzCurve               * rangecurve0;
    PzCurve               * rangecurve1;
    PzCurve               * rangecurve2;
    PzCurve               * rangecurve3;
    PzCurve               * rangecurve;
};

#endif

/// @}
