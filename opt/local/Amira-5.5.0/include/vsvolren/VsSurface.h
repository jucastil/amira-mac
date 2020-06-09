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
#ifndef _VS_SURFACE_H_
#define _VS_SURFACE_H_

#include "Vs.h"

#include "VsObject.h"

class McBox3f;
class McMat4f;
class McVec3f;
class McVec4f;

/** The VsSurface class describes a polygonal object in an abstract way.

    The underlying model is that of an indexed triangle set. A triangle
    is described with three indices pointing to a list of vertex positions.
    In addition to that a list of normal vectors and a list of color values
    describe the visual properties for the triangles.

    The mapping from triangle nodes to normals and colors can be different
    and is defined by the VsSurface::NormalBinding and VsSurface::ColorBinding,
    respectively. Normals can be either defined per vertex, per triangle or per
    vertex instance. Colors can be either constant, per vertex or per triangle.

    For efficiency reasons, the interface has been designed in such a way,
    that the corresponding methods VsSurface::points(), VsSurface::triangles(),
    VsSurface::normals(), VsSurface::colors() return pointers to internal
    data structures. Since during the external traversal of those internal
    data, modifications of the internal fields have to be prevented, the user
    explicitly has to lock the data by calling VsSurface::mapPointers() before
    accessing triangles, vertices, normals, or colors. Similarly the pointers
    have to be released after finishing traversal with a call to 
    VsSurface::unmapPointers().

    The explicit entry points that are provided by mapPointers() and 
    unmapPointers() also easily allow for internal data structures that are
    dynamically changed/adapted, like in the case of an out-of-core geometry
    where the polygon list is only loaded into memory on access.
*/

class VSVOLREN_API VsSurface : public VsObject
{
    VS_DECL_INTERFACE        ( VsSurface )
    VS_DECL_INTERFACE_IMPL   ( VsSurface )
//  VS_DECL_INTERFACE_FACTORY( VsSurface )
//  VS_DECL_INTERFACE_RELAY  ( VsSurface )

    /// Additional flags to be used in touch().
    enum TouchFlag
    {
        /** Set if the surface data has changed, this is important in case of
            caching, e.g., in nodes rendering the surface. */
        NEW_SURFACE_DATA = 1<<1,
        /// Set if a new transform was set.
        NEW_TRANSFORM    = 1<<2,
        /// Set if a new culling mode was set.
        NEW_CULLING      = 1<<3    
    };

public:
    /// Data structure for a triangle
    class Triangle {
      public:
        /** Indices of the three points of the triangle. Indices point into
            the array returned by VsSurface::points(). Thus they are expected
            to start with 0. */
        int points[3];
    };

    /// The semantics of stored normals
    enum NormalBinding {
        /// One normal per triangle.
        TRIANGLE_NORMALS = 0,
        /// One normal per vertex in the list of vertices.
        VERTEX_NORMALS   = 1,
        /// Three times as many normals as triangles.
        DIRECT_NORMALS   = 2
    };

    /// The semantics of stored color values
    enum ColorBinding {
        /// Constant color.
        CONSTANT_COLOR   = 0,
        /// One color per triangle.
        TRIANGLE_COLORS  = 1,
        /// One color per vertex in the list of vertices.
        VERTEX_COLORS    = 2
    };

    /// Culling modes
    enum CullingMode {
        /// No culling (render both faces).
        NO_CULLING       = 0,
        /// Cull back faces.
        BACK_FACE        = 1,
        /// Cull front faces.
        FRONT_FACE       = 2
    };

    /// Returns number of points of the surface
    virtual unsigned int numPoints() const = 0;
    /// Returns list of all points belonging to that surface
    virtual const McVec3f * points() const = 0;
    /// Returns number of triangles of the surface
    virtual unsigned int numTriangles() const = 0;
    /// Returns the array of triangles
    virtual const Triangle * triangles() const = 0;
    /// Returns the binding for stored normal vectors
    virtual NormalBinding normalBinding() const = 0;
    /// Returns number of normals stored for the surface
    virtual unsigned int numNormals() const = 0;
    /// Returns the array of normals
    virtual const McVec3f * normals() const = 0;
    /// Returns the binding for stored color values
    virtual ColorBinding colorBinding() const = 0;
    /// Returns number of color values stored for the surface
    virtual unsigned int numColors() const = 0;
    /// Returns the array of color values
    virtual const McVec4f * colors() const = 0;
    /// Returns whether the surface contains (semi-)transparent polygons
    virtual bool isTransparent() const;
    
    /// Generic interface for extended functionality
    virtual void * extension( int, void *);


    // ////////////////////////////////////////
    //  data mapping/unmapping
    // ////////////////////////////////////////

    /** Maps pointers to memory - this method has to be called BEFORE
        accessing any internal data via triangles(), points(), normals(),
        or colors(). The default implementation just calls VsObject::lock() to
        avoid concurrent access. However, the method can be overwritten to 
        perform more sophisticated operations, like load data from disk or 
        create temporary data arrays. In any case make sure to call 
        VsObject::lock() from within derived methods.
        \param  inReadWrite
                Permission for the requested mapping, options are 
                \c false for read-only access and \c true for read/write access.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT mapPointers(bool inReadWrite) { return inReadWrite ? lock() : lockReadOnly(); };

    /** Unmap pointers from memory. The method has to be called to release the
        data pointers that have been acquired via triangles(), points(), 
        normals(), or colors(). If the method is overwritten, do NOT forget
        to call VsObject::unlock() from inside derived methods.
    */
    virtual VSRESULT unmapPointers() { return unlock(); };


    // ////////////////////////////////////////
    //  bounding box
    // ////////////////////////////////////////

    /** Returns the bounding box of the surface.
        \param  outBox
                The current bounding box gets stored in the box object 
                referenced by this parameter.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT boundingBox( McBox3f & outBox ) const = 0;


    // ////////////////////////////////////////
    //  transformation matrix
    // ////////////////////////////////////////

    /** Set the transformation matrix that transforms from
        object local coordinates to world coordinates.
        \param  inMatrix
                The transformation matrix.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setTransformationMatrix( const McMat4f & inMatrix );

    /** Get the transformation matrix.
        \param  outMatrix
                Receives the current transformation matrix.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT transformationMatrix( McMat4f & outMatrix ) const;


    // ////////////////////////////////////////
    //  rendering parameters
    // ////////////////////////////////////////

    /** Set culling mode for that surface 
        which defines whether only front facing polygons are rendered,
        alternatives are back facing polygons or front and back facing polygons.
        \param  inCulling
                The culling mode.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setCullingMode( const CullingMode inCulling );

    /** Get the culling mode for that surface.
        \return 
                The current culling mode for that surface.
    */
    CullingMode cullingMode() const;
};

#endif


/// @}
