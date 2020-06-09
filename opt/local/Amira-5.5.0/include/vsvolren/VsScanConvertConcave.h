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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef _VS_SCANCONVERT_CONCAVE_H
#define _VS_SCANCONVERT_CONCAVE_H

#include <assert.h>

#include <mclib/McVec2f.h>

#include <vsvolren/VsVolrenAPI.h>

/** Scan conversion class for concave polygons. The class supports
    clipping, rendering of polygons, and anti-aliasing. For each pixel a
    user-defined callback method is invoked. Alternatively, a pixel span
    callback can be used to improve performance.

    The class does not support interpolation of additional values
    like depth or color inside a polygon !!
*/

class VSVOLREN_API VsScanConvertConcave
{
  public:
    /// Prototype of span callback.
    typedef void SpanCB(void* userData, int x0, int x1, int y,
	unsigned char* alpha);

    /// Prototype of pixel callback.
    typedef void PixelCB(void* userData, int x, int y, unsigned char alpha);

    /** Constructor with window of valid coordinates. All coordinates
	inclusive.*/
    VsScanConvertConcave(int x0, int y0, int x1, int y1, int antiAlias=0);
    
    /// Destructor.
    ~VsScanConvertConcave();
    
    /// Enable rendering of anti-aliased polygons.
    void setAntiAlias(int onOff);

    /// Set span callback.
    void setSpanCB(SpanCB* f, void* userData);

    /// Set pixel callback. Only called if no span callback is defined.
    void setPixelCB(PixelCB*, void* userData);
    
    /// Render a polygon defined by floating point vertices.
    void render(int n, const McVec2f* vertices);
    
    static void defaultSpanCB(void*, int, int, int, unsigned char*);
  protected:
    void* userData;
    SpanCB* spanCB;
    PixelCB* pixelCB;
    static void concaveCB(int, int, int);

    int antiAlias;
    unsigned char* alphaValues;
    int winX0, winY0, winX1, winY1;
};

#endif

/// @}
