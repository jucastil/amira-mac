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

/// @addtogroup hxneuroneditor hxneuroneditor
/// @{
#ifndef HX_NEURONEDITOR_SUBAPPLICATION_H
#define HX_NEURONEDITOR_SUBAPPLICATION_H

/** \class HxNeuronEditorSubApp
  \brief Filamenteditor Subapplication

  *** The Plug-in mechanism ***

  The Plug-in mechanism allows to load certain functionality dynamically at run time.

  1. The Plug-in has to be annouced within a package's .rc file

     In order to register a new Plug-in append the following list to the list 
     of Plug-Ins to register.

    # ----------------------------------------------------------------------------
    #   Filament editor Plug-in mechanism 
    # ----------------------------------------------------------------------------
    if { [info exists hxneuroneditorplugins] == 0} {
        set hxneuroneditorplugins [list];
    }

    #
    #   plugInName             = Descriptive name of the Plug-in
    #   plugInInitFunctionName = Name of the C function which gets called dynamically
    #   packageName            = Package name where the plugInInitFunction is defined
    # ----------------------------------------------------------------------------
    lappend hxneuroneditorplugins { pluginName pluginInitFunction packageName}

  2. A plain C function has to be declared which gets called on filament editor initial start up.
     We use extern "C" to avoid name mangling so HxDSO can find it.

    #ifdef __cplusplus
      extern "C" {
    #endif
      void EXPORT_API MyPlugin_init(HxNeuronEditorSubApp* editor);
    #ifdef __cplusplus
      }
    #endif

  3. Define the above declared init function.

     The Filament editor currently supports two different Plug-In types:
     - ToolBoxes @see QxNeuronEditorToolBox
     - Tools     @see QxNeuronEditorTool

    class MyNeuronEditorToolBox : public QxNeuronEditorToolBox
    {

    };

    class MyNeuronEditorTool : public QxNeuronEditor[Modal|Trigger]Tool
    {

    };

    void MyPlugin_init(HxNeuronEditorSubApp* editor)
    {
        MyNeuronEditorTool* myTool = new MyNeuronEditorTool();
        editor->registerTool(myTool);

        MyNeuronEditorToolBox* myToolBox = new MyNeuronEditorToolBox();
        editor->registerToolBox(myToolBox);
    }

*/

namespace Ui { class QxNeuronEditor; }
#include "hxneuroneditorAPI.h"

#include <QObject>

#include <hxcore/HxSubApplication.h>
#include <hxcore/HxBoundingBox.h>

#include <hxspatialgraph/SpatialGraphSelection.h>

#include <vsvolren/VsVolren.h>

#include <Inventor/nodes/SoCallback.h>

#include "MPRTools.h"
#include "ExNotifier.h"
#include "UndoRedoTool.h"

class VsSlice;
class VsSpatialGraphRen;
class VsSegmentRen;

class QStackedLayout;
class QToolBar;

class QxNeuronEditorTool;
class QxNeuronEditorModalTool;
class QxNeuronEditorToolBox;
class QxNeuronEditorViewerPanel;
class QxTracingToolbox;
class QxTraceTool;
class QxMoveTool;
class QxViewToolbox;
class QxEditingToolbox;
class QTreeWidgetItem;

class HxSpatialGraph;
#include <hxspatialgraph/HxSpatialGraphView.h>
class Operation;

class HxViewer;
class HxMPRViewer;
class HxSegmentMPRViewer;
class HxViewerModalTool;

class SoGetBoundingBoxAction;
class SoEventCallback;
class MPRPickingThresholds;

class HXNEURONEDITOR_API HxNeuronEditorSubApp : public QObject, public HxSubApplication
{
    Q_OBJECT

    MC_HEADER(HxNeuronEditorSubApp);
    
public:
    
    enum FilamentType {
        BRIGHT_FILAMENTS = 0,
        DARK_FILAMENTS   = 1
    };

    /** Specification which part of a spatialgraph has changed */
    enum SpatialGraphChange {
        SpatialGraphTransformationChange = 1, /**< Global transform associated with the spatialGraph changed. */
        SpatialGraphGeometryChange = 2,       /**< Vertices/edges/points are added/removed/relocated. */
        SpatialGraphAttributeChange = 4,      /**< PointAttributes/EdgeVertexAttributes are added/removed. */
        SpatialGraphAttributeValueChange = 8, /**< Actual values in any PointAttribute/EdgeVertexAttribute have changed. */
        SpatialGraphLabelTreeChange = 16,     /**< Label tree has been added/removed or labels have been added to/removed from the tree). */
        SpatialGraphLabelChange = 32,         /**< The name or color of a label has been changed. */
        SpatialGraphParameterChange = 64,     /**< Parameters (in HxParamBundle) have changed. */
        SpatialGraphDataSetChange = 128       /**< Different HxSpatialGraph object */
    };

    /** Use QFlags for type-safe usage of combinations of
     *  HxNeuronEditorSubApp::SpatialGraphChange values.
     *  This introduces the new type HxNeuronEditorSubApp::SpatialGraphChanges
     *  for such values.
     */
    Q_DECLARE_FLAGS(SpatialGraphChanges, SpatialGraphChange)

    HxNeuronEditorSubApp();

    ~HxNeuronEditorSubApp();
    
    static HxNeuronEditorSubApp* instance();

    virtual void onStart();
    virtual void onStop();
    
    /// Tcl command interface
    virtual int parse(Tcl_Interp* interpreter, int argc, char **argv);

    /**
        Register a neuron editor tool.
        @param tool The tool to be registered
        @param toolbar The toolbar the tool's tool button should belong to.
        Note: If the toolbar of name \a toolBarName cannot be found
              a new toolbar named \a toolBarName will be inserted into the 
              neuron editor viewer panel toolbar section.
        @param insertBeforeTool The tool button where \a tool should be inserted before
        @see QxNeuronEditorTool
    */
    bool registerTool(QxNeuronEditorTool* tool, const char* toolBarName=0, const char* insertBeforeTool=0);
    /**
        Register a neuron editor toolbox.
        @param toolBox The toolbox to register
        @see QxNeuronEditorToolBox
    */
    bool registerToolBox(QxNeuronEditorToolBox* toolBox);

    /// the current active modal tool 
    QxNeuronEditorModalTool* activeModalTool() const;
    
    /// the current active spatial graph
    HxSpatialGraph* getSpatialGraph();

    /// Set the HxSpatialGraph to be edited.
    /// Note: \a graph must be in the object pool as it should appear in the
    /// combobox containing all graphs. 
    void setSpatialGraph(HxSpatialGraph* graph);

    HxSpatialGraphView* getView();
    HxObject* getImageData();
    
    const MPRPickingThresholds& pickingThresholds();

    /* Get highlight selection of current active spatialgraph*/
    const SpatialGraphSelection& getHighlightedElements();
    /* Get visible selection of current active spatialgraph*/
    const SpatialGraphSelection& getVisibleElements();

    /** Sets a new highlight selection for the current active spatialgraph
     *  This method updates the filament editor according to the new
     *  selection. The selection in the label tree is cleared.
     */
    void setHighlightedElements(const SpatialGraphSelection& sel);

    /* Sets a new visible selection for the current active spatialgraph
       NOTE: This operation keeps the filament editor consistent!
       e.g. a redraw will be triggered, the label tree visibility will 
       be updated etc.*/
    void setVisibleElements(const SpatialGraphSelection& sel);

    HxMPRViewer* getMPRViewer();
    HxSegmentMPRViewer* getSegmentMPRViewer();
    HxViewer* get3DViewer();
    
    // execute operation
    int execNewOp(Operation* op);
    
    // spatialgraph view node pick callback
    static void pickCB(void *userData, SoEventCallback* node);
    void pickCallback(SoEventCallback* node);
    
    /* Triggers an update of the viewer panel's toobars.
     * Enables or disables the tool buttons according to the 
     * result of HxViewerTool::supportsViewer().
     */
    void updateToolBars();

    /// update data window ui elements if data window has been changed interactively by window-level tool 
    void updateMPRDataWindowUI();

    void setInteractive(bool mode);

    //QxLabelTree* getLabelTree() { return mLabelTree; };

    float getImageDataMin();
    float getImageDataMax();
    
    float getAutoSkeletonThreshold();

    // returns the current global filament type
    FilamentType getFilamentType() { return mFilamentType; }

    void focusSelectionAtPickedPoint(McVec3f pickedPoint, int vertexIdx, int edgeIdx, SpatialGraphPoint pointIdx);

    void setMPRSegmentColorAttribute(const char* attributeName);
    void setMPRNodeColorAttribute(const char* attributeName);

    bool isValueInsideAllowedIntensityRange(float value);

public slots:
    /// trigger or modal tool enabled
    //void toolTriggered (QAction*);
    /// interactive mode enabled 
    //void viewingModeActivated(bool iFlag);
    
    /// spatialgraph data object changed
    void spatialGraphChanged(int idx);
    /// the image data object changed
    void imageDataChanged(int idx);

    /// label based selection changed
    void labelTreeSelectionChanged();

    /// mpr thickness
    void thicknessSliderChanged(int);
    void thicknessLineEditChanged();
    
    /// data range and colormap 
    void processDataRangeSlider(float vmin, float vmax);

    // volren alpha scale 
    void processAlphaScaleSlider(int inAlpha); 
    void processAlphaScaleTextEdit();

    // undo / redo functionality
    void undo();
    void redo();
    
    /// react on new image or graph data added to the object pool
    /// but only while the filament editor is active 
    /// e.g. Open Data... from the file menu has been triggered
    void slotObjectAddedSA(HxObject* object);

    /// react on pool changes 
    void slotObjectRemovedSA(HxObject* object);
    void slotObjectRenamedSA(HxObject* object, const char* old_name);
    
    /// react on image data which has been modified outside the filament editor
    void slotImageDataTouched(unsigned int mask);

    void createNewSpatialGraph();
    
    void slotNetworkIsLoading(bool state);

    // enable/disable rendering of the bounding box of the image date in 3d viewer
    void slotShowBoundingBox(bool);
    // enable/disable rendering of mpr slice in 3d 
    void slotShowThickSlice(bool);
    // enable/disable volume rendering
    void slotShowVolren(bool);
    
    /// color \a color for label with \a id of label group \a labelGroupName changed
    void labelColorChanged(McString labelGroupName, int id, McColor color);

    /// label name changed
    void labelNameChanged(McString labelGroupName, int id, const char* name);

    /// visibility changed 
    void visibilityChanged(McString labelGroupName, int labelId, bool state);

    /// slot called if label \a srcId has been swapped with label \a dstId 
    /// within a label group \a labelGroupName
    void labelRelocated(const McString &labelGroupName, int srcId, int dstId);

    /// slot called if a whole label group \a srcLabelGroupName has been swapped
    /// with \a dstLabelGroupName
    void labelGroupRelocated(const McString &srcLabelGroupName, const McString &dstLabelGroupName);

    /// Called to temporarily store (NO_SAVE) the collapsed state in the graph's param bundle.
    void setLabelCollapsed(QTreeWidgetItem* item);

    /// Called to temporarily store (NO_SAVE) the collapsed state in the graph's param bundle.
    void setLabelExpanded(QTreeWidgetItem* item);

    // vertex size in 2d viewer changed
    void traceNodeSizeSliderChanged(float);
    
    // line width size in 2d viewer changed
    void traceLineWidthSliderChanged(float size);

    // the filament characteristics changed
    // filament types can either be "bright on drak background"
    // or "dark on bright background"
    void slotFilamentTypeChanged(int);

    /** For internal use only!

        Triggered if a tool button contained by
        the toolbox toolbar has been clicked in order to
        switch the toolbox widget etc.
    */
    void slotToolBoxTriggered(QAction* action);

    /** This method ensures that the HxNeuronEditorSubApp updates itself
     *  after the HxSpatialGraph has been changed as specified by \a changes.
     *  It emits the \a spatialGraphChanged signal to allow tools and
     *  toolboxes to update themselves as well.
     *
     *  Note: When the HxSpatialGraph data set or its geometry have changed,
     *  as specified by \a changes, this method ensures that the resulting
     *  changes in visibility and in the selection are handled as well. This
     *  method sends the \a visibilityChanged and the \a selectionChanged
     *  signals in this case.  Any editor component or tool(box) changing the
     *  graph data set or its geometry should therefore only call this method
     *  (and not \a updateAfterSelectionChange() or \a
     *  updateAfterVisibilityChange());
     */
    void updateAfterSpatialGraphChange(HxNeuronEditorSubApp::SpatialGraphChanges changes);

    /** This method ensures that the HxNeuronEditorSubApp updates itself
     *  after imageData has been set to a new value.
     *  It emits the \a imageChanged signal to allow tools and
     *  toolboxes to update themselves as well.
     */
    void updateAfterImageChange();

    /** This method ensures that the HxNeuronEditorSubApp updates itself
     *  after the highlighting (selection) of the spatialGraph has changed.
     *  It emits the \a selectionChanged signal to allow tools and
     *  toolboxes to update themselves as well.
     */
    void updateAfterSelectionChange();

    /** This method ensures that the HxNeuronEditorSubApp updates itself
     *  after the visibility of the spatialGraph has changed.
     *  It emits the \a visibilityChanged signal to allow tools and
     *  toolboxes to update themselves as well.
     */
    void updateAfterVisibilityChange();

    /// Render volume and thick slice nodes in 3D viewer, by triggering
    /// \a renderCallback.
    void updateVolrenAndThickSliceIn3DViewer();
   
signals:
    /** This signal is emitted when the HxSpatialGraph has been changed, as
     * specified by \a changes. Components like tools and toolboxes should
     * connect to this signal, when they have to be updated after a
     * HxSpatialGraph change.
     */
    void spatialGraphChanged(HxNeuronEditorSubApp::SpatialGraphChanges);

    /** This signal is emitted when the image has been changed. Components
     *  like tools and toolboxes should connect to this signal, when they have
     *  to be updated after an image change.
     */
    void imageChanged();

    /** This signal is emitted when the current selection has been changed.
     *  Components like tools and toolboxes should connect to this signal, when
     *  they have to be updated after an selection change.
     */
    void selectionChanged();

    /** This signal is emitted when the graph visibility has been changed.
     *  Components like tools and toolboxes should connect to this signal, when
     *  they have to be updated after a visibility change.
     */
    void visibilityChanged();

public:

    HxViewerModalTool* mDefaultMPRTool;

    /// update label tree visibility checkboxes according to the
    /// visible selection (see getVisibleElements()) of the current spatialgraph view module.
    void updateLabelTreeVisibility();

    /// add new label to label group \a labelGroupName under label with id \a parentId
    void addNewLabel(const char* labelGroupName, int parentId);

    /// assign current selection to label with \a labelId of label group \a labelGroupName
    void assignSelection(const char* labelGroupName, int labelId);

    /// delete a label or label group if the id \a labelId is the root id
    void deleteLabel(const char* labelGroupName, int labelId);

    /// check if label group name \a labelGroupName is unique within SpatialGraph \a graph
    bool isLabelGroupNameUnique(HxSpatialGraph* graph, const McString& labelGroupName);
    /// fixup label group name \a labelGroupName if necessary, if not \a labelGroupName won't change
    void makeLabelGroupNameUnique(HxSpatialGraph* graph, McString& labelGroupName);

    /// add a new label group if bot \a onEdge \a onVertex is true to location GRAPH or if
    /// both are false to POINT
    void addLabelGroup(bool onEdge, bool onVertex);
    void addLabelGroup(HierarchicalLabels* hierarchicalLabel, bool onEdge, bool onVertex);

    /// Emphasises the labels in the label tree which are assigned to an edge or a vertex
    /// of the current selection.
    void highlightSelectionInLabelTree();

    /// id of the viewer which will be used by the neuron editor
    static const int SViewerId; 

    /// Initializes the combo box with the HxSpatialGraphs from the pool. If
    /// possible, the currently selected graph stays current, if not, the
    /// first graph found is made current. 
    void initGraphData();

    void getBoundingBox(SoGetBoundingBoxAction* action);

    /// Rebuild label tree in LabelTreeView
    void updateLabelTreeView();

    /** Redraw of the MPR viewer.
     *  It is public so it can be called by ExNotifier after using the zoom
     *  tool in the MPR viewer.
     */
    void renderMPRViewer();
    void renderSegmentMPRViewer();

    static const char* sSelectionToolbarName;
    static const char* sEditToolbarName;
    static const char* sUndoToolbarName;
protected:

    // enable/disable gui controls related to image data
    void enableImageDataControls(bool state);

    /** Update basic graph information at the bottom of the editor.
     *  It displays 1) number of visible nodes/segments, 2) total number of
     *  nodes/segments and 3) number of selected nodes/segments.
     */
    void updateInfoArea();

    /// Set the image data
    void setImageData(HxObject *mImageData);

    /// Updates the thickness slider according to the current image data
    void updateThicknessSlider();

    /// Handle mouse and escape key events for MPR viewer
    virtual bool eventFilter(QObject* object, QEvent *e);
    
    /// Create MPR viewer (derived from ExBaseViewer. see hxvisageviewer)
    void createMPRViewer();
    void createSegmentMPRViewer();

    /// Creates the HxSpatialGraphView 
    void createSpatialGraphView();

    /// Connects current graph to the HxSpatialGraphView
    void connectSpatialGraphView();

    /// init image data 
    void initImageData();
    /// set volume data on slice
    void initMPRViewer();
    void initSegmentMPRViewer();
    /// set volume data on volren
    void initVolren();
    /// wait for current rendering, remove requests from queue
    void stopRendering();

    /// load plugins
    void loadTools();

    /// Clears the undo stack
    void clearUndoStack();

    /// the editor gui
    Ui::QxNeuronEditor* mUi;  // Keep mUi above ui (see ctor).
    Ui::QxNeuronEditor& ui;
    QWidget* uiParent;
    
    /// the panel and viewer
    QxNeuronEditorViewerPanel* mPanel;
    HxViewer* mViewer;
    HxMPRViewer* mMPRViewer;
    HxSegmentMPRViewer* mSegmentMPRViewer;

    // toolbox related stuff
    QToolBar*       mToolboxToolBar;
    QStackedLayout* mToolboxLayout;
    QActionGroup*   mToolboxActionGroup;

    // The currently selected graph in the combo box.
    HxSpatialGraph *mCurrGraph;

    /// 3D graph viewer module
    McHandle<HxSpatialGraphView> mView;

    /// Currently used image data as selected by the image data combo box
    HxObject *mImageData;
    /// Flag indicating if the image data has been touched
    bool      mImageDataTouched;

    McHandle<VsSlice> mSlice;
    McHandle<VsSlice> mSegmentSlice;
    McHandle<HxBoundingBox> mImageBB;
    McHandle<VsVolren> mVolren;
    VsSpatialGraphRen *mVsSpatialGraph;
    VsSegmentRen *mSegmentVsSpatialGraph;

    // Undo/redo functionality
    McDArray<Operation*> mUndoStack;
    mclong mUndoPos;   

    // Build in toolboxes
    QxViewToolbox     *mViewToolbox;
    QxTracingToolbox  *mTracingToolbox;
    QxEditingToolbox  *mEditingToolbox;

    QxTraceTool    *mTraceTool;
    QxMoveTool     *mMoveTool;

    // visage viewer navigation tools
    McHandle<MPRRotateTool>      mMPRRotateTool;
    McHandle<MPRTranslateTool>   mMPRTranslateTool;
    McHandle<MPRZoomTool>        mMPRZoomTool;
    McHandle<MPRBrowseTool>      mMPRBrowseTool;
    McHandle<MPRPickTool>        mMPRPickTool;
    McHandle<MPRWindowLevelTool> mMPRWindowLevelTool;

    // trigger tools
    McHandle<MPRSetToHomeTool>  mMPRResetSliceTool;
    McHandle<MPRSaveHomeTool>   mMPRSetHomeTool;
    McHandle<MPRResetViewTool>  mMPRView_YZ_Tool;
    McHandle<MPRResetViewTool>  mMPRView_XY_Tool;
    McHandle<MPRResetViewTool>  mMPRView_XZ_Tool;
    
    /// This notifier is notified by MPR tools and triggers an
    /// update of the MPRviewer.
    ExNotifier *mMPRViewerNotifier;
    ExNotifier *mSegmentMPRViewerNotifier;

    /// Observes \a mSlice. Triggers a call to \a
    /// updateVolrenAndThickSliceIn3DViewer when \a mSlice is modified.
    McHandle<VsNotifier> mSliceNotifier;
    McHandle<VsNotifier> mSegmentSliceNotifier;

    // undo/redo tools
    McHandle<UndoTool> mUndoTriggerTool;
    McHandle<RedoTool> mRedoTriggerTool;
   
    /// Enables/disables rendering of thick slice in 3D viewer
    bool mShowThickSliceIn3DViewer;
    bool mShowVolren;  // enable/disable volume rendering in render callback
    bool mVolrenForceLowRes; // force volren to render low resolution only 

    /// Enables/disables rendering of the bounding box of the image data in 3D viewer
    bool mShowImageBoundingBoxIn3DViewer;

    /// OIV callback to render volren and thick slice nodes in 3D viewer.
    McHandle<SoCallback> mSoCallback;
    static void renderCallback(void* userData, SoAction* action);

    /** Renders thick slice displayed in the MPR viewer as a single image
     *  slice in the 3D viewer. The image bounding box (orange lines), the
     *  current bounding box in the MPR viewer (orange stippled lines) and the
     *  currently displayed plane in the MPR viewer (yellow lines) are also
     *  displayed in the 3D viewer. */
    void renderThickSliceIn3DViewer();

    /** Renders volume rendering in 3D window.
     *  If \a interactive is true, a low-resolution version is rendered to
     *  allow for interaction.
     */
    void renderVolren(bool interactive);

    // helper function in order to update volren's data window
    // with respect to the filament type, where in case of 
    // dark filaments the colormap has to be inverted
    void updateVolrenDataWindow();

    /// Renders the SpatialGraphViewer in the 3D window
    void renderSpatialGraphViewer();

    /// Renders the bounding box of the image data in the 3D window
    void renderImageBoundingBoxIn3DViewer();

    /** Avoids the line edit text to be set to a slightly different value
     *  after a value has been typed. 
     *  Explanation:
     *  After typing a number in line edit, the \a thicknessLineEditChanged
     *  slot calls the \a thicknessSliderChanged slot. The latter sets the
     *  line edit text again, but to a slightly different number (due to
     *  floating point precision issues). This variable avoids setting the
     *  line edit text by the \a thicknessSliderChanged slot.*/
    bool wMPRThicknessLineEditNoTextFieldAdjust;

    friend class UndoTool;
    friend class RedoTool;

    // indicates if a network is currently loading
    bool mNetworkIsLoading;

    /** Computes the polygon representing the projection of the current
     *  contents of the MPR viewer projected onto the plane containing the
     *  current slice. The polygon points are in 3D world coordinates.
     *  This function is a helper function for computing the bounding box and
     *  for displaying the thick slice in the 3D viewer.
     */
    void computeViewPolygonVerticesIn3d(McDArray<McVec3f>& result);

    /** Sets the center of rotation of the mMPRRotateTool to the selected
     *  point or vertex, but only when exactly one point or vertex of the
     *  SpatialGraph is selected. 
     */
    void setMPRRotateToolRotationCenter();

    enum SizeLimits {
          SL_MIN_TOOLBOX_FRAME_HEIGHT = 180,
          SL_MIN_TOOLBOX_FRAME_WIDTH = 150
    };

    FilamentType mFilamentType;
    
    /** Configure rendering of decoration for slice. See VsSlice::Decoration for details on how to set the mask.
    */
    void setDecorationRendering(int mask);
    void setSegmentDecorationRendering(int mask);
    
    /** Sets the interpolation filter for rendering of slice. See VsSlice::Filter for possible options.
    */
    void setSliceInterpolationFilter(int filter);
    
    /** Sets the interpolation filter for extracting the slice from the volume. See VsSlice::Filter for possible options.
    */
    void setSliceExtractionFilter(int filter);

    MPRPickingThresholds* mPickingThresholds;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(HxNeuronEditorSubApp::SpatialGraphChanges)

#define theNeuronEditor HxNeuronEditorSubApp::instance()

#endif // HX_NEURONEDITOR_SUBAPPLICATION_H


/// @}
