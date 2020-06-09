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

/// @addtogroup hxmolsurface hxmolsurface
/// @{
#ifndef HX_MOLSURFACE_VIEW_H
#define HX_MOLSURFACE_VIEW_H

#include <mclib/McColor.h>

#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortColorList.h>
#include <hxcore/HxPortSeparator.h>

#include <hxsurface/HxSurface.h>
#include <hxsurface/HxTriBase.h>

#include <hxmolecule/MolColoring.h>
#include <hxmolecule/MolFilter.h>
#include <hxmolecule/MolHighlighting.h>
#include <hxmolecule/HxMolBaseDisplayModule.h>

#include <hxmolsurface/HxMolSurface.h>
#include <hxmolsurface/HxMolSurfaceWinDLLApi.h>

class HxSurfaceBaseEditor;

/** Display module for objects of type HxSurface. */

class HXMOLSURFACE_API HxMolSurfaceView : public HxTriBase, 
                                          public HxMolBaseDisplayModule {

  HX_HEADER(HxMolSurfaceView);

  public:
    /// Constructor.
    HxMolSurfaceView();

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Allows the module to be connected directly to surface scalar fields.
    virtual int autoConnect(HxObject*);

    /// Connection to transparency field.
    HxConnection portTransparencyField;

    /// Connection to HxMolecule to retrieve information from it.
    HxConnection portMolecule;
    /// Connection to HxMolecule to retrieve information from it.
    HxConnection * portMolecule2;

    /// Defines overall surface transparency.
    HxPortFloatSlider portBaseTrans;
    /// How to map the scalar field range onto the transparency intervall [0,1].
    HxPortFloatTextN  portTransparencyMapping;

    /// Constant, molecule, or field colors.
    HxPortRadioBox portColorMode;
    /// Outside and inside colors.
    HxPortColorList portDefaultColors;
    /// How to handle mouse click event.
    HxPortRadioBox portPickAction;
    HxPortFloatSlider portSelectionDistance;
    ///
    MolFilter filter;
    ///
    MolFilter * filter2;
    ///
    MolHighlighting highlighting;
    ///
    HxPortSeparator portSeparator;
    /// Color schemes for molecules.
    MolColoring coloring;
    ///
    HxPortSeparator portSeparator2;
    /// Color schemes for molecules.
    MolColoring * coloring2;

    /// Shows or hides specified surface patch.
    void selectPatch(int which, int state);

    /// Shows or hides all patches incident to specified material.
    void selectMaterial(int which, int state);

    void updateGeometry() { soTriSurface->touch(); }

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Save state method.
    virtual void savePorts(FILE* fp);

    /// Overloaded method creates surface with multiple patches.
    virtual void createSurfaceData();

    /// Draw-style changed notification.
    virtual void drawStyleChanged(DrawStyleParameters what);

    /// Overloaded in order to inform editors about selection changes.
    virtual void viewerSelect();

  protected:
    virtual ~HxMolSurfaceView();

    // The surface to be displayed
    HxMolSurface* surface;
    int nPoints;
    int nTriangles;
    int lastNumPoints;
    int lastNumTriangles;
    int recomputeEdgesAndNeighbors;
    int soTriSurfaceTouchFlag;

    virtual void mouseClick(SoEventCallback*);

    // List of registered surface editors.
    McDArray<HxSurfaceBaseEditor*> surfaceEditors;

    // SoSurface callback used for rendering highlighted edges and points.
    static void postRenderCB(void* userData);

    // Crease-angle used to create direct normals (can be changed via Tcl).
    float creaseAngle;

    // Mouse click callback
    void (*mouseClickCallback)(SoEventCallback*, void*);
    void selectTrianglesByDist(int triId, McBitfield & bf, 
                               const McVec3f & center, const float & dist2);

    // Mouse click callback user data
    void* mouseClickUserData;

  public:
    // API for surface editors which want to make use of HxDisplayModule.

    struct MyEdge {
        int from,to;    
        McColor color;
    };

    struct MyPoint {
        McVec3f point;  
        McColor color;
    };

    McDArray<MyEdge> highlightedEdges;
    McDArray<MyPoint> highlightedPoints;

    int pickedEdgeFrom;
    int pickedEdgeTo;
    int pickedTriangle;

    void setMouseClickCallback(void (*cb)(SoEventCallback*,void*), void*);
    void setPickAtomInfo(HxMolecule * hxmol, HxMolecule * hxmol2,
                         McDArray<int> & atoms1, McDArray<int> & atoms2, 
                         int shift, int idx=-1, float v=0.0, float w=0.0);
    void setPickAtomInfoOneMolecule(HxMolecule * hxmol, McDArray<int> & atoms, 
                                    int levelId, McString & legend);
    void setPickInfo(int pickedTriangle, float u, float v, int is3d=0);
    void setDataFieldPickInfo(McString & legend, HxSurface::Triangle & tri,
                              int k2, int idx, float u, float v, float w,
                              McVec3f & p);
    void determineBarycentricCoords(float u, float v, float w,
                                    int & k0, int & k1, int & k2);

    void addSurfaceEditor(HxSurfaceBaseEditor* editor);
    void removeSurfaceEditor(HxSurfaceBaseEditor* editor);
    void updateNormals(int n, int* triangleIndices);
    void generateNormals();
    void setupSurface(int initBox);
    void setupVisibleTriangles();
    void setupHighlightedTriangles();
    void setupColors();

    // Virtual function of base class @c HxMolBaseDisplayModule.
    virtual float getLabelOffset(MtGroupRef & gref, HxMolecule * hxmol);
};

#endif

/// @}
