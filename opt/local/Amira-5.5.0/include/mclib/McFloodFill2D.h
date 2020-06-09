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
#ifndef MC_FLOODFILL2D_H
#define MC_FLOODFILL2D_H

#include "McWinDLLApi.h"

#include "McBitfield.h"
#include "McDArray.h"
#include "McVec2i.h"

/** This method performs a 2D flood fill on a given data array. For
    performance reasons the data array is a template argument. The data
    class must provide a method @c get(i,j), which should return the
    data value at an index position (i,j). In addition, it must define
    two methods @c sizeX() and @c sizeY(). The class McRawData2D
    already provides these requirements.

    The flooding is performed with the help of a checker class. This class
    must provide a method <tt>check(T& value)</tt> which should return 1 or 0,
    depending on whether the given value should be flooded or not.
    See Checker classes for some sample classes already implemented.`

    Beginning with an index position (@c startx,@c starty), all 4-connected
    neighbour pixels are analyzed. The data array itself is not modified.
    Instead the bitfield @c output is set to 1 for all pixels which are
    part of the flooded area. If necessary, the @c output field is resized to
    fit the data arrays dimensions. The index into the bitfield is computed
    using the expression @c j*sizeX()+i. In addition, the bounding box
    of the flooded area may be stored in the vector @c box (if it is not null).
    The four elements of this vector are set to xmin, ymin, xmax, and ymax,
    respectively. The method returns the total number of pixels which
    have been flooded.
    @see  mcFloodFill3D
*/
//template<class T,class C>
//int mcFloodFill2D(const T& data, C& checker, int x, int y,
//    McBitfield& output, int box[4] = 0);
template<class T,class C>
int mcFloodFill2D(T& data, C& checker, int startx, int starty,
    McBitfield& output, int box[4]=0)
{
    int n = 0;
    int nx = data.sizeX();
    int ny = data.sizeY();
    const int xmax = nx-1;
    const int ymax = ny-1;

    if (output.nBits() != nx*ny) {
        output.resize(nx*ny);
        output.clearAll();
    }

    int defaultBox[4];
    if (!box) box = defaultBox;

    box[0] = startx;
    box[1] = starty;
    box[2] = startx;
    box[3] = starty;

    McDArray<McVec2i> stack;
    McVec2i v(startx,starty);

    if (v.x<0 || v.x>xmax || v.y<0 || v.y>ymax ||
	!checker.check(data.get(v.x,v.y),v.x,v.y))
	    return 0;

    output.set(v.y*nx+v.x);
    stack.push(v);
    ++n;

    while (stack.pop(v))
    {
	int k = v.y*nx+v.x;
        // Might be incorrect if get() returns float
        // TODO: Add additional template argument for prim type
        //  Standard mcFloodFill2D() should just use check()
        //  An extended version mcFloodFill2D2() should be implemented which uses check2()
	int last = data.get(v.x,v.y);

	if (v.x<box[0]) box[0] = v.x;
	    else if (v.x>box[2]) box[2] = v.x;
	if (v.y<box[1]) box[1] = v.y;
	    else if (v.y>box[3]) box[3] = v.y;

	if (v.x>0 && !output[k-1]) {
            if (checker.check2(data.get(v.x-1,v.y),last,v.x-1,v.y)) {
		stack.push(McVec2i(v.x-1,v.y));
                output.set(k-1);
                ++n;
            }
	}

	if (v.x<xmax && !output[k+1]) {
            if (checker.check2(data.get(v.x+1,v.y),last,v.x+1,v.y)) {
		stack.push(McVec2i(v.x+1,v.y));
                output.set(k+1);
                ++n;
            }
	}

	if (v.y>0 && !output[k-nx]) {
            if (checker.check2(data.get(v.x,v.y-1),last,v.x,v.y-1)) {
		stack.push(McVec2i(v.x,v.y-1));
                output.set(k-nx);
                ++n;
            }
	}

	if (v.y<ymax && !output[k+nx]) {
            if (checker.check2(data.get(v.x,v.y+1),last,v.x,v.y+1)) {
		stack.push(McVec2i(v.x,v.y+1));
                output.set(k+nx);
                ++n;
            }
	}
    }

    return n;
}

#endif

/// @}
