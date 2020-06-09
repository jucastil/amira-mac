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

/// @addtogroup hxmeasure hxmeasure
/// @{
#ifndef HX_SCALE_H 
#define HX_SCALE_H 

#include "HxMeasureWinDLLApi.h"

#include <hxcore/HxModule.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortColorList.h>
#include <hxcore/HxPortTextUTF8.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortGeneric.h>
#include <hxcore/HxPortFontSelection.h>
#include <mclib/McHandle.h>
#include <Inventor/nodes/SoText2.h>
#include <Inventor/nodes/SoAnnotation.h>
#include <Inventor/nodes/SoTextProperty.h>

class SbViewportRegion;
class SoGLRenderAction; 
class SoState;
class SoFont;
class SoMaterial;
class SoDrawStyle;
class SoIndexedLineSet;
class SoVertexProperty;
class SoSeparator;

/** The Module displays a 2D coordinate System on top of the rendering area.
    The coordinate a calculated on a plane perpendicular to the viewing 
    direction located a the focal distance of the camera. The focal distance 
    is the point about which rotations are preformed.
    In orthogonal projections the displayed distances are valid for all parts
    of the picture, in perspective projection only for the mentioned plane.
    The location and size of the coordinate system can be controlled by 
    the ports. The module scales things to get `nice' numbers (no fractionals).
*/
class HXMEASURE_API HxScale : public HxModule
{
    HX_HEADER(HxScale);

  public:
    /// Constructor.
    HxScale();

    /// Overloaded update() method.
    virtual void update();

    /// Overloaded compute() method.
    virtual void compute();

    /// Overloaded parse() method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Position of the Origin (fraction of viewport size).
    HxPortFloatSlider portPosX;

    /// Position of the Origin (fraction of viewport size).
    HxPortFloatSlider portPosY;

    /// Maximal size of the displayed coordinate system. 
    HxPortFloatSlider portSizeX;

    /// Maximal size of the displayed coordinate system. 
    HxPortFloatSlider portSizeY;

    /// Show x-axis, y-axis, border. 
    HxPortToggleList portFrame;

    /// Show ticks, grid, text.
    HxPortToggleList portTicks;

    /// Show subticks, grid
    HxPortToggleList portSubTicks;

    /// Units text, e.g. mm or cm.
    HxPortTextUTF8 portUnit;

    /// Grid color.
    HxPortColorList portColor;

    /// Line width of axes and tick marks.
    HxPortFloatTextN portLineWidth;

    HxPortFontSelection portFont;

    /// Options
    HxPortGeneric portOptions;

    //Multiplicative value factors
    HxPortFloatSlider portXFactor;
    HxPortFloatSlider portYFactor;

  protected:

    enum PortFrameValues {PORTFRAME_SHOW_X_AXIS=0,
                          PORTFRAME_SHOW_Y_AXIS=1,
                          PORTFRAME_SHOW_BORDER=2};

    enum PortTicksValues {PORTTICKS_SHOW=0,
                          PORTTICKS_SHOW_GRID=1,
                          PORTTICKS_SHOW_TEXT=2};

    enum PortSubTicksValues {PORTSUBTICKS_SHOW=0,
                             PORTSUBTICKS_SHOW_GRID=1};

    // The destructor should be hidden.
    virtual ~HxScale();

    /// Save additional port information
    void savePorts (FILE* fp);

    /// Render method.
    void render(SoGLRenderAction* renderAction);

    /// Static render callback to be called from outside.
    static void renderCallback(void* userData, SoAction* action);

    /// Caculates the size at focal distance (spaceDim).
    SbVec2f calcSpaceDim (SoState* state, const SbViewportRegion& viewport);

    /// Pixel-size criterion to accept or reject a tick interval
    static bool isTickIntervalOK(  float tickIntervalInWorldUnit, float pixelsPerWorldUnit, float minTickIntervalInPixels );

    /// Calculate the most appropriate tick interval for the viewport 
    static float calcTickInterval( float tickIntervalInWorldUnit, float pixelsPerWorldUnit, int minTickIntervalInPixels );

    void computeAxisLengthAndNumberOfTicks();

    void updateAxes();

    void updateFont();

    void updateLineProperties();

    void updateText();

    SbString getUnitString();
    SbString getFormattedUnitString();

    void drawAxes(McDArray<SbVec3f>& points, McDArray<int32_t>& lines);
    void drawEndTicksX(McDArray<SbVec3f>& points, McDArray<int32_t>& lines);
    void drawEndTicksY(McDArray<SbVec3f>& points, McDArray<int32_t>& lines);
    void drawIntermediateTicksAndSubTicksX(McDArray<SbVec3f>& points, McDArray<int32_t>& lines);
    void drawIntermediateTicksAndSubTicksY(McDArray<SbVec3f>& points, McDArray<int32_t>& lines);
    void drawUnitTextAtEndOfXAxis();
    void drawUnitTextAtEndOfYAxis();

    void addText(SoSeparator* parentNode,
                 const SbVec2f& positionScreenCoords,
                 const SbString text,
                 const SoText2::Justification alignH,
                 const SoTextProperty::AlignmentV alignV);

    const float VerticalTextOffset;
    const float HorizontalTextOffset;

    McString mTextFormat;

    /// Size of viewport at focal distance.
    SbVec2f mSpaceDim;

    SbVec2f mAxisLengthWorld;
    SbVec2f mAxisLengthScreen;
    SbVec2f mOriginScreen;

    SbVec2s mWindowSize;

    McVec2i mNumberOfTicks;
    McVec2i mNumberOfSubTicks;
    float mTickSize;
    float mSubTickSize;

    McHandle<SoAnnotation> mRootNode;

    SoMaterial* mAxisMaterial;
    SoDrawStyle* mAxisDrawStyle;
    SoIndexedLineSet* mAxisLineSet;
    SoVertexProperty* mAxisVertexProperty;

    SoFont* mFont;
    SoMaterial* mTextMaterial;

    SoSeparator* mUnitTextXSep;
    SoSeparator* mUnitTextYSep;

    SoSeparator* mNumberTextXSep;
    SoSeparator* mNumberTextYSep;
};

#endif 


/// @}
