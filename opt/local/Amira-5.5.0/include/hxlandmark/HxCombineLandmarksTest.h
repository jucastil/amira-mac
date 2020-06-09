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

/// @addtogroup hxlandmark hxlandmark
/// @{
#ifndef HXCOMBINELANDMARKSTEST_H
#define HXCOMBINELANDMARKSTEST_H

#include "HxCombineLandmarks.h"
#include "HxLandmarkSet.h"
#include "HxLandmarkWinDLLApi.h"
#include <mclib/McTest.h>

class HXLANDMARK_API HxCombineLandmarksTest : public McTest
{
    MC_HEADER(HxCombineLandmarksTest);
public:
    virtual void setUp();

    void testCombineLandmarksOneSet();
    void testCombineLandmarksNSets(); 
    void testCombineSetsWithSubsetsToNSets();

private:
    McDArray<McVec3f> allInOneLandmarkPositions;
    McDArray<McDArray<McVec3f> > nSetsLandmarkPositions;

    McDArray<McVec3f> mReferencePositionsSet1;
    McDArray<McVec3f> mReferencePositionsSet2;
    McDArray<McDArray<McVec3f> > mReferencePositionsNSets3;

    HxLandmarkSet* createLandmarkSet(McDArray<McVec3f> referenceSet);
    HxLandmarkSet* createLandmarkSetNSets (McDArray<McDArray<McVec3f> > referenceSet);

    void fillWithZero(McDArray<McVec3f> &referenceSet, int resultSetSize);
    void equalPointsInArray(McDArray<McVec3f> resultPoints, McDArray<McVec3f> referencePoints);

};

#endif

/// @}
