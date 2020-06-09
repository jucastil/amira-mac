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
#ifndef HX_ANNOTATION_TOOL_H
#define HX_ANNOTATION_TOOL_H

#include <hxcore/HxAmiraWinDLLApi.h>

#include <mclib/McHandle.h>
#include <mclib/McColor.h>
#include <hxcore/HxModule.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortTextUTF8.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortColorList.h>
#include <hxcore/HxPortFontSelection.h>
#include <hxcore/HxPortGeneric.h>
#include <hxcore/HxPortMultiMenu.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoFont.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoText2.h>
#include <Inventor/nodes/SoQuadMesh.h>
#include <Inventor/nodes/SoVertexProperty.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoCallback.h>

/// Display custom text in viewer window.

class HXCORE_API HxAnnotationTool {

  public:
    /// Constructor with as argument the display module which will use this annotation tool.
    HxAnnotationTool(HxModule *module);

    /// Destructor
    virtual ~HxAnnotationTool();

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// The background options.
    HxPortGeneric portBackground;
    enum { BACKGROUND_TRANSPARENT_CB, BACKGROUND_COLOR_BTN, BACKGROUND_COLOR_LABEL };

    /// Switch between position handling (NDC or absolute).
    HxPortRadioBox portPosType;

    /// Define origin: upper/lower + right/left
    HxPortMultiMenu portOrigin;
    enum { LOWER_LEFT, UPPER_LEFT, LOWER_RIGHT, UPPER_RIGHT};

    /// X and y position in pixel, negative values relative to right and top.
    HxPortIntTextN portPosition;

    /// X and y position in normalised coordinates.
    HxPortFloatTextN portNdcPosition;

    /// Custom text.
    HxPortTextUTF8 portText;

    /// To select the current font.
    HxPortFontSelection portFont;

    /// Tcl-command interface.
    int parse(Tcl_Interp* t, int argc, char **argv);

    /// Size of text used for the annotation (default=14).
    int pointSize;

    /// The position types.
    enum PositionType { ABSOLUTE_POSITION = 0, RELATIVE_POSITION = 1 };

    /// 
    bool hasTransparentBackground();

    /// Computes the text width and height in pixels and stores it in m_textSize.
    void updateTextSize();

    void setDisplayModule(HxModule* displayModule);

    McHandle<SoText2> m_text;

  protected:
    McHandle<SoSeparator> m_textSeparator;
    McHandle<SoCallback> m_callback;
    McHandle<SoOrthographicCamera> m_textCamera;
    McHandle<SoTranslation> m_textTranslation;
    McHandle<SoSwitch> m_textBackgroundSwitch;
    McHandle<SoMaterial> m_textBackgroundMaterial;
    McHandle<SoVertexProperty> m_textBackgroundVP;
    McHandle<SoQuadMesh> m_textBackgroundQM;
    McHandle<SoFont> m_textFont;
    McHandle<SoMaterial> m_textMaterial;
    SbVec2s m_textSize; 
    HxModule *m_module;   // Should not be a McHandle otherwise all display modules inhering from this 
                          // class will not be deleted.
    
    HxModule* m_displayModule;

    /// To update the font.
    void updateFont();

    /// Used to update the absolute translation and/or the quad mesh coordinates.
    void updateGeometry(const SbViewportRegion& viewportRegion);

    /// Static method associated to the m_callback node.
    static void renderCallback(void* userData, SoAction* action);

    void getScreenCoordinate(const SbVec2s& windowSize, float& xTrans, float& yTrans);

    void getPositionInWindow(const SbVec2s& windowSize, float& xTrans, float& yTrans);

    void getObjectsScreenSize(const SbVec2s& windowSize, SbVec2s& objectBBSize, SbVec2s& objectBBLLCorner);

    bool hasPositionReference();

    void getObjectBoundingBox(float* bb);

    void getProjectedBB(SbVec2s& objectBBSize, SbVec2s& objectBBLLCorner);

    SbVec3f mapWorldToScreen(const SbVec3f& world);

    int determineWhichCorner( const bool xPositive, const bool yPositive );

};

#endif

/// @}
