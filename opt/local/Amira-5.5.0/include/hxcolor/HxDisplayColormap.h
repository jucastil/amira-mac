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
#ifndef HX_DISPLAY_COLORMAP_H
#define HX_DISPLAY_COLORMAP_H

#include <Inventor/SbLinear.h>
#include <Inventor/nodes/SoSeparator.h>

#include <mclib/McHandle.h>
#include <mclib/McColor.h>
#include <hxcolor/HxColorWinDLLApi.h>
#include <hxcore/HxModule.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortGeneric.h>

/// Display colormap annotation.

class HxColormap;
class SoTranslation;
class SoTextProperty;
class SoText2;
class SoTexture2;

class HXCOLOR_API HxDisplayColormap : public HxModule {

  HX_HEADER(HxDisplayColormap);

  public:

    /// Constructor.
    HxDisplayColormap();

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Options: 0=custom text, 1=vertical, 2=relative size, 3=transparent bg
    HxPortToggleList portOptions;
    enum { CUSTOMTEXT=0, ORIENTATION=1, RELSIZE=2, TRANSPBG=3 };

    /// X and y position in pixel, negative values relative to right and top.
    HxPortIntTextN portPosition;

    /// Size of rectangle in pixels or relative to 1000x1000 window.
    HxPortFloatTextN portSize;

    /// User text, syntax is "<val>/<text> <val>/<text> ..."
    HxPortText portLabels;

    /// User title
    HxPortText portTitle;

    /// Histogram
    HxConnection portHistogram;

    /// Histogram options
    enum { POSITION_LIST=0 };
    HxPortGeneric portHistogramOptions;

    /// saves settings
    void savePorts(FILE* fp);

    /// Tcl-command interface.
    int parse(Tcl_Interp* t, int argc, char **argv);

  protected:
    virtual ~HxDisplayColormap();

    HxColormap* colormap;
    int width, length;
    int orgx, orgy;
    int pointSize;
    
    enum { HORIZONTAL=0, VERTICAL=1 };
    int orientation;
    McColor textColor;
    McColor bgColor;
    McHandle<SoSeparator> mRootNode;

    SoTranslation* mTitleTrans;
    SoTextProperty* mTitleProperty;
    SoText2* mTitle;
    SoTexture2* mTexture;

    void render(SoGLRenderAction* renderAction);
    void renderText();
    void updateTexture(int width, int height);

    static void renderCallback(void* userData, SoAction* action);
};

#endif

/// @}
