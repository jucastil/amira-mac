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
#ifndef MC_CUTBOXPLANEDOUBLE_H
#define MC_CUTBOXPLANEDOUBLE_H

#include "McWinDLLApi.h"
#include "McVec3d.h"

#pragma warning(push)

// 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
#pragma warning(disable:4251)

/** Computes the polygon resulting from intersecting an axes aligned
    box with an arbitrary plane. The class is optimized for succesive
    computation of intersections with many parallel planes. */

class MCLIB_API McCutBoxPlaneDouble {

  public:
    /// Constructs class from standard bbox (xmin, xmax, ymin, ymax, zmin, zmax)
    McCutBoxPlaneDouble(const double* bbox, const McVec3d& pNormal);

    ///
    McCutBoxPlaneDouble(const double* bbox, const double* tbox, const McVec3d& pNormal);

    /// Alternative constrcutor.
    McCutBoxPlaneDouble(const McVec3d& bbmin, const McVec3d& bbmax, const McVec3d& pNormal);

    /// Default constructor uses unit box and vector in x direction.
    McCutBoxPlaneDouble();

    /// Sets bounding box and normal vector of plane.
    void init(const double* bbox, const McVec3d& plane);

    /** Cut box with a plane. The plane is defined by the normal
            vector specified in the constructor and by the point
                @pCenter. The vertices of the intersecting polygon are
                returned in @c. There must be enough space for up to 6
                intersection points. The return value indicates the number
                of intersection points. */
    int cutPlane(const McVec3d& pCenter, McVec3d* c) {
        return cutPlane(pNormal.dot(pCenter),c);
    }

    int cutPlane(double distanceFromOrigin, McVec3d* c);

    /// Sets bounding box in texture space.
    void init(const double* bbox, const double* texBox, const McVec3d& plane);

    ///
    int cutPlane(const McVec3d& pCenter, McVec3d* c, McVec3d* t) {
        return cutPlane(pNormal.dot(pCenter),c,t);
    }

    int cutPlane(double distanceFromOrigin, McVec3d* c, McVec3d* t);

  protected:
    double dist[8];
    McVec3d pNormal;
    double bbox[6];
    McVec3d cpoints[8];
    McVec3d tpoints[8];
};

#pragma warning(pop)

#endif

/// @}
