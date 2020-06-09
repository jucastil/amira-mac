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
#ifndef HX_SLICEHISTOGRAM_H
#define HX_SLICEHISTOGRAM_H

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxfield/HxRegScalarField3.h>
#include <hxstatistics/HxStatisticsWinDLLApi.h>
#include <hxcore/HxPortDoIt.h>

#define MAX_BUFFER 5

class PzEasyPlot;
class PzPlot;

/// Computes the histogram and other statistical properties of a data set.

class HXSTATISTICS_API HxSliceHistogram : public HxCompModule {

  HX_HEADER(HxSliceHistogram);
  
  public:
    /// Constructor
    HxSliceHistogram();

    /// Update method
    virtual void update();

    /// Compute method
    virtual void compute();

    /// Options: 3d, slices
    HxPortRadioBox portMode;
    enum { VOLUME=0, SLICES=1 };

    /// Number of the current slice (if slices selected)
    HxPortIntSlider portSlice;

    /// 0=add slice to the histo buffer, 1=empty histo buffer
    HxPortDoIt portBuffer;

    /// Represents the polynomial adjustment function
    HxPortFloatSlider portAttenuation;

    /// 
    HxPortRadioBox portDirection;
    enum { BOTTOM_UP=0, TOP_DOWN=1 };

    /// 0=show or hide plot window, 1=reset range
    HxPortDoIt portAction;

    /// For the plot interface
    PzPlot* doGetPlotWindow(int idx=0) { return (PzPlot*)theHistogramPlotWin; }

    /// used by HxPlotWindowInterfaceProxy
    int doGetNumPlotWindows() { return 1; }

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

  protected:
    ~HxSliceHistogram();

    void createPlotWindow();
    void computeHistogram();
    void updateHistogram();
    void doExport();
    void computeHistogramIterrupted();

    bool isHistogramUpToDate;
    PzEasyPlot  *theHistogramPlotWin;

    int zSlices, bins, deleteHistogram, oldMode, newSlice;
    int sliceBufferSize, sliceBuffer[MAX_BUFFER], sliceBufferNew[MAX_BUFFER];
    float histogramMinRange, histogramMaxRange, quant;
    float *histogramRange, *histogramValues;
};

#endif

/// @}
