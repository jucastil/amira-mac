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

/// @addtogroup hxmolview hxmolview
/// @{
#ifndef HX_MEASUREMENT_H
#define HX_MEASUREMENT_H

#include <hxmolview/HxMolView.h>
#include <molecule/MolTrajectory.h>
#include <hxmolecule/HxMolecule.h>

#include <hxmolview/HxMolViewWinDLLApi.h>

#include <hxcore/HxModule.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortSeparator.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxConnection.h>

#include <hxplot/PzPlot.h>
#include <hxplot/PzAxis.h>
#include <hxplot/PzLegend.h>
#include <hxplot/PzCurve.h>
#include <hxplot/PzMarkerline.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransform.h>

#include <mclib/McDArray.h>

class ShapeView;

struct PlotRecord {
    McDArray<int> currentAtoms; 
    PzPlot* plot;
    PzPlotArea* tAnchor;
    PzAxis* tAxis;
    PzCurve* tCurve;
    PzMarkerline* tMl;
    PzMarkerline* tMeanMl;
    PzMarkerline* tStdDerMl1;
    PzMarkerline* tStdDerMl2;
    PzPlotArea* hAnchor;
    PzAxis* hAxis;
    PzCurve* hCurve;
    PzMarkerline* hMl;
    PzMarkerline* hMeanMl;
    PzMarkerline* hStdDerMl1;
    PzMarkerline* hStdDerMl2;
};

///
class HXMOLVIEW_API HxMeasurement : public HxModule {
    HX_HEADER(HxMeasurement);
public:
    float mean;
    float stdDev;
    // Connection to planar module
    HxConnection portData2;

    /// Selection info-Port
    HxPortInfo selectInfo;
    /// Measurement info-Port
    HxPortInfo measInfo;
    /// Measurement Mean Value Info-Port
    HxPortInfo measTrajectoryInfo;
    /// Options.
    HxPortToggleList portOptions;
    /// Measurement button-Port
    HxPortButtonList measTrajectoryButtons;
    HxPortSeparator sep1;
    HxPortText portObservableName;
    HxPortButtonList observableButtons;
    HxPortSeparator sep2;

    /// View Options
    HxPortToggleList portLengthViewOptions;
    HxPortToggleList portAngleViewOptions;
    HxPortToggleList portDihedralViewOptions;
    HxPortIntSlider portTextSize;
    /// Selection button-Port
    HxPortButtonList selectButtons;

    /// current source viewer
    McHandle<HxMolView> molView;
    /// current source molecule 
    McHandle<HxMolecule> mol;
    McHandle<HxMolecule> mol2;
    ///
    McHandle<Molecule> M;
    /// current source tracectory (NULL if none existing)
    McHandle<MolTrajectory> trajectory;

    /// Structure with pointers to plot elements 
    PlotRecord plot;
   
    /// root separator
    McHandle<SoSeparator> root;
    SoSeparator* sep;

    /// transform node -> transform is set to transform of molecule
    McHandle<SoTransform> transform;

    /// list of object viewers
    McDArray<McHandle<ShapeView> > views;

    /// Constuctor
    HxMeasurement();

    /// Destructor
    ~HxMeasurement();

    /// Update method.
    virtual void update();
    
    /// Compute method.
    virtual void compute();

    /// Show a time plot of a measurement defined by the list of atomIndices
    /// @c atomList for a trajectory
    void timePlot(const McDArray<McVec3i>& atomList);
    ///
    void createObservable(const McDArray<McVec3i>& atomList) ;
    /// return the value of a measurement
    float measure(const McDArray<McVec3f>& co) const;
    void calcMeanValue(const McDArray<McVec3i>& atomList) ;

    /// distance calculation for a list of 2 atom indices 
    float distance(const McDArray<McVec3f>& co) const;
    /// angle calculation for a list of 2 atom indices 
    float angle(const McDArray<McVec3f>& co) const;
    /// 
    float dihedral(const McDArray<McVec3f>& co) const;
    

    void atomIdToCoodinates(const McDArray<McVec3i>& id,McDArray<McVec3f>& co,bool traj=false);
    /// methods for creating measurement graphics
    void viewAngle(const McDArray<McVec3f>& co);
    void viewLine(const McDArray<McVec3f>& co);
    void viewPlanes(const McDArray<McVec3f>& co);
    void viewText(const McDArray<McVec3f>& co,const char* text);

    /// methods used by the plot interface
    PzPlot* doGetPlotWindow(int idx = 0) { return plot.plot; }
    int doGetNumPlotWindows() { return 1; }

    // is update method running for the first time?
    bool first;

};

#endif

/// @}
