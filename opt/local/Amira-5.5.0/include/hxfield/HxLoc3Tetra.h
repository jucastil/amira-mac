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

/// @addtogroup hxfield hxfield
/// @{
#ifndef LOC3_TETRA_H
#define LOC3_TETRA_H

#include <hxfield/HxLocation3.h>

class HxTetraGrid;

/// Defines a location within a tetrahedral grids.

class HXFIELD_API HxLoc3Tetra : public HxLocation3
{
  public:
    /// Sets location in tetrahedral grid (global search).
    virtual int set(float x, float y, float z);

    /// Moves to new location in tetrahedral grid.
    virtual int move(float x, float y, float z);

    /// Index of current tetrahedron.
    int idx;

    /// Barycentric coordinates.
    float b[4];

    /// Constructor.
    HxLoc3Tetra(HxTetraGrid* grid);

  protected:
    HxTetraGrid* theGrid;

    /// Checks, if point lies in given tetrahedron.
    int isInTetra(float x, float y, float z, int iTetra);

    /// Computes barycentric coordinates.
    void computeBarycentricCoords(float x, float y, float z, int iTetra);

    /**
        Computes the distance of the tetra center point to the face related to
        the distance of the tetra center point to a distant point in direction
        of the face normal. A value < 1 indicates that the face is closer to
        the center point as the distant point.
        Only positive return values are usable.

        @param face number of the face the distance is measured to.
        @param d vector from center point of current tetrahedron to a distant point
        @param p center point of tetrahedron
    */
    float getDistance(int face, const McVec3f& d, const McVec3f& p);
};

#endif

/// @}
