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
#ifndef EDGE_WINDOW_H
#define EDGE_WINDOW_H

#include <mclib/McVec2f.h>
#include <mclib/McFHeap.h>
#include <mclib/McHandable.h>
#include <hxsurface/Surface.h>

class GeodesicConnector;

/** This class is used in GeodesicConnector and all of its
    children. It represents a distancefunction on an edge.
*/
class EdgeWindow : public McFHeapElement, public McHandable {

public:

    //--------------------- Data ------------------------

    /// endpoints of window (scaled to [from=0,to=1])
    McVec2f b;

    /** location of pseudosource in triangle coord system,
        from = (0,0), x-axis || (to-from), y-axis oriented into triangle tau */
    McVec2f ps;

    /// geodesic distance from pseudosource to source vertex
    float sigma;

    /// direction of pseudosource from directed edge
    int tau;

    /// index of pseudosource vertex
    int psVertex;

    /// edge that window is defined on
    int edge;

    /// keeps track, whether window is in stored in heap
    bool inHeap;

    /// Pointer to connector
    GeodesicConnector* connector;

    //--------------------- Methods ------------------------

    /// Default constructor
    EdgeWindow(GeodesicConnector* connector);

    /// Default constructor
    EdgeWindow()
    {
        min=-1;
        connector=NULL;
    }

    /// Default constructor
    EdgeWindow(GeodesicConnector* connector,
               float b0, float b1, float d0, float d1,
               float sigma, int tau, int psVertex, int edge);

    /// Copy constructor
    EdgeWindow(const EdgeWindow& other);

    /// Destructor
    ~EdgeWindow() {}

    ///
    float getMin();

    ///
    bool operator<(EdgeWindow& other);

    ///
    void operator=(const EdgeWindow& other);

    /// Distance from left/right endpoint to pseudosource
    float d(int side) const;

    ///
    void switchEndPoints();

    /// check for consistency of window
    bool isConsistent() const;

    /// Distance of point on window
    float getDistance(float lambda) const;

    /// Set pseudo-source coord from local 2d coordinates
    void setPseudoSource(const McVec2f& p,
                         const McVec2f& from,
                         const McVec2f& to,
                         const McVec2f& p3);

    /// Set pseudo-source coord from local 3d coordinates
    void setPseudoSource(const McVec3f& p,
                         const McVec3f& from,
                         const McVec3f& to,
                         const McVec3f& p3);

    /// Print some debug info
    void info();

    /// Compute the barycentric coordinates of the window's @c edge
    /// and its opposite point.
    void getBarycentric(McDArray<McVec3f> & barys, int tri, Surface* surface);

    /// checks barycentric "length" of window versus a tolerance (1.e-5)
    bool isEpsilon(void);

    /// checks if two windows overlap
    bool intersects(EdgeWindow* other);

    /// computes the minimum distance to source and sets it
    void setMin(void);

    /// minimum distance to source
    float min;

    /// checks if a window has the same values as other
    bool equals(EdgeWindow& other);
};

#endif

/// @}
