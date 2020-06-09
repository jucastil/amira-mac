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

/// @addtogroup hxpathconnectors hxpathconnectors
/// @{
#ifndef WINDOW_PROPAGATOR_H
#define WINDOW_PROPAGATOR_H

#include <mclib/McDArray.h>
#include <mclib/McVec2f.h>
#include <mclib/McHandle.h>

class GeodesicConnector;
class EdgeWindow;
class Surface;

/** WindowPropagator is a helper-class for GeodesicConnector and its
    subclasses.  Propagates an edge-window trough the next triangle
    and computes the resulting windows.  For further information see
    "Fast approximate and exact geodesics on meshes", Hoppe et al.,
    SIGGRAPH 2005.
*/
class WindowPropagator {

public:

    /// Constructor.
    WindowPropagator(EdgeWindow* window, int triangle,
                     GeodesicConnector* connector);

    /// Compute new windows from propagation of current window.
    void getNewWindows(EdgeWindow* newWindows);

    /// Returns scale factor for dp, at which p+dp intersects line q1<->q2.
    static float intersection2d(const McVec2f& p, const McVec2f& dp,
                                const McVec2f& q1, const McVec2f& q2,
                                bool* parallel=NULL);

    /// Returns the surface point index of @c triangle which lies
    /// opposite of @c edge.
    static int getOppositePoint(Surface* surface, int edge, int triangle);

protected:

    /// Current window.
    EdgeWindow* window;

    /// Triangle, on which the propagation takes place.
    int triangle;

    /// Associated connector (for access to surface, edgeLenghts, etc.)
    GeodesicConnector* connector;

    /// Pointer to surface.
    Surface* surface;

    /// triangle in local 2d coords
    McVec2f p2d[3];

    /// window endpoints in local 2d coords
    McVec2f b2d[2];

    /// pseudo source in local 2d coords
    McVec2f ps2d;

    /// vertex indices of triangle points
    int v[3];

    /// edges adjacent to window->edge
    int adj[2];

    /// index of next free space in array
    int index;

    /// Internal structure to store ray-edge intersections.
    struct EdgeIntersection
    {
        /// Default constructor.
        EdgeIntersection() :
            lambda(-1), ok(false),overlay(false) {}

        /// Constructor for overlaying lines.
        EdgeIntersection(bool overlay) :
            lambda(-1), ok(true),overlay(overlay) {}

        /// Constructor for valid intersection.
        EdgeIntersection(float lambda) :
            lambda(lambda), ok(true),overlay(false) {}

        /// Edge coords of intersection.
        float lambda;

        /// Intersection is valid.
        bool ok;

        /// Lines overlay.
        bool overlay;
    };

    /// All possible intersections.
    EdgeIntersection eis[2][2];

    /// Compute local 2d coordinates (as shown in the paper).
    void setupCoordSystem();

    /// Return intersection point in from-to coordinates of edge.
    EdgeIntersection computeIntersection(int ray, int side);

    /// A case other than (a), (b), and (c) (see paper).
    void caseP(int side, EdgeWindow* windows);

    /// Case (a) of ray-edge intersection scenario (see paper).
    void caseA(int side, EdgeWindow* windows);

    /// Case (b) of ray-edge intersection scenario (see paper).
    void caseB(EdgeWindow* windows);

    /// Case (c) of ray-edge intersection scenario (see paper).
    void caseC(int side, EdgeWindow* windows);

    /// Debugging.
    void showAll();
};

#endif

/// @}
