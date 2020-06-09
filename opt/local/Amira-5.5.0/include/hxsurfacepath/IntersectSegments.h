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

/// @addtogroup hxsurfacepath hxsurfacepath
/// @{
#ifndef INTERSECT_SEGMENTS  
#define INTERSECT_SEGMENTS  

#include <mclib/McVec2f.h>
#include "hxsurfacepathAPI.h"

/** Computes intersection of straight lines or straightline segments
    in 2d.
*/
class HXSURFACEPATH_API IntersectSegments
{

public:
    /// Constructor setting tolerance.
    IntersectSegments(float tol=1.e-6);

    /// Destructor.
    ~IntersectSegments(void);

    /// Stores outcome of intersection computation.
    class Intersection
    {
    public:
        /// Constructor.
        Intersection()
        {
            intersected=false;
            lambda1=0;
            lambda2=0;
            overlay=false;
        }

        /// Do the segments intersect at all?
        bool intersected;

        /// Coordinate of intersection relative to p1,q1.  The
        /// coordinate of intersection would be:
        /// lambda1*p1+(1-lambda1)*q1.
        float lambda1;

        /// Coordinate of intersection relative to p2,q2.
        float lambda2;

        /// Do the segments overlay?
        bool overlay;
    };

    /// Tolerance when intersecting.
    float mTol;

    /// Computes intersection of straight lines.
    void intersectStraightLines(const McVec2f& p1, const McVec2f& q1, 
                                const McVec2f& p2, const McVec2f& q2, 
                                IntersectSegments::Intersection& intersection);

    /// Computes intersection of straightline segments.
    void intersectSegments(const McVec2f& p1, const McVec2f& q1, 
                           const McVec2f& p2, const McVec2f& q2,
                           IntersectSegments::Intersection& intersection);

    /// Returns trimmed value of @c lambda.  If lambda is within a
    /// certain tolerance of 0.0 or 1.0, then lambda is trimmed to 0.0
    /// or 1.0.
    float trimToTolerance(float lambda) const;

private:
    /// Computes barycentric coordinates of @c c w.r.t. edge
    /// connecting @c a and @c b.
    float computeBarycentric(const McVec2f& a, const McVec2f& b, const McVec2f& c);
};

#endif // INTERSECT_SEGMENTS

/// @}
