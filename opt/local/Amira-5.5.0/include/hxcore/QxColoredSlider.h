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
#ifndef QX_COLORED_SLIDER_H
#define QX_COLORED_SLIDER_H

#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcore/QxFullSlider.h>
#include <mclib/McColor.h>

/** A colored full slider. */

class HXCORE_API QxColoredSlider : public QxFullSlider
{
    Q_OBJECT

  public:
    enum Type {
        Type_unspecified=0,
        Type_R=1,
        Type_G=2,
        Type_B=3,
        Type_H=4,
        Type_S=8,
        Type_V=12,
        Type_Alpha=16
    };
  
    /// Constructor
    QxColoredSlider(QWidget* parent=0, const char *name=0, 
                    Type t=Type_R, bool buttons=1, int nCols=6);
    
    /// Destructor
    ~QxColoredSlider();

    /// Set the type ( = color channel) of the slider.
    bool setType (Type t);
    
    /// Set/unset wysiwyg mode
    bool setWysiwyg (bool onOff=TRUE);
    
    ///
    bool setColorHSV (const float* color); 

  public slots:
    /// Set the color
    bool setColor (const McColor &c, float a=1.f);
  
    /// Set the color
    bool setColor (const float* color); 
    
    /// Set the slider to the specified value
    bool setColorValue (float v); 

  protected:
    McColor theColor;
    float theAlpha;
    float theHsv[3];
    float lastHue;
    Type theType;
    bool wysiwyg;

    void setSliderColors ();

  signals:
    void colorChanged(const McColor &c, float a); 
};

#endif

/// @}
