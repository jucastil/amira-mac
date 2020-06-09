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

/// @addtogroup hxsurftools hxsurftools
/// @{
#ifndef _SURFACE_DISTANCE_H
#define _SURFACE_DISTANCE_H

#include <mclib/McBox3f.h>
#include <hxsurface/HxSurface.h>
#include <hxsurface/FaceOctree.h>
#include <hxsurftools/HxSurfToolsWinDLLApi.h>

/// This module computes the distance from a vertexSet to a surface.

class HXSURFTOOLS_API SurfaceDistance {
  
  public:

    /** struct representing the local coordinates xi, eta of the nearest point 
        on a triangle of surface2 for vertex vertNumb of surface1.
    */
    struct SurfacePointImage {
	float xi;
	float eta;
	int   vertNumb;
    };

    /// Constructor.
    SurfaceDistance();

    /// Destructor.
    ~SurfaceDistance();

    // Initialize computations if surface has changed
    void init(HxSurface* surface, int maxDepth=6, int maxTriPerLeaf=30)
    {
        mSurface2 = surface;

        mFaceOctree.cleanup();
        mFaceOctree.setMaxDepth( maxDepth );
        mFaceOctree.setMaxTriPerLeaf( maxTriPerLeaf );
        mFaceOctree.insertAllTriangles(mSurface2, 0, false);

        mSurface2->computeTrianglesPerPoint();
        mSurface2->createAllEdges();
    }

    /** Compute Hausdorff distance from vertexSet to surface. Trafos of
        vertexSet/surface are taken into consideration. The vector displacements 
        are computed in the (non-transformed) coordinate frame of surface1.
        Array pointImages may contain the information about the nearest 
        points on surface2 for all points of surface1.
	Return value is the number of successfully evaluated points. */
    int compHausdorffDist(HxVertexSet* vertexSet,
			  float *dst, 
                          float *vectors, 
                          int* tris, 
                          int thinoutStep=1, 
                          int considerPatches=0, 
			  int considerContours=0, 
                          int considerIsolatedPoints=0,
                          float maxDist=1e10, 
                          McProgressInterface* progress=NULL,
			  McDArray < McDArray<SurfacePointImage> > *pointImages=NULL);

    /** Surface distance can be evaluated within a region of interest.
        Setting the ROI with an emptyBox disables ROI checking */
    void setRoi (McBox3f  roiBox) {mRoi = roiBox;};

    ///
    void getPointsInRoi(McBitfield& isInRoi);

    /** Given a displacementfield from s1 to s2 and vice versa, invert the
        displacement field 2 (approximately), such that its direction is  
        from nodes on 1 to nodes on 2. vectors1 are given in the coordinate 
        frame of surface and, vectors2 in the frame of surface2 respectively. */
    void invertDisplacements(HxSurface* surface1, HxSurface* surface2,
                             float* vectors1, float* vectors2, float* vectors3, int*tris);

  protected:

    McDArray< McSmallArray<int,1> > mPatchPerNode;

    McBox3f mRoi;
    McBitfield mInRoi;

    int mThinoutStep;
    int mConsiderPatches;
    int mConsiderContours;
    float mMaxDist;

    FaceOctree<Surface> mFaceOctree;
    HxSurface* mSurface2;

    /** Get all triangles where box intersects octree cells.
        Filter triangles depending on considerPatches and considerContours. */
    void getNeighbours( const McBox3f& box,
                        int iVert,
                        McDArray<int>& neighbours,
                        McDArray<int>& pointList,
                        McDArray<int>& edgeList);

    /// Compute nearest neighbour from neighbour list.
    void getMinNeighbour( int iVert,
                          McVec3f& p,
                          const McDArray<int>& neighbours,
                          const McDArray<int>& pointList,
                          const McDArray<int>& edgeList,
                          float& minDist, McVec3f& minShift, int& minTri);

  public:

    /// Compute square of distance between point and triangle.
    static float sqDistPointTriangle(Surface* surface, const McVec3f &p, int iTri, McVec3f &shift);

    /// Compute square of distance between point and triangle.
    static inline float sqDistPointPoint(Surface* surface, const McVec3f &p, int iVert, McVec3f &shift);

    /// Compute square of distance between point and triangle.
    static float sqDistPointEdge(Surface* surface, const McVec3f &p, int iEdge, McVec3f &shift);

    /// Collect points.
    static void collectPoints(Surface* surface, 
                              const McDArray<int> &neighbours, 
                              McDArray<int> &pointList);

    /// Select points.
    static void selectPoints(Surface* surface, 
                             const McSmallArray<int,1> &patches,
		             McDArray<int> &pointList);

    /// Collect edges.
    static void collectEdges(Surface* surface, 
                             const McDArray<int> &neighbours, 
                             McDArray<int> &edgeList);

    /// Select edges.
    static void selectEdges(Surface* surface, 
                            const McSmallArray<int,1> &patches,
                            McDArray<int> &edgeList);

    /// Get the local coordinates xi, eta of a point on a triangle
    static void getLocalCoords(Surface* surface,
			       int iTri, McVec3f &point, 
			       float &xi, float &eta);

};

inline float SurfaceDistance::sqDistPointPoint(Surface* surface, 
                                               const McVec3f &p, 
                                               int iVert,
                                               McVec3f &shift)
{
    shift = surface->points[iVert] - p;
    return shift.length2();
}

#endif

/// @}
