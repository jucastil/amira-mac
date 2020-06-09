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
#ifndef PZ_MATRIXPLOT
#define PZ_MATRIXPLOT

#include <hxplot/PzPlot.h>

#define MAXROWS 64
#define MAXCOLS 64

class PzAxis;
class PzLegend;
class PzColormap;
class PzPlotGroup;
class PzPlotArea;
class PzLattice;
class PzCurve;
class PzScatter;

/**
   Matrix plot class. This class offers plot functions to setup a matrix plot
   as it is often used for scatter plots (SPLOM).
   
   \verbatim

   bool mirror = true;
   PzMatrixPlot* splom = new PzMatrixPlot("MySPloM",3,-1,mirror);
   splom->ref();

   // create plot at column 0, row 1, plot is mirrored to col 1, row 0
   splom->putData(0,1,numValues,xvalues,yvalues,zvalues);

   // create plot at column 0, row 2, plot is mirrored to col 2, row 0
   splom->putData(0,2,numValues,xvalues,yvalues,zvalues);
   // create plot at column 1, row 2, plot is mirrored to col 2, row 1
   splom->putData(1,2,numValues,xvalues,yvalues,zvalues);

   splom->show();
   \endverbatim

   This opens a plotwindow with 3x3 small plots and plots data into the
   lower left 3 plot areas. The 3 top right plot areas a filled with the
   mirrored values. The diagonal is left free.

@author Olaf Paetsch
*/
class HXPLOT_API PzMatrixPlot: public PzPlot {

public:

    /** \brief Constructor.

        Creates a squared matrix of plots of size \p dim x \p dim if \p dim2
        <= 0. otherwise a rectangular matrix \p dim x \p dim2 is created.
        If \p mirror == true plot[i,j] => plot[j,i] with x an d y values
        swapped. With \p triangular set to true the upper right triangle of
        plots is switched off leaving room for a magnified plot.
        The size of the plot window can be set after instantiation with:
        \em InstanceOfMatrixPlot \p ->setSize( \em desiredWidth,
                                               \em desiredHeight \p );
    */
    PzMatrixPlot(const char *name, const int dim, const int dim2 = 0, 
                 const bool mirror = true, const bool triangular = false);

    /// Destructor
    ~PzMatrixPlot();

    virtual const char* className() { return "PzMatrixPlot"; }

    /** \brief Set if update shall be called whenever all plots have new
         values, i.e., enough calls to putData(), remData() etc.

        Default on instantiation of MatrixPlot: false.
        Note: Only used in \p remData() by now.
    */
    void autoUpdate(bool upd = 1) { autoupdate = upd; }

    /** \brief Creates scattered data in plotarea [i,j] or
        sets values of existing scattered data in plotarea [i,j].

        Creates scattered data in plotarea [i,j] with \p n \p xvals, \p yvals
        and \p zvals and returns the pointer to it. If a scattered data in
        plotarea [i,j] exists its data is overridden by the new one.
        The plotobject is created with the name "spl<ii><jj>" and uses
        \p label if given as the label in a legend.
    */
    PzScatter* putData(int i, int j, int n, float* xvals, float* yvals,
                       float* zvals, const char* label = NULL);

    /** \brief Creates lattice data in plotarea [i,j] or
        sets values of existing scattered data in plotarea [i,j].

        Creates lattice data in plotarea [i,j] with \p m x \p n \p values
        and returns the pointer to it. If a lattice data in
        plotarea [i,j] exists its data is overridden by the new one.
        The plotobject is created with the name "spl<ii><jj>" and uses
        \p label if given as the label in a legend.
    */
    PzLattice* putData(int i, int j, int m, int n, float* values,
                       const char* label = NULL);

    /// Removes all plotobjects in all plotareas
    void remData();

    /// Removes plotobjects of plotarea [i,j]
    void remData(int i, int j);

    /** \brief Sets the overall min max for all axes in use.
    */
    void setMinMax(float xmin, float xmax, float ymin, float ymax);

    /** \brief Returns the overall min max for all axes in use.
    */
    void getMinMax(float& xmin, float& xmax, float& ymin, float& ymax);

    /** \brief Sets the min max for all axes in the given \p row
    */
    void setRowMinMax(int row, float ymin, float ymax);

    /** \brief Returns the min max for all axes in the given \p row
    */
    void getRowMinMax(int row, float& ymin, float& ymax);

    /** \brief Sets the min max for all axes in the given \p column
    */
    void setColMinMax(int col, float xmin, float xmax);

    /** \brief Returns the min max for all axes in the given \p column
    */
    void getColMinMax(int col, float& xmin, float& xmax);

    /// Returns pointer to the plotarea [i,j]
    PzPlotArea* getThePlotArea(int i, int j);

    /// Returns pointer to the axis of the given plotarea [i,j]
    PzAxis*     getTheAxis(int i, int j);

    /// Returns pointer to the legend (there is only one!)
    PzLegend*   getTheLegend();

    /// Returns pointer to the global colormap (there is only one!)
    PzColormap* getTheColormap() { return myColormap;}

    /// Returns pointer to the magnifier plotarea
    PzPlotArea* getTheMagArea() { return myMagArea;}

    /// Returns pointer to the axis of the magnifier plotarea
    PzAxis*     getTheMagAxis() { return myMagAxis;}

    /** \brief Returns the number of plotareas currently in use.
    */
    int getNumPlotAreas() { return nPlotAreas; }

    /// Returns the number of plotarea columns (max 64).
    int getNumColAreas() { return nCols; }

    /// Returns the number of plotarea rows (max 64).
    int getNumRowAreas() { return nRows; }

protected:

    static const int maxRows = MAXROWS;
    static const int maxCols = MAXCOLS;

    PzPlotArea*   myPlotAreas[maxCols][maxRows];
    PzAxis*       myAxis[maxCols][maxRows];
    PzLegend*     myLegend;
    PzColormap*   myColormap;
    PzPlotObject* myObjects[maxCols][maxRows];
    PzPlotArea*   myMagArea;
    PzAxis*       myMagAxis;

    float theMin[2], theMax[2];                   // overall min, max
    float theRowMin[maxRows], theRowMax[maxRows]; // min max for rows
    float theColMin[maxCols], theColMax[maxCols]; // min max for columns

    bool autoupdate;
    bool withLegend;
    bool myMirror;
    bool myTriangular;

    void assignAttr(PzPlotObject* obj, int i);

    void createTree(bool withlegend);

    void doAutoUpdate();

    static int staticParse(ClientData , Tcl_Interp* , int , char** );

private:

    void initDefaults();

    // how many areas are maximal in a row resp. in a column
    int nRows, nCols;

    float margin;     // margin between plots in ndc 

    int nPlotAreas;
};

#endif


/// @}
