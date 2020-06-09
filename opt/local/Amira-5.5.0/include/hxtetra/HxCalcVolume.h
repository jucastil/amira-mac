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

/// @addtogroup hxtetra hxtetra
/// @{
#ifndef HX_CALC_VOLUME
#define HX_CALC_VOLUME

#include <hxtetra/HxTetraWinDLLApi.h>
#include <hxcore/HxSpatialData.h>
#include <hxcore/HxTightConnection.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hxfield/HxTetraGrid.h>
#include <hxfield/HxTetraScalarField3.h>
#include <hxtetra/HxGridVolume.h>
#include <Inventor/SbLinear.h>

class PzPlot;
class PzAxis;
class PzPlotGroup;
class PzCurve;

class HXTETRA_API HxHistData {
public:
    HxHistData();
    virtual ~HxHistData();

    float           tHist;    // temperature 
    McDArray<float> absVol;   // absolute histogram
    McDArray<float> ratioVol; // relative histogram
    McDArray<float> diffVol;  // differential histogram

    void init(int n);
};

/// This class computes volume-dosis histograms.

class HXTETRA_API HxCalcVolume : public HxModule
{
    HX_HEADER(HxCalcVolume);
  
public:
    /// Constructor.
    HxCalcVolume();

    /// Update method.
    void update();

    /// Compute method.
    void compute();

    /// Autoconnect.
    virtual int autoConnect(HxObject* primary);

    /// Connection to grid volume module (used to select tetrahedra)
    HxTightConnection portGridVol;

    /// Histogram modes: 0=absolute 1=relative 2=differential
    HxPortToggleList portHistToggle;

    /// This port controls number of bins of histogram.
    HxPortIntSlider portSlider;
    
    static void nullPlotWin(HxCalcVolume *, PzPlot *);
 
    /// used by HxPlotWindowInterfaceProxy
    PzPlot* doGetPlotWindow(int idx = 0);

    /// used by HxPlotWindowInterfaceProxy
    int doGetNumPlotWindows() { return 3; }

protected:
    ~HxCalcVolume();

    HxGridVolume* gridVolume; 
    HxTetraScalarField3* tField;	// temperature field
    HxTetraGrid* grid;        		// grid data

    PzPlot *plotWinA;           	// Plot Class
    PzPlot *plotWinR;           	// Plot Class
    PzPlot *plotWinD;           	// Plot Class
    PzCurve **curvesPlotWinA;
    PzCurve **curvesPlotWinR;
    PzCurve **curvesPlotWinD;
    PzPlotGroup *groupPlotWinA;
    PzPlotGroup *groupPlotWinR;
    PzPlotGroup *groupPlotWinD;

    McDArray<float> tetVol;        // volume of each tetrahedron, unselected!
    McDArray<float> matVol;        // total volume per material
    int numMat;      	           // number of materials
    int numTetSel;   	           // number of selected tetrahedrons
    McDArray<signed char> tetSel;  // mark selected tetrahedrons 
    int oldnTetras;  	           // nTetras of last loop
    int numTicks;    	           // number of ticks
    int newSelFlag;  	           // indicates whether selection has changed
    McDArray<int> matSel;          // includes, whether material is selected
    int oldPort[3];  	           // old state of ports 
    int newPort[3];  	           // new state of ports
    int compNew;     	           // recompute if anything has changed
    float distance;    	           // distance between two ticks
    float min, max;    	           // minimum and maximum value of temperature
    int fieldDataType;             // 0 arbitrary data, 1 temperature, 2 SAR
    McDArray<HxHistData> hist;

    int newSelected ();
    void calcSelectedVolume ();
    void getMinMaxSelected(McDArray<McVec4f> &tempField);
    void histogram ();
    float volumeTetrahedron(McVec3f *);
    void setPlotProperties(int matIndex);
    void setAxisAttributes(PzAxis *axis, 
                           float xmin, float xmax, 
                           float ymin, float ymax);
    void plotCurves(void);
    void clearPlotWindows(void);

private:
    PzPlot* createPlotWin(char *title, PzPlotGroup *group);
};


#endif

/// @}
