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
#ifndef _VS_MESH_H_
#define _VS_MESH_H_

#include "VsPolygon.h"

#include <mclib/McLine.h>


////////////////////////////////////////////////////////////////////////////////
// VsMesh
////////////////////////////////////////////////////////////////////////////////

/** Base class for storing a polygonal object 
    
    The VsMesh interface considers the polygonal object as a list of polygons
    that may be traversed with the VsPolygon iterator pattern. Specific
    implementations may use better internal representations like a quad mesh,
    a triangle strip, or even a parametrical surface that is automatically
    tesselated during/for iteration.
*/
class VsMesh : public VsHandable
{

public:
    virtual ~VsMesh() {};

    /// Returns the number of polygons in the mesh
    virtual int numPolygons() const = 0;
    /** Returns the handle for the \c idx -th polygon - note that this is a
        handle to some internal data structure that might change, in particular
        with a second call to polygon(). It is therefore not save to keep the
        reference for further use. */
    virtual const VsPolygon * polygon(unsigned int idx) const = 0;

    /// Returns the number of contour lines in the mesh
    virtual int numContours() const = 0;
    /** Returns the handle for the \c idx -th contour line - note that this is a
        handle to some internal data structure that might change, in particular
        with a second call to polygon(). It is therefore not save to keep the
        reference for further use. */
    virtual const VsPolygon * contour(unsigned int idx) const = 0;

    /** Returns the bounding box of the mesh.
        \param  outBox
                The current bounding box gets stored in the box object 
                referenced by this parameter.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT boundingBox( McBox3f & outBox ) const = 0;

    /**
      * Intersect mesh by a line, returning the index of the polygon 
      * intersected, or -1 if no polygon was hit.
    */
    inline int intersect(const McLine &l, McVec3f &intersection, McVec3f &barycentric, McVec3i *indices = 0) const;

#if 0 
    // TODO:
    // Maybe we will need something like that for allowing e.g.
    // striping on top of VsMesh without data replication.
    // For the moment would try to do without them.

    /// Returns the number of vertices in the mesh
    virtual int numVertices() const = 0;
    /// Returns the vertex list
    McVec3f * coords() const = 0;
    /// Returns the texture coordinate list
    McVec2f * texCoords() const = 0;
    /// Returns the \c num -th attribute list
    McVec4f * attribs(int num) cons = 0;
#endif
};


////////////////////////////////////////////////////////////////////////////////
int VsMesh::intersect(const McLine &l, McVec3f &intersection, McVec3f &barycentric, McVec3i * indices) const
{
    int found = -1;

    float t       = 0;
    McVec3f dir   = l.getDirection();
    McVec3f start = l.getPosition();

    for (int i = 0; i < numPolygons(); i++)
    {
        McVec3f tmpIntersect;
        McVec3f tmpBarycentric;

        if (polygon(i)->intersect(l, tmpIntersect, tmpBarycentric, indices)) {
            if (found >= 0) {
                // Check for distance to line start and overwrite intersection if closer
                float tNew = (tmpIntersect - start).dot(dir);
                if (tNew < t) {
                    intersection = tmpIntersect;
                    barycentric  = tmpBarycentric;
                    t = (tmpIntersect - start).dot(dir);
                    found = i;
                }
            } else {
                // Set current intersectin
                intersection = tmpIntersect;
                barycentric  = tmpBarycentric;
                t = (tmpIntersect - start).dot(dir);
                found = i;
            }
        }
    }

    return found;
}

#endif // VS_MESH_H


/// @}
