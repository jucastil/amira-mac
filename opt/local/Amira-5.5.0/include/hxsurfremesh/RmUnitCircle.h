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

/// @addtogroup hxsurfremesh hxsurfremesh
/// @{
#ifndef _Rm_UNIT_CIRCLE_H
#define _Rm_UNIT_CIRCLE_H

#include "hxsurfremeshAPI.h"

#include <mclib/McDArray.h>
#include <mclib/McVec3f.h>

//---------------------------------------------------------------------

/** This class represents an oriented 2d closed unit circle with center at (0,0).
    It is represented by a number of n segments, that are connected 
    by the same no. of corners. By definition, segment 0
    is connected to segment 1 via corner 0, ... , finally
    segment n is connected to segment 1 via corner n,
    which closes the loop. */

class HXSURFREMESH_API RmUnitCircle
{

public:

    /// Returns no. of segments (= no. of corners).
    virtual int getNumSegments() const;

    /// Returns coordinates of corner @c iCorner.
    virtual McVec3f getCornerCoord(int iCorner) const;

    /** Returns coordinates of point on segment @c iSeg,
        with normalized arc-length of @c lambda between [0,1]. */
    virtual McVec3f getCoord(int iSeg, float lambda) const;

    /// Returns arc-length of segment @c iSeg.
    virtual float getLength(int iSeg) const;

    /// Returns arc-length of the whole contour
    virtual float getLength() const;

    /// Creates a discrete shape from sampled @c points
    virtual void create(const McDArray< McDArray<McVec3f> >& points) {}

    /// Creates an analytic shape from given segment lengths
    virtual void create(const McDArray<float>& lengths);

protected:

    /// angles of corners (in radians)
    McDArray<float> corners;
};

#endif

/// @}
