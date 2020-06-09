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
#ifndef HX_SURFACE_PATH_SET_H
#define HX_SURFACE_PATH_SET_H

#include <hxcore/HxVertexSet.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxObjectPool.h>
#include <hxcore/HxMessage.h>

#include "SurfacePathSet.h"
#include "hxsurfacepathAPI.h"

#include <hxlines/HxLineSetInterface.h>

class AmiraMesh;
class HxLineSet;
class HxSurface;
class HxDisplaySurfacePathSet;

/** Implements further methods needed for a SurfacePathSet to
    communicate with its environment.
*/
class HXSURFACEPATH_API HxSurfacePathSet : public HxVertexSet, public SurfacePathSet
{
    MC_HEADER(HxSurfacePathSet);

    friend class HxSurfacePathToLineSetInterface;

public:
    /// Returns pointer to vertex coordinates.
    virtual McVec3f* getCoords() const { 
        return SurfacePathSet::getCoords();
    }

    // ------------------ functions ------------------ 

    /// Constructor.
    HxSurfacePathSet();

    /// Handles new surface connections.
    void compute();

    /// Method called when user wants to save a @c HxSurfacePathSet as
    /// an ASCII-AmiraMesh file.
    int saveASCII(const char *filename);

    /// Method called when user wants to save a @c HxSurfacePathSet as
    /// an Binary-AmiraMesh file.
    int saveBIN(const char *filename);

    /// Static read-method called, when user tries to load a @c
    /// HxSurfacePathSet from an AmiraMesh-file.
    static int read(AmiraMesh * m,const char *filename);

    /// Parses tcl commands.
    int parse(Tcl_Interp* t, int argc, char **argv);

    /// Connects surface and remembers surface name and size.
    void connect(HxSurface* surface);

    /// Returns a copy of current object.
    virtual HxData* duplicate() const;

    /// Returns pointer to surface.
    HxSurface* getSurface() const;

    /// Prints some info about the path set.
    virtual void info();

    /// Returns total number of vertices of all lines.
    virtual int getNumPoints() const { return nodes.size(); }

    /// Returns first DisplaySurfacePathSet module that is connected
    /// to this path set.
    HxDisplaySurfacePathSet* getDisplaySurfacePathSet(bool doCreate=true);

    /// Fills array @c controlPoints.
    void getControlPoints(McDArray<int>& controlPoints);

    /// Copies all data from @c source to this path set.
    void copyData(const HxSurfacePathSet& source);

    /// Merges another path set into this one.
    bool merge( HxSurfacePathSet* ps );

    /// Refine the surface according to the path's nodes.
    bool refine( int mode, float tol = 0.001 );

    /// Create patches according the path set.
    bool patchify();

protected:

    /// Destructor.
    ~HxSurfacePathSet();

    /// Number of triangles of surface (for identification).
    int triangleSize;

    /// Label of surface (for identification).
    McString surfaceName;

    /// Surface where paths are defined on.
    HxConnection portSurface;

private:

    // Some strings for read/write routine
    // used when reading and writing AmiraMesh files
    static const char* SURFACE_NAME;
    static const char* TRIANGLE_SIZE;
    // used when reading and writing AmiraMesh files, MUST BE SET TO
    // "ContentType" OR AMIRAMESH WON'T WORK
    static const char* CONTENT_TYPE;
    static const char* NODE_ID_LOCATION;
    static const char* NODE_TYPE_LOCATION;
    static const char* BARY_COORDINATE_LOCATION;
    static const char* ABSOLUTE_COORDINATE_LOCATION;
    static const char* PATHS_LOCATION;
    static const char* ABSOLUTE_COORDINATES_DATA;
    static const char* BARY_COORDINATES_DATA;
    static const char* NODE_DATA;
    static const char* PATHS_DATA;
    static const char* NODE_TYPE_DATA;
    static const char* NODE_ID_DATA;
    static const char* CONTROL_POINT_LOCATION;
    static const char* CONTROL_POINT_DATA;

    void createInterface();

    /// Creates a @c HxSurfacePathSet from an @c AmiraMesh object and
    /// connects it to the surface.
    int load(AmiraMesh * m,const char *filename);

    /// Load the Pathset without surface.
    int loadPathSet(AmiraMesh * m);

    int tryLoadWith(HxSurface* surface, const char *fileName);

    /// Called, if the pathset is disconnected from the surface .
    void setSaveMethodLineSet();

    /// Saves a @c HxSurfacePathSet as an AmiraMesh-file.
    int save(const char *filename, int ascii);

    /// Converts surface path set to HxLineSet.
    HxLineSet* createLineSet();

    /// Checks for change on the surface.
    virtual void update();
};

/** Function to return a path realization which is independent path
    representation.  We use extern "C" to avoid name mangling so HxDSO
    can find it.
*/
extern "C" {
    bool HXSURFACEPATH_API HxSurfacePathSet_getPaths( HxData * pathRealization,
                                                      McDArray<McDArray<int> > & paths );
}

#endif

/// @}
