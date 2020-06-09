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
#ifndef MC_CUTBOXPLANE_H
#define MC_CUTBOXPLANE_H

#include "McWinDLLApi.h"
#include "McVec3f.h"

#pragma warning(push)

// 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
#pragma warning(disable:4251)

/** Computes the polygon resulting from intersecting an axes aligned
    box with an arbitrary plane. The class is optimized for succesive
    computation of intersections with many parallel planes. */

class MCLIB_API McCutBoxPlane {

  public:
    /// Constructs class from standard bbox (xmin, xmax, ymin, ymax, zmin, zmax)
    McCutBoxPlane(const float* bbox, const McVec3f& pNormal);

    ///
    McCutBoxPlane(const float* bbox, const float* tbox, const McVec3f& pNormal);

    /// Alternative constrcutor.
    McCutBoxPlane(const McVec3f& bbmin, const McVec3f& bbmax, const McVec3f& pNormal);

    /// Default constructor uses unit box and vector in x direction.
    McCutBoxPlane();

    /// Sets bounding box and normal vector of plane.
    void init(const float* bbox, const McVec3f& plane);

    /** Cut box with a plane. The plane is defined by the normal
            vector specified in the constructor and by the point
                @pCenter. The vertices of the intersecting polygon are
                returned in @c. There must be enough space for up to 6
                intersection points. The return value indicates the number
                of intersection points. */
    int cutPlane(const McVec3f& pCenter, McVec3f* c) {
        return cutPlane(pNormal.dot(pCenter),c);
    }

    int cutPlane(float distanceFromOrigin, McVec3f* c);

    /// Sets bounding box in texture space.
    void init(const float* bbox, const float* texBox, const McVec3f& plane);

    ///
    int cutPlane(const McVec3f& pCenter, McVec3f* c, McVec3f* t) {
        return cutPlane(pNormal.dot(pCenter),c,t);
    }

    int cutPlane(float distanceFromOrigin, McVec3f* c, McVec3f* t);

  protected:
    float dist[8];
    McVec3f pNormal;
    float bbox[6];
    McVec3f cpoints[8];
    McVec3f tpoints[8];
};

#pragma warning(pop)

#endif

/// @}
