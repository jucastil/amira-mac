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

/// @addtogroup hxcolor hxcolor
/// @{
#ifndef QX_COLORMAP_FULL_RANGE_SLIDER_H
#define QX_COLORMAP_FULL_RANGE_SLIDER_H

#include "HxColorWinDLLApi.h"

#include <hxcore/QxFullRangeSlider.h>

#include <mclib/McColor.h>

class HxColormap;

class HXCOLOR_API QxColormapFullRangeSlider : public QxFullRangeSliderBase
{
    Q_OBJECT

    public:
        /// CTOR
        QxColormapFullRangeSlider(QWidget* parent);

        /// DTOR
        virtual ~QxColormapFullRangeSlider(){};

        /// Set colormap 
        /// @param colormap if colormap is NULL a default gray ramp
        ///                 is used.
        void setColormap(HxColormap* colormap);

        /// Return colormap.
        HxColormap* getColormap() const;

        /// Set constant color @see showConstantColor().
        void setConstantColor(const McColor& constantColor);

        /// Return current constant color.
        const McColor& getConstantColor() const;

        /// Set constant color alpha @see showConstantColor().
        void setConstantColorAlpha(float constantColorAlpha);

        /// Return current constant color alpha.
        float getConstantColorAlpha() const;

        /// If true checkerboard pattern is draw for constant color 
        /// and colormaps with transparency
        void showAlpha(bool showAlpha);

        ///
        bool isAlphaEnabled() const;

        /// Show the current constant color instead of a colormap
        void showConstantColor(bool showConstantColor);

        ///
        bool isConstantColorEnabled() const;

        /** Convenicence function in order to show a constant colorbar

            If showConstantColorbar is true the slider handles and the histogram are hidden.
            Furthermore if constant color @see showConstantColor() is turned off the colormap
            is mapped between the left most and right most slider widget position instead
            between min and max slider handles.
        */
        void showConstantColorbar(bool showConstantColorbar);

        ///
        bool isConstantColorbarEnabled() const { return mIsConstantColorbar; }

        /// Show a progress @see setProgressValue at the bottom of the widget
        void showProgress(bool showProgress);

        ///
        bool isProgressEnabled() const;

        /** Set the progress value of the progressbar @see showProgress

            @param percentDone 0.f corresponds with the left most widget
                   position and 1.f with right most.
        */
        void setProgressValue(float percentDone);

        ///
        void zoomViewAll();

        /// 
        void zoomHistogram();

private:
        bool mIsConstantColorbar;
};

#endif

/// @}
