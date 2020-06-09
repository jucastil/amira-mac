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

/// @addtogroup hxplot hxplot
/// @{
#ifndef PZ_PORT_PLOT_H
#define PZ_PORT_PLOT_H

#include <hxplot/PzPlotWinDLLApi.h>
#include <hxcore/HxPort.h>
#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>

class PzPlot;
class PzCurve;
class PzLattice;
class PzAxis;
class PzLegend;
class PzGrid;
class PzPlotArea;
class PzPlotGroup;

class QzPortPlotLayout;
class QzPlotWidget;
class QxPushButton;

/** Provides a port to draw into a toplevel window as well as into
    the WorkArea.
    To create a classical toplevel window invoke the constructor as follows:
    portPlot(this,"portplot");
    A button labeled "Plot" is created in the WorkArea.

    portPlot(this,"portplot",PzTOPLEVEL,2);
    This creates a toplevel window and within the WorkArea a plot button and
    2 extra buttons.

    portPlot(this,"portplot",PzINWORKAREA|PzWITHSTDBUTTONS);
    This creates a plot widget in the WorkArea together with 3 buttons
    for "edit", "snapshot" and "saveData".
    */
class HXPLOT_API PzPortPlot : public HxPort {

  MC_ABSTRACT_HEADER(PzPortPlot);

  public:

    ///
    enum PzPortPlotMode { PzTOPLEVEL = 0,
                          PzINWORKAREA = 1,
                          PzWITHSTDBUTTONS = 2 };
 
    /// Constructor for objects.
    PzPortPlot(HxObject *object, const char* name,
               PzPortPlotMode mode = PzTOPLEVEL, int nextrabuttons = 0);

    /// Constructor for editors.
    PzPortPlot(HxEditor *editor, const char* name);

    /// Destructor.
    ~PzPortPlot();

    ///
    //const char* getValue() const { return value; }

    /// Sets label of port
    void setLabel(const char* label) { HxPort::setLabel(label); }

    /// Returns label of port
    const char* getLabel() const { return HxPort::getLabel(); }

    /// Sets label of specified button
    void setLabel(int item, const char* label);

    /// Gets label of specified button
    const char* getLabel(int item) const;

    /// Activates or deactivates a toggle.
    void setSensitivity(int item, int isOn);

    /// Checks whether the specified radio button is active or not.
    int getSensitivity(int item) const;

    /** Returns index of button which has been pushed last or -1 if
        @c HxPort::isNew() is false. This method doesn't interprete the
        snap toggle. If a button is snapped but the port is not new
        this method still returns -1. In order to handle snapped buttons
        you better should use the method wasHit(int). */
    int getValue() const { return newFlag ? index : -1; }
    
    /// Same as getValue().
    int getIndex() const { return newFlag ? index : -1; }

    /// Mark given button to be pushed.
    void setValue(int btn) { index = btn; newFlag = 1; }

    /// Same as setValue().
    void setIndex(int btn) { index = btn; newFlag = 1; }
    

    /** Returns 1 if the button has been hit or if its snap toggle is on.
        Unlike this method getValue() ignores the snap toggle. */
    int wasHit(int btn = 0);

    /// Command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Save state method.
    virtual void saveState(FILE* fp);

    // **************** The plot interface methods follow:

    /// returns the plot window
    PzPlot* getPlotWindow() { return thePlot; }

    /** Set if update shall be called after every \p putData call.
        Default on instantiation of EasyPlot: true.
    */
    void autoUpdate(bool upd = 1) { autoupdate = upd; }

    /// Updates the plot
    void updatePlot();

    /** Creates curve \p name with \p n \p xvals and \p yvals and
        returns a pointer to curve. If a curve named \p name exists its data
        is overridden by the new one.
    */
    PzCurve* putData(const char* name, int n, float* xvals, float* yvals);

    /** Creates curve \p name with \p n \p yvals and returns a pointer to curve.
        If a curve named \p name exists its data is overridden by the new one.
    */
    PzCurve* putData(const char* name, int n, float* yvals);

    /** Creates curve \p name with \p n \p xvals and \p yvals and
        returns a pointer to curve. If a curve named \p name exists the given
        data is appended.
    */
    PzCurve* addData(const char* name, int n, float* xvals, float* yvals);

    /** Creates curve \p name with \p n \p yvals and returns a pointer to curve.        If a curve named \p name exists the given data is appended.
    */
    PzCurve* addData(const char* name, int n, float* yvals);

    /** Creates a lattice \p name which is displayed as an image with \p m by
        \p n float \p values and returns a pointer to lattice.
        If a lattice named \p name exists its data is overridden by the new one.
    */
    PzLattice* putData(const char* name, int m, int n, float* values);

    /// Removes curve \p name or all curves if \p name == NULL
    void remData(const char* name = NULL);

    /// Returns pointer to the axis
    PzAxis*      getTheAxis()      { return myAxis; }

    /// Returns pointer to the legend
    PzLegend*    getTheLegend()    { return myLegend; }

    /// Returns pointer to the grid
    PzGrid*      getTheGrid()      { return myGrid; }

    /// Returns pointer to the plot group which groups the curves/lattices
    PzPlotGroup* getThePlotGroup() { return myDataGroup; }

    /// Returns pointer to the anchor
    PzPlotArea*  getTheAnchor()    { return myAnchor; }

    /// Returns true if the port has a top level window
    bool hasTopLevelWindow();

    /** Sets the size of the plot window. Note: This should be called
        in the contructor of the class which uses this port. The size of the
        plot widget within the WorkArea cannot be changed after the widget
        has been created. The size of a toplevel plot window can be
        changed afterwards.
    */
    void setPlotSize(int width, int height);

    /// Returns the width and the height of the plot widget resp. toplevel plot
    void getPlotSize(int& width, int& height);

    virtual void switchSinglePortLabels(const McString& currentString, const McString& newString);

  protected:

    QxGuardedPtr<QzPlotWidget> plotwidget;
    PzPlot*  thePlot;
    QxGuardedPtr<QzPortPlotLayout> layout;

    McDArray< QxGuardedPtr<QxPushButton> > buttonList;
    McDArray<McString> labels;
    McBitfield sensitivity;
    int index;
    int plotButton;
    int nItems, nStdButtons ,nExtraButtons;
    PzPortPlotMode plotWinMode;
    unsigned int modifierFlags;

    virtual void initDefaults();

    virtual void createWidget(QWidget* parent);
    virtual void destroyWidget();

    virtual void guiCallback();

    PzPlotArea*  myAnchor;
    PzAxis*      myAxis;
    PzGrid*      myGrid;
    PzLegend*    myLegend;
    PzPlotGroup* myDataGroup;

    int myWidth, myHeight;

    bool autoupdate;
    bool showLegend, showGrid;

    void assignAttr(PzCurve* curve, int i);

    void createPlotTree(bool showLegend, bool showGrid);

};

#endif

/// @}
