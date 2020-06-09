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

/// @addtogroup hxsurftools hxsurftools
/// @{
#ifndef SURFACE_PLANE_CUT_H
#define SURFACE_PLANE_CUT_H

#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>

#include <hxsurftools/HxSurfToolsWinDLLApi.h>

class Surface;
class HxLineSet;

class HXSURFTOOLS_API SurfacePlaneCut {

  public:

    /// Constructor.
    SurfacePlaneCut(Surface* surface) { 
        surf = surface; 
    }

    /// Set origin and normal vector of plane
    void setPlane( const McVec3f& p, const McVec3f& n ) {
        nVec = n;
        orig = p;
    }

    /// Compute intersection lines
    void compute(McDArray< McDArray<McVec3f> >& points, 
                 McDArray< McDArray<int> >& triangles );

  protected:

    ///
    Surface* surf;

    ///
    McVec3f nVec;

    ///
    McVec3f orig;

    ///
    void makeOverlay(McDArray<McVec3f>& coords, McDArray<int>& iTris);

    ///
    void reconstruct(McDArray<McVec3f>& array, ///the array op found intersections
                            McDArray<int>& tris,///corresponding triangle-IDs
                            McDArray< McDArray<McVec3f> >& points, ///the reconstructed lines
                            McDArray< McDArray<int> >& triangles);///the corresponding triangles to these lines

    ///
    class Line {
    private:
        int points[2];
    public:
        int get(int i){return points[i];};
        int set(int p1, int p2)
        {
            if(p1 == p2) return 0;
            
            points[0] = p1<p2 ? p1:p2; // min
            points[1] = p1<p2 ? p2:p1; // max
            return 1;
        };
        Line()
        {
            points[0] = points[1] = -1;
        };
        int operator==(const Line& other) const
        {
            return (points[0] == other.points[0]) &&
                (points[1] == other.points[1]);
        };
        int operator<(const Line& other) const {
            // Pre.: points[0] < points{1}
            return (points[0] < other.points[0]) ||
                ( (points[0] == other.points[0]) && 
                (points[1] < other.points[1]) );
        }
    };
    
    ///
    class Point {
    public:
        McVec3f p;
        int f;
        static const float tolerance;
        
        int operator== (const Point& other) const {
            return p.equals(other.p, tolerance); }
        int operator!= (const Point& other) const {
            return (operator==(other)) ? 0 : 1; }
        int operator> (const Point& other) const {
            if (operator==(other)) return 0;
            //return ((memcmp(&p,&other.p,3*sizeof(float))>0) ? 1 : 0); }
            return (p>other.p ? 1 : 0); }
        int operator< (const Point& other) const {
            if (operator==(other)) return 0;
            //return ((memcmp(&p,&other.p,3*sizeof(float))<0) ? 1 : 0); }
            return (p<other.p ? 1 : 0); }
    };

};

#endif

/// @}
