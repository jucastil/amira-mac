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

/// @addtogroup hxtime hxtime
/// @{
#ifndef HX_DISPLAY_VALUE_H
#define HX_DISPLAY_VALUE_H

#include <mclib/McHandle.h>
#include <mclib/McString.h>
#include <hxcore/HxModule.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortColorList.h>
#include <Inventor/SbLinear.h>
#include <Inventor/nodes/SoCallback.h>

#include <hxtime/HxTimeWinDLLApi.h>

const float twoPI = 6.283185;
const int NUMCIRC = 90;

/// Display time annotation.
class HXTIME_API HxDisplayValue : public HxModule {

  HX_HEADER(HxDisplayValue);

  public:

    /// Constructor.
    HxDisplayValue();

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Options: 0=display only text, 1=clock, 2=horizontal, 3=vertical
    HxPortRadioBox portOptions;

    /// Options: 0=frame, 1=fill, 2=value text, 3=filled value. 4=custom text
    HxPortToggleList portOptions2;

    /// The value
    HxPortFloatTextN portValue;

    /// X and y position in pixel, negative values relative to right and top.
    HxPortIntTextN portPosition;

    /// Size of rectangle in pixels or relative to 1000x1000 window.
    HxPortFloatTextN portSize;

    /// Colour for the objects
    HxPortColorList portColor;

    /// User text, syntax is "<val>/<text> <val>/<text> ..."
    HxPortText portLabels;

    /// Format for printing the value
    HxPortText portValueFormat;
	
	/// saves settings
    void savePorts(FILE* fp);

    /// Tcl-command interface.
    int parse(Tcl_Interp* t, int argc, char **argv);

  protected:
	 
    HxDisplayValue(const McTypeInfo *dataType);
    virtual ~HxDisplayValue();

	// Common constructor
	void commonInitConstructor();

    int width, length, radius;
    float minv, maxv;
    float	theValue;
    McString	theStringValue;
    int ival, ivalCirc;
    int orgx, orgy;
    int pointSize;
    McString minMaxFormat;
    bool useAnimationMinMax;

    enum { FRAME=0, FILL=1, VALUETEXT=2, FILLEDVALUE=3, CUSTOMTEXT=4 };
    enum { ONLYTEXT=0, CLOCK=1, HORIZONTAL=2, VERTICAL=3 };

    int renderOption;
    McHandle<SoCallback> callback;

    void render(SoGLRenderAction* renderAction);
    void renderText();
    virtual void buildValueText();

    static void renderCallback(void* userData, SoAction* action);

  private:

    float xcirc[NUMCIRC];
    float ycirc[NUMCIRC];
    int wasTextOnly;
};

#endif

/// @}
