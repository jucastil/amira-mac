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

/// @addtogroup hxvector hxvector
/// @{
#ifndef STREAM_SURFER_H
#define STREAM_SURFER_H

#include <hxvector/HxVectorWinDLLApi.h>
#include <mclib/McODE3.h>
#include <mclib/McDArray.h>
#include <setjmp.h>

#define COLOR_EVEN 0
#define COLOR_SPLIT 2
#define COLOR_MERGE 4
#define COLOR_MERGE_2 5
#define COLOR_STOP 6

///
class HXVECTOR_API StreamSurfer {

  public:
    /// Constructor.
    StreamSurfer(int hultquist=0);

    /// Define vector field to be traced.
    void setRightHandSide(int (*f)(const McVec3f& r, McVec3f& f, void*),
	int (*df)(const McVec3f& r, McVec3f df[], void*), void* userData=0);

    /// Set range check method.
    void setBoundingBox(const McVec3f& boxMin, const McVec3f& boxMax);

    void setBadRatio(float val) { badRatio=val; }

    /// Define seed line.
    void setRake(int n, McVec3f* rake, int isClosed);

    /// Compute the surface.
    void compute(int n, float hSampling);

    McDArray<McVec3f> points;

    McDArray<int> triangles;

    McDArray<int> lines;

    McDArray<unsigned char> triColors;

    void postscript(const char* fn, float xOffset, float xRange,
	float yOffset, float yRange, int doNum=0);

    int isOutside(const McVec3f& r);

  protected:
    struct Tracer {
	McODE3 ode;
	unsigned char stop;
	unsigned char noRibbonOnRight;
	int lastPoint;
	int currentPoint;

	Tracer() { stop=0; noRibbonOnRight=0; lastPoint=-1; }
    };

    McDArray<Tracer*> tracers;
    McDArray<int> boundaryIdx;

    int isClosed;
    int nTracers;
    int nFirst;
    int nLast;
    float hSampling;
    float orientation;
    float tolerance;
    McVec3f boxMin;
    McVec3f boxMax;
    int doBoxCheck;
    int outerLoopIndex;
    int hultquist;
    float badRatio;
    jmp_buf env;

    Tracer* newTracer(const McVec3f& r);
    int shouldStop(int i);
    void stopTracers(int offset);
    void deleteTracers(int offset);
    void go(Tracer*);
    int advanceRibbon(int k, int c=0);
    int addLine(int idx1, int idx2);
    int addTriangle(int idx1, int idx2, int idx3, int color);
    int isBad(const McVec3f&, const McVec3f&, const McVec3f&, const McVec3f&);
    int getCriticalPoint(McVec3f& r);

public:
    void* userData;
    int (*func)(const McVec3f& r, McVec3f& f, void*);
    int (*dfunc)(const McVec3f& r, McVec3f f[], void*);
};

#endif

/// @}
