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
#ifndef HX_DATA_PROBE_PLOT_WINDOW
#define HX_DATA_PROBE_PLOT_WINDOW

#include <hxplot/PzPlot.h>

#include <mclib/McString.h>
#include <mclib/McColor.h>
#include <mclib/McHashTable.h>

#define theSplineProbePlotWin HxDataProbePlotWindow::getInstance()

class PzAxis;
class PzPlotGroup;
class HxSplineProbe;
class PzCurve;
class QxAxisComboBoxSensor;

class HxDataProbePlotWindow : public PzPlot
{
public:
    static HxDataProbePlotWindow* getInstance();

    ///
    void registerDataProbe(HxSplineProbe* probe);
    
    ///
    void unregisterDataProbe(HxSplineProbe* probe, bool keepAll = false);

    ///
    void setDataProbeVisibility(HxSplineProbe* probe, bool visible);

    ///
    PzAxis * getAxis() { return m_axis; }
    
    ///
    void updateData(HxSplineProbe* parent, int numCurves = 1);

    ///
    void clearRemainingDisplayedResults();

    enum AxisType
    {
        LENGTH,
        XCOORD,
        YCOORD,
        ZCOORD
    };
    void setXAxisType(AxisType);
protected:
    HxDataProbePlotWindow();

    virtual ~HxDataProbePlotWindow();

    PzCurve* createCurve(HxSplineProbe* parent, const McString & name);
    void removeCurves(HxSplineProbe* parent);

private:
    PzAxis             *m_axis;

    class DataProbe
    {
    public:
        DataProbe() : plotGroup(0) {}

        PzPlotGroup* plotGroup;
        McDArray<PzCurve*> curves;
    };

    McHashTable<HxSplineProbe*, DataProbe > m_dataProbe;
    McDArray<DataProbe> m_remainingDisplayedProbeResultsInfos;

    void removeCurves(DataProbe& dataProbe);

    QxAxisComboBoxSensor* m_comboBoxSensor;
    AxisType m_xAxisType;
};

#endif

/// @}
