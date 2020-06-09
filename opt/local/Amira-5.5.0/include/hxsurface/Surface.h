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

/// @addtogroup hxsurface hxsurface
/// @{
#ifndef SURFACE_H
#define SURFACE_H

#include <hxsurface/HxSurfaceWinDLLApi.h>

#include "SurfaceData.h"

#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>
#include <mclib/McVec3f.h>
#include <mclib/McSmallArray.h>
#include <mclib/McSArray.h>
#include <amiramesh/HxParamBundle.h>
#ifndef NOAMIRA
#include <hxfield/oint.h>
#else
#include <hxsurface/oint.h>
#endif

#include <mclib/McFHeap.h>
class McBitfield;
class ProgressSenderIface;
class SurfaceLOD;

/** This class implements structured, triangulated surfaces. A surface
    consists of a number of sub-surfaces, called @c patches. Each patch can
    have different regions on its two sides: @c innerRegion and
    @c outerRegion. Patches are bounded by @c contours.

    Points can have different @c pointTypes. Points not lying on a contour
    are @c INNER points. Points lying on more than one contour, or being the
    first or last point of a contour are @c BRANCHING points. All other
    points are @c CONTOUR points.

    This implementation works with indices instead of pointers, this allows
    easy realloc. The surface contains one big array of @c points, of
    @c triangles, of @c patches, of @c contours and for temporary use of
    @c edges and lists of @c edgesPerPoint for each point. */

class HXSURFACE_API Surface { 

  public:

    // ==================== Subclass declaration ====================

    /**@name Subclass declaration */ //@{
    /// Point type. Stored in separate array.
    enum { INNER=0, CONTOUR, BRANCHING, DEADEND, UNUSED };

    /// This class represents a contour where different patches join.
    class Contour {
      public:
        /** The indices of the contour's points. <b> Note:</b> In the file
            format, the first point in the surface's point array is 1. In
            this data structure, the first point has the index 0.
            Conversion is done when writing and reading.*/
        McDArray<int> points;

        /** The indices of the patches this contour belongs to. */
        McDArray<int> patches;
    };

    /// This class represents a surface triangle.
    class Triangle {
      public:
        /** Indices of the three points of the triangle. <b> Note:</b> In the
            file format, the first point in the surface's point array is 1.
            In this data structure, the first point has the index 0.
            Conversion is done when writing and reading. */
        int points[3];

        /// Index of the patch this triangle belongs to.
        int patch;

        /// This struct is used to store neighbourhood information.
        struct Neighbour {
            /// Set if there is no neighbouring triangle in the same patch.
            unsigned int isEmpty:1;

            /// Set if the triangle touches a contour.
            unsigned int isContour:1;

            /// Index of neighbouring triangle, or index of boundary edge.
            int neighbourIdx:30;

            /// Constructor.
            Neighbour() { isEmpty=1; isContour=0; neighbourIdx=0; }
        };

        /// One neighbour struct for each of the three triangle edges.
        Neighbour neighbours[3];

        inline void invert() {
            int p = points[1];
            points[1] = points[2];
            points[2] = p;
            Neighbour n = neighbours[1];
            neighbours[1] = neighbours[2];
            neighbours[2] = n;
        }

        inline int hasPoint(int p) {
            return (p==points[0] || p==points[1] || p==points[2]);
        }

        inline int pointIndex(int p) {
            if (p==points[0]) return 0;
            if (p==points[1]) return 1;
            if (p==points[2]) return 2;
            return -1;
        }
    };

    /// This class represents a patch of connected triangles.
    class Patch {
      public:
        /// Index of the inner region (starting from zero).
        int innerRegion;

        /// Index of the outer region (starting from zero).
        int outerRegion;

        /// Additional id which defines some kind of material properties.
        int boundaryId;

        /// Indices of all inner branching points.
        McDArray<int> branchingPoints;

        /// Indices of all the triangles of the patch.
        McDArray<int> triangles;

        /// Indices of the patch's contours as well as their orientations.
        McDArray<oint> contours;

        /// Stores information about segments, i.e. subsequent contours
        struct Segment {
            /// Index of the first contour of a segment.
            int first;

            /// Index of the last contour (for closed segments first==last).
            int last;
        };

        /// Contains all connected contour segments of the patch.
        McDArray<Segment> segments;

        /// Assignment operator
        Patch& operator=(const Patch& other)
        {
            innerRegion = other.innerRegion;
            outerRegion = other.outerRegion;
            boundaryId  = other.boundaryId;
            branchingPoints = other.branchingPoints;
            triangles = other.triangles;
            contours  = other.contours;
            segments  = other.segments;
            return *this;
        }

        /// Default constructor.
        Patch() { innerRegion=outerRegion=boundaryId=0; }

        /// Copy constructor.
        Patch(const Patch& other) { *this = other; }
    };

    /// This class represents a surface edge.
    class Edge {
      public:
        /// Index of the first point of the edge.
        int from;

        /// Index of the second point of the edge.
        int to;

        /**
            Indices of the triangles that are adjacent to the edge.
            Normally, an edge has two adjacent triangles. Boundary
            edges have only one triangle and non-manifold surface
            connections have more than 2 triangles.
        */
        McSmallArray<int,3> triangles;

        ///
        Edge() { from=to=0; };
    };

    //@}

    // ======================= Member variables =====================

    /**@name Member variables */ //@{

    /// Branching points have indices [0...nBranchingPoints-1].
    int nBranchingPoints;

    /// Contour points start with index @c nBranchingPoints.
    int nContourPoints;

    /// Array of all surface points (required).
    McDArray<McVec3f> points;

    /// Array of point types (full surface only).
    McDArray<unsigned char> pointType;

    /// Array of all surface contours (full surface only).
    McDArray<Contour*> contours;

    /// Array of all surface patches (at least 1 patch is required).
    McDArray<Patch*> patches;

    /// Array of all surface triangles (required).
    McDArray<Triangle> triangles;

    /// All edges of the surface (temporary data).
    McDArray<Edge> edges;

    /// Stores for each point all edges incident at that point (temporary).
    McDArray< McSmallArray<int,6> > edgesPerPoint;

    /** Stores the edge ids for each triangle (optional and temporary).
        Edges of each triangle are ordered. The edge number of the triangle
        is the number of the opposite triangle vertex.
    */
    McDArray< McSArray<int,3> > edgesPerTriangle;

    /** Stores for each point all incident triangles. To initialize this
        array the method @c computeTrianglesPerPoint() has to be called
        explicitely. The class @c HxSurfaceEditor uses this information. */
    McDArray< McSmallArray<int,6> > trianglesPerPoint;

    /** Stores for each point all neighboured points. To initialize this
        array the method @c getPointsPerPoint() has to be called. For each (orientable!)
        manifold point the neighbours are sorted anti-clockwise around the point. */
    McDArray< McSmallArray<int,6> > neighsPerPoint;

    /** Contains info about the regions. The indices @c innerRegion and
        @c outerRegion refer to this structure, e.g. @c materials[0]. */
    HxParamBundle* params;

    McDArray<McVec3f> normals;

    enum NormalBinding { PER_TRIANGLE=0, PER_VERTEX, PER_VERTEX_INDEXED };

    NormalBinding normalBinding;

    /// Pointer to surface level-of-detail
    SurfaceLOD* lod;

    //@}

    // ======================== Member methods ======================

    /**@name Member methods */ //@{

    /// Constructor. If params is null an own parameter bundle is created.
    Surface(HxParamBundle* params=0);

    /// Destructor.
    virtual ~Surface();

    /// Deletes all points, triangles, patches, materials, etc.
    virtual void clear();

    /// Returns 1 if the contours of the surface have been computed.
    int hasContours();

    /** This method recomputes the connectivity information of a surface.
        Surface contours and point types are inewly determined. Patches
        containing disconnected triangles are separated into new patches. */
    void recompute();

    void recomputeNoRenumberPoints();

    /// Removes patches containing no triangles.
    void removeEmptyPatches();

    /// Remove all triangles with patchid<0, returns number of removed tris.
    int removeObsoleteTriangles();

    /** Remove coplanar triangles. The methods uses an iterative
        reduction scheme. It stops when no more coplanar triangles
        are found after an iteration or if the maximum number of
        iterations is reached (@c maxIter). If checkQuads is set
        also coplanar intersecting quad configurations are removed.
        If @c cleanup is set, and triangles have been removed, 
        - obsolete triangles will be removed at the end,
        - if the surface had an edge list before, a new up-to-date 
        edge list will be generated. 

        The method returns the number of removed triangles. */
    int removeCoplanarTriangles(int nMaxIter=4, int checkQuads=0, 
        bool cleanup=true);

    /// Fills the list with the state of Isolation for all points.
    /// 1 for non-isolated(used) and 0 for non-isolated(used).
    void findUsedPoints(McDArray<int> &used);

    /// Removes all points not referenced by any triangle.
    /// Returns the number of removed points
    int removeUnusedPoints();

    /// Removes all points not referenced by any triangle.
    /// Returns the number of removed points
    int removeUnusedPoints(McDArray<int>& newIndex);

    /**
        merges all Fields from the other surface to the fields of this surface.
        returns true if all the fields could be merged.
    */
    bool mergeFields(Surface* other);

    /** Simplify almost planar 3-star and 4-star configurations.
        The number of removed triangles is returned. Removed triangles
        are not actually deleted but only marked as obsolete. */
    int simplify34();

    /** Discards the contour information. This method should be called after
        the surface topology has been changed. */
    void cleanup();

    /// Returns bounding box of point coordinates.
    void getBoundingBox(float box[6]) const;

    /// Returns center of the surface (= average of all point coordinates).
    void getCenter(float center[3]);

    /// Modifies the coordinates of the surface points.
    void setCenter(const float center[3]);

    /// Copies points, triangles, and patches from other surface into this.
    void add(const Surface* other);

#ifndef NOAMIRA
    /// Read the surface from a file.
    int read(const char *, ProgressSenderIface *progress=0);

    /// Read surface information except header.
    int readSurfaceData(const char* file, FILE * in, int ascii,
                        McDArray<SurfaceData*>& additionalData,
                        ProgressSenderIface *progress=0);

    /// Read the surface from a file.
    int readPLY(const char *);

    /// Alternative read method which also return optional surface data.
    int read(const char *, McDArray<SurfaceData*>& additionalData, ProgressSenderIface *progress=0);

    /// Write surface + header to a file.
    int write(const char *file, int ascii=0);

    /// Write the surface without header to file.
    int writeSurfaceData(FILE *out, int ascii=0);
#endif

    /// Performs a consistency check (not very sophisticated up to now).
    void checkConsistency();

    /// Checks if indices are valid or if they are out-of-range.
    bool checkIndices(bool fixInvalidIndices);

    ///
    void computeNormalsPerTriangle();

    ///
    void computeNormalsPerVertexIndexed();

    ///
    void computeNormalsPerVertex(float creaseAngle);

    /** Refine surface. If mode==0, every edge is divided in two and
    each triangle into 4. If mode==1 an inner point is inserted into each
    triangle, dividing it into 3 triangles. */
    void refine(int mode);

    /** This function subdivides the surface edges until all edges are
        shorter than @c maxEdgeLength.  The edges are taken in the
        order defined by the edge lengths, that is, the algorithm will
        always take the longest currently existing edge. */
    void refineSubdivideEdges(const float maxEdgeLength);

    /** Makes orientation of triangles in patch consistent, by
        inverting some if necessary. You have to call @c createConnectivity
        before.
    @return Number of inverted triangles*/
    int fixOrientation(int patch);

    /** Invert the triangles of patch @c patch or all triangles, if
        #patch==-1.*/
    void invertTriangles(int patch=-1);

    //@}

    // ====================== Internal methods ======================

    /**@name Internal methods */ //@{

    ///
    int isClosedSegment(int patch,int segment) {
        int first = patches[patch]->segments[segment].first;
        int last = patches[patch]->segments[segment].last;

        return(contourFromPoint(patches[patch]->contours[first]) ==
               contourToPoint(patches[patch]->contours[last]));
    };

    /** Initializes the array @c trianglePerPoint. */
    void computeTrianglesPerPoint();

    /** Fills the @c edges, the @c edgesPerPoint and optionally the @c edgesPerTriangle arrays.
        @param createEdgeIds if set, the @c edgesPerTriangle array is filled,
        otherwise the @c edgesPerTriangle array is resized to zero */
    void createAllEdges(int  createEdgeIds = 0);

    /** Fills the neighbour array for each triangle in patch. This method
      needs the arrays @c edges and @c edgesPerPoint, which can be generated
      by calling @c createAllEdges(). If not all triangles in this patch
      are connected, the unconnected ones are put into a new patch.
      @c createConnectivity() for this new patch is called automatically.*/
    void createConnectivity(int patch);

    /** Fills the neighbour array for  all triangles.
      @see #createConnectivity */
    void createConnectivity();

    /** Fills the neighbour array for  all triangles without
    decomposing patches. */
    void createNeighbours();

    /** This methods initializes the @c type field in all
      point-structures with the correct value. This method relies on
      the arrays @c edges and @c edgesPerPoint, which can be generated by
      calling @c createAllEdges().*/
    void findBranchingPoints();

    /** Removes edges, that are not part of a contour. After doing this,
      this method calls @c renumberPoints. This method was kept for
      backward compatibility.*/
    void clearInnerEdges();

    /** Removes edges, that are not part of a contour. After doing this,
      this method calls @c renumberPoints, only if @c renumber is set to one. */
    void clearInnerEdges(int renumber);

    /** Find contours, by tracing edges.  This method relies on the
       arrays @c edges and @c edgesPerPoint, which can be generated by
       calling @c createAllEdges(). Also the @c PointType array must be
       initialized properly, which can be done by
       @c findBranchingPoints().*/
    void findContours();

    /** This method shuffels the points in such a way, that
      they are sorted according to their type in the following way:
      BRANCHING-points, CONTOUR-Points, INNER-Points.
      Points marked as UNUSED are deleted. The indices in the triangles
      edges and contours are modified accordingly. If the @c edgesPerPoint
      array is present, the @c edgesPerPoint lists are interchanged
      in a consistent way. As a side effect, the variables
      @c nBranchingPoints and @c nContourPoints are set.*/
    void renumberPoints();

    void deleteDeadEnds();

    /** Sort the contours so that they form one (or more) closed path.
      The indices pointing to the contours may become negative...
      @return The number of closed paths.
      */
    int sortContoursOfPatch(int p, int fixDeadEnds=0);

    /// Calls sortContoursOfPatch for all patches.
    void sortContoursOfPatches(int fixDeadEnds=0);


    /// sort triangle list according to patch order
    void sortTriangles();

    ///
    void findBranchingPointsOfPatches();

    ///
    void computeOrientationOfContours();

    /** Compute a triangulation for the polygon, consisting of the
      vertices v[]. Insert triangles into surfaces' triangle list.
      @return number of new triangles. This should be @c v.size()-2.*/
    int tile(const McDArray<int>& pidx);
    int tileCenter(const McDArray<int>& pidx);
    int tileFan(const McDArray<int>& pidx, int anchor);

    /** Compute best fitting plane for a polygon usign Newells method.*/
    void fitPlane(const McDArray<int>& pidx,float plane[4]);


    /// returns -1 if material is not found.
    int getMaterialID(const char *mat);

    //
    int addMaterial(const char *name,int id=-1);

    /**
        Sets boundary information for the given id into the object's parameter bundle.
        @param typeStr type of boundary, optional.
        @param info Additional info string, optional.
    */
    void setBoundaryIDInfo(int id, const char* typeStr=0, const char* info=0);

    ///
    void removePoint(int patch,int point);

    /** Remove triangles containing the same three points.
        @return Number of removed triangles. */
    int removeDuplicateTriangles();

    /** Remove triangles with two or three identical points.
        @return Number of removed triangles. */
    int removeDegenerateTriangles();

    ///
    int isInnerPoint(int idx) {
        return(idx>=nBranchingPoints+nContourPoints);
    }

    /** Get first point of contour indexed by @c contourIdx. @c contourIdx is
        an oint. If it is negatively oriented, the last point of the
        contour is returned instead. */
    int contourFromPoint(oint contourIdx) {
        if (contourIdx.positive()) return contours[(int)contourIdx]->points[0];
            else return contours[(int)contourIdx]->points.last();
    }

    /** Get last point of contour indexed by @c contourIdx. @c contourIdx is
        an oint. If it is negatively oriented, the first point of the
        contour is returned instead. */
    int contourToPoint(oint contourIdx) {
        if (contourIdx.positive()) return contours[(int)contourIdx]->points.last();
            else return contours[(int)contourIdx]->points[0];
    }

    ///
    int getEdgeOfTriangle(int triangleIdx,int which);

    ///
    int getNeighbourTriangle(int triangleIdx, int which, int global = 0);

    ///
    int getNextNeighbourTriangle();

    int debug;

    int operator==(const Surface& other) const;

    virtual void print();

    /// Copies the whole data set
    void copyData(const Surface &source);

    /// Appends a triangle and inserts it in given patch.
    void appendTriangle(int patchIdx, Triangle& triangle) {
        triangle.patch = patchIdx;
        int idx = triangles.append(triangle);
        patches[patchIdx]->triangles.append(idx);
    }

    /** Check surface closedness. @return 0 for closed surface,
    1 for non-closed surface, 2 for inconsistent triangle
    orientation. */
    int checkClosedness(McDArray<int> &patchOrientations,
            McDArray<int> &triangleList);

    /// Check intersection of triangle t with its neighbours.
    int intersectionTest(int t, McDArray<int>& neighbours,
             float eps, int selectNeighbours=0);

    /// Determine number of triangles of region adjacent to each edge.
    void classifyEdges(int iRegion, int &nOdd,
                       int &nEdge0, int &nEdge2, int &nEdge4,
                       McDArray<signed char> &markEdges,
                       McDArray<int> &triangleList);
    /// Create groups of connected triangles.
    int createTriangleGroups(const int iRegion,
                             McDArray<signed char> &markEdges,
                             McDArray<short> &markTriangles);
    /// Find inconsistent edges.
    void findInconsistentEdges(const int iRegion,
                               McDArray<signed char> &markEdges,
                               McDArray<short> &markTriangles);
    /// Create closed surfaces.
    int createClosedSurfaces(const int iRegion, int nGroups,
                             McDArray<signed char> &markEdges,
                             McDArray<short> &markTriangles);
    /// Calculate volumes enclosed by surfaces.
    void calcEnclosedVolumes(const int iRegion,
                             McDArray<short> &markTriangles,
                             McDArray<float> &enclosedVolumes);
    /// Check enclosed volumes.
    void checkEnclosedVolumes(McDArray<float> &enclosedVolumes,
                              McDArray<signed char> &inclusionInfo,
                              McDArray<short> &markTriangles,
                              int insideOut,
                              int &groupsOf4,
                              McDArray<int> &triangleList);

    /// Calculate minimal, maximal and mean edge length.
    void calcMinMaxMeanEdgeLen(float *min, float *max, float *mean);

    /// Compute edge lengths
    void calcEdgeLengths(McDArray<float>& lengths);


    // basic surface properties

    /** Returns value for (signed) curvature at edge:
        0=planar, +1=maximally convex, -1=maximally concave. */
    float getEdgeCurvature(int edge);

    /// Returns area of triangle.
    float getTriangleArea(int triangle) const;

    /// Returns normal at triangle
    McVec3f getTriangleNormal(int triangle) const;

    /// Returns normal at triangle
    McVec3f getVertexNormal(int vertex) const;

    /// Get surface area of given patch
    double getPatchArea(int patch) const;

    /// Make one patch.
    void makeOnePatch();

    /// Compute index of edge between given vertices
    int getEdgeIdx(int v1, int v2) const;

    /// Compute index of triangle with given vertices.
    int getTriangleIdx(int v1, int v2, int v3) const;

    /// Given a triangle index and two nodes, compute 3rd node number.
    int get3rdPoint(int v1, int v2, int triIdx, int& orient) const;

    /** Compute triangles along border around node v1 inside given patch.
        Start from edge (v1,v2). Return neighboured nodes and triangles.
        (orient==1 is clockwise, -1 is anticlockwise) */
    int getTrianglesAlongPath(const McBitfield& isPathEdge,
                              const McBitfield& considerTriangle,
                              int orient, int v1, int v2,
                              McDArray<int>& nodes, McDArray<int>& tris);

    /// Compute neighboured points around given points (sorted anti-clockwise if possible).
    bool getNeighsPerPoint(int node, McSmallArray<int,6>& neighs);

    /** Compute neighboured points around given points (sorted anti-clockwise if possible).
        Only consider neighs which triangles have the materialId as innerRegion*/
    bool getNeighsPerPointWithMaterial(int node, McSmallArray<int,6>& neighs, int materialId);

    /// Compute neighboured nodes at all vertices (only needs trianglePerPoint data).
    void getNeighsPerPoint();

    /// Determine indices of edges that connect given nodes
    void setPathEdges(const McDArray<int>& nodes, McBitfield& isPathEdge);

    /// Reset edges that connect given nodes
    void unsetPathEdges(const McDArray<int>& nodes, McBitfield& isPathEdge);

    /// Get triangles enclosed by given edges
    void getEnclosedTriangles(int first, const McBitfield& isPathEdge,
                              McDArray<int>& enclosed);

    /// Check if array of vertices form a closed loop on the surface
    int isClosedLoop(const McDArray<McDArray<int> >& path);

    /// Compute length of edge path on surface
    float getPathLength(const McDArray<int>& path);

    /// Compute length of edge path (and for each edge) on surface
    float getPathLength(const McDArray<int>& path, McDArray<float>& lengths);

    /// Get vertices around given points 
    McDArray<int> bfs(const McDArray<int>& nodes, int depth);

    //@}

  private:
    int contourFlag; // Indicates whether contours have been computed or not
    int lastTriangleIdx;
    int lastWhich;
    int lastGlobal;
    int lastNeighbourIdx;
    unsigned int hasOwnParamBundle;
};

#endif

/// @}
