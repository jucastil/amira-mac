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
#ifndef PZ_EASYPLOT
#define PZ_EASYPLOT

#include <hxplot/PzPlot.h>

class PzAxis;
class PzGrid;
class PzLegend;
class PzPlotGroup;
class PzPlotArea;
class PzLattice;
class PzMarkerline;
class PzCurve;
class PzScatter;

/**
   Easy plot class. This class offers plot functions with only a few 
   function calls. The simplest way to plot within an Amira module
   goes like this:
   
   \verbatim

   PzEasyPlot* plot = new PzEasyPlot("plot window title");

   plot->putData("dataname",n,dataarray);

   \endverbatim

   This opens a separate plotwindow and plots a curve named \p dataname
   with \p n datapoints into that window.

   Subsequent calls to \p putData add extra curves to the plot or, if the 
   same name is used the data is updated.

   Additional plots within the same plot window can be achieved by calling
   the method \p addPlot. If there are more plot areas than the default one
   in use \p PzEasyPlot maintains a grid of size 32 by 32 to arrange the extra
   plot areas. 
   Each extra plot area is created to the left or right of a given row index,
   resp. at the bottom or at the top of a given column index.
   The size of the plot window can be extended by a given factor. A factor
   of 1. will double the size of the window in the required direction if
   possible. With a factor of 0 the window size is not changed.
   The spacing between multiple plots is ruled by the \p marginFac parameter.
   The spacing is plotwidth/3 resp. plotheight/3 if \p marginFac is set to
   1. (default). A value of 0. results in a zero spacing, i.e. the plots are
   positioned directly side by side without a gap.

   The creation of a plot window with 4 separate plot areas can be done like
   the following code fragment:

   \verbatim

   PzEasyPlot* plot = new PzEasyPlot("plot window title");

   // create 2. plot area to the right of the first one. Enlarge window by 0.5
   PzPlotArea* plot2 = plot->addPlot(0,PzRight,0.5);

   // create 2. plot area at the bottom of the first one.
   PzPlotArea* plot3 = plot->addPlot(0,PzBottom,0.5);

   // create 2. plot area to the right of the first plot area in the second row.
   // Don't enlarge the window.
   PzPlotArea* plot4 = plot->addPlot(1,PzRight,0.0);

   // get pointer to the first (default) plot area _AFTER_ addPlot.
   PzPlotArea* plot1 = plot->getFirstPlotArea();

   // create a curve named "dataname" in the first plot area
   plot->putData("dataname",plot1,n,dataarray);

   \endverbatim


@author Olaf Paetsch
*/
class HXPLOT_API PzEasyPlot: public PzPlot {

public:

    enum PzWindowDir { PzOver=0, PzLeft=1, PzRight=2, PzBottom=4, PzTop=8 };

    /** \brief Constructor.

        A legend and a grid are always created but set
        active resp. inactive according to the parameters \p withLegend and
        \p withGrid . The size of the plot window can be set after
        instantiation with:
        \em InstanceOfEasyPlot \p ->setSize( \em desiredWidth, \em desiredHeight \p );
    */
    PzEasyPlot(const char *name, bool withLegend = 1, bool withGrid = 0);

    /// Destructor
    ~PzEasyPlot();

    virtual const char* className() { return "PzEasyPlot"; }

    /** \brief Adds a plot area relativ to the first (default) plot area.

        The plot window is enlarged in the given direction by the factor
        \p sizeFac (0 .. 1) only if needed.
        The margin between plot areas are computed by the following formula:
        horizontal_margin = (width / (num_of_horplots-1)) / 3 * \p marginFac
        vertical_margin = (height / (num_of_vertplots-1)) / 3 * \p marginFac
        The returned plot area must be used in the following \em putData calls
        to direct the data to the right plot area.
        All attributes, like colour, linewidth, arrow, ... are inherited from
        the first axis.
        The maximum number of plot area is 32 x 32.
    */
    PzPlotArea* addPlot(PzWindowDir dir, float sizeFac, float marginFac = 1.);

    /** \brief Adds a plot area relative to the given grid index \p rowcol.

        For a horizontal direction (\p PzLeft, \p PzRight) that index is 
        interpreted as a row index. Otherwise it is regarded as a column
        index.
        The plot window is enlarged in the given direction by the factor
        \p sizeFac (0 .. 1) only if needed.
        The returned plot area must be used in the following \em putData calls
        to direct the data to the right plot area.
    */
    PzPlotArea* addPlot(int rowcol, PzWindowDir dir, float sizeFac,
                        float marginFac = 1.);

    /** \brief Set if update shall be called after every change, i.e., a call to putData(), addData(), remData() etc.

        Default on instantiation of EasyPlot: true.
    */
    void autoUpdate(bool upd = 1) { autoupdate = upd; }

    /** \brief Creates curve \p name or adds values to existing curve \p name.

        Creates curve \p name  with \p n \p xvals and \p yvals and
        returns the pointer to curve. If a curve named \p name exists its data
        is overridden by the new one.
    */
    PzCurve* putData(const char* name, int n, float* xvals, float* yvals);

    /** \brief Creates curve \p name or updates values of existing curve
               \p name.

        Creates curve \p name  with \p n \p xvals and \p yvals in plot area
        \p plotarea and returns the pointer to curve.
        If a curve named \p name exists its data is overridden by the new one.
    */  
    PzCurve* putData(const char* name, PzPlotArea* plotarea, int n,
                     float* xvals, float* yvals);

    /** \brief Creates scattered data \p name or adds values to existing
        scattered data \p name.

        Creates scattered data \p name with \p n \p xvals, \p yvals and
        \p zvals and returns the pointer to it. If a scattered data named
        \p name exists its data is overridden by the new one.
    */
    PzScatter* putData(const char* name, int n, float* xvals, float* yvals,
                       float* zvals);

    /** \brief Creates scattered data \p name or adds values to existing
        scattered data \p name.

        Creates scattered data \p name with \p n \p xvals, \p yvals and
        \p zvals in plot area \p plotarea and returns the pointer to it.
        If a scattered data named \p name exists its data is overridden by
        the new one.
    */
    PzScatter* putData(const char* name, PzPlotArea* plotarea, int n,
                       float* xvals, float* yvals, float* zvals);

    /** \brief Creates curve \p name or updates values of existing curve
               \p name.

        Creates curve \p name with \p n \p yvals and returns the pointer to
        curve.
        If a curve named \p name exists its data is overridden by the new one.
    */
    PzCurve* putData(const char* name, int n, float* yvals);

    /** \brief Creates curve \p name or updates values of existing curve
               \p name.

        Creates curve \p name with \p n \p yvals in plot area \p plotarea and
        returns the pointer to curve.
        If a curve named \p name exists its data is overridden by the new one.
    */
    PzCurve* putData(const char* name, PzPlotArea* plotarea, int n,
                     float* yvals);

    /** \brief Creates curve \p name or adds values to existing curve
               \p name.

        Creates curve \p name with \p n \p xvals and \p yvals and
        returns the pointer to curve. If a curve named \p name exists the given
        data is appended.
    */
    PzCurve* addData(const char* name, int n, float* xvals, float* yvals);

    /** \brief Creates curve \p name or adds values to existing curve \p name.

        Creates curve \p name with \p n \p xvals and \p yvals in plot area
        \p plotarea and returns the pointer to curve.
        If a curve named \p name exists the given data is appended.
    */
    PzCurve* addData(const char* name, PzPlotArea* plotarea, int n,
                     float* xvals, float* yvals);

    /** \brief Creates scattered data \p name or adds values to existing
        scattered data \p name.

        Creates scattered data \p name with \p n \p xvals, \p yvals and
        \p zvals and returns the pointer to it. If a scattered data named
        \p name exists the given data is appended.
    */
    PzScatter* addData(const char* name, int n, float* xvals, float* yvals,
                       float* zvals);

    /** \brief Creates scattered data \p name or adds values to existing
        scattered data \p name.

        Creates scattered data \p name with \p n \p xvals, \p yvals and
        \p zvals in plot area \p plotarea and returns the pointer to it.
        If a scattered data named \p name exists the given data is appended.
    */
    PzScatter* addData(const char* name, PzPlotArea* plotarea, int n,
                       float* xvals, float* yvals, float* zvals);

    /** \brief Creates curve \p name or adds values to existing curve \p name.

        Creates curve \p name with \p n \p yvals and returns the pointer to
        curve. If a curve named \p name exists the given data is appended.
    */
    PzCurve* addData(const char* name, int n, float* yvals);

    /** \brief Creates curve \p name or adds values to existing curve \p name.

        Creates curve \p name with \p n \p yvals in plot area \p plotarea and
        returns the pointer to curve.
        If a curve named \p name exists the given data is appended.
    */
    PzCurve* addData(const char* name, PzPlotArea* plotarea, int n,
                     float* yvals);

    /** \brief Creates a lattice \p name or updates existing lattice \p name.

        Creates lattice \p name which is displayed as an image with
        \p m by \p n \p values and returns the pointer to lattice.
        If a lattice named \p name exists its data is overridden by the new one.
    */
    PzLattice* putData(const char* name, int m, int n, float* values);

    /** \brief Creates a lattice \p name or updates existing lattice \p name.

        Creates lattice \p name which is displayed as an image in the 
        plot area \p plotarea with \p m by \p n \p values and returns the
        pointer to lattice.
        If a lattice named \p name exists its data is overridden by the new one.
    */
    PzLattice* putData(const char* name, PzPlotArea* plotarea, int m, int n,
                       float* values);

    /// Removes curve \p name or all curves if \p name == NULL
    void remData(const char* name = NULL);

    /// Removes curve \p name or all curves if \p name == NULL from \p plotarea
    void remData(PzPlotArea* plotarea, const char* name = NULL);

	///Removes all curves which are \b not contained in the given list.
	void remDataNotInList(const McDArray< McString >& DataToKeep);

	///Removes all curves which are \b not contained in the given list.
	void remDataNotInList(PzPlotArea* plotarea, const McDArray< McString >& DataToKeep);

    /** \brief Adds or updates a markerline \p name to the default plot area.

        Adds a vertical markerline \p name to the default plot area at
        \p position. If a markerline named \p name exists it is set to the
        given position.
        The pointer to the markerline is returned.
    */
    PzMarkerline* setMarkerline(const char* name, float position);

    /** \brief Adds or updates a markerline \p name to the given \p plotarea 

        Adds a vertical markerline \p name to the given \p plotare at
        \p position. If a markerline named \p name exists it is set to the 
        given position..
        The pointer to the markerline is returned.
    */
    PzMarkerline* setMarkerline(const char* name, PzPlotArea* area,
                                float position);

    /// Returns pointer to the axis of a given plot area
    PzAxis*     getTheAxis(PzPlotArea* area = NULL);

    /// Returns pointer to the legend (there is only one!)
    PzLegend*   getTheLegend();

    /// Returns pointer to the axis' grid of a given plot area
    PzGrid*     getTheGrid(PzPlotArea* area = NULL);

    /** \brief Returns the first (default) plot area.

        Note: \p getFirstPlotArea returns a different pointer after the
        constructor has been called (i.e. after {\em new PzEasyPlot}) other
        than calling it after \em addPlot. 
    */
    PzPlotArea* getFirstPlotArea();

    /** \brief Returns the number of plot areas currently in use.

        0 means only the default plot area is in use. If \em addPlot has been
        called once the number of plot areas is 2.
    */
    int getNumPlotAreas() { return nPlotAreas; }

    /// Returns the number of plot area columns (max 32).
    int getNumColAreas() { return nColAreas; }

    /// Returns the number of plot area rows (max 32).
    int getNumRowAreas() { return nRowAreas; }

protected:

    PzLegend    *myLegend;
    PzAxis      *myAxis;
    PzGrid      *myGrid;
    PzPlotGroup *myDataGroup;

    int autoupdate;
    bool withLegend, withGrid;

    void assignAttr(PzCurve* curve, int i);

    void createTree(bool withlegend, bool withgrid);

private:

    // how many areas are maximal in a row resp. in a column
    int nRowAreas, nColAreas;

    PzBndBox overallBox;

    float horMargin, vertMargin;     // margins between plots

    static const int maxRows;
    static const int maxCols;
    PzPlotArea* areaGrid[32][32];

    int nPlotAreas;  // 0 means: only one default plotarea created

    void updateOverallBox();

    void initMultiPlot();

    PzPlotGroup* getFirstDataGroup(PzPlotArea* plotarea);

	void doAutoUpdate()
	{
		if (autoupdate)
		{
			if (!isVisible()) show();
			update();
		}
	}
};

#endif


/// @}
