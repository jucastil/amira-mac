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
#ifndef QZ_QTDRAW
#define QZ_QTDRAW

#include <QWidget>
#include <QShowEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QResizeEvent>
#include <QPixmap>
#include <QMouseEvent>
#include <QKeyEvent>

#include "PzGenDraw.h"
#include "PzPlotWinDLLApi.h"

class QPixmap;
class QPrinter;
class QPen;
class QBrush;
class QImage;
class QPaintEvent;
class QResizeEvent;
class QShowEvent;

/**
   Qt plot driver.
@author Olaf Paetsch
*/
class QzQtDraw : public virtual QWidget, public PzGenDraw {

  Q_OBJECT

  public:
	  ///Factors for pen width, font size etc. to achieve a high quality on screen and offscreen
	  struct TScreenQualityFactors
	  {
		   TScreenQualityFactors()
			   :penWidthFactor(1)
			   ,fontSizeFactor(1)
			   ,fontWeight(-1)
		   {}

           int penWidthFactor;
		   int fontSizeFactor;
		   int fontWeight;
	  };


  private:

    void initDefaults();

    inline void returnFormOverlay();

    inline void startOverlay();

    // arrow width table
    static int arrWT[3][6];

    // arrow length table
    static float arrLT[3];

    McDArray<PzSelObject*> allRes;

    int                        textX, textY;
    int                        posXpressed, posYpressed;
    int                        oldXmoved, oldYmoved;
    bool                       moveEnd;
    TScreenQualityFactors screenQualityFactors;

  protected:

    /// called on every resize event
    virtual void resizeEvent(QResizeEvent* re);

    /// called on every repaint (update) event
    virtual void paintEvent(QPaintEvent* pe);

    /// called only once when plot widget is realized
    virtual void showEvent(QShowEvent* se);

    ///
    virtual void mouseDoubleClickEvent(QMouseEvent* event);

    ///
    virtual void mouseMoveEvent(QMouseEvent* event);

    ///
    virtual void mousePressEvent(QMouseEvent* event);

    ///
    virtual void mouseReleaseEvent(QMouseEvent* event);

    ///
    virtual void keyPressEvent(QKeyEvent* event);

    ///
    virtual void keyReleaseEvent(QKeyEvent* event);

    ///
    virtual void returnInput();

    ///
    void drawArrow(int ix, int iy, int ixp, int iyp, int size = 2);

    /// Displays an overlay rectangle over the current drawing using 2. Pixmap
    void doOverlayBox(int blX, int blY, int trX, int trY);

    /// Displays an overlay line over the current drawing using  2. Pixmap
    void doOverlayLine(McDArray<int>x, McDArray<int>y, bool closed = false,
                       bool incremental = true);

    /// Displays an overlay rectangle over the current drawing using  2. Pixmap
    void doOverlayCircle(int centerX, int centerY, int radius);

    QWidget                   *parentWdgt;
    QPainter                  *painter;
    QPainter                  *widgetpainter;
    QPixmap                   *paintbuf;
    QPixmap                   *overlaybuf;
    QPen                      *pen, *ovlpen;
    QBrush                    *brush;
    QImage                    *image8, *image32;
    PzPlot                    *plotWin;

  public:

    /// Constructor
    QzQtDraw(char* name, QWidget* parent, int width, int height, PzPlot* obj, TScreenQualityFactors* argpScreenQualityFactors = NULL);

    /// Constructor
    QzQtDraw(char* name, QPrinter* printer, int width, int height, PzPlot* obj);

    /// Destructor
    ~QzQtDraw();

    virtual const char* className() { return "QzQtDraw"; }

	TScreenQualityFactors getScreenQualityFactors() const
	{return screenQualityFactors;}

    ///
    void setProj(double left, double right, double bottom, double top,
                 double mynear = -1.0,
                 double myfar  =  1.0);

    ///
    void useNormTr(int num = -1);

    ///
    void setLineProp(float width, int type, int arrowsize = 1);

    ///
    void doUpdate();

    ///
    void doClear(bool clearDList);

    /// Takes a snapshot
    void doOutput();

    /// Draws a vector from x1,y1 to x2,y2
    void doVect(float x1, float y1, float x2, float y2);

    /// Draws an overlay vector from x1,y1 to x2,y2 using XOR raster op
    void doOverlayVect(float x1, float y1, float x2, float y2);

    ///
    void doTriangle(float x1, float y1, float x2, float y2, float x3, float y3);

    /// Draws a line with num vertices
    void doLine(int num, float *X, float *Y);

    /// Draws an overlay line with num vertices using XOR raster op
    void doOverlayLine(int num, float *X, float *Y);

    /// Draws a closed polygon with num vertices (maybe filled)
    void doPoly(int num, float *X, float *Y);

    /// Draws a circle at center xc, yc with the given radius
    void doCircle(float xc, float yc, float radius, float complexity = 0.5);

    /// Draws an arc at center xc, yc with the given radius and start/end angle
    void doArc(float xc, float yc, float radius, float start = 0.,
               float end = 360.);

    /// Draws a rectangle
    void doRect(float blX, float blY, float trX, float trY);
    void doRect(float blX, float blY, float trX, float trY, float alpha, float maxy);

    ///
    void doImage(float x, float y, int w, int h, unsigned char* imagebuffer);

    ///
    void doImage(int w, int h, unsigned char* imagebuffer);

    ///
    void doImage(float x, float y, int w, int h, unsigned int* imagebuffer);

    ///
    virtual void doImage(int w, int h, unsigned int* imagebuffer);

    ///
    void doImage();

    /// Displays a text at a given position
    void doText(float x, float y, char* text);

    /// Displays a text appending it at the last one
    void doText(char* text);

    /// Displays a text at a given position vertical (bottom-up)
    void doVertText(float x, float y, char* text);

    /// Displays a text appending it at the last one vertical (bottom-up)
    void doVertText(char* text);

    /// Displays markers at the given positions
    void doMarker(int numMarkers, float* X, float* Y, int type = 0);

    /// Displays a marker at the given position
    void doMarker(float X, float Y, int type = 0);

    /// sets the clipping on or off
    void setClipping(bool clipflag);

    ///
    void setInputMode(int mode , void* obj);

    /// Loads a font with the requested attributes
    PzFont* loadFont(const char* family, int size, int weight = QFont::Normal,
                     bool italic = false);

	///Returns the rendered plot as image.
	QImage getRenderAreaAsImage() const;
};

/**
   Qt plot driver used for printing.
@author Olaf Paetsch
*/
class QzQtPrint : public QzQtDraw {

  private:

    bool     ePS, Frame, BlackWhite, AutoScale, WhiteBg;

  public:

    /// Constructor
    QzQtPrint(char* name, QPrinter* printer, int width, int height,
              PzPlot* obj);

    ///
    void setAttr(bool eps, bool frame = true, bool whitebg = true,
                 bool blackwhite = true, bool autoscale = true);

    ///
    void setFG_colour(float r, float g, float b, float a = 0.0);

    ///
    void setFG_colour(int r, int g, int b, float a = 0.0);

    ///
    void setBG_colour(float r, float g, float b, float a = 0.0);

    ///
    void setBG_colour(int r, int g, int b, float a = 0.0);

};

#endif /* QZ_QTDRAW */

/// @}
