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

/// @addtogroup hxsurfacepath hxsurfacepath
/// @{
#ifndef PATH_ENTANGLER_H
#define PATH_ENTANGLER_H

#include "SurfaceNode.h"
#include <mclib/McDArray.h>
#include <mclib/McHandle.h>
#include <mclib/McHandable.h>
#include <mclib/McVec2f.h>
#include <mclib/McBitfield.h>
#include "SurfacePathSet.h"

/** Finds all intersections including self-intersections in a 
    @c SurfacePathSet and adds the nodes corresponding to an
    intersection.  Entangled paths have no duplicate nodes, so if two
    paths cross, they point to the same node on the point of
    intersection.  If this node is deleted, it is deleted for all
    paths, the same goes for a move-operation.
*/
class HXSURFACEPATH_API PathEntangler 
{

public: 
    /// Forward declaration of Segment.
    class Segment;

    /// Constructor.
    PathEntangler(SurfacePathSet* pS, float tolerance=1.e-3,
                  bool insertControlPoints=true);

    /// Constructor.
    PathEntangler(SurfacePathSet* pS, const McDArray<int>&selP, 
                  float tolerance=1.e-3, bool insertControlPoints=true);

    /// Destructor.
    virtual ~PathEntangler(void);

    /// Starts computation.
    virtual bool compute();

    //int checkIfIntersections();


    /// Represents all segments of paths, that belong to one triangle.
    class TriangleSegments{
    public:
        /// All segments of paths, that belong to that triangle.
        McDArray<PathEntangler::Segment*> segments;

        ~TriangleSegments()
        {
            segments.clear();
        }
    };

    /// Represents a single segment of one path.
    class Segment : public McHandable
    {

    public:
        /// Constructor.
        Segment()
        {
            last=NULL;
            next=NULL;
        }

        /// Start node.
        int begin;

        /// End node.
        int end;

        /// The path, this segment belongs to.
        int pathID;

        /// Index of startnode in path.
        int indexInPath;
        
        /// All triangles, this segment belongs to.  A segment belongs
        /// to more than one triangle, if it lies on an edge.  If it
        /// only ends on an edge, it only belongs to the triangle it
        /// crosses.
        McDArray<int> tris;

        /// Pointer to segment before this one.
        PathEntangler::Segment* next;

        /// Pointer to segment after this one in path.
        PathEntangler::Segment* last;
    };

    /// Represents an intersection.
    class Intersection
    {

    public:
        Intersection()
        {
            intersected=false;
            segment=NULL;
            intersectedNode=-1;
        }
        
        /// Internal flag.
        bool intersected;

        /// Pointer to segment.
        PathEntangler::Segment* segment;

        /// Index of intersected node.
        int intersectedNode;
    };

private:
    /** Array with a TriangleSegments for each triangle that has a
        segment belonging to it.  If a triangle is not touched by a
        path, the place in the array at index triangleID is NULL.
    */
    McDArray<PathEntangler::TriangleSegments*> allTriangles;
    McDArray<McHandle<PathEntangler::Segment> > startSegments;

    McDArray<int> selectedPaths;

    void createBitfieldForSelectedNodes(McBitfield& selectedNodes);

    float mTolerance;

    /// Decides whether controlPoints or normal nodes are inserted on
    /// crossings.
    bool insertControlPoints;

    /// Initialises allTriangles array.
    void initSegments();

    /// Handles entangling for one triangle (returns number of splits).
    int entangleTS(PathEntangler::TriangleSegments*ts);

    /// Returns the edge if both nodes lie on one edge, -1 otherwise.
    int lieOnSameEdge(SurfaceNode* node1, SurfaceNode* node2);

    /// Checks similar Nodes and entangles these.
    void entangleSimilarNodes(PathEntangler::TriangleSegments*ts);

    /// Splits a path-segment at node of intersection.
    PathEntangler::Segment* splitSegment(PathEntangler::Segment* seg, 
                                         PathEntangler::Intersection intersection);

    /// Adds the new segment seg to all adjacent triangles.
    void appendSegmentToTriangles(PathEntangler::Segment* seg);

    /// Reconstructs path.
    void reconstructPaths(void);

    /// Computes path starting from @c startSeg.
    void computePath(PathEntangler::Segment* startSeg,SurfacePathSet::SurfacePath& path);

    /// Intersects segments @c s1 and @c s2.  The intersections are
    /// stored in @c i1 and @c i2.
    bool intersectSegments(PathEntangler::Segment      * s1,
                           PathEntangler::Segment      * s2,
                           PathEntangler::Intersection * i1,
                           PathEntangler::Intersection * i2);

    /// Returns common triangle of segment @c s1 and @c s2.
    int getCommonTriangle(PathEntangler::Segment* s1,PathEntangler::Segment*s2);

    /// Creates a node depending on whether the new node lies on an
    /// edge or within a triangle.
    SurfaceNode* createSurfaceNode(PathEntangler::Segment* seg,float lambda);

    /// Projects points of segments @c s1 and @c s2 into 2-dimensional plane.
    int projectTo2d(PathEntangler::Segment*s1,
                    PathEntangler::Segment*s2,
                    McVec2f& p1,
                    McVec2f& q1,
                    McVec2f& p2,
                    McVec2f& q2);

    /** Returns either @c node1 or @c node2.  The function first
        checks whether one of the nodes is a vertex node.  If so, it
        is returned.  If no node is a vertex node, the function checks
        whether a node is an edge node.  If so, it is returned.  If
        the nodes have the same type, @c node1 is returned.
    */
    int getPriorNode(int node1,int node2);
    
    /** Checks whether any of the begin or end nodes of @c s1 and
        @c s2 are within a certain tolerance to each other.  If so, they
        are set the same node.
    */
    void trimmSegments(PathEntangler::Segment*s1, PathEntangler::Segment*s2);

    /// The pathSet that is to be entangled.
    SurfacePathSet* pathSet;

    /// Checks consistency using assertions.
    void assertConsistency(PathEntangler::Segment* nSeg);

    /// Marks all nodes as control points, if they belong to more than
    /// one path.
    void  setControlPoints(void);

    /// Mean edge length over all surface edges.
    float mMeanEdgeLength;

    /// Computes mean edge length over all surface edges.
    float computeMeanEdgeLength();
};

#endif

/// @}
