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

/// @addtogroup hxmolecule hxmolecule
/// @{
#ifndef HX_MOL_OBSERVABLES_H
#define HX_MOL_OBSERVABLES_H

#include <hxcore/HxModule.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortRadioBox.h>

#include <hxtime/HxPortTime.h>

#include <hxplot/PzPlot.h>
#include <hxmolecule/MolAlignment.h>
#include <hxmolecule/HxMolTrajectory.h>
#include <hxmolecule/HxMoleculeWinDLLApi.h>

/** This class represents a tool for displaying properties of
    molecular trajectories over time. */

class HXMOLECULE_API HxMolObservables : public HxModule {
    
    HX_HEADER(HxMolObservables);

public:    
    /// Option port.
    HxPortRadioBox portOption;
    /// Alignment port.
    MolAlignment alignment;
    /// 0=logarithmic boxes 1=show plot
    HxPortMultiMenu portObservables;
    /// Separate .
    HxPortSeparator portSep;
    /// 0=reset range
    HxPortButtonList portAction;
    /// Display probe values.
    HxPortToggleList portPlotoptions;
    /// Shows a line in the plot at a certain time step.
    HxPortTime portTime;

private:
    // Auxiliary struct.
    struct PlotRecord {
        McHandle<PzPlot> plot;
    };
    
    // Current trajectory.
    McHandle<HxMolTrajectory> theTrajectory;
    // Array of currently open plots.
    McDArray<PlotRecord> thePlots;
    // RMSD plot.
    PlotRecord rmsdPlot;
    // to keep track of changes to first plot option
    int probeValueFlag:8;
    // to keep track of changes to second plot option
    int singlePlotFlag:8;
    // old observable
    int singlePlotId;
    // single plot
    PlotRecord singlePlot;

    // Sets new time step.
    void setTimeStep(PzPlot * plot);
    // Update plot according to new data.
    bool updatePlot(PzPlot * plot, int rmsdPlot=0);
    // Fills data for plot.
    bool fillData(McDArray<float> & dataX, McDArray<float> & dataY,
                  McString & name, int rmsdPlot=0);

public:
    /// This constructor leaves type list of portData empty.
    HxMolObservables();
    // Virtual destructor
    virtual ~HxMolObservables();

    /// Info function (overloaded). 
    void info();
    /// Update function (overloaded). 
    void update();
    /// Compute function (overloaded). 
    void compute();

};

#endif

/// @}
