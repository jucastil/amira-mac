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
#ifndef HX_ORTHO_SLICE_LDM_H
#define HX_ORTHO_SLICE_LDM_H

#include <hxcore/HxPlanarMod.h>
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
#include <hxvolumeviz/CustomDragger.h>
#include <hxvolumeviz/HxPortGPUShader.h>
#include <hxvolumeviz/HxGeometryPriority.h>

#include <hxfield/HxPortMultiChannel.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoLightModel.h>

#include <VolumeViz/nodes/SoOrthoSlice.h>

#include <hxlattice/HxContrastInterface.h>

// @TOBEREVIEWED_ALL

class HxArithLDM;

class HXVOLUMEVIZ_API HxOrthoSliceLDM : public HxPlanarMod, public HxMultiChannelMgr, public HxContrastInterfaceBase
{
    MC_HEADER(HxOrthoSliceLDM);

  public:

    /// Constructor
    HxOrthoSliceLDM();

    /// Compute method
    virtual void compute();

    /// Update method.
    virtual void update();

    /// Input port for region of interest.
    HxConnection        portROI;

    /// Modes: 0=Axial, 1=Coronal, 2=Sagittal
    HxPortRadioBox      portSliceOrientation;

    /// Modes: 0=adjust view  1=equal resolution
    HxPortToggleList    portOptions;
    enum { M_ADJUST_VIEW=0, M_EQUAL_RESOLUTION=1, M_LIGHTING=2, M_COLOR_TABLE=3};

    /// Toggles between nearest and linear interpolation
    HxPortRadioBox      portInterpolation;
    enum { M_NEAREST_INTERP=0, M_LINEAR_INTERP=1, M_MULTISAMPLE_12_INTERP=2};

    /// Colormap defines transfer function.
    HxPortColormap      portColormap;

    /// Number of slices to be used in 3D mode.
    HxPortIntSlider     portSliceNumber;

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

    /// Parse the interpreter command-line and execute commands
    int parse(Tcl_Interp* t, int argc, char **argv);

    /// To display memory information.
    void displayMemInfo() const;

    void updateEqualRez(bool onOff);

    virtual void updateSliceFromTranslation(float trans);

    virtual void finalizeSliceFromTranslation(float trans);

    virtual void updateTranslationFromSlice(int numSlice);

    virtual SoGroup* getScenegraph() {return m_scene;};

    /**
     * Return plane length into the local X,Y,Z coord system.
     */
    virtual void getPlaneLength(float& uLength, float& vLength, float* uMin=0, float* vMin=0);

    /**
     *  Return the "portSliceNumber".
     */
    virtual HxPort* getTranslationPort() {return &portSliceNumber;}

    /**
     *  Return the "portSliceOrientation".
     */
    virtual HxPort* getResetToOrthoPlanePort() {return &portSliceOrientation;}

    /**
     *  Reset the representation to one of the 3 major axes.
     */
    virtual void resetRepToOrthoPlane(OrthoPlane orthoPlane);

    /// Implement contrast interface
    HxConnection& portDataRef() {
        return this->portData;
    }

    HxPortMultiMenu* portMappingTypeRef() {
        return 0;
    }

    int legacyPortMappingTypeIndex;

    HxPortColormap& portColormapRef() {
        return this->portColormap;
    }

    void computeRef() {
        this->compute();
    }

  protected:

    virtual ~HxOrthoSliceLDM();
    void updatePlane() ;

    virtual void addHeadScenegraph();
    virtual void addTailScenegraph();

    void savePorts(FILE* fp) ;

    /// To compute the max main memory and the max tex memory used by the slice in full resolution.
    void computeMemSize();


    McHandle<SoOrthoSlice>  m_orthoSlice;

    /**
     *  Change the dragging active state according to data type or
     *  user request.
     */
    virtual void updateDraggingActiveState();

  private:

    McHandle<SoSeparator>   m_scene;
    McHandle<SoMaterial>    m_material;
    McHandle<SoLightModel>  m_lightModel;
    McHandle<CustomDragger> m_dragger;
    HxVolumeData*           m_hxVolData;

    HxArithLDM*             m_arithLDM;

    HxGeometryPriority      m_geometryPriority;

    /// The max main memory and the max tex memory used by the slice in full resolution.
    int m_sysMemSize;
    int m_texMemSize;
};

#endif // HX_ORTHO_SLICE_LDM_H

/// @}
