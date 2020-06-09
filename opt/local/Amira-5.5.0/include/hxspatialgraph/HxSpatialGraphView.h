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

/// @addtogroup hxspatialgraph hxspatialgraph
/// @{
#ifndef HX_SPATIALGRAPHVIEW_H
#define HX_SPATIALGRAPHVIEW_H

#include "hxspatialgraphAPI.h"
#include "SpatialGraphSelection.h"
#include "HxSpatialGraphSelectionInterface.h"
#include "SpatialGraphViewNode.h"
#include <hxcore/HxModule.h>
#include <hxcolor/HxPortColormap.h>
#include <hxvertexset/SoSphereSet.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortSeparator.h>
#include <mclib/McHandle.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoCallback.h>
#include <hxcore/HxPortColorList.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcolor/HxRangeSet.h>

class HxSpatialGraphInterface;
class HxSpatialGraphEditor;
class HxSpatialGraphEditor2;
class QxSpatialGraphNotifier;
class HxSpatialGraphSelectionInterfaceImpl;
class HxViewerLegend;

class HXSPATIALGRAPH_API HxSpatialGraphView : public HxModule
{
    HX_HEADER(HxSpatialGraphView);

private:
    class HxRangeSetModuleImpl : public HxRangeSetModule {
      public:
        HxRangeSetModuleImpl(HxSpatialGraphView* o)
            : HxRangeSetModule(o->getOwner(), McInterfaceOwner::STATIC_IFACE)
            , mOuter(o)
        {}

        /** Returns the current data set encoded as described at HxSpatialGraph::getRangeSet().
            Returns -1 if there is no current data set selected. */
        virtual int getCurrentSet(const HxData* data, const HxPortColormap& colormap) const;

      private:
        HxSpatialGraphView* mOuter;
    };

public:

    friend class HxSpatialGraphSelectionInterfaceImpl;

    HxSpatialGraphView();
    virtual ~HxSpatialGraphView();

    virtual void compute();
    virtual void update();

    /// Tcl command interface
    virtual int parse(Tcl_Interp* interpreter, int argc, char **argv);

    /// Save state method.
    virtual void savePorts(FILE* fp);

    /**** Common ports ****/

    /// Input for optional statistics spreadsheet.
    HxConnection     mPortStatistics;

    /// Toggle visibility of vertices, edges and edge points
    HxPortToggleList portItemsToShow;

    /**** Node ports ****/
    HxPortSeparator portSeparator1;

    /// Scaling of vertex data
    HxPortMultiMenu portVertexScaling;

    /// Scaling factor for vertices
    HxPortFloatSlider portVertexScaleValue;

    /// How to color vertices
    HxPortMultiMenu portVertexColoring;

    /// Coloring options of vertex data for labels
    HxPortRadioBox portVertexLabelColoringOptions;

    /// Coloring of vertex data
    HxPortColormap portVertexColormap;

    /// Coloring of vertex data for the Constant option
    HxPortColorList portVertexConstantColor;

    /**** Segment ports ****/
    HxPortSeparator portSeparator2;

    /// style of segment rendering (e.g lines, points or tubes)
    HxPortToggleList portSegmentStyle;

    HxPortMultiMenu portSegmentScaling;

    HxPortFloatSlider portSegmentScaleValue;

    HxPortFloatSlider portSegmentWidth;

    /// How to color edges
    HxPortMultiMenu portEdgeColoring;

    /// Coloring options of edge data for labels
    HxPortRadioBox portEdgeLabelColoringOptions;

    /// Coloring of edge data
    HxPortColormap portEdgeColormap;

    /// Coloring of edge data for the Constant option
    HxPortColorList portEdgeConstantColor;

    HxPortFloatSlider portPointSize;

public:

    void rebuildSceneGraph();

    void redraw();

    const SpatialGraphSelection& getHighlightedElements() const { return highlightedElements; }
    const SpatialGraphSelection& getVisibleElements()     const { return visibleElements; }

    void setHighlightedElements(const SpatialGraphSelection &sel) { highlightedElements = sel;}
    void setVisibleElements(const SpatialGraphSelection &sel)     { visibleElements = sel; }

    const QxSpatialGraphNotifier* getNotifier();
    void setPickCallback(void (*)(void*,SoEventCallback* node), void *userData);

    const SpatialGraphViewNode* getSpatialGraphViewNode() const {return graphViewNode; }

    void renderHighlightedElements(bool blockSpreadSheetSelection = false);

    /// Checks if the attached graph has a label attribute with name \a
    /// attribName defined at location \a attribLocation.
    bool isLabelGroupAttribute(const char* attribName, HxSpatialGraph::Location attribLocation);

    /// Set width of edges rendered as lines.
    void setLineWidth(const float width);

    void setPointSize(const float pointSize);

    void setTransparency(const float transp);

protected:
    HxSpatialGraphInterface* graph;
    McHandle<SoSeparator> scene;
    McHandle<SpatialGraphViewNode> graphViewNode;
    QxSpatialGraphNotifier *notifier;

    SpatialGraphSelection highlightedElements;
    SpatialGraphSelection visibleElements;

    /// Event callback.
    McHandle<SoEventCallback> eventCallback;

    /// Legend and event callback to show info on picked point
    HxViewerLegend *mPickQueryLegend;
    McHandle<SoEventCallback> mPickQueryCallback;
    static void pickQueryCallback(void *userData, SoEventCallback *node);
    void setPickQueryInfo(const SoPickedPoint *pickedPoint);

    McHandle<HxColormap> edgeColormap;
    McHandle<HxColormap> vertexColormap;

    // use colormap even if label colors could be used
    bool useColormapOnSegmentLabels;
    bool useColormapOnNodeLabels;

    void setColoring();

    // callback to set the full bounding box of the a spatialgraph
    // e.g. with respect to the underlying image data
    McHandle<SoCallback> mSoCallback;
    static void renderCallback(void* userData, SoAction* action);

private:

    void showVertices(const bool show);
    void showEdges(const bool show);

    void showLines(bool inFlag);
    void showPoints(bool inFlag);

    void showTubes(bool inFlag);
    bool mUseLegacyTubeRendering;

    // get \a visibleElements edge and vertex bitfield content
    // compressed as string containing only letters [A-Z].
    // The edge and vertex strings are separated by a space ' ' character.
    void getVisibility(McString& visibility);

    HxSpatialGraphSelectionInterfaceImpl* mSelectionIface;

    HxRangeSetModuleImpl mRangeSetModule;

    float mLineWidth;
    float mPointSize;
    float mTransparency;
};

class HxSpatialGraphSelectionInterfaceImpl : public HxSpatialGraphSelectionInterface
{
    HX_HEADER (HxSpatialGraphSelectionInterfaceImpl);
public:

    HxSpatialGraphSelectionInterfaceImpl (HxSpatialGraphView* view) {
        setOwner(view);
        mView = view;
    }

    const SpatialGraphSelection& getHighlightSelection() const
    {
        return mView->highlightedElements;
    }

private:
    HxSpatialGraphSelectionInterfaceImpl(){};

    HxSpatialGraphView* mView;
};

#endif

/// @}
