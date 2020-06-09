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

/// @addtogroup hxsurface hxsurface
/// @{
#ifndef HX_PORT_DRAWSTYLE_H
#define HX_PORT_DRAWSTYLE_H

#include <hxcore/HxPort.h>
#include <hxsurface/SoSurface.h>
#include <hxsurface/HxSurfaceWinDLLApi.h>

class HxViewBase;
class QComboBox;
class QPushButton;
class QAction;
class QActionGroup;
class QxActionNotifier;
class QxChooseColorButton;
class QxLineEdit;
class QLabel;

/// Special-purpose port for controlling the draw style in HxViewBase.

class HXSURFACE_API HxPortDrawStyle : public HxPort {

  MC_ABSTRACT_HEADER(HxPortDrawStyle);

  public:
    /// Constructor.
    HxPortDrawStyle(HxViewBase* object, const char* name);

    /// Destructor.
    ~HxPortDrawStyle();

    /// The different draw styles.
    enum Style {
        OUTLINED=0,
        SHADED=1,
        LINES=2,
        POINTS=3,
        SEMITRANSPARENT=4
    };

    /// The different normal bindings.
    enum NormalBinding {
        /// One normal per triangle.
        TRIANGLE_NORMALS=SoSurface::TRIANGLE_NORMALS,
        /// One normal per indexed vertex.
        VERTEX_NORMALS=SoSurface::VERTEX_NORMALS,
        /// Three times as many normals as triangles.
        DIRECT_NORMALS=SoSurface::DIRECT_NORMALS
    };

    /// Alpha modes.
    enum AlphaMode {
        /// Whole surface is opaque.
        OPAQUE_ALPHA=SoSurface::OPAQUE_ALPHA,
        /// Constant alpha.
        CONSTANT_ALPHA=SoSurface::CONSTANT_ALPHA,
        /// View-dependent alpha.
        FANCY_ALPHA=SoSurface::FANCY_ALPHA
    };

    /// Depth sorting modes.
    enum SortingMode {
        /// No sorting.
        NO_SORTING=SoSurface::NO_SORTING,
        /// Depth sorting along major axes.
        AXIS_SORTING=SoSurface::AXIS_SORTING
    };

    /// Culling modes.
    enum CullingMode {
        /// No culling (render both faces).
        NO_CULLING=SoSurface::NO_CULLING,
        /// Cull back faces.
        BACK_FACE=SoSurface::BACK_FACE,
        /// Cull front faces.
        FRONT_FACE=SoSurface::FRONT_FACE
    };

    /// Get draw style.
    int getValue() const { return drawStyle; }

    /// Set draw style.
    void setValue(int drawStyle);

    /// Check if texturing (as opposed to Gouraud shading) is enabled.
    bool isTexture() const { return textureFlag; }

    /// Sets texture option on or off and fires the network.
    void setTexture(bool value);

    /// Check if specular lighting is enabled.
    bool isSpecularLighting() const;

    /// Enables or disables specular lighting.
    void setSpecularLighting(bool value);

    /// Returns the current normal binding.
    NormalBinding getNormalBinding() const;

    /// Sets the normal binding and updates the view base module.
    void setNormalBinding(NormalBinding binding);

    /// Returns the current alpha mode.
    AlphaMode getAlphaMode() const;

    /// Sets the alpha mode and updates the view base module.
    void setAlphaMode(AlphaMode mode);

    /// Returns the current sorting mode.
    SortingMode getSortingMode() const;

    /// Sets the sorting mode and updates the view base module.
    void setSortingMode(SortingMode mode);

    /// Returns the current culling mode.
    CullingMode getCullingMode() const;

    /// Sets the culling mode and updates the view base module.
    void setCullingMode(CullingMode mode);

    /// Creates toggles for controlling the culling mode.
    void cullingControls();

    /// Creates toggles for controlling the normal binding.
    void normalControls();

    /// Tcl-command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Save state method.
    virtual void saveState(FILE* fp);

    /// Returns current state in ascii string.
    virtual void getState(McString& state);

    /// Restores current state from ascii string.
    virtual int setState(const McString& state);

    /// Set the line width.
    void setLineWidth(float f);
    
    /// Set the outline color.
    void setOutlineColor(const SbColor& c);

  protected:
    QxGuardedPtr<QComboBox> comboBox;
    QxGuardedPtr<QPushButton> m_optionsButton;
    QxGuardedPtr<QLabel> m_labelLineWidth;
    QxGuardedPtr<QxLineEdit> m_lineWidth;
    QxGuardedPtr<QxChooseColorButton> m_colorButton;
    QxGuardedPtr<QLabel> m_labelColorButton;

    QxGuardedPtr<QActionGroup> shadingActionGroup;
    QxGuardedPtr<QAction> specularAction;
    QxGuardedPtr<QAction> gouraudAction;
    QxGuardedPtr<QAction> textureAction;

    QxGuardedPtr<QActionGroup> alphaActionGroup;
    QxGuardedPtr<QAction> opaqueAction;
    QxGuardedPtr<QAction> constAlphaAction;
    QxGuardedPtr<QAction> fancyAlphaAction;
    QxGuardedPtr<QAction> sortingAction;

    QxGuardedPtr<QActionGroup> cullingActionGroup;
    QxGuardedPtr<QAction> bothFaceAction;
    QxGuardedPtr<QAction> frontFaceAction;
    QxGuardedPtr<QAction> backfaceAction;

    QxGuardedPtr<QActionGroup> normalActionGroup;
    QxGuardedPtr<QAction> triNormalAction;
    QxGuardedPtr<QAction> vertexNormalAction;
    QxGuardedPtr<QAction> directNormalAction;

    QxGuardedPtr<QAction> createSurfaceAction;

    int drawStyle;
    unsigned int textureFlag:1;
    unsigned int hasCullingControls:1;
    unsigned int hasNormalControls:1;

    void setSensitivity();

    virtual void guiCallback();
    virtual void createWidget(QWidget* parent);

    void popupActivated(QAction * action);
};

#endif

/// @}
