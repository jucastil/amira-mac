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

/// @addtogroup hximview hximview
/// @{
#ifndef QX_LIGHT_BOX
#define QX_LIGHT_BOX

#include <qmatrix.h>
#include <qpoint.h>
#include <mclib/McDArray.h>
#include <mclib/McHandle.h>
#include <mclib/McTypedData2D.h>
#include <Inventor/SbBox.h>
#include <Inventor/Qt/SoQtGLWidget.h>
#include <Inventor/SbViewportRegion.h>
#include <hximview/HxImviewWinDLLApi.h>
#include "QxLightBoxShape.h"

class QEvent;
class QScrollBar;

typedef bool (*QxLightBoxEventHandler)(void* userData, QEvent* e);

///
class HXIMVIEW_API QxLightBox : public SoQtGLWidget 
{ 

  Q_OBJECT

  public:    
    ///
    QxLightBox(QWidget* parent, bool embed = true);

    ///
    virtual ~QxLightBox();

    ///
    void setLayout(int nRows, int nCols);

    ///
    void setImage(const McTypedData2D& imageData, float min, float max, int row, int col);

    /// Currently only support for RGB or RGBA (primType bytes, nDataVar 3 or 4).
    void setColorImage(const McTypedData2D& imageData, int row, int col);

    ///
    void unsetImage(int row, int col);

    ///
    void setPixelScale(float xScale, float yScale, int row, int col);

    ///
    void setZoomFactor(float factor, int row, int col);

    ///
    float getZoomFactor(int row, int col) const;
    
    ///
    void setCenter(float x, float y, int row, int col);

    //
    void getCenter(float& x, float& y, int row, int col) const;

    ///
    void select(bool value, int row, int col);

    ///
    void setEventHandler(QxLightBoxEventHandler, void* userData);

    ///
    bool findImageUnderCursor(const QPoint& pos, int& row, int& col) const;

    /// Calls redraw() if necessary.
    void update();

    ///
    SbVec2f map(const SbVec2s& ij, int row, int col);

    ///
    SbVec2f mapf(const SbVec2f& fractional_ij, int row, int col);

    ///
    SbVec2s unmap(const SbVec2f& render_coord, int row, int col);

    ///
    SbVec2f unmapf(const SbVec2f& render_coord, int row, int col);

    ///
    SbVec2f mappedPos(const QPoint& window_coord, int row, int col);

    ///
    QPoint projectToScreen(const SbVec2f& render_coord, int row, int col);

    ///
    void addShape(QxLightBoxShape* shape, int index=-1);

    ///
    void removeShape(QxLightBoxShape* shape);

    ///
    bool blockRedraw(bool value);

    ///
    SbVec2s getImageWindowSize(int row=0, int col=0) const; 

    int numImages() { return mImages.size(); }

    void clearImages();

    void processEvent(QEvent* e);

    bool eventFilter(QObject * object,QEvent *event);

    void test() { testPattern();}

    virtual void show();
    virtual void hide();

  public slots:
    /// Redraws evrything.
    virtual void redraw();

    /// Adjusts the zoom factor so that the image completly fills the window.
    void fitToWindow(int row=-1, int col=-1);

  signals:
    void moveStarted(int row, int col);

    void moved(float deltax, float deltay);

    void moveFinished();

    void zoomStarted(int row, int col);

    void zoomed(float scale);

    void zoomFinished();


  protected:

    struct Image {
        Image();

        int isValid;
        int imageWidth;
        int imageHeight;
        int textureWidth;
        int textureHeight;
        float xCenter;
        float yCenter;
        float zoomFactor;
        unsigned int texName;
        unsigned int swapxy:1;
        unsigned int flipx:1;
        unsigned int flipy:1;
        unsigned int selected:1;
        McDArray<SbVec2f> coordsX;
        McDArray<SbVec2f> coordsY;
        QMatrix mat;
        QMatrix matInv;
        SbViewportRegion viewport;

        SbVec2f map(const SbVec2s& ij);
        SbVec2f mapf(const SbVec2f& fractional_ij);
        SbVec2s unmap(const SbVec2f& render_coord);
        SbVec2f unmapf(const SbVec2f& render_coord);
        void redraw(int viewportWidth, int viewportHeight);
    };

    int mNumRows;
    int mNumCols;
    int mNeedRedraw;
    int mRedrawLock;
    int mMoving;
    int mActiveRow;
    int mActiveCol;
    int mZooming;
    int mZoomRef;
    float mZoomFactor;
    SbVec2f mMoveOrigin;
    SbVec2f mMoveCenter;
    QMatrix mActiveMat;

    McDArray<Image*> mImages;

    void testPattern();

    void* mEventHandlerData;
    QxLightBoxEventHandler mEventHandler;
    McDArray< McHandle<QxLightBoxShape> > shapes;

    friend class QxLightBoxShape;
};

#endif

/// @}
