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
#ifndef VS_QUAD_MESH_H
#define VS_QUAD_MESH_H

#include <mclib/McBox3f.h>
#include <mclib/McVec2i.h>
#include <mclib/McWatch.h>

#include "VsObject.h"
#include "VsData.h"
#include "VsDataAccess.h"
#include "VsThickSliceImpl.h" // VsQuadMesh is an internal class, so it's ok to have this internal header
#include "VsImpl.h"
#include "VsScanConvert.h"

#include "VsMesh.h"    // a very simple abstract base class
#include "VsPolygon.h" // for iterating over the mesh

#include <assert.h>
#include <float.h> // for FLT_MAX
#include <vector>

#if defined(_MSC_VER) && _MSC_VER<1300
#define HX_VC6
#endif

#define USE_INTERPOLATION // TODO: this was a first attempt for implementing trilinear interpolation 
                          //       on curved slice extraction - still not fully implemented and does
                          //       not compile under LINUX. 


// a quad-mesh class consisting of a 2D-Array of vertices

class VsQuadMesh : public VsMesh
{
public:    

    // construct a quadmesh of m x n vertices
    VsQuadMesh(int m, int n, const McVec3f *vertices);
    // self-allocating quadmesh
    VsQuadMesh(int m, int n);
    // copy constructor
    VsQuadMesh(const VsQuadMesh & srcMesh);
    // destructor
    virtual ~VsQuadMesh() {};

    // -- interface inherited from VsMesh --
    virtual int numPolygons() const;
    virtual const VsPolygon* polygon(unsigned int i) const;  
    virtual int numContours() const { return 1; };
    virtual const VsPolygon* contour(unsigned int idx) const;
    virtual VSRESULT boundingBox( McBox3f & outBox ) const;
    // -- end of interface inherited from VsMesh --

    // initialize the mesh based on a list of m x n vertices
    void init(int m, int n, const McVec3f *vertices);

    /// initialize texture coordinates based on the provided array of m x n coordinate vectors
    void initTexCoords(int m, int n, const McVec2f *texCoords);
    /** initialize texture coordinates such that each patch of the quadmesh gets an 
        equal share of the texture space */
    void initTexCoords(McVec2f scale, int sizex = 0, int sizey = 0);
    /** initialize texture coordinates such that equal distances in the mesh receive
        the same amount of texture space. Texture coordinates are assigned with
        voxel centers at vertex positions.
        
        The method returns the number of voxels that are reqired in each dimension,
        to minimally capture all patches.
    */
    McVec2i initTexCoords(float voxelSpacing);

    /// transform the complete mesh by the specified matrix
    void transform(McMat4f & matrix);

    // access vertex array
    const McVec3f* vertices() const {
        return &(m_Vertices[0]);
    }

    // access array of texture coordinates
    const McVec2f* texCoords() const {   
        assert(m_TexCoords.size() > 0);
        return &(m_TexCoords[0]);
    }

    // get the vertex at location i,j in the mesh
    McVec3f& vertex(unsigned int i, unsigned int j) {
        assert(i < m_);
        assert(j < n_);
        return m_Vertices[m_ * j + i];
    }

    const McVec3f& vertex(unsigned int i, unsigned int j) const {
        assert(i < m_);
        assert(j < n_);
        return m_Vertices[m_ * j + i];
    }

    // get the texture coordinate corresponding to the vertex at location i,j in the mesh    
    McVec2f& texCoord(unsigned int i, unsigned int j) {
        assert(i < m_);
        assert(j < n_);
        assert(m_TexCoords.size() == m_ * n_);
        return m_TexCoords[m_ * j + i];
    }

    const McVec2f& texCoord(unsigned int i, unsigned int j) const {
        assert(i < m_);
        assert(j < n_);
        assert(m_TexCoords.size() == m_ * n_);
        return m_TexCoords[m_ * j + i];
    }

    McVec3f vertexNormal(unsigned int i, unsigned int j) const {

        McVec3f n(0.0f, 0.0f, 0.0f);

        assert(i < m_);
        assert(j < n_);

        //if ((i > 0) && (j > 0) && (i < m_-1) && (j < n_-1)) {
        McVec3f c = vertex(i,j); // center of the fan we have to process

        // now sum up the normal n

        // first triangle in first quadrant, .i.e. north-east-east triangle
        if ((i+1 < m_) && (j < n_) && (i < m_-1) && (j < n_-1))
            n += (vertex(i+1,j) - c).cross(centerVertex(i,j) - c);

        // north-north-east
        if ((i < m_-1) && (j < n_-1) && (j+1 < n_))
            n += (centerVertex(i,j) - c).cross(vertex(i,j+1) - c);

        // 2nd quadrant
        if ((j+1 < n_) && (i-1 >= 0) && (i-1 < m_-1) && (j < n_-1))
            n += (vertex(i,j+1) - c).cross(centerVertex(i-1,j) - c);

        if ((i-1 >= 0) && (i-1 < m_ - 1) && (j < n_ - 1))
            n += (centerVertex(i-1,j) - c).cross(vertex(i-1,j) - c);

        // 3rd quadrant
        if ((i-1 >= 0) && (j-1 >= 0) && (i-1 < m_-1) && (j-1 < n_-1))
            n += (vertex(i-1,j) - c).cross(centerVertex(i-1,j-1) - c);

        if ((i-1 >= 0) && (j-1 >= 0) && (i-1 < m_-1) && (j-1 < n_-1))
            n += (centerVertex(i-1,j-1) - c).cross(vertex(i,j-1) - c);

        // 4th quadrant
        if ((j-1 >= 0) && (i < m_-1) && (j-1 < n_-1))    
            n += (vertex(i,j-1) - c).cross(centerVertex(i,j-1) - c);

        if ((i < m_-1) && (j-1 >= 0) && (j-1 < n_-1) && (i+1 < m_))
            n += (centerVertex(i,j-1) - c).cross(vertex(i+1,j) - c);

        n.normalize();
        return n;
        
    }


    McVec3f centerNormal(unsigned int i, unsigned int j) const
    {    
        assert(i < m_-1);
        assert(j < n_-1);
        
        McVec3f n(0.0f, 0.0f, 0.0f);

        McVec3f c = centerVertex(i,j);
        
        McVec3f v0,v1,v2,v3;
        v0 = vertex(i+1,j);
        v1 = vertex(i+1,j+1);
        v2 = vertex(i,j+1);
        v3 = vertex(i,j);

        n += (v0-c).cross(v1-c);
        n += (v1-c).cross(v2-c);
        n += (v2-c).cross(v3-c);
        n += (v3-c).cross(v0-c);

        n.normalize();

        return n;            
    }   

    // Get the center vertex (i.e. the midpoint) of quad (i,j).
    // Note that there are m_ x n_ vertices but (n_-1) x (m_ - 1) quads.
    McVec3f& centerVertex(unsigned int i, unsigned int j) {
        return m_CenterVertices[(m_-1) * j + i];
    }

    const McVec3f& centerVertex(unsigned int i, unsigned int j) const {
        return m_CenterVertices[(m_-1) * j + i];
    }

    // Get the texture coord. of the center vertex (i.e. the midpoint) of quad (i,j).
    // Note that there are m_ x n_ vertices but (n_-1) x (m_ - 1) quads.
    McVec2f& centerTexCoord(unsigned int i, unsigned int j) {
        return m_CenterTexCoords[(m_-1) * j + i];
    }
  
    const McVec2f& centerTexCoord(unsigned int i, unsigned int j) const {
        return m_CenterTexCoords[(m_-1) * j + i];
    }

    // return the dimensions of the quad-mesh, i.e. the number of vertices in x- and y-direction
    // of the 2D-array of vertices
    McVec2i  dimensions() const { return McVec2i(m_, n_); };

    // Comparism
    friend int operator != (const VsQuadMesh& a, const VsQuadMesh& b) { return !(a==b); }
    friend int operator == (const VsQuadMesh& a, const VsQuadMesh& b)
    {
        int aNumVertices = a.dimensions()[0] * a.dimensions()[1];
        int bNumVertices = b.dimensions()[0] * b.dimensions()[1];

        if (&a == &b)
            return 1;
        if (aNumVertices != bNumVertices)
            return 0;

        // This is a somehow ad-hoc test. We only compare vertex positions!
        for (int j = 0; j < aNumVertices; j++) {
            McVec3f aCoord = a.vertices()[j];
            McVec3f bCoord = b.vertices()[j];
#if 0
            fprintf(stderr, "VsQuadMesh==: %f %f %f == %f %f %f\n",
                    aCoord[0], aCoord[1], aCoord[2],
                    bCoord[0], bCoord[1], bCoord[2]);
#endif
            if (aCoord != bCoord)
                return 0;
        }
        
        return 1;
    };



    // extract the texture data out of data
    // returns true for success, else false
    template <class F>
    static bool extractSliceFrustum(class VsQuadMesh * mesh, const VsDataAccess &sliceAccess, VsData &data, VsData * label, float thickness, int thickStride, int interpolate, F * functor, VsObject & object);

#ifdef HX_VC6
    bool extractSliceFrustum8MIP  (const VsDataAccess &sliceAccess, VsData &data, VsData * label, float thickness, int thickStride, int interpolate, MIPFunctor<unsigned char> *   functor, VsObject & object)
    { return extractSliceFrustum(this, sliceAccess, data, label, thickness, thickStride, functor, object); }
    bool extractSliceFrustum8MINIP(const VsDataAccess &sliceAccess, VsData &data, VsData * label, float thickness, int thickStride, int interpolate, MINIPFunctor<unsigned char> * functor, VsObject & object)
    { return extractSliceFrustum(this, sliceAccess, data, label, thickness, thickStride, functor, object); }
    bool extractSliceFrustum8AVG  (const VsDataAccess &sliceAccess, VsData &data, VsData * label, float thickness, int thickStride, int interpolate, AVGFunctor<unsigned char> *   functor, VsObject & object)
    { return extractSliceFrustum(this, sliceAccess, data, label, thickness, thickStride, functor, object); }

    bool extractSliceFrustum16MIP  (const VsDataAccess &sliceAccess, VsData &data, VsData * label, float thickness, int thickStride, int interpolate, MIPFunctor<short> *   functor, VsObject & object)
    { return extractSliceFrustum(this, sliceAccess, data, label, thickness, thickStride, functor, object); }
    bool extractSliceFrustum16MINIP(const VsDataAccess &sliceAccess, VsData &data, VsData * label, float thickness, int thickStride, int interpolate, MINIPFunctor<short> * functor, VsObject & object)
    { return extractSliceFrustum(this, sliceAccess, data, label, thickness, thickStride, functor, object); }
    bool extractSliceFrustum16AVG  (const VsDataAccess &sliceAccess, VsData &data, VsData * label, float thickness, int thickStride, int interpolate, AVGFunctor<short> *   functor, VsObject & object)
    { return extractSliceFrustum(this, sliceAccess, data, label, thickness, thickStride, functor, object); }

    bool extractSliceFrustumU16MIP  (const VsDataAccess &sliceAccess, VsData &data, VsData * label, float thickness, int thickStride, int interpolate, MIPFunctor<unsigned short> *   functor, VsObject & object)
    { return extractSliceFrustum(this, sliceAccess, data, label, thickness, thickStride, functor, object); }
    bool extractSliceFrustumU16MINIP(const VsDataAccess &sliceAccess, VsData &data, VsData * label, float thickness, int thickStride, int interpolate, MINIPFunctor<unsigned short> * functor, VsObject & object)
    { return extractSliceFrustum(this, sliceAccess, data, label, thickness, thickStride, functor, object); }
    bool extractSliceFrustumU16AVG  (const VsDataAccess &sliceAccess, VsData &data, VsData * label, float thickness, int thickStride, int interpolate, AVGFunctor<unsigned short> *   functor, VsObject & object)
    { return extractSliceFrustum(this, sliceAccess, data, label, thickness, thickStride, functor, object); }
#endif

    // just for debugging
    void initSin(const McBox3f &box);

private:
    // Internal update methods
    void computeVertexCenters();
    void computeTextureCenters();

private:

    // number of vertices
    unsigned int m_;
    unsigned int n_;

    std::vector<McVec3f> m_Vertices;           
    std::vector<McVec2f> m_TexCoords;    

    // center vertices of each quad
    std::vector<McVec3f> m_CenterVertices;   
    std::vector<McVec2f> m_CenterTexCoords;    

     // a helper polygon during iteration over the mesh
    VsGenericPolygon m_IteratorPolygon;
};




// 3D-rasterize a triangle using the volume-access "access" and write the result into the 2D-array "rawData".
// The 2D coordinates within the 2-dimensional rawData (i.e. texture "atlas") are indexOrigin, indexPos1, and indexPos2.
// The corresponding 3D coordinates in the volume are origin, pos1, and pos2.
// At the moment the method assumes that the 2D line from indexOrigin to indexPos1 (in the 2D-array) is horizontal or vertical
// (which is not the case for "general" triangles).
 
/*   template <typename T>
        void rasterTriangularFrustum(const VsDataAccess * rawData, const VsDataAccess *access, McBox3f bbox, McVec2f indexOrigin, McVec2f indexPos1, McVec2f indexPos2, McVec3f origin, McVec3f pos1, McVec3f pos2, float thickness);   
*/

// Note that -- in case of thick slices -- the volume that is sampled is not a right triangular prism but a triangular frustum.
// The suffixes B and F are used for the *F*ront and *B*ack triangle (i.e. top or bottom face) of the triangluar frustum that is sampled.
namespace {
    template <class Sampler>
    void rasterTriangularFrustum(const VsDataAccess * rawData, const VsDataAccess *access, McBox3f bbox,
                             McVec2f indexOrigin,          McVec2f indexPos1,  McVec2f indexPos2, 
                             McVec3f origin,               McVec3f pos1,       McVec3f pos2, 
                             McVec3f normalOrigin,         McVec3f normalPos1, McVec3f normalPos2, 
                             //McVec3f originF,            McVec3f pos1F,       McVec3f pos2F, 
                             float thickness,              int thickStride,    Sampler * sampler)
{
     assert(access != NULL);
     assert(rawData != NULL);

     bool interpolate = false;

     // ----- 1. determine how many samples we need -----
     int dims[3];
     access->dims().toInt(dims);
     McVec3f voxelSize = bbox.getVoxelSize(dims);
     McVec3f edge1(voxelSize[0], 0, 0);
     McVec3f edge2(0, voxelSize[1], 0);
     McVec3f edge3(0, 0, voxelSize[2]);

     // take the average normal vector of the triangle to guess the number of samples
     McVec3f N = (1.0f/3.0f) * (normalOrigin + normalPos1 + normalPos2);
     N.normalize(); // this shouldn't be necessary

     // now determine the number of samples used for a thick slice
     // first project the voxel's edge vectors onto N
     // and select the maximal length to scale the normalized N;
     McVec3f proj1 = edge1 * (N.dot(McVec3f(1,0,0))); 
     McVec3f proj2 = edge2 * (N.dot(McVec3f(0,1,0))); 
     McVec3f proj3 = edge3 * (N.dot(McVec3f(0,0,1))); 

    float maxProj = VS_MAX(VS_MAX(proj1.length(), proj2.length()), proj3.length());
    int numOrthoSamples = 0;
    if (thickness > 0) {
        numOrthoSamples = McRoundEven(thickness / maxProj);
    } else {
        numOrthoSamples = 1;
    }
#ifndef NDEBUG
    // std::cerr << "numOrthoSamples = " << numOrthoSamples << std::endl;
#endif



     // ----- 2. determine the front and back triangle -----

    McVec3f originF, originB;
    McVec3f pos1F, pos1B;
    McVec3f pos2F, pos2B;
    
    // assert normalOrigin.length() == 1
    originF = origin + 0.5f * normalOrigin * thickness;
    originB = origin - 0.5f * normalOrigin * thickness;

    // assert normalPos1.length() == 1
    pos1F = pos1 + 0.5f * normalPos1 * thickness;
    pos1B = pos1 - 0.5f * normalPos1 * thickness;

    // assert normalPos2.length() == 1
    pos2F = pos2 + 0.5f * normalPos2 * thickness;
    pos2B = pos2 - 0.5f * normalPos2 * thickness;



    // ----- now raster the thick trianglular frustum -----
    
    // get the bounding box of the volume data
    // needed for sampling to determine the indices
    McVec3f bbmin, bbmax;      
    bbox.getBounds(bbmin, bbmax);

    // only tested for ONE variable
    assert(access->nDataVar() == 1);

    float scalex = (access->dims()[0] - 1) / (bbmax.x - bbmin.x);
    float scaley = (access->dims()[1] - 1) / (bbmax.y - bbmin.y);
    float scalez = (access->dims()[2] - 1) / (bbmax.z - bbmin.z);


    // -------------------------------------------------------------------------
    // horizontal mode - scanlines go anlong x-axis
    if ((int)indexOrigin.y == (int)indexPos1.y) 
    {  
        float startLineF = indexOrigin.y; // VS_CLAMP(indexOrigin.y, 0.5f, rawData->dims()[1] - 1.5f);
        float endLineF   = indexPos2.y;   // VS_CLAMP(indexPos2.y,   0.5f, rawData->dims()[1] - 1.5f);

        int startLine = (int) (startLineF - 0.5f);
        int endLine   = (int) (endLineF - 0.5f);
        int lineInc   = indexPos2.y < indexOrigin.y ? -1 : 1; 

        assert(startLine >= 0);
        assert(startLine < rawData->dims()[1]);
        assert(endLine >= 0);
        assert(endLine < rawData->dims()[1]);

        assert((indexPos2.y - indexOrigin.y) != 0);

        // inverse slope of the line (origin, pos2)  (in the 2D plane of the triangle)
        float m_inv_orig_pos2 = (float)(indexPos2.x - indexOrigin.x) / (float)(indexPos2.y - indexOrigin.y) ;     
        float m_inv_pos1_pos2 = (float)(indexPos2.x - indexPos1.x) / (float)(indexPos2.y - indexPos1.y) ; 

        float lineF = startLineF;

        for (int line = (int)startLine; line != (int)(endLine + lineInc); line += lineInc, lineF += lineInc)
        {
            float startRowF = indexOrigin.x + m_inv_orig_pos2 * (lineF-indexOrigin.y); // VS_CLAMP(indexOrigin.x + m_inv_orig_pos2 * (lineF-indexOrigin.y), 0.5f, rawData->dims()[0]-1.5f);
            float endRowF   = indexPos1.x + m_inv_pos1_pos2 * (lineF-indexOrigin.y);   // VS_CLAMP(indexPos1.x + m_inv_pos1_pos2 * (lineF-indexOrigin.y),   0.5f, rawData->dims()[0]-1.5f);
        
            int startRow = (int)(startRowF - 0.5f);
            int endRow   = (int)(endRowF - 0.5f);
            int rowInc   = (endRow < startRow) ? -1 : 1;

            assert(startRow >= 0);
            assert(startRow < rawData->dims()[0]);
            assert(endRow >= 0);
            assert(endRow < rawData->dims()[0]);

            // float lineWeight = (lineF - indexOrigin.y) / (endLineF - startLineF);

            McVec3f samplePos;
            McVec3f basePosB, basePosF, basePos;
            
            float A, A0, A1, A2; // barycentric coords of row,line in 2D               
            float x1,y1,x2,y2,x3,y3;    
            // p0,p1,p2                
            x1 = indexOrigin.x; y1 = indexOrigin.y;
            x2 = indexPos1.x; y2 = indexPos1.y;
            x3 = indexPos2.x; y3 = indexPos2.y;            
            A = 0.5f * (-x2 * y1 + x3 * y1 + x1 * y2 - x3 * y2 - x1 * y3 + x2 * y3);

            float rowF = startRowF;

            for (int  row = (int)startRow; (rowInc > 0) ? (row <= endRow) : (row >= endRow); row += rowInc, rowF += rowInc) // FIRST AND LAST INDEX ARE VISITED
            { 
                // c,p1,p2
                x1 = rowF; y1 = lineF;
                x2 = indexPos1.x; y2 = indexPos1.y;
                x3 = indexPos2.x; y3 = indexPos2.y;            
                A0 = 0.5f * (-x2 * y1 + x3 * y1 + x1 * y2 - x3 * y2 - x1 * y3 + x2 * y3) / A;

                // p0, c, p2
                x1 = indexOrigin.x; y1 = indexOrigin.y;
                x2 = rowF; y2 = lineF;
                x3 = indexPos2.x; y3 = indexPos2.y;            
                A1 = 0.5f * (-x2 * y1 + x3 * y1 + x1 * y2 - x3 * y2 - x1 * y3 + x2 * y3) / A;

                // third component
                A2 = 1.0f - A0 - A1;

                basePosB = originB * A0 + pos1B * A1 + pos2B * A2;
                basePosF = originF * A0 + pos1F * A1 + pos2F * A2;
                
                // e3 is the replacement for N
                McVec3f e3 = (basePosF - basePosB) / (float)numOrthoSamples;

                int count = 0;
                int index = line * rawData->dims()[0] + row;

                //for (int thickPos = -numOrthoSamples/2; thickPos < numOrthoSamples/2 + 1; thickPos++) {
                for (int thickPos = 0; thickPos < numOrthoSamples; thickPos += thickStride)
                {
                    samplePos = basePosB + (float)thickPos * e3; //projNormal;

                    // this is too slow         
                    // data.sample(samplePos, result);

                    // *** begin of sampling               
                    
                    // TODO: support for more than one data variables
                    //for (unsigned int idx = 0; idx < dataVar; ++idx)
                    //    result[idx] = 0.0f;

                    float i = ( (samplePos.x - bbmin.x) * scalex );
                    float j = ( (samplePos.y - bbmin.y) * scaley );
                    float k = ( (samplePos.z - bbmin.z) * scalez );

                    // check that cursor is within bounding box and indices point to valid data
                    if ((i<0) || (i > access->dims()[0] - 1) ||
                        (j<0) || (j > access->dims()[1] - 1) ||
                        (k<0) || (k > access->dims()[2] - 1) ) {
                        continue;  // go to next row          
                    }

                    // fetch the data point and combine it with all previously collected
                    // no locking is necessary here -- the VsDataAccess is already locked
                    if (!interpolate)
                    {
                        if (thickPos)
                            (*sampler)(McRoundEven(i), McRoundEven(j), McRoundEven(k), index);
                        else
                            sampler->init(McRoundEven(i), McRoundEven(j), McRoundEven(k), index);
                    
                    } // end (if !interpolate)
#ifdef USE_INTERPOLATION
                    else 
                    {
                        if (thickPos)
                            (*sampler)(McTruncZero(i), McTruncZero(j), McTruncZero(k), index);
                        else
                            sampler->init(McTruncZero(i), McTruncZero(j), McTruncZero(k), index, 0);
                    }
#endif

                    count++;

                } // end (for thickpos...)

                // finalize the respective value, this could mean e.g. divide the sum of all values by 
                // the number of samples (averaging) or any other operation necessary
                
                if (count)
                    sampler->finalize(count, index); 
            
            } // *** end (for row...)

        } // *** end (for line ...)
    }


    // -------------------------------------------------------------------------
    // vertical mode
    if ((int)indexOrigin.x == (int)indexPos1.x)
    {
        float startLineF = indexOrigin.x; // VS_CLAMP(indexOrigin.x, 0.5f, rawData->dims()[0] - 1.5f);
        float endLineF   = indexPos2.x;   // VS_CLAMP(indexPos2.x,   0.5f, rawData->dims()[0] - 1.5f);

        int startLine = (int) (startLineF - 0.5f);
        int endLine   = (int) (endLineF   - 0.5f);
        int lineInc   = indexPos2.x < indexOrigin.x ? -1 : 1;

        assert(startLine >= 0);
        assert(startLine < rawData->dims()[0]);
        assert(endLine >= 0);
        assert(endLine < rawData->dims()[0]);

        assert((indexPos2.x - indexOrigin.x) != 0); // number of lines != 0

        // inverse slope of the line (origin, pos2)  (in the 2D plane of the triangle)    
        float m_inv_orig_pos2 = (float)(indexPos2.y - indexOrigin.y) / (float)(indexPos2.x - indexOrigin.x) ; 
        float m_inv_pos1_pos2 = (float)(indexPos1.y - indexPos2.y) / (float)(indexPos2.x - indexPos1.x) ; 

        float lineF = startLineF;

        for (int line = (int)startLine; line != (int)(endLine+lineInc); line += lineInc, lineF += lineInc) // lines go along x-axis!! // FIRST AND LAST INDEX ARE VISITED
        {
            float startRowF = (indexOrigin.y + m_inv_orig_pos2 * (lineF-indexOrigin.x)); // VS_CLAMP((indexOrigin.y + m_inv_orig_pos2 * (lineF-indexOrigin.x)), 0.5f, rawData->dims()[1]-1.5f);  // rows go along y-axis!
            float endRowF   = (indexPos1.y - m_inv_pos1_pos2 * (lineF-indexOrigin.x));   // VS_CLAMP((indexPos1.y - m_inv_pos1_pos2 * (lineF-indexOrigin.x)),   0.5f, rawData->dims()[1]-1.5f);

            int startRow = (int) (startRowF - 0.5f);
            int endRow   = (int) (endRowF - 0.5f);
            int rowInc   = (endRow < startRow) ? -1 : 1;

            //startRow = VS_CLAMP(startRow, 0, rawData->dims()[1]);
            //endRow   = VS_CLAMP(endRow, 0, rawData->dims()[1]);

            assert(startRow >= 0);
            assert(startRow < rawData->dims()[1]);
            assert(endRow >= 0);
            assert(endRow < rawData->dims()[1]);

            float lineWeight = (lineF - startLineF) / (endLineF - startLineF);
            McVec3f leftVertex  = origin * (1 - lineWeight) + pos2 * lineWeight;
            McVec3f rightVertex = pos1   * (1 - lineWeight) + pos2 * lineWeight;

            McVec3f samplePos;
            McVec3f basePosB, basePosF, basePos;

            float A, A0, A1, A2; // barycentric coords of row,line in 2D               
            float x1,y1,x2,y2,x3,y3;    
            // p0,p1,p2                
            x1 = indexOrigin.y; y1 = indexOrigin.x;
            x2 = indexPos1.y; y2 = indexPos1.x;
            x3 = indexPos2.y; y3 = indexPos2.x;            
            A = 0.5f * (-x2 * y1 + x3 * y1 + x1 * y2 - x3 * y2 - x1 * y3 + x2 * y3);

            float rowF = startRowF;

            for (int  row = startRow; row != endRow + rowInc; row += rowInc, rowF += rowInc) 
            {
                // float rowWeight = (rowF - startRowF) / (endRowF - startRowF);

                // McVec3f ppp = leftVertex * (1-rowWeight) + rightVertex * rowWeight;

                // c,p1,p2
                x1 = rowF; y1 = lineF;
                x2 = indexPos1.y; y2 = indexPos1.x;
                x3 = indexPos2.y; y3 = indexPos2.x;            
                A0 = 0.5f * (-x2 * y1 + x3 * y1 + x1 * y2 - x3 * y2 - x1 * y3 + x2 * y3) / A;

                // p0, c, p2
                x1 = indexOrigin.y; y1 = indexOrigin.x;
                x2 = rowF; y2 = lineF;
                x3 = indexPos2.y; y3 = indexPos2.x;            
                A1 = 0.5f * (-x2 * y1 + x3 * y1 + x1 * y2 - x3 * y2 - x1 * y3 + x2 * y3) / A;

                // third component
                A2 = 1.0f - A0 - A1;                
                                
                basePosB = originB * A0 + pos1B * A1 + pos2B * A2;                                
                basePosF = originF * A0 + pos1F * A1 + pos2F * A2;
                
                // e3 is the replacement for N
                McVec3f e3 = (basePosF - basePosB) / (float)numOrthoSamples;

                int count = 0;
                int index = row * rawData->dims()[0] + line;

                //for (int thickPos = -numOrthoSamples/2; thickPos < numOrthoSamples/2 + 1; thickPos++) {
                for (int thickPos = 0; thickPos < numOrthoSamples; thickPos += thickStride)
                {
                    samplePos =  basePosB + (float)thickPos * e3; //projNormal;  

                    //too slow:
                    //data.sample(samplePos, &f);                

                    // *** begin of sampling               

                    // TODO: support for more than one data variables
                    //for (unsigned int idx = 0; idx < dataVar; ++idx)
                    //    result[idx] = 0.0f;

                    float i = ( (samplePos.x - bbmin.x) * scalex );
                    float j = ( (samplePos.y - bbmin.y) * scaley );
                    float k = ( (samplePos.z - bbmin.z) * scalez );

                    // check that cursor is within bounding box and indices point to valid data
                    if ((i<0) || (i > access->dims()[0] - 1) ||
                        (j<0) || (j > access->dims()[1] - 1) ||
                        (k<0) || (k > access->dims()[2] - 1) ) {
                        continue;  // go to next row          
                    }

                    //  fetch the data point and combine it with all previously collected
                    // no locking -- the VsDataAccess is already locked here
                    if (!interpolate)
                    {
                        if (thickPos)
                            (*sampler)(McRoundEven(i), McRoundEven(j), McRoundEven(k), index);
                        else
                            sampler->init(McTruncZero(i), McTruncZero(j), McTruncZero(k), index);
//                            sampler->init(McRoundEven(i), McRoundEven(j), McRoundEven(k), index);

                    } // end (if !interpolate...)
#ifdef USE_INTERPOLATION
                    else
                    {
                        if (0) // thickPos)
                            (*sampler)(McTruncZero(i), McTruncZero(j), McTruncZero(k), index);
                        else
                            sampler->init(McTruncZero(i), McTruncZero(j), McTruncZero(k), index, 0);
                    }
#endif

                    count++;

                } // *** end (for thickpos...)

                // finalize the respective value, this could mean e.g. divide the sum of all values by 
                // the number of samples (averaging) or any other operation necessary
                
                if (count)
                    sampler->finalize(count, index); 

            } // *** end (for row...)

        } // *** end (for line...)
    }
}


template <class Sampler> 
class UserData {
public:
    UserData() {};
    const VsDataAccess * sliceAccess;
    const VsDataAccess * volumeAccess;
    Sampler *            sampler;
    McBox3f              bbox;
    float                scalex;
    float                scaley;
    float                scalez;
    int                  numSamples;
    int                  thickStride;
    bool                 interpolate;
};


template <class Sampler>
class Dummy {

public:
    static void pixelCB(int x, int y, float* data, void* ptr)
    {
        UserData<Sampler> * userData = (UserData<Sampler>*)(ptr);

#ifdef USE_INTERPOLATION
        //!! TODO: Interpolation not yet fully implemented
        //!!       In particular if activated here, also label would be implemented.
        bool interpolate = userData->interpolate;
#else
        bool interpolate = false; // true;
#endif

        int row  = (int)(x - 0.5f);
        int line = (int)(y - 0.5f);
        int index = line * userData->sliceAccess->dims()[0] + row;

        McVec3f bbmin, bbmax;
        userData->bbox.getBounds(bbmin, bbmax);

        McVec3f basePosB(data[0], data[1], data[2]);
        McVec3f basePosF(data[3], data[4], data[5]);
        McVec3f samplePos = basePosB;

        McVec3f e3 = (basePosF - basePosB) / (float)userData->numSamples;

        int count = 0;

        // Sample along the connecting line between front and back triangle
        for (int thickPos = 0; thickPos < userData->numSamples; thickPos += userData->thickStride)
        {
            float iF = ( (samplePos.x - bbmin.x) * userData->scalex );
            float jF = ( (samplePos.y - bbmin.y) * userData->scaley );
            float kF = ( (samplePos.z - bbmin.z) * userData->scalez );

            int i = McRoundEven(iF);
            int j = McRoundEven(jF);
            int k = McRoundEven(kF);

            if (   i < 0 || i >= userData->volumeAccess->dims()[0]
                || j < 0 || j >= userData->volumeAccess->dims()[1]
                || k < 0 || k >= userData->volumeAccess->dims()[2])
                continue;

            if (!interpolate) 
            {
                if (thickPos)
                    (*(userData->sampler))(i, j, k, index);
                else
                    userData->sampler->init(i, j, k, index);
            }
    #ifdef USE_INTERPOLATION
            else // end (if !interpolate)
            {
                if (iF < 0 || jF < 0 || kF < 0)
                    continue;

                if (thickPos)
                    (*(userData->sampler))(iF, jF, kF, index, 0);
                else
                    userData->sampler->init(iF, jF, kF, index, 0);
            }
    #endif

            samplePos += userData->thickStride * e3;
            count++;
    
        } // end (for thickPos ... )

        userData->sampler->finalize(count, index); 
    }
};


/** 3D-scan convert of a triangle.
    Values are extracted from volume-access \c access and are written into the
    2D-array \c rawData.

    The 2D coordinates within the 2-dimensional rawData (i.e. texture "atlas") 
    are \c indexOrigin, \c indexPos1, and \c indexPos2.
    
    The corresponding 3D coordinates into the volume are \c origin, \c pos1, 
    and \c pos2.
*/

template <class Sampler>
void scanConvertTriangularFrustum(const VsDataAccess * rawData, const VsDataAccess *access, McBox3f bbox,
                                  McVec2f indexOrigin,          McVec2f indexPos1,  McVec2f indexPos2, 
                                  McVec3f origin,               McVec3f pos1,       McVec3f pos2, 
                                  McVec3f normalOrigin,         McVec3f normalPos1, McVec3f normalPos2, 
                                  float thickness,              int thickStride,    int interpolate,
                                  Sampler * sampler)
{
    /* 
       The algorithm does compute thick slice extraction, if required.
       Thick slicing works by extruding the triangle along the normal direction to compose
       a frustum with a back and a front triangle. Interpolation is performed syncronously
       on the back and front triangle and thick sampling is performed along the connecting
       line between those interpolated points.

       Thin slice extraction is implemented as a special case of thick slice extraction 
       where the front and the back triangle coincide with the triangle in between 
       (the triangle that has been extruded in the first place).
    */

    // only implemented for ONE variable
    assert(access->nDataVar() == 1);


    // ----- 1. determine how many samples we need -----
    int dims[3];
    access->dims().toInt(dims);
    McVec3f voxelSize = bbox.getVoxelSize(dims);
    McVec3f edge1(voxelSize[0], 0, 0);
    McVec3f edge2(0, voxelSize[1], 0);
    McVec3f edge3(0, 0, voxelSize[2]);

    // take the average normal vector of the triangle to guess the number of samples
    McVec3f N = (1.0f/3.0f) * (normalOrigin + normalPos1 + normalPos2);
    N.normalize(); // this shouldn't be necessary

    // now determine the number of samples used for a thick slice
    // first project the voxel's edge vectors onto N
    // and select the maximal length to scale the normalized N;
    McVec3f proj1 = edge1 * (N.dot(McVec3f(1,0,0))); 
    McVec3f proj2 = edge2 * (N.dot(McVec3f(0,1,0))); 
    McVec3f proj3 = edge3 * (N.dot(McVec3f(0,0,1))); 

    // TODO: shouldn't this be the minimum length ?? (MW)
    float maxProj = VS_MAX3(proj1.length(), proj2.length(), proj3.length());
    int numOrthoSamples = 0;
    if (thickness > 0) {
        numOrthoSamples = McRoundEven(thickness / maxProj);
    } else {
        numOrthoSamples = 1;
    }
#ifndef NDEBUG
    // std::cerr << "numOrthoSamples = " << numOrthoSamples << std::endl;
#endif


    // ----- 2. determine the front and back triangle -----
    McVec3f originF, originB;
    McVec3f pos1F, pos1B;
    McVec3f pos2F, pos2B;
    
    // assert normalOrigin.length() == 1
    originF = origin + 0.5f * normalOrigin * thickness;
    originB = origin - 0.5f * normalOrigin * thickness;

    // assert normalPos1.length() == 1
    pos1F = pos1 + 0.5f * normalPos1 * thickness;
    pos1B = pos1 - 0.5f * normalPos1 * thickness;

    // assert normalPos2.length() == 1
    pos2F = pos2 + 0.5f * normalPos2 * thickness;
    pos2B = pos2 - 0.5f * normalPos2 * thickness;


    // ----- 3. assemble data structures for scan conversion -----
    // user data
    UserData<Sampler> userData;
    userData.sliceAccess  = rawData;
    userData.volumeAccess = access;
    userData.sampler      = sampler;
    userData.bbox         = bbox;
    userData.scalex       = (access->dims()[0] - 1) / bbox.getSize()[0];
    userData.scaley       = (access->dims()[1] - 1) / bbox.getSize()[1];
    userData.scalez       = (access->dims()[2] - 1) / bbox.getSize()[2];
    userData.numSamples   = numOrthoSamples;
    userData.thickStride  = thickStride;
    userData.interpolate  = interpolate;

    // vertex list
    VsScanConvert::Vertex vertices[3];

    vertices[0].x = indexOrigin.x;    // Texture coordinates for the output image
    vertices[0].y = indexOrigin.y;
    vertices[0].data[0] = originB.x;  // Texture coordinates for the input volume
    vertices[0].data[1] = originB.y;  //         (back triangle)
    vertices[0].data[2] = originB.z;
    vertices[0].data[3] = originF.x;  // Texture coordinates for the input volume
    vertices[0].data[4] = originF.y;  //         (front triangle)
    vertices[0].data[5] = originF.z;

    vertices[1].x = indexPos1.x;      // Texture coordinates for the output image
    vertices[1].y = indexPos1.y;
    vertices[1].data[0] = pos1B.x;    // Texture coordinates for the input volume
    vertices[1].data[1] = pos1B.y;    //         (back triangle)
    vertices[1].data[2] = pos1B.z;
    vertices[1].data[3] = pos1F.x;    // Texture coordinates for the input volume
    vertices[1].data[4] = pos1F.y;    //         (front triangle)
    vertices[1].data[5] = pos1F.z;

    vertices[2].x = indexPos2.x;      // Texture coordinates for the output image
    vertices[2].y = indexPos2.y;
    vertices[2].data[0] = pos2B.x;    // Texture coordinates for the input volume
    vertices[2].data[1] = pos2B.y;    //         (back triangle)
    vertices[2].data[2] = pos2B.z;
    vertices[2].data[3] = pos2F.x;    // Texture coordinates for the input volume
    vertices[2].data[4] = pos2F.y;    //         (front triangle)
    vertices[2].data[5] = pos2F.z;


    // ----- 4. now raster the thick trianglular frustum -----
    VsScanConvert scanConv(thickness > 0 ? 6 : 3); // 6 data vars for thick slice - 3 for thin slice
    scanConv.setCanvas(rawData->dims()[0], rawData->dims()[1]);
    scanConv.setPixelCallback(Dummy<Sampler>::pixelCB, &userData);
    scanConv.scanConvertPixelCB(3, vertices);
}


} // end annonymous namespace

namespace {
    template <class F>
    class RawSampler {
        F *                  mFunctor;
        const VsDataAccess * mAcc;
    public:
        RawSampler(F * functor, const VsDataAccess * data) { mAcc = data, mFunctor = functor; }
        inline void init(int i, int j, int k, int outIndex) {
#if 1
            assert(k >= 0);
            assert(k < mAcc->dims()[2]);
            assert(j >= 0);
            assert(j < mAcc->dims()[1]);
            assert(i >= 0);
            assert(i < mAcc->dims()[0]);
            assert(outIndex < mAcc->dims()[0]*mAcc->dims()[1]*mAcc->dims()[2]);
#endif
            char * ptr = mAcc->dataPtr(k) + j*mAcc->strides()[1] + i*mAcc->strides()[0];
            mFunctor->start(ptr, 0, outIndex);
        }

        // Same as RawSampler::init but performs linear interpolation
        inline void init(float i, float j, float k, int outIndex, void *) {

            int imin = VS_MAX((int) i, 0);
            int imax = VS_MIN((int) i+1, mAcc->dims()[0]-1);
            float iFrac = i - floor(i);

            int jmin = VS_MAX((int) j, 0);
            int jmax = VS_MIN((int) j+1, mAcc->dims()[1]-1);
            float jFrac = j - floor(j);

            int kmin = VS_MAX((int) k, 0);
            int kmax = VS_MIN((int) k+1, mAcc->dims()[2]-1);
            float kFrac = k - floor(k);

            typename F::Type * v000 = (typename F::Type*) (mAcc->dataPtr(kmin) + jmin*mAcc->strides()[1] + imin*mAcc->strides()[0]);
            typename F::Type * v001 = (typename F::Type*) (mAcc->dataPtr(kmin) + jmin*mAcc->strides()[1] + imax*mAcc->strides()[0]);
            typename F::Type * v010 = (typename F::Type*) (mAcc->dataPtr(kmin) + jmax*mAcc->strides()[1] + imin*mAcc->strides()[0]);
            typename F::Type * v011 = (typename F::Type*) (mAcc->dataPtr(kmin) + jmax*mAcc->strides()[1] + imax*mAcc->strides()[0]);
            typename F::Type * v100 = (typename F::Type*) (mAcc->dataPtr(kmax) + jmin*mAcc->strides()[1] + imin*mAcc->strides()[0]);
            typename F::Type * v101 = (typename F::Type*) (mAcc->dataPtr(kmax) + jmin*mAcc->strides()[1] + imax*mAcc->strides()[0]);
            typename F::Type * v110 = (typename F::Type*) (mAcc->dataPtr(kmax) + jmax*mAcc->strides()[1] + imin*mAcc->strides()[0]);
            typename F::Type * v111 = (typename F::Type*) (mAcc->dataPtr(kmax) + jmax*mAcc->strides()[1] + imax*mAcc->strides()[0]);

            float val00 = (*v000) * (1-iFrac) + (*v001) * iFrac; // interpolation along x-axis
            float val01 = (*v010) * (1-iFrac) + (*v011) * iFrac;
            float val10 = (*v100) * (1-iFrac) + (*v101) * iFrac;
            float val11 = (*v110) * (1-iFrac) + (*v111) * iFrac;

            float val0 = val00 * (1-jFrac) + val01 * jFrac; // interpolation along y-axis
            float val1 = val10 * (1-jFrac) + val11 * jFrac;

            typename F::Type val = (typename F::Type) (val0 * (1-kFrac) + val1 * kFrac); // interpolation along z-axis

            mFunctor->start(&val, 0, outIndex);
        }

        inline void operator()(int i, int j, int k, int outIndex) {
#if 1
            assert(k >= 0);
            assert(k < mAcc->dims()[2]);
            assert(j >= 0);
            assert(j < mAcc->dims()[1]);
            assert(i >= 0);
            assert(i < mAcc->dims()[0]);
            assert(outIndex < mAcc->dims()[0]*mAcc->dims()[1]*mAcc->dims()[2]);
#endif
            char * ptr = mAcc->dataPtr(k) + j*mAcc->strides()[1] + i*mAcc->strides()[0];
            mFunctor->accumulate(ptr, 0, outIndex);
        }

        // Same as RawSampler::operator() but performs linear interpolation
        inline void operator()(float i, float j, float k, int outIndex, void *) {

            int imin = VS_MAX((int) i, 0);
            int imax = VS_MIN((int) i+1, mAcc->dims()[0]-1);
            float iFrac = i - floor(i);

            int jmin = VS_MAX((int) j, 0);
            int jmax = VS_MIN((int) j+1, mAcc->dims()[1]-1);
            float jFrac = j - floor(j);

            int kmin = VS_MAX((int) k, 0);
            int kmax = VS_MIN((int) k+1, mAcc->dims()[2]-1);
            float kFrac = k - floor(k);

            typename F::Type * v000 = (typename F::Type*) (mAcc->dataPtr(kmin) + jmin*mAcc->strides()[1] + imin*mAcc->strides()[0]);
            typename F::Type * v001 = (typename F::Type*) (mAcc->dataPtr(kmin) + jmin*mAcc->strides()[1] + imax*mAcc->strides()[0]);
            typename F::Type * v010 = (typename F::Type*) (mAcc->dataPtr(kmin) + jmax*mAcc->strides()[1] + imin*mAcc->strides()[0]);
            typename F::Type * v011 = (typename F::Type*) (mAcc->dataPtr(kmin) + jmax*mAcc->strides()[1] + imax*mAcc->strides()[0]);
            typename F::Type * v100 = (typename F::Type*) (mAcc->dataPtr(kmax) + jmin*mAcc->strides()[1] + imin*mAcc->strides()[0]);
            typename F::Type * v101 = (typename F::Type*) (mAcc->dataPtr(kmax) + jmin*mAcc->strides()[1] + imax*mAcc->strides()[0]);
            typename F::Type * v110 = (typename F::Type*) (mAcc->dataPtr(kmax) + jmax*mAcc->strides()[1] + imin*mAcc->strides()[0]);
            typename F::Type * v111 = (typename F::Type*) (mAcc->dataPtr(kmax) + jmax*mAcc->strides()[1] + imax*mAcc->strides()[0]);

            float val00 = (*v000) * (1-iFrac) + (*v001) * iFrac; // interpolation along x-axis
            float val01 = (*v010) * (1-iFrac) + (*v011) * iFrac;
            float val10 = (*v100) * (1-iFrac) + (*v101) * iFrac;
            float val11 = (*v110) * (1-iFrac) + (*v111) * iFrac;

            float val0 = val00 * (1-jFrac) + val01 * jFrac; // interpolation along y-axis
            float val1 = val10 * (1-jFrac) + val11 * jFrac;

            typename F::Type val = (typename F::Type) (val0 * (1-kFrac) + val1 * kFrac); // interpolation along z-axis

            mFunctor->accumulate(&val, 0, outIndex);
        }

        inline void finalize(unsigned int count, int outIndex) {
            // this call will finalize the respective value - 
            // TODO: it's a side effect of AvgFunctor::value - so maybe we should have a specific function for that
#if 1
            assert(outIndex < mAcc->dims()[0]*mAcc->dims()[1]*mAcc->dims()[2]);
#endif
            typename F::Type dummy; 
            mFunctor->value(count, outIndex, &dummy);
        }
    };
    template <class F>
    class LabeledSampler {
        F *                  mFunctor;
        const VsDataAccess * mAcc;
        const VsDataAccess * mLabelAcc;
    public:
        LabeledSampler(F * functor, const VsDataAccess * data, const VsDataAccess * label) { 
            mFunctor = functor; mAcc = data; mLabelAcc = label;
        }
        inline void init(int i, int j, int k, int outIndex) {
            char * ptr  = mAcc->dataPtr(k) + j*mAcc->strides()[1] + i*mAcc->strides()[0];
            char * lPtr = mLabelAcc->dataPtr(k) + j*mLabelAcc->strides()[1] + i*mLabelAcc->strides()[0];
            mFunctor->start(ptr, (unsigned char*) lPtr, outIndex);
        }
        // Same as LabeledSampler::init since there is no linear interpolation on labels
        inline void init(float i, float j, float k, int outIndex, void *) {
            return init((int) i, (int) j, (int) k, outIndex);
        }
        inline void operator()(int i, int j, int k, int outIndex) {
            char * ptr  = mAcc->dataPtr(k) + j*mAcc->strides()[1] + i*mAcc->strides()[0];
            char * lPtr = mLabelAcc->dataPtr(k) + j*mLabelAcc->strides()[1] + i*mLabelAcc->strides()[0];
            mFunctor->accumulate(ptr, (unsigned char*) lPtr, outIndex);
        }
        // Same as LabeledSampler::operator() since there is no linear interpolation on labels
        inline void operator()(float i, float j, float k, int outIndex, void *) {
            return operator()((int) i, (int) j, (int) k, outIndex);
        }
        inline void finalize(unsigned int count, int outIndex) {
            // this call will finalize the respective value - 
            // TODO: it's a side effect of AvgFunctor::value - so maybe we should have a specific function for that
            typename F::Type dummy; 
            mFunctor->value(count, outIndex, &dummy);
        }
    };
}

#define CANCELED \
    if (object.canceled()) { \
        data.unlock(access); \
        return false; \
    }

// this is a modified version of extractSlice that uses a frustum instead of a triangular prism for sampling
template <class F>
bool VsQuadMesh::extractSliceFrustum(VsQuadMesh * mesh, const VsDataAccess &sliceAccess, VsData &data, VsData * label, float thickness, int thickStride, int interpolate, F * functor, VsObject & object)
{
    assert(sliceAccess.dims()[0] > 0);
    assert(sliceAccess.dims()[1] > 0);
    // assert((m_-1) > 0);
    // assert((n_-1) > 0);

    unsigned int m_ = mesh->dimensions()[0];
    unsigned int n_ = mesh->dimensions()[1];

    McVec3f * v[4];
    McVec2f * t[4];

    McVec2i quadDimInt;
    quadDimInt.x = sliceAccess.dims()[0] / (m_-1);
    quadDimInt.y = sliceAccess.dims()[1] / (n_-1);
    McWatch watch1;
    watch1.start();

    // lock the data   
    const VsDataAccess *access = data.lock(VsData::P_READONLY);

    if (!access) {
        // ok for WAN on client
        return false;       
    }

    // lock label data
    const VsDataAccess * labelAccess = label ? label->lock(VsData::P_READONLY) : 0;

    McBox3f bbox;
    data.boundingBox(bbox);

    // for all quads of the mesh
    for (unsigned int j = 0; j < n_-1; j++) {
        for (unsigned int i = 0; i < m_-1; i++) {

#ifndef NDEBUG
            fprintf(stderr, "%d / %d\r", j * (m_-1) + i, (n_-1) * (m_-1));
#endif
            CANCELED

            v[0] = &mesh->vertex(i,   j);   // &(m_Vertices[0])  + m_ * (j) + (i);
            v[1] = &mesh->vertex(i+1, j);   // &(m_Vertices[0])  + m_ * (j) + (i+1);
            v[2] = &mesh->vertex(i+1, j+1); // &(m_Vertices[0])  + m_ * (j+1) + (i+1);
            v[3] = &mesh->vertex(i,   j+1); // &(m_Vertices[0])  + m_ * (j+1) + (i);

            t[0] = &mesh->texCoord(i,   j);
            t[1] = &mesh->texCoord(i+1, j);
            t[2] = &mesh->texCoord(i+1, j+1);
            t[3] = &mesh->texCoord(i,   j+1);

            // There is a splitting in four triangles, to ensure well behaviour even if the
            // points are not coplanar.
            //
            //       NW -- NE
            //       | \  / |
            //       |  C   |
            //       | /  \ |
            //       SW -- SE

            McVec2f imageSize(sliceAccess.dims()[0], sliceAccess.dims()[1]);

            // get the 3D center of the current quad
            McVec3f centerPos(mesh->centerVertex(i,j));
            McVec2f centerTex = mesh->centerTexCoord(i,j).compprod(imageSize);

            // compute the texture coordinates of corner points
            McVec2f northEast = t[2]->compprod(imageSize);
            McVec2f southEast = t[1]->compprod(imageSize);
            McVec2f northWest = t[3]->compprod(imageSize);
            McVec2f southWest = t[0]->compprod(imageSize);

            static bool useScanConvert = true;

            if (labelAccess) {

                LabeledSampler<F> sampler(functor, access, labelAccess);

              if (useScanConvert) {
                // extract the southern triangle of the quad
                scanConvertTriangularFrustum<LabeledSampler<F> >(
                        &sliceAccess, access, bbox,
                        southWest, southEast, centerTex, // indexOrigin, indexPos1, indexPos2
                        *(v[0]), *(v[1]), centerPos, 
                        mesh->vertexNormal(i,j), mesh->vertexNormal(i+1,j), mesh->centerNormal(i,j),
                        thickness, thickStride, interpolate, &sampler);

                // extract the northern triangle of the quad
                scanConvertTriangularFrustum<LabeledSampler<F> >(
                        &sliceAccess, access, bbox,
                        northEast, northWest, centerTex, // indexOrigin, indexPos1, indexPos2
                        *(v[2]), *(v[3]), centerPos, 
                        mesh->vertexNormal(i+1,j+1), mesh->vertexNormal(i,j+1), mesh->centerNormal(i,j),
                        thickness, thickStride, interpolate, &sampler);

                CANCELED

                // extract the eastern triangle of the quad
                scanConvertTriangularFrustum<LabeledSampler<F> >(
                        &sliceAccess, access, bbox,
                        southEast, northEast, centerTex, // indexOrigin, indexPos1, indexPos2
                        *(v[1]), *(v[2]), centerPos, 
                        mesh->vertexNormal(i+1,j), mesh->vertexNormal(i+1,j+1), mesh->centerNormal(i,j),
                        thickness, thickStride, interpolate, &sampler);

                // extract the western triangle of the quad              
                scanConvertTriangularFrustum<LabeledSampler<F> >(
                        &sliceAccess, access, bbox,
                        northWest, southWest, centerTex, // indexOrigin, indexPos1, indexPos2
                        *(v[3]), *(v[0]), centerPos, 
                        mesh->vertexNormal(i,j+1), mesh->vertexNormal(i,j), mesh->centerNormal(i,j),
                        thickness, thickStride, interpolate, &sampler);

                CANCELED
              }
              else {
                // extract the southern triangle of the quad
                rasterTriangularFrustum<LabeledSampler<F> >(
                        &sliceAccess, access, bbox,
                        southWest, southEast, centerTex, // indexOrigin, indexPos1, indexPos2
                        *(v[0]), *(v[1]), centerPos, 
                        mesh->vertexNormal(i,j), mesh->vertexNormal(i+1,j), mesh->centerNormal(i,j),
                        thickness, thickStride, &sampler);

                // extract the northern triangle of the quad
                rasterTriangularFrustum<LabeledSampler<F> >(
                        &sliceAccess, access, bbox,
                        northEast, northWest, centerTex, // indexOrigin, indexPos1, indexPos2
                        *(v[2]), *(v[3]), centerPos, 
                        mesh->vertexNormal(i+1,j+1), mesh->vertexNormal(i,j+1), mesh->centerNormal(i,j),
                        thickness, thickStride, &sampler);

                CANCELED

                // extract the eastern triangle of the quad
                rasterTriangularFrustum<LabeledSampler<F> >(
                        &sliceAccess, access, bbox,
                        southEast, northEast, centerTex, // indexOrigin, indexPos1, indexPos2
                        *(v[1]), *(v[2]), centerPos, 
                        mesh->vertexNormal(i+1,j), mesh->vertexNormal(i+1,j+1), mesh->centerNormal(i,j),
                        thickness, thickStride, &sampler);

                // extract the western triangle of the quad              
                rasterTriangularFrustum<LabeledSampler<F> >(
                        &sliceAccess, access, bbox,
                        northWest, southWest, centerTex, // indexOrigin, indexPos1, indexPos2
                        *(v[3]), *(v[0]), centerPos, 
                        mesh->vertexNormal(i,j+1), mesh->vertexNormal(i,j), mesh->centerNormal(i,j),
                        thickness, thickStride, &sampler);

                CANCELED
              }
            }
            else {

                RawSampler<F> sampler(functor, access);

              if (useScanConvert) {

                // extract the southern triangle of the quad
                scanConvertTriangularFrustum<RawSampler<F> >(
                        &sliceAccess, access, bbox,
                        southWest, southEast, centerTex, // indexOrigin, indexPos1, indexPos2
                        *(v[0]), *(v[1]), centerPos, 
                        mesh->vertexNormal(i,j), mesh->vertexNormal(i+1,j), mesh->centerNormal(i,j),
                        thickness, thickStride, interpolate, &sampler);

                // extract the northern triangle of the quad
                scanConvertTriangularFrustum<RawSampler<F> >(
                        &sliceAccess, access, bbox,
                        northEast, northWest, centerTex, // indexOrigin, indexPos1, indexPos2
                        *(v[2]), *(v[3]), centerPos, 
                        mesh->vertexNormal(i+1,j+1), mesh->vertexNormal(i,j+1), mesh->centerNormal(i,j),
                        thickness, thickStride, interpolate, &sampler);

                CANCELED

                // extract the eastern triangle of the quad
                scanConvertTriangularFrustum<RawSampler<F> >(
                        &sliceAccess, access, bbox,
                        southEast, northEast, centerTex, // indexOrigin, indexPos1, indexPos2
                        *(v[1]), *(v[2]), centerPos, 
                        mesh->vertexNormal(i+1,j), mesh->vertexNormal(i+1,j+1), mesh->centerNormal(i,j),
                        thickness, thickStride, interpolate, &sampler);

                // extract the western triangle of the quad              
                scanConvertTriangularFrustum<RawSampler<F> >(
                        &sliceAccess, access, bbox,
                        northWest, southWest, centerTex, // indexOrigin, indexPos1, indexPos2
                        *(v[3]), *(v[0]), centerPos, 
                        mesh->vertexNormal(i,j+1), mesh->vertexNormal(i,j), mesh->centerNormal(i,j),
                        thickness, thickStride, interpolate, &sampler);

                CANCELED

              }
              else {

                // extract the southern triangle of the quad
                rasterTriangularFrustum<RawSampler<F> >(
                        &sliceAccess, access, bbox,
                        southWest, southEast, centerTex, // indexOrigin, indexPos1, indexPos2
                        *(v[0]), *(v[1]), centerPos, 
                        mesh->vertexNormal(i,j), mesh->vertexNormal(i+1,j), mesh->centerNormal(i,j),
                        thickness, thickStride, &sampler);

                // extract the northern triangle of the quad
                rasterTriangularFrustum<RawSampler<F> >(
                        &sliceAccess, access, bbox,
                        northEast, northWest, centerTex, // indexOrigin, indexPos1, indexPos2
                        *(v[2]), *(v[3]), centerPos, 
                        mesh->vertexNormal(i+1,j+1), mesh->vertexNormal(i,j+1), mesh->centerNormal(i,j),
                        thickness, thickStride, &sampler);

                CANCELED

                // extract the eastern triangle of the quad
                rasterTriangularFrustum<RawSampler<F> >(
                        &sliceAccess, access, bbox,
                        southEast, northEast, centerTex, // indexOrigin, indexPos1, indexPos2
                        *(v[1]), *(v[2]), centerPos, 
                        mesh->vertexNormal(i+1,j), mesh->vertexNormal(i+1,j+1), mesh->centerNormal(i,j),
                        thickness, thickStride, &sampler);

                // extract the western triangle of the quad              
                rasterTriangularFrustum<RawSampler<F> >(
                        &sliceAccess, access, bbox,
                        northWest, southWest, centerTex, // indexOrigin, indexPos1, indexPos2
                        *(v[3]), *(v[0]), centerPos, 
                        mesh->vertexNormal(i,j+1), mesh->vertexNormal(i,j), mesh->centerNormal(i,j),
                        thickness, thickStride, &sampler);

                CANCELED

              }
            }
        }
    }
 
    if (labelAccess)  label->unlock(labelAccess);
    VSRESULT result = data.unlock(access);
    
    assert(result == VS_OK);
    
    if (result != VS_OK) {
#ifndef NDEBUG
        fprintf(stderr, "warning: VsDataAccess couldn't be unlocked\n");
#endif        
      return false;
    }
    
#ifndef NDEBUG
    fprintf(stderr, "extraction time [ms] %f\n", 1000.0f*watch1.getTime());
#endif
    
    return true;
}

#endif

/// @}
