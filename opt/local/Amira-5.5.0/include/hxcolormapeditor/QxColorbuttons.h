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
#ifndef  QX_COLORBUTTONS_H
#define  QX_COLORBUTTONS_H

#include <qwidget.h>
#include <mclib/McColor.h>

class QMouseEvent;
class HxColormap256;

typedef int (*TPointRect)[2];

/** This widget display the entries of a HxColormap256 in a table.
    Individual color cells may be marked as key points. At any time
    there is one color cell which has the focus and which is drawn
    using a thick frame. When a color cell is marked or unmarked or
    when the focus changes appropriate signals are emitted. */

class QxColorbuttons : public QWidget
{
    
  Q_OBJECT

  public:
    /// Constructor
    QxColorbuttons(QWidget *parent = NULL, const char *name = NULL);

    /// Destructor
    ~QxColorbuttons();
   
    /// Set a colormap
    void setColormap(HxColormap256 *map);

    /// Get the colormap
    HxColormap256* getColormap() const { return colormap; }

    /// Set the default color
    void setDefaultColor (const McColor& defaultColor);
    
    /// Get the default color
    const McColor& getDefaultColor() const { return defaultColor; }
    
    /** Set the default alpha value. Often the alpha value and the color
        are changed at the same time. The parameter shouldRedraw allows
        you to skip calling redraw() in the body of setDefaultAlpha().
        In this case setDefaultAlpha() should be called before
        setDefaultColor() to let this function make the redraw(). */
    void setDefaultAlpha(float newDefaultAlpha, int shouldRedraw=1);

    /// Get the default alpha value
    float getDefaultAlpha() const { return defaultAlpha; }

    /// Get the focus
    int getFocus() const { return focus; }

    /// Set the focus
    void setTheFocus(int i);

    /// Test if entry has a knot
    int hasKnot(int i);

    /// Set a knot
    void setKnot(int i);

    /// Unset a knot
    void unsetKnot(int i);

    /** Returns a pointer to a new allocated copy of the whole knotmap
        (must be deleted, not freed).*/
    int* getAllKnots() const;

    /// Redraw a range of cells
    void redrawRange(int left_index, int right_index);

    /// Specifies which channels should be snapped during move.
    void setChannelMask(int mask) { channelMask=mask; }

  public slots:
    void unmarkFocusCell();

 protected:
    /// Calculation of the positions of the buttons
    virtual void calculateButtons(int w, int h);
    /// Determines cell in which was clicked
    virtual int     whichCell(short x, short y);
    /** Determining the left  knot of a colorindex.
        The  method does NOT test if the colorindex is valid!!!!*/
    virtual int     findLeftKnot(int colorindex);
    /** Determining the right knot of a colorindex.
        The  method does NOT test if the colorindex is valid!!!!*/
    virtual int     findRightKnot(int colorindex);
    /// Moves a color cell (with snapping)
    virtual void    moveCell(int colorindex);
    /// Snapping all colormap entries between the leftindex and rightindex
    virtual void    snapAll(int leftindex, int rightindex);
    /// Needed for overdrawFocus() - must always be inner!
    virtual void    redrawCellWithKnot(int colorindex);

    /// Paint event
    virtual void paintEvent (QPaintEvent*);
    /// Resize event
    virtual void resizeEvent (QResizeEvent*);
    /// mouse button press event
    virtual void mousePressEvent ( QMouseEvent * );
    /// mouse button double click event
    virtual void mouseDoubleClickEvent ( QMouseEvent * );
    /// mouse button release event
    virtual void mouseReleaseEvent ( QMouseEvent * );     
    /// mouse move event
    virtual void mouseMoveEvent ( QMouseEvent * );
    
    /// Draw the focuse 
    virtual void    drawFocus(QPainter * p);
    /// Overdraw the focus
    virtual void    overdrawFocus(QPainter * p);
    /// Procedure to draw all (buttons, knots and focus)
    virtual void    drawAll(QPainter * p);
    /// Draw a knot
    virtual void    drawKnot(int colorindex, int inner=0);
    /// Overdraw a knot
    virtual void    overdrawKnot(int colorindex, int inner=0);

    int	    widgetSize[2];
    HxColormap256*	    colormap;
    int*            knot;
    McColor	    defaultColor;
    float           defaultAlpha;
    QWidget*        widget;
    int             length;   // length of colormap
    int             cellSize;
    int             knotSize;
    TPointRect      colrect;  // upper left corner for each entry 
    TPointRect      knotrect; // (color / knot rectangle)
    int             focus; // on which cell is the focus?
    int             moving; // are we moving a color cell?
    int             movingColor; // index to oldcolormap
    float           (*oldcolormap)[4]; // for the old map before moving
    short           minX, maxX, minY, maxY; // minima / maxima of colrect
    short           buttonsPerRow; 
    int             lastActionWasMarking;
    int             channelMask;

  signals:
    void knotSet(int);
    void knotUnset(int);
    void focusSet(int);
    void colormapChanged();
    void startMoving();
    void finishMoving();
    void drag (int i,float *rgba);
};

#endif  /* QX_COLORBUTTONS_H */

/// @}
