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
#ifndef OCTAHEDRON_SPHERE_H
#define OCTAHEDRON_SPHERE_H

#include <mclib/McDArray.h>
#include <mclib/McSmallArray.h>
#include <mclib/McVec3f.h>

#include "MolSurfaceWinDLLApi.h"

class MOLSURFACE_API OctahedronSphere {

protected:  
    float radius;
    int complexity;
    int nTrisPerFace;
    float minDist, maxDist;
    float edgeEdgeLen;
    float triangleHeight;
    
    struct OctahedronEdge {
        int v[2];
        McDArray<int> p;
        McVec3f vec;
        float length;
        OctahedronEdge() {};
        void setVertices(int vertex0, int vertex1) {
            v[0] = vertex0;
            v[1] = vertex1;
        }
    };
    
    struct OctahedronFace {
        int v[3];
        int e[3];
        McDArray<int> p;
        OctahedronFace() {};
        void setVertices(int vertex0, int vertex1, int vertex2) {
            v[0] = vertex0;
            v[1] = vertex1;
            v[2] = vertex2;
        }
        void setEdges(int edge0, int edge1, int edge2) {
            e[0] = edge0; 
            e[1] = edge1; 
            e[2] = edge2; 
        }   
        void getEdges(int eIdx[3]) {
            eIdx[0] = e[0]; eIdx[1] = e[1]; eIdx[2] = e[2];
        }
    };

public:    
    struct Triangle;

    struct ContourPoint {
        int id;             // contour point id
        int sesId;          // index of vertex of ses
        int tri;            // triangle which contour point falls into
        int seesV;
        Triangle *seesTri;
        char isCornerVertex;
        // char edgeId;
        ContourPoint *next; // next contour point in same triangle
        ContourPoint *pred;
        ContourPoint *succ;
        ContourPoint *cornerPred;
        ContourPoint *cornerSucc;
        McVec3f vec;
        McVec3f normal;
        float len;
        float dist2; // squared distance to vertex seesV
        ContourPoint() {
            next = 0;
            seesV = -1;
            isCornerVertex = 0;
            dist2 = -1.0;
        }
    };

    struct Triangle {
        enum {UNSPECIFIED, OUTSIDE, INSIDE, ON_EDGE, FRONT_TRIANGLE};
        int id;       // triangle index
        int v[3];     // vertex indices
        int nf[3];    // neighbored triangles
        char nfe[3];  // edges of neighbored triangles via which they are 
                      // connected to this triangle
        char cl;      // classification, i.e. UNSPECIFIED, OUTSIDE, 
                      // INSIDE, or ON_EDGE
        ContourPoint *cp; // first contour point falling into this triangle
        short visited; // has triangle been visited yet
        signed char edgeToInside; // edge that is connected to inside of patch
        signed char edgeToParent; // from where did parent come to this tri
        signed char frontEdgeId;  // 
        signed char seesCp;       // 
        int ev[2];  // save two sphere vertex indices
        Triangle *parent; // used for tree
        Triangle *left;   // used for tree 
        Triangle *middle; // used for tree
        Triangle *right;  // used for tree
        Triangle *next;   // used for queue
        Triangle() {
            cl = UNSPECIFIED;
            cp = 0;
            visited = 0;
            parent = left = middle = right = next = 0;
            edgeToInside = -1;
            ev[0] = ev[1] = -1;
            seesCp = 0;
        }
    };

    struct Vertex { 
        enum Classification {FULLY_INSIDE, FREE_EDGE, FREE_VERTEX};
        enum InOut {ISIN, ISOUT, UNSPEC};
        int id;
        int sesId;        // index of vertex of ses
        McVec3f c;        // coordinate of vertex
        char inOut;       // is vertex inside of outside patch
        char cl;          // further classification of vertex
        int fvtri;        // used for free vertices
        char fvid;        // free vertex
        Vertex () {
            inOut = UNSPEC;
            cl = FULLY_INSIDE;
        }
    };
    
protected:
    OctahedronEdge oe[12]; // the 12 octahedron edges
    OctahedronFace of[8];  // the 8 octahedron faces
    McVec3f ofn[8];        // octahedron face normals
    McVec3f dividingPlaneNormals[3];
    McDArray<McVec3f> oc;  // octahedron coords
    
    McDArray<Vertex> vert;  // array of vertices
    McDArray<Triangle> tri; // array of triangles

    void initOctahedron(); 
    void tesselateOctahedron();    

public:
    OctahedronSphere(float radius, float edgeLength);

    float getMinDist();
    float getMaxDist();
    float getDistAngle();
    void getSphere(McDArray<Vertex> *&vertices, 
                   McDArray<Triangle> *&triangles) {
        vertices  = &vert;
        triangles = &tri;
    }
    
    void getOctahedronCoords(McDArray<McVec3f> &octCoords) {
        octCoords = oc; 
    }    
    
    int getIntersectedTriangle(McVec3f intersectionPoint);
    
    float getRadius() { return radius; }
};

#endif

/// @}
