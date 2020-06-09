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
#ifndef SPATIALGRAPHFUNCTIONS_H
#define SPATIALGRAPHFUNCTIONS_H

#include "hxspatialgraphAPI.h"
#include "SpatialGraphSelection.h"
#include <mclib/McDArray.h>
#include <mclib/McVec3f.h>
#include <mclib/McBox3f.h>
#include <Inventor/SbLinear.h>

class HxSpatialGraph;
class HierarchicalLabels;
class HxSpatialGraphInterface;

namespace NodeType {
    enum Enum {ISOLATED, TERMINAL, INTERMEDIATE, BRANCHING};
};


namespace SpatialGraphFunctions {

    HXSPATIALGRAPH_API int removeContours(HxSpatialGraph* graph);
    HXSPATIALGRAPH_API bool isContour(const HxSpatialGraph* graph, const int edge);
    HXSPATIALGRAPH_API bool isContourVertex(const HxSpatialGraph* graph, const int vertex);
    HXSPATIALGRAPH_API float getEdgeLength(const HxSpatialGraph* graph, const int edge);
    HXSPATIALGRAPH_API float getTransformedEdgeLength(const HxSpatialGraph* graph, const int edge);
    HXSPATIALGRAPH_API void resampleWithMaximumPointDistance(HxSpatialGraph* graph, 
                                                                  const float maxPointDistance);
    HXSPATIALGRAPH_API McDArray<int> getBranchingNodes(const HxSpatialGraph* graph);
    HXSPATIALGRAPH_API McDArray<int> getEndingNodes(const HxSpatialGraph* graph);

    HXSPATIALGRAPH_API bool isBranchingNode(const HxSpatialGraph* graph, const int vertex);
    HXSPATIALGRAPH_API bool isEndingNode(const HxSpatialGraph* graph, const int vertex);

    HXSPATIALGRAPH_API NodeType::Enum getNodeType(const HxSpatialGraph* graph, const int vertex);

    HXSPATIALGRAPH_API int getNumberOfNodesOfTypeInSelection(const HxSpatialGraph* graph,
                                                             const SpatialGraphSelection& selection,
                                                             const NodeType::Enum nodeType);

    HXSPATIALGRAPH_API SpatialGraphSelection getVerticesWithLabelId(const HxSpatialGraph* graph,
                                                                         const char* attributeName,
                                                                         const int labelId);
    HXSPATIALGRAPH_API SpatialGraphSelection getEdgesWithLabelId(const HxSpatialGraph* graph,
                                                                      const char* attributeName,
                                                                      const int labelId);
    HXSPATIALGRAPH_API SpatialGraphSelection getEdgesAndVerticesWithLabelId(const HxSpatialGraph* graph,
                                                                                 const char* attributeName,
                                                                                 const int labelId);

    /// Returns the points of edge \a edgeNum transformed with the transform
    /// associated with \a graph.
    HXSPATIALGRAPH_API McDArray<McVec3f> getTransformedEdgePoints(const HxSpatialGraphInterface* graphInterface, 
                                                                       const int edgeNum);
    HXSPATIALGRAPH_API McBox3f getTransformedEdgeBoundingBox(const HxSpatialGraphInterface* graphInterface, 
                                                                  const int edgeNum);

    HXSPATIALGRAPH_API McVec3f getTransformedPoint(const HxSpatialGraph* graph, 
                                                        const McVec3f);

    HXSPATIALGRAPH_API McVec3f getTransformedPoint(const SbMatrix& matrix, 
                                                        const McVec3f);

    HXSPATIALGRAPH_API McBitfield getLabelIdsInSubTree(const HierarchicalLabels* labels,
                                                            const McString& subTreeRootName);

};

#endif


/// @}
