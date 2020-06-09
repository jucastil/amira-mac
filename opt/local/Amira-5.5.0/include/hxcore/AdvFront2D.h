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

/// @addtogroup hxcore hxcore
/// @{
#ifndef ADVFRONT2D_H
#define ADVFRONT2D_H

#include <stdio.h>
#include <mclib/McVec2i.h>
#include <mclib/McVec2f.h>
#include <mclib/McDArray.h>
#include <hxcore/HxAmiraWinDLLApi.h>

/** A simple 2D grid generator based on an advancing front method. */

class HXCORE_API AdvFront2D
{
  public:

    /// Constructor.
    AdvFront2D();

    /// Destructor.
    ~AdvFront2D();

    /** Define a boundary curve. The curve must be defined in
        counter-clockwise orientation if the inner part is to be
        triangulated. The first and last node have to be the same!
        If you want to add several contours just use addContour for
        each contour.
        To run the algoritm just say triangulate(). You don't have to
        set any flag or the edge length. By default smoothing and the
        average length of the contour edges are set.
        ATTENTION! If you define own interior Nodes in this version
        they will be changed if the smoothing flag is set. */
    void addContour(int nNodes, McVec2f* coords);

    /** Refines the contour. If edgeLen is not set, the length of
        the minimal contour edge is taken. */
    int refineContour(float edgeLen = -1.0);

    void addOwnNodes(int nNodes, McVec2f* coords);

    /// Clears all given nodes and contours.
    void clear();

    /// Get the average length of the contour edges.
    float avgEdgeLength();

    /// Set wished edge length of the triangles for the node generation.
    void setEdgeLength(float len) {length=len;}

    float getEdgeLength() {return length;}

    /** Set tol*EdgeLength as min. distance to be hold between nodes
        and contour res. nodes and predefined nodes. */
    void setTolarance(float tol){tolerance = tol;}

    /// Run the advancing front algorithm.
    int triangulate(int smoothingFlag = 1);

    /// If set the result of constructTRiangulation will be smoothed.
    void setSmoothFlag(int flag = 1){ smoothFlag=flag;}

    /// Set iteration steps in smoothing method.
    void setSmoothSteps(int steps = 2){smoothSteps=steps;}

    /// Returns number of nodes.
    int nNodes(){ return nodes.size();}

    /// Returns pointer to node data.
    McVec2f* nodeData();

    /// Returns number of triangles.
    int nTriangles() { return triangles.size(); }

    /// Returns pointer to triangle data.
    int (*triangleData())[3];

    /** Returns quality of worst an average triangle
        ratio of incircle raduis to ambit radius. */
    float absQualMeasure1();

    /// Same as absQualMeasure1().
    float avgQualMeasure1();

    /// Flip edges of bad triangles near the contour.
    void flipEdges();

    int postscript(const char* filename);

    /// Get length of activeNodeList
    int getANLlength();

    struct Edge {
        int a, b;
        Edge(int a, int b) { this->a = a; this->b = b; }
        Edge() {}
    };

    McDArray<Edge> edgeList;
    McDArray<McVec2f> activeNodeList;
    McDArray<McVec2f> nodes;
    McDArray<int> currentNodes;
    McDArray<McVec2f> interiorNodes;
    McDArray<McVec2f> ownInteriorNodes;

    struct tri {
        int a;
        int b;
        int c;
    };

    /// Triangle set as indices of nodes
    McDArray<tri> triangles;

    int nInteriorNodes;

    int nContourNodes;

    int nOwnNodes;

  protected:

    /// Find best node for enhancing the advancing front (lo-measure).
    int findNode(const Edge &e,int &aIndex, int &bIndex);

    /// Incircle to circumcircle ratio measure.
    int findNode2(const Edge &e,int &aIndex, int &bIndex);

    int findEdge(const Edge &e);

    /// If set interior points will be generated.
    void setGeneration(int flag){ generateFlag = flag;}

    /// Set automatically by addOwnNodes().
    void setOwnNodes(int flag){ ownFlag = flag;}


    /// Attention!!! returns negative ratio!
    float incircleToAmbit(const McVec2f &a, const McVec2f &b
                                          , const McVec2f &c);

    /// Determines sum of squared lengths of triangle sides ac and bc.
    float squaredSideLength(const McVec2f &a, const McVec2f &b,
                            const McVec2f &c);

    /// Proves if point is an triangle ABC.
    int pointInTriangle(const McVec2f &point, const McVec2f &a,
                        const McVec2f &b, const McVec2f &c);

    /// Area of the triangle ABC.
    float area(const McVec2f &A, const McVec2f &B, const McVec2f &C);

    /// Approximate edge length of triangles used for generating interior nodes.
    float length;

    float tolerance;

    /// Returns 1 if node is interior.
    int isInterior(int node);

    int onContour(int node){if(node < nContourNodes) return 1;
                                                 else return 0;}

    /// First step of the alg.: generate interior nodes by scan-lines.
    int generateInteriorNodes();

    /// Validity-check for interior node candidate.
    int valid(const McVec2f& node);

    /// Second step of the alg.: construct a tringulation by adv.front method.
    int constructTriangulation();

    /// Third step of th alg.: smoothing of the triangulation of step two.
    int smoothTriangulation();

    int smoothFlag;
    int smoothSteps;
    int generateFlag;
    int ownFlag;

    /// Find edge in the front with end node of e as start node.
    int findNextEdge(int edgeIndex);

    /// Computes euclidean difference between two n-dim. vectors.
    float difference(const float *x, const float *y);

    /// Proves if a edge of the triangle edge + node intersects front.
    int intersectFront(int nodeIndex, const Edge& edge);

    float toler;

};

int intersect(const McVec2f& p, const McVec2f& q,
              const float& h, float& inter);

int sameSigns(float a, float b);

int intersect2(const McVec2f& a1, const McVec2f& a2, const McVec2f& b1,
               const McVec2f& b2);

#endif

/// @}
