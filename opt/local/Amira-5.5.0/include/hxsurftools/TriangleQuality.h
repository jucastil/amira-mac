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
#ifndef _TRIANGLE_QUALITY_H
#define _TRIANGLE_QUALITY_H

#include <hxsurface/FaceOctree.h>
#include <hxsurftools/HxSurfToolsWinDLLApi.h>
#include <mclib/McVec3f.h>

class HXSURFTOOLS_API TriangleQuality {

  public:

    TriangleQuality() : mSurface(0) {};

    TriangleQuality(Surface* surf) : mSurface(surf) {};

    ~TriangleQuality() {};

    /// quality measures that are calculated so far
    enum  enQualities {RADIUS_RATIO = 0, LARGEST_ANGLE, DIHED_ANGLE,
                       MEAN_EDGE_LEN, MIN_EDGE_LEN, MAX_EDGE_LEN,
                       TRIANGLE_INDEX, CIRCUM_RADIUS, IN_RADIUS,
                       MIN_HEIGHT, MAX_HEIGHT, SMALLEST_ANGLE, 
                       TRIANGLE_AREA, TRIANGLE_QUALITY,
                       TETRA_QUALITY_1, TETRA_QUALITY_2, NUM_QUALITIES};

    void setSurface( Surface* surf ) { mSurface = surf; };

    void compute( int quality , float * triangleQualities );

    /** Quality measures that depend only on the shape of the triangle,
        given by its points p0, p1, p2. */

    static float meanEdgeLength(const McVec3f& p0, const McVec3f& p1, const McVec3f& p2);

    static float minEdgeLength(const McVec3f& p0, const McVec3f& p1, const McVec3f& p2);

    static float maxEdgeLength(const McVec3f& p0, const McVec3f& p1, const McVec3f& p2);

    static float area(const McVec3f& p0, const McVec3f& p1, const McVec3f& p2);

    static float minHeight(const McVec3f& p0, const McVec3f& p1, const McVec3f& p2);

    static float maxHeight(const McVec3f& p0, const McVec3f& p1, const McVec3f& p2);

    static float largestAngle(const McVec3f& p0, const McVec3f& p1, const McVec3f& p2);
    
    static float smallestAngle(const McVec3f& p0, const McVec3f& p1, const McVec3f& p2);

    static float innerRadius(const McVec3f& p0, const McVec3f& p1, const McVec3f& p2);

    static float outerRadius(const McVec3f& p0, const McVec3f& p1, const McVec3f& p2);

    static float radiusRatio(const McVec3f& p0, const McVec3f& p1, const McVec3f& p2);

    static float invRadiusRatio(const McVec3f& p0, const McVec3f& p1, const McVec3f& p2);

    /// auxiliary structure for sorting triangles according to quality 
    /// criteria like aspect ratio, dihedral angle, tetrahedron quality
    struct QualityAux {
        int index;
        float quality;
        int vertex4;
    };
    
    void sortQuality(HxSurface *surface, int qualityMeasure,
                     McDArray<QualityAux> &qualityAux,
                     bool createSortedArray,
                     FaceOctree<HxSurface> &octree,
                     bool initOctree,
                     const McVec3f* normals,
                     McProgressInterface *progInterface);

    void getTetQuality(int idx1, int idx2, 
                       int idx3, int idx4,
                       McDArray<McVec3f> &points,
                       float& determinante,
                       float& inner_radius, 
                       float& outer_radius);

protected:

    Surface* mSurface;

    static int getRadii(const McVec3f& p0, const McVec3f& p1, const McVec3f& p2,
                        float& innerRadius, float& outerRadius);

    static int localCoords(const McVec3f& p0, const McVec3f& p1, const McVec3f& p2, 
                           float dx2[][2], float edgeLen[], float& area2);
};

#endif

/// @}
