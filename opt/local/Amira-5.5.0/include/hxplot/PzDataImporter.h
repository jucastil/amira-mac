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
#ifndef PZ_DATAIMPORTER
#define PZ_DATAIMPORTER

#include <hxplot/PzPlotWinDLLApi.h>
#include <hxplot/PzPlotData.h>
#include <mclib/McFilename.h>

class PzDataImporter;
class QzImportDialog;

class PzPlot;
class PzPlotGroup;


/// Plot curve specification
struct PzCurveSettings {
    /** Contains a list of columns subject to plot.
        For every curve a C-like read format is stored;
        Every curve can hold several columns e.g. plot colN over colM, or
        an error bar taking the data from up to 6 columns shall be plotted.
    */
    McDArray<int> columnList;

    McString curveName;

    McString readFormat;

    int curveType;

    /** Type how the data has to be interpreted
        0 = text resp. no number, 1 = number, 2 = date/time
    */
    int columnType;

    PzPlotData::PzTimeUnit timeUnit;

    int        timeRange;

    float      timeBase;

    PzCurveSettings() { init(); }

    PzCurveSettings(const char* name, int type = 3, int col1 = -1,
                    int col2 = -1, int col3 = -1, int col4 = -1, int col5 = -1,
                    int col6 = -1);

    void init();
};

/** Contains the settings to read and interpret the imported datafile.
    Note: Line numbers in files start with 1 (one)!!!
*/
struct PzDataImportRules {
       
    /// 0 = CSV, 1 = Formatted, 2 = Fixed width, 3 = Binary
    int dataFormat;

    /// contains separator token which separates data items per line
    char separator;

    /// contains comment token
    char comment;

    /// contain character which quotes a string
    char stringdelim;

    /// Number of first line to start reading data in file
    int firstLine;

    /// if set, the first non comment line in datafile is used as column name.
    bool firstLineAsName;

    /// number of line which contains column names (0 == unset)
    int noNameLine;

    /// contains specification of the curves to be plotted from data file
    McDArray<PzCurveSettings*> curveList;

    /// list of columns containing only numbers
    McDArray<int> activeColumns;

    /** list of all columns containing the type
        0 = text resp. no number, 1 = number, 2 = date/time
    */
    McDArray<int> columnType;

    /** contains C-like formats to interpret data per line.
        for formatted lines @c readFormat[0] contains C-like format string.
        for CSV lines @ readFormat contains a format string for every column.
    */
    McDArray<McString> readFormat;

    /// contains a comma separated headline for the column names (= curve names)
    McString headLine;

    /** array containing a format index for interpretation:
        0 = do not use, 1 = int, 2 = float, 3 = hex, 4 = oct
    */
    McDArray<int> readAs;

    /** contains the start index in @ readFormat to be interpreted according to
        @ readAs.
    */
    McDArray<int> readAsStart;

    /** contains the index of the first character not part of the conversion
        string in @ readFormat.
        readAs
    */
    McDArray<int> readAsSepNdx;

    /** 0 = all cols,        1 = cols against 1., 2 = xy cols pairs,
        3 = unused,          4 = all rows,        5 = rows against 1.
    */
    int plotSpec;

    /// toggle if only selected columns should be read
    int selected;

    PzDataImportRules() { init(); }

    void init() { dataFormat = -1;         // no format as default
                  separator = '\0';
                  comment = '\0';
                  stringdelim = '\0';
                  firstLine = 1;
                  firstLineAsName = false;
                  noNameLine = 0;
                  readFormat.resize(1);
                  headLine.clear();
                  curveList.clear();
                  activeColumns.clear();
                  columnType.clear();
                  readAs.clear();
                  readAsStart.clear();
                  readAsSepNdx.clear();
                  plotSpec = 0;
                  selected = 0; }

    void set(PzDataImportRules* src) { dataFormat      = src->dataFormat;
                                       separator       = src->separator;
                                       comment         = src->comment;
                                       stringdelim     = src->stringdelim;
                                       firstLine       = src->firstLine;
                                       firstLineAsName = src->firstLineAsName;
                                       noNameLine      = src->noNameLine;
                                       readFormat      = src->readFormat;
                                       headLine        = src->headLine;
                                       curveList       = src->curveList;
                                       activeColumns   = src->activeColumns;
                                       columnType      = src->columnType;
                                       readAs          = src->readAs;
                                       readAsStart     = src->readAsStart;
                                       readAsSepNdx    = src->readAsSepNdx;
                                       plotSpec        = src->plotSpec;
                                       selected        = src->selected; }

}; // struct PzDataImportRules

typedef void PzDataImporterCB(int result, void* calldata, void* userdata);

/**
   Import dialog for data files to be subject to plot
@author Olaf Paetsch
*/
class HXPLOT_API PzDataImporter {

  public:

    /// Constructor
    PzDataImporter(const char* name, PzPlot* plot);

    /// Destructor
    virtual ~PzDataImporter();

    virtual const char* className() { return "PzDataImporter"; }

    ///
    virtual void update();

    /** reads and imports @p filename according to the given @p importrules.
        If @p showDialog is true the importdialog is shown.  
        
    */
    virtual PzPlotGroup* readAndShow(const char* filename,
                                     PzDataImportRules* importrules = NULL,
                                     bool showDialog = true);

    ///
    virtual void hide();

    ///
    virtual bool isVisible();

    /// sets the window title in the title bar
    void setTitle(const char* title);

    ///
    void setImportCallback(PzDataImporterCB* clientfunc, void* clientdata);

    /// unsets the notifier above
    void unsetImportCallback() { dialogCallback = (PzDataImporterCB*)0; }

    /// reads data files (only .ampl format at the moment)
    static PzPlotGroup* readData(const char* filename, PzPlotGroup* anchor);

    /// reads data files containing (hopefully) plot data in CSV format
    static PzPlotGroup* readCSV(const char* filename,
                                PzDataImportRules* importsettings,
                                PzPlotGroup* anchor);

    /// reads data files containing (hopefully) plot data in amira plot format
    static PzPlotGroup* readAmpl(const char* filename, PzPlotGroup* anchor);

    /// reads data files according to given format line
    static PzPlotGroup* readFmt(const char* filename,
                                PzDataImportRules* importsettings,
                                PzPlotGroup* anchor);

    /** reads one given line of data according to a format line.
        Values are returned as floats in a McDArray.
        Returns number of valid items read.
    */
    static int readFmtLine(McDArray<float>& readValues, char* line,
                           PzDataImportRules* importsettings);

    /** Split @c inString by a character. All sub-strings separated
        by @c inToken will be put into @c outArr.
        Subsequent occurences of @c inToken will be skipped.
        If @c quoteMark is not '\0' it protects @c instring characters
        enclosed  @c quoteMark from being splitted.
    */
    static int stringExplode(McDArray<McString> & outArr, McString inString,
                             char inToken = ' ', char quoteMark = '"');

    /** Converts a string like 'january' or 'februar' to a number between
        (man ahnt es schon) 1 - 12. 
        Method checks only the first 3 characters. Recognizes english,
        german and french month notations.
        Returns 0 on error.
    */
    static int fromMonth(McString month);

    /** Converts a string containing a date or time to a value according
        to a given format. @c timeunit and @c timebase are set to the first
        date read, provided that dates are monotonically increasing.
        The value is returned in @c val.  The date read is
        converted to an appropriate float value. i.e a date consisting of
        year, month and day ist recomputed to the number of days starting
        from the first year found and @c timebase / @c timeunit are set to
        (the) year. @c timerange contains the range of timeunits used in
        the date. E.g. reading a format of YYYYMMDD has a timerange of 2.
        Returns 1 on success, 0 otherwise.
    */
    static int scandf(McString in, McString format, float* val,
                      PzPlotData::PzTimeUnit* timeunit, int* timerange,
                      float* timebase);

  protected:

    PzDataImportRules dialogImportRules;

  private:

    //PzDataImportRules* dialogImportRules;

    QzImportDialog*   dialogWindow;
    PzDataImporterCB* dialogCallback;
    void*             dialogUserdata;

    PzPlot* thePlot;

    McFilename theDatafile;

    static void dialogWindowCB(int result, const QzImportDialog& idwin,
                               void* userdata);

    // previews firstNlines of filename, returning 1 on success 0 otherwise
    int preview(const char* filename, int startline = 1, int firstnlines = 50,
                int noheadline = 0, bool showcomments = true);

    // creates curves to be plotted
    static PzPlotGroup* createCurves(const char* groupname, 
                                     PzDataImportRules* importsettings,
                                     McDArray< McDArray<float> > datain,
                              PzPlotGroup* anchor);
};

#endif

/// @}
