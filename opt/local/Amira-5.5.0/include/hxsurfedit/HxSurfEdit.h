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

/// @addtogroup hxsurfedit hxsurfedit
/// @{
#ifndef HX_SURF_EDIT_H
#define HX_SURF_EDIT_H

#include <QObject>

#include <mclib/McVec4i.h>
#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>

#include <hxsurftools/HxSurfaceBaseEditor.h>
#include <hxsurface/FaceOctree.h>

#include "HxSurfEditWinDLLApi.h"
#include "Undoable.h" // stefan

class QToolBar;
class QMenu;
class QComboBox;
class QStackedWidget;

class QxToolButton;
class HxViewer;

class SurfEditTool;
class SurfEditPickTool;
class SurfEditMouseTool;
class SurfEditSelector;
class SurfEditNotifier;
class SurfEditMagicWand;
class SurfEditBidTool;
class SurfEditEdgeFlipper;
class SurfEditFlipTool;
class SurfEditCollapse;
class SurfEditBisect;
class SurfEditPointMove;
class SurfEditPointSelect;
class SurfEditPatchReorder;
class SurfEditRefine;
class SurfEditHoleFill;
class SurfEditSmooth;
class SurfEditFixIntersections; //martin
class SurfEditFixDihed; //hans
class SurfEditFixTetra; //martin
class SurfEditPrepareTetragen; //martin
class SurfEditRemoveCoplanar; // stefan
class SurfEditConnectivity; // stefan
class SurfEditDeleteHighlighted; // stefan
class SurfEditProjector; // stefan
class BufferUndo; // stefan
class SurfEditBrushTool; // stefan
class SurfEditMousePatchSelector; // stefan
// class SurfEditRefineTool;
// class SurfEditCenterRefineTool; // stefan
// class SurfEditDrawContour; // stefan
// class SurfEditCutTool; // stefan
// class SurfEditEdgeRefineTool; // stefan
// class SurfEditPathRefineTool; // stefan

class SoEventCallback;
class SoSeparator;
class SoMatrixTransform;
class SoDragPointDragger;

/// New unified surface editor

class HXSURFEDIT_API HxSurfEdit : public HxSurfaceBaseEditor {

  HX_HEADER(HxSurfEdit);

  public:
    /// Default constructor.
    HxSurfEdit();

    /// Parse method
    int parse(Tcl_Interp* t, int argc, char **argv);

    /// Initialize ports here.
    virtual void startEditing(HxData *data);

    /// Remove selection callbacks here.
    virtual void stopEditing();

    /// Interpretes mouse click events.
    virtual void mouseClick(SoEventCallback *eventCB);

    /// Returns pointer to HxDisplaySurface object.
    HxDisplaySurface* getDisplaySurface() const { return display; }

    /// Returns pointer to SoTriSurface node.
    SoTriSurface* getSoTriSurface() const { return display->soTriSurface; }

    /// Returns pointer to surface being edited.
    HxSurface* getSurface() const { return (HxSurface*) getData(); }

    /// Returns the number of highlighted triangles.
    int getNumHighlighted();

    /// Returns true if there are highlighted faces.
    bool hasHighlightedFaces();

    /// Copies highlight flags into a bitfield.
    void getHighlightInfo(McBitfield& bitfield);

    /// Returns true if there are visible (selected) faces.
    bool hasVisibleFaces();

    enum Selector
    {
        SEL_MATERIALS=0,
        SEL_BOUNDARY_IDS,
        SEL_PATCHES,
        SEL_INTERSECTIONS,
        SEL_ORIENTATION,
        SEL_ASPECT_RATIO,
        SEL_DIHEDRAL_ANGLE,
        SEL_TETRA_QUALITY,
        SEL_NON_MANIFOLD,
        SEL_HOLES
    };

    /// Shows selector in selector tool bar.
    void activateSelector(Selector which);

    /// Called by the notifier to activate a tool.
    void activateTool(int which, int fromMenu=0, int setInteraction=1);

    /// Called by the notifier to activate a tool.
    void activateTool(SurfEditTool* tool, int fromMenu=0, int setInteraction=1);

    /** Add highlighted faces to buffer. If the @c clearBefore
        flag is set the buffer will be cleared before so that
        only the higlighted faces will be visible. */
    void addToBuffer(int clearBefore=0);

    /// Removes all highlighted triangles from the buffer
    void removeFromBuffer();

    /** Highlights all visible triangles. If inverse is true
        all invisible triangles are highlighted. */
    void highlightBuffer(int inverse=0);

    void highlightAllTriangles(int mode);

    void selectAllTriangles(int mode);

    int getPickedTriangle(int& t);

    int getPickedEdge(int& from, int& to);

    /// Calls surface->createAllEdges() if necessary
    void checkEdges();

    /// Calls surface->computeTrianglesPerPoint() if necessary
    void checkTrianglesPerPoint();

    // Calls surface->removeCoplanarTriangles() and updates the display.
    // void removeCoplanarTriangles(); // now in: SurfEditRemoveCoplanar

    // Calls surface->recompute() and updates the display.
    // void recomputeConnectivity(); // now in: SurfEditConnectivity

    // Deletes highlighted triangles, no undo yet
    // void deleteHighlightedTriangles(); //now in: SurfEditDeleteHighlighted

    /** Updates all currently active tools and selectors. This method
        should be called by a tool when the surface has been modified.
        The tool which modified the surface should be set in @c fromMe.
        This tool will not be updated. */
    void surfaceChanged(SurfEditTool* fromMe=0);

    /** Informs all currently active tools about selection changes.
        For the meaning of @c fromMe see surfaceChanged. */
    void selectionChanged(SurfEditTool* fromMe=0);

    /** Overloaded method from HxSurfaceBaseEditor. This method is called
        before the selection or highlight buffer is changed from within
        the surface display module. */
    virtual void preSelectionChange();

    /** Overloaded method from HxSurfaceBaseEditor. This method is called
        after the selection or highlight buffer is changed from within
        the surface display module. */
    virtual void postSelectionChange();

    SurfEditSelector* getSelector(Selector selector) const;

    SurfEditHoleFill* getSurfEditHoleFill(void) const{
        return holeFillTool;
    }

    /** Used to implement undo of buffer changes. Before the selection
        buffer of the highlight buffer is modified by a mouse tool or
        a selector this method should be called. After the buffer has
        been modified undoBufferEnd should be called. The mode
        parameter determines whether only the highlight buffer (bit 1)
        or only the selection buffer (bit 2) or both buffers (bits 1 and
        2, value 3) should be saved. The default is to save the highligt
        buffer only. */
    // void undoBufferBegin(int mode=1); // extern now

    /** Actually stores an undo entry. The method should be called after
        undoBufferBegin. */
    // void undoBufferEnd(); // extern now

    /** Used to implement undo of surface changes. The method should be
        called before the surface is actually modified. A compressed copy
        of the current surface is stored. Mode bit 0 indicates that
        parameters should be copied. Mode bit 1 indicates that the points
        should be copied. Mode bit 2 indicates that patches and triangles
        should be copied. The default is 7, i.e., all bits are set. */
    // void undoSurfaceBegin(int mode=7); // extern now

    /** Actually stores an undo entry. The method should be called after
        undoSurfaceBegin. */
    // void undoSurfaceEnd(); // extern now

  protected:
    ~HxSurfEdit();

    QToolBar* toolBar;
    QMenu* surfEditMenu;
	
    QMenu* editMenu;
    QAction* undoAction; //1
    QAction* deleteHighlightedFacesAction; //4

    QMenu* viewMenu;
    QAction* outlinedAction; //0
    QAction* shadedAction; //1
    QAction* linesAction; //2
    QAction* pointsAction; //3
    QAction* transparentAction; //4
    QAction* normalColorsAction; //5
    QAction* mixedColorsAction; //6
    QAction* twistedColorsAction; //7
    QAction* boundaryIdsAction; //8

    QMenu* bufferMenu;
    QAction* pasteHighlightsAction; //9
    QAction* pasteBufferAction; //5

    QAction* helpAction;

    SurfEditBidTool* bidTool;
    SurfEditProjector* projector; // stefan
    SurfEditPickTool* pickTool;
    SurfEditEdgeFlipper* edgeFlipper;
    SurfEditMagicWand* magicWand;
    SurfEditFlipTool* flipTool;
    SurfEditCollapse* collapseTool;
    SurfEditBisect* bisectTool;
    SurfEditPointMove* pointMoveTool;
    SurfEditPointSelect* pointSelectTool;
    SurfEditPatchReorder* patchReorder;
    SurfEditRefine* refineTool;
    SurfEditHoleFill* holeFillTool;
    SurfEditSmooth* smoothTool;
    SurfEditFixIntersections* fixInter; //martin
    SurfEditFixDihed* fixDihed; //hans
    SurfEditRemoveCoplanar* removeCoplanar; // stefan
    SurfEditConnectivity* connectivity; // stefan
    SurfEditDeleteHighlighted* deleteHighlighted; // stefan
    SurfEditBrushTool* brushTool; // stefan
    SurfEditMousePatchSelector* mousePatchSelector; // stefan
    // SurfEditRefineTool* mouseRefineTool; // stefan
    // SurfEditEdgeRefineTool* edgeRefineTool; // stefan
    // SurfEditCenterRefineTool* centerRefineTool; // stefan
    // SurfEditPathRefineTool* pathRefineTool; // stefan
    // SurfEditDrawContour* drawContour; // stefan
    // SurfEditCutTool* cutTool; // stefan
    SurfEditFixTetra* fixTetra; //martin
    SurfEditPrepareTetragen* prepareTetragen; //martin

    BufferUndo* bufferUndo; // stefan: HxSurfEdit can use a bufferUndoStack

    SurfEditNotifier* notifier;
    QxToolButton* bufferAddBtn;
    QxToolButton* bufferRemoveBtn;
    QxToolButton* bufferClearBtn;
    QxToolButton* bufferBoxBtn;
    QxToolButton* bufferDrawBtn;

    QComboBox* selectorBox;
    QStackedWidget* selectorStack;

    SurfEditTool* currentTool;
    McDArray<SurfEditTool*> tools;
    McDArray<SurfEditSelector*> selectors;
    SoEventCallback* eventCB;

    void createMenuBar();
    void createSelectorBar();
    void createToolBar();
    void checkBoundaryIds(HxSurface* surface);

  friend class SurfEditNotifier;

  public:
    //--------------------------------------------------------------------
    //
    //  These methods are interfaces between new and old code
    //
    //--------------------------------------------------------------------

    // Wrapper: uses SurfEditFlipTool::flipEdge
    int flipEdge(int from, int to);

    // Defined in SurfEditBisect.cpp
    // void bisectEdge(int from, int to); // now in: SurfEditBisect

    /// puts an undoable implementation on undoStack
    void announceUndoableAction(Undoable &undoImp);

    /// stack for Undoable actions
    McDArray< Undoable* > undoStack;

    //--------------------------------------------------------------------
    //
    //  Stuff copied from the old surface editor
    //  Code need to be distributed to the different tools !
    //
    //--------------------------------------------------------------------

#if 0 // in BufferUndo
    struct SurfaceUndoEntry {
        struct Patch {
            unsigned char innerRegion;
            unsigned char outerRegion;
            unsigned short boundaryId;
        };

        int mode;
        HxParamBundle parameters;
        McDArray<McVec3f> points;
        McDArray<Patch> patches;
        McDArray<McVec4i> triangles;
        McBitfield selectionData;
        McBitfield highlightData;
    };

    struct BufferUndoEntry {
        int selectionStart;
        int highlightStart;
        int selectionStop;
        int highlightStop;
        unsigned int* selectionData;
        unsigned int* highlightData;

        BufferUndoEntry() {
            selectionData = 0;
            highlightData = 0;
        }

        ~BufferUndoEntry() {
            if (selectionData) free(selectionData);
            if (highlightData) free(highlightData);
        }
    };

    struct UndoEntry {
        int type;
        int from, to;
        McSmallArray<int,3> trianglesAtEdge;
        McSmallArray<int,3> patches;
        McSmallArray<int,6> trianglesAt2;
        McVec3f oldLocation;
        BufferUndoEntry* bufferUndo;
        SurfaceUndoEntry* surfaceUndo;

        UndoEntry() {
            bufferUndo = 0;
            surfaceUndo = 0;
        }

        ~UndoEntry() {
            delete bufferUndo;
            delete surfaceUndo;
        }
    };

    McDArray<UndoEntry> undoInfo;
    void undoBuffer(BufferUndoEntry* entry);
    void undoSurface(SurfaceUndoEntry* entry);
#endif

    int currentPointIdx;
    int currentTriangle;
    Selector currentSelection;
    McDArray<int> triangleList;
    McDArray<float> qualityList;
    McDArray<int> fourthVertList;
    McDArray<int> oppositeTriList;

    SoSeparator* draggerSep;
    SoMatrixTransform* draggerTransform;
    SoDragPointDragger* dragger;

    void displayTriangle(int t);
    // void setPointDragger(int p); // now in: SurfEditPointMove
    void getTetQuality(int i1, int i2, int i3, int i4,
                       float& d, float& r, float& R);

    float getAdjacentTetQuality(int iTri, int& v4);

    int check4thVertex(int iTri, int& v4);

    float getTriangleQuality(int iTri);

    void sortQuality(int qualityMeasure = 0, int sortOut = 1);
    void sortIntersect();

    // basic editing operation: edge collapse
    // void collapse(int v1, int v2, int addUndoEntry=1); // now in: SurfEditCollapse

    // Undo edge collapse
    // int undoCollapse(UndoEntry &entry); // should be implemented in SurfEditCollapse

    /// Compute triangle normal.
    void computeNormal(int t);

    /// Find edge given the vertices.
    static int findEdge(Surface* surf, int v1, int v2);

    // basic editing operation: edge flip
    // int flipEdge(int v1, int v2, int &v3, int &v4, int &t1, int &t2, int &e);

    // Undo edge flip
    // int undoFlip(UndoEntry &entry); // should be implemented in SurfEditFlipTool

    /// basic editing operation: edge bisection
    // int bisectEdge(int v1, int v2, int &vnew, int verbose=0); // now in: SurfEditBisect

    FaceOctree<HxSurface> octree;

    /// global triangle intersection test
    int checkIntersections();
    void displayNeighbours(int triangle, int vertex4 = -1);
    void displayLeaf(int depth, int which);

    /// intersection test for single triangle
    static int intersectionTest(Surface* surf, int t, McDArray<int>& neighbours);

    /// intersection test for single triangle
    static int intersectionTest(Surface* surf, int t, McDArray<int>& neighbours,
                         McDArray<int>& edgeList,
                         McDArray<McVec3f>& intsctPnts);

    /// intersection test for single triangle (old version)
    // int intersectionTestSav(int t, McDArray<int>& neighbours);

    /// find intersecting edges from a list of triangles
    int findIntersectingEdges(McDArray<int>& neighbours,
                              McDArray<int>& edgeList,
                              McDArray<McVec3f>& intsctPnts);

    /// determine number of triangles of region adjacent to each edge
    void classifyEdges(int iRegion, int &nOdd,
                       int &nEdge0, int &nEdge2, int &nEdge4,
                       McDArray<signed char> &markEdges);
    /// create groups of connected triangles
    int createTriangleGroups(const int iRegion,
                             McDArray<signed char> &markEdges,
                             McDArray<short> &markTriangles);
    /// find inconsistent edges
    void findInconsistentEdges(const int iRegion,
                               McDArray<signed char> &markEdges,
                               McDArray<short> &markTriangles);
    /// create closed surfaces
    int createClosedSurfaces(const int iRegion, int nGroups,
                             McDArray<signed char> &markEdges,
                             McDArray<short> &markTriangles);
    /// calculate volumes enclosed by surfaces
    void calcEnclosedVolumes(const int iRegion,
                             McDArray<short> &markTriangles,
                             McDArray<float> &enclosedVolumes);
    /// find including surfaces for a given surface
    void findIncludingSurfaces(McDArray<short> &markTriangles,
                               const int jSurf,
                               McDArray<signed char> &includingSurfaces);
    /// determine which surfaces enclose each other
    void findInclusions(McDArray<short> &markTriangles,
                        const int nSurfaces,
                        McDArray<signed char> &inclusionInfo);
    /// check enclosed volumes
    void checkEnclosedVolumes(McDArray<float> &enclosedVolumes,
                              McDArray<signed char> &inclusionInfo,
                              McDArray<short> &markTriangles,
                              int &groupsOf4);

    /// repair groups of triangles with false orientation
    void repairFalseOrientation();

    /// check orientation of closed surfaces
    int checkOrientation();

    /// check orientation of single triangle
    int orientationTest(int t, int imax, const McVec3f &norm, McVec3f &cm,
                        McDArray<int>& neighbours);

    /// classifies a surface as a manifold or non-manifold surface
    int detectNonManifold();

    /// Hide all triangles in triangleList (useful for surface editing)
    void hideTriangles(int max);

    /// basic editing operation: move point
    static void movePointCB(void* userData, SoDragger*);
    static void startDraggerCB(void* userData, SoDragger*);
    static void finishDraggerCB(void* userData, SoDragger*);

    static int   keyPressCB (const SoEvent *, HxViewer *, void *);
    int          keyPress   (const SoEvent *);

    /// display list
    void displayFirst (void);
    void displayNext (void);
    void displayPrevious (void);
    void updateDisplay (void);

    /// undo
    void undo();
    void setupSurface(int nNewTriangles);
};

#endif

/// @}
