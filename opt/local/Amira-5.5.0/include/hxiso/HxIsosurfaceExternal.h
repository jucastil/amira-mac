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

/// @addtogroup hxiso hxiso
/// @{
#ifndef HX_ISOSURFACEEXTERNAL_H
#define HX_ISOSURFACEEXTERNAL_H

#include <hxiso/HxIsoWinDLLApi.h>
#include <hxiso/MyLookupTables.h>

#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>
#include <mclib/McPrimType.h>
#include <hxsurface/SoTriSurface.h>

#ifndef NOAMIRA
#include <hxfield/HxCoord3.h>
#include <hxfield/HxRegScalarField3.h>
#include <hxfield/HxUniformScalarField3.h>
#endif
#include <mclib/McDArray.h>


class SoTriSurface;
class McProgressInterface;
class HxObject;
class HxCoord3;
class HxRegScalarField3;

class HXISO_API HxIsosurfaceExternal  {
public:
  HxIsosurfaceExternal(const mculong* dims, 
		                  float threshold, int whichAlgorithm, float paramCC,
		                  SoTriSurface* result, HxCoord3 *_coord3, McProgressInterface* progress=0);
    
  void setIntersectionCallback(float (*f)(int ia, int ib, HxObject* object),
	                             HxObject* object);


  void computeProcedural(const McVec3f& origin, const McVec3f& cellsize,
                         float (*getValue) (void*, int x, int y, int z), void* callBackUserData);

#ifndef NOAMIRA
  void computeUniform(void* data, const McPrimType& pt, const McVec3f& origin, 
		                  const McVec3f& cellsize);
  void computeCurvilinear(HxRegScalarField3* volume);
#endif

protected:

  void computeSurfaceInternal();

    // Global flags
    enum { UnifByte, UnifShort, UnifInt, UnifFloat, UnifDbl, Curvilinear, UnifUShort, UnifFloatProcedural} dataType;

  
  /////// only used in the uniform case:
  void * dataPtr;
  float cellSizeX, cellSizeY, cellSizeZ; // Uniform fields only
  McVec3f origin;
  //////

  /////// only used in the curvilinear case:
  HxCoord3* coord3;
  HxRegScalarField3* volume;
  //////

  /////// only used in the procedural case:
    float (*getValueFunc)(void*, int, int, int);
    void* getValueUserData;
  //////

    mculong dimX, dimY, dimZ;
    float threshold;

    HxObject* intersectionCallbackObject;
    float (*intersectionCallback)(int, int, HxObject*);

    SoTriSurface* soTriSurface;
    McProgressInterface* progress;
    // This is either STANDARD_CUBES or COMPACT_CUBES.
    int	whichAlgorithm;

    // Used by compact cubes (don't weld vertices paramCC...1-paramCC)
    float paramCC;

    // number of degenerate triangles eliminated in compact cubes
    int mNumDegenerate;

    // current numbers of coords and triangles collected from threads
    int mNumCoordsCollected;
    int mNumTrianglesCollected;

    bool collect(int it, McDArray<SbVec3f> &coords, McDArray<SbVec3f> &normals, 
                 McDArray<SbVec3i32> &triangles, McDArray<int> &vertexOffsets);

    void computeSurface();
    void computeSurfaceMC();
    void computeSurfaceCC();

    ////////////////////////////////////////////////////////////////////////////////
    //
    //                        computeIndex()
    //           compute ISO 8-bit index to the lookup table
    //
    //    computeIndexByte   - uniform lattice,     byte data (CT data)
    //    computeIndexShort  - uniform lattice,     short data
    //    computeIndexFloat  - uniform lattice,     float data
    //    computeIndexCurv   - curvilinear lattice, float data
    //
    //  - vertices are numbered as in the original paper
    //  - index = v8.v7.v6.v5.v4.v3.v2.v1 (one bit for each vertice)
    //  - acceleration by computing only 4 new bits !
    //
    inline void computeIndexCurv(int zpos, int ypos, int xpos, unsigned int &inoutIndex)
    {
    #ifndef NOAMIRA
        if (xpos) { // not the first cube in x direction
            // get 4 bits from index of last cube:
            //        v2->v1, v6->v5        v4<-v3, v8<-v7
            inoutIndex = ((inoutIndex & 34) >> 1) | ((inoutIndex & 68) << 1);
        }
        else { // xpos == 0 -> first cube in x direction
            inoutIndex = 0;
            // compute these 4 bits newly
            if (volume->evalReg(xpos,ypos,  zpos  ) > threshold) inoutIndex |=   1; //  v1
            if (volume->evalReg(xpos,ypos+1,zpos  ) > threshold) inoutIndex |=   8; //  v4
            if (volume->evalReg(xpos,ypos,  zpos+1) > threshold) inoutIndex |=  16; //  v5
            if (volume->evalReg(xpos,ypos+1,zpos+1) > threshold) inoutIndex |= 128; //  v8
        }

        // compute index only for v2, v3, v6, v7
        if (volume->evalReg(xpos+1,ypos,  zpos  ) > threshold) inoutIndex |=  2; // v2
        if (volume->evalReg(xpos+1,ypos+1,zpos  ) > threshold) inoutIndex |=  4; // v3
        if (volume->evalReg(xpos+1,ypos,  zpos+1) > threshold) inoutIndex |= 32; // v6
        if (volume->evalReg(xpos+1,ypos+1,zpos+1) > threshold) inoutIndex |= 64; // v7

    #endif
    }


    ////////////////////////////////////////////////////////////////////////////////
    inline void computeIndexUnifByte(int zpos, int ypos, int xpos, unsigned int &inoutIndex)
    {
        unsigned char* data = (unsigned char*) dataPtr;
        unsigned char t = (unsigned char) threshold;

        if (xpos)
            inoutIndex = ((inoutIndex & 34) >> 1) | ((inoutIndex & 68) << 1);
        else {
            inoutIndex = 0;
            if (data[( zpos   *dimY+ypos  )*dimX+xpos] > t) inoutIndex |=   1; //v1
            if (data[( zpos   *dimY+ypos+1)*dimX+xpos] > t) inoutIndex |=   8; //v4
            if (data[((zpos+1)*dimY+ypos  )*dimX+xpos] > t) inoutIndex |=  16; //v5
            if (data[((zpos+1)*dimY+ypos+1)*dimX+xpos] > t) inoutIndex |= 128; //v8
        }

        if (data[( zpos   *dimY+ypos  )*dimX+xpos+1] > t) inoutIndex |=  2; // v2
        if (data[( zpos   *dimY+ypos+1)*dimX+xpos+1] > t) inoutIndex |=  4; // v3
        if (data[((zpos+1)*dimY+ypos  )*dimX+xpos+1] > t) inoutIndex |= 32; // v6
        if (data[((zpos+1)*dimY+ypos+1)*dimX+xpos+1] > t) inoutIndex |= 64; // v7
    }


    ////////////////////////////////////////////////////////////////////////////////
    inline void computeIndexUnifShort(int zpos, int ypos, int xpos, unsigned int &inoutIndex)
    {
        short* data = (short*) dataPtr;
        short t = (short) threshold;

        if (xpos)
            inoutIndex = ((inoutIndex & 34) >> 1) | ((inoutIndex & 68) << 1);
        else {
            inoutIndex = 0;
            if (data[( zpos   *dimY+ypos  )*dimX+xpos] > t) inoutIndex |=   1; //v1
            if (data[( zpos   *dimY+ypos+1)*dimX+xpos] > t) inoutIndex |=   8; //v4
            if (data[((zpos+1)*dimY+ypos  )*dimX+xpos] > t) inoutIndex |=  16; //v5
            if (data[((zpos+1)*dimY+ypos+1)*dimX+xpos] > t) inoutIndex |= 128; //v8
        }

        if (data[( zpos   *dimY+ypos  )*dimX+xpos+1] > t) inoutIndex |=  2; // v2
        if (data[( zpos   *dimY+ypos+1)*dimX+xpos+1] > t) inoutIndex |=  4; // v3
        if (data[((zpos+1)*dimY+ypos  )*dimX+xpos+1] > t) inoutIndex |= 32; // v6
        if (data[((zpos+1)*dimY+ypos+1)*dimX+xpos+1] > t) inoutIndex |= 64; // v7
    }


    ////////////////////////////////////////////////////////////////////////////////
    inline void computeIndexUnifUShort(int zpos, int ypos, int xpos, unsigned int &inoutIndex)
    {
        unsigned short* data = (unsigned short*) dataPtr;
        unsigned short t = (unsigned short) threshold;

        if (xpos)
            inoutIndex = ((inoutIndex & 34) >> 1) | ((inoutIndex & 68) << 1);
        else {
            inoutIndex = 0;
            if (data[( zpos   *dimY+ypos  )*dimX+xpos] > t) inoutIndex |=   1; //v1
            if (data[( zpos   *dimY+ypos+1)*dimX+xpos] > t) inoutIndex |=   8; //v4
            if (data[((zpos+1)*dimY+ypos  )*dimX+xpos] > t) inoutIndex |=  16; //v5
            if (data[((zpos+1)*dimY+ypos+1)*dimX+xpos] > t) inoutIndex |= 128; //v8
        }

        if (data[( zpos   *dimY+ypos  )*dimX+xpos+1] > t) inoutIndex |=  2; // v2
        if (data[( zpos   *dimY+ypos+1)*dimX+xpos+1] > t) inoutIndex |=  4; // v3
        if (data[((zpos+1)*dimY+ypos  )*dimX+xpos+1] > t) inoutIndex |= 32; // v6
        if (data[((zpos+1)*dimY+ypos+1)*dimX+xpos+1] > t) inoutIndex |= 64; // v7
    }


    ////////////////////////////////////////////////////////////////////////////////
    inline void computeIndexUnifInt(int zpos, int ypos, int xpos, unsigned int &inoutIndex)
    {
        int* data = (int*) dataPtr;
        int t = (int) threshold;

        if (xpos)
            inoutIndex = ((inoutIndex & 34) >> 1) | ((inoutIndex & 68) << 1);
        else {
            inoutIndex = 0;
            if (data[( zpos   *dimY+ypos  )*dimX+xpos] > t) inoutIndex |=   1; //v1
            if (data[( zpos   *dimY+ypos+1)*dimX+xpos] > t) inoutIndex |=   8; //v4
            if (data[((zpos+1)*dimY+ypos  )*dimX+xpos] > t) inoutIndex |=  16; //v5
            if (data[((zpos+1)*dimY+ypos+1)*dimX+xpos] > t) inoutIndex |= 128; //v8
        }

        if (data[( zpos   *dimY+ypos  )*dimX+xpos+1] > t) inoutIndex |=  2; // v2
        if (data[( zpos   *dimY+ypos+1)*dimX+xpos+1] > t) inoutIndex |=  4; // v3
        if (data[((zpos+1)*dimY+ypos  )*dimX+xpos+1] > t) inoutIndex |= 32; // v6
        if (data[((zpos+1)*dimY+ypos+1)*dimX+xpos+1] > t) inoutIndex |= 64; // v7
    }


    ////////////////////////////////////////////////////////////////////////////////
    inline void computeIndexUnifFloat(int zpos, int ypos, int xpos, unsigned int &inoutIndex)
    {
        float* data = (float*) dataPtr;
        float t = (float) threshold;

        if (xpos)
            inoutIndex = ((inoutIndex & 34) >> 1) | ((inoutIndex & 68) << 1);
        else {
            inoutIndex = 0;
            if (data[( zpos   *dimY+ypos  )*dimX+xpos] > t) inoutIndex |=   1; //v1
            if (data[( zpos   *dimY+ypos+1)*dimX+xpos] > t) inoutIndex |=   8; //v4
            if (data[((zpos+1)*dimY+ypos  )*dimX+xpos] > t) inoutIndex |=  16; //v5
            if (data[((zpos+1)*dimY+ypos+1)*dimX+xpos] > t) inoutIndex |= 128; //v8
        }

        if (data[( zpos   *dimY+ypos  )*dimX+xpos+1] > t) inoutIndex |=  2; // v2
        if (data[( zpos   *dimY+ypos+1)*dimX+xpos+1] > t) inoutIndex |=  4; // v3
        if (data[((zpos+1)*dimY+ypos  )*dimX+xpos+1] > t) inoutIndex |= 32; // v6
        if (data[((zpos+1)*dimY+ypos+1)*dimX+xpos+1] > t) inoutIndex |= 64; // v7
    }


    ////////////////////////////////////////////////////////////////////////////////
    inline void computeIndexUnifDbl(int zpos, int ypos, int xpos, unsigned int &inoutIndex)
    {
        double* data = (double*) dataPtr;
        double t = (double) threshold;

        if (xpos)
            inoutIndex = ((inoutIndex & 34) >> 1) | ((inoutIndex & 68) << 1);
        else {
            inoutIndex = 0;
            if (data[( zpos   *dimY+ypos  )*dimX+xpos] > t) inoutIndex |=   1; //v1
            if (data[( zpos   *dimY+ypos+1)*dimX+xpos] > t) inoutIndex |=   8; //v4
            if (data[((zpos+1)*dimY+ypos  )*dimX+xpos] > t) inoutIndex |=  16; //v5
            if (data[((zpos+1)*dimY+ypos+1)*dimX+xpos] > t) inoutIndex |= 128; //v8
        }

        if (data[( zpos   *dimY+ypos  )*dimX+xpos+1] > t) inoutIndex |=  2; // v2
        if (data[( zpos   *dimY+ypos+1)*dimX+xpos+1] > t) inoutIndex |=  4; // v3
        if (data[((zpos+1)*dimY+ypos  )*dimX+xpos+1] > t) inoutIndex |= 32; // v6
        if (data[((zpos+1)*dimY+ypos+1)*dimX+xpos+1] > t) inoutIndex |= 64; // v7
    }


    ////////////////////////////////////////////////////////////////////////////////
    inline void computeIndexUnifFloatProcedural(int zpos, int ypos, int xpos, unsigned int &inoutIndex)
    {
        float t = (float) threshold;

        if (xpos)
            inoutIndex = ((inoutIndex & 34) >> 1) | ((inoutIndex & 68) << 1);
        else {
            inoutIndex = 0;
            if (getValueFunc(getValueUserData,xpos, ypos,  zpos)   > t) inoutIndex |=   1; //v1
            if (getValueFunc(getValueUserData,xpos, ypos+1,zpos)   > t) inoutIndex |=   8; //v4
            if (getValueFunc(getValueUserData,xpos, ypos,  zpos+1) > t) inoutIndex |=  16; //v5
            if (getValueFunc(getValueUserData,xpos, ypos+1,zpos+1) > t) inoutIndex |= 128; //v8
        }

        if (getValueFunc(getValueUserData,xpos+1, ypos, zpos)    > t) inoutIndex |=   2; //v2
        if (getValueFunc(getValueUserData,xpos+1, ypos+1,  zpos) > t) inoutIndex |=   4; //v3
        if (getValueFunc(getValueUserData,xpos+1, ypos, zpos+1)  > t) inoutIndex |=  32; //v6
        if (getValueFunc(getValueUserData,xpos+1, ypos+1,zpos+1) > t) inoutIndex |=  64; //v7
    }

    ////////////////////////////////////////////////////////////////////////////////
    //
    //               computeIntersection()
    //         intersection along the given edge
    //
    //    computeIntersectionByte  - uniform lattice, byte data (CT data)
    //    computeIntersectionShort - uniform lattice, short data
    //    computeIntersectionFloat - uniform lattice, float data
    //    computeIntersectionCurv  - curvilinear lattice, float data
    //
    //  - linear interpolation on the specified edge
    //  - computing normals
    //  - computing (location of) nearest gridpoint (for CC only)
    //
    inline McVec3f computeIntersectionCurv(
        int zpos, int ypos, int xpos, int edge, McVec3f& normal, size_t& l)
    {
    #ifndef NOAMIRA
        int xa, ya, za, xe, ye, ze;
        float scale, leftval, rightval;
        McVec3f va, ve, vm, na, ne; // vertices and normal vectors
        // float h1[3], h2[3]; // temporary

        // These are zero if x/y/z pos are on grid boundary, 1 otherwise
        // int xup, yup, zup, xlow, ylow, zlow;

        // find beginning point of the edge
        xa = xpos + edge_ends[edge*6];
        ya = ypos + edge_ends[edge*6+1];
        za = zpos + edge_ends[edge*6+2];
        coord3->pos(xa,ya,za,&va[0]);
        leftval = volume->evalReg(xa,ya,za);

        // find end point of the edge
        xe = xpos + edge_ends[edge*6+3];
        ye = ypos + edge_ends[edge*6+4];
        ze = zpos + edge_ends[edge*6+5];
        coord3->pos(xe,ye,ze,&ve[0]);
        rightval = volume->evalReg(xe,ye,ze);

        // Linear interpolation
        scale = (threshold-leftval)/(rightval-leftval);
        if (scale > 0.5) l = (ze*dimY+ye)*dimX+xe;
        else l = (za*dimY+ya)*dimX+xa;

        vm = va + scale*(ve-va);
        normal.setValue(1,0,0);
        return vm;
    #else
        return McVec3f(0,0,0);
    #endif
    }


    ////////////////////////////////////////////////////////////////////////////////
    inline McVec3f computeIntersectionUnifByte(
        int zpos, int ypos, int xpos, int edge, McVec3f& normal, size_t& l)
    {
        unsigned char* data = (unsigned char*) dataPtr;
        unsigned char leftval, rightval;
        int xa, ya, za, xe, ye, ze;
        size_t le;
        float scale = 0.0;
        McVec3f va, ve, vm, na, ne;
        char xup,xlow,yup,ylow,zup,zlow;

        xa = xpos + edge_ends[edge*6];
        ya = ypos + edge_ends[edge*6+1];
        za = zpos + edge_ends[edge*6+2];
        va = origin + McVec3f(xa*cellSizeX, ya*cellSizeY, za*cellSizeZ);
        l  = (za*dimY+ya)*dimX+xa;
        leftval = data[l];

        xe = xpos + edge_ends[edge*6+3];
        ye = ypos + edge_ends[edge*6+4];
        ze = zpos + edge_ends[edge*6+5];
        ve = origin + McVec3f(xe*cellSizeX, ye*cellSizeY, ze*cellSizeZ);
        le = (ze*dimY+ye)*dimX+xe;
        rightval = data[le];

        xup  = (xa >= dimX - 1) ? 0 : 1;
        yup  = (ya >= dimY - 1) ? 0 : 1;
        zup  = (za >= dimZ - 1) ? 0 : 1;
        xlow = (xa <= 0 )       ? 0 : 1;
        ylow = (ya <= 0 )       ? 0 : 1;
        zlow = (za <= 0 )       ? 0 : 1;

        na[0] = (data[(za*dimY+ya)*dimX+xa+xup] -
            data[(za*dimY+ya)*dimX+xa-xlow]) / ((xup+xlow)*cellSizeX);
        na[1] = (data[(za*dimY+ya+yup)*dimX+xa] -
            data[(za*dimY+ya-ylow)*dimX+xa]) / ((yup+ylow)*cellSizeY);
        na[2] = (data[((za+zup)*dimY+ya)*dimX+xa] -
            data[((za-zlow)*dimY+ya)*dimX+xa]) / ((zup+zlow)*cellSizeZ);

        xup  = (xe >= dimX - 1) ? 0 : 1;
        yup  = (ye >= dimY - 1) ? 0 : 1;
        zup  = (ze >= dimZ - 1) ? 0 : 1;
        xlow = (xe <= 0 )       ? 0 : 1;
        ylow = (ye <= 0 )       ? 0 : 1;
        zlow = (ze <= 0 )       ? 0 : 1;

        ne[0] = (data[(ze*dimY+ye)*dimX+xe+xup] -
            data[(ze*dimY+ye)*dimX+xe-xlow]) / ((xup+xlow)*cellSizeX);
        ne[1] = (data[(ze*dimY+ye+yup)*dimX+xe] -
            data[(ze*dimY+ye-ylow)*dimX+xe]) / ((yup+ylow)*cellSizeY);
        ne[2] = (data[((ze+zup)*dimY+ye)*dimX+xe] -
            data[((ze-zlow)*dimY+ye)*dimX+xe]) / ((zup+zlow)*cellSizeZ);

        scale = (threshold - leftval) / (rightval - leftval);
        if (scale > 0.5) l=le;
        vm = va + scale*(ve-va);
        normal =  - na - scale*(ne-na);

        return vm;
    }


    ////////////////////////////////////////////////////////////////////////////////
    inline McVec3f computeIntersectionUnifShort(
        int zpos, int ypos, int xpos, int edge, McVec3f& normal, size_t& l)
    {
        short* data = (short*) dataPtr;
        short leftval, rightval;
        int xa, ya, za, xe, ye, ze;
        size_t la, le;
        float scale = 0.0;
        McVec3f va, ve, vm, na, ne;
        char xup,xlow,yup,ylow,zup,zlow;

        xa = xpos + edge_ends[edge*6];
        ya = ypos + edge_ends[edge*6+1];
        za = zpos + edge_ends[edge*6+2];
        va = origin + McVec3f(xa*cellSizeX, ya*cellSizeY, za*cellSizeZ);
        la = (za*dimY+ya)*dimX+xa;
        leftval = data[la];

        xe = xpos + edge_ends[edge*6+3];
        ye = ypos + edge_ends[edge*6+4];
        ze = zpos + edge_ends[edge*6+5];
        ve = origin + McVec3f(xe*cellSizeX, ye*cellSizeY, ze*cellSizeZ);
        le = (ze*dimY+ye)*dimX+xe;
        rightval = data[le];

        xup  = (xa >= dimX - 1) ? 0 : 1;
        yup  = (ya >= dimY - 1) ? 0 : 1;
        zup  = (za >= dimZ - 1) ? 0 : 1;
        xlow = (xa <= 0 )       ? 0 : 1;
        ylow = (ya <= 0 )       ? 0 : 1;
        zlow = (za <= 0 )       ? 0 : 1;

        na[0] = (data[(za*dimY+ya)*dimX+xa+xup] -
            data[(za*dimY+ya)*dimX+xa-xlow]) / ((xup+xlow)*cellSizeX);
        na[1] = (data[(za*dimY+ya+yup)*dimX+xa] -
            data[(za*dimY+ya-ylow)*dimX+xa]) / ((yup+ylow)*cellSizeY);
        na[2] = (data[((za+zup)*dimY+ya)*dimX+xa] -
            data[((za-zlow)*dimY+ya)*dimX+xa]) / ((zup+zlow)*cellSizeZ);

        xup  = (xe >= dimX - 1) ? 0 : 1;
        yup  = (ye >= dimY - 1) ? 0 : 1;
        zup  = (ze >= dimZ - 1) ? 0 : 1;
        xlow = (xe <= 0 )       ? 0 : 1;
        ylow = (ye <= 0 )       ? 0 : 1;
        zlow = (ze <= 0 )       ? 0 : 1;

        ne[0] = (data[(ze*dimY+ye)*dimX+xe+xup] -
            data[(ze*dimY+ye)*dimX+xe-xlow]) / ((xup+xlow)*cellSizeX);
        ne[1] = (data[(ze*dimY+ye+yup)*dimX+xe] -
            data[(ze*dimY+ye-ylow)*dimX+xe]) / ((yup+ylow)*cellSizeY);
        ne[2] = (data[((ze+zup)*dimY+ye)*dimX+xe] -
            data[((ze-zlow)*dimY+ye)*dimX+xe]) / ((zup+zlow)*cellSizeZ);

        scale = (threshold - leftval) / (rightval - leftval);
        l = -1;
        if (scale <= paramCC) l=la;
        if (scale >  1.-paramCC) l=le;
        vm = va + scale*(ve-va);
        normal =  - na - scale*(ne-na);

        return vm;
    }


    ////////////////////////////////////////////////////////////////////////////////
    inline McVec3f computeIntersectionUnifUShort(
        int zpos, int ypos, int xpos, int edge, McVec3f& normal, size_t& l)
    {
        unsigned short* data = (unsigned short*) dataPtr;
        unsigned short leftval, rightval;
        int xa, ya, za, xe, ye, ze;
        size_t la, le;
        float scale = 0.0;
        McVec3f va, ve, vm, na, ne;
        char xup,xlow,yup,ylow,zup,zlow;

        xa = xpos + edge_ends[edge*6];
        ya = ypos + edge_ends[edge*6+1];
        za = zpos + edge_ends[edge*6+2];
        va = origin + McVec3f(xa*cellSizeX, ya*cellSizeY, za*cellSizeZ);
        la = (za*dimY+ya)*dimX+xa;
        leftval = data[la];

        xe = xpos + edge_ends[edge*6+3];
        ye = ypos + edge_ends[edge*6+4];
        ze = zpos + edge_ends[edge*6+5];
        ve = origin + McVec3f(xe*cellSizeX, ye*cellSizeY, ze*cellSizeZ);
        le = (ze*dimY+ye)*dimX+xe;
        rightval = data[le];

        xup  = (xa >= dimX - 1) ? 0 : 1;
        yup  = (ya >= dimY - 1) ? 0 : 1;
        zup  = (za >= dimZ - 1) ? 0 : 1;
        xlow = (xa <= 0 )       ? 0 : 1;
        ylow = (ya <= 0 )       ? 0 : 1;
        zlow = (za <= 0 )       ? 0 : 1;

        na[0] = (data[(za*dimY+ya)*dimX+xa+xup] -
            data[(za*dimY+ya)*dimX+xa-xlow]) / ((xup+xlow)*cellSizeX);
        na[1] = (data[(za*dimY+ya+yup)*dimX+xa] -
            data[(za*dimY+ya-ylow)*dimX+xa]) / ((yup+ylow)*cellSizeY);
        na[2] = (data[((za+zup)*dimY+ya)*dimX+xa] -
            data[((za-zlow)*dimY+ya)*dimX+xa]) / ((zup+zlow)*cellSizeZ);

        xup  = (xe >= dimX - 1) ? 0 : 1;
        yup  = (ye >= dimY - 1) ? 0 : 1;
        zup  = (ze >= dimZ - 1) ? 0 : 1;
        xlow = (xe <= 0 )       ? 0 : 1;
        ylow = (ye <= 0 )       ? 0 : 1;
        zlow = (ze <= 0 )       ? 0 : 1;

        ne[0] = (data[(ze*dimY+ye)*dimX+xe+xup] -
            data[(ze*dimY+ye)*dimX+xe-xlow]) / ((xup+xlow)*cellSizeX);
        ne[1] = (data[(ze*dimY+ye+yup)*dimX+xe] -
            data[(ze*dimY+ye-ylow)*dimX+xe]) / ((yup+ylow)*cellSizeY);
        ne[2] = (data[((ze+zup)*dimY+ye)*dimX+xe] -
            data[((ze-zlow)*dimY+ye)*dimX+xe]) / ((zup+zlow)*cellSizeZ);

        scale = (threshold - leftval) / (rightval - leftval);
        l = -1;
        if (scale <= paramCC) l=la;
        if (scale >  1.-paramCC) l=le;
        vm = va + scale*(ve-va);
        normal =  - na - scale*(ne-na);

        return vm;
    }


    ////////////////////////////////////////////////////////////////////////////////
    inline McVec3f computeIntersectionUnifInt(
        int zpos, int ypos, int xpos, int edge, McVec3f& normal, size_t& l)
    {
        int* data = (int*) dataPtr;
        int leftval, rightval;
        int xa, ya, za, xe, ye, ze;
        size_t le;
        float scale = 0.0;
        McVec3f va, ve, vm, na, ne;
        char xup,xlow,yup,ylow,zup,zlow;

        xa = xpos + edge_ends[edge*6];
        ya = ypos + edge_ends[edge*6+1];
        za = zpos + edge_ends[edge*6+2];
        va = origin + McVec3f(xa*cellSizeX, ya*cellSizeY, za*cellSizeZ);
        l  = (za*dimY+ya)*dimX+xa;
        leftval = data[l];

        xe = xpos + edge_ends[edge*6+3];
        ye = ypos + edge_ends[edge*6+4];
        ze = zpos + edge_ends[edge*6+5];
        ve = origin + McVec3f(xe*cellSizeX, ye*cellSizeY, ze*cellSizeZ);
        le = (ze*dimY+ye)*dimX+xe;
        rightval = data[le];

        xup  = (xa >= dimX - 1) ? 0 : 1;
        yup  = (ya >= dimY - 1) ? 0 : 1;
        zup  = (za >= dimZ - 1) ? 0 : 1;
        xlow = (xa <= 0 )       ? 0 : 1;
        ylow = (ya <= 0 )       ? 0 : 1;
        zlow = (za <= 0 )       ? 0 : 1;

        na[0] = (data[(za*dimY+ya)*dimX+xa+xup] -
            data[(za*dimY+ya)*dimX+xa-xlow]) / ((xup+xlow)*cellSizeX);
        na[1] = (data[(za*dimY+ya+yup)*dimX+xa] -
            data[(za*dimY+ya-ylow)*dimX+xa]) / ((yup+ylow)*cellSizeY);
        na[2] = (data[((za+zup)*dimY+ya)*dimX+xa] -
            data[((za-zlow)*dimY+ya)*dimX+xa]) / ((zup+zlow)*cellSizeZ);

        xup  = (xe >= dimX - 1) ? 0 : 1;
        yup  = (ye >= dimY - 1) ? 0 : 1;
        zup  = (ze >= dimZ - 1) ? 0 : 1;
        xlow = (xe <= 0 )       ? 0 : 1;
        ylow = (ye <= 0 )       ? 0 : 1;
        zlow = (ze <= 0 )       ? 0 : 1;

        ne[0] = (data[(ze*dimY+ye)*dimX+xe+xup] -
            data[(ze*dimY+ye)*dimX+xe-xlow]) / ((xup+xlow)*cellSizeX);
        ne[1] = (data[(ze*dimY+ye+yup)*dimX+xe] -
            data[(ze*dimY+ye-ylow)*dimX+xe]) / ((yup+ylow)*cellSizeY);
        ne[2] = (data[((ze+zup)*dimY+ye)*dimX+xe] -
            data[((ze-zlow)*dimY+ye)*dimX+xe]) / ((zup+zlow)*cellSizeZ);

        scale = (threshold - leftval) / (rightval - leftval);
        if (scale > 0.5) l=le;
        vm = va + scale*(ve-va);
        normal =  - na - scale*(ne-na);

        return vm;
    }


    ////////////////////////////////////////////////////////////////////////////////
    inline McVec3f computeIntersectionUnifFloat(
        int zpos, int ypos, int xpos, int edge, McVec3f& normal, size_t& l)
    {
        float* data = (float*) dataPtr;
        int xa, ya, za, xe, ye, ze;
        size_t le;
        McVec3f va, ve, vm, na, ne;
        char xup,xlow,yup,ylow,zup,zlow;

        xa = xpos + edge_ends[edge*6];
        ya = ypos + edge_ends[edge*6+1];
        za = zpos + edge_ends[edge*6+2];
        va = origin + McVec3f(xa*cellSizeX, ya*cellSizeY, za*cellSizeZ);
        l  = (za*dimY+ya)*dimX+xa;
        float leftval = data[l];

        xe = xpos + edge_ends[edge*6+3];
        ye = ypos + edge_ends[edge*6+4];
        ze = zpos + edge_ends[edge*6+5];
        ve = origin + McVec3f(xe*cellSizeX, ye*cellSizeY, ze*cellSizeZ);
        le = (ze*dimY+ye)*dimX+xe;
        float rightval = data[le];

        xup  = (xa >= dimX - 1) ? 0 : 1;
        yup  = (ya >= dimY - 1) ? 0 : 1;
        zup  = (za >= dimZ - 1) ? 0 : 1;
        xlow = (xa <= 0 )       ? 0 : 1;
        ylow = (ya <= 0 )       ? 0 : 1;
        zlow = (za <= 0 )       ? 0 : 1;

        na[0] = (data[(za*dimY+ya)*dimX+xa+xup] -
            data[(za*dimY+ya)*dimX+xa-xlow]) / ((xup+xlow)*cellSizeX);
        na[1] = (data[(za*dimY+ya+yup)*dimX+xa] -
            data[(za*dimY+ya-ylow)*dimX+xa]) / ((yup+ylow)*cellSizeY);
        na[2] = (data[((za+zup)*dimY+ya)*dimX+xa] -
            data[((za-zlow)*dimY+ya)*dimX+xa]) / ((zup+zlow)*cellSizeZ);

        xup  = (xe >= dimX - 1) ? 0 : 1;
        yup  = (ye >= dimY - 1) ? 0 : 1;
        zup  = (ze >= dimZ - 1) ? 0 : 1;
        xlow = (xe <= 0 )       ? 0 : 1;
        ylow = (ye <= 0 )       ? 0 : 1;
        zlow = (ze <= 0 )       ? 0 : 1;

        ne[0] = (data[(ze*dimY+ye)*dimX+xe+xup] -
            data[(ze*dimY+ye)*dimX+xe-xlow]) / ((xup+xlow)*cellSizeX);
        ne[1] = (data[(ze*dimY+ye+yup)*dimX+xe] -
            data[(ze*dimY+ye-ylow)*dimX+xe]) / ((yup+ylow)*cellSizeY);
        ne[2] = (data[((ze+zup)*dimY+ye)*dimX+xe] -
            data[((ze-zlow)*dimY+ye)*dimX+xe]) / ((zup+zlow)*cellSizeZ);

        float scale = (threshold-leftval)/(rightval-leftval);
    #ifdef __sgi
        if (isnanf(scale))
            scale = 0.5;
    #endif
        if (scale>0.5)
            l=le;

        vm = va + scale*(ve-va);
        normal = -na - scale*(ne-na);

        return vm;
    }


    ////////////////////////////////////////////////////////////////////////////////
    inline McVec3f computeIntersectionUnifDbl(
        int zpos, int ypos, int xpos, int edge, McVec3f& normal, size_t& l)
    {
        double* data = (double*) dataPtr;
        int xa, ya, za, xe, ye, ze;
        size_t le;
        McVec3f va, ve, vm, na, ne;
        char xup,xlow,yup,ylow,zup,zlow;

        xa = xpos + edge_ends[edge*6];
        ya = ypos + edge_ends[edge*6+1];
        za = zpos + edge_ends[edge*6+2];
        va = origin + McVec3f(xa*cellSizeX, ya*cellSizeY, za*cellSizeZ);
        l  = (za*dimY+ya)*dimX+xa;
        double leftval = data[l];

        xe = xpos + edge_ends[edge*6+3];
        ye = ypos + edge_ends[edge*6+4];
        ze = zpos + edge_ends[edge*6+5];
        ve = origin + McVec3f(xe*cellSizeX, ye*cellSizeY, ze*cellSizeZ);
        le = (ze*dimY+ye)*dimX+xe;
        double rightval = data[le];

        xup  = (xa >= dimX - 1) ? 0 : 1;
        yup  = (ya >= dimY - 1) ? 0 : 1;
        zup  = (za >= dimZ - 1) ? 0 : 1;
        xlow = (xa <= 0 )       ? 0 : 1;
        ylow = (ya <= 0 )       ? 0 : 1;
        zlow = (za <= 0 )       ? 0 : 1;

        na[0] = (data[(za*dimY+ya)*dimX+xa+xup] -
            data[(za*dimY+ya)*dimX+xa-xlow]) / ((xup+xlow)*cellSizeX);
        na[1] = (data[(za*dimY+ya+yup)*dimX+xa] -
            data[(za*dimY+ya-ylow)*dimX+xa]) / ((yup+ylow)*cellSizeY);
        na[2] = (data[((za+zup)*dimY+ya)*dimX+xa] -
            data[((za-zlow)*dimY+ya)*dimX+xa]) / ((zup+zlow)*cellSizeZ);

        xup  = (xe >= dimX - 1) ? 0 : 1;
        yup  = (ye >= dimY - 1) ? 0 : 1;
        zup  = (ze >= dimZ - 1) ? 0 : 1;
        xlow = (xe <= 0 )       ? 0 : 1;
        ylow = (ye <= 0 )       ? 0 : 1;
        zlow = (ze <= 0 )       ? 0 : 1;

        ne[0] = (data[(ze*dimY+ye)*dimX+xe+xup] -
            data[(ze*dimY+ye)*dimX+xe-xlow]) / ((xup+xlow)*cellSizeX);
        ne[1] = (data[(ze*dimY+ye+yup)*dimX+xe] -
            data[(ze*dimY+ye-ylow)*dimX+xe]) / ((yup+ylow)*cellSizeY);
        ne[2] = (data[((ze+zup)*dimY+ye)*dimX+xe] -
            data[((ze-zlow)*dimY+ye)*dimX+xe]) / ((zup+zlow)*cellSizeZ);

        double scale = (threshold-leftval)/(rightval-leftval);
    #ifdef __sgi
        if (isnanf(scale))
            scale = 0.5;
    #endif
        if (scale>0.5)
            l=le;

        vm = va + scale*(ve-va);
        normal = -na - scale*(ne-na);

        return vm;
    }



    ////////////////////////////////////////////////////////////////////////////////
    inline McVec3f computeIntersectionUnifFloatProcedural(
        int zpos, int ypos, int xpos, int edge, McVec3f& normal, size_t& l)
    {
        int xa, ya, za, xe, ye, ze;
        size_t le;
        McVec3f va, ve, vm, na, ne;
        char xup,xlow,yup,ylow,zup,zlow;

        xa = xpos + edge_ends[edge*6];
        ya = ypos + edge_ends[edge*6+1];
        za = zpos + edge_ends[edge*6+2];
        va = origin + McVec3f(xa*cellSizeX, ya*cellSizeY, za*cellSizeZ);
        l  = (za*dimY+ya)*dimX+xa;
        float leftval = getValueFunc(getValueUserData,xa,ya,za);

        xe = xpos + edge_ends[edge*6+3];
        ye = ypos + edge_ends[edge*6+4];
        ze = zpos + edge_ends[edge*6+5];
        ve = origin + McVec3f(xe*cellSizeX, ye*cellSizeY, ze*cellSizeZ);
        le = (ze*dimY+ye)*dimX+xe;
        float rightval = getValueFunc(getValueUserData,xe,ye,ze);


        xup  = (xa >= dimX - 1) ? 0 : 1;
        yup  = (ya >= dimY - 1) ? 0 : 1;
        zup  = (za >= dimZ - 1) ? 0 : 1;
        xlow = (xa <= 0 )       ? 0 : 1;
        ylow = (ya <= 0 )       ? 0 : 1;
        zlow = (za <= 0 )       ? 0 : 1;

        na[0] = (getValueFunc(getValueUserData,xa+xup,ya,za) -
            getValueFunc(getValueUserData,xa-xlow,ya,za)) / ((xup+xlow)*cellSizeX);
        na[1] = (getValueFunc(getValueUserData,xa,ya+yup,za) -
            getValueFunc(getValueUserData,xa,ya-ylow,za)) / ((yup+ylow)*cellSizeY);
        na[2] = (getValueFunc(getValueUserData,xa,ya,za+zup) -
            getValueFunc(getValueUserData,xa,ya,za-zlow)) / ((zup+zlow)*cellSizeZ);

        xup  = (xe >= dimX - 1) ? 0 : 1;
        yup  = (ye >= dimY - 1) ? 0 : 1;
        zup  = (ze >= dimZ - 1) ? 0 : 1;
        xlow = (xe <= 0 )       ? 0 : 1;
        ylow = (ye <= 0 )       ? 0 : 1;
        zlow = (ze <= 0 )       ? 0 : 1;

        ne[0] = (getValueFunc(getValueUserData,xe+xup,ye,ze) -
            getValueFunc(getValueUserData,xe-xlow,ye,ze)) / ((xup+xlow)*cellSizeX);
        ne[1] = (getValueFunc(getValueUserData,xe,ye+yup,ze) -
            getValueFunc(getValueUserData,xe,ye-ylow,ze)) / ((yup+ylow)*cellSizeY);
        ne[2] = (getValueFunc(getValueUserData,xe,ye,ze+zup) -
            getValueFunc(getValueUserData,xe,ye,ze-zlow)) / ((zup+zlow)*cellSizeZ);

        float scale = (threshold-leftval)/(rightval-leftval);
    #ifdef __sgi
        if (isnanf(scale))
            scale = 0.5;
    #endif
        if (scale>0.5)
            l=le;

        vm = va + scale*(ve-va);
        normal = -na - scale*(ne-na);

        return vm;
    }


    ////////////////////////////////////////////////////////////////////////////////
    //
    //  computeIntersectionUser(..) computes the intersection
    //  by calling a callback function previously passed to
    //  HxIsosurface by some other module where this function
    //  has been implemented.
    //
    inline McVec3f computeIntersectionUser(
        int zpos, int ypos, int xpos, int edge, McVec3f& normal, size_t& l)
    {
    #ifndef NOAMIRA

        int ia, ie;
        int xa, ya, za, xe, ye, ze;
        McVec3f va, ve, vm, na, ne; // vertices and normal vectors

        // These are zero if x/y/z pos are on grid boundary, 1 otherwise
        // int xup, yup, zup, xlow, ylow, zlow;

        // find beginning point of the edge
        xa = xpos + edge_ends[edge*6];
        ya = ypos + edge_ends[edge*6+1];
        za = zpos + edge_ends[edge*6+2];
        ia = (za*dimY+ya)*dimX+xa;

        // find end point of the edge
        xe = xpos + edge_ends[edge*6+3];
        ye = ypos + edge_ends[edge*6+4];
        ze = zpos + edge_ends[edge*6+5];
        ie = (ze*dimY+ye)*dimX+xe;

        // linear interpolation
        float scale = intersectionCallback(ia,ie,intersectionCallbackObject);
        if (scale > 0.5) l = ie;
        else l = ia;

        coord3->pos(xa,ya,za,&va[0]);
        coord3->pos(xe,ye,ze,&ve[0]);
        vm = va + scale*(ve-va);
        normal.setValue(1,0,0);
        return vm;
    #else
        return McVec3f (0,0,0);
    #endif
    }

};



#endif


/// @}
