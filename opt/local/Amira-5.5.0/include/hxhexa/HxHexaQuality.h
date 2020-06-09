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

/// @addtogroup hxhexa hxhexa
/// @{
#ifndef _HX_HEXA_QUALITY_
#define _HX_HEXA_QUALITY_

#include <hxcore/HxCompModule.h>
#include <hxhexa/HxHexaWinDLLApi.h>
#include <hxcore/HxSpatialData.h>
#include <hxcore/HxTightConnection.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxfield/HxHexaGrid.h>
#include <hxhexa/HxHexaView.h>
#include <Inventor/SbLinear.h>
#include <mclib/McDArray.h>

class PzPlot;
class PzPlotGroup;
class PzCurve;

class HXHEXA_API HxHistDataTQ {
public:
    HxHistDataTQ () { };
    HxHistDataTQ (int n);
    virtual ~HxHistDataTQ ();

    float tHist; 
    int *kommVol;  // absolute histogram
protected:
    void commonInit ();
    int numMat;
};

/// Analyses quality of a hexahedral grid.

class HXHEXA_API HxHexaQuality : public HxCompModule {

    HX_HEADER(HxHexaQuality);
  
  public:
    /// Constructor.
    HxHexaQuality();

    /// Shows or hides ports as necessary.
    void update();

    /// Compute method.
    void compute();

    /// Autoconnect.
    virtual int autoConnect(HxObject* primary);

    /// Supported quality measures.
    enum QualityMeasure {
	/// Diameter ratio.
	SQUISH=0,
	/// Aspect ratio.
	EQUIANGLE,
	/// Dihedral angle.
	MAX_ANGLE,
	/// Solid angle.
	MIN_ANGLE,
	/// Edge length.
	ASPECT_RATIO
    };
    
    HxPortDoIt portAction;

    /// Connection to grid volume module (selects hexahedra).
    HxTightConnection portGridVol;
    
    /// Determines the quality measure to be used 
    HxPortMultiMenu portQuality;

    /// Select number of samples for histogram.
    HxPortIntSlider portSlider;

    /// Shows or hides the histogram plot window.
    HxPortToggleList portHistToggle;

    static void nullPlotWin(HxHexaQuality *, PzPlot *);

    int parse(Tcl_Interp* t, int argc, char **argv);

    /// used by HxPlotWindowInterfaceProxy
    PzPlot* doGetPlotWindow(int idx = 0) { return plotWinA; }

    /// used by HxPlotWindowInterfaceProxy
    int doGetNumPlotWindows() { return 1; }

  protected:

	~HxHexaQuality();

    HxHexaGrid* grid;
    HxHexaView* gridVolume; 
	  
    McDArray<float> m_hexaQuality; // quality per hexahedron

    PzPlot *plotWinA;           // Plot Class
    PzCurve **curvesPlotWinA;
    PzPlotGroup  *groupPlotWinA;

    int 
    numMat,      // number of materials
	  numHexSel,   // number of selected hexahedrons
	  numTicks;    // number of ticks

    McDArray<unsigned char> lastSelected;
    McDArray<unsigned char> matSel;

    int
    newSelFlag,  // indicates whether selection has changed
    oldPort,  // old state of ports 
    newPort,  // new state of ports
    compNew;     // recompute if anything has changed
    float 
    distance,      // distance between two ticks
    m_min, m_max;      // x-range of histogram

    QualityMeasure theQualityMeasure;

    HxHistDataTQ **hist;

    int newSelected ();
    void calcSelectedVolume ();
    void histogram ();
    void setPlotProperties(int matIndex);
    void plotCurves(void);
    void clearPlotWindows(void); 

private:

    PzPlot *createPlotWin(char *title, PzPlotGroup *group);

    float largestAngle(const McDArray<McVec3f> &faceNodes);

    float smallestAngle(const McDArray<McVec3f> &faceNodes);

    void largestAndSmallestAngle(const McDArray<McVec3f> &faceNodes,
                                                      float &minAngle,
                                                      float &maxAngle);

    float nodeMinimumDistance(const McDArray<McVec3f> &cellNodes);
};


#endif

/// @}
