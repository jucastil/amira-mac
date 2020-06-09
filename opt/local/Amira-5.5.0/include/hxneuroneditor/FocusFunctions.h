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
#ifndef FOCUSFUNCTIONS_H
#define FOCUSFUNCTIONS_H 

#include <hxspatialgraph/HxSpatialGraph.h>

#include "hxneuroneditorAPI.h"
#include "HxMPRViewer.h"

class HXNEURONEDITOR_API FocusFunctions
{
public:
    enum EdgeEndType
    {
        EDGE_SOURCE = 0,
        EDGE_TARGET = 1
    };

    /// Focus a given point in world coordinates in MPR-Viewer. Retain the slice orientation.
    static bool focusPointInMPRViewer(HxMPRViewer* const viewer, const McVec3f& focusPoint);

    /** Focus a given point in world coordinates in MPR-Viewer and adapt slice orientation to the given element.
     *  For slice orientation adaption see focusVertexInMPRViewer(), focusEdgeAtPointInMPRViewer() and
     *  focusEdgePointInMPRViewer().
     *  Note: Only one element can be forwarded via SpatialGraphSelection (edge point, edge or vertex).
     */
    static bool focusPointInMPRViewerAndAdaptSliceOrientation(HxMPRViewer* const viewer,
                                                              const HxSpatialGraph* const graph,
                                                              const McVec3f& focusPoint,
                                                              const SpatialGraphSelection& element,
                                                              const McVec3f& voxelSize = McVec3f(0.0));

    /** Focus a vertex in MPR-Viewer.
     *  If the vertex is an end of exactly one edge, then, optionally, the slice orientation
     *  of the MPR-Viewer can be adapted to the orientation of the edge at this end.
     */
    static bool focusVertexInMPRViewer(HxMPRViewer* const viewer,
                                       const HxSpatialGraph* const graph,
                                       const int vertexIdx,
                                       const bool adaptSliceOrientation = false,
                                       const McVec3f& voxelSize = McVec3f(0.0));

    /** Focus an edge source or edge target in MPR-Viewer.
     *  Optionally, the slice orientation of the MPR-Viewer can be adapted
     *  to the orientation of the edge at the edge source.
     */
    static bool focusEdgeEndInMPRViewer(HxMPRViewer* const viewer,
                                           const HxSpatialGraph* const graph,
                                           const int edgeIdx,
                                           const FocusFunctions::EdgeEndType edgeEndType,
                                           const bool adaptSliceOrientation = false,
                                           const McVec3f& voxelSize = McVec3f(0.0));

    /** Focus an edge at a given point in MPR-Viewer.
     *  Optionally, the slice orientation of the MPR-Viewer can be adapted
     *  to the orientation of the edge at this point.
     */
    static bool focusEdgeAtPointInMPRViewer(HxMPRViewer* const viewer,
                                            const HxSpatialGraph* const graph,
                                            const int edgeIdx,
                                            const McVec3f& focusPoint,
                                            const bool adaptSliceOrientation = false,
                                            const McVec3f& voxelSize = McVec3f(0.0));

    /** Focus an edge point in MPR-Viewer.
     *  Optionally, the slice orientation of the MPR-Viewer can be adapted
     *  to the orientation of the edge at this edge point.
     */
    static bool focusEdgePointInMPRViewer(HxMPRViewer* const viewer,
                                          const HxSpatialGraph* const graph,
                                          const SpatialGraphPoint& point,
                                          const bool adaptSliceOrientation = false,
                                          const McVec3f& voxelSize = McVec3f(0.0));

private:
    static void setMPRViewerSliceToPlane(HxMPRViewer* const viewer, const McPlane& slicePlane);

    static void setMPRViewerCamera(HxMPRViewer* const viewer,
                                   const McVec3f& camLookFrom,
                                   const McVec3f& camLookTo,
                                   const McVec3f& camLookUp,
                                   const McVec3f& voxelSize);

    static bool getPointsForNewSlicePlane(const HxSpatialGraph* const graph,
                                          const float minDist,
                                          const float worldTolerance,
                                          const int edge,
                                          const McVec3f& pos,
                                          McVec3f points[3]);

    static bool getPointsForNewSlicePlane(const HxSpatialGraph* const graph,
                                          const float minDist,
                                          const SpatialGraphPoint& point,
                                          McVec3f points[3]);

    static bool getPointsAtEdgeEndForNewSlicePlane(const HxSpatialGraph* const graph,
                                                   const float minDist,
                                                   const int edge,
                                                   const EdgeEndType edgePointType,
                                                   McVec3f points[3]);

    static bool getPointsOnEdgeForPlane(const McDArray<McVec3f>& edgePoints,
                                        const float minDist,
                                        const float worldTolerance,
                                        const McVec3f& pos,
                                        McVec3f points[2]);

    static bool getPointsOnEdgeForPlane(const McDArray<McVec3f>& edgePoints,
                                        const int pointNum,
                                        const float minDist,
                                        McVec3f points[2]);

    static bool getPointsOnEdgeAtEdgeEndForPlane(const McDArray<McVec3f>& edgePoints,
                                                 const float minDist,
                                                 const EdgeEndType edgeEndType,
                                                 McVec3f points[2]);

    /// Calculate the third point to span a plane
    static const McVec3f getThirdPointForPlane(const McVec3f points[2]);

    static const McVec3f getLookFrom(const McVec3f& lookTo, const McVec3f& orientation, const float minDist);
    
    static const McVec3f getLookUp(const McVec3f& point1, const McVec3f& point2, const McVec3f& camPos);

};

#endif


/// @}
