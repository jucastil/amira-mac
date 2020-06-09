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
#ifndef MC_FIT_PLANE_H
#define MC_FIT_PLANE_H

#include "McFitBase.h"
#include "McMat4f.h"

class MCLIB_API McFitPlane : public McFitBase {

public:

    /// Default constructor
    McFitPlane() {};

    /// Constructor copying an array of points
    McFitPlane(const McDArray<McVec3f> & points) : McFitBase(points) {};
    McFitPlane(const McVec3f* points, const int nPoints) : McFitBase(points, nPoints) {};

    /// determines the plane with the minimal sum
    /// of squared distances to all given points
    virtual void fit();

    virtual McString getOutput();

    // returns the centroid of the computed plane
    McVec3f  getCentroid (void) { return mCentroid; }

    /// returns the normal of computed plane
    McVec3f  getNormal (void) { return mNormal; }

    /// returns the transformation
    McMat4f  getTransformation (void) { return mTransformMat; }


protected:

    // creates an initial plane
    void  createPlane (void);

    // fits the plane to the point set via orthonormal regression
    float orthogonalPlaneFit (void);


private:

    McVec3f  mCentroid;
    McVec3f  mNormal;

    // the transformation matrix
    McMat4f  mTransformMat;
};

#endif

/// @}
