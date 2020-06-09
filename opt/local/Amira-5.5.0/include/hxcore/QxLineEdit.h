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
#ifndef  QX_LINEEDIT_H
#define  QX_LINEEDIT_H

#include <qlineedit.h>
#include <hxcore/HxAmiraWinDLLApi.h>

/** This is a QLineEdit widget with some additional features.

    The class emits the signal inputReady() when the return key is
    pressed, or when text was being edited and then the input focus is lost,
    for example, because the user clicked onto some other widget. This is
    quite useful because in general it is not possible to update e.g. an Amira
    module after every keystroke, but on the other hand one does not want to
    force the user to hit return once he finished text input.

    The class also provides a so-called virtual slider. If the widget's text
    represents a valid integer or floating-point number the user can shift-click
    into the widget and then change the value by moving the mouse in upward or
    downward direction while keeping the left-mouse button pressed.

    The class also provides a new method setNumColumns(), allowing to change
    the preferred width of the widget. This is often more convenient than
    specifying a fixed width or using more complex layout techniques. */
class HXCORE_API QxLineEdit : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(int numColumn READ numColumns WRITE setNumColumns)
  public:
    /// Constructor.
    QxLineEdit(QWidget* parent=NULL, const char *name=NULL);

    /// Destructor.
    ~QxLineEdit();

    /// Returns the preferred size of the widget.
    virtual QSize sizeHint() const;
    virtual QSize minimumSizeHint() const;

    /// Changes the preferred width in pixels.
    void setWidth(int width);

    /// Changes the preferred width in columns (base is letter 'A').
    void setNumColumns(int numColumns);

    /// Return the number of columns.
    int numColumns() const { return mNumColumns; }

    /** Overload method, does nothing if newVal is equal to old text. The original
        method deselects any selected text, although it does not emit a
        textChanged() signal if the text didn't change. */
    virtual void setText(const QString& newVal);

    /// fix the step use with virtual slider to a constant value. Use -1 to let the heuristic change the step dynamicaly.
    void setVirtualSliderStep(float value=-1);

    /**
     * To set the virtual slider mode.
     */
    void setVirtualSliderMode(short mode);

    /**
     * To set the virtual slider position.
     */
    void setVirtualSliderPos(short x, short y);

    /**
     * To set the virtual slider value.
     */
    void setVirtualSliderValue(float value);

    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void wheelEvent(QWheelEvent*);
    
    /**
     *  Enables or disables virtual slider tracking. If tracking is enabled (default),
     *  the virtual slider emits the inputReady() signal whenever the slider value
     *  changes. If tracking is disabled, the slider only emits the inputReady() 
     *  signal when the user releases the mouse button.
     */
    void setTracking(bool inFlag = true) { mTracking = inFlag; }

    ///
    bool isTracking() { return mTracking; }

  signals:
    /** Emitted when return is pressed or focus is lost. In Amira this
        signal is used in all ports to trigger computations. */
    void inputReady();
    /// Emitted whenever the value is changed by virtual slider.
    void virtualSliderChange(const QString &newval);
  protected slots:
    void firePendingChanges();
  protected:
    void virtSliderChange(float delta, int isFloat);

    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);

    int mNumColumns;
    unsigned short preferredWidth;
    short virtualSliderMode, virtualSliderPos[2];
    float virtualSliderValue, virtualSliderStep;
  
  private:
    bool mTracking;
    QString lastValueSent;
    int mWheelDelta;

};

// ------------------------------ INLINE methods. ------------------------------
inline void
QxLineEdit::setVirtualSliderMode(short mode)
{
  virtualSliderMode = mode;
}

inline void
QxLineEdit::setVirtualSliderPos(short x, short y)
{
  virtualSliderPos[0] = x;
  virtualSliderPos[1] = y;
}

inline void
QxLineEdit::setVirtualSliderValue(float value)
{
  virtualSliderValue = value;
}


#endif

/// @}
