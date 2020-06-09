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
#ifndef WINDOW_INTERSECTION_H
#define WINDOW_INTERSECTION_H

#include <mclib/McDArray.h>
#include <mclib/McVec2f.h>
#include <mclib/McBitfield.h>
#include <mclib/McHandle.h>

class EdgeWindow;

/** WindowIntersection is a helper-class for GeodesicConnector and its
    subclasses.  For further information see "Fast approximate and
    exact geodesics on meshes", Hoppe et al., SIGGRAPH 2005.
*/
class WindowIntersection {

public:

    /// Constructor
    WindowIntersection(EdgeWindow* window, EdgeWindow* other);

    /** Compute new windows: cut overlap region from other window.
        Returns fragments of intersection with smallest distance map. */
    void compute(EdgeWindow* newWindows, int* onWindow);

protected:

    /// This window
    EdgeWindow* window;

    /// Other window
    EdgeWindow* other;

    /// Pseudosource coordinates
    McVec2f ps2d[2];

    /// Class for classifying intersection intervals
    struct IntersectionInterval
    {
        /// Constructor
        IntersectionInterval() : left(-1), right(-1), window(0), overlap(false) {}
        /// left endpoint
        float left;
        /// right endpoint
        float right;
        /// window with minimal distance map
        EdgeWindow* window;
        /// indicates, whether interval belongs to overlap
        bool overlap;
    };

    /// Compute intersection intervals and store them in @c intervals.
    /// At most three intervals might occur.
    void computeIntersectionIntervals(IntersectionInterval* intervals);

    /// In case the intervals overlap, this function splits the
    /// intervals into non-overlapping intervals.  @c intervals must
    /// be of size 5.
    void splitOverlapInterval(IntersectionInterval* intervals);

    /// Compute edge @c windows and @c onWindow from @c intervals.
    /// All three arrays must be of size 5.
    void computeWindows(IntersectionInterval* intervals,EdgeWindow* windows, int* onWindow);

    /// Compute distance-map intersections of this and other window (on same edge)
    void computeEqualDistance(McDArray<float>& px);

    /// Remove intersections outside overlap interval given by its
    /// @c left and @c right values.
    void checkOverlap(float left, float right, McDArray<float>& px);
public:
    /// Initializes an array of @c intervals with size @c length.
    int initIntervals(IntersectionInterval* intervals, int length);
    void createNewWindows(EdgeWindow* newWindows, int* onWindow);
    void computeEqualDistance2(float* eDPs);
    void checkOverlap2(float* p, float left, float right);
};

#endif

/// @}
