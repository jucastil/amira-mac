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
#ifndef MC_BOX3I_H
#define MC_BOX3I_H

#include "McWinDLLApi.h"
#include "McVec3i.h"
#include "McVec3f.h"

/// This class represents a 3D box.
class McBox3i {
  public:
    /// Default constructor - leaves box totally empty.
    McBox3i() {}

    /// Constructor using given explicit bounds.
    McBox3i(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax) {
        box[0] = xmin;  box[1] = xmax;
        box[2] = ymin;  box[3] = ymax;
        box[4] = zmin;  box[5] = zmax;
    }

    /// Copy constructor.
    McBox3i(const McBox3i& old){
        for (int i=0; i<6; i++)
            box[i] = old[i];
    }

    /// Constructor using a given int[6] array.
    McBox3i(int *array){
        for (int i=0; i<6; i++)
            box[i] = array[i];
    }

    /// Constructor using two given points.
    McBox3i(const McVec3i& a, const McVec3i& b){
        if (a.i<b.i) {box[0] = a.i;   box[1] = b.i;}
        else         {box[0] = b.i;   box[1] = a.i;}

        if (a.j<b.j) {box[2] = a.j;   box[3] = b.j;}
        else         {box[2] = b.j;   box[3] = a.j;}

        if (a.k<b.k) {box[4] = a.k;   box[5] = b.k;}
        else         {box[4] = b.k;   box[5] = a.k;}
    }

    /// Returns true if box contains given point.
    int contains(const McVec3i& point) const {
        return (box[0] <= point.i && point.i <= box[1] &&
                box[2] <= point.j && point.j <= box[3] &&
                box[4] <= point.k && point.k <= box[5]);
    }

    /// Const version of scaling operator.
    const McBox3i& operator*=(int scale) {
        box[0]*=scale; box[1]*=scale;
        box[2]*=scale; box[3]*=scale;
        box[4]*=scale; box[5]*=scale;
        return *this;
    }

    /// Scaling operator.
    McBox3i operator*(int scale) {
        return McBox3i(box)*=scale;
    }

    /// Index operator.
    int& operator[](int n) {
        return box[n];
    }

    /// Const version of index operator.
    const int& operator[](int n) const {
        return box[n];
    }

    /// Sets the complete box.
    void setValue(int minx, int maxx, int miny, int maxy, int minz, int maxz){
        box[0] = minx;     box[1] = maxx;
        box[2] = miny;     box[3] = maxy;
        box[4] = minz;     box[5] = maxz;
    }

    /// Extends the box to contain given point.
    void extendBy(const McVec3i& point){
        if (isEmpty()) {
            box[0]=box[1]=point.i;
            box[2]=box[3]=point.j;
            box[4]=box[5]=point.k;
        } else {
            if (point.i<box[0]) box[0]=point.i;
            if (point.i>box[1]) box[1]=point.i;
            if (point.j<box[2]) box[2]=point.j;
            if (point.j>box[3]) box[3]=point.j;
            if (point.k<box[4]) box[4]=point.k;
            if (point.k>box[5]) box[5]=point.k;
        }
    }

    /// Extends the box to contain given box.
    void extendBy(const McBox3i& other){
        if (!other.isEmpty()) {
            extendBy(other.getMin());
            extendBy(other.getMax());
        }
    }

    /** Checks if box is empty. A box is called empty if either xmax<xmin
        or ymax<ymin or zmax<zmin. */
    int isEmpty() const {
        return (box[1]<box[0]) || (box[3]<box[2]) || (box[5]<box[4]);
    }

    /// Makes the box empty.
    void makeEmpty() {
        box[0]=box[2]=box[4] =  1;
        box[1]=box[3]=box[5] = -1;
    }

    /// Checks if min<=max for all three coordinates.
    int isConsistent() const {
        return (box[0]<=box[1] && box[2]<=box[3] && box[4]<=box[5]);
    }

    /// Enlarges the box by 'eps' to each side.
    void extendByEps(int eps){
        if ( isEmpty() )
            return;

        // TODO:
        // don't modify the box for negative eps?

        box[0]-=eps;    box[1]+=eps;
        box[2]-=eps;    box[3]+=eps;
        box[4]-=eps;    box[5]+=eps;
        assert (isConsistent());
    }

    /// Returns frontal lower left corner.
    McVec3i getMin() const {
        return McVec3i(box[0], box[2], box[4]);
    }

    /// Returns backward upper right corner.
    McVec3i getMax() const {
        return McVec3i(box[1], box[3], box[5]);
    }

    /** Return center of the box. Notice that a McVec3f is returned.
        The center may be between two voxels. */
    McVec3f getCenter() const {
        return McVec3f(.5f*float(box[0]+box[1] + 1)
                , .5f*float(box[2]+box[3] + 1)
                , .5f*float(box[4]+box[5] + 1));
    }

    /// Return size of the box.
    McVec3i getSize() const {
        return McVec3i(box[1] - box[0] + 1
                , box[3] - box[2] + 1
                , box[5]-box[4] + 1);
    }

    /// Returns the volume of the box
    int volume() const {
        if (isEmpty())
            return 0;
        return (box[1]-box[0]+1) * (box[3]-box[2]+1) * (box[5]-box[4]+1);
    }

    /// Returns true if the two boxes intersect each other
    int intersects(const McBox3i &other) const {
    	if (isEmpty() || other.isEmpty()) return 0;

        return (   (box[0] <= other[1])    // xmin1 < xmax2
                && (box[1] >= other[0])    // xmax1 > xmin2
                && (box[2] <= other[3])    // ymin1 < ymax2
                && (box[3] >= other[2])    // ymax1 > ymin2
                && (box[4] <= other[5])    // zmin1 < zmax2
                && (box[5] >= other[4]));  // zmax1 > zmin2
    }

    /// Comparison.
    bool operator== (const McBox3i& other) const {
        return (   (box[0] == other[0])   
                && (box[1] == other[1])   
                && (box[2] == other[2])   
                && (box[3] == other[3])   
                && (box[4] == other[4])   
                && (box[5] == other[5])); 
    }
protected:
    /// The boxes dimensions stored as minx, maxx, miny, maxy, minz, maxz.
    int box[6];
};

#endif

/// @}
