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
#ifndef  QX_SLIDER_H
#define  QX_SLIDER_H

#include <math.h>
#include <qwidget.h>
#include <hxcore/HxAmiraWinDLLApi.h>
#include <mclib/McDArray.h>

/** A slider with traditional Amira-style look and feel. The
    interface is more or less compatible with the native QSlider.
    This class is used in HxPortFloatSlider and at several
    other places such as in QxColorDialog or in the image
    segmentation editor. In addition to a standard slider several
    enhancements are available: (1) a colored background for use
    in a color dialog, (2) display of a number of tick marks for
    use in a keyframe editor, (3) display of two optional region
    delimiters. */

class HXCORE_API QxSlider : public QWidget {
    
    Q_OBJECT
    
  public:
    /// Defines how the background is drawn
    enum BackgroundType {
        /// Monochrome background (default).
        Type_Plain = 0,
        /// Colors are interpolated in RGB color space.
        Type_RGB = 1,
        /// Colors are interpolated in HSV color space.
        Type_HSV = 2
    };

    /// Denotes different frame styles.
    enum FrameStyle {
        ///
        MaximalFrame = 0,
        ///
        NormalFrame = 1,
        ///
        MinimalFrame = 2
    };

    /// Constructor.
    QxSlider(QWidget* parent=NULL, const char* name=NULL, BackgroundType t=Type_Plain);
    
    /// Destructor.
    ~QxSlider();

    /// Returns the current value of the slider.
    float value() const { return theValue; }

    /// Returns smallest allowed value.
    float minValue() const { return theMinValue; }

    /// Returns biggest allowed value.
    float maxValue() const { return theMaxValue; }

    /// Returns lower bound of sub range.
    float subMinValue() const { return theSubMinValue; }

    /// Returns upper bound of sub range.
    float subMaxValue() const { return theSubMaxValue; }

    /// Returns the frame style of the slider.
    int frameStyle() const { return theFrameStyle; }

    /// Returns true if the sub range feature is enabled.
    bool hasSubRangeButtons() const { return subRange; }

    /// Returns true if tracking is enabled.
    bool tracking() const { return trackingFlag; }

    /** Set slider type. Depending on the type the background of the
        slider is drawn in monochrome (@c Type_Plain) or as a color
        ramp interpolating between the two colors defined using
        setColor. If @c Type_RGB is set these colors are assumed
        to be RGB colors. If @c Type_HSV is set the colors are assumed
        to be HSV colors. */
    void setBackgroundType(int);
    
    /// Set background colors for @c Type_RGB or @c Type_HSV sliders.
    void setColors(const float *fc, const float *lc);
    
    /*** Sets an array of tick marks. If present tick marks are drawn
         as red vertial lines on top of the slider background. */
    void setTicks(const McDArray<float>& t);
    
    /// Sets the frame style of the slider, see FrameStyle.
    void setFrameStyle(int);

    /// Enables or disables the sub range feature, see setSubRange.
    void setSubRangeButtons(int onOff);

    /** Enables or disables slider tracking. If tracking is enabled (default),
        the slider emits the valueChanged() signal whenever the slider
        is being dragged. If tracking is disabled, the slider emits the
        valueChanged() signal when the user releases the mouse button
        (unless the value happens to be the same as before). */
    void setTracking(bool tracking) { trackingFlag = tracking; }

  public slots:
    /** Sets the value of the slider. The method returns true if the
        value has been changed, or zero if the slider already was set
        to the specified value. */
    bool setValue(float v);

    /** Sets range of allowed values. The method returns true if the
        slider value was changed because of clipping. */
    bool setRange(float min, float max);

    /** Defines a sub range allowing more detailed adjustment. If a
        subrange is defined, two additional tick marks are drawn in
        the upper half of the slider area. The actual value of the
        slider is restricted to the sub range. Note, that this method
        has no effect if the sub range buttons are not drawn. */
    bool setSubRange(float min, float max);

  signals:
    void valueClipped(float diff);
    void valueChanged(float value);
    void sliderPressed();
    void sliderMoved(float value);
    void sliderReleased();
    void subRangeChanged(float min, float max);

  protected:  
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);

    float theValue;
    float theMinValue;
    float theMaxValue;
    float theSubMinValue;
    float theSubMaxValue;

    unsigned int theFrameStyle:4;
    unsigned int theBackgroundType:2;
    unsigned int subRange:1;
    unsigned int pressedButton:2;
    unsigned int trackingFlag:1;
    unsigned int changedFlag:1;

    int pickOffset;
    float theFirstColor[4];
    float theLastColor[4];
    McDArray<float> ticks;

    void drawBackground (QPainter* p, const QPalette& g);
    void drawDownUIRegion(QPainter*, const QPalette&, int, int, int, int);
    void drawThumbThing(QPainter*, int x, int y);
    void drawLeftSubRangeButton(QPainter*, int x, int y);
    void drawRightSubRangeButton(QPainter*, int x, int y);

    int getPosition(const float& value) {
        float scale = (theMaxValue > theMinValue) ?
            (width()-14)/(theMaxValue-theMinValue) : 0;
        return (int) floor(6 + scale*(value-theMinValue) + 0.5);
    }
    
    int getSubPosition(const float& value) {
        float scale = (theSubMaxValue > theSubMinValue) ?
            (width()-14)/(theSubMaxValue-theSubMinValue) : 0;
        return (int) floor(6 + scale*(value-theSubMinValue) + 0.5);
    }

  public:
    static void drawDownUIBorders(QPainter* p, const QPalette& g,
        int x1, int y1, int x2, int y2, int n);

};

#endif

/// @}
