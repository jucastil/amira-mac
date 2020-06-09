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

/// @addtogroup hxvolumeviz hxvolumeviz
/// @{
#ifndef HX_VOLUME_RENDER_H
#define HX_VOLUME_RENDER_H

#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortGeneric.h>

#include <hxcore/HxDisplay.h>
#include <hxvolumeviz/HxVolumeRender.h>

#include <hxcolor/HxPortColormap.h>

#include <hxvolumeviz/HxMultiVolumeBase.h>
#include <hxvolumeviz/HxVolumeData.h>
#include <hxvolumeviz/HxPortGPUShader.h>
#include <hxvolumeviz/SoMovingComplexity.h>
#include <hxvolumeviz/HxGeometryPriority.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoMaterial.h>
#include <VolumeViz/nodes/SoVolumeRender.h>
#include <VolumeViz/nodes/SoVolumeSkin.h>
#include <VolumeViz/nodes/SoVolumeRenderingQuality.h>

#include <hxfield/HxPortMultiChannel.h>

// @TOBEREVIEWED_ALL

class HXVOLUMEVIZ_API HxVolumeRender : public HxMultiVolumeBase
{
    MC_HEADER(HxVolumeRender);

  public:
    /// Constructor
    HxVolumeRender();

    /// Update method.
    virtual void update();

    /// Compute method
    virtual void compute();

    /// Input port for region of interest.
    HxConnection        portROI;

    /// Render style: 0=volume rendering, 1=volume skin
    HxPortRadioBox      portRenderStyle;
    enum { M_VOLUME_RENDERING=0, M_VOLUME_SKIN=1};

    /// Modes: 0=lowres, 1=subtile+early-z
    HxPortToggleList    portPerformances;
    enum { PERFORMANCES_MOVE_LOW_RES = 0, PERFORMANCES_OPTIMIZATIONS_ALL = 1 };

    /// Modes: 0=lighting, 1=aligned slices, 2=color table
    HxPortToggleList    portRendering;
    enum { M_ILLUMINATION=0, M_ALIGNED_SLICES=1, M_COLOR_TABLE=2, M_HI_QUALITY=3 };

    HxPortToggleList    portRendering2;
    enum { M_JITTERING=0, M_EDGE_2D=1 };

    /// Composition mode: 0=alpha, 1=sum, 2=min, 3=max
    HxPortRadioBox      portComposition;
    enum { M_ALPHA_COMPOSITION=0, M_SUM_COMPOSITION=1, M_MAX_COMPOSITION=2, M_MIN_COMPOSITION=3 };

    /// Toggles between nearest and linear interpolation
    HxPortRadioBox      portInterpolation;
    enum { M_NEAREST_INTERP=0, M_LINEAR_INTERP=1, M_CUBIC_INTERP=2 };

    /// Range is used only if no colormap is present
    HxPortFloatTextN    portRange;

    /// Texture lookup mode: 0=alpha, 1=luminance-alpha, 2=rgba
    HxPortRadioBox      portLookup;
    enum { M_ALPHA=0, M_LUMINANCE_ALPHA=1, M_RGBA=2 };

    /// Colormap defines transfer function.
    HxPortColormap      portColormap;

    /// Gamma scale for multi-channel data
    HxPortFloatSlider   portGamma;

    /// Tile Refinment (used for projection) hidden by default
    HxPortIntSlider   portTileRefinement;

    /// Overall alpha scale factor (alpha value of slices)
    HxPortFloatSlider   portAlphaScale;

    /// Toggles between 2D and 3D mode.
    HxPortRadioBox      port2D3D;
    enum { M_TEXTURE2D=0, M_TEXTURE3D=1};

    /// Number of slices to be used in 3D mode.
    HxPortIntSlider     portSlices;

    /// For switching parts of a multi-channel field on or off.
    HxPortMultiChannel  portMultiChannel;

    /// Input port for Pixel Shader.
    HxPortGPUShader portPixelShader;

    HxPortToggleList portIllumination;
    enum {ILLUMINATION_LIGHTING = 0, ILLUMINATION_EDGE_ENHANCEMENT = 1, ILLUMINATION_BOUNDARY_OPACITY = 2};

    HxPortGeneric portIlluminationOptions;
    enum {ILLUMINATION_OPT_QUALITY = 0, ILLUMINATION_OPT_BRIGHT = 1};
    enum {GRADIENT_QUALITY_LOW, GRADIENT_QUALITY_MEDIUM, GRADIENT_QUALITY_HIGH};


    // Edge coloring.
    HxPortGeneric portEdgeColoring;
    enum { EDGE_COLORING_LABEL = 0, EDGE_COLORING_THRESHOLD = 1 };

    // Boundary opacity enhancement.
    HxPortGeneric portBoundaryOpacity;
    enum { BOUNDARY_OPACITY_INTENSITY_LABEL = 0, BOUNDARY_OPACITY_INTENSITY = 1,
           BOUNDARY_OPACITY_THRESHOLD_LABEL = 2, BOUNDARY_OPACITY_THRESHOLD = 3 };

    // 2D Edge detection
    HxPortGeneric portEdgeDetect2D;
    enum { EDGE_DETECT_INNER_LABEL = 0,
           EDGE_DETECT_INNER_THRESHOLD     = 1,
           EDGE_DETECT_OUTER_LABEL = 2,
           EDGE_DETECT_OUTER_THRESHOLD     = 3 };

    /// Parse the interpreter commandline and execute commands
    int parse(Tcl_Interp* t, int argc, char **argv);

    virtual SoGroup* getScenegraph() {return m_scene;};

  protected:
    virtual ~HxVolumeRender();

    //handle projection activation
    virtual void projectionActivated();

    McHandle<SoSeparator>               m_scene;
    McHandle<SoSwitch>                  m_volumeSwitch;
    McHandle<SoVolumeSkin>              m_volumeSkin;
    McHandle<SoVolumeRender>            m_volumeRender;
    McHandle<SoMaterial>                m_material;
    McHandle<SoSwitch>                  m_renderingQualitySwitch;
    McHandle<SoVolumeRenderingQuality>  m_renderingQuality;

    bool m_forceHighQuality;

    virtual void addHeadScenegraph();
    virtual void addTailScenegraph();

    virtual void enableVolumeShaderPorts(bool state);
    virtual void showVolumeRenderingPorts(bool doShow);
    virtual void showIlluminationPorts();
    virtual void enableLighting(bool state);
    virtual int avizo5Compatibility(Tcl_Interp* t, int argc, char **argv);

    //Import HxMultiChannelMgr method required because of next method definition with the same name
    using HxMultiChannelMgr::updateDataRange;

    virtual void updateDataRange();

    virtual void updateVolumeVizProperties();

  private:
    bool m_doVolumeRender;
    bool m_doColorTable;
    bool m_doMultiChannel;

    HxGeometryPriority m_geometryPriority;
};

#endif

/// @}
