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

/// @addtogroup hxsegeditor hxsegeditor
/// @{
#ifndef GIQ_FRAMEBUFFER_H
#define GIQ_FRAMEBUFFER_H

#include <qwidget.h>
#include <qcursor.h>
#include <QResizeEvent>
#include <QWheelEvent>
#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPaintEvent>
#include "GiFrameBuffer.h"
#include "McMouseButtonEvent.h"
#include "McMotionEvent.h"
#include "McKeyboardEvent.h"
#include "McLeaveWindowEvent.h"
#include "HxGiWinDLLApi.h"

#ifdef _WIN32
    #include <windows.h>
#endif

class QImage;
class QTimer;
class GiShape;

/** Provides a Qt implementation of the frame buffer.*/
class HXSEGEDITOR_API GiQFrameBuffer : public QWidget, public GiFrameBuffer
{
    Q_OBJECT

  protected:
    McMouseButtonEvent buttonEvent;
    McMotionEvent motionEvent;
    McKeyboardEvent keyEvent;
    McLeaveWindowEvent mcleaveEvent;

    QImage*         qimage;
    McVec2i         winSize;            // Size of drawing area
    McBox2i         pasteBox;
    unsigned int    sliceSliderCursor:1;
    unsigned int    sliceSliderActive:1;
    int             sliceSliderOffset;
    QCursor         savedCursor;

    QTimer*         mWheelTimer;
    int             mWheelDelta;

    void createBuffer(const McVec2i& size);
    void destroyBuffer();

    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent*);
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void wheelEvent(QWheelEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void translateKeyEvent(QKeyEvent*);
    void leaveEvent(QEvent*);

    virtual void setMemSize(const McVec2i& memSize);

  public slots:
    void wheelBrowsingStopped();

  public:
    static int collectKeyEvents;

    /** Get offset of visible area relative to virtual framebuffer.
     If window is larger then */
    McVec2i getDrawingAreaOffset();

    /** Creates a framebuffer of given size. */
    GiQFrameBuffer(const char* name, QWidget* parent,
                   int width, int height,
                   int winWidth, int winHeight);

    /// Destructor.
    ~GiQFrameBuffer();

    /// Copies framebuffer content onto screen.
    virtual void paste();

    /// Copies subarea of frame buffer onto screen.
    virtual void paste(const McBox2i& areaToBeDisplayed);

    /// Repositions subimage to be displayed.
    virtual void setOffset(const McVec2i& newOffset);

    ///
    virtual void resize(const McVec2i& size,
                        const int* pixelSizeX=0, const int* pixelSizeY=0);

    /// Redraws parts of the physical buffer.
    virtual void render(const McBox2i& region, GiShape* notMe = NULL);

    /// Redraws physical buffer, but does not display it.
    virtual void render(GiShape* notMe = NULL);

    /// Change flip flags.
    virtual void setFlip(int flipx, int flipy);

    void waitForSharedMemory();

    McVec2i translatePosFromScreen(const McVec2i& mp);

    McVec2i translatePosToScreen(const McVec2i& mp);

    virtual void setCursor(const QCursor& c);

};

#endif

/// @}
