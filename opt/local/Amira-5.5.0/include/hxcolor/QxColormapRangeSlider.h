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
#ifndef QX_COLORMAP_RANGE_SLIDER_H
#define QX_COLORMAP_RANGE_SLIDER_H

#include <hxcore/QxRangeSlider.h>

#include <hxcolor/HxColormap.h>
#include <hxcolor/HxColorWinDLLApi.h>

#include <mclib/McHandle.h>

class HXCOLOR_API QxColormapRangeSlider : public QxRangeSlider
{
    Q_OBJECT
public:

    enum ColorMappingType {
        MINMAX         = 0,
        DISPLAY_CLIP   = 1,
    };

    QxColormapRangeSlider(QWidget* parent=NULL, const char* name=NULL);

    ///
    void setColormap(HxColormap* colormap);

    ///
    HxColormap* getColormap() const { return mColormap; }

    ///
    void setConstantColor(const McColor& constantColor);

    ///
    const McColor& getConstantColor() const { return mConstantColor; }

    ///
    void setConstantColorAlpha(float alpha);

    ///
    float getConstantColorAlpha() const { return mAlpha; }

    ///
    void showAlpha(bool showAlpha);

    ///
    bool isAlphaEnabled() const { return mAlphaEnabled; }

    ///
    void showConstantColor(bool showConstantColor);

    ///
    bool isConstantColorEnabled() const { return mConstantColorEnabled; }

    ///
    void setColorMapping(ColorMappingType mappingType);

    ///
    bool getColorMapping() const { return mMappingType; }

    ///
    void showProgress(bool show);

    ///
    bool isProgressEnabled() const { return mProgressEnabled; }

    ///
    void setProgressValue(float percentDone);
    
protected:
    virtual void paintBackground(QPainter& painter, const QRect & rect);

private:
    McHandle<HxColormap> mColormap;

    McColor mConstantColor;
    float   mAlpha;
    bool    mConstantColorEnabled;
    bool    mAlphaEnabled;
    int     mMappingType;
    bool    mProgressEnabled;
    float   mProgressValue;
};

#endif

/// @}
