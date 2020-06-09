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

/// @addtogroup hxvertexset hxvertexset
/// @{
#ifndef HX_DISPLAY_VERTICES_H
#define HX_DISPLAY_VERTICES_H

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/draggers/SoTabBoxDragger.h>

#include <mclib/McHandle.h>
#include <mclib/McBitfield.h>

#include <hxcore/HxModule.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxGLPolyLine.h>

#include <hxcore/HxVertexSet.h>

#include <hxcolor/HxColormap.h>
#include <hxcolor/HxPortColormap.h>
#include <hxcore/HxPortMultiMenu.h>

#include <hxvertexset/SoSphereSet.h>
#include <hxvertexset/SoText2Set.h>
#include <hxvertexset/HxVertexsetWinDLLApi.h>

/// Displays a landmark set.
class HXVERTEXSET_API HxDisplayVertices : public HxModule {

    HX_HEADER(HxDisplayVertices);

public:
    /// Determines the way points are shown.
    enum DrawStyles {
        /// triangulated spheres
        SPHERES,
        /// sphere image mapped-on pologons
        PLATES,
        /// points independent of distance from viewer
        POINTS};

    /// Drop down list for sphere coloring of linesets.
    HxPortMultiMenu portFieldSelect;

    /// Optional scalar field determining coloring of sphere.
    HxConnection portColorField;
    /// Connection to optional colormap.
    HxPortColormap portColormap;
    /// Draw style: spheres, plates or points.
    HxPortRadioBox portDrawStyle;
    /// Unique radius for all spheres.
    HxPortFloatSlider portSphereRadius;
    /// Point size for draw style POINTS.
    HxPortIntSlider portPointSize;
    /// Controls complexity of spheres.
    HxPortFloatSlider portComplexity;
    /// Several options.
    HxPortToggleList portOptions;
    /// Size of text.
    HxPortIntSlider portFontSize;
    /// Transparency of spheres (only for SPHERES and PLATES modes).
    HxPortFloatSlider portTransparency;
    /// Actions for selected objects.
    HxPortButtonList portBuffer;

private:
    bool scaleRadii; // flag whether to scale, should perhaps better be a port
    float defaultSphereRadius;
    float fontSize;
    SbColor defaultColor;
    SbColor highlightColor;
    SbColor textColor;
    int pointNumOff;

    McHandle<HxVertexSet>     data;   // data object
    McVec3f                   *coords;

    // one bit for each point (internal buffer)
    McBitfield                selected;
    McHandle<SoSeparator>     soRoot;
    McHandle<SoSphereSet>     soSphereSet;
    McHandle<SoEventCallback> soEventCB;
    McHandle<SoText2Set>      soLabels;
    McHandle<SoTabBoxDragger> dragger; // used for selection
    HxGLPolyLine              polyLine;

    unsigned int isDragging;
    unsigned int draggerIsVisible;
    int oldOptions[3];
    // used for selecting with box dragger
    float maxScaleX, maxScaleY, maxScaleZ;
    float xMin, xMax, yMin, yMax, zMin, zMax;
    float defaultOffset;
    char initValues;

public:
    /// Constructor.
    HxDisplayVertices();
    /// Destructor.
    ~HxDisplayVertices();

    /// Update method shows/hides necessary ports.
    virtual void update();
    /// Compute method.
    virtual void compute();
    /// Tcl command interface.
    int parse(Tcl_Interp* t, int argc, char **argv);
    /// Write port state to file.
    void savePorts(FILE* fp);

    /// Set colors of vertices.
    void setColors(const SbColor * colors, int size);

    /// Add node to buffer
    void addToBuffer(int first, int last=-1);

    /// Get highlighted vertices
    void getHighlighted(McDArray<int>& highlighted);
	
    /// Get selected vertices
    void getSelected(McDArray<int>& selection);

    /// Redefine this method to add specific picking information.
    virtual void gatherPickInfo(
        const SoPickedPoint* pickedPt,
        McHashTable<McString, McString>& cbArguments);

private:
    enum BufferButtons {ADD, REMOVE, CLEAR, BOX, INVERT, DRAW};

    /// Interpretes portBuffer and calls bufferAdd(), bufferRemove(), etc.
    void handleBuffer();
    /// Selects all highlighted triangles (== adds them to buffer).
    void bufferAdd();
    /// Unselects all highlighted triangles (== removes them from buffer).
    void bufferRemove();
    /// Unselects all triangles.
    void bufferClear();
    /// Highlights all triangles inside box.
    void bufferNew();
    /// Inverts buffer.
    void bufferInvert();

    /** Decides whether all spheres or only buffered spheres should
        be shown. */
    void showSpheres();
    /// Show buffered spheres only.
    void showBufferedSpheres();
    /// Show all spheres.
    void showAllSpheres();
    /// Update (create and remove) labels for all (buffered) points.
    void updateLabels();
    void updateLabelOffsets(McDArray<float> &rad);
    void updateLabelSelection();

    /// Build sphere set.
    SoNode* buildSphereSet(void);
    /// Sets colors for all points.
    void getColorsFromColorField(McDArray<SbColor> &colors);
    /// Sets sizes for all points.
    void setRadii (McDArray<float> &sizes);

    /// Callback for selection via polyline.
    static void viewerSelectCB(void* userData);
    /// Select via polyline.
    void viewerSelect();

    /// Selection callback.
    static void selectionCB(void *p, SoEventCallback *eventCB);
    /// Member function selection callback.
    void selectionCallBack(SoEventCallback *eventCB);

    // Several functions operating on box dragger.
    void initBox(float box[6]);
    void showBox();
    void hideBox();
    void constrainBox();
    static void newBoxCB(void* userData, SoDragger* dragger);
    static void startDraggingCB(void* userData, SoDragger*);
    static void finishDraggingCB(void* userData, SoDragger* dragger);
};

#endif

/// @}
