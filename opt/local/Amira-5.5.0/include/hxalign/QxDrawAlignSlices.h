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

/// @addtogroup hxalign hxalign
/// @{
#ifndef QX_DRAW_ALIGN_SLICES_H
#define QX_DRAW_ALIGN_SLICES_H

#include <qwidget.h>
#include <qslider.h>
#include <qmenubar.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <QToolBar>
#include <qpixmap.h>
#include <q3scrollview.h> 
#include <qpoint.h>
#include <qtextstream.h>
#include <qwidget.h>
#include <qcursor.h>

#include <mclib/McVec2i.h>
#include <mclib/McDArray.h>
#include <hxalign/SliceInfo.h>
#include <hxalign/QxAutoAlignToolBar.h>

enum ViewModes { RED_GREEN=1, CHESSBOARD=2, AVERAGE=3, INVERT=4 };
//enum { UPPER=1, LOWER=-1, BOTH = 2 };
enum { EDIT=1, DRAW=2, HXPOINT=3 };


#define POINTDIM 10

class QxAlignUndoRedo;
class QxAlignSlices;

/** \class QxDrawAlignSlices QxDrawAlignSlices.h "hxalign/QxDrawAlignSlices.h"
 *  \brief This class provides the main alignment window, including the rendering and interaction.
 *
 *  This class provides the main alignment window, including the rendering and interaction.
 */

class QxDrawAlignSlices : public Q3ScrollView
{
  Q_OBJECT

  public:
    /** Pixel types for different platforms */
    enum PixelType {
        RGBA, /**< 32 bit (24 used) e.g. Indigo2 */
        BGRA, /**< 32 bit (24 used) onyx2, Intel-Linux */
        ARGB, /**< 32 bit (24 used) cross platform remote display */
        ABGR  /**< 32 bit (24 used) cross platform remote display */
    };

    /** Constructor */
    QxDrawAlignSlices(QxAlignSlices *parent = 0, const char *name = 0);

    /** Destructor */
    ~QxDrawAlignSlices();

    /** Prepares the data and the widget for drawing, but leaves the actual drawing to draw(). */
    void paintSlice(int width, int height,
        unsigned char* sliceData1,
        unsigned char* sliceData2,
        unsigned char* mappedData1,
        unsigned char* mappedData2,
        SliceInfo& trans1,
        SliceInfo& trans2,
        int nChannels,
        int sliceNumber);

    /** Sets the slice to display to UPPER, LOWER or BOTH */
    void displaySlice(int upperOrLower);

    void transform(SliceInfo);

    int getEditMode() const { return editMode; }

    int getEditableSlice();

    void setPoints(McDArray<QPoint> *p1,McDArray<QPoint> *p2);

    bool insideLandmark(QPoint, QPoint);
    
    int clearSelection();

    void setRotateCursor(bool b);

    void setUndo(QxAlignUndoRedo* u) { undo = u; }

    void setFixReference(bool b);

    void drawImageSize(float scaleX, float scaleY, bool active,int offsetX=-1,int offsetY=-1);

    int redrawInhibit;

    /** 
     * Called to update the viewport.
     */
    void updateViewport();

  signals:
    void click();
    void translated(float,float,bool);
    void rotated(float,bool);
    void addPoint(QPoint);
    void removePoint(QPoint);
    void removePoint(int);
    void movePoints(QPoint, int);
    void enableRemove(bool);
    
  public slots:
    void setZoom(float);
    void setEditableSlice(int);
    void setEditMode(int);
    void changeAlignMode(int);

    void redGreen() {viewMode = RED_GREEN; updateViewport(); }

    //GW not inline now
    //  void chess() { viewMode = CHESSBOARD; updateViewport(); }
    void chess(int chessFieldS);
    //GW this updates the chessFieldSize if viewMode == CHESSBOARD
    //and chessFieldSize is changed in the option panel.
    void updateChessFieldSize(int chessFieldS);
    void avg() { viewMode = AVERAGE; updateViewport(); }
    void invert() { viewMode = INVERT; updateViewport(); }
    void removeLandmark();
    void addLandmark();

  protected:
    QImage* img;
    int chessFieldSize;

    /** Draws the image in the style according to viewMode */
    void draw();

    unsigned char* memory;
    McVec2i imageSize;
    int bytesPerLine;

    McDArray<QPoint> contour;
    
    int nx,ny;

    unsigned char* sliceData1;
    unsigned char* sliceData2;
    unsigned char* mappedData1;
    unsigned char* mappedData2;

    /** The current transformation of the lower slice. The
       translations dx and dy must be floats. Otherwise we
       get trouble if the magnification factor is > 1. */
    float dx1,dy1,rot1;
    // The current transformation of the upper slice
    float dx2,dy2,rot2;

    int slice;

    SliceInfo *trans1, *trans2;

    McDArray<QPoint> *points1, *points2;
    McDArray<QColor> pointColors;

    float zoom;

    int origx,origy;
    int dx1Init, dy1Init, dx2Init, dy2Init;

    bool move;
    bool rotate;

    /** Indicates the current display mode, e.g. INVERT, CHESS, etc. */
    int viewMode;
    int nrColors;
    float minVal;
    float maxVal;
    int dataType;

    /** slice to display: either UPPER, LOWER or BOTH */
    int sliceToDisplay;

    int editableSlice;
    int editMode;
    int alignMode;

    bool editingMask;
    bool allPoints;
    int selectedPoint;
    int lastSelectedPoint;
    bool addingPoint;
    bool xformAll;
    bool fixReference;
    QxAlignUndoRedo* undo;
    
    void viewportMouseDoubleClickEvent(QMouseEvent *e);
    void viewportMousePressEvent(QMouseEvent *e);
    void viewportMouseReleaseEvent(QMouseEvent *e);
    void viewportMouseMoveEvent(QMouseEvent *e);
    void viewportResizeEvent(QResizeEvent*e);
    void viewportPaintEvent( QPaintEvent * );

    void redGreenView();
    void chessView();
    void averageView();
    void invertView();
    void drawPoints();
    void drawPoint(const QPoint&, const QColor&, bool, bool);
    void createImage(int width, int height);
    void destroyImage();

    McVec2f mapWindowToImage(int ex, int ey) const;

    /** Parent widget. Top level user interface for AlignSlices module. */
    QxAlignSlices* alignView;

    QCursor rotateCursor;

};

#endif

/// @}
