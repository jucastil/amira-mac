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

/// @addtogroup mclib mclib
/// @{
#ifndef MC_BOX2F_H
#define MC_BOX2F_H

#include "McWinDLLApi.h"
#include "McVec2f.h"

/// This class represents a 2D box, i.e. a rectangle
class McBox2f {
  public:
    /// Default constructor - leaves box totally empty
    McBox2f() { makeEmpty(); }

    /// Constructor given bounds
    McBox2f(float xmin, float xmax, float ymin, float ymax)
        : min(xmin, ymin), max(xmax, ymax) { }

    /** Constructs box from two points. The points can be any pair of
        opposite points of the box. */
    McBox2f(const McVec2f& a, const McVec2f& b) {
        if (a.x<b.x) {min[0] = a.x; max[0] = b.x;}
        else         {min[0] = b.x; max[0] = a.x;}

        if (a.y<b.y) {min[1] = a.y; max[1] = b.y;}
        else         {min[1] = b.y; max[1] = a.y;}
    }

    /// Returns true if box contains given point.
    int contains(const McVec2f& point, float eps=0) const {
        return (min.x-eps <= point.x && point.x <= max.x+eps &&
                min.y-eps <= point.y && point.y <= max.y+eps );
    }

    /// Returns true if box contains given point.
    int contains(float x, float y, float eps=0) const {
        return (min.x-eps <= x && x <= max.x+eps &&
                min.y-eps <= y && y <= max.y+eps );
    }

    /// Returns the minimum points
    const McVec2f &     getMin() const { return min; }

    /// Returns the maximum points
    const McVec2f &     getMax() const { return max; }

    /// Returns the center of a box
    McVec2f             getCenter() const { return (min+max)/2; }

    /// Returns size of box (xmax-xmin, ymax-ymin).
    McVec2f getSize() const {
        return max-min;
    }

    /// Returns the width of the bounding box.
    float width() const {
        return max.x-min.x;
    }

    /// Returns the height of the bounding box.
    float height() const {
        return max.y-min.y;
    }

    /// Extends Box2f (if necessary) to contain given 2D point
    void extendBy(const McVec2f &pt) {
        if (isEmpty()) {
            min = max = pt;
        } else {
            if (pt.x>max.x) max.x = pt.x;
            if (pt.x<min.x) min.x = pt.x;
            if (pt.y>max.y) max.y = pt.y;
            if (pt.y<min.y) min.y = pt.y;
        }
    }

    // Extends Box2f (if necessary) to contain given Box2f
    //void extendBy(const McBox2f &r);

    /// Returns TRUE if intersection of given point and Box2f is not empty
    int intersect(const McVec2f &pt) const {
        return (pt.x>=min.x && pt.x<=max.x && pt.y>=min.y && pt.y<=max.y);
    }

    /// Returns TRUE if intersection of given Box2f and Box2f is not empty
    int intersect(const McBox2f &bb) const {
        if (isEmpty() || bb.isEmpty()) return 0;
        if (bb.max.x<min.x || bb.min.x>max.x ||
            bb.max.y<min.y || bb.min.y>max.y) return 0;
        return 1;
    }

    /** Returns true if the two boxes intersect each other.
        in case 'withTouch' is 1 intersects returns also true
        in case the boxes share at least one face */
    int intersects(const McBox2f &other, int withTouch = 0) const {
        if (isEmpty() || other.isEmpty())
            return 0;
        if (withTouch)
            return (   (min[0] <= other.max[0])         // xmin1 <= xmax2
                    && (max[0] >= other.min[0])         // xmax1 >= xmin2
                    && (min[1] <= other.max[1])         // ymin1 <= ymax2
                    && (max[1] >= other.min[1]));       // ymax1 >= ymin2
        else
            return (   (min[0] < other.max[0])          // xmin1 < xmax2
                    && (max[0] > other.min[0])          // xmax1 > xmin2
                    && (min[1] < other.max[1])          // ymin1 < ymax2
                    && (max[1] > other.min[1]));        // ymax1 > ymin2
    }

    /// Sets rect to contain nothing
    void        makeEmpty() {
        min.x=1; max.x=0;
        min.y=1; max.y=0;
    }

    /** Checks if the box is empty (degenerate).
        Note that this relies on boxes being completely degenerate if
        they are degenerate at all.  All member functions preserve this
        invariant. */
    int isEmpty() const         { return max[0] < min[0]; }

    /// Checks if the box has area; i.e., both dimensions have positive size
    int hasArea() const
        { return (max[0] > min[0] && max[1] > min[1]); }

    /// Assignment.
    McBox2f& operator=(const McBox2f& o) {
        min=o.min; max=o.max; return *this;
    }

    // Equality comparisons
    //friend int          operator ==(const McBox2f &b1, const McBox2f &b2);
    //friend int          operator !=(const McBox2f &b1, const McBox2f &b2)
    //  { return !(b1 == b2); }

    McVec2f min; ///< Minimum point.
    McVec2f max; ///< Maximum point.
};

#endif

/// @}
