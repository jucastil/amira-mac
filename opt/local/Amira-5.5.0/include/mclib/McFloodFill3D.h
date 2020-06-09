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
#ifndef MC_FloodFILL3D_H
#define MC_FloodFILL3D_H

#include "McWinDLLApi.h"

#include "McWatch.h"
#include "McBitfield.h"
#include "McDArray.h"

/** This method performs a 3D flood fill on a given data array. For
    performance reasons the data array is a template argument. The data
    class must provide a method @c get(i,j,k), which should return the
    data value at an index position (i,j,k). In addition, it must define
    three methods @c sizeX(), @c sizeY(), and @c sizeZ(). The class
    McRawData3D already provides these requirements.

    The flooding is performed with the help of a checker class. This class
    must provide a method <tt>check(T& value)</tt> which should return 1 or 0,
    depending on whether the given value should be flooded or not.
    See Checker classes for some sample classes already implemented.`

    Beginning with an index position (x,y,z), all 6-connected
    neighbour pixels are analyzed. The data array itself is not modified.
    Instead the bitfield @c output is set to 1 for all pixels which are
    part of the flooded area. If necessary, the @c output field is resized to
    fit the data arrays dimensions. The index into the bitfield is computed
    using the expression @c (k*sizeY()+j)*sizeX()+i. In addition, the
    bounding box of the flooded volume may be stored in the vector @c box
    (if it is not null). The size elements of this vector are set to xmin,
    xmax, ymin, ymax, zmin and zmax, respectively. The method returns the
    total number of pixels which have been flooded.
    @see  mcFloodFill2D
*/
template<class T,class C>
mculong mcFloodFill3D(const T& data, C& checker, int x, int y, int z,
    McBitfield& output, int* box = 0);

template<class T,class C,class P>
mculong mcFloodFill3D_Progress(const T& data, C& checker, P& progress,
    int x, int y, int z, McBitfield& output, int* box = 0);

/** Same as mcFloodFill3D but with 18 neighbors connectivity.
  @see mcFloodFill3D.
*/
template<class T,class C>
mculong mcFloodFill3D18(const T& data, C& checker, int x, int y, int z,
    McBitfield& output, int* box = 0);

/** Same as mcFloodFill3D but with 26 neighbors connectivity.
  @see mcFloodFill3D.
*/
template<class T,class C>
mculong mcFloodFill3D26(const T& data, C& checker, int x, int y, int z,
    McBitfield& output, int* box = 0);

/**************************** Implementation *****************************/
/// @if EXCLUDETHIS
namespace {
    // change the ordering of the box array to the std.
    // xmin, xmax, ymin, ymax, zmin, zmax
    void toCorrectBoxOrder (int box[6]) {
        int tmp;
        tmp = box[1];
        box[1] = box[3];
        box[3] = box[4];
        box[4] = box[2];
        box[2] = tmp;

    };
}

struct SF3D_Segment {
    short z, y, xl, xr;
    SF3D_Segment() {}
    SF3D_Segment(short Z, short Y, short XL, short XR) :
	z(Z), y(Y), xl(XL), xr(XR) { }
};

#define PUSH3d(Z, Y, XL, XR, DZ, DY)                       	\
    if (Y+(DY)>=0 && mculong(Y+(DY))<ny && Z+(DZ)>=0 && mculong(Z+(DZ))<nz){ 	\
        stack.push(SF3D_Segment(Z+DZ,Y+DY,XL,XR));         	\
        if (Y < box[1]) box[1]=Y ;                         	\
	else if ( Y > box[4]) box[4]=Y ;                   	\
	else if ( Z < box[2]) box[2]=Z ;                   	\
	else if ( Z > box[5]) box[5]=Z ;                   	\
	if ( XL < box[0]) box[0]=XL;                       	\
	if ( XR > box[3]) box[3]=XR;                       	\
    }

#define POP3d(Z, Y, XL, XR) {					\
    SF3D_Segment& s = stack.last(); 				\
    Z = s.z; Y = s.y; XL=s.xl; XR=s.xr;				\
    stack.removeLast(); }

#undef check

struct McFloodFill3DDefaultProgress {
    void setCount(const mculong&) { }
};

template<class T,class C>
mculong mcFloodFill3D(const T& data, C& checker, int x, int y, int z,
    McBitfield& output, int* box)
{
    McFloodFill3DDefaultProgress progress;
    return mcFloodFill3D_Progress(data,checker,progress,x,y,z,output,box);
}

template<class T,class C,class P>
mculong mcFloodFill3D_Progress(const T& data, C& checker, P& progress,
                               int x, int y, int z, McBitfield& output, int* box)
{
    McWatch w;
    McDArray<SF3D_Segment> stack;

    const mculong nx = data.sizeX();
    const mculong ny = data.sizeY();
    const mculong nz = data.sizeZ();

    if (output.nBits() != nx*ny*nz) {
        output.resize(nx*ny*nz);
        output.clearAll();
    }

    int l, x1, x2;
    mculong n = 0;
    int defaultBox[6];
    if (!box) box = defaultBox;

    box[0]=x; box[1]=y; box[2]=z;
    box[3]=x; box[4]=y; box[5]=z;

    if (x<0 || mculong(x)>=nx || y<0 || mculong(y)>=ny || z<0 || mculong(z)>=nz || !checker.check(data.get(x,y,z),x,y,z)) {
        toCorrectBoxOrder(box);
        return 0;
    }

    PUSH3d(z, y, x, x, -1,  0);
    PUSH3d(z, y, x, x,  1,  0);
    PUSH3d(z, y, x, x,  0, -1);
    PUSH3d(z, y, x, x,  0,  1);
    PUSH3d(z, y, x, x,  0,  0);

    while (stack.size()) {
	POP3d(z, y, x1, x2);
        const mculong base = (z*ny+y)*nx;

        if (!output[base+x1]) { // Span not yet set
            if (checker.check(data.get(x1,y,z),x1,y,z)) {
                for (x=x1-1; x>=0 && checker.check(data.get(x,y,z),x,y,z); --x);
                l = x+1;

                for (x=x1+1; mculong(x)<nx && checker.check(data.get(x,y,z),x,y,z); ++x);
                output.setRange(base+l,base+x-1);
                n += x-l;
                progress.setCount(n);

                PUSH3d(z, y, l, x-1, -1,  0);
                PUSH3d(z, y, l, x-1,  1,  0);
                PUSH3d(z, y, l, x-1,  0, -1);
                PUSH3d(z, y, l, x-1,  0,  1);
                ++x;
            }
            else x=x1+1;
        } else { // Span was already set before, find right border...
            for (x=x1+1; x<x2 && output[base+x]; ++x);
        }

        // Skip unset pixels. Still could be optimized by looking at whole words...
        for (; x<=x2 && !checker.check(data.get(x,y,z),x,y,z); ++x);
    
        while (x<=x2) {
            assert(checker.check(data.get(x,y,z),x,y,z));
            if (!output[base+x]) {
                l = x;
                for (++x; mculong(x)<nx && checker.check(data.get(x,y,z),x,y,z); ++x);
                output.setRange(base+l,base+x-1);
                n += x-l;
                progress.setCount(n);

                PUSH3d(z, y, l, x-1, -1,  0);
                PUSH3d(z, y, l, x-1,  1,  0);
                PUSH3d(z, y, l, x-1,  0, -1);
                PUSH3d(z, y, l, x-1,  0,  1);
                ++x;
            } else { // Span was already set before, find right border...
                for (++x; x<x2 && output[base+x]; ++x);
            }
            // Skip unset pixels. Still could be optimized by looking at whole words...
            for (; x<=x2 && !checker.check(data.get(x,y,z),x,y,z); ++x);
        }
    }

    toCorrectBoxOrder (box);
    // printf("mcFloodFill3D %g msec\n", 1000*w.stop());
    return n;
}

#undef PUSH3d
#undef POP3d

// 18- and 26-neigborhood added by steffen
// brute force versions
// Mon Aug 19 14:14:31 CEST 2002, was really brute force
//      was depth first traversal which is really BAD
//      changed to breadth first

struct SF3D_Point {
    SF3D_Point (int a, int b, int c) : x(a), y(b), z(c) {};
    int x, y, z;
};

#include "McDArrayQueue.h"

#define QUEUE(X, Y, Z) \
    if ((X) >= 0 && (X) < nx && (Y) >= 0 && (Y) < ny \
         && (Z) >= 0 && (Z) < nz \
         && checker.check (data.get ((X), (Y), (Z)), (X), (Y), (Z)) \
         && !output[(mculong(Z) * mculong(ny) + mculong(Y)) * mculong(nx) + mculong(X)]) { \
        queue.put (SF3D_Point ((X), (Y), (Z))); \
        output.set ((mculong(Z) * mculong(ny) + mculong(Y)) * mculong(nx) + mculong(X)); \
        n++; \
    };

template<class T,class C>
mculong mcFloodFill3D18(const T& data, C& checker, int x, int y, int z,
    McBitfield& output, int* box)
{
    int nx = data.sizeX();
    int ny = data.sizeY();
    int nz = data.sizeZ();

    const mculong nnn = mculong(nx) * mculong(ny) * mculong (nz);
    if (output.nBits() != nnn) {
    	output.resize(nnn);
	    output.clearAll();
    }

    int n = 0;
    int defaultBox[6];
    if (!box) box = defaultBox;

    box[0]=x; box[1]=y; box[2]=z;
    box[3]=x; box[4]=y; box[5]=z;

    if (x<0 || x>=nx || y<0 || y>=ny || z<0 || z>=nz
	|| !checker.check(data.get(x,y,z),x,y,z)) {
            toCorrectBoxOrder (box);
	    return 0;
    }

    McDArrayQueue<SF3D_Point> queue;
    mculong cl = (nx * ny * nz) / 20; // use 5% of array size as max queue len
    if (cl < 1000000) {
        cl = 1000000;
    }
    queue.setCleanup (cl);

    QUEUE (x, y, z);

    SF3D_Point pt (0, 0, 0);
    while (queue.get (pt)) {
        x = pt.x; y = pt.y; z = pt.z;

        if (x < box[0]) box[0] = x;
        if (x > box[3]) box[3] = x;
        if (y < box[1]) box[1] = y;
        if (y > box[4]) box[4] = y;
        if (z < box[2]) box[2] = z;
        if (z > box[5]) box[5] = z;

        // face neighbors
        QUEUE (x + 1, y    , z    );
        QUEUE (x - 1, y    , z    );
        QUEUE (x    , y + 1, z    );
        QUEUE (x    , y - 1, z    );
        QUEUE (x    , y    , z + 1);
        QUEUE (x    , y    , z - 1);
        // edge neighbors
        QUEUE (x + 1, y    , z + 1);
        QUEUE (x - 1, y    , z + 1);
        QUEUE (x    , y + 1, z + 1);
        QUEUE (x    , y - 1, z + 1);

        QUEUE (x + 1, y    , z - 1);
        QUEUE (x - 1, y    , z - 1);
        QUEUE (x    , y + 1, z - 1);
        QUEUE (x    , y - 1, z - 1);

        QUEUE (x + 1, y + 1, z    );
        QUEUE (x - 1, y + 1, z    );
        QUEUE (x + 1, y - 1, z    );
        QUEUE (x - 1, y - 1, z    );
    }

    toCorrectBoxOrder (box);
    return n;
}


template<class T,class C>
mculong mcFloodFill3D26(const T& data, C& checker, int x, int y, int z,
    McBitfield& output, int* box)
{
    int nx = data.sizeX();
    int ny = data.sizeY();
    int nz = data.sizeZ();

    const mculong nnn = mculong(nx) * mculong(ny) * mculong (nz);
    if (output.nBits() != nnn) {
    	output.resize(nnn);
	    output.clearAll();
    }

    int n = 0;
    int defaultBox[6];
    if (!box) box = defaultBox;

    box[0]=x; box[1]=y; box[2]=z;
    box[3]=x; box[4]=y; box[5]=z;

    if (x<0 || x>=nx || y<0 || y>=ny || z<0 || z>=nz
	|| !checker.check(data.get(x,y,z),x,y,z)) {
            toCorrectBoxOrder (box);
	    return 0;
    }

    McDArrayQueue<SF3D_Point> queue;
    mculong cl = (nx * ny * nz) / 20; // use 5% of array size as max queue len
    if (cl < 1000000) {
        cl = 1000000;
    }
    queue.setCleanup (cl);

    QUEUE (x, y, z);

    SF3D_Point pt (0, 0, 0);
    while (queue.get (pt)) {
        x = pt.x; y = pt.y; z = pt.z;

        if (x < box[0]) box[0] = x;
        if (x > box[3]) box[3] = x;
        if (y < box[1]) box[1] = y;
        if (y > box[4]) box[4] = y;
        if (z < box[2]) box[2] = z;
        if (z > box[5]) box[5] = z;

        output.set ((mculong(z) * mculong(ny) + mculong(y)) * mculong(nx) + mculong(x));
        // face neighbors
        QUEUE (x + 1, y    , z    );
        QUEUE (x - 1, y    , z    );
        QUEUE (x    , y + 1, z    );
        QUEUE (x    , y - 1, z    );
        QUEUE (x    , y    , z + 1);
        QUEUE (x    , y    , z - 1);
        // edge neighbors
        QUEUE (x + 1, y    , z + 1);
        QUEUE (x - 1, y    , z + 1);
        QUEUE (x    , y + 1, z + 1);
        QUEUE (x    , y - 1, z + 1);

        QUEUE (x + 1, y    , z - 1);
        QUEUE (x - 1, y    , z - 1);
        QUEUE (x    , y + 1, z - 1);
        QUEUE (x    , y - 1, z - 1);

        QUEUE (x + 1, y + 1, z    );
        QUEUE (x - 1, y + 1, z    );
        QUEUE (x + 1, y - 1, z    );
        QUEUE (x - 1, y - 1, z    );
        // corner neighbors
        QUEUE (x + 1, y + 1, z + 1);
        QUEUE (x - 1, y + 1, z + 1);
        QUEUE (x + 1, y - 1, z + 1);
        QUEUE (x - 1, y - 1, z + 1);

        QUEUE (x + 1, y + 1, z - 1);
        QUEUE (x - 1, y + 1, z - 1);
        QUEUE (x + 1, y - 1, z - 1);
        QUEUE (x - 1, y - 1, z - 1);
    }

    toCorrectBoxOrder (box);
    return n;
}

#undef PUSH
#undef QUEUE

/// @endif

#endif

/// @}
