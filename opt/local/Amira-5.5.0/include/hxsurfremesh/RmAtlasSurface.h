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
#ifndef _RmAtlasSurface_h_
#define _RmAtlasSurface_h_

#include "hxsurfremeshAPI.h"

#include <hxsurface/HxSurface.h>
#include "RmSurfaceAtlas.h"
#include "RmPatchParametrizer.h"
#include <hxsurfacepath/SurfaceNode.h>
#include <hxsurfacepath/SurfaceNodeFactory.h>
#include <hxsurfacepath/SurfacePathSet.h>

/** Surface defined on a set of charts */

class HXSURFREMESH_API RmAtlasSurface : public HxSurface {

    HX_HEADER(RmAtlasSurface);

public:

    /// Default constructor.
    RmAtlasSurface();

    
    /* - - - - - - - Data section - - - - - - - */

    /// Points defined on the reference surface.
    McDArray<McHandle<SurfaceNode> > trianglePoints;

    // The paths on which some vertices are constrained. 
    // Especially contours, but arbitrary edge paths can be defined 
    // as constraints.
    McDArray<McDArray<int> > edgePaths;
    McDArray<McDArray<int> > atlasEdgePaths;

    /// Keeps track of boundary constraints.
    McDArray<int> onEdgePath;

    /// Keeps track of boundary constraints.
    McBitfield isFixPoint;

    /// Atlas (set of charts) the surface is defined on
    RmSurfaceAtlas atlas;

    int posIntMode;
    int normIntMode;

    McDArray<McVec3f> vertexNormals;

   // surface node factory
    SurfaceNodeFactory nFactory;

    /* - - - - - - - Function section - - - - - - - */
    
    /// Initialize without creating charts
    void createRemesh(Surface* surf, SurfacePathSet* surfacePathSet = 0, 
                      McDArray<int>* makeVertexNodes = 0);

    /** Initializes atlas surface without creating charts.  This
        method works for more than one surface path set. */
    void createRemesh(Surface                           * surf,
                      const McDArray< SurfacePathSet* > & surfacePathSets,
                      const McDArray<int>               * makeVertexNodes = 0);
    
    /// Update single point from trianglePoints
    bool updateCoord3d(int idx);

    /// Update all points array from trianglePoints
    int updateCoords3d();

    /// Update function.
    virtual void update();
    
    /// Create local chart (single triangle / two triangles sharing an edge / star)
    bool createLocalChart(int node, RmSurfaceChart& chart, 
                          McVec3f& center2d, McDArray<McVec3f>& neighs2d);

    void getPOTNormal(int potIdx);
    void getPOTNormals();


    /** Approximation measure of atlas to original surface 1: smoothness
        (c.f. Surazhsky, Gotsman: Explicit surface remeshing) */
    float getSmoothnessError(int tri);

    /** Approximation measure of atlas to original surface 2: distance
        (c.f. Surazhsky, Gotsman: Explicit surface remeshing) */
    float getDistanceError(int tri);

    /** Set how to interpolate positions and normals on the atlas.
     * 0: linearly
     * 1: use PN triangles (c.f. Vlachos et al.) */
    void setPositionInterpolationMode(int m);
    void setNormalInterpolationMode(int m);

    
    bool createSurfaceNodeOnEdge(int node,int edge,float a);
    bool createSurfaceNodeOnTriangle(int node,int triangle,McVec3f bary);

    float evaluateFieldOnTriangles(int node, float* field);


    /// Duplicates the current RmAtlasSurface object
    virtual HxData *duplicate() const;
	
    /// Used by duplicate() to copy the data
    void copyData(const RmAtlasSurface &source);
    void commit();
    void clearUndoEntry();
    int removeUnusedPoints();
    int removeUnusedPoints(McDArray< int > &newPointIndices);
    ~RmAtlasSurface();

    /// Returns true if @c p1 and @c p2 belong to a contour or surface
    /// path AND are connected via contours or surface paths.
    bool doPointsBelongToSamePathComponent(const int p1, const int p2);

protected:
    // This member variable stored for each path/contour which
    // connected path component it belongs to.
    McDArray<int> m_connectedPathComponents;

    /// This method prints some information about the object.
    virtual void info();
    
    McVec3f getAtlasVertexNormal(int vertex, int triangle) const;
    // get vertex normal wrt. to patch indicated by the triangle
    // (Now, this only compares patch numbers. What it should really do to be useful is
    // also to check the two sides of a feature line.)

    // This function takes @c tmpEdgePaths as input and creates
    // non-overlapping edge paths which are stored in
    // @c atlasEdgePaths.  Overlapping edges are removed from the
    // paths.  As result, some paths will be split into two or more
    // subpaths.
    void createNonOverlappingEdgePaths(   const McDArray< McDArray<int> > & tmpEdgePaths
                                        , McDArray< McDArray<int> >       & atlasEdgePaths );

    // This function takes a set of non-overlapping paths as input
    // (@c atlasEdgePaths) and sets the point type of point x to
    // Surface:BRANCHING_POINT, if point x represents a crossing point
    // of a single path or a point where two paths meet.
    void identifyBranchingPoints(   const McDArray< McDArray<int> > & atlasEdgePaths
                                  , McDArray<unsigned char>         & pointType );

    // This function computes the connected components of 
    // @c atlasEdgePaths.  That is, if edge paths i and j are
    // connected, then connectedComponents[i] will be equal to
    // connectedComponents[j].  The function assumes, that all points
    // of @c atlasEdgePaths have a valid path id stored in 
    // @c onEdgePath.
    void findConnectedPathComponents(   const McDArray< McDArray<int> > & atlasEdgePaths
                                      , const McDArray<int>             & onEdgePath
                                      , McDArray<int>                   & connectedComponents );
};

#endif

/// @}
