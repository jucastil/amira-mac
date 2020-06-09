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

/// @addtogroup hxsurface hxsurface
/// @{
#ifndef FACE_OCTREE_H
#define FACE_OCTREE_H

#include <hxsurface/HxSurfaceWinDLLApi.h>

#include <stdio.h>
#include <mclib/McDArray.h>
#include <mclib/McSmallArray.h>
#include <mclib/McBitfield.h>
#include <hxcore/HxMessage.h>
#include <hxcore/HxWorkArea.h>
#include <hxfield/HxTetraGrid.h>
#include <hxsurface/HxSurface.h>
#include <mclib/McBox3f.h>
#include <mclib/McVec3f.h>

#define MEMINCREMENT 15

template<class T> class FaceOctree {

public:
    
    ///
    FaceOctree(int maxDepth=6, int maxTriPerLeaf=50) {
        
        //theMsg->printf("FaceOctree warning: type not known...");
        
        this->maxDepth = maxDepth;
        this->maxTriPerLeaf = maxTriPerLeaf;
        // there exist special constructors for FaceOctree<HxSurface>
        // and FaceOctree<Surface> which set isSurface to 1;
        // isSurface is automatically set to one in function 
        // insertAllTriangles, if you use other functions for inserting
        // the triangles you might get problems if you have a surface
        // of type other than HxSurface of Surface
        isSurface=0;
        mesh=NULL;
    }

    //--------------------------------------------------------------------------

    ///
    ~FaceOctree() {
        cleanup();
    }

    //--------------------------------------------------------------------------

    ///
    void cleanup() {
        for (int i=allElements.size()-1; i>=0; i--) {
            if (allElements[i].leaf.triangles)
                free(allElements[i].leaf.triangles);
        }

        allElements.remax(0,0);
    
        triBoxes.remax(0,0);
    }

    //--------------------------------------------------------------------------

    ///
    void insertAllTriangles(T* t, const McVec3f* normals, bool useWorkArea=true) {

        this->mesh = dynamic_cast<T*>(t);

        if (!mesh) {
            theMsg->printf("FaceOctree error: mesh==NULL");
            return;
        }

        typename T::Triangle* triangles = t->triangles;
        
        this->normals = normals;
        t->getBoundingBox(&meshBox[0]);
        meshBox.extendByEps(0.01);

        cleanup();
        allElements.appendSpace(1);
        memset(&allElements[0], 0, sizeof(Element));

        int iUpdate = 0;
        int nTriangles = t->triangles.size();

        if (useWorkArea)
            theWorkArea->startWorkingNoStop("Building octree...");

        lookupFlags.resize(nTriangles);
        lookupFlags.clearAll();
        computeEps();
        computeTriBoxes();

        isSurface = (dynamic_cast<HxSurface*>(t) ? 1 : 0);

        for (int i=0; i<nTriangles; i++) {
            if (i>=iUpdate) {
                float incr = 0.02*nTriangles + 1;
                iUpdate += (int)incr;
                if (useWorkArea)
                    theWorkArea->setProgressValue((float) iUpdate/nTriangles);
            }
            Surface::Triangle* surfTri = 0;
            if (isSurface)
                surfTri = (Surface::Triangle*) &triangles[i];
            if (!isSurface || surfTri->patch >= 0)
                insertTriangle(i);
        }

        if (useWorkArea)
            theWorkArea->stopWorking();
    }

    //--------------------------------------------------------------------------

    ///
    void insertNewTriangle(int iTri) 
    {
        if (iTri >= lookupFlags.nBits())
            lookupFlags.resize(iTri + 1);
        lookupFlags.unset(iTri);

        if ( iTri >= triBoxes.size() )
            triBoxes.resize(iTri + 1);

        computeTriBox(iTri,triBoxes[iTri]);

        insertTriangle(0, 0, meshBox, iTri);
    }

    //--------------------------------------------------------------------------

    ///
    void computeTriBox(int iTri){
        computeTriBox(iTri,triBoxes[iTri]);
    }

    //--------------------------------------------------------------------------

    ///
    void insertTriangle(int iTri) {
        insertTriangle(0, 0, meshBox, iTri);
    }

    //--------------------------------------------------------------------------

    ///
    void removeTriangle(int iTri) {
        removeTriangle(0, meshBox, iTri);
    }

    //--------------------------------------------------------------------------

    ///
    void getNearbyTriangles(int iTri, McDArray<int>& result) {
        typename T::Triangle* triangles = mesh->triangles;
        result.resize(0);
    
        McBox3f triBox;
        computeTriBox(iTri, triBox);

        lookupTriangle(0, meshBox, iTri, result);

        int i,k,nNeighbours = result.size();

        for (i=0; i<nNeighbours; i++)
            lookupFlags.unset(result[i]);

        for (i=k=0; i<nNeighbours; i++) {
            int n = result[i];
            Surface::Triangle* surfTri = 0;
            if (isSurface)
                surfTri = (Surface::Triangle*) &triangles[i];
            if (n!=iTri && 
                (!isSurface || surfTri->patch >= 0) && 
                triBoxes[iTri].intersects(triBoxes[n]) && 
                intersectTriangle(triBoxes[iTri],n))
                result[k++] = result[i];
        }
        result.resize(k);
    }

    //--------------------------------------------------------------------------

    ///
    void lookupTriangles(const McBox3f &box, 
                         McDArray<int>& result) {
        typename T::Triangle* triangles = mesh->triangles;
        result.resize(0);

        lookupTriangle(0, meshBox, box, result);

        int i,k,nNeighbours = result.size();

        for (i=0; i<nNeighbours; i++)
            lookupFlags.unset(result[i]);

        for (i=k=0; i<nNeighbours; i++) {
            int n = result[i];
            Surface::Triangle* surfTri = 0;
            if (isSurface)
                surfTri = (Surface::Triangle*) &triangles[i];
            if ((!isSurface || surfTri->patch >= 0) && 
                box.intersects(triBoxes[n]) && 
                intersectTriangle(box,n))
                result[k++] = result[i];
        }
        result.resize(k);
    }

    //--------------------------------------------------------------------------

    ///
    void info() {
        int nTriangles = mesh->triangles.size();
        int nElements = allElements.size();
        int nLeafs = 0;
        int minNumTriangles = 100000;
        int maxNumTriangles = 0;
        int triangleSum = 0;

        for (int i=0; i<nElements; i++)
            if (isLeaf(i)) {
                nLeafs++;
                int n = allElements[i].leaf.nTriangles;
                if (n < minNumTriangles)
                    minNumTriangles = n;
                if (n > maxNumTriangles)
                    maxNumTriangles = n;
                triangleSum += n;
            }

        printf("Octree: %d nodes, %d leafs (%.2f MB)\n",
               nElements-nLeafs, nLeafs, memSize());
        printf("Octree triangles / mesh faces = %.2f\n",
               (float) triangleSum/nTriangles);
        printf("Average num faces per leaf = %.2f (%d..%d)\n",
               (float) triangleSum/nLeafs, minNumTriangles, maxNumTriangles);
    }

    //--------------------------------------------------------------------------

    ///
    float memSize() {
        size_t bytes = allElements.size() * sizeof(Element);

        bytes += mesh->triangles.size()*6*sizeof(float);

        for (int i=allElements.size()-1; i>=0; i--)
            if (isLeaf(i)) {
                int n = allElements[i].leaf.nTriangles / MEMINCREMENT;
                bytes += (n+1)*MEMINCREMENT*sizeof(int);
            }

        return (float) bytes/(1024*1024);
    }

    //--------------------------------------------------------------------------

    ///
    int getNumElements() const{
        return allElements.size(); 
    }

    //--------------------------------------------------------------------------

    ///
    int getMaxDepth() const {
        return maxDepth; 
    }

    //--------------------------------------------------------------------------

    ///
    void setMaxDepth(int maxDepth) {
        this->maxDepth = maxDepth; 
    }

    //--------------------------------------------------------------------------

    ///
    void setMaxTriPerLeaf(int maxTriPerLeaf) {
        this->maxTriPerLeaf = maxTriPerLeaf; 
    }

    //--------------------------------------------------------------------------

    ///
    float getEps() const { 
        return eps; 
    }

    //--------------------------------------------------------------------------

    /// Find including surfaces for a given surface.
    void findIncludingSurfaces(McDArray<short> &markTriangles,
                               const int jSurf,
                               McDArray<signed char> &includingSurfaces) {
        McVec3f*     points    = mesh->points;
        typename T::Triangle* triangles = mesh->triangles;
        McDArray<int> neighbours(100);
        McDArray<int> nOdd;
        McDArray<int> undecided;
        McDArray<float> coordList;
        McDArray<float> coordList2;

        int i,j,k,iSurf,iTri,iTriang;

        McVec3f meshPoint;

        int nTriangles = mesh->triangles.size();
        int nSurfaces = includingSurfaces.size();
        nOdd.resize(nSurfaces);

        float meshBox[6];
        mesh->getBoundingBox(meshBox);
        float eps = meshBox[1] - meshBox[0];
        if (meshBox[3] - meshBox[2] > eps)
            eps = meshBox[3] - meshBox[2];
        if (meshBox[5] - meshBox[4] > eps)
            eps = meshBox[5] - meshBox[4];
        eps *= 1.e-4;

        // - the following loop is repeated until for all surfaces
        //   the inclusion test could be decided
        // - in each loop a new selectedTriangle and a new meshPoint
        //   on this triangle is chosen
        includingSurfaces.fill(-1);
        undecided.resize(nSurfaces);
        undecided.fill(1);
        undecided[jSurf] = 0;
        int nUndecided = nSurfaces - 1;

        int selectedTriangle=0;
        int iSelect = 0;
        while (nUndecided > 0 && selectedTriangle>-1) {
            selectedTriangle=-1;
            k = 0;
            for (iTriang=0; iTriang<nTriangles && selectedTriangle==-1; 
                 iTriang++)
                if (markTriangles[iTriang]==jSurf+1) {
                    if (k==iSelect)
                        selectedTriangle = iTriang;
                    k++;
                }

            if (selectedTriangle>-1) {

                int v1 = triangles[selectedTriangle].points[0];
                int v2 = triangles[selectedTriangle].points[1];
                int v3 = triangles[selectedTriangle].points[2];

                // point inside selected triangle:
                // - weights 2/11, 4/11 and 5/11 for vertex coordinates
                // - might be better than center of mass 
                //   for regular geometries (?)
                meshPoint = ((points[v1] * 2) + (points[v2] * 4) + (points[v3] * 5)) / 11.;

                //initialize
                nOdd.fill(0);
                for (iSurf=0; iSurf<nSurfaces; iSurf++)
                    if (undecided[iSurf])
                        includingSurfaces[iSurf] = 0;

                // for inclusion test check rays through meshPoint
                // parallel to x-, y, and z-Axis
                int direction;
                for (direction=0; direction<3; direction++) {
                    coordList.resize(0);
                    int ixy[2];
                    ixy[0] = (direction+1)%3;
                    ixy[1] = (direction+2)%3;

                    // get all triangles from octree that might be hit 
                    // by the ray
                    float box[6];
                    box[2*direction]   = meshBox[2*direction]   - eps;
                    box[2*direction+1] = meshBox[2*direction+1] + eps;
                    for (i=0; i<2; i++) {
                        j = ixy[i];
                        box[2*j]   = meshPoint[j] - eps;
                        box[2*j+1] = meshPoint[j] + eps;
                    }
                    lookupTriangles(box,neighbours);

                    // select triangles that are really hit by the ray
                    for (i=k=0; i<neighbours.size(); i++) {
                        iTri = neighbours[i];

                        iSurf = markTriangles[iTri]-1;
                        if (iSurf >= 0) {
                            if (undecided[iSurf]) {
                                int* idx = triangles[iTri].points;

                                // These are the vertices of triangle iTri
                                McVec3f &p0 = points[idx[0]];
                                McVec3f &p1 = points[idx[1]];
                                McVec3f &p2 = points[idx[2]];

                                McVec3f d0 = p1 - p0;
                                McVec3f d1 = p2 - p0;

                                float det = d0[ixy[0]]*d1[ixy[1]] 
                                    - d0[ixy[1]]*d1[ixy[0]];

                                if (det == 0.) {
                                //nDet0++;
                                } else {
                                    float dx[2];
                                    dx[0] = meshPoint[ixy[0]] - p0[ixy[0]];
                                    dx[1] = meshPoint[ixy[1]] - p0[ixy[1]];

                                    float xi[3];
                                    xi[1] = (dx[0]*d1[ixy[1]] - 
                                             dx[1]*d1[ixy[0]]) / det;
                                    xi[2] = (d0[ixy[0]]*dx[1] - 
                                             d0[ixy[1]]*dx[0]) / det;
                                    xi[0] = 1. - xi[1] - xi[2];

                                    int inside = 1;
                                    for (j=0; j<3; j++)
                                        if (xi[j] < 0.) inside = 0;

                                    if (inside == 1) {
                                        neighbours[k++] = neighbours[i];

                                        float coord = xi[0]*p0[direction] 
                                            + xi[1]*p1[direction] 
                                            + xi[2]*p2[direction];
                                        coordList.append(coord);
                                    }
                                }
                            }
                        }
                    }
                    neighbours.resize(k);

                    int nSelectedTriangles = k;
                    for (iSurf=0; iSurf<nSurfaces; iSurf++) {
                        if (undecided[iSurf]) {
                            coordList2.resize(0);
                            for (i=0; i<nSelectedTriangles; i++) {
                                iTri = neighbours[i];
                                if (markTriangles[iTri]-1 == iSurf)
                                    coordList2.append(coordList[i]);
                            }
                            k = coordList2.size();

                            // - number of triangles should be even
                            // - odd number might occur e.g. due to 
                            //   roundoff errors if the ray 'exactly' 
                            //   hits the edge between 2 triangles
                            // - if number is odd, ignore this ray 
                            //   direction in inclusion test 
                            if (k%2==1) 
                                nOdd[iSurf]++;
                            else {
                                //sort coordList2
                                for (i=0; i<k-1; i++)
                                    for (j=i+1; j<k; j++)
                                        if (coordList2[i] > coordList2[j]) {
                                            float fbuf = coordList2[i];
                                            coordList2[i] = coordList2[j];
                                            coordList2[j] = fbuf;
                                        }

                                float coordj = meshPoint[direction];
                                int inside = 0;
                                for (i=0; i<k/2; i++)
                                    if (coordList2[2*i] < coordj           &&
                                        coordj          < coordList2[2*i+1]  )
                                        inside = 1;

                                if (inside) includingSurfaces[iSurf]++;
                            }
                        }
                    }

                }      // direction

                // number of rays to be taken into account: 3 - nOdd[iSurf]
                // number of rays for which meshPoint was inside surface iSurf:
                // includingSurfaces[iSurf]
                //
                // if nInside == nOutside 
                //    leave undecided[iSurf] at value 1
                //    repeat inclusion test for a different meshPoint

                for (iSurf=0; iSurf<nSurfaces; iSurf++) {
                    if (undecided[iSurf]) {
                        int nInside = includingSurfaces[iSurf];
                        int nOutside = 3 - nOdd[iSurf] - nInside;
                        if (nInside > nOutside) {
                            includingSurfaces[iSurf] = 1;
                            undecided[iSurf] = 0;
                        } else if (nInside < nOutside) {
                            includingSurfaces[iSurf] = 0;
                            undecided[iSurf] = 0;
                        } else
                            includingSurfaces[iSurf] = -1;
                    }
                }
            }              // selectedTriangle > -1

            nUndecided = 0;
            for (iSurf=0; iSurf<nSurfaces; iSurf++)
                if (undecided[iSurf])
                    nUndecided++;

            iSelect++;
        }                  // nUndecided > 0 && selectedTriangle > -1
    }

    //--------------------------------------------------------------------------

    /// Determine which surfaces enclose each other.
    void findInclusions(McDArray<short> &markTriangles,
                        const int nSurfaces,
                        McDArray<signed char> &inclusionInfo) {
        // inclusionInfo[i][j] = 1 : surface i includes surface j

        int i,j,k;

        McDArray<signed char> includingSurfaces;
        includingSurfaces.resize(nSurfaces);

        inclusionInfo.fill(0);

        int nUndecided = 0;
        int ij, ji, ik, kj;
        for (j=0; j<nSurfaces; j++) {
            includingSurfaces.fill(0);
            findIncludingSurfaces(markTriangles, j, 
                                  includingSurfaces);
            for (i=0; i<nSurfaces; i++) {
                if (i !=j ) {
                    ij = i * nSurfaces + j;
                    inclusionInfo[ij] = includingSurfaces[i];
                    if (inclusionInfo[ij] == -1)
                        nUndecided++;
                }
            }
        }
        if (nUndecided > 0) {
            nUndecided = 0;
            for (i=0; i<nSurfaces; i++) {
                for (j=0; j<nSurfaces; j++) {
                    ij = i * nSurfaces + j;
                    if (inclusionInfo[ij] == -1) {
                        ji = j * nSurfaces + i;
                        if (inclusionInfo[ji] == 1) 
                            inclusionInfo[ij] = 0;
                        else {
                            for (k=0; k<nSurfaces; k++) {
                                ik = i * nSurfaces + k;
                                kj = k * nSurfaces + j;
                                if (inclusionInfo[ik] && inclusionInfo[kj])
                                    inclusionInfo[ij] = 1;
                            }
                            if (inclusionInfo[ij] == -1) {
                                for (k=0; k<nSurfaces; k++) {
                                    kj = k * nSurfaces + j;
                                    if (inclusionInfo[kj])
                                        inclusionInfo[ij] = 0;
                                }
                            }
                        }
                        if (inclusionInfo[ij] == -1)
                            nUndecided++;
                    }
                }
            }

            if (nUndecided > 0) {
                theMsg->printf("findInclusions: nUndecided = %d",nUndecided);

                for (i=0; i<nSurfaces; i++) {
                    for (j=0; j<nSurfaces; j++) {
                        ij = i * nSurfaces + j;
                        if (inclusionInfo[ij] == -1) {
                            inclusionInfo[ij] = 1;                // ???????
                        }
                    }
                }
            }
        }

        // check inclusionInfo
        for (i=0; i<nSurfaces; i++) {
            for (j=0; j<nSurfaces; j++) {
                ij = i * nSurfaces + j;
                ji = j * nSurfaces + i;
                if (inclusionInfo[ij] == 1 &&
                    inclusionInfo[ji] == 1) {
                    theMsg->printf("findInclusions: WARNING");
                    theMsg->printf("i includes j and j includes i");
                    theMsg->printf("i,j: %d %d",i,j);
                }
            }
        }

        // remove redundant entries from inclusionInfo
        // if i includes k and k includes j, than i includes j
        // leave only 'direct' inclusions in inclusionInfo
        for (i=0; i<nSurfaces; i++) {
            for (j=0; j<nSurfaces; j++) {
                ij = i * nSurfaces + j;
                for (k=0; k<nSurfaces; k++) {
                    ik = i * nSurfaces + k;
                    kj = k * nSurfaces + j;
                    if (inclusionInfo[ik] && inclusionInfo[kj])
                        inclusionInfo[ij] = 0;
                }
            }
        }
    }

    //--------------------------------------------------------------------------
    
    ///
    int findFirstIntersectedTriangle(const McVec3f& origin, 
                                     const McVec3f& rayDir, 
                                     McVec3f& intersectionPoint,
                                     const bool halfSpaceCheck = false)
    {
        McVec3f bary;
        return findFirstIntersectedTriangle(origin, rayDir, intersectionPoint, bary, halfSpaceCheck);
    }

    //--------------------------------------------------------------------------
    
    ///
    int findFirstIntersectedTriangle(const McVec3f& origin, 
                                     const McVec3f& rayDir, 
                                     McVec3f& intersectionPoint,
                                     McVec3f& bary,
                                     const bool halfSpaceCheck = false)
    {
        int idx = -1;
        float dist2 = 0.;
        findFirstIntersectedTriangle(origin, rayDir, 
                                     0, meshBox, idx, dist2, 
                                     intersectionPoint, bary, halfSpaceCheck);
        return idx;
    }


    //--------------------------------------------------------------------------
    
    ///
    void findFirstIntersectedTriangle(const McVec3f& origin, 
                                      const McVec3f& rayDir,
                                      int elem, McBox3f& elemBox, 
                                      int& idx, float& dist2, 
                                      McVec3f& intersectionPoint,
                                      McVec3f& bary, const bool halfSpaceCheck = false)
    {
        if (isLeaf(elem)) {
            typename Element::Leaf& leaf = allElements[elem].leaf;
            double newDist2;
            McVec3f ip, ib, lineEnd = origin+rayDir;
            for (int i=0; i<leaf.nTriangles; i++) 
            {
                if (lineIntersectsTriangle(origin, lineEnd,
                                           mesh->triangles[leaf.triangles[i]], 
                                           ip, ib) 
                    && (newDist2=(ip-origin).length2())>=0 
                    && (idx<0 || newDist2<dist2) ) 
                {
                    if ( halfSpaceCheck ) {
                        McVec3f hsVector = ip - origin;
                        hsVector.normalize();
                        if ( rayDir.dot(hsVector) < 0.0 )
                            continue;
                    }
                    idx = leaf.triangles[i];
                    dist2 = newDist2;
                    intersectionPoint = ip;
                    bary = ib;
                }
            }
            return;
        }
    
        int firstChild = -allElements[elem].node.negativeChildIndex;
        McVec3f c, center = elemBox.getCenter();
        McBox3f childElemBox;
    
        // look in octant ---
        childElemBox.setValue(elemBox[0], center.x, elemBox[2],
            center.y, elemBox[4], center.z);
        if (childElemBox.intersectsRay(origin,rayDir,c))
            findFirstIntersectedTriangle(origin, rayDir, firstChild+0, 
                                         childElemBox, idx, dist2, intersectionPoint, bary, halfSpaceCheck);
    
        // look in octant +--
        childElemBox.setValue(center.x, elemBox[1], elemBox[2],
            center.y, elemBox[4], center.z);
        if (childElemBox.intersectsRay(origin,rayDir,c))
            findFirstIntersectedTriangle(origin, rayDir, firstChild+1, 
                                         childElemBox, idx, dist2, intersectionPoint, bary, halfSpaceCheck);
    
        // look in octant -+-
        childElemBox.setValue(elemBox[0], center.x, center.y,
            elemBox[3], elemBox[4], center.z);
        if (childElemBox.intersectsRay(origin,rayDir,c))
            findFirstIntersectedTriangle(origin, rayDir, firstChild+2, 
                                         childElemBox, idx, dist2, intersectionPoint, bary, halfSpaceCheck);
    
        // look in octant ++-
        childElemBox.setValue(center.x, elemBox[1], center.y,
            elemBox[3], elemBox[4], center.z);
        if (childElemBox.intersectsRay(origin,rayDir,c))
            findFirstIntersectedTriangle(origin, rayDir, firstChild+3, 
                                         childElemBox, idx, dist2, intersectionPoint, bary, halfSpaceCheck);
    
        // look in octant --+
        childElemBox.setValue(elemBox[0], center.x, elemBox[2],
            center.y, center.z, elemBox[5]);
        if (childElemBox.intersectsRay(origin,rayDir,c))
            findFirstIntersectedTriangle(origin, rayDir, firstChild+4, 
                                         childElemBox, idx, dist2, intersectionPoint, bary, halfSpaceCheck);
    
        // look in octant +-+
        childElemBox.setValue(center.x, elemBox[1], elemBox[2],
            center.y, center.z, elemBox[5]);
        if (childElemBox.intersectsRay(origin,rayDir,c))
            findFirstIntersectedTriangle(origin, rayDir, firstChild+5, 
                                         childElemBox, idx, dist2, intersectionPoint, bary, halfSpaceCheck);
    
        // look in octant -++
        childElemBox.setValue(elemBox[0], center.x, center.y,
            elemBox[3], center.z, elemBox[5]);
        if (childElemBox.intersectsRay(origin,rayDir,c))
            findFirstIntersectedTriangle(origin, rayDir, firstChild+6, 
                                         childElemBox, idx, dist2, intersectionPoint, bary, halfSpaceCheck);
    
        // look in octant +++
        childElemBox.setValue(center.x, elemBox[1], center.y,
            elemBox[3], center.z, elemBox[5]);
        if (childElemBox.intersectsRay(origin,rayDir,c))
            findFirstIntersectedTriangle(origin, rayDir, firstChild+7, 
                                         childElemBox, idx, dist2, intersectionPoint, bary, halfSpaceCheck);
    }

    //--------------------------------------------------------------------------

    /// Compute all faces intersected by given line
    bool lineIntersectsFaces(const McVec3f& lineStart, 
                             const McVec3f& lineEnd,
                             McDArray<int>& intersectionTriangles, 
                             McDArray<McVec3f>& intersectionPoints,
                             bool distanceCheck=false) {

        McBox3f vBox(lineStart, lineEnd);
        
        vBox.extendByEps(McVec3f(0.01));
        
        McDArray<int> triangleIdx(0);
        
        intersectionTriangles.resize(0);
        intersectionPoints.resize(0);
        
        lookupTriangles(vBox, triangleIdx);
        
        int i;
        for (i=0; i<triangleIdx.size(); i++) {
            
            McVec3f intersectionPoint, bary;
            if ( lineIntersectsTriangle(lineStart, 
                                        lineEnd, 
                                        mesh->triangles[triangleIdx[i]], 
                                        intersectionPoint, 
                                        bary,
                                        distanceCheck) ) 
            {    
                intersectionTriangles.append(triangleIdx[i]);
                intersectionPoints.append(intersectionPoint);
            }
        }
        
        if (intersectionTriangles.size()) return (true);
        else return (false);
    }

    //--------------------------------------------------------------------------
    
    /// test whether or not a line intersects a given triangle 
    /// (result: point of intersection)
    bool lineIntersectsTriangle(const McVec3f& lineStart, 
                                const McVec3f& lineEnd,
                                const typename T::Triangle& triangle, 
                                McVec3f& intersectionPoint,
                                McVec3f& bary,
                                bool distanceCheck=false)
    {
        McVec3f* points = mesh->points;
        
        McVec3f  & p1 = points[triangle.points[0]];
        McVec3f  & p2 = points[triangle.points[1]];
        McVec3f  & p3 = points[triangle.points[2]];
        
        // building local coordinate system (u,v) for the given triangle
        // two edge vectors sharing p1
        McVec3f  edge1 = p2 - p1;
        McVec3f  edge2 = p3 - p1;
        McVec3f edge3 = p3-p2;
        
        // algorithm from acm cg-lib (80% faster than the algorithm
        // from hxsurface)
        
        // no test if intersection point between lineStart and lineEnd (MS)
        //
        // 1 cross, 2 dot; 1st if
        // 1 cross, 1 dot; 2nd if
        
        const double tolerance = 1e-10;//05;
        
        McVec3f  lineDirection = lineEnd - lineStart;
        double dist = lineDirection.normalize();
        McVec3f triangleNormal = edge1.cross(edge2);
        triangleNormal.normalize();
        double area = (edge1.cross(edge2)).length();
        double tolerance2 = tolerance * area;
        
        // vector orthogonal to edge2 (|lineDirection|*|edge2|*sin(ß))
        McVec3f  pVec = lineDirection.cross(edge2);
        
        // calculating determinant - also used to calculate u parameter
        double  determinant = edge1.dot(pVec);
        
        // if determinant is near zero, ray lies in plane of triangle 
        if ((determinant > -tolerance2) && (determinant < tolerance2)){
            // set intersection point to first point on triangle (edge) where line comes in
            // project line start and line end on triangle plane
            // or check direction of projection vector (on triangleNormal)
            float projOnNormalLineStart = (lineStart-p1).dot(triangleNormal);
            float projOnNormalLineEnd = (lineStart-p1).dot(triangleNormal);
            if( projOnNormalLineStart*projOnNormalLineEnd>0 ){
                return(false);
            }
            else {
                // projection points on triangle plane:
                McVec3f projPointLineStart = lineStart-projOnNormalLineStart*triangleNormal;
                McVec3f projPointLineEnd = lineEnd-projOnNormalLineStart*triangleNormal;
                //test if projPointLineStart or projPointLineEnd or both lie in triangle!!
                //start:
                float startProjE1 = (projPointLineStart-p1).dot(edge1)/edge1.length2();
                float startProjE2 = (projPointLineStart-p1).dot(edge2)/edge2.length2();
                float endProjE1 = (projPointLineEnd-p1).dot(edge1)/edge1.length2();
                float endProjE2 = (projPointLineEnd-p1).dot(edge2)/edge2.length2();
                bool startProjInTriangle = false;
                bool endProjInTriangle = false;
                if (0<=startProjE1 && startProjE1<=1 && 0<=startProjE2 && startProjE2<=1 && startProjE1+startProjE2<=1)
                {
                    startProjInTriangle = true;
                }
                if (0<=endProjE1 && endProjE1<=1 && 0<=endProjE2 && endProjE2<=1 && endProjE1+endProjE2<=1)
                {
                    endProjInTriangle = true;
                }

                //test if projected line runs through triangle:
                //test if projected line crosses triangle edges
                //proj on normal to edge1 in triangle plane:
                McVec3f edge1NormalInPlane = edge1.cross(triangleNormal);
                edge1NormalInPlane.normalize();
                McVec3f edge2NormalInPlane = edge2.cross(triangleNormal);
                edge2NormalInPlane.normalize();
                McVec3f edge3NormalInPlane = edge3.cross(triangleNormal);
                edge3NormalInPlane.normalize();

                float projOnE1NormalProjPointLineStart = (projPointLineStart-p1).dot(edge1NormalInPlane);
                float projOnE1NormalProjPointLineEnd = (projPointLineEnd-p1).dot(edge1NormalInPlane);
                float productE1=projOnE1NormalProjPointLineStart*projOnE1NormalProjPointLineEnd;

                float projOnE2NormalProjPointLineStart = (projPointLineStart-p1).dot(edge2NormalInPlane);
                float projOnE2NormalProjPointLineEnd = (projPointLineEnd-p1).dot(edge2NormalInPlane);
                float productE2=projOnE2NormalProjPointLineStart*projOnE2NormalProjPointLineEnd;

                float projOnE3NormalProjPointLineStart = (projPointLineStart-p1).dot(edge3NormalInPlane);
                float projOnE3NormalProjPointLineEnd = (projPointLineEnd-p1).dot(edge3NormalInPlane);
                float productE3=projOnE3NormalProjPointLineStart*projOnE3NormalProjPointLineEnd;

                //which product is <0? if two, then which sum is bigger then tolerance2?
                if ( productE1<0 || productE2<0 || productE3<0 || startProjInTriangle || endProjInTriangle)
                {
                    //projected line crosses triangle.
                    if (fabs(projOnNormalLineStart-projOnNormalLineEnd)>tolerance2){
                        //no prob with intersection point calc
                        McVec3f trianglePlaneIntersectionPoint = projPointLineStart + (projOnNormalLineStart/(projOnNormalLineStart-projOnNormalLineEnd))*(projPointLineEnd-projPointLineStart);
                        //in triangle?
                        float ipProjE1 = (trianglePlaneIntersectionPoint-p1).dot(edge1)/edge1.length2();
                        float ipProjE2 = (trianglePlaneIntersectionPoint-p1).dot(edge2)/edge2.length2();
                        if (0<=ipProjE1 && ipProjE1<=1 && 0<=ipProjE2 && ipProjE2<=1 && ipProjE1+ipProjE2<=1){
                            intersectionPoint = trianglePlaneIntersectionPoint;
                            bary = McVec3f(1-ipProjE1-ipProjE2, ipProjE1, ipProjE2);
                            return(true);
                        }
                        else {
                            return(false);
                        }
                    }
                    else {
                        //we have strong parallelity, but surely an intersection point with triangle*plane*. with triangle as well?
                        //check the following:
                        //reproject crossing point with one of the edges to original line, and then to triangle normal. compare with other crossing point!
                        McSmallArray<McVec3f,2> backProj(2);
                        McSmallArray<McVec3f,2> cross(2);

                        float sumE1=fabs(projOnE1NormalProjPointLineStart-projOnE1NormalProjPointLineEnd);
                        float sumE2=fabs(projOnE2NormalProjPointLineStart-projOnE2NormalProjPointLineEnd);
                        float sumE3=fabs(projOnE3NormalProjPointLineStart-projOnE3NormalProjPointLineEnd);

                        //get two crossing points:
                        int numGoodCrossingPoints=0;
                        int numCrossingPoints=0;
                        if (productE1<0){
                            numCrossingPoints++;
                            if(sumE1>tolerance2){
                                cross[numGoodCrossingPoints] = projPointLineStart + (projOnE1NormalProjPointLineStart/sumE1)*(projPointLineEnd-projPointLineStart);
                                backProj[numGoodCrossingPoints]= lineStart + (cross[numGoodCrossingPoints]-projPointLineStart).length()/(projPointLineEnd-projPointLineStart).length() *(lineEnd-lineStart); ///crossing point with E1
                                numGoodCrossingPoints++;
                            }
                        }
                        if (productE2<0){
                            numCrossingPoints++;
                            if (sumE2>tolerance2){
                                cross[numGoodCrossingPoints] = projPointLineStart + (projOnE2NormalProjPointLineStart/sumE2)*(projPointLineEnd-projPointLineStart);
                                backProj[numGoodCrossingPoints]= lineStart + (cross[numGoodCrossingPoints]-projPointLineStart).length()/(projPointLineEnd-projPointLineStart).length() *(lineEnd-lineStart); ///crossing point with E1
                                numGoodCrossingPoints++;
                            }
                        }
                        if (productE3<0){
                            numCrossingPoints++;
                            if (sumE3>tolerance2 && numGoodCrossingPoints<2){
                                cross[numGoodCrossingPoints] = projPointLineStart + (projOnE3NormalProjPointLineStart/sumE3)*(projPointLineEnd-projPointLineStart);
                                backProj[numGoodCrossingPoints]= lineStart + (cross[numGoodCrossingPoints]-projPointLineStart).length()/(projPointLineEnd-projPointLineStart).length() *(lineEnd-lineStart); ///crossing point with E1
                                numGoodCrossingPoints++;
                            }
                        }
                        if (startProjInTriangle && numGoodCrossingPoints<2){
                            numCrossingPoints++;
                            cross[numGoodCrossingPoints] = projPointLineStart;
                            backProj[numGoodCrossingPoints]= lineStart;
                            numGoodCrossingPoints++;
                        }
                        if (endProjInTriangle && numGoodCrossingPoints<2){
                            numCrossingPoints++;
                            cross[numGoodCrossingPoints] = projPointLineEnd;
                            backProj[numGoodCrossingPoints]= lineEnd;
                            numGoodCrossingPoints++;
                        }


                        if (numCrossingPoints<2){
                            //can't happen...
                            return true;
                        }
                        else {
                            if (numGoodCrossingPoints<2){
                                //can't set intersection point
                                return true;
                            }
                        }

                        //now we have two back projected crossing points.
                        //projection on triangle Normal:
                        float projBackProj1 = (backProj[0]-p1).dot(triangleNormal);
                        float projBackProj2 = (backProj[1]-p1).dot(triangleNormal);
                        if (projBackProj1*projBackProj2>0)
                        {
                            //no intersection
                            return(false);
                        }
                        else {
                            //return middle of the two cross-points
                            intersectionPoint = (cross[0]+cross[1])/2;
                            float ipProjE1 = (intersectionPoint-p1).dot(edge1)/edge1.length2();
                            float ipProjE2 = (intersectionPoint-p1).dot(edge2)/edge2.length2();
                            bary = McVec3f(1-ipProjE1-ipProjE2, ipProjE1, ipProjE2);
                            return(true);
                        }
                    }
                }
                else {
                    return(false);
                }
            }
            
            //return(true);
        }
        
        double inverseDeterminant = 1.0 / determinant;
        
        // distance from p1 to ray origin
        McVec3f  tVec = lineStart - p1;
        
        double eps = 1.0e-5;
        
        // u and v are the barycentric coordinates of the intersection
        // point 
        
        // calculate u parameter and test bounds
        double  u = tVec.dot(pVec) * inverseDeterminant;
        if ((u < 0.0-eps) || (u > 1.0+eps))
            return(false);
        
        // prepare to test v parameter
        McVec3f  qVec = tVec.cross(edge1);
        
        // calculate v parameter and test bounds
        double  v = lineDirection.dot(qVec) * inverseDeterminant;
        if ((v < 0.0-eps) || ((u + v) > 1.0+eps))
            return(false);
        
        // calculate t, ray does intersect the triangle
        // double  t = edge2.dot(qVec) * inverseDeterminant;
        double  t = 1 - u - v;
        
        // here we can calculate the intersection point from the parameters
        intersectionPoint = (p1 * t) + (p2 * u) + (p3 * v);

        if ( distanceCheck ) {
            double s = (intersectionPoint-lineStart).dot(lineDirection);
            if ( s<0.0 || s>dist ) return(false);
        }

        bary = McVec3f(t, u, v);
        
        // OK, we found an intersection point within the given triangle
        return(true);
    }

    //--------------------------------------------------------------------------

    const T* getMesh(void) const {
        return mesh;
    }

    //--------------------------------------------------------------------------
    
    ///
    union Element {

        struct Node {
            int negativeChildIndex;
        } node;

        struct Leaf {
            int nTriangles;
            int* triangles;
        } leaf;
    };

    ///
    McDArray<Element> allElements;

    // An element is a leaf if negativeChildIndex/nTriangles >= 0
    int isLeaf(int elem) {
        return (allElements[elem].node.negativeChildIndex >= 0);
    }

protected:

    //--------------------------------------------------------------------------

    void insertTriangle(int elem, int depth, 
                        const McBox3f &elemBox, int iTri) {

        if (isLeaf(elem)) {
            typename Element::Leaf& leaf = allElements[elem].leaf;

            if (depth<maxDepth && leaf.nTriangles>=maxTriPerLeaf) {
                subdivide(elem, elemBox);
                goto DESCEND;
            }

            if (leaf.nTriangles % MEMINCREMENT == 0) {
                int newSize = leaf.nTriangles + MEMINCREMENT;
                int* triangles = (int*) realloc(leaf.triangles, newSize*sizeof(int));
                if (triangles) {
                    leaf.triangles=triangles;
                }
            }
            
            leaf.triangles[leaf.nTriangles++] = iTri;
            return;
        }

        DESCEND:

        int firstChild = -allElements[elem].node.negativeChildIndex;

        McVec3f center = elemBox.getCenter();
        McBox3f &triBox = triBoxes[iTri];

        depth++;
        
        McBox3f childElemBox;

        // look in octant ---
        if (lowerLeftFront(triBox[0], triBox[2], triBox[4], center)){
            childElemBox.setValue(elemBox[0], center.x, elemBox[2], center.y,
                                  elemBox[4], center.z);
            if (intersectTriangle(childElemBox,iTri))
                insertTriangle(firstChild+0, depth, childElemBox, iTri);
        }
        // look in octant +--
        if (lowerRightFront(triBox[1], triBox[2], triBox[4], center)){
            childElemBox.setValue(center.x, elemBox[1], elemBox[2], center.y,
                                  elemBox[4], center.z);
            if (intersectTriangle(childElemBox,iTri))
                insertTriangle(firstChild+1, depth, childElemBox, iTri);
        }
        // look in octant -+-
        if (lowerLeftBack(triBox[0], triBox[3], triBox[4], center)){
            childElemBox.setValue(elemBox[0], center.x, center.y, elemBox[3],
                                  elemBox[4], center.z);
            if (intersectTriangle(childElemBox,iTri))
                insertTriangle(firstChild+2, depth, childElemBox, iTri);
        }
        // look in octant ++-
        if (lowerRightBack(triBox[1], triBox[3], triBox[4], center)){
            childElemBox.setValue(center.x, elemBox[1], center.y, elemBox[3],
                                  elemBox[4], center.z);
            if (intersectTriangle(childElemBox,iTri))
                insertTriangle(firstChild+3, depth, childElemBox, iTri);
        }
        // look in octant --+
        if (upperLeftFront(triBox[0], triBox[2], triBox[5], center)){
            childElemBox.setValue(elemBox[0], center.x, elemBox[2], center.y,
                                  center.z, elemBox[5]);
            if (intersectTriangle(childElemBox,iTri))
                insertTriangle(firstChild+4, depth, childElemBox, iTri);
        }
        // look in octant +-+
        if (upperRightFront(triBox[1], triBox[2], triBox[5], center)){
            childElemBox.setValue(center.x, elemBox[1], elemBox[2], center.y,
                                  center.z, elemBox[5]);
            if (intersectTriangle(childElemBox,iTri))   
                insertTriangle(firstChild+5, depth, childElemBox, iTri);
        }
        // look in octant -++
        if (upperLeftBack(triBox[0], triBox[3], triBox[5], center)){
            childElemBox.setValue(elemBox[0], center.x, center.y, elemBox[3],
                                  center.z, elemBox[5]);
            if (intersectTriangle(childElemBox,iTri))
                insertTriangle(firstChild+6, depth, childElemBox, iTri);
        }
        // look in octant +++
        if (upperRightBack(triBox[1], triBox[3], triBox[5], center)){
            childElemBox.setValue(center.x, elemBox[1], center.y, elemBox[3],
                                  center.z, elemBox[5]);
            if (intersectTriangle(childElemBox,iTri))
                insertTriangle(firstChild+7, depth, childElemBox, iTri);
        }
    }

    //--------------------------------------------------------------------------

    void insertTriangle(typename Element::Leaf& leaf);

    //--------------------------------------------------------------------------

    void subdivide(int elem, const McBox3f &elemBox) {
        int childIndex = allElements.size();

        allElements.appendSpace(8);
        memset(&allElements[childIndex], 0, 8*sizeof(Element));

        typename Element::Node& node = allElements[elem].node;
        typename Element::Leaf& leaf = allElements[elem].leaf;

        int nTriangles = leaf.nTriangles;

        // leaf.nTriangles will be invalid after this !
        node.negativeChildIndex = -childIndex;

        for (int i=0; i<nTriangles; i++) {
            insertTriangle(elem,99,elemBox,leaf.triangles[i]);
        }

        if (leaf.triangles) {
            free(leaf.triangles);
            leaf.triangles = 0;
        }
    }

    //--------------------------------------------------------------------------

    void computeTriBox(int iTri, McBox3f &triBox) {
        McVec3f* points = mesh->points;
        typename T::Triangle& tri = mesh->triangles[iTri];

        McVec3f &a = points[tri.points[0]];
        McVec3f &b = points[tri.points[1]];
        McVec3f &c = points[tri.points[2]];

        triBox = McBox3f(a, b);
        triBox.extendBy(c);

        triBox.extendByEps(eps);
    }

    //--------------------------------------------------------------------------

    void computeTriBoxes() {
        int nTriangles = mesh->triangles.size();
        triBoxes.resize(nTriangles);
        for (int i=0; i<nTriangles; i++)
            computeTriBox(i,triBoxes[i]);
    }

    //--------------------------------------------------------------------------

    int intersectTriangle(const McBox3f &elemBox, int iTri)const {
        if (!normals)
            return 1;

        int idx = mesh->triangles[iTri].points[0];
        const McVec3f &n = normals[iTri]; 
        McVec3f &p = mesh->points[idx];

        float dz = n.dot(p);
        
        float n00 = n[0]*elemBox[0], n01 = n[0]*elemBox[1];
        float n12 = n[1]*elemBox[2], n24 = n[2]*elemBox[4];
        if (n00 + n12 + n24 > dz || n01 + n12 + n24 > dz) return 1;

        float n13 = n[1]*elemBox[3], n25 = n[2]*elemBox[5];
        
        if (n00 + n13 + n24 > dz || n01 + n13 + n24 > dz ||
            n00 + n12 + n25 > dz || n01 + n12 + n25 > dz ||
            n00 + n13 + n25 > dz || n01 + n13 + n25 > dz) return 1;

        return 0;
    }

    //--------------------------------------------------------------------------

    void computeEps() {
        typename T::Triangle* triangles = mesh->triangles;
        McVec3f* points = mesh->points;

        float d2Max = 0;
        for (int i=mesh->triangles.size()-1; i>=0; i--) {
            for (int k=0; k<3; k++) {
                McVec3f &a = points[triangles[i].points[k]];
                McVec3f &b = points[triangles[i].points[(k+1)%3]];
                
                float d2 = (b-a).length2();
                
                if (d2 > d2Max)
                    d2Max = d2;
            }
        }

        eps = 0.0002 * sqrt(d2Max);
    }

    //--------------------------------------------------------------------------

    void lookupTriangle(int elem, McBox3f &elemBox,
                        int iTri, McDArray<int>& result) {
        if (isLeaf(elem)) {
            typename Element::Leaf& leaf = allElements[elem].leaf;
            
            for (int i=0; i<leaf.nTriangles; i++) {
                int iTri2 = leaf.triangles[i];
                if (lookupFlags[iTri2] == 0) {
                    result.append(iTri2);
                    lookupFlags.set(iTri2);
                }
            }
            
            return;
        }

        int firstChild = -allElements[elem].node.negativeChildIndex;
        
        McVec3f center = elemBox.getCenter();
        McBox3f &triBox = triBoxes[iTri];
        
        McBox3f childElemBox;

        // look in octant ---
        if (lowerLeftFront(triBox[0], triBox[2], triBox[4], center)){
            childElemBox.setValue(elemBox[0], center.x, elemBox[2], center.y,
                                  elemBox[4], center.z);
            if (intersectTriangle(childElemBox,iTri))
                lookupTriangle(firstChild+0, childElemBox, iTri, result);
        }
        // look in octant +--
        if (lowerRightFront(triBox[1], triBox[2], triBox[4], center)){
            childElemBox.setValue(center.x, elemBox[1], elemBox[2], center.y,
                                  elemBox[4], center.z);
            if (intersectTriangle(childElemBox,iTri))
                lookupTriangle(firstChild+1, childElemBox, iTri, result);
        }
        // look in octant -+-
        if (lowerLeftBack(triBox[0], triBox[3], triBox[4], center)){
            childElemBox.setValue(elemBox[0], center.x, center.y, elemBox[3],
                                  elemBox[4], center.z);
            if (intersectTriangle(childElemBox,iTri))
                lookupTriangle(firstChild+2, childElemBox, iTri, result);
        }
        // look in octant ++-
        if (lowerRightBack(triBox[1], triBox[3], triBox[4], center)){
            childElemBox.setValue(center.x, elemBox[1], center.y, elemBox[3],
                                  elemBox[4], center.z);
            if (intersectTriangle(childElemBox,iTri))
                lookupTriangle(firstChild+3, childElemBox, iTri, result);
        }
        // look in octant --+
        if (upperLeftFront(triBox[0], triBox[2], triBox[5], center)){
            childElemBox.setValue(elemBox[0], center.x, elemBox[2], center.y,
                                  center.z, elemBox[5]);
            if (intersectTriangle(childElemBox,iTri))
                lookupTriangle(firstChild+4, childElemBox, iTri, result);
        }
        // look in octant +-+
        if (upperRightFront(triBox[1], triBox[2], triBox[5], center)){
            childElemBox.setValue(center.x, elemBox[1], elemBox[2], center.y,
                                  center.z, elemBox[5]);
            if (intersectTriangle(childElemBox,iTri))
                lookupTriangle(firstChild+5, childElemBox, iTri, result);
        }
        // look in octant -++
        if (upperLeftBack(triBox[0], triBox[3], triBox[5], center)){
            childElemBox.setValue(elemBox[0], center.x, center.y, elemBox[3],
                                  center.z, elemBox[5]);
            if (intersectTriangle(childElemBox,iTri))
                lookupTriangle(firstChild+6, childElemBox, iTri, result);
        }
        // look in octant +++
        if (upperRightBack(triBox[1], triBox[3], triBox[5], center)){
            childElemBox.setValue(center.x, elemBox[1], center.y, elemBox[3],
                                  center.z, elemBox[5]);
            if (intersectTriangle(childElemBox,iTri))   
                lookupTriangle(firstChild+7, childElemBox, iTri, result);
        }
    }

    //--------------------------------------------------------------------------

    void lookupTriangle(int elem, const McBox3f &elemBox,
                        const McBox3f &box, McDArray<int>& result) {
        if (isLeaf(elem)) {
            typename Element::Leaf& leaf = allElements[elem].leaf;

            for (int i=0; i<leaf.nTriangles; i++) {
                int iTri = leaf.triangles[i];
                if (lookupFlags[iTri] == 0) {
                    result.append(iTri);
                    lookupFlags.set(iTri);
                }
            }
            return;
        }

        int firstChild = -allElements[elem].node.negativeChildIndex;

        McVec3f center = elemBox.getCenter();

        McBox3f childElemBox;

        // look in octant ---
        if (lowerLeftFront(box[0], box[2], box[4], center)){
            childElemBox.setValue(elemBox[0], center.x, elemBox[2], center.y,
                                  elemBox[4], center.z);
            lookupTriangle(firstChild+0, childElemBox, box, result);
        }

        // look in octant +--
        if (lowerRightFront(box[1], box[2], box[4], center)){
            childElemBox.setValue(center.x, elemBox[1], elemBox[2], center.y,
                                  elemBox[4], center.z);
            lookupTriangle(firstChild+1, childElemBox, box, result);
        }
        // look in octant -+-
        if (lowerLeftBack(box[0], box[3], box[4], center)){
            childElemBox.setValue(elemBox[0], center.x, center.y, elemBox[3],
                                  elemBox[4], center.z);
            lookupTriangle(firstChild+2, childElemBox, box, result);
        }
        // look in octant ++-
        if (lowerRightBack(box[1], box[3], box[4], center)){
            childElemBox.setValue(center.x, elemBox[1], center.y, elemBox[3],
                                  elemBox[4], center.z);
            lookupTriangle(firstChild+3, childElemBox, box, result);
        }
        // look in octant --+
        if (upperLeftFront(box[0], box[2], box[5], center)){
            childElemBox.setValue(elemBox[0], center.x, elemBox[2], center.y,
                                  center.z, elemBox[5]);
            lookupTriangle(firstChild+4, childElemBox, box, result);
        }
        // look in octant +-+
        if (upperRightFront(box[1], box[2], box[5], center)){
            childElemBox.setValue(center.x, elemBox[1], elemBox[2], center.y,
                                  center.z, elemBox[5]);
            lookupTriangle(firstChild+5, childElemBox, box, result);
        }
        // look in octant -++
        if (upperLeftBack(box[0], box[3], box[5], center)){
            childElemBox.setValue(elemBox[0], center.x, center.y, elemBox[3],
                                  center.z, elemBox[5]);
            lookupTriangle(firstChild+6, childElemBox, box, result);
        }
        // look in octant +++
        if (upperRightBack(box[1], box[3], box[5], center)){
            childElemBox.setValue(center.x, elemBox[1], center.y, elemBox[3],
                                  center.z, elemBox[5]);
            lookupTriangle(firstChild+7, childElemBox, box, result);
        }
    }

    //--------------------------------------------------------------------------

    int removeTriangle(int elem, McBox3f &elemBox, int iTri) {
        int i;

        if (isLeaf(elem)) {
            typename Element::Leaf& leaf = allElements[elem].leaf;
            
            for (i=0; i<leaf.nTriangles; i++)
                if (leaf.triangles[i] == iTri) {
                    leaf.nTriangles--;
                    break;
                }
            
            for (; i<leaf.nTriangles; i++)
                leaf.triangles[i] = leaf.triangles[i+1];
            
            return 1;
        }

        int firstChild = -allElements[elem].node.negativeChildIndex;

        McVec3f center = elemBox.getCenter();
        McBox3f &triBox = triBoxes[iTri];
        McBox3f childElemBox;

        // look in octant ---
        if (lowerLeftFront(triBox[0], triBox[2], triBox[4], center)){
            childElemBox.setValue(elemBox[0], center.x, elemBox[2], center.y,
                                  elemBox[4], center.z);
            if (intersectTriangle(childElemBox,iTri))
                removeTriangle(firstChild+0, childElemBox, iTri);
        }
        // look in octant +--
        if (lowerRightFront(triBox[1], triBox[2], triBox[4], center)){
            childElemBox.setValue(center.x, elemBox[1], elemBox[2], center.y,
                                  elemBox[4], center.z);
            if (intersectTriangle(childElemBox,iTri))
                removeTriangle(firstChild+1, childElemBox, iTri);
        }
        // look in octant -+-
        if (lowerLeftBack(triBox[0], triBox[3], triBox[4], center)){
            childElemBox.setValue(elemBox[0], center.x, center.y, elemBox[3],
                                  elemBox[4], center.z);
            if (intersectTriangle(childElemBox,iTri))
                removeTriangle(firstChild+2, childElemBox, iTri);
        }
        // look in octant ++-
        if (lowerRightBack(triBox[1], triBox[3], triBox[4], center)){
            childElemBox.setValue(center.x, elemBox[1], center.y, elemBox[3],
                                  elemBox[4], center.z);        
            if (intersectTriangle(childElemBox,iTri))
                removeTriangle(firstChild+3, childElemBox, iTri);
        }
        // look in octant --+
        if (upperLeftFront(triBox[0], triBox[2], triBox[5], center)){
            childElemBox.setValue(elemBox[0], center.x, elemBox[2], center.y,
                                  center.z, elemBox[5]);
            if (intersectTriangle(childElemBox,iTri))
                removeTriangle(firstChild+4, childElemBox, iTri);
        }
        // look in octant +-+
        if (upperRightFront(triBox[1], triBox[2], triBox[5], center)){
            childElemBox.setValue(center.x, elemBox[1], elemBox[2], center.y,
                                  center.z, elemBox[5]);
            if (intersectTriangle(childElemBox,iTri))
                removeTriangle(firstChild+5, childElemBox, iTri);
        }
        // look in octant -++
        if (upperLeftBack(triBox[0], triBox[3], triBox[5], center)){
            childElemBox.setValue(elemBox[0], center.x, center.y, elemBox[3],
                                  center.z, elemBox[5]);
            if (intersectTriangle(childElemBox,iTri))
                removeTriangle(firstChild+6, childElemBox, iTri);
        }
        // look in octant +++
        if (upperRightBack(triBox[1], triBox[3], triBox[5], center)){
            childElemBox.setValue(center.x, elemBox[1], center.y, elemBox[3],
                                  center.z, elemBox[5]);
            if (intersectTriangle(childElemBox,iTri))
                removeTriangle(firstChild+7, childElemBox, iTri);
        }

        return 0;
    }

    //--------------------------------------------------------------------------

    // the following eight routines check whether a point is contained
    // in a particular octant in space, relative to 'center'

    int lowerLeftFront(float x, float y, float z, const McVec3f &center)const{
        return x<=center.x && y<=center.y && z<=center.z;
    };

    int lowerLeftBack(float x, float y, float z, const McVec3f &center)const{
        return x<=center.x && center.y<=y && z<=center.z;
    };

    int lowerRightFront(float x, float y, float z, const McVec3f &center)const{
        return center.x<=x && y<=center.y && z<=center.z;
    };

    int lowerRightBack(float x, float y, float z, const McVec3f &center)const{
        return center.x<=x && center.y<=y && z<=center.z;
    };

    int upperLeftFront(float x, float y, float z, const McVec3f &center)const{
        return x<=center.x && y<=center.y && center.z<=z;
    };

    int upperLeftBack(float x, float y, float z, const McVec3f &center)const{
        return x<=center.x && center.y<=y && center.z<=z;
    };

    int upperRightFront(float x, float y, float z, const McVec3f &center)const{
        return center.x<=x && y<=center.y && center.z<=z;
    };

    int upperRightBack(float x, float y, float z, const McVec3f &center)const{
        return center.x<=x && center.y<=y && center.z<=z;
    };

    //--------------------------------------------------------------------------

    float eps;
    int maxDepth;
    int maxTriPerLeaf;
    int isSurface;
    T* mesh;
    const McVec3f* normals;
    McBox3f meshBox;
    McBitfield lookupFlags;
    McDArray<McBox3f> triBoxes;
};

template<>
inline FaceOctree<HxTetraGrid>::FaceOctree(int maxDepth, int maxTriPerLeaf){
    this->maxDepth = maxDepth;
    this->maxTriPerLeaf = maxTriPerLeaf;
    isSurface = 0;
    mesh=NULL;
}

template<>
inline FaceOctree<TetraGrid>::FaceOctree(int maxDepth, int maxTriPerLeaf){
    this->maxDepth = maxDepth;
    this->maxTriPerLeaf = maxTriPerLeaf;
    isSurface = 0;
    mesh=NULL;
}

template<>
inline FaceOctree<HxSurface>::FaceOctree(int maxDepth, int maxTriPerLeaf){
    this->maxDepth = maxDepth;
    this->maxTriPerLeaf = maxTriPerLeaf;
    isSurface = 1;
    mesh=NULL;
}

template<>
inline FaceOctree<Surface>::FaceOctree(int maxDepth, int maxTriPerLeaf){
    this->maxDepth = maxDepth;
    this->maxTriPerLeaf = maxTriPerLeaf;
    isSurface = 1;
    mesh=NULL;
}

#endif

/// @}
