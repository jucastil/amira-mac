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
#ifndef QX_IMAGE_VIEWER_H
#define QX_IMAGE_VIEWER_H

#include <qwmatrix.h>
#include <mclib/McDArray.h>
#include <mclib/McHandle.h>
#include <mclib/McTypedData2D.h>
#include <Inventor/SbBox.h>
#include <Inventor/Qt/SoQtGLWidget.h>
#include <hximview/QxImageViewerShape.h>
#include <hximview/HxImviewWinDLLApi.h>
#include <hxcore/HxViewerBase.h>

class QScrollBar;

///
class HXIMVIEW_API QxImageViewer : public SoQtGLWidget, public HxViewerBase {

  Q_OBJECT

  public:
    enum Coords {
        BaseCoords,
        TransformedCoords,
        OverlayCoords
    };

    QxImageViewer(QWidget* parent, bool embed = true);

    virtual ~QxImageViewer();

    virtual QWidget * getWidget () const{ return SoQtGLWidget::getWidget(); }
    virtual void show();
    virtual void hide();
    virtual int isVisible(){ return SoQtGLWidget::isVisible() ? 1 : 0; }
    
    void setImage(const McTypedData2D& imageData, float min, float max);

    void setColorImage(const McTypedData2D& imageData);

    void unsetImage();

    void setTransformationMatrix(const QMatrix& matrix);

    const QMatrix& transformationMatrix() const { return mTransformationMatrix; }

    void setPixelScale(float xScale, float yScale);

    void setPixelScalePerLine(float xScale, float* coordPerLine, float yScale=1);
    
    void setOverlayImage(const McTypedData2D& imageData, float min, float max);

    void setOverlayColorImage(const McTypedData2D& imageData);

    void unsetOverlayImage();

    void setOverlayTransformationMatrix(const QMatrix& matrix);

    const QMatrix& overlayTransformationMatrix() const { return mOverlayTransformationMatrix; }

    enum OverlayMode { BLEND=0, ADD=1, MIP=2, CHECKERBOARD=3, WINDOW=4 };

    void setOverlayMode(OverlayMode mode);

    void setOverlayBlendFactor(float factor);

    void setOverlayPatternSize(int size);

    void setFlipX(bool val);

    bool getFlipX() const { return flipx; }

    void setFlipY(bool val);

    bool getFlipY() const { return flipy; }

    void setSwapXY(bool val);
    
    bool getSwapXY() const { return swapxy; }

    void setZoomFactor(float factor);

    float getZoomFactor() const { return zoomFactor; }

    enum Orientation { XY=2, XZ=1, YZ=0 };

    void setOrientation(Orientation orientation);

    Orientation getOrientation() const { return orientation; }

    enum CrossHairMode { OFF=0, RGB=1, WHITE=2 };

    void setCrossHairMode(CrossHairMode mode);

    CrossHairMode getCrossHairMode() const { return crossHairMode; }

    void setCrossHairPosition(const SbVec2s& pos);

    const SbVec2s& getCrossHairPosition() const { return crossHairPosition; }

    void setCrossHairChangedCallback(void (*f)(void*,QxImageViewer*),void* userData=0);

    void setHandleEventCallback(bool (*f)(void*,QxImageViewer*,QEvent*),void* userData=0);

    void setBilinearInterpolation(bool value);

    bool getBilinearInterpolation() const { return bilinear; }

    SbVec2f map(const SbVec2s& ij);

    SbVec2f mapf(const SbVec2f& fractional_ij);

    SbVec2s unmap(const SbVec2f& render_coord);

    SbVec2f unmapf(const SbVec2f& render_coord);

    SbVec2f mappedPos(const QPoint& window_coord);

    QPoint projectToScreen(const SbVec2f& render_coord, Coords input=BaseCoords);

    int getScaledImageWidth() const { return (int)(coordsX.last()[0]); }

    int getScaledImageHeight() const { return (int)(coordsY.last()[0]); }

    int getViewportWidth() const { return viewportWidth; }

    int getViewportHeight() const { return viewportHeight; }

    void addShape(QxImageViewerShape* shape, int index=-1);

    void removeShape(QxImageViewerShape* shape);

    void setScrollbarSlaves(QxImageViewer* horizontal, QxImageViewer* vertical);

    void update();

  public slots:
    void newOffset();

    virtual void redraw();

  protected:
    bool eventFilter(QObject * object,QEvent *event);
    void sizeChanged(const SbVec2s& size);
    void widgetChanged(QWidget *newWidget);
    void updateScrollbars(int w=-1, int h=-1, bool redraw=true);
    void updateCrossHairPosition(const SbVec2s& pos);
    void setTexture();
    void setOverlayTexture();
    void processEvent(QEvent*);
    void renderCheckerBoard();
    void renderOverlayWindow();
    void newOffset(bool redraw);
    void setCursor(int shape);
    int checkOverlayCursor(const QPoint& pos);

    QxImageViewer* hSlave;
    QxImageViewer* vSlave;
    QScrollBar* hScrollBar;
    QScrollBar* vScrollBar;

    float zoomFactor;
    int imageWidth;
    int imageHeight;
    int imageNumChannels;
    float scaledImageWidth;
    float scaledImageHeight;
    int zoomedWidth;
    int zoomedHeight;
    int viewportWidth;
    int viewportHeight;
    int xOffset;
    int yOffset;
    QMatrix mat;
    QMatrix matInv;
    QMatrix mTransformationMatrix;
    QMatrix mOverlayTransformationMatrix;

    unsigned int swapxy:1;
    unsigned int flipx:1;
    unsigned int flipy:1;
    unsigned int needRedraw:1;
    unsigned int needScrollbarUpdate:1;
    unsigned int hasHScrollBar:1;
    unsigned int hasVScrollBar:1;
    unsigned int textureSet:1;
    unsigned int overlayTextureSet:1;
    unsigned int reuseTexture:1;
    unsigned int reuseOverlayTexture:1;
    unsigned int bilinear:1;
    unsigned int redrawLock:8;
    
    unsigned int texName;
    unsigned int textureWidth;
    unsigned int textureHeight;
    unsigned char* texture;
    McDArray<SbVec2f> coordsX;
    McDArray<SbVec2f> coordsY;

    int overlayImageWidth;
    int overlayImageHeight;
    int overlayImageNumChannels;
    unsigned int overlayTexName;
    unsigned int overlayTextureWidth;
    unsigned int overlayTextureHeight;
    unsigned char* overlayTexture;
    float overlayTexCoordX[2];
    float overlayTexCoordY[2];

    OverlayMode overlayMode;
    float overlayBlendFactor;
    int overlayPatternSize;
    SbBox2f overlayWindow;
    QRect overlayRect;
    unsigned short overlayWindowAction;
    unsigned short cursorShape;

    Orientation orientation;
    SbVec2s crossHairPosition;
    CrossHairMode crossHairMode;
    void *crossHairChangedUserData;
    void (*crossHairChangedCallback)(void*,QxImageViewer*);
    void *handleEventUserData;
    bool (*handleEventCallback)(void*,QxImageViewer*,QEvent*);

    McDArray< McHandle<QxImageViewerShape> > shapes;
};

#endif

/// @}
