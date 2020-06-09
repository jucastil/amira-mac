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
#ifndef VS_POLYGON_H
#define VS_POLYGON_H

////////////////////////////////////////////////////////////////////////////////
// VsPolygon
////////////////////////////////////////////////////////////////////////////////

/** Iterator class for polygons 

    The VsPolygon class is intended to iterate over all polygons of a VsMesh,
    thereby hiding any specific implementation details inside VsMesh. In the 
    easiest way the mesh may be implemented as triangle soup with one set of 
    coordinates, texture coordinates etc. for each vertex. But also quad 
    meshes or triangle stripes with a list of vertices and a list of indices 
    referencing elements of that list is possible.

    For iteration purposes each VsMesh instance will return an appropriate
    VsPolygon object reference, which can in terms maps the indices of the 
    vertices to specific vertex elements or does any additional processing 
    like triangluate quads etc.

    For universality a polygon is here considered as list of vertices, each
    specified by a 3D point (see coords()). Optionally, in addition to that 
    each vertex may specify a 2D texture coordinate (see texCoords()) or 
    further attribute values (see attribs()). Note that if an optional 
    attribute is not available NULL is returned.
*/

#include <vector>

#include <mclib/McVec2f.h>
#include <mclib/McVec3f.h>
#include <mclib/McVec4f.h>
#include <mclib/McLine.h>

class VsPolygon
{
public:
    virtual ~VsPolygon() {};
    /// Returns the number of vertices in the polygon    
    virtual unsigned int numVertices() const = 0;
    /// Returns the vertex coordinates of the \c idx -th vertex
    virtual const McVec3f * coords(unsigned int idx) const = 0;
    /// Returns the texture coordinates of the \c idx -th vertex
    virtual const McVec2f * texCoords(unsigned int idx) const = 0;
    
    /// Returns the number of additional vertex attributes
    virtual unsigned int numAttribs() const = 0;
    
    /// Returns the \c num -th attribute vector of the \c idx -th vertex        
    virtual const McVec4f * attribs(unsigned int num, unsigned int idx) const = 0;

    /// Returns the intersection of a line with the convex polygon
    inline bool intersect(const McLine &l, McVec3f &intersection, McVec3f &barycentric, McVec3i *indices = 0) const;
};


////////////////////////////////////////////////////////////////////////////////
bool VsPolygon::intersect(const McLine &l, McVec3f &intersection, McVec3f &barycentric, McVec3i *indices) const
{
    bool    front;
    bool    isec = false;

    McVec3i idx(0, 1, 2);
    int  numVerts = numVertices();

    for (int i=3; i<=numVerts; ++i) {
        // trivial triangulation of a convex polygon to triangles with indices (0, 1, 2); (0, 2, 3); (0, 3, 4); ...
        idx[1] = i-2;
        idx[2] = i-1;

        isec = l.intersect(*coords(idx[0]), *coords(idx[1]), *coords(idx[2]), intersection, barycentric, front);
        if (isec)
            break;
    }
    
    if (isec && indices)
        *indices = idx;

    return isec;
}


////////////////////////////////////////////////////////////////////////////////
// a simple implementation of the VsPolygon abstract base class
////////////////////////////////////////////////////////////////////////////////

class VsGenericPolygon : public VsPolygon
{

public:

    VsGenericPolygon() 
    {
        m_NumVertices  = 0;
        m_VerticesRef  = 0;
        m_TexCoordsRef = 0;
    }

    VsGenericPolygon(unsigned int numVertices)
    {
        resize(numVertices);
    }

    VsGenericPolygon(unsigned int numVertices, McVec3f *vertices, McVec2f *texCoords, unsigned int numAttribs = 0, bool copy = true)
    {
        init(numVertices, vertices, texCoords, numAttribs, copy);
    }

    void init(unsigned int numVertices, McVec3f *vertices, McVec2f *texCoords, unsigned int numAttribs = 0, bool copy = true)
    {
        assert(vertices != NULL);
        assert(texCoords != NULL);

        m_Vertices.resize(numVertices);
        m_TexCoords.resize(numVertices);

        if (copy)
        {
            // Copy the vertex coords
            if (vertices != NULL) {
                std::vector<McVec3f>::iterator dest_v = m_Vertices.begin();
                McVec3f *src_v = vertices;
                for (unsigned int i = 0; i < numVertices; i++) {
                    *dest_v++ = *src_v++;
                }
            }

            // copy the texture coordinates
            if (texCoords != NULL) {
                std::vector<McVec2f>::iterator dest_t = m_TexCoords.begin();
                McVec2f *src_t = texCoords;
                for (unsigned int i = 0; i < numVertices; i++) {
                    *dest_t++ = *src_t++;
                }
            }

            m_NumVertices  = numVertices;
            m_VerticesRef  = &m_Vertices[0];
            m_TexCoordsRef = &m_TexCoords[0];
        }
        else 
        {
            // Just recall the pointer references
            m_NumVertices  = numVertices;
            m_VerticesRef  = vertices;
            m_TexCoordsRef = texCoords;
        }

        // Initialize the vector of attribute-vectors.
        // Note that the attribute-vectors are only allocated when setAttrib is called
        m_Attribs.resize(numAttribs);
    }

    void setNumAttribs(unsigned int numAttribs) {
      m_Attribs.resize(numAttribs);
    }

    // set the values for a given vertex attribute
    void setAttrib(unsigned int attribIndex, McVec4f *values) {

        assert(attribIndex < m_Attribs.size());
        assert(values != NULL);

        // resize the idx-th attribute vector
        m_Attribs[attribIndex].resize(m_Vertices.size());

        if (values != NULL) {
            std::vector<McVec4f>::iterator dest_attrib = m_Attribs[attribIndex].begin();
            McVec4f *src_attrib = values;
            const size_t numVertices = m_Vertices.size();
            for (size_t i = 0; i < numVertices; ++i) {
                *dest_attrib++ = *src_attrib++;
            }
        }
    }

    void clear() 
    {
        m_Vertices.clear();
        m_TexCoords.clear();

        m_NumVertices  = 0;
        m_VerticesRef  = &m_Vertices[0];
        m_TexCoordsRef = &m_TexCoords[0];

        std::vector<std::vector<McVec4f> >::iterator attrib_it = m_Attribs.begin();

        while(attrib_it != m_Attribs.end()) {
            attrib_it->clear();
            attrib_it++;
        }
    }

    void resize(unsigned int size) 
    {
        m_Vertices.resize(size);
        m_TexCoords.resize(size);

        m_NumVertices  = size;
        m_VerticesRef  = &m_Vertices[0];
        m_TexCoordsRef = &m_TexCoords[0];

        std::vector<std::vector<McVec4f> >::iterator attrib_it = m_Attribs.begin();

        while(attrib_it != m_Attribs.end()) {
           attrib_it->resize(size);
           attrib_it++;
        }
    }

    const std::vector<McVec3f>& coordVector()
    {
        assert(m_Vertices.size() > 0 && m_VerticesRef == &m_Vertices[0]);
        return m_Vertices;
    }

    const std::vector<McVec2f>& texCoordVector()
    {
        assert(m_TexCoords.size() > 0 && m_TexCoordsRef == &m_TexCoords[0]);
        return m_TexCoords;
    }

    void addVertex(McVec3f &vertex) {
        assert(m_VerticesRef == &m_Vertices[0]);
        m_Vertices.push_back(vertex);

        m_NumVertices  = int(m_Vertices.size());
        m_VerticesRef  = &m_Vertices[0];
    }

    void addTexCoord(McVec2f &texCoord) {
        assert(m_TexCoordsRef == &m_TexCoords[0]);
        m_TexCoords.push_back(texCoord);

        m_NumVertices  = int(m_Vertices.size());
        m_TexCoordsRef = &m_TexCoords[0];
    }
  
    void addAttrib(unsigned int attribIndex, McVec4f attrib)
    {
        assert(attribIndex < m_Attribs.size());
        m_Attribs[attribIndex].push_back(attrib);
    }
    
    const McVec3f& operator()(unsigned int idx) const
    {
        assert(m_Vertices.size() > idx && m_VerticesRef);
        return m_VerticesRef[idx];
    }

    McVec3f& operator[](unsigned int idx)
    {
        assert(m_Vertices.size() > idx && m_VerticesRef);
        return m_VerticesRef[idx];
    }

    void setCoord(unsigned int idx, const McVec3f& coord)
    {
        assert(m_Vertices.size() > idx && m_VerticesRef);
        m_VerticesRef[idx] = coord;
    }

    void setTexCoord(unsigned int idx, const McVec2f& texCoord)
    {
        assert(m_TexCoords.size() > idx && m_TexCoordsRef);
        m_TexCoordsRef[idx] = texCoord;
    }

    void setAttrib(unsigned int attribIndex, unsigned int idx, McVec4f &value)
    {
        assert(attribIndex < m_Attribs.size());
        assert(idx < m_Attribs[attribIndex].size());
        m_Attribs[attribIndex][idx] = value;
    }
    // -- methods defined by the VsPolygon interface --

    /// Returns the number of vertices in the polygon
    virtual unsigned int numVertices() const
    {
        return static_cast<unsigned int>(m_Vertices.size());
    }

    /// Returns the vertex coordinates of the \c idx -th vertex
    virtual const McVec3f* coords(unsigned int idx) const
    {
        assert(m_Vertices.size() > idx && m_VerticesRef);
        //return &(m_Vertices[idx]);
        return &(m_VerticesRef[idx]);
    }

    /// Returns the texture coordinates of the \c idx -th vertex
    virtual const McVec2f* texCoords(unsigned int idx) const
    {
        assert(m_TexCoords.size() > idx && m_TexCoordsRef);

        if (m_TexCoords.size() > 0)
            return &(m_TexCoordsRef[idx]);
        else
            return NULL;
    }

    virtual unsigned int numAttribs() const
    {
        return static_cast<unsigned int>(m_Attribs.size());
    }
    
    /// Returns the \c num -th attribute vector of the \c idx -th vertex
    virtual const McVec4f* attribs(unsigned int num, unsigned int idx) const
    {
        if (num >= m_Attribs.size())
            return NULL;
            
        if (idx >= m_Attribs[num].size())
            return NULL;

        return &(m_Attribs[num][idx]);
    }

private:

    int       m_NumVertices;
    McVec3f * m_VerticesRef;
    McVec2f * m_TexCoordsRef;

    std::vector<McVec3f> m_Vertices;
    std::vector<McVec2f> m_TexCoords;

    std::vector<std::vector<McVec4f> > m_Attribs;
};

#endif

/// @}
