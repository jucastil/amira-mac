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
#ifndef MC_SCANCONVERT_H
#define MC_SCANCONVERT_H

#include <assert.h>
#include "McVec2f.h"
#include "McWinDLLApi.h"

/** Scan conversion class for convex or concarve polygons. The class
    supports clipping and rendering of polygons. For each pixel a
    user-defined callback method is invoked. Alternatively, a pixel
    span callback can be used to improve performance.

    The class does not support interpolation of additional values
    like depth or color inside a polygon !
*/

class MCLIB_API McScanConvert
{
  public:
    /** Prototype of span callback. For each rendered horizontal line
	@f$( x_0, y)$ - $( x_1, y)@f$ @c SpanCB is called.
	@c userData may be set with setSpanCB().
    */
    typedef void SpanCB(void* userData, int x0, int x1, int y);

    /** Prototype of pixel callback. For each rendered pixel @f$( x, y)@f$
	@c PixelCB is called. @c userData may be set with setPixelCB().
    */
    typedef void PixelCB(void* userData, int x, int y);

    /** Constructor with window of valid coordinates.
        All coordinates	inclusive.*/
    McScanConvert(int x0, int y0, int x1, int y1);

    /// Destructor.
    ~McScanConvert();

    /// Set span callback.
    void setSpanCB(SpanCB* f, void* userData);

    /// Set pixel callback (called if no span callback is defined).
    void setPixelCB(PixelCB*, void* userData);

    /// Render a polygon defined by floating point vertices.
    void render(int n, const McVec2f* vertices);

    static void defaultSpanCB(void*, int, int, int);

  protected:
    void* userData;
    SpanCB* spanCB;
    PixelCB* pixelCB;

    int winX0, winY0, winX1, winY1;
    static void concaveCB(int, int, int);
};

#endif

/// @}
