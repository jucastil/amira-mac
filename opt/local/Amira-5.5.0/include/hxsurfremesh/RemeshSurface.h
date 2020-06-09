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

/// @addtogroup hxsurfremesh hxsurfremesh
/// @{
#ifndef REMESH_SURFACE_H
#define REMESH_SURFACE_H

#include <mclib/McDArray.h>
#include <mclib/McSmallArray.h>
#include <mclib/McVec3f.h>
#include <mclib/McBitfield.h>
#include <mclib/McHandable.h>
#include <mclib/McFHeap.h>

#include "hxsurfremeshAPI.h"

class McProgressInterface;
class RmAtlasSurface;

/** ... */
class HXSURFREMESH_API RemeshSurface : public McHandable 
{
    
public:
    enum ApproximationMode 
    {
        MODE_LINEAR=0,
        MODE_PN_TRIANGLES=1
    };

    /// Constructor
    RemeshSurface (RmAtlasSurface  *surface,
                   float           *curvature,
                   float           *mEL,
                   float            tsmth,
                   float            tdist);

    /// Destructor
    ~RemeshSurface (void) {}

    /** Determine the amount of console output.  A value of 0 will
        suppress all output. */
    void setVerbosity( const int verbosity );

    /// Number of smooth cycles
    void setIterations (int  iterations) 
    {
        nSteps = iterations;
    }

    /// assign a vertex list for restricted smoothing
    void setVertexList (const  McBitfield  &vList) 
    {
        vertexList = vList;
    }

    /// Here things happen
    
    // Relocate points, depending on "algorithm"-field either area-based, angle-based or voronoi-based
    int remesh (McProgressInterface * progressInterface = 0, int algorithm = 0, bool ignoreContours = 0);
    int relocatePoint(int i, int algorithm);

    // Delaunay-flip edges recursively. Initially, es are considered for flipping
    int flipEdgesRecursively(McDArray<int>& es);

    // Area-based relocation of a single point in 2D
    bool areaBasedRelocation2d(RmSurfaceChart& starChart, McVec3f& newCoord2d);
    // Angle-based relocation of a single point in 2D
    bool angleBasedRelocation2d(RmSurfaceChart& starChart, McVec3f& newCoord2d);
    // Lloyd-relaxation of a single point in 2D
    bool voronoiBasedRelocation2d(RmSurfaceChart& starChart, McVec3f& newCoord2d);
    
    // Lloyd-relaxation of the feature skeleton only
    int remeshContours(int depth = 0);
    // Experimental. Didn't work. Forget it.
    void addPointsNextToContour();

    // Split or contract edges
    int adjustVertexQuantity(int deltaPoints);
    
    // triangle quality
    float triangleRadiusRatio(int p1, int p2, int p3);
	
    // Delaunay-flip edges
    int flipEdges();

    // Contract edges on boundaries based on the connectivity-criterion
    int contractBoundaryEdges();

    // Do the regularisation (drift edges etc.)
    int regularise(int maxlevel);

    // prioritize edges by Surazhsky's error metric for simplification
    // (probably better use Garland/Heckbert metric)
    struct EdgeWithError: public McFHeapElement
    {
        float error;
        int operator < (const EdgeWithError& other)
        {
            return error < other.error;
        }
    };
    McFHeap<EdgeWithError> edgeHeap;
    McDArray<EdgeWithError> eedges;
    int edgeSlack;

    // collapse an edge
    // (had to be rewritten to keep connectivity data structures consistent)
    bool collapse(int v1, int v2, int updateRegularityHeap = 0);
    int bisectEdge(int p1, int p2, int updateRegularityHeap = 0);
    McVec3f getTriangleNormal(int P0, int P1, int P2) const;
    void getBlackWhiteVertices(McBitfield &blacks, McBitfield &whites);
    bool bisectEdge(int edge);
    float tsmth;
    float tdist;
    void cleanUp();
    // bisect marked edges
    void doRefine(McBitfield& edgeFlags);
    int refineByEdgeLength(float* minEdgeLength);
    void initDensity();
    bool andersrum;

protected:
    enum  {NUM_ITER=0, LAMBDA=1};
  
private:
    RmAtlasSurface  *theSurface;
    //    Surface *theOriginalSurface;
    
    int    nSteps;
    McBitfield  vertexList;

    // move the vertex given by triangle 'tri' and
    // vertex index 'vertex' to point given by barycentric
    // coordinates b
    int movePoint(int tri, int vertex, const McVec3f& b);
    int movePoint(int edge, int vertex, float a);
    float* curvature;
    float* minEdgeLengths;

    int m_verbosity;
 
    McDArray<float> psi;
    McDArray<McVec3f> vertexNormals;
    void removeEntry(McSmallArray<int,6>& a, int x);
	
    void setEdgeRegularityError(int e); 
    void initBoundary();
	
    McBitfield onBoundary;
    int flipEdge(int e, float maxRadiusRatio, int updateTrianglesPerPoint);
	
    // get number of neighbours of a point, but only those which reside on "patch" or on THAT
    // side of a feature line hinted at by vertex-id "otherPoint"
    int getNEdgesPerPointOnSamePatch(int point, int patch, int otherPoint);
    bool isContourEdge(int e);
    int getActDegree(int point, int patch, int otherPoint);
    int getDegreeDiff(int point);
    int testEdgeRegularityError(int e);
    int intersectionTest(int p1, int p2, int p3, int p4);
    int triangleEdgeIntersection(int p1, int p2, int p3, McDArray<int>& );
   
    void setEdgeRegularityErrorPerVertex(int p);
    int findEdge(int p1, int p2);
    void getEdgesPerTriangle(int triIdx);
    
    bool flipEdgeIfPossible(int j, int updateRegularityHeap = 0);
    int chaseDrifter(int e);
    
    void getPOTcurvature(int i);
    
    int getOptDegree(int p);
    int pointFixedness(int v);

    bool localDelaunay(McVec3f& p, McVec3f& q, McVec3f& r, McVec3f& s);
    int signDet4(McVec3f& p, McVec3f& q, McVec3f& r, McVec3f& s);
    float det(double a, double b, double c, double d);
    int signDet3(McVec3f& p, McVec3f& q, McVec3f& r);
    bool rightTurn(McVec3f& a, McVec3f& b, McVec3f& c);

    bool computeGeodesicPolarMap(int pp, RmSurfaceChart& chart, int patch1=-1, int patch2=-1);
    int relocateContourPoint(int p);
    
    int DNonConvex ;
    int DNonLocate ;
    int DNonDelaunay ;
};

#endif

/// @}
