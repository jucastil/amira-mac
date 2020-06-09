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

/// @addtogroup molsurface molsurface
/// @{
#ifndef MOL_SURFACE_DATA_STRUCTURES_H
#define MOL_SURFACE_DATA_STRUCTURES_H

#include <mclib/McVec3d.h>

class  ToroidalPatch;
struct Circle;
struct SphereContours;

class ArcVertex 
{
public:
    void * _pre, * _suc;       // needed for McList
    int surfId;
    McVec3d c;
    ArcVertex() {
        surfId = -1;
    }
    ~ArcVertex() { /* empty */ }
};

class ArcEndPoint : public ArcVertex 
{
public:
    SphereContours * spPatch;
    int nearestAtom;
    unsigned char handled:2;
    unsigned char mapped:2;    // has endpoint been mapped to ses yet

    ArcEndPoint() : ArcVertex() {
        nearestAtom = -1;
        spPatch = 0;
        handled = 0;
        mapped = 0;
    }
};

struct Arcc 
{
    Arcc * prevArc;             // predecessor arc on the cycle
    Arcc * nextArc;             // successive arc on the cycle
    ArcEndPoint * v[2];         // end points of the arc
    McDArray<ArcVertex *> midV; // middle points
    int neighAtom;              // neighboring atom which created the arc
    Arcc * nextCircleArc;       // successive arc on the circle
    Circle * circle;            // circle the arc belongs to
    Arcc * corrArc;             // equivalent arc with different orientation
    ToroidalPatch * tPatch;     // patch that is part of a torus
    unsigned int status:1;      // 0->up-to-date, 1->needs update
    unsigned int isTess:1;      // is arc tesselated
    unsigned int tess:1;        // tesselate arc 
    unsigned int handled:1;     // 
    unsigned int aId:2;         // 
    
    Arcc() {
        prevArc = nextArc = 0;
        v[0] = v[1]       = 0;
        neighAtom         = -1;
        nextCircleArc     = 0;
        circle            = 0;
        corrArc           = 0;
        tess              = 1;
        status            = 0;
        isTess            = 0;
        handled           = 0;
        aId               = 0;
        tPatch            = 0;
    }

    Arcc(unsigned int atomId) {
        prevArc = nextArc = 0;
        v[0] = v[1]       = 0;
        neighAtom         = -1;
        nextCircleArc     = 0;
        circle            = 0;
        corrArc           = 0;
        tess              = 1;
        status            = 0;
        isTess            = 0;
        handled           = 0;
        aId               = atomId;
        tPatch            = 0;
    }

    void clear() {
        status = 0;
        isTess = 0;
        midV.clear();
    }

    void copyAndInsertAfter(Arcc * a) {
        v[0]       = a->v[0];
        v[1]       = a->v[1];
        circle     = a->circle;
        prevArc    = a;
        nextArc    = a->nextArc;
        //rv         = a->rv;
        tess       = a->tess;
        neighAtom  = a->neighAtom;
        nextArc->prevArc = this;
        a->nextArc = this;
    }
    
    void removeArcFromCycle() {
        Arcc * p = prevArc;
        Arcc * n = nextArc;
        p->nextArc = n;
        n->prevArc = p;
    }

    /// Assignment.
    Arcc& operator=(const Arcc& a) {
        v[0]      = a.v[0];
        v[1]      = a.v[1];
        circle    = a.circle;
        //rv        = a.rv;
        tess      = a.tess;
        neighAtom = a.neighAtom;
        return *this;
    }
};

struct Circle {
    int atoms[2];              // atoms which create the circle
    Arcc * firstArc[2];        // first arc of circle of atoms i
    Arcc * lastArc[2];         // last arc of circle
    Circle * nextCircle;       // next circle of atom
    McVec3d planeNormal;       // normal vector pointing away from first atom
    McVec3d c[2];              // center of circle
    double radius[2];
    char handled[2];
    unsigned int added:1;      // has circle been added yet to neighbor

    Circle() {
        atoms[0] = atoms[1] = -1;
        firstArc[0] = firstArc[1] = lastArc[0] = lastArc[1] = 0;
        nextCircle = 0;
        handled[0] = handled[1] = 0;
        added = 0;
    }
    ~Circle() {};
};

struct Cycle {
    Arcc * firstArc;            // first arc of cycle
    Cycle * nextCycle;         // pointer to next cycle of same contour 
    unsigned int modified:2;   // modified flag
    unsigned int edgesCut:1;   // does cycle cut any edges
   
    Cycle() {
        firstArc  = 0;
        nextCycle = 0;
        modified  = 0;
        edgesCut  = 0;
    }
    ~Cycle() {};
};

struct Contour {
    Cycle * firstCycle;        // first cycle of contour
    Contour * nextContour;     // next contour of atom
    int patchIx;               // index of atomic patch
    
    Contour() {
        firstCycle  = 0;
        nextContour = 0;
    }
    ~Contour() {};
};

struct SphereContours {
    Contour * firstContour;     // first contour of atom (might not get used)
    Cycle   * firstCycle;       // first cycle of atom
    Circle  * firstCloseCircle; // first circle of atom - 
    Circle  * lastCloseCircle;  // list of previously computed circles 
    Circle  * firstFarCircle;   // first circle of atom - 
    Circle  * lastFarCircle;    // list of previously computed circles 
    int sphereId;
    int radId:24;
    int isFullSphere:4;
    int touchedByPartialSurfaceAtom:4;
    
    SphereContours() {
        firstContour                = 0;
        firstCycle                  = 0;
        firstCloseCircle            = 0;
        lastCloseCircle             = 0;
        firstFarCircle              = 0;
        lastFarCircle               = 0;
        isFullSphere                = 0;
        touchedByPartialSurfaceAtom = 0;
        sphereId                    = -1;        
    }
    ~SphereContours() {};
};

class ToroidalPatch 
{
public:
    McVec3d center;
    double radius;
    Arcc * arcs[2];
    ToroidalPatch() {};
    ~ToroidalPatch() {};
};

class ToroidalPatch2 : public ToroidalPatch 
{
public:
    McVec3d coords[2];
    Arcc * arcs2[4];
    char handled;
    ToroidalPatch2() {
        handled = 0;
    }
};

struct CrossingPoint {
    Arcc * intersectedArc;      // arc the point lies on 
    Cycle * intersectedCycle;  // cycle the point lies on
    McVec3d coord;             // coordinate of crossing point
    CrossingPoint * nextCP;    // for sorting
    unsigned int vertexType:1; // does c. p. replace v 1 or 2 of old arc
    unsigned int arcId:4;      // number of intersected arc

    CrossingPoint(Arcc * arc, Cycle * cycle, McVec3d & c, unsigned int vT) {
        intersectedArc = arc;
        intersectedCycle = cycle;
        coord = c;
        nextCP = 0;
        vertexType = vT;
        arcId = 0;
    }
};

#endif 

/// @}
