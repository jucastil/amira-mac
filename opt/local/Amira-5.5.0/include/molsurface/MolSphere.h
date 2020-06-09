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
#ifndef MOLSPHERE_H
#define MOLSPHERE_H

#include <math.h>

#include <mclib/McList.h>
#include <mclib/McDArray.h>
#include <mclib/McSmallArray.h>
#include <mclib/McVec3d.h>
#include <mclib/McBitfield.h>

#include "MolSurfaceWinDLLApi.h"

class AtomContour;
class ArcVertex;
struct Arcc;
struct Cycle;

class MOLSURFACE_API MolSphere {
    
public:  
    struct CyclePoint;
    
    struct Vertex { 
        enum Classification {
            UNSPECIFIED = 0x00,
            INSIDE      = 0x01, 
            NOT_INSIDE  = 0x02, 
            FREE_EDGE   = 0x04, 
            FREE_VERTEX = 0x08,
            ALL         = 0xff
        };
        
        McVec3d c;            // coordinate of vertex
        int id;               // vertex id  
        int surfId;           // index of vertex of ses
        int tId;    // triangles id (used only by free vertices)
        char cl;    // is vertex inside of outside patch
        CyclePoint * cp;
        
        Vertex () {
            cl = UNSPECIFIED;
            cp = 0;
        }
        void touch(unsigned char mask) {
            cl |= mask;
        }
        void untouch(unsigned char mask) {
            cl &= ~mask;
        }
    };

    struct CyclePoint { 
        void * _pre, * _suc;       // needed for McList
        CyclePoint * left;
        CyclePoint * right;
        CyclePoint * next;
        int tId;
        unsigned char nSeesCP:5;
        unsigned char vId:2;      // only used for inner vertex
        unsigned char handled:1;  // 
        unsigned char appended;
        int surfId;
        Vertex * innerVertex;
        ArcVertex * arcVertex;
        McSmallArray<CyclePoint * , 6> seesCP;
        McVec3d c;
        McVec3d n;
        int cycleId;
        CyclePoint() {
            innerVertex = 0;
            arcVertex = 0;
            surfId = -1;
            next = 0;
            nSeesCP = 0;
            handled = 0;
            appended = 0;
        }
        // Assignment operator -> only those information that
        // is actually needed is copied.
        CyclePoint& operator=(const CyclePoint& cp) {
            innerVertex = cp.innerVertex;
            arcVertex   = cp.arcVertex;
            surfId      = cp.surfId;
            cycleId     = cp.cycleId;
            c           = cp.c;
            return *this;
        }
        void clear() {
            innerVertex = 0;
            arcVertex = 0;
            surfId = -1;
            seesCP.clear();
            next = 0;
            nSeesCP = 0;
            handled = 0;
            appended = 0;
        }
    };
    
    struct EdgeInfo {
        int nt:29;                  // neighbored triangles
        unsigned int nte:2;         // edge index of neighbored triangles 
        unsigned int orient:1;      // orientation of edge
    };
        
    struct Edge;
    
    struct Triangle { 
        enum {
            UNSPECIFIED, 
            NOT_INSIDE, 
            INSIDE, 
            ON_EDGE
        };

        void * _pre, * _suc;  
        Triangle * next;           // used for searching for inner contour
        int id;                    // triangle index
        Vertex * v[3];             // vertices
        Edge * e[3];               // edges
        EdgeInfo ei[3];            // edge info
        unsigned char cl:3;        // classification of triangle
        unsigned char fromEdge:2;  // via which edge was triangle entered
        unsigned char frontEdge:2; // (one of) the front edge(s)
        unsigned char handled:1;   // 
        CyclePoint * cp;
        Triangle() {
            cl = UNSPECIFIED;
            handled = 0;
            next = 0;
            cp = 0;
        }
    };

    struct CutInfo {
        void * _pre, * _suc;  
        double dist2[2];
        unsigned char isInside0:1;
        unsigned char isInside1:1;
        
        CutInfo() {
            dist2[0] = dist2[1] = 1e9;
        }
    };

    struct Edge {
        void * _pre, * _suc;  
        Vertex * v[2];
        Triangle * t[2];      // the left hand triangle is the first one
        CutInfo * cutInfo;    // how was edge cut
        McVec3d planeNormal;
        
        Edge() {
            _pre = _suc = 0;
            v[0] = v[1] = 0;
            t[0] = t[1] = 0;
            cutInfo = 0;
        }
        Edge(Vertex * v0, Vertex * v1) {
            _pre = _suc = 0;
            v[0] = v0;
            v[1] = v1;
            t[0] = t[1] = 0;
            cutInfo = 0;
        }
    };
    
    struct FrontEdge {
        int v[2];         // vertices of front edge (right, left)
        Triangle *tri;    // adjacent triangle in front of front edge
        FrontEdge *next;
        FrontEdge () {
            next = 0;
        }
    };
    
    struct Ring {
        double radius;
        double longAngle;
        double longAngleOffset;
        int   numEdges;
        McDArray<Edge * > e;
    };

public:
    double theRadius;  
    double theEdgeLength;
    double theEdgeLength2;
    double theTriangleHeight;
    double theLatAngle;       // angle of latitudinal circle
    double theCircumference;
    int    theNumRings;
    int    theNumVertices;
    int    theNumEdges;
    int    theNumTriangles;

    McDArray<Ring>     rings;
    McList<Edge>       edges;
    McDArray<Vertex>   vertices;
    McDArray<Triangle> triangles;

    int nSpaceForMoreVertices;
    int nAdditionalVertices;
    int nTouchedVertices;
    McDArray<Vertex * > touchedVertices;
    int nTouchedTriangles;
    McDArray<int> touchedTriangles; 
    int nTouchedEdges;
    McDArray<Edge * > touchedEdges;
    McList<CutInfo> cutInfos;
    McDArray<CutInfo *> allCutInfos;
    
public:
    MolSphere(double radius, double edgeLength);
    ~MolSphere();

    void clear();        

    int  findTriangle(const McVec3d & p);
    void findTriangles(const McVec3d & p1, const McVec3d & p2);
    int  findTriangles(const McVec3d & sco, int fTId, Arcc * arc, Cycle * cy,
                       McDArray<CyclePoint * > & cps);

    inline int isPointBetweenEdges(MolSphere::CyclePoint * cp, 
                                   MolSphere::CyclePoint * cp2)
    {
        McVec3d leftVec  = cp->left->c.cross(cp->c);
        McVec3d rightVec = cp->c.cross(cp->right->c);
        double val[2];
        int orFlag = 0;
        if ( leftVec.dot(cp->right->c - cp->c) < 0.0 ) {
            orFlag = 1;
        }
        McVec3d cp2Vec = cp2->c - cp->c;
        val[0] = leftVec.dot(cp2Vec);
        val[1] = rightVec.dot(cp2Vec);
        if ( (val[0]>0.0 && val[1]>0.0) ||
             (orFlag && (val[0]>0.0 || val[1]>0.0)) ) {
            return 1;
        } else {
            return 0;
        }         
    }
    
    inline void findContourPoints(CyclePoint * cp)
    {
        McVec3d normal = cp->c.cross(cp->n); 
        Triangle * t = &triangles[cp->tId];
        
        if ( t->cp ) {
            if ( cp->right != cp ) {
                CyclePoint * triCP = t->cp;
                while ( triCP ) {
                    cp->seesCP.append(triCP); cp->nSeesCP++;
                    triCP->seesCP.append(cp); triCP->nSeesCP++;
                    triCP = triCP->next;
                }
            } else { // free vertex
                CyclePoint * triCP = t->cp;
                int j, oldSize = cp->seesCP.size();
                while ( triCP ) {
                    for (j=0; j<oldSize; j++) {
                        if ( triCP == cp->seesCP[j] ) break;
                    }
                    if ( j == oldSize ) { // not yet in seesCP list
                        cp->seesCP.append(triCP); cp->nSeesCP++;
                        triCP->seesCP.append(cp); triCP->nSeesCP++;
                    }
                    triCP = triCP->next;
                }
            }
            return;
        } 
        
        int vId  = cp->vId;
        int vId1 = (vId+1)%3;
        int vId2 = (vId+2)%3;
        
        double dot1, dot2;
        dot1 = (t->v[vId1]->c - cp->c).dot(normal);
        dot2 = (t->v[vId2]->c - cp->c).dot(normal);

        McVec3d jitterVec[8];
        jitterVec[0] = McVec3d(  1.0,  1.0,  1.0);
        jitterVec[1] = McVec3d(  1.0,  1.0, -1.0);
        jitterVec[2] = McVec3d(  1.0, -1.0,  1.0);
        jitterVec[3] = McVec3d(  1.0, -1.0, -1.0);
        jitterVec[4] = McVec3d( -1.0,  1.0,  1.0);
        jitterVec[5] = McVec3d( -1.0,  1.0, -1.0);
        jitterVec[6] = McVec3d( -1.0, -1.0,  1.0);
        jitterVec[7] = McVec3d( -1.0, -1.0, -1.0);
        
        McVec3d normalTmp = normal;
        double  jitterVal = 0.0001;
        int i = 0;
        while ( fabs(dot1)<0.000001 || fabs(dot2)<0.000001 ) {
            normalTmp = normal + (jitterVal * jitterVec[i++]);
            dot1 = (t->v[vId1]->c - cp->c).dot(normalTmp);
            dot2 = (t->v[vId2]->c - cp->c).dot(normalTmp);
            
            if ( i == 8 ) {
                jitterVal *= 10.0;
                i = 0;
            }
        }
        normal = normalTmp;
        
        while ( !(dot1<0.0 && dot2>0.0) ) {
            vId2 = t->ei[vId].nte;
            t = &triangles[int(t->ei[vId].nt)];
            vId  = (vId2+1)%3;
            vId1 = (vId2+2)%3;
            dot1 = (t->v[vId1]->c - cp->c).dot(normal);
            dot2 = (t->v[vId2]->c - cp->c).dot(normal);

            jitterVal = 0.0001;
            i = 0;
            while ( fabs(dot1)<0.000001 || fabs(dot2)<0.000001 ) {
                normalTmp = normal + (jitterVal * jitterVec[i++]);
                dot1 = (t->v[vId1]->c - cp->c).dot(normalTmp);
                dot2 = (t->v[vId2]->c - cp->c).dot(normalTmp);

                if ( i == 8 ) {
                    jitterVal *= 10.0;
                    i = 0;
                }
            }
            normal = normalTmp;
        }
        
        if ( t->cl==Triangle::ON_EDGE || 
             t->e[vId1]->cutInfo ) {
            return;
        }
        
        // triangle found which is cut by @c cp->n
        vId = t->ei[vId1].nte;
        t = &triangles[int(t->ei[vId1].nt)];
        vId1 = (vId+1)%3;
        vId2 = (vId+2)%3;
        while ( t->cl!=Triangle::ON_EDGE && !t->cp && !t->v[vId2]->cp ) { 
            if ( (t->v[vId2]->c - cp->c).dot(normal) > 0.0 ) {
                vId = int(t->ei[vId1].nte);
                t = &triangles[int(t->ei[vId1].nt)];
            } else {
                vId = int(t->ei[vId2].nte);
                t = &triangles[int(t->ei[vId2].nt)];
            }
            vId1 = (vId+1)%3;
            vId2 = (vId+2)%3;
        }
        if ( t->cp ) {
            if ( cp->right != cp ) {
                CyclePoint * triCP = t->cp;
                while ( triCP ) {
                    cp->seesCP.append(triCP); cp->nSeesCP++;
                    triCP->seesCP.append(cp); triCP->nSeesCP++;
                    triCP = triCP->next;
                }
            } else { // free vertex
                CyclePoint * triCP = t->cp;
                int j, oldSize = cp->seesCP.size();
                while ( triCP ) {
                    for (j=0; j<oldSize; j++) {
                        if ( triCP == cp->seesCP[j] ) break;
                    }
                    if ( j == oldSize ) { // not yet in seesCP list
                        cp->seesCP.append(triCP); cp->nSeesCP++;
                        triCP->seesCP.append(cp); triCP->nSeesCP++;
                    }
                    triCP = triCP->next;
                }
            }
        } else if ( t->v[vId2]->cp ) {
#if 0
            CyclePoint * bestCP = t->v[vId2]->cp;
            if ( bestCP->next ) {
                double val, valBest = bestCP->n.dot(bestCP->c - cp->c);
                // cp->n.dot(bestCP->n);
                CyclePoint * cp2 = bestCP->next;
                while ( cp2 ) {
                    val = cp2->n.dot(cp2->c - cp->c);
                    // cp->n.dot(cp2->n);
                    if ( val < valBest ) {
                        valBest = val;
                        bestCP = cp2;
                    }
                    cp2 = cp2->next;
                }
            }
#endif
            CyclePoint * bestCP = t->v[vId2]->cp;
            while ( bestCP && 
                    bestCP->left->innerVertex!=bestCP->right->innerVertex ) {
                if ( isPointBetweenEdges(bestCP, cp) ) break;
                bestCP = bestCP->next;
            }
            if ( bestCP ) {
                int j, oldSize = cp->seesCP.size();
                for (j=0; j<oldSize; j++) {
                    if ( bestCP == cp->seesCP[j] ) break;
                }
                if ( j == oldSize ) { // not yet in seesCP list
                    cp->seesCP.append(bestCP); cp->nSeesCP++;
                    bestCP->seesCP.append(cp); bestCP->nSeesCP++;
                }
            }
        }
    }
    
    inline void findPointsForFreeVertex(CyclePoint * cp) 
    {
        Triangle * firstT = &triangles[cp->innerVertex->tId];
        Triangle * t = firstT;
        int i, newVId, vId;
        for ( i=0; i<3; i++ ) {
            if ( cp->innerVertex == t->v[i] ) break;
        }
        vId = i;
        McVec3d midVec = (t->v[(vId+1)%3]->c + t->v[(vId+2)%3]->c)/2.0;
        cp->n = midVec - cp->c;
        cp->tId = t->id;
        cp->vId = vId;
        findContourPoints(cp);

        newVId = (t->ei[vId].nte+1)%3;
        t = &triangles[int(t->ei[vId].nt)];
        vId = newVId;
        while ( t != firstT ) {
            midVec = (t->v[(vId+1)%3]->c + t->v[(vId+2)%3]->c)/2.0;
            cp->n = midVec - cp->c;
            cp->tId = t->id;
            cp->vId = vId;
            findContourPoints(cp);

            newVId = (t->ei[vId].nte+1)%3;
            t = &triangles[int(t->ei[vId].nt)];
            vId = newVId;
        }
    }

    inline void findInnerPoints(CyclePoint * cp)
    {
        Triangle * t = &triangles[cp->tId];

        // check whether there are any points inside the triangle
        // appart from the point @c cp
        if ( t->cp->next ) {
            CyclePoint * triCP = t->cp;
            int j, oldSize, differentCycle = 0;
            oldSize = cp->seesCP.size();
            while ( triCP ) { 
                if ( triCP != cp && triCP != cp->right && triCP != cp->left ) {
                    for (j=0; j<oldSize; j++) {
                        if ( triCP == cp->seesCP[j] ) break;
                    }
                    if ( j == oldSize ) { // not yet in seesCP list
                        cp->seesCP.append(triCP); cp->nSeesCP++;
                        triCP->seesCP.append(cp); triCP->nSeesCP++;
                    }
                    if ( cp->cycleId != triCP->cycleId ) {
                        differentCycle = 1;
                    }
                }
                
                triCP = triCP->next;
            }
            if ( differentCycle ) return;
        }

        int i, j, flag = 0, oldSize = cp->seesCP.size();
        for (i=0; i<3; i++) {
            if ( t->v[i]->cp ) {
                flag++;
#if 0
                CyclePoint * bestCP = t->v[i]->cp;
                if ( bestCP->next ) {
                    double val, valBest = bestCP->n.dot(bestCP->c - cp->c);
                    // cp->n.dot(bestCP->n);
                    CyclePoint * cp2 = bestCP->next;
                    while ( cp2 ) {
                        val = cp2->n.dot(cp2->c - cp->c);
                        //cp->n.dot(cp2->n);
                        if ( val < valBest ) {
                            valBest = val;
                            bestCP = cp2;
                        }
                        cp2 = cp2->next;
                    }
                }
#endif
                CyclePoint * bestCP = t->v[i]->cp;
                while ( bestCP && 
                        bestCP->left->innerVertex!=bestCP->right->innerVertex ) {
                    if ( isPointBetweenEdges(bestCP, cp) ) break;
                    bestCP = bestCP->next;
                }
                
                if ( bestCP ) {
                    for (j=0; j<oldSize; j++) {
                        if ( bestCP == cp->seesCP[j] ) break;
                    }
                    if ( j == oldSize ) { // not yet in seesCP list
                        cp->seesCP.append(bestCP); cp->nSeesCP++;
                        bestCP->seesCP.append(cp); bestCP->nSeesCP++;
                    }
                }
            }
        }
        if ( flag ) return;
        
        McVec3d normal = cp->c.cross(cp->n); 
        int vId1;
        if ( normal.dot(t->v[0]->c - cp->c) > 0.0 ) { 
            // vertex 0 is inside
            if ( normal.dot(t->v[2]->c - cp->c) > 0.0 ) { 
                // vertex 2 is inside -> vertex 1 is outside
                vId1 = 1; 
            } else {
                // vertex 2 is outside
                vId1 = 2; 
            }
        } else {
            // vertex 0 is outside
            if ( normal.dot(t->v[1]->c - cp->c) > 0.0 ) { 
                // vertex 1 is inside -> vertex 2 is outside
                vId1 = 0;
            } else {
                // vertex 1 is outside
                vId1 = 1; 
            }
        }
        
        int vId2 = (vId1+1)%3;
        
        if ( ~(t->v[vId1]->cl) & Vertex::INSIDE &&
             ~(t->v[vId2]->cl) & Vertex::INSIDE ) {
            return;
        }

        // triangle found which is cut by @c cp->n
        int vId = t->ei[vId1].nte;
        t = &triangles[int(t->ei[vId1].nt)];
        vId1 = (vId+1)%3;
        vId2 = (vId+2)%3;
        while ( 1 ) {
            if ( t->cp ) {
                oldSize = cp->seesCP.size();
                CyclePoint * triCP = t->cp;
                while ( triCP ) {
                    if ( triCP != cp->right && triCP != cp->left ) {
                        for (j=0; j<oldSize; j++) {
                            if ( triCP == cp->seesCP[j] ) break;
                        }
                        if ( j == oldSize ) { // not yet in seesCP list
                            cp->seesCP.append(triCP); cp->nSeesCP++;
                            triCP->seesCP.append(cp); triCP->nSeesCP++;
                        }
                    }
                    
                    triCP = triCP->next;
                }
                return;
            } 
            
            if ( t->v[vId2]->cp ) {
                oldSize = cp->seesCP.size();
                
                CyclePoint * bestCP = t->v[vId2]->cp;
                while ( bestCP && 
                        (bestCP->left->innerVertex!=
                         bestCP->right->innerVertex) ){
                    if ( isPointBetweenEdges(bestCP, cp) ) break;
                    bestCP = bestCP->next;
                }
                
                if ( bestCP ) {
                    for (j=0; j<oldSize; j++) {
                        if ( bestCP == cp->seesCP[j] ) break;
                    }
                    if ( j == oldSize ) { // not yet in seesCP list
                        cp->seesCP.append(bestCP); cp->nSeesCP++;
                        bestCP->seesCP.append(cp); bestCP->nSeesCP++;
                    }
                    return;
                } 
            }
                
            // find next triangle
            if ( (t->v[vId2]->c - cp->c).dot(normal) > 0.0 ) {
                if ( t->cl==Triangle::ON_EDGE && 
                     ~(t->v[vId1]->cl) & Vertex::INSIDE &&
                     ~(t->v[vId2]->cl) & Vertex::INSIDE ) { 
                    return;
                }
                vId = t->ei[vId1].nte;
                t = &triangles[int(t->ei[vId1].nt)];
            } else {
                if ( t->cl==Triangle::ON_EDGE && 
                     ~(t->v[vId2]->cl) & Vertex::INSIDE &&
                     ~(t->v[vId]->cl) & Vertex::INSIDE ) { 
                    return;
                }
                vId = t->ei[vId2].nte;
                t = &triangles[int(t->ei[vId2].nt)];
            }
            vId1 = (vId+1)%3;
            vId2 = (vId+2)%3;
        }
    }
}; 
#endif


/// @}
