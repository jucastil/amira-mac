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
#ifndef  QX_FULL_SLIDER_H
#define  QX_FULL_SLIDER_H

#include "QWidget"
#include <QByteArray>
#include <hxcore/QxSlider.h>

class QxLineEdit;
class QToolButton;
class QMenu;

/** A slider with an additional text input field and optional buttons.
    The interface of this widget is similar to the original QSlider.
    The class makes use of a QxSlider but is not derived from
    it. However, for convenience many QxSlider methods are
    wrapped. */

class HXCORE_API QxFullSlider : public QWidget {
    
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

    /// Denotes different state of slider during interaction
    enum SliderState {
      ///
      SLIDER_RELEASED = 0,
      ///
      SLIDER_PRESSED = 1,
      ///
      SLIDER_MOVED = 2
    };

    /// Constructor.
    QxFullSlider(QWidget* parent=0, const char *name=0,
        bool buttons=0, int nColumns=10);
    
    /// Destructor.
    ~QxFullSlider();
    
    float value() const { return slider->value(); }

    float minValue() const { return slider->minValue(); }

    float maxValue() const { return slider->maxValue(); }

    float subMinValue() const { return slider->subMinValue(); }

    float subMaxValue() const { return slider->subMaxValue(); }

    float increment() const { return theIncrement; }
    
    const char* format() const { return theFormat; }
    
    int nColumns() const { return theNColumns; }

    int tracking() const { return slider->tracking(); }

    bool hasButtons() const;

    bool hasSubRangeButtons() const { return slider->hasSubRangeButtons(); }

    void setMinValue (float min);
    
    void setMaxValue (float max);
    
    void setIncrement(float v);
    
    void setFormat(const char* str);

    void setNColumns(int n);
    
    void setButtons(bool enable);
    
    void setFrameStyle(int style) { slider->setFrameStyle(style); }

    void setTracking(bool value) { slider->setTracking(value); }

    void setSubRangeButtons(int v) { slider->setSubRangeButtons(v); }

    void setTicks(const McDArray<float>& t) { slider->setTicks(t); }

    bool isDiscrete() const { return discreteFlag; }

    void setDiscrete(bool value);

    float discretize(const float& value, int subRange=1) const;

    void setTextMaximumWidth(const int maxWidth);

  bool getLeftBPressed(){return m_leftBPressed;}
  bool getRightBPressed(){return m_rightBPressed;}

    void setMenu ( QMenu * menu );
  public slots:
    virtual bool setValue(float v);

    virtual bool setRange(float min, float max);

    virtual bool setSubRange(float min, float max);
   
  signals:
    void sliderPressed();
    void valueChanged(float value);
    void sliderReleased();
    void sliderStateChanged(int state);
    void rightMouseButtonPressed(int x, int y);
    void subRangeChanged(float min, float max);
  protected:
    bool m_leftBPressed;
    bool m_rightBPressed;
    QToolButton* leftB;
    QToolButton* rightB;
    QxSlider* slider;
    QxLineEdit* textF;
    QToolButton* editB;
    QByteArray theFormat;
    QMenu* m_menu;

    float theIncrement;
    short theNColumns;
    short discreteFlag;

    void updateSlider();
    void updateText(float v);
    void createContents();

    virtual void contextMenuEvent ( QContextMenuEvent * event );
  private slots:
    void returnPressed();
    void leftButtonPressed();
    void rightButtonPressed();
    
    void valueChangedSlot(float value);
    void sliderMovedSlot(float value);
    void sliderPressedSlot();
    void sliderReleasedSlot();
    void subRangeChangedSlot(float min, float max);
};

#endif

/// @}
