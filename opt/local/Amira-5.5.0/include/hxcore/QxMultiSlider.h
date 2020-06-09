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
#ifndef QX_MULTIPLE_SLIDER_H
#define QX_MULTIPLE_SLIDER_H

#include <hxcore/HxAmiraWinDLLApi.h>

#include <QFrame>
#include <QVector>

#pragma warning(push)

// 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
#pragma warning(disable:4251)

class HXCORE_API QxMultiSlider : public QFrame
{
    Q_OBJECT
public:
    QxMultiSlider(QWidget * parent, const char * name = 0);
    QxMultiSlider(float minValue, float maxValue, QWidget * parent, const char * name = 0);
    virtual ~QxMultiSlider();

    /// If true, left click on the slider add an handle.
    void setAutoAdd(bool enabled){ m_autoAdd = enabled; }

    /// If true, right click on an handle remove it.
    void setAutoDel(bool enabled){ m_autoDel = enabled; }

    /// Returns the current minimum value of the slider.
    float getMinValue () const{ return m_minValue; }

    /// Returns the current maximum value of the slider.
    float getMaxValue () const{ return m_maxValue; }

    /// Sets the current minimum value of the slider.
    void setMinValue( float );

    /// Sets the current maximum value of the slider.
    void setMaxValue( float );

    /// Add a new slider handle at the specified value.
    virtual int addSlider(float value);

    /// Remove the specified slider handle.
    virtual void removeSlider(int slider);

    /// Returns the slider currently under the mouse cursor.
    virtual int sliderUnderCursor(int x, int y) const;

    /// Return current selected slider.
    int currentSlider() const{ return m_currSlider; }

    virtual void setCurrentSlider(int slider);

    /// Sets the specified slider value.
    virtual void setValue(int slider, float value);

    /// Returns the specified slider value.
    float getValue(int slider) const{ return m_sliderVal[slider]; }

    /// Returns the number of slider.
    int numSlider() const { return (int)m_sliderVal.size(); }

    /// Sets whether slider tracking is enabled to enable.
    void setTracking( bool enable ){ m_track = enable; }

    /// Returns true if slider tracking is enabled
    bool tracking() const { return m_track; }

    /// Returns the specified slider handle rectangle.
    virtual QRect sliderRect(int slider) const;

    /// Map device context to slider value.
    virtual float mapDcToValue(int dc) const;

    /// Map slider value to device context.
    virtual int mapValueToDc(float value) const;

    /// Remove all slider handles.
    virtual void clear();
signals:
    /// This signal is emitted when the slider value is changed. 
    void valueChanged();

    /// This signal is emitted when the user presses the slider with the mouse. 
    void sliderPressed(int slider);
    
    void sliderAdded(int slider);

    /// This signal is emitted when the slider is dragged, with the slider index as its argument.
    void sliderMoved(int slider);

    void sliderRemoved(int slider);

protected:
    virtual QSize sliderSize(int slider) const;
    virtual void paintEvent ( QPaintEvent *);
    virtual void mousePressEvent( QMouseEvent * );
    virtual void mouseReleaseEvent( QMouseEvent * );
    virtual void mouseMoveEvent( QMouseEvent * );
    virtual void drawHandle(QPainter * p, const QRect & rect, int slider, bool selected);
private:
    void init(float minv = 0.0f, float maxv = 100.0f);

    float m_minValue;
    float m_maxValue;
    int   m_currSlider;
    bool  m_dragSlider;
    bool  m_track;
    bool  m_autoAdd;
    bool  m_autoDel;

    QVector<float> m_sliderVal;
};

#pragma warning(pop)

#endif

/// @}
