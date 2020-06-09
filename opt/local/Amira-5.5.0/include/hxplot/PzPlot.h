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
#ifndef PZ_PLOT
#define PZ_PLOT

#include <hxplot/PzGenPlot.h>

#include <mclib/McString.h>
#include <mclib/McColor.h>
#include <mclib/McHashTable.h>

#include <tcl.h>

class PzObjectEditor;
class PzDataImporter;

class PzCurve;
class PzPlotGroup;
class PzBaseObject;
class PzPlotObject;

class PzGenDraw;

class HxColorEditor;

class QzGLDraw;
class QzMainWindow;
class QWidget;

class HxFileDialog;

typedef void PzPlotDeleteCB(const PzPlot &mwin, void* userdata);

/**
   Main plot class maintaining the plot gui's.
@author Olaf Paetsch
*/
class HXPLOT_API PzPlot: public PzGenPlot {

private:

    static McHashTable<const char*, int> objTypeTable;

    static void initPlottypeTable();

    QzMainWindow* mainWindow;
    QWidget*      plotWindow;
    PzGenDraw*    theDrawable;

    PzBaseObject*   located;
    PzBaseObject*   lastObj;

    int currFontSet;
    
    bool firstShow;
    bool decorationFlag;
    bool showWindow;

    PzPlotDeleteCB* deleteCallback;
    void*           deleteUserdata;

    int  nConfigProcs;
    McDArray<McString> configProcs;

    static void OE_Callback (int result, void* calldata, void* userdata);

    static void staticUpdate(PzGenDraw* drawable, void* userdata);

    static void inputCallback(McDArray<float> x, McDArray<float> y,
                              PzPlotObject* pobj, void* userdata);

    static void fkeyCallback(int fkey, int modifier, void* userdata);

    /// Checks if the curves in source have the same name in dest and copy data
    void handleExistingCurves(PzPlotGroup* dest, PzPlotGroup* source);

    void commonInit();

    static void itemSelectedCB(PzPlotObject* obj, void* userdata);

protected:

    PzObjectEditor* theObjectEditor;

    PzDataImporter* theDataImporter;

    McColor         currBGCol;

    HxFileDialog*   myFileDialog;

    void quitCB();

    void removeCB();

    void propCB();

    void plotAllCB();

    void openCB();

    void importCB();

    void saveStateCB();

    void printCB();

    void editCB();

    void setConfMenu();

    void callConfProc(int itemNo);

    void initInputCB(int mode);

    static void CE_applyokCallback(void* clientData, const HxColorEditor& );

    static void menuCB(int itemNo, const QzMainWindow &mwin, void* userdata);

    static void deleteCB(const QzMainWindow &mwin, void* userdata);

    static void plotareaCallback(float x, float y, int ix, int iy,
                                 PzPlotObject* area, PzPlot* plot);

    PzGenDraw* createDrawable(QWidget* parent, int xsize, int ysize);

    static int staticParse(ClientData , Tcl_Interp* , int , char** );

public:

    /// Constructor
    PzPlot(const char* name, int width = 512, int height = 512);

    /// Constructor with parent window
    PzPlot(QWidget* parent, const char* name);

    /// Destructor
    ~PzPlot();

    QzMainWindow* getMainWindow(){ return mainWindow;}

    QWidget* getWidget(){ return plotWindow;}

    virtual const char* className() { return "PzPlot"; }

    ///
    virtual void update();

    ///
    virtual void show();

    ///
    virtual void hide();

    ///
    virtual int isVisible();

    ///
    virtual int isTopLevel();

    ///
    virtual void clear();

    /// sets size of drawable area within window 
    virtual void setSize(int width, int height);

    /// returns size of drawable area within window 
    virtual void getSize(int& width, int& height);

    /// sets window size
    virtual void setWindowSize(int width, int height);

    /// returns window size
    virtual void getWindowSize(int& width, int& height);

    /// sets window position
    virtual void setPosition(int x, int y);

    /// returns window position
    virtual void getPosition(int& x, int& y);

    /// sets the window title in the title bar
    void setTitle(const char* title);

    /// sets the state of the decoration (i.e. menu bar and status bar)
    void setDecoration(bool flag);

    /// returns the state of the decoration
    bool hasDecoration() { return decorationFlag; }

    /** blocks or unblocks the display of the plot window, used e.g.
        if one likes to use plot in viewer functionality.
    */
    void setShowFlag(bool doShow) { showWindow = doShow; }

    /// sets the background colour
    void setBackgroundColor(float r, float g, float b);

    /// set the fontset (small = 0, normal = 1, big = 2)
    bool selectFontSet(int fs);

    /// returns the font set in use
    int fontSet() { return currFontSet; }

    ///
    virtual void editObjects();

    ///
    PzBaseObject* create(int typeId, const char* name, bool uniqueName = true);

    ///
    PzObjectEditor* objectEditor() { return theObjectEditor; }

    /// saves curve data to file after invoking dialog
    bool saveData();

    /// saves curve data to file
    bool saveData(const char* filename, int format);

    /// saves the plot properties to file
    bool saveState(const char* filename, bool allObjects = false);

    /// save preferences (only geometry by now, uses Amira registry)
    void savePreferences();

    bool saveState(FILE* fp, bool allObjects = false);

    /// print plot as PostScript to file (size = A4 in PS-points)
    bool print(const char* filename, int width = 595, int height = 841,
               bool landscape = true, bool autoscale = true, bool eps = false,
               bool drawframe = false, bool fillbg = false,
               bool blackNwhite = true, bool keepaspect = true);

    /** Renders the plot into an offscreen buffer (rgb[a] of the given size.
	
        If @c antiAliasing is set to a value larger than 0, the plot will
        be rendered with a width/height multiplied by that value.
        After rendering the resulting image will be smoothly scaled down
        to the given width/height.
        This creates smooth renderings. Line widths and font sizes are
        scaled appropriately.
        @c transparency (0 - 1) adjusts the transparency of the background.
        @c resultWHD[0] contains the width, @c resultWHD[1] contains the height
        and @c resultWHD[2] contains the number of channels (3 = rgb, 4 = rgba)
        of the returned image.

        The caller needs to free the result.
    */
    unsigned char* renderOffscreen(const int width, const int height,
                                   unsigned char antiAliasing,
                                   McVec3i& ResultWHD, float transparency = 0., 
                                   bool forceAlpha = false);

    /** Returns the plot window as an rgb[a] image.

        @c transparency (0 - 1) adjusts the transparency of the background.
        @c resultWHD[0] contains the width, @c resultWHD[1] contains the height
        and @c resultWHD[2] contains the number of channels (3 = rgb, 4 = rgba)
        of the returned image.
        The caller needs to free the result.
    */
    unsigned char* getScreenImage(McVec3i& resultWHD, float transparency = 0., 
                                  bool forceAlpha = false);

    /// create and save/print snapshot
    void snapshot(const char* filename = NULL);

    /// displays a message on the status bar for a certain time or forever (-1)
    void setStatus(const char* statusMsg = NULL, int milliSec = -1);

    /// sets the callback to be invoked whenever the window is closed
    void setDeleteCallback(PzPlotDeleteCB* clientfunc, void* clientdata);

    /// unsets the callback above
    void unsetDeleteCallback() { deleteCallback = NULL; }

    /** Sets the callback to be invoked whenever lines resp. polygons are
        entered interactively. I.e after hitting the Escape-key to end
        the input.
        Input callbacks from different module instances are distinguished
        by the clientdata.
        The callback is invoked as:
        (*PzPlotInputCB)(PzPlot* plotmodule, void* clientdata,
                         McDArray<float> x, McDArray<float> y);
    */
    void setInputCallback(PzPlotInputCB* clientfunc, void* clientdata);

    /// Unsets the callback above if the clientdata is the same
    void unsetInputCallback(void* clientdata);

    /** Sets the callback to be invoked whenever the user has clicked into
        a plotarea together with the control button,
                The callback is invoked as:
        (*PzPlotAreaCB)(PzPlot* plotmodule, void* clientdata,
                        PzPlotArea* area, float x, float y, int ix, int iy);
    */
    void setPlotAreaCallback(PzPlotAreaCB* clientfunc, void* clientdata);

    /// Unsets the callback above if the clientdata is the same
    void unsetPlotAreaCallback(void* clientdata);

    ///Get the drawable area
    PzGenDraw* getDrawableArea() {return theDrawable;}

    /**  creates a new plot window and copies all objects below @c area 
         and appends them under the anchor of the new window. It does not
         create a console window for the cloned plot window,
         Maybe used to magnify a plotarea from a plotwindow with many of it.
    */
    static PzPlot* cloneArea(PzPlotArea* area, const char* name,
                             int width = 512, int height = 512);

    /**  Copies all objects from @c fromParent to @c toParent 
    */
    static void recursiveClone(PzPlotGroup* fromParent, PzPlotGroup* toParent);

};

#endif

/// @}
