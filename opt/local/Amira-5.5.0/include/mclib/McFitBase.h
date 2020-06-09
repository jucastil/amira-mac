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
#ifndef MC_FIT_BASE_H
#define MC_FIT_BASE_H

#include "McWinDLLApi.h"
#include "McDArray.h"
#include "McVec3f.h"
#include "McString.h"

class McFitBase {

public:

    /// Default Constructor
    McFitBase (void) {};

    /// Constructor copying an array of points
    McFitBase (const McDArray<McVec3f> & points) { setPoints(points); }
    McFitBase (const McVec3f* points, const int nPoints) { setPoints(points, nPoints); }

    /// Destructor
    virtual ~McFitBase (void) {};

    /// the point set where the object is to be fit in
    void setPoints(const McDArray<McVec3f> & points) { mPointSet = points; }
    void setPoints(const McVec3f* points, const int nPoints);

    /// add a point to the point set where the object is to be fit in
    void addPoint(const McVec3f & point) { mPointSet.append(point); }

    /// add several points to the point set where the object is to be fit in
    void addPoints(const McDArray<McVec3f> & points) { mPointSet.appendArray(points); }
    void addPoints(const McVec3f* points, const int nPoints);

    /// fit the object to the point set
    virtual void fit() = 0;

    /// generate a result string
    virtual McString getOutput();

    int getNumPoints() { return mPointSet.size(); }

protected:

    /// the point set where the object is to be fit in
    McDArray<McVec3f>  mPointSet;

};

#endif

/// @}
