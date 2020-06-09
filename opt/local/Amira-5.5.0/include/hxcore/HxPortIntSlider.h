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
#ifndef HX_PORT_INT_SLIDER_H
#define HX_PORT_INT_SLIDER_H

#include <hxcore/HxPortFloatSlider.h>

/** Represents a bounded integer number which can be edited
    via a slider. You can also have arrow buttons (setButtons())
    for step-wise editing. Use setIncrement() to set the step width.

    Most of the port's options, e.g. the slider limits and step width,
    can be set interactively via a popup dialog,
    see the  @htmlonly <a href= ../usersguide/HxPortIntSlider.html> usersguide </A> @endhtmlonly
    for a detailed view of the port's GUI. */
class HXCORE_API HxPortIntSlider : public HxPortFloatSlider {
    MC_ABSTRACT_HEADER(HxPortIntSlider);

  public:
    /// Constructor for objects.
    HxPortIntSlider(HxObject *obj, const char *name);

    /// Constructor for editors.
    HxPortIntSlider(HxEditor *editor, const char *name);

    /// Destructor.
    virtual ~HxPortIntSlider();

    /// Returns port's value.
    int	getValue() const;

    /// Returns minimal allowed value, initially set to 0.
    int	getMinValue() const;

    /// Returns maximal allowed value, initially set to 1.
    int	getMaxValue() const;

    /// Set port's value.
    void setValue(int val);

    /// Set slider limits, initially set to 0-1.
    void setMinMax(int min, int max);

    /// Set increment value for arrow buttons, initially set to 1.
    void setIncrement(int increment);

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

protected:
    virtual void createWidget(QWidget* parent);
    virtual void guiCallback();

    inline static int floatToInt(const float& v)
    {
        if (v>0) return (int) (v+0.5);
        else return (int) (v-0.5);
    }
};

#endif

/// @}
