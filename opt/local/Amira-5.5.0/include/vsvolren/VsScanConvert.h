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
#ifndef VS_SCAN_CONVERT_H
#define VS_SCAN_CONVERT_H

#include "Vs.h"

#include <mclib/McMath.h>

/// \if UNDOCUMENTED

class VSVOLREN_API VsScanConvert
{
  public:
    struct Vertex {
        float x,y;
        float data[6];
    };

    typedef void PixelCB(int x, int y, float* data, void* userData);
    typedef void LineCB(int lx, int rx, int y, float* data, float *delta, void* userData);

    VsScanConvert(int nDataVar=6);
    ~VsScanConvert();

    void setNumDataVar(int nDataVar) { this->nDataVar = nDataVar; }

    void setCanvas(int width, int height);

    void setPixelCallback(PixelCB* callback, void* userData=0);

    void setLineCallback(LineCB* callback, void* userData=0);

    void scanConvertPixelCB(int nVertices, const Vertex* vertices);

    void scanConvertLineCB(int nVertices, const Vertex* vertices);

  protected:
    int nDataVar;
    int width, height;
    void* userData;
    PixelCB* pixelCallback;
    LineCB* lineCallback;

    void scanlinePixelCB(int y, Vertex& l, Vertex& r);

    void scanlineLineCB(int y, Vertex& l, Vertex& r);

    void increment_y(const Vertex& p1, const Vertex& p2,
        Vertex& p, Vertex& dp, int y);

    void increment_x(const Vertex& p1, const Vertex& p2,
        Vertex& p, Vertex& dp, int x);
};

inline void VsScanConvert::scanlinePixelCB(int y, Vertex& l, Vertex& r)
{
    int k, x, lx, rx;
    Vertex p, dp;

    //lx = (int) ceil(l.x-.5);
    lx=McRoundEven(l.x);
    if (lx<0)
        lx = 0;
    /* Make sure that pixels in last column are set as well. This is
       different from computer graphics application where we want to
       avoid that pixels are set twice for adjacent polygons. */
    //rx = (int) ceil(r.x-.5); // floor(r.x-.5);
    rx=McRoundEven(r.x);
    if (rx>=width)
        rx = width-1;
    if (lx>rx)
        return;
    increment_x(l, r, p, dp, lx);

    // for (x=lx; x<rx; x++) { // rx is clamped to canvas size therefor the last pixel to access is rx-1 (Manfred 2005/11/16)
    for (x=lx; x<=rx; x++) { // x<rc is wrong, rc is clamped to width-1, see above (Detlev 24-Nov-2005)
        if (pixelCallback)
            pixelCallback(x,y,p.data,userData);
        for (k=0; k<nDataVar; k++)
            p.data[k] += dp.data[k];
    }
}

inline void VsScanConvert::scanlineLineCB(int y, Vertex& l, Vertex& r)
{
    //lx = (int) ceil(l.x-.5);
    int lx = McRoundEven(l.x);
    if (lx < 0)
        lx = 0;

    /* Make sure that pixels in last column are set as well. This is
       different from computer graphics application where we want to
       avoid that pixels are set twice for adjacent polygons. */
    //rx = (int) ceil(r.x-.5); // floor(r.x-.5);
    int rx = McRoundEven(r.x);
    if (rx > width)
        rx = width;
    if (lx > rx)
        return;

    Vertex p, dp;
    increment_x(l, r, p, dp, lx);

    lineCallback(lx, rx, y, p.data, dp.data, userData);
}

//  Increment_y: put intersection of line Y=y+0.5 with edge between
//  points p1 and p2 in p, put change with respect to y in dp
//
inline void VsScanConvert::increment_y(const Vertex& p1, const Vertex& p2,
    Vertex& p, Vertex& dp, int y)
{
    float dy = p2.y - p1.y;
    if (dy==0.0f)
        dy = 1.0f;
    float frac = y+0.5f - p1.y;

    dp.x = (p2.x - p1.x)/dy;
    p.x = p1.x + dp.x*frac;

    for (int k=0; k<nDataVar; k++) {
        dp.data[k] = (p2.data[k] - p1.data[k])/dy;
        p.data[k] = p1.data[k] + dp.data[k]*frac;
    }
}

//  Increment_x: put intersection of line X=x+0.5 with edge between
//  points p1 and p2 in p, put change with respect to y in dp
//
inline void VsScanConvert::increment_x(const Vertex& p1, const Vertex& p2,
    Vertex& p, Vertex& dp, int x)
{
    float dx = p2.x - p1.x;
    if (dx==0.0f)
        dx = 1.0f;
    float frac = x+0.5f - p1.x;

    for (int k=0; k<nDataVar; k++) {
        dp.data[k] = (p2.data[k] - p1.data[k])/dx;
        p.data[k] = p1.data[k] + dp.data[k]*frac;
    }
}

/// \endif

#endif

/// @}
