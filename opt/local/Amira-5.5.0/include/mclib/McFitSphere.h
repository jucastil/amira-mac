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
#ifndef MC_FIT_SPHERE_H
#define MC_FIT_SPHERE_H

#include "McFitBase.h"
    
const float REL_ERR_SQ = 0.000001;
const int MAX_ITER = 10000;

/* Fits sphere to a set of points by minizing the sum of the squared distances */
class MCLIB_API McFitSphere : public McFitBase {

public:
    /// Default constructor
    McFitSphere() : mRelErrSq(REL_ERR_SQ), mMaxIter(MAX_ITER) {};
    
    /// Constructor copying an array of points
    McFitSphere(const McDArray<McVec3f> & points) : McFitBase(points), mRelErrSq(REL_ERR_SQ), mMaxIter(MAX_ITER) {};
    McFitSphere(const McVec3f* points, const int nPoints) : McFitBase(points, nPoints), mRelErrSq(REL_ERR_SQ), mMaxIter(MAX_ITER) {};

    /// determines the Sphere with the minimal sum
    /// of squared distances to all given points
    virtual void fit();

    virtual McString getOutput();

    // returns the centroid of the computed Sphere
    McVec3f  getCentroid (void) { return mCentroid; }

    /// returns the normal of computed Sphere
    float  getRadius (void) { return mRadius; }

    void setMaxIter(int maxIter) { mMaxIter = maxIter; }
    void setRelErrSq(float relErrSq) { mRelErrSq = relErrSq; }
    int getMaxIter() { return mMaxIter; }
    float getrelErrSq() { return mRelErrSq; }

protected:

    // creates an initial Sphere
    void  createSphere (void);

    void computeRadius(void);

private:

    McVec3f  mCentroid;
    float   mRadius;

    float mRelErrSq;
    int mMaxIter;
};

#endif

/// @}
