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

/// @addtogroup hxsurftools hxsurftools
/// @{
#ifndef HX_DISPLAY_SURFACE
#define HX_DISPLAY_SURFACE

#include <mclib/McColor.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxsurface/HxSurface.h>
#include <hxsurface/HxTriBase.h>
#include <hxsurface/FaceOctree.h>
#include <hxsurftools/HxSurfToolsWinDLLApi.h>

#include <mclib/McHashTable.h>

class HxViewerLegend;
class SoEventCallback;
class HxSurfaceBaseEditor;
class HxDisplaySurfaceData;

/** Display module for objects of type HxSurface. */

class HXSURFTOOLS_API HxDisplaySurface : public HxTriBase {

  HX_HEADER(HxDisplaySurface);

  public:
    /// Constructor.
    HxDisplaySurface();

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Allows the module to be connected directly to surface scalar fields.
    virtual int autoConnect(HxObject*);

    /// Selection Mode: 0 = material, 1 = patch, 2 = boundary id
    HxPortMultiMenu portSelectionMode;

    /// select a patch of the surface. 0 = all patches
    HxPortIntSlider portPatch;

    HxPortMultiMenu portBoundaryId;

    /// Material menu (triangles between selected regions are displayed).
    HxPortMultiMenu portMaterial;

    /// Color mode: 0=normal, 1=mixed, 2=twisted, 3=boundary ids
    HxPortMultiMenu portColorMode;

    /// Defines overall surface transparency.
    HxPortFloatSlider portBaseTrans;

    /// Interaction in VR mode.
    HxPortMultiMenu portVRMode;
    enum { VR_NONE, VR_QUERY, VR_HIGHLIGHT_PATCHES, VR_SELECT_PATCHES,
        VR_HIGHLIGHT_TRIANGLES, VR_SELECT_TRIANGLES };
    
    /// Shows or hides specified surface patch.
    void selectPatch(int which, int state);

    /// Shows or hides all patches incident to specified material.
    void selectMaterial(int which, int state);

    /// Checks whether speciefied triangle is highlighted.
    int isHighlighted(int t) { return soTriSurface->isHighlighted(t); }

    /// Checks whether speciefied triangle is selected.
    int isSelected(int t) { return soTriSurface->isSelected(t); }

    /// Touches the Inventor surface node, thereby causing a redraw.
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

    /// Overloaded method from HxSelectInterface.
    virtual HxParamBundle* selectinterface_bundle(int create);

    virtual void handleDrawStyle();

    /// Access to the scene currently displayed
    SoSeparator *  getRootSeparator (void) {return(soRoot);}

    /// Redefine this method to add specific picking information.
    virtual void gatherPickInfo(
        const SoPickedPoint* pickedPt, 
        McHashTable<McString, McString>& cbArguments);

  protected:
    // Virtual destructor.
    virtual ~HxDisplaySurface();

    // The surface being displayed
    HxSurface* surface;

    // Pointer to private data class
    HxDisplaySurfaceData* more;

    // Called when selection box has changed, selects triangles
    virtual void bufferNew();

    // Calles when a mouse press or mouse release event occurs
    virtual void mouseClick(SoEventCallback*);

    // List of registered surface editors.
    McDArray<HxSurfaceBaseEditor*> surfaceEditors;

    // SoSurface callback used for rendering highlighted edges and points.
    static void postRenderCB(void* userData);

    // Handles VR tracker events.
    static void trackerEventCB(void *userData, SoEventCallback* node);

    // Handles VR controller button events.
    static void controllerEventCB(void *userData, SoEventCallback* node);

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

    int pickedTriangle;
    HxViewerLegend* pickLegend;
    McDArray<MyEdge> highlightedEdges;
    McDArray<MyPoint> highlightedPoints;

    void setMouseClickCallback(void (*cb)(SoEventCallback*,void*), void*);
    void setPickInfo(int pickedTriangle, float u, float v, int is3d=0);
    void addSurfaceEditor(HxSurfaceBaseEditor* editor);
    void removeSurfaceEditor(HxSurfaceBaseEditor* editor);
    void updateNormals(int n, int* triangleIndices);
    void generateNormals();
    bool setupSurface(int initBox);
    void setupColors();

    void addToSurface(HxSurface& Surf, SbMatrix *transMat=0);

    void recreateVertexBuffers();

  private:
    // keeps track of material name and index 
    // mappings of the current selection (visible surface)
    McHashTable<McString, int>* mMaterialNameIndexMappings;

    // material colors of the current selection (visible surface)
    McDArray<SbColor> mMaterialColors;

    // material color transparencies of the current selection (visible surface)
    McDArray<float> mMaterialTransparencies;

    // material names of the current selection (visible surface)
    McDArray<McString> mMaterialNames;

    // keeps track of current selection (visible surface) patches' materials
    // (inner region and outer region material IDs)
    McDArray<McDArray<int> > mPatchMaterials;

    // maps patch ids to reindexed patch ids 
    // of the current selection (visible surface)
    McHashTable<unsigned int, unsigned int>* mPatchIdMappings;

    // keeps track of patches that triangles belong to
    McDArray<unsigned int> mTrianglePatches;

    int addUsedMaterial(const char *name, const SbColor color, float colorTransparency);

    // adds the new material (name) to the specified surface
    // makes the new material name unique if it already exists
    int addSurfaceMaterial(HxSurface& Surf, McString *name);

    int genNormals;

    bool isBigSurface();
};

#endif

/// @}
