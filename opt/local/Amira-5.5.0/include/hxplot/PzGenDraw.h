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
#ifndef PZ_GENDRAW
#define PZ_GENDRAW

#include <hxplot/PzPlotWinDLLApi.h>
#include <mclib/McQuadtree.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define PzPOINT                            0x1B00
#define PzLINE                             0x1B01
#define PzFILL                             0x1B02

#define AXIS_MTICK_LENGTH 0.02
#define AXIS_STICK_LENGTH 0.01
#define ARROW_LENGTH 0.04
#define ARROW_WIDTH_FAC 0.20
#define NUM_MARKERTYPES 24
#define NUM_LINETYPES 8

// for setAttr "font": normal font == 1
#define normalFontNdx  getNormalFontIndex()
// for setAttr "font": big font == 2
#define bigFontNdx     getBigFontIndex()
// for setAttr "font": small font == 0
#define smallFontNdx   getSmallFontIndex()
// for setAttr "font": huge font == 3
#define hugeFontNdx    getHugeFontIndex()
// unusable for the time being
#define symbolFontNdx  getSymbolFontIndex()

#include <mclib/McDArray.h>
#include <mclib/McBox2i.h>

class PzPlot;
class PzGenDraw;
class PzPlotObject;

struct PzCol {
              float r, g, b, a;
              int ir, ig, ib;
              PzCol();
              PzCol(float grey);
              PzCol(float red, float green, float blue, float alpha = 1.);
              PzCol(int red, int green, int blue);
             };

struct PzLineProp { float width; int type; int arowsize;
                    PzLineProp()
                              { width = 1.; type = 1; arowsize = 1; }
                    PzLineProp(float w, int t, int as = 1)
                              { width = w; type = t; arowsize = as; }
                  };

struct PzPolyProp { unsigned int mode; int fillstyle;
                    PzPolyProp() { mode = 0; fillstyle = 1; }
                  };

struct PzPrMat { double left;   double right;
                 double bottom; double top;
                 double mynear; double myfar; };

struct PzViewport { int x, y; int width, height; };

struct PzNormTr { double xfac, yfac, zfac, xoff, yoff, zoff; };

struct PzFont { char* name; int base, length, char_height, char_width;
                float meansizefac; void* devFont; };

typedef void PzSelCB(PzPlotObject* obj, void* userdata);

typedef void PzUpdateCB(PzGenDraw* drawable, void* userdata);

typedef void PzMousePressCB(float x, float y, int modifier, PzPlotObject* pobj);

typedef void PzMousePressPlotCB(float x, float y, int ix, int iy,
                                PzPlotObject* pobj, PzPlot* plot);

typedef void PzMouseMoveCB(float startx, float starty, float dx, float dy,
                           int modifier, PzPlotObject* pobj);

typedef void PzMouseRelCB(float startx, float starty, float dx, float dy,
                          int modifier, PzPlotObject* pobj);

typedef void PzKeyRelCB(const char* key, float x, float y, int modifier,
                        PzPlotObject* pobj);

typedef void PzFunctionKeyRelCB(int fkey, int modifier, void* userdata);

typedef void PzLineInputCB(McDArray<float>x, McDArray<float>y,
                           PzPlotObject* pobj, void* userdata);
 
struct PzSelObject {
                    PzSelObject(McBox2i b, PzPlotObject* o, float px, float py,
                                int itr)
                               {
                                bb = b; obj = o;
                                pixwcx = px; pixwcy = py;
                                normtr = itr;
                               }
                    McBox2i bb;
                    PzPlotObject* obj;
                    float pixwcx, pixwcy;
                    int normtr;
                    int intersect(float box[4], void* userdata);
                   };

/**
   Base class for a plot driver.
@author Olaf Paetsch
*/
class HXPLOT_API PzGenDraw {

  public:

    ///
    enum PzInputMode { NOINPUT         =  0,
                       SELECTMODE      =  1,
                       LINEINPUTMODE   =  2,
                       LASSOMODE       =  4,
                       ZOOMMODE        =  8,
                       RECTINPUTMODE   = 16,
                       CIRCLEINPUTMODE = 32
                     };

    enum PzFontSet { SMALLFONTS = 0, NORMALFONTS = 1, BIGFONTS = 2 };

  protected:

    void initDefaults();

    PzCol               BG_colour;
    PzCol               FG_colour;
    McDArray<unsigned int> coltab;
    PzLineProp          currLineProp;
    PzPolyProp          currPolyProp;
    PzPrMat             currProj;
    PzPrMat             currWCWin;
    PzPrMat             currWCView;
    PzViewport          currView;
    McDArray<PzNormTr*> NormTrList;
    McDArray<PzPrMat*>  WCWinList;
    McDArray<PzFont*>   FontList;
    int                 currXSize;
    int                 currYSize;
    int                 currMargin;
    int                 currNormTr;
    int                 lastFontDList;
    int                 currFont;
    int                 normalFont, bigFont, smallFont, symbolFont, hugeFont;
    int                 currMarkerType;
    int                 currType;
    PzPlotObject*       currObject;
    PzPlotObject*       currSelectable;
    PzPlotObject*       editObject;
    McQuadtree<PzSelObject> quadtree;
    PzSelObject*        currSel;
    int                 inpMode;
    bool                selPriority;
    bool                useClipping;

    McDArray<int>       inputX;
    McDArray<int>       inputY;

    PzSelCB*            selectionCallback;
    void*               selectionCBData;

    PzUpdateCB*         updateCallback;
    void*               updateCBData;

    PzLineInputCB*      inputCallback;
    void*               inputCBData;

    PzFunctionKeyRelCB* fkeyCallback;
    void*               fkeyCBData;

    McDArray<PzMousePressCB*> mPressCallbacks;
    McDArray<PzPlotObject*>   mPressCBObjs;

    McDArray<PzMouseRelCB*> mRelCallbacks;
    McDArray<PzPlotObject*> mRelCBObjs;

    McDArray<PzKeyRelCB*>   kRelCallbacks;
    McDArray<PzPlotObject*> kRelCBObjs;

    McDArray<PzMouseMoveCB*> mMoveCallbacks;
    McDArray<PzPlotObject*>  mMoveCBObjs;

    PzMousePressPlotCB* mPressPlotCallback;
    PzPlot*             mPressPlot;

    /// Constructor
    PzGenDraw(PzPlot*);

    /// Destructor
    virtual ~PzGenDraw();

    void line2quadtree(int x1, int y1, int x2, int y2);

    void box2quadtree(int x1, int x2, int y1, int y2);

    /// Displays an overlay rectangle over the current drawing
    virtual void doOverlayBox(int blX, int blY, int trX, int trY) { }

    /// Displays an overlay line over the current drawing
    virtual void doOverlayLine(McDArray<int>x, McDArray<int>y,
                               bool closed = false, bool incremental = true) { }

    /// Displays an overlay rectangle over the current drawing
    virtual void doOverlayCircle(int centerX, int centerY, int radius) { }

    static unsigned char luminance(unsigned char ired, unsigned char igreen,
                                      unsigned char iblue);

    static float luminance(float red, float green, float blue);

  public:

    virtual const char* className() { return "PzGenDraw"; }

    ///
    virtual void setBG_colour(int r, int g, int b, float a = 0.0);

    ///
    virtual void setBG_colour(float r, float g, float b, float a = 0.0);

    ///
    virtual void setFG_colour(int r, int g, int b, float a = 0.0);

    ///
    virtual void setFG_colour(float r, float g, float b, float a = 0.0);

    ///
    PzCol bgColour() { return BG_colour; }

    /** sets a colour table with colours in packed format. If table is null
        a default grey table with the given length is generated.
    */
    virtual void setColourtable(int length, unsigned int* table = NULL);

    ///
    void setWCWin(double, double, double, double,
                  double mynear = -1.0,
                  double myfar  =  1.0);
    ///
    void setWCView(double, double, double, double,
                   double mynear = -1.0,
                   double myfar  =  1.0);

    /** returns rectangle of point in respect to window
     @verbatim
    
            |       |       1000
      ------+-------+------
            |       |
            |   0   |         Y
            |       |
      ------+-------+------
            |       |       0100
       0001 |   X   | 0010
     @endverbatim

       if point in window return 0
       else return or'ed index
    */
    int getOuterRect(double x, double y);

    ///
    virtual void setProj(double, double, double, double,
                         double mynear = -1.0,
                         double myfar  =  1.0);
    ///
    int  setNormTr();

    ///
    PzViewport getWinSize() { return currView; }

    ///
    void getWinSize(int &width, int &height)
                   { 
                       width = currView.width; 
                       height = currView.height; 
                   }

    ///
    virtual void useNormTr(int) { }

    /// returns number of current normalization transformation
    int  getNormTr() { return currNormTr; }

    /// returns current normalization transformation
    int  getNormTr(float &xfac, float &yfac, float &xoff, float &yoff);

    /// returns a normalization transformation
    int  getNormTr(int itr, float &xfac, float &yfac, float &xoff, float &yoff);

    /// transform world coordinate to device coordinate
    void wc2dc(int &ix, int &iy, float x, float y);

    /// transform world coordinate to device coordinate and flip y coordinate
    void wc2dc(int &ix, int &iy, float x, float y, int height);

    /// converts the x-value from device to world coordinates
    float Xdc2wc(int dc, int normTr = -1);

    /// converts the y-value from device to world coordinates
    float Ydc2wc(int dc, int normTr = -1);

    ///
    virtual void setLineProp(float width, int type, int arrowsize = 1) { }

    /// fillstyle: 0 = no fill, 1 = solid fill, 2 = fill density = 60%, ...
    virtual void setPolyProp(int mode, int fillstyle = 1);

    ///
    virtual void doUpdate();

    ///
    virtual void doClear(bool);

    ///
    virtual void doOutput() { }

    /// Draws a vector from x1,y1 to x2,y2
    virtual void doVect(float x1, float y1, float x2, float y2) { }

    /// Draws an overlay vector from x1,y1 to x2,y2
    virtual void doOverlayVect(float x1, float y1, float x2, float y2) { }

    ///
    virtual void doTriangle(float x1, float y1, float x2, float y2,
                            float x3, float y3) { }

    /// Draws a line with num vertices
    virtual void doLine(int num, float *X, float *Y) { }

    /// Draws an overlay line with num vertices
    virtual void doOverlayLine(int num, float *X, float *Y) { }

    /// Draws a closed polygon with num vertices (maybe filled)
    virtual void doPoly(int num, float *X, float *Y) { }

    /// Draws a circle at center xc, yc with the given radius
    virtual void doCircle(float xc, float yc, float radius,
                          float complexity = 0.5) { }

    /// Draws an arc at center xc, yc with the given radius and start/end angle
    virtual void doArc(float xc, float yc, float radius,
                       float start = 0., float end = 360.) { }

    /// Draws a rectangle
    virtual void doRect(float blX, float blY, float trX, float trY) { }
    virtual void doRect(float blX, float blY, float trX, float trY, float alpha, float maxy) { }

    ///
    virtual void doImage(float x, float y, int w, int h,
                         unsigned char* imagebuffer) { }

    ///
    virtual void doImage(int w, int h, unsigned char* imagebuffer) { }

    ///
    virtual void doImage(float x, float y, int w, int h,
                         unsigned int* imagebuffer) { }

    ///
    virtual void doImage(int w, int h, unsigned int* imagebuffer) { }

    ///
    virtual void doImage() { }

    /// Displays a text at a given position
    virtual void doText(float x, float y, char* text) { }

    /// Displays a text appending it at the last one
    virtual void doText(char* text) { }

    /// Displays a text at a given position vertical (bottom-up)
    virtual void doVertText(float x, float y, char* text) { }

    /// Displays a text appending it at the last one vertical (bottom-up)
    virtual void doVertText(char* text) { }

    ///
    void setTextProp(int);

    ///
    virtual PzFont* getFont();

    ///
    virtual PzFont* getFont(int n);

    ///
    int getNormalFontIndex() { return normalFont; }

    ///
    int getBigFontIndex() { return bigFont; }

    ///
    int getSmallFontIndex() { return smallFont; }

    ///
    int getHugeFontIndex() { return hugeFont; }

    ///
    int getSymbolFontIndex() { return symbolFont; }

    /** Selects if smaller, normal or bigger fonts should be used.
        Call method _after_ the fonts are loaded! Returns false if no fonts
        are loaded.
    */
    bool selectFontSet(PzFontSet fs);

    /// Returns font set currently in use
    PzFontSet fontSet() { return (PzFontSet)smallFont; }

    ///
    virtual void doMarker(int numVertex, float* X, float* Y, int type) { }

    ///
    virtual void doMarker(float X, float Y, int type) { }

    ///
    virtual void doInfo(char* infotext) { }

    ///
    virtual void doProlog(FILE* fp) { }

    ///
    virtual void doEpilog() { }

    ///
    virtual int newDList();

    ///
    virtual void closeDList();

    ///
    bool isInSelectMode() { return inpMode == SELECTMODE; }

    ///
    bool isInLineInputMode() { return inpMode == LINEINPUTMODE; }

    ///
    bool isInLassoMode() { return inpMode == LASSOMODE; }

    ///
    bool isInZoomMode() { return inpMode == ZOOMMODE; }

    ///
    bool isInRectInputMode() { return inpMode == RECTINPUTMODE; }

    ///
    bool isInCircleInputMode() { return inpMode == CIRCLEINPUTMODE; }

    ///
    bool isInInputMode(unsigned int mask = 0xff) { return (inpMode&mask) > 0; }

    ///
    virtual void setInputMode(int mode , void* obj);

    ///
    virtual int inputMode() { return inpMode; }

    ///
    virtual void setObjectName(int type, PzPlotObject* obj,
                               bool priority = false);

    ///
    int currObjectType() { return currType; }

    ///
    virtual void setClipping(bool clipflag) { useClipping = clipflag; }

    ///
    virtual bool getClipping() { return useClipping; }

    ///
    void setSelectionCB(PzSelCB* clientfunc, void* clientdata);

    ///
    void unsetSelectionCB() { selectionCallback = NULL; }

    ///
    void setUpdateCallback(PzUpdateCB* clientfunc, void* clientdata);

    /// unsets the notifier above
    void unsetUpdateCallback() { updateCallback = NULL; }

    ///
    void setFKeyCallback(PzFunctionKeyRelCB* clientfunc, void* clientdata);

    /// unsets the notifier above
    void unsetFKeyCallback() { fkeyCallback = NULL; }

    ///
    void setInputCallback(PzLineInputCB* clientfunc, void* clientdata);

    /// unsets the notifier above
    void unsetInputCallback() { inputCallback = NULL; }

    /// sets the mouse press callback. Used by plot objects for interaction 
    void setMousePressCallback(PzMousePressCB* clientfunc, PzPlotObject* pobj);

    ///
    void unsetMousePressCallback(PzPlotObject* pobj);

    /** sets the mouse press callback. Used by PzPlot e.g. in order to identify
        a plotarea. Called on mouse press with control modifier.
    */
    void setMousePressPlotCallback(PzMousePressPlotCB* clientfunc,
                                   PzPlot* plot);

    ///
    void unsetMousePressPlotCallback(PzPlot* plot);

    /// sets the mouse release callback. Used by plot objects for interaction 
    void setMouseRelCallback(PzMouseRelCB* clientfunc, PzPlotObject* pobj);

    ///
    void unsetMouseRelCallback(PzPlotObject* pobj);

    /// sets the key release callback. Used by plot objects for interaction 
    void setKeyRelCallback(PzKeyRelCB* clientfunc, PzPlotObject* pobj);

    ///
    void unsetKeyRelCallback(PzPlotObject* pobj);

    /// sets the mouse move callback. Used by the plot objects for interaction 
    void setMouseMoveCallback(PzMouseMoveCB* clientfunc, PzPlotObject* pobj);

    ///
    void unsetMouseMoveCallback(PzPlotObject* pobj);

    /// Loads a font with the requested size
    virtual PzFont* loadFont(const char* family, int size = 10, int weight = 0,
                             bool italic = 0)
                    { return NULL; }

};

#endif /* PZ_GENDRAW */

/// @}
