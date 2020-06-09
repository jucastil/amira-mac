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

/// @addtogroup hxfastLIC hxfastLIC
/// @{
#ifndef HX_LINESTREAKS_H
#define HX_LINESTREAKS_H

#include <hxfastLIC/HxFastLICWinDLLApi.h>
#include <mclib/McDArray.h>
#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcolor/HxPortColormap.h>
#include <hxfield/HxVectorField3.h>
#include <hxlines/HxLineSet.h>
#include <hxsurface/HxSurface.h>
#include <hxsurftools/HxSurfaceVectorField.h>

/// This module generates line streaks on a surface.

class HXFASTLIC_API HxLineStreaks : public HxCompModule {

  HX_HEADER(HxLineStreaks);

  public:
    /// Constructor.
    HxLineStreaks();

    /// Compute method.
    virtual void compute();

    /// Auto connect method.
    int autoConnect(HxObject* primary);

    /// Connection to vector field.
    HxConnection portVectorField;

    /// Streak length
    HxPortIntTextN portStreakLength;

    /// Number of streaks
    HxPortIntTextN portNumStreaks;

    /// Options: 0=constant/variable lenght
    // HxPortToggleList portOptions;

    /// DoIt button
    HxPortDoIt portDoIt;

    virtual int parse(Tcl_Interp* t, int argc, char **argv);

  public:
    struct UnitVector { // per triangle in world coords
	float u[3];
	float v[3];
    };

    struct Triangle {
	int points[3];
	int neighbours[3];
	int inverted;
	float area;
	float u1,u2,v2;
	int isInverted() { return inverted; }
    };

  protected:
    virtual ~HxLineStreaks();

    int isOutside(float b[3]) { return (b[0]<0)||(b[1]<0)||(b[2]<0); }
    void getPhysicalCoords(int t, const float b[3], float x[3]);
    void getLocalCoords(int t, const float x[3], float u[2]);
    void getVector3D(int t, HxLocation3* loc, float vec[2]);
    void getVector(int t, const float b[3], float vec[2]);
    void sampleOneway(int t, float u[2], float b[3], float x[3], int&);
    int moveToNeighbour(int&, float p[2], float q[2], float b[3], int&, int);
    void fixOrientation(float res[3], float vec[2]);
    void copyStreak(int which, SbVec3f*, int iLeft, int iRight);

    void getBarycentricCoords(int t, const float u[2], float b[3]) {
	const Triangle& tri = triangles[t];
        b[2] = u[1]/tri.v2;
	b[1] = (u[0]-tri.u2*b[2])/tri.u1;
	b[0] = 1-b[1]-b[2];
    }

    void doIt();
    void initTriangles();
    void initUnitVectors();
    void processTriangles();

    float h_sampling;
    float resolution;		// influences gemetric resolution (256)
    float pixelSize;		// width of a pixel in world coordinates
    float objectSize;		// object dimension: diagonal / sqrt(3)
    float totalArea;
    int streakLength;
    int nSamples;
    float lastVec[3];
    SbVec3f* streakCoords;

    HxSurface* surface;		// the surface to be LICed
    Triangle* triangles;	// array of all triangles
    UnitVector* unitVectors;

    HxSurfaceVectorField* vectorField;
    HxVectorField3* vectorField3D;
    HxLocation3* location;
    HxLineSet* lineSet;
};

#endif

/// @}
