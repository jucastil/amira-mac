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
#ifndef _SurfaceLOD_H
#define _SurfaceLOD_H

#include <hxsurface/Surface.h>
#include <hxsurface/HxSurfaceWinDLLApi.h>

class LODCoordUpdate;
class McProgressInterface;

/** This class provides a level-of-detail (LOD) surface access.
    A LOD surface must be created by a number of edge-collapse
    steps. This can be stored in this class via the functions
    @c addCollapseInfo, @c addCollapsed and @c addRemaining. The base
    mesh must be stored at the beginning of the points/triangles
    arrays of the surface passed to the constructor. The function
    @c permute takes care of the permutation of the points indices
    (see hxsurftools/SimplifierQ).
    It is then possible to access arbitrary levels of detail
    via @c set(). Before any call to setLevel the SurfaceLOD
    must be initialized via @c init().
*/

class HXSURFACE_API SurfaceLOD {

  public:

    /// Constructor.
    SurfaceLOD(Surface* s);

    /// Destructor.
    ~SurfaceLOD();

    // ------------ Accessing the LOD surface ------------

    /// Init surface->trianglesPerPoint array
    void init(LODCoordUpdate* geom=0);

    /// Set level
    void set(int level, McProgressInterface* progress=0);

    /// Get current level
    int get();

    /// Get total number of levels
    int numLevels();

    /// Copy data to other surface
    void copyData(SurfaceLOD* other);

    /// Print collapseInfo (for debugging)
    void printCollapseInfo();

    /// Check consistency of collapseInfo (for debugging)
    int checkCollapseInfo();

    // ------------ Creating the LOD surface ------------

    /// Add new entry in collapseInfo array
    void addCollapseInfo(int v1, int v2, const McVec3f& v1Pos);

    /// Add information about a removed triangle
    void addCollapsed(int t, int v1, int v2);

    /// Add information about a remaining triangle
    void addRemaining(int t, int v2);

    /// Map point indices after all edge collapses have been performed.
    void permute(McDArray<int>& pointFlag);

    /// Return permutation of points from original surface
    void getPermutation(McDArray<int>& pointFlag);

    // ------------ IO ------------

    /// read collapse info from file
    int read(FILE * in, int ascii=0);

    /// append collapse info to file
    int write(FILE *out, int ascii=0);

    /// This class stores edge collaps information.
    class CollapseInfo {
      public:
        /// Index of the remaining point of the collapsed edge.
        int from;

        /// Index of the removed point of the collapsed edge.
        int to;

        /** Collapsed triangles, stored data:
            - collapsed[][0]: third point, other than from/to
            - collapsed[][1]: orientation of triangle
              -1: from -> third point -> to,
              1: from -> to -> third point
            - collapsed[][2]: patch
        */
        McDArray< McSmallArray<int,3> > collapsed;

        /// Remaining triangles: to -> remaining[][0] -> remaining[][1]
        McDArray< McSmallArray<int,2> > remaining;

        /// Position difference for the remaining point.
        McVec3f fromDelta;

        /// Position of the removed point.
        McVec3f toPos;
    };

  protected:

    /* - - - - - - - - - - Data  - - - - - - - - - - */

    /// Information about the edge collapses.
    McDArray<CollapseInfo> collapseInfo;

    /// Permutation of points of original surface
    McDArray<int> pointPermutation;

    /* - - - - - - - - - - - - - - - - - - - - - - - */

    /// Pointer to the surface object (surface will be modified by setLevel).
    Surface* surface;

    /// Pointer to geometry update strategy
    LODCoordUpdate* geometry;

    /// Perform vertex split on the basis of the collapseInfo data.
    void split();

    /// Perform edge collapse on the basis of the collapseInfo data.
    void collapse();

    /// Update patches
    void updatePatchesFromTriangles();

    /// read collapse info from file (ascii)
    int readAscii(FILE * in);

    /// read collapse info from file (binary)
    int readBinary(FILE* in);

    /// append collapse info to file (ascii)
    int writeAscii(FILE *out);

    /// append collapse info to file (binary)
    int writeBinary(FILE *out);

};

//---------------------------------------------------------------

typedef SurfaceLOD::CollapseInfo CollInfo;

//---------------------------------------------------------------

/// Class for defining the strategy of updating the 3d coordinates
class HXSURFACE_API LODCoordUpdate {

  public:

    /// The constructor must be supplied with the associated surface.
    LODCoordUpdate(Surface* s) : surface(s) {}

    /// Split will be called after the connectivity update
    virtual void split(const CollInfo& info) = 0;

    /// Collapse will be called before the connectivity update
    virtual void collapse(const CollInfo& info) = 0;

    virtual ~LODCoordUpdate();

  protected:

    ///
    Surface* surface;
};

//---------------------------------------------------------------

/// Default strategy of updating the geometry
class SurfaceLODCoordUpdate : public LODCoordUpdate {

  public:

    ///
    SurfaceLODCoordUpdate(Surface* s) : LODCoordUpdate(s) {}

    ///
    virtual void split(const CollInfo& info)
    {
        McDArray<McVec3f>& points = surface->points;
        points[ info.from ] += info.fromDelta;
        points.append( info.toPos );
    }

    ///
    virtual void collapse(const CollInfo& info)
    {
        McDArray<McVec3f>& points = surface->points;
        points[ info.from ] -= info.fromDelta;
        points.removeLast();
    }
};

//---------------------------------------------------------------

#endif

/// @}
