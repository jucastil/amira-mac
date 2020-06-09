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

/// @addtogroup hxsurfedit hxsurfedit
/// @{
#ifndef SURFEDITHOLETEST_H
#define SURFEDITHOLETEST_H


#include <hxsurfedit/SurfEditTest.h>
#include <hxsurfedit/HxSurfEditWinDLLApi.h>


/// Test which detects holes on a triangular mesh
class HXSURFEDIT_API SurfEditHoleTest : public SurfEditTest {

  public:

    /// Constructor
    SurfEditHoleTest(HxSurfEdit* surfEdit, const char* label);

    /// Destructor
    ~SurfEditHoleTest();

    /// Detect holes
    int findHoles(void);

    /// Get the boundary point indices of the currently diplayed hole
    McDArray< int > getCurrentHoleBoundaryPoints(void) const;

    /// Get the boundary edge indices of the currently diplayed hole
    McDArray< int > getCurrentHoleBoundaryEdges(void) const;

    /// Get the triangle indices of the currently diplayed hole
    McDArray< int > getCurrentHoleTriangulation(void) const;

    /// Set the triangulation of the current hole
    void setHoleTriangulation(McDArray< int > &triangleIndices);

    /// Delete the triangulation of the current hole
    void deleteHoleTriangulation(int triangleGroupIdx);

    /// Get the index of the current hole
    int getCurrentTriangleGroupIdx(void) const;

  public slots:

    virtual void compute(void);

    /// Display the first hole
	virtual void first(void);

    /// Display the next hole
    virtual void next(void);

    /// Display the previous hole
    virtual void previous(void);

    /// Update the view
    void updateDisplayGroup(void);

  protected:

    HxSurfEdit* surfEdit;

    /// Index of displayed hole
    int currentTriangleGroupIdx;

    /// Normal vector for every hole
    McDArray< McVec3f > holeOrientation;

    /// Triangles surrounding the hole
    McDArray< McDArray< int > > triangleGroupList;

    /// Hole points
    McDArray< McDArray< int > > holeContourPoints;

    /// Hole edges
    McDArray< McDArray< int > > holeContourEdges;

    /// Triangulation of the hole
    McDArray< McDArray< int > > holeTriangulation;

};

#endif

/// @}
