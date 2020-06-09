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
#ifndef SPATIALGRAPHVIEWNODE_H
#define SPATIALGRAPHVIEWNODE_H

#include "hxspatialgraphAPI.h"
#include "HxSpatialGraphInterface.h"

#include "SpatialGraphSelection.h"

#include <mclib/McHandable.h>
#include <mclib/McHandle.h>
#include <mclib/McVec3f.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoPointSet.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/SbColor.h>

#include <hxvertexset/SoSphereSet.h>
#include <hxcolor/HxPortColormap.h>

class HxSpatialGraphInterface;
class HxColormap256;
class PointAttribute;

class SoTubeSet;

class HXSPATIALGRAPH_API SpatialGraphViewNode : public McHandable {
public:

    SpatialGraphViewNode();
    ~SpatialGraphViewNode();
    SpatialGraphViewNode(HxSpatialGraphInterface* g);

    void setSpatialGraphInterface(HxSpatialGraphInterface* g);
    SoSeparator* getSpatialGraphNode();

    /// Renders the edges of the spatial graph.
    /// The set of edges to be rendered can be restricted by providing a SpatialGraphSelection (only the edges of the selection are considered)
    void makeLines(const SpatialGraphSelection *sel);
    void removeLines();
    void setLineColor(const SpatialGraphSelection *sel, const GraphAttribute* colorAttribute, bool useColormapOnLabels = false);

    void makeHighlightedLines(const SpatialGraphSelection *sel, const SpatialGraphSelection *visibleSel);
    void removeHighlightedLines();

    /// Renders the vertices of the spatial graph.
    /// The set of vertices to be rendered can be restricted by providing a SpatialGraphSelection (only the vertices of the selection are considered)
    void makeVertices(const SpatialGraphSelection *sel);
    void removeVertices();
    void setVertexColor(const SpatialGraphSelection *sel, const EdgeVertexAttribute* colorAttribute, bool useColormapOnLabels = false);
    void setVertexScale(const SpatialGraphSelection *sel, const EdgeVertexAttribute* scaleAttribute, float scale);

    void makeHighlightedVertices(const SpatialGraphSelection *sel, const SpatialGraphSelection *visibleSel);
    void removeHighlightedVertices();

    /// Renders the geometry points defined on the edge
    void makePoints(const SpatialGraphSelection *sel);
    void removePoints();
    void setPointsColor(const SpatialGraphSelection *sel, const GraphAttribute *attrib, bool useColormapOnLabels = false);
    void setPointSize(const float pointSize);

    void makeHighlightedPoints(const SpatialGraphSelection *sel);
    void removeHighlightedPoints();

    /// Renders edges with tube style (legacy mode)
    void makeTubes( const SpatialGraphSelection *sel,
                    const GraphAttribute *colorAttribute,
                    const PointAttribute *scaleAttribute,
                    float scaleFactor,
                    bool useColormapOnLabels = false);

    void removeTubes();

    /// Renders edges with tube style (VBO + Shaders)
    void makeTubes2(const SpatialGraphSelection *sel);
    void removeTubes2();
    void makeHighlightedTubes(const SpatialGraphSelection *highlightSel, const SpatialGraphSelection *visibleSel);

    void setTubeScaleFactor(float scale);
    void setTubeScaleAttribute(const PointAttribute* thicknessAttribute);
    void setTubeColorAttribute(const GraphAttribute* colorAttribute);

    void setTubeColormapDataWindow(float min, float max);
    void setTubeColormap(HxColormap* inColormap);
    void setTubeConstantColor(const McColor& inColor);

    /// colormaps
    void setEdgeColormapPort(const HxPortColormap* cmp);
    void setVertexColormapPort(const HxPortColormap* cmp);

    /// transformation
    void setTransform (SoTransform* trans);
    SoTransform* getTransform();

    bool getPickedElement( const SpatialGraphSelection *visibleElements,
                           const SpatialGraphSelection *highlightedElements,
                           const SoPickedPoint* pickedPoint,
                           int& vertexId,
                           int& edgeId,
                           SpatialGraphPoint& pointId
                           ) const;

    void setVertexDefaultColor(const SbColor color);
    void setEdgeDefaultColor(const SbColor color);
    void setHighlightColor(const SbColor color);
    void setTransparency(const float transp) {transparency = transp;}

    void setLineWidth(const float width);
    float getLineWidth() const;

protected:

    HxSpatialGraphInterface* graph;

    McHandle<SoSeparator> graphSep;
    McHandle<SoTransform> transform;
    McHandle<SoSeparator> edgesSep;
    McHandle<SoSeparator> highlightedEdgesSep;
    McHandle<SoSeparator> verticesSep;
    McHandle<SoSeparator> edgePointsSep;
    McHandle<SoSeparator> highlightedEdgePointsSep;
    McHandle<SoSeparator> tubesSep;
    McHandle<SoSeparator> tubesSep2;
    McHandle<SoDrawStyle> drawStyle;
    McHandle<SoDrawStyle> mPointDrawStyle;

    McHandle<SoLineSet> lineSet;
    McHandle<SoLineSet> highlightedLineSet;
    McHandle<SoSphereSet> sphereSet;
    McHandle<SoPointSet> pointSet;
    McHandle<SoPointSet> highlightedPointSet;
    SoTubeSet *tubeSet;

    const HxPortColormap* vertexColormap;
    const HxPortColormap* edgeColormap;

    static void initRandomColormap();
    static HxColormap256* randomColormap;

    void createColorTable(const GraphAttribute* att, McHashTable<int, SbColor>& table);

    void init();
    int getOrtho(int iEdge, int closed, McVec3f** pn, McVec3f** pb);
    void renderLines(const SpatialGraphSelection *sel, SoLineSet* lines);
    void renderPoints(const SpatialGraphSelection *sel, SoPointSet* pSet);

    SbColor edgeDefaultColor;
    SbColor vertexDefaultColor;
    SbColor defaultUnknownColor; // Use for unknown label values or other unexpected problems
    SbColor highlightColor;
    float lineWidth;
    float transparency;

    McDArray< McVec3f > OrthoNormalsArray;
    McDArray< McVec3f > OrthoBinormalsArray;
    McDArray< McVec3f > OrthoUnitVectorsArray;

    McDArray< McVec3f > MTPointsArray;
    McDArray< int >     MTCoordIdxArray;
    McDArray< float >   MTColorArray;
    McDArray< int >     MTMatIdxArray;

    int getPointIndex(const int edgeIdx, const int pointIdx, const SpatialGraphSelection *sel);
};

#endif

/// @}
