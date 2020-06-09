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
#ifndef QX_FULL_RANGE_SLIDER_H
#define QX_FULL_RANGE_SLIDER_H

#include <QWidget>

#include "HxAmiraWinDLLApi.h"

#include <mclib/McDArray.h>

#include "QxRangeSlider.h"

class QValidator;

class QxLineEdit;

class McHistogram;

/** A range slider @see QxRangeSlider with an additional minimum and 
    maximum text field @see QxLineEdit left and right next to the slider. 
*/
class HXCORE_API QxFullRangeSliderBase : public QWidget
{
    Q_OBJECT

    public:
        /// DTOR
        virtual ~QxFullRangeSliderBase();

        /** Set min, max adjustable data range.

            @param vmin Minimum adjsutable data value
            @param vmax Maximum adjsutable data value

            Note that by default vmin = -FLT_MAX and vmax = FLT_MAX.
        */
        void setDataRange(float vmin, float vmax);

       /** Set slider widget displayable range.

            Depending on the data range @see setDataRange() the left most displayable slider
            position will always be <= vmin and the right most displayable slider position
            will always be >= vmax.
        */
        void setDisplayRange(float vmin, float vmax);

        /** Convenience function to set the slider displayable range to min, max @see setDisplayRange
            and additionaly sets the adjustable data values according to an expand factor.

            The minimum adjustable value accepted by the widget is defined as 
            vmin -(vmax-vmin) * expandFactor and the maximum adjustable value 
            is defined as vmax + (vmax-vmin) * expandFactor.

            Accordingly the left most displayable slider position will always be 
            >= vmin -(vmax-vmin) * expandFactor and <= vmin and the 
            right most displayable slider position will always be <= vmax + (vmax-vmin)
            and >= vmax.

            Where the left most reachable slider position will never be greater vmin
            and the right most reachable slider position will never be less than vmax.

            @param expandFactor Factor to expand the adjustable data range
        */
        void setDisplayRange(float vmin, float vmax, float expandFactor);

        /** Convenience function to set the min, max adjustable data values and
            the slider displayable range.

            Meaning that the min, max adjustable values accepted by the widget
            are vmin and vmax and also the left most displayable slider position
            is always vmin and the right most displayable slider position is always vmax.

            In most cases this is what you might expect from a range slider.
        */
        void setRange(float vmin, float vmax);

         /** Returns the minimum allowed value of the slider */
        float minValue() const;

        /** Returns the maximum allowed value of the slider */
        float maxValue() const;

        /** Set slider's minimum, maximum value.
            @param vmin
            @param vmax
        */
        void setValue(float vmin, float vmax);

        /** Get minimum, maximum slider value.
            @param idx 0 = minimum value 
                       1 = maximum value
            @return minimum, maximum slider value 
        */  
        float value(int idx);

        /** Set slider's histogram.
        */
        void setHistogram(const McHistogram& histogram);

        /** Enables or disables slider tracking. If tracking is enabled (default),
        the slider emits the valueChanged() signal whenever the slider
        changes. If tracking is disabled, the slider emits the
        valueChanged() signal when the user releases the mouse button
        (unless the value happens to be the same as before). */
        void setTracking(bool inFlag = true);

        ///
        bool isTracking();

        /// Enables or disables discrete slider values (default is not discrete).
        void setDiscrete(bool inFlag = true);

        ///
        bool isDiscrete() const;

        /// Changes the preferred width in columns (base is letter 'A').
        void setNumColumns(int numColumns);
        int getNumColumns() const;

        /** Change the slider widget's minimum size.
            Together with the absolut minimum and maximum text field width @see setNumColumns,
            setting the minimum width of the slider widget influences the overall minimum width
            of this widget.
        */
        void setSliderMinimumWidth(int) const;

        /** Sets a marker line */
        void setMarker(float value);

        /** Unsets a marker line previously set via setMarker(). */
        void clearMarker();

        void enableMinMaxTextEdit(bool state);

        bool isMinMaxTextEditEnabled() const;

        void showTextItalic(bool state);

        bool isTextItalic() const;

        void setInvertible(bool state);
        bool isInvertable() const;

    signals:

        void valueChanged(float, float);
        void sliderDoubleClick(int);
        void sliderRightClick(int, int);

    private slots:

        void slotMinTextChanged(const QString &text);
        void slotMaxTextChanged(const QString &text);
        void slotSliderValueChanged(float, float);
        void slotSliderMoved(float,float);
        void slotEditingMinFinished();
        void slotEditingMaxFinished();

    protected:
        /// CTOR
        QxFullRangeSliderBase(QWidget* parent);

        QxRangeSlider* mSlider;

        /// initialize and create the widget
        void createWidget();
 private:        

        void setText(float vmin, float vmax);

        QxLineEdit*    mMinText;
        QxLineEdit*    mMaxText;
    
        QValidator*    mValidator;
        bool           mDiscreteFlag;

        int            mDecimals;

        bool           mTracking;

        bool           mInvertible;

};

class HXCORE_API QxFullRangeSlider : public QxFullRangeSliderBase
{
    Q_OBJECT

    public:
        /// CTOR
        QxFullRangeSlider(QWidget* parent) : QxFullRangeSliderBase(parent) {
            mSlider = new QxRangeSlider(this);
            createWidget();
        }

        /// DTOR
        ~QxFullRangeSlider() {}
};

#endif

/// @}
