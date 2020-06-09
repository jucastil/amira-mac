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

/// @addtogroup hxcore hxcore
/// @{
#ifndef HX_VERTEX_SET_H
#define HX_VERTEX_SET_H

#include <stdarg.h>
#include <mclib/McVec3f.h>
#include <mclib/McBitfield.h>
#include <mclib/McBox3f.h>
#include <hxcore/HxSpatialData.h>
#include "HxTransformable.h"

class SoTransform;
class SbMatrix;

class McVec3f;
class McProgressInterface;

class HxModule;

/** Base class for all HyperPlan data objects that are defined by a set
    of vertices and that can be transformed by transforming the
    vertices. */
class HXCORE_API HxVertexSet : public HxSpatialData {
    HX_ABSTRACT_HEADER(HxVertexSet);

  public:
    /// Get box containing all vertices.
    virtual void getBoundingBox(float bbox[6]) const;

    /// Transform the vertices.
    virtual void applyTransform(const SbMatrix& transform);

    /// Translate all points by vector @c d, uses applyTransform().
    void translateCoords(const McVec3f& d);

    /// Scale by an isotropic @c scaleFactor, uses applyTransform().
    void scaleCoords(float scaleFactor);

    /// Scale by an anisotropic @c scaleFactor, uses applyTransform().
    void scaleCoords(const McVec3f& scaleFactor);

    /** Compute <tt>v = center + scale * (v - center)</tt> for all vertices,
        uses applyTransform(). */
    void scaleCoords(const McVec3f& center, const McVec3f& scale);

    /// Add random value between @c -amount and @c +amount to each vertex.
    virtual void jitterCoords(const McVec3f& amount);

    /// Get average of all coords.
    virtual McVec3f getAverageCoord();

    /// Returns pointer to coordinate array.
    virtual McVec3f* getCoords() const = 0;

    /// Returns number of points.
    virtual int getNumPoints() const = 0;

    /// Tcl-command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /** Finds points in array @c points, which are closer than @c tol. If tol is
        zero, points with exactly the same coordinates are identified. The method
        returns the number of duplicated points found. @c aliases must point to an
        index array of size @c n. On return this array stores for each point the
        id of the point this point is a duplicate of. For example, if there are 5
        points 0...4, and point 2 is a duplicate of point 0, then @c aliases would
        be 0 1 0 3 4. The method returns the number of duplicated points. */
    static int findDuplicatePoints(int n, const McVec3f* points, int* aliases,
        float tol, McProgressInterface* workArea=0);

    /** Finds points in array @c points, which are closer than @c tol. 
        Similar as previous method, but the search for duplicate points is
        restricted to the points for which @c bitfield is set. The size of
        bitfield must be at least n, otherwise bitfield is ignored, i.e., all
        points are inspected. */
    static int findDuplicatePoints(int n, const McVec3f* points, 
        McBitfield *bitfield, int* aliases, float tol, 
        McProgressInterface* workArea=0);

    /** Removes points in array @c points, which are closer than @c tol. If tol is
        zero, points with exactly the same coordinates are removed. Removing a
        point means that the elements of @c points are rearranged (shifted) so that
        the resulting array is contiguous again. @c newIndices must point to an
        index array of size @c n. On return this array stores for each point the
        new index of that point after renumeration. For example, if there are 5
        points 0...4, and point 2 is a duplicate of point 0, then @c newIndices
        would be 0 1 0 2 3. The method returns the new number of points. */
    static int removeDuplicatePoints(int n, McVec3f* points, int* newIndices,
        float tol, McProgressInterface* workArea=0);

    /** for all points in points1, finds closest point in points2, if there is any in the specified range (tol). Returns
    number of points for which closest point is found.*/
    static int findClosestPoints(int n1, McVec3f* points1, int n2, McVec3f* points2, float range, int* closestPointIndices, McProgressInterface* workArea);

  protected:
    // Constructor is protected - this is an abstract class
    HxVertexSet();

    // Virtual destructor
    virtual ~HxVertexSet();

  private:
    HxTransformableProxy<HxVertexSet> mTransformable;

};

#endif

/// @}
