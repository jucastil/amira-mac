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

/// @addtogroup hxvector hxvector
/// @{
#ifndef HX_ICON_H
#define HX_ICON_H

#include <hxcore/HxModule.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxfield/HxVectorField3.h>
#include <hxvector/HxVectorWinDLLApi.h>

class SoNode;
class SoSeparator;
class SoScale;
class SoDragger;
class SoDragPointDragger;

/// This class implements the vector field probe of deLeeuw and van Wijk.
class HXVECTOR_API HxIcon : public HxModule {

  HX_HEADER(HxIcon);

  public:
    /// Constructor.
    HxIcon();

    /// Compute method.
    virtual void compute();

    /// Toggle to display probe dragger.
    HxPortToggleList portDragger;

    /// Buttons to add current probe to buffer and to clear buffer.
    HxPortButtonList portButtons;

    /// Slider to adjust overall size of probe.
    HxPortFloatSlider portScale;

    /// Slider to control arrow length.
    HxPortFloatSlider portLength;

    /// Tcl-command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

  protected:
    virtual ~HxIcon();

    SoDragPointDragger*	dragger;
    SoScale*		scaleNode;
    SoSeparator*	draggerSep;
    SoSeparator*	icons;
    SoSeparator*	current;
    HxVectorField3*	field;
    HxLocation3*	loc;
    float		bbox[6];
    float		delta;
    float		scale;

    float		p[3];
    float		ex[3];
    float		ey[3];
    float		ez[3];
    float		uLen;
    float		J[3][3];

    struct Info {
        float scale;
        SbVec3f pos;
    };

    McDArray<Info> history;

    bool m_is2DVectorField;

    void savePorts(FILE* fp);
    void updateIcon();
    void analyseField();
    void constrainDragger();
    int evalVerify(float J[3][3]);
    int evalField(float u[3], float J[3][3], const float p[3]);
    static void valueChangedCB(void* userData, SoDragger* dragger);
};

#endif

/// @}
