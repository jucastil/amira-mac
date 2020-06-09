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

/// @addtogroup hxcore hxcore
/// @{
#ifndef  QX_RANGE_SLIDER_H
#define  QX_RANGE_SLIDER_H

#include <hxcore/HxAmiraWinDLLApi.h>

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>

#include <mclib/McDArray.h>
#include <mclib/McHandle.h>

class McHistogram;

/** Range slider */
class HXCORE_API QxRangeSlider : public QWidget
{
    Q_OBJECT
    
  public:
    /// Constructor.
    QxRangeSlider(QWidget* parent=NULL, const char* name=NULL);
    
    /// Destructor.
    ~QxRangeSlider();

    /// Size hint method
    QSize sizeHint() const;

    /// Returns the current value of the slider.
    float value(int idx) const { return mValue[idx]; }

    /// Returns min/max allowed data value.
    float dataClipValue(int idx) const { return mDataClipValue[idx]; }
    
    /// Deprecated: use dataClipValue instead
    float clipValue(int idx) const { return mDataClipValue[idx]; }

    /// Returns min/max displayed data value.
    float displayClipValue(int idx) const { return mDisplayClipValue[idx]; }

    /// Returns true if tracking is enabled.
    bool tracking() const { return mTrackingFlag; }

    /** Enables or disables slider tracking. If tracking is enabled (default),
        the slider emits the valueChanged() signal whenever the slider
        is being dragged. If tracking is disabled, the slider emits the
        valueChanged() signal when the user releases the mouse button
        (unless the value happens to be the same as before). */
    void setTracking(bool tracking) { mTrackingFlag = tracking; }

    /** Set a histogram to be displayed. */
    void setHistogram(const McHistogram& histogram);

    /** Sets the histogram so that it looks the same as in the other
        range slider. */
    void setHistogram(const QxRangeSlider* other);

    /** Enable/disable painting of the histogram */
    void showHistogram(bool showHistogram);

    bool isHistogramEnabled() const;

    /** Sets a marker line */
    void setMarker(float value);

    /** Unsets a marker line previously set via setMarker(). */
    void clearMarker();
    
	/** Set the slider, so that a rangle larger than the mHistoRange
        can be selected. */
    bool toggleExpandable(bool state);

    void emitAction(float min, float max);

    void showMinMaxHandles() { mShowRangeSlider = true; }
    void hideMinMaxHandles() { mShowRangeSlider = false; }
    bool areMinMaxHandlesVisible() { return mShowRangeSlider; }

    /** If set to true the value of the minimum slider handle may be larger 
        than the value represented by the maximum slider handle and vice versa.
    */
    void setInvertible(bool inFlag) { mInvertible = inFlag; }
    bool isInvertible() const { return mInvertible; }

    /** Set the zoom factor */
    void setZoomFactor( float factor ) { mZoomFactor = factor; }
    float getZoomFactor() const        { return mZoomFactor;}

    void zoomViewAll();
    void zoomHistogram();


  public slots:
    /** Sets the value of the slider. The method returns true if the
        value has been changed, or zero if the slider already was set
        to the specified value. */
    bool setValue(float min, float max);

    /** Sets range of allowed values. The method returns true if the
        slider value was changed because of clipping. */
    bool setDataClipValue(float min, float max);

    /// Deprecated: use setDataClipValue instead.
    bool setClipValue(float min, float max);

    /** Sets the data range being displayed by the slider. This range
        might be different (usually smaller) than the range set via
        setDataClipRange(). */
    void setDisplayClipValue(float vmin, float vmax);

    /** Returns actual slider range (maybe larger than display window 
        if slider is scaled). */
    float rangeValue(int idx) const;

  signals:
    void valueChanged(float min, float max);
    void sliderPressed();
    void sliderMoved(float min, float max);
    void sliderReleased();
    void doubleClick(int dummy);
    void rightButtonPressed(int x, int y);

  protected:  
    virtual void paintBackground(QPainter& painter, const QRect & rect) {}
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);
    void leaveEvent(QEvent*);
    void enterEvent(QEvent*);
    void wheelEvent ( QWheelEvent * );
    
    float mValue[2];
    float mDataClipValue[2];
    float mDisplayClipValue[2];
    float mHistoRange[2];
    float mMarker;
    bool  mExpandable;
    McDArray<float> mHistogram;
    bool mHistogramEnabled;
    float mZoomFactor;

    int mPickOffset;
    unsigned int mChangedFlag:1;
    unsigned int mTrackingFlag:1;
    unsigned int mPickedHandle:2;
    unsigned int mLastMinMaxHandlePicked;
    unsigned int mHoverHandle:2;
    unsigned int mHasMarker:1;
    float mClipValueDragging[2];

    void drawMinHandle(QPainter&, int xMin, bool highlight=false);
    void drawMaxHandle(QPainter&, int xMax, bool highlight=false);
    void drawMidHandle(QPainter&, int xMin, int xMax, bool highlight=false);

    void clampDataClipValue();

    void updateClipValueDragging();
    bool isInverted() const;

    void zoomIn( float factor );
    void zoomOut( float factor );

    bool  mInvertible;
    bool  mInverted;

private:

    QBrush highlightFillBrush;
    QBrush fillBrush;

    QColor highlightOutLineColor;
    QColor outLineColor;

    QColor highlightShadowColor;
    QColor shadowColor;

    QColor highlightShadowColor2;
    QColor shadowColor2;

    QColor histogramColor;

    bool mMouseInside;
    bool mShowRangeSlider;

};

#endif // GIQ_RANGE_SLIDER_H


/// @}
