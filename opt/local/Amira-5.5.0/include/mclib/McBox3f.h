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
#ifndef MC_BOX3F_H
#define MC_BOX3F_H

#include "McWinDLLApi.h"
#include "McVec3f.h"
#include "McMat4f.h"

#include <float.h>

/// This class represents an axis-aligned 3D box.
class McBox3f
{
  public:
    /// Default constructor - creates empty box.
    McBox3f() { makeEmpty(); }

    /// Constructor using given explicit bounds.
    McBox3f(float xmin, float xmax, float ymin, float ymax,
        float zmin, float zmax) {
        box[0] = xmin;  box[1] = xmax;
        box[2] = ymin;  box[3] = ymax;
        box[4] = zmin;  box[5] = zmax;
    }

    /// Copy constructor.
    McBox3f(const McBox3f& old){
        for (int i=0; i<6; i++)
            box[i] = old[i];
    }

    /** Constructor using a float[6] array. The array should contain the
        xmin, xmax, ymin, ymax, zmin, and zmax values of the box in that
        order. This storage convention is compatible with the Amira
        method HxSpatialData::getBoundingBox(). */
    McBox3f(const float bbox[6]) {
        for (int i=0; i<6; i++)
            box[i] = bbox[i];
    }

    /** Constructs box from two points. The points can be any pair of
        opposite points of the box. */
    McBox3f(const McVec3f& a, const McVec3f& b) {
        if (a.x<b.x) {box[0] = a.x; box[1] = b.x;}
        else         {box[0] = b.x; box[1] = a.x;}

        if (a.y<b.y) {box[2] = a.y; box[3] = b.y;}
        else         {box[2] = b.y; box[3] = a.y;}

        if (a.z<b.z) {box[4] = a.z; box[5] = b.z;}
        else         {box[4] = b.z; box[5] = a.z;}
    }

    /// Destructor.
    ~McBox3f() { }

    /// Returns true if box contains given point.
    int contains(const McVec3f& point, float eps=0) const {
        return (box[0]-eps <= point.x && point.x <= box[1]+eps &&
                box[2]-eps <= point.y && point.y <= box[3]+eps &&
                box[4]-eps <= point.z && point.z <= box[5]+eps );
    }

    /** Calculates distance to border for point inside the box. The
        smallest distance to any plane of the six box planes is
        returned. If the point is outside of the box -1 is returned. */
    float distanceFromBorder(const McVec3f& point) const {
        if (!contains(point))
            return -1.0;

        float d = point.x - box[0];
        float test;
        test = box[1] - point.x;
        if (test < d) {
            d = test;
        }
        test = point.y - box[2];
        if (test < d) {
            d = test;
        }
        test = box[3] - point.y;
        if (test < d) {
            d = test;
        }
        test = point.z - box[4];
        if (test < d) {
            d = test;
        }
        test = box[5] - point.z;
        if (test < d) {
            d = test;
        }
        return d;
    }

    /// Assignment operator.
    const McBox3f& operator=(const McBox3f &other) {
        box[0] = other[0]; box[1] = other[1]; box[2] = other[2];
        box[3] = other[3]; box[4] = other[4]; box[5] = other[5];
        return(*this);
    }

    /// Scaling operator.
    const McBox3f& operator*=(float scale) {
        box[0]*=scale; box[1]*=scale;
        box[2]*=scale; box[3]*=scale;
        box[4]*=scale; box[5]*=scale;
        return *this;
    }

    /// Scaling operator.
    McBox3f operator*(float scale) {
        return McBox3f(box)*=scale;
    }

    /** Index operator. The elements of the box denote the xmin, xmax,
        ymin, ymax, zmin, and zmax coordinates in that order. This
        storage convention is compatible with the Amira method
        HxSpatialData::getBoundingBox(). */
    float& operator[](int n) {
        return box[n];
    }

    /// Const version of index operator.
    const float& operator[](int n) const {
        return box[n];
    }

    /// Sets the complete box.
    void setValue(float minx, float maxx, float miny, float maxy,
        float minz, float maxz) {
        box[0] = minx; box[1] = maxx;
        box[2] = miny; box[3] = maxy;
        box[4] = minz; box[5] = maxz;
    }

    /// Extends the box to contain given point.
    void extendBy(const McVec3f& point){
        if (isEmpty()) {
            box[0]=box[1]=point.x;
            box[2]=box[3]=point.y;
            box[4]=box[5]=point.z;
        } else {
            if (point.x<box[0]) box[0]=point.x;
            if (point.x>box[1]) box[1]=point.x;
            if (point.y<box[2]) box[2]=point.y;
            if (point.y>box[3]) box[3]=point.y;
            if (point.z<box[4]) box[4]=point.z;
            if (point.z>box[5]) box[5]=point.z;
        }
    }

    /// Extends the box to contain given box
    void extendBy(const McBox3f& other){
        if (!other.isEmpty()) {
            extendBy(other.getMin());
            extendBy(other.getMax());
        }
    }

    /// Checks if min==max for all three coordinates.
    int isNull() const {
        return (box[0]==box[1] && box[2]==box[3] && box[4]==box[5]);
    }

    /** Checks if box is empty. A box is called empty if either xmax<xmin
        or ymax<ymin or zmax<zmin. */
    int isEmpty() const {
        return (box[1]<box[0]) || (box[3]<box[2]) || (box[5]<box[4]);
    }

    /// Checks whether the box is consistent, i.e. not empty.
    int isConsistent() const {
        return (box[0]<=box[1] && box[2]<=box[3] && box[4]<=box[5]);
    }

    /// Makes the box empty.
    void makeEmpty() {
        box[0]=box[2]=box[4]=0;
        box[1]=box[3]=box[5]=-1e10;
    }

    /// Enlarges the box by 'eps' to each side
    void extendByEps(float eps){
        box[0]-=eps;    box[1]+=eps;
        box[2]-=eps;    box[3]+=eps;
        box[4]-=eps;    box[5]+=eps;
    }

    /// Enlarges the box by 'eps' to each side
    void extendByEps(const McVec3f& eps){
        box[0]-=eps.x;    box[1]+=eps.x;
        box[2]-=eps.y;    box[3]+=eps.y;
        box[4]-=eps.z;    box[5]+=eps.z;
    }

    /// Returns frontal lower left corner.
    void getBox(float bbox[6]) const {
        bbox[0] = box[0]; bbox[1] = box[1]; bbox[2] = box[2];
        bbox[3] = box[3]; bbox[4] = box[4]; bbox[5] = box[5];
    }

    /// Returns frontal lower left corner.
    McVec3f getMin() const {
        return McVec3f(box[0], box[2], box[4]);
    }

    /// Returns backward upper right corner.
    McVec3f getMax() const {
        return McVec3f(box[1], box[3], box[5]);
    }

    /// Return center of the box.
    McVec3f getCenter() const {
        return McVec3f(.5f*(box[0]+box[1]),
            .5f*(box[2]+box[3]), .5f*(box[4]+box[5]));
    }

    /// Returns size of box (xmax-xmin, ymax-ymin, zmax-zmin).
    McVec3f getSize() const {
        return McVec3f(box[1]-box[0], box[3]-box[2] , box[5]-box[4]);
    }

    /** Returns the voxelsize if the box surrounds a lattice of dims d.
        According to the general Amira convention it is assumed that the
        box encloses the voxel centers of the lattice. Thus the size of
        the box is divided by (d[*]-1) in order to get the voxel size. */
    McVec3f getVoxelSize (const int* d) const {
        McVec3f vs;
        vs.x = (box[1] - box[0])/((d[0] > 1) ? (d[0] - 1) : 1);
        vs.y = (box[3] - box[2])/((d[1] > 1) ? (d[1] - 1) : 1);
        vs.z = (box[5] - box[4])/((d[2] > 1) ? (d[2] - 1) : 1);
        return vs;
    }

    /** calculate voxelsize from fractional dimensions */
    McVec3f getVoxelSize (const McVec3f& d) const {
        McVec3f vs;
        vs.x = (box[1] - box[0])/((d[0] > 1) ? (d[0] - 1) : 1);
        vs.y = (box[3] - box[2])/((d[1] > 1) ? (d[1] - 1) : 1);
        vs.z = (box[5] - box[4])/((d[2] > 1) ? (d[2] - 1) : 1);
        return vs;
    }

    /** Returns the number of voxels of a lattice with this bounding box
        and the given voxel size. A fractional number of voxels may be
        returned if the box size is not an integer multiple of the voxel
        size in any direction. */
    McVec3f getUniformDims (const McVec3f& voxelsize) {
        McVec3f d;
        for (int i = 0; i < 3; i++) {
            d[i] = (voxelsize[i] > 0)
                ? (box[2*i + 1] - box[2 * i]) / voxelsize[i] + 1.0f
                  : 0;
        }
        return d;
    }

    /** Returns the number of voxels of a lattice with this bounding box
        and the given voxel size. The number of voxels is rounded to the
        nearest integer value in all directions. */
    void getUniformDims (const McVec3f& voxelsize, int* dims) {
        McVec3f d;
        d = getUniformDims (voxelsize);
        dims[0] = int(d[0] + 0.5);
        dims[1] = int(d[1] + 0.5);
        dims[2] = int(d[2] + 0.5);
    }

    /** Enlarges bounding box such that we get an isotropic lattice
        with the given voxel size. The size of the grid is saved in @c
        dims. Before computing the isotropic grid, the bounding box is
        enlarged by @c eps. */
    void enlargeBBoxForIsotropicGrid (float voxelsize, float eps, int dims[3])
    {
        for ( int i=0; i<3; i++ ) {
            box[2*i]   -= eps;
            box[2*i+1] += eps;
            dims[i] = ((int)((box[2*i+1]-box[2*i])/voxelsize))+2;
            box[2*i+1] = box[2*i] + (dims[i]-1)*voxelsize;
        }
    }

    /** Enlarges a given bounding box such that we get an isotropic
        lattice with the given voxel size. New bounding box and the
        size of the grid are returned. */
    static void enlargeBBoxForIsotropicGrid (float voxelsize, float eps,
                                             float bbox[6], int dims[3])
    {
        for ( int i=0; i<3; i++ ) {
            bbox[2*i]   -= eps;
            bbox[2*i+1] += eps;
            dims[i] = ((int)((bbox[2*i+1]-bbox[2*i])/voxelsize))+2;
            bbox[2*i+1] = bbox[2*i] + (dims[i]-1)*voxelsize;
        }
    }

    /// Returns the volume of the box.
    float volume() const {
        if (isEmpty())
            return -1;
        return (box[1]-box[0]) * (box[3]-box[2]) * (box[5]-box[4]);
    }

    /** Returns true if the two boxes intersect each other.
        in case 'withTouch' is 1 intersects returns also true
        in case the boxes share at least one face */
    int intersects(const McBox3f &other, int withTouch = 0) const {
        if (isEmpty() || other.isEmpty())
            return 0;
        if (withTouch)
            return (   (box[0] <= other[1])         // xmin1 <= xmax2
                    && (box[1] >= other[0])         // xmax1 >= xmin2
                    && (box[2] <= other[3])         // ymin1 <= ymax2
                    && (box[3] >= other[2])         // ymax1 >= ymin2
                    && (box[4] <= other[5])         // zmin1 <= zmax2
                    && (box[5] >= other[4]));       // zmax1 >= zmin2
        else
            return (   (box[0] < other[1])          // xmin1 < xmax2
                    && (box[1] > other[0])          // xmax1 > xmin2
                    && (box[2] < other[3])          // ymin1 < ymax2
                    && (box[3] > other[2])          // ymax1 > ymin2
                    && (box[4] < other[5])          // zmin1 < zmax2
                    && (box[5] > other[4]));        // zmax1 > zmin2
    }

    /// Returns intersection of two boxes.
    McBox3f intersectWith(const McBox3f &other) const {
        McBox3f innerBox(0,0,0,0,0,0);
        if (!other.isEmpty() && !isEmpty()) {
            for (int i = 0; i < 3; i++) {
                int  min = i * 2;
                int  max = min + 1;
                if ((box[max] < other[min]) || (box[min] > other[max]))
                    return(McBox3f(0,0,0,0,0,0));
                innerBox[min] = box[min] < other[min] ? other[min] : box[min];
                innerBox[max] = box[max] < other[max] ? box[max] : other[max];
            }
        }
        return innerBox;
    }

    /** Computes intersection with a ray. The method returns true if the
        specified ray intersects the box, and false otherwise. In case of
        an intersection the intersection point is returned in c. The
        intersection point either lies on one of the six planes of the
        box or it is equal to the ray's origin if the origin lies inside
        the box.

        If there is an intersection and the pointer pPlaneIdx is not
        NULL, it will be filled with the index of the plane where the
        intersection took place.

        If there is an intersection and the pointer pParamT is not
        NULL, it will be filled with the t parameter of the ray
        equation: c = orig + t*dir.
    */
    bool intersectsRay(const McVec3f& orig, const McVec3f& dir, McVec3f& c,
                                                int* pPlaneIdx = NULL, float* pParamT = NULL) const
        {
        bool inside = true;
        int i, quadrant[3];
        float maxT[3], candidatePlane[3];

        for (i=0; i<3; i++) {
            if (orig[i]<box[2*i]) {
                quadrant[i] = -1;
                candidatePlane[i] = box[2*i];
                inside = false;
            } else if (orig[i]>box[2*i+1]) {
                quadrant[i] = 1;
                candidatePlane[i] = box[2*i+1];
                inside = false;
            } else quadrant[i] = 0;
        }

        if (inside) {
            c = orig;
            return true;
        }

        for (i=0; i<3; i++) {
            if (quadrant[i]!=0 && dir[i]!=0.)
                maxT[i] = (candidatePlane[i]-orig[i])/dir[i];
            else maxT[i] = -1;
        }

        int whichPlane = 0;
        for (i=1; i<3; i++)
            if (maxT[whichPlane] < maxT[i])
                whichPlane = i;

        if (maxT[whichPlane] < 0.)
            return false;

        for (i=0; i<3; i++) {
            if (whichPlane != i) {
                c[i] = orig[i] + maxT[whichPlane]*dir[i];
                if (c[i]<box[2*i] || c[i]>box[2*i+1])
                    return false;
            } else c[i] = candidatePlane[i];
        }

        //Give plane where intersection took place
        if (pPlaneIdx) {
            *pPlaneIdx =
                (quadrant[whichPlane] < 0) ? 2*whichPlane : 2*whichPlane + 1;
        }

        //Give t parameter
        if (pParamT) {
            *pParamT = maxT[whichPlane];
        }

        return true;
    }

    /** Computes the intersection point of a ray starting inside the box with the box.

        @param orig
            Origin of the ray. Must be inside the box or on its faces.

        @param dir
            Direction of the ray.

        @param interPoint
            Intersection point of the ray with the box.

        @param pPlaneIdx
            If not NULL, it will be filled with
            the index of the plane where the intersection took place.

        @param pParamT
            If not NULL, it will be filled with
            the t parameter of the ray equation: c = orig + t*dir.

        @returns true, if an intersection was found.
        @returns false, only in the rare case that dir represents the null vector.

        @note This function works only properly, if orig lies inside or on the box.
        If this does not hold, the return values won't be usefull.
        It is not checked, whether orig is inside or outside the box.
        Furthermore, the function may return true, if orig is outside the box.
        If you're not sure, whether orig is inside or outside the box,
        call #getIntersectionWithRayFromAnywhere.

        @see #intersectsRay
        @see #getIntersectionWithRayFromCenter
        @see #getIntersectionWithRayFromAnywhere
    */
    bool getIntersectionWithRayFromInside(const McVec3f& orig,
                                          const McVec3f& dir,
                                          McVec3f& interPoint,
                                          int* pPlaneIdx = NULL,
                                          float* pParamT = NULL) const
    {
        //Ray formula: p = orig + t*dir
        //Lets get the smallest non-negative t, to find the
        //intersection of the ray with the box.  If orig is inside the
        //box, then this intersection point lies on the box for sure.
        float minT(FLT_MAX);
        int whichPlane(-1);
        for(int i=0;i<6;i++) {
            int component = i/2;

            if (dir[component] == 0.0) continue;

            float currentT = (box[i] - orig[component]) / dir[component];
            if ((currentT >= 0.0) && (currentT < minT)) {
                minT = currentT;
                whichPlane = i;
            }
        }

        //Is our t non-negative? I.e., whichPlane != -1?
        if (whichPlane != -1) {
            assert(minT >= 0.0);

            interPoint = orig + minT*dir;
            //The following is always true and already assured by the
            //formula above.  But due to numerical errors, the
            //intersection point is not exactly on the plane.  We
            //force it.
            // FK: removed this assertion as it does not take into account absolute
            // value of numbers.
            // assert( fabs(interPoint[whichPlane / 2] - box[whichPlane]) < 1E-6 );
            interPoint[whichPlane / 2] = box[whichPlane];

            //Give the caller some infos, if he wants to have them
            if (pPlaneIdx) *pPlaneIdx = whichPlane;
            if (pParamT) *pParamT = minT;

            return true;
        }

        //This might happen, if dir is the null vector.
        //Or orig lies outside the box AND dir points away from the box.
        return false;
    }

    /** Computes the intersection point of a ray starting at the
        center of the box with its faces.

        @see #getIntersectionWithRayFromInside
    */
    bool getIntersectionWithRayFromCenter(const McVec3f& dir,
                                          McVec3f& interPoint,
                                          int* pPlaneIdx = NULL,
                                          float* pParamT = NULL) const
    {
        return getIntersectionWithRayFromInside(getCenter(), dir, interPoint,
                                                pPlaneIdx, pParamT);
    }

    /** Computes the first intersection point of an arbitrary ray with
        the box.

        @returns true, if the ray intersects the box.
        The intersection point is written to interPoint.

        @see #intersectsRay
        @see #getIntersectionWithRayFromInside
    */
    bool getIntersectionWithRayFromAnywhere(const McVec3f& orig,
                                            const McVec3f& dir,
                                            McVec3f& interPoint,
                                            int* pPlaneIdx = NULL,
                                            float* pParamT = NULL) const
    {
        //It doesn't matter how contains() handles points ON the box.
        // Both functions can handle this case.
        if (contains(orig)) {
            return getIntersectionWithRayFromInside(orig, dir, interPoint,
                                                    pPlaneIdx, pParamT);
        }

        //else
        return intersectsRay(orig, dir, interPoint, pPlaneIdx, pParamT);
    }

    /** Clip a line segment defined by @c p0 and @c p1 against the box.
     *  This method uses the Liang-Barsky clipping algorithm.
     *  @returns true if the line segment intersects the box. 
     *  In this case,  @c q0 and @c q1 hold the intersection points 
     *  of the segment with the box.
     */  
    bool clipLine(const McVec3f& p0,
                  const McVec3f& p1,
                  McVec3f& q0,
                  McVec3f& q1) 
    {
        double t0(0.0);
        double t1(1.0);

        q0 = p0;
        q1 = p1;

        double Dx(q1.x-q0.x);
        if (LiangBarskyClipTest(-Dx, q0.x-box[0], t0, t1) ) {
            if (LiangBarskyClipTest(Dx, box[1]-q0.x, t0, t1) ) {
                double Dy(q1.y-q0.y);
                if (LiangBarskyClipTest(-Dy, q0.y-box[2], t0, t1) ) {
                    if (LiangBarskyClipTest(Dy, box[3]-q0.y, t0, t1) ) {
                        double Dz(q1.z-q0.z);
                        if (LiangBarskyClipTest(-Dz, q0.z-box[4], t0, t1) ) {
                            if (LiangBarskyClipTest(Dz, box[5]-q0.z, t0, t1) ) {
                                if (t0 > 0) {
                                    q0.x = p0.x + t0*Dx;
                                    q0.y = p0.y + t0*Dy;
                                    q0.z = p0.z + t0*Dz;
                                }
                                if (t1 < 1) {
                                    q1.x = p0.x + t1*Dx;
                                    q1.y = p0.y + t1*Dy;
                                    q1.z = p0.z + t1*Dz;
                                }
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }


    /// Gets the corners of the box.
    void getBounds(float &xmin, float &ymin, float &zmin,
                   float &xmax, float &ymax, float &zmax) const
    {
        xmin = box[0]; xmax = box[1];
        ymin = box[2]; ymax = box[3];
        zmin = box[4]; zmax = box[5];
    }

    /// Gets the corners of the box.
    void getBounds(McVec3f& _min, McVec3f& _max) const {
        _min.setValue(box[0],box[2],box[4]);
        _max.setValue(box[1],box[3],box[5]);
    }

    /// Cast to float*
    operator float* () { return box; }

    /// Cast to const float*
    operator const float* () const { return box; }

    /// Check for equality.
    friend int operator == ( const McBox3f & a, const McBox3f & b )
    {
        return  a.box[0] == b.box[0]
            &&  a.box[1] == b.box[1]
            &&  a.box[2] == b.box[2]
            &&  a.box[3] == b.box[3]
            &&  a.box[4] == b.box[4]
            &&  a.box[5] == b.box[5]
            ;
    }

    /// Check for inequality.
    friend int operator != ( const McBox3f & a, const McBox3f & b )
    {
        return !( a == b );
    }


  protected:
    /// The boxes dimensions stored as minx, maxx, miny, maxy, minz, maxz.
    float box[6];


    /// Helper function for the clipLine method
    bool LiangBarskyClipTest(double p, 
                             double q,
                             double& t0, 
                             double& t1) 
    {
        if (p < 0) {
            double t(q/p);
            if (t > t1) return false;
            if (t > t0) t0 = t;
        }
        else if (p > 0) {
            double t(q/p);
            if (t < t0) return false;
            if (t < t1) t1 = t;
        }
        else if (q < 0) return false;
        return true;
    }


};

#endif

/// @}
