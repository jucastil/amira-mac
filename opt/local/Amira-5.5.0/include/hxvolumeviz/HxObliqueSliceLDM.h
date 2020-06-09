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
#ifndef HX_OBLIQUE_SLICE_LDM_H
#define HX_OBLIQUE_SLICE_LDM_H

#include <hxcore/HxArbitraryCut.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortDoIt.h>

#include <hxcolor/HxPortColormap.h>
#include <hxcolor/HxColormap256.h>

#include <hxvolumeviz/HxVolumeData.h>
#include <hxvolumeviz/HxMultiChannelMgr.h>
#include <hxvolumeviz/HxPortGPUShader.h>
#include <hxvolumeviz/HxGeometryPriority.h>

#include <hxfield/HxPortMultiChannel.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoLightModel.h>
#include <VolumeViz/nodes/SoObliqueSlice.h>

// @TOBEREVIEWED_ALL

class HxArithLDM;

class HXVOLUMEVIZ_API HxObliqueSliceLDM : public HxArbitraryCut, public HxMultiChannelMgr
{
    MC_HEADER(HxObliqueSliceLDM);

  public:
    /// Constructor
    HxObliqueSliceLDM();

    /// Compute method
    virtual void compute();

    /// Update method.
    virtual void update();

    /// Modes: 0=equal resolution
    HxPortToggleList    portOptions2;
    enum { M_EQUAL_RESOLUTION=0, M_LIGHTING=4,M_COLOR_TABLE=1};

    /// Toggles between nearest and linear interpolation
    HxPortRadioBox      portInterpolation;
    enum { M_NEAREST_INTERP=0, M_LINEAR_INTERP=1, M_MULTISAMPLE_12_INTERP=2};

    HxPortMultiMenu     portMappingType;
    enum {M_LINEAR_MAPPING=0, M_COLORMAP_MAPPING=1} ;

    /// Range is used only if no colormap is present
    HxPortFloatTextN    portLinearRange;

    /// Colormap defines transfer function.
    HxPortColormap      portColormap;

    /// How to use transparency
    HxPortRadioBox portTransparency;
    enum { M_NONE_TRANSPARENCY=0, M_BINARY_TRANSPARENCY=1, M_ALPHA_TRANSPARENCY=2};


    // @TOBEREVIEWED
    /// Enables embossing 
    HxPortToggleList portEmbossing;
    enum { M_EMBOSSING=0 };

    ///
    HxPortFloatTextN portEmbossingFactor;

    /// For switching parts of a multi-channel field on or off.
    HxPortMultiChannel portMultiChannel;

    /// Input port for Pixel Shader.
    HxPortGPUShader portPixelShader;

    void updateEqualRez(bool onOff);

    virtual SoGroup* getScenegraph() {return m_scene;};

  protected:
    virtual ~HxObliqueSliceLDM();

    virtual void addHeadScenegraph();
    virtual void addTailScenegraph();

    enum { M_AXIAL=0, M_CORONAL=1, M_SAGITTAL=2};
    McHandle<SoSeparator>    m_scene;
    McHandle<SoMaterial>     m_material;
    McHandle<SoLightModel>   m_lightModel;
    McHandle<SoObliqueSlice> m_obliqueSlice;
    HxVolumeData*            m_hxVolData;
    HxArithLDM*              m_arithLDM;
    HxGeometryPriority       m_geometryPriority;
};

#endif

/// @}
