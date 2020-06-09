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
#ifndef HX_PORT_INT_TEXT_N_H
#define HX_PORT_INT_TEXT_N_H

#include <math.h>
#include <hxcore/HxPortFloatTextN.h>

/** This port represents a variable number of bounded integer values which may be
    edited interactively. The actual number of integer fields is set in the
    constructor, its default value is 1. In addition to the port's label ( which is set
    by @c HxPort::setLabel) you can define a label for each integer field
    using the HxPortFloatTextN::setLabel method.
    You also may set the format string, the minimum and maximimum values, as well
    as the sensitivity of each field.
    If a integer field needs not to be show all of the time you can use
    HxPortFloatTextN::setPart to hide or show it.
*/
class HXCORE_API HxPortIntTextN : public HxPortFloatTextN {

  MC_ABSTRACT_HEADER(HxPortIntTextN);

  public:
    /// Actual number of values is defined in constructor.
    HxPortIntTextN(HxObject *obj, const char *name, int n=1);

    /// Actual number of values is defined in constructor.
    HxPortIntTextN(HxEditor *editor, const char *name, int n=1);
    
    /// Destructor.
    virtual ~HxPortIntTextN();

    /// Returns @c nth integer value.
    int	getValue(int n=0) const;

    /// Returns lower bound of @c nth value.
    int	getMinValue(int n=0) const;

    /// Returns upper bound of @c nth value.
    int	getMaxValue(int n=0) const;

    /// Sets @c nth value.
    void setValue(int n, int v) {
        HxPortFloatTextN::setValue(n,(float)v);
    }

    /// Set value of first integer.
    void setValue(int v) { setValue(0,v); }

    /// Sets bounds of @c nth value.
    void setMinMax(int n, int min, int max) {
        HxPortFloatTextN::setMinMax(n, (float)min, (float)max);
    }

    /// Sets bounds of all parts.
    void setMinMax(int min, int max);

    /// Tcl-command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);


protected: 
    
    /// To cast a float value into an int one without overflow.
    static int getIntCastValue(float floatValue);

};

#endif

/// @}
