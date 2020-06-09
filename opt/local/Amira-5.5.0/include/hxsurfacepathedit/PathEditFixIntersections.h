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

/// @addtogroup hxsurfacepathedit hxsurfacepathedit
/// @{
#ifndef PATHEDIT_FIX_INTERSECTIONS_H
#define PATHEDIT_FIX_INTERSECTIONS_H

#include <hxsurfacepathedit/SinglePathOperation.h>

#include <mclib/McBitfield.h>
#include <mclib/McDArray.h>

/** This operation finds all checks for intersection of paths in more
    than one point, i.e., if linesegments of paths overlap.  The paths
    are split at these intersections and new paths are build that do
    not overlap.  The algorithm tries to keep the longest paths in one
    piece.
*/
class HXSURFACEPATHEDIT_API PathEditFixIntersections : public SinglePathOperation
{
    MC_ABSTRACT_HEADER(PathEditFixIntersections);

public:

    /// Helper class.
    class GraphSurfaceNode
    {
    public:

        SurfaceNode* node;
        McDArray<int> paths;
        McDArray<GraphSurfaceNode*> in_out_nodes;
        bool used;

        /// Constructor.
        GraphSurfaceNode(SurfaceNode* node)
        {
            this->node=node;
            used=false;
        }
    };

    /// Constructor.
    PathEditFixIntersections(SurfacePathSet* pS, SelectionInfo* sel, bool smoothPaths=true);

    /// Constructor.
    PathEditFixIntersections(SurfacePathSet* pS, SelectionInfo* sel, const McDArray<int>& selPath, bool smoothPaths=true);

    /// Destructor.
    ~PathEditFixIntersections(){};

    /// Set tolerance distance within which two nodes are considered
    /// as being equal.
    void setTolerance(float tol) { mTol=tol; }

protected:

    /** Update path set according to the operation that has been
        carried out.  Returns always true. */
    virtual bool updatePathset();

    /// The path set to be fixed.
    SurfacePathSet* pathSet;

    /// The paths in @c pathSet to be fixed.
    McDArray<int> selectedPaths;

    /// If @c smoothP is smooth, the path will be smoothed.
    bool smoothP;

    /// Tolerance.
    float mTol;

    /// Helper data struct.
    McDArray <GraphSurfaceNode* > graph;

    /// Build up @c graph.
    void buildGraph();

    /// Get the first found node that was not used yet.
    GraphSurfaceNode* getUnmarkedStartNode();

    void dfs(GraphSurfaceNode* prev, McDArray<int>& actPath,McDArray<SurfacePathSet::SurfacePath*>& newPaths);
    void buildNewPathSet(McDArray<SurfacePathSet::SurfacePath*>&);
    bool isPathInArray(SurfacePathSet::SurfacePath* path,McDArray<SurfacePathSet::SurfacePath*>paths);
    void smoothPaths(McDArray<SurfacePathSet::SurfacePath* >& paths);
    bool startNewPathAt(GraphSurfaceNode* last,GraphSurfaceNode* next);
    bool pathStartsHere(McDArray<int> path);
    bool pathEndsHere(GraphSurfaceNode* last,GraphSurfaceNode* next);
    int getLongestPath(const McBitfield& mbf);
    void patchPaths(int path,McDArray<SurfacePathSet::SurfacePath*>& paths,McDArray<SurfacePathSet::SurfacePath*>& newPaths);
    SurfacePathSet::SurfacePath* createNewSurfacePath(McDArray<int> path);
    void createBitfieldForSelectedNodes(McBitfield& selectedNodes);
    void createSelectedPathsSet(SurfacePathSet& newPS);
    void deleteSelectedPaths();
    void copyFixedPathsBack(SurfacePathSet& selectedPathsSet);

private:

    McDArray<McDArray<bool> > adjMat;
};

#endif

/// @}
