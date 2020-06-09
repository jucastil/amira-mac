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

/// @addtogroup hxcolormapeditor hxcolormapeditor
/// @{
#ifndef QX_COLORCHART_H
#define QX_COLORCHART_H

#include <qwidget.h>
#include <qbitmap.h>
#include <mclib/McColor.h>

class HxColormap256;
class QMouseEvent;
class QColorGroup;
class QPainter;
class ColorChartBrush;

/** Allows to manipulate a HxColormap256 by editing a line graph.
    For each color channel (RGBA or HSVA) a separate curve is displayed.
    The curves can be modified using various brushes.
*/
class QxColorchart : public QWidget
{
    
 Q_OBJECT

 public:
    enum {
        SmallBrush = 0,
        SquareBrush,
        CircleBrush,
        DiamondBrush,
        NumberOfBrushes // must be the last
    };

    enum {
        RGB = 0,
        HSV,
        NumberOfColorModes // must be the last
    };

    /// Constructor
    QxColorchart(QWidget *parent = NULL, const char *name = NULL);
    
    /// Destructor
    ~QxColorchart();
    
    /// Set the colormap
    void setColormap(HxColormap256 *map);
    
    /// Get the colormap
    HxColormap256* getColormap() const { return colormap; }
    
    /// Set the default color
    void setDefaultColor(const McColor& defaultColor);
    
    /// Get the default color
    const McColor& getDefaultColor() const { return defaultColor; }
    
    /** Set the default alpha value. Often the alpha value and a color is
        changed, so the parameter shouldRedraw gives the Opportunity to
        omit the call of redraw() in the body of setDefaultAlpha(). In this
        case setDefaultAlpha() should be called BEFORE setDefaultColor() to
        let this function make the redraw(). */
    void setDefaultAlpha(float newDefaultAlpha, int shouldRedraw = TRUE);
    
    /// Get the default alpha value
    float getDefaultAlpha() const { return defaultAlpha; }
    
    /// Set the Brush
    void setBrush(int which);

    /// Returns brush as QBitmap which can be inserted into menu.
    QBitmap getBrush(int which);

    /// Sets channel which can be edited with the left mouse button.
    void setActiveChannel(int channel);

    /// Returns channel which can be edited with the left mouse button.
    int getActiveChannel() const { return activeChannel; }

    /// Set the index of focus cell.
    void  setFocus(int colorindex);
    
    /// Get the index of focus cell.
    int getFocus() {return focus; }

    /// Set a knot.
    void setKnot(int colorindex);
    
    /// Unset a knot.
    void unsetKnot(int colorindex);
    
    /// Returns whether colorindex has a knot or not.
    int hasKnot(int colorindex);
    
    /// Returns copy of the whole knotmap (must be deleted, not freed)
    int (*getAllKnots() const);
    
    /** Sets the new value for the corresponding entry and channel with
      raising/lowering the color channel between the left and right knot
      the value must be valid for the actual ColorMode (RGB,HSV,YCbCr,..)
      Returns the corresponding indices in leftKnot and rightKnot.*/
    void setValue(int colorindex, int channel, float newValue,
                  int &leftKnot, int &rightKnot);
    
    /// Redraw method with reduced flicker??
    void redrawWithChangedColormap();

    /// For setting showAlpha
    void setShowAlpha(int state);

    /// Returns if showAlpha is set or not
    int isShowAlpha() const { return showAlpha; }
    
    /// Set the color mode
    void setMode(int newMode);

    /// Get the color mode, either RGB or HSV.
    int whichMode() const { return mode; }

    /** "snap" the specified color channels between the left knot and
       the right knot of the focus and return the index of the left knot
       and the right knot.*/
    void snapChannel(int channel, int &left_index, int &right_index);

    /** "snap" ALL color channels between the left knot and
       the right knot of the focus and return the index of the left knot
       and the right knot.*/
    void snap(int &left_index, int &right_index);
    
    /// This method "snaps" the whole colormap
    void snapAll();

  protected:
    enum MoveStatus {
      NewMove,
      MoveGoesOn,
      EndMove
    };
     
    /// Paint event
    virtual void paintEvent(QPaintEvent*);
    
    /// Resize event
    virtual void resizeEvent(QResizeEvent*);

    /// mouse button press event
    virtual void mousePressEvent(QMouseEvent*);
    
    /// mouse button release event
    virtual void mouseReleaseEvent(QMouseEvent*);     
    
    /// mouse move event
    virtual void mouseMoveEvent(QMouseEvent*);

    /** Core of HxColorchart
     Returns if colormap was changed or not.*/
    virtual int     brushBump(short x, short y, short w, short h,
                      int &leftIndex, int &rightIndex,
                      int &clearLeftIndex, int &clearRightIndex);
    /// (Over)draws the brush
    virtual void   drawBrush(short x, short y, int doClear = 0, int inner = 0);
    /// Responsible for moving the Brush
    virtual void    movingBrush(enum MoveStatus status, 
                      short x, short y, short w, short h);
    /// For saving time - calculates global variables
    virtual void    calculateGlobals();
    ///
    virtual void    calculateMode();
    ///
    virtual int     isAbove(short x, short y, short w, short h);
    /// Lighter version of brushBump to clear an area for a given Brush
    virtual void    calculateClearIndices(short x,
        int &leftIndex, int &rightIndex,
        int &clearLeftIndex, int &clearRightIndex);
    /** Determines the left  knot of colorindex.  This method
        does NOT test if the colorindex is valid!!*/
    virtual int  findLeftKnot(int colorindex);
    /** Determines the right  knot of colorindex.  This method
        does NOT test if the colorindex is valid!!*/
    virtual int  findRightKnot(int colorindex);
    /** (Over)draws all knots incl. focus
        Must be called before drawAllChannels() in case of clearing,
        otherwise after it*/
    virtual void drawAllKnotsFocus(QPainter * p, int left_index, int right_index,
        int doClear = 0, int inner = 0); 
    /// (Over)draws all channels
    virtual void drawAllChannels(QPainter * p, int left_index, int right_index,
        int doClear = 0, int inner = 0); 
    /// (Over)draws one channel
    virtual void drawChannel(QPainter * p, int left_index, int right_index, int channel, 
        int doClear = 0, int inner = 0);
    /// Draw the knots and focus 
    virtual void drawKnotFocus(QPainter * p, int index, int inner = 0);
    /// Overdraw the knots and focus 
    virtual void overdrawKnotFocus(QPainter * p, int index, int inner = 0);
    /// Responsible for snapping
    virtual void hiddenSnapChannel(int channel, 
        int leftindex, int rightindex);
    /// Static function for storing the various color models in RGBA
    static void  storeRGBA(HxColormap256 *map,int index,const float rgba[4]);
    /// Static function for storing the various color models in RGBA
    static void  storeHSVA(HxColormap256 *map,int index,const float hsva[4]);
    
    HxColormap256*  colormap;
    int*            knot;
    McColor	    defaultColor;
    float           defaultAlpha;
    int             invalidBrush;
    int             mode;
    float         (*channels)[4]; // the actual values (for the color model)
    float           minValue[4]; // the minima for the actual color model
    float           maxValue[4]; // the maxima for the actual color model
    void          (*store)(HxColormap256*,int,const float[4]); // store...A()
    int             length;   // length of colormap
    int             focus; // on which knot is the focus?
    int             brushingChannel; // on which channel do we brush?
    ColorChartBrush        **brushes; // brushes
    ColorChartBrush         *currentBrush; // pointer to the current brush
    int             above; // whether the brush is above or not
    int             showAlpha; // whether to show alpha or not
    int             maxCalculatingChannel; // depends on alpha: 2 / 3
    int             activeChannel;

    // And now plenty of global variables just to increase performance
    short          *entry_position_x;     // x_pos for every colormap entry
    short         (*entry_position_y)[4]; // y_pos for every colormap entry
                                          // and for every channel
    short           maxPos; // maximal x_pos without extra rules for brushing
    float          *liftdiff; // value increase for maxValue - minValue <= 1
    float           entry_diff_x; // (length-1)/(size_x-1)
    float           diff_pixel_y[4]; // (size_y-1)/(maxValue-minValue)
    float           brushWidthDiff; // difference from right to left
    int*            maxChannel; // maximum Channel for each entry position

    int brushX, brushY;
    QColor brushCol;
 signals:
    void colormapChanged (int,int);
    void startMoving();
    void finishMoving();
};

#endif


/// @}
